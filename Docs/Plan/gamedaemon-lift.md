# GameDaemon full C++ lift: plan

Status: plan, 2026-11-27. ROADMAP row S4.

Owner decision, 2026-11-26: every exe gets the full C++ lift, GameDaemon too. The lift is the parity oracle. A Rust step follows at each 10 % MATCH step (see `modernize.md`).

Marks: ❓ = estimate or not verified. Measure it in wave 0.

## 1. Scope

| Item | Rule | Source |
| --- | --- | --- |
| Logic | 2019 + PDB GameDaemon. PDB names only. | `plan.md`, `rust-port-brief.md` |
| Packets | The 381 build decides packet layout and codes. | Owner rule (381 authority) |
| Parity | Client-visible parity. Internals can be modern. | `modernize.md` (parity-scope) |
| Goal | 95 % per exe, 99 % preferred. Stall rule applies. | `Docs/Parity/README.md` |
| Server checks | In scope: movement, speed, fly, distance, skill checks and kicks. | Owner scope for GameDaemon |
| Anti-cheat vendor code | Out of scope: NCGuard, GameGuard, BloodCert, BNSHelper.dll, XIGNCode. EAC is deferred. | Owner scope for GameDaemon |

### Anti-cheat handling

| Part | Counted functions | Plan |
| --- | ---: | --- |
| Vendor libraries (GameGuard server lib, NCGuard server lib, BloodCert) | 11 | Do not lift. Do not link. They stay "only in original". |
| GameDaemon glue (NCGuard, GameGuard, XIGNCode3 classes, their timers and handlers) | 33 | Lift as "feature off" bodies with a `// LIFT:` note. Do not use `LIFT_STUB` (callers fold under LTCG). Not in any card scope. The config keeps the features off. |
| BNSHelper.dll | 0 | The 2019 + PDB exe does not import it. |
| TencentProtect | 2 | ❓ Not on the owner list. Treat it as glue (off body) until the owner decides. |

- Total: 44 counted functions (0.34 %). The best reachable parity is 12,807 / 12,851 = 99.66 %.
- No new exclusion rule is necessary. These functions get no credit.

## 2. Measured size

Source: 2019 + PDB `GameDaemon.exe` and `GameDaemon.pdb` (PDB age 2, the exe debug record matches). Counts use the same rules as `tools/funcdiff.py`. LobbyDaemon is the reference.

| Count | GameDaemon | LobbyDaemon | Ratio |
| --- | ---: | ---: | ---: |
| PDB procedure records | 24,222 | 3,789 | 6.4× |
| Unique function RVAs | 18,851 | 3,026 | 6.2× |
| funcdiff-counted functions (parity total) | 12,851 | 2,204 | 5.8× |
| Counted code bytes | 7.09M | 1.08M | 6.6× |
| Hex-Rays pseudocode lines | ~1.37M ❓ | 219k (measured) | 6.3× |
| Pseudocode tokens | ~11M ❓ | ~1.75M ❓ | |

- Toolchain: VS2010 (linker 10.0), the same as the other 5 exes.
- Imports: system DLLs plus msvcr100 and msvcp100 only. No game DLL is necessary.
- One card of 2,500 pseudocode lines is about 20k tokens of input.

### Build layout: unity build

The original GameDaemon is a unity build. The PDB modules are `UnityBuild02.obj` to `UnityBuild19.obj`. 12 unity modules hold most of the code (the largest has 3,584 counted functions). The `plan.md` rule "one .cpp per PDB module" does not fit.

The plan maps each function to its source file from the PDB line tables (first line entry at the function start). 19 functions have no file.

Rule for GameDaemon: one `.cpp` per original source file, in `src/Server/GameDaemon/`. The wave 0 pilot (card 0d) checks that this does not change codegen against a unity TU ❓.

### Counted functions by area

| Area | Counted | Shared with lifted exes |
| --- | ---: | --- |
| GameDaemon sources (303 files) | 10,523 | 22 MATCH, 13 not MATCH |
| BloodLib | 819 | 431 MATCH, 57 not MATCH, 331 new |
| Packet headers (game log 395) | 419 | 9 MATCH, 5 not MATCH |
| Data (DataManager 327, zlib 44, minizip 20, packer 14) | 410 | |
| DataReader library | 235 | |
| Property headers | 193 | |
| BloodCrypto | 105 | 85 MATCH, 19 not MATCH |
| Server shared | 59 | 36 MATCH, 8 not MATCH |
| CRT, VC headers, other libraries | 69 | CRT 11 MATCH |
| No file | 19 | |

| Group | Functions |
| --- | ---: |
| New (in no lifted exe) | 12,126 |
| Shared, MATCH in each exe that has them | 620 |
| Shared, not MATCH in every exe | 105 |

### Largest GameDaemon source files (counted functions)

| File | N | File | N | File | N |
| --- | ---: | --- | ---: | --- | ---: |
| task.cpp | 570 | skillaction.cpp | 215 | gamedebugcommand.cpp | 146 |
| gamepackethandler.cpp | 457 | guild.cpp | 210 | item.h | 141 |
| pc.cpp | 454 | effectcontent.cpp | 206 | gamearenachannel.cpp | 137 |
| cachedaemonchannel.cpp | 426 | inventory.cpp | 205 | item.cpp | 134 |
| inventoryaction.cpp | 404 | team.cpp | 190 | effect.cpp | 126 |
| zone.cpp | 300 | gamedebugpackethandler.cpp | 176 | world.cpp | 115 |
| questjournal.cpp | 222 | creature.cpp | 170 | accountinventorytran.cpp | 110 |

- 19 files have more than 120 counted functions. Split each into part files (`pc_1.cpp`, `pc_2.cpp`, ...) by RVA range in the skeleton. Then two cards in one wave never edit the same file (rule from the gap card index).

## 3. Wave order

Order: easy leaves first (wave E), then callees first, callers last. Reason: a `LIFT_STUB` body becomes noreturn under LTCG, and ICF folds it. A real caller of a stub then stays DIFF. So leaves (library, data, objects) come before actions, channels and handlers. A leaf calls no other lifted function, so it can MATCH in any wave.

Source of wave E: owner order 2026-11-27 ("get all easiest stuff out of the way"), card `lift-gamedaemon-0b2`.

### Card queue (measured, cards `lift-gamedaemon-0b` and `lift-gamedaemon-0b2`)

Queue: `Docs/Plan/cards/lift-gamedaemon-plan.tsv` (10 columns; column 10 = wave; row order = run order). Cards: `Docs/Plan/cards/lift-gamedaemon-eN.md` for E, `lift-gamedaemon-N.md` for W1 and W2.

| Class | Functions | Card scope |
| --- | ---: | --- |
| `shared-match` (MATCH in each lifted exe that has the name) | 606 | No card. The skeleton links the shared source. |
| `shared-diff` (shared, not MATCH in each exe) | 96 | W1. 32 of them are EXCLUDED in 1 or more exes. |
| `anticheat` (section 1: vendor 11, glue 33, TencentProtect 2) | 46 | No card. |
| `new` | 12,103 | Wave from the wave map below. |
| Total | 12,851 | |

| Wave | Functions | Pseudocode lines | Tokens (8 per line) | Cards | Status |
| --- | ---: | ---: | ---: | ---: | --- |
| E | 1,622 | 23,616 | 0.19M | 45 (11 `sonnet:high`) | ready |
| W1 | 754 | 84,837 | 0.68M | 38 (20 `sonnet:high`) | ready |
| W2 | 573 | 89,783 | 0.72M | 42 | ready |
| W3 | 2,303 | 268,557 | 2.15M | 131 | planned |
| W4 | 1,219 | 142,057 | 1.14M | 69 | planned |
| W5 | 1,707 | 189,088 | 1.51M | 94 | planned |
| W6 | 444 | 70,235 | 0.56M | 32 | planned |
| W7 | 2,999 | 306,559 | 2.45M | 158 | planned |
| W8 | 578 | 50,869 | 0.41M | 24 | planned |
| Total | 12,199 | 1,225,601 | 9.80M | 633 | |

Card 0b had W1 875 functions (44 cards), W2 837 (52), W3 2,731 (140), W4 1,391 (73), W5 1,878 (98), W6 460 (32), W7 3,369 (167), W8 658 (26). Wave E took its easy functions out of these waves.

#### Ease rule (card 0b2, script `ease_gd.py`)

Each `new` and `shared-diff` function gets these measured values from the pseudocode:

| Value | Rule |
| --- | --- |
| Lines | `last - first + 1` in `index.tsv` |
| Calls | Different direct calls in the body to counted functions of class `new`, `shared-diff` or `anticheat`. Calls to CRT functions, `shared-match` functions, Win32 and compiler helpers and virtual calls (`->f(`) do not count. 0 calls = leaf. |
| Form | `empty`; `getter` (one `return x;`); `setter` (one `this->m = x;`); `xtor` (constructor or destructor with at most 6 statements) |
| Plain | Leaf and (a form, or at most 8 lines: one statement) |
| Best state | `shared-diff` only: best funcdiff state in the 5 lifted exes (`Docs/Parity/baseline/<Exe>.json`) |
| Cost | Lines + 40 per call. +100 for a `shared-diff` function that is MATCH in no exe. Cost is the inverse of expected MATCH per token. |

| Rule | Value | Reason |
| --- | --- | --- |
| Easy (wave E) | Leaf, at most 30 lines | In the 5 lifted exes, 830 of 837 leaves (99 %) of at most 30 lines are MATCH; above 30 lines, 95 %. |
| Cap | At most 40 easy functions per stem | One E card holds 20 to 40 functions, and no stem is in two E cards. 39 easy functions (stems `duelbot_h`, `publisherlibsfunctions`) stay in their W card. |
| Excluded | Anti-cheat functions; upstream cards (zstd, zlib, minizip) | No hand lift. |
| Not easy | A simple form with a call (55 functions, for example a destructor that calls a base destructor) | A stub callee keeps it DIFF. It stays in its W card. |
| Card ease key | Cost per function of the card. Upstream cards: 0 (no hand lift). | |
| Ease band | `floor(log2(ease key))` | One band = a factor 2 in cost per function. |

Wave E cards (`lift-gamedaemon-e1` to `-e45`):

- One E card holds 20 to 40 functions and at most 2,500 lines from 1 or more stems of one source wave (W1 to W8). All easy functions of a stem are in one E card. 4 cards have fewer than 20 functions: their source wave has no other card with space (W1 11, W4 15, W5 15, W6 16).
- Packing: stems with only plain functions first and in their own cards; easiest stem first; first fit.
- Order: lowest ease band first; inside one band, the source wave order (W1 first); then the ease key.
- Model: `sonnet:high` when each function is plain (11 cards); else `opus` (34 cards).
- Depends on: `lift-gamedaemon-0e` only. A dep chain is necessary only when two E cards edit one file (0 cases).
- A W card that edits a file of an E card depends on that E card (475 W cards).
- W1 and W2 order: the easiest ready card first (ease band, then the area order), each dep before its user.
- W card ids: a W card keeps the 0b id of the card with the most of its functions (586 cards). 46 old ids went away (empty or merged). 2 new ids: `lift-gamedaemon-633` (W3), `lift-gamedaemon-634` (W7).

Planner rules (card 0b):

- A name in a GameDaemon source file is `shared` only if the lift defines it in shared code. Else it is `new` (35 functions, for example `wmain`). The card names the other exe file as a hint.
- zstd (W1), zlib and minizip (W2) are upstream cards. They link the upstream source and do not lift by hand (lessons A5).
- A stem above 40 functions or 2,500 lines is split by RVA into parts. The parts of one stem are a serial chain ("Depends on"). Thus two cards that edit the same file never run at the same time.
- 3 cards hold 1 function above 2,500 lines. A function cannot be split.
- Many cards have fewer than 20 functions: the mean function has about 100 pseudocode lines, so the 2,500-line limit applies first.
- The game log cards (395 functions) have one layout. The first card is `opus` and sets the pattern. The other cards are `sonnet:high` and depend on it. Card 0b2 moved most property header functions (getters) to wave E. The rest are in mixed W2 cards, so the property header group has no pattern card now.
- "Depends on" holds the chain part before, and the cards that hold callees (found in the pseudocode by PDB name) when the call order is clear. The wave gate of section 5 still applies.
- W3 to W8 rows have status `planned`: stems and counts only, chain deps only. A wave planner writes their card files and callee deps.

| Wave | Content | Counted | Cards ❓ | Pseudocode tokens ❓ |
| --- | --- | ---: | ---: | ---: |
| W0 | Setup: pseudocode export per source file, planner, skeleton, unity pilot, switch-on (section 4) | 0 | 5 | |
| E | Easy leaves of all areas W1 to W8 (owner order 2026-11-27, card 0b2) | 1,622 | 45 | 0.19M |
| W1 | Shared and common gaps: BloodLib new code (json, property, channel, log archive, HTTP client), BloodCrypto gaps, server shared, packet game log, FsdReader, banned word filter; zstd from upstream source | 754 | 38 | 0.68M |
| W2 | Data layer: DataManager, DataReader library, property headers. zlib and minizip from upstream source where the codegen allows. | 573 | 42 | 0.72M |
| W3 | Core objects: GameDaemon main and config, world, zone, geo world, creature, PC, NPC, user, item, inventory, effect, skill, env objects | ~2,800 | 93 | ~2.4M |
| W4 | Actions and server checks: move action, geo move checker, path finder, skill action, reaction, system, NPC, manipulate and boss skill actions, inventory action | ~1,390 | 46 | ~1.2M |
| W5 | Channels and transactions: CacheDaemon, LobbyDaemon, account inventory, arena, market dealer and other channels; all `*tran.cpp`; tickets | ~1,820 | 61 | ~1.7M |
| W6 | Packet handlers: game packet handler, smart coupon handler | ~460 | 15 | ~0.6M |
| W7 | Content systems: task, quest journal, guild, team, party, duel, battle royal, arena rooms, other content | ~3,370 | 112 | ~2.6M |
| W8 | GM and debug: game debug commands and handlers, GameBuilder; publisher and Tencent log code; anti-cheat glue as off bodies | ~680 | 23 | ~0.5M |

- E, W1 and W2 numbers are measured (cards `lift-gamedaemon-0b` and `0b2`). The other rows are the first plan estimates. The measured queue above replaces them.
- Total: 633 cards in `Docs/Plan/cards/lift-gamedaemon-plan.tsv` (125 ready: E 45, W1 38, W2 42; 508 planned).
- Rust steps: R10 at 1,285 MATCH, R20 at 2,570, and so on (`modernize.md`). A Rust step does not block the lift.
- Inside a wave, cards run in parallel only when their files do not overlap.

## 4. Wave 0 cards

| Card | Model | Scope | Done when |
| --- | --- | --- | --- |
| `lift-gamedaemon-0a` | sonnet:high | Tool: `tools/hr_export.py` gets a mode that writes one file per original source file (from the PDB line tables) and splits files above 120 functions by RVA range. Then IDA analysis of a copy and the export to `~/.cache/bns-lift/hr/GameDaemon/`. Writes `index.tsv` (function, RVA, file, part, lines). | Export has all 12,851 counted functions. |
| `lift-gamedaemon-0b` | opus:high | Planner (format of `lift-infogatedaemon-plan.md`): card queue for W1 and W2, then W3 and later waves. 20 to 40 functions and at most 2,500 lines per card. One pattern file per card. | `Docs/Plan/cards/lift-gamedaemon-plan.tsv` exists. No file is in two cards of one wave. |
| `lift-gamedaemon-0c` | opus | Skeleton (pattern `lift-lobbydaemon-0.md`): `include/pdb/GameDaemon/types.h` from `tools/pdb2h.py`; one header and one `.cpp` (or part files) per source file with `LIFT_STUB` bodies; anti-cheat glue as off bodies; CMake `lift_gamedaemon` plus `lift_common_gd` and `lift_exe(GameDaemon ...)`. GameDaemon is opt-in: it is not yet in the default exe lists. Make the `LiftStub.h` comment general (the RVA is in the exe of the module). | The exe links. Other 5 exes: no lost MATCH. |
| `lift-gamedaemon-0d` | sonnet:high | Pilot and measurement: unity TU against per-file TU for 2 sources (MATCH count must be equal); cold and warm build time, LTCG link time, peak RAM, object and output disk. Writes the numbers into this file (section 7). | Numbers are in section 7. Unity decision is written. |
| `lift-gamedaemon-0e` | sonnet:high | Switch-on: add GameDaemon (tag `GD`) to `tools/vs2010/build.sh`, `tools/parity.sh`, `tools/parity_readme.py`; first baseline with `tools/parity.sh --accept`. Lands only after the card engine supports GameDaemon (section 6). | Baseline has GameDaemon. README table has a GameDaemon row. |

## 5. Card size and gates

| Item | Rule | Source |
| --- | --- | --- |
| Card size | 20 to 40 real functions, at most 2,500 pseudocode lines, one stage of 25 turns | `cards/lift-infogatedaemon-plan.md` |
| Token target | One Opus session per card, about 200k to 320k tokens | gap card index |
| Pattern | Each card names one pattern file (a matched LobbyDaemon or GameDaemon file) | planner rules |
| Model | `opus:high` only for the planner card; `opus` for reversing; `sonnet:high` for known fix patterns; never xhigh or max | `Docs/Parity/README.md` "Model per card" |
| Card gate | Builds pass; no lost MATCH in any exe (else an `allow-worse.txt` row); review accepts each new MATCH | `Docs/Parity/README.md` |
| Fake MATCH | Never. A rejected MATCH goes to `excluded.tsv` only with an operator receipt. | `Docs/Parity/README.md` |
| Baseline | Only `tools/parity.sh --accept` changes `baseline/` and `progress.tsv` | `Docs/Parity/README.md` |
| Lessons | Each new fix pattern goes into `Docs/Parity/lessons.md` | `Docs/Parity/README.md` |
| Stall | 3 rounds with no gain = `stopped`, with a cause per open function | `Docs/Parity/README.md` |
| Wave gate | All cards of the wave landed or parked with a cause; lessons written; a 10 % step starts its Rust step | this plan, `modernize.md` |

## 6. Card engine needs

The card engine (operator tooling, not in this repo) knows 5 exes now. GameDaemon needs these changes before card `0e` lands. The operator makes them.

| # | Need |
| --- | --- |
| E1 | Add GameDaemon to the target exe list. This changes the target digest, so all card bases rebuild once. |
| E2 | Gate scripts and the remote build: mount and copy the GameDaemon original; generic exe lists in place of fixed lists. |
| E3 | Proof checker: pin the GameDaemon original hash. |
| E4 | Card filter and planner: exe tag `GD`; per-exe state in place of LobbyDaemon-only code; source dir per exe. |
| E5 | Linked REF/NOREF builds, cached build, preview, insn diff, evidence and author packet: an exe parameter (now LobbyDaemon only). |
| E6 | Land queue and triage: exclusion and NOREF rules per exe. |
| E7 | Disk guard peak, `/tmp` size and slot peak RAM: set from the card `0d` numbers. |
| E8 | Remote build host: GameDaemon toolchain cache. |

## 7. Build and disk

Estimates scale LobbyDaemon by 6.6× code. Card `0d` replaces them with measured numbers.

| Item | LobbyDaemon (measured) | GameDaemon ❓ |
| --- | --- | --- |
| Original exe / PDB | | 16.3 MB / 37.7 MB (measured) |
| VS2010 objects | 61 MB (+46 MB shared) | ~400 MB |
| Extra disk per full card dir | card dir now 334 MB | +0.6 to 1.0 GB |
| Warm linked build | 51 s | ~220 to 260 s |
| Cold build | 221 s | ~24 min at 4 cl jobs |
| LTCG link peak RAM | inside 2,130 MB slot peak | unknown, can be above the slot peak |
| funcdiff | a few s | ~30 s |

- The data disk has 35 GB free now. The disk guard floor is about 20 GB. 3 card dirs in parallel can use 3 to 4 GB more. Clean card dirs after land.
- A change in a unity-size TU recompiles many functions. Per-file TUs keep card builds small.

## 8. Token estimate

Unit: nocr tokens (meter column). Base rates are measured on the LobbyDaemon waves (card engine doc "waves vs v2").

| Rate per MATCH | When | Total for 95 % (~11,600 new MATCH) |
| --- | --- | ---: |
| 31k | best measured brief rate | ~360M |
| 84k | bar for a new pool (tries = 0) | ~975M |
| 107k | batch 2 rate | ~1.24B |

| Wave | Counted | Tokens at 84k, 95 % ❓ |
| --- | ---: | ---: |
| W0 | 0 | ~18M |
| W1 | ~860 | ~69M |
| W2 | ~840 | ~67M |
| W3 | ~2,800 | ~223M |
| W4 | ~1,390 | ~111M |
| W5 | ~1,820 | ~146M |
| W6 | ~460 | ~37M |
| W7 | ~3,370 | ~269M |
| W8 | ~640 | ~51M |
| Total | | ~990M |

- One 10 % step (1,285 MATCH) at 84k: about 108M.

## 9. Risks

| Risk | Effect | Action |
| --- | --- | --- |
| Unity build codegen | Per-file TUs can give other inlining or COMDAT order | Pilot in card `0d` before W1 |
| LTCG link RAM and time | Slots run out of RAM; gates take minutes | Measure in `0d`; set E7; fewer parallel GameDaemon builds |
| Disk | Disk guard stops builds | Clean card dirs; watch free space each wave |
| Stub callers fold | Callers stay DIFF until callees are lifted | Wave order callees first |
| Shared BloodLib differs | A GameDaemon fix can break another exe | Card gate: no lost MATCH in all exes; `lift_common_gd` for GameDaemon-only forms |
| `types.h` size | pdb2h output is very large; slow compile | Split per area if the pilot shows a problem ❓ |
| 381 packet layout differs from 2019 + PDB | Wrong client behaviour | Packets follow 381; mark gaps with ❓ |
| Large files (task.cpp 570) | Serial cards | Part files by RVA range |
| Token cost | ~1B tokens to 95 % | Report tokens per MATCH each wave; stall rule |
