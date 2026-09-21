/**
 * @file pass04_3.c
 * COM Passive: Dudley
 * Pattern scripts from Passive04_0133 on.
 */

#include "sf33rd/Source/Game/com/passive/pass04.h"
#include "sf33rd/Source/Game/com/passive/pass04_internal.h"
#include "sf33rd/Source/Game/com/patterns/com_pattern_run.h"
#include "sf33rd/Source/Game/com/patterns/com_patterns.h"
#include "common.h"
#include "sf33rd/Source/Game/com/com_sub.h"
#include "sf33rd/Source/Game/engine/workuser.h"

void Passive04_0133(PLW* wk) {
    pattern_em_term_sa_term_j_command_attack(
        wk,
        &(EM_Term_Params){-0x7F90, -1, 0, 1, -1},
        &(SA_Term_Args){0x35, 0x36, 0x37, 0},
        &(Command_Attack_Args){8, 0x1C, 10, -1}
    );
}

void Passive04_0134(PLW* wk) {
    active_pattern_em_term_j_command_attack(
        wk,
        &(EM_Term_Params){-0x7F80, -1, 0, 1, -1},
        &(Command_Attack_Args){8, 0x1C, 9, -1}
    );
}

void Passive04_0135(PLW* wk) {
    active_pattern_em_term_j_command_attack(
        wk,
        &(EM_Term_Params){-0x7F80, -1, 0, 1, -1},
        &(Command_Attack_Args){8, 0x1C, 9, 0x70}
    );
}

void Passive04_0136(PLW* wk) {
    pattern_jump(wk, 0);
}

void Passive04_0137(PLW* wk) {
    active_pattern_command_attack(wk, &(Command_Attack_Args){8, 0x21, 8, -1});
}

void Passive04_0138(PLW* wk) {
    active_pattern_command_attack(wk, &(Command_Attack_Args){8, 0x21, 10, 0x700});
}

void Passive04_0139(PLW* wk) {
    const Pattern_Step script[2] = { [0] = STEP(Approach_Walk, 0xB3, 2),
                                     [1] =
                                         STEP(Hi_Jump_Attack_Term, -0x7FA0, -0x7FA0, 8, 0x400, 0, -0x7F78, -1, 0x40) };
    Run_Pattern(wk, script, 2);
}

void Passive04_0140(PLW* wk) {
    const Pattern_Step script[3] = { [0] = STEP(Approach_Walk, 0xB3, 2),
                                     [1] = STEP(Hi_Jump_Attack_Term, -0x7FA0, -0x7FA0, 8, 0x400, 0, -0x7F78, -1, 0x40),
                                     [2] = STEP(Normal_Attack, 8, 0x400) };
    Run_Pattern(wk, script, 3);
}

void Passive04_0141(PLW* wk) {
    const Pattern_Step script[4] = { [0] = STEP(Approach_Walk, 0xB3, 2),
                                     [1] = STEP(Hi_Jump_Attack_Term, -0x7FA0, -0x7FA0, 8, 0x400, 0, -0x7F78, -1, 0x40),
                                     [2] = STEP(SA_Term, 0x35, 0x36, 0x37, 0),
                                     [3] = STEP(J_Command_Attack, 8, 0x1C, 0xA, -1) };
    Run_Pattern(wk, script, 4);
}
