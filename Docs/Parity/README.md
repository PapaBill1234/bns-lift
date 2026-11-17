# Parity phase (2026-11-17)

## Goal
The 4 lifted exes compile to the same code as the original 2019 + PDB exes. The target is **90 % parity** for each exe.

After each exe has 90 % or more, do "90+ rounds". The 90+ target is **99 % parity** for each exe. Each 90+ round fixes the DIFF functions that are left and that have a fixable cause. Its last card is a review.

The review after each 90+ round sets the state of each exe in `Docs/Parity/plus-state.tsv` (columns: exe, round, parity, gain, zero_rounds, state). `zero_rounds` counts the rounds in sequence with no gain.

| Exe result in the last round | Action |
| --- | --- |
| Parity 99 % or more | State `done`. Write no more cards for this exe. |
| Gain more than 0 | Set `zero_rounds` to 0. Write cards for the fixable DIFF functions that are left. |
| No gain, first time (`zero_rounds` = 1) | Find the cause of the stall. Write it in the review. Write a card that fixes the cause. |
| No gain, second time (`zero_rounds` = 2) | Do the check again. Find what the first fix did not solve. Write a card that fixes it. |
| No gain, third time (`zero_rounds` = 3) | State `stopped`. Write no more cards for this exe. Write the cause in the handoff. |

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
- A function that the original has and our exe does not have counts as a miss. Inlined code is a miss when the original did not inline it.

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

## Rules
| Rule | Why |
| --- | --- |
| Never change `baseline/` or `progress.tsv`. The runner changes them. | The gate compares with the committed baseline. |
| No exe may lose MATCH functions. | Shared code is in all 4 exes. A fix for one exe can break another. |
| A MATCH → DIFF change needs a line in `allow-worse.txt`: `<EXE> <function> \| <reason>`. | Only when a shared fix wins more than it loses. Give the counts. |
| Change `tools/funcdiff.py` only in a tooling card. Prove each normalization in `noise.md`. | A looser tool hides real differences. |
| Keep the original logic. Change only the source form: inline or not, the header or the `.cpp`, the order of calls, the types, the STL call. | Parity of the code, not new behaviour. |
| Write each fix pattern in `lessons.md` with one example (function, before, after). | The GameDaemon lift uses these patterns. |
