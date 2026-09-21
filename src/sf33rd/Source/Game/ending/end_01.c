/**
 * @file end_01.c
 * Alex's Ending
 */

#include "common.h"
#include "sf33rd/Source/Game/effect/effe6.h"
#include "sf33rd/Source/Game/effect/efff9.h"
#include "sf33rd/Source/Game/ending/end_data.h"
#include "sf33rd/Source/Game/ending/end_main.h"
#include "sf33rd/Source/Game/sound/se.h"
#include "sf33rd/Source/Game/stage/bg.h"
#include "sf33rd/Source/Game/stage/bg_data.h"
#include "sf33rd/Source/Game/system/sys_sub.h"
#include "sf33rd/Source/Game/ui/sc_sub.h"

void end_100_move();

void end_100_0000();
void end_100_0001();
void end_100_0002();
void end_100_0004();

const s16 timer_1_tbl[5] = { 1200, 900, 1260, 240, 360 };

const s16 end_1_pos[5][2] = { { 256, 768 }, { 256, 512 }, { 768, 512 }, { 256, 256 }, { 768, 240 } };

void end_01000(s16 pl_num) {
    switch (end_w.r_no_1) {
    case 0:
        end_w.r_no_1++;
        end_w.r_no_2 = 0;
        common_end_init00(pl_num);
        end_w.timer = timer_1_tbl[end_w.r_no_2];
        common_end_init01();
        BGM_Request(0x31);
        break;

    case 1:
        end_w.timer--;

        if (end_w.timer < 0) {
            end_w.r_no_2++;

            if (end_w.r_no_2 >= 5) {
                end_w.r_no_1++;
                end_w.end_flag = 1;
                fadeout_to_staff_roll();
                end_scn_pos_set2();
                end_bg_pos_hosei2();
                end_fam_set2();
                break;
            }

            end_w.timer = timer_1_tbl[end_w.r_no_2];
            bg_w.bgw[0].r_no_1 = 0;
            bg_w.bgw[1].r_no_1 = 0;
        }

        end_100_move();
        /* fallthrough */

    case 2:
        end_scn_pos_set2();
        end_bg_pos_hosei2();
        end_fam_set2();
        break;
    }
}

void end_100_move() {
    void (*end_100_jp[5])() = { end_100_0000, end_100_0001, end_100_0002, end_100_0002, end_100_0004 };
    bgw_ptr = &bg_w.bgw[0];
    end_100_jp[end_w.r_no_2]();
}

static void end_100_0000_wait_for_free(BGW* bgw) {
    bgw->free--;

    if (bgw->free < 1) {
        bgw->r_no_1++;
    }
}

static void end_100_0000_pan_camera(BGW* bgw) {
    bgw->xy[0].cal += 0x8000;

    if (384 < bgw->xy[0].disp.pos) {
        bgw->r_no_1++;
        bgw->xy[0].cal = 0x1800000;
        bgw->free = 0x5A;
    }

    bgw->abs_x = bgw->xy[0].disp.pos;
}

static void end_100_0000_ask_for_fade(BGW* bgw) {
    if (Request_Fade(3)) {
        bgw->r_no_1++;
        end_no_cut = 1;
    }
}

static void end_100_0000_raise_panel(BGW* bgw) {
    if (end_fade_complete()) {
        bgw->r_no_1++;
        bgw->free = 0x28;
        overwrite_panel(0xFFFFFFFF, 0x17);
    }
}

static void end_100_0000_hold_panel(BGW* bgw) {
    overwrite_panel(0xFFFFFFFF, 0x17);
    bgw->free--;

    if (bgw->free < 0) {
        bgw->r_no_1++;
        end_w.timer = 0;
    }
}

void end_100_0000() {
    switch (bgw_ptr->r_no_1) {
    case 0:
        bgw_ptr->r_no_1++;
        bgw_ptr->xy[0].disp.pos = end_1_pos[end_w.r_no_2][0];
        bgw_ptr->xy[1].disp.pos = end_1_pos[end_w.r_no_2][1];
        bgw_ptr->abs_x = bgw_ptr->xy[0].disp.pos;
        bgw_ptr->abs_y = 0;
        Bg_On_W(1);
        effect_E6_init(0xA1);
        Rewrite_End_Message(1);
        bgw_ptr->free = 0x46;
        break;

    case 1:
        end_100_0000_wait_for_free(bgw_ptr);
        break;

    case 2:
        end_100_0000_pan_camera(bgw_ptr);
        break;

    case 3:
        end_100_0000_wait_for_free(bgw_ptr);
        break;

    case 4:
        end_100_0000_ask_for_fade(bgw_ptr);
        break;

    case 5:
        end_100_0000_raise_panel(bgw_ptr);
        break;

    case 6:
        end_100_0000_hold_panel(bgw_ptr);
    }
}

void end_100_0001() {
    switch (bgw_ptr->r_no_1) {
    case 0:
        overwrite_panel(0xFFFFFFFF, 0x17);
        if (Request_Fade(2)) {
            bgw_ptr->r_no_1 += 1;
            end_no_cut = 1;
            bgw_ptr->xy[0].disp.pos = end_1_pos[end_w.r_no_2][0];
            bgw_ptr->xy[1].disp.pos = end_1_pos[end_w.r_no_2][1];
            bgw_ptr->abs_x = 512;
            effect_E6_init(0xA3);
            Rewrite_End_Message(2);
        }

        break;

    case 1:
        if (end_fade_complete()) {
            bgw_ptr->r_no_1 += 1;
            end_no_cut = 0;
        }

        break;

    case 2:
        break;
    }
}

void end_100_0002() {
    switch (bgw_ptr->r_no_1) {
    case 0:
        bgw_ptr->r_no_1++;
        bgw_ptr->xy[0].disp.pos = end_1_pos[end_w.r_no_2][0];
        bgw_ptr->xy[1].disp.pos = end_1_pos[end_w.r_no_2][1];

        switch (end_w.r_no_2) {
        case 2:
            effect_E6_init(0xA4U);
            Rewrite_End_Message(3U);
            break;

        case 3:
            Rewrite_End_Message(4U);
            break;
        }

        break;

    case 1:
        break;
    }
}

void end_100_0004() {
    switch (bgw_ptr->r_no_1) {
    case 0:
        bgw_ptr->r_no_1 += 1;
        bgw_ptr->xy[0].disp.pos = end_1_pos[end_w.r_no_2][0];
        bgw_ptr->xy[1].disp.pos = end_1_pos[end_w.r_no_2][1];
        bgw_ptr->abs_y = bgw_ptr->xy[1].disp.pos;
        effect_E6_init(0xA6);
        Rewrite_End_Message(5);
        end_fade_flag = 1;
        end_fade_timer = timer_1_tbl[end_w.r_no_2] - 120;
        bgw_ptr->speed_y = 0x4000;
        break;

    case 1:
        bgw_ptr->xy[1].cal += bgw_ptr->speed_y;

        if ((bgw_ptr->xy[1].disp.pos) > 272) {
            bgw_ptr->r_no_1++;
        }

        bgw_ptr->abs_y = bgw_ptr->xy[1].disp.pos;
        /* fallthrough */

    case 2:
        break;
    }
}
