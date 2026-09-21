/**
 * @file pass14_4.c
 * COM Passive: Akuma/Gouki
 * Pattern scripts from Passive14_0157 on.
 */

#include "common.h"
#include "sf33rd/Source/Game/com/com_sub.h"
#include "sf33rd/Source/Game/com/passive/pass14.h"
#include "sf33rd/Source/Game/com/passive/pass14_internal.h"
#include "sf33rd/Source/Game/com/patterns/com_pattern_run.h"
#include "sf33rd/Source/Game/com/patterns/com_patterns.h"
#include "sf33rd/Source/Game/engine/workuser.h"

void Passive14_0157(PLW* wk) {
    pattern_approach_walk_jump_attack_term_normal_attack_2(wk, 2, &(Command_Attack_Args) { 0xC, 0x1F, 10, -1 });
}

void Passive14_0158(PLW* wk) {
    const Pattern_Step script[6] = { [0] = STEP(Approach_Walk, 0xBF, 2),
                                     [1] = STEP(Jump_Attack_Term, -0x7FA8, -0x7FC8, 0xB, 0x400, 0, -0x7F80, -1, 0x400),
                                     [2] = STEP(Normal_Attack, 0xC, 0x202),
                                     [3] = STEP(Command_Attack, 0xB, 0x1F, 10, -1),
                                     [4] = STEP(Wait, 1),
                                     [5] = STEP(SA_Term, 0x2F, 0x34, 0x34, 0x7F) };
    Run_Pattern_Or(wk, script, 6, pattern_sa_term_from_step_6);
}

static void passive14_pattern_jump_attack_term_normal_attack_command_attack_2(PLW* wk, const Jump_Term_Args* a) {
    const Pattern_Step script[3] = { [0] = STEP_WITH(Jump_Attack_Term, a),
                                     [1] = STEP(Normal_Attack, 0xC, 0x202),
                                     [2] = STEP(Command_Attack, 0xC, 0x1F, 10, -1) };
    Run_Pattern(wk, script, 3);
}

void Passive14_0159(PLW* wk) {
    passive14_pattern_jump_attack_term_normal_attack_command_attack_2(
        wk, &(Jump_Term_Args) { -0x7FA8, -0x7FC8, 0xB, 0x400, 0, -0x7F80, -1, 0x400 }
    );
}

void Passive14_0160(PLW* wk) {
    passive14_pattern_jump_attack_term_normal_attack_command_attack(
        wk,
        &(Jump_Term_Args) { -0x7FA8, -0x7FC8, 0xB, 0x400, 0, -0x7F80, -1, 0x400 },
        &(Command_Attack_Args) { 0xC, 0x1F, 10, -1 },
        &(SA_Term_Args) { 0x2F, 0x30, 0x31, 0x7F }
    );
}

void Passive14_0161(PLW* wk) {
    passive14_pattern_jump_attack_term_normal_attack_command_attack_2(
        wk, &(Jump_Term_Args) { -0x7FA8, -0x7FC8, 0xB, 0x400, 0, -0x7F80, -1, 0x400 }
    );
}

void Passive14_0162(PLW* wk) {
    passive14_pattern_jump_attack_term_normal_attack_command_attack(
        wk,
        &(Jump_Term_Args) { -0x7FA8, -0x7FC8, 0xB, 0x400, 0, -0x7F80, -1, 0x400 },
        &(Command_Attack_Args) { 0xC, 0x1F, 10, -1 },
        &(SA_Term_Args) { 0x2F, 0x30, 0x31, 0x7F }
    );
}

void Passive14_0163(PLW* wk) {
    active_pattern_command_attack(wk, &(Command_Attack_Args) { 8, 1, -1, -1 });
}

void Passive14_0164(PLW* wk) {
    const Pattern_Step script[4] = { [0] = STEP(Command_Attack, 8, 1, -1, -1),
                                     [1] = STEP(Wait_Get_Up, 3, 0),
                                     [2] = STEP(SA_Term, 0x32, 0xFFFF, 0xFFFF, 0xBF),
                                     [3] = STEP(
                                         Com_Random_Select, &(Branch_Menu_Args) { 6, 0x71, 0x71, 0x72, 0x73 }, 2) };
    Run_Pattern(wk, script, 4);
}

void Passive14_0165(PLW* wk) {
    pattern_approach_walk_wait_get_up_sa_term_com_random_select(
        wk,
        0xBF,
        &(SA_Term_Args) { 0x32, 0xFFFF, 0xFFFF, 0xBF },
        &(Com_Random_Select_Step) { &(Branch_Menu_Args) { 6, 0x74, 0x74, 0x75, 0x76 }, 2 }
    );
}

static void passive14_pattern_command_attack_com_random_select(PLW* wk, const Branch_Menu_Args* p, s16 rnd_type) {
    const Pattern_Step script[2] = { [0] = STEP(Command_Attack, 8, 0, -1, -1),
                                     [1] = STEP(Com_Random_Select, p, rnd_type) };
    Run_Pattern(wk, script, 2);
}

void Passive14_0166(PLW* wk) {
    passive14_pattern_command_attack_com_random_select(wk, &(Branch_Menu_Args) { 6, 0x84, 0x84, 0x85, 0x86 }, 2);
}

void Passive14_0167(PLW* wk) {
    pattern_approach_walk_jump_attack_term_normal_attack_4(wk, &(Command_Attack_Args) { 0xC, 0x1F, 10, -1 });
}

static void passive14_0168_from_step_6(PLW* wk) {
    const Pattern_Step script[7] = { [6] = STEP(SA_Term, 0x2F, 0x34, 0x34, 0x7F) };
    Run_Pattern(wk, script, 7);
}

void Passive14_0168(PLW* wk) {
    const Pattern_Step script[6] = { [0] = STEP(Approach_Walk, 0xBF, 2),
                                     [1] = STEP(Jump_Attack_Term, -0x7FA8, -0x7FC8, 9, 0x400, 0, -0x7F80, -1, 0x400),
                                     [2] = STEP(Normal_Attack, 9, 0x220),
                                     [3] = STEP(Normal_Attack, 0xC, 0x202),
                                     [4] = STEP(Command_Attack, 0xB, 0x1F, 10, -1),
                                     [5] = STEP(Wait, 1) };
    Run_Pattern_Or(wk, script, 6, passive14_0168_from_step_6);
}

void Passive14_0169(PLW* wk) {
    pattern_approach_walk_jump_attack_term_normal_attack_3(wk, &(SA_Term_Args) { 0x32, 0xFFFF, 0xFFFF, 0xBF });
}

void Passive14_0170(PLW* wk) {
    pattern_approach_walk_turn_over_on_hi_jump_attack_term(
        wk,
        0xBF,
        &(Hi_Jump_Term_Args) { -1, 0x61, 9, 0x202, 0, -0x7F80, -1, 0x400 },
        &(SA_Term_Args) { 0x32, 0xFFFF, 0xFFFF, 0xBF }
    );
}

void Passive14_0171(PLW* wk) {
    pattern_approach_walk_jump_attack_term_normal_attack_3(wk, &(SA_Term_Args) { 0x34, 0x34, 0x34, 0x7F });
}

/* Passive14_0172 and Passive14_0178 are the same four-step script, literal for
 * literal. */
static void run_passive14_jump_attack_term_script(PLW* wk) {
    const Pattern_Step script[4] = { [0] = STEP(Jump_Attack_Term, -0x7FA8, -0x7FC8, 9, 0x400, 0, -0x7F80, -1, 0x400),
                                     [1] = STEP(Normal_Attack, 9, 0x220),
                                     [2] = STEP(Normal_Attack, 0xC, 0x202),
                                     [3] = STEP(Command_Attack, 0xC, 0x1F, 10, -1) };
    Run_Pattern(wk, script, 4);
}

void Passive14_0172(PLW* wk) {
    run_passive14_jump_attack_term_script(wk);
}

void Passive14_0173(PLW* wk) {
    pattern_jump_attack_term_normal_attack_command_attack_8(
        wk, &(Command_Attack_Args) { 0xC, 0x1F, 10, -1 }, &(SA_Term_Args) { 0x2F, 0x30, 0x31, 0x7F }
    );
}

static void passive14_pattern_jump_attack_term_normal_attack_sa_term(PLW* wk, s16 reaction, u16 lever_data,
                                                                     const SA_Term_Args* p) {
    const Pattern_Step script[4] = { [0] = STEP(Jump_Attack_Term, -0x7FA8, -0x7FC8, 9, 0x400, 0, -0x7F80, -1, 0x400),
                                     [1] = STEP(Normal_Attack, reaction, lever_data),
                                     [2] = STEP_WITH(SA_Term, p),
                                     [3] = STEP(
                                         Com_Random_Select, &(Branch_Menu_Args) { 6, 0x77, 0x77, 0x78, 0x79 }, 2) };
    Run_Pattern(wk, script, 4);
}

void Passive14_0174(PLW* wk) {
    passive14_pattern_jump_attack_term_normal_attack_sa_term(
        wk, 9, 0x220, &(SA_Term_Args) { 0x32, 0xFFFF, 0xFFFF, 0xBF }
    );
}

static void passive14_pattern_turn_over_on_hi_jump_attack_term_normal_attack(PLW* wk, const Hi_Jump_Term_Args* a,
                                                                             s16 reaction, const SA_Term_Args* p) {
    const Pattern_Step script[5] = { [0] = STEP_NOARG(Turn_Over_On),
                                     [1] = STEP_WITH(Hi_Jump_Attack_Term, a),
                                     [2] = STEP(Normal_Attack, reaction, 0x202),
                                     [3] = STEP_WITH(SA_Term, p),
                                     [4] = STEP(
                                         Com_Random_Select, &(Branch_Menu_Args) { 6, 0x77, 0x77, 0x78, 0x79 }, 2) };
    Run_Pattern(wk, script, 5);
}

void Passive14_0175(PLW* wk) {
    passive14_pattern_turn_over_on_hi_jump_attack_term_normal_attack(
        wk,
        &(Hi_Jump_Term_Args) { -1, 0x61, 9, 0x202, 0, -0x7F80, -1, 0x400 },
        9,
        &(SA_Term_Args) { 0x32, 0xFFFF, 0xFFFF, 0xBF }
    );
}

void Passive14_0176(PLW* wk) {
    passive14_pattern_jump_attack_term_normal_attack_sa_term(wk, 9, 0x220, &(SA_Term_Args) { 0x34, 0x34, 0x34, 0x7F });
}

void Passive14_0177(PLW* wk) {
    active_pattern_com_random_select(wk, &(Branch_Menu_Args) { 2, 0x3F, 0x40, 0x41, 0x42 }, 0);
}

void Passive14_0178(PLW* wk) {
    run_passive14_jump_attack_term_script(wk);
}

void Passive14_0179(PLW* wk) {
    pattern_jump_attack_term_normal_attack_command_attack_8(
        wk, &(Command_Attack_Args) { 0xB, 0x1F, 10, -1 }, &(SA_Term_Args) { 0x2F, 0x34, 0x34, 0x7F }
    );
}

void Passive14_0180(PLW* wk) {
    passive14_pattern_jump_attack_term_normal_attack_sa_term(
        wk, 9, 0x220, &(SA_Term_Args) { 0x32, 0xFFFF, 0xFFFF, 0xBF }
    );
}

void Passive14_0181(PLW* wk) {
    passive14_pattern_turn_over_on_hi_jump_attack_term_normal_attack(
        wk,
        &(Hi_Jump_Term_Args) { -1, 0x61, 9, 0x202, 0, -0x7F80, -1, 0x400 },
        9,
        &(SA_Term_Args) { 0x32, -1, -1, 0xBF }
    );
}

void Passive14_0182(PLW* wk) {
    passive14_pattern_jump_attack_term_normal_attack_sa_term(wk, 9, 0x220, &(SA_Term_Args) { 0x34, 0x34, 0x34, 0x7F });
}

void Passive14_0183(PLW* wk) {
    passive14_pattern_turn_over_on_hi_jump_attack_term_normal_attack(
        wk,
        &(Hi_Jump_Term_Args) { -1, 0x61, 9, 0x202, 0, -0x7F80, -1, 0x400 },
        9,
        &(SA_Term_Args) { 0x34, 0x34, 0x34, 0x7F }
    );
}

void Passive14_0184(PLW* wk) {
    const Pattern_Step script[4] = { [0] = STEP(Approach_Walk, 0xBF, 3),
                                     [1] = STEP(Command_Attack, 0xB, 0x1F, 10, -1),
                                     [2] = STEP(Wait, 1),
                                     [3] = STEP(SA_Term, 0x2F, 0xFFFF, 0xFFFF, 0xFFFF) };
    Run_Pattern(wk, script, 4);
}

void Passive14_0185(PLW* wk) {
    passive14_pattern_jump_attack_term_normal_attack_command_attack(
        wk,
        &(Jump_Term_Args) { -0x7FA8, -0x7FC8, 9, 0x400, 0, -0x7F80, -1, 0x400 },
        &(Command_Attack_Args) { 0xB, 0x1F, 10, -1 },
        &(SA_Term_Args) { 0x2F, 0x34, 0x34, 0x7F }
    );
}

void Passive14_0186(PLW* wk) {
    pattern_approach_walk_com_random_select_2(wk, &(Branch_Menu_Args) { 6, 0xB2, 0xB3, 0xB4, 0xB6 });
}

void Passive14_0187(PLW* wk) {
    passive14_pattern_jump_attack_term_normal_attack_command_attack_2(
        wk, &(Jump_Term_Args) { -0x7FA8, -0x7FC8, 9, 0x400, 0, -0x7F80, -1, 0x400 }
    );
}

void Passive14_0188(PLW* wk) {
    passive14_pattern_jump_attack_term_normal_attack_sa_term(
        wk, 0xB, 0x202, &(SA_Term_Args) { 0x32, 0xFFFF, 0xFFFF, 0xBF }
    );
}

void Passive14_0189(PLW* wk) {
    passive14_pattern_jump_attack_term_normal_attack_sa_term(
        wk, 0xB, 0x202, &(SA_Term_Args) { 0x34, 0x34, 0x34, 0x7F }
    );
}

void Passive14_0190(PLW* wk) {
    pattern_approach_walk_com_random_select_2(wk, &(Branch_Menu_Args) { 6, 0xB9, 0xBB, 0xBC, 0xBD });
}

void Passive14_0191(PLW* wk) {
    passive14_pattern_turn_over_on_hi_jump_attack_term_normal_attack(
        wk,
        &(Hi_Jump_Term_Args) { -1, 0x61, 0xB, 0x202, 0, -0x7F80, -1, 0x400 },
        0xB,
        &(SA_Term_Args) { 0x2F, 0x34, 0x34, 0x7F }
    );
}

void Passive14_0192(PLW* wk) {
    const Pattern_Step script[6] = { [0] = STEP_NOARG(Turn_Over_On),
                                     [1] = STEP(Hi_Jump_Attack_Term, -1, 0x61, 0xB, 0x202, 0, -0x7F80, -1, 0x400),
                                     [2] = STEP(Normal_Attack, 0xC, 0x202),
                                     [3] = STEP_NOARG(Pierce_On),
                                     [4] = STEP(J_Command_Attack, 0xB, 0x20, 8, -1),
                                     [5] = STEP(Wait, 3) };
    Run_Pattern_Or(wk, script, 6, pattern_j_command_attack_from_step_6);
}

void Passive14_0193(PLW* wk) {
    pattern_approach_walk_com_random_select_2(wk, &(Branch_Menu_Args) { 6, 0xB5, 0xB7, 0xBF, 0xC0 });
}

void Passive14_0194(PLW* wk) {
    active_pattern_com_random_select(wk, &(Branch_Menu_Args) { 6, 0xB2, 0xB3, 0xB4, 0xB6 }, 0);
}

void Passive14_0195(PLW* wk) {
    active_pattern_com_random_select(wk, &(Branch_Menu_Args) { 6, 0xB9, 0xBB, 0xBC, 0xBD }, 0);
}

void Passive14_0196(PLW* wk) {
    active_pattern_com_random_select(wk, &(Branch_Menu_Args) { 6, 0xB5, 0xB7, 0xBF, 0xC0 }, 0);
}

static void passive14_0197_from_step_6(PLW* wk) {
    const Pattern_Step script[9] = { [6] = STEP(J_Command_Attack, 8, 0x20, 8, -1),
                                     [7] = STEP(Wait, 3),
                                     [8] = STEP(J_Command_Attack, 8, 0x1E, 8, -1) };
    Run_Pattern(wk, script, 9);
}

void Passive14_0197(PLW* wk) {
    const Pattern_Step script[6] = {
        [0] = STEP(Command_Attack, 8, 0, -1, -1),     [1] = STEP(Approach_Walk, 0x47, 2),
        [2] = STEP(EM_Term, -1, -0x7FF8, 6, 6, 0x7C), [3] = STEP(SA_Term, 0x34, 0x34, 0x34, 0x7F),
        [4] = STEP(Normal_Attack, 0xC, 0x40),         [5] = STEP_NOARG(Pierce_On)
    };
    Run_Pattern_Or(wk, script, 6, passive14_0197_from_step_6);
}

void Passive14_0198(PLW* wk) {
    pattern_normal_attack(wk, 8, 0x400);
}

void Passive14_0199(PLW* wk) {
    const Pattern_Step script[4] = { [0] = STEP(Wait_Attack_Complete, 1, 1),
                                     [1] = STEP(SA_Term, 0x2F, 0x30, 0x31, 0x7F),
                                     [2] = STEP(Normal_Attack, 0xC, 0x202),
                                     [3] = STEP(Command_Attack, 8, 0x1F, 10, -1) };
    Run_Pattern(wk, script, 4);
}

static void passive14_pattern_turn_over_on_jump_attack_term_com_random_select(PLW* wk, const Branch_Menu_Args* p) {
    const Pattern_Step script[3] = { [0] = STEP_NOARG(Turn_Over_On),
                                     [1] = STEP(Jump_Attack_Term, -1, 0x49, 9, 0x202, 0, -0x7F80, -1, 0x40),
                                     [2] = STEP(Com_Random_Select, p, 0) };
    Run_Pattern(wk, script, 3);
}

void Passive14_0200(PLW* wk) {
    passive14_pattern_turn_over_on_jump_attack_term_com_random_select(
        wk, &(Branch_Menu_Args) { 2, 0x4C, 0x4D, 0x4E, 0x4F }
    );
}

void Passive14_0201(PLW* wk) {
    passive14_pattern_turn_over_on_jump_attack_term_com_random_select(
        wk, &(Branch_Menu_Args) { 2, 0x50, 0x51, 0x52, 0x53 }
    );
}

void Passive14_0202(PLW* wk) {
    passive14_pattern_turn_over_on_jump_attack_term_com_random_select(
        wk, &(Branch_Menu_Args) { 2, 0x54, 0x55, 0x56, 0x57 }
    );
}

void Passive14_0203(PLW* wk) {
    passive14_pattern_turn_over_on_jump_attack_term_com_random_select(
        wk, &(Branch_Menu_Args) { 2, 0x58, 0x59, 0x5A, 0x5B }
    );
}

void Passive14_0204(PLW* wk) {
    passive14_pattern_command_attack_com_random_select(wk, &(Branch_Menu_Args) { 2, 0x4C, 0x4D, 0x4E, 0x4F }, 0);
}

void Passive14_0205(PLW* wk) {
    passive14_pattern_command_attack_com_random_select(wk, &(Branch_Menu_Args) { 2, 0x50, 0x51, 0x52, 0x53 }, 0);
}

void Passive14_0206(PLW* wk) {
    passive14_pattern_command_attack_com_random_select(wk, &(Branch_Menu_Args) { 2, 0x54, 0x55, 0x56, 0x57 }, 0);
}

void Passive14_0207(PLW* wk) {
    passive14_pattern_command_attack_com_random_select(wk, &(Branch_Menu_Args) { 2, 0x58, 0x59, 0x5A, 0x5B }, 0);
}

void passive14_pattern_approach_walk_jump_command_attack_term_com_random_select(PLW* wk, s16 target_pos,
                                                                                const Branch_Menu_Args* p) {
    const Pattern_Step script[3] = {
        [0] = STEP(Approach_Walk, target_pos, 3),
        [1] = STEP(Jump_Command_Attack_Term, 8, 0x2F, 10, -1, -0x7F60, 0x50, 0, -0x7F80, -1, 0x400),
        [2] = STEP(Com_Random_Select, p, 0)
    };
    Run_Pattern(wk, script, 3);
}

void Passive14_0208(PLW* wk) {
    passive14_pattern_approach_walk_jump_command_attack_term_com_random_select(
        wk, 0xB5, &(Branch_Menu_Args) { 2, 0x4C, 0x4D, 0x4E, 0x4F }
    );
}
