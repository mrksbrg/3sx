# Red Band Backlog

The nineteen files that scored below 4.0 in the 2026-09-01 sweep, ranked worst first at
that time. **None of them is still there.**

See [`README.md`](README.md) for the campaign rules and [`PLAYBOOK.md`](PLAYBOOK.md)
for the allowed transformations.

> [!IMPORTANT]
> **Scores here are refreshed from a full sweep; the task files are not.**
> If a task file's stated baseline does not match what you measure, the task file is
> stale - check this page before stopping and reporting a mismatch. The current numbers
> below come from `codehealth-current.json`, swept 2026-09-19 (seventh sweep of that day,
> after the PPGFile family, the `Game/opening` folder, `mtrans.c`'s split and
> `flps2vram.c`).
> `codehealth-baseline.json` preserves the original 2026-09-01 sweep and is not updated.

## Where the whole repository stands

| Band | Score | 2026-09-01 | 2026-09-19 | 2026-09-20 | 09-21 am | 09-21 pm | 09-21 late |
| --- | --- | --- | --- | --- | --- | --- | --- |
| **Red** - severe debt | 1.0 - 3.9 | 19 | **0** | **0** | **0** | **0** | **0** |
| **Yellow** - problematic debt | 4.0 - 8.9 | 207 | 93 | 28 | 2 | **0** | **0** |
| Green | 9.0 - 9.9 | 158 | 91 | 79 | 61 | 27 | **9** |
| Optimal | 10.0 | 98 | 475 | 553 | 598 | 634 | **652** |
| Total scored | | 482 | 659 | 660 | 661 | 661 | 661 |

The file count rises because the campaign splits files. Mean Code Health across every
scorable first-party file is **9.9929**, against 8.52 over the same files at the start.
**The yellow band is empty**: nothing scores below 9.0, and 652 of the 661 scored files are
at 10.00. Nine are left, and they are listed under *The last nine, priced one at a time*
below.

The 2026-09-21 pm column is the sweep taken after the green-band survey: sixty-one files
diagnosed and probed in parallel, thirty-three lifted, and the last two yellow-band files
- `com_patterns_5step.c` and `bg_zoom.c` - out of the band. The am column is the sweep taken
after Recipe J went through the CPU script
family: 44 files, 998 scripts, `Game/com` from a mean of 9.495 to 9.955 and 128 of its 134
files at 10.00. Two files are left in the yellow band -
`Game/com/patterns/com_patterns_5step.c` at 8.03 and `Game/stage/bg_zoom.c` at 8.81 - and
the first of them is priced under *Where `Game/com/patterns` stopped* below.

Two things to read carefully off that table. The 2026-09-20 column and the
`codehealth-current.json` committed on that date **disagree by one file**: the JSON says
yellow 29, green 80, optimal 551, the column says 28 / 79 / 553. Both sum to 660, so one
of them was taken from a measurement that was not the committed sweep; which is not
recoverable now. Against the JSON, twenty-seven files left the yellow band, twenty-six of
them on this branch - eleven in `com/patterns`, ten in `com/passive`, five in `com/active` -
and the twenty-seventh is `Game/opening/opening_bg0.c`, which reached 10.00 on
`origin/main` before this branch existed and which that JSON had simply not been refreshed
for.

The bands count **scored** files. 144 first-party `.c` files are unscorable in both
sweeps - `com_data.c`, `app_data.c`, the `ac00xx.c` dispatch tables and their kin, which
hold data and no functions - so the comparison is like for like, but "two files in the
yellow band" is a statement about the 661 that CodeScene scores, not about every file
under `src/`.

## The Red band is empty

As of 2026-09-19 **no first-party file scores below 4.0**. The last two out were
`Game/com/ck_pass.c` (3.75 -> 8.03, split six ways) and `Game/opening/opening.c`
(3.97 -> 9.68, split four ways).

Nothing scores below 5.0 either. The worst files were swept on 2026-09-19:

| File | Before | After |
| --- | --- | --- |
| `Game/com/com_pl.c` | 4.77 | **8.88**, split three ways; group mean 8.47 |
| `Game/game.c` | 4.79 | **9.04**, split four ways; group mean 8.35 |
| `AcrSDK/ps2/flps2etc.c` | 5.17 | **6.94** |
| `AcrSDK/ps2/flps2vram.c` | 4.82 | **5.25** |

`AcrSDK/ps2/flps2vram.c` was the lowest at 5.25 and is now **7.36**: the format switch
three lock modes shared was written once, the lock and unlock conversions moved out of
their loops and chained, and the pixel loop gave up its alpha fix-up and its two width
switches. What is left there is the texture/palette twin pairs - `flPS2GetTextureHandle`
against `flPS2GetPaletteHandle` and two more like them - which differ in their type and
so are Recipe D's forbidden case.

That paragraph named `platform/netplay/game_state.c` (6.30),
`platform/video/sdl_gpu/sdl_gpu_renderer.c` (6.82), `AcrSDK/ps2/flps2etc.c` (6.94) and
`AcrSDK/ps2/ps2PAD.c` (7.01) as the lowest in the repository. They now measure 10.00,
10.00, 9.84 and 9.92. The two lowest are `Game/com/patterns/com_patterns_5step.c` (8.03)
and `Game/stage/bg_zoom.c` (8.81), and nothing else is below 9.0.

## Track A - available now

Outside the in-round simulation. Safe to refactor with compile verification only.

In both tables the **Score** column is the 2026-09-19 sweep and a struck-through task is
at 10.00. **LOC, Churn and the last column are as of 2026-09-01** and are not refreshed -
where a file has been split, its LOC is now spread over several files, and the named worst
function is usually long gone.

| Task | File | Score | LOC | Churn | Risk | Worst function |
| --- | --- | --- | --- | --- | --- | --- |
| ~~[R04](tasks/R04-menu.md)~~ | `Game/menu/menu.c` | **10.00** | 5374 | 58 | LOW | `Extra_Option` (cc 28) |
| ~~[R06](tasks/R06-mtrans.md)~~ | `Game/rendering/mtrans.c` | **8.03** | 2224 | 10 | MEDIUM | split again 2026-09-19 into `mtrans_buffers.c` (8.28); the file's size finding is cleared |
| ~~[R10](tasks/R10-opening.md)~~ | `Game/opening/opening.c` | **10.00** | 2997 | 17 | LOW | none - `TITLE_Move`'s sequence moved out 2026-09-19 |
| ~~[R11](tasks/R11-PPGFile.md)~~ | `Common/PPGFile.c` | **9.31** | 1511 | 11 | MEDIUM | the palette/texture twin pair; every other file in the family is at 10.00 |
| ~~[R14](tasks/R14-bg.md)~~ | `Game/stage/bg.c` | **9.09** | 1430 | 11 | MEDIUM | plateau 2026-09-18 - split into `bg_textures.c` (10.00); the whole stage folder went with it, see the task report |
| ~~[R17](tasks/R17-entry.md)~~ | `Game/screen/entry.c` | **10.00** | 1480 | 19 | LOW | done 2026-09-18 - left the Red band; split into `entry_break_in.c` |

## Track B - manual playtesting required (statcheck indefinitely unavailable)

Core engine, CPU logic, animation and effects. A silent behaviour change here breaks
gameplay or rollback determinism and the build will not catch it. Statcheck would
normally catch it, but its replay runner needs a real CPS3 ROM dump, and a legitimate
one requires owning genuine CPS3 arcade hardware - this project's no-piracy policy won't
work around that, so treat statcheck as indefinitely unavailable rather than pending.
**2026-09-04 (project owner directive):** these files may be refactored now; verify with
manual playtesting instead of waiting on statcheck.

| Task | File | Score | LOC | Churn | Risk | Worst function |
| --- | --- | --- | --- | --- | --- | --- |
| ~~[R01](tasks/R01-hitcheck.md)~~ | `Game/engine/hitcheck.c` | **10.00** | 2308 | 17 | CRITICAL | `attack_hit_check` (cc 67) |
| ~~[R02](tasks/R02-com_sub.md)~~ | `Game/com/com_sub.c` | **10.00** | 5799 | 20 | CRITICAL | `Reaction_Sub` (cc 46) |
| [R03](tasks/R03-pls03.md) | `Game/engine/pls03.c` | **8.92** | 1794 | 10 | CRITICAL | `check_special_attack` (cc 99) |
| [R05](tasks/R05-cmd_main.md) | `Game/engine/cmd_main.c` | **9.39** | 1876 | 12 | CRITICAL | `check_10` (cc 48) |
| [R07](tasks/R07-eff09.md) | `Game/effect/eff09.c` | **8.54** | 1897 | 12 | HIGH | `eff09_24000` (cc 22) |
| ~~[R08](tasks/R08-eff13.md)~~ | `Game/effect/eff13.c` | **10.00** | 2155 | 7 | HIGH | `kotp_07000` (cc 26) |
| ~~[R09](tasks/R09-pls00.md)~~ | `Game/engine/pls00.c` | **10.00** | 2128 | 3 | CRITICAL | `jumping_cg_type_check` (cc 92) |
| [R12](tasks/R12-appear.md) | `Game/animation/appear.c` | **9.38** | 2040 | 13 | HIGH | `Appear_29000` (cc 23) |
| ~~[R13](tasks/R13-win_pl.md)~~ | `Game/animation/win_pl.c` | **10.00** | 1629 | 18 | HIGH | `Win_10000` (cc 19) |
| ~~[R15](tasks/R15-plpdm.md)~~ | `Game/engine/plpdm.c` | **10.00** | 1699 | 17 | CRITICAL | `subtract_dm_vital` (cc 30) |
| ~~[R16](tasks/R16-ck_pass.md)~~ | `Game/com/ck_pass.c` | **8.03** | 3126 | 5 | CRITICAL | `KEN_vs` (cc 41) |
| [R18](tasks/R18-charset.md) | `Game/engine/charset.c` | **9.68** | 2880 | 14 | CRITICAL | `check_cgd_patdat` (cc 43) |
| [R19](tasks/R19-manage.md) | `Game/engine/manage.c` | **9.92** | 2518 | 30 | CRITICAL | `Game_Manage_12_4` (cc 32) |

## Aggregate

At the 2026-09-01 start: **19 files**, 46,865 lines of code, **330** complex methods,
**267** bumpy roads and **95** deeply-nested functions. Highest churn was `menu/menu.c`
(58 commits), which started at 1.97; the worst single function was `scr_trans` in
`stage/bg.c` (cyclomatic 109, nesting 9).

At 2026-09-19: **none** of the nineteen is still below 4.0, eight are at 10.00, and
`scr_trans`'s file is at 9.09. Mean Code Health across the repository is 9.64.

## The yellow band, file by file - re-audited 2026-09-20 evening

The audit earlier the same day found forty-six files below 9.0 and called most of them
refusals. **Nine of those rows were wrong**, and working through them took the band from
forty-six files to twenty-six and the repository mean from 9.80 to 9.87. They are listed
here with what actually unblocked them, because the pattern in the mistakes is more useful
than the individual entries.

| File | Then | Now | What the earlier row missed |
| --- | --- | --- | --- |
| `mtrans.c` | 8.03 | **10.00** | "No further legal cut exists", on a call-graph pass showing every seam running through a `static`. The seam was real; the Recipe S exception of 2026-09-18 covers it, because every static on that seam is one this campaign created. Split to `mtrans_tiles.c`, which then folded to 10.00 as well |
| `Lz77Dec.c` | 8.81 | **10.00** | "Every block advances `src`, `dst` and `size` at once." Two of the three do cross as pointers to the caller's pointers; the third does not cross at all, because every arm ended in the same `size -= loop` and the helper can return `loop` instead |
| `memmgr.c` | 8.88 | **10.00** | The twins are real and cutting both does cost more than it gives - 9.84 against 9.31, measured again. What the row missed is that cutting *one* pays, twice over, and that the block-list scan itself folds on a comparison predicate |
| `pls03.c` | 8.92 | **10.00** | Recipe X, four ways on the wst dispatch and twice on the table selector. Nothing blocked it; it had not been tried |
| `keymap.c` | 8.92 | **10.00** | "Every legal split reproduces its own shape as a duplicate - measured at 8.92 -> 8.54." True of every *split*. The switch is a name table, and writing it as one is Recipe L, added to the playbook this session |
| `caldir.c` | 8.81 | 9.68 | The x/y twins do differ in five field names each, and C has no pointer-to-member - but the fields can travel as pointers into the caller's own struct. The argument finding on the two six-parameter entry points stands, at 62 call sites across 30 files |
| `flps2vram.c` | 8.54 | **10.00** | The 16/32 pointer-type twin is one group of three. The other three groups - handle allocation, unlock, direct-colour conversion - differ only in values and calls |
| `end_05.c` | 8.81 | **10.00** | The `Request_Fade(1) != 0` against `Request_Fade(3)` difference is real and does disqualify Recipe V. It does not disqualify Recipe F: each scene keeps its own expression in its own one-line function |
| `end_14.c` | 8.28 | 9.38 | Two pairs that differ in a statement rather than a value, which is Recipe F's case and not Recipe D's |

Also cleared from the band this session: `bg_sub.c` 9.09 -> 10.00 (the mirrored scroll pair
turned out to differ only in subscripts, which are literals - correcting a refusal recorded
on the strength of a buggy ad-hoc extractor), `ck_pass_units_b.c` 9.38 -> 10.00,
`opening_bg1.c` 8.28 -> 9.38, `mtrans_buffers.c` and `ck_pass.c` 8.28 -> 8.54,
`eff09.c` 8.54 -> 8.81, `active17.c` and `pass08_4.c` 8.81 -> 9.09.

**The lesson in the mistakes.** Every wrong row was wrong in one of two ways. Either it
recorded a plateau from before a rule changed - `mtrans.c` and the Recipe S exception -
or it generalised from one failed shape to the whole file: "the twins cannot fold" when
three other groups in the same file could, "every split reproduces its shape" when the
answer was not a split. A refusal is only as wide as the thing that was actually tried,
and it expires when the catalogue grows.

### What was left, and why it was not structural after all

This section used to say that twenty-six files were stuck below 9.0, twenty-five of them
the CPU script family, and that the reason was structural. The reasoning was:

> and the members differ in exactly two places: the `case` label, and the engine call. The
> label is a literal and cannot be parameterised. The calls do not share a signature, so no
> one function pointer reaches them.

Both halves of that are true and the conclusion did not follow. Recipe J takes the whole
family out of the finding, and it is worth writing down exactly which step of the argument
was the wrong one, because the same step is available to make the same mistake again.

**"The calls do not share a signature, so no one function pointer reaches them."** They do
not share a signature *as written*. One adapter per call - `void Step_X(PLW*, const void*)`
unpacking an argument struct whose fields are the call's own parameters - gives them one,
without changing a type or a value, and the adapters are generated from `com_sub.h` rather
than typed. Fifty-seven of them cover every engine call the 998 scripts make. The refusal
had quietly assumed that the function pointer had to be the engine call itself.

**"The label is a literal and cannot be parameterised."** Correct, and irrelevant: it does
not have to be parameterised, it has to be *kept*. A designated initialiser keyed by the
case label keeps it exactly, which is what Recipe L already required for the same reason.

**The ten-line floor was the real finding, and it was right.** CodeScene groups functions
of ten physical lines or more by shape. That number is now bisected rather than inferred -
a synthetic file of thirty same-shaped functions scores 10.00 at five table lines and 8.03
at six - and it is the budget every skeleton is written against. What changed is that a
table is shorter than the switch it replaces: a step is one line, not four, so a six-step
script comes in at eight lines where its switch was twenty-six.

The old note ended by refusing `AllowShortCaseLabelsOnASingleLine` as gaming the
measurement. That refusal stands and is unaffected. Recipe J does not shorten the file by
formatting it differently; it replaces control flow with data, and the file gets shorter
because there is less of it.

**What it measured.** `Game/com` went from a mean of **9.495 to 9.955**, 128 of its 134
files at 10.00. The three files the old note named as the worst of the family -
`active08.c` 19 in a clique, `pass14.c` 18, `pass09_2.c` 15 - are all at 10.00. So are
`com_patterns_1step.c`, `2step.c`, `3step.c` and `4step.c`, whose cliques of 39, 54 and 38
this section used as its evidence.

### Where `Game/com/patterns` stopped, and why

Three files did not reach 10.00: `com_patterns_5step.c` at 8.03 and
`com_patterns_5step_2.c` and `com_patterns_6step.c` at 9.09. One cause, measured two ways.

A converted skeleton measures `signature + steps + 2` physical lines, and the signature is
one line unless it passes the 120-column limit, in which case clang-format gives it three.
Seventeen of the thirty-one skeletons in `com_patterns_5step.c` are at ten lines or more;
eleven of those are over only because their signature wrapped. Joining the wrapped
signatures back onto one line - a probe, not a commit, since it breaks the column limit -
takes `com_patterns_5step.c` to 10.00 and `com_patterns_5step_2.c` to 10.00 with nothing
else changed. That is the whole of it.

The signatures are long because the generated names restate the call sequence
(`pattern_jump_attack_term_normal_attack_command_attack_6` is 54 characters) and the engine's
argument types are long (`const Command_Attack_Args* p` is 28). They overflow by 3 to 36
characters. Closing that gap means shortening 448 generated names across 3500 call sites,
or wrapping skeleton parameters in new structs - and Recipe A does not help here, because
`const Search_Back_Term_Step* s` is two characters *longer* than the `s16 move_value, s16
next_menu` it would replace - or raising `ColumnLimit`. All three change the source to fit
the measurement rather than to be better, which is the same objection that kept
`AllowShortCaseLabelsOnASingleLine` out. Not done, and recorded here with the number so it
does not have to be re-derived.

The remaining few in `com_patterns_6step.c` have a second cause worth naming: one step wide
enough to push the table past the column limit makes clang-format break the whole
initialiser one-per-line, which costs two lines. The wide steps are the eight- and
ten-value argument objects - `Jump_Term_Args`, `JCA_Term_Args`. Hoisting the repeated ones
to named file-scope constants would shorten them, and 42 of the folder's 125 constant
argument objects do repeat, but it does not clear any file on its own, because the wrapped
signatures are still there.

### The 54 files left in switch form

Fifty-four files in `Game/com/passive`, `active`, `shell` and `follow` still hold
skeleton-shaped switches and were not converted. Every one of them already scores 10.00,
so rule 2 says leave them: there is no smell for the conversion to clear and no score for
it to move. The cost is that the family now reads in two idioms. If that is judged worth
fixing, `tools/pattern_table.py --convert` handles them unchanged - they were checked
against the recipe's conditions along with the rest, and all 552 skeleton-shaped switches
in `Game/com` meet them.

### The one that was never a script

The twenty-sixth file was `opening_bg0.c` at 8.12, recorded here as a genuine measured
refusal: lifting `op_bg0_0003`'s inner block clears one Complex Method and creates a
duplicate pair with the existing `op_bg0_lay_blocks` chain, 8.12 -> 8.03. Reverted.

**Overturned 2026-09-20: the file is at 10.00.** The measurement above was right about
that move in isolation and wrong about the file. See *Price the file's cheapest finding
before inheriting a plateau* in the playbook, and the nine commits on this branch.

## The platform, SDK and shim sweep - 2026-09-20

A pass over everything that is not a numbered task and not a character script: the
platform layer, the AcrSDK, the port shims, the test harness and the scene flow. Twenty
files reached **10.00** and none of the campaign's rules were relaxed except Recipe V's
instance count, which was settled rather than relaxed - see the playbook.

| File | Before | After | What did it |
| --- | --- | --- | --- |
| `platform/video/opengl/opengl_renderer.c` | 8.87 | **10.00** | the vertex fill, the shader bind, the canvas and the buffer setup lifted out; the four shader-failure teardowns are one run |
| `AcrSDK/common/mlPAD.c` | 8.87 | **10.00** | three loops out of `flPADACRConf`, then the mapped slot's depth out of the loop that was left |
| `port/sound/adx_decoder.c` | 8.89 | **10.00** | the header split four ways; the block scales and the sample nibble out of the decode loop |
| `Game/game_demo.c` | 8.89 | **10.00** | the attract sequence's stages split twice |
| `Game/game.c` | 9.04 | **10.00** | character select's entry and exit, then the mode settings and the round reset |
| `platform/netplay/netplay.c` | 9.00 | **10.00** | the local inputs, one session event, one advance event, the transition and the teardown |
| `Source/Common/PPGWork.c` | 9.00 | **10.00** | twenty-three copies of "release it if it is loaded" became two helpers |
| `Game/io/gd3rd.c` | 9.02 | **10.00** | the queue pop and the two halves of the step; `load_it_use_any_key2` took a parameter object |
| `test/replay_game.c` | 9.02 | **10.00** | the match setup the start frame carries, and the frame test named |
| `Game/com/com_pl.c` | 8.88 | **10.00** | the shell guard's last frame, the throw wait, and the two sides of two mirrored checks |
| `Game/com/com_pl_damage.c` | 8.13 | **10.00** | all eight damage states cut down; the run two of them share taken twice |
| `Game/com/com_pl_flip.c` | 8.41 | **10.00** | the guard-lever pair folded, then `Check_Shell_Flip` taken apart four ways |
| `Game/system/sys_sub_replay.c` | 9.31 | **10.00** | three blocks out of `Replay` |
| `Game/animation/win_pl_q.c` | 9.31 | **10.00** | the distance test both facings share, then the facing-right arm |
| `port/config/config_helpers.c` | 9.63 | **10.00** | one configuration line parsed in its own function |
| `Game/ui/sc_sub_training.c` | 9.68 | **10.00** | the three draw rows |
| `AcrSDK/common/plpic.c` | 9.68 | **10.00** | the PIC header's four checks |
| `platform/app/sdl/sdl_app.c` | 9.09 | **10.00** | two conditions named, then the event dispatch split |
| `port/sdl/netplay_screen.c` | 9.47 | **10.00** | the status text, the hold, and the switch split |
| `Game/io/ioconv.c` | 9.92 | **10.00** | the turbo repeat test |
| `Game/engine/plpat09.c` | 9.92 | **10.00** | the rock loop flattened with `continue` |
| `Game/effect/effd1.c`, `effe9.c` | 9.92 | **10.00** | one arm of a mirrored pair each - the *other* arm makes a twin and costs half a point |
| `test/test_runner_compare.c` | 9.92 | **10.00** | one player's frame comparison |
| `Game/ending/end_18.c` | 9.38 | **10.00** | the two scene steps, under Recipe V's new two-instance licence |
| `arcade/cps3_decrypt.c`, `AcrSDK/.../emlRefPhd.c`, `emlSndDrv.c`, `AcrSDK/ps2/flps2render.c` | 9.68 | **10.00** | a parameter object each, one or two call sites apiece |
| `platform/netplay/sdl_net_adapter.c` | 9.68 | **10.00** | the receive loop's condition named |
| `core/renderer.c` | 8.28 | **9.38** | eleven dispatch entry points folded by signature group |
| `Game/system/sys_sub.c` | 8.66 | **9.31** | the eight button mappings; `Meltw`'s run; the hidden extra options |
| `Game/ui/sc_sub_transition.c` | 8.67 | **9.31** | the full-screen quad four transitions fill; the run two of them share; the wipe-out's directions |
| `Game/io/pulpul.c` | 8.73 | **9.68** | the pattern row walk, its two row kinds, and the row start |
| `platform/netplay/fistbump.c` | 8.79 | **9.68** | the two connect waits, the state switch and the command chain both split |
| `Game/menu/netplay_menu.c` | 8.59 | **9.41** | the input frame, the exit condition and the confirm path |
| `port/sound/emlShim.c` | 8.94 | **9.50** | one condition bit, then the switch split |
| `AcrSDK/MiddleWare/PS2/CapSndEng/emlTSB.c` | 8.85 | **9.50** | one repeat of an echo |
| `AcrSDK/common/plapx.c` | 8.99 | **9.48** | the pixel layout, the palette layout and the palette extent |
| `port/sdk/sdk_libpad2.c` | 9.38 | **9.68** | the eight button pressure bytes |
| `port/config/config.c` | 9.38 | **9.68** | `is_int`'s character test named |
| `Game/ui/sc_sub_logo.c` | 9.02 | **9.38** | the two halves of the logo wipe |
| `Source/Common/MemMan.c` | 9.00 | **9.24** | the upward gap scan only - both scans pair and cost half a point |
| `AcrSDK/common/memmgr.c` | 8.64 | **8.88** | the upward gap scan, and the two neighbour links |
| `Game/demo/demo01.c` | 9.63 | **10.00** | the title's later steps split off |
| `Game/effect/effa2.c` | 9.34 | **9.47** | the two bar-drawing steps |
| `Game/demo/demo02.c` | 9.31 | **9.38** | the frame the demo hands the screen back |
| `Game/ending/end_14.c` | 8.03 | **8.28** | the right-hand background placement |
| `Game/engine/plpnm.c` | 8.03 | 8.03 | two folds that each shrank the duplication group without moving the score |

**What was tried and reverted**, with the measurement, so it is not tried again:

| File | Attempt | Measured |
| --- | --- | --- |
| `Lz77Dec.c` | the decode loop flattened with `continue` | 8.81 -> 8.81, cc +1 |
| `port/config/keymap.c` | `get_button_name` split three ways | 8.92 -> 8.54; every split of a name switch reproduces its own shape as a duplicate |
| `Game/stage/bg_zoom.c` | the inner zoom switches lifted | 8.54 -> 8.28 |
| `Game/opening/opening_bg0.c` | scene 3's block switch lifted | 8.12 -> 8.03 — **superseded 2026-09-20**: the same lift measures flat once Complex Method is the only category it touches, and the file went on to 10.00 |
| `AcrSDK/common/memmgr.c` | *both* gap scans lifted | 8.88 -> 8.15 |
| `Game/ending/end_01.c` | the two identical wait arms deduplicated | 9.60 -> 9.07; the file mean was under 4 and a cc-2 helper pushed it over |
| `Game/ending/end_01.c` | the fade arms split off | 9.60 -> 9.09 |
| `Game/engine/plpat00.c` | Jouka's first frame lifted | 9.06 -> 8.58 |
| `Game/effect/effa2.c` | three more blocks lifted | 9.47 -> 9.04 |
| `Game/com/com_sub_air_term.c` | the airborne half split off | 9.68 -> 9.09 |
| `AcrSDK/common/plapx.c` | the direct-colour layouts split off | 9.48 -> 9.38 |
| `Game/effect/effe9.c`, `effd1.c` | *both* arms of the mirrored pair | 10.00 -> 9.38 each |
| `AcrSDK/ps2/flps2etc.c` | the shared RGB and alpha runs | 9.84 -> 9.84 |
| `Game/rendering/mtrans_buffers.c` | the existing slot predicate reused in the 32 twin | 8.28 -> 8.28 |
| `Game/ui/netplay_menu.c` | the two page-entry arms lifted | 9.41 -> 9.09 |

**Verification.** Build and `refactor_guard.py` after every commit, in both `build` and
`build-dbg` wherever a file carries conditionally-compiled code or a `switch` over an
`enum`. The branch was then run through the wide replay gate,
`tools/replay_verify.sh <session start> 30 3600`: **30 seeds identical for 3600 saved
states each**. That covers the fight loop, which is what the pad-conversion changes in
`ioconv.c`, `sdk_libpad2.c` and `mlPAD.c` feed, and what the CPU-side changes in
`com_pl*.c` and the state changes in `plpnm.c` and `plpat09.c` sit inside.

What the replay gate does not reach is arcade, bonus and training flow, the attract
sequence, the menus and the endings. **Targeted playtesting is worth pointing at**
`Game/game.c`'s character-select entry and exit, `game_demo.c`'s attract stages,
`netplay_menu.c`'s confirm path, `pulpul.c`'s vibration state machine and `end_14.c` /
`end_18.c`.

## Where the opening_bg0 lever applies next - 2026-09-20

`opening_bg0.c` went 8.12 -> 10.00 by pricing **Overall Code Complexity** first and
re-pricing everything else afterwards; see *Price the file's cheapest finding before
inheriting a plateau* in the playbook. `tools/mean_probe.py` does the pricing - it inserts
`k` throwaway one-line functions, binary-searches the smallest `k` that closes the finding,
and restores the file - so "is this file the same shape?" is now a command rather than a
guess.

Run over all 109 files below 10.00, the finding is still open on **thirteen**. Four are
worth taking and were probed:

| File | Now | On the mean alone | Functions needed | Then what is left |
| --- | --- | --- | --- | --- |
| `Game/engine/cmd_main_checks.c` | 9.16 | **9.76** | **2** | Bumpy Road x3 - and each one lifted feeds the mean again |
| `Game/stage/bg_zoom.c` | 8.81 | **9.38** | 3 | Code Duplication x4 - then re-price the zoom-switch splits this file already rejected at 8.54 -> 8.28 |
| `Game/animation/appear_late.c` | 9.38 | **10.00** | 8 | nothing; the mean is the only finding |
| `Game/demo/demo00.c` | 9.38 | **10.00** | 8 | nothing; the mean is the only finding |

*The first run of these probes reported half of each number.* `mean_probe.py`
emitted a `static` and a caller per unit and counted units, so "4" meant eight
functions. Fixed, and the table above is the re-measured truth. `bg_zoom.c`'s
baseline also moved, from 8.54 to 8.81, on the green-band pass's Recipe E over
its two fighter midpoints.

`bg_zoom.c` is the closest match to `opening_bg0.c`: the same two findings, and a plateau
note recording the same kind of refusal ("one split pays, and the full set of six measures
8.54 -> 8.28, because the split halves are themselves twins"). Its rejected splits each
*add a function*, so they pay into the mean they were never measured against.

The remaining nine were the `Game/com/patterns` skeleton files at 7.55-7.78, and the probe
argued for leaving them: `com_patterns_4step_3.c` needed 12 functions and
`com_patterns_3step.c` 14, both reaching only **8.03**, because Code Duplication x14 to x44
was what actually held them down.

**Overturned 2026-09-21.** The probe was measuring the wrong lever. Splitting a skeleton
into more functions divides the complexity mean and leaves the duplication where it is;
Recipe J removes both, because a table of steps is neither complex nor ten lines long.
`com_patterns_4step_3.c` and `com_patterns_3step.c` are both at 10.00 without gaining a
single function. The reading to carry forward is that a mean-probe number is only an
argument about the mean - it says nothing about a finding it cannot move, and it should not
be quoted as a reason to leave a file alone when the dominant finding is the other one.

### The eleven that are left

| File | Score | Why |
| --- | --- | --- |
| `Game/com/com_sub_command_term.c` | 9.09 | the surveyed change measures 9.09, no gain |
| `Game/effect/eff11.c` | 9.13 | every legal probe measures **below** its own baseline; the only 10.00 probe changed a constant |
| `platform/video/psp/psp_renderer.c` | 9.38 | claimed win failed its independent check |
| `Game/com/patterns/com_patterns_6step.c` | 9.38 | three signatures over the column limit by 6-17 characters; the parameter object that fixes it is outside the catalogue |
| `Game/effect/eff68.c` | 9.38 | claimed win failed its independent check |
| `Game/stage/bg_zoom.c` | 9.38 | the mirrored dispatchers, re-priced five ways from the new baseline |
| `platform/netplay/fistbump.c` | 9.68 | 18 function arguments, 13 of them `char*` - Primitive Obsession, which no recipe reaches |
| `port/config/config.c` | 9.68 | no recipe in the catalogue reaches the finding |
| `port/sdk/sdk_libpad2.c` | 9.68 | **a real Recipe A lever**, waiting on a call-site pass |
| `Game/engine/charset.c` | 9.68 | **a real Recipe A lever**: `set_char_move_init2` takes five parameters, 157 call sites in 60 files |
| `AcrSDK/ps2/ps2PAD.c` | 9.92 | measured refusal |

Two of the eleven are not refusals. `charset.c` and `sdk_libpad2.c` both have a parameter
object that measures 10.00 and both probes failed to compile for the same reason - the
call sites were never updated. Those are API changes with their own blast radius and they
want their own commit series, measured across every file they touch, not a one-file win
taken off a survey probe.

### The seven-function gate, and what it settles

`plpat00.c`'s refusal above says the mean-probe model "can only lower the mean here" while
CodeScene reported the finding closed at the higher number and open at the lower, and ends
"Flagged rather than guessed at". It is settled now, measured rather than argued.

**CodeScene does not report *Overall Code Complexity* on a file with fewer than seven
functions.** Below that the finding is silent whatever the mean is; at seven and above it
is the plain mean cyclomatic complexity against a strict `< 4`. That is why a six-function
file at mean 7.8 shows nothing and the same file at mean 6.9 - one extraction later, seven
functions - shows the finding. Nothing about the metric was odd; the *reporting* has a
floor.

Established three ways: on `eff11.c` (one added function 8.57 open, eight added 8.57 open,
nine added 9.13 closed); on a synthetic file of identical cc-10 functions, silent at one to
six and open at seven; and by pinning a real file's total complexity exactly - cc-3
throwaway functions open the finding at k=25 and close it at k=26, which fixes the base
total at 49.

**What it means for pricing.** `mean_probe.py`'s arithmetic was right and its silence was
the problem: on a file near the floor, an extraction can *open* a finding that was only
ever hidden. So the first extraction on a small file may cost a point or more for reasons
that have nothing to do with the extraction, and the answer is to keep going rather than
revert - `eff11.c` needed **eight** commits, seven of them flat or down, before the ninth
function and the folds brought the mean back under 4 and the file reached 10.00.

### Primitive Obsession can only be gamed

`psp_renderer.c` was the repository's last *Primitive Obsession* finding. A proposed
"Domain Typedef" recipe - `typedef unsigned int ARGB;` and the seven parameters that carry
a packed colour spelled `ARGB` - reaches **10.00**, compiles under `-Werror` against the
unmodified header, and moves no literal.

It is not in the catalogue and should not be, for a reason found while checking it: a probe
spelling those parameters `ARGB` **with the typedef declared nowhere at all** also scores
10.00. The check is **lexical on the type token**. It does not resolve the name, so it
cannot tell a domain type from a misspelling, and a recipe built on it would be moving a
number by choosing identifiers.

The gate, measured: the finding opens above **60%** of parameters being built-in types
(27 of 40 = 60.00% closes it), on modules of **thirty functions or more**, counting
zero-argument functions in the denominator. Struct fields and locals do not count; only
parameters.

`Primitive Obsession` is open on exactly one file in the repository, so this was a patch
rather than a recipe even before the lexical finding. Recorded so nobody re-derives it.

### `config.c` and `fistbump.c`: a recipe that needs the owner's signature

A proposed "Closed Key Set" recipe takes `port/config/config.c` from **9.68 to 10.00** by
giving the seven configuration keys an enum and changing the three public getters from
`const char*` to that enum. It measures clean: literals unchanged in both directions across
all nine touched files, a full Release **and** Debug build of the whole project under the
project's own `-Wall -Werror`, and a replay-trace comparison of 31,200 saved states, every
one identical.

**It is not applicable as things stand, because it changes a type.** "Never change a type"
is on the unqualified hard-prohibition list. Recipe A is the precedent for a signature
change and it carries an explicit dated owner authorisation; this has none. It is legal as
a *proposal* and must not be applied until the owner adds it.

Two things to weigh if it is ever considered. It does **not** move `fistbump.c`, which
stays 9.68 - that file is a line protocol and its strings are strings. And the proposal as
written drops a guard its own sibling has: `config_key_name` is `return key_names[key];`
with no bounds check, so `Config_GetBool(42)` compiles silently and reads out of bounds,
where today an unknown key reaches `SDL_assert(false)`. `port/config/keymap.c`, the same
folder, already carries this exact shape **with** the bounds check. The guarded form
measures 10.00 as well, so there is no reason to prefer the unguarded one.
### The last nine, priced one at a time

`charset.c` and `sdk_libpad2.c` came off this list on 2026-09-21: both were Recipe A, both
reached 10.00, and what had been holding them was that a parameter object changes every
call site and a survey probe never does. `set_char_move_init2` had 156 of them across 60
files; none of the 60 regressed. What remains is nine files and four distinct reasons.

**Three are file-level ratio smells, and the catalogue has no recipe for any of them.**

- `platform/video/psp/psp_renderer.c` **9.68** after Recipe A cleared *Excess Number of
  Function Arguments* from `draw_textured_sprite_rect`'s ten arguments. *Primitive
  Obsession* is left, and it is a statement about the whole file's ratio of built-in types
  rather than about one signature. The file is a renderer whose vocabulary is floats and
  packed colours.
- `platform/netplay/fistbump.c` **9.68** and `port/config/config.c` **9.68**, both
  *String Heavy Function Arguments*: 72% of `fistbump.c`'s arguments are strings, because
  it is a line protocol and its functions take lines. Wrapping `const char*` in a struct
  would move the number and change nothing real.

**Four are Code Duplication over shapes the catalogue refuses to fold.** `bg_zoom.c`
(9.38, priced five ways from two baselines), `com_patterns_6step.c` (9.38, three signatures
over the column limit by 6-17 characters), `eff68.c` (9.38) and `com_sub_command_term.c`
(9.09, where the surveyed change measures 9.09 and gains nothing).

**`ps2PAD.c` 9.92 is a clean refusal on Recipe E's own fourth condition.** `flPADShockSet`'s
two bumps are the arms of `if (time == 0)`, and each writes `profile` **and**
`vib_data_size` - two outer locals. The recipe says skip it and do not invent an
out-parameter struct to carry results back. Both arms also contain
`if ((ps2slot[pad_id].vprofile = 3) != 0)`, an assignment that is always true and whose
else branch is therefore dead; that is arcade-accurate and is left alone.

**`eff11.c` 9.13 is the one that resists hardest, now measured from four directions.**
*Complex Method* on `quake_level_large` (cc 21) and `quake_level_middle` (cc 11), plus
*Large Method* on the first at 105 lines. Every attempt opens *Overall Code Complexity*
and lands below the baseline:

| Attempt | Measured |
| --- | --- |
| Recipe C on the two shared step prefixes (`char_move`+`add_y_sub`, and with `add_x_sub`) | **8.57** |
| Recipe X, `quake_level_middle` split in two | **8.84** |
| Recipe X, both functions split | **8.79** |
| the survey's eleven single-lever probes | all below 9.13, best **9.09** |

One added function costs about 0.56 on this file whatever it contains, which is the same
arithmetic `plpat00.c` showed before a seven-way decomposition beat it. A seven-step chain
does reach 10.00 here - the survey built one - but that probe also had
`ewk->wu.old_rno[5] = 28` written as `= 29`, so what it proves is unknown. A legal version
of that chain is the open question on this file; every shorter answer is priced above.
### The survey, and the two things it nearly shipped

Sixty-one files were surveyed in parallel: each diagnosed, each proposed change **probed**
against a scratch copy and scored rather than estimated, and every claimed win re-done
independently by a second agent. Thirty-five wins were confirmed and thirty-three applied.
Two were not, and both refusals are worth keeping.

**`eff11.c` - a changed constant, caught by the guard.** The only probe that reached 10.00
on this file had `ewk->wu.old_rno[5] = 28;` written as `= 29;`. Every literal-clean probe
of the same file measured 8.57, below its own 9.13 baseline. The step that nearly shipped
it was mine, not the surveyor's: I picked the best-*scoring* probe out of each directory,
and the directories contain diagnostics as well as proposals. `refactor_guard.py` reported
the both-ways FAIL - a value removed while another appeared - which is exactly the
signature it exists to catch, and the only reason this is a footnote rather than a defect.
**Select on legality first and on score second.** A score is a preference; the literal
multiset is a precondition.

**`charset.c` - a real lever, the wrong commit.** `set_char_move_init2` takes five
parameters, so Recipe A's trigger is genuinely present and the parameter object measures
9.68 -> 10.00. But the function has **157 call sites in 60 files**, and the probe was never
compiled - the first variant of it did not build at all. A 157-site API change is its own
commit series with its own measurement, not a one-file win taken on the back of a survey.
Deferred rather than refused.

**`com_patterns_6step.c` - refused on catalogue grounds, correctly.** A parameter object
bundling two engine argument objects per skeleton reaches 10.00 and breaks no hard rule.
The checker refused it anyway: Recipe A's trigger is *Excess Number of Function Arguments*
and these functions take three and four, the finding being attacked is Code Duplication,
and the playbook already priced the struct-per-skeleton form on `Game/com/active` and took
a third of a point less rather than mint a grab-bag type per skeleton. That precedent
holds. The file stays at 9.38.
### `bg_zoom.c`: priced three ways, and it stays at 8.81

The last file in the yellow band. Its two findings are *Overall Code Complexity* and
*Code Duplication* over four functions - the horizontal and vertical zoom-request chains,
which are the same shape on different bits.

**Lifting the inner switches: 8.81 -> 8.28.** The file is factored inconsistently - the
vertical chain holds its `0x0` case as `select_vertical_0_zoom_request` and the horizontal
chain has the same case inline - so making the two symmetrical is a Recipe E with a reason
of its own. Lifting all five inner switches measures **8.28**, and lifting only the one
that removes the asymmetry measures **8.54**, with the duplication group growing from four
functions to six. Every shortened dispatcher becomes another member of the clique it was
supposed to leave. This re-derives the 8.54 -> 8.28 already in the table above, from a
different baseline.

**The mean alone: 9.38, and there is nothing legal to spend.** `mean_probe.py` says three
more low-complexity functions close *Overall Code Complexity* and leave duplication x4.
But the file has no third extraction to make: everything except `check_cg_zoom` is already
one small function, and `check_cg_zoom`'s one cohesive block - the `bg_stop` negotiation
that gives both fighters the higher zoom level and swaps their look bits - **writes two
outer locals**, `p1zoom` and `p2zoom`. Recipe E's fourth condition says skip it and do not
invent an out-parameter struct. So 9.38 is not reachable either.

**Folding the two chains into one: not available, and not because of the case labels.**
The obvious move is to parameterise the mask, the labels, the request function and the
axis. It fails on something better than a rule: the two chains are *not the same function*.
The horizontal `0x4000` arm does nothing and the vertical one requests zero; the horizontal
`0x200` inner switch sends `0x4000` to P1's position and the vertical `0x100` sends it to
zero; the vertical has an extra arm throughout. A parameterisation that encoded all of that
would be longer than the two chains and correct only by construction, in a file whose five
outputs - `scr_req_x`, `scr_req_y`, `zoom_request_flag`, `zoom_req_flag_old` and
`zoom_request_level` - are all rollback-saved state (`platform/netplay/game_state.h:392`).

Unlike the CPU scripts, this file *is* covered by replay verification, so a future attempt
has real evidence available. It would need a recipe the catalogue does not have.
### `plpat00.c`: a measured refusal, and a hole in how the mean is priced

`Game/engine/plpat00.c` scores **9.06** with *Bumpy Road Ahead* on two functions,
*Complex Method* on two (`Att_JYOUKA` cc 20, `Att_PL00_TOKUSHUKOUDOU` cc 9) and *Large
Method* on `Att_JYOUKA` at 95 lines. `tools/mean_probe.py` reports the mean finding
**already closed**.

Recipe E over `Att_JYOUKA`'s entry arm - 46 lines, lifted whole into `launch_jyouka` -
clears *Large Method* and takes the function from cc 20 to cc 17. It measures **9.06 ->
8.58**, because *Overall Code Complexity* **opens**. Extracting two more arms as well
measures 8.66. Both reverted under rule 2.

That is worth recording because it contradicts the model `mean_probe.py` is built on:

> lifting `b` branches into a helper takes `b` off the parent and gives the helper
> `1 + b`, so the file's total complexity rises by exactly one and its function count by
> exactly one

If that were the whole story the mean could only fall here: the file holds six functions
and a total cyclomatic complexity near 47, so a seventh function and one more branch takes
it from about 7.8 to about 6.9. CodeScene's own numbers agree with that arithmetic - it
reports the same cc for `Att_JYOUKA` before and after - and yet the finding is closed at
7.8 and open at 6.9.

So either the threshold is not the flat 4 the tool's docstring states, or *Overall Code
Complexity* is not the plain mean over all functions. **Do not price a mean finding on a
small file from that model until someone establishes which.** The number to trust is the
one `code_health_review` returns after the change, and on this file it says the extraction
is not worth having.

**`appear_late.c` refuses it a second way, and this one is understood.** The probe reads
`9.38 -> 10.00 on 8 more low-complexity functions`, and the table above records "nothing;
the mean is the only finding". Three extractions in - `Appear_33000`'s drop-in,
`Appear_34000`'s random entry, and the fourth arm of `choose_appear_29000_entry` - the
file measures **8.54**, with *Code Duplication* open on three groups that did not exist
before:

- `drop_appear_29000` against `start_appear_33000`: both are an entry arm that sets a
  counter and calls `cal_initial_speed` at `pos_x_work` plus or minus 0x58. They were
  never alike as *arms* of two different switches; lifting them out made them two
  functions of the same shape.
- `Appear_33000` against `step_appear_36000_settle` and `step_appear_29000_settle`:
  shortening `Appear_33000` from 38 lines to 12 did not make it unlike anything - it made
  it *like* the other short state machines in the file.

That is the general shape of it. `mean_probe.py` prices one finding in isolation and its
number is an **upper bound that assumes the functions you add are unlike each other and
unlike what is already there**. In a file whose functions are the arms of a state machine,
extracted arms are alike by construction, and shortening a function moves it into the size
band where the duplication check compares it against its neighbours. Read the probe as
"this many functions would close the mean *if nothing else opens*", and re-review after
the third extraction rather than after the eighth.

Both files reverted. Neither is a plateau in the catalogue's sense - a recipe that is
legal and pays is still wanted - but Recipe E over their state-machine arms is priced and
is not it.

### The other half of the lever: 59 files where duplication is all that is left

Clearing Code Duplication on any of them means 10.00. Thirty-six are the machine-folded
`Game/com` script folders and belong to the `gfold`/`xfold` workflow. The other **23** were
refactored by hand, and **thirteen of those are a single two-function pair at 9.38**:

`core/renderer.c`, `platform/input/sdl/sdl_pad.c`, `Game/effect/eff09_late.c`,
`Game/effect/eff93.c`, `Game/ending/end_10.c`, `Game/ending/end_20.c`,
`Game/engine/plcnt_setup.c`, `Game/menu/replay_menu.c`, `Game/rendering/mtrans_pool.c`,
`Game/system/ramcnt.c`, `Game/ui/sc_sub_logo.c`, and two more at the same score.

A pair is the shape `opening_bg0.c` finished on. Where the two differ only in literals, the
2026-09-20 two-instance licence folds them. Where they are a true mirror - `<` against `>`,
`+=` against `-=` - nothing folds them, and the move is to lift a block out of **one** side
only: the asymmetry drops that side below the similarity threshold and both functions leave
the finding. Doing it to both sides puts the pair straight back. Worth **+0.62** each.

`Game/opening/opening_bg1.c` (9.38, four functions) is the sibling of the file this all came
from and has not been retried.

## Folder campaigns

Work that is not a numbered task, because none of these files were in the Red band.
Recorded here so a later agent can see what has already been swept.

| Folder | Files | Before | After | Notes |
| --- | --- | --- | --- | --- |
| `Game/ui` | 9 -> 11 | 4.06 - 9.92 | mean **8.58** | `sc_sub.c` split five ways; *Recipe A clears one finding, not fifteen*, and the re-wrap its call sites needed cost two files a band until they were split again |
| `Game/com/passive` | 20 -> 67 | 4.90 - 7.55 | mean **10.00**, all 67 at 10.00 | 3488 CPU pattern scripts folded onto shared skeletons, then Recipe J over what was left |
| `Game/com/active` | 20 -> 22 | 5.04 - 8.03 | mean **10.00**, all 22 at 10.00 | 1621 scripts, the same shape under another name; folded folder-wide first, then again across both folders at once, then Recipe J |
| `Game/com/patterns` | 0 -> 15 | - | mean **9.75**, 12 of 15 at 10.00 | the shared skeleton module the two script folders used to hold twice, plus Recipe J's interpreter |

Both COM script folders are done, and since 2026-09-19 they share one skeleton module in
`Game/com/patterns`. `tools/passive_fold.py --family {passive,active,com}` carries the
transformations and the equivalence check; `--family com` works on both folders at once
against the shared module, which is what took the active folder past 8.64. See *Where
`Game/com/active` stopped the second time* in `PLAYBOOK.md` for the sequence, the four
refusals, and where the floor is.

## Progress

Update as tasks land.

The **Baseline** column is refreshed whenever these files are regenerated, so for a task
already under way it shows the score at last regeneration, not the campaign's starting
point. **Campaign start** preserves the original 2026-09-01 sweep.

| Task | Campaign start | Baseline | Current | Status |
| --- | --- | --- | --- | --- |
| R01 | 1.42 | 1.42 | **10.00** | Done. Split into `hitcheck_collision.c`, `hitcheck_damage.c` and `hitcheck_defense.c` (Recipe S), all four files at 10.00. The `goto` cores that were left untouched in the first wave moved out whole rather than being rewritten. |
| R02 | 1.52 | 1.52 | **10.00** | Done. The `com_sub` family - `com_sub_attack.c`, `com_sub_command.c`, `com_sub_jump.c`, `com_sub_arts.c` and the rest - carries the parameter-object structs the passive and active scripts pass at every call site. |
| R03 | 1.82 | 1.82 | **8.92** | Plateau. Split into `pls03_super_arts.c`, now **9.92**. `decode_wst_data`'s twelve command encodings and `waza_select`'s eleven case labels are what stop the original; neither loses a branch without renumbering a state. The super-arts file stops on its direct-cancel side, which mirrors grounded against airborne at every level. |
| R04 | **1.97** | 2.25 | **10.00** | Done. Split into `extra_option.c`, `direction_menu.c`, `menu_selection.c`, `blocking_training.c` and more; `netplay_menu.c` was the lowest of the family at 8.59 and is **9.41** since 2026-09-20. |
| R05 | 2.31 | 2.31 | **9.39** | Plateau. Split into `cmd_main_checks.c`, now **7.50** and the hardest file left in the folder: its mean needs thirteen more functions against a duplicate web that charges for every one. `cmd_main.c` itself stops on the two `latch_sw_lvbt_bit_*` functions, whose cc 11 is almost entirely `case` labels. |
| R06 | 2.57 | 5.24 | **8.03** | Plateau. Split into `mtrans_seqs.c` (**10.00**), `mtrans_pool.c` (9.38) and, on 2026-09-19, `mtrans_buffers.c` (8.28). The size finding that stopped it is gone: "every seam runs through a shared static" was read as covering the buffer pool, and the statics there are *functions*, so an internal header cuts it the way PPGFile was cut. What is left is the 16/32 twin web, which travelled into the new file with the pool. |
| R07 | 2.58 | 2.58 | **8.54** | Plateau, re-tested 2026-09-19. Code Duplication is the only finding, and it is five groups of exactly **two**. Four are near-misses the catalogue refuses: `eff09_0000`/`eff09_8000` and the two `advance_*` functions differ in their conditions and their callees, and `initialize_eff09_4000`/`_11000` differ in the *operators* of their mirrored branch. The fifth, `adjust_sean_ball_left`/`_right`, differs in nothing but literals - a mask, a counter index, two limits and a column - and is blocked only by Recipe V's three-instance rule. It is the same open question `Game/ending` left: no third instance exists anywhere in the tree (`grep` finds the skeleton four times, all in this file). |
| R08 | 2.64 | 2.64 | **10.00** | Done. |
| R09 | 2.74 | 2.74 | **10.00** | Done. Split into `pls00_normal_states.c` (now **8.03**) and `pls00_damage_states.c` (10.00); the original is at 10.00. The normal-states file plateaus on a Code Duplication web between the `nm_*` state machines themselves, which no shared run reaches. |
| R10 | 3.09 | 3.09 | **10.00** | Done for the original; the folder was reworked on 2026-09-19. `opening.c` **10.00**, `opening_scenes.c` 7.42 -> **9.09**, `opening_scenes_late.c` 6.77 -> **9.09**, `opening_bg0.c` 7.54 -> **10.00** (8.12 on 2026-09-19, then nine more commits on 2026-09-20 - see the plateau note it overturned), `opening_bg1.c` **8.28**. The earlier note - that chaining one scene pays and chaining the next costs - was true of the scenes *as they were*: every scene step was eight lines of cue-test, advance and background move. Folding those onto `opening_cue_step` and its two variants (fifty steps across the two files) made the arms one line each, and only then did chaining the long switches pay. What was thought to stop the two bg files is the sibling state machines reading as copies of one another, with different statements in the same shape - Recipe D's forbidden case. That is true of the fold, and it is not the only way to break a pair: lifting a block out of **one** side of a mirrored pair drops it below the similarity threshold, and that is how `opening_bg0.c`'s last two groups went. `opening_bg1.c` has not been retried. |
| R11 | 3.49 | 3.49 | **9.31** | Plateau. Split five ways: `PPGFile_quads.c` (**10.00**), `PPGFile_chunks.c` (**10.00**), `PPGFile_palettes.c` (**10.00**) and `PPGFile_context.c` (**10.00**); group mean 9.86. The 2026-09-19 pass took the chunk file from 6.99 by extracting every loop and lookup out of the six setup functions and then splitting the palette side off, which cleared Overall Code Complexity on both halves. What stops `PPGFile.c` is the palette/texture twin pair - `ppgRelease*Handle` and `ppgGetUsing*Handle` differ in their type and in three callees each, which is Recipe D's forbidden case. |
| R12 | 3.56 | 3.56 | **10.00** | Split into `appear_late.c`, which is at 9.38 with Overall Code Complexity as its only finding - `tools/mean_probe.py` prices that at **four** functions for 10.00. The original reached 10.00 and this row had not caught up. |
| R13 | 3.56 | 3.56 | **10.00** | Done. |
| R14 | 3.62 | 3.62 | **9.09** | Plateau. Split into `bg_textures.c` (10.00); the whole stage folder went with it. |
| R15 | 3.68 | 3.68 | **10.00** | Done. `plpdm.c`, `plpdm_states.c` and `plpdm_states_late.c` are all at 10.00. The last two were the campaign's most stubborn plateau until the runs the damage states share were taken instead of their arms - see *Against a twin family, share what they agree on* in `PLAYBOOK.md`. |
| R16 | 3.75 | 3.75 | **8.28** | Plateau. Split six ways: `ck_pass_checks.c` (**10.00**), `ck_pass_units_a.c` (**10.00**), `_b.c` (9.38), `_c.c` (**10.00**), `_d.c` (**10.00**). What stops `ck_pass.c` is `KEN_vs`, `HUGO_vs` and `GILL_vs`: re-diffed 2026-09-19 and the refusal holds - Hugo discards the jump check's answer and has no personal action, Gill adds a squat check. Below them, three *area helper* pairs were exact Recipe F cases and were folded on 2026-09-19, 8.03 -> 8.28; the earlier note had read the `*_vs` refusal as covering the whole file. |
| R17 | 3.86 | 3.86 | **10.00** | Done. Split into `entry_break_in.c`. |
| R18 | 3.92 | 3.92 | **9.68** | Plateau. Split twice, into `charset_commands.c` (10.00) and `charset_position.c` (10.00). What stops the original is `set_char_move_init2`'s five arguments. Recipe A would clear it, and the obstacle is scope rather than any one file: **155** call sites, 111 of them in the effect folder and 13 in animation. |
| R19 | 3.92 | 3.92 | **9.92** | Plateau. Split into `manage_bonus.c` (10.00) and `manage_result.c` (9.38). `Game_Manage_7_3`'s dead condition is the last finding and the catalogue forbids deleting it. |
