/**
 * @file effe6_early_variant.c
 * Variant early-state handlers for effect E6.
 */

#include "sf33rd/Source/Game/effect/effe6_early_variant.h"
#include "sf33rd/Source/Game/effect/effe6_internal.h"
#include "common.h"
#include "sf33rd/Source/Game/ending/end_00.h"
#include "sf33rd/Source/Game/ending/end_data.h"
#include "sf33rd/Source/Game/engine/charset.h"
#include "sf33rd/Source/Game/engine/workuser.h"
#include "sf33rd/Source/Game/stage/bg.h"
#include "sf33rd/Source/Game/stage/ta_sub.h"

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
