# Refactoring Playbook - Core

A codebase-independent core of the playbook that took 3SX from a mean Code Health of 8.52
to every scored file at 10.00 in three weeks. It keeps the operating loop, the rules, the
verification tiers and the twenty-two recipes with one short example each, and drops every
plateau, file name and measurement that belonged to that project. Its companion,
[`CODE-HEALTH-FIELD-GUIDE.md`](CODE-HEALTH-FIELD-GUIDE.md), holds what was learned about
the metric itself.

**How to start a new campaign from this file.** Copy it as the new repository's
`PLAYBOOK.md`. Add an empty `PLAYBOOK-NOTES.md` beside it for the plateaus and rules the new
codebase will teach you, dated and with the number that was measured. Decide the
prohibition list and the verification tiers for the new codebase on day one, before the
first commit, because those two decisions shape everything the agents will refuse.

---

## 1. The operating loop

Every task is scoped to **one file**, bounded by a **closed catalogue of transformations**,
and judged by an **external metric** rather than by taste. That combination is what lets
the work be handed to many agents, including agents that cannot reason about the whole
system.

**The three rules.**

1. **One recipe, one function, one commit.** A commit may apply the same recipe several
   times to one function, but never two recipes, and never two functions. The point is
   that a reviewer can revert exactly one behaviour.
2. **Re-measure after every commit.** If the score improved, keep it. If it did not, read
   the review: keep the change only when the targeted function left a smell category or
   its complexity fell, because a flat score often means a finding shrank without
   closing. Otherwise revert.
3. **When in doubt, stop and report.** An unfinished task is a good result. A silently
   broken program is not.

**The measure-first habit.** Before touching a file, run the review and record the score.
Before applying a transformation you are not sure of, apply it to a **scratch copy** and
score that. A probe costs seconds; a reverted commit costs a session. Select on legality
first and on score second: a probe that scores 10.00 by changing a value is a defect, not a
win.

**Plateau notes.** A plateau is a result, not a failure: the point where no legal recipe
raises the score further. Record it with the file, the score, the transformations tried and
the number each measured, so the next agent does not spend a session rediscovering it. Write
it narrowly. A note that names a mechanism is a claim to check later, not a finding to
inherit; several plateaus in the source campaign were overturned by re-measuring.

---

## 2. What is forbidden, and why

The prohibition list is the single most important decision in a campaign, and it depends on
what the codebase can prove about itself. Two tiers.

**Always forbidden, in any codebase.** These change behaviour and no recipe here needs
them:

- Reordering statements that have side effects.
- Changing a comparison operator, including `<` to `<=`.
- Changing arithmetic, bitwise operations or shifts.
- Deleting code that looks dead without proof that it is unreachable.
- Fixing a bug you noticed. Report it in its own issue.
- Widening the linkage of an existing `static` so another file can reach it, except for a
  helper the campaign itself created (see Recipe S).

**Forbidden where the codebase has no oracle.** The source campaign also forbade every
change to a numeric, string or character literal, every type change including signedness
and width, and every change to a `const` data table, because it was a decompiled program
with no tests and no replay corpus. Those rules made a literal-fingerprint guard the proof
of every commit. A codebase with tests, golden outputs or a simulator can relax them,
**recipe by recipe and with the tests as the proof**, but it should start with them on and
relax deliberately. Recipes O, M, J2 and Q below show what a relaxation looks like when it
is done with an equivalence harness instead of a guard.

**Case labels are literals.** Renumbering states, `case 3:` to `case 0:` with an offset on
the switch expression, is a literal change however tempting it looks when two state
machines differ only in their numbering. Recipes X, L and J keep labels as they are.

---

## 3. Verification tiers

Cost rises down the table. Every commit takes the first two tiers; the rest are chosen by
the risk the recipe carries.

| Tier | What it proves | When |
| --- | --- | --- |
| **Build** under the project's own warnings-as-errors | it compiles, nothing became unused | every commit |
| **Guard**: literal fingerprint and call fingerprint before and after | no value or callee vanished or was substituted | every commit |
| **Tests / golden outputs**, where the codebase has them | observable behaviour on the covered paths | every commit that touches a covered path |
| **Trace replay**: identical inputs to two builds, per-frame or per-step state hashes compared | determinism over a long run | recipes that reroute control flow (F, R, X chains, J, K) and once before a push |
| **Equivalence harness**: old and new region compiled behind the same fakes, enumerated over the input domain | exact equivalence of the transformed code | recipes the guard cannot follow (M, O, J2, Q) |
| **Targeted playtest / manual check** | whatever the tiers above provably do not reach | named in the commit message |

**The guard.** Extract every literal from the file before and after, compare the
multisets, and do the same for the names of called functions. Expected signatures:

| Recipe shape | Literal fingerprint | Call fingerprint |
| --- | --- | --- |
| extract, flatten, split (E, G, X, R) | nothing removed; a guard clause may add its own `return 0` | nothing removed; each helper `+2`, its definition and the one call that replaced the block |
| deduplicate, share (D, C, P, V, T, B, N, W, F) | copies removed, every value still present somewhere | shared callees drop by the copies removed; the helper is `+1` per call site `+1` for its definition |
| file split (S) | each file alone reads as loss; the **combined** group is unchanged | the combined group is unchanged |
| pointer-passed callee (F, K, J) | unchanged | declare each callee now passed by name, so a bare mention counts as the call it replaced |

A value that vanishes from the file entirely is a FAIL. A count that drops while another
rises is a substitution and a FAIL. Copies removed with every value present is a WARN and
wants a human to confirm it is deduplication rather than a deleted block. Two things the
guard cannot see: **reordering**, which is why the prohibition on it is absolute, and
**transposed arguments** in a compound literal, whose multiset is identical. For the second,
rewrite call sites mechanically and check argument counts per call.

**The equivalence harness.** For a recipe that changes the shape of the text, compile the
base revision's region and the working tree's region into one executable behind a minimal
fake of the state they touch, run both over the whole input domain or a large corpus, record
every observable effect, and diff. State the count in the commit. Keep the harness in the
repository so the proof can be re-run against a later base.

---

## 4. The catalogue

Twenty-two recipes in four groups. Each entry gives the finding it answers, the steps, the
preconditions that make it safe, what the guard shows, and the risk tier. The examples are
schematic; keep the real ones in the notes file with their measured score.

A recurring safety argument runs through the sharing recipes and is worth naming once.
**Recipe D allows a helper to take one varying value** because with one value there is no
pair to cross. Recipes V, T, B, N, W and F allow several varying things by a different
argument: **every varying part is written out in full, in positional order, at its own
call site, and the helper does nothing with it but the operation the original performed
in that position.** It never tests one, indexes with one, compares two of them or computes
from one. The moment it does, the differences have been generalised and the recipe no
longer applies.

### 4.1 Structure inside one function

#### Recipe E - Extract Function

**Use when:** *Bumpy Road Ahead*, *Complex Method*, *Large Method*. Each nested block is a
missing function.

**How:** cut one nested block into a `static` function directly above; pass in every
variable it reads; return the single value it produces. Name it for what it does.

**Preconditions:** the block writes at most one outer local (writing many *fields* through a
pointer the block already holds is fine, and is the common case). If it writes two or more
outer locals, skip it or use Recipe O. Do not invent an out-parameter to carry results.

```c
/* before */                                 /* after */
if (p->state == STATE_HIT) {                 static void tick_hit_recovery(Player *p) {
    if (p->hit_timer > 0) {                      if (p->state != STATE_HIT) { return; }
        p->hit_timer--;                          if (p->hit_timer <= 0) { return; }
        if (p->hit_timer == 0) {                 p->hit_timer--;
            p->state = STATE_IDLE;               if (p->hit_timer == 0) { p->state = STATE_IDLE; }
        }                                    }
    }                                        ...
}                                            tick_hit_recovery(p);
```

**Guard:** extract signature. **Tier:** build and guard. **Watch:** extracting the same
shape from two sibling functions manufactures a duplication pair; see the field guide's
*one arm only* rule before lifting from both.

#### Recipe G - Guard Clauses

**Use when:** *Deep, Nested Complexity*, nesting four or more.

**How:** invert the outermost condition and return early; repeat until the body sits at one
level. Every guard returns the *same* value the original produced by falling through, so
read the end of the function first. Recipe G may invert a condition; Recipe P may not.

```c
if (p != NULL) {                    if (p == NULL) { return; }
    if (p->active) {                if (!p->active) { return; }
        work(p);          ->        work(p);
    }
}
```

**Guard:** literals added, none removed. **Tier:** build and guard.

#### Recipe P - Named Predicate

**Use when:** *Complex Conditional*, or *Complex Method* driven by compound booleans.

**How:** move the expression, character for character, into a `static` function whose name
states the intent. Do not simplify the algebra or reorder operands: `&&` short-circuits,
and reordering changes which side effects run. Name the **whole** condition when the
finding is Complex Conditional; naming only its parts leaves the finding.

**Guard:** copies of the condition's literals removed, `0`/`1` may appear. **Tier:** build
and guard.

#### Recipe R - Resolve a Goto Chain

**Use when:** *Complex Method* on a function whose branches are `if (...) goto label;`
chains, which the metric counts twice. Common in decompiled output.

**How:** replace each `goto L;` with a verbatim copy of the transfer under `L`; delete labels
now unreferenced; the label reachable by fall-through keeps its return as the tail.

**Preconditions:** every label ends in an unconditional transfer and holds nothing after
it; no label is reached by falling into it from another; every `goto` jumps forward within
the same construct; the conditions are untouched; nothing else references the labels.

**Guard:** literals added, none removed. **Tier:** control flow, so trace replay.

#### Recipe L - Lookup Table

**Use when:** *Complex Method* on a switch whose every arm is `return <constant>;`.

**How:** a `static const` array sized by the enum's count, **keyed by designated
initialisers whose subscripts are the case labels**; the function becomes a range guard
returning the old `default`, a second guard for a hole in the table returning the same, and
the lookup. Keep the two guards separate: one `||` chain trades Complex Method for Complex
Conditional.

**Preconditions:** every arm is one return of a compile-time constant; the controlling
expression has no effects; there is a `default` returning a constant; the enum has a count.
The table's hole value must not be a legitimate value.

**Guard:** unchanged apart from the added bound and `0`. **Tier:** build and guard.

#### Recipe X - Split Dispatch

**Use when:** *Complex Method* on a state machine whose complexity is its own switch.

**How:** move a contiguous group of later arms into a `static` helper that switches on the
**same expression with the same labels**, reached from the original `default`. Anything
that ran after the switch stays after it in the caller. Chain through successive defaults
when the label count alone is over the threshold.

**Variant:** two sibling switches that share several identical arms may both reach one
helper holding those arms from a new `default`, provided neither had a `default` before.

**Preconditions:** every fall-through stays inside the function that holds both its ends;
both halves come in under the threshold, or the split pays nothing. Fold repeated arm
shapes (Recipe V) *before* chaining, because chaining spreads repetition.

**Guard:** extract signature. **Tier:** build and guard; trace replay when a `goto` or a
fall-through is involved.

### 4.2 Sharing between functions

#### Recipe D - Deduplicate

**Use when:** *Code Duplication* on blocks that are **identical, or differ by a single
value**.

**How:** one `static` helper; the differing value is its parameter. Two or more differences:
leave them, or see whether V, C, T, B, N, W or F applies. Two identical helpers merge under
this recipe too.

**Guard:** deduplication WARN. **Tier:** build and guard.

#### Recipe C - Extract Common Part

**Use when:** duplicated blocks share a **contiguous identical run**, a prefix, suffix or
middle, and differ elsewhere.

**How:** move exactly the identical run into a `static` helper, untidied; leave every
difference at its call site. If the run ends inside control flow, the helper returns `0` or
`1` and each caller branches on it, and nothing else.

```c
static s32 approach_complete(Work *w) {      if (approach_complete(w)) { set_anim(w, 29); }
    if (!paused()) {                         ...
        move(w);                             if (approach_complete(w)) { parent->cmd = 9; }
        if (--w->timer <= 0) { w->state++; return 1; }
    }
    return 0;
}
```

**Guard:** deduplication WARN with `0`/`1` added. **Tier:** build and guard.

#### Recipe V - Verbatim Values

**Use when:** a skeleton repeats **three or more times** and the instances differ in two or
more **literals** sitting in the middle of it, so D refuses and C finds no run.

**How:** one helper performing exactly the operations that were there, in order; every
varying literal written out at its own call site in positional order.

**Preconditions:** the skeleton is byte-identical apart from the literals, checked by diff
not by eye; only literals vary, where a named constant and a struct field passed by
address both count as literals; the helper tests a parameter only where the block tested
that literal; a condition hoisted into an argument is pure. **Two instances are enough
only when a tool re-expands the fold and diffs it against the original**; a hand fold of
two near-misses is Recipe D's forbidden case.

**Guard:** one copy of each literal removed per instance, every value present. **Tier:**
build and guard; the fold checker where one exists.

#### Recipe T - Shared Table Scan

**Use when:** the same threshold-table scan repeats with a different table, bound and
scanned value.

**How:** name the table's row type in a header (so the parameter adds no literal to the
`.c`), extract the loop once unchanged, and pass table, bound and value verbatim from each
call site. Also covers a table *selection* where several arms choose between two tables the
same way. Group the scans by what they score; several small helpers become duplicates of
one another.

**Guard:** deduplication WARN with the bounds still present at their call sites. **Tier:**
build and guard.

#### Recipe B - Shared Buffer Loop

**Use when:** identical loops walk a caller-named buffer to a caller-named length.

**Preconditions beyond T:** the body cannot move its own bound, because the original re-read
the length each pass and the helper takes it by value once, so the body writes only its own
locals or through pointers that provably cannot alias the length; parameter types are the
*field* types, not the loop variable's; the buffer parameter is `const` where only read.
Two instances are enough.

#### Recipe N - Shared Index Range

**Use when:** identical scans over the same buffer differ only in their first index and
limit.

**Preconditions:** the comparison is copied, not chosen; the bound cannot move (as B);
parameter types are the loop variable's. **One value may ride along** as an argument the
helper only uses where the original used that expression, provided the expression is free
of side effects and keeps its type. This is the one place a helper may *index* with a
parameter, because nothing is chosen: the call site wrote the value.

#### Recipe W - Shared Call Site

**Use when:** several places make the same call with the same long argument list,
differing in a few argument *expressions*.

**How:** one helper passes each shared argument to the position it occupied; the varying
expressions are its parameters, written out at each call site. Where shared arguments
outnumber four, bundle them in a parameter object built at the call site (Recipe A).

**Preconditions:** same callee and arity everywhere; every shared argument identical
character for character; **every argument free of side effects**, because the helper
changes the evaluation order; check the argument lists mechanically, grouping by position.

#### Recipe F - Action Parameter

**Use when:** two or more functions or arms share a control skeleton identical except for
the **name of one or more functions being called**.

**How:** the callee becomes a function-pointer parameter passed **as a bare name at the
call site**; the helper only calls it. The call may differ whole, callee and arguments, as
long as the arguments travel verbatim. Where fixed arguments plus pointers exceed four, the
varying parts may travel in a compound literal built at the call site, holding bare names,
never assigned to a variable or put in a table that outlives the call.

**Preconditions:** only callees differ, never a statement, operator or value; the callees'
signatures are identical, and casting a pointer to make them fit is forbidden and undefined;
nothing becomes non-`static` to be pointed at; the helper never tests or chooses between
pointers.

**Guard:** declare each callee passed by name. **Tier:** control flow, so trace replay.

### 4.3 Tables and dispatch

#### Recipe J - Dispatch Table

**Use when:** a family of functions is each one switch whose every arm is a single call,
and the file reports *Overall Code Complexity* or *Code Duplication*.

**How:** one argument struct and one adapter per callee, generated from the callees'
signatures; one interpreter that indexes a table by the switch's expression and falls to
the default arm past the end or on a hole; each function becomes a table **keyed by
designated initialisers whose subscripts are the case labels** and one interpreter call.

**Preconditions:** every arm is one call then `break`; no argument has an effect, because
the table builds every step's arguments on entry; labels unique and ascending over a plain
integer; a single-statement `default`; the callees declared in one header so the
infrastructure can be generated. **Apply by tool, not by hand**, and prove it by running
the tool backwards: regenerate the switch form from the tables and diff it against the
source. The guard learns to invert a converted file before counting.

**Line budget:** a converted function measures signature lines + steps + 2; the duplication
check groups functions of ten lines or more, so a six-step table with a one-line signature
clears and one with a wrapped signature does not.

#### Recipe J2 - Uniform Step Table

**Use when:** Recipe J's shape on callees that are file-local statics with heterogeneous
signatures, where the generator does not reach.

**How:** every step becomes a `static` adapter with **one uniform signature**, the
dispatcher's own parameters, whose body is the original arm's call verbatim; one interpreter
per argument type reads the state, takes the step at that index if the table has one, else
the `end` step; write the bounds test and the null test as two statements. Convert every
dispatcher in the file in one commit so it reads in one idiom.

**Proof:** the guard fails by construction, so stub every leaf callee to record its name and
arguments, drive every state value the index type can hold through old and new, and diff
the recordings. **Tier:** equivalence harness, plus a manual check where the code is outside
any replay.

#### Recipe K - Check List

**Use when:** *Code Duplication* across functions that are each a run of `if (check(x))
return;` guards over the same argument.

**How:** one pointer type, one scan that runs a null-terminated table of checks and returns
on the first that fires, and one table per function. A check whose type differs from the
table's gets a three-line adapter returning the value its own `if` tested, because
**calling through a pointer of the wrong type is undefined behaviour**, not a warning.

**Guard:** unchanged. **Tier:** control flow, so trace replay.

#### Recipe M - Decision Table

**Use when:** *Code Duplication* on dispatcher chains of one shape on different masks,
labels or callees, whose behaviour depends only on a **small finite classification** of
their inputs.

**How:** enumerate the classes each chain distinguishes, plus one for anything else; write
each chain's outcome per cell into a `static const` table of an outcome `enum`, keyed by
class names; one classifier, one interpreter, and a `static const` descriptor per chain
carrying the differences, selected at compile time at each call site.

**Preconditions:** the input domain is small enough to enumerate completely; the outcomes
are the same actions the original performed in the same order per call; the descriptor is
never indexed at run time by anything computed.

**Proof:** compile old and new behind a fake of the state they touch and compare the
effects over the **whole** domain. **Tier:** equivalence harness; trace replay where the
code is inside one.

### 4.4 Interfaces and files

#### Recipe A - Parameter Object

**Use when:** *Excess Number of Function Arguments*, more than four in C.

**How:** a `struct` whose fields are the parameters in the same order with the same types;
the function takes `const Struct*`; every call site passes its original argument list
through a compound literal, rewritten mechanically with a per-call argument-count check;
the struct is declared in the header the callers already include.

**Preconditions:** functions share a struct only if their parameter lists match in order
and type; a function referenced through a pointer table cannot take a new signature; the
guard reports OK, not WARN. The finding is scored once per file however many functions
carry it, so count the flagged functions and commit to finishing them: the intermediate
commits measure flat.

**Tier:** build and guard; a signature change on a public function needs the owner's
authorisation.

#### Recipe O - Return an Object

**Use when:** *Bumpy Road Ahead* or *Complex Method* where the bumps are the arms of one
conditional and Recipe E refuses because each arm writes **two or more outer locals** that
only one sink after the branch reads.

**How:** a small `struct` holding exactly those locals in the sink's order; each arm moves
verbatim into a `static` helper that fills and **returns the struct by value**; the parent
becomes `c = arm_a(...)` or `c = arm_b(...)` and the unchanged sink reads `c.field`. This is
Recipe A for outputs. Returning by value has no aliasing and nothing the caller can observe
half-done, which is what the out-parameter refusal in Recipe E guards against.

**Preconditions:** the locals are read only after the branch; no arm reads a local another
arm wrote. **Guard:** OK or the plain extract WARN. **Tier:** build and guard, plus a
harness recording the sink's arguments over the input domain where the function is outside
any replay.

#### Recipe Q - Parsed Message

**Use when:** *String Heavy Function Arguments* on a module that speaks a line protocol,
where a dispatcher matches a command word by prefix and each handler matches the same word
again inside its own parse.

**How:** an `enum` of command words and a message `struct` of command and payload pointer;
one table of words with the space that ends each and its length, copied from the
`strncmp` calls; one function that splits a line into a message; handlers take
`const Message*` and parse the payload with the old format minus the word; dispatch through
a table indexed by the enum, not a switch. **Watch `sscanf`'s whitespace rules:** a format
space skips any run of whitespace, a literal does not, so a format that began with a
literal after the word keeps a leading space.

**Proof:** this edits string literals, so the guard fails by construction; run both parsers
behind the same fakes over a corpus of every command word and near-miss, spacing variants,
missing and oversized fields and tens of thousands of random lines, from several starting
states, recording every log and side effect. **Tier:** equivalence harness; owner's
authorisation where literals are otherwise forbidden.

#### Recipe S - Split File

**Use when:** *Lines of Code in a Single File*, and, as measured, file-level ratio findings
gated on file size. Apply it last, never first.

**How:** group functions that share a `static` variable or a theme; move the group to a new
`.c` beside the original; add a header only for functions used from outside; rebuild and
confirm the link. Check the guard on the **combined group**, because each file alone reads
as loss.

**Preconditions:** no original `static` is widened. **A helper the campaign itself created
may cross the cut**, because it is a verbatim copy of lines already inline at every call
site, so widening it exposes nothing the program did not already execute; declare it in the
header the two halves share, never a third "common" file. Where a seam needs one accessor
into the other half's state, that is a new function and a judgement call to record.

---

## 5. Which recipe for which finding

Work the list from the **bottom**: a function barely over a threshold clears its finding
with one small extraction, while a large one brought from very high to merely high pays
almost nothing. Then, in order of preference:

| Finding | First try | Then | If the shape is a family |
| --- | --- | --- | --- |
| Deep, Nested Complexity | G | E | - |
| Bumpy Road Ahead | E (one arm only if the sibling is a twin) | O when arms write two locals | - |
| Complex Method | P on the whole condition, E from the bottom | X when it is a switch, L when arms return constants, R when it is gotos | J when every arm is one call |
| Complex Conditional | P on the **whole** condition | - | - |
| Large Method | E, X | - | V, W |
| Code Duplication | D, C on the identical run first | V, T, B, N, W, F by what varies | J, K, M; S when two families sit in one file |
| Excess Number of Function Arguments | A, all flagged functions in one series | - | - |
| Overall Code Complexity | split the branching of the **largest** function | E from the bottom | J |
| Lines of Code in a Single File | reduce function complexity first | S along a static-sharing seam | - |
| Primitive Obsession, String Heavy Arguments | a real domain type where one exists (Q) | S when the gate is file size | - |

**Refuse when:** two blocks differ in a statement, an operator or a subscript and no recipe
above names that difference; a helper would have to test, index with or choose between its
parameters; a case label would have to move; a `static` that predates the campaign would
have to widen; or you cannot say what the function falls through to.

---

## 6. The plateau note

```
### <file> - <score>, <date>

<the finding or findings left, with the functions they name>

| What was tried | Recipe | Measured |
| --- | --- | --- |
| <one line per probe, on a scratch copy> | <letter> | <score, or "refused: <precondition>"> |

<why the best legal probe does not reach 10.00, in one paragraph, naming the mechanism>
<what would reach it, if anything, and what authorisation or new recipe that needs>
```

Re-measure the file before trusting a note, then diff the functions it names yourself. A
measurement is valid only for the file as it stood: a twin that cost 0.3 with five findings
open may pay 0.9 as the file's last finding.
