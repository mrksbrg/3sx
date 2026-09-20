/**
 * @file com_pattern_run.c
 * Recipe J - the pattern skeletons' dispatch table and its interpreter.
 *
 * The adapters are generated from com_sub.h's own signatures, so every value
 * still reaches its call in the call's own parameter order, with the call's
 * own types. See tools/pattern_table.py.
 */

#include "sf33rd/Source/Game/com/patterns/com_pattern_run.h"

#include "common.h"
#include "sf33rd/Source/Game/com/com_sub.h"
#include "sf33rd/Source/Game/engine/workuser.h"

s32 Run_Pattern_Steps(PLW* wk, const Pattern_Step* steps, s32 count) {
    s32 step = CP_Index[wk->wu.id][0];

    if (step >= count) {
        return 0;
    }

    if (steps[step].fn == NULL) {
        return 0;
    }

    steps[step].fn(wk, steps[step].arg);
    return 1;
}

void Run_Pattern(PLW* wk, const Pattern_Step* steps, s32 count) {
    if (!Run_Pattern_Steps(wk, steps, count)) {
        End_Pattern(wk);
    }
}

void Step_Adjust_Attack(PLW* wk, const void* arg) {
    const Adjust_Attack_Step* a = arg;

    Adjust_Attack(wk, a->Reaction, a->Lever_Data);
}

void Step_Approach_Walk(PLW* wk, const void* arg) {
    const Approach_Walk_Step* a = arg;

    Approach_Walk(wk, a->Target_Pos, a->Option);
}

void Step_Branch_Unit_Area(PLW* wk, const void* arg) {
    Branch_Unit_Area(wk, arg);
}

void Step_Branch_Wait_Area(PLW* wk, const void* arg) {
    Branch_Wait_Area(wk, arg);
}

void Step_Check_EX(PLW* wk, const void* arg) {
    const Check_EX_Step* a = arg;

    Check_EX(wk, a->Next_Action, a->Next_Menu);
}

void Step_Check_SA(PLW* wk, const void* arg) {
    const Check_SA_Step* a = arg;

    Check_SA(wk, a->Next_Action, a->Next_Menu);
}

void Step_Check_SA_Full(PLW* wk, const void* arg) {
    const Check_SA_Full_Step* a = arg;

    Check_SA_Full(wk, a->Next_Action, a->Next_Menu);
}

void Step_Check_Store_Lever(PLW* wk, const void* arg) {
    const Check_Store_Lever_Step* a = arg;

    Check_Store_Lever(wk, a->Tech_Number, a->Next_Action, a->Next_Menu);
}

void Step_Com_Random_Select(PLW* wk, const void* arg) {
    const Com_Random_Select_Step* a = arg;

    Com_Random_Select(wk, a->p, a->Rnd_Type);
}

void Step_Command_Attack(PLW* wk, const void* arg) {
    Command_Attack(wk, arg);
}

void Step_EM_Term(PLW* wk, const void* arg) {
    EM_Term(wk, arg);
}

void Step_ETC_Term(PLW* wk, const void* arg) {
    const ETC_Term_Step* a = arg;

    ETC_Term(wk, a->Exit_No, a->Next_Action, a->Next_Menu);
}

void Step_Forced_Guard(PLW* wk, const void* arg) {
    const Forced_Guard_Step* a = arg;

    Forced_Guard(wk, a->Guard_Type);
}

void Step_Hi_Jump(PLW* wk, const void* arg) {
    const Hi_Jump_Step* a = arg;

    Hi_Jump(wk, a->Pl_Number, a->Jump_Dir);
}

void Step_Hi_Jump_Attack(PLW* wk, const void* arg) {
    Hi_Jump_Attack(wk, arg);
}

void Step_Hi_Jump_Attack_Term(PLW* wk, const void* arg) {
    Hi_Jump_Attack_Term(wk, arg);
}

void Step_Hi_Jump_Command_Attack_Term(PLW* wk, const void* arg) {
    Hi_Jump_Command_Attack_Term(wk, arg);
}

void Step_J_Command_Attack(PLW* wk, const void* arg) {
    J_Command_Attack(wk, arg);
}

void Step_Jump(PLW* wk, const void* arg) {
    const Jump_Step* a = arg;

    Jump(wk, a->Time);
}

void Step_Jump_Attack(PLW* wk, const void* arg) {
    Jump_Attack(wk, arg);
}

void Step_Jump_Attack_Term(PLW* wk, const void* arg) {
    Jump_Attack_Term(wk, arg);
}

void Step_Jump_Command_Attack_Term(PLW* wk, const void* arg) {
    Jump_Command_Attack_Term(wk, arg);
}

void Step_Keep_Away(PLW* wk, const void* arg) {
    const Keep_Away_Step* a = arg;

    Keep_Away(wk, a->Target_Pos, a->Option);
}

void Step_Keep_Status(PLW* wk, const void* arg) {
    const Keep_Status_Step* a = arg;

    Keep_Status(wk, a->Lever_Data, a->Option_Data);
}

void Step_Lever_Attack(PLW* wk, const void* arg) {
    const Lever_Attack_Step* a = arg;

    Lever_Attack(wk, a->Reaction, a->Lever, a->Lever_Data);
}

void Step_Lever_Attack_SP(PLW* wk, const void* arg) {
    Lever_Attack_SP(wk, arg);
}

void Step_Lever_Off(PLW* wk, const void* arg) {
    (void)arg;
    Lever_Off(wk);
}

void Step_Lever_On(PLW* wk, const void* arg) {
    const Lever_On_Step* a = arg;

    Lever_On(wk, a->LR_Lever, a->UD_Lever);
}

void Step_Look(PLW* wk, const void* arg) {
    const Look_Step* a = arg;

    Look(wk, a->Time);
}

void Step_Next_Another_Menu(PLW* wk, const void* arg) {
    const Next_Another_Menu_Step* a = arg;

    Next_Another_Menu(wk, a->Next_Action, a->Next_Menu);
}

void Step_Next_Be_Flip(PLW* wk, const void* arg) {
    const Next_Be_Flip_Step* a = arg;

    Next_Be_Flip(wk, a->xx);
}

void Step_Normal_Attack(PLW* wk, const void* arg) {
    const Normal_Attack_Step* a = arg;

    Normal_Attack(wk, a->Reaction, a->Lever_Data);
}

void Step_Normal_Attack_SP(PLW* wk, const void* arg) {
    const Normal_Attack_SP_Step* a = arg;

    Normal_Attack_SP(wk, a->Reaction, a->Lever_Data, a->Time);
}

void Step_ORO_HJCA_Term(PLW* wk, const void* arg) {
    ORO_HJCA_Term(wk, arg);
}

void Step_ORO_JA_Term(PLW* wk, const void* arg) {
    ORO_JA_Term(wk, arg);
}

void Step_ORO_JCA_Term(PLW* wk, const void* arg) {
    ORO_JCA_Term(wk, arg);
}

void Step_Pierce_On(PLW* wk, const void* arg) {
    (void)arg;
    Pierce_On(wk);
}

void Step_Provoke(PLW* wk, const void* arg) {
    const Provoke_Step* a = arg;

    Provoke(wk, a->Lever);
}

void Step_Push_Shot(PLW* wk, const void* arg) {
    const Push_Shot_Step* a = arg;

    Push_Shot(wk, a->Power_Level);
}

void Step_Rapid_Command_Attack(PLW* wk, const void* arg) {
    Rapid_Command_Attack(wk, arg);
}

void Step_SA_Term(PLW* wk, const void* arg) {
    SA_Term(wk, arg);
}

void Step_SHELL_Term(PLW* wk, const void* arg) {
    SHELL_Term(wk, arg);
}

void Step_Search_Back_Term(PLW* wk, const void* arg) {
    const Search_Back_Term_Step* a = arg;

    Search_Back_Term(wk, a->Move_Value, a->Next_Action, a->Next_Menu);
}

void Step_Short_Range_Attack(PLW* wk, const void* arg) {
    Short_Range_Attack(wk, arg);
}

void Step_Turn_Over_On(PLW* wk, const void* arg) {
    (void)arg;
    Turn_Over_On(wk);
}

void Step_VS_Jump_Guard(PLW* wk, const void* arg) {
    (void)arg;
    VS_Jump_Guard(wk);
}

void Step_Wait(PLW* wk, const void* arg) {
    const Wait_Step* a = arg;

    Wait(wk, a->Time);
}

void Step_Wait_Attack_Complete(PLW* wk, const void* arg) {
    const Wait_Attack_Complete_Step* a = arg;

    Wait_Attack_Complete(wk, a->Lever_Data, a->Option);
}

void Step_Wait_Get_Up(PLW* wk, const void* arg) {
    const Wait_Get_Up_Step* a = arg;

    Wait_Get_Up(wk, a->Lever_Data, a->Option);
}

void Step_Wait_Lie(PLW* wk, const void* arg) {
    const Wait_Lie_Step* a = arg;

    Wait_Lie(wk, a->Lever_Data);
}

void Step_Walk(PLW* wk, const void* arg) {
    const Walk_Step* a = arg;

    Walk(wk, a->Lever, a->Time, a->unused);
}
