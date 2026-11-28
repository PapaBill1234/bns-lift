# lift-gamedaemon-gap-044-e44: handoff

## Lifted

Stem `questjournal_cpp_2`:

- `QuestJournal::validateQuestId` (0x573010).
- `QuestJournal::isScriptableCase` (0x5730a0).
- `QuestJournal::RemoveLeaveZoneRollbackQuestIndex` (0x581080).
- `QuestJournal::removeAttrationQuest` (0x583ce0).

Each body has an `/INCLUDE` keep pragma. No lifted caller keeps them yet.
`questjournal.h` now has the PDB member layout of `QuestJournal` (size 0x9A8). The `_completes` member (PDB type `QuestList`) is a byte array. The `QuestList` layout is not declared yet.

## Not done

Stem `questjournal_cpp_2`:

- `QuestJournal::IsRewardRestrictedCase` (0x572fa0): the static array `_rewardRestrictedCase` has no definition in the repo. `QuestCase` has no layout in the headers. Note: the original tests `subtype <= 25`, but the array has 25 entries (a read of one byte past the end).
- `QuestJournal::calcQuestRewardExpBonus` (0x57a090): `Data::DataManager`, `QuestTable` and `GameDaemon::ruleConfig` have no layout in the headers.
- `QuestJournal::calcQuestRewardExpBonusTestServer` (0x57a110): `ContentsRuleConfig` has no members in the headers.
- `QuestJournal::checkPcDifficultyType` (0x57dc70): `Pc::_partyDifficultyType` is inside the undeclared part of `Pc` (`LiftBytes`).
- `QuestJournal::HasFactionQuest` (0x580f00): `OpenQuest` has no layout. The type of the quest record (faction at +48) is not in the PDB types.
- `QuestJournal::calcCaseFee` (0x582500): `Pc::Prop` and `Data::DataManager::_levelDataTable` are not declared.

Stem `filter_cpp` (all 11 functions): the headers have empty `ScriptParam`, `Data::FilterRecord` and `GameObject` (type at +46). The sub-record types (`data[1]`) and the type of `Data::FilterRecordSubDefs` are not declared. `FilterFactory::clear` needs the `Filter` vtable and the `Memory` manager form. The two template `Check` bodies have no wave-0 skeleton.

- `PcFilter::Check` (0x277f50).
- `NpcFilter::Check` (0x278540).
- `NotNpcFilter::Check` (0x2785b0).
- `EventBroadcastedFilter::Check` (0x278bf0).
- `EnvFilter::Check` (0x278c10).
- `SummonedFilter::Check` (0x2791f0).
- `NotSummonedFilter::Check` (0x279270).
- `LinkLaserTerminateReasonFilter::Check` (0x2792f0).
- `FilterFactory::clear` (0x2796e0).
- `DataKeyFilter<Data::FilterRecordActSequence>::Check` (0x346ca0).
- `DataIdFilter<Data::FilterRecordSkill3Id,Data::Skill3Record>::Check` (0x346d10).

Stem `teamparty` (all 7 functions): `teamparty.h` has no members and no vfptr for `TeamParty` (PDB size 0x730, virtual destructor). `Team`, `Pc`, `ArenaLobbyTeamMemberInfo`, `TeamParty::MemberAppearance` and the `Data::DataManager::_loaderDefs` tables have no layout in the headers.

- `TeamParty::GetMaxMemberCountByPartyType` (0x211170): needs the `_loaderDefs[56]` table `Find` call.
- `TeamParty::~TeamParty` (0x2113c0): needs the vfptr, `GameObjectCounter`, the `Memory` manager form and `_partyAuctionCS`.
- `TeamParty::AddAuction` (0x213250): needs `Team::Id` and the `_partyAuctions` layout.
- `TeamParty::IsEnteredMemberByAttraction` (0x2147a0): needs the `_loaderDefs[247]` table.
- `TeamParty::addMember` (0x21b970): needs `ArenaLobbyTeamMemberInfo` and `MemberAppearance`.
- `TeamParty::buildAppearance` (0x21bd80): needs the `Pc` layout. The pseudocode is not clear.
- `TeamParty::isFull` (0x21c1c0): needs the `_loaderDefs[56]` table.

Stem `publicraid_cpp` (all 3 functions): `EnterPublicRaidAttractionState` (PDB size 0xD340, vfptr base) has no layout in `publicraid.h`. `Zone` has no `Id` member and the `Pc` `Id` is inside `LiftBytes`. `ArenaLobbyRoomInfo` has no layout.

- `EnterPublicRaidAttractionState::SetRoomInfo` (0x1a0cf0).
- `EnterPublicRaidAttractionState::setMaxReservePcCountTouched` (0x1a0d70).
- `EnterPublicRaidAttractionState::checkReservePcCount` (0x1a10b0): the pseudocode also shows a removed parameter (LTCG). The source form is not clear.

Stem `fishingcontainer_cpp`:

- `FishingEntry::Initialize` (0xbae40): the Hex-Rays output shows the log format string as a wrong global name (`zone._simOperations`). The format literal is not known. `FishingEntry` and `Data::FishRecordPtr` have no layout in the headers.

Stem `mentoring`:

- `MentoringManager::Initialize` (0x169a10): `MentoringManager` has no layout in the headers. The body needs the two PDB `std::map` members (`_mentoringList`, `_menteeIdList`, `clear()`) with the `StlAllocator` type and the SRW lock `_mentoringMgrCS`.

## Changed files

- `src/Server/GameDaemon/questjournal.h`
- `src/Server/GameDaemon/questjournal_cpp_2.cpp`
- `Docs/Plan/handoffs/lift-gamedaemon-gap-044-e44.md`

## Gate and MATCH

The driver builds and compares after this session.
