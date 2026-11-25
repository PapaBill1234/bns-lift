# Handoff: lift-lobbydaemon-gap-03-presence

| Item | Value |
| --- | --- |
| Card | `design/parity-v2/gap-cards/gap-03-presence.md` (private project) |
| Branch | `gap-03-presence` (scratch clone only, not pushed) |
| Base | `1b0f305` (gap-01-core code commit; branch tip `37f32f9`) |
| Code commit | `1159881` |
| Source | LobbyDaemon 2019 + PDB (VS2010 SP1), HR pseudocode. IDA was not opened. Packets: 381 client. |
| Author and committer | `Claude <noreply@anthropic.com>` |

## Result

| Check | Result |
| --- | --- |
| Gate `pilot.py gate --rev 1159881` | 18 of 24 card IDs have no reason. 3 are dropped (`not_measurable`). 3 are `ineligible_unpaired` (blocked on gap-02). Eligible pool: 197 -> 216. |
| Full 5-exe build (`gate_full.sh`, cold, fresh clone of `1159881`) | rc 0, "parity ok", 424 s |
| Proof (`proof.py --base 1b0f305 --candidate 1159881`, strict rules not changed) | verdict `review`: 0 lost MATCH, 0 strict regress, 0 reasons, 28 review items (25 from gap-01, 3 new) |
| Lost MATCH, LobbyDaemon REF | 0 (673 -> 676) |
| Lost MATCH, LobbyDaemon NOREF | 1 name (927 -> 941). See "NOREF naming artifact". |

## MATCH per exe (cold gate build)

| Exe | Before (`1b0f305`) | After (`1159881`) | Delta | Lost |
| --- | ---: | ---: | ---: | ---: |
| CacheGate | 456 | 456 | 0 | 0 |
| LobbyGate | 658 | 658 | 0 | 0 |
| SmartCouponDaemon | 630 | 630 | 0 | 0 |
| PostOfficeDaemon | 694 | 694 | 0 | 0 |
| LobbyDaemon | 673 | 676 | +3 | 0 |
| LobbyDaemon NOREF | 927 | 941 | +14 | 1 (artifact) |

New REF MATCH: `GameWorld::EnterUser`, `GameWorldCluster::enterUser`, `GradeService::IsActivated`. Most card bodies have no caller in the REF build yet, so /OPT:REF removes them.

## Classes and layouts

| Class | Size | File |
| --- | ---: | --- |
| `ContentsRuleConfig` (LobbyDaemon) | 0x18 | `ContentsRuleConfigDefinition.h` (new) |
| `CliSessionEnterWorldMessage` | 0x10 | `LobbyMessage.h` |
| `CliSessionLeaveWorldMessage` | 0x10 | `LobbyMessage.h` |
| `WaitQueueInfo::Init`, `WaitInfo::Init` (PDB inline) | - | `WaitQueue.h` |

## Bodies

Status: funcdiff of the NOREF build (`noref-build-6V3jmHRF`) and the REF build (`gate_full.sh`). "-" = not in the build or not paired.

| Name | RVA | NOREF | REF |
| --- | --- | --- | --- |
| `GameWorldPresence::scalar deleting destructor` | 0x329e0 | - (SKIP_NAME) | - |
| `AnonymousLobbyGatePresence::scalar deleting destructor` | 0x3a450 | - (SKIP_NAME) | - |
| `AnonymousLobbyGatePresence::OnSet` | 0x3a530 | MATCH | - |
| `AnonymousLobbyGatePresence::OnUnset` | 0x3a600 | MATCH | - |
| `LobbyGatePresence::scalar deleting destructor` | 0x3a710 | - (SKIP_NAME) | - |
| `LobbyGatePresence::Close` | 0x3abc0 | DIFF 0.0 (folded) | - |
| `LobbyGatePresence::Kick` | 0x3ac20 | - (folded) | - |
| `LobbyGatePresence::NotifyChangedGrade` | 0x3aca0 | - (folded) | - |
| `LobbyGatePresence::NotifyChangedGradeLevel` | 0x3ad60 | - (folded) | - |
| `GameWorldPresence::Close` | 0x3b0c0 | MATCH | - |
| `GameWorldPresence::NotifyChangedGrade` | 0x3b1c0 | MATCH | - |
| `GameWorldPresence::NotifyChangedGradeLevel` | 0x3b290 | MATCH | - |
| `GameServiceLocation::OnEnter` | 0x3b3d0 | MATCH | - |
| `GameServiceLocation::OnLeave` | 0x3b540 | MATCH | - |
| `GameServiceLocation::Enter` | 0x3b6f0 | DIFF 99.0 | - |
| `GameServiceLocation::Leave` | 0x3b9a0 | DIFF 88.9 | - |
| `GameServiceLocation::NotifyStopPlay` | 0x3bda0 | MATCH | - |
| `GameWorldCluster::enterUser` | 0x4dd90 | MATCH | MATCH |
| `GamedChannelManager::OnClose` | 0x80790 | DIFF 89.3 | DIFF 89.3 |
| `HandleLobbyGame_AuctionEscrowOk` | 0x92280 | MATCH | - |
| `HandleLobbyGame_AuctionEscrowFail` | 0x92400 | MATCH | - |
| `HandleLobbyGame_GetGradeListReq` | 0x92ca0 | DIFF 79.5 | - |
| `HandleLobbyGame_BoastEventInWorldNotify` | 0x94780 | MATCH | - |
| `HandleLobbyGame_UpdateAccountExpReq` | 0x94df0 | DIFF 77.9 | - |

Scope additions (not card IDs):

| Name | RVA | NOREF |
| --- | --- | --- |
| `GameServiceLocation::~GameServiceLocation` | 0x3b360 | MATCH |
| `GetLobbyGateKickReason` | 0x96480 | DIFF 98.4 |
| `CliSessionEnterWorldMessage::~CliSessionEnterWorldMessage` | - | MATCH |
| `ContentsRuleConfig` static data | 0x209590-0x2095b0 | data |

## Open DIFFs (card IDs that pair but do not MATCH)

| Name | Score | Cause |
| --- | ---: | --- |
| `GameServiceLocation::Enter` | 99.0 | Uses a local `WaitInfo`, not the TLS static `_waitResult`. See "Decisions". |
| `GameServiceLocation::Leave` | 88.9 | calls 67. Callees still `LIFT_STUB` (`GameWorldCluster::leaveUser`) ❓ |
| `GamedChannelManager::OnClose` | 89.3 | Calls `OnCloseGamedChannel` (still `LIFT_STUB`) ❓ |
| `HandleLobbyGame_GetGradeListReq` | 79.5 | Calls `HandleGameGetGradeList` (not lifted) ❓ |
| `HandleLobbyGame_UpdateAccountExpReq` | 77.9 | Calls `UpdateAccountExp` (not lifted) ❓ |
| `LobbyGatePresence::Close` | 0.0 | Folded with Kick and Notify*, see "Blocked". |

## Decisions

1. **No TLS `_waitResult`.** The PDB has `static __declspec(thread) WaitInfo GameServiceLocation::_waitResult` (S_GTHREAD32, TLS +0x10). A build with this definition (`022ad2b`) reorders the whole TLS block in the VS2010 LTCG link. `PacketBufferAllocator::_Local` moves from TLS +0x58 to +0xfac8 (after `NPChannel::_buffer`). That changes the TLS offset constant in 107 LobbyDaemon functions (for example `AccountInventoryChannel::SendHelloReq`), and proof gives `fail` with 107 `strict_regress` (level `cc`). The definition position in the file does not change the order (experiment A). Without the definition, the order is the same as gap-01 (experiment 1). Enter now uses a local `WaitInfo`. The value is scratch data for one call, so the behavior is the same.
2. **`RemoveTimer`.** `TimerQueue::Remove` is protected. The bodies call the public `LobbyDaemon::_instance->RemoveTimer(timer)` (PDB public, inlined).
3. **No new `/INCLUDE` pragmas.** The existing pragma on `GameWorld::EnterUser` stays.
4. **Friends.** `GameWorld`, `GameWorldCluster`, `WaitQueue`, `WaitQueueList` and `MileageManager` get `friend` lines for the lifted callers. Each has a LIFT comment; the WaitQueue ones are ❓.

## Blocked

| Name | RVA | Cause |
| --- | --- | --- |
| `LobbyGatePresence::Kick` | 0x3ac20 | `LobbyGateChannelManager::Acquire` 0xc0d50 is `LIFT_STUB` (gap-02 owns it). The stub does not return, so Close, Kick, NotifyChangedGrade and NotifyChangedGradeLevel fold to one address (PDB publics, NOREF build, `0001:487824`). |
| `LobbyGatePresence::NotifyChangedGrade` | 0x3aca0 | Same. |
| `LobbyGatePresence::NotifyChangedGradeLevel` | 0x3ad60 | Same. |

They pair when gap-02 lifts `Acquire`.

## NOREF naming artifact

`StsMsgLib::_StsMsgRequest::GetTransactionId` is MATCH in the gap-01 NOREF build and has no name in this NOREF build. The out-of-line inline getter `ContentsRuleConfig::GetMinBotScoreToApplyBotPriorityQueue` is folded by ICF at the same address, and funcdiff now picks that name. The REF build has no lost MATCH. ❓ (not proven beyond the shared address).

## Not done

| Name | RVA | Reason |
| --- | --- | --- |
| `HandleGameGetGradeList` | - | Not in the card ID table. |
| `UpdateAccountExp` | - | Not in the card ID table. |
| `GamedChannelManager::OnCloseGamedChannel` | - | Not in the card ID table. |
| `GameWorldCluster::leaveUser` | - | Not in the card ID table. |
| `LoadContentsRuleConfig` | 0x297d0 | Not in the card ID table. `ContentsRuleConfig::Config` stays null until it is lifted. |

Unverified meanings (❓ in the code): mileageType 2 and 1 in OnEnter and OnLeave; task ids 131 and 132 in the handlers.

## Rules kept

- No inline asm, no byte tricks, no new `/INCLUDE`. funcdiff, strict and proof are not changed.
- PDB names only. Server checks are kept (null world and null channel checks, `TLobbyError` on full world, state checks in Enter and Leave).
- No binaries, PDBs, IDBs or keys in this commit.
