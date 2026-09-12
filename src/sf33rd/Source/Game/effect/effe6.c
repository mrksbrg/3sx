/**
 * @file effe6.c
 * TODO: identify what this effect does
 */

#include "sf33rd/Source/Game/effect/effe6.h"
#include "sf33rd/Source/Game/effect/effe6_arc.h"
#include "sf33rd/Source/Game/effect/effe6_ascent.h"
#include "sf33rd/Source/Game/effect/effe6_animation_cycle.h"
#include "sf33rd/Source/Game/effect/effe6_controls.h"
#include "sf33rd/Source/Game/effect/effe6_data.h"
#include "sf33rd/Source/Game/effect/effe6_delayed.h"
#include "sf33rd/Source/Game/effect/effe6_descent.h"
#include "sf33rd/Source/Game/effect/effe6_early.h"
#include "sf33rd/Source/Game/effect/effe6_early_variant.h"
#include "sf33rd/Source/Game/effect/effe6_endgame.h"
#include "sf33rd/Source/Game/effect/effe6_internal.h"
#include "sf33rd/Source/Game/effect/effe6_late.h"
#include "sf33rd/Source/Game/effect/effe6_late_alternate.h"
#include "sf33rd/Source/Game/effect/effe6_lift.h"
#include "sf33rd/Source/Game/effect/effe6_middle.h"
#include "sf33rd/Source/Game/effect/effe6_palette.h"
#include "sf33rd/Source/Game/effect/effe6_shrink.h"
#include "sf33rd/Source/Game/effect/effe6_transition.h"
#include "sf33rd/Source/Game/effect/effe6_visibility.h"
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
