/**
 * @file com_patterns_2step.c
 * COM: pattern skeletons shared by every character
 *
 * The two-step patterns. Part 1 of 3, in name order.
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

void pattern_approach_walk_normal_attack_4(PLW* wk, s16 target_pos, s16 reaction, u16 lever_data) {
    const Pattern_Step script[2] = { [0] = STEP(Approach_Walk, target_pos, 2),
                                     [1] = STEP(Normal_Attack, reaction, lever_data) };
    Run_Pattern(wk, script, 2);
}

void pattern_em_term_adjust_attack_2(PLW* wk, const EM_Term_Params* p, u16 lever_data) {
    const Pattern_Step script[2] = { [0] = STEP_WITH(EM_Term, p), [1] = STEP(Adjust_Attack, 8, lever_data) };
    Run_Pattern(wk, script, 2);
}

void pattern_etc_term_provoke_2(PLW* wk, s16 exit_no, u32 next_action, u16 next_menu) {
    const Pattern_Step script[2] = { [0] = STEP(ETC_Term, exit_no, next_action, next_menu), [1] = STEP(Provoke, -1) };
    Run_Pattern(wk, script, 2);
}

void active_pattern_adjust_attack_3(PLW* wk, u16 lever_data) {
    const Pattern_Step script[2] = { [0] = STEP(Adjust_Attack, 9, 0x100), [1] = STEP(Adjust_Attack, 8, lever_data) };
    Run_Pattern(wk, script, 2);
}

void active_pattern_adjust_attack_4(PLW* wk, s16 reaction, s16 reaction_b, u16 lever_data) {
    const Pattern_Step script[2] = { [0] = STEP(Adjust_Attack, reaction, 0x10),
                                     [1] = STEP(Adjust_Attack, reaction_b, lever_data) };
    Run_Pattern(wk, script, 2);
}

void active_pattern_adjust_attack_branch_unit_area(PLW* wk, u16 lever_data, const Branch_Menu_Args* p) {
    const Pattern_Step script[2] = { [0] = STEP(Adjust_Attack, 8, lever_data), [1] = STEP_WITH(Branch_Unit_Area, p) };
    Run_Pattern(wk, script, 2);
}

void active_pattern_adjust_attack_command_attack(PLW* wk, s16 reaction, u16 lever_data, const Command_Attack_Args* p) {
    const Pattern_Step script[2] = { [0] = STEP(Adjust_Attack, reaction, lever_data),
                                     [1] = STEP_WITH(Command_Attack, p) };
    Run_Pattern(wk, script, 2);
}

void active_pattern_adjust_attack_j_command_attack(PLW* wk, s16 reaction, u16 lever_data,
                                                   const Command_Attack_Args* p) {
    const Pattern_Step script[2] = { [0] = STEP(Adjust_Attack, reaction, lever_data),
                                     [1] = STEP_WITH(J_Command_Attack, p) };
    Run_Pattern(wk, script, 2);
}

void active_pattern_adjust_attack_lever_attack_2(PLW* wk, s16 reaction, u16 lever_data, u16 lever) {
    const Pattern_Step script[2] = { [0] = STEP(Adjust_Attack, reaction, lever_data),
                                     [1] = STEP(Lever_Attack, 8, lever, 0x20) };
    Run_Pattern(wk, script, 2);
}

void active_pattern_adjust_attack_normal_attack(PLW* wk, s16 reaction, u16 lever_data, u16 lever_data_b) {
    const Pattern_Step script[2] = { [0] = STEP(Adjust_Attack, reaction, lever_data),
                                     [1] = STEP(Normal_Attack, 8, lever_data_b) };
    Run_Pattern(wk, script, 2);
}

void active_pattern_approach_walk_com_random_select(PLW* wk, s16 target_pos, const Branch_Menu_Args* p) {
    pattern_approach_walk_com_random_select(wk, target_pos, p, 1);
}

void active_pattern_approach_walk_com_random_select_2(PLW* wk, s16 target_pos, s16 option, const Branch_Menu_Args* p) {
    const Pattern_Step script[2] = { [0] = STEP(Approach_Walk, target_pos, option),
                                     [1] = STEP(Com_Random_Select, p, 0) };
    Run_Pattern(wk, script, 2);
}

void active_pattern_approach_walk_command_attack(PLW* wk, s16 target_pos, const Command_Attack_Args* p) {
    const Pattern_Step script[2] = { [0] = STEP(Approach_Walk, target_pos, 2), [1] = STEP_WITH(Command_Attack, p) };
    Run_Pattern(wk, script, 2);
}

void active_pattern_approach_walk_normal_attack(PLW* wk, s16 target_pos, u16 lever_data) {
    pattern_approach_walk_normal_attack_4(wk, target_pos, 8, lever_data);
}

void active_pattern_check_sa_command_attack(PLW* wk, s16 next_action, s16 next_menu, const Command_Attack_Args* p) {
    const Pattern_Step script[2] = { [0] = STEP(Check_SA, next_action, next_menu), [1] = STEP_WITH(Command_Attack, p) };
    Run_Pattern(wk, script, 2);
}

void active_pattern_command_attack_2(PLW* wk, const Command_Attack_Args* p, const Command_Attack_Args* p_b) {
    const Pattern_Step script[2] = { [0] = STEP_WITH(Command_Attack, p), [1] = STEP_WITH(Command_Attack, p_b) };
    Run_Pattern(wk, script, 2);
}

void active_pattern_command_attack_com_random_select(PLW* wk, const Command_Attack_Args* p, const Branch_Menu_Args* p_b,
                                                     s16 rnd_type) {
    const Pattern_Step script[2] = { [0] = STEP_WITH(Command_Attack, p), [1] = STEP(Com_Random_Select, p_b, rnd_type) };
    Run_Pattern(wk, script, 2);
}

void active_pattern_command_attack_j_command_attack(PLW* wk, const Command_Attack_Args* p,
                                                    const Command_Attack_Args* p_b) {
    const Pattern_Step script[2] = { [0] = STEP_WITH(Command_Attack, p), [1] = STEP_WITH(J_Command_Attack, p_b) };
    Run_Pattern(wk, script, 2);
}

void active_pattern_command_attack_jump_attack(PLW* wk, const Command_Attack_Args* p, const Jump_Attack_Args* a) {
    const Pattern_Step script[2] = { [0] = STEP_WITH(Command_Attack, p), [1] = STEP_WITH(Jump_Attack, a) };
    Run_Pattern(wk, script, 2);
}

void active_pattern_command_attack_lever_attack(PLW* wk, const Command_Attack_Args* p, u16 lever, u16 lever_data) {
    const Pattern_Step script[2] = { [0] = STEP_WITH(Command_Attack, p),
                                     [1] = STEP(Lever_Attack, 8, lever, lever_data) };
    Run_Pattern(wk, script, 2);
}

void active_pattern_command_attack_look(PLW* wk) {
    const Pattern_Step script[2] = { [0] = STEP(Command_Attack, 8, 0, 0xB, -1), [1] = STEP(Look, 0) };
    Run_Pattern(wk, script, 2);
}

void active_pattern_command_attack_normal_attack(PLW* wk, const Command_Attack_Args* p, s16 reaction, u16 lever_data) {
    const Pattern_Step script[2] = { [0] = STEP_WITH(Command_Attack, p),
                                     [1] = STEP(Normal_Attack, reaction, lever_data) };
    Run_Pattern(wk, script, 2);
}

void active_pattern_command_attack_push_shot(PLW* wk, const Command_Attack_Args* p, s16 power_level) {
    const Pattern_Step script[2] = { [0] = STEP_WITH(Command_Attack, p), [1] = STEP(Push_Shot, power_level) };
    Run_Pattern(wk, script, 2);
}

void active_pattern_em_term_adjust_attack(PLW* wk, const EM_Term_Params* p) {
    pattern_em_term_adjust_attack_2(wk, p, 0x10);
}

void active_pattern_em_term_command_attack(PLW* wk, const EM_Term_Params* p, const Command_Attack_Args* p_b) {
    const Pattern_Step script[2] = { [0] = STEP_WITH(EM_Term, p), [1] = STEP_WITH(Command_Attack, p_b) };
    Run_Pattern(wk, script, 2);
}

void active_pattern_em_term_j_command_attack(PLW* wk, const EM_Term_Params* p, const Command_Attack_Args* p_b) {
    const Pattern_Step script[2] = { [0] = STEP_WITH(EM_Term, p), [1] = STEP_WITH(J_Command_Attack, p_b) };
    Run_Pattern(wk, script, 2);
}

void active_pattern_em_term_lever_attack(PLW* wk, const EM_Term_Params* p, u16 lever, u16 lever_data) {
    const Pattern_Step script[2] = { [0] = STEP_WITH(EM_Term, p), [1] = STEP(Lever_Attack, 8, lever, lever_data) };
    Run_Pattern(wk, script, 2);
}

void active_pattern_em_term_normal_attack(PLW* wk, const EM_Term_Params* p, s16 reaction, u16 lever_data) {
    const Pattern_Step script[2] = { [0] = STEP_WITH(EM_Term, p), [1] = STEP(Normal_Attack, reaction, lever_data) };
    Run_Pattern(wk, script, 2);
}

void active_pattern_etc_term_command_attack(PLW* wk, u16 next_menu, const Command_Attack_Args* p) {
    const Pattern_Step script[2] = { [0] = STEP(ETC_Term, 0, 6, next_menu), [1] = STEP_WITH(Command_Attack, p) };
    Run_Pattern(wk, script, 2);
}

void active_pattern_etc_term_j_command_attack(PLW* wk, u16 next_menu, const Command_Attack_Args* p) {
    const Pattern_Step script[2] = { [0] = STEP(ETC_Term, 3, 2, next_menu), [1] = STEP_WITH(J_Command_Attack, p) };
    Run_Pattern(wk, script, 2);
}

void active_pattern_etc_term_provoke(PLW* wk, u32 next_action, u16 next_menu) {
    pattern_etc_term_provoke_2(wk, 5, next_action, next_menu);
}

void active_pattern_hi_jump_attack_term_com_random_select(PLW* wk) {
    const Pattern_Step script[2] = { [0] = STEP(Hi_Jump_Attack_Term, -0x7FA0, -0x7FC0, 8, 0x20, 0, -0x7FA0, 8, 0x200),
                                     [1] = STEP(Com_Random_Select, &Branch_Menu_2_18_18_11_11, 0) };
    Run_Pattern(wk, script, 2);
}

void active_pattern_j_command_attack_2(PLW* wk, const Command_Attack_Args* p, const Command_Attack_Args* p_b) {
    const Pattern_Step script[2] = { [0] = STEP_WITH(J_Command_Attack, p), [1] = STEP_WITH(J_Command_Attack, p_b) };
    Run_Pattern(wk, script, 2);
}

void active_pattern_jump_attack_term_command_attack(PLW* wk, const Jump_Term_Args* a, const Command_Attack_Args* p) {
    const Pattern_Step script[2] = { [0] = STEP_WITH(Jump_Attack_Term, a), [1] = STEP_WITH(Command_Attack, p) };
    Run_Pattern(wk, script, 2);
}

void active_pattern_jump_attack_term_j_command_attack(PLW* wk, const Jump_Term_Args* a, const Command_Attack_Args* p) {
    const Pattern_Step script[2] = { [0] = STEP_WITH(Jump_Attack_Term, a), [1] = STEP_WITH(J_Command_Attack, p) };
    Run_Pattern(wk, script, 2);
}

void active_pattern_jump_look(PLW* wk, s16 time) {
    const Pattern_Step script[2] = { [0] = STEP(Jump, time), [1] = STEP(Look, 0) };
    Run_Pattern(wk, script, 2);
}

void active_pattern_keep_away_com_random_select(PLW* wk, const Branch_Menu_Args* p) {
    const Pattern_Step script[2] = { [0] = STEP(Keep_Away, 0xBF, 1), [1] = STEP(Com_Random_Select, p, 3) };
    Run_Pattern(wk, script, 2);
}

void active_pattern_lever_off_look(PLW* wk) {
    const Pattern_Step script[2] = { [0] = STEP_NOARG(Lever_Off), [1] = STEP(Look, 0) };
    Run_Pattern(wk, script, 2);
}

void active_pattern_lever_on_look(PLW* wk) {
    const Pattern_Step script[2] = { [0] = STEP(Lever_On, 1, 2), [1] = STEP(Look, 0) };
    Run_Pattern(wk, script, 2);
}

void active_pattern_normal_attack_3(PLW* wk, u16 lever_data, s16 reaction, u16 lever_data_b) {
    const Pattern_Step script[2] = { [0] = STEP(Normal_Attack, 9, lever_data),
                                     [1] = STEP(Normal_Attack, reaction, lever_data_b) };
    Run_Pattern(wk, script, 2);
}

void active_pattern_normal_attack_branch_unit_area(PLW* wk, s16 reaction, u16 lever_data, const Branch_Menu_Args* p) {
    const Pattern_Step script[2] = { [0] = STEP(Normal_Attack, reaction, lever_data),
                                     [1] = STEP_WITH(Branch_Unit_Area, p) };
    Run_Pattern(wk, script, 2);
}

void active_pattern_normal_attack_command_attack(PLW* wk, s16 reaction, u16 lever_data, const Command_Attack_Args* p) {
    const Pattern_Step script[2] = { [0] = STEP(Normal_Attack, reaction, lever_data),
                                     [1] = STEP_WITH(Command_Attack, p) };
    Run_Pattern(wk, script, 2);
}

void active_pattern_normal_attack_j_command_attack(PLW* wk, s16 reaction, u16 lever_data,
                                                   const Command_Attack_Args* p) {
    const Pattern_Step script[2] = { [0] = STEP(Normal_Attack, reaction, lever_data),
                                     [1] = STEP_WITH(J_Command_Attack, p) };
    Run_Pattern(wk, script, 2);
}

void active_pattern_normal_attack_lever_attack(PLW* wk, s16 reaction, u16 lever_data, u16 lever) {
    const Pattern_Step script[2] = { [0] = STEP(Normal_Attack, reaction, lever_data),
                                     [1] = STEP(Lever_Attack, 8, lever, 0x20) };
    Run_Pattern(wk, script, 2);
}

void active_pattern_sa_term_command_attack(PLW* wk, const SA_Term_Args* p, const Command_Attack_Args* p_b) {
    const Pattern_Step script[2] = { [0] = STEP_WITH(SA_Term, p), [1] = STEP_WITH(Command_Attack, p_b) };
    Run_Pattern(wk, script, 2);
}

void active_pattern_sa_term_hi_jump_attack_term(PLW* wk) {
    const Pattern_Step script[2] = { [0] = STEP(SA_Term, 0xFFFF, 0xFFFF, 0x30, 0),
                                     [1] = STEP(Hi_Jump_Attack_Term, -0x7FB0, 8, 8, 0x8400, 0, -0x7FA0, 8, 0x20) };
    Run_Pattern(wk, script, 2);
}

void active_pattern_search_back_term_walk(PLW* wk, s16 move_value, s16 next_action, s16 next_menu) {
    const Pattern_Step script[2] = { [0] = STEP(Search_Back_Term, move_value, next_action, next_menu),
                                     [1] = STEP(Walk, 1, 0x30, 0) };
    Run_Pattern(wk, script, 2);
}

void active_pattern_search_back_term_walk_2(PLW* wk, s16 move_value, s16 next_action, s16 next_menu) {
    const Pattern_Step script[2] = { [0] = STEP(Search_Back_Term, move_value, next_action, next_menu),
                                     [1] = STEP(Walk, 1, 0x60, 0) };
    Run_Pattern(wk, script, 2);
}

void pattern_approach_walk_com_random_select(PLW* wk, s16 target_pos, const Branch_Menu_Args* p, s16 rnd_type) {
    const Pattern_Step script[2] = { [0] = STEP(Approach_Walk, target_pos, 2),
                                     [1] = STEP(Com_Random_Select, p, rnd_type) };
    Run_Pattern(wk, script, 2);
}

void pattern_approach_walk_em_term(PLW* wk, s16 target_pos, const EM_Term_Params* p) {
    const Pattern_Step script[2] = { [0] = STEP(Approach_Walk, target_pos, 2), [1] = STEP_WITH(EM_Term, p) };
    Run_Pattern(wk, script, 2);
}

void pattern_approach_walk_j_command_attack(PLW* wk, s16 target_pos, const Command_Attack_Args* p) {
    const Pattern_Step script[2] = { [0] = STEP(Approach_Walk, target_pos, 2), [1] = STEP_WITH(J_Command_Attack, p) };
    Run_Pattern(wk, script, 2);
}

void pattern_approach_walk_lever_attack(PLW* wk, s16 target_pos, u16 lever, u16 lever_data) {
    const Pattern_Step script[2] = { [0] = STEP(Approach_Walk, target_pos, 2),
                                     [1] = STEP(Lever_Attack, 8, lever, lever_data) };
    Run_Pattern(wk, script, 2);
}

void pattern_approach_walk_look(PLW* wk, s16 option) {
    const Pattern_Step script[2] = { [0] = STEP(Approach_Walk, 0xBF, option), [1] = STEP(Look, 2) };
    Run_Pattern(wk, script, 2);
}

void pattern_approach_walk_normal_attack_2(PLW* wk, s16 reaction, u16 lever_data) {
    pattern_approach_walk_normal_attack_4(wk, 0x47, reaction, lever_data);
}

void pattern_approach_walk_sa_term(PLW* wk, s16 target_pos, const SA_Term_Args* p) {
    const Pattern_Step script[2] = { [0] = STEP(Approach_Walk, target_pos, 2), [1] = STEP_WITH(SA_Term, p) };
    Run_Pattern(wk, script, 2);
}

void pattern_check_ex_command_attack(PLW* wk, s16 next_menu, const Command_Attack_Args* p) {
    const Pattern_Step script[2] = { [0] = STEP(Check_EX, 6, next_menu), [1] = STEP_WITH(Command_Attack, p) };
    Run_Pattern(wk, script, 2);
}

void pattern_check_ex_j_command_attack(PLW* wk, s16 next_menu, const Command_Attack_Args* p) {
    const Pattern_Step script[2] = { [0] = STEP(Check_EX, 6, next_menu), [1] = STEP_WITH(J_Command_Attack, p) };
    Run_Pattern(wk, script, 2);
}

void pattern_command_attack_branch_unit_area(PLW* wk, const Command_Attack_Args* p, const Branch_Menu_Args* p_b) {
    const Pattern_Step script[2] = { [0] = STEP_WITH(Command_Attack, p), [1] = STEP_WITH(Branch_Unit_Area, p_b) };
    Run_Pattern(wk, script, 2);
}

void pattern_search_back_term_jump_attack_term(PLW* wk, const Search_Back_Term_Step* search_back_term,
                                               const Jump_Term_Args* a) {
    const Pattern_Step script[2] = { [0] = STEP_WITH(Search_Back_Term, search_back_term),
                                     [1] = STEP_WITH(Jump_Attack_Term, a) };
    Run_Pattern(wk, script, 2);
}

void pattern_check_store_lever_command_attack(PLW* wk, const Check_Store_Lever_Step* check_store_lever,
                                              const Command_Attack_Args* p) {
    const Pattern_Step script[2] = { [0] = STEP_WITH(Check_Store_Lever, check_store_lever),
                                     [1] = STEP_WITH(Command_Attack, p) };
    Run_Pattern(wk, script, 2);
}

void pattern_shell_term_jump(PLW* wk, const Shell_Term_Params* p, s16 time) {
    const Pattern_Step script[2] = { [0] = STEP_WITH(SHELL_Term, p), [1] = STEP(Jump, time) };
    Run_Pattern(wk, script, 2);
}

void pattern_shell_term_jump_attack_term(PLW* wk, const Shell_Term_Params* p, const Jump_Term_Args* a) {
    const Pattern_Step script[2] = { [0] = STEP_WITH(SHELL_Term, p), [1] = STEP_WITH(Jump_Attack_Term, a) };
    Run_Pattern(wk, script, 2);
}

void pattern_shell_term_command_attack(PLW* wk, const Command_Attack_Args* p) {
    const Pattern_Step script[2] = { [0] = STEP(SHELL_Term, 3, 2, 1, -1, -1), [1] = STEP_WITH(Command_Attack, p) };
    Run_Pattern(wk, script, 2);
}
