#!/usr/bin/env python3
"""Recipe O proof for ps2PAD.c: flPADShockSet at a base ref against the working tree,
with the sceVibSetActParam call recorded, over both pads, six vibration profiles,
seventeen levels (every masked class plus wide values) and six times.

    python tools/equivalence/ps2pad_shock.py [--base <ref>]

Exit status 0 means every call produced the same SDK parameters, return value and
slot state.
"""
import argparse, os, subprocess, sys, tempfile

REPO = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
SRC = "src/sf33rd/AcrSDK/ps2/ps2PAD.c"

COMMON = r"""
#include <stdio.h>
#include <string.h>
typedef int s32; typedef unsigned int u32; typedef unsigned char u8;
typedef struct { u32 socket_id; u32 vprofile; u32 vib_timer; } PS2Slot;
extern PS2Slot ps2slot[2];
typedef struct { s32 socket_id; s32 one; u8* profile; s32 size; u8* data; } VibActParam;
extern char logbuf[512]; extern int logpos;
static s32 sceVibSetActParam(const VibActParam* p) {
    logpos += snprintf(logbuf + logpos, sizeof(logbuf) - logpos, "vib(sock=%d,%d,profile=%u,size=%d,data=", p->socket_id, p->one, *p->profile, p->size);
    for (s32 i = 0; i < p->size; i++) logpos += snprintf(logbuf + logpos, sizeof(logbuf) - logpos, "%02X", p->data[i]);
    logpos += snprintf(logbuf + logpos, sizeof(logbuf) - logpos, ");");
    return 0;
}
"""

MAIN = r"""
#include "common.h"
PS2Slot ps2slot[2]; char logbuf[512]; int logpos;
s32 OLD_flPADShockSet(s32, u32, u32); s32 flPADShockSet(s32, u32, u32);
static void reset(int pad, u32 profile) { memset(ps2slot, 0, sizeof ps2slot); ps2slot[pad].socket_id = 40 + pad; ps2slot[pad].vprofile = profile; ps2slot[pad].vib_timer = 999; }
int main(void) {
    const u32 levels[] = { 0,1,2,3,4,5,6,7,8,9,15,16,255,256,0xFFFFFFF8u,0xFFFFFFFFu,0x12345678u };
    const u32 times[] = { 0, 1, 2, 30, 0xFFFF, 0xFFFFFFFFu };
    const u32 profiles[] = { 0, 1, 2, 3, 4, 0xFFFFFFFFu };
    char a[512]; long checked = 0, bad = 0;
    for (int pad = 0; pad < 2; pad++) for (unsigned pi = 0; pi < 6; pi++) for (unsigned li = 0; li < 17; li++) for (unsigned ti = 0; ti < 6; ti++) {
        PS2Slot s1, s2; s32 r1, r2;
        reset(pad, profiles[pi]); logpos = 0; logbuf[0] = 0; r1 = OLD_flPADShockSet(pad, levels[li], times[ti]); strcpy(a, logbuf); s1 = ps2slot[pad];
        reset(pad, profiles[pi]); logpos = 0; logbuf[0] = 0; r2 = flPADShockSet(pad, levels[li], times[ti]); s2 = ps2slot[pad];
        checked++;
        if (r1 != r2 || strcmp(a, logbuf) != 0 || memcmp(&s1, &s2, sizeof s1) != 0) {
            bad++;
            if (bad < 10) printf("MISMATCH pad=%d prof=%u level=%u time=%u\n old(%d): %s\n new(%d): %s\n", pad, profiles[pi], levels[li], times[ti], r1, a, r2, logbuf);
        }
    }
    printf("checked %ld calls, %ld mismatches\n", checked, bad);
    return bad ? 1 : 0;
}
"""

SIG = "s32 flPADShockSet(s32 pad_id, u32 level, u32 time) {"


def region(text):
    """flPADShockSet and any helpers declared for it directly above (Recipe O's helpers)."""
    end = text.index("\n}\n", text.index(SIG)) + len("\n}\n")
    marker = "/* One vibration command as sceVibSetActParam wants it"
    start = text.index(marker) if marker in text else text.index(SIG)
    return text[start:end]


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--base", default="HEAD")
    args = ap.parse_args()
    old = subprocess.run(["git", "show", "%s:%s" % (args.base, SRC)], capture_output=True, text=True, cwd=REPO, check=True).stdout
    new = open(os.path.join(REPO, SRC), encoding="utf-8").read()
    with tempfile.TemporaryDirectory() as d:
        open(os.path.join(d, "common.h"), "w").write(COMMON)
        open(os.path.join(d, "old.c"), "w").write('#include "common.h"\n#define flPADShockSet OLD_flPADShockSet\n' + region(old))
        open(os.path.join(d, "new.c"), "w").write('#include "common.h"\n' + region(new))
        open(os.path.join(d, "main.c"), "w").write(MAIN)
        exe = os.path.join(d, "harness.exe" if os.name == "nt" else "harness")
        cc = os.environ.get("CC", "clang")
        r = subprocess.run([cc, "-O1", "-Wall", "-Wno-unused-function", "-o", exe,
                            os.path.join(d, "old.c"), os.path.join(d, "new.c"), os.path.join(d, "main.c")],
                           capture_output=True, text=True)
        if r.returncode:
            sys.exit(r.stdout + r.stderr)
        r = subprocess.run([exe], capture_output=True, text=True)
        print(r.stdout.strip())
        sys.exit(r.returncode)


if __name__ == "__main__":
    main()
