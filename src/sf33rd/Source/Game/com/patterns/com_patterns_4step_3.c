/**
 * @file com_patterns_4step_3.c
 * COM: pattern skeletons shared by every character
 *
 * The four-step patterns. Part 3 of 3, in name order.
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

void pattern_sa_term_approach_walk_sa_term(
    PLW* wk, const SA_Term_Args* p, const SA_Term_Args* p_b, const Command_Attack_Args* p_b_b
) {
    const Pattern_Step script[4] = { [0] = STEP_WITH(SA_Term, p),
                                     [1] = STEP(Approach_Walk, 0x7F, 2),
                                     [2] = STEP_WITH(SA_Term, p_b),
                                     [3] = STEP_WITH(Command_Attack, p_b_b) };
    Run_Pattern(wk, script, 4);
}

void pattern_sa_term_em_term_sa_term(PLW* wk) {
    const Pattern_Step script[4] = { [0] = STEP(SA_Term, 0xFFFF, 0xFFFF, 0x30, 0),
                                     [1] = STEP(EM_Term, -1, -0x7FC8, 6, 1, -1),
                                     [2] = STEP(SA_Term, 0x2E, 0x2F, 0xFFFF, 0),
                                     [3] = STEP(Command_Attack, 8, 0x1E, 9, -1) };
    Run_Pattern(wk, script, 4);
}

void pattern_search_back_term_pierce_on_command_attack(
    PLW* wk, s16 move_value, s16 next_menu, const Command_Attack_Args* p
) {
    const Pattern_Step script[4] = { [0] = STEP(Search_Back_Term, move_value, 6, next_menu),
                                     [1] = STEP_NOARG(Pierce_On),
                                     [2] = STEP_WITH(Command_Attack, p),
                                     [3] = STEP(Wait_Get_Up, 3, -1) };
    Run_Pattern(wk, script, 4);
}

void pattern_search_back_term_pierce_on_command_attack_2(
    PLW* wk, s16 move_value, s16 next_menu, const Branch_Menu_Args* p
) {
    const Pattern_Step script[4] = { [0] = STEP(Search_Back_Term, move_value, 6, next_menu),
                                     [1] = STEP_NOARG(Pierce_On),
                                     [2] = STEP(Command_Attack, 8, 1, -1, -1),
                                     [3] = STEP(Com_Random_Select, p, 1) };
    Run_Pattern(wk, script, 4);
}

void pattern_search_back_term_pierce_on_command_attack_3(PLW* wk, const Command_Attack_Args* p) {
    const Pattern_Step script[4] = { [0] = STEP(Search_Back_Term, 0x30, 6, 0x58),
                                     [1] = STEP_NOARG(Pierce_On),
                                     [2] = STEP(Command_Attack, 8, 1, 0xB, -1),
                                     [3] = STEP_WITH(Command_Attack, p) };
    Run_Pattern(wk, script, 4);
}

void pattern_search_back_term_walk_em_term(PLW* wk, const Command_Attack_Args* p) {
    const Pattern_Step script[4] = { [0] = STEP(Search_Back_Term, 0x50, 6, 0x6E),
                                     [1] = STEP(Walk, 1, 0x18, 0),
                                     [2] = STEP(EM_Term, -1, -0x7FB0, 6, 1, -1),
                                     [3] = STEP_WITH(Command_Attack, p) };
    Run_Pattern(wk, script, 4);
}

void pattern_wait_command_attack_wait_from_step_6(PLW* wk) {
    const Pattern_Step script[10] = { [6] = STEP(Wait, 0xe),
                                      [7] = STEP(Command_Attack, 0xe, 0x1e, 0xb, 0x70),
                                      [8] = STEP(Wait, 0xe),
                                      [9] = STEP(Command_Attack, 0xe, 0x1e, 0xb, 0x70) };
    Run_Pattern(wk, script, 10);
}

void pattern_wait_get_up_jump_attack_term_normal_attack_2(
    PLW* wk, const Jump_Term_Args* a, s16 reaction, u16 lever_data
) {
    const Pattern_Step script[4] = { [0] = STEP(Wait_Get_Up, 0, -1),
                                     [1] = STEP_WITH(Jump_Attack_Term, a),
                                     [2] = STEP(Normal_Attack, reaction, 0x10),
                                     [3] = STEP(Normal_Attack, 8, lever_data) };
    Run_Pattern(wk, script, 4);
}

void pattern_wait_get_up_jump_attack_term_normal_attack_4(
    PLW* wk, const Jump_Term_Args* a, const Command_Attack_Args* p
) {
    const Pattern_Step script[4] = { [0] = STEP(Wait_Get_Up, 0, -1),
                                     [1] = STEP_WITH(Jump_Attack_Term, a),
                                     [2] = STEP(Normal_Attack, 8, 0x10),
                                     [3] = STEP_WITH(Command_Attack, p) };
    Run_Pattern(wk, script, 4);
}

void pattern_wait_get_up_normal_attack_2(PLW* wk, u16 lever_data) {
    const Pattern_Step script[4] = { [0] = STEP(Wait_Get_Up, 0, -1),
                                     [1] = STEP(Normal_Attack, 8, 0x102),
                                     [2] = STEP(Normal_Attack, 8, 0x102),
                                     [3] = STEP(Normal_Attack, 8, lever_data) };
    Run_Pattern(wk, script, 4);
}

void pattern_wait_get_up_normal_attack_sa_term(
    PLW* wk, s16 option, const SA_Term_Args* p, const Command_Attack_Args* p_b
) {
    const Pattern_Step script[4] = { [0] = STEP(Wait_Get_Up, 0, option),
                                     [1] = STEP(Normal_Attack, 0xC, 0x40),
                                     [2] = STEP_WITH(SA_Term, p),
                                     [3] = STEP_WITH(J_Command_Attack, p_b) };
    Run_Pattern(wk, script, 4);
}

void pattern_wait_get_up_normal_attack_sa_term_2(PLW* wk, const SA_Term_Args* p, const Command_Attack_Args* p_b) {
    const Pattern_Step script[4] = { [0] = STEP(Wait_Get_Up, 0, -1),
                                     [1] = STEP(Normal_Attack, 0xC, 0x20),
                                     [2] = STEP_WITH(SA_Term, p),
                                     [3] = STEP_WITH(Command_Attack, p_b) };
    Run_Pattern(wk, script, 4);
}

void pattern_wait_get_up_normal_attack_sa_term_3(PLW* wk, const SA_Term_Args* p, const Command_Attack_Args* p_b) {
    const Pattern_Step script[4] = { [0] = STEP(Wait_Get_Up, 3, -1),
                                     [1] = STEP(Normal_Attack, 0xC, 0x22),
                                     [2] = STEP_WITH(SA_Term, p),
                                     [3] = STEP_WITH(Command_Attack, p_b) };
    Run_Pattern(wk, script, 4);
}

void pattern_wait_get_up_normal_attack_sa_term_4(
    PLW* wk, s16 option, const SA_Term_Args* p, const Command_Attack_Args* p_b
) {
    const Pattern_Step script[4] = { [0] = STEP(Wait_Get_Up, 0, option),
                                     [1] = STEP(Normal_Attack, 0xC, 0x40),
                                     [2] = STEP_WITH(SA_Term, p),
                                     [3] = STEP_WITH(Command_Attack, p_b) };
    Run_Pattern(wk, script, 4);
}

void pattern_wait_get_up_pierce_on_command_attack(PLW* wk, const Command_Attack_Args* p, const EM_Term_Params* p_b) {
    const Pattern_Step script[4] = { [0] = STEP(Wait_Get_Up, 3, -1),
                                     [1] = STEP_NOARG(Pierce_On),
                                     [2] = STEP_WITH(Command_Attack, p),
                                     [3] = STEP_WITH(EM_Term, p_b) };
    Run_Pattern(wk, script, 4);
}

void pattern_wait_get_up_search_back_term_jump_attack_term(
    PLW* wk, s16 next_menu, const Jump_Term_Args* a, const Command_Attack_Args* p
) {
    const Pattern_Step script[4] = { [0] = STEP(Wait_Get_Up, 0, 0),
                                     [1] = STEP(Search_Back_Term, 0xE0, 6, next_menu),
                                     [2] = STEP_WITH(Jump_Attack_Term, a),
                                     [3] = STEP_WITH(J_Command_Attack, p) };
    Run_Pattern(wk, script, 4);
}
