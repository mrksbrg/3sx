/**
 * @file effe6_controls.c
 * Interactive positioning state for effect E6.
 */

#include "sf33rd/Source/Game/effect/effe6_controls.h"
#include "sf33rd/Source/Game/effect/effe6_internal.h"
#include "common.h"
#include "sf33rd/Source/Game/effect/effect.h"
#include "sf33rd/Source/Game/ending/end_data.h"
#include "sf33rd/Source/Game/engine/charset.h"
#include "sf33rd/Source/Game/stage/ta_sub.h"
#include "sf33rd/Source/Game/system/work_sys.h"

static void set_effe6_0025_position(WORK_Other* ewk) {
    switch (ewk->wu.old_rno[2]) {
    case 0:
        ewk->wu.xyz[0].disp.pos = 608;
        break;

    case 1:
        ewk->wu.xyz[0].disp.pos = 609;
        break;

    case 2:
        ewk->wu.xyz[0].disp.pos = 610;
        break;

    case 3:
        ewk->wu.xyz[0].disp.pos = 607;
        break;

    case 4:
        ewk->wu.xyz[0].disp.pos = 606;
        break;

    case 5:
        ewk->wu.xyz[0].disp.pos = 611;
    }
}

static void update_effe6_0025_player_one(WORK_Other* ewk) {
    if (p1sw_0 & 8) {
        ewk->wu.xyz[0].disp.pos++;
    }

    if (p1sw_0 & 4) {
        ewk->wu.xyz[0].disp.pos--;
    }

    if (p1sw_0 & 1) {
        ewk->wu.xyz[1].disp.pos++;
    }

    if (p1sw_0 & 2) {
        ewk->wu.xyz[1].disp.pos--;
    }
}

static void update_effe6_0025_player_two(WORK_Other* ewk) {
    u16 work;

    if (p2sw_0 & 8) {
        ewk->wu.xyz[0].disp.pos++;
    }

    if (p2sw_0 & 4) {
        ewk->wu.xyz[0].disp.pos--;
    }

    if (p2sw_0 & 1) {
        ewk->wu.xyz[1].disp.pos++;
    }

    if (p2sw_0 & 2) {
        ewk->wu.xyz[1].disp.pos--;
    }

    work = p2sw_0 & ~p2sw_1;

    if (work & 0x10) {
        char_move_z(&ewk->wu);
        ewk->wu.old_rno[2]++;

        if (ewk->wu.old_rno[2] >= 7) {
            ewk->wu.old_rno[2] = 0;
        }
    }

    set_effe6_0025_position(ewk);
}

void effe6_0025(WORK_Other* ewk) {

    switch (ewk->wu.routine_no[1]) {
    case 0:
        effe6_init_common(ewk);
        disp_pos_trans_entry(ewk);
        ewk->wu.old_rno[2] = 0;
        break;

    case 1:
        if (ewk->wu.type == 150) {
            update_effe6_0025_player_one(ewk);
        } else {
            update_effe6_0025_player_two(ewk);
        }

        disp_pos_trans_entry(ewk);
        break;

    default:
        push_effect_work(&ewk->wu);
        break;
    }
}
