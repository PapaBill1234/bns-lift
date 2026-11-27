# lift-gamedaemon-0b: plan the GameDaemon lift cards (W1 and W2 first)

You are a planner card. You do not lift code. You write cards and queue rows.

| Item | Value |
| --- | --- |
| Source build | GameDaemon 2019 + PDB (VS2010 SP1) |
| Exe / PDB | `<work-root>/ida/lift/GameDaemon/GameDaemon.exe`, `.pdb` (read only) |
| Pseudocode | `~/.cache/bns-lift/hr/GameDaemon/<stem>.c` (card 0a; one file per source file, part files above 120 counted functions) |
| Pseudocode index | `~/.cache/bns-lift/hr/GameDaemon/index.tsv` (module, rva, name, first, last, status, source file, part) and `files.tsv` |
| Measured data | `<scratch>/s4/measure/` (`GameDaemon.counted.json`, `GameDaemon.src.json`, `gdfiles.json`), scripts `<scratch>/s4/scripts/` (`waves.py` = wave map of the plan agent) |
| Plan | `Docs/Plan/gamedaemon-lift.md` (sections 1 to 5) |
| Base | branch `tools-gamedaemon-0a` of `<scratch>/gap/clone-gd0a` |
| Wave | 0 |
| Model | opus:high |

`<work-root>` = the private work directory. `<scratch>` = a scratch directory outside the repo.

## Read first

- `Docs/Plan/gamedaemon-lift.md` (all). Sections 1 (anti-cheat), 3 (wave order) and 5 (card size) are the rules.
- `Docs/Plan/cards/lift-infogatedaemon-plan.md` (planner format) and `Docs/Plan/cards/lift-lobbydaemon-1.md` (wave card format).
- `Docs/Parity/README.md` "Model per card".
- Grep, do not read in full: `Docs/Parity/lessons.md`, big pseudocode files, `index.tsv`.

## Tasks

1. Make a scratch clone on the 0a branch:
   ```bash
   git clone --no-hardlinks <scratch>/gap/clone-gd0a <scratch>/gap/clone-gd0b
   cd <scratch>/gap/clone-gd0b && git remote set-url --push origin no_push
   git checkout -b lift-gamedaemon-0b origin/tools-gamedaemon-0a
   ```
2. Classify each of the 12,851 counted functions (write a script; keep it in `<scratch>/s4/scripts/plan_gd.py`, run it with `python3 -I`):
   - `shared-match`: the same PDB name is MATCH in every lifted exe that has it (`Docs/Parity/baseline/<Exe>.json`). No card. The skeleton links the shared source.
   - `shared-diff`: shared, but not MATCH in every exe. W1 card scope.
   - `anticheat`: section 1 of the plan (vendor libraries: no card, no link; glue and TencentProtect: off body in the skeleton, no card).
   - `new`: all others. Wave from the plan wave map (`waves.py`, section 3).
3. Group the W1 and W2 functions into cards:
   - 20 to 40 real functions per card (no EH funclets, no scalar deleting destructors). At most 2,500 pseudocode lines (`last - first + 1` in `index.tsv`).
   - Group by output file stem (`index.tsv` column 1). A card holds whole stems: one large stem, or 2 to 4 small stems of one area. No stem is in two cards of one wave.
   - Callees before callers inside a wave when the order is clear.
   - Each card names one pattern file: a matched LobbyDaemon (or other lifted exe) source file with the same role. Write "Pattern: none" only if no file fits.
   - Model per card: `opus` for reversing; `sonnet:high` only for a known fix pattern. Never xhigh or max.
4. Write each W1 and W2 card as `Docs/Plan/cards/lift-gamedaemon-N.md` (N = 1, 2, ... in queue order). Format: `lift-lobbydaemon-1.md`, plus these rows, so that the card author driver can read it after the engine change:
   - Table row `| Exe | GD |` and `| Depends on | <ids or -> |`.
   - A scope table with one row per function: `| n | GD | \`0xRVA\` | \`PDB name\` | <stem> | <lines> |`.
   - "Files": the lift source files the card edits (`src/Server/GameDaemon/<stem>.cpp` and `.h`, or the shared path for `shared-diff` items).
5. Write the queue `Docs/Plan/cards/lift-gamedaemon-plan.tsv`. Use the 9 columns of `lift-infogatedaemon-plan.md` (id, kind, model, crate, paths, deps, turns, status, title) and add a 10th column `wave` (`W1` ... `W8`). Rows: all W1 and W2 cards with status `ready`. Then one row per planned W3 to W8 card with status `planned` if your token budget allows (stems and counts only; no card file). Else write one row per later wave: `lift-gamedaemon-plan-w3` (planner) and so on.
6. Write `<scratch>/s4/cards/plan.json` (not in the repo): `{card id: {wave, model, deps, stems: [...], ids: [[rva hex, name], ...], lines, pattern}}`. The lead uses it.
7. Write a summary table at the top of the queue section in `Docs/Plan/gamedaemon-lift.md` section 3: measured counts per wave (from step 2) and card counts. Replace the ❓ estimates of W1 and W2 with the measured numbers.
8. Check: each W1/W2 function is in exactly one card; no stem is in two cards of one wave; each card has at most 2,500 lines. Print the check result.
9. Commit (author and committer `Claude <noreply@anthropic.com>`, `git commit --no-verify`, no Co-Authored-By). Copy this card to `Docs/Plan/cards/lift-gamedaemon-0b.md` (private paths → `<work-root>` / `<lift-root>`). Do not push. Do not land.

## Rules

- bns-lift is PUBLIC. No binary, PDB, IDA database, pseudocode, key, abuse note or anti-cheat internals. PDB names only. Mention no other repo.
- Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
- No build is necessary.
- Write all text in ASD-STE100. Sizes in tokens.
- Keep context lean. Do the counting in scripts. Print summaries only.

## Done when

- `Docs/Plan/cards/lift-gamedaemon-plan.tsv` exists. W1 and W2 card files exist. `plan.json` exists. The checks of step 8 pass.

## Report (final message, at most 300 words)

Commit SHA; counts per class (shared-match, shared-diff, anticheat, new); W1 and W2: functions, cards, lines; later waves: rows written or planner rows; check result; problems.
