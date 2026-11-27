# lift-gamedaemon-e41: Easy leaves (GameDaemon): partybattlemanager_cpp, guild_cpp_1, battleroyalfield_cpp, tendencymanager_cpp, ...

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

40 functions, about 764 pseudocode lines (about 6,112 tokens). Stems: `partybattlemanager_cpp`, `guild_cpp_1`, `battleroyalfield_cpp`, `tendencymanager_cpp`, `team_cpp_1`, `duelbot_cpp`.

Wave E (owner order 2026-11-27: the easiest work first). Each function in this card is a leaf: its body calls no other counted function that needs a lift. Thus a `LIFT_STUB` callee cannot keep it DIFF. Each function has at most 30 pseudocode lines. Ease key: 19.1 cost per function (rule in `Docs/Plan/gamedaemon-lift.md` section 3).

Lift only the functions in the table. The other functions of these stems are in later W cards. Those cards depend on this card.

| n | Exe | RVA | PDB name | Stem | Lines | Form |
| ---: | --- | --- | --- | --- | ---: | --- |
| 1 | GD | `0x181370` | `PartyBattleSide::PartyBattleSide` | partybattlemanager_cpp | 18 | leaf |
| 2 | GD | `0x1813a0` | `PartyBattleSide::~PartyBattleSide` | partybattlemanager_cpp | 18 | leaf |
| 3 | GD | `0x181aa0` | `PartyBattleSide::IncreaseDeathCount` | partybattlemanager_cpp | 28 | leaf |
| 4 | GD | `0x181b20` | `PartyBattleSide::IncreaseOccupationCount` | partybattlemanager_cpp | 25 | leaf |
| 5 | GD | `0x181b80` | `PartyBattleSide::IncreaseManipulationCount` | partybattlemanager_cpp | 25 | leaf |
| 6 | GD | `0x182200` | `PartyBattleSide::GetFirstMemberId` | partybattlemanager_cpp | 21 | leaf |
| 7 | GD | `0x184310` | `PartyBattleManager::CheckToFinishGame` | partybattlemanager_cpp | 29 | leaf |
| 8 | GD | `0x184370` | `PartyBattleManager::CanResurrect` | partybattlemanager_cpp | 9 | leaf |
| 9 | GD | `0x1843d0` | `PartyBattleManager::CanTakeAchievementReward` | partybattlemanager_cpp | 7 | getter |
| 10 | GD | `0x1858d0` | `PartyBattleManager::getAttackerPc` | partybattlemanager_cpp | 17 | leaf |
| 11 | GD | `0x185b70` | `PartyBattleManager::isSaveGameResult` | partybattlemanager_cpp | 7 | leaf |
| 12 | GD | `0xe1a50` | `Guild::SetRenameGuildInProgress` | guild_cpp_1 | 21 | leaf |
| 13 | GD | `0xe1ac0` | `Guild::GetGuildInfoForGameLog` | guild_cpp_1 | 13 | leaf |
| 14 | GD | `0xe5f90` | `Guild::ResetLevelUp` | guild_cpp_1 | 9 | leaf |
| 15 | GD | `0xe5fd0` | `Guild::GetBanishOpenGuildMemberCountResetTime` | guild_cpp_1 | 22 | leaf |
| 16 | GD | `0xe8440` | `Guild::GetMemberIndexByPcDbId` | guild_cpp_1 | 30 | leaf |
| 17 | GD | `0x515d0` | `BattleRoyalField::~BattleRoyalField` | battleroyalfield_cpp | 25 | leaf |
| 18 | GD | `0x53980` | `BattleRoyalField::setEventAreaInfo` | battleroyalfield_cpp | 28 | leaf |
| 19 | GD | `0x53d70` | `BattleRoyalField::setBattleRoyalFieldStartTime` | battleroyalfield_cpp | 30 | leaf |
| 20 | GD | `0x544e0` | `BattleRoyalField::IsPartyMode` | battleroyalfield_cpp | 24 | leaf |
| 21 | GD | `0x54520` | `BattleRoyalField::IsArenaMathcing` | battleroyalfield_cpp | 7 | getter |
| 22 | GD | `0x56ab0` | `BattleRoyalField::GetStateName` | battleroyalfield_cpp | 21 | leaf |
| 23 | GD | `0x56b00` | `BattleRoyalField::GetPartyStateName` | battleroyalfield_cpp | 19 | leaf |
| 24 | GD | `0x57720` | `BattleRoyalField::EnableInfiniteHyperEnergy` | battleroyalfield_cpp | 7 | getter |
| 25 | GD | `0x57730` | `BattleRoyalField::EnableArenaEventReturnToArenaLobbyAllPc` | battleroyalfield_cpp | 7 | getter |
| 26 | GD | `0x59110` | `BattleRoyalFieldPlayerManager::GetPlayerKillCount` | battleroyalfield_cpp | 21 | leaf |
| 27 | GD | `0x59270` | `BattleRoyalFieldPlayerManager::GetPlayerAttackDamage` | battleroyalfield_cpp | 21 | leaf |
| 28 | GD | `0x594f0` | `BattleRoyalFieldPlayerManager::GetPlayerRanking` | battleroyalfield_cpp | 21 | leaf |
| 29 | GD | `0x21fa30` | `TendencyField::getStateStr` | tendencymanager_cpp | 14 | leaf |
| 30 | GD | `0x21ff20` | `TendencyField::CheckManifestTendency` | tendencymanager_cpp | 23 | leaf |
| 31 | GD | `0x220230` | `TendencyField::resetTendencyInfo` | tendencymanager_cpp | 22 | leaf |
| 32 | GD | `0x222f80` | `NormalTendencyAttractionQuestPack::NormalTendencyAttractionQuestPack` | tendencymanager_cpp | 27 | leaf |
| 33 | GD | `0x223680` | `NormalTendencyAttractionQuestPack::Init` | tendencymanager_cpp | 15 | leaf |
| 34 | GD | `0x223a20` | `BuyuDoTendencyAttractionQuestPack::Init` | tendencymanager_cpp | 15 | leaf |
| 35 | GD | `0x1eff00` | `TeamPartyIdManager::~TeamPartyIdManager` | team_cpp_1 | 20 | leaf |
| 36 | GD | `0x1f0eb0` | `TeamManager::ReleaseAndUnlockTeam` | team_cpp_1 | 18 | leaf |
| 37 | GD | `0x2013e0` | `TeamManager::toPcIndex` | team_cpp_1 | 20 | leaf |
| 38 | GD | `0x201460` | `TeamManager::toPartyIndex` | team_cpp_1 | 20 | leaf |
| 39 | GD | `0x9e1c0` | `DuelBot::CheckUseSkill` | duelbot_cpp | 24 | leaf |
| 40 | GD | `0xa1e00` | `DuelBotSummoned::OnAttacked` | duelbot_cpp | 16 | leaf |

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/partybattlemanager_cpp.cpp`
- `src/Server/GameDaemon/partybattlemanager_cpp.h`
- `src/Server/GameDaemon/guild_cpp_1.cpp`
- `src/Server/GameDaemon/guild_cpp_1.h`
- `src/Server/GameDaemon/battleroyalfield_cpp.cpp`
- `src/Server/GameDaemon/battleroyalfield_cpp.h`
- `src/Server/GameDaemon/tendencymanager_cpp.cpp`
- `src/Server/GameDaemon/tendencymanager_cpp.h`
- `src/Server/GameDaemon/team_cpp_1.cpp`
- `src/Server/GameDaemon/team_cpp_1.h`
- `src/Server/GameDaemon/duelbot_cpp.cpp`
- `src/Server/GameDaemon/duelbot_cpp.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-e41.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
