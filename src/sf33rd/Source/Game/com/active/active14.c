/**
 * @file active14.c
 * COM Active: Akuma/Gouki
 */

#include "sf33rd/Source/Game/com/active/active14.h"
#include "sf33rd/Source/Game/com/active/active14_internal.h"
#include "sf33rd/Source/Game/com/patterns/com_pattern_run.h"
#include "sf33rd/Source/Game/com/patterns/com_patterns.h"
#include "common.h"
#include "sf33rd/Source/Game/com/com_sub.h"
#include "sf33rd/Source/Game/engine/workuser.h"

void (*const Pattern14_Tbl[151])();

void Computer14(PLW* wk) {
    Pattern14_Tbl[(s16)Pattern_Index[wk->wu.id]](wk);
}

void Pattern14_0000(PLW* wk) {
    active_pattern_lever_off_look(wk);
}

void Pattern14_0001(PLW* wk) {
    active_pattern_wait(wk, 0);
}

void Pattern14_0002(PLW* wk) {
    active_pattern_normal_attack(wk, 8, 0x10);
}

void Pattern14_0003(PLW* wk) {
    active_pattern_normal_attack(wk, 8, 0x20);
}

void Pattern14_0004(PLW* wk) {
    active_pattern_normal_attack(wk, 8, 0x40);
}

void Pattern14_0005(PLW* wk) {
    active_pattern_normal_attack(wk, 8, 0x100);
}

void Pattern14_0006(PLW* wk) {
    active_pattern_normal_attack(wk, 8, 0x200);
}

void Pattern14_0007(PLW* wk) {
    active_pattern_normal_attack(wk, 8, 0x400);
}

void Pattern14_0008(PLW* wk) {
    active_pattern_normal_attack(wk, 8, 0x12);
}

void Pattern14_0009(PLW* wk) {
    active_pattern_normal_attack(wk, 8, 0x22);
}

void Pattern14_0010(PLW* wk) {
    active_pattern_normal_attack(wk, 8, 0x42);
}

void Pattern14_0011(PLW* wk) {
    active_pattern_normal_attack(wk, 8, 0x102);
}

void Pattern14_0012(PLW* wk) {
    active_pattern_normal_attack(wk, 8, 0x202);
}

void Pattern14_0013(PLW* wk) {
    active_pattern_normal_attack(wk, 8, 0x402);
}

void Pattern14_0014(PLW* wk) {
    active_pattern_command_attack(wk, &(Command_Attack_Args){8, 0x1F, 8, -1});
}

void Pattern14_0015(PLW* wk) {
    active_pattern_command_attack(wk, &(Command_Attack_Args){8, 0x1F, 9, -1});
}

void Pattern14_0016(PLW* wk) {
    active_pattern_command_attack(wk, &(Command_Attack_Args){8, 0x1F, 0xA, -1});
}

void Pattern14_0017(PLW* wk) {
    active_pattern_command_attack_j_command_attack(
        wk,
        &(Command_Attack_Args){8, 0x1F, 8, -1},
        &(Command_Attack_Args){8, 0x1E, 8, -1}
    );
}

void Pattern14_0018(PLW* wk) {
    active_pattern_j_command_attack(wk, &(Command_Attack_Args){8, 0x1E, 8, -1});
}

void Pattern14_0019(PLW* wk) {
    active_pattern_j_command_attack(wk, &(Command_Attack_Args){8, 0x20, 8, -1});
}

void Pattern14_0020(PLW* wk) {
    active_pattern_j_command_attack(wk, &(Command_Attack_Args){8, 0x20, 9, -1});
}

void Pattern14_0021(PLW* wk) {
    active_pattern_j_command_attack(wk, &(Command_Attack_Args){8, 0x20, 0xA, -1});
}

void Pattern14_0022(PLW* wk) {
    active_pattern_j_command_attack_2(
        wk,
        &(Command_Attack_Args){9, 0x20, 8, -1},
        &(Command_Attack_Args){8, 0x1E, 8, -1}
    );
}

void Pattern14_0023(PLW* wk) {
    active_pattern_j_command_attack_2(
        wk,
        &(Command_Attack_Args){9, 0x20, 9, -1},
        &(Command_Attack_Args){8, 0x1E, 8, -1}
    );
}

void Pattern14_0024(PLW* wk) {
    active_pattern_keep_away(wk, 0x7F, 0);
}

void Pattern14_0025(PLW* wk) {
    active_pattern_keep_away(wk, 0xBF, 0);
}

static void pattern14_0026_from_step_6(PLW* wk) {
    const Pattern_Step script[8] = { [6] = STEP(SA_Term, 0x2f, 0xffff, 0x31, 0x7f),
                                     [7] = STEP(J_Command_Attack, 8, 0x1e, 10, -1) };
    Run_Pattern(wk, script, 8);
}

void Pattern14_0026(PLW* wk) {
    const Pattern_Step script[6] = { [0] = STEP_NOARG(Pierce_On),
                                     [1] = STEP(Approach_Walk, 0xbf, 3),
                                     [2] = STEP(
                                         Jump_Command_Attack_Term, 8, 0x2E, 8, -1, -1, 0x30, 0, -0x7F80, -1, 0x400),
                                     [3] = STEP(Normal_Attack, 0xb, 0x202),
                                     [4] = STEP(J_Command_Attack, 0xb, 0x20, 8, -1),
                                     [5] = STEP(Wait, 5) };
    Run_Pattern_Or(wk, script, 6, pattern14_0026_from_step_6);
}

void Pattern14_0027(PLW* wk) {
    active_pattern_lever_attack(wk, 8, 0, 0x20);
}

void Pattern14_0028(PLW* wk) {
    const Pattern_Step script[3] = { [0] = STEP(Approach_Walk, 0xBF, 3),
                                     [1] = STEP(
                                         Jump_Command_Attack_Term, 8, 0x2E, 8, -1, -1, 0x30, 0, -0x7F80, -1, 0x400),
                                     [2] = STEP(Lever_Attack, 8, 0, 0x20) };
    Run_Pattern(wk, script, 3);
}

void Pattern14_0029(PLW* wk) {
    active_pattern_approach_walk_jump_attack_term_normal_attack(wk, 3);
}

void Pattern14_0030(PLW* wk) {
    active_pattern_approach_walk_jump_attack_term_normal_attack_2(wk, 3);
}

void Pattern14_0031(PLW* wk) {
    active_pattern_approach_walk_jump_attack_term_normal_attack(wk, 2);
}

void Pattern14_0032(PLW* wk) {
    active_pattern_approach_walk_jump_attack_term_normal_attack_2(wk, 2);
}

void Pattern14_0033(PLW* wk) {
    const Pattern_Step script[6] = { [0] = STEP_NOARG(Pierce_On),
                                     [1] = STEP(Approach_Walk, 0xbf, 2),
                                     [2] = STEP(
                                         Jump_Command_Attack_Term, 8, 0x2e, 8, -1, -1, 0x30, 0, -0x7F80, -1, 0x400),
                                     [3] = STEP(Normal_Attack, 0xb, 0x202),
                                     [4] = STEP(J_Command_Attack, 8, 0x20, 8, -1),
                                     [5] = STEP(Wait, 3) };
    Run_Pattern_Or(wk, script, 6, active_pattern_j_command_attack_from_step_6);
}

void Pattern14_0034(PLW* wk) {
    active_pattern_pierce_on_approach_walk_jump_command_attack_term(
        wk,
        &(JCA_Term_Args){0xB, 0x2F, 0xA, -1, -1, 0x30, 0, -1, -1, -1}
    );
}

void Pattern14_0035(PLW* wk) {
    const Pattern_Step script[4] = { [0] = STEP_NOARG(Turn_Over_On),
                                     [1] = STEP(Hi_Jump_Attack_Term, -1, 0x61, 8, 0x202, 0, -0x7F80, -1, 0x400),
                                     [2] = STEP(Normal_Attack, 0xB, 0x202),
                                     [3] = STEP(Command_Attack, 8, 0x1F, 0xA, -1) };
    Run_Pattern(wk, script, 4);
}

void Pattern14_0036(PLW* wk) {
    const Pattern_Step script[6] = { [0] = STEP_NOARG(Turn_Over_On),
                                     [1] = STEP(Hi_Jump_Attack_Term, -1, 0x61, 8, 0x202, 0, 0x8080, -1, 0x400),
                                     [2] = STEP(Normal_Attack, 0xb, 0x202),
                                     [3] = STEP(Command_Attack, 0xc, 0x1f, 10, -1),
                                     [4] = STEP(Wait, 1),
                                     [5] = STEP(SA_Term, 0x2f, 0x30, 0x31, 0x7f) };
    Run_Pattern(wk, script, 6);
}

void Pattern14_0037(PLW* wk) {
    const Pattern_Step script[6] = { [0] = STEP_NOARG(Turn_Over_On),
                                     [1] = STEP(Hi_Jump_Attack_Term, -1, 0x61, 8, 0x202, 0, 0x8080, -1, 0x400),
                                     [2] = STEP(Normal_Attack, 0xb, 0x202),
                                     [3] = STEP_NOARG(Pierce_On),
                                     [4] = STEP(J_Command_Attack, 8, 0x20, 8, -1),
                                     [5] = STEP(Wait, 3) };
    Run_Pattern_Or(wk, script, 6, active_pattern_j_command_attack_from_step_6);
}

void Pattern14_0038(PLW* wk) {
    active_pattern_etc_term_j_command_attack(wk, 0, &(Command_Attack_Args){8, 0x20, 8, -1});
}

void Pattern14_0039(PLW* wk) {
    active_pattern_etc_term_j_command_attack(wk, 0, &(Command_Attack_Args){8, 0x20, 8, -1});
}

void Pattern14_0040(PLW* wk) {
    active_pattern_etc_term_j_command_attack(wk, 0, &(Command_Attack_Args){8, 0x20, 8, -1});
}

void Pattern14_0041(PLW* wk) {
    const Pattern_Step script[3] = { [0] = STEP(ETC_Term, 3, 2, 0),
                                     [1] = STEP(J_Command_Attack, 0xB, 0x20, 8, -1),
                                     [2] = STEP(J_Command_Attack, 8, 0x1E, 8, -1) };
    Run_Pattern(wk, script, 3);
}

void Pattern14_0042(PLW* wk) {
    const Pattern_Step script[5] = { [0] = STEP(ETC_Term, 3, 2, 0),
                                     [1] = STEP(Normal_Attack, 0xB, 0x202),
                                     [2] = STEP(Command_Attack, 0xC, 0x1F, 0xA, -1),
                                     [3] = STEP(Wait, 1),
                                     [4] = STEP(SA_Term, 0x2F, 0x30, 0x31, 0x7F) };
    Run_Pattern(wk, script, 5);
}

void Pattern14_0043(PLW* wk) {
    const Pattern_Step script[3] = { [0] = STEP(ETC_Term, 3, 2, 0),
                                     [1] = STEP(Normal_Attack, 0xB, 0x202),
                                     [2] = STEP(Command_Attack, 8, 0x1F, 0xA, -1) };
    Run_Pattern(wk, script, 3);
}

void Pattern14_0044(PLW* wk) {
    active_pattern_com_random_select(wk, &(Branch_Menu_Args){6, 0x71, 0x71, 0x72, 0x73}, 2);
}

void Pattern14_0045(PLW* wk) {
    active_pattern_com_random_select(wk, &(Branch_Menu_Args){6, 0x74, 0x74, 0x75, 0x76}, 2);
}

void Pattern14_0046(PLW* wk) {
    active_pattern_com_random_select(wk, &(Branch_Menu_Args){6, 0x77, 0x77, 0x78, 0x79}, 2);
}

void Pattern14_0047(PLW* wk) {
    active_pattern_command_attack(wk, &(Command_Attack_Args){8, 0x8014, 0xA, -1});
}

void Pattern14_0048(PLW* wk) {
    active_pattern_j_command_attack(wk, &(Command_Attack_Args){8, 0x8015, 0xA, -1});
}

void Pattern14_0049(PLW* wk) {
    active_pattern_j_command_attack(wk, &(Command_Attack_Args){8, 0x8016, 0xA, -1});
}

void Pattern14_0050(PLW* wk) {
    active_pattern_branch_unit_area(wk, &(Branch_Menu_Args){2, 0x37, 0x37, 0x36, 0x35});
}

void Pattern14_0051(PLW* wk) {
    active_pattern_jump_command_attack_term(wk, &(JCA_Term_Args){8, 0x8016, 0xA, -1, -0x7FB0, -0x7FC0, 0, -1, -1, -1});
}

static void pattern14_0052_from_step_6(PLW* wk) {
    const Pattern_Step script[11] = { [6] = STEP(Lever_On, 0, 0),
                                      [7] = STEP(Wait, 1),
                                      [8] = STEP(Only_Shot, 0x100),
                                      [9] = STEP(Wait, 1),
                                      [10] = STEP(Only_Shot, 0x40) };
    Run_Pattern(wk, script, 11);
}

void Pattern14_0052(PLW* wk) {
    const Pattern_Step script[6] = { [0] = STEP(Check_SA_Full, 6, 0x7c), [1] = STEP(EM_Term, 0x80d0, -1, 5, 2, 0),
                                     [2] = STEP(Only_Shot, 0x10),        [3] = STEP(Wait, 1),
                                     [4] = STEP(Only_Shot, 0x10),        [5] = STEP(Wait, 1) };
    Run_Pattern_Or(wk, script, 6, pattern14_0052_from_step_6);
}

void Pattern14_0053(PLW* wk) {
    active_pattern_jump_command_attack_term(wk, &(JCA_Term_Args){8, 0x8014, 8, -1, -1, 0x20, 0, -1, -1, -1});
}

void Pattern14_0054(PLW* wk) {
    active_pattern_jump_command_attack_term(wk, &(JCA_Term_Args){8, 0x8014, 8, -1, -1, 0x20, 2, -1, -1, -1});
}

void Pattern14_0055(PLW* wk) {
    active_pattern_jump_command_attack_term(wk, &(JCA_Term_Args){8, 0x8014, 8, -1, -1, 0x20, 1, -1, -1, -1});
}

void Pattern14_0056(PLW* wk) {
    const Pattern_Step script[3] = { [0] = STEP(Approach_Walk, 0xBF, 2),
                                     [1] = STEP(SA_Term, 0x32, 0xFFFF, 0xFFFF, 0xBF),
                                     [2] = STEP(
                                         Com_Random_Select, &(Branch_Menu_Args) { 6, 0x74, 0x74, 0x75, 0x76 }, 2) };
    Run_Pattern(wk, script, 3);
}

void Pattern14_0057(PLW* wk) {
    active_pattern_command_attack_com_random_select(
        wk,
        &(Command_Attack_Args){8, 0, -1, -1},
        &(Branch_Menu_Args){6, 0x84, 0x84, 0x85, 0x86},
        2
    );
}

void Pattern14_0058(PLW* wk) {
    pattern_approach_walk_jump_attack_term_normal_attack_4(wk, &(Command_Attack_Args){0xC, 0x1F, 0xA, -1});
}

static void pattern14_0059_from_step_6(PLW* wk) {
    const Pattern_Step script[7] = { [6] = STEP(SA_Term, 0x2f, 0x30, 0x31, 0x7f) };
    Run_Pattern(wk, script, 7);
}

void Pattern14_0059(PLW* wk) {
    const Pattern_Step script[6] = { [0] = STEP(Approach_Walk, 0xbf, 2),
                                     [1] = STEP(Jump_Attack_Term, 0x8058, 0x8038, 9, 0x400, 0, 0x8080, -1, 0x400),
                                     [2] = STEP(Normal_Attack, 9, 0x220),
                                     [3] = STEP(Normal_Attack, 0xc, 0x202),
                                     [4] = STEP(Command_Attack, 0xc, 0x1f, 10, -1),
                                     [5] = STEP(Wait, 1) };
    Run_Pattern_Or(wk, script, 6, pattern14_0059_from_step_6);
}

void Pattern14_0060(PLW* wk) {
    active_pattern_approach_walk_jump_attack_term_normal_attack_3(wk, &(SA_Term_Args){0x32, 0xFFFF, 0xFFFF, 0xBF});
}

void Pattern14_0061(PLW* wk) {
    pattern_approach_walk_turn_over_on_hi_jump_attack_term(
        wk,
        0xbf,
        &(Hi_Jump_Term_Args){-1, 0x61, 9, 0x202, 0, 0x8080, -1, 0x400},
        &(SA_Term_Args){0x32, 0xffff, 0xffff, 0xbf}
    );
}

void Pattern14_0062(PLW* wk) {
    active_pattern_approach_walk_jump_attack_term_normal_attack_3(wk, &(SA_Term_Args){0x34, 0x34, 0x34, 0x7F});
}

void pattern14_0063_from_step_6(PLW* wk) {
    const Pattern_Step script[8] = { [6] = STEP(Wait, 1), [7] = STEP(SA_Term, 0x2f, 0x30, 0x31, 0x7f) };
    Run_Pattern(wk, script, 8);
}

void (*const Pattern14_Tbl[151])(PLW*) = {
    Pattern14_0000, Pattern14_0001, Pattern14_0002, Pattern14_0003, Pattern14_0004, Pattern14_0005, Pattern14_0006,
    Pattern14_0007, Pattern14_0008, Pattern14_0009, Pattern14_0010, Pattern14_0011, Pattern14_0012, Pattern14_0013,
    Pattern14_0014, Pattern14_0015, Pattern14_0016, Pattern14_0017, Pattern14_0018, Pattern14_0019, Pattern14_0020,
    Pattern14_0021, Pattern14_0022, Pattern14_0023, Pattern14_0024, Pattern14_0025, Pattern14_0026, Pattern14_0027,
    Pattern14_0028, Pattern14_0029, Pattern14_0030, Pattern14_0031, Pattern14_0032, Pattern14_0033, Pattern14_0034,
    Pattern14_0035, Pattern14_0036, Pattern14_0037, Pattern14_0038, Pattern14_0039, Pattern14_0040, Pattern14_0041,
    Pattern14_0042, Pattern14_0043, Pattern14_0044, Pattern14_0045, Pattern14_0046, Pattern14_0047, Pattern14_0048,
    Pattern14_0049, Pattern14_0050, Pattern14_0051, Pattern14_0052, Pattern14_0053, Pattern14_0054, Pattern14_0055,
    Pattern14_0056, Pattern14_0057, Pattern14_0058, Pattern14_0059, Pattern14_0060, Pattern14_0061, Pattern14_0062,
    Pattern14_0063, Pattern14_0064, Pattern14_0065, Pattern14_0066, Pattern14_0067, Pattern14_0068, Pattern14_0069,
    Pattern14_0070, Pattern14_0071, Pattern14_0072, Pattern14_0073, Pattern14_0074, Pattern14_0075, Pattern14_0076,
    Pattern14_0077, Pattern14_0078, Pattern14_0079, Pattern14_0080, Pattern14_0081, Pattern14_0082, Pattern14_0083,
    Pattern14_0084, Pattern14_0085, Pattern14_0086, Pattern14_0087, Pattern14_0088, Pattern14_0089, Pattern14_0090,
    Pattern14_0091, Pattern14_0092, Pattern14_0093, Pattern14_0094, Pattern14_0095, Pattern14_0096, Pattern14_0097,
    Pattern14_0098, Pattern14_0099, Pattern14_0100, Pattern14_0101, Pattern14_0102, Pattern14_0103, Pattern14_0104,
    Pattern14_0105, Pattern14_0106, Pattern14_0107, Pattern14_0108, Pattern14_0109, Pattern14_0110, Pattern14_0111,
    Pattern14_0112, Pattern14_0113, Pattern14_0114, Pattern14_0115, Pattern14_0116, Pattern14_0117, Pattern14_0118,
    Pattern14_0119, Pattern14_0120, Pattern14_0121, Pattern14_0122, Pattern14_0123, Pattern14_0124, Pattern14_0125,
    Pattern14_0126, Pattern14_0127, Pattern14_0128, Pattern14_0129, Pattern14_0130, Pattern14_0131, Pattern14_0132,
    Pattern14_0133, Pattern14_0134, Pattern14_0135, Pattern14_0136, Pattern14_0137, Pattern14_0138, Pattern14_0139,
    Pattern14_0140, Pattern14_0141, Pattern14_0142, Pattern14_0143, Pattern14_0144, Pattern14_0145, Pattern14_0146,
    Pattern14_0147, Pattern14_0148, Pattern14_0149, Pattern14_0150
};
