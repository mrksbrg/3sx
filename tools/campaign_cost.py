#!/usr/bin/env python3
"""Estimate what the refactoring campaign cost in tokens, priced at public API list rates.

Reads the two log stores an agent harness leaves on a machine:

  ~/.claude/projects/<project>/*.jsonl   Claude Code transcripts; every assistant message
                                         carries usage: input, output, cache writes (split
                                         by 5m / 1h TTL) and cache reads, plus the model.
  ~/.codex/sessions/YYYY/MM/DD/*.jsonl   Codex rollouts; token_count events carry a
                                         cumulative total_token_usage per session and the
                                         turn_context carries the model.

    python tools/campaign_cost.py [--since 2026-09-01] [--until 2026-09-22] [--cwd-filter "Street Fighter"]

Run it on every machine that took part and add the tables up. Subscription plans are not
billed per token, so the dollar figures are what the same tokens would have cost on the
API at list price, not what was paid. Prices are the September 2026 list; edit PRICES.
"""
from __future__ import annotations

import argparse
import collections
import glob
import json
import os

# $ per million tokens: (input, cache write 5m, cache write 1h, cache read, output)
PRICES = {
    "claude-fable-5-1": (10.0, 12.5, 20.0, 0.25, 50.0),
    "claude-opus-5": (5.0, 6.25, 10.0, 0.50, 25.0),
    "claude-sonnet-5": (2.0, 2.50, 4.0, 0.20, 10.0),
    "claude-haiku-4-5": (1.0, 1.25, 2.0, 0.10, 5.0),
    # OpenAI: (input, -, -, cached input, output); Codex logs do not split cache writes
    "gpt-5.6-sol": (4.0, None, None, 0.40, 20.0),
    "gpt-5.6-terra": (2.0, None, None, 0.20, 12.0),
    "gpt-5.6-luna": (0.2, None, None, 0.02, 1.2),
    "gpt-5.3-codex": (1.75, None, None, 0.175, 14.0),
    # not on the public price list; priced as terra and marked as an assumption
    "codex-auto-review": (2.0, None, None, 0.20, 12.0),
}


def price(model, uncached, w5m, w1h, read, out):
    p = PRICES.get(model)
    if p is None:
        return None
    base, p5, p1, pr, po = p
    return (uncached * base + w5m * (p5 or 0) + w1h * (p1 or 0) + read * pr + out * po) / 1e6


def claude_sessions(root, since, until, cwd_filter):
    rows = []
    for f in sorted(glob.glob(os.path.join(root, "*", "*.jsonl"))):
        if cwd_filter and cwd_filter.replace(" ", "-") not in os.path.basename(os.path.dirname(f)):
            continue
        first = last = None
        per_model = collections.defaultdict(lambda: collections.Counter())
        with open(f, encoding="utf-8", errors="replace") as fh:
            for line in fh:
                try:
                    o = json.loads(line)
                except ValueError:
                    continue
                ts = o.get("timestamp")
                if ts:
                    first = first or ts
                    last = ts
                m = o.get("message") if isinstance(o.get("message"), dict) else None
                if not (m and m.get("role") == "assistant" and m.get("usage")):
                    continue
                model = m.get("model") or "?"
                if model.startswith("<"):
                    continue
                u = m["usage"]
                c = per_model[model]
                c["turns"] += 1
                c["uncached"] += u.get("input_tokens", 0) or 0
                c["out"] += u.get("output_tokens", 0) or 0
                c["read"] += u.get("cache_read_input_tokens", 0) or 0
                cc = u.get("cache_creation") or {}
                w5 = cc.get("ephemeral_5m_input_tokens")
                w1 = cc.get("ephemeral_1h_input_tokens")
                if w5 is None and w1 is None:
                    w5 = u.get("cache_creation_input_tokens", 0) or 0  # TTL unknown: price as 5m
                c["w5m"] += w5 or 0
                c["w1h"] += w1 or 0
        if not first or first[:10] < since or first[:10] > until:
            continue
        for model, c in per_model.items():
            rows.append(("claude", os.path.basename(f)[:8], first[:16], last[:16], model, c))
    return rows


def codex_sessions(root, since, until, cwd_filter):
    rows = []
    for f in sorted(glob.glob(os.path.join(root, "*", "*", "*", "*.jsonl"))):
        day = "-".join(f.replace("\\", "/").split("/")[-4:-1])
        if day < since or day > until:
            continue
        cwd = None
        models = collections.Counter()
        first = last = None
        total = None
        with open(f, encoding="utf-8", errors="replace") as fh:
            for line in fh:
                try:
                    o = json.loads(line)
                except ValueError:
                    continue
                ts = o.get("timestamp")
                if ts:
                    first = first or ts
                    last = ts
                p = o.get("payload") or {}
                if not isinstance(p, dict):
                    continue
                cwd = p.get("cwd") or cwd
                if p.get("model"):
                    models[p["model"]] += 1
                if p.get("type") == "token_count" and p.get("info") and p["info"].get("total_token_usage"):
                    total = p["info"]["total_token_usage"]
        if not total or not models:
            continue
        if cwd_filter and cwd_filter not in (cwd or ""):
            continue
        model = models.most_common(1)[0][0]
        c = collections.Counter(turns=0)
        c["uncached"] = total.get("input_tokens", 0) - total.get("cached_input_tokens", 0)
        c["read"] = total.get("cached_input_tokens", 0)
        c["w5m"] = total.get("cache_write_input_tokens", 0) or 0
        c["out"] = total.get("output_tokens", 0)
        rows.append(("codex", os.path.basename(f)[8:27], (first or "")[:16], (last or "")[:16], model, c))
    return rows


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--since", default="2026-09-01")
    ap.add_argument("--until", default="2026-09-30")
    ap.add_argument("--cwd-filter", default="Street Fighter")
    ap.add_argument("--claude-root", default=os.path.expanduser("~/.claude/projects"))
    ap.add_argument("--codex-root", default=os.path.expanduser("~/.codex/sessions"))
    ap.add_argument("--sessions", action="store_true", help="print one line per session")
    args = ap.parse_args()

    rows = claude_sessions(args.claude_root, args.since, args.until, args.cwd_filter) + \
        codex_sessions(args.codex_root, args.since, args.until, args.cwd_filter)

    if args.sessions:
        for h, sid, a, b, model, c in rows:
            cost = price(model, c["uncached"], c["w5m"], c["w1h"], c["read"], c["out"])
            print("%-6s %-19s %s -> %s  %-18s out %9d  read %11d  write %9d  $%.2f" % (
                h, sid, a, b, model, c["out"], c["read"], c["w5m"] + c["w1h"], cost or 0))
        print()

    by_model = collections.defaultdict(lambda: collections.Counter())
    for h, sid, a, b, model, c in rows:
        m = by_model[(h, model)]
        m["sessions"] += 1
        for k, v in c.items():
            m[k] += v
    print("%-6s %-18s %8s %12s %12s %14s %12s %10s" % ("harness", "model", "sessions", "uncached in", "cache write", "cache read", "output", "API $"))
    grand = 0.0
    for (h, model), m in sorted(by_model.items()):
        cost = price(model, m["uncached"], m["w5m"], m["w1h"], m["read"], m["out"])
        grand += cost or 0
        print("%-6s %-18s %8d %12d %12d %14d %12d %10s" % (
            h, model, m["sessions"], m["uncached"], m["w5m"] + m["w1h"], m["read"], m["out"],
            ("%.2f" % cost) if cost is not None else "no price"))
    print("%-6s %-18s %8s %12s %12s %14s %12s %10.2f" % ("total", "", "", "", "", "", "", grand))
    print("\nCache writes on Claude are priced at the TTL the transcript records (1h in Claude Code); Codex logs carry no write split.")
    print("codex-auto-review is priced as gpt-5.6-terra (assumption). Subscription plans are not billed per token; this is API-equivalent list price.")


if __name__ == "__main__":
    main()
