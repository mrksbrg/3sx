/**
 * @file com_patterns_3step_3.c
 * COM: pattern skeletons shared by every character
 *
 * The three-step patterns. Part 3 of 3, in name order.
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

void pattern_lever_on_em_term_j_command_attack(PLW* wk, u16 lr_lever, const EM_Term_Params* p,
                                               const Command_Attack_Args* p_b) {
    const Pattern_Step script[3] = { [0] = STEP(Lever_On, lr_lever, 2),
                                     [1] = STEP_WITH(EM_Term, p),
                                     [2] = STEP_WITH(J_Command_Attack, p_b) };
    Run_Pattern(wk, script, 3);
}

void pattern_normal_attack_4(PLW* wk, s16 reaction, s16 reaction_b, u16 lever_data) {
    const Pattern_Step script[3] = { [0] = STEP(Normal_Attack, reaction, 0x102),
                                     [1] = STEP(Normal_Attack, reaction_b, lever_data),
                                     [2] = STEP(Normal_Attack, 8, 0x402) };
    Run_Pattern(wk, script, 3);
}

void pattern_normal_attack_5(PLW* wk, s16 reaction, s16 reaction_b, u16 lever_data) {
    const Pattern_Step script[3] = { [0] = STEP(Normal_Attack, reaction, 0x10),
                                     [1] = STEP(Normal_Attack, reaction_b, lever_data),
                                     [2] = STEP(Normal_Attack, 8, 0x400) };
    Run_Pattern(wk, script, 3);
}

void pattern_normal_attack_branch_unit_area(PLW* wk, const Branch_Menu_Args* p) {
    const Pattern_Step script[3] = { [0] = STEP(Normal_Attack, 8, 0x12),
                                     [1] = STEP(Normal_Attack, 8, 0x12),
                                     [2] = STEP_WITH(Branch_Unit_Area, p) };
    Run_Pattern(wk, script, 3);
}

void pattern_normal_attack_command_attack(PLW* wk, s16 reaction, s16 reaction_b, const Command_Attack_Args* p) {
    const Pattern_Step script[3] = { [0] = STEP(Normal_Attack, reaction, 0x220),
                                     [1] = STEP(Normal_Attack, reaction_b, 0x102),
                                     [2] = STEP_WITH(Command_Attack, p) };
    Run_Pattern(wk, script, 3);
}

void pattern_normal_attack_command_attack_3(PLW* wk, s16 reaction, s16 reaction_b, const Command_Attack_Args* p) {
    const Pattern_Step script[3] = { [0] = STEP(Normal_Attack, reaction, 0x102),
                                     [1] = STEP(Normal_Attack, reaction_b, 0x202),
                                     [2] = STEP_WITH(Command_Attack, p) };
    Run_Pattern(wk, script, 3);
}

void pattern_normal_attack_command_attack_4(PLW* wk, s16 reaction, s16 reaction_b, const Command_Attack_Args* p) {
    const Pattern_Step script[3] = { [0] = STEP(Normal_Attack, reaction, 0x102),
                                     [1] = STEP(Normal_Attack, reaction_b, 0x102),
                                     [2] = STEP_WITH(Command_Attack, p) };
    Run_Pattern(wk, script, 3);
}

void pattern_normal_attack_j_command_attack_3(PLW* wk, u16 lever_data, u16 lever_data_b, const Command_Attack_Args* p) {
    const Pattern_Step script[3] = { [0] = STEP(Normal_Attack, 9, lever_data),
                                     [1] = STEP(Normal_Attack, 9, lever_data_b),
                                     [2] = STEP_WITH(J_Command_Attack, p) };
    Run_Pattern(wk, script, 3);
}

void pattern_normal_attack_j_command_attack_4(PLW* wk, u16 lever_data, const Command_Attack_Args* p) {
    const Pattern_Step script[3] = { [0] = STEP(Normal_Attack, 9, lever_data),
                                     [1] = STEP(Normal_Attack, 8, 0x42),
                                     [2] = STEP_WITH(J_Command_Attack, p) };
    Run_Pattern(wk, script, 3);
}

void pattern_normal_attack_j_command_attack_com_random_select_2(PLW* wk) {
    const Pattern_Step script[3] = { [0] = STEP(Normal_Attack, 0xB, 0x200),
                                     [1] = STEP(J_Command_Attack, 8, 0x1C, 0xA, -1),
                                     [2] = STEP(Com_Random_Select, &Branch_Menu_6_2D_FF_FF_FF, 2) };
    Run_Pattern(wk, script, 3);
}

void pattern_normal_attack_sa_term_branch_unit_area(PLW* wk, const SA_Term_Args* p, const Branch_Menu_Args* p_b) {
    const Pattern_Step script[3] = { [0] = STEP(Normal_Attack, 8, 0x100),
                                     [1] = STEP_WITH(SA_Term, p),
                                     [2] = STEP_WITH(Branch_Unit_Area, p_b) };
    Run_Pattern(wk, script, 3);
}

void pattern_normal_attack_sa_term_com_random_select(PLW* wk, s16 reaction, const SA_Term_Args* p) {
    const Pattern_Step script[3] = { [0] = STEP(Normal_Attack, reaction, 0x20),
                                     [1] = STEP_WITH(SA_Term, p),
                                     [2] = STEP(Com_Random_Select, &Branch_Menu_6_37_37_27_27, 0) };
    Run_Pattern(wk, script, 3);
}

void pattern_normal_attack_sa_term_command_attack(PLW* wk, const SA_Term_Args* p, const Command_Attack_Args* p_b) {
    const Pattern_Step script[3] = { [0] = STEP(Normal_Attack, 0xC, 0x202),
                                     [1] = STEP_WITH(SA_Term, p),
                                     [2] = STEP_WITH(Command_Attack, p_b) };
    Run_Pattern(wk, script, 3);
}

void pattern_normal_attack_sa_term_command_attack_2(PLW* wk, s16 reaction, const SA_Term_Args* p,
                                                    const Command_Attack_Args* p_b) {
    const Pattern_Step script[3] = { [0] = STEP(Normal_Attack, reaction, 0x100),
                                     [1] = STEP_WITH(SA_Term, p),
                                     [2] = STEP_WITH(Command_Attack, p_b) };
    Run_Pattern(wk, script, 3);
}

void pattern_normal_attack_sa_term_j_command_attack(PLW* wk, u16 lever_data, const SA_Term_Args* p,
                                                    const Command_Attack_Args* p_b) {
    const Pattern_Step script[3] = { [0] = STEP(Normal_Attack, 0xC, lever_data),
                                     [1] = STEP_WITH(SA_Term, p),
                                     [2] = STEP_WITH(J_Command_Attack, p_b) };
    Run_Pattern(wk, script, 3);
}

void pattern_normal_attack_sa_term_normal_attack(PLW* wk, const SA_Term_Args* p) {
    const Pattern_Step script[3] = { [0] = STEP(Normal_Attack, 0xB, 0x102),
                                     [1] = STEP_WITH(SA_Term, p),
                                     [2] = STEP(Normal_Attack, 8, 0x402) };
    Run_Pattern(wk, script, 3);
}

void pattern_pierce_on_command_attack_branch_unit_area(PLW* wk, const Command_Attack_Args* p,
                                                       const Branch_Menu_Args* p_b) {
    const Pattern_Step script[3] = { [0] = STEP_NOARG(Pierce_On),
                                     [1] = STEP_WITH(Command_Attack, p),
                                     [2] = STEP_WITH(Branch_Unit_Area, p_b) };
    Run_Pattern(wk, script, 3);
}

void pattern_pierce_on_command_attack_j_command_attack(PLW* wk, const Command_Attack_Args* p,
                                                       const Command_Attack_Args* p_b) {
    const Pattern_Step script[3] = { [0] = STEP_NOARG(Pierce_On),
                                     [1] = STEP_WITH(Command_Attack, p),
                                     [2] = STEP_WITH(J_Command_Attack, p_b) };
    Run_Pattern(wk, script, 3);
}

void pattern_pierce_on_command_attack_normal_attack_3(PLW* wk) {
    const Pattern_Step script[3] = { [0] = STEP_NOARG(Pierce_On),
                                     [1] = STEP(Command_Attack, 0xC, 0, 0xB, -1),
                                     [2] = STEP(Normal_Attack, 8, 0x400) };
    Run_Pattern(wk, script, 3);
}

void pattern_pierce_on_j_command_attack(PLW* wk, const Command_Attack_Args* p, const Command_Attack_Args* p_b) {
    const Pattern_Step script[3] = { [0] = STEP_NOARG(Pierce_On),
                                     [1] = STEP_WITH(J_Command_Attack, p),
                                     [2] = STEP_WITH(J_Command_Attack, p_b) };
    Run_Pattern(wk, script, 3);
}

void pattern_pierce_on_lever_attack(PLW* wk) {
    const Pattern_Step script[3] = { [0] = STEP_NOARG(Pierce_On),
                                     [1] = STEP(Lever_Attack, 8, 0, 0x400),
                                     [2] = STEP(Lever_Attack, 8, 1, 0x200) };
    Run_Pattern(wk, script, 3);
}

void pattern_provoke_sa_term_com_random_select(PLW* wk, const SA_Term_Args* p, const Branch_Menu_Args* p_b) {
    const Pattern_Step script[3] = { [0] = STEP(Provoke, 1),
                                     [1] = STEP_WITH(SA_Term, p),
                                     [2] = STEP(Com_Random_Select, p_b, 1) };
    Run_Pattern(wk, script, 3);
}

void pattern_sa_term_approach_walk_jump_attack(PLW* wk) {
    const Pattern_Step script[3] = { [0] = STEP(SA_Term, 0xFFFF, 0xFFFF, 0x30, 0),
                                     [1] = STEP(Approach_Walk, 0xC3, 2),
                                     [2] = STEP(Jump_Attack, 8, 0xC, 0x42, 0) };
    Run_Pattern(wk, script, 3);
}

void pattern_sa_term_command_attack_2(PLW* wk, const SA_Term_Args* p, const SA_Term_Args* p_b,
                                      const Command_Attack_Args* p_b_b) {
    const Pattern_Step script[3] = { [0] = STEP_WITH(SA_Term, p),
                                     [1] = STEP_WITH(SA_Term, p_b),
                                     [2] = STEP_WITH(Command_Attack, p_b_b) };
    Run_Pattern(wk, script, 3);
}

void pattern_search_back_term_walk_normal_attack(PLW* wk, s16 next_menu, u16 lever_data) {
    const Pattern_Step script[3] = { [0] = STEP(Search_Back_Term, 0x48, 6, next_menu),
                                     [1] = STEP(Walk, 1, 0x18, 0),
                                     [2] = STEP(Normal_Attack, 8, lever_data) };
    Run_Pattern(wk, script, 3);
}

void pattern_search_back_term_walk_wait_get_up(PLW* wk, s16 move_value, s16 next_menu, s16 time) {
    const Pattern_Step script[3] = { [0] = STEP(Search_Back_Term, move_value, 6, next_menu),
                                     [1] = STEP(Walk, 1, time, 0),
                                     [2] = STEP(Wait_Get_Up, 0, -1) };
    Run_Pattern(wk, script, 3);
}

void pattern_search_back_term_walk_wait_get_up_2(PLW* wk, s16 move_value, s16 next_menu, s16 time) {
    const Pattern_Step script[3] = { [0] = STEP(Search_Back_Term, move_value, 6, next_menu),
                                     [1] = STEP(Walk, 1, time, 0),
                                     [2] = STEP(Wait_Get_Up, 3, -1) };
    Run_Pattern(wk, script, 3);
}

void pattern_wait_attack_complete_sa_term_wait_attack_complete(PLW* wk, const SA_Term_Args* p) {
    const Pattern_Step script[3] = { [0] = STEP(Wait_Attack_Complete, 3, 1),
                                     [1] = STEP_WITH(SA_Term, p),
                                     [2] = STEP(Wait_Attack_Complete, 3, 0) };
    Run_Pattern(wk, script, 3);
}

void pattern_wait_em_term_j_command_attack(PLW* wk, const Command_Attack_Args* p) {
    const Pattern_Step script[3] = { [0] = STEP(Wait, 2),
                                     [1] = STEP(EM_Term, -0x7F98, -1, 0, 1, -1),
                                     [2] = STEP_WITH(J_Command_Attack, p) };
    Run_Pattern(wk, script, 3);
}

void pattern_wait_em_term_normal_attack(PLW* wk, s16 time, const EM_Term_Params* p, u16 lever_data) {
    const Pattern_Step script[3] = { [0] = STEP(Wait, time),
                                     [1] = STEP_WITH(EM_Term, p),
                                     [2] = STEP(Normal_Attack, 8, lever_data) };
    Run_Pattern(wk, script, 3);
}

void pattern_wait_get_up_branch_wait_area_command_attack(PLW* wk, const Command_Attack_Args* p) {
    const Pattern_Step script[3] = { [0] = STEP(Wait_Get_Up, 0, 0),
                                     [1] = STEP(Branch_Wait_Area, 0x14, 0xF, 5, 1),
                                     [2] = STEP_WITH(Command_Attack, p) };
    Run_Pattern(wk, script, 3);
}

void pattern_wait_get_up_branch_wait_area_j_command_attack(PLW* wk, const Branch_Wait_Args* p,
                                                           const Command_Attack_Args* p_b) {
    const Pattern_Step script[3] = { [0] = STEP(Wait_Get_Up, 0, 0),
                                     [1] = STEP_WITH(Branch_Wait_Area, p),
                                     [2] = STEP_WITH(J_Command_Attack, p_b) };
    Run_Pattern(wk, script, 3);
}

void pattern_wait_get_up_command_attack_em_term(PLW* wk) {
    const Pattern_Step script[3] = { [0] = STEP(Wait_Get_Up, 3, -1),
                                     [1] = STEP(Command_Attack, 8, 0, 0xB, -1),
                                     [2] = STEP(EM_Term, 0x7FFF, -1, 1, 1, -1) };
    Run_Pattern(wk, script, 3);
}

void pattern_wait_get_up_jump_attack_term_j_command_attack(PLW* wk, const Jump_Term_Args* a,
                                                           const Command_Attack_Args* p) {
    const Pattern_Step script[3] = { [0] = STEP(Wait_Get_Up, 0, 0),
                                     [1] = STEP_WITH(Jump_Attack_Term, a),
                                     [2] = STEP_WITH(J_Command_Attack, p) };
    Run_Pattern(wk, script, 3);
}

void pattern_wait_get_up_normal_attack_command_attack(PLW* wk, const Command_Attack_Args* p) {
    const Pattern_Step script[3] = { [0] = STEP(Wait_Get_Up, 0, -1),
                                     [1] = STEP(Normal_Attack, 0xC, 0x40),
                                     [2] = STEP_WITH(Command_Attack, p) };
    Run_Pattern(wk, script, 3);
}

void pattern_wait_get_up_normal_attack_j_command_attack(PLW* wk, u16 lever_data, const Command_Attack_Args* p) {
    const Pattern_Step script[3] = { [0] = STEP(Wait_Get_Up, 0, -1),
                                     [1] = STEP(Normal_Attack, 0xC, lever_data),
                                     [2] = STEP_WITH(J_Command_Attack, p) };
    Run_Pattern(wk, script, 3);
}

void pattern_wait_get_up_sa_term_j_command_attack(PLW* wk, const SA_Term_Args* p, const Command_Attack_Args* p_b) {
    const Pattern_Step script[3] = { [0] = STEP(Wait_Get_Up, 0, -1),
                                     [1] = STEP_WITH(SA_Term, p),
                                     [2] = STEP_WITH(J_Command_Attack, p_b) };
    Run_Pattern(wk, script, 3);
}

void pattern_walk_wait_get_up_j_command_attack(PLW* wk, const Command_Attack_Args* p) {
    const Pattern_Step script[3] = { [0] = STEP(Walk, 1, 0x30, 0),
                                     [1] = STEP(Wait_Get_Up, 0, -1),
                                     [2] = STEP_WITH(J_Command_Attack, p) };
    Run_Pattern(wk, script, 3);
}
