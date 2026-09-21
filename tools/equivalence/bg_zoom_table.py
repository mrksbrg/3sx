#!/usr/bin/env python3
"""Recipe M proof for bg_zoom.c: the zoom-request selection at a base ref against the
working tree, over every (p1zoom, p2zoom) pair in 0..0xFFFF x 0..0xFFFF and two
initial request-flag states.

    python tools/equivalence/bg_zoom_table.py [--base <ref>]

Both versions are compiled behind a minimal fake of the state they touch (the two
fighters' display positions and the three request globals) into one executable, which
runs them side by side and counts mismatches. Exit status 0 means none.
"""
import argparse, os, subprocess, sys, tempfile

REPO = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
SRC = "src/sf33rd/Source/Game/stage/bg_zoom.c"

COMMON = r"""
#include <stddef.h>
typedef short s16; typedef unsigned short u16; typedef int s32; typedef unsigned char u8;
typedef struct { struct { struct { s16 pos; } disp; } xyz[2]; } FakeWU;
typedef struct { FakeWU wu; } FakePLW;
extern FakePLW plw[2];
extern s16 zoom_request_flag, scr_req_x, scr_req_y;
"""

MAIN = r"""
#include "common.h"
#include <stdio.h>
FakePLW plw[2];
s16 zoom_request_flag, scr_req_x, scr_req_y;
void old_run(u16, u16); void new_run(u16, u16);
int main(void) {
    const s16 inits[2] = { 0, (s16)0x8001 };
    unsigned long long checked = 0, mismatches = 0;
    plw[0].wu.xyz[0].disp.pos = 100; plw[1].wu.xyz[0].disp.pos = 300;
    plw[0].wu.xyz[1].disp.pos = 1000; plw[1].wu.xyz[1].disp.pos = 3000;
    for (int k = 0; k < 2; k++)
        for (unsigned p1 = 0; p1 <= 0xFFFF; p1++)
            for (unsigned p2 = 0; p2 <= 0xFFFF; p2++) {
                s16 f1, x1, y1, f2, x2, y2;
                zoom_request_flag = inits[k]; scr_req_x = -1; scr_req_y = -1;
                old_run((u16)p1, (u16)p2); f1 = zoom_request_flag; x1 = scr_req_x; y1 = scr_req_y;
                zoom_request_flag = inits[k]; scr_req_x = -1; scr_req_y = -1;
                new_run((u16)p1, (u16)p2); f2 = zoom_request_flag; x2 = scr_req_x; y2 = scr_req_y;
                checked++;
                if (f1 != f2 || x1 != x2 || y1 != y2) {
                    if (mismatches < 10)
                        printf("MISMATCH p1=%04X p2=%04X init=%04X old=(%04X,%d,%d) new=(%04X,%d,%d)\n",
                               p1, p2, (u16)inits[k], (u16)f1, x1, y1, (u16)f2, x2, y2);
                    mismatches++;
                }
            }
    printf("checked %llu input pairs, %llu mismatches\n", checked, mismatches);
    return mismatches ? 1 : 0;
}
"""


def region(text):
    """The selection code: from the first midpoint helper up to the screen-placement code."""
    a = text.index("static s16 fighters_horizontal_midpoint")
    b = text.index("static void place_fighter_on_screen")
    return text[a:b]


def entry(text):
    """A wrapper calling whichever shape of the selection this version has."""
    if "select_zoom_request(&horizontal_axis" in text:
        return "void %s_run(u16 p1, u16 p2) { select_zoom_request(&horizontal_axis, p1, p2); select_zoom_request(&vertical_axis, p1, p2); }\n"
    return "void %s_run(u16 p1, u16 p2) { select_horizontal_zoom_request(p1, p2); select_vertical_zoom_request(p1, p2); }\n"


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--base", default="HEAD")
    args = ap.parse_args()
    old = subprocess.run(["git", "show", "%s:%s" % (args.base, SRC)], capture_output=True, text=True, cwd=REPO, check=True).stdout
    new = open(os.path.join(REPO, SRC), encoding="utf-8").read()
    with tempfile.TemporaryDirectory() as d:
        open(os.path.join(d, "common.h"), "w").write(COMMON)
        open(os.path.join(d, "old.c"), "w").write('#include "common.h"\n' + region(old) + entry(old) % "old")
        open(os.path.join(d, "new.c"), "w").write('#include "common.h"\n' + region(new) + entry(new) % "new")
        open(os.path.join(d, "main.c"), "w").write(MAIN)
        exe = os.path.join(d, "harness.exe" if os.name == "nt" else "harness")
        cc = os.environ.get("CC", "clang")
        r = subprocess.run([cc, "-O2", "-Wall", "-Wno-unused-function", "-o", exe,
                            os.path.join(d, "old.c"), os.path.join(d, "new.c"), os.path.join(d, "main.c")],
                           capture_output=True, text=True)
        if r.returncode:
            sys.exit(r.stdout + r.stderr)
        r = subprocess.run([exe], capture_output=True, text=True)
        print(r.stdout.strip())
        sys.exit(r.returncode)


if __name__ == "__main__":
    main()
