# Parity phase (2026-11-17)

## Goal
The 4 lifted exes compile to the same code as the original 2019 + PDB exes. The target is **90 % parity** for each exe.

After each exe has 90 % or more, do 1 more round of cards (the "90+ round"). This round fixes the DIFF functions that are left and that have a fixable cause. The review after the 90+ round ends the parity phase. It writes no new cards.

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
