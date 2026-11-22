# lift-lobbydaemon-23: GamedChannel 2, InfoGate

Source: LobbyDaemon 2019 + PDB, VS2010 SP1. Branch `slice/lift-lobbydaemon-23`, base main `9d0ef81`.
The six checkpoints (`build-ld-23/checkpoint-1..6.tsv`) cover all 45 card functions. No row overlaps another row.
Eight checkpoint RVAs differ by 2 to 0x18 bytes from the index RVAs (the checkpoint wrote a mid-function address). This file uses the `index.tsv` RVAs.

## Result

| Item | Value |
| --- | --- |
| Lifted | 45 of 45 |
| Not done | 0 |
| Gate | `gate ok` (LIFT_BUILD_DIR=build-ld-23) |
| Parity | `parity ok` |
| LobbyDaemon MATCH before (baseline, main) | 436 |
| LobbyDaemon MATCH after | 463 (+27) |
| Of the +27 | 24 card functions and 3 shared (`CliSessionTable::Select`, `Session::SendV`, `Session::Send`) |
| MATCH lost | 0 (MATCH to DIFF 0, name gone 0) |
| CacheGate | 456/491 = 92.9 % (+0) |
| LobbyGate | 658/739 = 89.0 % (+0) |
| SmartCouponDaemon | 630/669 = 94.2 % (+0) |
| PostOfficeDaemon | 694/759 = 91.4 % (+0) |
| LobbyDaemon | 463/2204 = 21.0 % |

The two scalar deleting destructors (`0x2ea50`, `0xc2590`) are compiler generated. The card does not count them.

## Verify steps in this run

1. The first parity run failed to link in all 5 exes (`ZSTD_*` unresolved). `vendor/zstd/src` was missing in the worktree. It was copied from `lift-lobbydaemon-22` (commit `bb6eaf64`). It is git-ignored and not committed.
2. The three `HandleLobbyInfoGate_*` functions were dead-stripped: only the null handler table reaches them. Three `/INCLUDE` pragmas were added in `LobbyInfoGatePacketHandler.cpp`. Result: +3 paired functions, +3 MATCH in the first measure.
3. Three codegen trials (see Codegen trials).

## Functions

| Module | RVA | Function | Score | Status |
| --- | --- | --- | ---: | --- |
| InfoGateChannel | `0x2e6d0` | `InfoGateChannel::SendAuthTokenOk` | 93.3 | DIFF |
| InfoGateChannel | `0x2e870` | `InfoGateChannel::SendAuthTokenFail` | 100.0 | MATCH |
| InfoGateChannel | `0x2e980` | `InfoGateChannel::SendGetWorldInfoListFail` | 88.6 | DIFF |
| InfoGateChannel | `0x2ea70` | `InfoGateChannelManager::~InfoGateChannelManager` | 100.0 | MATCH |
| InfoGateChannel | `0x2eb50` | `InfoGateChannelManager::Add` | 100.0 | MATCH |
| InfoGateChannel | `0x2ec10` | `InfoGateChannelManager::Remove` | 100.0 | MATCH |
| InfoGateChannel | `0x2ed20` | `InfoGateChannelManager::Acquire` | 100.0 | MATCH |
| InfoGateChannel | `0x2edf0` | `InfoGateChannelManager::BroadcastBoastEventInWorldNotify` | 87.5 | DIFF |
| InfoGateChannel | `0x2ef40` | `InfoGateChannelManager::Broadcast` | 100.0 | MATCH |
| InfoGateChannel | `0x2f040` | `InfoGateChannelManager::OnAccept` | 100.0 | MATCH |
| InfoGateChannel | `0x2f0b0` | `InfoGateChannelManager::OnConnect` | 100.0 | MATCH |
| InfoGateChannel | `0x2f170` | `InfoGateChannelManager::OnClose` | 100.0 | MATCH |
| InfoGateChannel | `0x2f300` | `InfoGateChannelManager::PacketHandler` | 77.3 | DIFF |
| LobbyInfoGatePacketHandler | `0x56d40` | `HandleLobbyInfoGate_HelloReq` | 30.4 | DIFF |
| LobbyInfoGatePacketHandler | `0x57350` | `HandleLobbyInfoGate_AuthTokenReq` | 94.9 | DIFF |
| LobbyInfoGatePacketHandler | `0x57880` | `HandleLobbyInfoGate_GetWorldInfoListReq` | 82.7 | DIFF |
| GamedChannel | `0x82b70` | `GamedChannel::SendChangeCharacterRaceReq` | 100.0 | MATCH |
| GamedChannel | `0x82db0` | `GamedChannel::SendRenameCharacterReq` | 100.0 | MATCH |
| GamedChannel | `0x82f70` | `GamedChannel::SendExtendJumpingCharacterCreationQuotaWithAccountInventoryItemOk` | 93.3 | DIFF |
| GamedChannel | `0x83060` | `GamedChannel::SendExtendJumpingCharacterCreationQuotaWithAccountInventoryItemFail` | 93.3 | DIFF |
| GamedChannel | `0x83150` | `GamedChannel::SendUpgradeJumpingCharacterStateWithCreationQuotaOk` | 93.3 | DIFF |
| GamedChannel | `0x83250` | `GamedChannel::SendUpgradeJumpingCharacterStateWithCreationQuotaFail` | 93.3 | DIFF |
| GamedChannel | `0x83340` | `GamedChannel::SendUpdateJumpingCharacterStateOk` | 100.0 | MATCH |
| GamedChannel | `0x83430` | `GamedChannel::SendUpdateJumpingCharacterStateFail` | 93.3 | DIFF |
| GamedChannel | `0x83520` | `GamedChannel::SendSecondPasswordGetStatusOk` | 93.3 | DIFF |
| GamedChannel | `0x83670` | `GamedChannel::SendSecondPasswordGetStatusFail` | 93.3 | DIFF |
| GamedChannel | `0x83770` | `GamedChannel::SendSecondPasswordIsVerifiedOk` | 93.3 | DIFF |
| GamedChannel | `0x83860` | `GamedChannel::SendSecondPasswordIsVerifiedFail` | 93.3 | DIFF |
| GamedChannel | `0x83960` | `GamedChannel::SendAuctionEscrowReq` | 100.0 | MATCH |
| GamedChannel | `0x83b00` | `GamedChannel::SendGetGradeListFail` | 93.3 | DIFF |
| GamedChannel | `0x83c20` | `GamedChannel::SendActivateGradeOk` | 93.3 | DIFF |
| GamedChannel | `0x83d60` | `GamedChannel::SendActivateGradeFail` | 93.3 | DIFF |
| GamedChannel | `0x83ea0` | `GamedChannel::SendChangedGradeNotify` | 100.0 | MATCH |
| GamedChannel | `0x84090` | `GamedChannel::SendChangedGradeLevelNotify` | 100.0 | MATCH |
| GamedChannel | `0x841a0` | `GamedChannel::SendDepositGameMileageOk` | 100.0 | MATCH |
| GamedChannel | `0x84310` | `GamedChannel::SendDepositGameMileageFail` | 100.0 | MATCH |
| GamedChannel | `0x84460` | `GamedChannel::SendAuctionBidOk` | 100.0 | MATCH |
| GamedChannel | `0x845f0` | `GamedChannel::SendAuctionBidFail` | 93.3 | DIFF |
| GamedChannel | `0x84790` | `GamedChannel::SendTakeAccountTimeBasedPlayRewardFail` | 93.3 | DIFF |
| GamedChannel | `0x848f0` | `GamedChannel::SendUpdateAccountExpOk` | 100.0 | MATCH |
| GamedChannel | `0x849c0` | `GamedChannel::SendUpdateAccountExpFail` | 100.0 | MATCH |
| GamedChannel | `0x84aa0` | `GamedChannel::SendUpdateAccountContentQuotaOk` | 100.0 | MATCH |
| GamedChannel | `0x84b70` | `GamedChannel::SendUpdateAccountContentQuotaFail` | 100.0 | MATCH |
| GamedChannel | `0x84c50` | `GamedChannel::SendUpdateAccountRecycleTimeOk` | 100.0 | MATCH |
| GamedChannel | `0x84d20` | `GamedChannel::SendUpdateAccountRecycleTimeFail` | 100.0 | MATCH |

## Not done

None. All 45 functions are lifted. The DIFF functions below are lifted but not MATCH.

## DIFF reasons

| Function | Score | Reason |
| --- | ---: | --- |
| `HandleLobbyInfoGate_HelloReq` (`0x56d40`) | 30.4 | `BLDaemonInfoTable::Find` is a `LIFT_STUB` of an earlier card (noreturn). LTCG drops the code after the call, so ours has 24 of 63 calls. It rises when that card lifts `Find`. |
| `HandleLobbyInfoGate_GetWorldInfoListReq` (`0x57880`) | 82.7 | Ours inlines `Packet::Allocate`. The original calls it out of line, (A4) ❓ and the error block order differs (A17). Not tried (below 85 and `Packet::Allocate` is shared). |
| `HandleLobbyInfoGate_AuthTokenReq` (`0x57350`) | 94.9 | The original reads `ID128_ID_ZERO` and calls `removeReferenceCount` in the decompose-fail block. See Safety differences. |
| `InfoGateChannelManager::PacketHandler` (`0x2f300`) | 77.3 | The handler table `LobbyInfoGatePacketLobbySideHandlerList` has null entries (ld-18 convention). Owner: the cards that lift the handlers. |
| `InfoGateChannelManager::BroadcastBoastEventInWorldNotify` (`0x2edf0`) | 87.5 | Block order of the error blocks differs. Not tried. |
| 16 `Send*` functions at 88.6 to 93.3 | see table | One cause: `Send` comes before `Log::Write` in ours (error block must be first, lessons ld-23 and A17). Not tried (trial limit). |

## Safety differences

| Where | Difference | Reason |
| --- | --- | --- |
| `HandleLobbyInfoGate_AuthTokenReq` | The token-mismatch log writes zeros in place of the required infogate token. Format string and argument count are the same. | The original logs an auth secret. The lift never logs it. This costs the `ID128_ID_ZERO` ref and some score. |
| `HandleLobbyInfoGate_HelloReq` | `// BUG:` no null check after `Memory::Alloc` (kept as in the original). | Marked as a bug, not changed, to keep parity. |

## Codegen trials (limit: 3 functions, 1 form each)

| Function | Form | Before | After |
| --- | --- | ---: | ---: |
| `GamedChannel::SendUpdateJumpingCharacterStateOk` | `if (0 == p.Compose(...)) { Log::Write } else Send(&p);` | 93.3 | 100.0 MATCH |
| `GamedChannel::SendAuctionBidOk` | same | 93.3 | 100.0 MATCH |
| `InfoGateChannel::SendAuthTokenFail` | same | 88.6 | 100.0 MATCH |

All 3 reached MATCH on the first form. LobbyDaemon MATCH 460 -> 463.

## Not tried

| What | Why |
| --- | --- |
| The same error-first form on the other 16 `Send*` functions (`SendAuthTokenOk`, `SendGetWorldInfoListFail`, 9 Jumping and SecondPassword functions, `SendGetGradeListFail`, `SendActivateGradeOk`, `SendActivateGradeFail`, `SendAuctionBidFail`, `SendTakeAccountTimeBasedPlayRewardFail`) | Trial limit of 3 functions. Expected up to +16 MATCH ❓. This is the first task for the verify card. |
| `BroadcastBoastEventInWorldNotify` block order | Trial limit. |
| `HandleLobbyInfoGate_GetWorldInfoListReq` `noinline` form | Trial limit. `Packet::Allocate` is shared by all 5 exes. |
| `HandleLobbyInfoGate_AuthTokenReq` | Gap comes from a deliberate safety difference. |

## Next

- The three `/INCLUDE` pragmas in `LobbyInfoGatePacketHandler.cpp` and the pragmas in the three card files stay until the callers are lifted. The verify card removes them.
- The handler table in `InfoGateChannel.cpp` stays null until the handlers have an owner.
