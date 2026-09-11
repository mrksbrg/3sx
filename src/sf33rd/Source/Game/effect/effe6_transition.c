/**
 * @file effe6_transition.c
 * Transition state handlers for effect E6.
 */

#include "sf33rd/Source/Game/effect/effe6_transition.h"
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


static void update_effe6_0019_final_animation(WORK_Other* ewk) {
    char_move(&ewk->wu);

    if (ewk->wu.cg_type) {
        ewk->wu.routine_no[2] = 99;
        end_etc_flag = 1;
        ewk->wu.disp_flag = 0;
    }

    disp_pos_trans_entry(ewk);
}

void effe6_0019(WORK_Other* ewk) {
    if (ewk->wu.old_rno[0] != end_w.r_no_2) {
        ewk->wu.routine_no[2] = 99;
    }

    switch (ewk->wu.routine_no[1]) {
    case 0:
        effe6_init_common(ewk);
        break;

    case 1:
        char_move(&ewk->wu);

        if (ewk->wu.cg_type) {
            ewk->wu.routine_no[1]++;
            ewk->wu.xyz[0].disp.pos = 496;
            ewk->wu.xyz[1].disp.pos = 16;
            set_char_move_init2(&ewk->wu, 0, 37, 1, 0);
        }

        disp_pos_trans_entry(ewk);
        break;

    case 2:
        char_move(&ewk->wu);

        if (ewk->wu.cg_type) {
            ewk->wu.routine_no[1]++;
            ewk->wu.xyz[0].disp.pos = 416;
            ewk->wu.xyz[1].disp.pos = 48;
            set_char_move_init2(&ewk->wu, 0, 37, 1, 0);
        }

        disp_pos_trans_entry(ewk);
        break;

    case 3:
        update_effe6_0019_final_animation(ewk);
        break;
    }
}


void effe6_0021(WORK_Other* ewk) {
    mark_effe6_for_cleanup_if_stale(ewk);

    switch (ewk->wu.routine_no[1]) {
    case 0:
        effe6_init_common(ewk);
        ewk->wu.old_rno[2] = 48;
        ewk->wu.my_mr_flag = 1;
        ewk->wu.my_mr.size.x = 63;
        ewk->wu.my_mr.size.y = 63;
        disp_pos_trans_entry5(ewk);
        break;

    case 1:
        char_move(&ewk->wu);

        if (ewk->wu.xyz[0].disp.pos >= 576) {
            ewk->wu.routine_no[1]++;
            ewk->wu.xyz[0].cal = 0x2400000;
        }

        /* fallthrough */

    case 2:
        disp_pos_trans_entry(ewk);
        break;
    }
}


void effe6_0023(WORK_Other* ewk) {
    mark_effe6_for_cleanup_if_stale(ewk);

    switch (ewk->wu.routine_no[1]) {
    case 0:
        effe6_init_common(ewk);
        ewk->wu.mvxy.a[0].sp = 0x12000;
        ewk->wu.mvxy.a[1].sp = 0x18000;
        disp_pos_trans_entry(ewk);
        break;

    case 1:
        ewk->wu.xyz[0].cal += ewk->wu.mvxy.a[0].sp;
        ewk->wu.xyz[1].cal -= ewk->wu.mvxy.a[1].sp;

        if (ewk->wu.xyz[1].disp.pos < -207) {
            ewk->wu.xyz[0].cal = 0x1400000;
            ewk->wu.xyz[1].cal = 0x1300000;
        }

        disp_pos_trans_entry(ewk);
        break;
    }
}

static void update_effe6_0024_motion(WORK_Other* ewk) {
    char_move(&ewk->wu);

    if (ewk->wu.type == 138) {
        if (ewk->wu.xyz[0].disp.pos < 641) {
            ewk->wu.routine_no[1]++;
        }
    } else if (ewk->wu.xyz[0].disp.pos >= 424) {
        ewk->wu.routine_no[1]++;
    }
}

void effe6_0024(WORK_Other* ewk) {
    mark_effe6_for_cleanup_if_stale(ewk);

    switch (ewk->wu.routine_no[1]) {
    case 0:
        effe6_init_common(ewk);
        disp_pos_trans_entry(ewk);
        break;

    case 1:
        if (ewk->wu.old_rno[6] == end_w.r_no_2) {
            ewk->wu.routine_no[1]++;
            ewk->wu.old_rno[2] = 0;
        }

        disp_pos_trans_entry(ewk);
        break;

    case 2:
        update_effe6_0024_motion(ewk);

        /* fallthrough */

    case 3:
        disp_pos_trans_entry(ewk);
        break;
    }
}

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
