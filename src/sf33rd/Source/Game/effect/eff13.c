/**
 * @file eff13.c
 * TODO: identify what this effect does
 */

#include "sf33rd/Source/Game/effect/eff13.h"
#include "sf33rd/Source/Game/effect/eff13_internal.h"
#include "sf33rd/Source/Game/effect/eff13_kotp16.h"
#include "sf33rd/Source/Game/effect/eff13_tengu.h"
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

void tama_display(WORK* wk);

extern const s16 kotp_07_dm_vital[4];
extern const TAMA tama_data[243];
extern const s16 tcct[36];
void (*const kind_of_tama_process[17])();
extern const s16 kage_tbl[6][4];
extern const s16 homing_empos_hos[1][20][2];
extern const s16 enemy_pos_hos[1][20][2];
extern const s16 X_F_L_A_T_pos_hos[1][20][2];

static void set_tama_color(WORK_Other* ewk, TAMA* tama) {
    if (ewk->master_id) {
        if (tama->col_2p == 0) {
            ewk->wu.my_col_code = ewk->wu.old_rno[7];
        } else {
            ewk->wu.my_col_code = tcct[tama->col_2p];
        }
    } else if (tama->col_1p == 0) {
        ewk->wu.my_col_code = ewk->wu.old_rno[7];
    } else {
        ewk->wu.my_col_code = tcct[tama->col_1p];
    }
}

static void configure_tama_shadow(WORK_Other* ewk, TAMA* tama) {
    if (tama->kage_index) {
        ewk->wu.kage_flag = 1;
        ewk->wu.kage_hx = kage_tbl[tama->kage_index][0];
        ewk->wu.kage_hy = kage_tbl[tama->kage_index][1];
        ewk->wu.kage_prio = kage_tbl[tama->kage_index][2];
        ewk->wu.kage_char = kage_tbl[tama->kage_index][3];
    } else {
        ewk->wu.kage_flag = 0;
    }
}

static void initialize_standard_tama_motion(WORK_Other* ewk, TAMA* tama) {
    if (ewk->wu.rl_flag) {
        ewk->wu.xyz[0].disp.pos -= tama->hos_x;
    } else {
        ewk->wu.xyz[0].disp.pos += tama->hos_x;
    }

    ewk->wu.xyz[1].disp.pos += tama->hos_y;
    ewk->wu.position_z = ewk->wu.my_priority;

    if (tama->kind_of_tama == 7) {
        ewk->wu.position_z += 2;
    }

    setup_mvxy_data(&ewk->wu, tama->data00);
    set_char_move_init(&ewk->wu, 0, tama->chix);
}

static void initialize_tama_motion(WORK_Other* ewk, TAMA* tama) {
    PLW* mwk;
    PLW* emwk;

    if (tama->kind_of_tama == 2) {
        set_tengu_init_pos(&ewk->wu, (WORK*)ewk->my_master);
        ewk->wu.disp_flag = 0;
        ewk->wu.dir_old = ((PLW*)ewk->my_master)->sa->id_arts;
        set_char_move_init2(&ewk->wu, 0, tama->chix, random_16() & 7, 0);
    } else if (tama->kind_of_tama == 0xF) {
        mwk = (PLW*)ewk->my_master;

        if (tama->data01) {
            ewk->wu.mvxy.a[0].sp = mwk->wu.mvxy.a[0].sp;
            ewk->wu.mvxy.a[1].sp = mwk->wu.mvxy.a[1].sp ? mwk->wu.mvxy.a[1].sp : -0x80000;
            ewk->wu.mvxy.d[0].sp = mwk->wu.mvxy.d[0].sp;
            ewk->wu.mvxy.d[1].sp = mwk->wu.mvxy.d[1].sp;
            ewk->wu.mvxy.kop[1] = 0;
        } else {
            emwk = (PLW*)mwk->wu.target_adrs;
            ewk->wu.xyz[0].disp.pos = tama->hos_x;
            ewk->wu.xyz[0].disp.pos += emwk->wu.xyz[0].disp.pos;
            ewk->wu.xyz[0].disp.pos += X_F_L_A_T_pos_hos[0][emwk->player_number][0];
            ewk->wu.xyz[1].disp.pos = tama->hos_y;
            ewk->wu.xyz[1].disp.pos += emwk->wu.xyz[1].disp.pos;
            ewk->wu.xyz[1].disp.pos += X_F_L_A_T_pos_hos[0][emwk->player_number][1];
            ewk->wu.rl_flag = ewk->wu.xyz[0].disp.pos > emwk->wu.xyz[0].disp.pos ? 0 : 1;
            setup_mvxy_data(&ewk->wu, tama->data00);
        }

        set_char_move_init(&ewk->wu, 0, tama->chix);
    } else {
        initialize_standard_tama_motion(ewk, tama);
    }
}

static void configure_special_tama(WORK_Other* ewk, TAMA* tama) {
    if (tama->kind_of_tama == 11) {
        ewk->wu.next_z = 71;
        ewk->wu.my_mr_flag = 1;
        ewk->wu.my_mr.size.x = 127;
        ewk->wu.my_mr.size.y = 127;
    }

    if (tama->kind_of_tama == 10) {
        ewk->wu.rl_flag = ((WORK*)ewk->my_master)->rl_waza;
    }
}

static void update_active_tama(WORK_Other* ewk, TAMA* tama) {
    if (ewk->wu.dead_f == 1 || Suicide[6] != 0) {
        ewk->wu.disp_flag = 0;
        ewk->wu.routine_no[0]++;
        return;
    }

    if (ewk->wu.hit_stop < 0) {
        ewk->wu.hit_stop = -ewk->wu.hit_stop;
    }

    if (EXE_flag == 0 && Game_pause == 0) {
        kind_of_tama_process[tama->kind_of_tama](ewk, tama);
    }

    tama_display(&ewk->wu);

    if (ewk->wu.floor) {
        ewk->wu.kind_of_waza |= 0x20;
        ewk->wu.at_koa = 0x80;
    }

    hit_push_request(&ewk->wu);
}

void effect_13_move(WORK_Other* ewk) {
    TAMA* tama = (TAMA*)ewk->wu.my_effadrs;

    switch (ewk->wu.routine_no[0]) {
    case 0:
        ewk->wu.routine_no[0]++;
        ewk->wu.my_mts = 14;
        ewk->wu.charset_id = 11;
        set_char_base_data(&ewk->wu);
        ewk->wu.hf.hit_flag = 0;
        ewk->wu.work_id = tama->my_wkid;
        ewk->wu.dir_timer = tama->life_time;
        ewk->wu.disp_flag = tama->disp_type;
        ewk->wu.blink_timing = ewk->master_id;
        ewk->wu.at_koa = tama->koa;
        ewk->wu.vital_new = tama->def_power;
        ewk->wu.dm_vital = 0;
        ewk->wu.original_vitality = tama->waza_num;
        ewk->wu.shell_vs_refrect = tama->vs_refrect;
        ewk->wu.charset_id = tama->kind_of_tama;

        set_tama_color(ewk, tama);

        configure_tama_shadow(ewk, tama);

        initialize_tama_motion(ewk, tama);

        configure_special_tama(ewk, tama);

        tama_display(&ewk->wu);
        effect_00_init(&ewk->wu);
        break;

    case 1:
        update_active_tama(ewk, tama);
        break;

    case 2:
        erase_my_shell_ix((WORK*)ewk->my_master, ewk->wu.myself);
        ewk->wu.routine_no[0] = 3;
        break;

    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}

void tama_display(WORK* wk) {
    set_quake((PLW*)wk);
    wk->position_x = wk->xyz[0].disp.pos + wk->next_x;
    wk->position_y = wk->xyz[1].disp.pos;
    sort_push_request(wk);
}

s32 screen_x_range_check(WORK* wk) {
    s16 scpx = get_center_position();
    s16 scpxr = scpx + 256;
    s16 scpxl = scpx - 256;

    scpx = wk->xyz[0].disp.pos;

    if (scpxl < 0) {
        scpxr -= scpxl;
        scpx -= scpxl;
        scpxl = 0;
    }

    if (scpx > scpxr || scpx < scpxl) {
        return 1;
    }

    return 0;
}

s32 screen_range_check(WORK* wk) {
    s16 scpx = get_center_position();
    s16 scpxr = scpx + 256;
    s16 scpxl = scpx - 256;
    s16 scpy;
    s16 scpyu;

    scpx = wk->xyz[0].disp.pos;

    if (scpxl < 0) {
        scpxr -= scpxl;
        scpx -= scpxl;
        scpxl = 0;
    }

    if (scpx > scpxr || scpx < scpxl) {
        return 1;
    }

    scpy = get_height_position();
    scpyu = scpy + 288;
    scpy = wk->xyz[1].disp.pos;

    if (scpy > scpyu) {
        return 1;
    }

    return 0;
}

s32 tama15_screen_check(WORK* wk) {
    s16 scpx = get_center_position();
    s16 scpxr = scpx + 512;
    s16 scpxl = scpx - 512;
    s16 scpy;
    s16 scpyu;
    s16 scpyd;

    scpx = wk->xyz[0].disp.pos;

    if (scpxl < 0) {
        scpxr -= scpxl;
        scpx -= scpxl;
        scpxl = 0;
    }

    if (scpx > scpxr || scpx < scpxl) {
        return 1;
    }

    scpy = get_height_position();
    scpyu = scpy + 512;
    scpyd = scpy - 288;
    scpy = wk->xyz[1].disp.pos;

    if (scpyd < 0) {
        scpyu -= scpyd;
        scpy -= scpyd;
        scpyd = 0;
    }

    if (scpy > scpyu || scpy < scpyd) {
        return 1;
    }

    return 0;
}


static void set_kotp_hit_move(WORK_Other* ewk, TAMA* twk) {
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

static void enter_kotp_destroyed_phase(WORK_Other* ewk) {
    ewk->wu.routine_no[1] = 2;
    ewk->wu.routine_no[2] = 1;
    ewk->wu.kage_flag = 0;
    ewk->wu.hit_stop = 0;
}

static void apply_kotp_reflection(WORK_Other* ewk) {
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

static void enter_kotp_exit_phase(WORK_Other* ewk, TAMA* twk) {
    ewk->wu.mvxy.a[0].sp /= 4;
    ewk->wu.mvxy.a[1].sp /= 4;
    set_char_move_init(&ewk->wu, 0, twk->ernm);
    ewk->wu.routine_no[1] = 2;
    ewk->wu.routine_no[2] = 0;
}

static void advance_kotp_motion(WORK_Other* ewk) {
    add_mvxy_speed(&ewk->wu);
    cal_mvxy_speed(&ewk->wu);
    char_move(&ewk->wu);
}

static s32 prepare_kotp_exp_motion(WORK_Other* ewk);
static void resolve_kotp_reflected_hit(WORK_Other* ewk, TAMA* twk, s16 destroyed_threshold);

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

static void resolve_kotp_reflected_hit(WORK_Other* ewk, TAMA* twk, s16 destroyed_threshold) {
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

static s32 prepare_kotp_exp_motion(WORK_Other* ewk) {
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


static s32 uses_second_player_effect_data(WORK* wk) {
    return wk->work_id == 1 && wk->rl_flag == 1 && ((PLW*)wk)->player_number == 0;
}

s32 effect_13_init(WORK* wk, u8 data) {
    WORK_Other* ewk;
    s16 ix;

    if ((ix = pull_effect_work(3)) == -1) {
        return -1;
    }

    ewk = (WORK_Other*)frw[ix];
    write_my_shell_ix(wk, ix);

    if (uses_second_player_effect_data(wk)) {
        data++;
    }

    ewk->wu.be_flag = 1;
    ewk->wu.id = 13;
    ewk->wu.type = data;
    ewk->wu.operator = wk->operator;
    ewk->wu.rl_flag = wk->rl_flag;
    ewk->wu.my_family = wk->my_family;
    ewk->wu.cgromtype = wk->cgromtype;
    ewk->wu.my_col_mode = wk->my_col_mode;
    ewk->wu.old_rno[7] = wk->my_col_code;
    ewk->wu.weight_level = wk->weight_level;
    ewk->wu.rl_waza = Round_num;
    ewk->my_master = wk;

    if (wk->work_id == 1) {
        ewk->master_player = ((PLW*)wk)->player_number;
        ewk->master_id = wk->id;
        ewk->master_work_id = wk->work_id;
        ewk->wu.olc_work_ix[0] = ((PLW*)wk)->tk_dageki;
        ewk->wu.olc_work_ix[1] = ((PLW*)wk)->tk_nage;
        ewk->wu.olc_work_ix[2] = ((PLW*)wk)->tk_kizetsu;
        ewk->wu.olc_work_ix[3] = wk->routine_no[1];
    } else {
        ewk->master_player = ((WORK_Other*)wk)->master_player;
        ewk->master_id = ((WORK_Other*)wk)->master_id;
        ewk->master_work_id = ((WORK_Other*)wk)->master_work_id;
    }

    ewk->wu.xyz[0] = wk->xyz[0];
    ewk->wu.xyz[1] = wk->xyz[1];
    ewk->wu.my_effadrs = &tama_data[data];

    if (wk->work_id == 1) {
        ewk->wu.floor = ((PLW*)wk)->metamorphose;
    }

    return 0;
}

void (*const kind_of_tama_process[17])() = { kotp_00000, kotp_01000, kotp_02000, kotp_03000, kotp_04000, kotp_05000,
                                             kotp_06000, kotp_07000, kotp_08000, kotp_09000, kotp_10000, kotp_11000,
                                             kotp_12000, kotp_13000, kotp_14000, kotp_15000, kotp_16000 };
