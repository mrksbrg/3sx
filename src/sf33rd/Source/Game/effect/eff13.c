/**
 * @file eff13.c
 * TODO: identify what this effect does
 */

#include "sf33rd/Source/Game/effect/eff13.h"
#include "sf33rd/Source/Game/effect/eff13_internal.h"
#include "sf33rd/Source/Game/effect/eff13_kotp16.h"
#include "sf33rd/Source/Game/effect/eff13_kotp_early.h"
#include "sf33rd/Source/Game/effect/eff13_kotp_late.h"
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

extern const TAMA tama_data[243];
extern const s16 tcct[36];
extern const s16 kage_tbl[6][4];
extern const s16 X_F_L_A_T_pos_hos[1][20][2];
void (*const kind_of_tama_process[17])();

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

static void initialize_flat_tama_motion(WORK_Other* ewk, TAMA* tama) {
    PLW* mwk;
    PLW* emwk;

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
}

static void initialize_tama_motion(WORK_Other* ewk, TAMA* tama) {
    if (tama->kind_of_tama == 2) {
        set_tengu_init_pos(&ewk->wu, (WORK*)ewk->my_master);
        ewk->wu.disp_flag = 0;
        ewk->wu.dir_old = ((PLW*)ewk->my_master)->sa->id_arts;
        set_char_move_init2(&ewk->wu, 0, tama->chix, random_16() & 7, 0);
    } else if (tama->kind_of_tama == 0xF) {
        initialize_flat_tama_motion(ewk, tama);
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
