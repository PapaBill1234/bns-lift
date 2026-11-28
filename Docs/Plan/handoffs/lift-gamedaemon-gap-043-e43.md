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

### guild_cpp_2

- `Guild::findByPcDbId` (0xfa740)
- `Guild::findByPcName` (0xfa770)
- `Guild::findByPcDbIdInWaiting` (0xfa7f0)
- `Guild::checkPermissionGuild20` (0xfa830)
- `GuildIdManager::Initialize` (0x104f10)
- `GuildIdManager::PushGuildId` (0x104f90)
- `GuildIdManager::PopGuildId` (0x105030)

### guildcraft

- `GuildCraft::GetAsseintGuildCraftQuota` (0x114960)
- `GuildCraft::MakeGuildCraft` (0x114b90)
- `GuildCraft::EnableDonationGuildCraft` (0x114c30)
- `GuildCraft::IsCompletedGuildCraftDonation` (0x115190)

The header `guildcraft.h` now has the PDB layout of `GuildCraft` (base `DynamicRefCntObj`, size 0x1848) and a view of `GuildCraft::Assentient`.

### partyauction

- `PartyAuction::nextStep` (0x173570)
- `PartyAuction::checkAuth` (0x1736c0)

The header `partyauction.h` now has the PDB layout of `PartyAuction` (base `RefCntObject`, size 0x1D8), `AuctionItem` and `AuctionMember`. The destructor and `deallocate_me` are declared only. Their bodies are in a later card.

### petitionmanager

- `Petition::Petition` (0x18f8d0)
- `Petition::Accept` (0x18fa50)

The header `petitionmanager.h` now has the PDB layout of `Petition` (base `DynamicRefCntObj`, size 0x110).

### clientsessionhandler

- `ClientSessionHandler::OnAccept` (0x7d7b0)
- `ClientSessionHandler::OnConnect` (0x7d810)

The header `clientsessionhandler.h` now has the PDB class `ClientSessionData` (size 0x20, inline constructor). The pseudocode drops the line argument of `Alloc` in `OnAccept`. The lift uses line 57 (❓).

## Not done

The stem `arenaroommanager_cpp` is closed. The four functions below stay `LIFT_STUB`.

### arenaroommanager_cpp

- `ArenaDungeonRoom::ArenaDungeonRoom` (0x49ed0): the constructor needs the full `ArenaRoom` / `DynamicRefCntObj` hierarchy and the PDB vtable order. The header has no such layout yet.
- `ArenaPublicRaidRoom::ArenaPublicRaidRoom` (0x4a350): same reason. The base `ArenaDungeonRoom` is only a padding view.
- `ArenaDungeonRoom::GetPcContentsType` (0x4a090): the fields of `Data::InterDungeonListRecord` and `GameDaemon::ruleConfig->_usePcContentsTypeDungeonEnable` are not declared.
- `ArenaRoomManager::ArenaRoomManager` (0x4a6e0): `_roomList` needs `std::map` with `StlAllocator<..., 2>` and `_lock` needs `CriticalSection`. These are not declared in the class view.

### guild_cpp_2

- `Guild::isFullWaitingGuildMember` (0xfa2d0): it needs a `DataManager` table lookup (`GuildlevelRecord`, loader index 104) and `Guild::_guildLevel` / `_guildType`. The class view in `guild.h` does not declare them.
- `Guild::EnableRetrieveRankingInfo` (0x1018d0): `Guild::_latestRankingInfo`, `Guild::_rankingRewardListLock` and `LatestRankingInfo` are not declared in `guild.h`.

### guildcraft

- `GuildCraft::EnableMakeGuildCraft` (0x114ad0): it needs the `DataManager` table lookup of `GuildCraftRecipeRecord` (loader index 102) and the record fields. These are not declared. The pseudocode also shows a release of `_srwLock` with no acquire in this body. This needs a check before a lift.

### partyauction

- `PartyAuction::sendSelectPacket` (0x173640): it sends a static packet of the zone object through the `Pc` virtual `Send`. The packet global and the `Pc` vtable slot are not declared.

### petitionmanager

- `PetitionManager::PetitionManager` (0x18fb30): three `std::map` members with `StlAllocator<..., 2>` and a `CriticalSection` member. The class view does not declare them yet.

### clientsessionhandler

- `ClientSessionHandler::OnCreated` (0x7d6b0): it needs `GameDaemon::GamedInstance->_tlsInterface`, `TencentLibsInterface` and the class `TpDPSecurity` (vtable and size 80). These are not declared.
- `ClientSessionHandler::OnDestroyed` (0x7d730): same reason as `OnCreated`.

## Files changed

- `src/Server/GameDaemon/arenaroommanager.h`
- `src/Server/GameDaemon/arenaroommanager_cpp.cpp`
