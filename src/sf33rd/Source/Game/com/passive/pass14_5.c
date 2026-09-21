/**
 * @file pass14_5.c
 * COM Passive: Akuma/Gouki
 * Pattern scripts from Passive14_0209 on.
 */

#include "sf33rd/Source/Game/com/passive/pass14.h"
#include "sf33rd/Source/Game/com/passive/pass14_internal.h"
#include "sf33rd/Source/Game/com/patterns/com_pattern_run.h"
#include "sf33rd/Source/Game/com/patterns/com_patterns.h"
#include "common.h"
#include "sf33rd/Source/Game/com/com_sub.h"
#include "sf33rd/Source/Game/engine/workuser.h"

void Passive14_0209(PLW* wk) {
    passive14_pattern_approach_walk_jump_command_attack_term_com_random_select(
        wk,
        0xBF,
        &(Branch_Menu_Args){2, 0x50, 0x51, 0x52, 0x53}
    );
}

void Passive14_0210(PLW* wk) {
    passive14_pattern_approach_walk_jump_command_attack_term_com_random_select(
        wk,
        0xAD,
        &(Branch_Menu_Args){2, 0x54, 0x55, 0x56, 0x57}
    );
}

void Passive14_0211(PLW* wk) {
    passive14_pattern_approach_walk_jump_command_attack_term_com_random_select(
        wk,
        0xBF,
        &(Branch_Menu_Args){2, 0x58, 0x59, 0x5A, 0x5B}
    );
}

void Passive14_0212(PLW* wk) {
    pattern_sa_term_com_random_select(
        wk,
        &(SA_Term_Args){0x32, 0xFFFF, 0xFFFF, 0xBF},
        &(Branch_Menu_Args){6, 0x71, 0x71, 0x72, 0x73},
        2
    );
}

void Passive14_0213(PLW* wk) {
    passive14_pattern_em_term_com_random_select(wk, &(Branch_Menu_Args){2, 0x4C, 0x4D, 0x4E, 0x4F}, 0);
}

void Passive14_0214(PLW* wk) {
    passive14_pattern_em_term_com_random_select(wk, &(Branch_Menu_Args){2, 0x50, 0x51, 0x52, 0x53}, 0);
}

void Passive14_0215(PLW* wk) {
    passive14_pattern_em_term_com_random_select(wk, &(Branch_Menu_Args){2, 0x54, 0x55, 0x56, 0x57}, 0);
}

void Passive14_0216(PLW* wk) {
    passive14_pattern_em_term_com_random_select(wk, &(Branch_Menu_Args){2, 0x58, 0x59, 0x5A, 0x5B}, 0);
}

static void passive14_pattern_command_attack_turn_over_on_jump_attack_term(PLW* wk, const Branch_Menu_Args* p) {
    const Pattern_Step script[4] = { [0] = STEP(Command_Attack, 8, 1, -1, -1),
                                     [1] = STEP_NOARG(Turn_Over_On),
                                     [2] = STEP(Jump_Attack_Term, -1, 0x49, 9, 0x202, 0, -0x7F80, -1, 0x40),
                                     [3] = STEP(Com_Random_Select, p, 0) };
    Run_Pattern(wk, script, 4);
}

void Passive14_0217(PLW* wk) {
    passive14_pattern_command_attack_turn_over_on_jump_attack_term(wk, &(Branch_Menu_Args){2, 0x4C, 0x4D, 0x4E, 0x4F});
}

void Passive14_0218(PLW* wk) {
    passive14_pattern_command_attack_turn_over_on_jump_attack_term(wk, &(Branch_Menu_Args){2, 0x50, 0x51, 0x52, 0x53});
}

void Passive14_0219(PLW* wk) {
    passive14_pattern_command_attack_turn_over_on_jump_attack_term(wk, &(Branch_Menu_Args){2, 0x54, 0x55, 0x56, 0x57});
}

void Passive14_0220(PLW* wk) {
    passive14_pattern_command_attack_turn_over_on_jump_attack_term(wk, &(Branch_Menu_Args){2, 0x58, 0x59, 0x5A, 0x5B});
}

void Passive14_0221(PLW* wk) {
    pattern_search_back_term_command_attack_sa_term_2(wk, 0x300, 0xE1, &(Command_Attack_Args){8, 0x1D, 10, -1});
}

void Passive14_0222(PLW* wk) {
    pattern_search_back_term_command_attack_sa_term_2(wk, 0x80, 0xE1, &(Command_Attack_Args){8, 0x1D, 10, -1});
}

void Passive14_0223(PLW* wk) {
    pattern_search_back_term_command_attack_sa_term_2(wk, 0x200, 0xE2, &(Command_Attack_Args){8, 0x1D, 8, -1});
}

void Passive14_0224(PLW* wk) {
    pattern_search_back_term_command_attack_sa_term_2(wk, 0x100, 0xE2, &(Command_Attack_Args){8, 0x1D, 8, -1});
}

static void passive14_pattern_command_attack_sa_term_em_term(PLW* wk, const Command_Attack_Args* p,
                                                             const SA_Term_Args* p_b) {
    const Pattern_Step script[4] = { [0] = STEP_WITH(Command_Attack, p),
                                     [1] = STEP_WITH(SA_Term, p_b),
                                     [2] = STEP(EM_Term, -0x7FB0, -1, 5, 6, 1),
                                     [3] = STEP(J_Command_Attack, 8, 0x1E, 8, -1) };
    Run_Pattern(wk, script, 4);
}

void Passive14_0225(PLW* wk) {
    passive14_pattern_command_attack_sa_term_em_term(
        wk,
        &(Command_Attack_Args){8, 0x1C, 10, -1},
        &(SA_Term_Args){0x34, 0x34, 0x34, 0x47}
    );
}

void Passive14_0226(PLW* wk) {
    passive14_pattern_command_attack_sa_term_em_term(
        wk,
        &(Command_Attack_Args){8, 0x1C, 8, -1},
        &(SA_Term_Args){0x34, 0x34, 0x34, 0x47}
    );
}

void Passive14_0227(PLW* wk) {
    passive14_pattern_command_attack_sa_term_em_term(
        wk,
        &(Command_Attack_Args){8, 0x1C, 10, -1},
        &(SA_Term_Args){0x2F, 0x30, 0x31, 0x47}
    );
}

void Passive14_0228(PLW* wk) {
    passive14_pattern_command_attack_sa_term_em_term(
        wk,
        &(Command_Attack_Args){8, 0x1C, 8, -1},
        &(SA_Term_Args){0x2F, 0x30, 0x31, 0x47}
    );
}

void Passive14_0229(PLW* wk) {
    passive14_pattern_command_attack_sa_term_em_term(
        wk,
        &(Command_Attack_Args){8, 0x22, 8, -1},
        &(SA_Term_Args){0x34, 0x34, 0x34, 0x47}
    );
}

void Passive14_0230(PLW* wk) {
    const Pattern_Step script[6] = { [0] = STEP(EM_Term, -1, -0x7FF8, 6, 6, 1),
                                     [1] = STEP(Check_SA_Full, 6, 0x11),
                                     [2] = STEP(SA_Term, 0x34, 0x34, 0x34, 0x7F),
                                     [3] = STEP(Normal_Attack, 0xC, 0x40),
                                     [4] = STEP_NOARG(Pierce_On),
                                     [5] = STEP(J_Command_Attack, 8, 0x20, 8, -1) };
    Run_Pattern_Or(wk, script, 6, pattern_wait_j_command_attack_from_step_6);
}

void Passive14_0231(PLW* wk) {
    const Pattern_Step script[6] = { [0] = STEP(Command_Attack, 8, 0, -1, -1),
                                     [1] = STEP(Check_SA_Full, 6, 0x11),
                                     [2] = STEP(SA_Term, 0x34, 0x34, 0x34, 0xBF),
                                     [3] = STEP(Normal_Attack, 0xC, 0x40),
                                     [4] = STEP_NOARG(Pierce_On),
                                     [5] = STEP(J_Command_Attack, 8, 0x20, 8, -1) };
    Run_Pattern_Or(wk, script, 6, pattern_wait_j_command_attack_from_step_6);
}

void Passive14_0232(PLW* wk) {
    pattern_approach_walk_look(wk, 3);
}

void Passive14_0233(PLW* wk) {
    pattern_approach_walk_look(wk, 2);
}

void Passive14_0234(PLW* wk) {
    const Pattern_Step script[4] = { [0] = STEP(Wait_Attack_Complete, 1, 1),
                                     [1] = STEP(EM_Term, -1, -0x7FF8, 6, 6, 1),
                                     [2] = STEP(Normal_Attack, 0xC, 0x202),
                                     [3] = STEP(Command_Attack, 8, 0x1F, 10, -1) };
    Run_Pattern(wk, script, 4);
}

void Passive14_0235(PLW* wk) {
    passive14_pattern_em_term_sa_term_j_command_attack(
        wk,
        &(EM_Term_Params){-0x7F80, -1, 6, 6, 1},
        &(SA_Term_Args){0x2F, 0x30, 0x31, 0x7F}
    );
}

void Passive14_0236(PLW* wk) {
    const Pattern_Step script[6] = { [0] = STEP(EM_Term, -0x7F68, -1, 6, 6, 1),
                                     [1] = STEP(EM_Term, -1, -0x7FF8, 4, 6, 0xEB),
                                     [2] = STEP(Normal_Attack, 0xC, 0x202),
                                     [3] = STEP(Command_Attack, 0xC, 0x1F, 10, -1),
                                     [4] = STEP(Wait, 1),
                                     [5] = STEP(SA_Term, 0x2F, 0x30, 0x31, 0x7F) };
    Run_Pattern(wk, script, 6);
}

void Passive14_0237(PLW* wk) {
    active_pattern_em_term_j_command_attack(
        wk,
        &(EM_Term_Params){-0x7F80, -1, 6, 6, 1},
        &(Command_Attack_Args){8, 0x1E, 0xA, -1}
    );
}

void Passive14_0238(PLW* wk) {
    const Pattern_Step script[3] = { [0] = STEP(Normal_Attack, 9, 0x10),
                                     [1] = STEP(Normal_Attack, 0xC, 0x202),
                                     [2] = STEP(Command_Attack, 8, 0x1F, 0xA, -1) };
    Run_Pattern(wk, script, 3);
}

void Passive14_0239(PLW* wk) {
    pattern_jump(wk, 0);
}

void Passive14_0240(PLW* wk) {
    pattern_wait_get_up_com_random_select(wk, 3, 0, &(Branch_Menu_Args){2, 0x84, 0x85, 0x86, 0x87});
}

static void passive14_pattern_approach_walk_wait_get_up_turn_over_on(PLW* wk, const Branch_Menu_Args* p) {
    const Pattern_Step script[5] = { [0] = STEP(Approach_Walk, 0x57, 3),
                                     [1] = STEP(Wait_Get_Up, 3, 0),
                                     [2] = STEP_NOARG(Turn_Over_On),
                                     [3] = STEP(Jump_Attack_Term, -1, 0x49, 9, 0x202, 0, -0x7F80, -1, 0x40),
                                     [4] = STEP(Com_Random_Select, p, 0) };
    Run_Pattern(wk, script, 5);
}

void Passive14_0241(PLW* wk) {
    passive14_pattern_approach_walk_wait_get_up_turn_over_on(wk, &(Branch_Menu_Args){2, 0x89, 0x8A, 0x8B, 0x8C});
}

void Passive14_0242(PLW* wk) {
    const Pattern_Step script[4] = { [0] = STEP(Wait_Get_Up, 3, 0),
                                     [1] = STEP_NOARG(Turn_Over_On),
                                     [2] = STEP(Jump_Attack_Term, -1, 0x49, 9, 0x202, 0, -0x7F80, -1, 0x40),
                                     [3] = STEP(
                                         Com_Random_Select, &(Branch_Menu_Args) { 2, 0x89, 0x8A, 0x8B, 0x8C }, 0) };
    Run_Pattern(wk, script, 4);
}

void Passive14_0243(PLW* wk) {
    active_pattern_com_random_select(wk, &(Branch_Menu_Args){2, 0x26, 0x27, 0x28, 0x29}, 0);
}

void Passive14_0244(PLW* wk) {
    passive14_pattern_approach_walk_wait_get_up_turn_over_on(wk, &(Branch_Menu_Args){2, 0x4C, 0x4D, 0x4E, 0x4F});
}

void Passive14_0245(PLW* wk) {
    passive14_pattern_approach_walk_wait_get_up_turn_over_on(wk, &(Branch_Menu_Args){2, 0x50, 0x51, 0x52, 0x53});
}

void Passive14_0246(PLW* wk) {
    passive14_pattern_approach_walk_wait_get_up_turn_over_on(wk, &(Branch_Menu_Args){2, 0x54, 0x55, 0x56, 0x57});
}

void Passive14_0247(PLW* wk) {
    passive14_pattern_approach_walk_wait_get_up_turn_over_on(wk, &(Branch_Menu_Args){2, 0x58, 0x59, 0x5A, 0x5B});
}

void Passive14_0248(PLW* wk) {
    active_pattern_com_random_select(wk, &(Branch_Menu_Args){2, 0x89, 0x8A, 0x8B, 0x8C}, 0);
}

void Passive14_0249(PLW* wk) {
    active_pattern_normal_attack_command_attack(wk, 0xC, 0x402, &(Command_Attack_Args){0xC, 0x1F, 0xA, -1});
}

void Passive14_0250(PLW* wk) {
    active_pattern_com_random_select(wk, &(Branch_Menu_Args){6, 0x77, 0x77, 0x78, 0x79}, 2);
}

void Passive14_0251(PLW* wk) {
    const Pattern_Step script[2] = { [0] = STEP(Command_Attack, 8, 0x8019, 0xA, -1),
                                     [1] = STEP(J_Command_Attack, 0xB, 0x20, 9, -1) };
    Run_Pattern(wk, script, 2);
}

void Passive14_0252(PLW* wk) {
    pattern_check_sa_full_em_term_command_attack(wk);
}
