/**
 * @file effe6_lift.c
 * Lift transition state for effect E6.
 */

#include "sf33rd/Source/Game/effect/effe6_lift.h"
#include "sf33rd/Source/Game/effect/effe6_internal.h"
#include "common.h"
#include "sf33rd/Source/Game/ending/end_data.h"
#include "sf33rd/Source/Game/stage/ta_sub.h"

void effe6_0018(WORK_Other* ewk) {
    mark_effe6_for_cleanup_if_stale(ewk);

    switch (ewk->wu.routine_no[1]) {
    case 0:
        ewk->wu.routine_no[1]++;
        ewk->wu.old_rno[2] = 70;
        break;

    case 1:
        ewk->wu.old_rno[2]--;

        if (ewk->wu.old_rno[2] <= 0) {
            effe6_init_common(ewk);
            disp_pos_trans_entry(ewk);
        }

        break;

    case 2:
        ewk->wu.xyz[1].cal += 0x10000;

        if (ewk->wu.xyz[1].disp.pos >= 48) {
            ewk->wu.routine_no[1]++;
        }

        /* fallthrough */

    case 3:
        disp_pos_trans_entry(ewk);
        break;
    }
}
