/**
 * @file pass08_4.c
 * COM Passive: Elena
 * Pattern scripts from Passive08_0159 on.
 */

#include "common.h"
#include "sf33rd/Source/Game/com/com_sub.h"
#include "sf33rd/Source/Game/com/passive/pass08.h"
#include "sf33rd/Source/Game/com/passive/pass08_internal.h"
#include "sf33rd/Source/Game/com/patterns/com_pattern_run.h"
#include "sf33rd/Source/Game/com/patterns/com_patterns.h"
#include "sf33rd/Source/Game/engine/workuser.h"

void Passive08_0159(PLW* wk) {
    const Pattern_Step script[6] = {
        [0] = STEP(Approach_Walk, 0x3F, 2),       [1] = STEP(Normal_Attack, 0xC, 0x40),
        [2] = STEP(SA_Term, 0x39, 0x3A, 0x3B, 0), [3] = STEP(J_Command_Attack, 8, 0x1E, 10, -1),
        [4] = STEP(Normal_Attack, 8, 0x402),      [5] = STEP_NOARG(Pierce_On)
    };
    if (!Run_Pattern_Steps(wk, script, 6)) {
        pattern_search_back_term_command_attack_from_step_6(wk);
    }
}

void Passive08_0160(PLW* wk) {
    active_pattern_jump_attack_term_normal_attack_j_command_attack(
        wk,
        &(Jump_Term_Args) { -0x7FA8, -0x7FC0, 9, 0x200, 0, -0x7FB0, -1, 0x20 },
        0x202,
        &(Command_Attack_Args) { 8, 0x1E, 0xA, -1 }
    );
}

void Passive08_0161(PLW* wk) {
    pattern_jump_attack_term_sa_term_j_command_attack(
        wk, &(SA_Term_Args) { 0x39, 0x3A, 0x3B, 0 }, &(Command_Attack_Args) { 8, 0x1C, 0xA, -1 }
    );
}

/* The three Normal_Attack steps this script runs, named rather than indexed:
 * subscripts would put integers into the file that the scripts themselves never
 * wrote, and refactor_guard.py is right to refuse that. */
typedef struct {
    Normal_Attack_Step first;
    Normal_Attack_Step second;
    Normal_Attack_Step third;
} Passive08_Normal_Attacks;

/* Passive08_0162 and Passive08_0164 are the same four steps: a jump attack term
 * and three Normal_Attacks. Six of their nineteen literals differ, which is too
 * many to pass one by one, so each call's values travel as the parameter object
 * that call already has a shape for. */
static void run_passive08_jump_attack_term_3normal(PLW* wk, const Jump_Term_Args* a,
                                                   const Passive08_Normal_Attacks* n) {
    const Pattern_Step script[4] = { [0] = STEP_WITH(Jump_Attack_Term, a),
                                     [1] = STEP(Normal_Attack, n->first.Reaction, n->first.Lever_Data),
                                     [2] = STEP(Normal_Attack, n->second.Reaction, n->second.Lever_Data),
                                     [3] = STEP(Normal_Attack, n->third.Reaction, n->third.Lever_Data) };
    Run_Pattern(wk, script, 4);
}

void Passive08_0162(PLW* wk) {
    run_passive08_jump_attack_term_3normal(
        wk,
        &(Jump_Term_Args) { -0x7FA8, -0x7FC0, 9, 0x20, 0, -0x7FB0, -1, 0x200 },
        &(Passive08_Normal_Attacks) { { 9, 0x12 }, { 8, 0x202 }, { 9, 0x402 } }
    );
}

void Passive08_0163(PLW* wk) {
    pattern_jump_attack_term_normal_attack_com_random_select(
        wk,
        &(Jump_Term_Args) { -0x7FA8, -0x7FC0, 9, 0x200, 0, -0x7FB0, -1, 0x200 },
        &(Branch_Menu_Args) { 6, 0x2D, 0xFF, 0xFF, 0xFF },
        2
    );
}

void Passive08_0164(PLW* wk) {
    run_passive08_jump_attack_term_3normal(
        wk,
        &(Jump_Term_Args) { -0x7FA0, -0x7FC0, 9, 0x400, 0, -0x7FB0, -1, 0x200 },
        &(Passive08_Normal_Attacks) { { 8, 0x102 }, { 8, 0x400 }, { 8, 0x402 } }
    );
}

void Passive08_0165(PLW* wk) {
    pattern_jump_attack_term_normal_attack_j_command_attack_2(
        wk,
        &(Jump_Term_Args) { -0x7FA0, -0x7FC0, 9, 0x400, 0, -0x7FB0, -1, 0x200 },
        0x402,
        &(Command_Attack_Args) { 8, 0x1E, 0xA, -1 }
    );
}

void Passive08_0166(PLW* wk) {
    pattern_jump_attack_term_normal_attack_3(
        wk, &(Jump_Term_Args) { -0x7FA0, -0x7FC0, 9, 0x400, 0, -0x7FB0, -1, 0x200 }, 0x102, 0x402
    );
}

void Passive08_0167(PLW* wk) {
    const Pattern_Step script[4] = { [0] = STEP(Jump_Attack_Term, -0x7FA0, -0x7FC0, 9, 0x400, 0, -0x7FB0, -1, 0x200),
                                     [1] = STEP(Normal_Attack, 9, 0x402),
                                     [2] = STEP(J_Command_Attack, 8, 0x1E, 8, -1),
                                     [3] = STEP(J_Command_Attack, 8, 0x1C, 0xA, -1) };
    Run_Pattern(wk, script, 4);
}

void Passive08_0168(PLW* wk) {
    pattern_walk(wk, -1);
}

void Passive08_0169(PLW* wk) {
    pattern_normal_attack_2(wk, 8, 0x102, 0x402);
}

void Passive08_0170(PLW* wk) {
    pattern_keep_away_wait_get_up_2(wk, 3);
}

void Passive08_0171(PLW* wk) {
    pattern_keep_away_wait_get_up_2(wk, 0);
}

void Passive08_0172(PLW* wk) {
    pattern_keep_away_wait_get_up_2(wk, 3);
}

void Passive08_0173(PLW* wk) {
    pattern_sa_term(wk, &(SA_Term_Args) { 0xFFFF, 0xFFFF, 0x3B, 0 });
}

void Passive08_0174(PLW* wk) {
    pattern_approach_walk_em_term_normal_attack_4(
        wk, 0x3F, &(Command_Attack_Args) { 0xC, 0x1E, 9, -1 }, &(SA_Term_Args) { 0x39, 0x3A, 0x3B, 0 }
    );
}

void Passive08_0175(PLW* wk) {
    pattern_normal_attack_j_command_attack_5(wk, &(Command_Attack_Args) { 8, 0x1C, 0xA, -1 });
}

void Passive08_0176(PLW* wk) {
    pattern_normal_attack_j_command_attack_com_random_select(wk);
}

void Passive08_0177(PLW* wk) {
    pattern_normal_attack_j_command_attack_com_random_select_2(wk);
}

void Passive08_0178(PLW* wk) {
    const Pattern_Step script[4] = { [0] = STEP(Jump_Attack_Term, -0x7FA0, -0x7FC0, 9, 0x40, 0, -0x7FB0, -1, 0x200),
                                     [1] = STEP(Normal_Attack, 0xB, 0x40),
                                     [2] = STEP(J_Command_Attack, 0xC, 0x1E, 0xA, -1),
                                     [3] = STEP(SA_Term, 0x39, 0x3A, 0x3B, 0) };
    Run_Pattern(wk, script, 4);
}

void Passive08_0179(PLW* wk) {
    pattern_lever_attack_normal_attack(wk);
}

void Passive08_0180(PLW* wk) {
    const Pattern_Step script[4] = { [0] = STEP(Lever_Attack, 8, 0, 0x200),
                                     [1] = STEP(J_Command_Attack, 8, 0x1E, 8, -1),
                                     [2] = STEP(J_Command_Attack, 8, 0x1E, 9, -1),
                                     [3] = STEP(J_Command_Attack, 8, 0x1C, 0xA, -1) };
    Run_Pattern(wk, script, 4);
}

void Passive08_0181(PLW* wk) {
    pattern_lever_attack_normal_attack_j_command_attack(wk, 0x200, 0x400, &(Command_Attack_Args) { 8, 0x1E, 0xA, -1 });
}

void Passive08_0182(PLW* wk) {
    active_pattern_approach_walk(wk, 0x3F);
}

void Passive08_0183(PLW* wk) {
    pattern_jump_attack_term_normal_attack_j_command_attack_2(
        wk,
        &(Jump_Term_Args) { -0x7FA0, -0x7FC0, 9, 0x40, 0, -0x7FB0, -1, 0x200 },
        0x40,
        &(Command_Attack_Args) { 8, 0x1D, 0xA, -1 }
    );
}

void Passive08_0184(PLW* wk) {
    pattern_jump_attack_term_normal_attack_j_command_attack_3(wk, &(Command_Attack_Args) { 8, 0x1D, 10, -1 });
}

void Passive08_0185(PLW* wk) {
    active_pattern_normal_attack(wk, 8, 0x20);
}

void Passive08_0186(PLW* wk) {
    passive08_pattern_pierce_on_j_command_attack_search_back_term(wk, &(Command_Attack_Args) { 8, 0x1D, 8, -1 });
}

void Passive08_0187(PLW* wk) {
    passive08_pattern_pierce_on_j_command_attack_search_back_term(wk, &(Command_Attack_Args) { 8, 0x1D, 9, -1 });
}

void Passive08_0188(PLW* wk) {
    passive08_pattern_pierce_on_j_command_attack_search_back_term(wk, &(Command_Attack_Args) { 8, 0x1D, 0xA, -1 });
}

void Passive08_0189(PLW* wk) {
    active_pattern_em_term_j_command_attack(
        wk, &(EM_Term_Params) { -0x7F70, 0x28, 7, 1, -1 }, &(Command_Attack_Args) { 8, 0x1C, 9, -1 }
    );
}

void Passive08_0190(PLW* wk) {
    active_pattern_em_term_j_command_attack(
        wk, &(EM_Term_Params) { -0x7F70, 0x28, 7, 1, -1 }, &(Command_Attack_Args) { 8, 0x1C, 0xA, -1 }
    );
}

void Passive08_0191(PLW* wk) {
    pattern_approach_walk_com_random_select(wk, 0x60, &(Branch_Menu_Args) { 6, 0x3F, 0x40, 0x41, 0x43 }, 0);
}

void Passive08_0192(PLW* wk) {
    pattern_keep_away_com_random_select(wk, 0xBF);
}

void Passive08_0193(PLW* wk) {
    pattern_walk_com_random_select(wk, 0x20, &(Branch_Menu_Args) { 6, 0xBA, 1, 0xAF, 0x92 }, 3);
}

void Passive08_0194(PLW* wk) {
    pattern_normal_attack_com_random_select_3(wk, 0x200);
}

void Passive08_0195(PLW* wk) {
    pattern_normal_attack_com_random_select_3(wk, 0x400);
}

void Passive08_0196(PLW* wk) {
    active_pattern_em_term_j_command_attack(
        wk, &(EM_Term_Params) { -0x7F70, 0x28, 7, 1, -1 }, &(Command_Attack_Args) { 8, 0x1D, 0xA, -1 }
    );
}

void Passive08_0197(PLW* wk) {
    pattern_em_term_normal_attack(wk, &(EM_Term_Params) { -0x7F70, 0x28, 7, 1, -1 }, 0x20);
}

void Passive08_0198(PLW* wk) {
    active_pattern_em_term_lever_attack(wk, &(EM_Term_Params) { -0x7F70, 0x28, 7, 1, -1 }, 0, 0x402);
}

void Passive08_0199(PLW* wk) {
    active_pattern_normal_attack_j_command_attack(wk, 0xC, 0x40, &(Command_Attack_Args) { 8, 0x1C, 0xA, -1 });
}

void Passive08_0200(PLW* wk) {
    const Pattern_Step script[5] = { [0] = STEP(Normal_Attack, 0xC, 0x40),
                                     [1] = STEP(J_Command_Attack, 8, 0x1C, 0xA, -1),
                                     [2] = STEP_NOARG(Pierce_On),
                                     [3] = STEP(Search_Back_Term, 0x60, 1, -1),
                                     [4] = STEP(Command_Attack, 8, 1, -1, -1) };
    Run_Pattern(wk, script, 5);
}

void Passive08_0201(PLW* wk) {
    const Pattern_Step script[4] = { [0] = STEP(Normal_Attack, 9, 0x40),
                                     [1] = STEP(J_Command_Attack, 0xC, 0x1C, 0xA, -1),
                                     [2] = STEP(Wait, 5),
                                     [3] = STEP(SA_Term, 0x39, 0x3A, 0x3B, 0) };
    Run_Pattern(wk, script, 4);
}

void Passive08_0202(PLW* wk) {
    pattern_normal_attack_sa_term_j_command_attack(
        wk, 0x40, &(SA_Term_Args) { 0x39, 0x3A, 0x3B, 0 }, &(Command_Attack_Args) { 8, 0x1D, 0xA, -1 }
    );
}

void Passive08_0203(PLW* wk) {
    pattern_wait_j_command_attack(wk, 2, &(Command_Attack_Args) { 8, 0x1C, 0xA, -1 });
}

void Passive08_0204(PLW* wk) {
    pattern_wait_j_command_attack(wk, 6, &(Command_Attack_Args) { 8, 0x1C, 0xA, -1 });
}

void Passive08_0205(PLW* wk) {
    pattern_jump_look(wk);
}

void Passive08_0206(PLW* wk) {
    active_pattern_jump_attack_term(wk, &(Jump_Term_Args) { -0x7FA0, -1, 8, 0x400, 1, -1, 0x20, 0x400 });
}

void Passive08_0207(PLW* wk) {
    active_pattern_jump_attack_term_command_attack(
        wk,
        &(Jump_Term_Args) { -0x7FA8, -0x7FB0, 8, 0x200, 2, -1, -0x7FB0, 0x200 },
        &(Command_Attack_Args) { 8, 0x1C, 0xA, -1 }
    );
}

void Passive08_0208(PLW* wk) {
    pattern_jump_attack_term_com_random_select(
        wk,
        &(Jump_Term_Args) { -0x7FA0, -0x7FB0, 8, 0x400, 2, -1, -0x7FB0, 0x400 },
        &(Branch_Menu_Args) { 6, 0xAF, 0xB0, 0x78, 0x7B }
    );
}

void Passive08_0209(PLW* wk) {
    active_pattern_jump_attack_term_j_command_attack(
        wk,
        &(Jump_Term_Args) { -0x7FA0, -0x7FB0, 8, 0x40, 2, -1, -0x7FB0, 0x40 },
        &(Command_Attack_Args) { 8, 0x20, 9, -1 }
    );
}

void Passive08_0210(PLW* wk) {
    pattern_jump_attack_term_normal_attack(
        wk, &(Jump_Term_Args) { -0x7FA8, -0x7FB0, 8, 0x200, 2, -1, -0x7FB0, 0x200 }, 8, 0x20
    );
}

void Passive08_0211(PLW* wk) {
    active_pattern_normal_attack(wk, 8, 0x402);
}

void Passive08_0212(PLW* wk) {
    pattern_command_attack(wk, &(Command_Attack_Args) { 9, 0x1F, 8, -1 });
}

void Passive08_0213(PLW* wk) {
    active_pattern_jump_attack_term(wk, &(Jump_Term_Args) { -0x7F00, 0x38, 8, 0x200, 1, -1, -1, -1 });
}
