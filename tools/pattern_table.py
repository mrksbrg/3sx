#!/usr/bin/env python3
"""Recipe J - turn the COM pattern skeletons into dispatch tables, and prove it.

The 448 skeletons in src/sf33rd/Source/Game/com/patterns/ are all one shape: a
`switch` on the COM step counter whose every arm is a single engine call. That
is a dispatch table written as control flow, exactly as Recipe L's subject is a
lookup table written as control flow.

This tool does three things:

    --emit-infra          write the interpreter, the adapters and the argument
                          structs, generated from com_sub.h's own signatures
    --convert  FILE...    rewrite a skeleton file into table form
    --verify   FILE...    parse a converted file, regenerate the switch form
                          from it, and diff that against the pre-conversion
                          source. An exact match is a proof of equivalence at
                          the source level: the conversion is invertible, and
                          the inverse reproduces the original text.

The last mode is the point. There is no statcheck and no replay coverage for
CPU AI (docs/refactoring/REPLAY-VERIFICATION.md), so the only thing that can
carry 448 functions is a transformation that can be run backwards.

Usage:
    python tools/pattern_table.py --emit-infra
    python tools/pattern_table.py --convert src/sf33rd/Source/Game/com/patterns/*.c
    python tools/pattern_table.py --verify  src/sf33rd/Source/Game/com/patterns/*.c
"""

from __future__ import annotations

import argparse
import re
import subprocess
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
PATTERNS = REPO / "src/sf33rd/Source/Game/com/patterns"
COM = REPO / "src/sf33rd/Source/Game/com"
COM_SUB_H = REPO / "src/sf33rd/Source/Game/com/com_sub.h"

SWITCH_HEAD = "switch (CP_Index[wk->wu.id][0])"
RUN_INCLUDE = '#include "sf33rd/Source/Game/com/patterns/com_pattern_run.h"'
PATTERNS_INCLUDE = '#include "sf33rd/Source/Game/com/patterns/com_patterns.h"' 


# --------------------------------------------------------------------------
# Parsing


def split_functions(src: str):
    """(start, end, name, params, body) for every function definition in src."""
    out = []
    for m in re.finditer(r"^(static\s+)?(\w[\w \*]*?)\b(\w+)\(([^;{]*?)\)\s*\{", src, re.M | re.S):
        open_brace = m.end() - 1
        depth = 0
        i = open_brace
        while i < len(src):
            if src[i] == "{":
                depth += 1
            elif src[i] == "}":
                depth -= 1
                if depth == 0:
                    break
            i += 1
        out.append((
            m.start(), i + 1,
            ("static " if m.group(1) else "") + m.group(3),
            " ".join(m.group(4).split()),
            src[open_brace + 1 : i],
        ))
    return out


def split_top_level(text: str):
    """Split on commas that are not nested inside brackets."""
    out, depth, cur = [], 0, ""
    for ch in text:
        if ch in "([{":
            depth += 1
        elif ch in ")]}":
            depth -= 1
        if ch == "," and depth == 0:
            out.append(cur.strip())
            cur = ""
        else:
            cur += ch
    if cur.strip():
        out.append(cur.strip())
    return out


def parse_params(params: str):
    """[(type, name)] for a parameter list, pointer stars kept on the type.

    A declaration may leave a parameter unnamed - com_sub.h has
    `void Next_Be_Passive(PLW* wk, s32);` - so an unnamed one is given its
    position as a name, which is what the generated struct field is called.
    """
    out = []
    for i, p in enumerate(split_top_level(params)):
        text = p.strip()
        m = re.match(r"^(.*?[ \*])(\w+)$", text)
        if m and m.group(2) not in TYPE_WORDS:
            out.append((m.group(1).strip(), m.group(2)))
        else:
            out.append((text, "arg%d" % i))
    return out


TYPE_WORDS = {"void", "s8", "u8", "s16", "u16", "s32", "u32", "s64", "u64", "int", "char", "float", "double"}


def parse_skeleton(body: str):
    """(arms, default_stmt) for a switch skeleton body, or None if not one."""
    t = body.strip()
    if not t.startswith(SWITCH_HEAD):
        return None
    inner = t[t.index("{") + 1 : t.rindex("}")]
    parts = re.split(r"\n\s*(case [^:\n]+:|default:)\s*\n", "\n" + inner)
    if parts[0].strip():
        return None
    arms, default = [], None
    for label, chunk in zip(parts[1::2], parts[2::2]):
        stmts = [x.strip() for x in chunk.splitlines() if x.strip() and x.strip() != "break;"]
        call = " ".join(stmts)
        if label.strip() == "default:":
            default = call
        else:
            arms.append((int(label.strip()[5:-1], 0), call))
    return arms, default


def parse_call(stmt: str):
    """(callee, [argument text]) for `F(wk, a, b);`."""
    m = re.match(r"^(\w+)\((.*)\);$", stmt.strip(), re.S)
    callee, args = m.group(1), split_top_level(m.group(2))
    assert args[0] == "wk", stmt
    return callee, args[1:]


# --------------------------------------------------------------------------
# The engine's own signatures


def engine_signatures():
    """{callee: [(type, name)]} for the extra parameters after `PLW* wk`."""
    text = re.sub(r"//[^\n]*", "", COM_SUB_H.read_text())
    sigs = {}
    for m in re.finditer(r"\bvoid\s+(\w+)\(([^;)]*)\);", text):
        params = parse_params(m.group(2))
        if not params or params[0][1] != "wk":
            continue
        sigs[m.group(1)] = params[1:]
    return sigs


SIGS = engine_signatures()


def step_struct(callee: str) -> str:
    return callee + "_Step"


def passthrough(callee: str) -> bool:
    """One extra parameter and it is already a pointer: no wrapper needed."""
    ps = SIGS[callee]
    return len(ps) == 1 and ps[0][0].endswith("*")


def passthrough_type(callee: str) -> str:
    """The engine's own argument type for a pass-through call."""
    return SIGS[callee][0][0].replace("const", "").replace("*", "").strip()


# --------------------------------------------------------------------------
# Forward: switch -> table


def entry_for(call: str, params: list, label: int) -> str:
    callee, args = parse_call(call)
    sig = SIGS[callee]
    if not args:
        return "[%d] = STEP_NOARG(%s)" % (label, callee)
    if passthrough(callee):
        # An argument object written out on the spot is the same list of values
        # STEP takes for every other call; only a name has to stay a name.
        m = re.match(r"^&\(%s\)\s*\{\s*(.*?)\s*\}$" % re.escape(passthrough_type(callee)), args[0], re.S)
        if m:
            return "[%d] = STEP(%s, %s)" % (label, callee, m.group(1))
        return "[%d] = STEP_WITH(%s, %s)" % (label, callee, args[0])
    # `x->A, x->B` over a parameter already of the right struct type is the
    # struct itself; hand the pointer straight over.
    unpacked = [re.match(r"^(\w+)->(\w+)$", a) for a in args]
    by_param = {n: t for t, n in params}
    if all(unpacked) and len({m.group(1) for m in unpacked}) == 1:
        base = unpacked[0].group(1)
        fields = [m.group(2) for m in unpacked]
        want = "const " + step_struct(callee) + "*"
        if by_param.get(base, "").replace(" ", "") == want.replace(" ", "") and fields == [n for _, n in sig]:
            return "[%d] = STEP_WITH(%s, %s)" % (label, callee, base)
    return "[%d] = STEP(%s, %s)" % (label, callee, ", ".join(args))


def convert_source(src: str) -> str:
    edits = []
    for start, end, name, params, body in split_functions(src):
        parsed = parse_skeleton(body)
        if parsed is None:
            continue
        arms, default = parsed
        if not arms:
            continue  # nothing to dispatch on; the switch is already one arm
        plist = parse_params(params)
        count = arms[-1][0] + 1
        entries = [entry_for(call, plist, label) for label, call in arms]
        decl = "    const Pattern_Step script[%d] = { %s };\n" % (count, ", ".join(entries))
        if default == "End_Pattern(wk);":
            new_body = decl + "    Run_Pattern(wk, script, %d);\n" % count
        else:
            new_body = decl + "    if (!Run_Pattern_Steps(wk, script, %d)) {\n        %s\n    }\n" % (count, default)
        edits.append((start, end, "%svoid %s(%s) {\n%s}" % (
            "static " if name.startswith("static ") else "", name.replace("static ", ""), params, new_body)))
        # Formatting one function at a time keeps the diff to the conversion.
        # Most of Game/com is not clang-format clean, and reformatting a whole
        # file would bury a Recipe J commit under a few hundred style lines.
    out = src
    for start, end, text in reversed(edits):
        out = out[:start] + clang_format(text, "fragment.c").rstrip("\n") + out[end:]
    if edits and RUN_INCLUDE not in out:
        out = out.replace(PATTERNS_INCLUDE, RUN_INCLUDE + "\n" + PATTERNS_INCLUDE, 1)
    return out


# --------------------------------------------------------------------------
# Inverse: table -> switch


TABLE_RE = re.compile(r"const Pattern_Step script\[(\d+)\] = \{", re.S)
CHAIN_RE = re.compile(r"if \(!Run_Pattern_Steps\(wk, script, \d+\)\) \{\s*(.*?)\s*\n    \}", re.S)


def braced_body(text: str, open_at: int) -> str:
    """The contents of the brace that starts at open_at."""
    depth = 0
    for i in range(open_at, len(text)):
        if text[i] == "{":
            depth += 1
        elif text[i] == "}":
            depth -= 1
            if depth == 0:
                return text[open_at + 1 : i]
    raise ValueError("unbalanced table initialiser")
ENTRY_RE = re.compile(r"^\[(\d+)\] = STEP(_NOARG|_WITH)?\(\s*(\w+)\s*(?:,\s*(.*?)\s*)?\)$", re.S)


def call_for(kind: str, callee: str, arg: str, params: list) -> str:
    sig = SIGS[callee]
    if kind == "_NOARG":
        return "%s(wk);" % callee
    if kind != "_WITH":
        if passthrough(callee):
            return "%s(wk, &(%s) { %s });" % (callee, passthrough_type(callee), arg)
        return "%s(wk, %s);" % (callee, arg)
    if passthrough(callee):
        return "%s(wk, %s);" % (callee, arg)
    # a bare parameter of the callee's own step-struct type: expand its fields
    return "%s(wk, %s);" % (callee, ", ".join("%s->%s" % (arg, n) for _, n in sig))


def invert_source(src: str) -> str:
    edits = []
    for start, end, name, params, body in split_functions(src):
        m = TABLE_RE.search(body)
        if m is None:
            continue
        plist = parse_params(params)
        entries = []
        table = braced_body(body, m.end() - 1)
        for item in split_top_level(" ".join(x.strip() for x in table.splitlines())):
            e = ENTRY_RE.match(item.strip())
            entries.append((int(e.group(1)), call_for(e.group(2), e.group(3), e.group(4), plist)))
        chained = CHAIN_RE.search(body)
        default = chained.group(1).strip() if chained else "End_Pattern(wk);"
        arms = "".join("    case %d:\n        %s\n        break;\n\n" % (lab, call) for lab, call in entries)
        new_body = "    %s {\n%s    default:\n        %s\n        break;\n    }\n" % (
            SWITCH_HEAD,
            arms,
            default,
        )
        edits.append((start, end, "%svoid %s(%s) {\n%s}" % (
            "static " if name.startswith("static ") else "", name.replace("static ", ""), params, new_body)))
        # Formatting one function at a time keeps the diff to the conversion.
        # Most of Game/com is not clang-format clean, and reformatting a whole
        # file would bury a Recipe J commit under a few hundred style lines.
    out = src
    for start, end, text in reversed(edits):
        out = out[:start] + text + out[end:]
    if edits:
        out = out.replace(RUN_INCLUDE + "\n", "", 1)
    return out


# --------------------------------------------------------------------------
# Generated infrastructure


HEADER_WARNING = "/* Generated by tools/pattern_table.py from com_sub.h. Do not edit by hand. */\n"


def emit_infra(used: set) -> dict:
    wrapped = sorted(c for c in used if SIGS[c] and not passthrough(c))
    files = {}

    lines = [
        "/*",
        " * One step's worth of arguments, for the pattern skeletons in this folder.",
        " *",
        " * A family of pattern scripts whose steps differ in four or more values cannot",
        " * be folded onto one skeleton: `wk` plus four parameters is one over the",
        " * argument-count threshold. Where the surplus values belong to the *same*",
        " * engine call, they travel as one of these instead - the same idiom the engine",
        " * itself uses for Command_Attack_Args and its kin, and the same safety",
        " * argument as Recipe V, because every value is still written out in full, in",
        " * the call's own parameter order, at its own call site.",
        " *",
        " * Recipe J gave them a second job. A skeleton's step hands one of these to the",
        " * matching Step_ adapter in com_pattern_run.c, which unpacks it into the call",
        " * written out in full, so the table carries the same values the switch arm did.",
        " *",
        " * Each struct's field order and field types are the parameter order and",
        " * parameter types of the call it names, taken from com_sub.h.",
        " * Generated by tools/pattern_table.py.",
        " */",
        "",
        "#ifndef COM_PATTERN_ARGS_H",
        "#define COM_PATTERN_ARGS_H",
        "",
        '#include "sf33rd/Source/Game/com/com_sub.h"',
        '#include "types.h"',
        "",
    ]
    for c in wrapped:
        ps = SIGS[c]
        lines.append("/* The %d value%s %s takes, in its own parameter order. */"
                     % (len(ps), "" if len(ps) == 1 else "s", c))
        lines.append("typedef struct {")
        for t, n in ps:
            lines.append("    %s%s%s;" % (t, "" if t.endswith("*") else " ", n))
        lines.append("} %s;" % step_struct(c))
        lines.append("")
    lines.append("/* The calls that take one of the engine's own argument objects. Naming it")
    lines.append(" * after the call too lets a step spell it the way every other step is")
    lines.append(" * spelled: STEP, the call, and the values, in the call's parameter order. */")
    for c in sorted(x for x in used if SIGS[x] and passthrough(x)):
        lines.append("typedef %s %s;" % (passthrough_type(c), step_struct(c)))
    lines.append("")
    lines += ["#endif", ""]
    files["com_pattern_args.h"] = "\n".join(lines)

    lines = [
        "/*",
        " * Recipe J - the pattern skeletons' dispatch table and its interpreter.",
        " *",
        " * A COM pattern script is a step counter and one engine call per step. The",
        " * skeletons used to spell that as a switch whose every arm was a single call;",
        " * they spell it as this table now, keyed by the same step numbers the case",
        " * labels held.",
        " */",
        "",
        "#ifndef COM_PATTERN_RUN_H",
        "#define COM_PATTERN_RUN_H",
        "",
        '#include "sf33rd/Source/Game/com/patterns/com_pattern_args.h"',
        '#include "structs.h"',
        '#include "types.h"',
        "",
        "/* One step: the engine call, and the arguments it was written with. */",
        "typedef void (*Pattern_Step_Fn)(PLW* wk, const void* arg);",
        "",
        "typedef struct {",
        "    Pattern_Step_Fn fn;",
        "    const void* arg;",
        "} Pattern_Step;",
        "",
        "/* One step, written the way the arm that held it was: the engine call by",
        " * name, then the values it was called with, in its own parameter order.",
        " * STEP_WITH takes one of the engine's own argument objects instead, and",
        " * STEP_NOARG the calls that take nothing but the work pointer. */",
        "#define STEP(call, ...) { Step_##call, &(const call##_Step) { __VA_ARGS__ } }",
        "#define STEP_WITH(call, ...) { Step_##call, (__VA_ARGS__) }",
        "#define STEP_NOARG(call) { Step_##call, NULL }",
        "",
        "/* Runs the step the COM step counter selects. 0 if it selected none, which is",
        " * every index the switch used to send to its default arm: past the last step,",
        " * or a hole the step numbers left. */",
        "s32 Run_Pattern_Steps(PLW* wk, const Pattern_Step* steps, s32 count);",
        "",
        "/* The same, with the default arm all but five of the skeletons had. */",
        "void Run_Pattern(PLW* wk, const Pattern_Step* steps, s32 count);",
        "",
    ]
    for c in sorted(used):
        lines.append("void Step_%s(PLW* wk, const void* arg);" % c)
    lines += ["", "#endif", ""]
    files["com_pattern_run.h"] = "\n".join(lines)

    lines = [
        "/**",
        " * @file com_pattern_run.c",
        " * Recipe J - the pattern skeletons' dispatch table and its interpreter.",
        " *",
        " * The adapters are generated from com_sub.h's own signatures, so every value",
        " * still reaches its call in the call's own parameter order, with the call's",
        " * own types. See tools/pattern_table.py.",
        " */",
        "",
        '#include "sf33rd/Source/Game/com/patterns/com_pattern_run.h"',
        "",
        '#include "common.h"',
        '#include "sf33rd/Source/Game/com/com_sub.h"',
        '#include "sf33rd/Source/Game/engine/workuser.h"',
        "",
        "s32 Run_Pattern_Steps(PLW* wk, const Pattern_Step* steps, s32 count) {",
        "    s32 step = CP_Index[wk->wu.id][0];",
        "",
        "    if (step >= count) {",
        "        return 0;",
        "    }",
        "",
        "    if (steps[step].fn == NULL) {",
        "        return 0;",
        "    }",
        "",
        "    steps[step].fn(wk, steps[step].arg);",
        "    return 1;",
        "}",
        "",
        "void Run_Pattern(PLW* wk, const Pattern_Step* steps, s32 count) {",
        "    if (!Run_Pattern_Steps(wk, steps, count)) {",
        "        End_Pattern(wk);",
        "    }",
        "}",
        "",
    ]
    for c in sorted(used):
        ps = SIGS[c]
        lines.append("void Step_%s(PLW* wk, const void* arg) {" % c)
        if not ps:
            lines.append("    (void)arg;")
            lines.append("    %s(wk);" % c)
        elif passthrough(c):
            lines.append("    %s(wk, arg);" % c)
        else:
            lines.append("    const %s* a = arg;" % step_struct(c))
            lines.append("")
            lines.append("    %s(wk, %s);" % (c, ", ".join("a->" + n for _, n in ps)))
        lines.append("}")
        lines.append("")
    files["com_pattern_run.c"] = "\n".join(lines)
    return files


# --------------------------------------------------------------------------


def used_callees(paths):
    """Every engine call the skeletons make, read from the switch form.

    A file that has already been converted is inverted first, so regenerating
    the infrastructure from a converted tree gives the same answer.
    """
    used = set()
    for p in paths:
        src = Path(p).read_text()
        if TABLE_RE.search(src):
            src = invert_source(src)
        for _, _, _, _, body in split_functions(src):
            parsed = parse_skeleton(body)
            if parsed is None:
                continue
            for _, call in parsed[0]:
                used.add(parse_call(call)[0])
    return used


CLANG_FORMAT = next(
    (c for c in (
        "clang-format",
        "/opt/homebrew/opt/llvm/bin/clang-format",
        "/Library/Developer/CommandLineTools/usr/bin/clang-format",
    ) if __import__("shutil").which(c)),
    None,
)


TOKEN_RE = re.compile(
    r"""\s+|/\*.*?\*/|//[^\n]*"""          # skipped: whitespace and comments
    r"""|"(?:\\.|[^"\\])*"|'(?:\\.|[^'\\])*'"""  # kept: string and char literals
    r"""|[A-Za-z_]\w*|\d[\w.]*|.""",       # kept: identifiers, numbers, punctuation
    re.S,
)


def tokens(src: str) -> list:
    """Every C token in src, with whitespace and comments dropped.

    The round-trip is checked on tokens rather than on text so that it answers
    the one question that matters - did any call, argument or step number move -
    without also insisting that the file was laid out the way clang-format would
    lay it out. Most of Game/com was not.
    """
    out = []
    for m in TOKEN_RE.finditer(src):
        t = m.group(0)
        if t.isspace() or t.startswith("/*") or t.startswith("//"):
            continue
        out.append(t)
    return out


def clang_format(text: str, name: str) -> str:
    if CLANG_FORMAT is None:
        sys.exit("clang-format is not on PATH; the conversion must land clang-format clean")
    r = subprocess.run(
        [CLANG_FORMAT, "--assume-filename=" + name,
         "--style={BasedOnStyle: InheritParentConfig, SortIncludes: Never}"],
        input=text, capture_output=True, text=True, cwd=REPO,
    )
    return r.stdout if r.returncode == 0 else text


def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--emit-infra", action="store_true")
    ap.add_argument("--convert", nargs="*", default=None)
    ap.add_argument("--verify", nargs="*", default=None)
    ap.add_argument("--restyle", nargs="*", default=None,
                    help="invert an already-converted file and convert it again, to pick up a "
                         "change in how the tables are written")
    ap.add_argument("--base", default="HEAD")
    a = ap.parse_args()

    if a.emit_infra:
        paths = sorted(COM.rglob("*.c"))
        for name, text in emit_infra(used_callees(paths)).items():
            (PATTERNS / name).write_text(clang_format(text, name))
            print("wrote", (PATTERNS / name).relative_to(REPO))
        return 0

    if a.convert is not None:
        for p in a.convert:
            src = Path(p).read_text()
            Path(p).write_text(convert_source(src))
            print("converted", p)
        return 0

    if a.restyle is not None:
        for q in a.restyle:
            src = Path(q).read_text()
            Path(q).write_text(clang_format(convert_source(invert_source(src)), Path(q).name))
            print("restyled", q)
        return 0

    if a.verify is not None:
        bad = 0
        for p in a.verify:
            rel = str(Path(p).resolve().relative_to(REPO))
            old = subprocess.run(
                ["git", "show", "%s:%s" % (a.base, rel)], capture_output=True, text=True, cwd=REPO
            ).stdout
            if TABLE_RE.search(old):
                print("SKIP %s  %s already holds the table form; verify against the "
                      "commit before the conversion" % (rel, a.base))
                continue
            back = invert_source(Path(p).read_text())
            want, got = tokens(old), tokens(back)
            if want == got:
                print("OK   %s  the table form inverts to the source it replaced" % rel)
            else:
                bad += 1
                print("FAIL %s  the inverse does not reproduce %s" % (rel, a.base))
                import difflib

                for line in list(difflib.unified_diff(want, got, lineterm="", n=3))[:40]:
                    print("    " + line)
        return 1 if bad else 0

    ap.print_help()
    return 2


if __name__ == "__main__":
    sys.exit(main())
