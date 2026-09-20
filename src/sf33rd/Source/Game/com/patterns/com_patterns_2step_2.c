/**
 * @file com_patterns_2step_2.c
 * COM: pattern skeletons shared by every character
 *
 * The two-step patterns. Part 2 of 3, in name order.
 *
 * A COM pattern script is a switch on the step counter with one engine call
 * per step, and the same step sequences recur across characters. Each skeleton
 * here is exactly the body its call sites used to hold, with the arguments of
 * its calls taken as parameters and written out in full at each call site.
 */

#include "common.h"
#include "sf33rd/Source/Game/com/com_sub.h"
#include "sf33rd/Source/Game/com/patterns/com_pattern_run.h"
#include "sf33rd/Source/Game/com/patterns/com_patterns.h"
#include "sf33rd/Source/Game/engine/workuser.h"

void pattern_em_term_adjust_attack(PLW* wk, const EM_Term_Params* p) {
    pattern_em_term_adjust_attack_2(wk, p, 0x20);
}

void pattern_em_term_branch_unit_area(PLW* wk, const EM_Term_Params* p, const Branch_Menu_Args* p_b) {
    const Pattern_Step script[2] = { [0] = STEP_WITH(EM_Term, p), [1] = STEP_WITH(Branch_Unit_Area, p_b) };
    Run_Pattern(wk, script, 2);
}

void pattern_em_term_com_random_select(PLW* wk, const EM_Term_Params* p, const Branch_Menu_Args* p_b) {
    const Pattern_Step script[2] = { [0] = STEP_WITH(EM_Term, p), [1] = STEP(Com_Random_Select, p_b, 1) };
    Run_Pattern(wk, script, 2);
}

void pattern_em_term_jump_attack_term(PLW* wk, const EM_Term_Params* p, const Jump_Term_Args* a) {
    const Pattern_Step script[2] = { [0] = STEP_WITH(EM_Term, p), [1] = STEP_WITH(Jump_Attack_Term, a) };
    Run_Pattern(wk, script, 2);
}

void pattern_em_term_jump_command_attack_term(PLW* wk, const EM_Term_Params* p) {
    const Pattern_Step script[2] = { [0] = STEP_WITH(EM_Term, p),
                                     [1] =
                                         STEP(Jump_Command_Attack_Term, 8, 0x2F, 9, -1, -1, 0x40, 1, -1, 0x30, 0x400) };
    Run_Pattern(wk, script, 2);
}

void pattern_em_term_short_range_attack(PLW* wk, const Short_Range_Args* p) {
    const Pattern_Step script[2] = { [0] = STEP(EM_Term, -0x7F80, 0, 0, 2, 0), [1] = STEP_WITH(Short_Range_Attack, p) };
    Run_Pattern(wk, script, 2);
}

void pattern_etc_term_branch_unit_area(PLW* wk, u32 next_action, u16 next_menu, const Branch_Menu_Args* p) {
    const Pattern_Step script[2] = { [0] = STEP(ETC_Term, 0, next_action, next_menu),
                                     [1] = STEP_WITH(Branch_Unit_Area, p) };
    Run_Pattern(wk, script, 2);
}

void pattern_etc_term_normal_attack(PLW* wk) {
    const Pattern_Step script[2] = { [0] = STEP(ETC_Term, 0, 6, 0x34), [1] = STEP(Normal_Attack, 8, 0x200) };
    Run_Pattern(wk, script, 2);
}

void pattern_etc_term_provoke(PLW* wk, s16 exit_no, u16 next_menu) {
    pattern_etc_term_provoke_2(wk, exit_no, 6, next_menu);
}

void pattern_hi_jump_attack_term_command_attack(PLW* wk, const Hi_Jump_Term_Args* a, const Command_Attack_Args* p) {
    const Pattern_Step script[2] = { [0] = STEP_WITH(Hi_Jump_Attack_Term, a), [1] = STEP_WITH(Command_Attack, p) };
    Run_Pattern(wk, script, 2);
}

void pattern_hi_jump_attack_term_normal_attack(PLW* wk, const Hi_Jump_Term_Args* a, u16 lever_data) {
    const Pattern_Step script[2] = { [0] = STEP_WITH(Hi_Jump_Attack_Term, a),
                                     [1] = STEP(Normal_Attack, 8, lever_data) };
    Run_Pattern(wk, script, 2);
}

void pattern_jump_attack_term_com_random_select(PLW* wk, const Jump_Term_Args* a, const Branch_Menu_Args* p) {
    const Pattern_Step script[2] = { [0] = STEP_WITH(Jump_Attack_Term, a), [1] = STEP(Com_Random_Select, p, 1) };
    Run_Pattern(wk, script, 2);
}

void pattern_jump_attack_term_normal_attack(PLW* wk, const Jump_Term_Args* a, s16 reaction, u16 lever_data) {
    const Pattern_Step script[2] = { [0] = STEP_WITH(Jump_Attack_Term, a),
                                     [1] = STEP(Normal_Attack, reaction, lever_data) };
    Run_Pattern(wk, script, 2);
}

void pattern_keep_away_com_random_select(PLW* wk, s16 target_pos) {
    const Pattern_Step script[2] = { [0] = STEP(Keep_Away, target_pos, 1),
                                     [1] = STEP(Com_Random_Select, &(Branch_Menu_Args) { 6, 0xBA, 1, 0xAF, 0x92 }, 3) };
    Run_Pattern(wk, script, 2);
}

void pattern_keep_away_com_random_select_2(PLW* wk, s16 target_pos, s16 option, const Branch_Menu_Args* p) {
    const Pattern_Step script[2] = { [0] = STEP(Keep_Away, target_pos, option), [1] = STEP(Com_Random_Select, p, 0) };
    Run_Pattern(wk, script, 2);
}

void pattern_keep_away_wait_get_up(PLW* wk, s16 target_pos, u16 lever_data, s16 option) {
    const Pattern_Step script[2] = { [0] = STEP(Keep_Away, target_pos, 0),
                                     [1] = STEP(Wait_Get_Up, lever_data, option) };
    Run_Pattern(wk, script, 2);
}

void pattern_lever_attack_command_attack(PLW* wk, u16 lever, const Command_Attack_Args* p) {
    const Pattern_Step script[2] = { [0] = STEP(Lever_Attack, 8, lever, 0x200), [1] = STEP_WITH(Command_Attack, p) };
    Run_Pattern(wk, script, 2);
}

void pattern_lever_attack_j_command_attack(PLW* wk, u16 lever_data, const Command_Attack_Args* p) {
    const Pattern_Step script[2] = { [0] = STEP(Lever_Attack, 8, 0, lever_data), [1] = STEP_WITH(J_Command_Attack, p) };
    Run_Pattern(wk, script, 2);
}

void pattern_lever_attack_normal_attack(PLW* wk) {
    const Pattern_Step script[2] = { [0] = STEP(Lever_Attack, 8, 0, 0x200), [1] = STEP(Normal_Attack, 8, 0x400) };
    Run_Pattern(wk, script, 2);
}

void pattern_lever_attack_sp_com_random_select(PLW* wk, const Branch_Menu_Args* p) {
    const Pattern_Step script[2] = { [0] = STEP(Lever_Attack_SP, 8, 0, 0x400, 0x12),
                                     [1] = STEP(Com_Random_Select, p, 4) };
    Run_Pattern(wk, script, 2);
}

void pattern_normal_attack_2(PLW* wk, s16 reaction, u16 lever_data, u16 lever_data_b) {
    const Pattern_Step script[2] = { [0] = STEP(Normal_Attack, reaction, lever_data),
                                     [1] = STEP(Normal_Attack, 8, lever_data_b) };
    Run_Pattern(wk, script, 2);
}

void pattern_normal_attack_3(PLW* wk, u16 lever_data, s16 reaction, u16 lever_data_b) {
    const Pattern_Step script[2] = { [0] = STEP(Normal_Attack, 8, lever_data),
                                     [1] = STEP(Normal_Attack, reaction, lever_data_b) };
    Run_Pattern(wk, script, 2);
}

void pattern_normal_attack_6(PLW* wk, s16 reaction, u16 lever_data, s16 reaction_b) {
    const Pattern_Step script[2] = { [0] = STEP(Normal_Attack, reaction, lever_data),
                                     [1] = STEP(Normal_Attack, reaction_b, 0x102) };
    Run_Pattern(wk, script, 2);
}

void pattern_normal_attack_com_random_select(PLW* wk, u16 lever_data, const Branch_Menu_Args* p, s16 rnd_type) {
    const Pattern_Step script[2] = { [0] = STEP(Normal_Attack, 8, lever_data),
                                     [1] = STEP(Com_Random_Select, p, rnd_type) };
    Run_Pattern(wk, script, 2);
}

void pattern_normal_attack_com_random_select_2(PLW* wk, s16 reaction, u16 lever_data) {
    const Pattern_Step script[2] = {
        [0] = STEP(Normal_Attack, reaction, lever_data),
        [1] = STEP(Com_Random_Select, &(Branch_Menu_Args) { 6, 0x4B, 0x36, 0x3B, 0x70 }, 1)
    };
    Run_Pattern(wk, script, 2);
}

void pattern_pierce_on_command_attack(PLW* wk, const Command_Attack_Args* p) {
    const Pattern_Step script[2] = { [0] = STEP_NOARG(Pierce_On), [1] = STEP_WITH(Command_Attack, p) };
    Run_Pattern(wk, script, 2);
}

void pattern_provoke_com_random_select(PLW* wk, const Branch_Menu_Args* p) {
    const Pattern_Step script[2] = { [0] = STEP(Provoke, 1), [1] = STEP(Com_Random_Select, p, 1) };
    Run_Pattern(wk, script, 2);
}

void pattern_provoke_wait_get_up(PLW* wk) {
    const Pattern_Step script[2] = { [0] = STEP(Provoke, -1), [1] = STEP(Wait_Get_Up, 0, -1) };
    Run_Pattern(wk, script, 2);
}

void pattern_sa_term_2(PLW* wk) {
    const Pattern_Step script[2] = { [0] = STEP(SA_Term, 0x35, 0x36, 0xFFFF, 0x47),
                                     [1] = STEP(SA_Term, 0xFFFF, 0xFFFF, 0x19, 0x3C) };
    Run_Pattern(wk, script, 2);
}

void pattern_sa_term_branch_unit_area(PLW* wk, const SA_Term_Args* p, const Branch_Menu_Args* p_b) {
    const Pattern_Step script[2] = { [0] = STEP_WITH(SA_Term, p), [1] = STEP_WITH(Branch_Unit_Area, p_b) };
    Run_Pattern(wk, script, 2);
}

void pattern_sa_term_com_random_select(PLW* wk, const SA_Term_Args* p, const Branch_Menu_Args* p_b, s16 rnd_type) {
    const Pattern_Step script[2] = { [0] = STEP_WITH(SA_Term, p), [1] = STEP(Com_Random_Select, p_b, rnd_type) };
    Run_Pattern(wk, script, 2);
}

void pattern_sa_term_forced_guard(PLW* wk, const SA_Term_Args* p) {
    const Pattern_Step script[2] = { [0] = STEP_WITH(SA_Term, p), [1] = STEP(Forced_Guard, 0) };
    Run_Pattern(wk, script, 2);
}

void pattern_sa_term_j_command_attack(PLW* wk, const SA_Term_Args* p, const Command_Attack_Args* p_b) {
    const Pattern_Step script[2] = { [0] = STEP_WITH(SA_Term, p), [1] = STEP_WITH(J_Command_Attack, p_b) };
    Run_Pattern(wk, script, 2);
}

void pattern_sa_term_next_another_menu(PLW* wk, const SA_Term_Args* p, u16 next_menu) {
    const Pattern_Step script[2] = { [0] = STEP_WITH(SA_Term, p), [1] = STEP(Next_Another_Menu, 6, next_menu) };
    Run_Pattern(wk, script, 2);
}

void pattern_sa_term_normal_attack(PLW* wk, const SA_Term_Args* p, s16 reaction, u16 lever_data) {
    const Pattern_Step script[2] = { [0] = STEP_WITH(SA_Term, p), [1] = STEP(Normal_Attack, reaction, lever_data) };
    Run_Pattern(wk, script, 2);
}

void pattern_search_back_term_command_attack(PLW* wk, s16 move_value, s16 next_menu, const Command_Attack_Args* p) {
    const Pattern_Step script[2] = { [0] = STEP(Search_Back_Term, move_value, 6, next_menu),
                                     [1] = STEP_WITH(Command_Attack, p) };
    Run_Pattern(wk, script, 2);
}

void pattern_search_back_term_command_attack_2(PLW* wk, const Command_Attack_Args* p) {
    const Pattern_Step script[2] = { [0] = STEP(Search_Back_Term, 0x60, 1, -1), [1] = STEP_WITH(Command_Attack, p) };
    Run_Pattern(wk, script, 2);
}

void pattern_search_back_term_command_attack_from_step_6(PLW* wk) {
    const Pattern_Step script[8] = { [6] = STEP(Search_Back_Term, 0x60, 1, -1),
                                     [7] = STEP(Command_Attack, 8, 1, -1, -1) };
    Run_Pattern(wk, script, 8);
}

void pattern_search_back_term_jump(PLW* wk, s16 move_value) {
    const Pattern_Step script[2] = { [0] = STEP(Search_Back_Term, move_value, 1, -1), [1] = STEP(Jump, 1) };
    Run_Pattern(wk, script, 2);
}

void pattern_turn_over_on_jump_attack_term(PLW* wk) {
    const Pattern_Step script[2] = { [0] = STEP_NOARG(Turn_Over_On),
                                     [1] = STEP(Jump_Attack_Term, -0x7F90, -0x7FA8, 8, 0x42, 0, -0x7F68, -1, 0x400) };
    Run_Pattern(wk, script, 2);
}

void pattern_wait_attack_complete_normal_attack(PLW* wk) {
    const Pattern_Step script[2] = { [0] = STEP(Wait_Attack_Complete, 3, 1), [1] = STEP(Normal_Attack, 8, 0x402) };
    Run_Pattern(wk, script, 2);
}

void pattern_wait_branch_unit_area(PLW* wk, s16 time, const Branch_Menu_Args* p) {
    const Pattern_Step script[2] = { [0] = STEP(Wait, time), [1] = STEP_WITH(Branch_Unit_Area, p) };
    Run_Pattern(wk, script, 2);
}

void pattern_wait_com_random_select(PLW* wk, s16 time, const Branch_Menu_Args* p) {
    const Pattern_Step script[2] = { [0] = STEP(Wait, time), [1] = STEP(Com_Random_Select, p, 1) };
    Run_Pattern(wk, script, 2);
}

void pattern_wait_command_attack(PLW* wk, s16 time, const Command_Attack_Args* p) {
    const Pattern_Step script[2] = { [0] = STEP(Wait, time), [1] = STEP_WITH(Command_Attack, p) };
    Run_Pattern(wk, script, 2);
}

void pattern_wait_get_up_branch_unit_area(PLW* wk, u16 lever_data, const Branch_Menu_Args* p) {
    const Pattern_Step script[2] = { [0] = STEP(Wait_Get_Up, lever_data, -1), [1] = STEP_WITH(Branch_Unit_Area, p) };
    Run_Pattern(wk, script, 2);
}

void pattern_wait_get_up_com_random_select(PLW* wk, u16 lever_data, s16 option, const Branch_Menu_Args* p) {
    const Pattern_Step script[2] = { [0] = STEP(Wait_Get_Up, lever_data, option), [1] = STEP(Com_Random_Select, p, 0) };
    Run_Pattern(wk, script, 2);
}

void pattern_wait_get_up_command_attack(PLW* wk, u16 lever_data, s16 option, const Command_Attack_Args* p) {
    const Pattern_Step script[2] = { [0] = STEP(Wait_Get_Up, lever_data, option), [1] = STEP_WITH(Command_Attack, p) };
    Run_Pattern(wk, script, 2);
}

void pattern_wait_get_up_j_command_attack(PLW* wk, const Command_Attack_Args* p) {
    const Pattern_Step script[2] = { [0] = STEP(Wait_Get_Up, 0, 0), [1] = STEP_WITH(J_Command_Attack, p) };
    Run_Pattern(wk, script, 2);
}

void pattern_wait_get_up_jump_attack_term(PLW* wk, const Jump_Term_Args* a) {
    const Pattern_Step script[2] = { [0] = STEP(Wait_Get_Up, 0, -1), [1] = STEP_WITH(Jump_Attack_Term, a) };
    Run_Pattern(wk, script, 2);
}

void pattern_wait_get_up_lever_attack(PLW* wk, u16 lever_data, u16 lever, u16 lever_data_b) {
    const Pattern_Step script[2] = { [0] = STEP(Wait_Get_Up, lever_data, -1),
                                     [1] = STEP(Lever_Attack, 8, lever, lever_data_b) };
    Run_Pattern(wk, script, 2);
}

void pattern_wait_get_up_normal_attack(PLW* wk, u16 lever_data, u16 lever_data_b) {
    const Pattern_Step script[2] = { [0] = STEP(Wait_Get_Up, lever_data, -1),
                                     [1] = STEP(Normal_Attack, 8, lever_data_b) };
    Run_Pattern(wk, script, 2);
}

void pattern_wait_j_command_attack(PLW* wk, s16 time, const Command_Attack_Args* p) {
    const Pattern_Step script[2] = { [0] = STEP(Wait, time), [1] = STEP_WITH(J_Command_Attack, p) };
    Run_Pattern(wk, script, 2);
}

void pattern_wait_j_command_attack_from_step_6(PLW* wk) {
    const Pattern_Step script[8] = { [6] = STEP(Wait, 3), [7] = STEP(J_Command_Attack, 8, 0x1E, 8, -1) };
    Run_Pattern(wk, script, 8);
}

void pattern_wait_lie_approach_walk(PLW* wk, s16 target_pos) {
    const Pattern_Step script[2] = { [0] = STEP(Wait_Lie, 0), [1] = STEP(Approach_Walk, target_pos, 2) };
    Run_Pattern(wk, script, 2);
}

void pattern_wait_lie_jump(PLW* wk) {
    const Pattern_Step script[2] = { [0] = STEP(Wait_Lie, 0), [1] = STEP(Jump, 0) };
    Run_Pattern(wk, script, 2);
}

void pattern_walk_branch_unit_area(PLW* wk, const Branch_Menu_Args* p) {
    const Pattern_Step script[2] = { [0] = STEP(Walk, 1, 0x30, 0), [1] = STEP_WITH(Branch_Unit_Area, p) };
    Run_Pattern(wk, script, 2);
}
