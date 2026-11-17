# lift-parity-review-1: parity review: measure, write the lessons, plan the next round

Repo: bns-lift (PRIVATE). IDA only when the pseudocode and funcdiff are not enough (`/home/ubuntu/Documents/Codex/private-project/ida/lift/CacheGate/CacheGate.exe`).

## Goal
We know what works. The next round of parity cards is queued if an exe is below 90 %. The lift rules for GameDaemon have the lessons.

## Facts
- Read `Docs/Parity/README.md` first. It has the goal, the parity definition, the commands and the rules.
- Read `Docs/Parity/triage.md` and `Docs/Parity/lessons.md` if they exist.
- The runner gate runs `tools/gate.sh` and then `tools/parity.sh`. The gate fails if an exe loses a MATCH function.
- Run `tools/gate.sh` and then `tools/parity.sh` yourself before you stop. One parity run takes about 2 to 10 minutes.
- Pseudocode of the original exes: `~/.cache/bns-lift/hr/<EXE>/` for CacheGate, LobbyGate, SmartCouponDaemon and PostOfficeDaemon.
- `Docs/Parity/progress.tsv` has one row per accepted card.
- The runner adds the rows of `Docs/Plan/queue/lift-parity-review-1.tsv` to the queue after this card. The columns are: id, kind, model, crate, paths, deps, turns, status, title. Use kind `lift`, model `opus`, crate `-`, turns `150`, status `ready`. Each id must start with `lift-parity-`.
- Read the handoffs `Docs/Plan/handoffs/lift-parity-*.md`.
- An older review lists behaviour differences that a past port of SmartCouponDaemon missed: `/home/ubuntu/Documents/Codex/private-project/bns-server/Docs/Reviews/rev-small-348.md` (about 7k tokens). Read only sections 2, 3 and 5 (lines 64-125 and 185-219). The review calls the 2019 + PDB build "348". It is about a Rust port, not this lift. Use it for miss classes only. Do not copy Rust paths or code.

## Tasks
1. Run `tools/gate.sh` and `tools/parity.sh`. Write the parity of each exe and the change since the start.
2. Write `Docs/Parity/review-1.md`: what worked (with counts), what did not work, the turn cost of each card if the handoffs give it, and the DIFF functions that are left, by cause class.
3. Clean `Docs/Parity/lessons.md`: merge equal patterns, sort by the number of functions fixed.
4. Write `Docs/Parity/rules-proposal.md`: the changes to the lift rules and the lift method that would prevent each miss class in a new lift (for GameDaemon). Write each change as a rule in ASD-STE100 with the reason.
   Add a section "Behaviour misses (rev-small-348)". For each miss class in that review (for example: SQL store, NP transport, request decoding, packet widths), write if funcdiff parity can find it. If it cannot, propose a check that can (runtime test, packet log, layout check), and say which lift step must run it.
5. If an exe is below 90 %: write the next cards (`Docs/Plan/cards/lift-parity-<name>-2.md` and so on) in the same form as the cards of round 1. Group the work by cause, not by exe, where a cause is in more than one exe. Add `lift-parity-review-2` as the last card. Write the rows in `Docs/Plan/queue/lift-parity-review-1.tsv`.
6. If each exe has 90 % or more: write the 90+ round (see `Docs/Parity/README.md`, Goal). Write 1 card for each cause class of the DIFF functions that are left and that have a fixable cause (`lift-parity-plus-<cause>.md`). Add `lift-parity-review-plus` as the last card. That review ends the parity phase and writes no new cards.
7. Each later review (`lift-parity-review-2` and on) uses tasks 5 and 6 of this card in the same way.

## Files
- `Docs/Parity/`
- `Docs/Plan/queue/`
- `Docs/Plan/cards/`
- `Docs/Plan/handoffs/lift-parity-review-1.md`

## Done when
- `Docs/Parity/review-1.md` and `Docs/Parity/rules-proposal.md` exist.
- The next round is queued: a round to 90 %, or the 90+ round.
