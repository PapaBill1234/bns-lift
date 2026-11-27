# lift-gamedaemon-e26: Easy leaves (DataManager and DataReader): datamanager_cpp_1, elreaderimpl, datamanager_h, datamanager_cpp_2, ...

| Item | Value |
| --- | --- |
| Exe | GD |
| Source build | GameDaemon 2019 + PDB (VS2010 SP1) |
| Exe file | `<work-root>/ida/lift/GameDaemon/GameDaemon.exe` |
| PDB | `<work-root>/ida/lift/GameDaemon/GameDaemon.pdb` |
| Pseudocode | `~/.cache/bns-lift/hr/GameDaemon/<stem>.c` |
| Pseudocode index | `~/.cache/bns-lift/hr/GameDaemon/index.tsv` (stem, rva, name, first, last, status, source file, part) |
| Wave | E |
| Model | opus |
| Depends on | `lift-gamedaemon-0e` |
| Pattern | none |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: none. No lifted file has the same role.
- Dead-strip: `wmain` and most callers are still `LIFT_STUB` bodies. `/OPT:REF` removes a lifted function that has no live caller, and funcdiff then cannot pair it. For each function in scope with no live caller, add `#pragma comment(linker, "/INCLUDE:<public name>")` in its `.cpp` (public names: `llvm-pdbutil dump -publics`; grep `/INCLUDE` in `Docs/Parity/lessons.md`). Do not add a pragma for a function that a lifted caller keeps.

## Scope

38 functions, about 659 pseudocode lines (about 5,272 tokens). Stems: `datamanager_cpp_1`, `elreaderimpl`, `datamanager_h`, `datamanager_cpp_2`, `util`.

Wave E (owner order 2026-11-27: the easiest work first). Each function in this card is a leaf: its body calls no other counted function that needs a lift. Thus a `LIFT_STUB` callee cannot keep it DIFF. Each function has at most 30 pseudocode lines. Ease key: 17.3 cost per function (rule in `Docs/Plan/gamedaemon-lift.md` section 3).

Lift only the functions in the table. The other functions of these stems are in later W cards. Those cards depend on this card.

| n | Exe | RVA | PDB name | Stem | Lines | Form |
| ---: | --- | --- | --- | --- | ---: | --- |
| 1 | GD | `0x616f60` | `Data::DataStaticMemoryManager::Alloc` | datamanager_cpp_1 | 11 | leaf |
| 2 | GD | `0x616f70` | `Data::DataStaticMemoryManager::Realloc` | datamanager_cpp_1 | 12 | leaf |
| 3 | GD | `0x616f90` | `Data::DataStaticMemoryManager::Free` | datamanager_cpp_1 | 11 | leaf |
| 4 | GD | `0x616fb0` | `Data::WriteDataManagerLog` | datamanager_cpp_1 | 16 | leaf |
| 5 | GD | `0x617060` | `Data::GamedGeoDataLog::WriteErrorV` | datamanager_cpp_1 | 12 | leaf |
| 6 | GD | `0x617090` | `Data::GamedGeoDataLog::WriteDebugV` | datamanager_cpp_1 | 12 | leaf |
| 7 | GD | `0x6170c0` | `Data::GamedGeoDataLog::WriteTraceV` | datamanager_cpp_1 | 12 | leaf |
| 8 | GD | `0x617490` | `Data::JumpingCharacterData::~JumpingCharacterData` | datamanager_cpp_1 | 21 | leaf |
| 9 | GD | `0x617a90` | `Data::JumpingCharacterData2::~JumpingCharacterData2` | datamanager_cpp_1 | 21 | leaf |
| 10 | GD | `0x618280` | `Data::SlateRelationCache::~SlateRelationCache` | datamanager_cpp_1 | 25 | leaf |
| 11 | GD | `0x61f4c0` | `Data::DataManager::FlushLog` | datamanager_cpp_1 | 18 | leaf |
| 12 | GD | `0x620c40` | `Data::insertQuest` | datamanager_cpp_1 | 3 | empty |
| 13 | GD | `0x620d30` | `Data::insertQuestConvoy` | datamanager_cpp_1 | 3 | empty |
| 14 | GD | `0x620de0` | `Data::insertQuestFactionPcKill` | datamanager_cpp_1 | 3 | empty |
| 15 | GD | `0x621120` | `Data::getNpcScriptId` | datamanager_cpp_1 | 23 | leaf |
| 16 | GD | `0x621180` | `Data::getEnvScriptId` | datamanager_cpp_1 | 14 | leaf |
| 17 | GD | `0x6211c0` | `Data::getZoneScriptId` | datamanager_cpp_1 | 14 | leaf |
| 18 | GD | `0x62be40` | `Data::DataManager::GetExp` | datamanager_cpp_1 | 18 | leaf |
| 19 | GD | `0x62c1b0` | `Data::DataManager::GetAccountExp` | datamanager_cpp_1 | 18 | leaf |
| 20 | GD | `0x62c2b0` | `Data::DataManager::GetMasteryExp` | datamanager_cpp_1 | 18 | leaf |
| 21 | GD | `0x62c910` | `Data::postprocNpc` | datamanager_cpp_1 | 14 | leaf |
| 22 | GD | `0x62dc10` | `Data::postprocDuelBotEquippedItem` | datamanager_cpp_1 | 15 | leaf |
| 23 | GD | `0x62f5d0` | `Data::postprocSummoned` | datamanager_cpp_1 | 10 | leaf |
| 24 | GD | `0x62fa90` | `Data::postprocBoardGachaReward` | datamanager_cpp_1 | 29 | leaf |
| 25 | GD | `0x6ed6d0` | `DrElReaderImpl::~DrElReaderImpl` | elreaderimpl | 7 | xtor |
| 26 | GD | `0x6ee200` | `DrElReaderImpl::findSubtype` | elreaderimpl | 20 | leaf |
| 27 | GD | `0x6ee280` | `DrElReaderImpl::findEltype` | elreaderimpl | 17 | leaf |
| 28 | GD | `0x6ee2f0` | `DrElReaderImpl::findTableType` | elreaderimpl | 21 | leaf |
| 29 | GD | `0x6ee370` | `DrElReaderImpl::findSeqstr` | elreaderimpl | 21 | leaf |
| 30 | GD | `0x6ee3d0` | `DrElReaderImpl::readSeq` | elreaderimpl | 29 | leaf |
| 31 | GD | `0x6ee470` | `DrElReaderImpl::readSeq16` | elreaderimpl | 27 | leaf |
| 32 | GD | `0x6ee520` | `DrElReaderImpl::readPropField` | elreaderimpl | 24 | leaf |
| 33 | GD | `0x6ee840` | `DrElReaderImpl::DrElReaderImpl` | elreaderimpl | 12 | xtor |
| 34 | GD | `0x34ef90` | `Data::DataManager::CheckJumpingCharacterTicketItemDataId` | datamanager_h | 30 | leaf |
| 35 | GD | `0x453e30` | `Data::DataManager::GetSkillByQuestMissionList` | datamanager_h | 11 | leaf |
| 36 | GD | `0x632730` | `Data::DataManager::IsValidCombatSeasonContentsType` | datamanager_cpp_2 | 27 | leaf |
| 37 | GD | `0x633410` | `Data::DataManager::GetNextSeasonContentsDefaultRatingScore` | datamanager_cpp_2 | 30 | leaf |
| 38 | GD | `0x6fee60` | `DrUtil::Length` | util | 30 | leaf |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/datamanager_cpp_1.cpp`
- `src/Server/GameDaemon/datamanager_cpp_1.h`
- `src/Server/GameDaemon/elreaderimpl.cpp`
- `src/Server/GameDaemon/elreaderimpl.h`
- `src/Server/GameDaemon/datamanager_h.cpp`
- `src/Server/GameDaemon/datamanager_h.h`
- `src/Server/GameDaemon/datamanager_cpp_2.cpp`
- `src/Server/GameDaemon/datamanager_cpp_2.h`
- `src/Server/GameDaemon/util.cpp`
- `src/Server/GameDaemon/util.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-e26.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
