# Handoff: lift-lobbydaemon-gap-19-managechannel

Date: 2026-11-26. Branch: `gap-19`. Base: `7b92217` (origin/main; it holds fix7 `e68e5d0`).
Code commits: `a538d2b`, `e5d9fe2`. This handoff is in the next commit.

## Scope

| ID (RVA) | Function | REF | NOREF |
| --- | --- | --- | --- |
| 0x9d520 | `LobbyDaemon::initNetwork` | MATCH | DIFF 96.3 |
| 0x587d0 | `HandleLobbyManage_HelloReq` | MATCH | MATCH |
| 0x58770 | `ManageChannel::GetId` | MATCH | MATCH |
| 0x5b8a0, 0x5b9d0 | `SendCleanupGameAccountIdIndexOk/Fail` | MATCH | MATCH |
| 0x5bb10, 0x5bc40 | `SendCleanupPcidIndexOk/Fail` | MATCH | MATCH |
| 0x5b630, 0x5b760 | `SendKickOk/Fail` | not live | MATCH |
| 0x5bd80, 0x5beb0 | `SendRetryMileageDepositOk/Fail` | not live | MATCH |
| 0x5b2a0 | `ManageSessionHandler::PacketHandler` | DIFF 93.0 | DIFF 93.0 |
| 0x590a0 | `HandleLobbyManage_CleanupGameAccountIdIndexReq` | DIFF 84.8 | DIFF 84.8 |
| 0x59470 | `HandleLobbyManage_CleanupPcidIndexReq` | DIFF 85.7 | DIFF 85.7 |

Also lifted (not card IDs): `ManageSessionHandler::OnAccept`, `OnConnect`, `OnClose` (MATCH in REF and NOREF), the manage handler table `LobbyManagePacketLobbySideHandlerList[17]`, and `Initialize(short, short)` for the lobby-gate, info-gate and gamed channel managers.

## Not done

| ID (RVA) | Function | Reason |
| --- | --- | --- |
| 0xcb710 | `DispatchNPLobbyMessageHandler` | gap-20 owns `NPLobbyMessageHandler`. The body needs about 60 handler declarations. |
| 0xcc370 | `Handle_SrvPres_LogoutUser` | gap-20 owns the module. The body needs `KickJob` and `NPDemander`. |
| 0x59820 | `HandleLobbyManage_RetryMileageDepositReq` | Needs the `DepositMileageJob` layout (gap-22), `LobbyDB::RetrieveMileageDeposit`, `DepositMileageReqParam` and `MileageDepositInfo`. |
| 0x596f0 | `DepositPcCafeMileageJobManageCallback::OnSuccess` | Same as 0x59820. |

`AnnounceNotify` (0x589b0) and `KickReq` (0x58b00) stay `LIFT_STUB`. They are not card IDs. So `SendKickOk/Fail` and `SendRetryMileageDeposit*` stay dead in REF.

## Shared files (gap-17 lifts `LobbyDaemon::initialize` in clone-17)

| File | Change |
| --- | --- |
| `src/Server/LobbyDaemon/LobbyDaemon.cpp` | `initNetwork` body only, and 6 new includes. `initialize` is not changed. |
| `src/Server/LobbyDaemon/LobbyGateChannel.h/.cpp` | Inline empty ctor; `bool Initialize(short, short)`. |
| `src/Server/LobbyDaemon/InfoGateChannel.h/.cpp` | Same. |
| `src/Server/LobbyDaemon/GamedChannel.h/.cpp` | Same. |
| `src/Server/Shared/SharedChannel.h` | `SharedChannelList` ctor that sets its 4 fields to 0. |

Merge note: if gap-17 also adds these ctors or `Initialize`, keep one copy.

## What changed

- `initNetwork` opens the NP, account inventory, post-office, lobby-gate, info-gate, gamed and manage ports in the original order.
- LTCG removed constant args: `Network::Initialize` gets only the worker count. The `OpenPort` bools are false, true, false.
- BUG comments are kept, not fixed in a way that changes the client view:
  - The account inventory port uses `_maxNPSessionCount + 1`.
  - The manager pointers have no null check before use.
  - `HelloReq` has no null check after `Alloc`.
- The senders use the original block order: on `Compose` fail, write the log; else send.
- `PacketHandler` uses the original order: the range check first, then the auth branch, then `removeReferenceCount`. The log 71 path returns false.
- `ManageChannel` gets `explicit ManageChannel(unsigned short)` and `GetManageWid()`.
- CMakeLists.txt not changed. No inline asm or byte tricks. IDA not opened.

## Checks

| Check | Result |
| --- | --- |
| REF build `builds-19/main-build-sNkBoZmW` (`e5d9fe2`) | 940 paired, 757 MATCH (674 before), lost 0 |
| NOREF build `builds-19/noref-build-QhwbfZYT` (`e5d9fe2`) | 1221 paired, 987 MATCH (973 before, 1205 paired), lost 0 |
| `pilot.py gate` (18 card IDs) | 13 of 13 pool IDs clear (9 before); 5 IDs are not in the ready pool; clear pool 276 -> 279 |
| `gate_fast.sh` (fresh clone of `e5d9fe2`) | rc 0, gate ok, parity ok, 478 s |
| `strict.py` (5 exes, `cfg` level) | no FAIL; LobbyDaemon cfg 594 -> 666 (841 -> 940 paired); LobbyGate cfg 515 -> 516; others same |
| `proof.py --base 7b92217 --candidate e5d9fe2` | verdict `review`; 0 lost, 0 strict regress, 0 cfg regress, 0 reasons; 45 credited, 38 review items |
| `review.py run` (ledger `/data/parity-v2/gap/review-19/ledger.sqlite`) | 14 accept, 24 reject (22 precheck, 2 model), 0 park; 79,354 tokens |
| `integrate.check_proof` (dry) | REFUSED: reject receipts and no operator exclude receipt |

## MATCH

| Exe | Before | After | Lost |
| --- | --- | --- | --- |
| CacheGate | 456 | 456 | 0 |
| LobbyGate | 658 | 658 | 0 |
| SmartCouponDaemon | 630 | 630 | 0 |
| PostOfficeDaemon | 694 | 694 | 0 |
| LobbyDaemon (REF) | 674 | 757 | 0 |
| LobbyDaemon (NOREF) | 973 (1205 paired) | 987 (1221 paired) | 0 |

| Gain | Predicted | Real |
| --- | --- | --- |
| REF | +43.4 | +83 |
| NOREF | +14.4 | +14 |

REF gains more than predicted. `initNetwork` makes the whole network chain live: `Network`, `Port`, `PortListener`, `IoWorker`, `Crypto`, `Aes`, `Blowfish`, the packet buffer handler classes, zstd helpers and `CliSessionTable::Select/Delete_index_account`.

## Review rejects

| Items | Cause | State |
| --- | --- | --- |
| 22 precheck rejects (`P2_cc`, `P3_imm`, `P1_calls`) | Branch inversions and immediates differ. 21 are earlier lifted chain bodies (Aes128NI, Blowfish::Encrypt, Ctr, Crypto, Prng::Initialize, Ripemd160, Port, PortListener, Session::Accept, Connection::Accept, packet buffer handlers, CliSessionTable index helpers). They become live now. `LobbyDaemon::initNetwork` fails `P2_cc` (jg vs jle at branch 1). | open ❓ |
| `LobbyGateChannelManager::OnConnect` (model) | The original reads `session->_id` before the second `Network::GetAddressStringW` call; the build reads it after. | open |
| `PortListener::HandleFailedEvent` (model) | The original reads `_portInstance->_id` before `WSAGetLastError`; the build reads it after. | open |

Credited today: 45 auto + 14 review accept = 59 of the 83 new REF MATCH.

## Open items

- `CleanupGameAccountIdIndexReq` and `CleanupPcidIndexReq`: the guard style of `a538d2b` scored 91.2 and 93.9. The nested style of `e5d9fe2` scores 84.8 and 85.7. The original starts with `cmp <zero reg>, ax` after `Decompose` and puts the decompose-fail block first ❓. Try the guard style again with other locals.
- `PacketHandler` (93.0): the original logs "handle begin" and "handle end" around the call in one branch ❓. Check the log lines 87 and 89.
- `initNetwork` NOREF DIFF 96.3 (REF MATCH): NOREF inlining differs ❓.
- The NOREF pairing of the stub ctors `ActivateGradeJob`/`CreateCharacterJob`/`~ChangeCharacterAppearanceJob` moved (ICF folds identical stubs). No MATCH changed.
- Branch is not merged into bns-lift. Merge is the parent's decision.
