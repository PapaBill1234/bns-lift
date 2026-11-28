# Handoff: lift-gamedaemon-gap-030-e30 (round 5)

## Lifted

30 functions keep a lifted body. The review accepted them in the last run.

- `pc_cpp_3`: `Pc::isActivatedGrade`, `GetRewardContribution`, `AvailableTurnBack`, `BeginArenaLobbyReservation`, `RollbackArenaLobbyReservation`, `LeaveArenaLobbyOk`, `ReturnToGameByEnterFail`, `GetArenaSessionState`, `checkTeamGuildBattleFieldWithTarget`.
- `pc_cpp_4`: `Pc::SetTakingAchievementReward`, `IsTakingAchievementReward`, `GetPowerInfoForGameLog`, `HasCraft`, `FetchCraftUnionList`, `IsUsingJumpingCharacter2Ticket`, `ClearTransformItemRetry`, `ClearAttractionReward`, `SendInitializeSeasonContentsRecordFail`, `isAccountExpCharged`.
- `user_cpp`: `TimeBasedPlayInfoList::~TimeBasedPlayInfoList`, `SetLastCheckTimeUTC`, `GetValidCheckTimeUTC`, `SetData`, `SetDurationForDebug`; `User::SetSession`, `SetPcCafeDebugCode`, `resetPc` thunk (0x3e56f0).
- `npcspawn_h`: `NpcSpawnInfo::GetAlias`, `GetActDetect`, `GetActSocial`.

## Notes

- Each lifted leaf with no live caller has a `/INCLUDE` keep pragma with a `// LIFT:` note.
- The `User::resetPc` thunk (0x3e56f0) stays lifted. It only jumps to `resetPc(void)`. Its `/INCLUDE` pragma stays, because it is the only keep line of that thunk.

## Round 5 repair: R4 `strict_regress` on `RefCntHistory::add`

The earlier cause text was wrong and is removed. The two `LIFT_STUB` bodies of round 4 did not change the regress. New callers of `RefCntObject::removeReferenceCount` are not the cause.

Bisect result: **not done**. The author session could not run a build. The shell refused `slotrun` and `tools/vs2010/build.sh`. Thus there are 0 build results, and no body changed in this round.

What the source shows (static check, not proof):

- The card does not edit `RefCntHistory::add` (`src/Server/BloodLib/source/RefCntObject.cpp`).
- No lifted body of this card names `RefCntObject`, `Pointer2` or `RefCntHistory`. The only match is the parameter types of the `User::resetPc` thunk.
- The regress first showed in round 3. The base changed in that round (875a51e to 4f0910b, with E40 and E41). Round 2 had 35 bodies and no regress. Round 4 had 2 fewer bodies and the same ratio (0.9375 to 0.6304).
- An open hypothesis: the regress comes from the base change (E40 or E41), not from this card. Test: build main `07760ee` and run `tools/funcdiff.py` for GameDaemon. If the `RefCntHistory::add` row already shows 0.6304 on main, the card is not the cause.
- If main is clean, bisect next: `user_cpp.cpp` (8 bodies and the thunk), then `pc_cpp_4.cpp`, then `pc_cpp_3.cpp`, then `npcspawn_h.cpp`. Use at most 6 builds.

## Not done

Each function below is a `LIFT_STUB`. Each goes to a later card.

| Function | RVA | Reason |
| --- | --- | --- |
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

- `Docs/Plan/handoffs/lift-gamedaemon-gap-030-e30.md`
