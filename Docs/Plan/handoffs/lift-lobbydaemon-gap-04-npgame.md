# Handoff: lift-lobbydaemon-gap-04-npgame

| Item | Value |
| --- | --- |
| Card | `design/parity-v2/gap-cards/gap-04-npgame.md` (private project) |
| Branch | `gap-04-npgame` (scratch clone only, not pushed) |
| Base | `eb68b2a` |
| Code commit | `9f95268` |
| Source | LobbyDaemon 2019 + PDB (VS2010 SP1), HR pseudocode. IDA was not opened. Packets: 381 client. |
| Author and committer | `Claude <noreply@anthropic.com>` |

## Result

| Check | Result |
| --- | --- |
| Gate `pilot.py gate --rev 9f95268` | 32 of 32 card IDs have no reason. Eligible pool (no reason): 284 of 856. |
| Full 5-exe build (`gate_full.sh`, fresh clone of `9f95268`) | rc 0, "parity ok", 570 s |
| Proof (`proof.py --base eb68b2a --candidate 9f95268`) | verdict `review`: 0 lost MATCH, 0 strict regress, 0 reasons, 23 review items (22 inherited, 1 new) |
| Review (`review.py run`, fresh ledger `review-04/ledger.sqlite`, digest 7ff33683) | 22 accept, 1 reject, 0 park |
| Integrate dry check (`integrate.check_proof`) | refused: `SendRequestPresenceKick: reject` |

## MATCH per exe

| Exe | Before (`eb68b2a`) | After (`9f95268`) | Delta | Lost |
| --- | ---: | ---: | ---: | ---: |
| CacheGate | 456 | 456 | 0 | 0 |
| LobbyGate | 658 | 658 | 0 | 0 |
| SmartCouponDaemon | 630 | 630 | 0 | 0 |
| PostOfficeDaemon | 694 | 694 | 0 | 0 |
| LobbyDaemon (REF) | 674 | 675 | +1 | 0 |
| LobbyDaemon NOREF | 973 | 1003 | +30 | 0 |

- REF new MATCH: `SendRequestPresenceKick`. It is the only sender with a lifted caller (LobbyGamePacketHandler). /OPT:REF removes the other senders.
- NOREF base: `builds-05/noref-build-3A46ADFJ` (eb68b2a). NOREF candidate: `builds-04/noref-build-9BCA9XIA`.
- NOREF new MATCH: 29 card IDs and `swprintf_s<33>`.

## Card IDs

Status: funcdiff. "-" = not in the REF build (no caller, /OPT:REF).

| Name | RVA | NOREF | REF |
| --- | --- | --- | --- |
| `NPServiceChannelManager::OnConnect` | 0xcfdb0 | MATCH | - |
| `NPGameServiceChannel::SendRequestConsumeGameToken` | 0xd0220 | MATCH | - |
| `NPGameServiceChannel::SendRequestAuthChangeMyUserNameIncomplete` | 0xd0370 | MATCH | - |
| `NPGameServiceChannel::SendRequestSlotGetSlot` | 0xd03d0 | MATCH | - |
| `NPGameServiceChannel::SendRequestSlotCreateActivitySlots` | 0xd0450 | MATCH | - |
| `NPGameServiceChannel::SendRequestSlotSetActivitySlotData` | 0xd0560 | MATCH | - |
| `NPGameServiceChannel::SendRequestPresenceLogin` | 0xd0650 | MATCH | - |
| `NPGameServiceChannel::SendRequestPresenceLogout` | 0xd0800 | MATCH | - |
| `NPGameServiceChannel::SendRequestPresenceKick` | 0xd09b0 | MATCH | MATCH |
| `NPGameServiceChannel::SendResponseGateLogoutUser` | 0xd0e20 | MATCH | - |
| `NPGameServiceChannel::SendRequestChargeGetInfo` | 0xd0e90 | MATCH | - |
| `NPGameServiceChannel::SendRequestChargeStart` | 0xd0fc0 | MATCH | - |
| `NPGameServiceChannel::SendRequestChargeStop` | 0xd1110 | MATCH | - |
| `NPGameServiceChannel::SendRequestChargeAbandon` | 0xd1230 | DIFF 93.3 | - |
| `NPGameServiceChannel::SendResponseChargeRequestStopFail` | 0xd1310 | MATCH | - |
| `NPGameServiceChannel::SendRequestListUserLastPresences` | 0xd1390 | MATCH | - |
| `NPGameServiceChannel::SendRequestGradeListAllGrades` | 0xd1410 | MATCH | - |
| `NPGameServiceChannel::SendRequestGradeActivateGrade` | 0xd1510 | MATCH | - |
| `NPGameServiceChannel::SendResponseGameAuctionEscrowOk` | 0xd1610 | MATCH | - |
| `NPGameServiceChannel::SendResponseGameAuctionEscrowFail` | 0xd1710 | DIFF 88.9 | - |
| `NPGameServiceChannel::SendResponseGameAuctionRollbackEscrowOk` | 0xd17f0 | MATCH | - |
| `NPGameServiceChannel::SendResponseGameAuctionRollbackEscrowFail` | 0xd1860 | MATCH | - |
| `NPGameServiceChannel::SendResponseGameAuctionDeliveryOk` | 0xd18e0 | MATCH | - |
| `NPGameServiceChannel::SendResponseGameAuctionDeliveryFail` | 0xd19e0 | DIFF 95.2 | - |
| `NPGameServiceChannel::SendRequestListUserBans` | 0xd1af0 | MATCH | - |
| `NPGameServiceChannel::SendRequestRMSInquiry` | 0xd1be0 | MATCH | - |
| `NPGameServiceChannel::SendRequestProfileGetUserProfile` | 0xd1ce0 | MATCH | - |
| `NPGameServiceChannel::SendRequestGameTimeGetGameTime` | 0xd1d60 | MATCH | - |
| `NPGameServiceChannel::SendRequestPromotionStampListCurrentPromotions` | 0xd1de0 | MATCH | - |
| `NPGameServiceChannel::SendRequestPromotionStampGetPromotionPolicy` | 0xd1f00 | MATCH | - |
| `NPGameServiceChannel::SendRequestPromotionStampGetUserPromotionStatus` | 0xd1f90 | MATCH | - |
| `NPGameServiceChannel::SendRequestPromotionStampAttendPromotionSecured` | 0xd20d0 | MATCH | - |

## Changes

| File | Change |
| --- | --- |
| `src/Server/LobbyDaemon/NPServiceChannel.h` | `NPGameServiceChannel` size assert 0x40. `NPServiceChannelManager` gets OnConnect, OnClose, HandleMessage (0xd0100) and the members `_init`, `_gameServChannel`. |
| `src/Server/LobbyDaemon/NPServiceChannel.cpp` | 31 senders and `NPServiceChannelManager::OnConnect` lifted. 27 `StsMsgLib` message structs with PDB names and size asserts. `_StsMsgResponse` virtual bodies. Initialize, OnClose and HandleMessage stay LIFT_STUB. |
| `src/Server/SmartCouponDaemon/NPChannelBase.h` | `_StsMsgResponse` declares GetCommand, GetTransactionId, GetMessageType (PDB: defined in NPServiceChannel.obj). SmartCouponDaemon does not change (proof: 0 changes). |
| `src/Server/Shared/NPChannel2.cpp` | `NPChannel::SendMsg` is `__declspec(noinline)`. The LobbyDaemon and SmartCouponDaemon originals call it at every site. Without it, LTCG inlines it into PresenceKick and PresenceLogout. |

## Decisions

| Decision | Why |
| --- | --- |
| No `/INCLUDE` pragmas | pilot.py FORBIDDEN rejects them. The gate pairs the senders through the NOREF build. |
| No new TLS variable | `npAddressStringA` uses the existing `__ip_addr_string_a__` (Network.cpp). A new TLS variable reorders the TLS block (gap-03). |
| Unused parameters stay unnamed | LTCG removed them in the original: `t` (PresenceKick), `gameAlias` (PresenceLogin), `passwordHash` (AuthChange, sends L"dummy"), `slotType` and `count` (SlotCreate, sends L"activity" and 1), `clientInstanceCount` (ChargeStart, sends 1), `requestEvent` (RMSInquiry, sends "bns:trade"), `escrowId` (EscrowFail). |
| OnConnect inlines `PipeConsole::SetInvalidInfo(..., false)` | The original inlines it (PipeConsole.cpp line 837 free). Same form as `LobbydReloadInvalidRestoreTimer::restoreInvalid`. Public members only. |
| `swprintf_s(slotData, ...)` template form | The original calls `swprintf_s<33>`. `crt_cpp_overload.h` under `__clang__` only. An explicit size loses 2 MATCH. |
| Server checks kept | All null-transaction checks with Log::Write and AlertSender::Write, and the app-group-code buffer check. |

## Review reject (SendRequestPresenceKick)

| Item | Value |
| --- | --- |
| Reviewer reason | The original has `xor r9d,r9d` before `NPChannel::SendMsg`. The REF build does not. So r9 (context) holds `force`. |
| Evidence against | The REF `NPChannel::SendMsg` does not read r9. LTCG propagates the constant `context = nullptr`, because every live REF caller passes nullptr. |
| NOREF build | The stream is equal to the original, except the ICF-folded vftable name. `xor r9d,r9d` is present. |
| Source | `return SendMsg(&msg, true, nullptr);` |
| Status | Not changed. The parent decides: re-review, or accept as a REF-build artifact ❓. |

## Open items

| Item | Note |
| --- | --- |
| Integrate refused | 1 review reject (above). |
| 3 DIFF card IDs | ChargeAbandon 93.3 (store order). EscrowFail 88.9 (original keeps a dead `memset` of escrowIdStr after LTCG removed the escrowId branch; the lift has no caller to reproduce this). DeliveryFail 95.2 (register choice). |
| LIFT_STUB | `NPServiceChannelManager::Initialize`, `OnClose`, `HandleMessage` (0xd0100). Not card IDs. While Initialize is a stub, OnConnect is not reachable in REF. |
| Proof review items | 22 items come from earlier cards (Docs/Parity baseline 645). All 22 accept. |
| Merge | Not merged, not pushed. Merge is the parent's decision. |
