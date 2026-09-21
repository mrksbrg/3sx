/**
 * @file com_patterns_3step_2.c
 * COM: pattern skeletons shared by every character
 *
 * The three-step patterns. Part 2 of 3, in name order.
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

void pattern_approach_walk_normal_attack_branch_unit_area(PLW* wk, s16 target_pos, const Branch_Menu_Args* p) {
    const Pattern_Step script[3] = { [0] = STEP(Approach_Walk, target_pos, 2),
                                     [1] = STEP(Normal_Attack, 8, 0x12),
                                     [2] = STEP_WITH(Branch_Unit_Area, p) };
    Run_Pattern(wk, script, 3);
}

void pattern_approach_walk_normal_attack_command_attack(PLW* wk, s16 reaction, u16 lever_data,
                                                        const Command_Attack_Args* p) {
    const Pattern_Step script[3] = { [0] = STEP(Approach_Walk, 0x37, 2),
                                     [1] = STEP(Normal_Attack, reaction, lever_data),
                                     [2] = STEP_WITH(Command_Attack, p) };
    Run_Pattern(wk, script, 3);
}

void pattern_approach_walk_normal_attack_j_command_attack(PLW* wk, s16 target_pos, u16 lever_data,
                                                          const Command_Attack_Args* p) {
    const Pattern_Step script[3] = { [0] = STEP(Approach_Walk, target_pos, 2),
                                     [1] = STEP(Normal_Attack, 0xB, lever_data),
                                     [2] = STEP_WITH(J_Command_Attack, p) };
    Run_Pattern(wk, script, 3);
}

void pattern_approach_walk_normal_attack_j_command_attack_2(PLW* wk, s16 target_pos, const Command_Attack_Args* p) {
    const Pattern_Step script[3] = { [0] = STEP(Approach_Walk, target_pos, 2),
                                     [1] = STEP(Normal_Attack, 8, 0x20),
                                     [2] = STEP_WITH(J_Command_Attack, p) };
    Run_Pattern(wk, script, 3);
}

void pattern_approach_walk_normal_attack_lever_attack_2(PLW* wk, s16 target_pos, u16 lever) {
    const Pattern_Step script[3] = { [0] = STEP(Approach_Walk, target_pos, 2),
                                     [1] = STEP(Normal_Attack, 9, 0x100),
                                     [2] = STEP(Lever_Attack, 8, lever, 0x200) };
    Run_Pattern(wk, script, 3);
}

void pattern_approach_walk_sa_term_command_attack_2(PLW* wk, s16 target_pos, const SA_Term_Args* p) {
    const Pattern_Step script[3] = { [0] = STEP(Approach_Walk, target_pos, 2),
                                     [1] = STEP_WITH(SA_Term, p),
                                     [2] = STEP(Command_Attack, 8, 0x1C, 0xA, -1) };
    Run_Pattern(wk, script, 3);
}

void pattern_approach_walk_wait_get_up_command_attack(PLW* wk, s16 target_pos, s16 option,
                                                      const Command_Attack_Args* p) {
    const Pattern_Step script[3] = { [0] = STEP(Approach_Walk, target_pos, 2),
                                     [1] = STEP(Wait_Get_Up, 0, option),
                                     [2] = STEP_WITH(Command_Attack, p) };
    Run_Pattern(wk, script, 3);
}

void pattern_approach_walk_wait_get_up_j_command_attack(PLW* wk, s16 target_pos, const Command_Attack_Args* p) {
    const Pattern_Step script[3] = { [0] = STEP(Approach_Walk, target_pos, 2),
                                     [1] = STEP(Wait_Get_Up, 0, -1),
                                     [2] = STEP_WITH(J_Command_Attack, p) };
    Run_Pattern(wk, script, 3);
}

void pattern_approach_walk_wait_get_up_lever_attack(PLW* wk, s16 target_pos, u16 lever, u16 lever_data) {
    const Pattern_Step script[3] = { [0] = STEP(Approach_Walk, target_pos, 2),
                                     [1] = STEP(Wait_Get_Up, 0, -1),
                                     [2] = STEP(Lever_Attack, 8, lever, lever_data) };
    Run_Pattern(wk, script, 3);
}

void pattern_approach_walk_wait_get_up_normal_attack(PLW* wk, s16 target_pos, u16 lever_data) {
    const Pattern_Step script[3] = { [0] = STEP(Approach_Walk, target_pos, 2),
                                     [1] = STEP(Wait_Get_Up, 0, -1),
                                     [2] = STEP(Normal_Attack, 8, lever_data) };
    Run_Pattern(wk, script, 3);
}

void pattern_check_ex_wait_j_command_attack(PLW* wk, s16 time, const Command_Attack_Args* p) {
    const Pattern_Step script[3] = { [0] = STEP(Check_EX, 6, 0x9B),
                                     [1] = STEP(Wait, time),
                                     [2] = STEP_WITH(J_Command_Attack, p) };
    Run_Pattern(wk, script, 3);
}

void pattern_check_sa_full_em_term_command_attack(PLW* wk) {
    const Pattern_Step script[3] = { [0] = STEP(Check_SA_Full, 6, 0x7C),
                                     [1] = STEP(EM_Term, -0x7F30, -1, 5, 2, 0),
                                     [2] = STEP(Command_Attack, 8, 0x8019, 0xA, -1) };
    Run_Pattern(wk, script, 3);
}

void pattern_command_attack_2(PLW* wk, const Command_Attack_Args* p) {
    const Pattern_Step script[3] = { [0] = STEP_WITH(Command_Attack, p),
                                     [1] = STEP(Command_Attack, 8, 0x1C, 9, -1),
                                     [2] = STEP(Command_Attack, 8, 0x1C, 8, -1) };
    Run_Pattern(wk, script, 3);
}

void pattern_command_attack_em_term_command_attack(PLW* wk) {
    const Pattern_Step script[3] = { [0] = STEP(Command_Attack, 8, 0x1F, 0xA, -1),
                                     [1] = STEP(EM_Term, 0x50, -0x7FB0, 8, 1, -1),
                                     [2] = STEP(Command_Attack, 8, 0x2E, 8, -1) };
    Run_Pattern(wk, script, 3);
}

void pattern_em_term_lever_attack_normal_attack(PLW* wk, const EM_Term_Params* p, s16 reaction, u16 lever_data) {
    const Pattern_Step script[3] = { [0] = STEP_WITH(EM_Term, p),
                                     [1] = STEP(Lever_Attack, reaction, 0, 0x200),
                                     [2] = STEP(Normal_Attack, 8, lever_data) };
    Run_Pattern(wk, script, 3);
}

void pattern_em_term_normal_attack_3(PLW* wk, const EM_Term_Params* p, s16 reaction, u16 lever_data) {
    const Pattern_Step script[3] = { [0] = STEP_WITH(EM_Term, p),
                                     [1] = STEP(Normal_Attack, reaction, lever_data),
                                     [2] = STEP(Normal_Attack, 8, 0x40) };
    Run_Pattern(wk, script, 3);
}

void pattern_em_term_normal_attack_4(PLW* wk, const EM_Term_Params* p) {
    const Pattern_Step script[3] = { [0] = STEP_WITH(EM_Term, p),
                                     [1] = STEP(Normal_Attack, 8, 0x12),
                                     [2] = STEP(Normal_Attack, 8, 0x12) };
    Run_Pattern(wk, script, 3);
}

void pattern_em_term_normal_attack_5(PLW* wk, const EM_Term_Params* p) {
    const Pattern_Step script[3] = { [0] = STEP_WITH(EM_Term, p),
                                     [1] = STEP(Normal_Attack, 8, 0x10),
                                     [2] = STEP(Normal_Attack, 8, 0x10) };
    Run_Pattern(wk, script, 3);
}

void pattern_em_term_normal_attack_6(PLW* wk, const EM_Term_Params* p) {
    const Pattern_Step script[3] = { [0] = STEP_WITH(EM_Term, p),
                                     [1] = STEP(Normal_Attack, 8, 0x102),
                                     [2] = STEP(Normal_Attack, 8, 0x102) };
    Run_Pattern(wk, script, 3);
}

void pattern_em_term_normal_attack_com_random_select(PLW* wk, u16 lever_data) {
    const Pattern_Step script[3] = { [0] = STEP(EM_Term, -1, -0x7FB0, 6, 1, -1),
                                     [1] = STEP(Normal_Attack, 0xC, lever_data),
                                     [2] = STEP(Com_Random_Select, &Branch_Menu_6_4B_36_3B_70, 1) };
    Run_Pattern(wk, script, 3);
}

void pattern_em_term_normal_attack_command_attack(PLW* wk, const EM_Term_Params* p, u16 lever_data,
                                                  const Command_Attack_Args* p_b) {
    const Pattern_Step script[3] = { [0] = STEP_WITH(EM_Term, p),
                                     [1] = STEP(Normal_Attack, 8, lever_data),
                                     [2] = STEP_WITH(Command_Attack, p_b) };
    Run_Pattern(wk, script, 3);
}

void pattern_em_term_normal_attack_j_command_attack(PLW* wk, const EM_Term_Params* p, u16 lever_data,
                                                    const Command_Attack_Args* p_b) {
    const Pattern_Step script[3] = { [0] = STEP_WITH(EM_Term, p),
                                     [1] = STEP(Normal_Attack, 0xB, lever_data),
                                     [2] = STEP_WITH(J_Command_Attack, p_b) };
    Run_Pattern(wk, script, 3);
}

void pattern_em_term_normal_attack_j_command_attack_2(PLW* wk, const EM_Term_Params* p, u16 lever_data,
                                                      const Command_Attack_Args* p_b) {
    const Pattern_Step script[3] = { [0] = STEP_WITH(EM_Term, p),
                                     [1] = STEP(Normal_Attack, 9, lever_data),
                                     [2] = STEP_WITH(J_Command_Attack, p_b) };
    Run_Pattern(wk, script, 3);
}

void pattern_em_term_sa_term_command_attack(PLW* wk, const EM_Term_Params* p, const SA_Term_Args* p_b,
                                            const Command_Attack_Args* p_b_b) {
    const Pattern_Step script[3] = { [0] = STEP_WITH(EM_Term, p),
                                     [1] = STEP_WITH(SA_Term, p_b),
                                     [2] = STEP_WITH(Command_Attack, p_b_b) };
    Run_Pattern(wk, script, 3);
}

void pattern_em_term_sa_term_forced_guard(PLW* wk, const EM_Term_Params* p, const SA_Term_Args* p_b) {
    const Pattern_Step script[3] = { [0] = STEP_WITH(EM_Term, p),
                                     [1] = STEP_WITH(SA_Term, p_b),
                                     [2] = STEP(Forced_Guard, 0) };
    Run_Pattern(wk, script, 3);
}

void pattern_em_term_sa_term_j_command_attack(PLW* wk, const EM_Term_Params* p, const SA_Term_Args* p_b,
                                              const Command_Attack_Args* p_b_b) {
    const Pattern_Step script[3] = { [0] = STEP_WITH(EM_Term, p),
                                     [1] = STEP_WITH(SA_Term, p_b),
                                     [2] = STEP_WITH(J_Command_Attack, p_b_b) };
    Run_Pattern(wk, script, 3);
}

void pattern_em_term_search_back_term_command_attack(PLW* wk, const Command_Attack_Args* p) {
    const Pattern_Step script[3] = { [0] = STEP(EM_Term, -0x7FA0, -1, 0, 1, -1),
                                     [1] = STEP(Search_Back_Term, 0x30, 6, 0x6D),
                                     [2] = STEP_WITH(Command_Attack, p) };
    Run_Pattern(wk, script, 3);
}

void pattern_etc_term_normal_attack_lever_attack(PLW* wk, u16 next_menu, u16 lever, u16 lever_data) {
    const Pattern_Step script[3] = { [0] = STEP(ETC_Term, 0, 6, next_menu),
                                     [1] = STEP(Normal_Attack, 0xB, 0x10),
                                     [2] = STEP(Lever_Attack, 8, lever, lever_data) };
    Run_Pattern(wk, script, 3);
}

void pattern_etc_term_provoke_next_another_menu(PLW* wk, u16 next_menu, u16 next_menu_b) {
    const Pattern_Step script[3] = { [0] = STEP(ETC_Term, 4, 6, next_menu),
                                     [1] = STEP(Provoke, -1),
                                     [2] = STEP(Next_Another_Menu, 6, next_menu_b) };
    Run_Pattern(wk, script, 3);
}

void pattern_hi_jump_attack_term_normal_attack_2(PLW* wk, const Hi_Jump_Term_Args* a, u16 lever_data,
                                                 u16 lever_data_b) {
    const Pattern_Step script[3] = { [0] = STEP_WITH(Hi_Jump_Attack_Term, a),
                                     [1] = STEP(Normal_Attack, 8, lever_data),
                                     [2] = STEP(Normal_Attack, 8, lever_data_b) };
    Run_Pattern(wk, script, 3);
}

void pattern_hi_jump_attack_term_normal_attack_4(PLW* wk, const Hi_Jump_Term_Args* a, u16 lever_data,
                                                 u16 lever_data_b) {
    const Pattern_Step script[3] = { [0] = STEP_WITH(Hi_Jump_Attack_Term, a),
                                     [1] = STEP(Normal_Attack, 0xB, lever_data),
                                     [2] = STEP(Normal_Attack, 8, lever_data_b) };
    Run_Pattern(wk, script, 3);
}

void pattern_hi_jump_attack_term_normal_attack_lever_attack(PLW* wk, const Hi_Jump_Term_Args* a, u16 lever_data) {
    const Pattern_Step script[3] = { [0] = STEP_WITH(Hi_Jump_Attack_Term, a),
                                     [1] = STEP(Normal_Attack, 8, 0x100),
                                     [2] = STEP(Lever_Attack, 8, 0, lever_data) };
    Run_Pattern(wk, script, 3);
}

void pattern_hi_jump_attack_term_normal_attack_lever_attack_2(PLW* wk, const Hi_Jump_Term_Args* a, s16 reaction) {
    const Pattern_Step script[3] = { [0] = STEP_WITH(Hi_Jump_Attack_Term, a),
                                     [1] = STEP(Normal_Attack, reaction, 0x10),
                                     [2] = STEP(Lever_Attack, 8, 0, 0x200) };
    Run_Pattern(wk, script, 3);
}

void pattern_jump_attack_term_normal_attack_3(PLW* wk, const Jump_Term_Args* a, u16 lever_data, u16 lever_data_b) {
    const Pattern_Step script[3] = { [0] = STEP_WITH(Jump_Attack_Term, a),
                                     [1] = STEP(Normal_Attack, 8, lever_data),
                                     [2] = STEP(Normal_Attack, 8, lever_data_b) };
    Run_Pattern(wk, script, 3);
}

void pattern_jump_attack_term_normal_attack_4(PLW* wk, const Jump_Term_Args* a, u16 lever_data, u16 lever_data_b) {
    const Pattern_Step script[3] = { [0] = STEP_WITH(Jump_Attack_Term, a),
                                     [1] = STEP(Normal_Attack, 0xB, lever_data),
                                     [2] = STEP(Normal_Attack, 8, lever_data_b) };
    Run_Pattern(wk, script, 3);
}

void pattern_jump_attack_term_normal_attack_command_attack_2(PLW* wk, const Jump_Term_Args* a,
                                                             const Command_Attack_Args* p) {
    const Pattern_Step script[3] = { [0] = STEP_WITH(Jump_Attack_Term, a),
                                     [1] = STEP(Normal_Attack, 0xB, 0x202),
                                     [2] = STEP_WITH(Command_Attack, p) };
    Run_Pattern(wk, script, 3);
}

void pattern_jump_attack_term_normal_attack_j_command_attack_2(PLW* wk, const Jump_Term_Args* a, u16 lever_data,
                                                               const Command_Attack_Args* p) {
    const Pattern_Step script[3] = { [0] = STEP_WITH(Jump_Attack_Term, a),
                                     [1] = STEP(Normal_Attack, 9, lever_data),
                                     [2] = STEP_WITH(J_Command_Attack, p) };
    Run_Pattern(wk, script, 3);
}

void pattern_jump_attack_term_sa_term_j_command_attack(PLW* wk, const SA_Term_Args* p, const Command_Attack_Args* p_b) {
    const Pattern_Step script[3] = { [0] = STEP(Jump_Attack_Term, -0x7FA8, -0x7FC0, 0xB, 0x200, 0, -0x7FB0, -1, 0x40),
                                     [1] = STEP_WITH(SA_Term, p),
                                     [2] = STEP_WITH(J_Command_Attack, p_b) };
    Run_Pattern(wk, script, 3);
}

void pattern_jump_attack_term_wait_get_up_normal_attack(PLW* wk, const Jump_Term_Args* a, u16 lever_data) {
    const Pattern_Step script[3] = { [0] = STEP_WITH(Jump_Attack_Term, a),
                                     [1] = STEP(Wait_Get_Up, 0, -1),
                                     [2] = STEP(Normal_Attack, 8, lever_data) };
    Run_Pattern(wk, script, 3);
}

void pattern_keep_away_em_term_normal_attack(PLW* wk, const EM_Term_Params* p, s16 reaction, u16 lever_data) {
    const Pattern_Step script[3] = { [0] = STEP(Keep_Away, 0x7F, 3),
                                     [1] = STEP_WITH(EM_Term, p),
                                     [2] = STEP(Normal_Attack, reaction, lever_data) };
    Run_Pattern(wk, script, 3);
}

void pattern_keep_away_wait_get_up_com_random_select(PLW* wk, s16 target_pos, const Branch_Menu_Args* p) {
    const Pattern_Step script[3] = { [0] = STEP(Keep_Away, target_pos, 0),
                                     [1] = STEP(Wait_Get_Up, 0, 0),
                                     [2] = STEP(Com_Random_Select, p, 0) };
    Run_Pattern(wk, script, 3);
}

void pattern_keep_away_wait_get_up_command_attack(PLW* wk, s16 target_pos, s16 option, const Command_Attack_Args* p) {
    const Pattern_Step script[3] = { [0] = STEP(Keep_Away, target_pos, 0),
                                     [1] = STEP(Wait_Get_Up, 0, option),
                                     [2] = STEP_WITH(Command_Attack, p) };
    Run_Pattern(wk, script, 3);
}

void pattern_lever_attack_normal_attack_j_command_attack(PLW* wk, u16 lever_data, u16 lever_data_b,
                                                         const Command_Attack_Args* p) {
    const Pattern_Step script[3] = { [0] = STEP(Lever_Attack, 8, 0, lever_data),
                                     [1] = STEP(Normal_Attack, 8, lever_data_b),
                                     [2] = STEP_WITH(J_Command_Attack, p) };
    Run_Pattern(wk, script, 3);
}
