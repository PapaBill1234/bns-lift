# lift-gamedaemon-26: Packet game log: gamelog_3 part 4/5

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
| Depends on | `lift-gamedaemon-12`, `lift-gamedaemon-13`, `lift-gamedaemon-25` |
| Pattern | `src/Server/GameDaemon/gamelog_1.cpp` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: `src/Server/GameDaemon/gamelog_1.cpp`. Read it one time. Use its form for the functions of this card.
  The pattern is the output of `lift-gamedaemon-13`. Use the same form for each function: the functions in this group have one layout.

## Scope

15 functions, about 1,583 pseudocode lines (about 12,664 tokens). Stems: `gamelog_3`.

This card is part 4/5 of stem `gamelog_3`. The other parts are in other cards of this wave. They run one after the other (column "Depends on"). Edit only the functions in this table.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x435d40` | `GameLog::FishingStart` | gamelog_3 | 103 |
| 2 | GD | `0x436100` | `GameLog::FishingEnd` | gamelog_3 | 109 |
| 3 | GD | `0x436500` | `GameLog::FishingCancel` | gamelog_3 | 103 |
| 4 | GD | `0x4368c0` | `GameLog::ContentQuotaRecovery` | gamelog_3 | 101 |
| 5 | GD | `0x436c70` | `GameLog::FastGrowthRewardItem` | gamelog_3 | 105 |
| 6 | GD | `0x437030` | `GameLog::ChangeMentoringRole` | gamelog_3 | 102 |
| 7 | GD | `0x4373e0` | `GameLog::GraduatedMentoring` | gamelog_3 | 104 |
| 8 | GD | `0x437890` | `GameLog::SalesLimitExceed` | gamelog_3 | 101 |
| 9 | GD | `0x437c30` | `GameLog::LootItem` | gamelog_3 | 107 |
| 10 | GD | `0x438020` | `GameLog::DestroyItem` | gamelog_3 | 116 |
| 11 | GD | `0x4384c0` | `GameLog::MasterLooterResult` | gamelog_3 | 113 |
| 12 | GD | `0x4389d0` | `GameLog::MainFactionCoinDisappear` | gamelog_3 | 101 |
| 13 | GD | `0x438d70` | `GameLog::UseItemByGetPouch` | gamelog_3 | 103 |
| 14 | GD | `0x439130` | `GameLog::EquipItem` | gamelog_3 | 107 |
| 15 | GD | `0x439510` | `GameLog::UnEquipItem` | gamelog_3 | 108 |

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

Write `Docs/Plan/handoffs/lift-gamedaemon-26.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
