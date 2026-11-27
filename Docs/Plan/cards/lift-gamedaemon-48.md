# lift-gamedaemon-48: DataReader: questtableimpl_cpp part 1/2

| Item | Value |
| --- | --- |
| Exe | GD |
| Source build | GameDaemon 2019 + PDB (VS2010 SP1) |
| Exe file | `<work-root>/ida/lift/GameDaemon/GameDaemon.exe` |
| PDB | `<work-root>/ida/lift/GameDaemon/GameDaemon.pdb` |
| Pseudocode | `~/.cache/bns-lift/hr/GameDaemon/<stem>.c` |
| Pseudocode index | `~/.cache/bns-lift/hr/GameDaemon/index.tsv` (stem, rva, name, first, last, status, source file, part) |
| Wave | W2 |
| Model | opus |
| Depends on | `lift-gamedaemon-e14`, `lift-gamedaemon-52` |
| Pattern | `src/library/FsdReader/FsdDecomposer.cpp` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: `src/library/FsdReader/FsdDecomposer.cpp`. Read it one time. Use its form for the functions of this card.

## Scope

7 functions, about 851 pseudocode lines (about 6,808 tokens). Stems: `questtableimpl_cpp`.

The easy functions of this stem are in `lift-gamedaemon-e14`. Do not change them unless a fix needs it.

This card is part 1/2 of stem `questtableimpl_cpp`. The other parts are in other cards of this wave. They run one after the other (column "Depends on"). Edit only the functions in this table.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x6f7440` | `QuestTableImpl::loadFilterSet` | questtableimpl_cpp | 97 |
| 2 | GD | `0x6f76b0` | `QuestTableImpl::loadReactionSet` | questtableimpl_cpp | 97 |
| 3 | GD | `0x6f7920` | `QuestTableImpl::loadCase` | questtableimpl_cpp | 153 |
| 4 | GD | `0x6f7c00` | `QuestTableImpl::loadMissionStepFail` | questtableimpl_cpp | 192 |
| 5 | GD | `0x6f7f20` | `QuestTableImpl::loadCompletion` | questtableimpl_cpp | 104 |
| 6 | GD | `0x6f8130` | `QuestTableImpl::loadTransit` | questtableimpl_cpp | 165 |
| 7 | GD | `0x6f83d0` | `QuestTableImpl::allocQuestRewardContents` | questtableimpl_cpp | 43 |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/questtableimpl_cpp.cpp`
- `src/Server/GameDaemon/questtableimpl_cpp.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-48.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
