#!/usr/bin/env python3
"""Recipe J2 proof for com_sub_command_term.c: the Hi_Jump_Command_Attack_Term,
ORO_JCA_Term and ORO_HJCA_Term dispatchers at a base ref against the working tree.
Every leaf call is stubbed to record its name and arguments; each of the 256 states
CP_Index can hold is driven through both versions for both fighters, and the
recordings must match exactly.

    python tools/equivalence/command_term_dispatch.py [--base <ref>]
"""
import argparse, os, subprocess, sys, tempfile

REPO = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
SRC = "src/sf33rd/Source/Game/com/com_sub_command_term.c"
ENTRIES = ["Hi_Jump_Command_Attack_Term", "ORO_JCA_Term", "ORO_HJCA_Term"]

COMMON = r"""
#include <stddef.h>
#include <stdio.h>
#include <string.h>
typedef short s16; typedef unsigned short u16; typedef int s32; typedef unsigned char u8; typedef unsigned int u32;
typedef struct { struct { s32 id; } wu; } PLW;
extern u8 CP_Index[2][8];
typedef struct { s16 Reaction; s16 Jump_Dir; s16 JY; s16 Jump_Dir2; s16 RX; s16 RY; u16 Tech_Number; s16 Power_Level; s16 Ex_Shot; s16 RJX; s16 RJY; u16 JLD; } ORO_JCA_Term_Args;
typedef struct { s16 Reaction; u16 Tech_Number; s16 Power_Level; s16 Ex_Shot; s16 RX; s16 RY; s16 Jump_Dir; s16 JRX; s16 JRY; u16 JLD; } JCA_Term_Args;
typedef struct { s16 Reaction; s16 RX; s16 RY; s16 JRX; s16 JRY; u16 JLD; } Attack_Range_Args;
typedef struct { s16 Reaction; u16 Tech_Number; s16 Power_Level; s16 Ex_Shot; } Command_Landing_Args;
extern char logbuf[8192]; extern int logpos;
#define LOG(...) logpos += snprintf(logbuf + logpos, sizeof(logbuf) - logpos, __VA_ARGS__)
static void HJCA_Term_Begin(PLW* wk, u16 t) { LOG("HJCA_Begin(%d,%u);", wk->wu.id, t); }
static void HJCA_Term_Launch(PLW* wk, s16 d) { LOG("HJCA_Launch(%d,%d);", wk->wu.id, d); }
static void HJCA_Term_Arm(PLW* wk) { LOG("HJCA_Arm(%d);", wk->wu.id); }
static void HJCA_Term_Rise(PLW* wk) { LOG("HJCA_Rise(%d);", wk->wu.id); }
static void Command_Term_Approach(PLW* wk, const Attack_Range_Args* r) { LOG("Approach(%d,%d,%d,%d,%d,%d,%u);", wk->wu.id, r->Reaction, r->RX, r->RY, r->JRX, r->JRY, r->JLD); }
static void Command_Term_Hold(PLW* wk, s16 re, s16 m) { LOG("Hold(%d,%d,%d);", wk->wu.id, re, m); }
static void HJCA_Term_Land(PLW* wk, const Command_Landing_Args* L) { LOG("HJCA_Land(%d,%d,%u,%d,%d);", wk->wu.id, L->Reaction, L->Tech_Number, L->Power_Level, L->Ex_Shot); }
static void HJCA_Term_End(PLW* wk, s16 re) { LOG("HJCA_End(%d,%d);", wk->wu.id, re); }
static void ORO_Term_Rise(PLW* wk) { LOG("ORO_Rise(%d);", wk->wu.id); }
static void ORO_Term_Climb(PLW* wk, const ORO_JCA_Term_Args* a) { LOG("ORO_Climb(%d,%d);", wk->wu.id, a->Reaction); }
static void JCA_Term_Land(PLW* wk, const Command_Landing_Args* L) { LOG("JCA_Land(%d,%d,%u,%d,%d);", wk->wu.id, L->Reaction, L->Tech_Number, L->Power_Level, L->Ex_Shot); }
static void JCA_Term_End(PLW* wk, s16 re) { LOG("JCA_End(%d,%d);", wk->wu.id, re); }
static s32 Check_Passive(PLW* wk) { LOG("Check_Passive(%d);", wk->wu.id); return 0; }
static void Command_Term_Open(PLW* wk, u16 t) { LOG("Open(%d,%u);", wk->wu.id, t); }
static s32 JCA_Launch_Ready(PLW* wk) { LOG("LaunchReady(%d);", wk->wu.id); return 1; }
static void dash_flag_clear(s32 id) { LOG("dash_clear(%d);", id); }
static void Jump_Init(PLW* wk, s16 d) { LOG("Jump_Init(%d,%d);", wk->wu.id, d); }
static void Check_Air_Guard(PLW* wk) { LOG("AirGuard(%d);", wk->wu.id); }
static s32 Check_Diagonal_Shell(PLW* wk) { LOG("Diag(%d);", wk->wu.id); return 1; }
static void Next_Be_Free(PLW* wk) { LOG("NextFree(%d);", wk->wu.id); }
"""

MAIN = r"""
#include "common.h"
u8 CP_Index[2][8]; char logbuf[8192]; int logpos;
void OLD_Hi_Jump_Command_Attack_Term(PLW*, const JCA_Term_Args*); void Hi_Jump_Command_Attack_Term(PLW*, const JCA_Term_Args*);
void OLD_ORO_JCA_Term(PLW*, const ORO_JCA_Term_Args*); void ORO_JCA_Term(PLW*, const ORO_JCA_Term_Args*);
void OLD_ORO_HJCA_Term(PLW*, const ORO_JCA_Term_Args*); void ORO_HJCA_Term(PLW*, const ORO_JCA_Term_Args*);
int main(void) {
    JCA_Term_Args j = { 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
    ORO_JCA_Term_Args o = { 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32 };
    char a[8192]; long checked = 0, bad = 0;
    for (int id = 0; id < 2; id++) for (int s = 0; s < 256; s++) for (int fn = 0; fn < 3; fn++) {
        PLW wk = { { id } };
        CP_Index[id][1] = (u8)s;
        logpos = 0; logbuf[0] = 0;
        if (fn == 0) OLD_Hi_Jump_Command_Attack_Term(&wk, &j); else if (fn == 1) OLD_ORO_JCA_Term(&wk, &o); else OLD_ORO_HJCA_Term(&wk, &o);
        strcpy(a, logbuf);
        logpos = 0; logbuf[0] = 0;
        if (fn == 0) Hi_Jump_Command_Attack_Term(&wk, &j); else if (fn == 1) ORO_JCA_Term(&wk, &o); else ORO_HJCA_Term(&wk, &o);
        checked++;
        if (strcmp(a, logbuf) != 0) { bad++; if (bad < 10) printf("MISMATCH fn=%d id=%d state=%d\n old: %s\n new: %s\n", fn, id, s, a, logbuf); }
    }
    printf("checked %ld dispatches, %ld mismatches\n", checked, bad);
    return bad ? 1 : 0;
}
"""


def region(text):
    """From the first Term dispatcher's comment to the end of the file. The helpers above
    it are leaf calls the harness stubs; the infrastructure Recipe J2 adds sits inside."""
    markers = ["/* A Term step:", "/* The airborne half of Hi_Jump_Command_Attack_Term"]
    for m in markers:
        if m in text:
            return text[text.index(m):]
    sys.exit("could not find the Term dispatcher region")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--base", default="HEAD")
    args = ap.parse_args()
    old = subprocess.run(["git", "show", "%s:%s" % (args.base, SRC)], capture_output=True, text=True, cwd=REPO, check=True).stdout
    new = open(os.path.join(REPO, SRC), encoding="utf-8").read()
    renames = "".join("#define %s OLD_%s\n" % (n, n) for n in ENTRIES)
    with tempfile.TemporaryDirectory() as d:
        open(os.path.join(d, "common.h"), "w").write(COMMON)
        open(os.path.join(d, "old.c"), "w").write('#include "common.h"\n' + renames + region(old))
        open(os.path.join(d, "new.c"), "w").write('#include "common.h"\n' + region(new))
        open(os.path.join(d, "main.c"), "w").write(MAIN)
        exe = os.path.join(d, "harness.exe" if os.name == "nt" else "harness")
        cc = os.environ.get("CC", "clang")
        r = subprocess.run([cc, "-O1", "-Wall", "-Wno-unused-function", "-Wno-unused-parameter", "-o", exe,
                            os.path.join(d, "old.c"), os.path.join(d, "new.c"), os.path.join(d, "main.c")],
                           capture_output=True, text=True)
        if r.returncode:
            sys.exit(r.stdout + r.stderr)
        r = subprocess.run([exe], capture_output=True, text=True)
        print(r.stdout.strip())
        sys.exit(r.returncode)


if __name__ == "__main__":
    main()
