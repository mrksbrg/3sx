#!/usr/bin/env python3
"""List every identifier the first-party source declares, as the compiler sees it.

    python tools/identifiers.py [--compdb build/compile_commands.json] [-o identifiers.csv]

Parses each first-party translation unit with libclang using the flags the build uses,
walks the AST, and writes one row per declaration whose location is in first-party
source (src/ minus the vendored and generated folders): functions, parameters, locals,
globals and statics, struct/union/enum tags, fields, enum constants, typedefs, labels and
macros. Declarations seen through several translation units (headers) are written once.

The output is a checklist for a renaming pass: every row is something a rename must
visit, with its kind, linkage, file and line, and the function or record it belongs to.
Requires: pip install libclang; a compile database from `ninja -C build -t compdb`; the build's clang on PATH,
so its libclang and resource directory (builtin headers) are used and every unit parses without errors.
"""
from __future__ import annotations

import argparse
import collections
import csv
import json
import os
import shlex
import sys

import clang.cindex as ci

EXCLUDE = ("src/imgui/", "src/stb/", "src/argparse/", "src/bin2obj/", "src/platform/video/opengl/glad/", "third_party/")

KINDS = {
    ci.CursorKind.FUNCTION_DECL: "function",
    ci.CursorKind.PARM_DECL: "parameter",
    ci.CursorKind.VAR_DECL: "variable",
    ci.CursorKind.FIELD_DECL: "field",
    ci.CursorKind.STRUCT_DECL: "struct",
    ci.CursorKind.UNION_DECL: "union",
    ci.CursorKind.ENUM_DECL: "enum",
    ci.CursorKind.ENUM_CONSTANT_DECL: "enum_constant",
    ci.CursorKind.TYPEDEF_DECL: "typedef",
    ci.CursorKind.LABEL_STMT: "label",
    ci.CursorKind.MACRO_DEFINITION: "macro",
}


def norm(path):
    return path.replace("\\", "/")


def first_party(path, repo):
    p = norm(path)
    if not p.startswith(repo + "/src/"):
        return False
    rel = p[len(repo) + 1:]
    return not any(rel.startswith(e) for e in EXCLUDE)


def clang_args(entry):
    """The build's flags for one translation unit, minus the compiler, output and dependency options."""
    argv = shlex.split(entry["command"].replace("\\", "/"), posix=True) if "command" in entry else entry["arguments"]
    out = []
    skip = 0
    for a in argv[1:]:
        if skip:
            skip -= 1
            continue
        if a in ("-o", "-MF", "-MT", "-MQ"):
            skip = 1
            continue
        if a in ("-c", "-MD", "-MMD") or a.endswith(".c") or a.endswith(".cpp"):
            continue
        out.append(a)
    return out


def walk(cursor, repo, rows, seen, scope=None):
    for c in cursor.get_children():
        loc = c.location
        if loc.file is None:
            continue
        kind = KINDS.get(c.kind)
        if kind and c.spelling and first_party(loc.file.name, repo):
            key = c.get_usr() or ("%s:%s:%d:%d" % (kind, norm(loc.file.name), loc.line, loc.column))
            if c.kind == ci.CursorKind.FUNCTION_DECL and not c.is_definition():
                kind = "prototype"
            if key not in seen or (kind == "function" and seen[key] == "prototype"):
                seen[key] = kind
                if c.kind in (ci.CursorKind.FUNCTION_DECL, ci.CursorKind.VAR_DECL):
                    linkage = {ci.LinkageKind.INTERNAL: "static", ci.LinkageKind.EXTERNAL: "external"}.get(c.linkage, "local" if scope else "?")
                    if c.kind == ci.CursorKind.VAR_DECL and scope and c.linkage == ci.LinkageKind.NO_LINKAGE:
                        linkage = "local"
                else:
                    linkage = ""
                rows[key] = dict(name=c.spelling, kind=kind, linkage=linkage, scope=scope or "",
                                 file=norm(loc.file.name)[len(repo) + 1:], line=loc.line,
                                 type=(c.type.spelling if c.kind in (ci.CursorKind.VAR_DECL, ci.CursorKind.PARM_DECL, ci.CursorKind.FIELD_DECL) else ""))
        child_scope = scope
        if c.kind == ci.CursorKind.FUNCTION_DECL:
            child_scope = c.spelling
        elif c.kind in (ci.CursorKind.STRUCT_DECL, ci.CursorKind.UNION_DECL, ci.CursorKind.ENUM_DECL) and c.spelling:
            child_scope = c.spelling
        walk(c, repo, rows, seen, child_scope)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--compdb", default="build/compile_commands.json")
    ap.add_argument("-o", "--output", default="identifiers.csv")
    ap.add_argument("--libclang", default=None, help="path to libclang.dll/.so; default: the one on PATH's clang, else the bundled one")
    ap.add_argument("--resource-dir", default=None, help="clang resource dir (builtin headers); default: `clang -print-resource-dir`")
    args = ap.parse_args()
    import shutil, subprocess
    clang_exe = shutil.which("clang")
    if args.libclang:
        ci.Config.set_library_file(args.libclang)
    elif clang_exe:
        for cand in (os.path.join(os.path.dirname(clang_exe), "libclang.dll"), os.path.join(os.path.dirname(clang_exe), "..", "lib", "libclang.so")):
            if os.path.exists(cand):
                ci.Config.set_library_file(cand)
                break
    resource_dir = args.resource_dir
    if not resource_dir and clang_exe:
        resource_dir = subprocess.run([clang_exe, "-print-resource-dir"], capture_output=True, text=True).stdout.strip()
    extra = ["-resource-dir", norm(resource_dir)] if resource_dir else []
    repo = norm(os.path.abspath(os.getcwd()))
    entries = [e for e in json.load(open(args.compdb, encoding="utf-8")) if first_party(e["file"], repo)]
    index = ci.Index.create()
    rows, seen = {}, {}
    failed = 0
    units_with_errors = 0
    for i, e in enumerate(entries, 1):
        try:
            tu = index.parse(e["file"], args=clang_args(e) + extra, options=ci.TranslationUnit.PARSE_DETAILED_PROCESSING_RECORD | ci.TranslationUnit.PARSE_SKIP_FUNCTION_BODIES * 0)
        except ci.TranslationUnitLoadError as ex:
            failed += 1
            print("failed:", e["file"], ex, file=sys.stderr)
            continue
        errors = [d for d in tu.diagnostics if d.severity >= ci.Diagnostic.Error]
        if errors:
            units_with_errors += 1
            if units_with_errors <= 5:
                print("errors in", norm(e["file"])[len(repo) + 1:], ":", errors[0].spelling, file=sys.stderr)
        walk(tu.cursor, repo, rows, seen)
        if i % 100 == 0:
            print("%d/%d translation units, %d identifiers" % (i, len(entries), len(rows)), file=sys.stderr)
    with open(args.output, "w", newline="", encoding="utf-8") as fh:
        w = csv.DictWriter(fh, fieldnames=["name", "kind", "linkage", "scope", "file", "line", "type"])
        w.writeheader()
        for r in sorted(rows.values(), key=lambda r: (r["file"], r["line"], r["name"])):
            w.writerow(r)
    by_kind = collections.Counter(r["kind"] for r in rows.values())
    print("%d translation units (%d failed to load, %d with compile errors), %d identifiers -> %s" % (len(entries), failed, units_with_errors, len(rows), args.output))
    for k, n in by_kind.most_common():
        print("  %-14s %6d" % (k, n))
    print("  distinct names %6d" % len({r["name"] for r in rows.values()}))


if __name__ == "__main__":
    main()
