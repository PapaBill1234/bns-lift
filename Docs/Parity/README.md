# Parity phase (2026-11-17)

## Goal
The 4 lifted exes compile to the same code as the original 2019 + PDB exes. | Level | Parity per exe | Meaning |
| --- | ---: | --- |
| Checkpoint | 90 % | End of the base rounds. Then the 90+ rounds start. |
| Goal | **95 %** | Minimum result for the phase. |
| Preferred | **99 %** | Target of the 90+ rounds. |
| Shared library | **99 %** preferred | Functions that 2 or more exes have (BloodLib, Shared, Packet, CRT). A shared function is MATCH only if it is MATCH in each exe. Measure: `tools/parity_shared.py` (`--list` gives the DIFF functions). |

The parity table in the top `README.md` is written by `tools/parity_readme.py`. `tools/parity.sh --accept` runs it after each accepted card. Cards do not edit that table.

Shared library cards come first in each round. One fix in shared code helps each exe and later GameDaemon. Start (after `lift-parity-s3`): 354/478 = 74.1 %.

After each exe has 90 % or more, do "90+ rounds". The 90+ target is **99 % parity** for each exe. Each 90+ round fixes the DIFF functions that are left and that have a fixable cause. Its last card is a review.

The review after each 90+ round sets the state of each exe in `Docs/Parity/plus-state.tsv` (columns: exe, round, parity, gain, zero_rounds, state). `zero_rounds` counts the rounds in sequence with no gain.

| Exe result in the last round | Action |
| --- | --- |
| Parity 99 % or more | State `done`. Write no more cards for this exe. |
| Shared library below 99 % | Row `shared` in `plus-state.tsv`. Same stall rule as an exe. Shared cards come before exe cards. |
| Gain more than 0 | Set `zero_rounds` to 0. Write cards for the fixable DIFF functions that are left. |
| No gain, first time (`zero_rounds` = 1) | Find the cause of the stall. Write it in the review. Write a card that fixes the cause. |
| No gain, second time (`zero_rounds` = 2) | Do the check again. Find what the first fix did not solve. Write a card that fixes it. |
| No gain, third time (`zero_rounds` = 3) | State `stopped`. Write no more cards for this exe. Write the cause in the handoff. If parity is below 95 %, write "BELOW GOAL" at the top of the handoff with the cause and the options that are left. |

A card for a cause in more than 1 exe stays 1 card. An exe with state `done` or `stopped` gets no new cards, but the gate still runs on it. It must not lose MATCH functions.
The parity phase stops when each exe has state `done` or `stopped`. There is no limit on the number of rounds.
When the phase stops, the review writes no new cards. The handoff gives the parity of each exe and the reason for the stop.

| Exe | Start parity |
| --- | --- |
| CacheGate | 216 / 491 = 44.0 % |
| LobbyGate | 280 / 739 = 37.9 % |
| SmartCouponDaemon | 225 / 669 = 33.6 % |
| PostOfficeDaemon | 262 / 759 = 34.5 % |

No new daemon work starts before the 4 exes reach the target. This phase is a test ground for GameDaemon. Write each lesson in `lessons.md`.

## Definition
- Parity % = MATCH / (paired functions + functions only in the original).
- MATCH = the calls, the data refs and the constants of a function are equal (`tools/funcdiff.py`).
- MATCH-B (exact) = a MATCH function whose ordered instruction stream is also equal to the original. Registers, immediates, memory forms, order and branch sense must be equal. Relocation targets compare by name. This is the `full` level of the parity engine strict compare (the only definition). MATCH stays the progress signal; MATCH-B shows how much of it is exact code. The runner gives the strict data of the build to `tools/parity.sh --accept` (env `PARITY_STRICT`). The accept writes `"exact": true|false` into each MATCH row of `baseline/` and `exact N` into the `progress.tsv` cell. The README table shows it in the column Exact. Manual report: `tools/parity_exact.py`. The engine refuses a card that makes a baseline MATCH lose a strict level, and gives automatic credit only with strict `full` and `cfg` (other new MATCH go to review).
- A function that the original has and our exe does not have counts as a miss. Inlined code is a miss when the original did not inline it.
- EXCLUDED = funcdiff says MATCH, but a review rejected the function and the operator excluded it (no honest source fix). An excluded function is not a MATCH. It gets no credit and does not count in parity %. The list is `excluded.tsv` (columns: exe, symbol, reason, card, proof_digest). `tools/parity.sh --accept` writes it into `baseline/` with status `EXCLUDED`. `progress.tsv` and the README table show MATCH without it and a separate excluded count. An old baseline with status `MATCH` for a listed symbol is read as `EXCLUDED`.

## Measure
```
tools/gate.sh            # clang build in build/ (build.sh needs build/build.ninja)
tools/parity.sh          # VS2010 /GL /LTCG build, funcdiff, compare with Docs/Parity/baseline/
```

```
src ──► tools/gate.sh (clang) ──► build/build.ninja ──► tools/vs2010/build.sh ──► build-vs2010/<EXE>.exe
                                                                                       │
          Docs/Parity/baseline/<EXE>.json ◄── runner --accept ◄── tools/parity.sh ◄── funcdiff vs ida/lift/<EXE>/
```

- One function: `uv run -q --no-project --with capstone --with pefile python tools/funcdiff.py <EXE> --build build-vs2010 --show '<regex>'`. It prints the call, ref and const diff.
- Results of the last run: `build-vs2010/<EXE>.funcdiff.json` and `.funcdiff.txt`.
- Pseudocode of the original: `~/.cache/bns-lift/hr/<EXE>/` (`index.tsv`, one `.c` per PDB module).
- Progress: `progress.tsv` (one row per accepted card).

## Model per card
The queue column `model` takes `opus:high`, `opus`, `sonnet:high` or `sonnet:medium`. The runner gives `--model` and `--effort` to the session. Plain `opus` = effort medium. A fix round 2 or later of a Sonnet card uses `opus`. An `opus:high` card keeps high effort.

| Model | Use it for |
| --- | --- |
| `opus:high` | Only these 4 areas. An error here goes into many later cards or stops an exe below its goal: (1) the second stall check of an exe (the last check before `stopped`); (2) a review that writes `rules-proposal.md` (rules for the GameDaemon lift); (3) a lift plan card for a new exe; (4) bug and exploit judgement (fix or port, see the no-bug-port rule) |
| `opus` | Complex code reversing, IDA work, plans, specs, rules, bug and exploit judgement, parity reviews, stall checks, DIFF functions with no known cause |
| `sonnet:high` | Apply a known fix pattern to named functions, Rust from a spec, gate and build errors, helper scripts (IDAPython, Diaphora, funcdiff), tests |
| `sonnet:medium` | Docs and README updates, ASD-STE100 rewrites, notes tidying, card files after a review named the causes, rules-proposal text into the lift rules, log summaries |

Cost: high uses about 1.4× the tokens of medium. Do not use `xhigh` or `max`. Check after the first 2 `opus:high` stall checks: did each name a cause that a later card fixed? If not, use `opus` again.

## Rules
| Rule | Why |
| --- | --- |
| Never change `baseline/` or `progress.tsv`. The runner changes them. | The gate compares with the committed baseline. |
| No exe may lose MATCH functions. | Shared code is in all 4 exes. A fix for one exe can break another. |
| A MATCH → DIFF change needs a line in `allow-worse.txt`: `<EXE> <function> \| <reason>`. | Only when a shared fix wins more than it loses. Give the counts. |
| Cards never edit `excluded.tsv`. The lander adds a row only with an operator exclude receipt (engine `integrate.py exclude`) and its proof digest. | An exclude must be on record. It must never raise MATCH. |
| Change `tools/funcdiff.py` only in a tooling card. Prove each normalization in `noise.md`. | A looser tool hides real differences. |
| Keep the original logic. Change only the source form: inline or not, the header or the `.cpp`, the order of calls, the types, the STL call. | Parity of the code, not new behaviour. |
| Write each fix pattern in `lessons.md` with one example (function, before, after). | The GameDaemon lift uses these patterns. |
