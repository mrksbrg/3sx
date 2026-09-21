/**
 * @file active07.c
 * COM Active: Ibuki
 */

#include "sf33rd/Source/Game/com/active/active07.h"
#include "common.h"
#include "sf33rd/Source/Game/com/com_sub.h"
#include "sf33rd/Source/Game/com/patterns/com_pattern_run.h"
#include "sf33rd/Source/Game/com/patterns/com_patterns.h"
#include "sf33rd/Source/Game/engine/workuser.h"

void (*const Pattern07_Tbl[76])();

void Computer07(PLW* wk) {
    Pattern07_Tbl[(s16)Pattern_Index[wk->wu.id]](wk);
}

void Pattern07_0000(PLW* wk) {
    active_pattern_lever_off_look(wk);
}

void Pattern07_0001(PLW* wk) {
    active_pattern_normal_attack_8(wk, 0x102, 0x102, 0x400);
}

void Pattern07_0002(PLW* wk) {
    const Pattern_Step script[3] = { [0] = STEP(J_Command_Attack, 0xB, 0x1C, 8, -1),
                                     [1] = STEP(Search_Back_Term, 0x60, 1, -1),
                                     [2] = STEP(Command_Attack, 8, 1, 0xB, -1) };
    Run_Pattern(wk, script, 3);
}

void Pattern07_0003(PLW* wk) {
    const Pattern_Step script[4] = { [0] = STEP(Normal_Attack, 8, 0x10),
                                     [1] = STEP(Normal_Attack, 9, 0x20),
                                     [2] = STEP(Normal_Attack, 9, 0x400),
                                     [3] = STEP(Normal_Attack, 8, 0x40) };
    Run_Pattern(wk, script, 4);
}

void Pattern07_0004(PLW* wk) {
    const Pattern_Step script[2] = { [0] = STEP(J_Command_Attack, 8, 0x1E, 8, -1),
                                     [1] = STEP(Command_Attack, 8, 0x1F, 9, -1) };
    Run_Pattern(wk, script, 2);
}

void Pattern07_0005(PLW* wk) {
    const Pattern_Step script[3] = { [0] = STEP(Lever_Attack, 8, 0, 0x40),
                                     [1] = STEP(Lever_Attack, 0xB, 0, 0x400),
                                     [2] = STEP(Command_Attack, 8, 1, 0xA, -1) };
    Run_Pattern(wk, script, 3);
}

void Pattern07_0006(PLW* wk) {
    active_pattern_wait(wk, 0);
}

void Pattern07_0007(PLW* wk) {
    active_pattern_search_back_term_pierce_on_command_attack_4(wk, 0x60, 1, -1);
}

void Pattern07_0008(PLW* wk) {
    const Pattern_Step script[4] = { [0] = STEP(Jump_Attack_Term, -0x7F90, -0x7FC0, 8, 0x40, 0, -0x7F90, -1, 0x200),
                                     [1] = STEP(Normal_Attack, 9, 0x102),
                                     [2] = STEP(Lever_Attack, 8, 0, 0x200),
                                     [3] = STEP(Normal_Attack, 8, 0x402) };
    Run_Pattern(wk, script, 4);
}

void Pattern07_0009(PLW* wk) {
    active_pattern_command_attack_j_command_attack(
        wk, &(Command_Attack_Args) { 8, 0x20, 8, -1 }, &(Command_Attack_Args) { 8, 0x1E, 9, -1 }
    );
}

void Pattern07_0010(PLW* wk) {
    const Pattern_Step script[3] = { [0] = STEP(Jump_Attack_Term, -0x7F90, -0x7FC0, 8, 0x40, 0, -0x7F90, -1, 0x200),
                                     [1] = STEP(Normal_Attack, 9, 0x102),
                                     [2] = STEP(Lever_Attack, 8, 0, 0x200) };
    Run_Pattern(wk, script, 3);
}

void Pattern07_0011(PLW* wk) {
    const Pattern_Step script[3] = { [0] = STEP(Lever_Attack, 8, 0, 0x200),
                                     [1] = STEP(Lever_Attack, 0xB, 0, 0x202),
                                     [2] = STEP(Normal_Attack, 8, 0x400) };
    Run_Pattern(wk, script, 3);
}

void Pattern07_0012(PLW* wk) {
    const Pattern_Step script[2] = { [0] = STEP(Lever_Attack, 8, 0, 0x400), [1] = STEP(Normal_Attack, 8, 0x402) };
    Run_Pattern(wk, script, 2);
}

void Pattern07_0013(PLW* wk) {
    const Pattern_Step script[4] = { [0] = STEP(Normal_Attack, 0xB, 0x200),
                                     [1] = STEP(J_Command_Attack, 9, 0x1E, 9, -1),
                                     [2] = STEP(Search_Back_Term, 0x60, 1, -1),
                                     [3] = STEP(Command_Attack, 8, 1, 0xA, -1) };
    Run_Pattern(wk, script, 4);
}

void Pattern07_0014(PLW* wk) {
    const Pattern_Step script[3] = { [0] = STEP(Jump_Attack_Term, -0x7FA0, -0x7FC0, 8, 0x200, 2, -0x7F80, -1, 0x200),
                                     [1] = STEP(Lever_Attack, 9, 0, 0x200),
                                     [2] = STEP(Command_Attack, 8, 0x1F, 9, -1) };
    Run_Pattern(wk, script, 3);
}

void Pattern07_0015(PLW* wk) {
    active_pattern_walk(wk, 0, 0x30, 0);
}

void Pattern07_0016(PLW* wk) {
    active_pattern_walk(wk, 1, 0x30, 0);
}

void Pattern07_0017(PLW* wk) {
    active_pattern_j_command_attack(wk, &(Command_Attack_Args) { 8, 0x20, 0xA, -1 });
}

void Pattern07_0018(PLW* wk) {
    const Pattern_Step script[4] = {
        [0] = STEP(Search_Back_Term, 0x50, 1, -1), [1] = STEP(Jump, 1), [2] = STEP_NOARG(Lever_Off), [3] = STEP(Look, 0)
    };
    Run_Pattern(wk, script, 4);
}

/* The two Normal_Attack steps this script runs, named rather than indexed so no
 * subscript integers enter a file whose scripts never wrote them. */
typedef struct {
    Normal_Attack_Step first;
    Normal_Attack_Step second;
} Pattern07_Normal_Attacks;

/* Pattern07_0019 and Pattern07_0021 are the same four steps: a jump attack
 * term, two Normal_Attacks and a jumping command attack. Four of their
 * twenty-one literals differ, spread across three of the four calls, so each
 * call's values travel as its own parameter object. */
static void run_pattern07_jump_attack_term_2normal_j_command(PLW* wk, const Jump_Term_Args* a,
                                                             const Pattern07_Normal_Attacks* n,
                                                             const Command_Attack_Args* p) {
    const Pattern_Step script[4] = { [0] = STEP_WITH(Jump_Attack_Term, a),
                                     [1] = STEP(Normal_Attack, n->first.Reaction, n->first.Lever_Data),
                                     [2] = STEP(Normal_Attack, n->second.Reaction, n->second.Lever_Data),
                                     [3] = STEP_WITH(J_Command_Attack, p) };
    Run_Pattern(wk, script, 4);
}

void Pattern07_0019(PLW* wk) {
    run_pattern07_jump_attack_term_2normal_j_command(
        wk,
        &(Jump_Term_Args) { -0x7F9C, -0x7FC0, 8, 0x100, 0, -0x7F90, -1, 0x200 },
        &(Pattern07_Normal_Attacks) { { 9, 0x102 }, { 9, 0x100 } },
        &(Command_Attack_Args) { 8, 0x20, 9, -1 }
    );
}

void Pattern07_0020(PLW* wk) {
    active_pattern_command_attack_j_command_attack(
        wk, &(Command_Attack_Args) { 8, 0x1F, 0xA, -1 }, &(Command_Attack_Args) { 8, 0x1C, 9, -1 }
    );
}

void Pattern07_0021(PLW* wk) {
    run_pattern07_jump_attack_term_2normal_j_command(
        wk,
        &(Jump_Term_Args) { -0x7F9C, -0x7FC0, 8, 0x20, 0, -0x7F90, -1, 0x200 },
        &(Pattern07_Normal_Attacks) { { 8, 0x102 }, { 9, 0x400 } },
        &(Command_Attack_Args) { 8, 0x1C, 9, -1 }
    );
}

void Pattern07_0022(PLW* wk) {
    active_pattern_jump_attack_term_command_attack(
        wk,
        &(Jump_Term_Args) { -0x7FA0, -0x7FC0, 8, 0x40, 0, -0x7F90, -1, 0x100 },
        &(Command_Attack_Args) { 8, 0x1F, 9, -1 }
    );
}

void Pattern07_0023(PLW* wk) {
    active_pattern_approach_walk(wk, 0xC7);
}

void Pattern07_0024(PLW* wk) {
    active_pattern_walk(wk, 0, 0x60, 0);
}

void Pattern07_0025(PLW* wk) {
    active_pattern_walk(wk, 1, 0x60, 0);
}

void Pattern07_0026(PLW* wk) {
    const Pattern_Step script[4] = { [0] = STEP(Command_Attack, 8, 0, 0xA, -1),
                                     [1] = STEP(Command_Attack, 8, 0x1D, 0xA, -1),
                                     [2] = STEP_NOARG(Lever_Off),
                                     [3] = STEP(Look, 0) };
    Run_Pattern(wk, script, 4);
}

void Pattern07_0027(PLW* wk) {
    const Pattern_Step script[6] = { [0] = STEP(Jump, 0),
                                     [1] = STEP(Normal_Attack, 9, 0x10),
                                     [2] = STEP(Command_Attack, 8, 0x1d, 10, -1),
                                     [3] = STEP(Normal_Attack, 8, 0x10),
                                     [4] = STEP(Search_Back_Term, 0x60, 1, -1),
                                     [5] = STEP(Command_Attack, 8, 1, 10, -1) };
    Run_Pattern(wk, script, 6);
}

void Pattern07_0028(PLW* wk) {
    active_pattern_approach_walk(wk, 0x78);
}

void Pattern07_0029(PLW* wk) {
    active_pattern_adjust_attack_j_command_attack(wk, 9, 0x100, &(Command_Attack_Args) { 8, 0x1F, 9, -1 });
}

void Pattern07_0030(PLW* wk) {
    pattern_adjust_attack_lever_attack(wk, 9, &(Adjust_Attack_Step) { 9, 0x100 }, 0x200);
}

void Pattern07_0031(PLW* wk) {
    active_pattern_jump_attack_term_normal_attack(
        wk, &(Jump_Term_Args) { -0x7FA0, -0x7FC0, 9, 0x200, 0, -0x7F68, -1, 0x200 }, 0x402
    );
}

void Pattern07_0032(PLW* wk) {
    const Pattern_Step script[4] = { [0] = STEP(Normal_Attack, 0xB, 0x10),
                                     [1] = STEP(Normal_Attack, 0xB, 0x20),
                                     [2] = STEP(Lever_Attack, 0xB, 0, 0x100),
                                     [3] = STEP(J_Command_Attack, 8, 0x1F, 9, -1) };
    Run_Pattern(wk, script, 4);
}

void Pattern07_0033(PLW* wk) {
    active_pattern_adjust_attack_j_command_attack(wk, 0xB, 0x10, &(Command_Attack_Args) { 8, 0x20, 0xA, -1 });
}

void Pattern07_0034(PLW* wk) {
    const Pattern_Step script[5] = { [0] = STEP(Normal_Attack, 9, 0x100),
                                     [1] = STEP(Normal_Attack, 0xB, 0x202),
                                     [2] = STEP(Normal_Attack, 0xB, 0x200),
                                     [3] = STEP_NOARG(Lever_Off),
                                     [4] = STEP(Look, 0) };
    Run_Pattern(wk, script, 5);
}

void Pattern07_0035(PLW* wk) {
    active_pattern_normal_attack(wk, 8, 0x20);
}

void Pattern07_0036(PLW* wk) {
    active_pattern_normal_attack(wk, 8, 0x42);
}

void Pattern07_0037(PLW* wk) {
    const Pattern_Step script[3] = { [0] = STEP(Lever_Attack, 8, 0, 0x110),
                                     [1] = STEP(Search_Back_Term, 0x60, 1, -1),
                                     [2] = STEP(Command_Attack, 8, 1, 0xA, -1) };
    Run_Pattern(wk, script, 3);
}

void Pattern07_0038(PLW* wk) {
    const Pattern_Step script[5] = { [0] = STEP(SA_Term, 0x35, 0x36, 0x37, 0),
                                     [1] = STEP_NOARG(Pierce_On),
                                     [2] = STEP(Adjust_Attack, 0xB, 0x20),
                                     [3] = STEP(Normal_Attack, 0xB, 0x202),
                                     [4] = STEP(Lever_Attack, 8, 0, 0x400) };
    Run_Pattern(wk, script, 5);
}

void Pattern07_0039(PLW* wk) {
    active_pattern_command_attack_j_command_attack(
        wk, &(Command_Attack_Args) { 8, 0, 0xA, -1 }, &(Command_Attack_Args) { 8, 0x1C, 0xA, -1 }
    );
}

void Pattern07_0040(PLW* wk) {
    active_pattern_normal_attack_j_command_attack(wk, 9, 0x202, &(Command_Attack_Args) { 8, 0x1C, 0xA, -1 });
}

void Pattern07_0041(PLW* wk) {
    pattern_normal_attack_j_command_attack_2(
        wk, &(Normal_Attack_Step) { 0xB, 0x102 }, 0x20, &(Command_Attack_Args) { 8, 0x20, 0xA, -1 }
    );
}

void Pattern07_0042(PLW* wk) {
    const Pattern_Step script[4] = { [0] = STEP(Normal_Attack, 8, 0x12),
                                     [1] = STEP(Normal_Attack, 8, 0x12),
                                     [2] = STEP(Normal_Attack, 8, 0x202),
                                     [3] = STEP(J_Command_Attack, 8, 0x1C, 0xA, -1) };
    Run_Pattern(wk, script, 4);
}

void Pattern07_0043(PLW* wk) {
    active_pattern_jump_attack_term(wk, &(Jump_Term_Args) { -0x7FA0, -0x7FC0, 8, 0x40, 0, -1, 0x30, 0x4020 });
}

void Pattern07_0044(PLW* wk) {
    active_pattern_jump_attack_term(wk, &(Jump_Term_Args) { -0x7FA0, -0x7FC0, 8, 0x40, 0, -1, 0x30, 0x400 });
}

void Pattern07_0045(PLW* wk) {
    active_pattern_jump_attack_term(wk, &(Jump_Term_Args) { -0x7FA0, -0x7FC0, 8, 0x400, 0, -1, -1, -1 });
}

void Pattern07_0046(PLW* wk) {
    active_pattern_(wk);
}

void Pattern07_0047(PLW* wk) {
    active_pattern_hi_jump_command_attack_term(
        wk, &(JCA_Term_Args) { 8, 0x2E, 9, -1, -0x7FA0, 0x38, 0x0, -1, 0x30, 0x400 }
    );
}

void Pattern07_0048(PLW* wk) {
    const Pattern_Step script[3] = { [0] = STEP(Normal_Attack, 8, 0x20),
                                     [1] = STEP(Lever_Attack, 8, 0, 0x100),
                                     [2] = STEP(Jump_Command_Attack_Term, 8, 0x2E, 0xA, -1, -1, 0x38, 1, -1, -1, -1) };
    Run_Pattern(wk, script, 3);
}

void Pattern07_0049(PLW* wk) {
    const Pattern_Step script[4] = { [0] = STEP(Hi_Jump_Attack_Term, -1, -0x7FC8, 8, 0x200, 0, -0x7FA8, -1, 0x200),
                                     [1] = STEP(Lever_Attack, 9, 0, 0x100),
                                     [2] = STEP(Lever_Attack, 9, 0, 0x100),
                                     [3] = STEP(Normal_Attack, 8, 0x200) };
    Run_Pattern(wk, script, 4);
}

void Pattern07_0050(PLW* wk) {
    active_pattern_hi_jump_attack(wk);
}

void Pattern07_0051(PLW* wk) {
    pattern_hi_jump_attack_term_command_attack(
        wk,
        &(Hi_Jump_Term_Args) { -1, -0x7FC8, 8, 0x20, 0, -0x7FA8, -1, 0x200 },
        &(Command_Attack_Args) { 8, 0x1D, 0xA, -1 }
    );
}

void Pattern07_0052(PLW* wk) {
    active_pattern_hi_jump_command_attack_term(wk, &(JCA_Term_Args) { 8, 0x8126, 0xA, -1, -1, 0x30, 0, -1, -1, -1 });
}

void Pattern07_0053(PLW* wk) {
    active_pattern_branch_unit_area(wk, &(Branch_Menu_Args) { 2, 0x38, 0x3A, 0x3A, 0x3A });
}

void Pattern07_0054(PLW* wk) {
    active_pattern_command_attack(wk, &(Command_Attack_Args) { 8, 0x8015, 0xA, -1 });
}

void Pattern07_0055(PLW* wk) {
    active_pattern_command_attack(wk, &(Command_Attack_Args) { 8, 0x8014, 0xA, -1 });
}

void Pattern07_0056(PLW* wk) {
    active_pattern_jump_command_attack_term(wk, &(JCA_Term_Args) { 8, 0x8126, 9, -1, -1, 0x40, 1, -1, -1, -1 });
}

void Pattern07_0057(PLW* wk) {
    active_pattern_jump_command_attack_term(wk, &(JCA_Term_Args) { 8, 0x8126, 9, -1, -1, 0x40, 2, -1, -1, -1 });
}

void Pattern07_0058(PLW* wk) {
    active_pattern_jump_command_attack_term(wk, &(JCA_Term_Args) { 8, 0x8126, 0xA, -1, -1, 0x30, 2, -1, -1, -1 });
}

void Pattern07_0059(PLW* wk) {
    const Pattern_Step script[4] = { [0] = STEP(Command_Attack, 8, 0, 0xB, -1),
                                     [1] = STEP(Command_Attack, 8, 0x1D, 9, -1),
                                     [2] = STEP(Normal_Attack, 8, 0x200),
                                     [3] = STEP(Normal_Attack, 8, 0x400) };
    Run_Pattern(wk, script, 4);
}

void Pattern07_0060(PLW* wk) {
    active_pattern_walk_2(wk, 0x15, 0x14, 0x10);
}

void Pattern07_0061(PLW* wk) {
    const Pattern_Step script[4] = { [0] = STEP(Walk, 1, 0x14, 0),
                                     [1] = STEP(Walk, 0, 0x10, 0),
                                     [2] = STEP(Walk, 1, 0x18, 0),
                                     [3] = STEP(Walk, 0, 0x10, 0) };
    Run_Pattern(wk, script, 4);
}

void Pattern07_0062(PLW* wk) {
    const Pattern_Step script[4] = {
        [0] = STEP(Walk, 0, 0x10, 0), [1] = STEP(Walk, 1, 0x18, 0), [2] = STEP(Wait, 0x10), [3] = STEP(Walk, 0, 0x10, 0)
    };
    Run_Pattern(wk, script, 4);
}

void Pattern07_0063(PLW* wk) {
    active_pattern_em_term_command_attack(
        wk, &(EM_Term_Params) { -0x7F98, 0, 4, 2, 0 }, &(Command_Attack_Args) { 8, 0, 0xA, -1 }
    );
}

void Pattern07_0064(PLW* wk) {
    active_pattern_j_command_attack(wk, &(Command_Attack_Args) { 8, 0x1F, 0xA, -1 });
}

void Pattern07_0065(PLW* wk) {
    active_pattern_j_command_attack(wk, &(Command_Attack_Args) { 8, 0x1F, 9, -1 });
}

void Pattern07_0066(PLW* wk) {
    active_pattern_j_command_attack(wk, &(Command_Attack_Args) { 8, 0x1F, 8, -1 });
}

void Pattern07_0067(PLW* wk) {
    active_pattern_command_attack(wk, &(Command_Attack_Args) { 8, 0x22, 8, -1 });
}

void Pattern07_0068(PLW* wk) {
    active_pattern_command_attack(wk, &(Command_Attack_Args) { 8, 0x22, 0xA, -1 });
}

void Pattern07_0069(PLW* wk) {
    active_pattern_command_attack_2(
        wk, &(Command_Attack_Args) { 8, 0x22, 0xA, -1 }, &(Command_Attack_Args) { 8, 0x20, 8, -1 }
    );
}

void Pattern07_0070(PLW* wk) {
    pattern_command_attack_em_term_command_attack(wk);
}

void Pattern07_0071(PLW* wk) {
    pattern_command_attack_em_term_sa_term(wk);
}

void Pattern07_0072(PLW* wk) {
    active_pattern_branch_unit_area(wk, &(Branch_Menu_Args) { 2, 0x49, 0x49, 0x4A, 0x4B });
}

void Pattern07_0073(PLW* wk) {
    active_pattern_command_attack(wk, &(Command_Attack_Args) { 8, 0x8126, 8, -1 });
}

void Pattern07_0074(PLW* wk) {
    active_pattern_command_attack(wk, &(Command_Attack_Args) { 8, 0x8126, 9, -1 });
}

void Pattern07_0075(PLW* wk) {
    active_pattern_command_attack(wk, &(Command_Attack_Args) { 8, 0x8126, 0xA, -1 });
}

void (*const Pattern07_Tbl[76])(PLW*) = {
    Pattern07_0000, Pattern07_0001, Pattern07_0002, Pattern07_0003, Pattern07_0004, Pattern07_0005, Pattern07_0006,
    Pattern07_0007, Pattern07_0008, Pattern07_0009, Pattern07_0010, Pattern07_0011, Pattern07_0012, Pattern07_0013,
    Pattern07_0014, Pattern07_0015, Pattern07_0016, Pattern07_0017, Pattern07_0018, Pattern07_0019, Pattern07_0020,
    Pattern07_0021, Pattern07_0022, Pattern07_0023, Pattern07_0024, Pattern07_0025, Pattern07_0026, Pattern07_0027,
    Pattern07_0028, Pattern07_0029, Pattern07_0030, Pattern07_0031, Pattern07_0032, Pattern07_0033, Pattern07_0034,
    Pattern07_0035, Pattern07_0036, Pattern07_0037, Pattern07_0038, Pattern07_0039, Pattern07_0040, Pattern07_0041,
    Pattern07_0042, Pattern07_0043, Pattern07_0044, Pattern07_0045, Pattern07_0046, Pattern07_0047, Pattern07_0048,
    Pattern07_0049, Pattern07_0050, Pattern07_0051, Pattern07_0052, Pattern07_0053, Pattern07_0054, Pattern07_0055,
    Pattern07_0056, Pattern07_0057, Pattern07_0058, Pattern07_0059, Pattern07_0060, Pattern07_0061, Pattern07_0062,
    Pattern07_0063, Pattern07_0064, Pattern07_0065, Pattern07_0066, Pattern07_0067, Pattern07_0068, Pattern07_0069,
    Pattern07_0070, Pattern07_0071, Pattern07_0072, Pattern07_0073, Pattern07_0074, Pattern07_0075
};
