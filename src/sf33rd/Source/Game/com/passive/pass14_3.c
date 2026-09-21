/**
 * @file pass14_3.c
 * COM Passive: Akuma/Gouki
 * Pattern scripts from Passive14_0086 on.
 */

#include "sf33rd/Source/Game/com/passive/pass14.h"
#include "sf33rd/Source/Game/com/passive/pass14_internal.h"
#include "sf33rd/Source/Game/com/patterns/com_pattern_run.h"
#include "sf33rd/Source/Game/com/patterns/com_patterns.h"
#include "common.h"
#include "sf33rd/Source/Game/com/com_sub.h"
#include "sf33rd/Source/Game/engine/workuser.h"

static void passive14_pattern_normal_attack(PLW* wk, u16 lever_data, u16 lever_data_b) {
    const Pattern_Step script[2] = { [0] = STEP(Normal_Attack, 9, lever_data),
                                     [1] = STEP(Normal_Attack, 8, lever_data_b) };
    Run_Pattern(wk, script, 2);
}

void Passive14_0086(PLW* wk) {
    passive14_pattern_normal_attack(wk, 0x202, 0x202);
}

static void passive14_pattern_normal_attack_j_command_attack(PLW* wk, u16 lever_data, const Command_Attack_Args* p) {
    const Pattern_Step script[2] = { [0] = STEP(Normal_Attack, 0xB, lever_data), [1] = STEP_WITH(J_Command_Attack, p) };
    Run_Pattern(wk, script, 2);
}

void Passive14_0087(PLW* wk) {
    passive14_pattern_normal_attack_j_command_attack(wk, 0x102, &(Command_Attack_Args){8, 0x20, 10, -1});
}

void Passive14_0088(PLW* wk) {
    passive14_pattern_normal_attack_j_command_attack(wk, 0x102, &(Command_Attack_Args){8, 0x1E, 8, -1});
}

void Passive14_0089(PLW* wk) {
    active_pattern_normal_attack_command_attack(wk, 0xB, 0x102, &(Command_Attack_Args){8, 0x1F, 10, -1});
}

void Passive14_0090(PLW* wk) {
    passive14_pattern_normal_attack_j_command_attack(wk, 0x202, &(Command_Attack_Args){8, 0x20, 10, -1});
}

void Passive14_0091(PLW* wk) {
    pattern_normal_attack_sa_term_j_command_attack(
        wk,
        0x202,
        &(SA_Term_Args){0x2F, 0x30, 0x31, 0x7F},
        &(Command_Attack_Args){8, 0x1E, 8, -1}
    );
}

void Passive14_0092(PLW* wk) {
    pattern_normal_attack_sa_term_j_command_attack(
        wk,
        0x202,
        &(SA_Term_Args){0x2F, 0x30, 0x31, 0x7F},
        &(Command_Attack_Args){8, 0x1E, 10, -1}
    );
}

void Passive14_0093(PLW* wk) {
    pattern_normal_attack_sa_term_command_attack(
        wk,
        &(SA_Term_Args){0x2F, 0x30, 0x31, 0x7F},
        &(Command_Attack_Args){8, 0x1F, 10, -1}
    );
}

void Passive14_0094(PLW* wk) {
    pattern_normal_attack_command_attack_6(wk, 9, 0x220, &(Command_Attack_Args){8, 0x1F, 8, -1});
}

void Passive14_0095(PLW* wk) {
    pattern_normal_attack_command_attack_wait_2(wk, 0x220, 0xC);
}

void Passive14_0096(PLW* wk) {
    const Pattern_Step script[5] = { [0] = STEP(Normal_Attack, 9, 0x220),
                                     [1] = STEP(Normal_Attack, 0xC, 0x202),
                                     [2] = STEP(J_Command_Attack, 0xC, 0x1E, 10, -1),
                                     [3] = STEP(Wait, 3),
                                     [4] = STEP(SA_Term, 0x2F, 0x30, 0x31, 0x7F) };
    Run_Pattern(wk, script, 5);
}

void Passive14_0097(PLW* wk) {
    pattern_keep_away_com_random_select_2(wk, 0xBF, 1, &(Branch_Menu_Args){6, 0x15, 0x1D, 0x1E, 0x1F});
}

void Passive14_0098(PLW* wk) {
    passive14_pattern_normal_attack(wk, 0x200, 0x202);
}

void Passive14_0099(PLW* wk) {
    passive14_pattern_normal_attack(wk, 0x200, 0x200);
}

void Passive14_0100(PLW* wk) {
    passive14_pattern_normal_attack(wk, 0x102, 0x202);
}

void Passive14_0101(PLW* wk) {
    pattern_normal_attack_4(wk, 9, 10, 0x202);
}

void Passive14_0102(PLW* wk) {
    pattern_normal_attack_command_attack_4(wk, 9, 10, &(Command_Attack_Args){8, 0x1F, 10, -1});
}

void Passive14_0103(PLW* wk) {
    pattern_normal_attack_command_attack_3(wk, 9, 10, &(Command_Attack_Args){8, 0x1F, 10, -1});
}

void Passive14_0104(PLW* wk) {
    pattern_normal_attack_command_attack_wait_2(wk, 0x102, 10);
}

void Passive14_0105(PLW* wk) {
    active_pattern_command_attack_2(
        wk,
        &(Command_Attack_Args){8, 1, -1, -1},
        &(Command_Attack_Args){8, 0x1F, 10, -1}
    );
}

void Passive14_0106(PLW* wk) {
    active_pattern_command_attack_2(
        wk,
        &(Command_Attack_Args){8, 1, -1, -1},
        &(Command_Attack_Args){8, 0x21, 8, -1}
    );
}

void Passive14_0107(PLW* wk) {
    active_pattern_wait(wk, 0);
}

void Passive14_0108(PLW* wk) {
    pattern_approach_walk_normal_attack_2(wk, 8, 0x20);
}

void Passive14_0109(PLW* wk) {
    pattern_approach_walk_normal_attack_2(wk, 8, 0x40);
}

void Passive14_0110(PLW* wk) {
    pattern_approach_walk_normal_attack_2(wk, 8, 0x400);
}

void Passive14_0111(PLW* wk) {
    pattern_approach_walk_normal_attack_2(wk, 8, 0x402);
}

void Passive14_0112(PLW* wk) {
    pattern_approach_walk_normal_attack_j_command_attack_3(
        wk,
        0x47,
        &(Normal_Attack_Step){ 0xC, 0x20 },
        &(Command_Attack_Args){8, 0x1E, 10, -1}
    );
}

void Passive14_0113(PLW* wk) {
    active_pattern_jump_command_attack_term(wk, &(JCA_Term_Args){8, 0x2E, 8, -1, -1, 0x20, 2, -0x7F80, -1, 0x400});
}

void Passive14_0114(PLW* wk) {
    active_pattern_jump_command_attack_term(wk, &(JCA_Term_Args){8, 0x2E, 9, -1, -1, 0x20, 2, -0x7F80, -1, 0x400});
}

void Passive14_0115(PLW* wk) {
    active_pattern_jump_command_attack_term(wk, &(JCA_Term_Args){8, 0x2E, 0xA, -1, -1, 0x20, 2, -0x7F80, -1, 0x400});
}

void Passive14_0116(PLW* wk) {
    active_pattern_jump_command_attack_term(wk, &(JCA_Term_Args){8, 0x2E, 8, -1, -1, 0x20, 0, -0x7F80, -1, 0x400});
}

void Passive14_0117(PLW* wk) {
    active_pattern_jump_command_attack_term(wk, &(JCA_Term_Args){8, 0x2E, 9, -1, -1, 0x20, 0, -0x7F80, -1, 0x400});
}

void Passive14_0118(PLW* wk) {
    active_pattern_jump_command_attack_term(wk, &(JCA_Term_Args){8, 0x2E, 0xA, -1, -1, 0x20, 0, -0x7F80, -1, 0x400});
}

void Passive14_0119(PLW* wk) {
    active_pattern_jump_command_attack_term(wk, &(JCA_Term_Args){8, 0x2E, 8, -1, -1, 0x20, 1, -0x7F80, -1, 0x400});
}

void Passive14_0120(PLW* wk) {
    active_pattern_jump_command_attack_term(wk, &(JCA_Term_Args){8, 0x2E, 9, -1, -1, 0x20, 1, -0x7F80, -1, 0x400});
}

void Passive14_0121(PLW* wk) {
    active_pattern_jump_command_attack_term(wk, &(JCA_Term_Args){8, 0x2E, 0xA, -1, -1, 0x20, 1, -0x7F80, -1, 0x400});
}

void Passive14_0122(PLW* wk) {
    active_pattern_com_random_select(wk, &(Branch_Menu_Args){6, 0x71, 0x71, 0x72, 0x73}, 2);
}

void Passive14_0123(PLW* wk) {
    active_pattern_com_random_select(wk, &(Branch_Menu_Args){6, 0x74, 0x74, 0x75, 0x76}, 2);
}

void Passive14_0124(PLW* wk) {
    active_pattern_com_random_select(wk, &(Branch_Menu_Args){6, 0x77, 0x77, 0x78, 0x79}, 2);
}

void passive14_pattern_em_term_com_random_select(PLW* wk, const Branch_Menu_Args* p, s16 rnd_type) {
    const Pattern_Step script[2] = { [0] = STEP(EM_Term, -1, -0x7FF8, 6, 6, 1),
                                     [1] = STEP(Com_Random_Select, p, rnd_type) };
    Run_Pattern(wk, script, 2);
}

void Passive14_0125(PLW* wk) {
    passive14_pattern_em_term_com_random_select(wk, &(Branch_Menu_Args){6, 0x57, 0x57, 0x58, 0x59}, 2);
}

void Passive14_0126(PLW* wk) {
    passive14_pattern_em_term_com_random_select(wk, &(Branch_Menu_Args){6, 0x5A, 0x5B, 0x5C, 0x5D}, 2);
}

void Passive14_0127(PLW* wk) {
    pattern_approach_walk_com_random_select(wk, 0x47, &(Branch_Menu_Args){6, 0x57, 0x57, 0x58, 0x59}, 2);
}

void Passive14_0128(PLW* wk) {
    pattern_approach_walk_com_random_select(wk, 0x47, &(Branch_Menu_Args){6, 0x5A, 0x5B, 0x5C, 0x5D}, 2);
}

void Passive14_0129(PLW* wk) {
    pattern_approach_walk_lever_attack(wk, 0x10, 0, 0x110);
}

void Passive14_0130(PLW* wk) {
    pattern_approach_walk_lever_attack(wk, 0x10, 1, 0x110);
}

void Passive14_0131(PLW* wk) {
    active_pattern_com_random_select(wk, &(Branch_Menu_Args){6, 0x81, 0x81, 0x82, 0x82}, 0);
}

void Passive14_0132(PLW* wk) {
    active_pattern_command_attack(wk, &(Command_Attack_Args){8, 0x1F, 8, -1});
}

void Passive14_0133(PLW* wk) {
    active_pattern_command_attack(wk, &(Command_Attack_Args){8, 0x1F, 9, -1});
}

void Passive14_0134(PLW* wk) {
    active_pattern_command_attack(wk, &(Command_Attack_Args){8, 0x1F, 10, -1});
}

void Passive14_0135(PLW* wk) {
    active_pattern_command_attack(wk, &(Command_Attack_Args){8, 0x21, 8, -1});
}

void Passive14_0136(PLW* wk) {
    active_pattern_command_attack(wk, &(Command_Attack_Args){8, 0x21, 9, -1});
}

void Passive14_0137(PLW* wk) {
    active_pattern_command_attack(wk, &(Command_Attack_Args){8, 0x21, 10, -1});
}

void Passive14_0138(PLW* wk) {
    active_pattern_com_random_select(wk, &(Branch_Menu_Args){6, 0x84, 0x84, 0x85, 0x86}, 2);
}

void Passive14_0139(PLW* wk) {
    active_pattern_com_random_select(wk, &(Branch_Menu_Args){6, 0x87, 0x87, 0x88, 0x89}, 2);
}

static void passive14_pattern_j_command_attack(PLW* wk, const Command_Attack_Args* p) {
    const Pattern_Step script[2] = { [0] = STEP_WITH(J_Command_Attack, p),
                                     [1] = STEP(J_Command_Attack, 8, 0x1E, 8, -1) };
    Run_Pattern(wk, script, 2);
}

void Passive14_0140(PLW* wk) {
    passive14_pattern_j_command_attack(wk, &(Command_Attack_Args){9, 0x20, 8, -1});
}

void Passive14_0141(PLW* wk) {
    passive14_pattern_j_command_attack(wk, &(Command_Attack_Args){9, 0x20, 9, -1});
}

void Passive14_0142(PLW* wk) {
    passive14_pattern_j_command_attack(wk, &(Command_Attack_Args){9, 0x20, 10, -1});
}

void Passive14_0143(PLW* wk) {
    passive14_pattern_em_term_com_random_select(wk, &(Branch_Menu_Args){6, 0x8C, 0x8C, 0x8D, 0x8E}, 2);
}

void Passive14_0144(PLW* wk) {
    active_pattern_j_command_attack(wk, &(Command_Attack_Args){8, 0x1E, 8, -1});
}

void Passive14_0145(PLW* wk) {
    const Pattern_Step script[2] = { [0] = STEP(J_Command_Attack, 8, 0x1E, 8, -1),
                                     [1] = STEP(
                                         Com_Random_Select, &(Branch_Menu_Args) { 6, 0x90, 0xFF, 0xFF, 0xFF }, 0) };
    Run_Pattern(wk, script, 2);
}

void Passive14_0146(PLW* wk) {
    const Pattern_Step script[2] = { [0] =
                                         STEP(Jump_Command_Attack_Term, 0xC, 0x2E, 8, -1, -1, 0x34, 0, -1, -1, 0xFFFF),
                                     [1] = STEP(SA_Term, 0x2F, 0xFFFF, 0xFFFF, 0xBF) };
    Run_Pattern(wk, script, 2);
}

static void passive14_0147_from_step_6(PLW* wk) {
    const Pattern_Step script[10] = {
        [6] = STEP(Wait, 1), [7] = STEP(Only_Shot, 0x100), [8] = STEP(Wait, 1), [9] = STEP(Only_Shot, 0x40)
    };
    Run_Pattern(wk, script, 10);
}

void Passive14_0147(PLW* wk) {
    const Pattern_Step script[6] = {
        [0] = STEP(Check_SA_Full, 6, 0x76), [1] = STEP(Only_Shot, 0x10), [2] = STEP(Wait, 1),
        [3] = STEP(Only_Shot, 0x10),        [4] = STEP(Wait, 1),         [5] = STEP(Lever_On, 0, 0)
    };
    if (!Run_Pattern_Steps(wk, script, 6)) {
        passive14_0147_from_step_6(wk);
    }
}

void Passive14_0148(PLW* wk) {
    const Pattern_Step script[2] = { [0] = STEP(Check_SA, 6, 0x76),
                                     [1] = STEP(
                                         Jump_Command_Attack_Term, 8, 0x8014, 10, -1, -1, 0x20, 0, -1, -1, 0xFFFF) };
    Run_Pattern(wk, script, 2);
}

void Passive14_0149(PLW* wk) {
    active_pattern_com_random_select(wk, &(Branch_Menu_Args){6, 0x92, 0x92, 0x93, 0x94}, 2);
}

void Passive14_0150(PLW* wk) {
    const Pattern_Step script[2] = { [0] = STEP(Normal_Attack, 9, 0x220),
                                     [1] = STEP(
                                         Com_Random_Select, &(Branch_Menu_Args) { 6, 0x81, 0x82, 0x81, 0x82 }, 0) };
    Run_Pattern(wk, script, 2);
}

void passive14_pattern_jump_attack_term_normal_attack_command_attack(PLW* wk, const Jump_Term_Args* a,
                                                                     const Command_Attack_Args* p,
                                                                     const SA_Term_Args* p_b) {
    const Pattern_Step script[5] = { [0] = STEP_WITH(Jump_Attack_Term, a),
                                     [1] = STEP(Normal_Attack, 0xC, 0x202),
                                     [2] = STEP_WITH(Command_Attack, p),
                                     [3] = STEP(Wait, 1),
                                     [4] = STEP_WITH(SA_Term, p_b) };
    Run_Pattern(wk, script, 5);
}

void Passive14_0151(PLW* wk) {
    passive14_pattern_jump_attack_term_normal_attack_command_attack(
        wk,
        &(Jump_Term_Args){8, 0x49, 0xB, 0x202, 0, -0x7F80, -1, 0x400},
        &(Command_Attack_Args){0xB, 0x1F, 10, -1},
        &(SA_Term_Args){0x2F, 0x34, 0x34, 0x7F}
    );
}

void Passive14_0152(PLW* wk) {
    const Pattern_Step script[6] = { [0] = STEP_NOARG(Turn_Over_On),
                                     [1] = STEP(Hi_Jump_Attack_Term, -1, 0x61, 0xB, 0x202, 0, -0x7F80, -1, 0x400),
                                     [2] = STEP(Normal_Attack, 0xC, 0x202),
                                     [3] = STEP(Command_Attack, 0xB, 0x1F, 10, -1),
                                     [4] = STEP(Wait, 1),
                                     [5] = STEP(SA_Term, 0x2F, 0x34, 0x34, 0x7F) };
    Run_Pattern(wk, script, 6);
}

void Passive14_0153(PLW* wk) {
    pattern_lever_attack(wk, 0, 0x20);
}

void Passive14_0154(PLW* wk) {
    active_pattern_em_term_normal_attack(wk, &(EM_Term_Params){-1, -0x7FF8, 6, 6, 1}, 0xD, 0x20);
}

void Passive14_0155(PLW* wk) {
    pattern_approach_walk_jump_attack_term_normal_attack_2(wk, 3, &(Command_Attack_Args){8, 0x1F, 10, -1});
}

void Passive14_0156(PLW* wk) {
    const Pattern_Step script[6] = { [0] = STEP(Approach_Walk, 0xBF, 3),
                                     [1] = STEP(Jump_Attack_Term, -0x7FA8, -0x7FC8, 0xB, 0x400, 0, -0x7F80, -1, 0x400),
                                     [2] = STEP(Normal_Attack, 0xC, 0x202),
                                     [3] = STEP(Command_Attack, 0xB, 0x1F, 10, -1),
                                     [4] = STEP(Wait, 1),
                                     [5] = STEP(SA_Term, 0x2F, 0x34, 0x34, 0x7F) };
    Run_Pattern(wk, script, 6);
}
