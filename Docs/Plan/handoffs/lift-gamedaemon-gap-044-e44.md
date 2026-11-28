# lift-gamedaemon-gap-044-e44: handoff

## Lifted

Stem `questjournal_cpp_2`:

- `QuestJournal::validateQuestId` (0x573010).
- `QuestJournal::isScriptableCase` (0x5730a0).
- `QuestJournal::RemoveLeaveZoneRollbackQuestIndex` (0x581080).
- `QuestJournal::removeAttrationQuest` (0x583ce0).

Each body has an `/INCLUDE` keep pragma. No lifted caller keeps them yet.
`questjournal.h` now has the PDB member layout of `QuestJournal` (size 0x9A8). The `_completes` member (PDB type `QuestList`) is a byte array. The `QuestList` layout is not declared yet.

Stem `rankingseason_cpp`:

- `RankingSeasonManager::GetSeasonContentsSchedule` (0x1b5e40). The formtest verdict is SAME. The body has an `/INCLUDE` keep pragma.

`rankingseason.h` now has the PDB member layout of `RankingSeasonManager` (size 0x98). The base (PDB type 0x74A9), the two `SeasonList` maps and `_seasonInfoPacket` are `LiftBytes`. `GameDaemonFwd.h` now has the PDB members of `SeasonContentsSchedule` (size 0x20).

## Not done

Stem `rankingseason_cpp`:

- `RankingSeasonManager::RankingSeasonManager` (0x1b39e0): the ctor sets the base members `_ref`, `_tag` and `_history`. The base class (PDB type 0x74A9) is not declared. The `SeasonList` map type with `StlAllocator<..., 2>` and the `Memory::_Manager[2]->AllocZero` form (128 bytes, no line argument) are not declared in this header.

Stem `questjournal_cpp_2` (the stem is closed for this round; the 4 lifted bodies above are the only edits):

- `QuestJournal::IsRewardRestrictedCase` (0x572fa0): the static array `_rewardRestrictedCase` has no definition in the repo. `QuestCase` has no layout in the headers. Note: the original tests `subtype <= 25`, but the array has 25 entries (a read of one byte past the end).
- `QuestJournal::calcQuestRewardExpBonus` (0x57a090): `Data::DataManager`, `QuestTable` and `GameDaemon::ruleConfig` have no layout in the headers.
- `QuestJournal::calcQuestRewardExpBonusTestServer` (0x57a110): `ContentsRuleConfig` has no members in the headers.
- `QuestJournal::checkPcDifficultyType` (0x57dc70): `Pc::_partyDifficultyType` is inside the undeclared part of `Pc` (`LiftBytes`).
- `QuestJournal::HasFactionQuest` (0x580f00): `OpenQuest` has no layout. The type of the quest record (faction at +48) is not in the PDB types.
- `QuestJournal::calcCaseFee` (0x582500): `Pc::Prop` and `Data::DataManager::_levelDataTable` are not declared.

Stem `filter_cpp` (all 11 functions; the stem is closed for this round): the headers have empty `ScriptParam`, `Data::FilterRecord` and `GameObject` (type at +46). The sub-record types (`data[1]`) and the type of `Data::FilterRecordSubDefs` are not declared. `FilterFactory::clear` needs the `Filter` vtable and the `Memory` manager form. The two template `Check` bodies have no wave-0 skeleton.

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

Stem `teamparty` (all 7 functions; the stem is closed for this round): `teamparty.h` has no members and no vfptr for `TeamParty` (PDB size 0x730, virtual destructor). `Team`, `Pc`, `ArenaLobbyTeamMemberInfo`, `TeamParty::MemberAppearance` and the `Data::DataManager::_loaderDefs` tables have no layout in the headers.

- `TeamParty::GetMaxMemberCountByPartyType` (0x211170): needs the `_loaderDefs[56]` table `Find` call.
- `TeamParty::~TeamParty` (0x2113c0): needs the vfptr, `GameObjectCounter`, the `Memory` manager form and `_partyAuctionCS`.
- `TeamParty::AddAuction` (0x213250): needs `Team::Id` and the `_partyAuctions` layout.
- `TeamParty::IsEnteredMemberByAttraction` (0x2147a0): needs the `_loaderDefs[247]` table.
- `TeamParty::addMember` (0x21b970): needs `ArenaLobbyTeamMemberInfo` and `MemberAppearance`.
- `TeamParty::buildAppearance` (0x21bd80): needs the `Pc` layout. The pseudocode is not clear.
- `TeamParty::isFull` (0x21c1c0): needs the `_loaderDefs[56]` table.

Stem `publicraid_cpp` (all 3 functions; the stem is closed for this round): `EnterPublicRaidAttractionState` (PDB size 0xD340, vfptr base) has no layout in `publicraid.h`. `Zone` has no `Id` member and the `Pc` `Id` is inside `LiftBytes`. `ArenaLobbyRoomInfo` has no layout.

- `EnterPublicRaidAttractionState::SetRoomInfo` (0x1a0cf0).
- `EnterPublicRaidAttractionState::setMaxReservePcCountTouched` (0x1a0d70).
- `EnterPublicRaidAttractionState::checkReservePcCount` (0x1a10b0): the pseudocode also shows a removed parameter (LTCG). The source form is not clear.

Stem `fishingcontainer_cpp` (closed for this round):

- `FishingEntry::Initialize` (0xbae40): the Hex-Rays output shows the log format string as a wrong global name (`zone._simOperations`). The format literal is not known. `FishingEntry` and `Data::FishRecordPtr` have no layout in the headers.

Stem `mentoring` (closed for this round):

- `MentoringManager::Initialize` (0x169a10): `MentoringManager` has no layout in the headers. The body needs the two PDB `std::map` members (`_mentoringList`, `_menteeIdList`, `clear()`) with the `StlAllocator` type and the SRW lock `_mentoringMgrCS`.

Stem `postbox` (closed for this round): `postbox.h` declares `PostBox`, its nested structs and `RetreivePostBriefListTask` with no members and no bases.

- `PostBox::~PostBox` (0x1922c0): the body decrements `GameObjectCounter::Instance._postCount` and frees each `PostBox::Post` through `Memory::_Manager[2]`. `GameObjectCounter` has no members in the headers. `PostBox::Post` (PDB size 0x5BF8) and its `PostBody` have no layout. The source form of the free (an inlined `Post` delete form) is not known.
- `RetreivePostBriefListTask::AddPost` (0x195620): the pseudocode has a fifth parameter `postCount` that the PDB signature does not have (LTCG). The source of the index is not known. The base class (PDB type 0x840C, size 0x90) has no layout in the headers.

Stem `task_cpp_5` (all 3 functions; closed for this round): each body gets the owner `Pc` from `_childRole->_parent` and clears two `Pc` members at +0x8DA8/+0x8DB0 (challenge party) or +0x8D78/+0x8D80 (mentoring). These members and `Pc::DbId` (+0x4E10) are inside the undeclared part of `Pc` (`LiftBytes`). The two `Fail` bodies also call a `Pc` virtual at vtable offset +600 with a packet-name argument that Hex-Rays shows as a wrong global (`zone._extraPrivateProp[3532]`). The PDB names of the members, the virtual and the argument are not known.

- `ConfirmInvitationChallengePartyFailFromCacheTask::start` (0x2d2010).
- `ConfirmInvitationMentoringOkFromCacheTask::start` (0x2d52a0).
- `ConfirmInvitationMentoringFailFromCacheTask::start` (0x2d5430).

## Changed files

- `src/Server/GameDaemon/questjournal.h`
- `src/Server/GameDaemon/questjournal_cpp_2.cpp`
- `src/Server/GameDaemon/rankingseason.h`
- `src/Server/GameDaemon/rankingseason_cpp.cpp`
- `src/Server/GameDaemon/GameDaemonFwd.h`
- `Docs/Plan/handoffs/lift-gamedaemon-gap-044-e44.md`

## Gate and MATCH

The driver builds and compares after this session.
