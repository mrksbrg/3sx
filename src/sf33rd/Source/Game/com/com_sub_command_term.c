/**
 * @file com_sub_command_term.c
 * CPU Controlled Character command attack Term state machines.
 *
 * Split out of com_sub_command.c unchanged - no function body was edited.
 */

#include "sf33rd/Source/Game/com/com_sub.h"
#include "common.h"
#include "sf33rd/AcrSDK/common/pad.h"
#include "sf33rd/Source/Game/com/active/ac0000.h"
#include "sf33rd/Source/Game/com/active/ac0001.h"
#include "sf33rd/Source/Game/com/active/ac0002.h"
#include "sf33rd/Source/Game/com/active/ac0003.h"
#include "sf33rd/Source/Game/com/active/ac0004.h"
#include "sf33rd/Source/Game/com/ck_pass.h"
#include "sf33rd/Source/Game/com/com_data.h"
#include "sf33rd/Source/Game/com/com_datu.h"
#include "sf33rd/Source/Game/com/com_pl.h"
#include "sf33rd/Source/Game/com/follow/fl_com00.h"
#include "sf33rd/Source/Game/com/follow/fl_com02.h"
#include "sf33rd/Source/Game/com/passive/pass0000.h"
#include "sf33rd/Source/Game/com/passive/pass0001.h"
#include "sf33rd/Source/Game/com/passive/pass0002.h"
#include "sf33rd/Source/Game/com/passive/pass0003.h"
#include "sf33rd/Source/Game/debug/debug_config.h"
#include "sf33rd/Source/Game/effect/effect.h"
#include "sf33rd/Source/Game/engine/cmd_data.h"
#include "sf33rd/Source/Game/engine/cmd_main.h"
#include "sf33rd/Source/Game/engine/hitcheck.h"
#include "sf33rd/Source/Game/engine/plcnt.h"
#include "sf33rd/Source/Game/engine/pls02.h"
#include "sf33rd/Source/Game/engine/pls03.h"
#include "sf33rd/Source/Game/engine/workuser.h"
#include "sf33rd/Source/Game/screen/vs_shell.h"
#include "sf33rd/Source/Game/stage/bg.h"
#include "sf33rd/Source/Game/system/sysdir.h"
#include "sf33rd/Source/Game/system/work_sys.h"
#include "structs.h"
#include "sf33rd/Source/Game/com/com_sub_internal.h"


/* Load the command's tech script, once the character is free to act.
 * Jump_Command_Attack_Term guards this with spmv_ng_flag first and ORO_JCA_Term
 * does not; that guard is the only difference between their openings. */
static void Command_Term_Open(PLW* wk, u16 Tech_Number) {
    Lever_Buff[wk->wu.id] = Lever_LR[wk->wu.id];
    if (!Check_Free_To_Act(wk)) {
        return;
    }

    Continue_Menu[wk->wu.id] = 0;
    CP_Index[wk->wu.id][1]++;
    if (cmd_sel[wk->wu.id]) {
        Tech_Address[wk->wu.id] = player_CMD[wk->player_number][Tech_Number & 0xFF];
    } else {
        Tech_Address[wk->wu.id] = player_cmd[wk->player_number][Tech_Number & 0xFF];
    }
    Check_First_Menu(wk);
}

/* The landing opcode step shared by the command Term functions. Distinct from
 * Landing_Tech_Step in com_sub_jump.c, which passes different arguments to
 * Command_Type_00. The inner switch has only a default group; preserved. */
static void Command_Term_Landing_Step(PLW* wk, u16 Tech_Number, s16 Power_Level, s16 Ex_Shot) {
    switch (Tech_Address[wk->wu.id][Tech_Index[wk->wu.id]]) {
    default:
    case 1:
    case 10:
        if (Command_Type_00(wk, Power_Level & 0xF, Tech_Number, Ex_Shot) == -1) {
            CP_Index[wk->wu.id][1] = 0x63;
        }
        break;
    }
}

/* Hold while airborne: latch any hit, then watch for the landing. The two jump
 * Terms mask the reaction with 0xFFF and the two ORO Terms with 0x7F - the only
 * difference between the four copies. */
static void Command_Term_Hold(PLW* wk, s16 Reaction, s16 mask) {
    if (wk->wu.hf.hit.player) {
        Stock_Hit_Flag[wk->wu.id] = wk->wu.hf.hit.player;
    }
    Check_Landed(wk, Reaction & mask);
}

/* The rise arm the two ORO Terms share: climb, or hold the pooled lever and
 * reset the descent timer. */
static void ORO_Term_Rise(PLW* wk) {
    if (wk->wu.xyz[1].disp.pos > 0) {
        CP_Index[wk->wu.id][1]++;
        return;
    }

    Lever_Buff[wk->wu.id] = Lever_Pool[wk->wu.id];
    Timer_00[wk->wu.id] = 2;
}

/* The second jump the two ORO Terms take once the height gate passes. */
static void ORO_Term_Climb(PLW* wk, const ORO_JCA_Term_Args* a) {
    Check_Air_Guard(wk);

    if (Check_Landed(wk, a->Reaction) != 0) {
        return;
    }
    if (Check_VS_Air_Attack(wk, a->RJX, a->RJY, a->JLD) != 0) {
        return;
    }
    if (Check_Com_Add_Y(wk, wk->wu.xyz[1].disp.pos, a->JY) == 0) {
        return;
    }

    Jump_Init(wk, a->Jump_Dir2);
    if (--Timer_00[wk->wu.id] == 0) {
        CP_Index[wk->wu.id][1]++;
    }
}

static void JCA_Term_Begin(PLW* wk, u16 Tech_Number) {
    if (Check_Passive(wk) != 0) {
        return;
    }

    if (wk->spmv_ng_flag & 0x30000) {
        Next_Be_Free(wk);
        return;
    }

    Command_Term_Open(wk, Tech_Number);
}

/* The countdown both plain command attack launches share, and the two steps
 * they take once it reaches zero. Non-zero when the jump goes out this frame.
 * HJCA_Term_Launch is deliberately not a caller: it counts down a different
 * Combo_Speed slot - see the note on that function. */
static s32 JCA_Launch_Ready(PLW* wk) {
    if (Check_Passive(wk) != 0) {
        return 0;
    }
    if (--Combo_Speed[wk->wu.id] != 0) {
        return 0;
    }

    CP_Index[wk->wu.id][1]++;
    Tech_Index[wk->wu.id] = 0xC;

    return 1;
}

static void JCA_Term_Launch(PLW* wk, u16 Tech_Number, s16 Jump_Dir) {
    if (!JCA_Launch_Ready(wk)) {
        return;
    }

    Jump_Init(wk, Jump_Dir);
    Check_Rapid(wk, Tech_Number);

    if (Check_Diagonal_Shell(wk) != 0) {
        Next_Be_Free(wk);
    }
}

static void JCA_Term_Rise(PLW* wk) {
    Lever_Buff[wk->wu.id] = Lever_Pool[wk->wu.id];
    if (wk->wu.xyz[1].disp.pos > 0) {
        CP_Index[wk->wu.id][1]++;
    }
}

static void JCA_Term_Approach(PLW* wk, const JCA_Term_Args* a) {
    const Attack_Range_Args r = { a->Reaction, a->RX, a->RY, a->JRX, a->JRY, a->JLD };

    Check_Air_Guard(wk);
    Stock_Hit_Flag[wk->wu.id] = wk->wu.hf.hit.player;

    if (Attack_Range_Gates(wk, &r) == 0) {
        return;
    }

    CP_Index[wk->wu.id][1] += 2;
}

static void JCA_Term_Land(PLW* wk, const Command_Landing_Args* L) {
    Lever_Buff[wk->wu.id] = Lever_LR[wk->wu.id];
    if (Check_Landed(wk, L->Reaction) != 0) {
        return;
    }

    Command_Term_Landing_Step(wk, L->Tech_Number, L->Power_Level, L->Ex_Shot);
}

static void JCA_Term_End(PLW* wk, s16 Reaction) {
    Stock_Hit_Flag[wk->wu.id] = wk->wu.hf.hit.player;
    Rapid_Sub(wk);
    Check_Landed(wk, Reaction & 0xFFF);
}

void Jump_Command_Attack_Term(PLW* wk, const JCA_Term_Args* a) {
    const Command_Landing_Args L = { a->Reaction, a->Tech_Number, a->Power_Level, a->Ex_Shot };

    switch (CP_Index[wk->wu.id][1]) {

    case 0:
        JCA_Term_Begin(wk, a->Tech_Number);
        break;

    case 1:
        JCA_Term_Launch(wk, a->Tech_Number, a->Jump_Dir);
        break;

    case 2:
        JCA_Term_Rise(wk);
        break;

    case 3:
        JCA_Term_Approach(wk, a);
        break;

    case 4:
        Command_Term_Hold(wk, a->Reaction, 0xFFF);
        break;

    case 5:
        JCA_Term_Land(wk, &L);
        break;

    default:
        JCA_Term_End(wk, a->Reaction);
        break;
    }
}

static void HJCA_Term_Begin(PLW* wk, u16 Tech_Number) {
    Lever_Buff[wk->wu.id] = Lever_LR[wk->wu.id];
    if (Check_Passive(wk) != 0) {
        return;
    }

    if (wk->spmv_ng_flag & 0x30000) {
        Next_Be_Free(wk);
        return;
    }

    if (Check_Start_Hi_Jump(wk) != 0) {
        return;
    }

    Continue_Menu[wk->wu.id] = 0;
    CP_Index[wk->wu.id][1]++;
    if (cmd_sel[wk->wu.id]) {
        Tech_Address[wk->wu.id] = player_CMD[wk->player_number][Tech_Number & 0x7FFF];
    } else {
        Tech_Address[wk->wu.id] = player_cmd[wk->player_number][Tech_Number & 0x7FFF];
    }
    Check_First_Menu(wk);
}

/* NOTE: the combo test reads Combo_Speed[wk->wu.id == 0] - the bracket encloses
 * the comparison, so it decrements Combo_Speed[0] or [1] according to whether
 * the id is zero, rather than testing --Combo_Speed[id] == 0 as every sibling
 * does. Copied verbatim; the same shape appears in ORO_HJA_Term. */
static void HJCA_Term_Launch(PLW* wk, s16 Jump_Dir) {
    if (Check_Passive(wk) != 0) {
        return;
    }
    if (!(--Combo_Speed[wk->wu.id == 0])) {
        return;
    }

    CP_Index[wk->wu.id][1]++;
    Tech_Index[wk->wu.id] = 0xC;

    Jump_Init(wk, Jump_Dir);
    Lever_Pool[wk->wu.id] &= 0xC;
    Lever_Buff[wk->wu.id] = 0;
    Check_Air_Guard(wk);
    if (Check_Diagonal_Shell(wk) != 0) {
        Next_Be_Free(wk);
    }
}

static void HJCA_Term_Arm(PLW* wk) {
    if (Check_Passive(wk) != 0) {
        return;
    }

    CP_Index[wk->wu.id][1]++;
    Lever_Buff[wk->wu.id] = 2;
    Lever_Pool[wk->wu.id] |= 1;
}

static void HJCA_Term_Rise(PLW* wk) {
    Lever_Buff[wk->wu.id] = Lever_Pool[wk->wu.id] | 1;
    if (wk->wu.xyz[1].disp.pos > 0) {
        CP_Index[wk->wu.id][1]++;
    }
}

static void Command_Term_Approach(PLW* wk, const Attack_Range_Args* r) {
    Check_Air_Guard(wk);

    if (Attack_Range_Gates(wk, r) == 0) {
        return;
    }

    CP_Index[wk->wu.id][1] += 2;
}

static void HJCA_Term_Land(PLW* wk, const Command_Landing_Args* L) {
    Lever_Buff[wk->wu.id] = Lever_LR[wk->wu.id];
    if (Check_Landed(wk, L->Reaction) != 0) {
        return;
    }

    Command_Term_Landing_Step(wk, L->Tech_Number, L->Power_Level, L->Ex_Shot);
}

static void HJCA_Term_End(PLW* wk, s16 Reaction) {
    Stock_Hit_Flag[wk->wu.id] = wk->wu.hf.hit.player;
    Check_Landed(wk, Reaction & 0xFFF);
}

/* A Term step: what one state of a Term does, given the Term's arguments. The
 * dispatchers below are tables of these, indexed by the state the switch they
 * replace used to test. */
typedef void (*JCA_Term_Step)(PLW* wk, const JCA_Term_Args* a);

typedef struct {
    const JCA_Term_Step* steps;
    s32 count;
    JCA_Term_Step end;
} JCA_Term_Script;

/* The step the Term's state selects, or `end` for a state past the table or
 * with no step of its own - the default arm of the switch this replaces. */
static void Run_JCA_Term(PLW* wk, const JCA_Term_Args* a, const JCA_Term_Script* s) {
    s32 state = CP_Index[wk->wu.id][1];
    JCA_Term_Step step = NULL;

    if (state >= 0 && state < s->count) {
        step = s->steps[state];
    }

    if (step != NULL) {
        step(wk, a);
    } else {
        s->end(wk, a);
    }
}

static void HJCA_Begin_Step(PLW* wk, const JCA_Term_Args* a) {
    HJCA_Term_Begin(wk, a->Tech_Number);
}

static void HJCA_Launch_Step(PLW* wk, const JCA_Term_Args* a) {
    HJCA_Term_Launch(wk, a->Jump_Dir);
}

static void HJCA_Arm_Step(PLW* wk, const JCA_Term_Args* a) {
    HJCA_Term_Arm(wk);
}

static void HJCA_Rise_Step(PLW* wk, const JCA_Term_Args* a) {
    HJCA_Term_Rise(wk);
}

static void HJCA_Approach_Step(PLW* wk, const JCA_Term_Args* a) {
    Command_Term_Approach(wk, &(Attack_Range_Args) { a->Reaction, a->RX, a->RY, a->JRX, a->JRY, a->JLD });
}

static void HJCA_Hold_Step(PLW* wk, const JCA_Term_Args* a) {
    Command_Term_Hold(wk, a->Reaction, 0xFFF);
}

static void HJCA_Land_Step(PLW* wk, const JCA_Term_Args* a) {
    HJCA_Term_Land(wk, &(Command_Landing_Args) { a->Reaction, a->Tech_Number, a->Power_Level, a->Ex_Shot });
}

static void HJCA_End_Step(PLW* wk, const JCA_Term_Args* a) {
    HJCA_Term_End(wk, a->Reaction);
}

/* The airborne half of Hi_Jump_Command_Attack_Term: everything from the rise
 * onwards. The case labels are the original ones, so this reads against the
 * same state numbers as the ground half it was lifted out of. */
static void HJCA_Term_Airborne(PLW* wk, const JCA_Term_Args* a) {
    const JCA_Term_Step steps[7] = {
        [3] = HJCA_Rise_Step, [4] = HJCA_Approach_Step, [5] = HJCA_Hold_Step, [6] = HJCA_Land_Step
    };
    Run_JCA_Term(wk, a, &(JCA_Term_Script) { steps, 7, HJCA_End_Step });
}

void Hi_Jump_Command_Attack_Term(PLW* wk, const JCA_Term_Args* a) {
    const JCA_Term_Step steps[3] = { [0] = HJCA_Begin_Step, [1] = HJCA_Launch_Step, [2] = HJCA_Arm_Step };
    Run_JCA_Term(wk, a, &(JCA_Term_Script) { steps, 3, HJCA_Term_Airborne });
}

/* ORO_JCA_Term's opening: unlike the jump Terms it has no spmv_ng_flag guard. */
static void ORO_JCA_Term_Begin(PLW* wk, u16 Tech_Number) {
    if (Check_Passive(wk) != 0) {
        return;
    }

    Command_Term_Open(wk, Tech_Number);
}

/* Clears the dash flag and runs the air guard, which the jump Term launch does
 * not; kept separate for that reason. */
static void ORO_JCA_Term_Launch(PLW* wk, s16 Jump_Dir) {
    if (!JCA_Launch_Ready(wk)) {
        return;
    }
    dash_flag_clear(wk->wu.id);

    Jump_Init(wk, Jump_Dir);
    Check_Air_Guard(wk);
    if (Check_Diagonal_Shell(wk) != 0) {
        Next_Be_Free(wk);
    }
}

typedef void (*ORO_Term_Step)(PLW* wk, const ORO_JCA_Term_Args* a);

typedef struct {
    const ORO_Term_Step* steps;
    s32 count;
    ORO_Term_Step end;
} ORO_Term_Script;

static void Run_ORO_Term(PLW* wk, const ORO_JCA_Term_Args* a, const ORO_Term_Script* s) {
    s32 state = CP_Index[wk->wu.id][1];
    ORO_Term_Step step = NULL;

    if (state >= 0 && state < s->count) {
        step = s->steps[state];
    }

    if (step != NULL) {
        step(wk, a);
    } else {
        s->end(wk, a);
    }
}

static void ORO_JCA_Begin_Step(PLW* wk, const ORO_JCA_Term_Args* a) {
    ORO_JCA_Term_Begin(wk, a->Tech_Number);
}

static void ORO_JCA_Launch_Step(PLW* wk, const ORO_JCA_Term_Args* a) {
    ORO_JCA_Term_Launch(wk, a->Jump_Dir);
}

static void ORO_HJCA_Begin_Step(PLW* wk, const ORO_JCA_Term_Args* a) {
    HJCA_Term_Begin(wk, a->Tech_Number);
}

static void ORO_HJCA_Launch_Step(PLW* wk, const ORO_JCA_Term_Args* a) {
    HJCA_Term_Launch(wk, a->Jump_Dir);
}

static void ORO_HJCA_Arm_Step(PLW* wk, const ORO_JCA_Term_Args* a) {
    HJCA_Term_Arm(wk);
}

static void ORO_Rise_Step(PLW* wk, const ORO_JCA_Term_Args* a) {
    ORO_Term_Rise(wk);
}

static void ORO_Approach_Step(PLW* wk, const ORO_JCA_Term_Args* a) {
    Command_Term_Approach(wk, &(Attack_Range_Args) { a->Reaction, a->RX, a->RY, a->RJX, a->RJY, a->JLD });
}

static void ORO_Hold_Step(PLW* wk, const ORO_JCA_Term_Args* a) {
    Command_Term_Hold(wk, a->Reaction, 0x7F);
}

static void ORO_Land_Step(PLW* wk, const ORO_JCA_Term_Args* a) {
    JCA_Term_Land(wk, &(Command_Landing_Args) { a->Reaction, a->Tech_Number, a->Power_Level, a->Ex_Shot });
}

static void ORO_End_Step(PLW* wk, const ORO_JCA_Term_Args* a) {
    JCA_Term_End(wk, a->Reaction);
}

/* The airborne half of ORO_JCA_Term: everything from the rise onwards. The case
 * labels are the original ones. */
static void ORO_JCA_Term_Airborne(PLW* wk, const ORO_JCA_Term_Args* a) {
    const ORO_Term_Step steps[7] = {
        [2] = ORO_Rise_Step, [3] = ORO_Term_Climb, [4] = ORO_Approach_Step, [5] = ORO_Hold_Step, [6] = ORO_Land_Step
    };
    Run_ORO_Term(wk, a, &(ORO_Term_Script) { steps, 7, ORO_End_Step });
}

void ORO_JCA_Term(PLW* wk, const ORO_JCA_Term_Args* a) {
    const ORO_Term_Step steps[2] = { [0] = ORO_JCA_Begin_Step, [1] = ORO_JCA_Launch_Step };
    Run_ORO_Term(wk, a, &(ORO_Term_Script) { steps, 2, ORO_JCA_Term_Airborne });
}

/* The airborne half of ORO_HJCA_Term: everything from the rise onwards. The
 * case labels are the original ones, so this reads against the same state
 * numbers as the ground half it was lifted out of. */
static void ORO_HJCA_Term_Airborne(PLW* wk, const ORO_JCA_Term_Args* a) {
    const ORO_Term_Step steps[8] = {
        [3] = ORO_Rise_Step, [4] = ORO_Term_Climb, [5] = ORO_Approach_Step, [6] = ORO_Hold_Step, [7] = ORO_Land_Step
    };
    Run_ORO_Term(wk, a, &(ORO_Term_Script) { steps, 8, ORO_End_Step });
}

void ORO_HJCA_Term(PLW* wk, const ORO_JCA_Term_Args* a) {
    const ORO_Term_Step steps[3] = { [0] = ORO_HJCA_Begin_Step, [1] = ORO_HJCA_Launch_Step, [2] = ORO_HJCA_Arm_Step };
    Run_ORO_Term(wk, a, &(ORO_Term_Script) { steps, 3, ORO_HJCA_Term_Airborne });
}
