# lift-gamedaemon-30: Packet game log: gamelog_4 part 3/5

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
| Depends on | `lift-gamedaemon-12`, `lift-gamedaemon-13`, `lift-gamedaemon-29` |
| Pattern | `src/Server/GameDaemon/gamelog_1.cpp` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: `src/Server/GameDaemon/gamelog_1.cpp`. Read it one time. Use its form for the functions of this card.
  The pattern is the output of `lift-gamedaemon-13`. Use the same form for each function: the functions in this group have one layout.
- Dead-strip: `wmain` and most callers are still `LIFT_STUB` bodies. `/OPT:REF` removes a lifted function that has no live caller, and funcdiff then cannot pair it. For each function in scope with no live caller, add `#pragma comment(linker, "/INCLUDE:<public name>")` in its `.cpp` (public names: `llvm-pdbutil dump -publics`; grep `/INCLUDE` in `Docs/Parity/lessons.md`). Do not add a pragma for a function that a lifted caller keeps.

## Scope

23 functions, about 2,449 pseudocode lines (about 19,592 tokens). Stems: `gamelog_4`.

This card is part 3/5 of stem `gamelog_4`. The other parts are in other cards of this wave. They run one after the other (column "Depends on"). Edit only the functions in this table.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x448700` | `GameLog::UseGatheringItem` | gamelog_4 | 102 |
| 2 | GD | `0x448ab0` | `GameLog::CompleteGatheringItem` | gamelog_4 | 102 |
| 3 | GD | `0x448e60` | `GameLog::GetGatheringItem` | gamelog_4 | 103 |
| 4 | GD | `0x449220` | `GameLog::DisposeGatheringItem` | gamelog_4 | 101 |
| 5 | GD | `0x4495c0` | `GameLog::SpendReceiveCost` | gamelog_4 | 103 |
| 6 | GD | `0x449970` | `GameLog::ExpireEventItem` | gamelog_4 | 102 |
| 7 | GD | `0x449d20` | `GameLog::ReceiveEventItemTry` | gamelog_4 | 102 |
| 8 | GD | `0x44a0d0` | `GameLog::GetSummoned` | gamelog_4 | 103 |
| 9 | GD | `0x44a520` | `GameLog::ConsumeItemByChangeSummonedName` | gamelog_4 | 104 |
| 10 | GD | `0x44a8e0` | `GameLog::AcquireSkill` | gamelog_4 | 104 |
| 11 | GD | `0x44aca0` | `GameLog::CastSkill` | gamelog_4 | 121 |
| 12 | GD | `0x44b210` | `GameLog::LearnTraining` | gamelog_4 | 105 |
| 13 | GD | `0x44b5f0` | `GameLog::AddTrainingPage` | gamelog_4 | 106 |
| 14 | GD | `0x44b9c0` | `GameLog::ChangeTrainingPage` | gamelog_4 | 102 |
| 15 | GD | `0x44bd70` | `GameLog::SkillHit` | gamelog_4 | 117 |
| 16 | GD | `0x44c2b0` | `GameLog::AcquireQuest` | gamelog_4 | 118 |
| 17 | GD | `0x44c700` | `GameLog::ProgressMission` | gamelog_4 | 120 |
| 18 | GD | `0x44cb40` | `GameLog::CompleteMissionStep` | gamelog_4 | 106 |
| 19 | GD | `0x44cf10` | `GameLog::CompleteQuest` | gamelog_4 | 108 |
| 20 | GD | `0x44d310` | `GameLog::DisposeQuest` | gamelog_4 | 104 |
| 21 | GD | `0x44d6d0` | `GameLog::GetQuestItem` | gamelog_4 | 109 |
| 22 | GD | `0x44db20` | `GameLog::SystemDeleteQuestItem` | gamelog_4 | 104 |
| 23 | GD | `0x44def0` | `GameLog::GetQuestSkill` | gamelog_4 | 103 |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/gamelog_4.cpp`
- `src/Server/GameDaemon/gamelog_4.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-30.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
