/**
 * @file com_patterns_6step.c
 * COM: pattern skeletons shared by every character
 *
 * The six-step patterns.
 *
 * A COM pattern script is a switch on the step counter with one engine call
 * per step, and the same step sequences recur across characters. Each skeleton
 * here is exactly the body its call sites used to hold, with the arguments of
 * its calls taken as parameters and written out in full at each call site.
 */

#include "common.h"
#include "sf33rd/Source/Game/com/com_sub.h"
#include "sf33rd/Source/Game/com/patterns/com_branch_menus.h"
#include "sf33rd/Source/Game/com/patterns/com_pattern_run.h"
#include "sf33rd/Source/Game/com/patterns/com_patterns.h"
#include "sf33rd/Source/Game/engine/workuser.h"

void active_pattern_approach_walk_jump_attack_term_normal_attack_2(PLW* wk, s16 option) {
    const Pattern_Step script[6] = { [0] = STEP(Approach_Walk, 0xbf, option),
                                     [1] = STEP(Jump_Attack_Term, 0x8058, 0x8038, 0xb, 0x400, 0, 0x8080, -1, 0x400),
                                     [2] = STEP(Normal_Attack, 0xb, 0x202),
                                     [3] = STEP(Command_Attack, 0xc, 0x1f, 10, -1),
                                     [4] = STEP(Wait, 1),
                                     [5] = STEP(SA_Term, 0x2f, 0x30, 0x31, 0x7f) };
    Run_Pattern(wk, script, 6);
}

void active_pattern_normal_attack_pierce_on_j_command_attack(PLW* wk, u16 lever_data) {
    const Pattern_Step script[6] = { [0] = STEP(Normal_Attack, 9, lever_data),
                                     [1] = STEP(Normal_Attack, 0xc, 0x202),
                                     [2] = STEP_NOARG(Pierce_On),
                                     [3] = STEP(J_Command_Attack, 0xb, 0x20, 8, -1),
                                     [4] = STEP(Wait, 5),
                                     [5] = STEP(SA_Term, 0x2f, -1, 0x31, 0x7f) };
    Run_Pattern_Or(wk, script, 6, active_pattern_j_command_attack_from_step_6_2);
}

void active_pattern_normal_attack_pierce_on_j_command_attack_2(PLW* wk, s16 reaction, u16 lever_data) {
    const Pattern_Step script[6] = { [0] = STEP(Normal_Attack, 9, 0x200),
                                     [1] = STEP(Normal_Attack, reaction, lever_data),
                                     [2] = STEP_NOARG(Pierce_On),
                                     [3] = STEP(J_Command_Attack, 0xb, 0x20, 9, -1),
                                     [4] = STEP(Wait, 3),
                                     [5] = STEP(J_Command_Attack, 8, 0x1e, 9, -1) };
    Run_Pattern(wk, script, 6);
}

void active_pattern_pierce_on_command_attack_wait(PLW* wk, const Command_Attack_Args* p, const Command_Attack_Args* p_b,
                                                  const Command_Attack_Args* p_b_b) {
    const Pattern_Step script[6] = { [0] = STEP_NOARG(Pierce_On), [1] = STEP_WITH(Command_Attack, p),
                                     [2] = STEP(Wait, 0xe),       [3] = STEP_WITH(Command_Attack, p_b),
                                     [4] = STEP(Wait, 0xe),       [5] = STEP_WITH(Command_Attack, p_b_b) };
    Run_Pattern(wk, script, 6);
}

void active_pattern_search_back_term_walk_wait(PLW* wk) {
    const Pattern_Step script[6] = { [0] = STEP(Search_Back_Term, 0x30, 2, 0xF),
                                     [1] = STEP(Walk, 1, 0x20, 0),
                                     [2] = STEP(Wait, 3),
                                     [3] = STEP(Walk, 0, 0x30, 0),
                                     [4] = STEP(Wait, 9),
                                     [5] = STEP(Walk, 0, 0x20, 0) };
    Run_Pattern(wk, script, 6);
}

void pattern_approach_walk_em_term_normal_attack_4(PLW* wk, s16 target_pos, const Command_Attack_Args* p,
                                                   const SA_Term_Args* p_b) {
    const Pattern_Step script[6] = { [0] = STEP(Approach_Walk, target_pos, 2),
                                     [1] = STEP(EM_Term, -1, -0x7FF0, 6, 1, -1),
                                     [2] = STEP(Normal_Attack, 9, 0x40),
                                     [3] = STEP_WITH(J_Command_Attack, p),
                                     [4] = STEP(Wait, 5),
                                     [5] = STEP_WITH(SA_Term, p_b) };
    Run_Pattern(wk, script, 6);
}

void pattern_approach_walk_em_term_normal_attack_8(PLW* wk, const EM_Term_Params* p, u16 lever_data, s16 time) {
    const Pattern_Step script[6] = { [0] = STEP(Approach_Walk, 0x47, 2),
                                     [1] = STEP_WITH(EM_Term, p),
                                     [2] = STEP(Normal_Attack, 0xC, lever_data),
                                     [3] = STEP(J_Command_Attack, 0xC, 0x1E, 10, -1),
                                     [4] = STEP(Wait, time),
                                     [5] = STEP(SA_Term, 0x2F, 0x30, 0x31, 0x7F) };
    Run_Pattern(wk, script, 6);
}

void pattern_approach_walk_em_term_sa_term_4(PLW* wk, s16 target_pos, const SA_Term_Args* p, s16 reaction) {
    const Pattern_Step script[6] = { [0] = STEP(Approach_Walk, target_pos, 2),
                                     [1] = STEP(EM_Term, -1, -0x7FF8, 6, 1, -1),
                                     [2] = STEP_WITH(SA_Term, p),
                                     [3] = STEP(Normal_Attack, reaction, 0x12),
                                     [4] = STEP(Normal_Attack, 8, 0x42),
                                     [5] = STEP(Com_Random_Select, &Branch_Menu_6_37_37_27_27, 0) };
    Run_Pattern(wk, script, 6);
}

void pattern_approach_walk_turn_over_on_hi_jump_attack_term(PLW* wk, s16 target_pos, const Hi_Jump_Term_Args* a,
                                                            const SA_Term_Args* p) {
    const Pattern_Step script[6] = { [0] = STEP(Approach_Walk, target_pos, 2),
                                     [1] = STEP_NOARG(Turn_Over_On),
                                     [2] = STEP_WITH(Hi_Jump_Attack_Term, a),
                                     [3] = STEP(Normal_Attack, 9, 0x202),
                                     [4] = STEP_WITH(SA_Term, p),
                                     [5] = STEP(Com_Random_Select, &Branch_Menu_6_77_77_78_79, 2) };
    Run_Pattern(wk, script, 6);
}

void pattern_em_term_sa_term_normal_attack(PLW* wk, const SA_Term_Args* p, s16 reaction, s16 reaction_b) {
    const Pattern_Step script[6] = {
        [0] = STEP(EM_Term, -1, -0x7FD8, 6, 1, -1),  [1] = STEP_WITH(SA_Term, p),
        [2] = STEP(Normal_Attack, reaction, 0x10),   [3] = STEP(Normal_Attack, 8, 0x20),
        [4] = STEP(Normal_Attack, reaction_b, 0x40), [5] = STEP(Com_Random_Select, &Branch_Menu_6_37_37_27_27, 0)
    };
    Run_Pattern(wk, script, 6);
}

void pattern_jump_attack_term_normal_attack_command_attack_4(PLW* wk, const Jump_Term_Args* a,
                                                             const Command_Attack_Args* p, s16 rnd_type) {
    const Pattern_Step script[6] = {
        [0] = STEP_WITH(Jump_Attack_Term, a), [1] = STEP(Normal_Attack, 9, 0x12),
        [2] = STEP(Normal_Attack, 9, 0x102),  [3] = STEP(Normal_Attack, 8, 0x202),
        [4] = STEP_WITH(Command_Attack, p),   [5] = STEP(Com_Random_Select, &Branch_Menu_6_2D_FF_FF_FF, rnd_type)
    };
    Run_Pattern(wk, script, 6);
}

void pattern_jump_attack_term_normal_attack_command_attack_8(PLW* wk, const Command_Attack_Args* p,
                                                             const SA_Term_Args* p_b) {
    const Pattern_Step script[6] = { [0] = STEP(Jump_Attack_Term, -0x7FA8, -0x7FC8, 9, 0x400, 0, -0x7F80, -1, 0x400),
                                     [1] = STEP(Normal_Attack, 9, 0x220),
                                     [2] = STEP(Normal_Attack, 0xC, 0x202),
                                     [3] = STEP_WITH(Command_Attack, p),
                                     [4] = STEP(Wait, 1),
                                     [5] = STEP_WITH(SA_Term, p_b) };
    Run_Pattern(wk, script, 6);
}

void pattern_jump_attack_term_normal_attack_j_command_attack_3(PLW* wk, const Command_Attack_Args* p) {
    const Pattern_Step script[6] = { [0] = STEP(Jump_Attack_Term, -0x7FA8, -0x7FC0, 9, 0x200, 0, -0x7FB0, -1, 0x200),
                                     [1] = STEP(Normal_Attack, 9, 0x12),
                                     [2] = STEP(Normal_Attack, 9, 0x102),
                                     [3] = STEP(Normal_Attack, 8, 0x202),
                                     [4] = STEP_WITH(J_Command_Attack, p),
                                     [5] = STEP(Com_Random_Select, &Branch_Menu_6_2D_FF_FF_FF, 2) };
    Run_Pattern(wk, script, 6);
}

void pattern_normal_attack_jump_attack_term_normal_attack_2(PLW* wk, const Command_Attack_Args* p) {
    const Pattern_Step script[6] = { [0] = STEP(Normal_Attack, 9, 0x100),
                                     [1] = STEP(Jump_Attack_Term, -0x7FA8, -0x7FC0, 9, 0x20, 0, -0x7FB0, -1, 0x200),
                                     [2] = STEP(Normal_Attack, 9, 0x12),
                                     [3] = STEP(Normal_Attack, 9, 0x102),
                                     [4] = STEP(Normal_Attack, 8, 0x202),
                                     [5] = STEP_WITH(Command_Attack, p) };
    Run_Pattern(wk, script, 6);
}

void pattern_pierce_on_approach_walk_jump_attack_term(PLW* wk, const Jump_Term_Args* a, const Command_Attack_Args* p) {
    const Pattern_Step script[6] = { [0] = STEP_NOARG(Pierce_On),          [1] = STEP(Approach_Walk, 0xB1, 2),
                                     [2] = STEP_WITH(Jump_Attack_Term, a), [3] = STEP(Normal_Attack, 8, 0x42),
                                     [4] = STEP_WITH(J_Command_Attack, p), [5] = STEP(ETC_Term, 2, 6, 1) };
    Run_Pattern_Or(wk, script, 6, pattern_command_attack_from_step_6);
}

void pattern_pierce_on_command_attack_jump_attack_term(PLW* wk, const SA_Term_Args* p, const Command_Attack_Args* p_b) {
    const Pattern_Step script[6] = { [0] = STEP_NOARG(Pierce_On),
                                     [1] = STEP(Command_Attack, 8, 0, -1, -1),
                                     [2] = STEP(Jump_Attack_Term, -0x7FA8, -0x7FC0, 0xB, 0x200, 0, -0x7FB0, -1, 0x40),
                                     [3] = STEP(Normal_Attack, 0xB, 0x400),
                                     [4] = STEP_WITH(SA_Term, p),
                                     [5] = STEP_WITH(J_Command_Attack, p_b) };
    Run_Pattern(wk, script, 6);
}

void pattern_pierce_on_command_attack_jump_attack_term_2(PLW* wk, const SA_Term_Args* p) {
    const Pattern_Step script[6] = { [0] = STEP_NOARG(Pierce_On),
                                     [1] = STEP(Command_Attack, 8, 0, -1, -1),
                                     [2] = STEP(Jump_Attack_Term, -0x7FA8, -0x7FC0, 0xB, 0x200, 0, -1, -1, -1),
                                     [3] = STEP(Normal_Attack, 0xB, 0x12),
                                     [4] = STEP_WITH(SA_Term, p),
                                     [5] = STEP(Normal_Attack, 8, 0x402) };
    Run_Pattern(wk, script, 6);
}

void pattern_pierce_on_command_attack_normal_attack(PLW* wk, const SA_Term_Args* p) {
    const Pattern_Step script[6] = { [0] = STEP_NOARG(Pierce_On),         [1] = STEP(Command_Attack, 8, 0, -1, -1),
                                     [2] = STEP(Normal_Attack, 9, 0x102), [3] = STEP(Normal_Attack, 0xB, 0x102),
                                     [4] = STEP_WITH(SA_Term, p),         [5] = STEP(Normal_Attack, 8, 0x202) };
    Run_Pattern(wk, script, 6);
}

void pattern_pierce_on_command_attack_normal_attack_5(PLW* wk, const Command_Attack_Args* p) {
    const Pattern_Step script[6] = { [0] = STEP_NOARG(Pierce_On),         [1] = STEP(Command_Attack, 8, 0, -1, -1),
                                     [2] = STEP(Normal_Attack, 9, 0x102), [3] = STEP(Normal_Attack, 9, 0x102),
                                     [4] = STEP(Normal_Attack, 9, 0x202), [5] = STEP_WITH(Command_Attack, p) };
    Run_Pattern(wk, script, 6);
}

void pattern_pierce_on_command_attack_wait(PLW* wk) {
    const Pattern_Step script[6] = { [0] = STEP_NOARG(Pierce_On), [1] = STEP(Command_Attack, 0xe, 0x1e, 0xb, 0x70),
                                     [2] = STEP(Wait, 0xe),       [3] = STEP(Command_Attack, 0xe, 0x1e, 0xb, 0x70),
                                     [4] = STEP(Wait, 0xe),       [5] = STEP(Command_Attack, 0xe, 0x1e, 0xb, 0x70) };
    Run_Pattern_Or(wk, script, 6, pattern_wait_command_attack_wait_from_step_6);
}

void pattern_pierce_on_hi_jump_attack_term_lever_on(PLW* wk, u16 lever_data) {
    const Pattern_Step script[6] = { [0] = STEP_NOARG(Pierce_On),
                                     [1] = STEP(Hi_Jump_Attack_Term, -1, 0x40, 8, 0x400, 0, -0x7F90, -1, 0x200),
                                     [2] = STEP(Lever_On, 1, 0xFFFF),
                                     [3] = STEP(Normal_Attack, 8, 0x12),
                                     [4] = STEP(Normal_Attack, 8, lever_data),
                                     [5] = STEP(Command_Attack, 8, 0x1C, 8, -1) };
    Run_Pattern(wk, script, 6);
}

void pattern_sa_term_wait_get_up_sa_term(PLW* wk, const SA_Term_Args* p, const SA_Term_Args* p_b, s16 reaction) {
    const Pattern_Step script[6] = { [0] = STEP_WITH(SA_Term, p),        [1] = STEP(Wait_Get_Up, 0, -1),
                                     [2] = STEP_WITH(SA_Term, p_b),      [3] = STEP(Normal_Attack, reaction, 0x10),
                                     [4] = STEP(Normal_Attack, 8, 0x20), [5] = STEP(Normal_Attack, 8, 0x40) };
    Run_Pattern_Or(wk, script, 6, pattern_com_random_select_from_step_6);
}

void pattern_search_back_term_pierce_on_keep_away_2(PLW* wk, s16 target_pos, const Branch_Menu_Args* p) {
    const Pattern_Step script[6] = {
        [0] = STEP(Search_Back_Term, 0x60, 6, 0x6C), [1] = STEP_NOARG(Pierce_On),
        [2] = STEP(Keep_Away, target_pos, 0),        [3] = STEP(Wait_Get_Up, 3, -1),
        [4] = STEP(Normal_Attack, 8, 0x12),          [5] = STEP_WITH(Branch_Unit_Area, p)
    };
    Run_Pattern(wk, script, 6);
}

void pattern_search_back_term_pierce_on_keep_away_5(PLW* wk, s16 target_pos) {
    const Pattern_Step script[6] = { [0] = STEP(Search_Back_Term, 0x60, 6, 0x6C), [1] = STEP_NOARG(Pierce_On),
                                     [2] = STEP(Keep_Away, target_pos, 0),        [3] = STEP(Wait_Get_Up, 3, -1),
                                     [4] = STEP(Normal_Attack, 8, 0x10),          [5] = STEP(Normal_Attack, 8, 0x10) };
    Run_Pattern_Or(wk, script, 6, pattern_normal_attack_from_step_6);
}
