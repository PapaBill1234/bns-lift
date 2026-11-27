# lift-gamedaemon-e42: Easy leaves (GameDaemon): guilduniform, warfieldmanager, scripttable, duelmanager_h, ...

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

40 functions, about 827 pseudocode lines (about 6,616 tokens). Stems: `guilduniform`, `warfieldmanager`, `scripttable`, `duelmanager_h`, `team_cpp_2`, `petitionpacketbufferhandler`, `brainmonstertalkable_h`, `task_cpp_4`, `gameobject_cpp`, `raiddungeon`, `brainstate_cpp`.

Wave E (owner order 2026-11-27: the easiest work first). Each function in this card is a leaf: its body calls no other counted function that needs a lift. Thus a `LIFT_STUB` callee cannot keep it DIFF. Each function has at most 30 pseudocode lines. Ease key: 20.7 cost per function (rule in `Docs/Plan/gamedaemon-lift.md` section 3).

Lift only the functions in the table. The other functions of these stems are in later W cards. Those cards depend on this card.

| n | Exe | RVA | PDB name | Stem | Lines | Form |
| ---: | --- | --- | --- | --- | ---: | --- |
| 1 | GD | `0x131560` | `GuildUniform::fetchUniformInfo` | guilduniform | 22 | leaf |
| 2 | GD | `0x131db0` | `GuildUniform::EnableRegisterGuildUniform` | guilduniform | 12 | leaf |
| 3 | GD | `0x1324a0` | `GuildUniformManager::GetRegisteredUniformCount` | guilduniform | 26 | leaf |
| 4 | GD | `0x226d70` | `WarFieldGroup::getDataKey` | warfieldmanager | 20 | leaf |
| 5 | GD | `0x42e430` | `Data::QuestDecision::QuestDecision` | scripttable | 11 | xtor |
| 6 | GD | `0x467060` | `Data::FilterSet::FilterSet` | scripttable | 12 | xtor |
| 7 | GD | `0x467080` | `Data::FilterSet::~FilterSet` | scripttable | 29 | leaf |
| 8 | GD | `0x4670f0` | `Data::ReactionSet::ReactionSet` | scripttable | 14 | leaf |
| 9 | GD | `0x467110` | `Data::ReactionSet::~ReactionSet` | scripttable | 29 | leaf |
| 10 | GD | `0x467380` | `Data::ObjectScript::GetDecisionSequence` | scripttable | 25 | leaf |
| 11 | GD | `0x27bb0` | `DuelTeam::DuelTeam` | duelmanager_h | 28 | leaf |
| 12 | GD | `0x27d60` | `DuelTeam::instantiateDuelMember` | duelmanager_h | 26 | leaf |
| 13 | GD | `0x97070` | `DuelManager::isSaveGameResult` | duelmanager_h | 7 | getter |
| 14 | GD | `0x202980` | `TeamManager::unlock` | team_cpp_2 | 11 | leaf |
| 15 | GD | `0x2062f0` | `Team::GetPartyDifficultyType` | team_cpp_2 | 12 | leaf |
| 16 | GD | `0x206320` | `Team::GetPartyMemberCount` | team_cpp_2 | 21 | leaf |
| 17 | GD | `0x207970` | `Team::GetPartyDungeonStep` | team_cpp_2 | 28 | leaf |
| 18 | GD | `0x2079e0` | `Team::GetPartyChallengePartyAttractionId` | team_cpp_2 | 21 | leaf |
| 19 | GD | `0x207a40` | `Team::PartyIsInChallengePartyAttraction` | team_cpp_2 | 21 | leaf |
| 20 | GD | `0x207cb0` | `Team::IsPublishedRecruitArenaDungeonPartyMember` | team_cpp_2 | 21 | leaf |
| 21 | GD | `0x20e710` | `Team::findEmptyPartyIndex` | team_cpp_2 | 21 | leaf |
| 22 | GD | `0x20f150` | `Team::setVisible` | team_cpp_2 | 27 | leaf |
| 23 | GD | `0x190990` | `PetitionPacketBufferHandler::Clone` | petitionpacketbufferhandler | 24 | leaf |
| 24 | GD | `0x1909e0` | `PetitionPacketBufferHandler::Destroy` | petitionpacketbufferhandler | 12 | leaf |
| 25 | GD | `0x190a90` | `PetitionPacketBufferHandler::ToBuffer` | petitionpacketbufferhandler | 19 | leaf |
| 26 | GD | `0x190c10` | `PetitionPacketBufferHandler::Decompose` | petitionpacketbufferhandler | 28 | leaf |
| 27 | GD | `0x630e0` | `BrainMonsterTalkable::GetState` | brainmonstertalkable_h | 21 | leaf |
| 28 | GD | `0x2c3590` | `TakeAttractionRewardTask::start` | task_cpp_4 | 18 | leaf |
| 29 | GD | `0x2c35e0` | `ReviveByAttractionRuleTask::start` | task_cpp_4 | 24 | leaf |
| 30 | GD | `0x36c580` | `GameObject::Think` | gameobject_cpp | 16 | leaf |
| 31 | GD | `0x36c5c0` | `GameObject::OnTimer` | gameobject_cpp | 26 | leaf |
| 32 | GD | `0x36d500` | `GameObjectTimer::TimerExpired` | gameobject_cpp | 21 | leaf |
| 33 | GD | `0x1a71c0` | `RaidDungeon::GetMaxUnbindCount` | raiddungeon | 25 | leaf |
| 34 | GD | `0x1a8360` | `RaidDungeon::GetOccupyingObjectId` | raiddungeon | 14 | leaf |
| 35 | GD | `0x1a94a0` | `RaidDungeon::IsBound` | raiddungeon | 14 | leaf |
| 36 | GD | `0x1aa220` | `RaidDungeonManager::RaidDungeonManager` | raiddungeon | 24 | leaf |
| 37 | GD | `0x1aa2d0` | `RaidDungeonManager::~RaidDungeonManager` | raiddungeon | 24 | leaf |
| 38 | GD | `0x1aaf70` | `RaidDungeonManager::GetRaidDungeonPtrById` | raiddungeon | 22 | leaf |
| 39 | GD | `0x1ab2e0` | `RaidDungeonPropertyContainer::RaidDungeonPropertyContainer` | raiddungeon | 29 | leaf |
| 40 | GD | `0x403d60` | `ActSeqState::leave` | brainstate_cpp | 22 | leaf |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/guilduniform.cpp`
- `src/Server/GameDaemon/guilduniform.h`
- `src/Server/GameDaemon/warfieldmanager.cpp`
- `src/Server/GameDaemon/warfieldmanager.h`
- `src/Server/GameDaemon/scripttable.cpp`
- `src/Server/GameDaemon/scripttable.h`
- `src/Server/GameDaemon/duelmanager_h.cpp`
- `src/Server/GameDaemon/duelmanager_h.h`
- `src/Server/GameDaemon/team_cpp_2.cpp`
- `src/Server/GameDaemon/team_cpp_2.h`
- `src/Server/GameDaemon/petitionpacketbufferhandler.cpp`
- `src/Server/GameDaemon/petitionpacketbufferhandler.h`
- `src/Server/GameDaemon/brainmonstertalkable_h.cpp`
- `src/Server/GameDaemon/brainmonstertalkable_h.h`
- `src/Server/GameDaemon/task_cpp_4.cpp`
- `src/Server/GameDaemon/task_cpp_4.h`
- `src/Server/GameDaemon/gameobject_cpp.cpp`
- `src/Server/GameDaemon/gameobject_cpp.h`
- `src/Server/GameDaemon/raiddungeon.cpp`
- `src/Server/GameDaemon/raiddungeon.h`
- `src/Server/GameDaemon/brainstate_cpp.cpp`
- `src/Server/GameDaemon/brainstate_cpp.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-e42.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
