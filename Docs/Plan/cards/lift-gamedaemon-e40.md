# lift-gamedaemon-e40: Easy leaves (GameDaemon): combatsequence_cpp, fielditem, braincitizen_h, serializedobject_cpp, ...

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

## Scope

40 functions, about 709 pseudocode lines (about 5,672 tokens). Stems: `combatsequence_cpp`, `fielditem`, `braincitizen_h`, `serializedobject_cpp`, `gameobject_h`, `gamemath_h`, `brainboss_cpp`, `rankingseason_h`, `achievementdata`, `duelmanager_cpp`, `brainbase_cpp`, `leadtheballmanager_cpp`, `recycletimemanager`, `campfire`, `partymatchmaker_cpp`, `brainbase_h`.

Wave E (owner order 2026-11-27: the easiest work first). Each function in this card is a leaf: its body calls no other counted function that needs a lift. Thus a `LIFT_STUB` callee cannot keep it DIFF. Each function has at most 30 pseudocode lines. Ease key: 17.7 cost per function (rule in `Docs/Plan/gamedaemon-lift.md` section 3).

Lift only the functions in the table. The other functions of these stems are in later W cards. Those cards depend on this card.

| n | Exe | RVA | PDB name | Stem | Lines | Form |
| ---: | --- | --- | --- | --- | ---: | --- |
| 1 | GD | `0x630d0` | `BossCombatSequence::~BossCombatSequence` | combatsequence_cpp | 7 | xtor |
| 2 | GD | `0x4059c0` | `isSufficentHpCondition` | combatsequence_cpp | 17 | leaf |
| 3 | GD | `0x407c80` | `CombatSequence::checkSpecialFired` | combatsequence_cpp | 3 | empty |
| 4 | GD | `0x4080b0` | `CombatSequence::finishSpecial` | combatsequence_cpp | 29 | leaf |
| 5 | GD | `0x408970` | `CombatSequence::registerLastAction` | combatsequence_cpp | 24 | leaf |
| 6 | GD | `0x5a06b0` | `FieldItemIdManager::IsExist` | fielditem | 24 | leaf |
| 7 | GD | `0x5a0a90` | `FieldItem::GetRemainedDecomposition` | fielditem | 13 | leaf |
| 8 | GD | `0x5a0af0` | `FieldItem::GetRemainedExplosion` | fielditem | 13 | leaf |
| 9 | GD | `0x402a80` | `BrainCitizen::GetState` | braincitizen_h | 17 | leaf |
| 10 | GD | `0x663090` | `SerializedObject::~SerializedObject` | serializedobject_cpp | 17 | leaf |
| 11 | GD | `0x1d080` | `GameObject::~GameObject` | gameobject_h | 8 | xtor |
| 12 | GD | `0x1d090` | `GameObjectIdManager::Make` | gameobject_h | 27 | leaf |
| 13 | GD | `0x27280` | `getAngle` | gamemath_h | 23 | leaf |
| 14 | GD | `0x1808e0` | `randomValue2Amount100` | gamemath_h | 12 | leaf |
| 15 | GD | `0x7c9f0` | `BrainBoss::InitSpecialState` | brainboss_cpp | 13 | leaf |
| 16 | GD | `0x7d2e0` | `BrainBoss::checkPCHateListEmptied` | brainboss_cpp | 22 | leaf |
| 17 | GD | `0x180910` | `RankingSeasonInfo::CopySeasonInfo` | rankingseason_h | 19 | leaf |
| 18 | GD | `0x1809b0` | `RankingSeasonManager::isClosedSeason` | rankingseason_h | 16 | leaf |
| 19 | GD | `0x34aa0` | `AchievementData::SendNewbieCareCompleteRegister` | achievementdata | 18 | leaf |
| 20 | GD | `0xb1750` | `DuelMember::ReadyRound` | duelmanager_cpp | 23 | leaf |
| 21 | GD | `0xb17c0` | `DuelMember::ResetRound` | duelmanager_cpp | 11 | leaf |
| 22 | GD | `0xb1860` | `DuelTeam::IsTeamMemberAllDead` | duelmanager_cpp | 18 | leaf |
| 23 | GD | `0xb1cf0` | `DuelTeam::ResetRound` | duelmanager_cpp | 7 | setter |
| 24 | GD | `0xb7c40` | `DuelManager::finishGame` | duelmanager_cpp | 24 | leaf |
| 25 | GD | `0xb84d0` | `DuelManager::resetRound` | duelmanager_cpp | 7 | setter |
| 26 | GD | `0xb84e0` | `DuelManager::getRoundStartPcSpawn` | duelmanager_cpp | 26 | leaf |
| 27 | GD | `0xbad50` | `DuelRule::IsGameDone` | duelmanager_cpp | 29 | leaf |
| 28 | GD | `0x3fefc0` | `BrainBase::~BrainBase` | brainbase_cpp | 7 | xtor |
| 29 | GD | `0x400d10` | `BrainBase::ResetAllHates` | brainbase_cpp | 22 | leaf |
| 30 | GD | `0x402910` | `BrainBase::pushState` | brainbase_cpp | 23 | leaf |
| 31 | GD | `0x4029a0` | `BrainBase::popState` | brainbase_cpp | 21 | leaf |
| 32 | GD | `0x138720` | `LeadTheBallManager::OnCanceledEnvManipulation` | leadtheballmanager_cpp | 20 | leaf |
| 33 | GD | `0x138bb0` | `LeadTheBallManager::getRatingRevise` | leadtheballmanager_cpp | 17 | leaf |
| 34 | GD | `0x6101c0` | `RecycleTimeManager::SetGlobalRecycleTime2` | recycletimemanager | 13 | leaf |
| 35 | GD | `0x610fd0` | `RecycleTimeManager::confirmRecycleTime2` | recycletimemanager | 24 | leaf |
| 36 | GD | `0x63fe0` | `CampfireIdManager::IsExist` | campfire | 24 | leaf |
| 37 | GD | `0x64350` | `Campfire::GetRemainDuration` | campfire | 14 | leaf |
| 38 | GD | `0x18b0e0` | `PartyMatchQueue::push` | partymatchmaker_cpp | 23 | leaf |
| 39 | GD | `0x18b1a0` | `PartyMatchPoint::PartyMatchPoint` | partymatchmaker_cpp | 15 | leaf |
| 40 | GD | `0x34f040` | `BrainBase::IsPeace` | brainbase_h | 19 | leaf |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/combatsequence_cpp.cpp`
- `src/Server/GameDaemon/combatsequence_cpp.h`
- `src/Server/GameDaemon/fielditem.cpp`
- `src/Server/GameDaemon/fielditem.h`
- `src/Server/GameDaemon/braincitizen_h.cpp`
- `src/Server/GameDaemon/braincitizen_h.h`
- `src/Server/GameDaemon/serializedobject_cpp.cpp`
- `src/Server/GameDaemon/serializedobject_cpp.h`
- `src/Server/GameDaemon/gameobject_h.cpp`
- `src/Server/GameDaemon/gameobject_h.h`
- `src/Server/GameDaemon/gamemath_h.cpp`
- `src/Server/GameDaemon/gamemath_h.h`
- `src/Server/GameDaemon/brainboss_cpp.cpp`
- `src/Server/GameDaemon/brainboss_cpp.h`
- `src/Server/GameDaemon/rankingseason_h.cpp`
- `src/Server/GameDaemon/rankingseason_h.h`
- `src/Server/GameDaemon/achievementdata.cpp`
- `src/Server/GameDaemon/achievementdata.h`
- `src/Server/GameDaemon/duelmanager_cpp.cpp`
- `src/Server/GameDaemon/duelmanager_cpp.h`
- `src/Server/GameDaemon/brainbase_cpp.cpp`
- `src/Server/GameDaemon/brainbase_cpp.h`
- `src/Server/GameDaemon/leadtheballmanager_cpp.cpp`
- `src/Server/GameDaemon/leadtheballmanager_cpp.h`
- `src/Server/GameDaemon/recycletimemanager.cpp`
- `src/Server/GameDaemon/recycletimemanager.h`
- `src/Server/GameDaemon/campfire.cpp`
- `src/Server/GameDaemon/campfire.h`
- `src/Server/GameDaemon/partymatchmaker_cpp.cpp`
- `src/Server/GameDaemon/partymatchmaker_cpp.h`
- `src/Server/GameDaemon/brainbase_h.cpp`
- `src/Server/GameDaemon/brainbase_h.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-e40.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
