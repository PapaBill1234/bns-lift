# Handoff: lift-gamedaemon-gap-040-e40 (card lift-gamedaemon-e40)

The skeleton classes have no PDB members and no bases. The lifted bodies use local `...View` structs (PDB offsets) for member access.

## Lifted

### combatsequence_cpp

- `CombatSequence::finishSpecial` (0x4080b0). It calls `Zone::GetTickTime`. That callee is still a `LIFT_STUB`, so the body can stay DIFF until a later card lifts it.
- `CombatSequence::registerLastAction` (0x408970).

### fielditem

- `FieldItemIdManager::IsExist` (0x5a06b0). `FieldItemList::Get` and `FieldItemList::find` are now PDB inline members in `fielditem.h`.
- `FieldItem::GetRemainedDecomposition` (0x5a0a90).
- `FieldItem::GetRemainedExplosion` (0x5a0af0).

### Other stems (earlier session of this round)

- `BrainCitizen::GetState` (0x402a80).
- `GameObject::~GameObject` (0x1d080), `GameObjectIdManager::Make` (0x1d090).
- `getAngle` (0x27280), `randomValue2Amount100` (0x1808e0).
- `BrainBoss::InitSpecialState` (0x7c9f0), `BrainBoss::checkPCHateListEmptied` (0x7d2e0).
- `RankingSeasonInfo::CopySeasonInfo` (0x180910), `RankingSeasonManager::isClosedSeason` (0x1809b0).
- `DuelMember::ReadyRound` (0xb1750), `DuelMember::ResetRound` (0xb17c0), `DuelTeam::IsTeamMemberAllDead` (0xb1860), `DuelTeam::ResetRound` (0xb1cf0), `DuelManager::finishGame` (0xb7c40), `DuelManager::resetRound` (0xb84d0), `DuelManager::getRoundStartPcSpawn` (0xb84e0), `DuelRule::IsGameDone` (0xbad50).
- `BrainBase::~BrainBase` (0x3fefc0), `BrainBase::ResetAllHates` (0x400d10), `BrainBase::pushState` (0x402910), `BrainBase::popState` (0x4029a0).

### Second session of this round

- `LeadTheBallManager::OnCanceledEnvManipulation` (0x138720). Local views give `PartyBattleManager::_step` (+0x18) and `DrEl::subtype` (+2). The PDB names of the values 2, 6, 8 and 9 are not known (`❓`).
- `RecycleTimeManager::SetGlobalRecycleTime2` (0x6101c0). The original inlines `setGlobalRecycleTime2`.
- `RecycleTimeManager::confirmRecycleTime2` (0x610fd0).
- `CampfireIdManager::IsExist` (0x63fe0). `CampfireList::Get` and `CampfireList::find` are now PDB inline members in `campfire.h`.
- `Campfire::GetRemainDuration` (0x64350).
- `BrainBase::IsPeace` (0x34f040).

All lifted leaves have a `/INCLUDE` keep pragma with a `// LIFT:` note.

## Files changed in the second session

- `src/Server/GameDaemon/leadtheballmanager_cpp.cpp`
- `src/Server/GameDaemon/recycletimemanager.cpp`
- `src/Server/GameDaemon/campfire.cpp`
- `src/Server/GameDaemon/campfire.h`
- `src/Server/GameDaemon/brainbase_h.cpp`
- `Docs/Plan/handoffs/lift-gamedaemon-gap-040-e40.md`

## Round 2 fix

- The gate build failed: the lift toolchain has no `<list>` header. `duelmanager_cpp.cpp` does not include `<list>` now. `DuelTeamView::_members` is a local view of the VS2010 list layout (`_Myhead` at +8, `_Mysize` at +16). `DuelTeam::IsTeamMemberAllDead` walks the nodes from `_Myhead->_Next`, as in the original.
- Changed file: `src/Server/GameDaemon/duelmanager_cpp.cpp`.

## Gate and MATCH

The author did not run a build, the gate or funcdiff. The driver does them.

## Not done

### combatsequence_cpp

- `BossCombatSequence::~BossCombatSequence` (0x630d0): the original stores the `CombatSequence` vftable. The skeleton has no `CombatSequence` base class.
- `isSufficentHpCondition` (0x4059c0): `HP_PERCENT_COND_TABLE` is not declared and its values are not known. The function is static and has no public, so a keep pragma is not possible.
- `CombatSequence::checkSpecialFired` (0x407c80): the pseudocode cache has no body (`None`).

### Other stems

- `SerializedObject::~SerializedObject` (0x663090): the original calls the `RelationalRefCntObject` and `RefCntObject` base destructors. The skeleton has no base class.
- `LeadTheBallManager::getRatingRevise` (0x138bb0): the body reads `Data::DataManager::Instance->_loaderDefs[6].table` through a virtual call. The skeleton has no `DataManager` or `DrTable` declaration.
- `PartyMatchQueue::push` (0x18b0e0): the skeleton class has no members. The body needs the PDB member `std::deque<Pc *, StlAllocator<Pc *, 2> > _queue[15]`, `Pc::_partyMatchQueueRegistered` and `RefCntObject::removeReferenceCount` on `Pc`.
- `PartyMatchPoint::PartyMatchPoint` (0x18b1a0): the body constructs the inline `PartyMatchQueue` member (15 deques). The skeleton classes have no members. If you add them, the stub destructors change too, and `PartyMatchPoint` must get access to the protected `PartyMatchQueue` constructor and destructor.
- `AchievementData::SendNewbieCareCompleteRegister` (0x34aa0): the skeleton has no `Packet` class, no static `_newbieCareCompletePacket` and no virtual `Pc::Send(Packet const *)`.
