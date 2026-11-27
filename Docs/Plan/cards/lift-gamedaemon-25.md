# lift-gamedaemon-25: Packet game log: gamelog_3 part 3/5

| Item | Value |
| --- | --- |
| Exe | GD |
| Source build | GameDaemon 2019 + PDB (VS2010 SP1) |
| Exe file | `<work-root>/ida/lift/GameDaemon/GameDaemon.exe` |
| PDB | `<work-root>/ida/lift/GameDaemon/GameDaemon.pdb` |
| Pseudocode | `~/.cache/bns-lift/hr/GameDaemon/<stem>.c` |
| Pseudocode index | `~/.cache/bns-lift/hr/GameDaemon/index.tsv` (stem, rva, name, first, last, status, source file, part) |
| Wave | W1 |
| Model | sonnet:high |
| Depends on | `lift-gamedaemon-12`, `lift-gamedaemon-13`, `lift-gamedaemon-24` |
| Pattern | `src/Server/GameDaemon/gamelog_1.cpp` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: `src/Server/GameDaemon/gamelog_1.cpp`. Read it one time. Use its form for the functions of this card.
  The pattern is the output of `lift-gamedaemon-13`. Use the same form for each function: the functions in this group have one layout.

## Scope

23 functions, about 2,398 pseudocode lines (about 19,184 tokens). Stems: `gamelog_3`.

This card is part 3/5 of stem `gamelog_3`. The other parts are in other cards of this wave. They run one after the other (column "Depends on"). Edit only the functions in this table.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x34e8b0` | `GameLog::BOTScoreChange` | gamelog_3 | 105 |
| 2 | GD | `0x34ec70` | `GameLog::TraceRoute` | gamelog_3 | 87 |
| 3 | GD | `0x430820` | `GameLog::EnterWorld` | gamelog_3 | 112 |
| 4 | GD | `0x430c60` | `GameLog::LeaveWorld` | gamelog_3 | 113 |
| 5 | GD | `0x4310c0` | `GameLog::EnterZone` | gamelog_3 | 104 |
| 6 | GD | `0x4314a0` | `GameLog::LeaveZone` | gamelog_3 | 105 |
| 7 | GD | `0x4318b0` | `GameLog::Teleport` | gamelog_3 | 101 |
| 8 | GD | `0x431c60` | `GameLog::UseWarpPoint` | gamelog_3 | 101 |
| 9 | GD | `0x432010` | `GameLog::GetAccountExperience` | gamelog_3 | 107 |
| 10 | GD | `0x4323e0` | `GameLog::PcLevelUp` | gamelog_3 | 100 |
| 11 | GD | `0x432780` | `GameLog::GetHeart` | gamelog_3 | 104 |
| 12 | GD | `0x432b40` | `GameLog::UseHeart` | gamelog_3 | 103 |
| 13 | GD | `0x432f00` | `GameLog::Exhaustion` | gamelog_3 | 110 |
| 14 | GD | `0x4333e0` | `GameLog::Die` | gamelog_3 | 111 |
| 15 | GD | `0x4338c0` | `GameLog::Resurrect` | gamelog_3 | 106 |
| 16 | GD | `0x433d60` | `GameLog::CombatStart` | gamelog_3 | 102 |
| 17 | GD | `0x434110` | `GameLog::CombatEnd` | gamelog_3 | 102 |
| 18 | GD | `0x4344c0` | `GameLog::KillPC` | gamelog_3 | 112 |
| 19 | GD | `0x4349d0` | `GameLog::CastSelfRevival` | gamelog_3 | 98 |
| 20 | GD | `0x434d50` | `GameLog::GetMainFactionCoin` | gamelog_3 | 108 |
| 21 | GD | `0x435220` | `GameLog::GetRankingRewardItem` | gamelog_3 | 114 |
| 22 | GD | `0x435640` | `GameLog::DuelBotTrainingRoomRewardItem` | gamelog_3 | 104 |
| 23 | GD | `0x435a10` | `GameLog::ChallengeGetScore` | gamelog_3 | 89 |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/gamelog_3.cpp`
- `src/Server/GameDaemon/gamelog_3.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-25.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
