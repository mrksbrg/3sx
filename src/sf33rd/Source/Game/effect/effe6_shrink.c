/**
 * @file effe6_shrink.c
 * Shrinking marker state for effect E6.
 */

#include "sf33rd/Source/Game/effect/effe6_shrink.h"
#include "sf33rd/Source/Game/effect/effe6_internal.h"
#include "common.h"
#include "sf33rd/Source/Game/engine/charset.h"
#include "sf33rd/Source/Game/stage/ta_sub.h"

static void update_effe6_0014_first_shrink(WORK_Other* ewk) {
    ewk->wu.old_rno[2]--;

    if (ewk->wu.old_rno[2] < 0) {
        ewk->wu.old_rno[2] = 2;
        ewk->wu.my_mr.size.x--;
        ewk->wu.my_mr.size.y--;

        if (ewk->wu.my_mr.size.x < 60) {
            ewk->wu.routine_no[1]++;
            set_char_move_init2(&ewk->wu, 0, 21, 9, 0);
            ewk->wu.old_rno[2] = 4;
        } else {
            ewk->wu.old_rno[2] = 3;
        }
    }
}

static void update_effe6_0014_second_shrink(WORK_Other* ewk) {
    ewk->wu.old_rno[2]--;

    if (ewk->wu.old_rno[2] < 0) {
        ewk->wu.old_rno[2] = 3;
        ewk->wu.my_mr.size.x--;
        ewk->wu.my_mr.size.y--;

        if (ewk->wu.my_mr.size.x < 56) {
            ewk->wu.routine_no[1]++;
            set_char_move_init2(&ewk->wu, 0, 21, 10, 0);
            ewk->wu.old_rno[2] = 4;
        }
    }
}

static void update_effe6_0014_final_shrink(WORK_Other* ewk) {
    ewk->wu.old_rno[2]--;

    if (ewk->wu.old_rno[2] < 0) {
        ewk->wu.old_rno[2] = 4;
        ewk->wu.my_mr.size.x--;
        ewk->wu.my_mr.size.y--;

        if (ewk->wu.my_mr.size.x <= 0) {
            ewk->wu.routine_no[2] = 99;
            ewk->wu.my_mr.size.x = 0;
            ewk->wu.my_mr.size.y = 0;
        }
    }
}

void effe6_0014(WORK_Other* ewk) {
    mark_effe6_for_cleanup_if_stale(ewk);

    switch (ewk->wu.routine_no[1]) {
    case 0:
        effe6_init_common(ewk);
        ewk->wu.my_mr_flag = 1;
        ewk->wu.old_rno[2] = 4;
        ewk->wu.my_mr.size.x = 63;
        ewk->wu.my_mr.size.y = 63;
        disp_pos_trans_entry5(ewk);
        break;

    case 1:
        ewk->wu.old_rno[2]--;

        if (ewk->wu.old_rno[2] < 0) {
            ewk->wu.routine_no[1]++;
            ewk->wu.old_rno[2] = 4;
        }

        disp_pos_trans_entry5(ewk);
        break;

    case 2:
        update_effe6_0014_first_shrink(ewk);
        disp_pos_trans_entry5(ewk);
        break;

    case 3:
        update_effe6_0014_second_shrink(ewk);
        disp_pos_trans_entry5(ewk);
        break;

    case 4:
        update_effe6_0014_final_shrink(ewk);
        disp_pos_trans_entry5(ewk);
        break;
    }
}
