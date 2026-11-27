# lift-gamedaemon-0b2: easy cards first (owner order)

You are a planner card. You do not lift code. You change the GameDaemon card queue of card 0b.

| Item | Value |
| --- | --- |
| Base | bns-lift main `29150bf` (has card 0b: `Docs/Plan/cards/lift-gamedaemon-plan.tsv`, `lift-gamedaemon-1.md` to `-96.md`) |
| Pseudocode | `~/.cache/bns-lift/hr/GameDaemon/<stem>.c`, `index.tsv` (stem, rva, name, first, last, status, source file, part), `files.tsv` |
| 0b scripts | `<scratch>/s4/scripts/plan_gd.py` (classes, waves, cards), `plan_gd_write.py` (card files, queue). Lead file `<scratch>/s4/cards/plan.json`. |
| Wave | 0 |
| Model | opus:high |

`<work-root>` = the private work directory. `<lift-root>` = the bns-lift checkout. `<scratch>` = a scratch directory outside the repo.

## Owner order (verbatim, 2026-11-27)

"after ur done run it for client.exe and for gamedaemon so we can get all easiest stuff out of the way. make sure to use also remote builds when possible."

Operator rule: in the W1+ queue, put the easiest cards first: small leaf functions, getters, shared code that is MATCH in other exes, high MATCH per token. Hard files wait.

## Why the order matters

The plan orders waves callees first. Reason: a `LIFT_STUB` callee becomes noreturn under LTCG, so a real caller of a stub stays DIFF. A leaf function (no call to another lifted function) does not have this problem. A leaf can MATCH in any wave.

## Tasks

1. Scratch clone of main:
   ```bash
   git clone --no-hardlinks <lift-root> <scratch>/gap/clone-gd0b2
   cd <scratch>/gap/clone-gd0b2 && git remote set-url --push origin no_push
   git fetch <public-remote> main && git checkout -b lift-gamedaemon-0b2 FETCH_HEAD   # must be 29150bf or later
   ```
2. Give each `new` and `shared-diff` function an ease score (script `<scratch>/s4/scripts/ease_gd.py`, `python3 -I`). Use facts you can measure:
   - pseudocode lines (`last - first + 1`);
   - calls to other counted functions in the pseudocode body (0 = leaf); calls to CRT and compiler helpers do not count;
   - simple form: getter, setter, small ctor or dtor, `return` of a member, empty body;
   - shared-diff: the best funcdiff state in another exe (`Docs/Parity/baseline/<Exe>.json`), when the baseline has it.
   Write the rule and the thresholds in the plan file. Keep the rule simple.
3. Make a new wave `E` (easy) before W1. `E` holds the easy functions of all areas (W1 to W8): leaves and simple forms up to a small line limit that you choose from the data. Exclude anticheat functions and the upstream library cards (zstd, zlib, minizip).
   - Group by stem. All easy functions of one stem go into one E card. One E card holds 20 to 40 functions (2,500 lines at most) from 1 or more stems of one area. No stem is in two E cards.
   - Order the E cards: highest expected MATCH per token first (short leaves first). Inside the same ease, callees-first area order (W1 area before W2 area, and so on).
   - Model: `sonnet:high` for E cards of plain getters, setters and empty bodies; `opus` else. Never xhigh or max.
   - E cards depend only on `lift-gamedaemon-0e`, plus a dep chain if two E cards must edit one file.
4. Remove the E functions from the scope of the W1 to W8 cards. Re-make the W1 and W2 card files and the W3 to W8 planned rows with `plan_gd_write.py` (change the scripts; keep the card format of 0b). A W card that becomes empty goes away. A W card of a stem with an E card depends on that E card (same file).
5. Inside W1 and W2: order the cards easy first too, but keep each dep before its user.
6. Queue `Docs/Plan/cards/lift-gamedaemon-plan.tsv`: E rows first (status `ready`), then W1, W2 (`ready`), then W3 to W8 (`planned`). Column 10 = wave (`E`, `W1`, ...). Row order = run order. Card files for all E cards and for W1 and W2. Card ids: keep the old ids of W cards if possible; E cards get ids `lift-gamedaemon-e1`, `-e2`, ....
7. Update `<scratch>/s4/cards/plan.json` (same keys as 0b, plus `ease`).
8. Update `Docs/Plan/gamedaemon-lift.md` section 3: wave E row (functions, cards, lines, tokens), changed W counts, the ease rule. Add the owner order as the source.
9. Checks (print them): each counted non-anticheat, non-shared-match function is in exactly one card; no stem is in two cards of one wave unless the cards are in a dep chain; each card ≤ 2,500 lines except one-function cards and upstream cards; each dep exists and comes earlier in the queue.
10. Commit (author and committer `Claude <noreply@anthropic.com>`, `git commit --no-verify`, no Co-Authored-By). Copy this card to `Docs/Plan/cards/lift-gamedaemon-0b2.md`; replace private paths with `<work-root>` / `<lift-root>`; remove the GitHub URL. Do not push. Do not land.

## Rules

- bns-lift is PUBLIC. No binary, PDB, IDA database, pseudocode, key, abuse note or anti-cheat internals. PDB names only. Mention no other repo.
- Do not open IDA. No build is necessary. Do not edit the engine.
- ASD-STE100. Sizes in tokens. Keep context lean: do the work in scripts, print summaries.

## Done when

- The queue starts with E cards. E, W1 and W2 card files exist. The checks of task 9 pass.

## Report (final message, at most 300 words)

Commit SHA; the ease rule; E: functions, cards, lines, tokens, models; changed W1 to W8 counts; check result; problems.
