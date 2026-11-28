# lift-gamedaemon-gap-043-e43: handoff

## Lifted

### arenaroommanager_cpp

- `ArenaDuelRoom::build` (0x49c50)
- `ArenaPublicRaidRoom::GetPcContentsType` (0x4a500)
- `ArenaRoomManager::IssueOtp` (0x4a900)
- `ArenaSessionTimer::ArenaSessionTimer` (0x4ac20)
- `DisconnectedArenaSessionInfo::Init` (0x4acd0)
- `DisconnectedArenaSessionInfo::Decompose` (0x4ae50)

The header `arenaroommanager.h` now has the PDB layouts of `ArenaSessionTimer`, `DisconnectedArenaSessionInfo` (base `DynamicRefCntObj`) and `ArenaRoomManager::_otpSeed`. `ArenaDuelRoom` has a view of `_roomInfo`.

## Not done

### arenaroommanager_cpp

- `ArenaDungeonRoom::ArenaDungeonRoom` (0x49ed0): the constructor needs the full `ArenaRoom` / `DynamicRefCntObj` hierarchy and the PDB vtable order. The header has no such layout yet.
- `ArenaPublicRaidRoom::ArenaPublicRaidRoom` (0x4a350): same reason. The base `ArenaDungeonRoom` is only a padding view.
- `ArenaDungeonRoom::GetPcContentsType` (0x4a090): the fields of `Data::InterDungeonListRecord` and `GameDaemon::ruleConfig->_usePcContentsTypeDungeonEnable` are not declared.
- `ArenaRoomManager::ArenaRoomManager` (0x4a6e0): `_roomList` needs `std::map` with `StlAllocator<..., 2>` and `_lock` needs `CriticalSection`. These are not declared in the class view.

## Files changed

- `src/Server/GameDaemon/arenaroommanager.h`
- `src/Server/GameDaemon/arenaroommanager_cpp.cpp`
