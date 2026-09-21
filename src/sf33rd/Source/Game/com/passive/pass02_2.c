/**
 * @file pass02_2.c
 * COM Passive: Ryu
 * Pattern scripts from Passive02_0065 on.
 */

#include "sf33rd/Source/Game/com/passive/pass02.h"
#include "sf33rd/Source/Game/com/passive/pass02_internal.h"
#include "sf33rd/Source/Game/com/patterns/com_pattern_run.h"
#include "sf33rd/Source/Game/com/patterns/com_patterns.h"
#include "common.h"
#include "sf33rd/Source/Game/com/com_sub.h"
#include "sf33rd/Source/Game/engine/workuser.h"

void Passive02_0065(PLW* wk) {
    pattern_approach_walk_normal_attack_command_attack(wk, 0xB, 0x200, &(Command_Attack_Args){8, 0x1F, 8, -1});
}

void Passive02_0066(PLW* wk) {
    const Pattern_Step script[3] = { [0] = STEP(Approach_Walk, 0xBF, 2),
                                     [1] = STEP(SA_Term, 0x35, 0x36, 0xFFFF, 0x47),
                                     [2] = STEP(SA_Term, 0xFFFF, 0xFFFF, 0x19, 0x3C) };
    Run_Pattern(wk, script, 3);
}

void Passive02_0067(PLW* wk) {
    pattern_wait_attack_complete(wk, 0);
}

void Passive02_0068(PLW* wk) {
    const Pattern_Step script[2] = { [0] = STEP(Wait_Attack_Complete, 3, 1), [1] = STEP(Next_Be_Passive, 0) };
    Run_Pattern(wk, script, 2);
}

void Passive02_0069(PLW* wk) {
    pattern_wait_attack_complete_sa_term_wait_attack_complete(wk, &(SA_Term_Args){0x35, 0xFFFF, 0x37, 0});
}

static void passive02_0070_from_step_6(PLW* wk) {
    const Pattern_Step script[7] = { [6] = STEP(Normal_Attack, 8, 0x202) };
    Run_Pattern(wk, script, 7);
}

void Passive02_0070(PLW* wk) {
    const Pattern_Step script[6] = { [0] = STEP(Approach_Walk, 0x40, 2),
                                     [1] = STEP(Wait_Get_Up, 0, -1),
                                     [2] = STEP(Wait, 10),
                                     [3] = STEP(SA_Term, 0x35, 0x36, 0xFFFF, 0x47),
                                     [4] = STEP(SA_Term, 0xFFFF, 0xFFFF, 0x19, 0x3C),
                                     [5] = STEP(Wait_Get_Up, 0, -1) };
    Run_Pattern_Or(wk, script, 6, passive02_0070_from_step_6);
}

static void passive02_0071_from_step_6(PLW* wk) {
    const Pattern_Step script[8] = { [6] = STEP(Wait, 1), [7] = STEP(Command_Attack, 8, 0x1D, 10, -1) };
    Run_Pattern(wk, script, 8);
}

void Passive02_0071(PLW* wk) {
    const Pattern_Step script[6] = {
        [0] = STEP(Approach_Walk, 0x37, 2), [1] = STEP(EM_Term, -1, -0x7FF0, 0, 1, -1),
        [2] = STEP(ETC_Term, 8, 6, 7),      [3] = STEP(Check_SA, 6, 7),
        [4] = STEP_NOARG(Pierce_On),        [5] = STEP(Command_Attack, 8, 0x8016, 10, -1)
    };
    Run_Pattern_Or(wk, script, 6, passive02_0071_from_step_6);
}

void Passive02_0072(PLW* wk) {
    active_pattern_sa_term_command_attack(
        wk,
        &(SA_Term_Args){0x35, 0xFFFF, 0xFFFF, 0},
        &(Command_Attack_Args){8, 0x1D, 0xA, -1}
    );
}

void Passive02_0073(PLW* wk) {
    const Pattern_Step script[4] = { [0] = STEP(SA_Term, 0x35, 0xFFFF, 0x37, 0),
                                     [1] = STEP(Adjust_Attack, 0xB, 0x10),
                                     [2] = STEP(Normal_Attack, 0xA, 0x202),
                                     [3] = STEP(Command_Attack, 8, 0x1F, 8, -1) };
    Run_Pattern(wk, script, 4);
}

void Passive02_0074(PLW* wk) {
    pattern_sa_term_command_attack_2(
        wk,
        &(SA_Term_Args){0x35, 0x36, 0xFFFF, 0x47},
        &(SA_Term_Args){0xFFFF, 0xFFFF, 0x19, 0x3C},
        &(Command_Attack_Args){8, 0x1F, 8, -1}
    );
}

void Passive02_0075(PLW* wk) {
    pattern_em_term_normal_attack_j_command_attack(
        wk,
        &(EM_Term_Params){-0x7FC0, -1, 5, 6, 0x1F},
        0x12,
        &(Command_Attack_Args){8, 0x1C, 8, -1}
    );
}

void Passive02_0076(PLW* wk) {
    active_pattern_em_term_lever_attack(wk, &(EM_Term_Params){-0x7FB0, -1, 5, 6, 0x1C}, 0, 0x20);
}

void Passive02_0077(PLW* wk) {
    pattern_wait_attack_complete_normal_attack(wk);
}

static void passive02_0078_from_step_6(PLW* wk) {
    const Pattern_Step script[9] = { [6] = STEP(EM_Term, -0x7F58, -1, 0, 1, -1),
                                     [7] = STEP(Wait, 2),
                                     [8] = STEP(J_Command_Attack, 8, 0x1C, 10, -1) };
    Run_Pattern(wk, script, 9);
}

void Passive02_0078(PLW* wk) {
    const Pattern_Step script[6] = { [0] = STEP(Approach_Walk, 0xBF, 2),
                                     [1] = STEP(Wait_Get_Up, 0, -1),
                                     [2] = STEP(Check_EX, 6, 0x70),
                                     [3] = STEP_NOARG(Pierce_On),
                                     [4] = STEP(Command_Attack, 8, 0x1F, 8, 0x700),
                                     [5] = STEP(Check_BOSS_EX, 1, 0xFFFF) };
    Run_Pattern_Or(wk, script, 6, passive02_0078_from_step_6);
}

void Passive02_0079(PLW* wk) {
    pattern_forced_guard(wk, 2);
}

void Passive02_0080(PLW* wk) {
    const Pattern_Step script[5] = { [0] = STEP(Jump_Attack_Term, -0x7FA0, -0x7FC0, 9, 0x400, 0, -0x7FB0, -1, 0x200),
                                     [1] = STEP(Normal_Attack, 9, 0x42),
                                     [2] = STEP(Command_Attack, 0xC, 0x1C, 0xA, -1),
                                     [3] = STEP(Wait, 5),
                                     [4] = STEP(SA_Term, 0x35, 0x36, 0x37, 0) };
    Run_Pattern(wk, script, 5);
}

void Passive02_0081(PLW* wk) {
    const Pattern_Step script[6] = { [0] = STEP(Jump_Attack_Term, -0x7FA0, -0x7FC0, 9, 0x40, 0, -0x7FB0, -1, 0x400),
                                     [1] = STEP(Normal_Attack, 9, 0x40),
                                     [2] = STEP(Command_Attack, 0xC, 0x1D, 10, -1),
                                     [3] = STEP(Wait, 5),
                                     [4] = STEP(SA_Term, 0x35, 0x36, 0xFFFF, 0x47),
                                     [5] = STEP(SA_Term, 0xFFFF, 0xFFFF, 0x19, 0x3C) };
    Run_Pattern(wk, script, 6);
}

void Passive02_0082(PLW* wk) {
    const Pattern_Step script[6] = { [0] = STEP(Approach_Walk, 0x10, 2),
                                     [1] = STEP(EM_Term, -1, -0x7FF0, 6, 1, -1),
                                     [2] = STEP(Normal_Attack, 9, 0x202),
                                     [3] = STEP(Command_Attack, 0xC, 0x1D, 10, -1),
                                     [4] = STEP(Wait, 5),
                                     [5] = STEP(SA_Term, 0x35, 0x36, 0x37, 0) };
    Run_Pattern(wk, script, 6);
}

void Passive02_0083(PLW* wk) {
    pattern_etc_term_provoke(wk, 4, 0x2A);
}

void Passive02_0084(PLW* wk) {
    active_pattern_jump_attack_term(wk, &(Jump_Term_Args){-1, -0x7FC0, 9, 0x100, 1, -0x7FB0, -1, 0x20});
}

void Passive02_0085(PLW* wk) {
    pattern_normal_attack_command_attack_5(wk, &(Command_Attack_Args){8, 0x1D, 8, -1});
}

void Passive02_0086(PLW* wk) {
    pattern_keep_away_wait_get_up(wk, 0xBF, 3, -1);
}

void Passive02_0087(PLW* wk) {
    active_pattern_jump_command_attack_term(wk, &(JCA_Term_Args){8, 0x2E, 8, 0x700, -0x7FA0, 0x48, 0, 0x700, 0x30, 0x20});
}

void Passive02_0088(PLW* wk) {
    pattern_jump_attack_term_normal_attack_command_attack_4(
        wk,
        &(Jump_Term_Args){-0x7FA8, -0x7FC0, 9, 0x200, 0, -0x7FB0, -1, 0x200},
        &(Command_Attack_Args){8, 0x1D, 10, -1},
        2
    );
}

void Passive02_0089(PLW* wk) {
    pattern_pierce_on_command_attack_branch_unit_area(
        wk,
        &(Command_Attack_Args){8, 0, -1, -1},
        &(Branch_Menu_Args){6, 0x20, 0x3B, 0x36, 0x5A}
    );
}

void Passive02_0090(PLW* wk) {
    active_pattern_command_attack(wk, &(Command_Attack_Args){8, 0x1D, 0xA, -1});
}

void Passive02_0091(PLW* wk) {
    pattern_em_term_command_attack_wait(
        wk,
        &(Command_Attack_Args){0xC, 0x1D, 0xA, -1},
        &(SA_Term_Args){0x35, 0xFFFF, 0x37, 0}
    );
}

void Passive02_0092(PLW* wk) {
    pattern_em_term_com_random_select(
        wk,
        &(EM_Term_Params){-1, -0x7FF0, 0, 1, -1},
        &(Branch_Menu_Args){6, 0x60, 0x61, 0x62, 99}
    );
}

void Passive02_0093(PLW* wk) {
    pattern_jump_attack_term_normal_attack_command_attack_7(
        wk,
        &(Jump_Term_Args){-0x7FA0, -0x7FC0, 9, 0x40, 0, -0x7FB0, -1, 0x400},
        &(Command_Attack_Args){0xC, 0x1D, 0xA, -1}
    );
}

void Passive02_0094(PLW* wk) {
    active_pattern_sa_term(wk, &(SA_Term_Args){0xFFFF, 0xFFFF, 3, 0x3C});
}

void Passive02_0095(PLW* wk) {
    active_pattern_sa_term(wk, &(SA_Term_Args){0xFFFF, 0xFFFF, 0xD, 0x3B});
}

void Passive02_0096(PLW* wk) {
    active_pattern_sa_term(wk, &(SA_Term_Args){0xFFFF, 0xFFFF, 0xF, 0x3C});
}

void Passive02_0097(PLW* wk) {
    active_pattern_sa_term(wk, &(SA_Term_Args){0xFFFF, 0xFFFF, 0xF, 0});
}

void Passive02_0098(PLW* wk) {
    active_pattern_sa_term(wk, &(SA_Term_Args){0xFFFF, 0xFFFF, 3, 0x3C});
}

void Passive02_0099(PLW* wk) {
    active_pattern_sa_term(wk, &(SA_Term_Args){0xFFFF, 0xFFFF, 0x11, 0x3C});
}

void Passive02_0100(PLW* wk) {
    pattern_em_term_normal_attack(wk, &(EM_Term_Params){-1, -0x7FA0, 0, 2, 0}, 0x400);
}

void Passive02_0101(PLW* wk) {
    active_pattern_em_term_j_command_attack(
        wk,
        &(EM_Term_Params){-1, 0x30, 0, 1, -1},
        &(Command_Attack_Args){8, 0x1C, 0xA, -1}
    );
}

void Passive02_0102(PLW* wk) {
    pattern_em_term_jump_attack_term(
        wk,
        &(EM_Term_Params){-1, 0x30, 0, 1, -1},
        &(Jump_Term_Args){-0x7FA0, -0x7FD0, 8, 0x200, 0, -0x7F70, -1, 0x20}
    );
}

void Passive02_0103(PLW* wk) {
    active_pattern_em_term_j_command_attack(
        wk,
        &(EM_Term_Params){-0x7F88, -0x7FC0, 0, 1, -1},
        &(Command_Attack_Args){8, 0x1C, 8, -1}
    );
}

void Passive02_0104(PLW* wk) {
    active_pattern_em_term_j_command_attack(
        wk,
        &(EM_Term_Params){-0x7F88, -0x7FC0, 0, 1, -1},
        &(Command_Attack_Args){8, 0x1C, 8, -1}
    );
}

void Passive02_0105(PLW* wk) {
    pattern_em_term_sa_term_j_command_attack(
        wk,
        &(EM_Term_Params){-0x7F88, -0x7FC0, 0, 1, -1},
        &(SA_Term_Args){0xFFFF, 0x36, 0xFFFF, 0x47},
        &(Command_Attack_Args){8, 0x1C, 0xA, -1}
    );
}

void Passive02_0106(PLW* wk) {
    pattern_search_back_term_pierce_on_command_attack_2(wk, 0x60, 9, &(Branch_Menu_Args){6, 0xB, 2, 0xC, 0x5A});
}

void Passive02_0107(PLW* wk) {
    active_pattern_com_random_select(wk, &(Branch_Menu_Args){6, 7, 0x67, 8, 0x68}, 1);
}

void Passive02_0108(PLW* wk) {
    active_pattern_com_random_select(wk, &(Branch_Menu_Args){6, 9, 0x69, 9, 0x69}, 1);
}

void Passive02_0109(PLW* wk) {
    pattern_pierce_on_command_attack_j_command_attack(
        wk,
        &(Command_Attack_Args){0xC, 0, -1, -1},
        &(Command_Attack_Args){8, 0x1C, 0xA, -1}
    );
}

void Passive02_0110(PLW* wk) {
    passive02_pattern_check_boss_next_another_menu(wk, 0x6A);
}

void Passive02_0111(PLW* wk) {
    pattern_em_term_normal_attack(wk, &(EM_Term_Params){-0x7F88, -0x7FD0, 0, 2, 0}, 0x400);
}

void Passive02_0112(PLW* wk) {
    active_pattern_em_term_command_attack(
        wk,
        &(EM_Term_Params){-1, -0x7FF0, 0, 6, 0x1F},
        &(Command_Attack_Args){8, 0x1F, 8, -1}
    );
}

void Passive02_0113(PLW* wk) {
    const Pattern_Step script[2] = { [0] = STEP(Check_BOSS_EX, 6, 0x72),
                                     [1] = STEP(
                                         Com_Random_Select, &(Branch_Menu_Args) { 6, 0x4C, 0x37, 0x37, 0x30 }, 1) };
    Run_Pattern(wk, script, 2);
}

void Passive02_0114(PLW* wk) {
    const Pattern_Step script[6] = { [0] = STEP(EM_Term, -0x7FD0, -0x7FF0, 5, 6, 1),
                                     [1] = STEP(Normal_Attack, 9, 0x20),
                                     [2] = STEP(Wait, 5),
                                     [3] = STEP(SA_Term, 0x35, 0x36, 0xFFFF, 0),
                                     [4] = STEP(SA_Term, 0xFFFF, 0xFFFF, 0x19, 0x3C),
                                     [5] = STEP(Command_Attack, 0xC, 0x1C, 10, -1) };
    Run_Pattern(wk, script, 6);
}

void Passive02_0115(PLW* wk) {
    pattern_jump(wk, 0);
}

void Passive02_0116(PLW* wk) {
    pattern_jump_attack_term_normal_attack(
        wk,
        &(Jump_Term_Args){-0x7F90, -0x7FC0, 9, 0x400, 0, -0x7FB0, -1, 0x200},
        8,
        0x402
    );
}
