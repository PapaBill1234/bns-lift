# lift-parity-review-2: parity review: measure, write the lessons, plan the next round

Repo: bns-lift (PRIVATE). IDA only when the pseudocode and funcdiff are not enough (`<work-root>/ida/lift/CacheGate/CacheGate.exe`).

## Goal
We know what worked in round 2. The next round of parity cards is queued if an exe is below 90 %, or a 90+ round is queued.

## Facts
- Read `Docs/Parity/README.md` first. It has the goal, the parity definition, the commands and the rules.
- Read `Docs/Parity/triage.md`, `Docs/Parity/lessons.md`, `Docs/Parity/review-1.md` and `Docs/Parity/rules-proposal.md`.
- The runner gate runs `tools/gate.sh` and then `tools/parity.sh`. The gate fails if an exe loses a MATCH function.
- Run `tools/gate.sh` and then `tools/parity.sh` yourself before you stop. One parity run takes about 2 to 10 minutes.
- Pseudocode of the original exes: `~/.cache/bns-lift/hr/<EXE>/` for CacheGate, LobbyGate, SmartCouponDaemon and PostOfficeDaemon.
- `Docs/Parity/progress.tsv` has one row per accepted card.
- Parity at review 1: CG 387/491 (78.8 %), LG 487/739 (65.9 %), SCD 461/669 (68.9 %), POD 509/759 (67.1 %), shared 369/489 (75.5 %).
- The runner adds the rows of `Docs/Plan/queue/lift-parity-review-2.tsv` to the queue after this card. The columns are: id, kind, model, crate, paths, deps, turns, status, title. Use kind `lift`, crate `-`, turns `150`, status `ready`. Each id must start with `lift-parity-`. Choose the model of each card by the table "Model per card" in `Docs/Parity/README.md`.
- Read the handoffs `Docs/Plan/handoffs/lift-parity-*-2.md`. Use their `Turns:` lines for the turn cost.

## Tasks
1. Run `tools/gate.sh` and `tools/parity.sh`. Write the parity of each exe and the change since review 1.
2. Write `Docs/Parity/review-2.md`: what worked (with counts), what did not work, the turn cost of each card, and the DIFF functions that are left, by cause class.
3. Clean `Docs/Parity/lessons.md`: merge equal patterns, sort by the number of functions fixed. If a new pattern changes a rule, add the change to `Docs/Parity/rules-proposal.md`.
5. If an exe is below 90 %: write the next cards (`Docs/Plan/cards/lift-parity-<name>-3.md` and so on) in the same form as the cards of round 2. Group the work by cause, not by exe, where a cause is in more than one exe. Add `lift-parity-review-3` as the last card. Write the rows in `Docs/Plan/queue/lift-parity-review-2.tsv`.
6. If each exe has 90 % or more: apply the 90+ rule in `Docs/Parity/README.md` (Goal). Write `Docs/Parity/plus-state.tsv`. Write the cards for the exes with no state `done` or `stopped` (`lift-parity-plus<N>-<cause>.md`, N = 90+ round number). Add `lift-parity-review-plus<N>` as the last card. If each exe has state `done` or `stopped`: write no new cards. Give the reasons in the handoff.
6a. Run `tools/parity_shared.py --list`. Write the shared library parity in the handoff. Group the shared DIFF functions by cause. Write a shared card for each fixable cause and put it before the exe cards. This applies also below 90 %.
7. Each later review (`lift-parity-review-3`, `lift-parity-review-plus<N>`) uses tasks 5 and 6 of this card in the same way. Each review writes the state of each exe in the handoff.

## Files
- `Docs/Parity/`
- `Docs/Plan/queue/`
- `Docs/Plan/cards/`
- `Docs/Plan/handoffs/lift-parity-review-2.md`

## Done when
- `Docs/Parity/review-2.md` exists.
- The next round is queued (a round to 90 % or a 90+ round), or the handoff gives the reason for the stop.
