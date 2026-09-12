/**
 * @file eff26.c
 * TODO: identify what this effect does
 */

#include "sf33rd/Source/Game/effect/eff26.h"
#include "common.h"
#include "sf33rd/Source/Game/effect/eff05.h"
#include "sf33rd/Source/Game/effect/eff25.h"
#include "sf33rd/Source/Game/effect/eff27.h"
#include "sf33rd/Source/Game/effect/effect.h"
#include "sf33rd/Source/Game/engine/charset.h"
#include "sf33rd/Source/Game/engine/slowf.h"
#include "sf33rd/Source/Game/engine/workuser.h"
#include "sf33rd/Source/Game/rendering/aboutspr.h"
#include "sf33rd/Source/Game/stage/bg.h"
#include "sf33rd/Source/Game/stage/bg_sub.h"
#include "sf33rd/Source/Game/stage/ta_sub.h"

void (*eff26_jp_tbl[6])(WORK_Other*);

const s16 eff26_num[1] = { 1 };

const s16 eff26_data_0000[1] = { 0 };

static s32 game_is_active(void) {
    return !EXE_flag && !Game_pause;
}

static void move_during_hit_stop_26(WORK_Other* ewk) {
    if (ewk->wu.hit_stop && !EXE_obroll) {
        char_move(&ewk->wu);
    }
}

static void move_unless_obroll_26(WORK_Other* ewk) {
    if (!EXE_obroll) {
        char_move(&ewk->wu);
    }
}

static void advance_piece_when_parent_ready_26(WORK_Other* ewk, WORK_Other* parent) {
    if (parent->wu.routine_no[1] <= 1) {
        return;
    }

    ewk->wu.routine_no[1]++;
    piece_set(ewk);
    set_char_move_init(&ewk->wu, 0, ewk->wu.old_rno[1]);
}

static void update_waiting_piece_26(WORK_Other* ewk, WORK_Other* parent) {
    move_during_hit_stop_26(ewk);
    advance_piece_when_parent_ready_26(ewk, parent);
}

typedef enum {
    ADVANCE_SUBSTATE_26,
    FINISH_EFFECT_26,
} AnimationEndAction26;

static void update_animation_until_end_26(WORK_Other* ewk, AnimationEndAction26 action) {
    move_unless_obroll_26(ewk);

    if (ewk->wu.cg_type != 1) {
        return;
    }

    if (action == FINISH_EFFECT_26) {
        ewk->wu.routine_no[0] = 2;
    } else {
        ewk->wu.routine_no[1]++;
    }
}

static void update_active_effect_26(WORK_Other* ewk) {
    if (game_is_active()) {
        eff26_jp_tbl[ewk->wu.old_rno[2] / 2](ewk);
    }

    disp_pos_trans_entry_rs(ewk);
}

static void spawn_followup_if_requested_26(WORK_Other* ewk) {
    if (!(ewk->wu.old_rno[2] & 1) || ewk->wu.old_rno[5] <= 0) {
        return;
    }

    effect_27_init(ewk, ewk->wu.old_rno[5]);
}

static void finish_effect_when_hit_resolves_26(WORK_Other* ewk) {
    if (!eff_hit_check(ewk, ewk->wu.old_rno[4])) {
        return;
    }

    spawn_followup_if_requested_26(ewk);
    ewk->wu.routine_no[0] = 2;
}

static void start_followup_animation_when_hit_resolves_26(WORK_Other* ewk) {
    if (!eff_hit_check(ewk, ewk->wu.old_rno[4])) {
        return;
    }

    ewk->wu.routine_no[1]++;
    spawn_followup_if_requested_26(ewk);
    set_char_move_init(&ewk->wu, 0, ewk->wu.old_rno[3]);
}

static void enter_effect03_hit_response_26(WORK_Other* ewk) {
    ewk->wu.routine_no[1]++;

    if (eff_hit_flag[ewk->wu.type]) {
        ewk->wu.routine_no[0] = 99;
        return;
    }

    ewk->wu.disp_flag = 1;
    finish_effect_when_hit_resolves_26(ewk);
}

static void enter_effect04_hit_response_26(WORK_Other* ewk) {
    ewk->wu.routine_no[1]++;

    if (eff_hit_flag[ewk->wu.type]) {
        ewk->wu.routine_no[0] = 99;
        return;
    }

    start_followup_animation_when_hit_resolves_26(ewk);
    update_animation_until_end_26(ewk, FINISH_EFFECT_26);
}

static void enter_effect05_hit_response_26(WORK_Other* ewk) {
    ewk->wu.routine_no[1]++;
    ewk->wu.disp_flag = 1;

    if (eff_hit_flag[ewk->wu.type]) {
        ewk->wu.routine_no[1] = 7;
        set_char_move_init(&ewk->wu, 0, ewk->wu.old_rno[7]);
        return;
    }

    start_followup_animation_when_hit_resolves_26(ewk);
}

void effect_26_move(WORK_Other* ewk) {
    if (obr_no_disp_check()) {
        return;
    }

    if (compel_dead_check(ewk)) {
        ewk->wu.routine_no[0] = 99;
        ewk->wu.disp_flag = 0;
        return;
    }

    switch (ewk->wu.routine_no[0]) {
    case 0:
        ewk->wu.routine_no[0]++;
        ewk->wu.routine_no[1] = 0;
        ewk->wu.disp_flag = 1;
        set_char_move_init(&ewk->wu, 0, ewk->wu.char_index);
        break;

    case 1:
        update_active_effect_26(ewk);
        break;

    case 2:
        ewk->wu.disp_flag = 0;
        ewk->wu.routine_no[0]++;
        break;

    case 3:
        ewk->wu.routine_no[0]++;
        break;

    default:
        all_cgps_put_back(&ewk->wu);
        push_effect_work(&ewk->wu);
        break;
    }
}

void eff26_00(WORK_Other* ewk) {
    WORK_Other* oya = (WORK_Other*)ewk->my_master;

    if (oya->wu.routine_no[1] > 1) {
        ewk->wu.routine_no[0] = 2;
        piece_set(ewk);
        return;
    }

    move_during_hit_stop_26(ewk);
}

void eff26_01(WORK_Other* ewk) {
    WORK_Other* oya = (WORK_Other*)ewk->my_master;

    switch (ewk->wu.routine_no[1]) {
    case 0:
        ewk->wu.routine_no[1]++;

        if (eff_hit_flag[oya->wu.type]) {
            ewk->wu.routine_no[0] = 99;
            break;
        }

        /* fallthrough */

    case 1:
        update_waiting_piece_26(ewk, oya);

        break;

    case 2:
        update_animation_until_end_26(ewk, FINISH_EFFECT_26);
        break;
    }
}

void eff26_02(WORK_Other* ewk) {
    WORK_Other* oya = (WORK_Other*)ewk->my_master;

    switch (ewk->wu.routine_no[1]) {
    case 0:
        ewk->wu.routine_no[1]++;

        if (eff_hit_flag[oya->wu.type]) {
            ewk->wu.routine_no[1] = 3;
            ewk->wu.disp_flag = 1;
            set_char_move_init(&ewk->wu, 0, ewk->wu.old_rno[7]);
            break;
        }

        /* fallthrough */

    case 1:
        update_waiting_piece_26(ewk, oya);

        break;

    case 2:
        update_animation_until_end_26(ewk, ADVANCE_SUBSTATE_26);
        break;

    case 3:
        move_unless_obroll_26(ewk);

        break;
    }
}

void eff26_03(WORK_Other* ewk) {
    WORK_Other* oya = (WORK_Other*)ewk->my_master;

    switch (ewk->wu.routine_no[1]) {
    case 0:
        ewk->wu.routine_no[1]++;

        if (eff_hit_flag[oya->wu.type]) {
            ewk->wu.routine_no[1] = 3;
            set_char_move_init(&ewk->wu, 0, ewk->wu.old_rno[1]);
            goto case_3;
        }

    case 1:
        update_waiting_piece_26(ewk, oya);

        break;

    case 2:
        update_animation_until_end_26(ewk, ADVANCE_SUBSTATE_26);
        break;

    case 3:
    case_3:
        enter_effect03_hit_response_26(ewk);
        break;

    case 4:
        finish_effect_when_hit_resolves_26(ewk);
        break;
    }
}

void eff26_04(WORK_Other* ewk) {
    WORK_Other* oya = (WORK_Other*)ewk->my_master;

    switch (ewk->wu.routine_no[1]) {
    case 0:
        if (eff_hit_flag[oya->wu.type]) {
            ewk->wu.routine_no[1] = 2;
            goto case_2;
        }

        update_waiting_piece_26(ewk, oya);

        break;

    case 1:
        update_animation_until_end_26(ewk, ADVANCE_SUBSTATE_26);
        break;

    case 2:
    case_2:
        enter_effect04_hit_response_26(ewk);
        break;

    case 3:
        start_followup_animation_when_hit_resolves_26(ewk);

        /* fallthrough */

    case 4:
        update_animation_until_end_26(ewk, FINISH_EFFECT_26);
        break;
    }
}

void eff26_05(WORK_Other* ewk) {
    WORK_Other* oya = (WORK_Other*)ewk->my_master;

    switch (ewk->wu.routine_no[1]) {
    case 0:
        ewk->wu.routine_no[1]++;

        if (eff_hit_flag[oya->wu.type]) {
            ewk->wu.routine_no[2] = 3;
            set_char_move_init(&ewk->wu, 0, ewk->wu.old_rno[1]);
            goto case_3;
        }

        /* fallthrough */

    case 1:
        update_waiting_piece_26(ewk, oya);

        break;

    case 2:
        update_animation_until_end_26(ewk, ADVANCE_SUBSTATE_26);
        break;

    case 3:
    case_3:
        enter_effect05_hit_response_26(ewk);
        break;

    case 4:
        start_followup_animation_when_hit_resolves_26(ewk);
        break;

    case 5:
        update_animation_until_end_26(ewk, ADVANCE_SUBSTATE_26);
        break;

    case 7:
        move_unless_obroll_26(ewk);

        break;
    }
}

void (*eff26_jp_tbl[6])(WORK_Other*) = { eff26_00, eff26_01, eff26_02, eff26_03, eff26_04, eff26_05 };

const s16* scr_obj_data26[1] = { eff26_data_0000 };

s32 effect_26_init(WORK_Other* oya, s16 type26) {
    WORK_Other* ewk;
    s16 ix;
    s16 lp_cnt = eff26_num[type26];
    s16 i;
    const s16* data_ptr;

    if (!lp_cnt) {
        return 0;
    }

    for (data_ptr = scr_obj_data26[type26], i = 0; i < lp_cnt; i++) {
        if ((ix = pull_effect_work(4)) == -1) {
            return -1;
        }

        ewk = (WORK_Other*)frw[ix];
        ewk->wu.be_flag = 1;
        ewk->wu.id = 26;
        ewk->wu.work_id = 16;
        ewk->my_master = oya;
        ewk->wu.cgromtype = 1;
        ewk->wu.rl_flag = 0;
        ewk->wu.my_col_mode = 0x4200;
        ewk->wu.dead_f = *data_ptr++;
        ewk->wu.type = (s8)*data_ptr++;
        ewk->wu.my_family = *data_ptr++;
        ewk->wu.my_col_code = *data_ptr++;
        ewk->wu.xyz[0].disp.pos = *data_ptr++;
        ewk->wu.xyz[1].disp.pos = *data_ptr++;
        ewk->wu.position_z = *data_ptr++;
        ewk->wu.char_index = *data_ptr++;
        ewk->wu.hit_stop = *data_ptr++;
        ewk->wu.sync_suzi = *data_ptr++;
        ewk->wu.old_rno[0] = *data_ptr++;
        ewk->wu.old_rno[1] = *data_ptr++;
        ewk->wu.old_rno[2] = *data_ptr++;
        ewk->wu.old_rno[3] = *data_ptr++;
        ewk->wu.old_rno[7] = *data_ptr++;
        ewk->wu.old_rno[4] = *data_ptr++;
        ewk->wu.old_rno[5] = *data_ptr++;
        ewk->wu.char_table[0] = char_add[bg_w.bg_index];
        suzi_offset_set(ewk);
    }

    return 0;
}
