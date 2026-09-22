#!/usr/bin/env python3
"""What the tools cost: per-tool call counts and result sizes in Claude Code transcripts,
and the share of each session's context that CodeScene's output occupied.

    python tools/campaign_tools.py [--since 2026-09-01] [--until 2026-09-22] [--claude-root "~/.claude*/projects"]

A tool result is paid for once as cache write and then again as a cache read on every
later turn of the session, so its cost is its size times the turns that follow it. The
"CS ctx share" column estimates that: for each response, the CodeScene bytes already in
the transcript (at four characters per token) divided by that response's cache-read
tokens, averaged over the session. CodeScene output is recognised whether it came through
the MCP tool or through a script run in Bash, by the text it produces.

What this cannot measure: the MCP server's *tool definitions*. Transcripts do not record
the system prompt or the tool block. Their only trace is the first response's context
("1st ctx": system prompt + tools + first message), and Claude Code's /context view is the
authoritative reading of that block - as a share of the window at the moment it is run,
which is large on early turns and small once the context has grown.
"""
from __future__ import annotations

import argparse
import collections
import glob
import json
import os

CODESCENE_MARKERS = ("Code Health score", '"review":', "code_health_review", "code_health_score")


def result_text(block):
    c = block.get("content")
    if isinstance(c, str):
        return c
    if isinstance(c, list):
        return "".join(x.get("text", "") for x in c if isinstance(x, dict))
    return ""


def analyse(path, since, until):
    seen = set()
    tool_by_id = {}
    calls = collections.Counter()
    chars = collections.Counter()
    cs_calls = 0
    cs_chars_total = 0
    cs_chars_so_far = 0      # CodeScene text accumulated in the transcript before the current response
    cs_weighted = 0.0        # sum over responses of CodeScene tokens present / cache-read tokens
    reads = 0
    responses = 0
    model = None
    first = None
    first_ctx = None         # context of the first response: system prompt + tool definitions + first message
    for line in open(path, encoding="utf-8", errors="replace"):
        try:
            o = json.loads(line)
        except ValueError:
            continue
        first = first or o.get("timestamp")
        m = o.get("message") if isinstance(o.get("message"), dict) else None
        if not m:
            continue
        content = m.get("content")
        if m.get("role") == "assistant":
            key = (m.get("id"), o.get("requestId"))
            if key not in seen and m.get("usage") and not (m.get("model") or "").startswith("<"):
                seen.add(key)
                model = m.get("model")
                responses += 1
                u = m["usage"]
                r = u.get("cache_read_input_tokens", 0) or 0
                reads += r
                if first_ctx is None:
                    first_ctx = r + (u.get("cache_creation_input_tokens") or 0) + (u.get("input_tokens") or 0)
                if r:
                    cs_weighted += min(1.0, (cs_chars_so_far / 4) / r)
            if isinstance(content, list):
                for b in content:
                    if b.get("type") == "tool_use":
                        tool_by_id[b.get("id")] = b.get("name")
                        calls[b.get("name")] += 1
        elif m.get("role") == "user" and isinstance(content, list):
            for b in content:
                if b.get("type") != "tool_result":
                    continue
                name = tool_by_id.get(b.get("tool_use_id"), "?")
                text = result_text(b)
                chars[name] += len(text)
                if (name or "").startswith("mcp__codescene") or any(k in text for k in CODESCENE_MARKERS):
                    cs_calls += 1
                    cs_chars_total += len(text)
                    cs_chars_so_far += len(text)
    if not first or first[:10] < since or first[:10] > until or not responses:
        return None
    return dict(session=os.path.basename(path)[:8], model=model, responses=responses, reads=reads,
                first_ctx=first_ctx or 0, calls=calls, chars=chars, cs_calls=cs_calls, cs_chars=cs_chars_total,
                cs_share=(cs_weighted / responses) if responses else 0.0)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--since", default="2026-09-01")
    ap.add_argument("--until", default="2026-09-30")
    ap.add_argument("--claude-root", default=os.path.expanduser("~/.claude*/projects"))
    args = ap.parse_args()
    sessions = [s for s in (analyse(f, args.since, args.until)
                            for f in sorted(glob.glob(os.path.join(args.claude_root, "*", "*.jsonl")))) if s]

    calls = collections.Counter()
    chars = collections.Counter()
    for s in sessions:
        calls.update(s["calls"])
        chars.update(s["chars"])
    tc, tch = sum(calls.values()), sum(chars.values())
    print("%-40s %7s %7s %13s %7s" % ("tool", "calls", "share", "result chars", "share"))
    for name, n in calls.most_common(15):
        print("%-40s %7d %6.1f%% %13s %6.1f%%" % (name, n, 100 * n / tc, f"{chars[name]:,}", 100 * chars[name] / max(tch, 1)))
    print("%-40s %7d %7s %13s" % ("total", tc, "", f"{tch:,}"))

    print("\n%-9s %-18s %9s %14s %10s %8s %12s %11s" % ("session", "model", "responses", "cache reads", "1st ctx", "CS calls", "CS chars", "CS ctx share"))
    tot_reads = tot_w = 0.0
    tot_cs_calls = tot_cs_chars = 0
    for s in sorted(sessions, key=lambda s: -s["reads"]):
        print("%-9s %-18s %9d %14s %10s %8d %12s %10.1f%%" % (
            s["session"], s["model"], s["responses"], f'{s["reads"]:,}', f'{s["first_ctx"]:,}',
            s["cs_calls"], f'{s["cs_chars"]:,}', 100 * s["cs_share"]))
        tot_reads += s["reads"]
        tot_w += s["cs_share"] * s["reads"]
        tot_cs_calls += s["cs_calls"]
        tot_cs_chars += s["cs_chars"]
    print("%-9s %-18s %9s %14s %10s %8d %12s %10.1f%%  (weighted by cache reads)" % (
        "all", "", "", f"{int(tot_reads):,}", "", tot_cs_calls, f"{tot_cs_chars:,}", 100 * tot_w / max(tot_reads, 1)))
    print("\nCS ctx share: CodeScene *output* resident in context as a fraction of each response's cache reads, averaged over")
    print("the session, assuming results stay in context (no compaction) and four characters per token.")
    print("NOT measured here: the MCP tool *definitions*. Transcripts do not record the system prompt or tool block; their")
    print("size is only visible inside '1st ctx' (system prompt + tools + first message) or in Claude Code's /context view.")


if __name__ == "__main__":
    main()
