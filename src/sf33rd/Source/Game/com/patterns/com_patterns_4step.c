/**
 * @file com_patterns_4step.c
 * COM: pattern skeletons shared by every character
 *
 * The four-step patterns. Part 1 of 3, in name order.
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

void pattern_approach_walk_jump_attack_term_normal_attack_5(PLW* wk, s16 option, s16 reaction,
                                                            const Command_Attack_Args* p) {
    const Pattern_Step script[4] = { [0] = STEP(Approach_Walk, 0xBF, option),
                                     [1] = STEP(Jump_Attack_Term, -0x7FA8, -0x7FC8, 0xB, 0x400, 0, -0x7F80, -1, 0x400),
                                     [2] = STEP(Normal_Attack, reaction, 0x202),
                                     [3] = STEP_WITH(Command_Attack, p) };
    Run_Pattern(wk, script, 4);
}

void active_pattern_adjust_attack_command_attack_2(PLW* wk, const Command_Attack_Args* p) {
    const Pattern_Step script[4] = { [0] = STEP(Adjust_Attack, 9, 0x10),
                                     [1] = STEP(Adjust_Attack, 0xC, 0x20),
                                     [2] = STEP(Adjust_Attack, 8, 0x40),
                                     [3] = STEP_WITH(Command_Attack, p) };
    Run_Pattern(wk, script, 4);
}

void active_pattern_adjust_attack_lever_attack(PLW* wk) {
    const Pattern_Step script[4] = { [0] = STEP(Adjust_Attack, 9, 0x100),
                                     [1] = STEP(Adjust_Attack, 0xC, 0x100),
                                     [2] = STEP(Adjust_Attack, 0xC, 0x202),
                                     [3] = STEP(Lever_Attack, 8, 0, 0x200) };
    Run_Pattern(wk, script, 4);
}

void active_pattern_approach_walk_jump_attack_term_normal_attack(PLW* wk, s16 option) {
    pattern_approach_walk_jump_attack_term_normal_attack_5(
        wk, option, 0xB, &(Command_Attack_Args) { 0xC, 0x1F, 0xA, -1 });
}

void active_pattern_approach_walk_normal_attack_sa_term(PLW* wk, s16 target_pos, const SA_Term_Args* p,
                                                        const Command_Attack_Args* p_b) {
    const Pattern_Step script[4] = { [0] = STEP(Approach_Walk, target_pos, 2),
                                     [1] = STEP(Normal_Attack, 0xC, 0x40),
                                     [2] = STEP_WITH(SA_Term, p),
                                     [3] = STEP_WITH(J_Command_Attack, p_b) };
    Run_Pattern(wk, script, 4);
}

void active_pattern_approach_walk_pierce_on_command_attack(PLW* wk) {
    const Pattern_Step script[4] = { [0] = STEP(Approach_Walk, 0x58, 2),
                                     [1] = STEP_NOARG(Pierce_On),
                                     [2] = STEP(Command_Attack, 0xB, 0x21, 0xA, -1),
                                     [3] = STEP(Command_Attack, 8, 0x1E, 0xA, -1) };
    Run_Pattern(wk, script, 4);
}

void active_pattern_approach_walk_turn_over_on_jump_attack_term(PLW* wk, const Branch_Menu_Args* p) {
    const Pattern_Step script[4] = { [0] = STEP(Approach_Walk, 0x57, 3),
                                     [1] = STEP_NOARG(Turn_Over_On),
                                     [2] = STEP(Jump_Attack_Term, -1, 0x49, 9, 0x202, 0, -0x7F80, -1, 0x40),
                                     [3] = STEP(Com_Random_Select, p, 0) };
    Run_Pattern(wk, script, 4);
}

void active_pattern_command_attack_check_sa_command_attack(PLW* wk, const Command_Attack_Args* p) {
    const Pattern_Step script[4] = { [0] = STEP_WITH(Command_Attack, p),
                                     [1] = STEP(Check_SA, 2, 0x35),
                                     [2] = STEP(Command_Attack, 8, 0x8016, 8, -1),
                                     [3] = STEP(Command_Attack, 8, 0x1E, 8, -1) };
    Run_Pattern(wk, script, 4);
}

void active_pattern_command_attack_sa_term_em_term(PLW* wk, const Command_Attack_Args* p) {
    const Pattern_Step script[4] = { [0] = STEP_WITH(Command_Attack, p),
                                     [1] = STEP(SA_Term, 0x34, 0x34, 0x34, 0x47),
                                     [2] = STEP(EM_Term, -0x7FB0, -1, 5, 6, 1),
                                     [3] = STEP(J_Command_Attack, 8, 0x1E, 8, -1) };
    Run_Pattern(wk, script, 4);
}

void active_pattern_command_attack_turn_over_on_jump_attack_term(PLW* wk, const Branch_Menu_Args* p) {
    const Pattern_Step script[4] = { [0] = STEP(Command_Attack, 8, 1, -1, -1),
                                     [1] = STEP_NOARG(Turn_Over_On),
                                     [2] = STEP(Jump_Attack_Term, -1, 0x49, 9, 0x202, 0, -0x7F80, -1, 0x40),
                                     [3] = STEP(Com_Random_Select, p, 0) };
    Run_Pattern(wk, script, 4);
}

void active_pattern_lever_on_normal_attack_command_attack(PLW* wk, u16 lever_data, u16 lever_data_b,
                                                          const Command_Attack_Args* p) {
    const Pattern_Step script[4] = { [0] = STEP(Lever_On, 1, 0xFFFF),
                                     [1] = STEP(Normal_Attack, 8, lever_data),
                                     [2] = STEP(Normal_Attack, 8, lever_data_b),
                                     [3] = STEP_WITH(Command_Attack, p) };
    Run_Pattern(wk, script, 4);
}

void active_pattern_normal_attack_sa_term_approach_walk(PLW* wk, u16 lever_data, u16 lever) {
    const Pattern_Step script[4] = { [0] = STEP(Normal_Attack, 9, lever_data),
                                     [1] = STEP(SA_Term, 0x34, 0x34, 0x34, 0x7F),
                                     [2] = STEP(Approach_Walk, 0x10, 2),
                                     [3] = STEP(Lever_Attack, 8, lever, 0x110) };
    Run_Pattern(wk, script, 4);
}

void active_pattern_pierce_on_approach_walk_jump_command_attack_term(PLW* wk, const JCA_Term_Args* a) {
    const Pattern_Step script[4] = { [0] = STEP_NOARG(Pierce_On),
                                     [1] = STEP(Approach_Walk, 0xBF, 2),
                                     [2] = STEP_WITH(Jump_Command_Attack_Term, a),
                                     [3] = STEP(J_Command_Attack, 8, 0x1E, 8, -1) };
    Run_Pattern(wk, script, 4);
}

void active_pattern_pierce_on_command_attack_2(PLW* wk, const Command_Attack_Args* p, const Command_Attack_Args* p_b,
                                               const Command_Attack_Args* p_b_b) {
    const Pattern_Step script[4] = { [0] = STEP_NOARG(Pierce_On),
                                     [1] = STEP_WITH(Command_Attack, p),
                                     [2] = STEP_WITH(Command_Attack, p_b),
                                     [3] = STEP_WITH(Command_Attack, p_b_b) };
    Run_Pattern(wk, script, 4);
}

void active_pattern_pierce_on_search_back_term_command_attack(PLW* wk) {
    const Pattern_Step script[4] = { [0] = STEP_NOARG(Pierce_On),
                                     [1] = STEP(Search_Back_Term, 0x60, 2, 0x12),
                                     [2] = STEP(Command_Attack, 8, 1, 0xB, -1),
                                     [3] = STEP(J_Command_Attack, 8, 0x1D, 0xA, -1) };
    Run_Pattern(wk, script, 4);
}

void active_pattern_search_back_term_pierce_on_command_attack_3(PLW* wk) {
    const Pattern_Step script[4] = { [0] = STEP(Search_Back_Term, 0x70, 2, 0),
                                     [1] = STEP_NOARG(Pierce_On),
                                     [2] = STEP(Command_Attack, 8, 1, 0xB, -1),
                                     [3] = STEP(Hi_Jump_Attack_Term, -0x7FA0, -1, 8, 0x8400, 0, -0x7FA0, -1, 0x8400) };
    Run_Pattern(wk, script, 4);
}

void pattern_approach_walk_command_attack_com_random_select(PLW* wk, s16 target_pos, const Command_Attack_Args* p) {
    const Pattern_Step script[4] = { [0] = STEP(Approach_Walk, target_pos, 2),
                                     [1] = STEP_WITH(Command_Attack, p),
                                     [2] =
                                         STEP(Com_Random_Select, &(Branch_Menu_Args) { 6, 0x42, 0x46, 0x4A, 0x4A }, 1),
                                     [3] = STEP(Lever_Attack, 8, 0, 0x40) };
    Run_Pattern(wk, script, 4);
}

void pattern_approach_walk_em_term_command_attack_2(PLW* wk, s16 target_pos, const Command_Attack_Args* p,
                                                    const Branch_Menu_Args* p_b) {
    const Pattern_Step script[4] = { [0] = STEP(Approach_Walk, target_pos, 2),
                                     [1] = STEP(EM_Term, -1, -0x7FC0, 6, 1, -1),
                                     [2] = STEP_WITH(Command_Attack, p),
                                     [3] = STEP(Com_Random_Select, p_b, 1) };
    Run_Pattern(wk, script, 4);
}

void pattern_approach_walk_em_term_command_attack_3(PLW* wk, s16 target_pos, const Command_Attack_Args* p,
                                                    const SA_Term_Args* p_b) {
    const Pattern_Step script[4] = { [0] = STEP(Approach_Walk, target_pos, 2),
                                     [1] = STEP(EM_Term, -1, -0x7FC0, 6, 1, -1),
                                     [2] = STEP_WITH(Command_Attack, p),
                                     [3] = STEP_WITH(SA_Term, p_b) };
    Run_Pattern(wk, script, 4);
}

void pattern_approach_walk_em_term_command_attack_4(PLW* wk, const EM_Term_Params* p) {
    const Pattern_Step script[4] = { [0] = STEP(Approach_Walk, 0x4B, 2),
                                     [1] = STEP_WITH(EM_Term, p),
                                     [2] = STEP(Command_Attack, 8, 0x1F, 9, -1),
                                     [3] = STEP(Com_Random_Select, &Branch_Menu_2_3_38_44_45, 1) };
    Run_Pattern(wk, script, 4);
}

void pattern_approach_walk_em_term_j_command_attack_2(PLW* wk, const Command_Attack_Args* p, const SA_Term_Args* p_b) {
    const Pattern_Step script[4] = { [0] = STEP(Approach_Walk, 0x10, 2),
                                     [1] = STEP(EM_Term, -1, -0x7FE8, 6, 1, -1),
                                     [2] = STEP_WITH(J_Command_Attack, p),
                                     [3] = STEP_WITH(SA_Term, p_b) };
    Run_Pattern(wk, script, 4);
}

void pattern_approach_walk_em_term_lever_attack_2(PLW* wk, u16 lever) {
    const Pattern_Step script[4] = { [0] = STEP(Approach_Walk, 0x3B, 2),
                                     [1] = STEP(EM_Term, -1, -0x7FF8, 6, 1, -1),
                                     [2] = STEP(Lever_Attack, 8, lever, 0x110),
                                     [3] = STEP(Normal_Attack, 8, 0x402) };
    Run_Pattern(wk, script, 4);
}

void pattern_approach_walk_em_term_normal_attack_3(PLW* wk, s16 target_pos, const EM_Term_Params* p,
                                                   const Command_Attack_Args* p_b) {
    const Pattern_Step script[4] = { [0] = STEP(Approach_Walk, target_pos, 2),
                                     [1] = STEP_WITH(EM_Term, p),
                                     [2] = STEP(Normal_Attack, 0xC, 0x40),
                                     [3] = STEP_WITH(Command_Attack, p_b) };
    Run_Pattern(wk, script, 4);
}

void pattern_approach_walk_em_term_normal_attack_6(PLW* wk, const EM_Term_Params* p, u16 lever_data,
                                                   const Command_Attack_Args* p_b) {
    const Pattern_Step script[4] = { [0] = STEP(Approach_Walk, 0x47, 2),
                                     [1] = STEP_WITH(EM_Term, p),
                                     [2] = STEP(Normal_Attack, 0xC, lever_data),
                                     [3] = STEP_WITH(J_Command_Attack, p_b) };
    Run_Pattern(wk, script, 4);
}

void pattern_approach_walk_em_term_sa_term(PLW* wk, s16 target_pos, const SA_Term_Args* p,
                                           const Command_Attack_Args* p_b) {
    const Pattern_Step script[4] = { [0] = STEP(Approach_Walk, target_pos, 2),
                                     [1] = STEP(EM_Term, -1, -0x7FD0, 6, 1, -1),
                                     [2] = STEP_WITH(SA_Term, p),
                                     [3] = STEP_WITH(J_Command_Attack, p_b) };
    Run_Pattern(wk, script, 4);
}

void pattern_approach_walk_em_term_sa_term_5(PLW* wk, s16 target_pos, const SA_Term_Args* p) {
    const Pattern_Step script[4] = { [0] = STEP(Approach_Walk, target_pos, 2),
                                     [1] = STEP(EM_Term, -1, -0x7FF8, 6, 1, -1),
                                     [2] = STEP_WITH(SA_Term, p),
                                     [3] = STEP(Command_Attack, 8, 0x1C, 10, -1) };
    Run_Pattern(wk, script, 4);
}

void pattern_approach_walk_jump_attack_term_normal_attack_2(PLW* wk, s16 option, const Command_Attack_Args* p) {
    pattern_approach_walk_jump_attack_term_normal_attack_5(wk, option, 0xC, p);
}

void pattern_approach_walk_lever_attack_sa_term(PLW* wk, s16 target_pos, u16 lever, const SA_Term_Args* p) {
    const Pattern_Step script[4] = { [0] = STEP(Approach_Walk, target_pos, 2),
                                     [1] = STEP(Lever_Attack, 0xC, lever, 0x200),
                                     [2] = STEP_WITH(SA_Term, p),
                                     [3] = STEP(Normal_Attack, 8, 0x402) };
    Run_Pattern(wk, script, 4);
}

void pattern_approach_walk_normal_attack(PLW* wk, s16 target_pos) {
    const Pattern_Step script[4] = { [0] = STEP(Approach_Walk, target_pos, 2),
                                     [1] = STEP(Normal_Attack, 9, 0x10),
                                     [2] = STEP(Normal_Attack, 9, 0x20),
                                     [3] = STEP(Normal_Attack, 8, 0x402) };
    Run_Pattern(wk, script, 4);
}

void pattern_approach_walk_normal_attack_lever_attack(PLW* wk, s16 target_pos, u16 lever, u16 lever_data) {
    const Pattern_Step script[4] = { [0] = STEP(Approach_Walk, target_pos, 2),
                                     [1] = STEP(Normal_Attack, 9, 0x10),
                                     [2] = STEP(Lever_Attack, 9, lever, lever_data),
                                     [3] = STEP(Normal_Attack, 8, 0x402) };
    Run_Pattern(wk, script, 4);
}

void pattern_approach_walk_normal_attack_sa_term(PLW* wk, s16 target_pos, const SA_Term_Args* p,
                                                 const Command_Attack_Args* p_b) {
    const Pattern_Step script[4] = { [0] = STEP(Approach_Walk, target_pos, 2),
                                     [1] = STEP(Normal_Attack, 9, 0x100),
                                     [2] = STEP_WITH(SA_Term, p),
                                     [3] = STEP_WITH(Command_Attack, p_b) };
    Run_Pattern(wk, script, 4);
}

void pattern_approach_walk_normal_attack_sa_term_2(PLW* wk, s16 target_pos, const SA_Term_Args* p,
                                                   const Command_Attack_Args* p_b) {
    const Pattern_Step script[4] = { [0] = STEP(Approach_Walk, target_pos, 2),
                                     [1] = STEP(Normal_Attack, 0xC, 0x20),
                                     [2] = STEP_WITH(SA_Term, p),
                                     [3] = STEP_WITH(Command_Attack, p_b) };
    Run_Pattern(wk, script, 4);
}

void pattern_approach_walk_normal_attack_sa_term_3(PLW* wk, s16 target_pos, const SA_Term_Args* p,
                                                   const Command_Attack_Args* p_b) {
    const Pattern_Step script[4] = { [0] = STEP(Approach_Walk, target_pos, 2),
                                     [1] = STEP(Normal_Attack, 0xC, 0x20),
                                     [2] = STEP_WITH(SA_Term, p),
                                     [3] = STEP_WITH(J_Command_Attack, p_b) };
    Run_Pattern(wk, script, 4);
}

void pattern_approach_walk_sa_term_command_attack(PLW* wk, s16 target_pos, const Command_Attack_Args* p) {
    const Pattern_Step script[4] = { [0] = STEP(Approach_Walk, target_pos, 2),
                                     [1] = STEP(SA_Term, 0x2E, 0x2F, 0xFFFF, 0),
                                     [2] = STEP_WITH(Command_Attack, p),
                                     [3] = STEP(Com_Random_Select, &Branch_Menu_2_3_38_44_45, 1) };
    Run_Pattern(wk, script, 4);
}

void pattern_approach_walk_wait_get_up_em_term(PLW* wk, u16 lever_data) {
    const Pattern_Step script[4] = { [0] = STEP(Approach_Walk, 0x7F, 2),
                                     [1] = STEP(Wait_Get_Up, 0, -1),
                                     [2] = STEP(EM_Term, -0x7FB0, -1, 5, 6, 0x1C),
                                     [3] = STEP(Lever_Attack, 8, 0, lever_data) };
    Run_Pattern(wk, script, 4);
}

void pattern_approach_walk_wait_get_up_normal_attack_3(PLW* wk, u16 lever_data) {
    const Pattern_Step script[4] = { [0] = STEP(Approach_Walk, 0x71, 2),
                                     [1] = STEP(Wait_Get_Up, 3, -1),
                                     [2] = STEP(Normal_Attack, 0xB, 0x20),
                                     [3] = STEP(Normal_Attack, 8, lever_data) };
    Run_Pattern(wk, script, 4);
}

void pattern_approach_walk_wait_get_up_sa_term(PLW* wk, s16 target_pos, const SA_Term_Args* p,
                                               const Command_Attack_Args* p_b) {
    const Pattern_Step script[4] = { [0] = STEP(Approach_Walk, target_pos, 2),
                                     [1] = STEP(Wait_Get_Up, 3, -1),
                                     [2] = STEP_WITH(SA_Term, p),
                                     [3] = STEP_WITH(Command_Attack, p_b) };
    Run_Pattern(wk, script, 4);
}

void pattern_approach_walk_wait_get_up_sa_term_com_random_select(PLW* wk, s16 target_pos, const SA_Term_Args* p,
                                                                 const Com_Random_Select_Step* com_random_select) {
    const Pattern_Step script[4] = { [0] = STEP(Approach_Walk, target_pos, 2),
                                     [1] = STEP(Wait_Get_Up, 3, 0),
                                     [2] = STEP_WITH(SA_Term, p),
                                     [3] = STEP_WITH(Com_Random_Select, com_random_select) };
    Run_Pattern(wk, script, 4);
}

void pattern_approach_walk_wait_get_up_normal_attack_5(PLW* wk) {
    const Pattern_Step script[4] = { [0] = STEP(Approach_Walk, 0x71, 2),
                                     [1] = STEP(Wait_Get_Up, 3, -1),
                                     [2] = STEP(Normal_Attack, 9, 0x12),
                                     [3] = STEP(Normal_Attack, 0xB, 0x202) };
    Run_Pattern(wk, script, 4);
}

void pattern_shell_term_jump_attack_term_normal_attack_2(PLW* wk, const Command_Attack_Args* p) {
    const Pattern_Step script[4] = { [0] = STEP(SHELL_Term, 0, 2, 1, -1, -1),
                                     [1] = STEP(Jump_Attack_Term, -0x7FA8, -0x7FD0, 9, 0x200, 0, -0x7FB0, -1, 0x200),
                                     [2] = STEP(Normal_Attack, 0xB, 0x20),
                                     [3] = STEP_WITH(J_Command_Attack, p) };
    Run_Pattern(wk, script, 4);
}

void pattern_shell_term_jump_attack_term_normal_attack_3(PLW* wk, const Jump_Term_Args* a, u16 lever_data) {
    const Pattern_Step script[4] = { [0] = STEP(SHELL_Term, 0, 2, 1, -1, -1),
                                     [1] = STEP_WITH(Jump_Attack_Term, a),
                                     [2] = STEP(Normal_Attack, 0xB, 0x20),
                                     [3] = STEP(Normal_Attack, 8, lever_data) };
    Run_Pattern(wk, script, 4);
}
