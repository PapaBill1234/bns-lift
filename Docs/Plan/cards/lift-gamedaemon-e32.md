# lift-gamedaemon-e32: Easy leaves (GameDaemon): zone_cpp_3, geoworld_cpp, world, zoneevent, ...

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

40 functions, about 842 pseudocode lines (about 6,736 tokens). Stems: `zone_cpp_3`, `geoworld_cpp`, `world`, `zoneevent`, `zonecellattributemanager`.

Wave E (owner order 2026-11-27: the easiest work first). Each function in this card is a leaf: its body calls no other counted function that needs a lift. Thus a `LIFT_STUB` callee cannot keep it DIFF. Each function has at most 30 pseudocode lines. Ease key: 21.1 cost per function (rule in `Docs/Plan/gamedaemon-lift.md` section 3).

Lift only the functions in the table. The other functions of these stems are in later W cards. Those cards depend on this card.

| n | Exe | RVA | PDB name | Stem | Lines | Form |
| ---: | --- | --- | --- | --- | ---: | --- |
| 1 | GD | `0x2567d0` | `Zone::HandleNpcSpawnEvent` | zone_cpp_3 | 15 | leaf |
| 2 | GD | `0x2570b0` | `Zone::CanResurrect` | zone_cpp_3 | 17 | leaf |
| 3 | GD | `0x2577b0` | `Zone::IsAllowInvitePartyInArena` | zone_cpp_3 | 29 | leaf |
| 4 | GD | `0x257ad0` | `Zone::GetDuelAttractionState` | zone_cpp_3 | 13 | leaf |
| 5 | GD | `0x257b10` | `Zone::GetPartyBattleFieldAttractionState` | zone_cpp_3 | 13 | leaf |
| 6 | GD | `0x257b50` | `Zone::GetPublicRaid` | zone_cpp_3 | 13 | leaf |
| 7 | GD | `0x257b90` | `Zone::GetEnterPublicRaidAttractionState` | zone_cpp_3 | 15 | leaf |
| 8 | GD | `0x257bd0` | `Zone::GetBattleRoyalFieldAttractionState` | zone_cpp_3 | 18 | leaf |
| 9 | GD | `0x257e60` | `Zone::FetchInZoneAttractionMemberState` | zone_cpp_3 | 17 | leaf |
| 10 | GD | `0x257ef0` | `Zone::GetGuildBattleFieldEntrance` | zone_cpp_3 | 27 | leaf |
| 11 | GD | `0x2582a0` | `Zone::CheckActivatedGuildBattleField` | zone_cpp_3 | 24 | leaf |
| 12 | GD | `0x258710` | `Zone::GetZoneScore` | zone_cpp_3 | 28 | leaf |
| 13 | GD | `0x2587e0` | `Zone::SetZRegVar` | zone_cpp_3 | 15 | leaf |
| 14 | GD | `0x2589c0` | `ZoneWaitingPcList::Initialize` | zone_cpp_3 | 30 | leaf |
| 15 | GD | `0x258f80` | `ZoneWaitingPcList::Find` | zone_cpp_3 | 30 | leaf |
| 16 | GD | `0x259340` | `ZoneWaitingPcList::GetCount` | zone_cpp_3 | 15 | leaf |
| 17 | GD | `0x2593a0` | `ZonePerfMonitor::~ZonePerfMonitor` | zone_cpp_3 | 30 | leaf |
| 18 | GD | `0x259f90` | `ZonePerfMonitor::EndZsoTest` | zone_cpp_3 | 19 | leaf |
| 19 | GD | `0xdb0d0` | `GeoCube::GeoCube` | geoworld_cpp | 20 | leaf |
| 20 | GD | `0xdb290` | `GeoCube::~GeoCube` | geoworld_cpp | 23 | leaf |
| 21 | GD | `0xdf0e0` | `GeoZone::GetRespawn` | geoworld_cpp | 20 | leaf |
| 22 | GD | `0xdf1c0` | `GeoZone::FindArea` | geoworld_cpp | 26 | leaf |
| 23 | GD | `0xdf680` | `GeoZone::IsFactionBattleFieldDungeon` | geoworld_cpp | 19 | leaf |
| 24 | GD | `0xdf6d0` | `GeoZone::IsTeamPartyZone` | geoworld_cpp | 15 | leaf |
| 25 | GD | `0x3ebfb0` | `WorldClock::~WorldClock` | world | 21 | leaf |
| 26 | GD | `0x3ec040` | `WorldClock::HandleEvent` | world | 12 | leaf |
| 27 | GD | `0x3ec1f0` | `ZoneIdManager::IsExist` | world | 27 | leaf |
| 28 | GD | `0x3ec290` | `PcIdManager::IsExist` | world | 17 | leaf |
| 29 | GD | `0x3ec300` | `SummonedIdManager::IsExist` | world | 17 | leaf |
| 30 | GD | `0x3f1af0` | `World::GetMaxChannelCount` | world | 20 | leaf |
| 31 | GD | `0x3f24e0` | `World::findZone` | world | 20 | leaf |
| 32 | GD | `0x3f45f0` | `World::DestroySummoned` | world | 28 | leaf |
| 33 | GD | `0x3f6e00` | `World::getChannelEnable` | world | 12 | leaf |
| 34 | GD | `0x42eed0` | `IdManager<__int64>::~IdManager<__int64>` | world | 27 | leaf |
| 35 | GD | `0x42ef80` | `IdManager<__int64>::Initialize` | world | 20 | leaf |
| 36 | GD | `0x42f000` | `IdManager<__int64>::PushId` | world | 27 | leaf |
| 37 | GD | `0x42f0a0` | `IdManager<__int64>::PopId` | world | 21 | leaf |
| 38 | GD | `0x25cef0` | `InOutDetector::InOutDetector` | zoneevent | 25 | leaf |
| 39 | GD | `0x25d210` | `InOutDetector::clear` | zoneevent | 27 | leaf |
| 40 | GD | `0x13150` | `ZoneCellAttributeTable::~ZoneCellAttributeTable` | zonecellattributemanager | 30 | leaf |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/zone_cpp_3.cpp`
- `src/Server/GameDaemon/zone_cpp_3.h`
- `src/Server/GameDaemon/geoworld_cpp.cpp`
- `src/Server/GameDaemon/geoworld_cpp.h`
- `src/Server/GameDaemon/world.cpp`
- `src/Server/GameDaemon/world.h`
- `src/Server/GameDaemon/zoneevent.cpp`
- `src/Server/GameDaemon/zoneevent.h`
- `src/Server/GameDaemon/zonecellattributemanager.cpp`
- `src/Server/GameDaemon/zonecellattributemanager.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-e32.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
