/**
 * @file com_patterns_4step_2.c
 * COM: pattern skeletons shared by every character
 *
 * The four-step patterns. Part 2 of 3, in name order.
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

void pattern_command_attack_approach_walk_em_term(PLW* wk, const EM_Term_Params* p) {
    const Pattern_Step script[4] = { [0] = STEP(Command_Attack, 8, 0, -1, -1),
                                     [1] = STEP(Approach_Walk, 0x7F, 2),
                                     [2] = STEP_WITH(EM_Term, p),
                                     [3] = STEP(Normal_Attack, 8, 0x402) };
    Run_Pattern(wk, script, 4);
}

void pattern_command_attack_approach_walk_em_term_2(PLW* wk, u16 lever) {
    const Pattern_Step script[4] = { [0] = STEP(Command_Attack, 8, 0, -1, -1),
                                     [1] = STEP(Approach_Walk, 0x10, 2),
                                     [2] = STEP(EM_Term, -1, -0x7FF8, 6, 1, -1),
                                     [3] = STEP(Lever_Attack, 8, lever, 0x110) };
    Run_Pattern(wk, script, 4);
}

void pattern_command_attack_check_sa_command_attack_2(PLW* wk, const Command_Attack_Args* p) {
    const Pattern_Step script[4] = {
        [0] = STEP_WITH(Command_Attack, p),
        [1] = STEP(Check_SA, 2, 0x34),
        [2] = STEP(Command_Attack, 8, 0x1E, 8, -1),
        [3] = STEP(Com_Random_Select, &(Branch_Menu_Args) { 2, 0x31, 0x31, 0x32, 0x33 }, 0)
    };
    Run_Pattern(wk, script, 4);
}

void pattern_command_attack_em_term_sa_term(PLW* wk) {
    const Pattern_Step script[4] = { [0] = STEP(Command_Attack, 8, 0x1F, 0xA, -1),
                                     [1] = STEP(EM_Term, 0x50, -0x7FB0, 8, 1, -1),
                                     [2] = STEP(SA_Term, 0x48, 0xFFFF, 0xFFFF, 0),
                                     [3] = STEP(Command_Attack, 8, 0x2E, 8, -1) };
    Run_Pattern(wk, script, 4);
}

void pattern_em_term_command_attack_wait(PLW* wk, const Command_Attack_Args* p, const SA_Term_Args* p_b) {
    const Pattern_Step script[4] = { [0] = STEP(EM_Term, -0x7FB0, -0x7FF0, 6, 1, -1),
                                     [1] = STEP_WITH(Command_Attack, p),
                                     [2] = STEP(Wait, 5),
                                     [3] = STEP_WITH(SA_Term, p_b) };
    Run_Pattern(wk, script, 4);
}

void pattern_em_term_normal_attack_7(PLW* wk, const EM_Term_Params* p, s16 reaction, u16 lever_data) {
    const Pattern_Step script[4] = { [0] = STEP_WITH(EM_Term, p),
                                     [1] = STEP(Normal_Attack, reaction, 0x100),
                                     [2] = STEP(Normal_Attack, 8, 0x100),
                                     [3] = STEP(Normal_Attack, 8, lever_data) };
    Run_Pattern(wk, script, 4);
}

void pattern_em_term_normal_attack_sa_term(PLW* wk) {
    const Pattern_Step script[4] = { [0] = STEP(EM_Term, -1, -0x7FD0, 6, 1, -1),
                                     [1] = STEP(Normal_Attack, 0xC, 0x202),
                                     [2] = STEP(SA_Term, 0x30, 0x31, 0x32, 0x7F),
                                     [3] = STEP(Command_Attack, 8, 0x1D, 9, -1) };
    Run_Pattern(wk, script, 4);
}

void pattern_hi_jump_attack_normal_attack(PLW* wk, const Jump_Attack_Args* a, u16 lever_data) {
    const Pattern_Step script[4] = { [0] = STEP_WITH(Hi_Jump_Attack, a),
                                     [1] = STEP(Normal_Attack, 8, 0x102),
                                     [2] = STEP(Normal_Attack, 8, 0x102),
                                     [3] = STEP(Normal_Attack, 8, lever_data) };
    Run_Pattern(wk, script, 4);
}

void pattern_hi_jump_attack_term_normal_attack_3(PLW* wk, const Hi_Jump_Term_Args* a, u16 lever_data) {
    const Pattern_Step script[4] = { [0] = STEP_WITH(Hi_Jump_Attack_Term, a),
                                     [1] = STEP(Normal_Attack, 8, 0x100),
                                     [2] = STEP(Normal_Attack, 8, 0x100),
                                     [3] = STEP(Normal_Attack, 8, lever_data) };
    Run_Pattern(wk, script, 4);
}

void pattern_hi_jump_attack_term_normal_attack_command_attack(
    PLW* wk, const Hi_Jump_Term_Args* a, const Command_Attack_Args* p
) {
    const Pattern_Step script[4] = { [0] = STEP_WITH(Hi_Jump_Attack_Term, a),
                                     [1] = STEP(Normal_Attack, 9, 0x10),
                                     [2] = STEP(Normal_Attack, 0xB, 0x20),
                                     [3] = STEP_WITH(Command_Attack, p) };
    Run_Pattern(wk, script, 4);
}

void pattern_hi_jump_attack_term_normal_attack_j_command_attack(
    PLW* wk, const Hi_Jump_Term_Args* a, const Command_Attack_Args* p
) {
    const Pattern_Step script[4] = { [0] = STEP_WITH(Hi_Jump_Attack_Term, a),
                                     [1] = STEP(Normal_Attack, 9, 0x10),
                                     [2] = STEP(Normal_Attack, 8, 0x42),
                                     [3] = STEP_WITH(J_Command_Attack, p) };
    Run_Pattern(wk, script, 4);
}

void pattern_jump_attack_term_em_term_sa_term(PLW* wk, const Jump_Term_Args* a, const SA_Term_Args* p) {
    const Pattern_Step script[4] = { [0] = STEP_WITH(Jump_Attack_Term, a),
                                     [1] = STEP(EM_Term, -1, -0x8000, 4, 1, -1),
                                     [2] = STEP_WITH(SA_Term, p),
                                     [3] = STEP(J_Command_Attack, 8, 0x1C, 0xA, -1) };
    Run_Pattern(wk, script, 4);
}

void pattern_jump_attack_term_normal_attack_5(PLW* wk, const Jump_Term_Args* a) {
    const Pattern_Step script[4] = { [0] = STEP_WITH(Jump_Attack_Term, a),
                                     [1] = STEP(Normal_Attack, 9, 0x100),
                                     [2] = STEP(Normal_Attack, 0xB, 0x20),
                                     [3] = STEP(Normal_Attack, 8, 0x400) };
    Run_Pattern(wk, script, 4);
}

void pattern_jump_attack_term_normal_attack_command_attack(PLW* wk, const Command_Attack_Args* p) {
    const Pattern_Step script[4] = { [0] = STEP(Jump_Attack_Term, -1, -0x7FA0, 8, 0x402, 0, -0x7FA0, -1, 0x200),
                                     [1] = STEP(Normal_Attack, 0xC, 0x102),
                                     [2] = STEP(Normal_Attack, 0xC, 0x102),
                                     [3] = STEP_WITH(Command_Attack, p) };
    Run_Pattern(wk, script, 4);
}

void pattern_jump_attack_term_normal_attack_command_attack_3(
    PLW* wk, s16 reaction, s16 reaction_b, const Command_Attack_Args* p
) {
    const Pattern_Step script[4] = { [0] = STEP(Jump_Attack_Term, -0x7FB0, -1, 8, 0x8400, 0, -0x7FA0, -1, 0x40),
                                     [1] = STEP(Normal_Attack, reaction, 0x10),
                                     [2] = STEP(Normal_Attack, reaction_b, 0x40),
                                     [3] = STEP_WITH(Command_Attack, p) };
    Run_Pattern(wk, script, 4);
}

void pattern_jump_attack_term_normal_attack_command_attack_7(
    PLW* wk, const Jump_Term_Args* a, const Command_Attack_Args* p
) {
    const Pattern_Step script[4] = { [0] = STEP_WITH(Jump_Attack_Term, a),
                                     [1] = STEP(Normal_Attack, 9, 0x202),
                                     [2] = STEP_WITH(Command_Attack, p),
                                     [3] = STEP(Wait, 5) };
    Run_Pattern(wk, script, 4);
}

void pattern_jump_attack_term_normal_attack_sa_term(PLW* wk, const SA_Term_Args* p, const Command_Attack_Args* p_b) {
    const Pattern_Step script[4] = { [0] = STEP(Jump_Attack_Term, -0x7FA8, -0x7FC0, 0xB, 0x200, 0, -0x7FB0, -1, 0x40),
                                     [1] = STEP(Normal_Attack, 0xB, 0x400),
                                     [2] = STEP_WITH(SA_Term, p),
                                     [3] = STEP_WITH(J_Command_Attack, p_b) };
    Run_Pattern(wk, script, 4);
}

void pattern_lever_on_em_term_check_store_lever(PLW* wk, u16 tech_number) {
    const Pattern_Step script[4] = { [0] = STEP(Lever_On, 1, 2),
                                     [1] = STEP(EM_Term, -1, -0x7FD0, 6, 1, -1),
                                     [2] = STEP(Check_Store_Lever, tech_number, 1, -1),
                                     [3] = STEP(Branch_Unit_Area, 6, 0x69, 0x6A, 1, 1) };
    Run_Pattern(wk, script, 4);
}

void pattern_lever_on_em_term_check_store_lever_2(PLW* wk, const Command_Attack_Args* p) {
    const Pattern_Step script[4] = { [0] = STEP(Lever_On, 0xFFFF, 2),
                                     [1] = STEP(EM_Term, -0x7FB0, -0x7FD8, 3, 1, -1),
                                     [2] = STEP(Check_Store_Lever, 0x1C, 6, 0x3C),
                                     [3] = STEP_WITH(J_Command_Attack, p) };
    Run_Pattern(wk, script, 4);
}

void pattern_normal_attack_com_random_select_4(PLW* wk, s16 reaction, s16 reaction_b) {
    const Pattern_Step script[4] = {
        [0] = STEP(Normal_Attack, reaction, 0x10),
        [1] = STEP(Normal_Attack, 8, 0x20),
        [2] = STEP(Normal_Attack, reaction_b, 0x40),
        [3] = STEP(Com_Random_Select, &(Branch_Menu_Args) { 6, 0x37, 0x37, 0x27, 0x27 }, 0)
    };
    Run_Pattern(wk, script, 4);
}

void pattern_normal_attack_com_random_select_5(PLW* wk, u16 lever_data) {
    const Pattern_Step script[4] = {
        [0] = STEP(Normal_Attack, 9, lever_data),
        [1] = STEP(Normal_Attack, 8, 0x102),
        [2] = STEP(Normal_Attack, 8, 0x102),
        [3] = STEP(Com_Random_Select, &(Branch_Menu_Args) { 6, 0xA5, 0xE9, 0xE7, 0xAD }, 4)
    };
    Run_Pattern(wk, script, 4);
}

void pattern_normal_attack_command_attack_5(PLW* wk, const Command_Attack_Args* p) {
    const Pattern_Step script[4] = { [0] = STEP(Normal_Attack, 8, 0x220),
                                     [1] = STEP(Normal_Attack, 9, 0x102),
                                     [2] = STEP(Normal_Attack, 8, 0x202),
                                     [3] = STEP_WITH(Command_Attack, p) };
    Run_Pattern(wk, script, 4);
}

void pattern_normal_attack_command_attack_6(PLW* wk, s16 reaction, u16 lever_data, const Command_Attack_Args* p) {
    const Pattern_Step script[4] = { [0] = STEP(Normal_Attack, reaction, lever_data),
                                     [1] = STEP(Normal_Attack, 9, 0x102),
                                     [2] = STEP(Normal_Attack, 9, 0x202),
                                     [3] = STEP_WITH(Command_Attack, p) };
    Run_Pattern(wk, script, 4);
}

void pattern_normal_attack_command_attack_wait(PLW* wk, const Command_Attack_Args* p, const SA_Term_Args* p_b) {
    const Pattern_Step script[4] = { [0] = STEP(Normal_Attack, 9, 0x40),
                                     [1] = STEP_WITH(Command_Attack, p),
                                     [2] = STEP(Wait, 5),
                                     [3] = STEP_WITH(SA_Term, p_b) };
    Run_Pattern(wk, script, 4);
}

void pattern_normal_attack_jump_attack_term_sa_term(PLW* wk, const SA_Term_Args* p, const Command_Attack_Args* p_b) {
    const Pattern_Step script[4] = { [0] = STEP(Normal_Attack, 9, 0x100),
                                     [1] = STEP(Jump_Attack_Term, -0x7FA8, -0x7FC0, 0xB, 0x200, 0, -1, -1, -1),
                                     [2] = STEP_WITH(SA_Term, p),
                                     [3] = STEP_WITH(Command_Attack, p_b) };
    Run_Pattern(wk, script, 4);
}

void pattern_normal_attack_jump_attack_term_sa_term_2(
    PLW* wk, s16 reaction, const SA_Term_Args* p, const Command_Attack_Args* p_b
) {
    const Pattern_Step script[4] = { [0] = STEP(Normal_Attack, reaction, 0x100),
                                     [1] = STEP(Jump_Attack_Term, -0x7FA8, -0x7FC0, 0xB, 0x200, 0, -0x7FB0, -1, 0x40),
                                     [2] = STEP_WITH(SA_Term, p),
                                     [3] = STEP_WITH(J_Command_Attack, p_b) };
    Run_Pattern(wk, script, 4);
}

void pattern_normal_attack_sa_term_normal_attack_2(PLW* wk, const SA_Term_Args* p, u16 lever_data) {
    const Pattern_Step script[4] = { [0] = STEP(Normal_Attack, 9, 0x102),
                                     [1] = STEP(Normal_Attack, 0xB, 0x102),
                                     [2] = STEP_WITH(SA_Term, p),
                                     [3] = STEP(Normal_Attack, 8, lever_data) };
    Run_Pattern(wk, script, 4);
}

void pattern_pierce_on_command_attack_approach_walk(PLW* wk, s16 target_pos, const Command_Attack_Args* p) {
    const Pattern_Step script[4] = { [0] = STEP_NOARG(Pierce_On),
                                     [1] = STEP(Command_Attack, 0xC, 0, 0xB, -1),
                                     [2] = STEP(Approach_Walk, target_pos, 2),
                                     [3] = STEP_WITH(Command_Attack, p) };
    Run_Pattern(wk, script, 4);
}

void pattern_pierce_on_command_attack_em_term(PLW* wk) {
    const Pattern_Step script[4] = { [0] = STEP_NOARG(Pierce_On),
                                     [1] = STEP(Command_Attack, 8, 0, -1, -1),
                                     [2] = STEP(EM_Term, -1, -0x7FD0, 6, 1, -1),
                                     [3] = STEP(Normal_Attack, 9, 0x402) };
    Run_Pattern(wk, script, 4);
}

void pattern_pierce_on_command_attack_normal_attack_2(PLW* wk, s16 reaction, u16 lever_data) {
    const Pattern_Step script[4] = { [0] = STEP_NOARG(Pierce_On),
                                     [1] = STEP(Command_Attack, 8, 0, -1, -1),
                                     [2] = STEP(Normal_Attack, reaction, 0x102),
                                     [3] = STEP(Normal_Attack, 8, lever_data) };
    Run_Pattern(wk, script, 4);
}

void pattern_pierce_on_command_attack_wait_3(PLW* wk, const Command_Attack_Args* p) {
    const Pattern_Step script[4] = { [0] = STEP_NOARG(Pierce_On),
                                     [1] = STEP_WITH(Command_Attack, p),
                                     [2] = STEP(Wait, 2),
                                     [3] = STEP(Lever_Attack, 8, 0, 0x20) };
    Run_Pattern(wk, script, 4);
}

void pattern_pierce_on_em_term_j_command_attack(
    PLW* wk, const EM_Term_Params* p, const Command_Attack_Args* p_b, const Command_Attack_Args* p_b_b
) {
    const Pattern_Step script[4] = { [0] = STEP_NOARG(Pierce_On),
                                     [1] = STEP_WITH(EM_Term, p),
                                     [2] = STEP_WITH(J_Command_Attack, p_b),
                                     [3] = STEP_WITH(J_Command_Attack, p_b_b) };
    Run_Pattern(wk, script, 4);
}

void pattern_pierce_on_em_term_normal_attack_2(PLW* wk) {
    const Pattern_Step script[4] = { [0] = STEP_NOARG(Pierce_On),
                                     [1] = STEP(EM_Term, -1, -0x7FD0, 6, 1, -1),
                                     [2] = STEP(Normal_Attack, 8, 0x42),
                                     [3] = STEP(Normal_Attack, 8, 0x40) };
    Run_Pattern(wk, script, 4);
}

void pattern_pierce_on_em_term_normal_attack_3(PLW* wk, const Command_Attack_Args* p) {
    const Pattern_Step script[4] = { [0] = STEP_NOARG(Pierce_On),
                                     [1] = STEP(EM_Term, -1, -0x7FB0, 6, 1, -1),
                                     [2] = STEP(Normal_Attack, 8, 0x42),
                                     [3] = STEP_WITH(J_Command_Attack, p) };
    Run_Pattern(wk, script, 4);
}

void pattern_pierce_on_j_command_attack_normal_attack(PLW* wk, const Command_Attack_Args* p) {
    const Pattern_Step script[4] = { [0] = STEP_NOARG(Pierce_On),
                                     [1] = STEP(J_Command_Attack, 8, 0x1E, 0xA, -1),
                                     [2] = STEP(Normal_Attack, 0xC, 0x202),
                                     [3] = STEP_WITH(Command_Attack, p) };
    Run_Pattern(wk, script, 4);
}

void pattern_pierce_on_lever_on_lever_attack(PLW* wk) {
    const Pattern_Step script[4] = { [0] = STEP_NOARG(Pierce_On),
                                     [1] = STEP(Lever_On, 1, 0xFFFF),
                                     [2] = STEP(Lever_Attack, 8, 1, 0x402),
                                     [3] = STEP(Command_Attack, 8, 0x1D, 9, -1) };
    Run_Pattern(wk, script, 4);
}
