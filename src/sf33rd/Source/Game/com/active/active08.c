/**
 * @file active08.c
 * COM Active: Elena
 */

#include "sf33rd/Source/Game/com/active/active08.h"
#include "sf33rd/Source/Game/com/patterns/com_pattern_run.h"
#include "sf33rd/Source/Game/com/patterns/com_patterns.h"
#include "common.h"
#include "sf33rd/Source/Game/com/com_sub.h"
#include "sf33rd/Source/Game/engine/workuser.h"

void (*const Pattern08_Tbl[71])();

static void pattern08_0034_from_step_6(PLW* wk) {
    const Pattern_Step script[7] = { [6] = STEP(Look, 0) };
    Run_Pattern(wk, script, 7);
}

void Computer08(PLW* wk) {
    Pattern08_Tbl[(s16)Pattern_Index[wk->wu.id]](wk);
}

void Pattern08_0000(PLW* wk) {
    active_pattern_lever_off_look(wk);
}

void Pattern08_0001(PLW* wk) {
    active_pattern_normal_attack_7(wk, 0x102, 0x102, 0x402);
}

void Pattern08_0002(PLW* wk) {
    active_pattern_normal_attack_3(wk, 0x100, 9, 0x102);
}

void Pattern08_0003(PLW* wk) {
    active_pattern_adjust_attack_4(wk, 9, 8, 0x10);
}

void Pattern08_0004(PLW* wk) {
    const Pattern_Step script[4] = { [0] = STEP(J_Command_Attack, 0xB, 0x1E, 9, -1),
                                     [1] = STEP(J_Command_Attack, 8, 0x1C, 9, -1),
                                     [2] = STEP_NOARG(Pierce_On),
                                     [3] = STEP(Command_Attack, 8, 1, 0xA, -1) };
    Run_Pattern(wk, script, 4);
}

void Pattern08_0005(PLW* wk) {
    pattern_lever_attack_normal_attack_j_command_attack(wk, 0x110, 0x402, &(Command_Attack_Args){8, 0x1E, 9, -1});
}

void Pattern08_0006(PLW* wk) {
    active_pattern_wait(wk, 0);
}

void Pattern08_0007(PLW* wk) {
    active_pattern_search_back_term_pierce_on_command_attack_4(wk, 0x70, 2, 3);
}

void Pattern08_0008(PLW* wk) {
    const Pattern_Step script[3] = { [0] = STEP(Jump_Attack_Term, -0x7F90, -0x7FC0, 8, 0x200, 0, -0x7F98, -1, 0x10),
                                     [1] = STEP(Normal_Attack, 8, 0x402),
                                     [2] = STEP(J_Command_Attack, 8, 0x1E, 0xA, -1) };
    Run_Pattern(wk, script, 3);
}

void Pattern08_0009(PLW* wk) {
    const Pattern_Step script[4] = { [0] = STEP(J_Command_Attack, 8, 0x1C, 8, -1),
                                     [1] = STEP(J_Command_Attack, 8, 0x1C, 8, -1),
                                     [2] = STEP(J_Command_Attack, 9, 0x1E, 0xA, -1),
                                     [3] = STEP(J_Command_Attack, 8, 0x1C, 0xA, -1) };
    Run_Pattern(wk, script, 4);
}

void Pattern08_0010(PLW* wk) {
    active_pattern_normal_attack(wk, 8, 0x402);
}

void Pattern08_0011(PLW* wk) {
    const Pattern_Step script[4] = { [0] = STEP(Normal_Attack, 9, 0x102),
                                     [1] = STEP(Normal_Attack, 0xB, 0x202),
                                     [2] = STEP(J_Command_Attack, 9, 0x1E, 0xA, -1),
                                     [3] = STEP(J_Command_Attack, 8, 0x1C, 0xA, -1) };
    Run_Pattern(wk, script, 4);
}

void Pattern08_0012(PLW* wk) {
    active_pattern_normal_attack(wk, 8, 0x40);
}

void Pattern08_0013(PLW* wk) {
    pattern_normal_attack_7(
        wk,
        &(Normal_Attack_Step){ 8, 0x200 },
        &(Normal_Attack_Step){ 0xB, 0x202 },
        &(Normal_Attack_Step){ 8, 0x400 }
    );
}

void Pattern08_0014(PLW* wk) {
    active_pattern_jump_attack_term_normal_attack(
        wk,
        &(Jump_Term_Args){-0x7FA0, -0x7FC8, 8, 0x200, 2, -1, -0x7FF0, 0x100},
        0x402
    );
}

void Pattern08_0015(PLW* wk) {
    active_pattern_walk(wk, 0, 0x30, 0);
}

void Pattern08_0016(PLW* wk) {
    active_pattern_walk(wk, 1, 0x30, 0);
}

void Pattern08_0017(PLW* wk) {
    active_pattern_j_command_attack(wk, &(Command_Attack_Args){8, 0x1D, 0xA, -1});
}

void Pattern08_0018(PLW* wk) {
    const Pattern_Step script[5] = { [0] = STEP(Search_Back_Term, 0x60, 1, -1),
                                     [1] = STEP(Jump, 1),
                                     [2] = STEP(Command_Attack, 8, 0, 0xA, -1),
                                     [3] = STEP_NOARG(Lever_Off),
                                     [4] = STEP(Look, 0) };
    Run_Pattern(wk, script, 5);
}

void Pattern08_0019(PLW* wk) {
    active_pattern_em_term_lever_attack(wk, &(EM_Term_Params){0x70, -1, 0, 2, 5}, 0, 0x200);
}

void Pattern08_0020(PLW* wk) {
    active_pattern_j_command_attack_2(
        wk,
        &(Command_Attack_Args){9, 0x1D, 0xA, -1},
        &(Command_Attack_Args){8, 0x1C, 0xA, -1}
    );
}

void Pattern08_0021(PLW* wk) {
    active_pattern_j_command_attack(wk, &(Command_Attack_Args){8, 0x1D, 0xA, -1});
}

void Pattern08_0022(PLW* wk) {
    active_pattern_jump_attack_term_j_command_attack(
        wk,
        &(Jump_Term_Args){-0x7F98, -0x7FC0, 9, 0x40, 0, -0x7F90, -1, 0x100},
        &(Command_Attack_Args){8, 0x1C, 0xA, -1}
    );
}

void Pattern08_0023(PLW* wk) {
    active_pattern_approach_walk(wk, 0x7B);
}

void Pattern08_0024(PLW* wk) {
    active_pattern_walk(wk, 0, 0x60, 0);
}

void Pattern08_0025(PLW* wk) {
    active_pattern_walk(wk, 1, 0x60, 0);
}

void Pattern08_0026(PLW* wk) {
    active_pattern_command_attack_lever_off_look(wk);
}

void Pattern08_0027(PLW* wk) {
    active_pattern_jump(wk);
}

void Pattern08_0028(PLW* wk) {
    active_pattern_approach_walk(wk, 0xBF);
}

void Pattern08_0029(PLW* wk) {
    const Pattern_Step script[4] = { [0] = STEP(Normal_Attack, 9, 0x102),
                                     [1] = STEP(J_Command_Attack, 8, 0x1E, 9, -1),
                                     [2] = STEP(Normal_Attack, 8, 0x40),
                                     [3] = STEP(Lever_Attack, 8, 0, 0x402) };
    Run_Pattern(wk, script, 4);
}

void Pattern08_0030(PLW* wk) {
    const Pattern_Step script[4] = { [0] = STEP(Normal_Attack, 9, 0x100),
                                     [1] = STEP(Lever_Attack, 8, 0, 0x20),
                                     [2] = STEP(Normal_Attack, 9, 0x200),
                                     [3] = STEP(J_Command_Attack, 8, 0x1C, 0xA, -1) };
    Run_Pattern(wk, script, 4);
}

void Pattern08_0031(PLW* wk) {
    active_pattern_jump_attack_term_normal_attack(
        wk,
        &(Jump_Term_Args){-0x7F98, -0x7FC0, 8, 0x200, 0, -0x7F68, -1, 0x200},
        0x402
    );
}

void Pattern08_0032(PLW* wk) {
    const Pattern_Step script[3] = { [0] = STEP(Adjust_Attack, 0xB, 0x10),
                                     [1] = STEP(Adjust_Attack, 0xB, 0x20),
                                     [2] = STEP(Normal_Attack, 8, 0x40) };
    Run_Pattern(wk, script, 3);
}

void Pattern08_0033(PLW* wk) {
    const Pattern_Step script[2] = { [0] = STEP(Lever_Attack, 9, 0, 0x20), [1] = STEP(Lever_Attack, 8, 0, 0x402) };
    Run_Pattern(wk, script, 2);
}

void Pattern08_0034(PLW* wk) {
    const Pattern_Step script[6] = { [0] = STEP(Normal_Attack, 0xb, 0x100),    [1] = STEP(Normal_Attack, 0xb, 0x40),
                                     [2] = STEP(Normal_Attack, 0xb, 0x402),    [3] = STEP_NOARG(Pierce_On),
                                     [4] = STEP(Command_Attack, 8, 1, 10, -1), [5] = STEP_NOARG(Lever_Off) };
    Run_Pattern_Or(wk, script, 6, pattern08_0034_from_step_6);
}

void Pattern08_0035(PLW* wk) {
    active_pattern_normal_attack(wk, 8, 0x20);
}

void Pattern08_0036(PLW* wk) {
    active_pattern_normal_attack(wk, 8, 0x42);
}

void Pattern08_0037(PLW* wk) {
    active_pattern_lever_attack(wk, 8, 1, 0x110);
}

void Pattern08_0038(PLW* wk) {
    const Pattern_Step script[5] = { [0] = STEP(SA_Term, 0x39, 0x3A, 0xFFFF, 0),
                                     [1] = STEP_NOARG(Pierce_On),
                                     [2] = STEP(Adjust_Attack, 8, 0x200),
                                     [3] = STEP(Lever_Attack, 8, 0, 0x20),
                                     [4] = STEP(Lever_Attack, 8, 0, 0x402) };
    Run_Pattern(wk, script, 5);
}

void Pattern08_0039(PLW* wk) {
    active_pattern_command_attack_j_command_attack(
        wk,
        &(Command_Attack_Args){8, 0, 0xB, -1},
        &(Command_Attack_Args){8, 0x1C, 9, -1}
    );
}

void Pattern08_0040(PLW* wk) {
    active_pattern_normal_attack_j_command_attack(wk, 9, 0x202, &(Command_Attack_Args){8, 0x1C, 9, -1});
}

void Pattern08_0041(PLW* wk) {
    const Pattern_Step script[3] = { [0] = STEP(Normal_Attack, 0xB, 0x40),
                                     [1] = STEP(J_Command_Attack, 8, 0x1E, 0xA, -1),
                                     [2] = STEP(Lever_Attack, 8, 0, 0x402) };
    Run_Pattern(wk, script, 3);
}

void Pattern08_0042(PLW* wk) {
    active_pattern_jump_attack_term(wk, &(Jump_Term_Args){-0x7F90, -0x7FC0, 8, 0x200, 0, -0x7F70, -1, 0x400});
}

void Pattern08_0043(PLW* wk) {
    active_pattern_jump_attack_term(wk, &(Jump_Term_Args){-0x7F98, -0x7FC0, 8, 0x40, 0, -1, -0x7FE0, 0x200});
}

void Pattern08_0044(PLW* wk) {
    const Pattern_Step script[2] = { [0] = STEP(Jump_Attack_Term, -0x7F98, -0x7FC0, 8, 0x40, 0, -0x7F70, -1, 0x200),
                                     [1] = STEP(Normal_Attack, 8, 0x402) };
    Run_Pattern(wk, script, 2);
}

void Pattern08_0045(PLW* wk) {
    const Pattern_Step script[3] = { [0] = STEP(Jump_Attack_Term, -0x7F98, -0x7FC0, 0xB, 0x400, 0, -0x7F70, -1, 0x20),
                                     [1] = STEP(Normal_Attack, 9, 0x12),
                                     [2] = STEP(Normal_Attack, 8, 0x402) };
    Run_Pattern(wk, script, 3);
}

void Pattern08_0046(PLW* wk) {
    active_pattern_walk_2(wk, 0x15, 0x13, 0x10);
}

void Pattern08_0047(PLW* wk) {
    const Pattern_Step script[5] = { [0] = STEP(Walk, 1, 0x20, 0),
                                     [1] = STEP(Walk, 0, 0x14, 0),
                                     [2] = STEP(Walk, 1, 0x18, 0),
                                     [3] = STEP(Wait, 0x14),
                                     [4] = STEP(Walk, 0, 0x14, 0) };
    Run_Pattern(wk, script, 5);
}

void Pattern08_0048(PLW* wk) {
    active_pattern_wait(wk, 0x3C);
}

void Pattern08_0049(PLW* wk) {
    active_pattern_command_attack(wk, &(Command_Attack_Args){8, 0, 0xA, -1});
}

void Pattern08_0050(PLW* wk) {
    active_pattern_hi_jump_attack_term(wk, &(Hi_Jump_Term_Args){-0x7F98, -0x7FB8, 8, 0x400, 2, -1, -0x7FF0, 0x10});
}

void Pattern08_0051(PLW* wk) {
    active_pattern_hi_jump_attack_term(wk, &(Hi_Jump_Term_Args){-0x7F98, -0x7FB8, 8, 0x40, 0, -1, -0x7FF0, 0x10});
}

void Pattern08_0052(PLW* wk) {
    active_pattern_hi_jump_attack_term(wk, &(Hi_Jump_Term_Args){-0x7F98, -0x7FB8, 8, 0x40, 0, -1, -0x7FF0, 0x10});
}

void Pattern08_0053(PLW* wk) {
    const Pattern_Step script[3] = { [0] = STEP_NOARG(Pierce_On),
                                     [1] = STEP(J_Command_Attack, 8, 0x1D, 0xA, -1),
                                     [2] = STEP(Command_Attack, 8, 1, 0xA, -1) };
    Run_Pattern(wk, script, 3);
}

void Pattern08_0054(PLW* wk) {
    active_pattern_j_command_attack(wk, &(Command_Attack_Args){8, 0x1C, 0xA, -1});
}

void Pattern08_0055(PLW* wk) {
    const Pattern_Step script[6] = {
        [0] = STEP(Search_Back_Term, 0x60, 1, -1), [1] = STEP_NOARG(Pierce_On),
        [2] = STEP(Command_Attack, 8, 1, 10, -1),  [3] = STEP(Search_Back_Term, 0x60, 1, -1),
        [4] = STEP(Command_Attack, 8, 1, 10, -1),  [5] = STEP(J_Command_Attack, 8, 0x1d, 10, -1)
    };
    Run_Pattern(wk, script, 6);
}

void Pattern08_0056(PLW* wk) {
    const Pattern_Step script[6] = {
        [0] = STEP(Search_Back_Term, 0x60, 1, -1), [1] = STEP_NOARG(Pierce_On),
        [2] = STEP(Command_Attack, 8, 1, 10, -1),  [3] = STEP(Search_Back_Term, 0x60, 1, -1),
        [4] = STEP(Command_Attack, 8, 1, 10, -1),  [5] = STEP(SA_Term, -1, -1, 0x3b, 0)
    };
    Run_Pattern(wk, script, 6);
}

void Pattern08_0057(PLW* wk) {
    active_pattern_j_command_attack(wk, &(Command_Attack_Args){8, 0x8014, 0xA, -1});
}

void Pattern08_0058(PLW* wk) {
    active_pattern_j_command_attack(wk, &(Command_Attack_Args){8, 0x8015, 0xA, -1});
}

void Pattern08_0059(PLW* wk) {
    active_pattern_command_attack(wk, &(Command_Attack_Args){8, 0x8016, 0xA, -1});
}

void Pattern08_0060(PLW* wk) {
    active_pattern_(wk);
}

void Pattern08_0061(PLW* wk) {
    const Pattern_Step script[2] = { [0] = STEP(Command_Attack, 8, 1, 0xA, -1),
                                     [1] = STEP(SA_Term, 0xFFFF, 0xFFFF, 0x3B, 0) };
    Run_Pattern(wk, script, 2);
}

void Pattern08_0062(PLW* wk) {
    active_pattern_sa_term(wk, &(SA_Term_Args){0x39, 0x3A, 0xFFFF, 0});
}

void Pattern08_0063(PLW* wk) {
    active_pattern_(wk);
}

void Pattern08_0064(PLW* wk) {
    active_pattern_command_attack(wk, &(Command_Attack_Args){8, 0x20, 8, -1});
}

void Pattern08_0065(PLW* wk) {
    active_pattern_command_attack(wk, &(Command_Attack_Args){9, 0x1F, 8, -1});
}

void Pattern08_0066(PLW* wk) {
    active_pattern_command_attack(wk, &(Command_Attack_Args){9, 0x1F, 9, -1});
}

void Pattern08_0067(PLW* wk) {
    active_pattern_command_attack(wk, &(Command_Attack_Args){9, 0x1F, 0xA, -1});
}

void Pattern08_0068(PLW* wk) {
    active_pattern_command_attack(wk, &(Command_Attack_Args){9, 0x1F, 0xA, 0x700});
}

void Pattern08_0069(PLW* wk) {
    const Pattern_Step script[2] = { [0] = STEP(Jump, 0), [1] = STEP(Command_Attack, 9, 0x1F, 9, -1) };
    Run_Pattern(wk, script, 2);
}

void Pattern08_0070(PLW* wk) {
    active_pattern_jump_attack_term_command_attack(
        wk,
        &(Jump_Term_Args){-0x7F98, -0x7FC0, 9, 0x400, 0, -0x7F90, -1, 0x100},
        &(Command_Attack_Args){9, 0x1F, 0xA, -1}
    );
}

void (*const Pattern08_Tbl[71])(PLW*) = {
    Pattern08_0000, Pattern08_0001, Pattern08_0002, Pattern08_0003, Pattern08_0004, Pattern08_0005, Pattern08_0006,
    Pattern08_0007, Pattern08_0008, Pattern08_0009, Pattern08_0010, Pattern08_0011, Pattern08_0012, Pattern08_0013,
    Pattern08_0014, Pattern08_0015, Pattern08_0016, Pattern08_0017, Pattern08_0018, Pattern08_0019, Pattern08_0020,
    Pattern08_0021, Pattern08_0022, Pattern08_0023, Pattern08_0024, Pattern08_0025, Pattern08_0026, Pattern08_0027,
    Pattern08_0028, Pattern08_0029, Pattern08_0030, Pattern08_0031, Pattern08_0032, Pattern08_0033, Pattern08_0034,
    Pattern08_0035, Pattern08_0036, Pattern08_0037, Pattern08_0038, Pattern08_0039, Pattern08_0040, Pattern08_0041,
    Pattern08_0042, Pattern08_0043, Pattern08_0044, Pattern08_0045, Pattern08_0046, Pattern08_0047, Pattern08_0048,
    Pattern08_0049, Pattern08_0050, Pattern08_0051, Pattern08_0052, Pattern08_0053, Pattern08_0054, Pattern08_0055,
    Pattern08_0056, Pattern08_0057, Pattern08_0058, Pattern08_0059, Pattern08_0060, Pattern08_0061, Pattern08_0062,
    Pattern08_0063, Pattern08_0064, Pattern08_0065, Pattern08_0066, Pattern08_0067, Pattern08_0068, Pattern08_0069,
    Pattern08_0070
};
