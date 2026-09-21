/**
 * @file bg_zoom.c
 * Stage zoom requests, split from bg_sub.c.
 */

#include "sf33rd/Source/Game/stage/bg_sub.h"
#include "common.h"
#include "sf33rd/Source/Game/engine/plcnt.h"
#include "sf33rd/Source/Game/engine/workuser.h"
#include "sf33rd/Source/Game/stage/bg.h"
#include "sf33rd/Source/Game/stage/bg_data.h"
#include "structs.h"

static s16 fighters_horizontal_midpoint(void) {
    return (plw[0].wu.xyz[0].disp.pos + plw[1].wu.xyz[0].disp.pos) >> 1;
}

static s16 fighters_vertical_midpoint(void) {
    return (plw[0].wu.xyz[1].disp.pos + plw[1].wu.xyz[1].disp.pos) >> 1;
}

static void request_horizontal_zoom(s16 pos) {
    zoom_request_flag = 0x100;
    scr_req_x = pos;
}

static void request_vertical_zoom(s16 pos) {
    zoom_request_flag |= 0x1000;
    scr_req_y = pos;
}

/* What a zoom request aims the screen at. */
typedef enum { ZOOM_NONE, ZOOM_P1, ZOOM_P2, ZOOM_MID, ZOOM_ZERO } ZoomTarget;

/* The bit patterns of a fighter's masked zoom word that the request logic tells
 * apart, in table order, plus a row and column for anything else. */
enum {
    ZOOM_CLASS_CLEAR,
    ZOOM_CLASS_OWN,
    ZOOM_CLASS_OTHER,
    ZOOM_CLASS_BOTH,
    ZOOM_CLASS_HOLD,
    ZOOM_CLASS_UNKNOWN,
    ZOOM_CLASS_COUNT
};

/* One screen axis: which bits of cg_zoom it reads, what they mean, and how it
 * requests a position. */
typedef struct {
    u16 mask;
    u16 own_bit;
    u16 other_bit;
    u16 both_bits;
    s16 coord;
    s16 (*midpoint)(void);
    void (*request)(s16 pos);
    const ZoomTarget (*targets)[ZOOM_CLASS_COUNT];
} ZoomAxis;

/* Row: P1's class. Column: P2's class. Horizontal bits: own 0x200, other 0x2000. */
static const ZoomTarget horizontal_targets[ZOOM_CLASS_COUNT][ZOOM_CLASS_COUNT] = {
    [ZOOM_CLASS_CLEAR] = { [ZOOM_CLASS_CLEAR] = ZOOM_NONE,
                           [ZOOM_CLASS_OWN] = ZOOM_P2,
                           [ZOOM_CLASS_OTHER] = ZOOM_P1,
                           [ZOOM_CLASS_BOTH] = ZOOM_MID,
                           [ZOOM_CLASS_HOLD] = ZOOM_NONE,
                           [ZOOM_CLASS_UNKNOWN] = ZOOM_NONE },
    [ZOOM_CLASS_OWN] = { [ZOOM_CLASS_CLEAR] = ZOOM_P1,
                         [ZOOM_CLASS_OWN] = ZOOM_MID,
                         [ZOOM_CLASS_OTHER] = ZOOM_P1,
                         [ZOOM_CLASS_BOTH] = ZOOM_P1,
                         [ZOOM_CLASS_HOLD] = ZOOM_P1,
                         [ZOOM_CLASS_UNKNOWN] = ZOOM_NONE },
    [ZOOM_CLASS_OTHER] = { [ZOOM_CLASS_CLEAR] = ZOOM_P2,
                           [ZOOM_CLASS_OWN] = ZOOM_P2,
                           [ZOOM_CLASS_OTHER] = ZOOM_MID,
                           [ZOOM_CLASS_BOTH] = ZOOM_P2,
                           [ZOOM_CLASS_HOLD] = ZOOM_P1,
                           [ZOOM_CLASS_UNKNOWN] = ZOOM_NONE },
    [ZOOM_CLASS_BOTH] = { [ZOOM_CLASS_CLEAR] = ZOOM_MID,
                          [ZOOM_CLASS_OWN] = ZOOM_P2,
                          [ZOOM_CLASS_OTHER] = ZOOM_P1,
                          [ZOOM_CLASS_BOTH] = ZOOM_MID,
                          [ZOOM_CLASS_HOLD] = ZOOM_MID,
                          [ZOOM_CLASS_UNKNOWN] = ZOOM_NONE },
    [ZOOM_CLASS_HOLD] = { [ZOOM_CLASS_CLEAR] = ZOOM_NONE,
                          [ZOOM_CLASS_OWN] = ZOOM_NONE,
                          [ZOOM_CLASS_OTHER] = ZOOM_NONE,
                          [ZOOM_CLASS_BOTH] = ZOOM_NONE,
                          [ZOOM_CLASS_HOLD] = ZOOM_NONE,
                          [ZOOM_CLASS_UNKNOWN] = ZOOM_NONE },
    [ZOOM_CLASS_UNKNOWN] = { [ZOOM_CLASS_CLEAR] = ZOOM_NONE,
                             [ZOOM_CLASS_OWN] = ZOOM_NONE,
                             [ZOOM_CLASS_OTHER] = ZOOM_NONE,
                             [ZOOM_CLASS_BOTH] = ZOOM_NONE,
                             [ZOOM_CLASS_HOLD] = ZOOM_NONE,
                             [ZOOM_CLASS_UNKNOWN] = ZOOM_NONE },
};

/* Vertical bits: own 0x100, other 0x1000. A holding P1 always requests zero. */
static const ZoomTarget vertical_targets[ZOOM_CLASS_COUNT][ZOOM_CLASS_COUNT] = {
    [ZOOM_CLASS_CLEAR] = { [ZOOM_CLASS_CLEAR] = ZOOM_NONE,
                           [ZOOM_CLASS_OWN] = ZOOM_P2,
                           [ZOOM_CLASS_OTHER] = ZOOM_P1,
                           [ZOOM_CLASS_BOTH] = ZOOM_MID,
                           [ZOOM_CLASS_HOLD] = ZOOM_ZERO,
                           [ZOOM_CLASS_UNKNOWN] = ZOOM_NONE },
    [ZOOM_CLASS_OWN] = { [ZOOM_CLASS_CLEAR] = ZOOM_P1,
                         [ZOOM_CLASS_OWN] = ZOOM_MID,
                         [ZOOM_CLASS_OTHER] = ZOOM_P1,
                         [ZOOM_CLASS_BOTH] = ZOOM_P1,
                         [ZOOM_CLASS_HOLD] = ZOOM_ZERO,
                         [ZOOM_CLASS_UNKNOWN] = ZOOM_NONE },
    [ZOOM_CLASS_OTHER] = { [ZOOM_CLASS_CLEAR] = ZOOM_P2,
                           [ZOOM_CLASS_OWN] = ZOOM_P2,
                           [ZOOM_CLASS_OTHER] = ZOOM_MID,
                           [ZOOM_CLASS_BOTH] = ZOOM_P2,
                           [ZOOM_CLASS_HOLD] = ZOOM_ZERO,
                           [ZOOM_CLASS_UNKNOWN] = ZOOM_NONE },
    [ZOOM_CLASS_BOTH] = { [ZOOM_CLASS_CLEAR] = ZOOM_MID,
                          [ZOOM_CLASS_OWN] = ZOOM_P2,
                          [ZOOM_CLASS_OTHER] = ZOOM_P1,
                          [ZOOM_CLASS_BOTH] = ZOOM_MID,
                          [ZOOM_CLASS_HOLD] = ZOOM_ZERO,
                          [ZOOM_CLASS_UNKNOWN] = ZOOM_NONE },
    [ZOOM_CLASS_HOLD] = { [ZOOM_CLASS_CLEAR] = ZOOM_ZERO,
                          [ZOOM_CLASS_OWN] = ZOOM_ZERO,
                          [ZOOM_CLASS_OTHER] = ZOOM_ZERO,
                          [ZOOM_CLASS_BOTH] = ZOOM_ZERO,
                          [ZOOM_CLASS_HOLD] = ZOOM_ZERO,
                          [ZOOM_CLASS_UNKNOWN] = ZOOM_ZERO },
    [ZOOM_CLASS_UNKNOWN] = { [ZOOM_CLASS_CLEAR] = ZOOM_NONE,
                             [ZOOM_CLASS_OWN] = ZOOM_NONE,
                             [ZOOM_CLASS_OTHER] = ZOOM_NONE,
                             [ZOOM_CLASS_BOTH] = ZOOM_NONE,
                             [ZOOM_CLASS_HOLD] = ZOOM_NONE,
                             [ZOOM_CLASS_UNKNOWN] = ZOOM_NONE },
};

static const ZoomAxis horizontal_axis = {
    0xE200, 0x200, 0x2000, 0x2200, 0, fighters_horizontal_midpoint, request_horizontal_zoom, horizontal_targets
};
static const ZoomAxis vertical_axis = {
    0xD100, 0x100, 0x1000, 0x1100, 1, fighters_vertical_midpoint, request_vertical_zoom, vertical_targets
};

static s32 zoom_class(const ZoomAxis* axis, u16 zoom) {
    u16 bits = zoom & axis->mask;

    if (bits == 0x0) {
        return ZOOM_CLASS_CLEAR;
    }
    if (bits == axis->own_bit) {
        return ZOOM_CLASS_OWN;
    }
    if (bits == axis->other_bit) {
        return ZOOM_CLASS_OTHER;
    }
    if (bits == axis->both_bits) {
        return ZOOM_CLASS_BOTH;
    }
    if (bits == 0x4000) {
        return ZOOM_CLASS_HOLD;
    }
    return ZOOM_CLASS_UNKNOWN;
}

static void select_zoom_request(const ZoomAxis* axis, u16 p1zoom, u16 p2zoom) {
    switch (axis->targets[zoom_class(axis, p1zoom)][zoom_class(axis, p2zoom)]) {
    case ZOOM_P1:
        axis->request(plw[0].wu.xyz[axis->coord].disp.pos);
        break;

    case ZOOM_P2:
        axis->request(plw[1].wu.xyz[axis->coord].disp.pos);
        break;

    case ZOOM_MID:
        axis->request(axis->midpoint());
        break;

    case ZOOM_ZERO:
        axis->request(0);
        break;

    case ZOOM_NONE:
        break;
    }
}

static void place_fighter_on_screen(s16 i) {
    if (plw[i].scr_pos_set_flag) {
        plw[i].wu.scr_mv_x = plw[i].wu.xyz[0].disp.pos;
        plw[i].wu.scr_mv_y = plw[i].wu.xyz[1].disp.pos;
    } else if (plw[i].tsukamare_f) {
        plw[i].wu.scr_mv_x = plw[(i + 1) & 1].wu.xyz[0].disp.pos;
        plw[i].wu.scr_mv_y = plw[(i + 1) & 1].wu.xyz[1].disp.pos;
    }
}

static void update_fighter_screen_positions() {
    s16 i;

    for (i = 0; i < 2; i++) {
        place_fighter_on_screen(i);
    }
}

static void begin_zoom_request_frame() {
    zoom_req_flag_old = zoom_request_flag;
    zoom_request_flag = 0;
}

static u16 higher_zoom_level(u16 p1zoom, u16 p2zoom) {
    u16 zmlv;

    zmlv = p1zoom & 0xFF;

    if (zmlv < (p2zoom & 0xFF)) {
        zmlv = p2zoom & 0xFF;
    }

    return zmlv;
}

static void publish_zoom_request_level(u16 p1zoom, u16 p2zoom) {
    zoom_request_level = higher_zoom_level(p1zoom, p2zoom);

    if (zoom_request_level) {
        zoom_request_flag |= 1;
    }
}

void check_cg_zoom() {
    u16 p1zoom;
    u16 p2zoom;
    u16 zmlv;
    u16 lookp1;
    u16 lookp2;

    p1zoom = plw[0].wu.cg_zoom;
    p2zoom = plw[1].wu.cg_zoom;

    if (bg_stop != 0 && !((p1zoom | p2zoom) & 0x4000)) {
        zmlv = higher_zoom_level(p1zoom, p2zoom);

        lookp1 = p1zoom >> 8 & 3;
        lookp2 = p2zoom >> 8 & 3;
        p1zoom = zmlv | (lookp2 << 12 | lookp1 << 8);
        p2zoom = zmlv | (lookp1 << 12 | lookp2 << 8);
    }

    begin_zoom_request_frame();

    update_fighter_screen_positions();

    select_zoom_request(&horizontal_axis, p1zoom, p2zoom);
    select_zoom_request(&vertical_axis, p1zoom, p2zoom);

    publish_zoom_request_level(p1zoom, p2zoom);
}
