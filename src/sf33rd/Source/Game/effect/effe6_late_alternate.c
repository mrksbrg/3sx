/**
 * @file effe6_late_alternate.c
 * Alternate late-state sequences for effect E6.
 */

#include "sf33rd/Source/Game/effect/effe6_late_alternate.h"
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

void effe6_0027(WORK_Other* ewk) {
    mark_effe6_for_cleanup_if_stale(ewk);

    switch (ewk->wu.routine_no[1]) {
    case 0:
        effe6_init_common(ewk);
        disp_pos_trans_entry(ewk);
        break;

    case 1:
        char_move(&ewk->wu);

        if (ewk->wu.cg_type == 0xFF) {
            ewk->wu.routine_no[1]++;
            effect_E6_init(0xA7);
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

static void initialize_effe6_0032(WORK_Other* ewk) {
    effe6_init_common(ewk);
    ewk->wu.old_rno[5] = gill_time[2];
    ewk->wu.old_rno[2] = ewk->wu.old_rno[7] = 0;

    switch (ewk->wu.type) {
    case 176:
        ewk->wu.routine_no[1] = 9;
        break;

    case 177:
    case 178:
        ewk->wu.routine_no[1] = 10;
        ewk->wu.old_rno[5] = gill_time[9];
        break;
    }

    disp_pos_trans_entry(ewk);
}

static void update_effe6_0032_intro_motion(WORK_Other* ewk) {
    mark_effe6_for_cleanup_if_stale(ewk);

    switch (ewk->wu.type) {
    case 174:
        ewk->wu.xyz[1].cal -= gill_range[2] / gill_time[2];
        break;

    case 175:
        ewk->wu.xyz[1].cal -= gill_range[3] / gill_time[2];
        break;
    }

    if (!ewk->wu.old_rno[5]--) {
        ewk->wu.routine_no[1]++;
    }

    disp_pos_trans_entry(ewk);
}

static void update_effe6_0032_outro_motion(WORK_Other* ewk) {
    mark_effe6_for_cleanup_if_stale(ewk);

    switch (ewk->wu.type) {
    case 177:
        ewk->wu.xyz[0].cal -= gill_range[5] / gill_time[4];
        break;

    case 178:
        ewk->wu.xyz[0].cal += gill_range[6] / gill_time[4];
        break;
    }

    if (!ewk->wu.old_rno[5]--) {
        ewk->wu.routine_no[1]++;
    }

    char_move(&ewk->wu);
    disp_pos_trans_entry(ewk);
}

static bool update_effe6_0032_intro(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case 0:
        initialize_effe6_0032(ewk);
        return true;

    case 1:
        update_effe6_0032_intro_motion(ewk);
        return true;

    case 2:
        mark_effe6_for_cleanup_if_stale(ewk);

        ewk->wu.routine_no[1]++;
        ewk->wu.old_rno[5] = gill_time[3];
        disp_pos_trans_entry(ewk);

    case 3:
        mark_effe6_for_cleanup_if_stale(ewk);

        ewk->wu.xyz[1].cal -= gill_range[4] / gill_time[3];

        if (!ewk->wu.old_rno[5]--) {
            ewk->wu.routine_no[1]++;
        }

        disp_pos_trans_entry(ewk);
        return true;

    case 4:
        mark_effe6_for_cleanup_if_stale(ewk);

        disp_pos_trans_entry(ewk);
        return true;

    default:
        return false;
    }
}

void effe6_0032(WORK_Other* ewk) {
    if (update_effe6_0032_intro(ewk)) {
        return;
    }

    switch (ewk->wu.routine_no[1]) {

    case 9:
        char_move(&ewk->wu);

        if (ewk->wu.cg_type) {
            ewk->wu.routine_no[1]++;
            end_etc_flag = 1;
            effect_E6_init(177);
            effect_E6_init(178);
            ewk->wu.old_rno[5] = gill_time[9];
        }

        disp_pos_trans_entry(ewk);
        break;

    case 10:
        mark_effe6_for_cleanup_if_stale(ewk);

        ewk->wu.routine_no[1]++;
        ewk->wu.old_rno[5] = gill_time[4];
        char_move(&ewk->wu);
        disp_pos_trans_entry(ewk);
        break;

    case 11:
        update_effe6_0032_outro_motion(ewk);
        break;

    case 12:
        mark_effe6_for_cleanup_if_stale(ewk);

        char_move(&ewk->wu);
        disp_pos_trans_entry(ewk);
        break;
    }
}
