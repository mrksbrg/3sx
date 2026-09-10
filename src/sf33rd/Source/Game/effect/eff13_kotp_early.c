/**
 * @file eff13_kotp_early.c
 * Projectile behaviors 00 through 07 for effect 13.
 */

#include "sf33rd/Source/Game/effect/eff13_kotp_early.h"
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

extern const s16 kotp_07_dm_vital[4];
extern const s16 homing_empos_hos[1][20][2];

void set_kotp_hit_move(WORK_Other* ewk, TAMA* twk) {
    if (ewk->wu.hf.hit.player) {
        if (ewk->wu.hf.hit.player & 0xF0) {
            set_char_move_init(&ewk->wu, 0, twk->erdf);
        } else {
            set_char_move_init(&ewk->wu, 0, twk->erht);
        }
    } else {
        set_char_move_init(&ewk->wu, 0, twk->erex);
    }
}

static void spawn_kotp_hit_effect(WORK_Other* ewk, TAMA* twk) {
    if (ewk->wu.hf.hit.player) {
        if (ewk->wu.hf.hit.player & 0xF0) {
            effect_96_init(&ewk->wu, twk->erdf, ewk->wu.disp_flag, ewk->wu.hit_stop);
        } else {
            effect_96_init(&ewk->wu, twk->erht, ewk->wu.disp_flag, ewk->wu.hit_stop);
        }
    } else {
        effect_96_init(&ewk->wu, twk->erex, ewk->wu.disp_flag, ewk->wu.hit_stop);
    }
}

void enter_kotp_destroyed_phase(WORK_Other* ewk) {
    ewk->wu.routine_no[1] = 2;
    ewk->wu.routine_no[2] = 1;
    ewk->wu.kage_flag = 0;
    ewk->wu.hit_stop = 0;
}

void apply_kotp_reflection(WORK_Other* ewk) {
    if (ewk->dm_refrect) {
        ewk->master_id = (ewk->master_id + 1) & 1;
        ewk->wu.rl_flag = (ewk->wu.rl_flag + 1) & 1;
        ewk->dm_refrect = 0;
    }
}

void enter_kotp_landing_phase(WORK_Other* ewk, TAMA* twk) {
    ewk->wu.mvxy.a[0].sp = 0;
    ewk->wu.mvxy.a[1].sp = 0;
    ewk->wu.mvxy.d[0].sp = 0;
    ewk->wu.mvxy.d[1].sp = 0;
    set_char_move_init(&ewk->wu, 0, twk->erex);
    ewk->wu.routine_no[1] = 2;
    ewk->wu.routine_no[2] = 1;
    ewk->wu.xyz[1].disp.pos = -ewk->wu.cg_jphos;
}

void enter_kotp_exit_phase(WORK_Other* ewk, TAMA* twk) {
    ewk->wu.mvxy.a[0].sp /= 4;
    ewk->wu.mvxy.a[1].sp /= 4;
    set_char_move_init(&ewk->wu, 0, twk->ernm);
    ewk->wu.routine_no[1] = 2;
    ewk->wu.routine_no[2] = 0;
}

void advance_kotp_motion(WORK_Other* ewk) {
    add_mvxy_speed(&ewk->wu);
    cal_mvxy_speed(&ewk->wu);
    char_move(&ewk->wu);
}

static void resolve_kotp_00_hit(WORK_Other* ewk, TAMA* twk) {
    resolve_kotp_reflected_hit(ewk, twk, 0x100);
}

static s32 kotp_00_remains_on_screen(WORK_Other* ewk) {
    return --ewk->wu.dir_timer >= 0 && screen_range_check(&ewk->wu) == 0;
}

void kotp_00000(WORK_Other* ewk, TAMA* twk) {
    enter_kotp_hit_phase(ewk);

    switch (ewk->wu.routine_no[1]) {
    case 0:
        if (!prepare_kotp_exp_motion(ewk)) {
            break;
        }

        cal_mvxy_speed(&ewk->wu);
        char_move(&ewk->wu);

        if (ewk->wu.cg_type == 0xFF) {
            set_char_move_init(&ewk->wu, 0, twk->ernm);
            ewk->wu.routine_no[1] = 2;
            ewk->wu.routine_no[2] = 0;
            break;
        }

        if ((ewk->wu.xyz[1].disp.pos + ewk->wu.cg_jphos) <= 0) {
            enter_kotp_landing_phase(ewk, twk);
            break;
        }

        if (kotp_00_remains_on_screen(ewk)) {
            break;
        }

        enter_kotp_exit_phase(ewk, twk);
        break;

    case 1:
        resolve_kotp_00_hit(ewk, twk);
        break;

    case 2:
        finish_kotp_07(ewk);
        break;
    }
}

static void resolve_kotp_01_hit(WORK_Other* ewk, TAMA* twk) {
    set_kotp_hit_move(ewk, twk);

    ewk->wu.routine_no[1] = 2;
    ewk->wu.routine_no[2] = 0;
    ewk->wu.hf.hit_flag = 0;
    ewk->wu.hit_quake = 0;
}

void kotp_01000(WORK_Other* ewk, TAMA* twk) {
    enter_kotp_hit_phase(ewk);

    switch (ewk->wu.routine_no[1]) {
    case 0:
        if (ewk->wu.hit_stop) {
            ewk->wu.hit_stop--;
            break;
        }

        char_move(&ewk->wu);

        if (ewk->wu.cg_type == 0xFF) {
            set_char_move_init(&ewk->wu, 0, twk->ernm);
            ewk->wu.routine_no[1] = 2;
            ewk->wu.routine_no[2] = 0;
            break;
        }

        if (screen_range_check(&ewk->wu)) {
            ewk->wu.routine_no[0] = 2;
            ewk->wu.disp_flag = 0;
        }

        break;

    case 1:
        resolve_kotp_01_hit(ewk, twk);
        break;

    case 2:
        char_move(&ewk->wu);

        if (ewk->wu.cg_type == 0xFF) {
            ewk->wu.routine_no[0] = 2;
            ewk->wu.disp_flag = 0;
        }

        break;
    }
}


static void resolve_kotp_03_hit(WORK_Other* ewk, TAMA* twk) {
    ewk->wu.vital_new -= ewk->wu.dm_vital;
    ewk->wu.hit_stop = 0;
    ewk->wu.hit_quake = 0;

    if (ewk->wu.vital_new < 0x100) {
        if (ewk->wu.hf.hit.player) {
            if (ewk->wu.hf.hit.player & 0xF0) {
                set_char_move_init(&ewk->wu, 0, twk->erdf);
            } else {
                set_char_move_init(&ewk->wu, 0, twk->erht);
                ewk->wu.routine_no[1] = 2;
                ewk->wu.routine_no[2] = 1;
                ewk->wu.mvxy.a[0].sp = 0;
                ewk->wu.mvxy.a[1].sp = 0;
                ewk->wu.mvxy.d[0].sp = 0;
                ewk->wu.mvxy.d[1].sp = 0;
                ewk->wu.hf.hit_flag = 0;
                ewk->wu.kage_flag = 0;
                return;
            }
        } else {
            set_char_move_init(&ewk->wu, 0, twk->erex);
        }

        ewk->wu.routine_no[1] = 2;
        ewk->wu.routine_no[2] = 0;
        ewk->wu.disp_flag = 2;
        ewk->wu.mvxy.a[0].sp = -ewk->wu.mvxy.a[0].sp;
        ewk->wu.mvxy.a[0].sp /= 3;
        ewk->wu.mvxy.a[1].sp = 0;
        ewk->wu.mvxy.d[0].sp = 0;
        ewk->wu.hf.hit_flag = 0;
        ewk->wu.kage_flag = 0;
        return;
    }

    ewk->wu.routine_no[1] = 0;
    ewk->wu.hf.hit_flag = 0;
}

void kotp_03000(WORK_Other* ewk, TAMA* twk) {
    enter_kotp_hit_phase(ewk);

    switch (ewk->wu.routine_no[1]) {
    case 0:
        if (ewk->wu.hit_stop) {
            ewk->wu.hit_stop--;
            break;
        }

        advance_kotp_motion(ewk);

        if ((ewk->wu.xyz[1].disp.pos + ewk->wu.cg_jphos) <= 0) {
            ewk->wu.mvxy.a[0].sp = 0;
            ewk->wu.mvxy.a[1].sp = 0;
            ewk->wu.mvxy.d[0].sp = 0;
            ewk->wu.mvxy.d[1].sp = 0;
            set_char_move_init(&ewk->wu, 0, twk->ernm);
            ewk->wu.routine_no[1] = 2;
            ewk->wu.routine_no[2] = 1;
            ewk->wu.xyz[1].disp.pos = -ewk->wu.cg_jphos;
            break;
        }

        if (kotp_remains_on_screen(ewk)) {
            break;
        }

        ewk->wu.disp_flag = 0;
        ewk->wu.routine_no[0] = 2;
        break;

    case 1:
        resolve_kotp_03_hit(ewk, twk);
        break;

    case 2:
        finish_kotp_07(ewk);
        break;
    }
}

void kotp_04000(WORK_Other* ewk, TAMA* /* unused */) {
    ewk->wu.disp_flag = 0;
    ewk->wu.routine_no[0] = 2;
}

static void resolve_kotp_05_hit(WORK_Other* ewk, TAMA* twk) {
    ewk->wu.vital_new -= ewk->wu.dm_vital;
    ewk->wu.dm_vital = 0;

    if (ewk->wu.vital_new < 256) {
        set_kotp_hit_move(ewk, twk);

        enter_kotp_destroyed_phase(ewk);
    } else {
        ewk->wu.routine_no[1] = 0;

        spawn_kotp_hit_effect(ewk, twk);
    }

    ewk->wu.hf.hit_flag = 0;
    ewk->wu.hit_quake = 0;
}

static s32 kotp_05_remains_on_screen(WORK_Other* ewk) {
    return --ewk->wu.dir_timer >= 0 && screen_x_range_check(&ewk->wu) == 0;
}

void kotp_05000(WORK_Other* ewk, TAMA* twk) {
    enter_kotp_hit_phase(ewk);

    switch (ewk->wu.routine_no[1]) {
    case 0:
        if (ewk->wu.routine_no[3] == 0) {
            ewk->wu.routine_no[3]++;
            ewk->wu.xyz[1].disp.pos = get_height_position() + 256;
        }

        if (ewk->wu.hit_stop) {
            ewk->wu.hit_stop--;
            break;
        }

        advance_kotp_motion(ewk);

        if ((ewk->wu.xyz[1].disp.pos + ewk->wu.cg_jphos) <= 0) {
            enter_kotp_landing_phase(ewk, twk);
            break;
        }

        if (kotp_05_remains_on_screen(ewk)) {
            break;
        }

        enter_kotp_exit_phase(ewk, twk);
        break;

    case 1:
        resolve_kotp_05_hit(ewk, twk);
        break;

    case 2:
        finish_kotp_07(ewk);
        break;
    }
}

static void steer_kotp_06_homing(WORK_Other* ewk, const PLW* mwk, const PLW* emwk) {
    s16 dir;
    s16 emdir;
    s16* target_x = &ewk->wu.E3_work_index;
    s16* target_y = &ewk->wu.E4_work_index;

    *target_x = homing_empos_hos[0][ewk->master_player][0];
    *target_x = mwk->wu.rl_flag ? emwk->wu.xyz[0].disp.pos - *target_x : emwk->wu.xyz[0].disp.pos + *target_x;
    *target_y = homing_empos_hos[0][ewk->master_player][1] + emwk->wu.xyz[1].disp.pos;
    dir = ewk->wu.direction;
    emdir = caldir_pos_256(ewk->wu.xyz[0].disp.pos, ewk->wu.xyz[1].disp.pos, *target_x, *target_y);
    dir += (emdir - (dir - 0x80) & 0xFF) > 0x80 ? 4 : -4;
    dir = dir & 0xFF;
    ewk->wu.mvxy.a[0].sp = (rate_256_table[dir][0] * 480) / 256;
    ewk->wu.mvxy.a[0].sp *= ewk->wu.rl_flag ? 1 : -1;
    ewk->wu.mvxy.a[1].sp = (rate_256_table[dir][1] * 512) / 256;
    ewk->wu.direction = dir;

    if (ewk->wu.mvxy.a[0].sp < 0) {
        ewk->wu.routine_no[3]++;
    } else if (!ewk->wu.kezurare_flag--) {
        ewk->wu.routine_no[3]++;
    }
}

static void steer_kotp_06(WORK_Other* ewk, const TAMA* twk, const PLW* mwk, const PLW* emwk) {

    switch (ewk->wu.routine_no[3]) {
    case 0:
        ewk->wu.routine_no[3]++;
        ewk->wu.kezurare_flag = 6;
        ewk->wu.direction = ewk->wu.rl_flag ? twk->data01 : 256 - twk->data01 & 0xFF;
        effect_I9_init(ewk, 2, 3, 0x77);
        break;

    case 1:
        if (ewk->wu.kezurare_flag--) {
            break;
        }

        ewk->wu.routine_no[3]++;
        ewk->wu.kezurare_flag = 0x70;
        /* fallthrough */

    case 2:
        steer_kotp_06_homing(ewk, mwk, emwk);
        break;
    }
}

void enter_kotp_hit_phase(WORK_Other* ewk) {
    if (ewk->wu.hf.hit_flag) {
        ewk->wu.routine_no[1] = 1;
    }
}

void kotp_06000(WORK_Other* ewk, TAMA* twk) {
    PLW* mwk;
    PLW* emwk;

    mwk = (PLW*)ewk->my_master;
    emwk = (PLW*)mwk->wu.target_adrs;

    enter_kotp_hit_phase(ewk);

    switch (ewk->wu.routine_no[1]) {
    case 0:
        if (ewk->wu.hit_stop) {
            ewk->wu.hit_stop--;
            break;
        }

        steer_kotp_06(ewk, twk, mwk, emwk);

        advance_kotp_motion(ewk);

        if ((ewk->wu.xyz[1].disp.pos + ewk->wu.cg_jphos) <= 0) {
            enter_kotp_landing_phase(ewk, twk);
            return;
        }

        if (--ewk->wu.dir_timer < 0 || screen_range_check(&ewk->wu) != 0) {
            enter_kotp_exit_phase(ewk, twk);
        }

        break;

    case 1:
        resolve_kotp_05_hit(ewk, twk);
        break;

    case 2:
        finish_kotp_07(ewk);
        break;
    }
}

static void prepare_kotp_07_damage(WORK_Other* ewk) {
    WORK* awk;
    s16 dsst;

    if (ewk->wu.hf.hit_flag == 0) {
        awk = (WORK*)ewk->wu.dmg_adrs;

        if (awk->work_id == 1) {
            dsst = 3;

            if (!(ewk->wu.dm_kind_of_waza & 0xF8)) {
                dsst = (ewk->wu.dm_kind_of_waza / 2) & 3;
            }

            ewk->wu.dm_vital = kotp_07_dm_vital[dsst];
        } else {
            ewk->wu.dm_vital = kotp_07_dm_vital[2];
        }
    }
}

void resolve_kotp_reflected_hit(WORK_Other* ewk, TAMA* twk, s16 destroyed_threshold) {
    ewk->wu.vital_new -= ewk->wu.dm_vital;
    ewk->wu.dm_vital = 0;

    if (ewk->wu.vital_new < destroyed_threshold) {
        set_kotp_hit_move(ewk, twk);

        enter_kotp_destroyed_phase(ewk);
    } else {
        ewk->wu.routine_no[1] = 0;

        spawn_kotp_hit_effect(ewk, twk);

        apply_kotp_reflection(ewk);
    }

    ewk->wu.hf.hit_flag = 0;
    ewk->wu.hit_quake = 0;
}

static void resolve_kotp_07_hit(WORK_Other* ewk, TAMA* twk) {
    prepare_kotp_07_damage(ewk);
    resolve_kotp_reflected_hit(ewk, twk, 0x100);
}

static void redirect_kotp_07_velocity(WORK_Other* ewk) {
    PLW* mwk;
    PLW* emwk;
    s16 tama_x;

    if (ewk->wu.cg_type == 20) {
        setup_mvxy_data(&ewk->wu, ewk->wu.mvxy.index);
        ewk->wu.mvxy.index++;
        ewk->wu.cg_type = 0;
        mwk = (PLW*)ewk->my_master;
        emwk = (PLW*)mwk->wu.target_adrs;
        tama_x = ewk->wu.xyz[0].disp.pos;

        if (tama_x > emwk->wu.xyz[0].disp.pos) {
            ewk->wu.mvxy.a[0].sp *= ewk->wu.rl_flag ? -1 : 1;
            ewk->wu.mvxy.d[0].sp *= ewk->wu.rl_flag ? -1 : 1;
        } else {
            ewk->wu.mvxy.a[0].sp *= ewk->wu.rl_flag ? 1 : -1;
            ewk->wu.mvxy.d[0].sp *= ewk->wu.rl_flag ? 1 : -1;
        }
    }
}

void finish_kotp_07(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[2]) {
    case 0:
        add_mvxy_speed(&ewk->wu);
        cal_mvxy_speed(&ewk->wu);
        /* fallthrough */

    case 1:
        char_move(&ewk->wu);

        if (ewk->wu.cg_type == 0xFF) {
            ewk->wu.disp_flag = 0;
            ewk->wu.routine_no[0] = 2;
        }

        break;
    }
}

void kotp_07000(WORK_Other* ewk, TAMA* twk) {
    enter_kotp_hit_phase(ewk);

    switch (ewk->wu.routine_no[1]) {
    case 0:
        if (ewk->wu.hit_stop) {
            ewk->wu.hit_stop--;
            break;
        }

        advance_kotp_motion(ewk);

        if (bg_w.stage == 20) {
            ewk->wu.vs_id = 7;
        }
        redirect_kotp_07_velocity(ewk);

        if (--ewk->wu.dir_timer < 0) {
            set_char_move_init(&ewk->wu, 0, twk->ernm);
            ewk->wu.routine_no[1] = 2;
            ewk->wu.routine_no[2] = 0;
        }

        break;

    case 1:
        resolve_kotp_07_hit(ewk, twk);
        break;

    case 2:
        finish_kotp_07(ewk);
        break;
    }
}
