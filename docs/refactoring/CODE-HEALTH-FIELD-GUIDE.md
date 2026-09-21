# CodeScene Code Health - a field guide

What three weeks of refactoring against Code Health taught about the metric itself. Every
statement here was established by measuring, most of them by bisecting a synthetic file or
probing a real one two ways, against **cs-mcp 1.4.7** and CodeScene's shipped rules in
September 2026. The mechanics are facts about the tool, not about any codebase, so they
travel; the thresholds should still be re-confirmed on a new repository's first plateau
rather than trusted blindly, and a few of them were pinned from three probes on one file.

The companion [`PLAYBOOK-CORE.md`](PLAYBOOK-CORE.md) holds the recipes. This file explains
why they score the way they do.

---

## 1. How the score is built

**Findings, not degrees.** A file's score is driven by which findings are open, weighted by
how many functions carry each and how bad they are, not by a continuous sum of complexity.
The consequences shape the whole method:

- A function taken from complexity 25 to 20 keeps its *Complex Method* finding and pays
  almost nothing. One taken from 10 to 6 loses the finding and pays properly. **Work the
  threshold list from the bottom.**
- Some findings are scored **once per file** however many functions carry them. *Excess
  Number of Function Arguments* is one: converting fourteen of fifteen flagged functions
  measures exactly flat and the fifteenth moves the score half a point. Count the flagged
  functions before starting and commit to finishing them, and say in each commit how many
  are left so a flat score reads as progress.
- **A flat score is not a failed refactor.** A finding that shrank but did not close leaves
  the score where it was. Read the review after a flat commit: keep the change if the
  targeted function left a smell category or its complexity fell, because the next commit
  will land on the finding's edge.
- **A measurement is valid only for the file as it stood.** The same extraction, unchanged,
  measured -0.16 with five findings open and +0.87 as the file's last finding. Keep a note
  of what you rejected for duplication cost and come back to it when the file is nearly
  done.

**Thresholds observed.** Complex Method opens at cyclomatic complexity 9 and above for C.
Deep Nested Complexity opens at depth 4. Complex Conditional counts terms in one condition;
three is enough. Large Method is around a hundred lines. *Overall Code Complexity* is the
mean cyclomatic complexity over the file's functions, judged against a **strict 4**, and
it is **not reported on a file with fewer than seven functions**; see below.

**Case labels are complexity.** A switch with eleven labels has a floor of complexity 12
that no extraction, predicate or deduplication reaches. Only splitting the switch (Recipe
X, possibly chained) or turning it into data (Recipes L and J) moves it.

**Gotos count double.** Each `goto` is a branch, so a chain of `if (...) goto` scores
roughly twice its apparent complexity.

---

## 2. Code Duplication

The finding that dominated the second half of the campaign, and the one whose mechanics
matter most.

**It compares shape, not values.** The similarity is computed on the structure of two
functions, with `function_duplication_min_similarity_percentage` at 75. Two bodies that
differ only in their literals are 100 percent alike. Two consequences:

- A **per-case setter family** costs more than the switch it replaces. Five helpers of
  twelve assignments each, differing only in constants, are a five-function duplication
  group. Extract what differs in structure and leave what differs only in values inside the
  switch that chooses between them: a switch arm is the cheapest place a constant can live.
- Two helpers that differ only in an element type are one shape twice. Extract them if they
  clear a Complex Method, but expect the pair and do not merge them behind a width flag.

**The ten-line floor.** Functions of **ten lines or more** are grouped by shape; nine lines
is clear. Bisected on a synthetic file of thirty same-shaped functions: five table lines
scored 10.00, six scored 8.03. Physical lines count, including a wrapped signature, and a
blank line inside the body does not change the verdict. This floor is why a Recipe J table
with a one-line signature clears and the same table under a wrapped signature does not, and
why three-line adapters never become a finding.

**clang-format decides some of it.** A braced initialiser is laid out one item per line when
any column's items differ by more than ten characters, so a short step under long ones
pushes a table past the floor. Formatting is not a recipe, but it is a mechanism worth
knowing when a file is flagged for its line count alone.

**Twins cost more than bumps.** Extracting the same helper from two arms that are structural
twins, differing in a constant, an operator or an offset, clears the bumps and manufactures
a duplication pair, and the pair costs 0.2 to 0.6 every time. Rules that fell out:

- **Extract from one arm only**, and say in the commit that the other was left inline on
  purpose. Extract from both only if that brings the parent under its threshold, because
  then the finding it loses outweighs the pair it gains.
- **Cut shallower.** Lift the inner chunk, not the whole arm.
- **Weigh an arm against the family it would join.** The third or fourth member of a
  near-twin family costs more than a second, so look at what the file already holds.
- **Follow through with Recipe F when the twin is unavoidable:** extract every sibling's
  arm, then collapse the identical shells behind a pointer. The intermediate commit measures
  flat or negative; judge the pair and record both numbers.
- **Never apply the same split across an already-duplicated family.** Thinning each member
  the same way makes them more alike and multiplies the finding.

**Separate the shape from the substance.** A file's duplication is often two things:
identical runs that really are shared, which Recipes C and P clear, and dispatchers that
differ only in which functions they call, which need Recipe F or a table. Extract the runs,
measure, and only then judge the plateau.

**Order matters on a duplication-heavy file.** Clear the other findings first, then take the
shared runs: a run taken early clears no finding and measures flat, and rule 2 makes you
revert work you will redo. And **share the run before you split the shape**: splitting two
twins first spreads the run over more functions and the file ends below where it started.

**A duplicated call site is worth extracting even when the score does not move**, because
it is what the later fold will land on.

**Fold before you chain.** Recipe X moves lines between functions and cannot make a
repeated arm shorter; Recipe V removes the repetition outright. A switch judged "too long
to chain" was measured on arms that had not been folded yet.

---

## 3. The file mean

*Overall Code Complexity* is the mean cyclomatic complexity over the file's functions
against a strict threshold of 4, **reported only on files with seven or more functions**.
Established by pinning a real file's total complexity and adding functions one at a time,
and confirmed on a synthetic file.

What follows from the seven-function gate:

- On a small file, the **first extraction can open a finding that was only hidden**: six
  functions at a mean of 7.8 show nothing, seven at 6.9 show the finding. The answer is to
  keep going, not to revert; one file needed eight commits, seven of them flat or down,
  before the ninth function and the folds brought the mean under 4.
- The mean responds to **moving branches, not to removing lines**. Lifting a block into a
  helper takes its branches off the parent and gives the helper one plus those branches, so
  the total rises by one and the count by one. When the mean is the only finding left,
  **split the branching of the largest function** rather than hunting more duplicate runs.
- Count how many extractions the mean needs **before** doing any, and spend them on the
  functions least like their siblings, or the extractions form a duplicate family and cost
  more than the mean pays.
- A file can be **too big for its own mean**: past a size, every extraction that helps the
  mean lands on a duplicate family. Recipe S first, then the duplication it exposes.
- **Function work stops paying while a file is over its size threshold.** Split first.

---

## 4. File-level ratio findings

Three findings are statements about a whole file's parameters rather than about any
function, and no per-function recipe reaches them.

**Primitive Obsession.** Opens when more than about **60 percent** of a file's parameters
are built-in types, counting zero-argument functions in the denominator, and only above a
size gate. The gate is a **parameter count near 32**, not a function count: a 21-function
half with 20 of 31 built-in parameters scores 10.00, a 22-function half with 21 of 32 does
not, and adding a two-parameter function of struct types to the first keeps it clear. The
check is **lexical on the type token**: a parameter spelled with a typedef that is declared
nowhere at all also closes it, so the finding cannot tell a domain type from a misspelling
and a recipe built on renaming would be moving a number by choosing identifiers. Real
levers: a genuine domain type where one exists, or Recipe S along a seam that puts each
half under the gate.

**String Heavy Function Arguments.** Opens above about **40 percent** of parameters being
`char*`: pinned on one file at 7 strings of 18 clear and 8 open. A line-protocol module
whose handlers each take the line they parse sits at 70 percent by nature. The real lever is
Recipe Q, tokenising once and handing the handlers a message, which is the design the
finding is asking for.

**Excess Number of Function Arguments.** More than four in C, scored once per file (see
section 1). Recipe A, all flagged functions in one series.

---

## 5. Two conditionals want opposite treatments

*Complex Conditional* is cleared by **naming the whole condition** as one predicate; naming
its parts leaves the finding open on the shorter expression that remains. *Complex Method*
is cleared by **taking branches out**, and a named predicate does not remove a branch. A
two-guard lookup (Recipe L) scores 10.00 where the same tests folded into one `||` chain
scores 9.68, because the one-condition form trades the first finding for the second. Write
bounds and null tests as two statements.

---

## 6. Recipe X pays only if both halves clear

Splitting a switch that leaves either half over the threshold clears nothing and adds a
function. Divide the arm count before cutting; when one cut is not enough, chain through
successive defaults so that each level comes in under. Every fall-through must stay inside
the function that holds both its ends, and a chain is refused if a caller already has a
`default` that the shared arms would now bypass.

---

## 7. Probing

Do not estimate a score; measure it. The procedure that carried the last two weeks:

1. **Probe on a scratch copy.** Write the candidate into a copy outside the source tree
   (the scorer may require it inside the repository's folder), run the review, and read the
   findings, not just the number.
2. **Score-only probes are legitimate for shape questions.** A table form written without
   its infrastructure still tells you whether the duplication would clear. Compile it before
   trusting anything else about it.
3. **Compile with the production flags** when the probe is code: pull the exact command from
   the build system and add a syntax-only flag, so an unused static under warnings-as-errors
   is caught before it costs a commit.
4. **Check every claimed win independently.** In the source campaign a second agent re-did
   every survey win; two were refused, one because its only 10.00 probe had changed a
   constant. Select on legality first and on score second.
5. **Re-measure a recorded plateau before inheriting it.** Three of four re-tested plateaus
   were wrong: one mistook static *functions* for shared state, one refused functions it had
   never diffed, one measured a chain on code that had not been folded yet. A note that
   names a mechanism is a claim to check; a note that names functions is a diff to re-run.

---

## 8. What the checkers cannot see

The literal-fingerprint guard compares multisets of literals and of called names. It is
deliberately dumb, and its blind spots define where a second proof is needed:

- **Reordering.** Two statements swapped have the same fingerprint. Nothing mechanical in a
  fingerprint catches it, which is why reordering side effects is forbidden absolutely.
- **Transposed arguments in a compound literal.** `{ 0x60, 0x10, 2 }` for `{ 0x60, 2, 0x10 }`
  has the same values. Rewrite call sites mechanically, assert argument counts per call, and
  where a fold reads through a struct, teach the equivalence checker to resolve fields back
  through the literal before trusting it.
- **A deleted copy versus a deduplicated one.** Both read as copies removed with every value
  present. A human confirms the WARN.
- **A recipe that changes shape.** Case labels becoming table subscripts, a string format
  losing its command word, a helper the campaign made disappearing into a table: all read
  as substitution or loss. For these the proof is an **equivalence harness**: compile the
  old and new region behind the same fakes, enumerate the input domain or a corpus, record
  every observable effect, diff. Quote the count.

An inline-expansion checker, which substitutes a helper's body back into each call site and
diffs against the original, catches the argument transposition the guard misses and makes
a two-instance fold safe. It sees text, so it needs the same field resolution for struct
parameters, and a DIFFERS is read rather than obeyed.

---

## 9. Harness coverage is a claim to check

A trace-replay harness proves that two builds compute the same state for the inputs it
tries. Say in the commit what it does **not** reach, and measure rather than assume: in the
source campaign the harness never played one of the twenty stages, and that was found only
by reading the stage out of each seed's saved state, after a clean run had been quoted as
evidence for a change on that stage. Random inputs never end a round, never land a named
move on purpose, and exclude any state kept outside the saved snapshot. Name the manual
check that covers the rest.

---

## 10. Version note

Thresholds and gates were measured against cs-mcp 1.4.7 in September 2026. Re-confirm the
duplication floor, the seven-function gate and the two ratio gates on the new repository's
first plateau, with a synthetic file where a real one is ambiguous, and record the version
beside the numbers.
