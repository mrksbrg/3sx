/**
 * @file psp_textures.c
 * The PSP renderer's texture cache: which texture and palette the GU currently has
 * loaded, and the texture and palette handle entry points. Split from psp_renderer.c.
 */

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

static unsigned int current_texture_code = -1;
static void* current_texture_source = NULL;
static void* current_palette_source = NULL;

static const void* get_source_pixels(const FLTexture* texture) {
    if (texture->wkVram != NULL) {
        return texture->wkVram;
    }

    if (texture->mem_handle != 0) {
        return flPS2GetSystemBuffAdrs(texture->mem_handle);
    }

    return NULL;
}

const FLTexture* PSPTextures_Current(void) {
    const unsigned int texture_handle = LO_16_BITS(current_texture_code);

    if ((texture_handle == 0) || (texture_handle > FL_TEXTURE_MAX)) {
        fatal_error("Invalid PSP texture handle: %u", texture_handle);
    }

    return &flTexture[texture_handle - 1];
}

void PSPTextures_Reset(unsigned int texture_code) {
    current_texture_code = texture_code;
    current_texture_source = NULL;
    current_palette_source = NULL;
}

static unsigned int ps2_to_psp_format(int ps2_format) {
    switch (ps2_format) {
    case SCE_GS_PSMCT16:
        return GU_PSM_5551;
    case SCE_GS_PSMCT24:
    case SCE_GS_PSMCT32:
        return GU_PSM_8888;
    case SCE_GS_PSMT8:
        return GU_PSM_T8;
    case SCE_GS_PSMT4:
        return GU_PSM_T4;
    default:
        fatal_error("Unhandled PSP texture format: %d", ps2_format);
    }
}

void PSPRenderer_CreateTexture(unsigned int th) {
    const unsigned int texture_handle = LO_16_BITS(th);
    FLTexture* flTex;

    if ((texture_handle == 0) || (texture_handle > FL_TEXTURE_MAX)) {
        fatal_error("Invalid PSP texture handle: %u", texture_handle);
    }
}

void PSPRenderer_DestroyTexture(unsigned int texture_handle) {
    if ((texture_handle == 0) || (texture_handle > FL_TEXTURE_MAX)) {
        return;
    }
}

void PSPRenderer_UnlockTexture(unsigned int th) {
    const unsigned int texture_handle = LO_16_BITS(th);

    if ((texture_handle == 0) || (texture_handle > FL_TEXTURE_MAX)) {
        fatal_error("Invalid PSP texture handle: %u", texture_handle);
    }
}

void PSPRenderer_CreatePalette(unsigned int ph) {
    // Do nothing
}

void PSPRenderer_DestroyPalette(unsigned int palette_handle) {
    // Do nothing
}

void PSPRenderer_UnlockPalette(unsigned int ph) {
    // Do nothing
}

void PSPRenderer_SetTexture(unsigned int th) {
    int texture_handle = LO_16_BITS(th) - 1;
    FLTexture* flTex = &flTexture[texture_handle];
    int palette_handle = HI_16_BITS(th) - 1;
    FLTexture* flPal = &flPalette[palette_handle];

    void* texture_source = get_source_pixels(flTex);
    void* palette_source = get_source_pixels(flPal);

    unsigned int tex_format = ps2_to_psp_format(flTex->format);

    bool is_indexed = tex_format == GU_PSM_T4 || tex_format == GU_PSM_T8;

    if (current_palette_source != palette_source && is_indexed) {
        sceGuClutMode(GU_PSM_5551, 0, 255, 0);
        sceGuClutLoad(flPal->size / 16, palette_source);
        current_palette_source = palette_source;
    }

    if (current_texture_source != texture_source) {
        sceGuTexMode(tex_format, 0, 0, GU_FALSE);
        sceGuTexImage(0, flTex->width, flTex->height, flTex->width, texture_source);
        current_texture_source = texture_source;
    }

    current_texture_code = th;
}

#endif
