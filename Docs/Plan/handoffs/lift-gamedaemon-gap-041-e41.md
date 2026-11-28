# lift-gamedaemon-gap-041-e41 handoff

## Lifted

Stem `partybattlemanager_cpp`:

- `PartyBattleSide::PartyBattleSide` (0x181370)
- `PartyBattleSide::~PartyBattleSide` (0x1813a0)
- `PartyBattleSide::IncreaseDeathCount` (0x181aa0)
- `PartyBattleSide::IncreaseOccupationCount` (0x181b20)
- `PartyBattleSide::IncreaseManipulationCount` (0x181b80)
- `PartyBattleSide::GetFirstMemberId` (0x182200)
- `PartyBattleManager::CheckToFinishGame` (0x184310)
- `PartyBattleManager::CanTakeAchievementReward` (0x1843d0)
- `PartyBattleManager::isSaveGameResult` (0x185b70)

Stem `guild_cpp_1`:

- `Guild::GetBanishOpenGuildMemberCountResetTime` (0xe5fd0). The body does not read `this`. LTCG drops the unused `this` argument.

`PartyBattleSide` has its PDB layout now (size 0x30). `PartyBattleSideMemberView`, `PartyBattleFieldZoneRecordView` and `PartyBattleManagerView` are partial views. Each lifted body has an `/INCLUDE` keep pragma, because no caller is lifted yet.

## Not done

- `PartyBattleManager::CanResurrect` (0x184370): the offset of `Pc::_lastDeadTime` is not in a repo view. One look-up did not give it.
- `PartyBattleManager::getAttackerPc` (0x1858d0): the owner field of the attacker object (type 2) is not decoded. It needs the Npc or Summoned layout.
- `Guild::SetRenameGuildInProgress` (0xe1a50), `Guild::GetGuildInfoForGameLog` (0xe1ac0), `Guild::ResetLevelUp` (0xe5f90), `Guild::GetMemberIndexByPcDbId` (0xe8440): `Guild` has no member list in the repo. These bodies need `_guildCS`, `_renameGuildInProgress`, `_reserveLevelUp`, `_guildMember` and the guild info fields, and the `GuildInfoForGameLog` layout. Add a Guild view in a later round.
- Stem `battleroyalfield_cpp` (0x515d0, 0x53980, 0x53d70, 0x544e0, 0x54520, 0x56ab0, 0x56b00, 0x57720, 0x57730, 0x59110, 0x59270, 0x594f0): not started in this round. The session context was used by the layout look-ups of the first stems.
- Stem `tendencymanager_cpp` (0x21fa30, 0x21ff20, 0x220230, 0x222f80, 0x223680, 0x223a20): not started in this round.
- Stem `team_cpp_1` (0x1eff00, 0x1f0eb0, 0x2013e0, 0x201460): not started in this round.
- Stem `duelbot_cpp` (0x9e1c0, 0xa1e00): not started in this round.

## Open points

- `CanTakeAchievementReward` compares the step with 4. The PartyBattleStep enumerator name is not checked.
- `isSaveGameResult` skips detail rules 3 to 5. The enumerator names are not checked.
- The mangled names in the keep pragmas were written by hand. Check them against the publics if a body does not pair.

## Repair round 2

- The gate build failed. The toolchain did not find the header `<cstddef>`.
- `src/Server/GameDaemon/partybattlemanager.h` now includes `<stddef.h>` for `offsetof`. Other repo headers use the same form.

## Changed files

- `src/Server/GameDaemon/partybattlemanager.h`
- `src/Server/GameDaemon/partybattlemanager_cpp.cpp`
- `src/Server/GameDaemon/guild_cpp_1.cpp`
- `Docs/Plan/handoffs/lift-gamedaemon-gap-041-e41.md`

The driver runs the gate and the MATCH comparison.
