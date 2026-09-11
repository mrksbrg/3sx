/**
 * @file effe6_ascent.c
 * Ascending transition state for effect E6.
 */

#include "sf33rd/Source/Game/effect/effe6_ascent.h"
#include "sf33rd/Source/Game/effect/effe6_internal.h"
#include "common.h"
#include "sf33rd/Source/Game/ending/end_data.h"
#include "sf33rd/Source/Game/stage/ta_sub.h"

void effe6_0022(WORK_Other* ewk) {
    mark_effe6_for_cleanup_if_stale(ewk);

    switch (ewk->wu.routine_no[1]) {
    case 0:
        ewk->wu.routine_no[1]++;
        ewk->wu.old_rno[2] = 180;
        break;

    case 1:
        ewk->wu.old_rno[2]--;

        if (ewk->wu.old_rno[2] < 0) {
            ewk->wu.mvxy.a[1].sp = 0x28000;
            effe6_init_common(ewk);
            disp_pos_trans_entry(ewk);
        }

        break;

    case 2:
        ewk->wu.xyz[1].cal += ewk->wu.mvxy.a[1].sp;

        if (ewk->wu.xyz[1].disp.pos >= 48) {
            ewk->wu.routine_no[1]++;
            ewk->wu.xyz[1].cal = 0x300000;
        }

        /* fallthrough */

    case 3:
        disp_pos_trans_entry(ewk);
        break;
    }
}
