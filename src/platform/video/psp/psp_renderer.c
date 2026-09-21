#if CRS_VIDEO_DRIVER_PSP

#include "platform/video/psp/psp_renderer.h"
#include "platform/video/psp/psp_textures.h"

#include "common.h"
#include "port/utils.h"
#include "sf33rd/AcrSDK/common/plcommon.h"
#include "sf33rd/AcrSDK/ps2/flps2etc.h"
#include "sf33rd/AcrSDK/ps2/flps2render.h"
#include "sf33rd/AcrSDK/ps2/foundaps2.h"

#include <libgraph.h>
#include <pspdisplay.h>
#include <pspgu.h>
#include <pspkernel.h>

#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 272
#define BUFFER_WIDTH 512
#define GAME_WIDTH 384
#define GAME_HEIGHT 224

#define DISPLAY_AREA_WIDTH 363
#define DISPLAY_AREA_HEIGHT SCREEN_HEIGHT
#define DISPLAY_OFFSET_X ((SCREEN_WIDTH - DISPLAY_AREA_WIDTH) / 2)
#define DISPLAY_OFFSET_Y 0

typedef struct PSPVertex {
    short u;
    short v;
    unsigned int color;
    float x;
    float y;
    float z;
} PSPVertex;

typedef struct PSPColorVertex {
    unsigned int color;
    float x;
    float y;
    float z;
} PSPColorVertex;

static unsigned int __attribute__((aligned(64))) display_list[0x40000];
static void* frame_buffers[2] = { NULL, NULL };
static void* depth_buffer = NULL;
static int current_back_buffer = 0;
static bool initialized = false;

static bool textured_enabled = false;
static bool full_screen_scissor_enabled = false;

static unsigned int argb_to_abgr(unsigned int color) {
    return (color & 0xFF00FF00u) | ((color >> 16) & 0xFFu) | ((color & 0xFFu) << 16);
}

static float snap_screen_coord(float value) {
    return (float)((int)value);
}

static float game_to_screen_x(float value) {
    return (float)DISPLAY_OFFSET_X + value * ((float)DISPLAY_AREA_WIDTH / (float)GAME_WIDTH);
}

static float game_to_screen_y(float value) {
    return (float)DISPLAY_OFFSET_Y + value * ((float)DISPLAY_AREA_HEIGHT / (float)GAME_HEIGHT);
}

static short texel_coord(float normalized, float extent) {
    return (short)(normalized * extent + 0.5f);
}

static void setup_full_screen_scissor(bool full_screen_scissor) {
    if (full_screen_scissor == full_screen_scissor_enabled) {
        return;
    }

    if (full_screen_scissor) {
        sceGuScissor(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    } else {
        sceGuScissor(DISPLAY_OFFSET_X, DISPLAY_OFFSET_Y, DISPLAY_AREA_WIDTH, DISPLAY_AREA_HEIGHT);
    }
    full_screen_scissor_enabled = full_screen_scissor;
}

static void setup_draw_textured(bool textured) {
    if (textured == textured_enabled) {
        return;
    }

    if (textured) {
        sceGuEnable(GU_TEXTURE_2D);
    } else {
        sceGuDisable(GU_TEXTURE_2D);
    }
    textured_enabled = textured;
}

static void fill_textured_vertices(PSPVertex* vertices, const Sprite* sprite, unsigned int color) {
    const FLTexture* texture = PSPTextures_Current();
    const float texture_width = (float)texture->width;
    const float texture_height = (float)texture->height;

    for (int i = 0; i < 4; i++) {
        vertices[i].u = texel_coord(sprite->t[i].s, texture_width);
        vertices[i].v = texel_coord(sprite->t[i].t, texture_height);
        vertices[i].color = argb_to_abgr(color);
        vertices[i].x = snap_screen_coord(game_to_screen_x(sprite->v[i].x));
        vertices[i].y = snap_screen_coord(game_to_screen_y(sprite->v[i].y));
        vertices[i].z = flPS2ConvScreenFZ(sprite->v[i].z);
    }
}

static void draw_textured_quad(const Sprite* sprite, unsigned int color) {
    PSPVertex* vertices = sceGuGetMemory(4 * sizeof(PSPVertex));

    fill_textured_vertices(vertices, sprite, color);
    setup_full_screen_scissor(false);
    setup_draw_textured(true);
    sceGuDrawArray(
        GU_TRIANGLE_STRIP, GU_TEXTURE_16BIT | GU_COLOR_8888 | GU_VERTEX_32BITF | GU_TRANSFORM_2D, 4, 0, vertices);
}

/* The two corners of a textured sprite rectangle and the colour it is drawn
 * with, in the order draw_textured_sprite_rect took them. */
typedef struct {
    float x0;
    float y0;
    float z0;
    float s0;
    float t0;
    float x1;
    float y1;
    float s1;
    float t1;
    unsigned int color;
} TexturedSpriteRect;

static void draw_textured_sprite_rect(const TexturedSpriteRect* r) {
    const float x0 = r->x0;
    const float y0 = r->y0;
    const float z0 = r->z0;
    const float s0 = r->s0;
    const float t0 = r->t0;
    const float x1 = r->x1;
    const float y1 = r->y1;
    const float s1 = r->s1;
    const float t1 = r->t1;
    const unsigned int color = r->color;

    const FLTexture* texture = PSPTextures_Current();
    const float texture_width = (float)texture->width;
    const float texture_height = (float)texture->height;
    PSPVertex* vertices = sceGuGetMemory(2 * sizeof(PSPVertex));
    const unsigned int abgr = argb_to_abgr(color);

    vertices[0].u = texel_coord(s0, texture_width);
    vertices[0].v = texel_coord(t0, texture_height);
    vertices[0].color = abgr;
    vertices[0].x = snap_screen_coord(game_to_screen_x(x0));
    vertices[0].y = snap_screen_coord(game_to_screen_y(y0));
    vertices[0].z = flPS2ConvScreenFZ(z0);

    vertices[1].u = texel_coord(s1, texture_width);
    vertices[1].v = texel_coord(t1, texture_height);
    vertices[1].color = abgr;
    vertices[1].x = snap_screen_coord(game_to_screen_x(x1));
    vertices[1].y = snap_screen_coord(game_to_screen_y(y1));
    vertices[1].z = flPS2ConvScreenFZ(z0);

    setup_full_screen_scissor(false);
    setup_draw_textured(true);
    sceGuDrawArray(GU_SPRITES, GU_TEXTURE_16BIT | GU_COLOR_8888 | GU_VERTEX_32BITF | GU_TRANSFORM_2D, 2, 0, vertices);
}

static void submit_solid_quad_vertices(const PSPColorVertex* vertices, bool full_screen_scissor) {
    setup_full_screen_scissor(full_screen_scissor);
    setup_draw_textured(false);

    sceGuDrawArray(GU_TRIANGLE_STRIP, GU_COLOR_8888 | GU_VERTEX_32BITF | GU_TRANSFORM_2D, 4, 0, vertices);
}

static void draw_solid_quad_vertices(const Quad* quad, unsigned int color) {
    PSPColorVertex* vertices = sceGuGetMemory(4 * sizeof(PSPColorVertex));

    for (int i = 0; i < 4; i++) {
        vertices[i].color = color;
        vertices[i].x = snap_screen_coord(game_to_screen_x(quad->v[i].x));
        vertices[i].y = snap_screen_coord(game_to_screen_y(quad->v[i].y));
        vertices[i].z = flPS2ConvScreenFZ(quad->v[i].z);
    }

    submit_solid_quad_vertices(vertices, false);
}

static void draw_black_bar(float x0, float y0, float x1, float y1) {
    PSPColorVertex* vertices = sceGuGetMemory(4 * sizeof(PSPColorVertex));
    const unsigned int black_color = 0xFF000000;

    vertices[0].color = black_color;
    vertices[0].x = x0;
    vertices[0].y = y0;
    vertices[0].z = 0.0f;

    vertices[1].color = black_color;
    vertices[1].x = x1;
    vertices[1].y = y0;
    vertices[1].z = 0.0f;

    vertices[2].color = black_color;
    vertices[2].x = x0;
    vertices[2].y = y1;
    vertices[2].z = 0.0f;

    vertices[3].color = black_color;
    vertices[3].x = x1;
    vertices[3].y = y1;
    vertices[3].z = 0.0f;

    submit_solid_quad_vertices(vertices, true);
}

static void draw_pillarbox_bars(void) {
    const float left_width = DISPLAY_OFFSET_X;
    const float right_start = DISPLAY_OFFSET_X + DISPLAY_AREA_WIDTH;

    if (left_width > 0.0f) {
        draw_black_bar(0.0f, 0.0f, left_width, (float)SCREEN_HEIGHT);
    }

    if (right_start < (float)SCREEN_WIDTH) {
        draw_black_bar(right_start, 0.0f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
    }
}

void PSPRenderer_Init() {
    if (initialized) {
        return;
    }

    sceGuInit();

    frame_buffers[0] = guGetStaticVramBuffer(BUFFER_WIDTH, SCREEN_HEIGHT, GU_PSM_8888);
    frame_buffers[1] = guGetStaticVramBuffer(BUFFER_WIDTH, SCREEN_HEIGHT, GU_PSM_8888);
    depth_buffer = guGetStaticVramBuffer(BUFFER_WIDTH, SCREEN_HEIGHT, GU_PSM_4444);

    sceGuStart(GU_DIRECT, display_list);
    sceGuDrawBuffer(GU_PSM_8888, frame_buffers[0], BUFFER_WIDTH);
    sceGuDispBuffer(SCREEN_WIDTH, SCREEN_HEIGHT, frame_buffers[1], BUFFER_WIDTH);
    sceGuDepthBuffer(depth_buffer, BUFFER_WIDTH);
    sceGuOffset(2048 - (SCREEN_WIDTH / 2), 2048 - (SCREEN_HEIGHT / 2));
    sceGuViewport(2048, 2048, SCREEN_WIDTH, SCREEN_HEIGHT);
    sceGuScissor(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    sceGuEnable(GU_SCISSOR_TEST);
    sceGuDisable(GU_CULL_FACE);
    sceGuDisable(GU_LIGHTING);
    sceGuDisable(GU_CLIP_PLANES);
    sceGuEnable(GU_BLEND);
    sceGuBlendFunc(GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0, 0);
    sceGuEnable(GU_ALPHA_TEST);
    sceGuAlphaFunc(GU_GREATER, 0, 0xFF);
    sceGuEnable(GU_DEPTH_TEST);
    sceGuDepthFunc(GU_GEQUAL);
    sceGuTexFunc(GU_TFX_MODULATE, GU_TCC_RGBA);
    sceGuTexFilter(GU_NEAREST, GU_NEAREST);
    sceGuTexWrap(GU_CLAMP, GU_CLAMP);
    sceGuEnable(GU_TEXTURE_2D);
    sceGuFinish();
    sceGuSync(GU_SYNC_FINISH, GU_SYNC_WHAT_DONE);
    sceDisplayWaitVblankStart();
    sceGuDisplay(GU_TRUE);

    initialized = true;
    current_back_buffer = 0;
}

void PSPRenderer_Shutdown() {
    if (!initialized) {
        return;
    }

    sceGuDisplay(GU_FALSE);
    sceGuTerm();
    initialized = false;

    PSPTextures_Reset(0);
}

void PSPRenderer_BeginFrame() {
    const unsigned int clear_color = argb_to_abgr(flPs2State.FrameClearColor);

    sceGuStart(GU_DIRECT, display_list);
    sceGuDrawBufferList(GU_PSM_8888, frame_buffers[current_back_buffer], BUFFER_WIDTH);
    sceGuOffset(2048 - (SCREEN_WIDTH / 2), 2048 - (SCREEN_HEIGHT / 2));
    sceGuViewport(2048, 2048, SCREEN_WIDTH, SCREEN_HEIGHT);
    setup_full_screen_scissor(true);
    sceGuEnable(GU_SCISSOR_TEST);
    sceGuClearColor(0xFF000000);
    sceGuClearDepth(0);
    sceGuClear(GU_COLOR_BUFFER_BIT | GU_DEPTH_BUFFER_BIT);

    setup_full_screen_scissor(false);
    sceGuEnable(GU_SCISSOR_TEST);
    sceGuClearColor(clear_color);
    sceGuClear(GU_COLOR_BUFFER_BIT | GU_DEPTH_BUFFER_BIT);

    PSPTextures_Reset(-1);

    setup_draw_textured(true);
}

void PSPRenderer_RenderFrame() {
    // Do nothing
}

void PSPRenderer_EndFrame() {
    draw_pillarbox_bars();
    sceGuFinish();
    sceGuSync(GU_SYNC_FINISH, GU_SYNC_WHAT_DONE);
    sceDisplayWaitVblankStart();
    sceGuSwapBuffers();
    current_back_buffer ^= 1;
}

void PSPRenderer_DrawTexturedQuad(const Sprite* sprite, unsigned int color) {
    draw_textured_quad(sprite, color);
}

void PSPRenderer_DrawSprite(const Sprite* sprite, unsigned int color) {
    draw_textured_sprite_rect(&(TexturedSpriteRect) { sprite->v[0].x,
                                                      sprite->v[0].y,
                                                      sprite->v[0].z,
                                                      sprite->t[0].s,
                                                      sprite->t[0].t,
                                                      sprite->v[3].x,
                                                      sprite->v[3].y,
                                                      sprite->t[3].s,
                                                      sprite->t[3].t,
                                                      color });
}

void PSPRenderer_DrawSprite2(const Sprite2* sprite2) {
    draw_textured_sprite_rect(&(TexturedSpriteRect) { sprite2->v[0].x,
                                                      sprite2->v[0].y,
                                                      sprite2->v[0].z,
                                                      sprite2->t[0].s,
                                                      sprite2->t[0].t,
                                                      sprite2->v[1].x,
                                                      sprite2->v[1].y,
                                                      sprite2->t[1].s,
                                                      sprite2->t[1].t,
                                                      sprite2->vertex_color });
}

void PSPRenderer_DrawSolidQuad(const Quad* quad, unsigned int color) {
    draw_solid_quad_vertices(quad, argb_to_abgr(color));
}

#endif
