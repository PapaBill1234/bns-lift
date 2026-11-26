# lift-parity-review-5: parity review: measure, merge the lessons, plan the next round

Repo: bns-lift (PUBLIC). Never commit binaries, PDBs, IDA databases or abuse notes. IDA only when the pseudocode and funcdiff are not enough. Close the database when you are done.

## Goal
We know what worked in round 5. The next round is queued (an exe is below 95 %, or a 90+ round), or the handoff gives the reason for the stop.

## Facts
- Read `Docs/Parity/README.md` first. Read `Docs/Parity/review-4.md`, `Docs/Parity/lessons.md` and `Docs/Parity/rules-proposal.md`.
- Scope: CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon. LobbyDaemon is done by another system: write no LobbyDaemon cards,
  do not change its columns in `progress.tsv`, and do not merge the `ld-*` sections of `lessons.md`. Its MATCH must not drop.
- `Docs/Parity/excluded.tsv` stays as it is.
- Main at review 4: CG 456/491 (92.9 %), LG 658/739 (89.0 %), SCD 630/669 (94.2 %), POD 694/759 (91.4 %). Goal 95 %: CG 467, LG 703, SCD 636, POD 722.
- Round 5 cards (built in parallel, disjoint files, all `opus` medium): shared-5, lg-5a, lg-5b, pod-5a, pod-5b, cgscd-5.
  Read the handoffs `Docs/Plan/handoffs/lift-parity-*-5.md`. Use their `Turns:` lines for the turn cost.
- Round 5 is the first wave on Opus 5.5 medium for every card. Give the MATCH per 100 turns of each card and of the round.
  Compare with round 4 (116 MATCH, about 907 turns, 12.8 MATCH per 100 turns; review-4 section 4).
- The round-5 cards write their lessons in the handoff (section `## Lessons`), not in `lessons.md`. Merge them into A, B and D.
- If manual work came after round 5 (rows in `progress.tsv` that are not round 5 cards), count it as its own row.
- Queue file: `Docs/Plan/queue/lift-parity-review-5.tsv` (columns: id, kind, model, crate, paths, deps, turns, status, title; kind `lift`, crate `-`,
  turns `150`, status `ready`, ids start with `lift-parity-`).

## Tasks
1. Run `tools/gate.sh` and `tools/parity.sh`. Write the parity of each exe and the change since review 4.
2. Write `Docs/Parity/review-5.md`: what worked (with counts), what did not work, the turn cost of each card, the DIFF functions that are left by cause class.
   Compare the gain of each card with the estimate of review-4 section 6.
3. Merge the handoff lessons into `Docs/Parity/lessons.md`. Keep the numbers stable. Give the mapping in the header.
4. Apply the stall check of `Docs/Parity/README.md` to each exe with a gain below 2 % in round 5.
5. If an exe is below 95 %: write the next cards (`lift-parity-<name>-6.md`) with disjoint files, named function lists and the lessons sections.
   Split a card with more than about 30 functions. Add `lift-parity-review-6` as the last card.
6. If each exe has 95 % or more: apply the 90+ rule (README, Goal). Write `Docs/Parity/plus-state.tsv` and the 90+ cards, or give the stop reason in the handoff.
7. Run `tools/parity_shared.py --list`. Write the shared library parity and its change since review 4 in the handoff.

## Files
- `Docs/Parity/` (not `baseline/`, `progress.tsv`, `excluded.tsv`)
- `Docs/Plan/queue/lift-parity-review-5.tsv`
- `Docs/Plan/cards/`
- `Docs/Plan/handoffs/lift-parity-review-5.md`

## Done when
- `Docs/Parity/review-5.md` exists.
- The next round is queued, or the handoff gives the reason for the stop.
