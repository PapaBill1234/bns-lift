# Handoff: lift-gamedaemon-gap-030-e30 (round 1)

## Lifted

All 40 functions of the card have a lifted body. No `LIFT_STUB` remains for the card RVAs.

- `pc_cpp_3`: `Pc::isActivatedGrade`, `GetRewardContribution`, `AvailableTurnBack`, `BeginArenaLobbyReservation`, `RollbackArenaLobbyReservation`, `LeaveArenaLobbyOk`, `ReturnToGameByEnterFail`, `GetArenaSessionState`, `IsInArenaOrArenaLobby`, `checkTeamGuildBattleFieldWithTarget`.
- `pc_cpp_4`: `Pc::SetTakingAchievementReward`, `IsTakingAchievementReward`, `GetPowerInfoForGameLog`, `EnableToRetrieveMyRanking`, `HasCraft`, `IsJoinedCraftUnion`, `GetCraftUnionExp`, `FetchCraftUnionList`, `IsRegisteredCraftRecipe`, `clearCraftList`, `IsUsingJumpingCharacter2Ticket`, `ClearTransformItemRetry`, `ClearAttractionReward`, `SendInitializeSeasonContentsRecordFail`, `isAccountExpCharged`.
- `user_cpp`: `TimeBasedPlayInfoList::~TimeBasedPlayInfoList`, `SetLastCheckTimeUTC`, `GetValidCheckTimeUTC`, `SetData`, `SetDurationForDebug`; `User::SetSession`, `SetPcCafeDebugCode`, `resetPc` (0x3e56f0 and 0x3e5700), `setExistContentsBan`, `IsBannedContents`, `ClearBotState`.
- `npcspawn_h`: `NpcSpawnInfo::GetAlias`, `GetActDetect`, `GetActSocial`.

## Notes

- `npcspawn.h` declares `NpcSpawnInfo` without members. The bodies read the PDB layout (size 0x20) through a local `NpcSpawnInfoView` struct and `reinterpret_cast`.
- The record pointers point to `DrEl` records (6 bytes each). The raw offsets come from `record[n].size`: `GetAlias` +0x10, `GetActDetect` +0xA0 / +0x88, `GetActSocial` +0x88.
- `GetAlias` returns `L""` for the last fallback. The original returns the shared empty wide string at `zone._privateProp[292]`. Marked `// LIFT:`.
- Each leaf with no live caller has a `/INCLUDE` keep pragma with a `// LIFT:` note.

## Not done

None.

## Not checked

The driver builds and runs the gate and funcdiff. The author did not run them. The state of each body is unverified until the driver reports MATCH.

## Files changed

- `src/Server/GameDaemon/pc_cpp_3.cpp`
- `src/Server/GameDaemon/pc_cpp_4.cpp`
- `src/Server/GameDaemon/user_cpp.cpp`
- `src/Server/GameDaemon/npcspawn_h.cpp`
- `Docs/Plan/handoffs/lift-gamedaemon-gap-030-e30.md`
