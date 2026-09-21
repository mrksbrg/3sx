/**
 * @file pass04_2.c
 * COM Passive: Dudley
 * Pattern scripts from Passive04_0062 on.
 */

#include "sf33rd/Source/Game/com/passive/pass04.h"
#include "sf33rd/Source/Game/com/passive/pass04_internal.h"
#include "sf33rd/Source/Game/com/patterns/com_pattern_run.h"
#include "sf33rd/Source/Game/com/patterns/com_patterns.h"
#include "common.h"
#include "sf33rd/Source/Game/com/com_sub.h"
#include "sf33rd/Source/Game/engine/workuser.h"

void Passive04_0062(PLW* wk) {
    active_pattern_normal_attack_command_attack(wk, 0xB, 0x20, &(Command_Attack_Args){0xD, 0x20, 0x60A, -1});
}

void Passive04_0063(PLW* wk) {
    const Pattern_Step script[3] = { [0] = STEP(SA_Term, 0xFFFF, 0x36, 0x37, 0),
                                     [1] = STEP(Approach_Walk, 0x9F, 2),
                                     [2] = STEP(SA_Term, 0x35, 0xFFFF, 0xFFFF, 0) };
    Run_Pattern(wk, script, 3);
}

void Passive04_0064(PLW* wk) {
    pattern_approach_walk_normal_attack_j_command_attack(wk, 0x47, 0x20, &(Command_Attack_Args){8, 0x1C, 9, -1});
}

void Passive04_0065(PLW* wk) {
    pattern_approach_walk_normal_attack_2(wk, 0xD, 0x200);
}

void Passive04_0066(PLW* wk) {
    pattern_approach_walk_sa_term(wk, 0x47, &(SA_Term_Args){0x35, 0x36, 0x37, 0});
}

void Passive04_0067(PLW* wk) {
    pattern_wait_attack_complete(wk, 0);
}

void Passive04_0068(PLW* wk) {
    passive04_pattern_approach_walk_wait_get_up_command_attack(wk, 0xDF, &(Command_Attack_Args){8, 0x1F, 9, -1});
}

void Passive04_0069(PLW* wk) {
    pattern_wait_attack_complete_sa_term_wait_attack_complete(wk, &(SA_Term_Args){0x35, 0xFFFF, 0x37, 0});
}

void Passive04_0070(PLW* wk) {
    const Pattern_Step script[4] = { [0] = STEP(Approach_Walk, 0x9F, 2),
                                     [1] = STEP(Wait_Get_Up, 0, -1),
                                     [2] = STEP(SA_Term, 0x35, 0x36, 0x37, 0),
                                     [3] = STEP(Normal_Attack, 8, 0x202) };
    Run_Pattern(wk, script, 4);
}

void Passive04_0071(PLW* wk) {
    pattern_em_term_sa_term_command_attack(
        wk,
        &(EM_Term_Params){-0x7FB0, -0x7FF0, 0, 1, -1},
        &(SA_Term_Args){0xFFFF, 0x36, 0xFFFF, 0},
        &(Command_Attack_Args){8, 0x1F, 10, -1}
    );
}

void Passive04_0072(PLW* wk) {
    pattern_sa_term_forced_guard(wk, &(SA_Term_Args){0x35, 0xFFFF, 0x37, 0});
}

void Passive04_0073(PLW* wk) {
    pattern_sa_term_normal_attack(wk, &(SA_Term_Args){0x35, 0xFFFF, 0x37, 0}, 0xD, 0x20);
}

void Passive04_0074(PLW* wk) {
    pattern_sa_term_command_attack_2(
        wk,
        &(SA_Term_Args){0xFFFF, 0x36, 0x37, 0},
        &(SA_Term_Args){0x35, 0xFFFF, 0xFFFF, 0x9F},
        &(Command_Attack_Args){0xD, 0x20, 0x30A, -1}
    );
}

void Passive04_0075(PLW* wk) {
    const Pattern_Step script[3] = { [0] = STEP(EM_Term, -0x7FC0, -1, 5, 6, 0x1F),
                                     [1] = STEP(Normal_Attack, 9, 0x22),
                                     [2] = STEP(Command_Attack, 8, 0x1F, 8, -1) };
    Run_Pattern(wk, script, 3);
}

void Passive04_0076(PLW* wk) {
    active_pattern_em_term_lever_attack(wk, &(EM_Term_Params){-0x7FB0, -1, 5, 6, 0x1C}, 0, 0x400);
}

void Passive04_0077(PLW* wk) {
    pattern_wait_attack_complete_normal_attack(wk);
}

void Passive04_0078(PLW* wk) {
    pattern_approach_walk_normal_attack_2(wk, 8, 0x402);
}

void Passive04_0079(PLW* wk) {
    pattern_wait_get_up_command_attack_2(wk, &(Command_Attack_Args){8, 0x1F, 10, -1});
}

void Passive04_0080(PLW* wk) {
    pattern_wait_get_up_command_attack_2(wk, &(Command_Attack_Args){0xD, 0x20, 0x30A, -1});
}

void Passive04_0081(PLW* wk) {
    pattern_wait_get_up_command_attack_2(wk, &(Command_Attack_Args){8, 0x20, 10, -1});
}

void Passive04_0082(PLW* wk) {
    const Pattern_Step script[2] = { [0] = STEP(SA_Term, 0x35, 0xFFFF, 0x37, 0),
                                     [1] = STEP(Lever_Attack, 0xD, 0, 0x200) };
    Run_Pattern(wk, script, 2);
}

void Passive04_0083(PLW* wk) {
    active_pattern_em_term_command_attack(
        wk,
        &(EM_Term_Params){-0x7F90, 0, 0, 2, 0},
        &(Command_Attack_Args){0xD, 0x20, 0x609, -1}
    );
}

void Passive04_0084(PLW* wk) {
    active_pattern_em_term_command_attack(
        wk,
        &(EM_Term_Params){-0x7FB0, 0, 0, 2, 0},
        &(Command_Attack_Args){0xD, 0x20, 0x608, -1}
    );
}

void Passive04_0085(PLW* wk) {
    active_pattern_em_term_command_attack(
        wk,
        &(EM_Term_Params){-0x7F90, 0, 0, 2, 0},
        &(Command_Attack_Args){0xD, 0x20, 0x309, -1}
    );
}

void Passive04_0086(PLW* wk) {
    active_pattern_em_term_command_attack(
        wk,
        &(EM_Term_Params){-0x7FB0, 0, 0, 2, 0},
        &(Command_Attack_Args){0xD, 0x20, 0x308, -1}
    );
}

void Passive04_0087(PLW* wk) {
    pattern_sa_term_forced_guard(wk, &(SA_Term_Args){0xFFFF, 0xFFFF, 0x37, 0});
}

void Passive04_0088(PLW* wk) {
    active_pattern_normal_attack(wk, 8, 0x42);
}

void Passive04_0089(PLW* wk) {
    pattern_wait_attack_complete_sa_term_wait_attack_complete(wk, &(SA_Term_Args){0xFFFF, 0x36, 0x37, 0});
}

void Passive04_0090(PLW* wk) {
    active_pattern_command_attack(wk, &(Command_Attack_Args){0xD, 0x20, 0x608, -1});
}

void Passive04_0091(PLW* wk) {
    active_pattern_command_attack(wk, &(Command_Attack_Args){0xD, 0x20, 0x609, -1});
}

void Passive04_0092(PLW* wk) {
    active_pattern_command_attack(wk, &(Command_Attack_Args){0xD, 0x20, 0x60A, -1});
}

void Passive04_0093(PLW* wk) {
    active_pattern_j_command_attack(wk, &(Command_Attack_Args){8, 0x1C, 8, -1});
}

void Passive04_0094(PLW* wk) {
    const Pattern_Step script[4] = { [0] = STEP(EM_Term, -0x7FC0, -0x7FF0, 6, 1, -1),
                                     [1] = STEP(Normal_Attack, 8, 0x12),
                                     [2] = STEP(Normal_Attack, 8, 0x12),
                                     [3] = STEP(Normal_Attack, 8, 0x12) };
    Run_Pattern(wk, script, 4);
}

void Passive04_0095(PLW* wk) {
    active_pattern_em_term_normal_attack(wk, &(EM_Term_Params){-0x7FB0, -0x7FC0, 0, 1, -1}, 0xB, 0x200);
}

void Passive04_0096(PLW* wk) {
    pattern_em_term_normal_attack_j_command_attack(
        wk,
        &(EM_Term_Params){-0x7FB0, -0x7FC0, 0, 1, -1},
        0x202,
        &(Command_Attack_Args){8, 0x1C, 9, -1}
    );
}

void Passive04_0097(PLW* wk) {
    pattern_approach_walk_normal_attack_2(wk, 0xB, 0x202);
}

void Passive04_0098(PLW* wk) {
    const Pattern_Step script[3] = { [0] = STEP(Check_EX, 6, 8),
                                     [1] = STEP(EM_Term, -0x7FA0, -1, 0, 1, -1),
                                     [2] = STEP(J_Command_Attack, 8, 0x1C, 9, 0x70) };
    Run_Pattern(wk, script, 3);
}

void Passive04_0099(PLW* wk) {
    active_pattern_em_term_j_command_attack(
        wk,
        &(EM_Term_Params){-1, -0x7FD8, 0, 1, -1},
        &(Command_Attack_Args){8, 0x1C, 10, 0x70}
    );
}

void Passive04_0100(PLW* wk) {
    pattern_provoke(wk, -1);
}

void Passive04_0101(PLW* wk) {
    active_pattern_approach_walk_command_attack(wk, 0x7F, &(Command_Attack_Args){8, 0x21, 8, -1});
}

void Passive04_0102(PLW* wk) {
    pattern_em_term_search_back_term_command_attack(wk, &(Command_Attack_Args){8, 0x21, 10, -1});
}

void Passive04_0103(PLW* wk) {
    pattern_em_term_search_back_term_command_attack(wk, &(Command_Attack_Args){8, 0x21, 9, 0x700});
}

void Passive04_0104(PLW* wk) {
    active_pattern_approach_walk_command_attack(wk, 0x7F, &(Command_Attack_Args){8, 0x21, 10, 0x700});
}

void Passive04_0105(PLW* wk) {
    pattern_wait_get_up_command_attack_2(wk, &(Command_Attack_Args){8, 0x21, 10, -1});
}

void Passive04_0106(PLW* wk) {
    passive04_pattern_approach_walk_wait_get_up_command_attack(wk, 0x7F, &(Command_Attack_Args){8, 0x21, 10, -1});
}

void Passive04_0107(PLW* wk) {
    passive04_pattern_approach_walk_wait_get_up_command_attack(wk, 0x7F, &(Command_Attack_Args){8, 0x21, 10, 0x700});
}

void Passive04_0108(PLW* wk) {
    pattern_wait_em_term_normal_attack(wk, 2, &(EM_Term_Params){-0x7FA0, -1, 0, 1, -1}, 0x200);
}

void Passive04_0109(PLW* wk) {
    active_pattern_command_attack(wk, &(Command_Attack_Args){8, 0x20, 10, -1});
}

void Passive04_0110(PLW* wk) {
    pattern_wait_em_term_j_command_attack(wk, &(Command_Attack_Args){8, 0x1C, 8, -1});
}

void Passive04_0111(PLW* wk) {
    pattern_wait_em_term_j_command_attack(wk, &(Command_Attack_Args){8, 0x1C, 9, -1});
}

void Passive04_0112(PLW* wk) {
    const Pattern_Step script[4] = { [0] = STEP(Wait, 2),
                                     [1] = STEP(EM_Term, -0x7F98, -1, 0, 1, -1),
                                     [2] = STEP(SA_Term, 0x35, 0xFFFF, 0xFFFF, 0),
                                     [3] = STEP(J_Command_Attack, 8, 0x1C, 10, -1) };
    Run_Pattern(wk, script, 4);
}

void Passive04_0113(PLW* wk) {
    const Pattern_Step script[4] = { [0] = STEP(Wait, 2),
                                     [1] = STEP(Check_EX, 6, 0x6F),
                                     [2] = STEP(EM_Term, -0x7F98, -1, 0, 1, -1),
                                     [3] = STEP(J_Command_Attack, 8, 0x1C, 9, 0x70) };
    Run_Pattern(wk, script, 4);
}

void Passive04_0114(PLW* wk) {
    pattern_search_back_term_pierce_on_command_attack_4(wk, 0x33);
}

void Passive04_0115(PLW* wk) {
    active_pattern_keep_away(wk, 0xDF, 2);
}

void Passive04_0116(PLW* wk) {
    pattern_em_term_sa_term_command_attack(
        wk,
        &(EM_Term_Params){-0x7FB0, -0x7FF0, 5, 1, -1},
        &(SA_Term_Args){0xFFFF, 0x36, 0xFFFF, 0},
        &(Command_Attack_Args){8, 0x1F, 10, -1}
    );
}

void Passive04_0117(PLW* wk) {
    pattern_jump_look(wk);
}

void Passive04_0118(PLW* wk) {
    active_pattern_jump_attack_term(wk, &(Jump_Term_Args){-0x7FB0, -1, 8, 0x400, 1, -1, 0x20, 0x400});
}

void Passive04_0119(PLW* wk) {
    active_pattern_jump_attack_term_command_attack(
        wk,
        &(Jump_Term_Args){-0x7FB0, -0x7FB0, 8, 0x40, 2, -1, -0x7FB0, 0x40},
        &(Command_Attack_Args){8, 0x1C, 10, -1}
    );
}

void Passive04_0120(PLW* wk) {
    pattern_jump_attack_term_normal_attack_4(
        wk,
        &(Jump_Term_Args){-0x7FB0, -0x7FB0, 8, 0x40, 2, -1, -0x7FB0, 0x40},
        0x20,
        0x40
    );
}

void Passive04_0121(PLW* wk) {
    active_pattern_normal_attack_6(wk, 0x12, 0x12, 0x12);
}

void Passive04_0122(PLW* wk) {
    active_pattern_normal_attack(wk, 8, 0x202);
}

void Passive04_0123(PLW* wk) {
    active_pattern_command_attack(wk, &(Command_Attack_Args){0xD, 0x20, 0x609, -1});
}

void Passive04_0124(PLW* wk) {
    active_pattern_command_attack(wk, &(Command_Attack_Args){0xD, 0x20, 0x608, -1});
}

void Passive04_0125(PLW* wk) {
    active_pattern_command_attack(wk, &(Command_Attack_Args){0xD, 0x20, 0x309, -1});
}

void Passive04_0126(PLW* wk) {
    active_pattern_command_attack(wk, &(Command_Attack_Args){0xD, 0x20, 0x308, -1});
}

void Passive04_0127(PLW* wk) {
    active_pattern_em_term_normal_attack(wk, &(EM_Term_Params){-0x7F90, -1, 0, 1, -1}, 8, 0x20);
}

void Passive04_0128(PLW* wk) {
    active_pattern_em_term_normal_attack(wk, &(EM_Term_Params){-0x7F90, -1, 0, 1, -1}, 8, 0x22);
}

void Passive04_0129(PLW* wk) {
    active_pattern_em_term_j_command_attack(
        wk,
        &(EM_Term_Params){-0x7F90, -1, 0, 1, -1},
        &(Command_Attack_Args){8, 0x1C, 9, -1}
    );
}

void Passive04_0130(PLW* wk) {
    pattern_em_term_normal_attack_5(wk, &(EM_Term_Params){-0x7F80, -1, 0, 1, -1});
}

void Passive04_0131(PLW* wk) {
    pattern_em_term_normal_attack_6(wk, &(EM_Term_Params){-0x7F80, -1, 0, 1, -1});
}

void Passive04_0132(PLW* wk) {
    active_pattern_em_term_j_command_attack(
        wk,
        &(EM_Term_Params){-0x7F90, -1, 0, 1, -1},
        &(Command_Attack_Args){8, 0x1C, 9, 0x70}
    );
}
