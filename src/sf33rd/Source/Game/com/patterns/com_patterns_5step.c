/**
 * @file com_patterns_5step.c
 * COM: pattern skeletons shared by every character
 *
 * The five-step patterns. Part 1 of 2, in name order.
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

void active_pattern_approach_walk_jump_attack_term_normal_attack_3(PLW* wk, const SA_Term_Args* p) {
    const Pattern_Step script[5] = { [0] = STEP(Approach_Walk, 0xBF, 2),
                                     [1] = STEP(Jump_Attack_Term, -0x7FA8, -0x7FC8, 9, 0x400, 0, -0x7F80, -1, 0x400),
                                     [2] = STEP(Normal_Attack, 9, 0x220),
                                     [3] = STEP_WITH(SA_Term, p),
                                     [4] = STEP(Com_Random_Select, &Branch_Menu_6_77_77_78_79, 2) };
    Run_Pattern(wk, script, 5);
}

void active_pattern_jump_attack_term_normal_attack_command_attack(PLW* wk, const Jump_Term_Args* a, u16 lever_data,
                                                                  const SA_Term_Args* p) {
    const Pattern_Step script[5] = { [0] = STEP_WITH(Jump_Attack_Term, a),
                                     [1] = STEP(Normal_Attack, 9, lever_data),
                                     [2] = STEP(Command_Attack, 0xC, 0x1D, 0xA, -1),
                                     [3] = STEP(Wait, 5),
                                     [4] = STEP_WITH(SA_Term, p) };
    Run_Pattern(wk, script, 5);
}

void active_pattern_jump_attack_term_normal_attack_command_attack_3(PLW* wk, const Command_Attack_Args* p, s16 time,
                                                                    const SA_Term_Args* p_b) {
    const Pattern_Step script[5] = { [0] = STEP(Jump_Attack_Term, -0x7FA0, -0x7FC0, 9, 0x40, 0, -0x7FB0, -1, 0x200),
                                     [1] = STEP(Normal_Attack, 9, 0x40),
                                     [2] = STEP_WITH(Command_Attack, p),
                                     [3] = STEP(Wait, time),
                                     [4] = STEP_WITH(SA_Term, p_b) };
    Run_Pattern(wk, script, 5);
}

void active_pattern_search_back_term_command_attack_sa_term(PLW* wk, s16 move_value, s16 next_menu,
                                                            const Command_Attack_Args* p) {
    const Pattern_Step script[5] = { [0] = STEP(Search_Back_Term, move_value, 2, next_menu),
                                     [1] = STEP_WITH(Command_Attack, p),
                                     [2] = STEP(SA_Term, 0x34, 0x34, 0x34, 0x47),
                                     [3] = STEP(EM_Term, -0x7FB0, -1, 5, 6, 1),
                                     [4] = STEP(J_Command_Attack, 8, 0x1E, 8, -1) };
    Run_Pattern(wk, script, 5);
}

void active_pattern_search_back_term_hi_jump_attack_term_pierce_on(PLW* wk) {
    const Pattern_Step script[5] = { [0] = STEP(Search_Back_Term, 0x70, 2, 0x11),
                                     [1] = STEP(Hi_Jump_Attack_Term, -0x7FA0, -0x7FC0, 8, 0x20, 1, -0x7FA0, 8, 0x200),
                                     [2] = STEP_NOARG(Pierce_On),
                                     [3] = STEP(Command_Attack, 8, 0, 0xB, -1),
                                     [4] = STEP(Com_Random_Select, &Branch_Menu_2_18_18_11_11, 0) };
    Run_Pattern(wk, script, 5);
}

void active_pattern_search_back_term_jump_attack_term_pierce_on(PLW* wk) {
    const Pattern_Step script[5] = { [0] = STEP(Search_Back_Term, 0x70, 2, 0),
                                     [1] = STEP(Jump_Attack_Term, -0x7FA0, -0x7FC0, 8, 0x200, 0, -1, -1, -1),
                                     [2] = STEP_NOARG(Pierce_On),
                                     [3] = STEP(Command_Attack, 8, 0, 0xB, -1),
                                     [4] = STEP(Com_Random_Select, &Branch_Menu_2_18_18_11_11, 0) };
    Run_Pattern(wk, script, 5);
}

void active_pattern_search_back_term_pierce_on_command_attack_2(PLW* wk) {
    const Pattern_Step script[5] = { [0] = STEP(Search_Back_Term, 0x70, 2, 0x11),
                                     [1] = STEP_NOARG(Pierce_On),
                                     [2] = STEP(Command_Attack, 8, 1, 0xB, -1),
                                     [3] = STEP(Command_Attack, 8, 0, 0xB, -1),
                                     [4] = STEP(Com_Random_Select, &Branch_Menu_2_18_18_11_11, 0) };
    Run_Pattern(wk, script, 5);
}

void active_pattern_search_back_term_walk_wait_2(PLW* wk) {
    const Pattern_Step script[5] = { [0] = STEP(Search_Back_Term, 0x20, 2, 0x1B),
                                     [1] = STEP(Walk, 1, 0x18, 0),
                                     [2] = STEP(Wait, 8),
                                     [3] = STEP(Search_Back_Term, 0x30, 2, 0x1B),
                                     [4] = STEP(Walk, 1, 0x20, 0) };
    Run_Pattern(wk, script, 5);
}

void active_pattern_walk_search_back_term_walk(PLW* wk) {
    const Pattern_Step script[5] = { [0] = STEP(Walk, 0, 0x20, 0),
                                     [1] = STEP(Search_Back_Term, 0x30, 2, 6),
                                     [2] = STEP(Walk, 1, 0x28, 0),
                                     [3] = STEP(Wait, 8),
                                     [4] = STEP(Walk, 0, 0x20, 0) };
    Run_Pattern(wk, script, 5);
}

void pattern_approach_walk_em_term_normal_attack(PLW* wk, s16 target_pos, const SA_Term_Args* p,
                                                 const Command_Attack_Args* p_b) {
    const Pattern_Step script[5] = { [0] = STEP(Approach_Walk, target_pos, 2),
                                     [1] = STEP(EM_Term, -1, -0x7FF8, 6, 1, -1),
                                     [2] = STEP(Normal_Attack, 0xC, 0x40),
                                     [3] = STEP_WITH(SA_Term, p),
                                     [4] = STEP_WITH(Command_Attack, p_b) };
    Run_Pattern(wk, script, 5);
}

void pattern_approach_walk_em_term_normal_attack_5(PLW* wk, s16 target_pos, const SA_Term_Args* p,
                                                   const Command_Attack_Args* p_b) {
    const Pattern_Step script[5] = { [0] = STEP(Approach_Walk, target_pos, 2),
                                     [1] = STEP(EM_Term, -1, -0x7FF8, 6, 1, -1),
                                     [2] = STEP(Normal_Attack, 0xC, 0x40),
                                     [3] = STEP_WITH(SA_Term, p),
                                     [4] = STEP_WITH(J_Command_Attack, p_b) };
    Run_Pattern(wk, script, 5);
}

void pattern_approach_walk_em_term_sa_term_2(PLW* wk) {
    const Pattern_Step script[5] = { [0] = STEP(Approach_Walk, 0x4B, 2),
                                     [1] = STEP(EM_Term, -1, -0x7FF8, 6, 1, -1),
                                     [2] = STEP(SA_Term, 0x2E, 0x2F, 0x30, 0),
                                     [3] = STEP(Command_Attack, 8, 0x1F, 10, -1),
                                     [4] = STEP(Com_Random_Select, &Branch_Menu_2_3_38_44_45, 1) };
    Run_Pattern(wk, script, 5);
}

void pattern_approach_walk_em_term_sa_term_3(PLW* wk, const SA_Term_Args* p) {
    const Pattern_Step script[5] = { [0] = STEP(Approach_Walk, 0x59, 2),
                                     [1] = STEP(EM_Term, -1, -0x7FD8, 6, 1, -1),
                                     [2] = STEP_WITH(SA_Term, p),
                                     [3] = STEP(Approach_Walk, 0x4F, 2),
                                     [4] = STEP(Command_Attack, 8, 0x1D, 0xA, -1) };
    Run_Pattern(wk, script, 5);
}

void pattern_approach_walk_em_term_search_back_term(PLW* wk, s16 target_pos, const Command_Attack_Args* p) {
    const Pattern_Step script[5] = { [0] = STEP(Approach_Walk, target_pos, 2),
                                     [1] = STEP(EM_Term, -1, -0x7FD0, 6, 1, -1),
                                     [2] = STEP(Search_Back_Term, 0x60, 1, -1),
                                     [3] = STEP(Command_Attack, 8, 1, -1, -1),
                                     [4] = STEP_WITH(J_Command_Attack, p) };
    Run_Pattern(wk, script, 5);
}

void pattern_approach_walk_jump_attack_term_normal_attack(PLW* wk, const Jump_Term_Args* a,
                                                          const Command_Attack_Args* p) {
    const Pattern_Step script[5] = { [0] = STEP(Approach_Walk, 0xB1, 2),
                                     [1] = STEP_WITH(Jump_Attack_Term, a),
                                     [2] = STEP(Normal_Attack, 9, 0x10),
                                     [3] = STEP(Normal_Attack, 8, 0x42),
                                     [4] = STEP_WITH(J_Command_Attack, p) };
    Run_Pattern(wk, script, 5);
}

void pattern_approach_walk_jump_attack_term_normal_attack_4(PLW* wk, const Command_Attack_Args* p) {
    const Pattern_Step script[5] = { [0] = STEP(Approach_Walk, 0xBF, 2),
                                     [1] = STEP(Jump_Attack_Term, -0x7FA8, -0x7FC8, 9, 0x400, 0, -0x7F80, -1, 0x400),
                                     [2] = STEP(Normal_Attack, 9, 0x220),
                                     [3] = STEP(Normal_Attack, 0xC, 0x202),
                                     [4] = STEP_WITH(Command_Attack, p) };
    Run_Pattern(wk, script, 5);
}

void pattern_approach_walk_lever_attack_sa_term_2(PLW* wk, s16 target_pos, u16 lever_data, const SA_Term_Args* p) {
    const Pattern_Step script[5] = { [0] = STEP(Approach_Walk, target_pos, 2),
                                     [1] = STEP(Lever_Attack, 0xC, 0, lever_data),
                                     [2] = STEP_WITH(SA_Term, p),
                                     [3] = STEP(J_Command_Attack, 8, 0x1C, 8, -1),
                                     [4] = STEP(J_Command_Attack, 8, 0x1E, 10, -1) };
    Run_Pattern(wk, script, 5);
}

void pattern_approach_walk_wait_get_up_normal_attack_2(PLW* wk) {
    const Pattern_Step script[5] = { [0] = STEP(Approach_Walk, 0x71, 2),
                                     [1] = STEP(Wait_Get_Up, 0, -1),
                                     [2] = STEP(Normal_Attack, 9, 0x10),
                                     [3] = STEP(Normal_Attack, 0xB, 0x20),
                                     [4] = STEP(Command_Attack, 8, 0x1E, 8, -1) };
    Run_Pattern(wk, script, 5);
}

void pattern_approach_walk_wait_get_up_normal_attack_4(PLW* wk, s16 target_pos, s16 reaction) {
    const Pattern_Step script[5] = { [0] = STEP(Approach_Walk, target_pos, 2),
                                     [1] = STEP(Wait_Get_Up, 3, -1),
                                     [2] = STEP(Normal_Attack, 8, 0x102),
                                     [3] = STEP(Normal_Attack, reaction, 0x202),
                                     [4] = STEP(Normal_Attack, 8, 0x402) };
    Run_Pattern(wk, script, 5);
}

void pattern_em_term_sa_term_em_term(PLW* wk, const EM_Term_Params* p, const EM_Term_Params* p_b,
                                     const Command_Attack_Args* p_b_b) {
    const Pattern_Step script[5] = { [0] = STEP_WITH(EM_Term, p),
                                     [1] = STEP(SA_Term, 0xFFFF, 0x2F, 0xFFFF, 0),
                                     [2] = STEP_WITH(EM_Term, p_b),
                                     [3] = STEP(SA_Term, 0x2E, 0xFFFF, 0xFFFF, 0),
                                     [4] = STEP_WITH(Command_Attack, p_b_b) };
    Run_Pattern(wk, script, 5);
}

void pattern_hi_jump_attack_term_normal_attack_com_random_select(PLW* wk, s16 reaction, s16 reaction_b) {
    const Pattern_Step script[5] = { [0] = STEP(Hi_Jump_Attack_Term, -0x7FA0, -1, 8, 0x8400, 0, -0x7FA0, -1, 0x40),
                                     [1] = STEP(Normal_Attack, reaction, 0x10),
                                     [2] = STEP(Normal_Attack, 8, 0x20),
                                     [3] = STEP(Normal_Attack, reaction_b, 0x40),
                                     [4] = STEP(Com_Random_Select, &Branch_Menu_6_37_37_27_27, 0) };
    Run_Pattern(wk, script, 5);
}

void pattern_jump_attack_term_normal_attack_com_random_select(PLW* wk, const Jump_Term_Args* a,
                                                              const Branch_Menu_Args* p, s16 rnd_type) {
    const Pattern_Step script[5] = { [0] = STEP_WITH(Jump_Attack_Term, a),
                                     [1] = STEP(Normal_Attack, 9, 0x12),
                                     [2] = STEP(Normal_Attack, 9, 0x102),
                                     [3] = STEP(Normal_Attack, 8, 0x202),
                                     [4] = STEP(Com_Random_Select, p, rnd_type) };
    Run_Pattern(wk, script, 5);
}

void pattern_jump_attack_term_normal_attack_command_attack_5(PLW* wk, const Jump_Term_Args* a,
                                                             const Command_Attack_Args* p, const SA_Term_Args* p_b) {
    const Pattern_Step script[5] = { [0] = STEP_WITH(Jump_Attack_Term, a),
                                     [1] = STEP(Normal_Attack, 9, 0x202),
                                     [2] = STEP_WITH(Command_Attack, p),
                                     [3] = STEP(Wait, 5),
                                     [4] = STEP_WITH(SA_Term, p_b) };
    Run_Pattern(wk, script, 5);
}

void pattern_jump_attack_term_normal_attack_command_attack_6(PLW* wk, const Jump_Term_Args* a,
                                                             const Command_Attack_Args* p) {
    const Pattern_Step script[5] = { [0] = STEP_WITH(Jump_Attack_Term, a),
                                     [1] = STEP(Normal_Attack, 9, 0x40),
                                     [2] = STEP_WITH(Command_Attack, p),
                                     [3] = STEP(Wait, 5),
                                     [4] = STEP(SA_Term, 0x30, 0x31, 0x32, 0) };
    Run_Pattern(wk, script, 5);
}

void pattern_jump_attack_term_normal_attack_j_command_attack(PLW* wk, const Jump_Term_Args* a,
                                                             const Command_Attack_Args* p, const SA_Term_Args* p_b) {
    const Pattern_Step script[5] = { [0] = STEP_WITH(Jump_Attack_Term, a),
                                     [1] = STEP(Normal_Attack, 9, 0x40),
                                     [2] = STEP_WITH(J_Command_Attack, p),
                                     [3] = STEP(Wait, 5),
                                     [4] = STEP_WITH(SA_Term, p_b) };
    Run_Pattern(wk, script, 5);
}

void pattern_normal_attack_command_attack_wait_2(PLW* wk, u16 lever_data, s16 reaction) {
    const Pattern_Step script[5] = { [0] = STEP(Normal_Attack, 9, lever_data),
                                     [1] = STEP(Normal_Attack, reaction, 0x202),
                                     [2] = STEP(Command_Attack, 0xC, 0x1F, 10, -1),
                                     [3] = STEP(Wait, 1),
                                     [4] = STEP(SA_Term, 0x2F, 0x30, 0x31, 0x7F) };
    Run_Pattern(wk, script, 5);
}

void pattern_normal_attack_j_command_attack_com_random_select(PLW* wk) {
    const Pattern_Step script[5] = { [0] = STEP(Normal_Attack, 8, 0x10),
                                     [1] = STEP(Normal_Attack, 8, 0x10),
                                     [2] = STEP(Normal_Attack, 0xB, 0x200),
                                     [3] = STEP(J_Command_Attack, 8, 0x1E, 0xA, -1),
                                     [4] = STEP(Com_Random_Select, &Branch_Menu_6_2D_FF_FF_FF, 2) };
    Run_Pattern(wk, script, 5);
}

void pattern_normal_attack_jump_attack_term_normal_attack(PLW* wk, const SA_Term_Args* p) {
    const Pattern_Step script[5] = { [0] = STEP(Normal_Attack, 9, 0x100),
                                     [1] = STEP(Jump_Attack_Term, -0x7FA8, -0x7FC0, 9, 0x200, 0, -0x7FB0, -1, 0x20),
                                     [2] = STEP(Normal_Attack, 0xB, 0x12),
                                     [3] = STEP_WITH(SA_Term, p),
                                     [4] = STEP(Normal_Attack, 8, 0x402) };
    Run_Pattern(wk, script, 5);
}

void pattern_pierce_on_command_attack_normal_attack_4(PLW* wk) {
    const Pattern_Step script[5] = { [0] = STEP_NOARG(Pierce_On),
                                     [1] = STEP(Command_Attack, 8, 0, -1, -1),
                                     [2] = STEP(Normal_Attack, 9, 0x102),
                                     [3] = STEP(Normal_Attack, 9, 0x202),
                                     [4] = STEP(Normal_Attack, 8, 0x402) };
    Run_Pattern(wk, script, 5);
}

void pattern_pierce_on_command_attack_wait_2(PLW* wk, const Command_Attack_Args* p) {
    const Pattern_Step script[5] = { [0] = STEP_NOARG(Pierce_On),
                                     [1] = STEP(Command_Attack, 0xe, 0x1e, 10, -1),
                                     [2] = STEP(Command_Attack, 0xe, 0x1e, 10, -1),
                                     [3] = STEP(Wait, 0xe),
                                     [4] = STEP_WITH(Command_Attack, p) };
    Run_Pattern(wk, script, 5);
}

void pattern_pierce_on_em_term_normal_attack(PLW* wk, const EM_Term_Params* p, s16 reaction, u16 lever_data) {
    const Pattern_Step script[5] = { [0] = STEP_NOARG(Pierce_On),
                                     [1] = STEP_WITH(EM_Term, p),
                                     [2] = STEP(Normal_Attack, reaction, 0x42),
                                     [3] = STEP(Wait, 5),
                                     [4] = STEP(Normal_Attack, 8, lever_data) };
    Run_Pattern(wk, script, 5);
}
