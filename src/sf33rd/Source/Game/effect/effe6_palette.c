/**
 * @file effe6_palette.c
 * Palette animation state for effect E6.
 */

#include "sf33rd/Source/Game/effect/effe6_palette.h"
#include "sf33rd/Source/Game/effect/effe6_internal.h"
#include "common.h"
#include "sf33rd/Source/Game/ending/end_data.h"
#include "sf33rd/Source/Game/engine/charset.h"
#include "sf33rd/Source/Game/stage/bg.h"
#include "sf33rd/Source/Game/stage/ta_sub.h"

const s16 effe6_0010_col_tbl[8] = { 8521, 8524, 8525, 8526, 8527, 8526, 8525, 8524 };

void effe6_0010_sub(WORK_Other* ewk) {
    ewk->wu.old_rno[5]--;

    if (ewk->wu.old_rno[5] >= 0) {
        return;
    }

    ewk->wu.old_rno[5] = 8;
    ewk->wu.old_rno[2]++;

    if (ewk->wu.old_rno[2] >= 8) {
        ewk->wu.routine_no[1]++;
    }

    ewk->wu.old_rno[2] &= 7;
    ewk->wu.extra_col = effe6_0010_col_tbl[ewk->wu.old_rno[2]];
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
