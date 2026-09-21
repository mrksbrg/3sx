/**
 * @file com_patterns_3step.c
 * COM: pattern skeletons shared by every character
 *
 * The three-step patterns. Part 1 of 3, in name order.
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

void active_pattern_adjust_attack(PLW* wk, u16 lever_data, u16 lever_data_b, u16 lever_data_b_b) {
    const Pattern_Step script[3] = { [0] = STEP(Adjust_Attack, 0xC, lever_data),
                                     [1] = STEP(Adjust_Attack, 0xC, lever_data_b),
                                     [2] = STEP(Adjust_Attack, 8, lever_data_b_b) };
    Run_Pattern(wk, script, 3);
}

void active_pattern_adjust_attack_2(PLW* wk, u16 lever_data, u16 lever_data_b, u16 lever_data_b_b) {
    const Pattern_Step script[3] = { [0] = STEP(Adjust_Attack, 8, lever_data),
                                     [1] = STEP(Adjust_Attack, 8, lever_data_b),
                                     [2] = STEP(Adjust_Attack, 8, lever_data_b_b) };
    Run_Pattern(wk, script, 3);
}

void active_pattern_adjust_attack_normal_attack_branch_unit_area(PLW* wk) {
    const Pattern_Step script[3] = { [0] = STEP(Adjust_Attack, 0xB, 0x20),
                                     [1] = STEP(Normal_Attack, 0xA, 0x202),
                                     [2] = STEP(Branch_Unit_Area, 2, 0x31, 0x32, 0x33, 1) };
    Run_Pattern(wk, script, 3);
}

void active_pattern_adjust_attack_normal_attack_command_attack(
    PLW* wk, u16 lever_data, s16 reaction, u16 lever_data_b
) {
    const Pattern_Step script[3] = { [0] = STEP(Adjust_Attack, 0xB, lever_data),
                                     [1] = STEP(Normal_Attack, reaction, lever_data_b),
                                     [2] = STEP(Command_Attack, 8, 0x1F, 0xA, -1) };
    Run_Pattern(wk, script, 3);
}

void active_pattern_adjust_attack_normal_attack_lever_attack(PLW* wk) {
    const Pattern_Step script[3] = { [0] = STEP(Adjust_Attack, 0xB, 0x20),
                                     [1] = STEP(Normal_Attack, 0xA, 0x202),
                                     [2] = STEP(Lever_Attack, 8, 0, 0x40) };
    Run_Pattern(wk, script, 3);
}

void active_pattern_approach_walk_jump_command_attack_term_com_random_select(PLW* wk, const Branch_Menu_Args* p) {
    const Pattern_Step script[3] = {
        [0] = STEP(Approach_Walk, 0xBF, 3),
        [1] = STEP(Jump_Command_Attack_Term, 8, 0x2F, 0xA, -1, -0x7F60, 0x50, 0, -0x7F80, -1, 0x400),
        [2] = STEP(Com_Random_Select, p, 0)
    };
    Run_Pattern(wk, script, 3);
}

void active_pattern_approach_walk_look_com_random_select(PLW* wk, s16 target_pos) {
    const Pattern_Step script[3] = {
        [0] = STEP(Approach_Walk, target_pos, 2),
        [1] = STEP(Look, 2),
        [2] = STEP(Com_Random_Select, &(Branch_Menu_Args) { 2, 0x4C, 0x4D, 0x4E, 0x4F }, 0)
    };
    Run_Pattern(wk, script, 3);
}

void active_pattern_approach_walk_normal_attack_j_command_attack(
    PLW* wk, s16 target_pos, s16 reaction, u16 lever_data
) {
    const Pattern_Step script[3] = { [0] = STEP(Approach_Walk, target_pos, 2),
                                     [1] = STEP(Normal_Attack, reaction, lever_data),
                                     [2] = STEP(J_Command_Attack, 8, 0x1C, 0xA, -1) };
    Run_Pattern(wk, script, 3);
}

void active_pattern_approach_walk_sa_term_j_command_attack(
    PLW* wk, s16 target_pos, const SA_Term_Args* p, const Command_Attack_Args* p_b
) {
    const Pattern_Step script[3] = { [0] = STEP(Approach_Walk, target_pos, 2),
                                     [1] = STEP_WITH(SA_Term, p),
                                     [2] = STEP_WITH(J_Command_Attack, p_b) };
    Run_Pattern(wk, script, 3);
}

void active_pattern_command_attack_lever_off_look(PLW* wk) {
    const Pattern_Step script[3] = { [0] = STEP(Command_Attack, 8, 0, 0xB, -1),
                                     [1] = STEP_NOARG(Lever_Off),
                                     [2] = STEP(Look, 0) };
    Run_Pattern(wk, script, 3);
}

void active_pattern_jump_attack_term_normal_attack_command_attack_2(
    PLW* wk, const Jump_Term_Args* a, u16 lever_data, const Command_Attack_Args* p
) {
    const Pattern_Step script[3] = { [0] = STEP_WITH(Jump_Attack_Term, a),
                                     [1] = STEP(Normal_Attack, 9, lever_data),
                                     [2] = STEP_WITH(Command_Attack, p) };
    Run_Pattern(wk, script, 3);
}

void active_pattern_jump_attack_term_normal_attack_j_command_attack(
    PLW* wk, const Jump_Term_Args* a, u16 lever_data, const Command_Attack_Args* p
) {
    const Pattern_Step script[3] = { [0] = STEP_WITH(Jump_Attack_Term, a),
                                     [1] = STEP(Normal_Attack, 0xB, lever_data),
                                     [2] = STEP_WITH(J_Command_Attack, p) };
    Run_Pattern(wk, script, 3);
}

void active_pattern_jump_attack_term_sa_term_command_attack(
    PLW* wk, const SA_Term_Args* p, const Command_Attack_Args* p_b
) {
    const Pattern_Step script[3] = { [0] = STEP(Jump_Attack_Term, -0x7FA8, -0x7FC0, 0xB, 0x200, 0, -1, -1, -1),
                                     [1] = STEP_WITH(SA_Term, p),
                                     [2] = STEP_WITH(Command_Attack, p_b) };
    Run_Pattern(wk, script, 3);
}

void active_pattern_jump_lever_off_look(PLW* wk) {
    const Pattern_Step script[3] = { [0] = STEP(Jump, 1), [1] = STEP_NOARG(Lever_Off), [2] = STEP(Look, 0) };
    Run_Pattern(wk, script, 3);
}

/* The four active_pattern_normal_attack_5..8 skeletons are the same switch;
 * only the three reactions differ. The steps arrive as a table of the
 * Normal_Attack_Step parameter object com_pattern_args.h already defines, which
 * keeps the helper at two parameters. */
static void run_normal_attack_3step(PLW* wk, const Normal_Attack_Step* steps) {
    const Pattern_Step script[3] = { [0] = STEP(Normal_Attack, steps[0].Reaction, steps[0].Lever_Data),
                                     [1] = STEP(Normal_Attack, steps[1].Reaction, steps[1].Lever_Data),
                                     [2] = STEP(Normal_Attack, steps[2].Reaction, steps[2].Lever_Data) };
    Run_Pattern(wk, script, 3);
}

void active_pattern_normal_attack_5(PLW* wk, u16 lever_data, u16 lever_data_b, u16 lever_data_b_b) {
    run_normal_attack_3step(
        wk, (Normal_Attack_Step[]) { { 9, lever_data }, { 9, lever_data_b }, { 8, lever_data_b_b } }
    );
}

void active_pattern_normal_attack_6(PLW* wk, u16 lever_data, u16 lever_data_b, u16 lever_data_b_b) {
    run_normal_attack_3step(
        wk, (Normal_Attack_Step[]) { { 8, lever_data }, { 8, lever_data_b }, { 8, lever_data_b_b } }
    );
}

void active_pattern_normal_attack_7(PLW* wk, u16 lever_data, u16 lever_data_b, u16 lever_data_b_b) {
    run_normal_attack_3step(
        wk, (Normal_Attack_Step[]) { { 9, lever_data }, { 9, lever_data_b }, { 9, lever_data_b_b } }
    );
}

void active_pattern_normal_attack_8(PLW* wk, u16 lever_data, u16 lever_data_b, u16 lever_data_b_b) {
    run_normal_attack_3step(
        wk, (Normal_Attack_Step[]) { { 9, lever_data }, { 8, lever_data_b }, { 8, lever_data_b_b } }
    );
}

void active_pattern_normal_attack_command_attack_2(
    PLW* wk, u16 lever_data, u16 lever_data_b, const Command_Attack_Args* p
) {
    const Pattern_Step script[3] = { [0] = STEP(Normal_Attack, 0xB, lever_data),
                                     [1] = STEP(Normal_Attack, 0xB, lever_data_b),
                                     [2] = STEP_WITH(Command_Attack, p) };
    Run_Pattern(wk, script, 3);
}

void active_pattern_normal_attack_command_attack_3(PLW* wk, u16 lever_data, const Command_Attack_Args* p) {
    const Pattern_Step script[3] = { [0] = STEP(Normal_Attack, 8, 0x102),
                                     [1] = STEP(Normal_Attack, 8, lever_data),
                                     [2] = STEP_WITH(Command_Attack, p) };
    Run_Pattern(wk, script, 3);
}

void active_pattern_normal_attack_j_command_attack_2(
    PLW* wk, s16 reaction, u16 lever_data, const Command_Attack_Args* p
) {
    const Pattern_Step script[3] = { [0] = STEP(Normal_Attack, 8, 0x10),
                                     [1] = STEP(Normal_Attack, reaction, lever_data),
                                     [2] = STEP_WITH(J_Command_Attack, p) };
    Run_Pattern(wk, script, 3);
}

void active_pattern_normal_attack_lever_off_look(PLW* wk, s16 reaction) {
    const Pattern_Step script[3] = { [0] = STEP(Normal_Attack, reaction, 0x100),
                                     [1] = STEP_NOARG(Lever_Off),
                                     [2] = STEP(Look, 0) };
    Run_Pattern(wk, script, 3);
}

void active_pattern_pierce_on_command_attack(PLW* wk, const Command_Attack_Args* p, const Command_Attack_Args* p_b) {
    const Pattern_Step script[3] = { [0] = STEP_NOARG(Pierce_On),
                                     [1] = STEP_WITH(Command_Attack, p),
                                     [2] = STEP_WITH(Command_Attack, p_b) };
    Run_Pattern(wk, script, 3);
}

void active_pattern_pierce_on_j_command_attack_normal_attack(PLW* wk, const Command_Attack_Args* p) {
    const Pattern_Step script[3] = { [0] = STEP_NOARG(Pierce_On),
                                     [1] = STEP_WITH(J_Command_Attack, p),
                                     [2] = STEP(Normal_Attack, 8, 0x402) };
    Run_Pattern(wk, script, 3);
}

void active_pattern_pierce_on_jump_com_random_select(PLW* wk, const Branch_Menu_Args* p, s16 rnd_type) {
    const Pattern_Step script[3] = { [0] = STEP_NOARG(Pierce_On),
                                     [1] = STEP(Jump, 0),
                                     [2] = STEP(Com_Random_Select, p, rnd_type) };
    Run_Pattern(wk, script, 3);
}

void active_pattern_search_back_term_jump_look(PLW* wk, s16 move_value, s16 next_action, s16 next_menu) {
    const Pattern_Step script[3] = { [0] = STEP(Search_Back_Term, move_value, next_action, next_menu),
                                     [1] = STEP(Jump, 1),
                                     [2] = STEP(Look, 0) };
    Run_Pattern(wk, script, 3);
}

void active_pattern_search_back_term_pierce_on_command_attack(PLW* wk, s16 move_value, s16 next_action, s16 next_menu) {
    const Pattern_Step script[3] = { [0] = STEP(Search_Back_Term, move_value, next_action, next_menu),
                                     [1] = STEP_NOARG(Pierce_On),
                                     [2] = STEP(Command_Attack, 8, 1, 0xB, -1) };
    Run_Pattern(wk, script, 3);
}

void active_pattern_search_back_term_pierce_on_command_attack_4(
    PLW* wk, s16 move_value, s16 next_action, s16 next_menu
) {
    const Pattern_Step script[3] = { [0] = STEP(Search_Back_Term, move_value, next_action, next_menu),
                                     [1] = STEP_NOARG(Pierce_On),
                                     [2] = STEP(Command_Attack, 8, 1, 0xA, -1) };
    Run_Pattern(wk, script, 3);
}

void active_pattern_turn_over_on_jump_attack_term_com_random_select(PLW* wk, const Branch_Menu_Args* p) {
    const Pattern_Step script[3] = { [0] = STEP_NOARG(Turn_Over_On),
                                     [1] = STEP(Jump_Attack_Term, -1, 0x49, 9, 0x202, 0, -0x7F80, -1, 0x40),
                                     [2] = STEP(Com_Random_Select, p, 0) };
    Run_Pattern(wk, script, 3);
}

void active_pattern_walk_2(PLW* wk, s16 time, s16 time_b, s16 time_b_b) {
    const Pattern_Step script[3] = { [0] = STEP(Walk, 0, time, 0),
                                     [1] = STEP(Walk, 1, time_b, 0),
                                     [2] = STEP(Walk, 0, time_b_b, 0) };
    Run_Pattern(wk, script, 3);
}

void pattern_approach_walk_command_attack(
    PLW* wk, s16 target_pos, const Command_Attack_Args* p, const Command_Attack_Args* p_b
) {
    const Pattern_Step script[3] = { [0] = STEP(Approach_Walk, target_pos, 2),
                                     [1] = STEP_WITH(Command_Attack, p),
                                     [2] = STEP_WITH(Command_Attack, p_b) };
    Run_Pattern(wk, script, 3);
}

void pattern_approach_walk_command_attack_com_random_select_2(
    PLW* wk, const Command_Attack_Args* p, const Branch_Menu_Args* p_b
) {
    const Pattern_Step script[3] = { [0] = STEP(Approach_Walk, 0x4B, 2),
                                     [1] = STEP_WITH(Command_Attack, p),
                                     [2] = STEP(Com_Random_Select, p_b, 1) };
    Run_Pattern(wk, script, 3);
}

void pattern_approach_walk_em_term_com_random_select(PLW* wk, s16 target_pos, const Branch_Menu_Args* p) {
    const Pattern_Step script[3] = { [0] = STEP(Approach_Walk, target_pos, 2),
                                     [1] = STEP(EM_Term, -1, -0x7FF8, 6, 1, -1),
                                     [2] = STEP(Com_Random_Select, p, 1) };
    Run_Pattern(wk, script, 3);
}

void pattern_approach_walk_em_term_command_attack(
    PLW* wk, s16 target_pos, const EM_Term_Params* p, const Command_Attack_Args* p_b
) {
    const Pattern_Step script[3] = { [0] = STEP(Approach_Walk, target_pos, 2),
                                     [1] = STEP_WITH(EM_Term, p),
                                     [2] = STEP_WITH(Command_Attack, p_b) };
    Run_Pattern(wk, script, 3);
}

void pattern_approach_walk_em_term_j_command_attack(
    PLW* wk, s16 target_pos, const EM_Term_Params* p, const Command_Attack_Args* p_b
) {
    const Pattern_Step script[3] = { [0] = STEP(Approach_Walk, target_pos, 2),
                                     [1] = STEP_WITH(EM_Term, p),
                                     [2] = STEP_WITH(J_Command_Attack, p_b) };
    Run_Pattern(wk, script, 3);
}

void pattern_approach_walk_em_term_lever_attack(PLW* wk, s16 target_pos, const EM_Term_Params* p, u16 lever) {
    const Pattern_Step script[3] = { [0] = STEP(Approach_Walk, target_pos, 2),
                                     [1] = STEP_WITH(EM_Term, p),
                                     [2] = STEP(Lever_Attack, 8, lever, 0x110) };
    Run_Pattern(wk, script, 3);
}

void pattern_approach_walk_em_term_normal_attack_2(PLW* wk, s16 target_pos, const EM_Term_Params* p, u16 lever_data) {
    const Pattern_Step script[3] = { [0] = STEP(Approach_Walk, target_pos, 2),
                                     [1] = STEP_WITH(EM_Term, p),
                                     [2] = STEP(Normal_Attack, 8, lever_data) };
    Run_Pattern(wk, script, 3);
}

void pattern_approach_walk_em_term_normal_attack_7(PLW* wk, const EM_Term_Params* p, s16 reaction, u16 lever_data) {
    const Pattern_Step script[3] = { [0] = STEP(Approach_Walk, 0x83, 3),
                                     [1] = STEP_WITH(EM_Term, p),
                                     [2] = STEP(Normal_Attack, reaction, lever_data) };
    Run_Pattern(wk, script, 3);
}

void pattern_approach_walk_etc_term_com_random_select(PLW* wk) {
    const Pattern_Step script[3] = {
        [0] = STEP(Approach_Walk, 0x37, 2),
        [1] = STEP(ETC_Term, 0, 2, 0xD),
        [2] = STEP(Com_Random_Select, &(Branch_Menu_Args) { 6, 0x9D, 0x9E, 0x9F, 0x9F }, 1)
    };
    Run_Pattern(wk, script, 3);
}

void pattern_approach_walk_etc_term_lever_attack(PLW* wk, s16 target_pos, u32 next_action, u16 next_menu) {
    const Pattern_Step script[3] = { [0] = STEP(Approach_Walk, target_pos, 2),
                                     [1] = STEP(ETC_Term, 0, next_action, next_menu),
                                     [2] = STEP(Lever_Attack, 8, 0, 0x110) };
    Run_Pattern(wk, script, 3);
}

void pattern_approach_walk_hi_jump_attack_term_command_attack(
    PLW* wk, s16 target_pos, const Hi_Jump_Term_Args* a, const Command_Attack_Args* p
) {
    const Pattern_Step script[3] = { [0] = STEP(Approach_Walk, target_pos, 2),
                                     [1] = STEP_WITH(Hi_Jump_Attack_Term, a),
                                     [2] = STEP_WITH(Command_Attack, p) };
    Run_Pattern(wk, script, 3);
}

void pattern_approach_walk_lever_attack_2(PLW* wk, s16 target_pos, u16 lever_data) {
    const Pattern_Step script[3] = { [0] = STEP(Approach_Walk, target_pos, 2),
                                     [1] = STEP(Lever_Attack, 0xB, 0, lever_data),
                                     [2] = STEP(Lever_Attack, 8, 0, 0x402) };
    Run_Pattern(wk, script, 3);
}

void pattern_approach_walk_normal_attack_3(PLW* wk, s16 target_pos, s16 reaction, u16 lever_data) {
    const Pattern_Step script[3] = { [0] = STEP(Approach_Walk, target_pos, 2),
                                     [1] = STEP(Normal_Attack, reaction, 0x100),
                                     [2] = STEP(Normal_Attack, 8, lever_data) };
    Run_Pattern(wk, script, 3);
}

void pattern_wait_get_up_normal_attack_3(
    PLW* wk, u16 lever_data, const Normal_Attack_Step* normal_attack, u16 lever_data_b
) {
    const Pattern_Step script[3] = { [0] = STEP(Wait_Get_Up, lever_data, -1),
                                     [1] = STEP_WITH(Normal_Attack, normal_attack),
                                     [2] = STEP(Normal_Attack, 8, lever_data_b) };
    Run_Pattern(wk, script, 3);
}

void pattern_normal_attack_7(
    PLW* wk, const Normal_Attack_Step* normal_attack, const Normal_Attack_Step* normal_attack_b,
    const Normal_Attack_Step* normal_attack_b_b
) {
    const Pattern_Step script[3] = { [0] = STEP_WITH(Normal_Attack, normal_attack),
                                     [1] = STEP_WITH(Normal_Attack, normal_attack_b),
                                     [2] = STEP_WITH(Normal_Attack, normal_attack_b_b) };
    Run_Pattern(wk, script, 3);
}

void pattern_lever_attack_2(
    PLW* wk, const Lever_Attack_Step* lever_attack, const Lever_Attack_Step* lever_attack_b, u16 lever_data
) {
    const Pattern_Step script[3] = { [0] = STEP_WITH(Lever_Attack, lever_attack),
                                     [1] = STEP_WITH(Lever_Attack, lever_attack_b),
                                     [2] = STEP(Lever_Attack, 8, 0, lever_data) };
    Run_Pattern(wk, script, 3);
}

void pattern_approach_walk_normal_attack_j_command_attack_3(
    PLW* wk, s16 target_pos, const Normal_Attack_Step* normal_attack, const Command_Attack_Args* p
) {
    const Pattern_Step script[3] = { [0] = STEP(Approach_Walk, target_pos, 2),
                                     [1] = STEP_WITH(Normal_Attack, normal_attack),
                                     [2] = STEP_WITH(J_Command_Attack, p) };
    Run_Pattern(wk, script, 3);
}

void pattern_etc_term_normal_attack_com_random_select(
    PLW* wk, const ETC_Term_Step* etc_term, const Normal_Attack_Step* normal_attack,
    const Com_Random_Select_Step* com_random_select
) {
    const Pattern_Step script[3] = { [0] = STEP_WITH(ETC_Term, etc_term),
                                     [1] = STEP_WITH(Normal_Attack, normal_attack),
                                     [2] = STEP_WITH(Com_Random_Select, com_random_select) };
    Run_Pattern(wk, script, 3);
}

void pattern_normal_attack_command_attack_com_random_select(
    PLW* wk, const Normal_Attack_Step* normal_attack, const Command_Attack_Args* p,
    const Com_Random_Select_Step* com_random_select
) {
    const Pattern_Step script[3] = { [0] = STEP_WITH(Normal_Attack, normal_attack),
                                     [1] = STEP_WITH(Command_Attack, p),
                                     [2] = STEP_WITH(Com_Random_Select, com_random_select) };
    Run_Pattern(wk, script, 3);
}

void pattern_approach_walk_em_term_normal_attack_9(
    PLW* wk, s16 target_pos, const EM_Term_Params* p, const Normal_Attack_Step* normal_attack
) {
    const Pattern_Step script[3] = { [0] = STEP(Approach_Walk, target_pos, 2),
                                     [1] = STEP_WITH(EM_Term, p),
                                     [2] = STEP_WITH(Normal_Attack, normal_attack) };
    Run_Pattern(wk, script, 3);
}

void pattern_adjust_attack_lever_attack(
    PLW* wk, s16 reaction, const Adjust_Attack_Step* adjust_attack, u16 lever_data
) {
    const Pattern_Step script[3] = { [0] = STEP(Adjust_Attack, reaction, 0x100),
                                     [1] = STEP_WITH(Adjust_Attack, adjust_attack),
                                     [2] = STEP(Lever_Attack, 8, 0, lever_data) };
    Run_Pattern(wk, script, 3);
}

void pattern_normal_attack_j_command_attack_2(
    PLW* wk, const Normal_Attack_Step* normal_attack, u16 lever_data, const Command_Attack_Args* p
) {
    const Pattern_Step script[3] = { [0] = STEP_WITH(Normal_Attack, normal_attack),
                                     [1] = STEP(Normal_Attack, 0xB, lever_data),
                                     [2] = STEP_WITH(J_Command_Attack, p) };
    Run_Pattern(wk, script, 3);
}

void pattern_etc_term_check_sa_branch_unit_area(
    PLW* wk, const ETC_Term_Step* etc_term, s16 next_menu, const Branch_Menu_Args* p
) {
    const Pattern_Step script[3] = { [0] = STEP_WITH(ETC_Term, etc_term),
                                     [1] = STEP(Check_SA, 2, next_menu),
                                     [2] = STEP_WITH(Branch_Unit_Area, p) };
    Run_Pattern(wk, script, 3);
}

void pattern_shell_term_jump_attack_term_normal_attack(PLW* wk, const Jump_Term_Args* a, u16 lever_data) {
    const Pattern_Step script[3] = { [0] = STEP(SHELL_Term, 0, 2, 1, -1, -1),
                                     [1] = STEP_WITH(Jump_Attack_Term, a),
                                     [2] = STEP(Normal_Attack, 8, lever_data) };
    Run_Pattern(wk, script, 3);
}

void pattern_lever_off_shell_term_next_be_flip(PLW* wk) {
    const Pattern_Step script[3] = { [0] = STEP_NOARG(Lever_Off),
                                     [1] = STEP(SHELL_Term, 2, 2, 1, -1, -1),
                                     [2] = STEP(Next_Be_Flip, 8) };
    Run_Pattern(wk, script, 3);
}

void pattern_shell_term_jump_attack_term_j_command_attack(PLW* wk) {
    const Pattern_Step script[3] = { [0] = STEP(SHELL_Term, 0, 2, 1, -1, -1),
                                     [1] = STEP(Jump_Attack_Term, -0x7FA8, -0x7FC0, 0xB, 0x200, 0, -0x7FB0, -1, 0x400),
                                     [2] = STEP(J_Command_Attack, 8, 0x1C, 0xA, -1) };
    Run_Pattern(wk, script, 3);
}
