/**
 * @file com_patterns_2step_3.c
 * COM: pattern skeletons shared by every character
 *
 * The two-step patterns. Part 3 of 3, in name order.
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

void pattern_walk_com_random_select(PLW* wk, s16 time, const Branch_Menu_Args* p, s16 rnd_type) {
    const Pattern_Step script[2] = { [0] = STEP(Walk, 1, time, -1), [1] = STEP(Com_Random_Select, p, rnd_type) };
    Run_Pattern(wk, script, 2);
}

void pattern_walk_com_random_select_2(PLW* wk) {
    const Pattern_Step script[2] = {
        [0] = STEP(Walk, 1, 0x30, 0),
        [1] = STEP(Com_Random_Select, &(Branch_Menu_Args) { 6, 0x59, 0x59, 0x59, 0x5A }, 0)
    };
    Run_Pattern(wk, script, 2);
}
