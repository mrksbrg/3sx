/**
 * @file eff13_kotp_late.c
 * Projectile behaviors 08 through 15 for effect 13.
 */

#include "sf33rd/Source/Game/effect/eff13_kotp_late.h"
#include "sf33rd/Source/Game/effect/eff13.h"
#include "sf33rd/Source/Game/effect/eff13_internal.h"
#include "common.h"
#include "sf33rd/Source/Game/effect/eff00.h"
#include "sf33rd/Source/Game/effect/eff96.h"
#include "sf33rd/Source/Game/effect/effect.h"
#include "sf33rd/Source/Game/effect/effi9.h"
#include "sf33rd/Source/Game/engine/caldir.h"
#include "sf33rd/Source/Game/engine/charid.h"
#include "sf33rd/Source/Game/engine/charset.h"
#include "sf33rd/Source/Game/engine/grade.h"
#include "sf33rd/Source/Game/engine/hitcheck.h"
#include "sf33rd/Source/Game/engine/plcnt.h"
#include "sf33rd/Source/Game/engine/pls02.h"
#include "sf33rd/Source/Game/engine/slowf.h"
#include "sf33rd/Source/Game/engine/workuser.h"
#include "sf33rd/Source/Game/io/pulpul.h"
#include "sf33rd/Source/Game/rendering/aboutspr.h"
#include "sf33rd/Source/Game/stage/bg.h"
#include "sf33rd/Source/Game/stage/bg_sub.h"

extern const s16 enemy_pos_hos[1][20][2];

static void resolve_kotp_08_hit(WORK_Other* ewk, TAMA* twk) {
    ewk->wu.vital_new -= ewk->wu.dm_vital;
    ewk->wu.dm_vital = 0;

    if (ewk->wu.vital_new < 256) {
        set_kotp_hit_move(ewk, twk);

        enter_kotp_destroyed_phase(ewk);
    } else {
        ewk->wu.routine_no[1] = 0;

        if (ewk->wu.hf.hit.player) {
            if (ewk->wu.hf.hit.player & 0xF0) {
                effect_96_init(&ewk->wu, twk->erdf, ewk->wu.disp_flag, ewk->wu.hit_stop);
            } else {
                effect_96_init(&ewk->wu, twk->erht, ewk->wu.disp_flag, ewk->wu.hit_stop);
            }
        } else if (ewk->dm_refrect) {
            effect_96_init(&ewk->wu, twk->erex, ewk->wu.disp_flag, ewk->wu.hit_stop);
        } else {
            set_char_move_init(&ewk->wu, 0, twk->erex);
            enter_kotp_destroyed_phase(ewk);
        }

        apply_kotp_reflection(ewk);
    }

    ewk->wu.hf.hit_flag = 0;
    ewk->wu.hit_quake = 0;
}

static void finish_standard_kotp_trajectory(WORK_Other* ewk, TAMA* twk) {
    if ((ewk->wu.xyz[1].disp.pos + ewk->wu.cg_jphos) <= 0) {
        enter_kotp_landing_phase(ewk, twk);
        return;
    }

    if (kotp_remains_on_screen(ewk)) {
        return;
    }

    enter_kotp_exit_phase(ewk, twk);
}

void kotp_08000(WORK_Other* ewk, TAMA* twk) {
    enter_kotp_hit_phase(ewk);

    switch (ewk->wu.routine_no[1]) {
    case 0:
        if (ewk->wu.hit_stop) {
            ewk->wu.hit_stop--;
            break;
        }

        advance_kotp_motion(ewk);

        finish_standard_kotp_trajectory(ewk, twk);
        break;

    case 1:
        resolve_kotp_08_hit(ewk, twk);
        break;

    case 2:
        finish_kotp_07(ewk);
        break;
    }
}

static void resolve_kotp_09_hit(WORK_Other* ewk, TAMA* twk) {
    ewk->wu.vital_new -= ewk->wu.dm_vital;
    ewk->wu.dm_vital = 0;

    if (ewk->wu.vital_new < 256) {
        set_kotp_hit_move(ewk, twk);

        enter_kotp_destroyed_phase(ewk);
    } else {
        ewk->wu.routine_no[1] = 0;

        if (ewk->wu.hf.hit.player) {
            if (ewk->wu.hf.hit.player & 0xF0) {
                set_char_move_init(&ewk->wu, 0, twk->erdf);
            } else {
                set_char_move_init(&ewk->wu, 0, twk->erht);
            }

            enter_kotp_destroyed_phase(ewk);
        } else {
            effect_96_init(&ewk->wu, twk->erex, ewk->wu.disp_flag, ewk->wu.hit_stop);
        }

        if (ewk->dm_refrect) {
            ewk->master_id = (ewk->master_id + 1) & 1;
            ewk->wu.rl_flag = (ewk->wu.rl_flag) + 1 & 1;
            ewk->dm_refrect = 0;
        }
    }

    ewk->wu.hf.hit_flag = 0;
    ewk->wu.hit_quake = 0;
}

void kotp_09000(WORK_Other* ewk, TAMA* twk) {
    enter_kotp_hit_phase(ewk);

    switch (ewk->wu.routine_no[1]) {
    case 0:
        if (ewk->wu.hit_stop) {
            ewk->wu.hit_stop--;
            break;
        }

        advance_kotp_motion(ewk);

        if (ewk->wu.cg_type == 0xFF) {
            set_char_move_init(&ewk->wu, 0, twk->ernm);
            ewk->wu.routine_no[1] = 2;
            ewk->wu.routine_no[2] = 0;
            break;
        }

        finish_standard_kotp_trajectory(ewk, twk);
        break;

    case 1:
        resolve_kotp_09_hit(ewk, twk);
        break;

    case 2:
        finish_kotp_07(ewk);
        break;
    }
}

void kotp_10000(WORK_Other* ewk, TAMA* twk) {
    char_move(&ewk->wu);

    if (ewk->wu.cg_type == 0xFF) {
        ewk->wu.routine_no[0] = 2;
        return;
    }
}

static void update_kotp_11_descent(WORK_Other* ewk, TAMA* twk, PLW* mwk) {
    if (mwk->sa_stop_flag == 1) {
        return;
    }

    char_move(&ewk->wu);
    add_mvxy_speed(&ewk->wu);
    cal_mvxy_speed(&ewk->wu);

    if (ewk->wu.xyz[1].disp.pos <= 0) {
        ewk->wu.mvxy.a[1].sp = ewk->wu.mvxy.d[1].sp = ewk->wu.mvxy.kop[1] = 0;
        set_char_move_init(&ewk->wu, 0, twk->erex);
        ewk->wu.xyz[1].disp.pos = 0;
        ewk->wu.routine_no[1] = 2;
    }
}

void kotp_11000(WORK_Other* ewk, TAMA* twk) {
    PLW* mwk = (PLW*)ewk->my_master;

    switch (ewk->wu.routine_no[1]) {
    case 0:
    case 1:
        update_kotp_11_descent(ewk, twk, mwk);
        break;

    case 2:
        if (mwk->sa_stop_flag == 1) {
            break;
        }

        char_move(&ewk->wu);
        add_mvxy_speed(&ewk->wu);
        cal_mvxy_speed(&ewk->wu);

        if (ewk->wu.cg_type == 0xFF) {
            ewk->wu.disp_flag = 0;
            ewk->wu.routine_no[0] = 2;
        }

        break;
    }

    if (ewk->wu.position_z == ewk->wu.next_z) {
        ewk->wu.position_z = ewk->wu.my_priority;
        return;
    }

    ewk->wu.position_z = ewk->wu.next_z;
}

void resolve_kotp_12_hit(WORK_Other* ewk, TAMA* twk) {
    resolve_kotp_reflected_hit(ewk, twk, 256);
}

s32 prepare_kotp_exp_motion(WORK_Other* ewk) {
    if (ewk->wu.hit_stop) {
        if (ewk->wu.hit_stop == 1) {
            ewk->wu.hit_stop = 0;
            add_mvxy_speed_exp(&ewk->wu, 2);
        } else {
            ewk->wu.hit_stop--;
            return 0;
        }
    } else {
        add_mvxy_speed(&ewk->wu);
    }

    return 1;
}

s32 kotp_remains_on_screen(WORK_Other* ewk) {
    return --ewk->wu.dir_timer >= 0 && !screen_range_check(&ewk->wu);
}

static void update_kotp_12(WORK_Other* ewk, TAMA* twk) {
    if (!prepare_kotp_exp_motion(ewk)) {
        return;
    }

    cal_mvxy_speed(&ewk->wu);
    char_move(&ewk->wu);

    if (ewk->wu.cg_type == 10) {
        add_to_mvxy_data(&ewk->wu, twk->data01);
        ewk->wu.cg_type = 0;
        return;
    }

    if (ewk->wu.cg_type == 0xFF) {
        set_char_move_init(&ewk->wu, 0, twk->ernm);
        ewk->wu.routine_no[1] = 2;
        ewk->wu.routine_no[2] = 0;
        return;
    }

    if ((ewk->wu.xyz[1].disp.pos + ewk->wu.cg_jphos) <= 0) {
        enter_kotp_landing_phase(ewk, twk);
        return;
    }

    if (kotp_remains_on_screen(ewk)) {
        return;
    }

    enter_kotp_exit_phase(ewk, twk);
}

void kotp_12000(WORK_Other* ewk, TAMA* twk) {
    enter_kotp_hit_phase(ewk);

    switch (ewk->wu.routine_no[1]) {
    case 0:
        update_kotp_12(ewk, twk);
        break;

    case 1:
        resolve_kotp_12_hit(ewk, twk);
        break;

    case 2:
        finish_kotp_07(ewk);
        break;
    }
}

static void update_kotp_13(WORK_Other* ewk, TAMA* twk) {
    PLW* mwk;
    PLW* emwk;
    s16 ipos_x;

    if (ewk->wu.hit_stop) {
        ewk->wu.hit_stop--;
        return;
    }

    if (!ewk->wu.routine_no[3]) {
        ewk->wu.xyz[1].disp.pos = 0;
        ewk->wu.routine_no[3]++;

        if (twk->data00) {
            mwk = (PLW*)ewk->my_master;
            emwk = (PLW*)mwk->wu.target_adrs;
            ipos_x = enemy_pos_hos[0][emwk->player_number][0];
            ewk->wu.xyz[0].disp.pos =
                emwk->wu.rl_flag ? emwk->wu.xyz[0].disp.pos + ipos_x : emwk->wu.xyz[0].disp.pos - ipos_x;
        }
    }

    char_move(&ewk->wu);

    if (ewk->wu.cg_type == 0xFF) {
        set_char_move_init(&ewk->wu, 0, twk->ernm);
        ewk->wu.routine_no[1] = 2;
        ewk->wu.routine_no[2] = 0;
        return;
    }

    if (screen_range_check(&ewk->wu)) {
        ewk->wu.routine_no[0] = 2;
        ewk->wu.disp_flag = 0;
    }
}

void kotp_13000(WORK_Other* ewk, TAMA* twk) {
    PLW* mwk;

    enter_kotp_hit_phase(ewk);

    mwk = (PLW*)ewk->my_master;

    if (mwk->wu.routine_no[1] != 4) {
        ewk->wu.routine_no[0] = 2;
        ewk->wu.disp_flag = 0;
        return;
    }

    switch (ewk->wu.routine_no[1]) {
    case 0:
        update_kotp_13(ewk, twk);
        break;

    case 1:
        ewk->wu.vital_new -= ewk->wu.dm_vital;
        ewk->wu.dm_vital = 0;

        if (ewk->wu.vital_new < 256) {
            enter_kotp_destroyed_phase(ewk);
            ewk->wu.att_hit_ok = 0;
        } else {
            ewk->wu.routine_no[1] = 0;
        }

        ewk->wu.hf.hit_flag = 0;
        ewk->wu.hit_quake = 0;
        break;

    case 2:
        char_move(&ewk->wu);
        ewk->wu.att_hit_ok = 0;

        if (ewk->wu.cg_type == 0xFF) {
            ewk->wu.routine_no[0] = 2;
            ewk->wu.disp_flag = 0;
        }

        break;
    }
}

void kotp_14000(WORK_Other* ewk, TAMA* /* unused */) {
    char_move(&ewk->wu);

    if (ewk->wu.hf.hit_flag) {
        ((WORK*)ewk->my_master)->hf.hit_flag = ewk->wu.hf.hit_flag;
        ewk->wu.hf.hit_flag = 0;
    }

    if (ewk->wu.cg_type == 0xFF) {
        ewk->wu.disp_flag = 0;
        ewk->wu.routine_no[0] = 2;
    }
}

static s32 kotp_15_remains_on_screen(WORK_Other* ewk) {
    return --ewk->wu.dir_timer >= 0 && !tama15_screen_check(&ewk->wu);
}

void kotp_15000(WORK_Other* ewk, TAMA* twk) {
    enter_kotp_hit_phase(ewk);

    switch (ewk->wu.routine_no[1]) {
    case 0:
        if (ewk->wu.hit_stop) {
            ewk->wu.hit_stop--;
            break;
        }

        advance_kotp_motion(ewk);

        if (ewk->wu.cg_type == 0xFF) {
            set_char_move_init(&ewk->wu, 0, twk->ernm);
            ewk->wu.routine_no[1] = 2;
            ewk->wu.routine_no[2] = 0;
            break;
        }

        if (kotp_15_remains_on_screen(ewk)) {
            break;
        }

        ewk->wu.mvxy.a[0].sp = 0;
        ewk->wu.mvxy.a[1].sp = 0;
        ewk->wu.mvxy.d[0].sp = 0;
        ewk->wu.mvxy.d[1].sp = 0;
        set_char_move_init(&ewk->wu, 0, twk->ernm);
        ewk->wu.routine_no[1] = 2;
        ewk->wu.routine_no[2] = 0;
        break;

    case 1:
        ewk->wu.vital_new -= ewk->wu.dm_vital;
        ewk->wu.dm_vital = 0;

        if (ewk->wu.vital_new < 256) {
            set_char_move_init(&ewk->wu, 0, twk->ernm);
            ewk->wu.routine_no[1] = 2;
            ewk->wu.routine_no[2] = 0;
        } else {
            ewk->wu.routine_no[1] = 0;
        }

        ewk->wu.hf.hit_flag = 0;
        ewk->wu.hit_quake = 0;
        pp_pulpara_hit((WORK*)ewk->my_master);
        break;

    case 2:
        finish_kotp_07(ewk);
        break;
    }
}
