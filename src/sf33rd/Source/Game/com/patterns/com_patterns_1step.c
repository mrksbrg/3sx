/**
 * @file com_patterns_1step.c
 * COM: pattern skeletons shared by every character
 *
 * The one-step patterns.
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

void pattern_j_command_attack(PLW* wk, const Command_Attack_Args* p) {
    const Pattern_Step script[7] = { [6] = STEP_WITH(J_Command_Attack, p) };
    Run_Pattern(wk, script, 7);
}

void pattern_command_attack_3(PLW* wk, const Command_Attack_Args* p) {
    const Pattern_Step script[7] = { [6] = STEP_WITH(Command_Attack, p) };
    Run_Pattern(wk, script, 7);
}

void active_pattern_approach_walk(PLW* wk, s16 target_pos) {
    const Pattern_Step script[1] = { [0] = STEP(Approach_Walk, target_pos, 2) };
    Run_Pattern(wk, script, 1);
}

void active_pattern_branch_unit_area(PLW* wk, const Branch_Menu_Args* p) {
    const Pattern_Step script[1] = { [0] = STEP_WITH(Branch_Unit_Area, p) };
    Run_Pattern(wk, script, 1);
}

void active_pattern_com_random_select(PLW* wk, const Branch_Menu_Args* p, s16 rnd_type) {
    const Pattern_Step script[1] = { [0] = STEP(Com_Random_Select, p, rnd_type) };
    Run_Pattern(wk, script, 1);
}

void active_pattern_command_attack(PLW* wk, const Command_Attack_Args* p) {
    const Pattern_Step script[1] = { [0] = STEP_WITH(Command_Attack, p) };
    Run_Pattern(wk, script, 1);
}

void active_pattern_hi_jump_attack(PLW* wk) {
    const Pattern_Step script[1] = { [0] = STEP(Hi_Jump_Attack, 8, 0xA, 0x400, 2) };
    Run_Pattern(wk, script, 1);
}

void active_pattern_hi_jump_attack_term(PLW* wk, const Hi_Jump_Term_Args* a) {
    const Pattern_Step script[1] = { [0] = STEP_WITH(Hi_Jump_Attack_Term, a) };
    Run_Pattern(wk, script, 1);
}

void active_pattern_hi_jump_command_attack_term(PLW* wk, const JCA_Term_Args* a) {
    const Pattern_Step script[1] = { [0] = STEP_WITH(Hi_Jump_Command_Attack_Term, a) };
    Run_Pattern(wk, script, 1);
}

void active_pattern_j_command_attack(PLW* wk, const Command_Attack_Args* p) {
    const Pattern_Step script[1] = { [0] = STEP_WITH(J_Command_Attack, p) };
    Run_Pattern(wk, script, 1);
}

void active_pattern_j_command_attack_from_step_6(PLW* wk) {
    pattern_j_command_attack(wk, &(Command_Attack_Args) { 8, 0x1e, 8, -1 });
}

void active_pattern_j_command_attack_from_step_6_2(PLW* wk) {
    pattern_j_command_attack(wk, &(Command_Attack_Args) { 8, 0x1e, 10, -1 });
}

void active_pattern_jump_attack(PLW* wk, const Jump_Attack_Args* a) {
    const Pattern_Step script[1] = { [0] = STEP_WITH(Jump_Attack, a) };
    Run_Pattern(wk, script, 1);
}

void active_pattern_jump_attack_term(PLW* wk, const Jump_Term_Args* a) {
    const Pattern_Step script[1] = { [0] = STEP_WITH(Jump_Attack_Term, a) };
    Run_Pattern(wk, script, 1);
}

void active_pattern_jump_command_attack_term(PLW* wk, const JCA_Term_Args* a) {
    const Pattern_Step script[1] = { [0] = STEP_WITH(Jump_Command_Attack_Term, a) };
    Run_Pattern(wk, script, 1);
}

void active_pattern_keep_away(PLW* wk, s16 target_pos, s16 option) {
    const Pattern_Step script[1] = { [0] = STEP(Keep_Away, target_pos, option) };
    Run_Pattern(wk, script, 1);
}

void active_pattern_lever_attack(PLW* wk, s16 reaction, u16 lever, u16 lever_data) {
    const Pattern_Step script[1] = { [0] = STEP(Lever_Attack, reaction, lever, lever_data) };
    Run_Pattern(wk, script, 1);
}

void active_pattern_normal_attack(PLW* wk, s16 reaction, u16 lever_data) {
    const Pattern_Step script[1] = { [0] = STEP(Normal_Attack, reaction, lever_data) };
    Run_Pattern(wk, script, 1);
}

void active_pattern_normal_attack_sp(PLW* wk) {
    const Pattern_Step script[1] = { [0] = STEP(Normal_Attack_SP, 8, 0x200, 0x12) };
    Run_Pattern(wk, script, 1);
}

void active_pattern_oro_ja_term(PLW* wk, const ORO_Air_Term_Args* a) {
    const Pattern_Step script[1] = { [0] = STEP_WITH(ORO_JA_Term, a) };
    Run_Pattern(wk, script, 1);
}

void active_pattern_oro_jca_term(PLW* wk, const ORO_JCA_Term_Args* a) {
    const Pattern_Step script[1] = { [0] = STEP_WITH(ORO_JCA_Term, a) };
    Run_Pattern(wk, script, 1);
}

void active_pattern_rapid_command_attack(PLW* wk, const Rapid_Command_Args* p) {
    const Pattern_Step script[1] = { [0] = STEP_WITH(Rapid_Command_Attack, p) };
    Run_Pattern(wk, script, 1);
}

void active_pattern_sa_term(PLW* wk, const SA_Term_Args* p) {
    const Pattern_Step script[1] = { [0] = STEP_WITH(SA_Term, p) };
    Run_Pattern(wk, script, 1);
}

void active_pattern_wait(PLW* wk, s16 time) {
    const Pattern_Step script[1] = { [0] = STEP(Wait, time) };
    Run_Pattern(wk, script, 1);
}

void active_pattern_walk(PLW* wk, u16 lever, s16 time, s16 unused) {
    const Pattern_Step script[1] = { [0] = STEP(Walk, lever, time, unused) };
    Run_Pattern(wk, script, 1);
}

void pattern_adjust_attack(PLW* wk, u16 lever_data) {
    const Pattern_Step script[1] = { [0] = STEP(Adjust_Attack, 8, lever_data) };
    Run_Pattern(wk, script, 1);
}

void pattern_com_random_select_from_step_6(PLW* wk) {
    const Pattern_Step script[7] = { [6] = STEP(Com_Random_Select, &Branch_Menu_6_37_37_27_27, 0) };
    Run_Pattern(wk, script, 7);
}

void pattern_command_attack_from_step_6(PLW* wk) {
    pattern_command_attack_3(wk, &(Command_Attack_Args) { 8, 0x1C, 10, -1 });
}

void pattern_command_attack_from_step_6_2(PLW* wk) {
    pattern_command_attack_3(wk, &(Command_Attack_Args) { 8, 1, 10, -1 });
}

void pattern_forced_guard(PLW* wk, s16 guard_type) {
    const Pattern_Step script[1] = { [0] = STEP(Forced_Guard, guard_type) };
    Run_Pattern(wk, script, 1);
}

void pattern_hi_jump(PLW* wk, s16 pl_number) {
    const Pattern_Step script[1] = { [0] = STEP(Hi_Jump, pl_number, 0) };
    Run_Pattern(wk, script, 1);
}

void pattern_j_command_attack_from_step_6(PLW* wk) {
    pattern_j_command_attack(wk, &(Command_Attack_Args) { 8, 0x1E, 8, -1 });
}

void pattern_jump(PLW* wk, s16 time) {
    const Pattern_Step script[1] = { [0] = STEP(Jump, time) };
    Run_Pattern(wk, script, 1);
}

void pattern_keep_status(PLW* wk, s16 option_data) {
    const Pattern_Step script[1] = { [0] = STEP(Keep_Status, 2, option_data) };
    Run_Pattern(wk, script, 1);
}

void pattern_lever_attack_sp(PLW* wk) {
    const Pattern_Step script[1] = { [0] = STEP(Lever_Attack_SP, 8, 0, 0x400, 0x12) };
    Run_Pattern(wk, script, 1);
}

void pattern_look(PLW* wk) {
    const Pattern_Step script[1] = { [0] = STEP(Look, 0) };
    Run_Pattern(wk, script, 1);
}

void pattern_normal_attack_from_step_6(PLW* wk) {
    const Pattern_Step script[7] = { [6] = STEP(Normal_Attack, 8, 0x200) };
    Run_Pattern(wk, script, 7);
}

void pattern_oro_hjca_term(PLW* wk, const ORO_JCA_Term_Args* a) {
    const Pattern_Step script[1] = { [0] = STEP_WITH(ORO_HJCA_Term, a) };
    Run_Pattern(wk, script, 1);
}

void pattern_provoke(PLW* wk, s16 lever) {
    const Pattern_Step script[1] = { [0] = STEP(Provoke, lever) };
    Run_Pattern(wk, script, 1);
}

void pattern_sa_term_from_step_6(PLW* wk) {
    const Pattern_Step script[7] = { [6] = STEP(SA_Term, 0x2F, 0x30, 0x31, 0x7F) };
    Run_Pattern(wk, script, 7);
}

void pattern_short_range_attack(PLW* wk) {
    const Pattern_Step script[1] = { [0] = STEP(Short_Range_Attack, 8, 0x40, 6, 0x1D) };
    Run_Pattern(wk, script, 1);
}

void pattern_vs_jump_guard(PLW* wk) {
    const Pattern_Step script[1] = { [0] = STEP_NOARG(VS_Jump_Guard) };
    Run_Pattern(wk, script, 1);
}

void pattern_wait_attack_complete(PLW* wk, s16 option) {
    const Pattern_Step script[1] = { [0] = STEP(Wait_Attack_Complete, 3, option) };
    Run_Pattern(wk, script, 1);
}

void pattern_wait_get_up(PLW* wk, u16 lever_data, s16 option) {
    const Pattern_Step script[1] = { [0] = STEP(Wait_Get_Up, lever_data, option) };
    Run_Pattern(wk, script, 1);
}
