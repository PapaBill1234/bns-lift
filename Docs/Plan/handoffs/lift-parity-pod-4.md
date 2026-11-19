# lift-parity-pod-4 handoff

## Result
- Status: partial. POD is at 671/759 (88.4 %). The goal was 684 (90 %).
- `tools/gate.sh`: gate ok. `tools/parity.sh`: parity ok. MATCH -> DIFF 0 and MATCH name gone 0 in all 4 exes.

| Exe | Main MATCH | Now | Gain | New MATCH |
| --- | --- | --- | --- | --- |
| CacheGate | 448 | 448 (91.2 %) | +0 | none |
| LobbyGate | 627 | 627 (84.8 %) | +0 | none |
| SmartCouponDaemon | 582 | 584 (87.3 %) | +2 | `BnsCommonConfig::LoadBnsCommonConfig`, `ReloadBnsCommonConfig` |
| PostOfficeDaemon | 665 | 671 (88.4 %) | +6 | `CacheGateSessionHandler::OnConnect`, `OnClose`, `HandlePostOfficeServiceCheckPostCapacityReq`, `BnsCommonConfig::LoadBnsCommonConfig`, `ReloadBnsCommonConfig`, `PostInfo::PostInfo` |

Total gain over main: +8.

## Changes
- `CacheGateChannel.cpp`: `OnConnect`/`OnClose` read globals and fields again at each use (lessons A26).
- `WorldPacketHandler.cpp/.h`: `CheckPostCapacityReq` uses the single-expression `::new` (A27). The `CheckPostCapacityRelayContext` ctor sets `_response` in the init list.
- `StringUtil.h/.cpp`: `ID128_GUID_ZERO` is `id128 const` (PDB `?ID128_GUID_ZERO@@3Tid128@@B` in all 4 exes).
- `BnsCommonConfigDefinition.h`: per-exe ctor form. SCD and POD copy the id128 fields with `memcpy` (A28).
- `PostOfficeDB.cpp/.h`: `AutoDbTran(dbId, timeoutSec)` ctor. Score only (`LoadPostList` 98.3 -> 99.1, `LoadRetryReadyPostList` 98.6 -> 99.1).
- `PingGenerator.cpp`: named `PingRelayRequest` local before `Alloc`. Score only (97.0 -> 99.2).

## Unfixed DIFF functions in scope (function, score, signal, cause, why stopped)
- `PingGenerator::sendPing` 99.2, refs (`_instance` 1 less): LTCG propagates the constant `this` into `checkCacheGateServiceState`, so the caller does not load `_instance`; no legitimate source form; stopped (compiler).
- `PostOfficeDaemon::checkCacheGateServiceState` 98.4, refs: same LTCG `this` propagation (ours loads `_instance` inside, orig uses `rcx+0x840`); a source change would only fool funcdiff; stopped.
- `PostOfficeDB::LoadPostList` / `LoadRetryReadyPostList` 99.1, calls: register hoisting duplicates the loop header (one more `memset, memset, Fetch`); 3 tries with no gain; stopped.
- `WorldConfigManager::setupWorldConfigList` 98.6, refs: orig loads `L"world config manager"` again at 3 more log sites, ours keeps it in a register; register allocation; not fixed.
- `AgentSessionHandler::OnClose` 97.6, refs: ours loads `L"AgentSessionHandler::OnClose"` and `L"agent channel"` once more (the opposite of the item above); register allocation; not fixed.
- `PingRelayContext::processRelayResponse` 97.6, calls+refs: failure-first form was worse in round 3 (B); no new idea.
- `ManagementSessionHandler::PacketHandler` 97.8, calls: the handler call is at the end in the original (lessons D); block layout; not tried, out of turns.
- `HandlePostOfficeRegisterPostReq` 98.0, calls+refs: single-expression `::new` (A27) gave no change; block layout (D, 0x1aaa0); stopped.
- `DeliverPostRelayContext::processRelayResponse` 96.5, calls+refs: ❓ not examined in this card; out of turns.
- `RelayTimeoutChecker::checkRelayTimeout` 96.3, consts: ❓ not examined; out of turns.
- `parseHexInt` 97.4 / `parseDecInt` 94.4, consts: ❓ constant lowering, not examined; out of turns.
- `HandlePostOfficeHelloReq` 95.6, consts / `HandlePostOfficeServiceRegisterPostReq` 95.6, refs: ❓ not examined; out of turns.
- `CachedWatchdogManager::updateWorldList` 95.5, `UnsentPostContextManager::updateWorldList` 90.5, `WorldConfigManager::updateWorldList` 80.2: block layout; `goto` and RAII forms failed (B); stop list.
- `UnsentPostContextManager::initContextManager` 92.9: same as `updateWorldList`; stop list.
- `WorldConfigManager::loadWorldConfigFile` 94.3, calls: success-first form was worse (B); no new idea.
- `HandleCacheGateFragmentRelay` 94.7, `HandleCacheGateRelay` 92.8 (shared POD form): 3 forms in round 3 (B, 93.3 best); not tried again.
- `CacheGateChannel::SendRelayRequest` 94.1, `SendFragmentRelayRequest` 86.9, calls: ❓ inline decision of the send helpers; not examined; out of turns.
- `CheckPostCapacityRelayContext::ComposeResponsePacket` / `RetrieveCharacterInfoRelayContext::ComposeResponsePacket` 90.5, consts: constants with no known cause (D).
- `PostInfo::CheckValidityPostData` 90.9, consts: switch lowering 0x2/0x7 against 0x5 (D).
- `PostOfficeDB::LoadSinglePost` 88.4 / `LoadRetryReadySinglePost` 88.8: orig merges 17 `statmentErrorLog` calls into one site (D); needs a full rewrite; out of turns.
- `PostDeliveryEvent::deliverPost` 85.4, calls: ❓ not examined; out of turns.
- `PostOfficeDB::RegisterPost` 84.0: ❓ not examined; out of turns.
- `HandleCacheGateRelayFail` / `HandleCacheGateRelayInvalid` 82.7: orig has 3 `ProcessRelayResponse` calls (D); not tried; out of turns.
- `PostOfficeDaemon::initialize` 67.8: EH state and the `wmain` inline (ehstate-4 owns `wmain`); not changed.
- `CacheGateChannel::combineFragmentRelayFormat` 53.9: ❓ not examined; out of turns.
- Shared BloodLib and crypto DIFFs (`BigInteger::*`, `aes128*`, `Session::*`, `PipeConsole::*`, `Network::*`): out of scope; stop list (lessons D).

## Do not try again
- Single-expression `::new` in `MakePostContext` (4 loaders worse) and in `HandlePostOfficeRegisterPostReq` (no change).
- `LoadPostList` success-first reorder (worse).
- `ID128_GUID_ZERO` const alone, or a `.id[0]/.id[1]` copy: the compiler still merges the loads.

Turns: 150
