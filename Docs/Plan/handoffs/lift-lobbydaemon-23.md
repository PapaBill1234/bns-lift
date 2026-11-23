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
| LobbyDaemon MATCH after | 480 (+44) |
| Of the +44 | 41 card functions and 3 shared (`CliSessionTable::Select`, `Session::SendV`, `Session::Send`) |
| MATCH lost | 0 (MATCH to DIFF 0, name gone 0) |
| CacheGate | 456/491 = 92.9 % (+0) |
| LobbyGate | 658/739 = 89.0 % (+0) |
| SmartCouponDaemon | 630/669 = 94.2 % (+0) |
| PostOfficeDaemon | 694/759 = 91.4 % (+0) |
| LobbyDaemon | 480/2204 = 21.8 % |

The two scalar deleting destructors (`0x2ea50`, `0xc2590`) are compiler generated. The card does not count them.

## Verify steps in this run

1. The first parity run failed to link in all 5 exes (`ZSTD_*` unresolved). `vendor/zstd/src` was missing in the worktree. It was copied from `lift-lobbydaemon-22` (commit `bb6eaf64`). It is git-ignored and not committed.
2. The first measure dead-stripped the three `HandleLobbyInfoGate_*` functions. The repair fills the handler table, so the table reaches them. The 6 `/INCLUDE` pragmas for the 3 handlers and the 3 `InfoGateChannel::Send*` functions are removed. All 6 functions are in `LobbyDaemon.pdb` and paired.
3. Repair after the Opus review (see Review findings and Codegen trials).

## Functions

| Module | RVA | Function | Score | Status |
| --- | --- | --- | ---: | --- |
| InfoGateChannel | `0x2e6d0` | `InfoGateChannel::SendAuthTokenOk` | 100.0 | MATCH |
| InfoGateChannel | `0x2e870` | `InfoGateChannel::SendAuthTokenFail` | 100.0 | MATCH |
| InfoGateChannel | `0x2e980` | `InfoGateChannel::SendGetWorldInfoListFail` | 100.0 | MATCH |
| InfoGateChannel | `0x2ea70` | `InfoGateChannelManager::~InfoGateChannelManager` | 100.0 | MATCH |
| InfoGateChannel | `0x2eb50` | `InfoGateChannelManager::Add` | 100.0 | MATCH |
| InfoGateChannel | `0x2ec10` | `InfoGateChannelManager::Remove` | 100.0 | MATCH |
| InfoGateChannel | `0x2ed20` | `InfoGateChannelManager::Acquire` | 100.0 | MATCH |
| InfoGateChannel | `0x2edf0` | `InfoGateChannelManager::BroadcastBoastEventInWorldNotify` | 100.0 | MATCH |
| InfoGateChannel | `0x2ef40` | `InfoGateChannelManager::Broadcast` | 100.0 | MATCH |
| InfoGateChannel | `0x2f040` | `InfoGateChannelManager::OnAccept` | 100.0 | MATCH |
| InfoGateChannel | `0x2f0b0` | `InfoGateChannelManager::OnConnect` | 100.0 | MATCH |
| InfoGateChannel | `0x2f170` | `InfoGateChannelManager::OnClose` | 100.0 | MATCH |
| InfoGateChannel | `0x2f300` | `InfoGateChannelManager::PacketHandler` | 77.3 | DIFF |
| LobbyInfoGatePacketHandler | `0x56d40` | `HandleLobbyInfoGate_HelloReq` | 30.4 | DIFF |
| LobbyInfoGatePacketHandler | `0x57350` | `HandleLobbyInfoGate_AuthTokenReq` | 97.7 | DIFF |
| LobbyInfoGatePacketHandler | `0x57880` | `HandleLobbyInfoGate_GetWorldInfoListReq` | 82.7 | DIFF |
| GamedChannel | `0x82b70` | `GamedChannel::SendChangeCharacterRaceReq` | 100.0 | MATCH |
| GamedChannel | `0x82db0` | `GamedChannel::SendRenameCharacterReq` | 100.0 | MATCH |
| GamedChannel | `0x82f70` | `GamedChannel::SendExtendJumpingCharacterCreationQuotaWithAccountInventoryItemOk` | 100.0 | MATCH |
| GamedChannel | `0x83060` | `GamedChannel::SendExtendJumpingCharacterCreationQuotaWithAccountInventoryItemFail` | 100.0 | MATCH |
| GamedChannel | `0x83150` | `GamedChannel::SendUpgradeJumpingCharacterStateWithCreationQuotaOk` | 100.0 | MATCH |
| GamedChannel | `0x83250` | `GamedChannel::SendUpgradeJumpingCharacterStateWithCreationQuotaFail` | 100.0 | MATCH |
| GamedChannel | `0x83340` | `GamedChannel::SendUpdateJumpingCharacterStateOk` | 100.0 | MATCH |
| GamedChannel | `0x83430` | `GamedChannel::SendUpdateJumpingCharacterStateFail` | 100.0 | MATCH |
| GamedChannel | `0x83520` | `GamedChannel::SendSecondPasswordGetStatusOk` | 100.0 | MATCH |
| GamedChannel | `0x83670` | `GamedChannel::SendSecondPasswordGetStatusFail` | 100.0 | MATCH |
| GamedChannel | `0x83770` | `GamedChannel::SendSecondPasswordIsVerifiedOk` | 100.0 | MATCH |
| GamedChannel | `0x83860` | `GamedChannel::SendSecondPasswordIsVerifiedFail` | 100.0 | MATCH |
| GamedChannel | `0x83960` | `GamedChannel::SendAuctionEscrowReq` | 100.0 | MATCH |
| GamedChannel | `0x83b00` | `GamedChannel::SendGetGradeListFail` | 100.0 | MATCH |
| GamedChannel | `0x83c20` | `GamedChannel::SendActivateGradeOk` | 100.0 | MATCH |
| GamedChannel | `0x83d60` | `GamedChannel::SendActivateGradeFail` | 100.0 | MATCH |
| GamedChannel | `0x83ea0` | `GamedChannel::SendChangedGradeNotify` | 100.0 | MATCH |
| GamedChannel | `0x84090` | `GamedChannel::SendChangedGradeLevelNotify` | 100.0 | MATCH |
| GamedChannel | `0x841a0` | `GamedChannel::SendDepositGameMileageOk` | 100.0 | MATCH |
| GamedChannel | `0x84310` | `GamedChannel::SendDepositGameMileageFail` | 100.0 | MATCH |
| GamedChannel | `0x84460` | `GamedChannel::SendAuctionBidOk` | 100.0 | MATCH |
| GamedChannel | `0x845f0` | `GamedChannel::SendAuctionBidFail` | 100.0 | MATCH |
| GamedChannel | `0x84790` | `GamedChannel::SendTakeAccountTimeBasedPlayRewardFail` | 100.0 | MATCH |
| GamedChannel | `0x848f0` | `GamedChannel::SendUpdateAccountExpOk` | 100.0 | MATCH |
| GamedChannel | `0x849c0` | `GamedChannel::SendUpdateAccountExpFail` | 100.0 | MATCH |
| GamedChannel | `0x84aa0` | `GamedChannel::SendUpdateAccountContentQuotaOk` | 100.0 | MATCH |
| GamedChannel | `0x84b70` | `GamedChannel::SendUpdateAccountContentQuotaFail` | 100.0 | MATCH |
| GamedChannel | `0x84c50` | `GamedChannel::SendUpdateAccountRecycleTimeOk` | 100.0 | MATCH |
| GamedChannel | `0x84d20` | `GamedChannel::SendUpdateAccountRecycleTimeFail` | 100.0 | MATCH |

## Not done

None. All 45 functions are lifted. The 4 DIFF functions below are lifted but not MATCH.

## DIFF reasons

| Function | Score | Reason |
| --- | ---: | --- |
| `HandleLobbyInfoGate_HelloReq` (`0x56d40`) | 30.4 | `BLDaemonInfoTable::Find` is a `LIFT_STUB` of card 20 (noreturn). LTCG drops the code after the call, so ours has 24 of 63 calls. It rises when card 20 lifts `Find`. |
| `HandleLobbyInfoGate_GetWorldInfoListReq` (`0x57880`) | 82.7 | Ours inlines `Packet::Allocate`. The original calls it out of line (A4) and orders the error block first (A17). Below 85: no tries (and `Packet::Allocate` is shared by all 5 exes). |
| `HandleLobbyInfoGate_AuthTokenReq` (`0x57350`) | 97.7 | One `removeReferenceCount` call is missing (calls 97, refs 96). VS2010 merges the two tail calls (line 149 and line 138) into one block that loads a different `r8d` line number. The original keeps two calls because the mismatch path reads the session token fields from a saved copy of the session pointer. Ours writes zeros there (Safety differences), so the register pressure differs and the tails merge. ❓ The merge cause is read from our disassembly. The original disassembly was not compared. |
| `InfoGateChannelManager::PacketHandler` (`0x2f300`) | 77.3 | The handler table is now filled (3 entries, none is a fragment handler). LTCG folds the table: the fragment branch (`ConcatenatePacket`, `FragmentPacketConcatenater::Copy`) is dead code in ours. The original has it. The only reference to the table in the original is `lea` at `0x2f3b3`. ❓ Why the original does not fold is not known. Below 85: no tries. |

## Safety differences

| Where | Difference | Reason |
| --- | --- | --- |
| `HandleLobbyInfoGate_AuthTokenReq` | The token-mismatch log writes zeros in place of the required infogate token. Format string and argument count are the same. | The original logs an auth secret. The lift never logs it. |
| `HandleLobbyInfoGate_AuthTokenReq` | The OK-path log (line 144) writes zeros in place of the infogate token. Format string and argument count are the same. | The value equals `CliSession::_infoGateToken`, a session secret. The mismatch path already wrote zeros. |
| `HandleLobbyInfoGate_HelloReq` | `// BUG:` no null check after `Memory::Alloc` (kept as in the original). | Marked as a bug, not changed, to keep parity. |

## Review findings (Opus, `/tmp/ld-findings/ld-23.json`) and status

| Finding | Status |
| --- | --- |
| A17 not tried on 14 `Send*` DIFF functions | Done. All 14 use the error-first form and reach MATCH. `SendAuthTokenOk` and `SendGetWorldInfoListFail` do too. See Codegen trials. |
| Handler table all null | Done. New file `LobbyInfoGatePacketLobbySideHandlerList.cpp` holds the table (entries 1, 4, 7 and flags from `.data` rva `0x202D30`). The struct and the `extern` are in `LobbyInfoGatePacketHandler.h`. `PacketHandler` stays at 77.3 (see DIFF reasons). |
| `BLDaemonInfo.h` changed (card 20 owns it) | Done. The file is the same as main. `HelloReq` reads the two fields it needs through a local layout (`BLDaemonIdLayout`, `BLDaemonInfoLayout`) with a `// LIFT:` comment. The verify card replaces them with the header types. |
| `AuthTokenReq` OK path logs the token | Done. It writes zeros (Safety differences). |
| False `AuthTokenReq` DIFF reason | Done. New reason above. |
| Non-PDB local and helper names | Done. `HelloReq` locals are `cmd`, `acc`, `exp`. `GateWid` is gone. `InfoGateChannel::GetWid`, `IsBroadcastable` and `StartBroadcast` are inline members (PDB types `0x53EC`, `0x53ED`, `0x53EA`). `_broadcastable` is private as in the PDB. |
| 3 unneeded `/INCLUDE` pragmas | Done. All 6 are removed (3 handler and 3 `InfoGateChannel::Send*`). |

## Codegen trials (limit: 3 forms per function)

| Function | Form | Before | After |
| --- | --- | ---: | ---: |
| 3 functions of the first run (`SendUpdateJumpingCharacterStateOk`, `SendAuctionBidOk`, `SendAuthTokenFail`) | A17 error-first | 93.3 / 93.3 / 88.6 | 100.0 each |
| 16 `Send*` functions (`InfoGateChannel::SendAuthTokenOk`, `SendGetWorldInfoListFail`, and 14 `GamedChannel` functions: 5 Jumping, 4 SecondPassword, `SendGetGradeListFail`, `SendActivateGradeOk`, `SendActivateGradeFail`, `SendAuctionBidFail`, `SendTakeAccountTimeBasedPlayRewardFail`) | A17 error-first, form 1 | 88.6 to 93.3 | 100.0 each (MATCH) |
| `InfoGateChannelManager::BroadcastBoastEventInWorldNotify` | form 1: A17 error block first with `return` | 87.5 | 98.0 |
| same | form 2: broadcast-fail block also ends in `return` (the original has a separate `Packet::Clear` on the success path) | 98.0 | 100.0 MATCH |
| `HandleLobbyInfoGate_AuthTokenReq` | form 2 (form 1 was OK first): mismatch block first, as the line map of the PDB shows (136 before 142) | 94.9 | 97.7 (no further gain; tail merge stays) |
| `InfoGateChannelManager::PacketHandler` | form 1: table in its own translation unit | 77.3 | 77.3 (LTCG folds across units) |

MATCH 436 (main) -> 480.
