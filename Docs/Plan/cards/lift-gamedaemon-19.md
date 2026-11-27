# lift-gamedaemon-19: Packet game log: gamelog_2 part 2/5

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
| Depends on | `lift-gamedaemon-12`, `lift-gamedaemon-13`, `lift-gamedaemon-18` |
| Pattern | `src/Server/GameDaemon/gamelog_1.cpp` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: `src/Server/GameDaemon/gamelog_1.cpp`. Read it one time. Use its form for the functions of this card.
  The pattern is the output of `lift-gamedaemon-13`. Use the same form for each function: the functions in this group have one layout.

## Scope

23 functions, about 2,441 pseudocode lines (about 19,528 tokens). Stems: `gamelog_2`.

This card is part 2/5 of stem `gamelog_2`. The other parts are in other cards of this wave. They run one after the other (column "Depends on"). Edit only the functions in this table.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x1784e0` | `GameLog::PublicRaidEventStart` | gamelog_2 | 86 |
| 2 | GD | `0x1787f0` | `GameLog::PublicRaidEventFinish` | gamelog_2 | 87 |
| 3 | GD | `0x178b10` | `GameLog::BoardGachaJoin` | gamelog_2 | 108 |
| 4 | GD | `0x178ef0` | `GameLog::BoardGachaJoinItem` | gamelog_2 | 105 |
| 5 | GD | `0x1792c0` | `GameLog::ReceiveBoardGachaReward` | gamelog_2 | 105 |
| 6 | GD | `0x179690` | `GameLog::DuelTag` | gamelog_2 | 109 |
| 7 | GD | `0x179b60` | `GameLog::DuelInterference` | gamelog_2 | 104 |
| 8 | GD | `0x179f20` | `GameLog::DuelRecordChange` | gamelog_2 | 111 |
| 9 | GD | `0x17a320` | `GameLog::PartyBattleRecordChange` | gamelog_2 | 114 |
| 10 | GD | `0x17a730` | `GameLog::PartyBattleStartTeam` | gamelog_2 | 109 |
| 11 | GD | `0x17ab20` | `GameLog::PartyBattleEndTeam` | gamelog_2 | 116 |
| 12 | GD | `0x17af60` | `GameLog::PartyBattleStartPC` | gamelog_2 | 111 |
| 13 | GD | `0x17b360` | `GameLog::PartyBattleResult` | gamelog_2 | 116 |
| 14 | GD | `0x17b790` | `GameLog::OccupyControlPoint` | gamelog_2 | 110 |
| 15 | GD | `0x17bb90` | `GameLog::PartyBattleDisconnected` | gamelog_2 | 106 |
| 16 | GD | `0x17bf70` | `GameLog::PartyBattleRejoin` | gamelog_2 | 105 |
| 17 | GD | `0x17c350` | `GameLog::PartyBattleMvpVote` | gamelog_2 | 110 |
| 18 | GD | `0x17c860` | `GameLog::CreateBall` | gamelog_2 | 89 |
| 19 | GD | `0x17cb90` | `GameLog::GoalIn` | gamelog_2 | 108 |
| 20 | GD | `0x17cf70` | `GameLog::CostItemToSendPost` | gamelog_2 | 103 |
| 21 | GD | `0x17d330` | `GameLog::SendPostSummary` | gamelog_2 | 110 |
| 22 | GD | `0x17d800` | `GameLog::SendPostItem` | gamelog_2 | 109 |
| 23 | GD | `0x17dcc0` | `GameLog::ReadPost` | gamelog_2 | 110 |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/gamelog_2.cpp`
- `src/Server/GameDaemon/gamelog_2.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-19.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
