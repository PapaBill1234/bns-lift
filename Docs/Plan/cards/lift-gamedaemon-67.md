# lift-gamedaemon-67: DataManager: datamanager_cpp_1 part 1/10

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
| Depends on | `lift-gamedaemon-e26` |
| Pattern | none |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: none. No lifted file has the same role.
- Dead-strip: `wmain` and most callers are still `LIFT_STUB` bodies. `/OPT:REF` removes a lifted function that has no live caller, and funcdiff then cannot pair it. For each function in scope with no live caller, add `#pragma comment(linker, "/INCLUDE:<public name>")` in its `.cpp` (public names: `llvm-pdbutil dump -publics`; grep `/INCLUDE` in `Docs/Parity/lessons.md`). Do not add a pragma for a function that a lifted caller keeps.

## Scope

17 functions, about 1,139 pseudocode lines (about 9,112 tokens). Stems: `datamanager_cpp_1`.

The easy functions of this stem are in `lift-gamedaemon-e26`. Do not change them unless a fix needs it.

This card is part 1/10 of stem `datamanager_cpp_1`. The other parts are in other cards of this wave. They run one after the other (column "Depends on"). Edit only the functions in this table.

| n | Exe | RVA | PDB name | Stem | Lines |
| ---: | --- | --- | --- | --- | ---: |
| 1 | GD | `0x6170f0` | `Data::XmlReaderLogger::Error` | datamanager_cpp_1 | 15 |
| 2 | GD | `0x617130` | `Data::XmlReaderLogger::Debug` | datamanager_cpp_1 | 15 |
| 3 | GD | `0x617170` | `Data::XmlReaderLogger::Trace` | datamanager_cpp_1 | 15 |
| 4 | GD | `0x6171b0` | `Data::DataLogger::Write` | datamanager_cpp_1 | 39 |
| 5 | GD | `0x617290` | `Data::NoneSpecifyObjectQuestForwarding::AddNoneSpecifyObjectQuestForwardingInfo` | datamanager_cpp_1 | 34 |
| 6 | GD | `0x617320` | `Data::JumpingCharacterData::JumpingCharacterData` | datamanager_cpp_1 | 54 |
| 7 | GD | `0x617500` | `Data::JumpingCharacterData::addJumpingQuest` | datamanager_cpp_1 | 77 |
| 8 | GD | `0x617630` | `Data::JumpingCharacterData::addJumpingTeleport` | datamanager_cpp_1 | 78 |
| 9 | GD | `0x617760` | `Data::JumpingCharacterData::addJumpingCharacter` | datamanager_cpp_1 | 72 |
| 10 | GD | `0x617880` | `Data::JumpingCharacterData::addJumpingTutorialZone` | datamanager_cpp_1 | 74 |
| 11 | GD | `0x6179a0` | `Data::JumpingCharacterData2::JumpingCharacterData2` | datamanager_cpp_1 | 46 |
| 12 | GD | `0x617b10` | `Data::JumpingCharacterData2::AddJumpingCharacterQuestsToComplete` | datamanager_cpp_1 | 231 |
| 13 | GD | `0x617f20` | `Data::JumpingCharacterData2::AddJumpingQuest` | datamanager_cpp_1 | 127 |
| 14 | GD | `0x6181b0` | `Data::JumpingCharacterData2::AddJumpingTeleport` | datamanager_cpp_1 | 62 |
| 15 | GD | `0x6182f0` | `Data::SlateRelationCache::init` | datamanager_cpp_1 | 35 |
| 16 | GD | `0x618390` | `Data::SlateRelationCache::addStoneCache` | datamanager_cpp_1 | 50 |
| 17 | GD | `0x618450` | `Data::DataManager::InitInstance` | datamanager_cpp_1 | 115 |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/datamanager_cpp_1.cpp`
- `src/Server/GameDaemon/datamanager_cpp_1.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-67.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
