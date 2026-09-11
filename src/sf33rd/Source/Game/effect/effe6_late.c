/**
 * @file effe6_late.c
 * Late state handlers for effect E6.
 */

#include "sf33rd/Source/Game/effect/effe6_late.h"
#include "sf33rd/Source/Game/effect/effe6.h"
#include "sf33rd/Source/Game/effect/effe6_internal.h"
#include "bin2obj/char_table.h"
#include "common.h"
#include "sf33rd/Source/Game/effect/effect.h"
#include "sf33rd/Source/Game/ending/end_00.h"
#include "sf33rd/Source/Game/ending/end_data.h"
#include "sf33rd/Source/Game/engine/caldir.h"
#include "sf33rd/Source/Game/engine/charset.h"
#include "sf33rd/Source/Game/engine/workuser.h"
#include "sf33rd/Source/Game/rendering/color3rd.h"
#include "sf33rd/Source/Game/rendering/texcash.h"
#include "sf33rd/Source/Game/rendering/texgroup.h"
#include "sf33rd/Source/Game/stage/bg.h"
#include "sf33rd/Source/Game/stage/ta_sub.h"
#include "sf33rd/Source/Game/system/work_sys.h"

void effe6_0026(WORK_Other* ewk) {
    mark_effe6_for_cleanup_if_stale(ewk);

    switch (ewk->wu.routine_no[1]) {
    case 0:
        effe6_init_common(ewk);
        disp_pos_trans_entry(ewk);
        break;

    case 1:
        char_move(&ewk->wu);

        if (ewk->wu.xyz[1].disp.pos < 152) {
            ewk->wu.routine_no[1]++;
        }

        /* fallthrough */

    case 2:
        disp_pos_trans_entry(ewk);
        break;

    default:
        push_effect_work(&ewk->wu);
        break;
    }
}



static void grow_effe6_0029_marker(WORK_Other* ewk) {
    ewk->wu.old_rno[2]--;

    if (ewk->wu.old_rno[2] <= 0) {
        ewk->wu.old_rno[2] = 5;
        ewk->wu.my_mr.size.x++;
        ewk->wu.my_mr.size.y++;

        if (ewk->wu.my_mr.size.x >= 127) {
            ewk->wu.routine_no[1]++;
            ewk->wu.my_mr.size.x = 127;
            ewk->wu.my_mr.size.y = 127;
        }
    }
}

void effe6_0029(WORK_Other* ewk) {
    mark_effe6_for_cleanup_if_stale(ewk);

    switch (ewk->wu.routine_no[1]) {
    case 0:
        effe6_init_common(ewk);
        ewk->wu.old_rno[2] = 5;
        ewk->wu.my_mr_flag = 1;
        ewk->wu.my_mr.size.x = 63;
        ewk->wu.my_mr.size.y = 63;
        disp_pos_trans_entry5(ewk);
        break;

    case 1:
        char_move(&ewk->wu);

        if (ewk->wu.xyz[0].disp.pos < 224) {
            ewk->wu.routine_no[2] = 99;
        } else {
            grow_effe6_0029_marker(ewk);
        }

        disp_pos_trans_entry5(ewk);
        break;

    case 2:
        disp_pos_trans_entry5(ewk);
        break;

    default:
        push_effect_work(&ewk->wu);
        break;
    }
}

static void start_effe6_0030_fade(WORK_Other* ewk) {
    s16 i;

    ewk->wu.routine_no[1]++;

    for (i = 0; i < 64; i++) {
        ColorRAM[327][i] = ColorRAM[343][i];
    }

    for (i = 0; i < 64; i++) {
        ColorRAM[328][i] = ColorRAM[343][i];
    }

    for (i = 0; i < 64; i++) {
        ColorRAM[329][i] = ColorRAM[343][i];
    }

    for (i = 0; i < 64; i++) {
        ColorRAM[330][i] = ColorRAM[343][i];
    }

    ewk->wu.disp_flag = 2;
    ewk->wu.blink_timing = 1;
    ewk->wu.old_rno[2] = 30;
    palUpdateGhostCP3(0x147, 4);
}

static void update_effe6_0030_color(WORK_Other* ewk) {
    if (end_w.r_no_2 == 4 && bg_w.bgw[0].r_no_1 == 1) {
        switch (bg_w.bgw[0].l_limit) {
        case 0:
            ewk->wu.my_col_code = 0x130;
            break;

        case 1:
            ewk->wu.my_col_code = 0x134;
            break;

        case 2:
            ewk->wu.my_col_code = 0x138;
            break;

        case 3:
            ewk->wu.my_col_code = 0x13C;
            break;
        }
    }
}

void effe6_0030(WORK_Other* ewk) {
    mark_effe6_for_cleanup_if_stale(ewk);

    switch (ewk->wu.routine_no[1]) {
    case 0:
        effe6_init_common(ewk);
        disp_pos_trans_entry(ewk);
        break;

    case 1:
        update_effe6_0030_color(ewk);

        if (end_etc_flag) {
            start_effe6_0030_fade(ewk);
        }

        disp_pos_trans_entry(ewk);
        break;

    case 2:
        ewk->wu.old_rno[2]--;

        if (ewk->wu.old_rno[2] < 0) {
            ewk->wu.routine_no[2] = 99;
        }

        disp_pos_trans_entry(ewk);
        break;

    default:
        push_effect_work(&ewk->wu);
        break;
    }
}

const s32 gill_range[7] = { 0x900000, 0x900000, 0x100000, 0x900000, 0x900000, 0x200000, 0x50000 };

static void update_effe6_0031_rise(WORK_Other* ewk) {
    ewk->wu.xyz[1].cal += gill_range[0] / gill_time[0];

    if (!(--ewk->wu.old_rno[5])) {
        ewk->wu.routine_no[1]++;
    }

    disp_pos_trans_entry(ewk);
}

void effe6_0031(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case 0:
        effe6_init_common(ewk);
        ewk->wu.old_rno[5] = gill_time[0];
        disp_pos_trans_entry(ewk);
        break;

    case 1:
        update_effe6_0031_rise(ewk);
        break;

    case 2:
        if (end_etc_flag) {
            ewk->wu.routine_no[1]++;
            ewk->wu.old_rno[5] = gill_time[1];
            end_etc_flag = 0;
        }

        disp_pos_trans_entry(ewk);
        break;

    case 3:
        ewk->wu.xyz[1].cal -= gill_range[1] / gill_time[1];

        if (!ewk->wu.old_rno[5]--) {
            ewk->wu.routine_no[1]++;
        }

        disp_pos_trans_entry(ewk);
        break;

    case 4:
        mark_effe6_for_cleanup_if_stale(ewk);

        disp_pos_trans_entry(ewk);
        break;
    }
}


static void update_effe6_0033_fade(WORK_Other* ewk) {
    mark_effe6_for_cleanup_if_stale(ewk);

    ewk->wu.my_clear_level -= 256 / gill_time[7];

    if (ewk->wu.my_clear_level <= 0) {
        ewk->wu.routine_no[1]++;
        ewk->wu.my_clear_level = 0;
    }

    disp_pos_trans_entry(ewk);
}

void effe6_0033(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case 0:
        effe6_init_common(ewk);
        ewk->wu.old_rno[5] = end_0_1_time[0] + gill_time[0];
        ewk->wu.my_clear_level = 0xFF;
        disp_pos_trans_entry(ewk);
        break;

    case 1:
        mark_effe6_for_cleanup_if_stale(ewk);

        if (!ewk->wu.old_rno[5]--) {
            ewk->wu.routine_no[1]++;
        }

        disp_pos_trans_entry(ewk);
        break;

    case 2:
        update_effe6_0033_fade(ewk);
        break;

    case 3:
        mark_effe6_for_cleanup_if_stale(ewk);

        disp_pos_trans_entry(ewk);
        break;
    }
}
