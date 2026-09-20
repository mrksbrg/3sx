/**
 * @file com_patterns_5step_2.c
 * COM: pattern skeletons shared by every character
 *
 * The five-step patterns. Part 2 of 2, in name order.
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

void pattern_pierce_on_hi_jump_attack_term_lever_on_2(PLW* wk, const Hi_Jump_Term_Args* a) {
    const Pattern_Step script[5] = { [0] = STEP_NOARG(Pierce_On),
                                     [1] = STEP_WITH(Hi_Jump_Attack_Term, a),
                                     [2] = STEP(Lever_On, 1, 0xFFFF),
                                     [3] = STEP(Lever_Attack, 8, 1, 0x402),
                                     [4] = STEP(Command_Attack, 8, 0x1C, 8, -1) };
    Run_Pattern(wk, script, 5);
}

void pattern_provoke_pierce_on_command_attack(PLW* wk, const Command_Attack_Args* p) {
    const Pattern_Step script[5] = { [0] = STEP(Provoke, 1),
                                     [1] = STEP_NOARG(Pierce_On),
                                     [2] = STEP(Command_Attack, 0xC, 0, 0xB, -1),
                                     [3] = STEP(Command_Attack, 0xC, 0, 0xB, -1),
                                     [4] = STEP_WITH(Command_Attack, p) };
    Run_Pattern(wk, script, 5);
}

void pattern_sa_term_approach_walk_sa_term_2(PLW* wk) {
    const Pattern_Step script[5] = { [0] = STEP(SA_Term, 0xFFFF, 0x2F, 0x30, 0),
                                     [1] = STEP(Approach_Walk, 0x41, 2),
                                     [2] = STEP(SA_Term, 0x2E, 0xFFFF, 0xFFFF, 0x41),
                                     [3] = STEP(Command_Attack, 8, 0x1F, 10, -1),
                                     [4] = STEP(Com_Random_Select, &(Branch_Menu_Args) { 2, 3, 0x38, 0x44, 0x45 }, 1) };
    Run_Pattern(wk, script, 5);
}

void pattern_sa_term_approach_walk_sa_term_3(PLW* wk, const SA_Term_Args* p) {
    const Pattern_Step script[5] = { [0] = STEP_WITH(SA_Term, p),
                                     [1] = STEP(Approach_Walk, 0x59, 2),
                                     [2] = STEP(SA_Term, 0x2E, 0xFFFF, 0xFFFF, 0x59),
                                     [3] = STEP(Approach_Walk, 0x4F, 2),
                                     [4] = STEP(Command_Attack, 8, 0x1D, 0xA, -1) };
    Run_Pattern(wk, script, 5);
}

void pattern_sa_term_normal_attack_com_random_select(PLW* wk, const SA_Term_Args* p, s16 reaction) {
    const Pattern_Step script[5] = {
        [0] = STEP_WITH(SA_Term, p),
        [1] = STEP(Normal_Attack, 8, 0x10),
        [2] = STEP(Normal_Attack, 8, 0x20),
        [3] = STEP(Normal_Attack, reaction, 0x40),
        [4] = STEP(Com_Random_Select, &(Branch_Menu_Args) { 6, 0x37, 0x37, 0x27, 0x27 }, 0)
    };
    Run_Pattern(wk, script, 5);
}

void pattern_search_back_term_command_attack_sa_term(
    PLW* wk, s16 move_value, s16 next_menu, const Command_Attack_Args* p
) {
    const Pattern_Step script[5] = { [0] = STEP(Search_Back_Term, move_value, 6, next_menu),
                                     [1] = STEP_WITH(Command_Attack, p),
                                     [2] = STEP(SA_Term, 0x2F, 0x30, 0x31, 0x47),
                                     [3] = STEP(EM_Term, -0x7FB0, -1, 5, 6, 1),
                                     [4] = STEP(J_Command_Attack, 8, 0x1E, 8, -1) };
    Run_Pattern(wk, script, 5);
}

void pattern_search_back_term_command_attack_sa_term_2(
    PLW* wk, s16 move_value, s16 next_menu, const Command_Attack_Args* p
) {
    const Pattern_Step script[5] = { [0] = STEP(Search_Back_Term, move_value, 6, next_menu),
                                     [1] = STEP_WITH(Command_Attack, p),
                                     [2] = STEP(SA_Term, 0x34, 0x34, 0x34, 0x47),
                                     [3] = STEP(EM_Term, -0x7FB0, -1, 5, 6, 1),
                                     [4] = STEP(J_Command_Attack, 8, 0x1E, 8, -1) };
    Run_Pattern(wk, script, 5);
}

void pattern_search_back_term_pierce_on_keep_away(PLW* wk, s16 next_menu, s16 target_pos, const Branch_Menu_Args* p) {
    const Pattern_Step script[5] = { [0] = STEP(Search_Back_Term, 0x60, 6, next_menu),
                                     [1] = STEP_NOARG(Pierce_On),
                                     [2] = STEP(Keep_Away, target_pos, 0),
                                     [3] = STEP(Wait_Get_Up, 3, -1),
                                     [4] = STEP_WITH(Branch_Unit_Area, p) };
    Run_Pattern(wk, script, 5);
}

void pattern_search_back_term_pierce_on_keep_away_3(PLW* wk, s16 target_pos) {
    const Pattern_Step script[5] = { [0] = STEP(Search_Back_Term, 0x60, 6, 0x6C),
                                     [1] = STEP_NOARG(Pierce_On),
                                     [2] = STEP(Keep_Away, target_pos, 0),
                                     [3] = STEP(Wait_Get_Up, 0, -1),
                                     [4] = STEP(Normal_Attack, 8, 0x200) };
    Run_Pattern(wk, script, 5);
}

void pattern_search_back_term_pierce_on_keep_away_4(PLW* wk, s16 move_value, s16 next_menu, s16 target_pos) {
    const Pattern_Step script[5] = { [0] = STEP(Search_Back_Term, move_value, 6, next_menu),
                                     [1] = STEP_NOARG(Pierce_On),
                                     [2] = STEP(Keep_Away, target_pos, 0),
                                     [3] = STEP(Wait_Get_Up, 0, -1),
                                     [4] = STEP(Normal_Attack, 8, 0x400) };
    Run_Pattern(wk, script, 5);
}

void pattern_search_back_term_pierce_on_keep_away_6(PLW* wk, s16 target_pos, const Command_Attack_Args* p) {
    const Pattern_Step script[5] = { [0] = STEP(Search_Back_Term, 0x70, 6, 0x68),
                                     [1] = STEP_NOARG(Pierce_On),
                                     [2] = STEP(Keep_Away, target_pos, 0),
                                     [3] = STEP(Wait_Get_Up, 3, -1),
                                     [4] = STEP_WITH(Command_Attack, p) };
    Run_Pattern(wk, script, 5);
}

void pattern_wait_get_up_jump_attack_term_normal_attack(PLW* wk, const Jump_Term_Args* a, u16 lever_data) {
    const Pattern_Step script[5] = { [0] = STEP(Wait_Get_Up, 0, -1),
                                     [1] = STEP_WITH(Jump_Attack_Term, a),
                                     [2] = STEP(Normal_Attack, 8, 0x10),
                                     [3] = STEP(Normal_Attack, 8, 0x10),
                                     [4] = STEP(Normal_Attack, 8, lever_data) };
    Run_Pattern(wk, script, 5);
}

void pattern_wait_get_up_jump_attack_term_normal_attack_3(
    PLW* wk, const Jump_Term_Args* a, s16 reaction, const Command_Attack_Args* p
) {
    const Pattern_Step script[5] = { [0] = STEP(Wait_Get_Up, 0, -1),
                                     [1] = STEP_WITH(Jump_Attack_Term, a),
                                     [2] = STEP(Normal_Attack, reaction, 0x10),
                                     [3] = STEP(Normal_Attack, 8, 0x10),
                                     [4] = STEP_WITH(Command_Attack, p) };
    Run_Pattern(wk, script, 5);
}
