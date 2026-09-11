/**
 * @file effe6_animation_cycle.c
 * Multi-phase animation cycle for effect E6.
 */

#include "sf33rd/Source/Game/effect/effe6_animation_cycle.h"
#include "sf33rd/Source/Game/effect/effe6_internal.h"
#include "common.h"
#include "sf33rd/Source/Game/engine/charset.h"
#include "sf33rd/Source/Game/stage/ta_sub.h"

static void update_effe6_0016_animation(WORK_Other* ewk) {
    char_move(&ewk->wu);

    if (ewk->wu.cg_type == 9) {
        if (ewk->wu.routine_no[1] == 1) {
            ewk->wu.old_rno[2] = 10;
        } else {
            ewk->wu.old_rno[2] = 80;
        }

        ewk->wu.routine_no[1]++;
        char_move_z(&ewk->wu);
    } else {
        disp_pos_trans_entry(ewk);
    }
}

static void update_effe6_0016_delay(WORK_Other* ewk) {
    ewk->wu.old_rno[2]--;

    if (ewk->wu.old_rno[2] < 1) {
        ewk->wu.routine_no[1]++;
    }
}

void effe6_0016(WORK_Other* ewk) {
    mark_effe6_for_cleanup_if_stale(ewk);

    switch (ewk->wu.routine_no[1]) {
    case 0:
        effe6_init_common(ewk);
        break;

    case 1:
    case 3:
        update_effe6_0016_animation(ewk);
        break;

    case 2:
    case 4:
        update_effe6_0016_delay(ewk);
        break;

    case 5:
        char_move(&ewk->wu);

        if (ewk->wu.cg_type == 0xFF) {
            ewk->wu.routine_no[2] = 99;
        }

        disp_pos_trans_entry(ewk);
        break;
    }
}
