/**
 * @file effe3.c
 * TODO: identify what this effect does
 */

#include "sf33rd/Source/Game/effect/effe3.h"
#include "common.h"
#include "sf33rd/Source/Game/effect/effect.h"
#include "sf33rd/Source/Game/engine/plcnt.h"
#include "sf33rd/Source/Game/engine/plmain.h"
#include "sf33rd/Source/Game/engine/spgauge.h"
#include "sf33rd/Source/Game/engine/workuser.h"
#include "sf33rd/Source/Game/system/sysdir.h"
#include "sf33rd/Source/Game/system/work_sys.h"

static s32 should_disable_new_challenger_vibration(const PLW* mwk) {
    return mwk->wu.id == New_Challenger && Training[0].contents[0][0][0] != 4;
}


static s32 effect_should_stop(const WORK_Other* ewk, const PLW* mwk) {
    return (mwk->wu.E3_work_index != ewk->wu.myself || ewk->wu.dead_f != 0) ||
           (Mode_Type != MODE_NORMAL_TRAINING && Mode_Type != MODE_PARRY_TRAINING);
}

static s32 is_airborne_action_window(const PLW* mwk) {
    return (mwk->wu.routine_no[1] == 1 && mwk->wu.routine_no[2] >= 4) && mwk->wu.routine_no[2] < 14;
}

static void configure_training_feedback_E3(WORK_Other* ewk, PLW* mwk) {
    if (should_disable_new_challenger_vibration(mwk)) {
        vib_sel[mwk->wu.id] = 0;
    }

    if (Training[0].contents[0][1][TRAINING_OPTION_DIFFICULTY] == 2) {
        vib_sel[mwk->wu.id] = 0;
    }

    ewk->wu.direction = 0;

    if (Training[0].contents[0][0][0] == 3 || Training[0].contents[0][0][0] == 4) {
        ewk->wu.direction = 1;
    }

    omop_vital_ix[mwk->wu.id] = 1;

    if (Training[0].contents[0][1][TRAINING_OPTION_DIFFICULTY] == 0) {
        omop_vital_ix[mwk->wu.id] = 3;
    }

    ewk->wu.dm_vital = 0;
    ewk->wu.vitality = 0;
    ewk->wu.dir_timer = 0;
}

static void configure_challenger_restrictions_E3(PLW* mwk) {
    switch (Training[0].contents[0][0][1]) {
    case 0:
    case 1:
    case 6:
        mwk->spmv_ng_flag &= 0xFFFFFFEF;
        mwk->spmv_ng_flag |= 0xC0;
        break;

    case 2:
    case 4:
        mwk->spmv_ng_flag |= 0x80;
        mwk->spmv_ng_flag &= 0xFFFFFFBF;
        mwk->spmv_ng_flag &= 0xFFFFFFEF;
        break;

    case 3:
    case 5:
        mwk->spmv_ng_flag |= 0x40;
        mwk->spmv_ng_flag &= 0xFFFFFF7F;
        mwk->spmv_ng_flag &= 0xFFFFF0FF;
        break;
    }
}

static void configure_new_challenger_E3(WORK_Other* ewk, PLW* mwk) {
    if (mwk->wu.id != New_Challenger) {
        return;
    }

    mwk->py->now.quantity.h = 0;

    if (ewk->wu.direction == 0) {
        configure_challenger_restrictions_E3(mwk);
    } else {
        mwk->spmv_ng_flag |= 0xC0;
        mwk->spmv_ng_flag &= 0xFFFFFFEF;
        mwk->spmv_ng_flag &= 0xFFFFF0FF;
    }
}

static void configure_sa_gauge_E3(PLW* mwk) {
    switch (Training[0].contents[0][1][TRAINING_OPTION_SA_GAUGE]) {
    case 1:
        mwk->spmv_ng_flag2 &= 0xFFFBFFFF;
        mwk->spmv_ng_flag2 |= 0x90000;
        demo_set_sa_full(mwk->sa);
        tr_spgauge_cont_init2(mwk->wu.id);
        break;

    case 3:
        mwk->spmv_ng_flag2 &= 0xFFF7FFFF;
        mwk->spmv_ng_flag2 |= 0x50000;
        demo_set_sa_full(mwk->sa);
        tr_spgauge_cont_init2(mwk->wu.id);
        break;

    case 2:
        mwk->spmv_ng_flag2 &= 0xFFFEFFFF;
        mwk->spmv_ng_flag2 |= 0xC0000;
        clear_super_arts_point(mwk);
        tr_spgauge_cont_init(mwk->wu.id);
        break;

    case 0:
        mwk->spmv_ng_flag2 |= 0xD0000;
        clear_super_arts_point(mwk);
        tr_spgauge_cont_init(mwk->wu.id);
        break;
    }
}

typedef enum {
    INITIALIZATION_PAUSED_E3,
    INITIALIZATION_COMPLETE_E3,
} InitializationResultE3;

static InitializationResultE3 initialize_training_effect_E3(WORK_Other* ewk, PLW* mwk) {
    if (effect_should_stop(ewk, mwk)) {
        ewk->wu.routine_no[0] = 2;
        return INITIALIZATION_PAUSED_E3;
    }

    if (mwk->init_E3_flag == 0) {
        return INITIALIZATION_PAUSED_E3;
    }

    mwk->init_E3_flag = 0;

    if (Mode_Type != MODE_NORMAL_TRAINING) {
        return INITIALIZATION_PAUSED_E3;
    }

    configure_training_feedback_E3(ewk, mwk);
    configure_new_challenger_E3(ewk, mwk);
    configure_sa_gauge_E3(mwk);
    ewk->wu.routine_no[0]++;
    omop_spmv_ng_table[mwk->wu.id] = mwk->spmv_ng_flag;
    omop_spmv_ng_table2[mwk->wu.id] = mwk->spmv_ng_flag2;
    return INITIALIZATION_COMPLETE_E3;
}

static void enable_quick_stand_E3(PLW* mwk) {
    mwk->spmv_ng_flag2 |= DIP_UNKNOWN_9;
}

static void disable_quick_stand_E3(PLW* mwk) {
    mwk->spmv_ng_flag2 &= ~DIP_UNKNOWN_9;
}

static void update_quick_stand_E3(PLW* mwk) {
    switch (Training[0].contents[0][0][2]) {
    case 0:
        enable_quick_stand_E3(mwk);
        break;

    case 1:
        disable_quick_stand_E3(mwk);
        break;

    default:
        if (Game_timer & 0xF) {
            return;
        }

        if ((mwk->spmv_ng_flag2 & DIP2_QUICK_STAND_DISABLED) == 0) {
            enable_quick_stand_E3(mwk);
        } else {
            disable_quick_stand_E3(mwk);
        }

        break;
    }
}

static void disable_all_guard_assists_E3(PLW* mwk) {
    mwk->spmv_ng_flag |= DIP_AUTO_PARRY_DISABLED;
    mwk->spmv_ng_flag |= DIP_AUTO_GUARD_DISABLED;
    mwk->spmv_ng_flag |= DIP_GUARD_DISABLED;
}

static void enable_auto_guard_E3(PLW* mwk) {
    mwk->spmv_ng_flag |= DIP_AUTO_PARRY_DISABLED;
    mwk->spmv_ng_flag &= ~DIP_AUTO_GUARD_DISABLED;
    mwk->spmv_ng_flag &= ~DIP_GUARD_DISABLED;
}

static void enable_auto_parry_E3(PLW* mwk) {
    mwk->spmv_ng_flag |= DIP_AUTO_GUARD_DISABLED;
    mwk->spmv_ng_flag &= ~DIP_AUTO_PARRY_DISABLED;
    mwk->spmv_ng_flag &=
        (DIP_UNKNOWN_8 | DIP_UNKNOWN_9 | DIP_AIR_PARRY_DISABLED | DIP_ANTI_AIR_PARRY_DISABLED);
}

static void update_one_hit_guard_E3(WORK_Other* ewk, PLW* mwk) {
    if (mwk->wu.routine_no[1] == 1 || mwk->wu.routine_no[1] == 3) {
        ewk->wu.dm_vital = 1;
        ewk->wu.dir_timer = 12;
    } else {
        ewk->wu.dm_vital = 0;
    }

    if (ewk->wu.dm_vital) {
        mwk->spmv_ng_flag &= ~DIP_AUTO_GUARD_DISABLED;
        return;
    }

    if (ewk->wu.dir_timer == 0) {
        mwk->spmv_ng_flag |= DIP_AUTO_GUARD_DISABLED;
    } else {
        ewk->wu.dir_timer--;
    }
}

static void update_random_guard_E3(WORK_Other* ewk, PLW* mwk) {
    if (is_airborne_action_window(mwk)) {
        ewk->wu.dm_vital = 1;
        ewk->wu.dir_timer = 12;
    } else {
        ewk->wu.dm_vital = 0;
    }

    if (ewk->wu.dm_vital) {
        mwk->spmv_ng_flag &= ~DIP_AUTO_GUARD_DISABLED;
        return;
    }

    if (ewk->wu.dir_timer != 0) {
        ewk->wu.dir_timer--;
        return;
    }

    if ((Game_timer & 4) != 0) {
        mwk->spmv_ng_flag &= ~DIP_AUTO_GUARD_DISABLED;
    } else {
        mwk->spmv_ng_flag |= DIP_AUTO_GUARD_DISABLED;
    }
}

static void update_alternating_guard_E3(PLW* mwk) {
    if ((Game_timer & 2) != 0) {
        enable_auto_parry_E3(mwk);
    } else {
        disable_all_guard_assists_E3(mwk);
    }
}

static void update_rotating_guard_E3(PLW* mwk) {
    switch (Game_timer % 3) {
    case 1:
        disable_all_guard_assists_E3(mwk);
        break;

    case 2:
        enable_auto_guard_E3(mwk);
        break;

    default:
        enable_auto_parry_E3(mwk);
        break;
    }
}

static void update_guard_setting_E3(WORK_Other* ewk, PLW* mwk) {
    switch (Training[0].contents[0][0][1]) {
    case 0:
        update_one_hit_guard_E3(ewk, mwk);
        break;

    case 1:
        disable_all_guard_assists_E3(mwk);
        break;

    case 2:
        enable_auto_guard_E3(mwk);
        break;

    case 3:
        enable_auto_parry_E3(mwk);
        break;

    case 4:
        update_random_guard_E3(ewk, mwk);
        break;

    case 5:
        update_alternating_guard_E3(mwk);
        break;

    case 6:
        update_rotating_guard_E3(mwk);
        break;
    }
}

static void update_defense_training_E3(WORK_Other* ewk, PLW* mwk) {
    mwk->cp->waza_flag[7] = 2;
    update_quick_stand_E3(mwk);
    update_guard_setting_E3(ewk, mwk);
}

static s32 is_one_hit_stun_window_E3(const PLW* mwk) {
    return (mwk->wu.routine_no[1] == 1 && mwk->guard_chuu == 0) || mwk->wu.routine_no[1] == 3;
}

static void update_one_hit_stun_E3(WORK_Other* ewk, PLW* mwk) {
    if (is_one_hit_stun_window_E3(mwk)) {
        ewk->wu.vitality = 1;
        ewk->wu.dir_step = 20;
    } else {
        ewk->wu.vitality = 0;
    }

    if (ewk->wu.vitality != 0) {
        return;
    }

    if (ewk->wu.dir_step == 0) {
        mwk->py->now.quantity.h = mwk->py->genkai - 1;
    } else {
        ewk->wu.dir_step--;
    }
}

static void update_stun_setting_E3(WORK_Other* ewk, PLW* mwk) {
    switch (Training[0].contents[0][0][3]) {
    case 1:
        update_one_hit_stun_E3(ewk, mwk);
        break;

    case 2:
        mwk->py->now.quantity.h = 0;
        break;
    }
}

static void update_training_effect_E3(WORK_Other* ewk, PLW* mwk) {
    if (effect_should_stop(ewk, mwk)) {
        ewk->wu.routine_no[0] = 2;
        return;
    }

    if (mwk->init_E3_flag == 1) {
        ewk->wu.routine_no[0] = 0;
        mwk->spmv_ng_flag = ewk->master_ng_flag;
        mwk->spmv_ng_flag2 = ewk->master_ng_flag2;
        return;
    }

    if (New_Challenger != mwk->wu.id) {
        return;
    }

    if (ewk->wu.direction == 0) {
        update_defense_training_E3(ewk, mwk);
    }

    update_stun_setting_E3(ewk, mwk);
}

void effect_E3_move(WORK_Other* ewk) {
    PLW* mwk = (PLW*)ewk->my_master;

    switch (ewk->wu.routine_no[0]) {
    case 0:
        if (initialize_training_effect_E3(ewk, mwk) == INITIALIZATION_PAUSED_E3) {
            break;
        }

        /* fallthrough */

    case 1:
        update_training_effect_E3(ewk, mwk);
        break;

    case 2:
    default:
        push_effect_work(&ewk->wu);
        break;
    }
}

s32 effect_E3_init(PLW* wk) {
    WORK_Other* ewk;
    s16 ix;

    if ((ix = pull_effect_work(3)) == -1) {
        return -1;
    }

    ewk = (WORK_Other*)frw[ix];
    ewk->wu.be_flag = 1;
    ewk->wu.id = 143;
    ewk->wu.work_id = 16;
    ewk->my_master = wk;
    ewk->master_work_id = wk->wu.work_id;
    ewk->master_id = wk->wu.id;
    ewk->master_player = wk->player_number;
    ewk->master_ng_flag = wk->spmv_ng_flag;
    ewk->master_ng_flag2 = wk->spmv_ng_flag2;
    wk->init_E3_flag = 1;
    wk->wu.E3_work_index = ewk->wu.myself;
    return 0;
}
