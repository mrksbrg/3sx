/**
 * @file effe6.c
 * TODO: identify what this effect does
 */

#include "sf33rd/Source/Game/effect/effe6.h"
#include "sf33rd/Source/Game/effect/effe6_data.h"
#include "sf33rd/Source/Game/effect/effe6_early.h"
#include "sf33rd/Source/Game/effect/effe6_internal.h"
#include "sf33rd/Source/Game/effect/effe6_middle.h"
#include "sf33rd/Source/Game/effect/effe6_transition.h"
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

void effe6_0026(WORK_Other* ewk);
void effe6_0027(WORK_Other* ewk);
void effe6_0028(WORK_Other* ewk);
void effe6_0029(WORK_Other* ewk);
void effe6_0030(WORK_Other* ewk);
void effe6_0031(WORK_Other* ewk);
void effe6_0032(WORK_Other* ewk);
void effe6_0033(WORK_Other* ewk);


void effect_E6_move(WORK_Other* ewk) {
    void (*effe6_jp[34])(WORK_Other*) = { effe6_0000, effe6_0001, effe6_0002, effe6_0003, effe6_0004, effe6_0005,
                                          effe6_0006, effe6_0007, effe6_0007, effe6_0009, effe6_0010, effe6_0011,
                                          effe6_0012, effe6_0013, effe6_0014, effe6_0015, effe6_0016, effe6_0017,
                                          effe6_0018, effe6_0019, effe6_0020, effe6_0021, effe6_0022, effe6_0023,
                                          effe6_0024, effe6_0025, effe6_0026, effe6_0027, effe6_0028, effe6_0029,
                                          effe6_0030, effe6_0031, effe6_0032, effe6_0033 };

    switch (ewk->wu.routine_no[2]) {
    case 0x0:
        effe6_jp[ewk->wu.routine_no[0]](ewk);
        break;

    case 99:
        ewk->wu.routine_no[2]++;
        break;

    case 100:
        push_effect_work(&ewk->wu);
        break;

    case 4649:
        ewk->wu.routine_no[2] = 0;
        break;
    }
}

void mark_effe6_for_cleanup_if_stale(WORK_Other* ewk) {
    if (ewk->wu.old_rno[6] < end_w.r_no_2) {
        ewk->wu.routine_no[2] = 99;
    }
}




void effe6_0026(WORK_Other* ewk) {
    mark_effe6_for_cleanup_if_stale(ewk);

    switch (ewk->wu.routine_no[1]) {
    case 0:
        effe6_init_common(ewk);
        disp_pos_trans_entry(ewk);
        break;

    case 1:
        char_move(&ewk->wu);

        if (ewk->wu.xyz[1].disp.pos < 152) {
            ewk->wu.routine_no[1]++;
        }

        /* fallthrough */

    case 2:
        disp_pos_trans_entry(ewk);
        break;

    default:
        push_effect_work(&ewk->wu);
        break;
    }
}

void effe6_0027(WORK_Other* ewk) {
    mark_effe6_for_cleanup_if_stale(ewk);

    switch (ewk->wu.routine_no[1]) {
    case 0:
        effe6_init_common(ewk);
        disp_pos_trans_entry(ewk);
        break;

    case 1:
        char_move(&ewk->wu);

        if (ewk->wu.cg_type == 0xFF) {
            ewk->wu.routine_no[1]++;
            effect_E6_init(0xA7);
        }

        /* fallthrough */

    case 2:
        disp_pos_trans_entry(ewk);
        break;

    default:
        push_effect_work(&ewk->wu);
        break;
    }
}

void effe6_0028(WORK_Other* ewk) {
    mark_effe6_for_cleanup_if_stale(ewk);

    switch (ewk->wu.routine_no[1]) {
    case 0:
        effe6_init_common(ewk);
        disp_pos_trans_entry(ewk);
        break;

    case 1:
        char_move(&ewk->wu);

        if (ewk->wu.cg_type == 9) {
            ewk->wu.disp_flag = 0;
        } else {
            ewk->wu.disp_flag = 1;
        }

        disp_pos_trans_entry(ewk);
        break;

    default:
        push_effect_work(&ewk->wu);
        break;
    }
}

static void grow_effe6_0029_marker(WORK_Other* ewk) {
    ewk->wu.old_rno[2]--;

    if (ewk->wu.old_rno[2] <= 0) {
        ewk->wu.old_rno[2] = 5;
        ewk->wu.my_mr.size.x++;
        ewk->wu.my_mr.size.y++;

        if (ewk->wu.my_mr.size.x >= 127) {
            ewk->wu.routine_no[1]++;
            ewk->wu.my_mr.size.x = 127;
            ewk->wu.my_mr.size.y = 127;
        }
    }
}

void effe6_0029(WORK_Other* ewk) {
    mark_effe6_for_cleanup_if_stale(ewk);

    switch (ewk->wu.routine_no[1]) {
    case 0:
        effe6_init_common(ewk);
        ewk->wu.old_rno[2] = 5;
        ewk->wu.my_mr_flag = 1;
        ewk->wu.my_mr.size.x = 63;
        ewk->wu.my_mr.size.y = 63;
        disp_pos_trans_entry5(ewk);
        break;

    case 1:
        char_move(&ewk->wu);

        if (ewk->wu.xyz[0].disp.pos < 224) {
            ewk->wu.routine_no[2] = 99;
        } else {
            grow_effe6_0029_marker(ewk);
        }

        disp_pos_trans_entry5(ewk);
        break;

    case 2:
        disp_pos_trans_entry5(ewk);
        break;

    default:
        push_effect_work(&ewk->wu);
        break;
    }
}

static void start_effe6_0030_fade(WORK_Other* ewk) {
    s16 i;

    ewk->wu.routine_no[1]++;

    for (i = 0; i < 64; i++) {
        ColorRAM[327][i] = ColorRAM[343][i];
    }

    for (i = 0; i < 64; i++) {
        ColorRAM[328][i] = ColorRAM[343][i];
    }

    for (i = 0; i < 64; i++) {
        ColorRAM[329][i] = ColorRAM[343][i];
    }

    for (i = 0; i < 64; i++) {
        ColorRAM[330][i] = ColorRAM[343][i];
    }

    ewk->wu.disp_flag = 2;
    ewk->wu.blink_timing = 1;
    ewk->wu.old_rno[2] = 30;
    palUpdateGhostCP3(0x147, 4);
}

static void update_effe6_0030_color(WORK_Other* ewk) {
    if (end_w.r_no_2 == 4 && bg_w.bgw[0].r_no_1 == 1) {
        switch (bg_w.bgw[0].l_limit) {
        case 0:
            ewk->wu.my_col_code = 0x130;
            break;

        case 1:
            ewk->wu.my_col_code = 0x134;
            break;

        case 2:
            ewk->wu.my_col_code = 0x138;
            break;

        case 3:
            ewk->wu.my_col_code = 0x13C;
            break;
        }
    }
}

void effe6_0030(WORK_Other* ewk) {
    mark_effe6_for_cleanup_if_stale(ewk);

    switch (ewk->wu.routine_no[1]) {
    case 0:
        effe6_init_common(ewk);
        disp_pos_trans_entry(ewk);
        break;

    case 1:
        update_effe6_0030_color(ewk);

        if (end_etc_flag) {
            start_effe6_0030_fade(ewk);
        }

        disp_pos_trans_entry(ewk);
        break;

    case 2:
        ewk->wu.old_rno[2]--;

        if (ewk->wu.old_rno[2] < 0) {
            ewk->wu.routine_no[2] = 99;
        }

        disp_pos_trans_entry(ewk);
        break;

    default:
        push_effect_work(&ewk->wu);
        break;
    }
}

const s32 gill_range[7] = { 0x900000, 0x900000, 0x100000, 0x900000, 0x900000, 0x200000, 0x50000 };

static void update_effe6_0031_rise(WORK_Other* ewk) {
    ewk->wu.xyz[1].cal += gill_range[0] / gill_time[0];

    if (!(--ewk->wu.old_rno[5])) {
        ewk->wu.routine_no[1]++;
    }

    disp_pos_trans_entry(ewk);
}

void effe6_0031(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case 0:
        effe6_init_common(ewk);
        ewk->wu.old_rno[5] = gill_time[0];
        disp_pos_trans_entry(ewk);
        break;

    case 1:
        update_effe6_0031_rise(ewk);
        break;

    case 2:
        if (end_etc_flag) {
            ewk->wu.routine_no[1]++;
            ewk->wu.old_rno[5] = gill_time[1];
            end_etc_flag = 0;
        }

        disp_pos_trans_entry(ewk);
        break;

    case 3:
        ewk->wu.xyz[1].cal -= gill_range[1] / gill_time[1];

        if (!ewk->wu.old_rno[5]--) {
            ewk->wu.routine_no[1]++;
        }

        disp_pos_trans_entry(ewk);
        break;

    case 4:
        mark_effe6_for_cleanup_if_stale(ewk);

        disp_pos_trans_entry(ewk);
        break;
    }
}

static void initialize_effe6_0032(WORK_Other* ewk) {
    effe6_init_common(ewk);
    ewk->wu.old_rno[5] = gill_time[2];
    ewk->wu.old_rno[2] = ewk->wu.old_rno[7] = 0;

    switch (ewk->wu.type) {
    case 176:
        ewk->wu.routine_no[1] = 9;
        break;

    case 177:
    case 178:
        ewk->wu.routine_no[1] = 10;
        ewk->wu.old_rno[5] = gill_time[9];
        break;
    }

    disp_pos_trans_entry(ewk);
}

static void update_effe6_0032_intro_motion(WORK_Other* ewk) {
    mark_effe6_for_cleanup_if_stale(ewk);

    switch (ewk->wu.type) {
    case 174:
        ewk->wu.xyz[1].cal -= gill_range[2] / gill_time[2];
        break;

    case 175:
        ewk->wu.xyz[1].cal -= gill_range[3] / gill_time[2];
        break;
    }

    if (!ewk->wu.old_rno[5]--) {
        ewk->wu.routine_no[1]++;
    }

    disp_pos_trans_entry(ewk);
}

static void update_effe6_0032_outro_motion(WORK_Other* ewk) {
    mark_effe6_for_cleanup_if_stale(ewk);

    switch (ewk->wu.type) {
    case 177:
        ewk->wu.xyz[0].cal -= gill_range[5] / gill_time[4];
        break;

    case 178:
        ewk->wu.xyz[0].cal += gill_range[6] / gill_time[4];
        break;
    }

    if (!ewk->wu.old_rno[5]--) {
        ewk->wu.routine_no[1]++;
    }

    char_move(&ewk->wu);
    disp_pos_trans_entry(ewk);
}

static bool update_effe6_0032_intro(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case 0:
        initialize_effe6_0032(ewk);
        return true;

    case 1:
        update_effe6_0032_intro_motion(ewk);
        return true;

    case 2:
        mark_effe6_for_cleanup_if_stale(ewk);

        ewk->wu.routine_no[1]++;
        ewk->wu.old_rno[5] = gill_time[3];
        disp_pos_trans_entry(ewk);

    case 3:
        mark_effe6_for_cleanup_if_stale(ewk);

        ewk->wu.xyz[1].cal -= gill_range[4] / gill_time[3];

        if (!ewk->wu.old_rno[5]--) {
            ewk->wu.routine_no[1]++;
        }

        disp_pos_trans_entry(ewk);
        return true;

    case 4:
        mark_effe6_for_cleanup_if_stale(ewk);

        disp_pos_trans_entry(ewk);
        return true;

    default:
        return false;
    }
}

void effe6_0032(WORK_Other* ewk) {
    if (update_effe6_0032_intro(ewk)) {
        return;
    }

    switch (ewk->wu.routine_no[1]) {

    case 9:
        char_move(&ewk->wu);

        if (ewk->wu.cg_type) {
            ewk->wu.routine_no[1]++;
            end_etc_flag = 1;
            effect_E6_init(177);
            effect_E6_init(178);
            ewk->wu.old_rno[5] = gill_time[9];
        }

        disp_pos_trans_entry(ewk);
        break;

    case 10:
        mark_effe6_for_cleanup_if_stale(ewk);

        ewk->wu.routine_no[1]++;
        ewk->wu.old_rno[5] = gill_time[4];
        char_move(&ewk->wu);
        disp_pos_trans_entry(ewk);
        break;

    case 11:
        update_effe6_0032_outro_motion(ewk);
        break;

    case 12:
        mark_effe6_for_cleanup_if_stale(ewk);

        char_move(&ewk->wu);
        disp_pos_trans_entry(ewk);
        break;
    }
}

void effe6_0033(WORK_Other* ewk) {
    switch (ewk->wu.routine_no[1]) {
    case 0:
        effe6_init_common(ewk);
        ewk->wu.old_rno[5] = end_0_1_time[0] + gill_time[0];
        ewk->wu.my_clear_level = 0xFF;
        disp_pos_trans_entry(ewk);
        break;

    case 1:
        mark_effe6_for_cleanup_if_stale(ewk);

        if (!ewk->wu.old_rno[5]--) {
            ewk->wu.routine_no[1]++;
        }

        disp_pos_trans_entry(ewk);
        break;

    case 2:
        mark_effe6_for_cleanup_if_stale(ewk);

        ewk->wu.my_clear_level -= 256 / gill_time[7];

        if (ewk->wu.my_clear_level <= 0) {
            ewk->wu.routine_no[1]++;
            ewk->wu.my_clear_level = 0;
        }

        disp_pos_trans_entry(ewk);
        break;

    case 3:
        mark_effe6_for_cleanup_if_stale(ewk);

        disp_pos_trans_entry(ewk);
        break;
    }
}

void effe6_init_common(WORK_Other* ewk) {
    ewk->wu.routine_no[1]++;
    ewk->wu.disp_flag = 1;
    set_char_move_init2(&ewk->wu, 0, ewk->wu.old_rno[4], ewk->wu.char_index, 0);
}

s32 effect_E6_init(u8 char_num) {
    WORK_Other* ewk;
    s16 ix;
    const s16* data_ptr;

    if ((ix = pull_effect_work(4)) == -1) {
        return -1;
    }

    ewk = (WORK_Other*)frw[ix];
    ewk->wu.id = 146;
    ewk->wu.be_flag = 1;
    ewk->wu.type = char_num;
    ewk->wu.work_id = 16;
    ewk->wu.cgromtype = 1;
    ewk->wu.old_rno[0] = end_w.r_no_2;
    ewk->wu.my_col_mode = 0x4200;
    ewk->wu.char_table[0] = (u32*)_end_char_table;
    ewk->wu.my_col_code = 0x12C;
    data_ptr = &effe6_data_tbl[char_num][0];
    ewk->wu.my_family = *data_ptr++;
    ewk->wu.old_rno[6] = *data_ptr++;
    ewk->wu.old_rno[6] += end_w.r_no_2;
    ewk->wu.old_rno[4] = *data_ptr++;
    ewk->wu.xyz[0].disp.pos = *data_ptr++;
    ewk->wu.xyz[1].disp.pos = *data_ptr++;
    ewk->wu.my_priority = ewk->wu.position_z = *data_ptr++;
    ewk->wu.char_index = *data_ptr++;
    ewk->wu.old_rno[1] = ewk->wu.char_index - 1;
    ewk->wu.routine_no[0] = *data_ptr;
    ewk->wu.my_mts = 8;
    ewk->wu.my_trans_mode = get_my_trans_mode(ewk->wu.my_mts);

    switch (char_num) {
    case 79:
        ewk->wu.routine_no[2] = 0;
        break;

    default:
        ewk->wu.routine_no[2] = 4649;
        break;
    }

    return 0;
}

static const u16 END_BCB[20] = { 0x8D00, 0x8D40, 0x8D60, 0x8DC0, 0x8DE0, 0x8E00, 0x8E20, 0x8E40, 0x8E60, 0x8E80,
                                 0x8EA0, 0x8EC0, 0x8EE0, 0x8F00, 0x8F20, 0x8F60, 0x8F80, 0x8FA0, 0x8FC0, 0x9000 };

static const u16 END_COL[20] = {
    89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108
};

void ending_obj_load() {
    make_texcash_work(12);
    load_any_texture_patnum(0x7F30, 23, 0);
    load_any_texture_patnum(0x78B0, 23, 0);
    make_texcash_work(8);
    load_any_texture_patnum(END_BCB[End_PL], 23, 0);
    load_any_color(END_COL[End_PL], 2);
}
