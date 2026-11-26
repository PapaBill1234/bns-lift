# Handoff: lift-lobbydaemon-gap-26-lobbygamepackethandler-part-1

Date: 2026-11-26. Branch: `gap-26`. Base: `e0e8fff` (bns-lift main with gap-05 and gap-06).
Code commits: `ec8f9a5`, `3ab654c`, `d8c6656`, `c9cd395`, `1ac0e03`. This handoff is in the next commit.

## Scope

All 14 card IDs are lifted in `LobbyGamePacketHandler.cpp`. All 14 stay DIFF. The keep pragmas stay until the
callers are lifted.

| Card ID | Handler | REF | NOREF | Cause of DIFF |
| --- | --- | --- | --- | --- |
| 0x89270 | `HandleLobbyGame_EnterWorldReq` | 12.2 | 12.2 | `LobbyTokenDesk::Verify` 0x96fb0 and `EnterGameWorldJob::Initialize` are stubs (gap-16). |
| 0x899a0 | `HandleLobbyGame_LeaveWorldReq` | 61.5 | 60.1 | `LeaveGameWorldJob::Initialize` is a stub (gap-08). |
| 0x8a060 | `HandleLobbyGame_LogoutNotify` | 59.7 | 59.7 | `LogoutInGameWorldJob::Initialize` is a stub (gap-08). |
| 0x8b5b0 | `HandleLobbyGame_StartChargeReq` | 98.3 | 98.3 | `ObjPool::Checkout` const propagation (see below). |
| 0x8b9b0 | `HandleLobbyGame_StopChargeReq` | 98.3 | 97.5 | Same. |
| 0x8be60 | `HandleLobbyGame_AbandonChargeNotify` | 98.2 | 98.2 | Same. Also `lea r8d,[r9+0x7a]` (original) vs `mov r8d,0x7a` (ours). ❓ |
| 0x8d590 | `HandleLobbyGame_TryRegisterGuildReq` | 56.2 | 56.2 | `RuleSet::CheckName` 0x6bfc0 is a stub. |
| 0x8dc80 | `HandleLobbyGame_TryRenameGuildReq` | 28.7 | 28.7 | Same. |
| 0x8fb00 | `HandleLobbyGame_ExtendJumping...Req` | 97.5 | 99.2 | `ObjPool::Checkout` const propagation. |
| 0x8ffc0 | `HandleLobbyGame_UpgradeJumping...Req` | 97.5 | 99.2 | Same. |
| 0x903d0 | `HandleLobbyGame_UpdateJumpingCharacterStateReq` | 97.5 | 99.2 | Same. |
| 0x90f70 | `HandleLobbyGame_FriendMessageNotify` | 92.2 | 92.2 | `NPGameServiceChannel::SendRequestFriendSendMessage` 0xd0a00 is a stub. The NPChannel2 senders are not lifted. |
| 0x91ab0 | `HandleLobbyGame_SecondPasswordGetStatusReq` | 99.2 | 99.2 | `ObjPool::Checkout` const propagation. |
| 0x91e80 | `HandleLobbyGame_SecondPasswordIsVerifiedReq` | 99.2 | 99.2 | Same. |

Scope additions:

| Item | Reason | NOREF |
| --- | --- | --- |
| `LobbyObjectPool.cpp`: `ObjPool` ctor, dtor, `Checkout` (0x628c0) | The handlers take jobs from the pools. | `Checkout` DIFF 93.3 |
| `X::_pool` definitions at the end of each job .cpp (10 jobs) | PDB: `ObjPool X::_pool(1, sizeof(X), L"X")`. | n/a |
| `RefCntPoolObj` pool operators (PDB) | Placement `new`, placement `delete` (0x4f30, logs CRASH), private `new` forms. The placement delete gives the handlers their EH unwind action. | `operator delete` MATCH |
| `ExtendJumpingCharacterCreationQuotaJob` ctor 0x2a440, `UpgradeJumpingCharacterStateJob` ctor 0x2d4c0 | They were stubs. A stub callee ends the handler body. | MATCH |
| `RuleSet` layout, `CheckName` stub; `SecondPassword*Job` layouts; `NPGameServiceChannel::SendRequestFriendSendMessage` stub | The handlers need the declarations. | n/a |
| `RefCntPoolObj::operator delete(void*)` under `#if defined(__clang__)` | clang needs a usual delete for a virtual dtor. VS2010 does not (its deleting dtors call the global delete). The VS2010 build does not see it. | n/a |

## Why the job handlers stay DIFF: Checkout const propagation

- Each live caller of `ObjPool::Checkout` passes `L"LobbyGamePacketHandler.cpp"` as the file argument.
- LTCG IPA then folds the file constant into `Checkout`. The callers do not load it. Each handler has one ref less than the original, and `Checkout` has one ref more.
- In the original, other callers pass other files: `AbandonChargeJob` 0x5690/0x5b10, `LobbyToken::Expire` 0x96b00, `LobbyDaemon::setupNpScheduleInfo` 0x9f130, `CliSessionManager` 0x3cbd0/0x3cdd0, `GameTimeQueue::Block` 0x4bb80, `GameWorldCluster::leaveUser` 0x4e080, `LobbyManage` 0x58b00/0x59820, `StopPlayTimerEvent` 0xbbcf0, `Mileage` 0x5e1a0/0x61060, `StartCliSessionWnpTokenJob` 0xdb950.
- All of these are stubs now. When one of them is lifted, the 8 job handlers and `Checkout` should go to MATCH. ❓
- No address-taking or other trick was used. That would be a fake MATCH.

## Checks

| Check | Result |
| --- | --- |
| `pilot.py gate` (7 unlock IDs, REF `main-build-AjzWJ1xk`, NOREF `noref-build-MpsVjdon`, both `c9cd395`) | 4 of 7 clear (4 of 7 before at `e0e8fff`); 3 `ineligible_unpaired` (`Enter/Leave/LogoutInGameWorldJob::Initialize`); eligible pool 345 -> 345 |
| `buildonce gate` = `gate_fast.sh` (fresh clone of `1ac0e03`) | rc 0, gate ok, parity ok, 221 s |
| `strict.py` (5 exes, `cfg` level) | no FAIL |
| `proof.py --base e0e8fff --candidate 1ac0e03` | verdict `review`; 0 lost MATCH, 0 strict regress, 0 reasons, 12 review items |
| `integrate.check_proof` (dry) | Refused: a review proof needs the review receipts |

The first gate run at `c9cd395` failed: clang rejected `RefCntPoolObj` (no usual `operator delete`). `1ac0e03` fixes it for clang only.

## MATCH

| Exe | Before | After | Lost |
| --- | --- | --- | --- |
| CacheGate | 456 | 456 | 0 |
| LobbyGate | 658 | 658 | 0 |
| SmartCouponDaemon | 630 | 630 | 0 |
| PostOfficeDaemon | 694 | 694 | 0 |
| LobbyDaemon (REF) | 677 (841 paired) | 701 (888 paired) | 0 |
| LobbyDaemon (NOREF) | 1033 (1297 paired) | 1036 (1313 paired) | 0 |

The REF gain (+24) comes from bodies that the handlers make live: the charge jobs (`Initialize`, `init`, `work`,
`GetDefinition`, `expireStartCharge`), `CliSessionJob` ctor/dtor/`dispatch_work`, `LobbyJob` and `LobbyJobManager`
helpers, `NPLobbyJobTransaction::Expire`, `CliSession::setChargeKey` and `RefCntPoolObj::operator delete`.

## Open items

| Item | Cause | Owner |
| --- | --- | --- |
| 8 job handlers and `ObjPool::Checkout` DIFF | Checkout const propagation. Needs a lifted second caller. ❓ | later cards |
| EnterWorld, LeaveWorld, LogoutNotify | Stub callees (gap-16, gap-08, `LobbyTokenDesk::Verify`). | gap-16, gap-08 |
| TryRegisterGuild, TryRenameGuild | `RuleSet::CheckName` stub. | not planned |
| FriendMessageNotify | NP sender stub; NPChannel2 not lifted. | not planned |
| 12 proof review items | New MATCH without strict full proof (6 with cfg true). | review route |
| gap-04 conflict | gap-04 also adds `LobbyObjectPool.cpp` and its CMake line (add/add). Keep one copy at merge. | merge |
| Keep pragmas | All 14 stay: the callers are not lifted. | - |
| `vendor/zstd/src` | Git-ignored. Scratch clones must copy it in. | build scripts |
