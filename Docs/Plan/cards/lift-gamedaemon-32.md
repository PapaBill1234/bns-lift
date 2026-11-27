# lift-gamedaemon-32: Packet game log: gamelog_4 part 5/5

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
| Depends on | `lift-gamedaemon-12`, `lift-gamedaemon-13`, `lift-gamedaemon-31` |
| Pattern | `src/Server/GameDaemon/gamelog_1.cpp` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: `src/Server/GameDaemon/gamelog_1.cpp`. Read it one time. Use its form for the functions of this card.
  The pattern is the output of `lift-gamedaemon-13`. Use the same form for each function: the functions in this group have one layout.

## Scope

14 functions, about 1,390 pseudocode lines (about 11,120 tokens). Stems: `gamelog_4`.

This card is part 5/5 of stem `gamelog_4`. The other parts are in other cards of this wave. They run one after the other (column "Depends on"). Edit only the functions in this table.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x451df0` | `GameLog::KeepFactionCoin` | gamelog_4 | 105 |
| 2 | GD | `0x4521d0` | `GameLog::CompleteRefinement` | gamelog_4 | 88 |
| 3 | GD | `0x452500` | `GameLog::RefinerDeactivating` | gamelog_4 | 87 |
| 4 | GD | `0x452820` | `GameLog::RefinerNeutralization` | gamelog_4 | 87 |
| 5 | GD | `0x452b40` | `GameLog::RequestRefineReward` | gamelog_4 | 103 |
| 6 | GD | `0x452f10` | `GameLog::OpenWarpPoint` | gamelog_4 | 86 |
| 7 | GD | `0x453220` | `GameLog::CloseWarpPoint` | gamelog_4 | 85 |
| 8 | GD | `0x6743e0` | `GameLog::ZoneTriggerEvent` | gamelog_4 | 89 |
| 9 | GD | `0x674710` | `GameLog::ProcessModuleDetection` | gamelog_4 | 113 |
| 10 | GD | `0x674b70` | `GameLog::USBDeviceDetection` | gamelog_4 | 103 |
| 11 | GD | `0x674f50` | `GameLog::ExecAlarmDetection` | gamelog_4 | 104 |
| 12 | GD | `0x675360` | `GameLog::ClientInspectDetection` | gamelog_4 | 108 |
| 13 | GD | `0x675750` | `GameLog::PatchDefenderDetection` | gamelog_4 | 106 |
| 14 | GD | `0x675bb0` | `GameLog::MalwareDetection` | gamelog_4 | 126 |

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

Write `Docs/Plan/handoffs/lift-gamedaemon-32.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
