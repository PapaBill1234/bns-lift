# Handoff: lift-gamedaemon-gap-030-e30 (round 6)

## Lifted

29 functions keep a lifted body.

- `pc_cpp_3`: `Pc::isActivatedGrade`, `GetRewardContribution`, `AvailableTurnBack`, `BeginArenaLobbyReservation`, `RollbackArenaLobbyReservation`, `LeaveArenaLobbyOk`, `ReturnToGameByEnterFail`, `GetArenaSessionState`, `checkTeamGuildBattleFieldWithTarget`.
- `pc_cpp_4`: `Pc::SetTakingAchievementReward`, `IsTakingAchievementReward`, `GetPowerInfoForGameLog`, `HasCraft`, `FetchCraftUnionList`, `IsUsingJumpingCharacter2Ticket`, `ClearTransformItemRetry`, `ClearAttractionReward`, `SendInitializeSeasonContentsRecordFail`, `isAccountExpCharged`.
- `user_cpp`: `TimeBasedPlayInfoList::~TimeBasedPlayInfoList`, `SetLastCheckTimeUTC`, `GetValidCheckTimeUTC`, `SetData`, `SetDurationForDebug`; `User::SetPcCafeDebugCode`, `resetPc` thunk (0x3e56f0).
- `npcspawn_h`: `NpcSpawnInfo::GetAlias`, `GetActDetect`, `GetActSocial`.

## Notes

- Each lifted leaf with no live caller has a `/INCLUDE` keep pragma with a `// LIFT:` note.
- The `User::resetPc` thunk (0x3e56f0) stays lifted. It only jumps to `resetPc(void)`. Its `/INCLUDE` pragma stays, because it is the only keep line of that thunk.

## Round 6 repair: R4 `strict_regress` on `RefCntHistory::add`

The lead found the cause with preview builds. The `User::SetSession` body changes the LTCG code of `RefCntHistory::add` (the `ref` argument is dropped). This is link-time collateral. It is not an error in `RefCntHistory::add`.

Fix: `User::SetSession` is back to `LIFT_STUB(0x3e4610)`. Its `/INCLUDE` pragma is removed. No other body changed in this round.

## Not done

Each function below is a `LIFT_STUB`. Each goes to a later card.

| Function | RVA | Reason |
| --- | --- | --- |
| `User::SetSession` | 0x3e4610 | R4: LTCG collateral on `RefCntHistory::add`; a later card. |
| `Pc::clearCraftList` | 0x608950 | Round 4 stub. The R4 regress on `RefCntHistory::add` stayed after the stub, so the cause is not this body alone. A later card. |
| `User::resetPc` (void) | 0x3e5700 | Round 4 stub. The same note as `Pc::clearCraftList`. A later card. |
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

- `src/Server/GameDaemon/user_cpp.cpp`
- `Docs/Plan/handoffs/lift-gamedaemon-gap-030-e30.md`
