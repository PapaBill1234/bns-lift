# lift-parity-review-2: handoff

## Done
- `tools/gate.sh` ok. `tools/parity.sh` ok (MATCH -> DIFF 0). No source change in this card.
- `Docs/Parity/review-2.md` (new): measure, what worked, what did not work, turn cost, DIFF by cause class, round 3 plan.
- `Docs/Parity/lessons.md` cleaned and sorted (A1 to A17). `Docs/Parity/rules-proposal.md`: A refs renumbered, M5 corrected, section 4 (N1 to N12).
- Round 3: 9 cards in `Docs/Plan/cards/` and rows in `Docs/Plan/queue/lift-parity-review-2.tsv`.

## State of each exe (all below 90 %: round 3 queued, no 90+ round, no `plus-state.tsv`)
| Exe | Review 1 | Review 2 | Change |
| --- | --- | --- | --- |
| CG | 387/491 (78.8 %) | 420/491 (85.5 %) | +33 |
| LG | 487/739 (65.9 %) | 530/739 (71.7 %) | +43 |
| SCD | 461/669 (68.9 %) | 510/669 (76.2 %) | +49 |
| POD | 509/759 (67.1 %) | 588/759 (77.5 %) | +79 |
| Shared | 369/489 (75.5 %) | 421/499 (84.4 %) | +52, 78 DIFF |

## Shared DIFF by cause (entries in 2 or more exes, review-2 section 5)
Constants only 79, refs 37, other callee 30, call order 29, orig calls more 29, ours calls more 13, path literal 6, call count 2.
Shared cards first: perexe-3, cryptolib-3, inline-3, order-3, consts-3. Then arraynew-3, handlers-3, dbbind-3, review-3.

Turn cost round 2: about 580 turns for 204 MATCH (2.8 turns per MATCH), review-2 section 4.
## ❓
- Model rule "a fix round 2 or later of a Sonnet card uses opus": read as a re-run of the same card after a fail, not as round 3 cards.
- cryptolib-3 size is not measured. The card tells the session to split the work if it needs more than 150 turns.
- review-3 uses `opus:high` because it writes `rules-proposal.md` (README model table, area 2).

Blocked: none.
Turns: 26
