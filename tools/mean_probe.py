#!/usr/bin/env python3
"""Price a file's Overall Code Complexity finding before refactoring it.

Overall Code Complexity is CodeScene's mean cyclomatic complexity for the file,
measured against a flat threshold of 4. It is the one finding that *every* legal
move in this campaign pays into by the same amount: lifting `b` branches into a
helper takes `b` off the parent and gives the helper `1 + b`, so the file's total
complexity rises by exactly one and its function count by exactly one, whatever
the helper contains. A straight-line deduplication does the same.

That makes the finding cheap to price in advance, and pricing it changes what
every later measurement says - see *Price the file's cheapest finding before
inheriting a plateau* in docs/refactoring/PLAYBOOK.md. This tool does the
pricing: it inserts `k` throwaway one-line functions, asks CodeScene whether the
finding is still open, binary-searches the smallest `k` that closes it, and puts
the file back.

    python tools/mean_probe.py src/.../a.c src/.../b.c

    src/.../a.c    9.38 -> 10.00 on 4 more low-complexity functions

The number is what to spend before re-pricing anything the file's plateau note
rejected. The score on the right is what the file reaches on those functions
alone, with nothing else done to it.

The file is restored even when the probe is interrupted. Nothing is committed.
"""

from __future__ import annotations

import argparse
import re
import subprocess
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
FINDING = "Overall Code Complexity"

# Two functions per unit, so neither is unused: the compiler never sees these,
# but a reader who interrupts the probe should find something that builds.
PROBE = (
    "static int cs_probe_{i}(int x) {{ return x; }}\n"
    "int cs_probe_use_{i}(int x) {{ return cs_probe_{i}(x); }}\n"
)


def review(path: str) -> tuple[float, bool]:
    """(score, is the mean finding open) for one file."""
    out = subprocess.run(
        [sys.executable, str(REPO / "tools" / "ch.py"), "--review", path],
        capture_output=True, text=True, cwd=REPO,
    ).stdout
    m = re.search(r"([0-9.]+)\s+" + re.escape(path), out)
    if not m:
        sys.exit("no score for %s - is CS_ACCESS_TOKEN set?\n%s" % (path, out))
    return float(m.group(1)), FINDING in out


def insertion_point(src: str) -> int:
    """Just after the last #include, so nothing is declared before its types."""
    includes = [m.end() for m in re.finditer(r"^#include .*$", src, re.M)]
    return includes[-1] + 1 if includes else 0


def probe(path: str, bound: int) -> tuple[float, float | None, int | None, bool]:
    src = Path(path).read_text()
    at = insertion_point(src)
    try:
        score, still_open = review(path)
        if not still_open:
            return score, score, 0, False

        lo, hi, best = 1, bound, None
        while lo <= hi:
            k = (lo + hi) // 2
            blob = "\n" + "".join(PROBE.format(i=i) for i in range(k))
            Path(path).write_text(src[:at] + blob + src[at:])
            probed, open_now = review(path)
            if open_now:
                lo = k + 1
            else:
                best, hi = (k, probed), k - 1
        return score, (best[1] if best else None), (best[0] if best else None), True
    finally:
        Path(path).write_text(src)


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("files", nargs="+")
    ap.add_argument("--bound", type=int, default=32,
                    help="largest k to search (default 32)")
    args = ap.parse_args()

    for path in args.files:
        before, after, k, was_open = probe(path, args.bound)
        if not was_open:
            print("%-58s %.2f   the mean finding is already closed" % (path, before))
        elif k is None:
            print("%-58s %.2f   not closed within %d functions" % (path, before, args.bound))
        else:
            print("%-58s %.2f -> %.2f on %d more low-complexity functions"
                  % (path, before, after, k))


if __name__ == "__main__":
    main()
