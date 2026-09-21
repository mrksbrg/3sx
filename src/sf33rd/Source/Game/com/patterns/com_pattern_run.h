/*
 * Recipe J - the pattern skeletons' dispatch table and its interpreter.
 *
 * A COM pattern script is a step counter and one engine call per step. The
 * skeletons used to spell that as a switch whose every arm was a single call;
 * they spell it as this table now, keyed by the same step numbers the case
 * labels held.
 */

#ifndef COM_PATTERN_RUN_H
#define COM_PATTERN_RUN_H

#include "sf33rd/Source/Game/com/patterns/com_pattern_args.h"
#include "structs.h"
#include "types.h"

/* One step: the engine call, and the arguments it was written with. */
typedef void (*Pattern_Step_Fn)(PLW* wk, const void* arg);

typedef struct {
    Pattern_Step_Fn fn;
    const void* arg;
} Pattern_Step;

/* One step, written the way the arm that held it was: the engine call by
 * name, then the values it was called with, in its own parameter order.
 * STEP_WITH takes one of the engine's own argument objects instead, and
 * STEP_NOARG the calls that take nothing but the work pointer. */
#define STEP(call, ...)                                                                                                \
    {                                                                                                                  \
        Step_##call, &(const call##_Step) {                                                                            \
            __VA_ARGS__                                                                                                \
        }                                                                                                              \
    }
#define STEP_WITH(call, ...) { Step_##call, (__VA_ARGS__) }
#define STEP_NOARG(call) { Step_##call, NULL }

/* Runs the step the COM step counter selects, then the default arm the
 * switch sent every other index to: past the last step, or a hole the step
 * numbers left. Run_Pattern supplies the End_Pattern that almost every
 * script's default arm held; Run_Pattern_Or takes the continuation the rest
 * of them chained to, so that arm stays data like all the others. */
void Run_Pattern(PLW* wk, const Pattern_Step* steps, s32 count);
void Run_Pattern_Or(PLW* wk, const Pattern_Step* steps, s32 count, void (*otherwise)(PLW* wk));

void Step_Adjust_Attack(PLW* wk, const void* arg);
void Step_Approach_Walk(PLW* wk, const void* arg);
void Step_Branch_Unit_Area(PLW* wk, const void* arg);
void Step_Branch_Wait_Area(PLW* wk, const void* arg);
void Step_Check_BOSS(PLW* wk, const void* arg);
void Step_Check_BOSS_EX(PLW* wk, const void* arg);
void Step_Check_EX(PLW* wk, const void* arg);
void Step_Check_SA(PLW* wk, const void* arg);
void Step_Check_SA_Full(PLW* wk, const void* arg);
void Step_Check_Store_Lever(PLW* wk, const void* arg);
void Step_Com_Random_Select(PLW* wk, const void* arg);
void Step_Command_Attack(PLW* wk, const void* arg);
void Step_EM_Term(PLW* wk, const void* arg);
void Step_ETC_Term(PLW* wk, const void* arg);
void Step_Forced_Guard(PLW* wk, const void* arg);
void Step_Hi_Jump(PLW* wk, const void* arg);
void Step_Hi_Jump_Attack(PLW* wk, const void* arg);
void Step_Hi_Jump_Attack_Term(PLW* wk, const void* arg);
void Step_Hi_Jump_Command_Attack_Term(PLW* wk, const void* arg);
void Step_J_Command_Attack(PLW* wk, const void* arg);
void Step_Jump(PLW* wk, const void* arg);
void Step_Jump_Attack(PLW* wk, const void* arg);
void Step_Jump_Attack_Term(PLW* wk, const void* arg);
void Step_Jump_Command_Attack_Term(PLW* wk, const void* arg);
void Step_Keep_Away(PLW* wk, const void* arg);
void Step_Keep_Status(PLW* wk, const void* arg);
void Step_Lever_Attack(PLW* wk, const void* arg);
void Step_Lever_Attack_SP(PLW* wk, const void* arg);
void Step_Lever_Off(PLW* wk, const void* arg);
void Step_Lever_On(PLW* wk, const void* arg);
void Step_Look(PLW* wk, const void* arg);
void Step_Next_Another_Menu(PLW* wk, const void* arg);
void Step_Next_Be_Flip(PLW* wk, const void* arg);
void Step_Next_Be_Passive(PLW* wk, const void* arg);
void Step_Normal_Attack(PLW* wk, const void* arg);
void Step_Normal_Attack_SP(PLW* wk, const void* arg);
void Step_ORO_HJA_Term(PLW* wk, const void* arg);
void Step_ORO_HJCA_Term(PLW* wk, const void* arg);
void Step_ORO_JA_Term(PLW* wk, const void* arg);
void Step_ORO_JCA_Term(PLW* wk, const void* arg);
void Step_Only_Shot(PLW* wk, const void* arg);
void Step_Pierce_On(PLW* wk, const void* arg);
void Step_Provoke(PLW* wk, const void* arg);
void Step_Push_Shot(PLW* wk, const void* arg);
void Step_Rapid_Command_Attack(PLW* wk, const void* arg);
void Step_SA_Term(PLW* wk, const void* arg);
void Step_SHELL_Term(PLW* wk, const void* arg);
void Step_Search_Back_Term(PLW* wk, const void* arg);
void Step_Setup_DENJIN_LEVEL(PLW* wk, const void* arg);
void Step_Short_Range_Attack(PLW* wk, const void* arg);
void Step_Turn_Over_On(PLW* wk, const void* arg);
void Step_VS_Jump_Guard(PLW* wk, const void* arg);
void Step_Wait(PLW* wk, const void* arg);
void Step_Wait_Attack_Complete(PLW* wk, const void* arg);
void Step_Wait_Get_Up(PLW* wk, const void* arg);
void Step_Wait_Lie(PLW* wk, const void* arg);
void Step_Walk(PLW* wk, const void* arg);

#endif
