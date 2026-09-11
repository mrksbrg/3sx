/**
 * @file effe6_early.c
 * Early state handlers for effect E6.
 */

#include "sf33rd/Source/Game/effect/effe6_early.h"
#include "sf33rd/Source/Game/effect/effe6_internal.h"
#include "sf33rd/Source/Game/effect/effe6_middle.h"
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

static s16 select_effe6_0000_color(s16 active_color) {
    return bg_w.bgw[0].l_limit ? active_color : 0x12C;
}

static void update_effe6_0000_color(WORK_Other* ewk) {
    if (End_PL == 17) {
    switch (ewk->wu.type) {
    case 0x74:
        ewk->wu.my_col_code = select_effe6_0000_color(0x12E);
        break;

    case 0x75:
        ewk->wu.my_col_code = select_effe6_0000_color(0x130);
        break;

    case 0x76:
        ewk->wu.my_col_code = select_effe6_0000_color(0x132);
        break;

    case 0x78:
        ewk->wu.my_col_code = select_effe6_0000_color(0x138);
        break;

    case 0xA2:
        ewk->wu.my_col_code = select_effe6_0000_color(0x12D);
        break;
        }
    }
}

void effe6_0000(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case 0:
        effe6_init_common(ewk);
        disp_pos_trans_entry(ewk);
        break;

    case 1:
        mark_effe6_for_cleanup_if_stale(ewk);
        update_effe6_0000_color(ewk);
        disp_pos_trans_entry(ewk);
    }
}

void effe6_0001(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case 0:
        effe6_init_common(ewk);
        disp_pos_trans_entry(ewk);
        break;

    case 1:
        if (ewk->wu.old_rno[6] < end_w.r_no_2) {
            ewk->wu.routine_no[2] = 99;
        } else {
            char_move(&ewk->wu);
        }

        disp_pos_trans_entry(ewk);
        break;
    }
}

static void update_effe6_0002_animation(WORK_Other* ewk) {
    if (ewk->wu.old_rno[6] < end_w.r_no_2) {
        ewk->wu.routine_no[2] = 99;
    } else {
        char_move(&ewk->wu);

        if (ewk->wu.cg_type) {
            end_etc_flag = 1;
        }
    }
}

void effe6_0002(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case 0:
        effe6_init_common(ewk);
        break;

    case 1:
        update_effe6_0002_animation(ewk);
        disp_pos_trans_entry(ewk);
        break;
    }
}

void effe6_0003(WORK_Other* ewk) {
    mark_effe6_for_cleanup_if_stale(ewk);

    switch (ewk->wu.routine_no[1]) {
    case 0:
        effe6_init_common(ewk);
        break;

    case 1:
        char_move(&ewk->wu);

        if (ewk->wu.cg_type) {
            ewk->wu.routine_no[2] = 99;
        }

        disp_pos_trans_entry(ewk);
        break;
    }
}

static void update_effe6_0004_blink(WORK_Other* ewk) {
    if (ewk->wu.old_rno[6] < end_w.r_no_2) {
        ewk->wu.routine_no[2] = 99;
    } else {
        ewk->wu.old_rno[5]--;

        if (ewk->wu.old_rno[5] <= 0) {
            ewk->wu.disp_flag ^= 1;
            ewk->wu.old_rno[5] = ewk->wu.old_rno[2];
        }
    }
}

void effe6_0004(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case 0:
        effe6_init_common(ewk);
        ewk->wu.old_rno[2] = 1;
        ewk->wu.old_rno[5] = 1;
        disp_pos_trans_entry(ewk);
        break;

    case 1:
        update_effe6_0004_blink(ewk);
        disp_pos_trans_entry(ewk);
        break;
    }
}

void effe6_0005(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case 0:
        effe6_init_common(ewk);
        disp_pos_trans_entry(ewk);
        break;

    case 1:
        if (ewk->wu.old_rno[6] < end_w.r_no_2) {
            ewk->wu.routine_no[1]++;
            ewk->wu.mvxy.a[0].sp = 0x80000;
            ewk->wu.mvxy.d[0].sp = 0x40000;
        }

        disp_pos_trans_entry(ewk);
        break;

    case 2:
        add_x_sub(&ewk->wu);

        if (ewk->wu.xyz[0].disp.pos > -1216) {
            ewk->wu.routine_no[2] = 99;
            ewk->wu.disp_flag = 0;
            end_etc_flag = 1;
        }

        disp_pos_trans_entry(ewk);
        break;
    }
}

static void update_effe6_0006_position(WORK_Other* ewk) {
    s16 work;

    if (ewk->wu.old_rno[6] < end_w.r_no_2) {
        ewk->wu.routine_no[2] = 99;
    } else {
        if (ewk->wu.type == 73) {
            work = ewk->wu.old_rno[2] - 704;
        } else {
            work = ewk->wu.old_rno[2] - 384;
        }

        if (work > bg_w.bgw[ewk->wu.my_family - 1].xy[0].disp.pos) {
            ewk->wu.routine_no[2] = 99;
        }
    }
}

void effe6_0006(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case 0:
        effe6_init_common(ewk);
        ewk->wu.old_rno[2] = ewk->wu.xyz[0].disp.pos;
        disp_pos_trans_entry(ewk);
        break;

    case 1:
        update_effe6_0006_position(ewk);
        disp_pos_trans_entry(ewk);
        break;
    }
}

static void set_effe6_0007_color(WORK_Other* ewk) {
    switch (ewk->wu.type) {
    case 22:
        ewk->wu.my_col_code = 0x12C;
        break;

    case 23:
        ewk->wu.my_col_code = 0x12D;
        break;

    case 24:
    case 27:
    case 28:
        ewk->wu.my_col_code = 0x12E;
        break;
    }
}

static void display_effe6_0007(WORK_Other* ewk) {
    switch (ewk->wu.type) {
    case 22:
    case 23:
    case 24:
    case 27:
    case 28:
        disp_pos_trans_entry_r4(ewk);
        break;

    default:
        disp_pos_trans_entry_r(ewk);
        break;
    }
}

void effe6_0007(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case 0:
        set_effe6_0007_color(ewk);
        ewk->wu.my_col_mode = 0x200;
        effe6_init_common(ewk);
        disp_pos_trans_entry(ewk);
        break;

    case 1:
        if (ewk->wu.old_rno[6] < end_w.r_no_2) {
            ewk->wu.routine_no[2] = 99;
        } else if (ewk->wu.routine_no[0] & 1) {
            char_move(&ewk->wu);
        }

        display_effe6_0007(ewk);
        break;
    }
}

void effe6_0009(WORK_Other* ewk) {
    mark_effe6_for_cleanup_if_stale(ewk);

    switch (ewk->wu.routine_no[1]) {
    case 0:
        effe6_init_common(ewk);
        disp_pos_trans_entry(ewk);
        break;

    case 1:
        ewk->wu.xyz[0].cal -= 0xB000;
        ewk->wu.xyz[1].cal += -0x1A000;

        if (ewk->wu.xyz[1].disp.pos < -199) {
            ewk->wu.routine_no[1]++;
            bg_w.bgw[0].r_no_1++;
            bg_w.bgw[1].r_no_1++;
        }

        char_move(&ewk->wu);
        disp_pos_trans_entry(ewk);
        break;

    case 2:
        char_move(&ewk->wu);
        ewk->wu.xyz[1].cal += 0x800;
        disp_pos_trans_entry(ewk);
        break;
    }
}

void effe6_0010(WORK_Other* ewk) {
    mark_effe6_for_cleanup_if_stale(ewk);

    switch (ewk->wu.routine_no[1]) {
    case 0:
        ewk->wu.old_rno[2] = 0;
        ewk->wu.old_rno[5] = 8;
        ewk->wu.my_col_mode = 0x200;
        effe6_init_common(ewk);
        ewk->wu.extra_col = 0x2149;
        disp_pos_trans_entry(ewk);
        break;

    case 1:
        ewk->wu.xyz[1].cal += 0x20000;

        if (ewk->wu.xyz[1].disp.pos > 160) {
            ewk->wu.routine_no[1]++;
            ewk->wu.xyz[1].cal = 0xA00000;
            bg_w.bgw[0].r_no_1++;
        }

        /* fallthrough */

    case 2:
        effe6_0010_sub(ewk);
        /* fallthrough */

    case 3:
        disp_pos_trans_entry5(ewk);
        break;
    }
}
