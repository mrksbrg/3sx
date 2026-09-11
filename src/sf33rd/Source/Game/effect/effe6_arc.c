/**
 * @file effe6_arc.c
 * Arc-motion state for effect E6.
 */

#include "sf33rd/Source/Game/effect/effe6_arc.h"
#include "sf33rd/Source/Game/effect/effe6_internal.h"
#include "common.h"
#include "sf33rd/Source/Game/engine/caldir.h"
#include "sf33rd/Source/Game/engine/charset.h"
#include "sf33rd/Source/Game/stage/ta_sub.h"

void effe6_0012(WORK_Other* ewk) {
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
            ewk->wu.mvxy.a[1].sp = -0x5000;
            ewk->wu.mvxy.d[1].sp = -0x2000;
        }

        disp_pos_trans_entry(ewk);
        break;

    case 2:
        add_y_sub(&ewk->wu);

        if (ewk->wu.xyz[1].disp.pos < 48) {
            ewk->wu.routine_no[2] = 99;
        }

        disp_pos_trans_entry(ewk);
        break;
    }
}
