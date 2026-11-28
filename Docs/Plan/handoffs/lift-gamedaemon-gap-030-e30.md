# Handoff: lift-gamedaemon-gap-030-e30 (round 3)

## Lifted

32 functions keep a lifted body. The review accepted them in the last run.

- `pc_cpp_3`: `Pc::isActivatedGrade`, `GetRewardContribution`, `AvailableTurnBack`, `BeginArenaLobbyReservation`, `RollbackArenaLobbyReservation`, `LeaveArenaLobbyOk`, `ReturnToGameByEnterFail`, `GetArenaSessionState`, `checkTeamGuildBattleFieldWithTarget`.
- `pc_cpp_4`: `Pc::SetTakingAchievementReward`, `IsTakingAchievementReward`, `GetPowerInfoForGameLog`, `HasCraft`, `FetchCraftUnionList`, `clearCraftList`, `IsUsingJumpingCharacter2Ticket`, `ClearTransformItemRetry`, `ClearAttractionReward`, `SendInitializeSeasonContentsRecordFail`, `isAccountExpCharged`.
- `user_cpp`: `TimeBasedPlayInfoList::~TimeBasedPlayInfoList`, `SetLastCheckTimeUTC`, `GetValidCheckTimeUTC`, `SetData`, `SetDurationForDebug`; `User::SetSession`, `SetPcCafeDebugCode`, `resetPc` (0x3e56f0 and 0x3e5700).
- `npcspawn_h`: `NpcSpawnInfo::GetAlias`, `GetActDetect`, `GetActSocial`.

## Notes

- Each lifted leaf with no live caller has a `/INCLUDE` keep pragma with a `// LIFT:` note.
- The 8 rejected bodies are back to `LIFT_STUB`. Their `/INCLUDE` pragmas are removed.

## Not done

Each function below is a `LIFT_STUB` again. Each goes to a later card.

| Function | RVA | Reason |
| --- | --- | --- |
| `Pc::IsInArenaOrArenaLobby` | 0x601020 | Review reject P2_cc (build `jb`, original `jl`). A later card. |
| `Pc::EnableToRetrieveMyRanking` | 0x607550 | Review reject P2_cc (build `jbe`, original `ja`) and P3_imm. A later card. |
| `Pc::IsJoinedCraftUnion` | 0x6083a0 | Review reject P2_cc (build `jge`, original `jl`) and P9_ret_width. A later card. |
| `Pc::GetCraftUnionExp` | 0x6084c0 | Review reject P2_cc (build `jge`, original `jl`). A later card. |
| `Pc::IsRegisteredCraftRecipe` | 0x608720 | Review reject: vector field offsets are 8 bytes off (original `[rbx+0x9550]`, build `[rbx+0x9558]`). A later card. |
| `User::setExistContentsBan` | 0x3e5e60 | Review reject P2_cc (build `jge`, original `jl`). A later card. |
| `User::IsBannedContents` | 0x3e5eb0 | Review reject P2_cc (build `setle`, original `cmovle`), P3_imm and P9_ret_width. A later card. |
| `User::ClearBotState` | 0x3e8440 | Review reject: second argument saved as 64 bit (original `mov ebp,edx`, build `mov rbp,rdx`). A later card. |

## Not checked

The driver builds and runs the gate and funcdiff. The author did not run them.

## Files changed

- `src/Server/GameDaemon/pc_cpp_3.cpp`
- `src/Server/GameDaemon/pc_cpp_4.cpp`
- `src/Server/GameDaemon/user_cpp.cpp`
- `Docs/Plan/handoffs/lift-gamedaemon-gap-030-e30.md`
