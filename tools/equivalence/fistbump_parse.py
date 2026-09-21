#!/usr/bin/env python3
"""Recipe Q proof for fistbump.c: the server-line parser at a base ref against the
working tree, over a corpus of well-formed, malformed, oddly spaced and random lines.

    python tools/equivalence/fistbump_parse.py [--base <ref>] [--random N]

Both parsers run behind the same fakes of the module state and of the SDL calls the
handlers make; every SDL_Log and SaveToken is recorded. For each line, both start from
the same state and must leave the same state, the same buffers and the same recording.
"""
import argparse, os, random, subprocess, sys, tempfile

REPO = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
SRC = "src/platform/netplay/fistbump.c"

COMMON = r"""
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
typedef enum { FISTBUMP_IDLE, FISTBUMP_CONNECTING, FISTBUMP_SENDING_TOKEN, FISTBUMP_LOGGING_IN, FISTBUMP_AWAITING_LOGIN,
               FISTBUMP_AWAITING_MATCH, FISTBUMP_MATCHED, FISTBUMP_SENDING_UDP, FISTBUMP_GAME_START, FISTBUMP_ERROR } FistbumpState;
typedef struct { char match_id[37]; int player; char opponent_name[64]; char ip[64]; int remote_port; } MatchResult;
typedef struct { char code[9]; char activate_url[128]; } DAG;
typedef struct { char token[1024]; int expiry; } JWT;
typedef struct { char username[64]; } Fistbump_Profile;
extern FistbumpState state; extern char id_buf[8]; extern DAG dag; extern JWT refresh_token;
extern Fistbump_Profile profile; extern MatchResult match_result;
extern char logbuf[16384]; extern int logpos;
static void SDL_Log(const char* fmt, ...) {
    va_list ap; va_start(ap, fmt);
    logpos += vsnprintf(logbuf + logpos, sizeof(logbuf) - logpos, fmt, ap);
    va_end(ap);
}
#define SDL_sscanf sscanf
#define SDL_zero(x) memset(&(x), 0, sizeof(x))
#define SDL_arraysize(a) (sizeof(a) / sizeof((a)[0]))
static size_t SDL_strlcpy(char* dst, const char* src, size_t n) {
    size_t len = strlen(src);
    if (n) { size_t c = len < n - 1 ? len : n - 1; memcpy(dst, src, c); dst[c] = 0; }
    return len;
}
static void SaveToken(const JWT* jwt) { logpos += snprintf(logbuf + logpos, sizeof(logbuf) - logpos, "[SaveToken %s %d]", jwt->token, jwt->expiry); }
"""

MAIN = r"""
#include "common.h"
#include <stdlib.h>
FistbumpState state; char id_buf[8]; DAG dag; JWT refresh_token; Fistbump_Profile profile; MatchResult match_result;
char logbuf[16384]; int logpos;
void OLD_Fistbump_ParseCommand(const char*); void Fistbump_ParseCommand(const char*);
typedef struct { FistbumpState state; char id_buf[8]; DAG dag; JWT refresh_token; Fistbump_Profile profile; MatchResult match_result; char log[16384]; } Snapshot;
static void seed_state(int variant) {
    memset(id_buf, 0, sizeof id_buf); memset(&dag, 0, sizeof dag); memset(&refresh_token, 0, sizeof refresh_token);
    memset(&profile, 0, sizeof profile); memset(&match_result, 0, sizeof match_result);
    state = (variant & 1) ? FISTBUMP_MATCHED : FISTBUMP_AWAITING_MATCH;
    if (variant & 2) strcpy(match_result.match_id, "abc-123");
    strcpy(id_buf, "seed");
}
static void take(Snapshot* s) {
    s->state = state; memcpy(s->id_buf, id_buf, sizeof id_buf); s->dag = dag; s->refresh_token = refresh_token;
    s->profile = profile; s->match_result = match_result; memcpy(s->log, logbuf, sizeof logbuf);
}
int main(void) {
    static char line[4096]; static Snapshot a, b; long checked = 0, bad = 0;
    while (fgets(line, sizeof line, stdin)) {
        size_t n = strlen(line); if (n && line[n - 1] == '\n') line[n - 1] = 0;
        for (int v = 0; v < 4; v++) {
            seed_state(v); memset(logbuf, 0, sizeof logbuf); logpos = 0; OLD_Fistbump_ParseCommand(line); take(&a);
            seed_state(v); memset(logbuf, 0, sizeof logbuf); logpos = 0; Fistbump_ParseCommand(line); take(&b);
            checked++;
            if (memcmp(&a, &b, sizeof a) != 0) {
                bad++;
                if (bad < 10) printf("MISMATCH variant %d on line [%s]\n old: state %d log %s\n new: state %d log %s\n", v, line, a.state, a.log, b.state, b.log);
            }
        }
    }
    printf("checked %ld line runs, %ld mismatches\n", checked, bad);
    return bad ? 1 : 0;
}
"""


def region(text):
    start_markers = ["/* A line from the server, split once", "void Fistbump_HandleSESSION(const char* line) {"]
    for m in start_markers:
        if m in text:
            a = text.index(m)
            break
    else:
        sys.exit("could not find the parser region")
    b = text.index("\n}\n", text.index("void Fistbump_ParseCommand(const char* line) {")) + len("\n}\n")
    return text[a:b]


def corpus(n_random, rng):
    words = ["SESSION", "DAG", "UDP", "TOKEN", "PROFILE", "MATCH", "CANCEL", "START", "session", "SESSIONS", "MATCHX", "TOKENS", "STAR", "", "QUIT"]
    tokens = ["", "a", "ok", "OK", "abc1234", "abcdefgh", "x" * 40, "y" * 130, "12", "-5", "0", "99999999999", "7000", "1.2.3.4:7000",
              "1.2.3.4", ":7000", "::", "refresh", "refreshed", "tok", "tok:99", "abc-123", "abc-124", "%s", "%d", "\t", "a b", "http://x/y?z=1"]
    seps = [" ", "  ", "\t", " \t ", ""]
    lines = []
    for w in words:
        for sep0 in seps:
            lines.append(w + sep0)
            for t1 in tokens:
                lines.append(w + sep0 + t1)
                for sep in seps[:3]:
                    for t2 in tokens[:14]:
                        lines.append(w + sep0 + t1 + sep + t2)
    lines.append("TOKEN refresh " + "z" * 1100 + " 5")
    lines.append("START 2 " + "9" * 70 + ":1")
    alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 :-._/%\t"
    for _ in range(n_random):
        w = rng.choice(words)
        body = "".join(rng.choice(alphabet) for _ in range(rng.randint(0, 60)))
        lines.append(w + rng.choice(seps) + body)
    return [l for l in lines if "\n" not in l]


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--base", default="HEAD")
    ap.add_argument("--random", type=int, default=50000)
    args = ap.parse_args()
    old = subprocess.run(["git", "show", "%s:%s" % (args.base, SRC)], capture_output=True, text=True, cwd=REPO, check=True).stdout
    new = open(os.path.join(REPO, SRC), encoding="utf-8").read()
    with tempfile.TemporaryDirectory() as d:
        open(os.path.join(d, "common.h"), "w").write(COMMON)
        open(os.path.join(d, "old.c"), "w").write('#include "common.h"\n#define Fistbump_ParseCommand OLD_Fistbump_ParseCommand\n'
                                                  + "".join("#define %s OLD_%s\n" % (h, h) for h in
                                                            ["Fistbump_HandleSESSION", "Fistbump_HandleDAG", "Fistbump_HandleUDP", "Fistbump_HandleTOKEN",
                                                             "Fistbump_HandlePROFILE", "Fistbump_HandleMATCH", "Fistbump_HandleCANCEL", "Fistbump_HandleSTART"])
                                                  + region(old))
        open(os.path.join(d, "new.c"), "w").write('#include "common.h"\n' + region(new))
        open(os.path.join(d, "main.c"), "w").write(MAIN)
        exe = os.path.join(d, "harness.exe" if os.name == "nt" else "harness")
        cc = os.environ.get("CC", "clang")
        r = subprocess.run([cc, "-O1", "-Wall", "-Wno-unused-function", "-Wno-format-security", "-o", exe,
                            os.path.join(d, "old.c"), os.path.join(d, "new.c"), os.path.join(d, "main.c")],
                           capture_output=True, text=True)
        if r.returncode:
            sys.exit(r.stdout + r.stderr)
        lines = corpus(args.random, random.Random(20260921))
        r = subprocess.run([exe], input="\n".join(lines) + "\n", capture_output=True, text=True)
        print("%d distinct lines x 4 starting states" % len(lines))
        print(r.stdout.strip())
        sys.exit(r.returncode)


if __name__ == "__main__":
    main()
