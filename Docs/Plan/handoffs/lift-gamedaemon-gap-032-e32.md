# Handoff: lift-gamedaemon-gap-032-e32 (card lift-gamedaemon-e32), round 1

The driver builds, runs the gate and records the MATCH counts. This file does not record them.

## Lifted

The first session of this round lifted these bodies. The second session lifted `World::getChannelEnable`.

| RVA | PDB name | Note |
| --- | --- | --- |
| `0x2567d0` | `Zone::HandleNpcSpawnEvent` | Uses `ZoneView` and `ZoneNpcSpawnEventManagerView` in `zone.h`. |
| `0x257ad0` | `Zone::GetDuelAttractionState` | |
| `0x257b10` | `Zone::GetPartyBattleFieldAttractionState` | |
| `0x257b50` | `Zone::GetPublicRaid` | |
| `0x257b90` | `Zone::GetEnterPublicRaidAttractionState` | |
| `0x257bd0` | `Zone::GetBattleRoyalFieldAttractionState` | |
| `0x258710` | `Zone::GetZoneScore` | |
| `0x2589c0` | `ZoneWaitingPcList::Initialize` | |
| `0x258f80` | `ZoneWaitingPcList::Find` | |
| `0x259340` | `ZoneWaitingPcList::GetCount` | |
| `0x259f90` | `ZonePerfMonitor::EndZsoTest` | |
| `0xdb0d0` | `GeoCube::GeoCube` | Dead-strip keep pragma. |
| `0xdb290` | `GeoCube::~GeoCube` | Dead-strip keep pragma. |
| `0xdf0e0` | `GeoZone::GetRespawn` | Dead-strip keep pragma. Formtest DIFF 4 (array index form). |
| `0xdf6d0` | `GeoZone::IsTeamPartyZone` | Dead-strip keep pragma. |
| `0x42eed0` | `IdManager<__int64>::~IdManager<__int64>` | Dead-strip keep pragma. |
| `0x42ef80` | `IdManager<__int64>::Initialize` | Dead-strip keep pragma. |
| `0x42f000` | `IdManager<__int64>::PushId` | Dead-strip keep pragma. |
| `0x42f0a0` | `IdManager<__int64>::PopId` | Dead-strip keep pragma. |
| `0x3f6e00` | `World::getChannelEnable` | Dead-strip keep pragma. Formtest DIFF 6: the original has `channel` in rcx and does not use `this`. The PDB lists `this`, so an LTCG register change is likely. Same logic. `World::ChannelList` now has its PDB layout. |

## Not done

| RVA | PDB name | Reason |
| --- | --- | --- |
| `0x13150` | `ZoneCellAttributeTable::~ZoneCellAttributeTable` | Log path (E16): calls `Log::Write`. |
| `0x25cef0` | `InOutDetector::InOutDetector` | `InOutDetector` has no layout in the repo. `vector16` is an empty struct in `GameDaemonFwd.h`. `ZERO_VECTOR16` is not declared. The `std::map` member needs `StlAllocator`. That is more than 5 reads. |
| `0x25d210` | `InOutDetector::clear` | Same cause as the constructor. |
| `0xdf1c0` | `GeoZone::FindArea` | Log path (E16): calls `Log::Write`. |
| `0xdf680` | `GeoZone::IsFactionBattleFieldDungeon` | Calls a `Data::DataManager` loader table virtual (`_loaderDefs[74]`). The repo has no `DataManager` view. |
| `0x3ebfb0` | `WorldClock::~WorldClock` | `WorldClock` must derive from `Timer`. Then the vtable needs `TimerClass` and `TimerId` bodies, and this card does not cover them. |
| `0x3ec040` | `WorldClock::HandleEvent` | Same cause as `WorldClock::~WorldClock`. |
| `0x3ec1f0` | `ZoneIdManager::IsExist` | Log path (E16): calls `Log::Write` and `AlertSender::Write`. |
| `0x3ec290` | `PcIdManager::IsExist` | Log path (E16): calls `Log::Write`. |
| `0x3ec300` | `SummonedIdManager::IsExist` | Log path (E16): calls `Log::Write`. |
| `0x3f1af0` | `World::GetMaxChannelCount` | Calls a `Data::DataManager` loader table virtual (`_loaderDefs[260]`). The repo has no `DataManager` view. |
| `0x3f24e0` | `World::findZone` | Log path (E16): calls `Log::Write` and `AlertSender::Write`. |
| `0x3f45f0` | `World::DestroySummoned` | `World` has no PDB layout in the repo (`SummonedMgrCS`, `SummonedIdMgr`, `SummonedList`, `SummonedCount`). |
| `0x2570b0` | `Zone::CanResurrect` | Needs views of `Pc::_lastDeadTime`, of the `GuildBattleFieldManager` record and of `Daemon::StartSystemTick64`. That is more than 5 reads. |
| `0x2577b0` | `Zone::IsAllowInvitePartyInArena` | Log path (E16): calls `Log::Write` and `AlertSender::Write`. |
| `0x257e60` | `Zone::FetchInZoneAttractionMemberState` | `FragmentPacket` has no layout in the repo. |
| `0x257ef0` | `Zone::GetGuildBattleFieldEntrance` | Calls `Data::DataManager` loader table virtuals (`_loaderDefs[87]`, `[100]`). The repo has no `DataManager` view. |
| `0x2582a0` | `Zone::CheckActivatedGuildBattleField` | Same cause as `Zone::GetGuildBattleFieldEntrance`. |
| `0x2587e0` | `Zone::SetZRegVar` | Log path (E16): calls `Log::Write`. |
| `0x2593a0` | `ZonePerfMonitor::~ZonePerfMonitor` | Log path (E16): destroys a `LogFile` (`LogMedia`). |

## Changed files

- `src/Server/GameDaemon/GameDaemonFwd.h`
- `src/Server/GameDaemon/geoworld.h`
- `src/Server/GameDaemon/geoworld_cpp.cpp`
- `src/Server/GameDaemon/world.h`
- `src/Server/GameDaemon/world.cpp`
- `src/Server/GameDaemon/zone.h`
- `src/Server/GameDaemon/zone_cpp_3.cpp`
- `src/Server/GameDaemon/zonescore.h`
- `src/Server/GameDaemon/zonecellattributemanager.cpp` (note on the log-path stub only)
- `Docs/Plan/handoffs/lift-gamedaemon-gap-032-e32.md`

## Round 2 fix

- The gate `pdb_layout` check failed on `ZonePerfMonitor::lift_pad_90`.
- `zone.h` now declares the PDB members `zoneCounter` (+0x90) and `initCounter` (+0xA0).
- `zoneCounter` is a 0x10-byte placeholder. Its PDB type is `ZoneCounterSet`. GameDaemon does not declare the full class yet (marked `// ❓`).
