# Parity review 3 (lift-parity-review-3, 2026-11-18)

## 1. Measurement

`tools/gate.sh`: gate ok. `tools/parity.sh`: parity ok, MATCH -> DIFF 0 in all 4 exes. No source change in this card.
`tools/parity_shared.py build-vs2010`: shared library 490/549 = 89.3 %.

| Exe | Review 2 | Review 3 (now) | Change | 90 % needs | Gap to 90 % | Paired | Misses (orig only) | Mean score |
| --- | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: |
| CacheGate | 420/491 = 85.5 % | 448/491 = **91.2 %** | +28 | 442 | 0 (95 %: 467, gap 19) | 488 | 3 | 99.3 |
| LobbyGate | 530/739 = 71.7 % | 627/739 = **84.8 %** | +97 | 666 | 39 | 736 | 3 | 98.5 |
| SmartCouponDaemon | 510/669 = 76.2 % | 582/669 = **87.0 %** | +72 | 603 | 21 | 667 | 2 | 99.0 |
| PostOfficeDaemon | 588/759 = 77.5 % | 665/759 = **87.6 %** | +77 | 684 | 19 | 754 | 5 | 98.9 |
| Shared library | 421/499 = 84.4 % | 490/549 = **89.3 %** | +69 | 99 %: 544 | 54 | - | - | - |

- CG is at 90 % or more. LG, SCD and POD are below 90 %. So this review queues round 4 (task 5), not a 90+ round.
- Each exe gained 2 % or more (CG +5.7, LG +13.1, SCD +10.8, POD +10.1). No stall check is necessary.
- The shared denominator changed from 499 to 549: the crypto functions now pair (cryptolib-3).
- Misses fell from 4/81/50/53 to 3/3/2/5. Nearly all functions pair now. The work that is left is DIFF functions.

## 2. What worked (round 3)

| Card | CG | LG | SCD | POD | Sum | Turns | MATCH per 100 turns | Estimate (review-2 section 6) | Main cause fixed |
| --- | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | --- |
| lift-parity-perexe-3 | +1 | +3 | +2 | +4 | 10 | 75 | 13 | +6 | per-exe define, `StlMemory.h` case forms, `deallocateCrypt` chain |
| lift-parity-cryptolib-3 | 0 | +41 | +28 | +28 | 97 | about 85 | 114 | +116 | lift the closed-lib callers, `/INCLUDE`, PDB param facts |
| lift-parity-inline-3 | +3 | +9 | +3 | +6 | 21 | about 100 | 21 | +25 | `Log::Log` stores, `InitSymbol` noinline, `LobbyD::Send*` init |
| lift-parity-order-3 | +6 | +5 | +7 | +5 | 23 | 133 | 17 | +20 | statement order in daemon startup and config load |
| lift-parity-consts-3 | +6 | +7 | +6 | +6 | 25 | 66 | 38 | +16 | `Session::Accept`/`recv` reads, `ToPacket`, `SysInfo` loops, `initAllocator` |
| lift-parity-arraynew-3 | 0 | +5 | 0 | 0 | 5 | about 53 | 9 | +10 | vec new in LG `Client.cpp` |
| lift-parity-handlers-3 | 0 | +1 | +1 | +8 | 10 | about 105 | 10 | +25 | PacketHandler form, failure-first management handlers, `AutoCS` scope |
| lift-parity-dbbind-3 | 0 | 0 | 0 | 0 | 0 | 42 | 0 | +6 | score only (SCD 95 to 98, POD 88 to 99) |
| manual-parity (astra + opus 6.2) | +12 | +26 | +25 | +20 | 83 | - | - | - | placement delete, `inline_depth(0)`, statement order, funcdiff fix 9 and 10 |
| **Sum** | **+28** | **+97** | **+72** | **+77** | **274** | about 659 (cards) | 29 (cards) | | |

- The 8 cards gave 191 MATCH. The manual work gave 83. Without the manual work the result is CG 436, LG 601, SCD 557, POD 645.
- dbbind-3 made SCD `DbTransaction::BindCol` 0x20e40 MATCH. The manual work counted that MATCH first, so the card row shows 0.
- Estimates of review 2 against the result (with the manual work): CG 440 -> 448 (+8), LG 625 -> 627 (+2), SCD 585 -> 582 (-3), POD 670 -> 665 (-5).
- The best card: cryptolib-3 (114 per 100 turns). It found one large cause (a closed library with no debug info).
  After it: consts-3 (38). The worst: dbbind-3 (0), arraynew-3 (9), handlers-3 (10).

Manual work, by method:

| Commit or method | Gain | Lessons |
| --- | ---: | --- |
| 27d5420 `AlertSender::run` separate stores | 4 | A19 |
| 46fe9c1 manual checks | 11 (LG 6, SCD 2, POD 3) | A2, A8 |
| beb4669 global placement delete, `::new` | 22 (CG 5, LG 5, SCD 6, POD 6) | A14 |
| Arithmetic and startup | 14 (LG 6, SCD 4, POD 4) | A4, A9, A21 |
| Logging and timers (`inline_depth(0)`) | 10 (CG 2, LG 2, SCD 4, POD 2) | A20 |
| funcdiff fix 9 (TLS address in separate blocks) | 15 (CG 3, LG 5, SCD 4, POD 3) | A1 |
| funcdiff fix 10 (public names of folded vtables) | 5 | A1, A21 |
| TLS buffer from `Network.cpp` | SCD 1 | A8 |

## 3. What did not work
- perexe-3: IDA did not open `CacheGate.exe.i64` (status 4). `Session::SendV` was not checked (0xf9e is there twice in the original).
  `parity_shared.py` showed DIFF where `<EXE>.funcdiff.json` showed MATCH (❓, lessons C4).
- inline-3: `UninstallService` (tail merge, 2 forms), `SetInvalidInfo` (3 forms), `Network::OpenPort` (constant propagation),
  `PacketBuffer::Compose` case P (`memcpy` tail merge, 96.3 -> 93.0), `Session::HandleEvent` (an extra `Log::Write`, 98.5),
  `TextStream` Destroy (an extra `<indirect>`, 93.3).
- order-3: `PipeConsole::run` (3 tries, stop). `Channel::MakeSession` port-first lost MATCH in CG, LG, POD (the manual work then fixed SCD
  with a per-exe file). POD `UnsentPostContextManager` `initContextManager`/`updateWorldList`: `goto` and RAII forms give the same layout.
  SCD `DChannelMgr::SetupDaemonList` stays at 96.3 (ref order, const 0x178).
- consts-3: `Session::Session` and `StaticPageMemoryManager::Initialize` (LTCG address fold), `HandleFailedEvent` (register form).
  Some named functions were not examined.
- arraynew-3: the `Finalize` `.tls` 0x18/0x10 is on the stop list. `BroadcastAnnounceNotify` branch swap: no gain. `MakeGateKey` 94.3 not tried.
- handlers-3: `HandleCacheGateRelay` (3 forms, 93.3). RelayFail/Invalid need 3 `ProcessRelayResponse` calls (not tried).
  `ManagementSessionHandler` 97.8 (the handler call is at the end in the original). POD pool index in the inlined `Packet::Allocate` (orig 0x28, ours 0x90).
  Many LG and SCD handlers were not tried.
- dbbind-3: the SCD loaders inline only column 1; ours has one more `Fetch`, consts 0x2/0x3/0x5, one more `L"db"` ref (95.0 to 97.8).
  POD 0x14e50 98.3 and 0x190f0 98.6 (rotated fetch loop, const 0x23). POD 0x15fa0 88.4 and 0x18010 88.8 (one shared `statmentErrorLog` site,
  "Not initialized" log before the binds). `RegisterPost` not examined.
- Manual work: AES key setup in groups of 5 and the dec key pointer, `CacheD::Verify` mismatch-first, `loadUnhandledGameEventLog` success-first,
  `InitSymbol` common unload, `HandleEvent` common log, `UninstallService` `wprintf` select, GUID word loads, `PingRelayContext` failure-first
  (97.6 -> 95.1), `clearPacketBufferList` `inline_depth(1)`, `Network::Clear` countdown or cached port, `LoadCachedListConfigFile` loop (96.3),
  `ObjPool` init list, `BigInteger::mul` pointer loop, explicit `Allocate` in `Client::Send*`, `loadWorldConfigFile` success-first.
  All in lessons B.

## 4. Turn cost
- Round 3 cards: about 659 turns for 191 MATCH = 3.5 turns per MATCH (round 2: 2.8).
- Without cryptolib-3: about 574 turns for 94 MATCH = 6.1 turns per MATCH. The cost of a MATCH rises again.
- The manual work gave 83 MATCH. It used methods that the cards did not use: PDB facts first, `inline_depth(0)`, `::new` with the global
  placement delete, and tool checks (fix 9, fix 10). Round 4 cards name these methods (lessons A1, A14, A20, A21).
- Cards with many "not tried" items (consts-3, handlers-3) stopped by turn budget. Round 4 cards are smaller and give a function list per card.

## 5. DIFF functions that are left, by cause class
Classifier: a scratch classifier on `funcdiff.py --show . --only` (rule by signal, as `triage.md`; same rules as review 2, plus the class
"EH state const" for the const `0xfffffffffffffffe`). One entry = one function in one exe. "Shared" = DIFF in 2 or more exes.

| Cause class | Shared entries | Exe-only entries | Round 4 card |
| --- | ---: | ---: | --- |
| Constants only (LTCG folding, line numbers, stack) | 57 | 31 | crypto-4, net-4, packet-4, exe cards |
| Other callee (inline choice, inlined crypto, closed-lib forms) | 19 | 42 | crypto-4, lg-4, scd-4, pod-4 |
| Refs (+ consts) | 31 | 25 | crypto-4, console-4, exe cards |
| Orig calls more (ours inlines) | 23 | 16 | crypto-4, net-4, console-4 |
| Call order (block layout) | 9 | 22 | console-4, scd-4, pod-4, cg-4 |
| Ours calls more | 11 | 17 | crypto-4, packet-4, exe cards |
| Call count | 5 | 3 | packet-4, console-4 |
| Path literal | 0 | 6 | lg-4 |
| EH state const (`-2`) | 4 | 2 | ehstate-4 |
| **Sum** | **159** | **164** | |

Per exe: CG 40 DIFF + 3 misses (22 ours-only), LG 109 + 3 (60), SCD 85 + 2 (28), POD 89 + 5 (29).
Shared library: 59 names are not MATCH in all 4 exes (549 - 490).

### Named causes with function lists
- **Crypto, shared** (LG, SCD, POD; 14 names): `BigInteger::Mul` (consts 0x1000/0xffffffe0, `_alloca`), `mul` x2, `sub`, `Sqr` (orig calls more),
  `Divide` 76.7, `InvMod`, `invMod` (ours inlines `LeftShift`, `add`, `sub`, `RightShift`), `expMod` (ours calls more), `OaepEncoder::Setup/encode/decode`,
  `Rsa::decrypt`, `RsaPublic::Setup`, `RsaPublic::~RsaPublic` (orig refs `??_7Ripemd128` and `??_7RsaPublic`; ours `??_7Rsa`).
  LG only: `Crypto::Create` 34.0, `Crypto::InstanceSize` 44.4, `Session::allocateCrypt` 67.4, `Dh::*`, `RsaPrivate::*`, `BigInteger::IsPrime` 82.2,
  `isPrimeMR` 88.4, `Session::completeHandshake` 55.6, `BroadcastCrypt`. Card crypto-4.
- **EH state `-2`** (A14): `wmain` x4 (CG 61.9, LG 66.7, SCD 66.7, POD 85.2), `FragmentPacketConcatenater::Clone` (LG, POD 93.3),
  LG `IdleWatcher::run`, SCD `NPServiceChannelManager::HandleMessage`, POD `operator delete[]` (score 0). Card ehstate-4.
- **BloodLib network**: `Session::HandleEvent` 98.5, `Session::HandleFailedEvent`, `Session::Connect` (LG, SCD), `Session::SendV` (CG; 0xf9e x2),
  `IoWorker::run` x4 (84.9), `SessionSendBuffer::clearPacketBufferList` x4 (orig calls `RefCntHistory::add`), `Network::Clear` x4 (97.2),
  `Network::OpenPort` (2 overloads). Card net-4.
- **Packet**: `PacketBuffer::Compose` x4, `Decompose` x4, `CheckCompose` (LG, POD), `RepeatPacketComposer::PushRepeatCount` (LG, POD),
  `FragmentPacketConcatenater::Add` (LG, POD); LG `Packet::Copy`, `PacketConcatenateBuffer::Decompose` 95.2, `ClientPacketBufferHandler::ToPacket` 85.2,
  `FragmentPacket::StartRepeat`. Card packet-4.
- **Console and config**: `PipeConsole::processCommand` x4, `PipeCommandProcess::processCommand` x4, `InitSymbol` x4 (98.0), `UninstallService`,
  `DaemonConfig::Dump` (CG, SCD), `BnsCommonConfig::Load`/`Reload` (SCD, POD); LG `PipeConsole::SetRunningInfo`, `IdleStateTable::scan`. Card console-4.
- **Handlers, shared**: `HandleCacheGateRelay`, `FragmentRelay`, `Hello`, `HelloFail`, `RelayFail`; `CacheGateSessionHandler::OnConnect`/`OnClose`. Cards pod-4, cg-4.
- **LG only**: `HandleLobbyLobbyGate_*` (about 12), `HandleLobbyGate_*` (5), `Client::Send*Ok` (3), `ContentsRuleConfig` (4 path literals),
  `LobbyGate::reload`/`initialize`/`AddJobTimer`/`PrintDependency`/`FailedEventObjectHandler`, `LobbyD::Hello`/`hello`, `LobbyDSessionHandler::OnConnect`/`OnClose`,
  `GateKeyManager::MakeGateKey` 94.3, `ClientManager::BroadcastAnnounceNotify` 97.8, `AlertSender::init`, `restoreInvalid`, `ClientSessionTimerJob::HandleEvent`,
  `ClientSessionHandler::OnClose`. Card lg-4.
- **SCD only**: `SmartCouponDB::Load*`/`Process*` (6), `DChannelMgr` (`writeFileUtf8` 59.3, `SetupDaemonListFromXml`, `PacketHandler`, `AddDaemon`,
  `~DChannelMgr`, `SetupDaemonList` 96.3), `EventNotiJob` (`Initialize` 77.8, `eventNotiRes`/`Req`), `HandleSmartCouponManager_*` (2), `HandleSmartCoupon_*` (3),
  `ManagerChannel::SendRetryCouponPublicationOk/Fail`, `NPServiceChannel::SendRequestEventNoti`, `GameEventConfig::Load`, `CouponJob::transit`,
  `NPChannel::SendMsg`, `NPTransactionRegistry::Register`, `SmartCouponDaemon::initialize`/`loadUnhandledGameEventLog`. Card scd-4.
- **POD only**: `PostOfficeDB` (`RegisterPost` 84.0, `LoadSinglePost` 88.4, `LoadRetryReadySinglePost` 88.8, `LoadPostList` 98.3, `LoadRetryReadyPostList` 98.6),
  `HandleCacheGateRelayFail/Invalid` 82.7, `combineFragmentRelayFormat` 53.9, `CacheGateChannel::Send*Request`, `PostOfficeDaemon::initialize` 67.8,
  `WorldConfigManager::updateWorldList` 80.2 / `loadWorldConfigFile` / `setupWorldConfigList`, `UnsentPostContextManager::*` (2), `deliverPost` 85.4,
  `HandlePostOffice*` (4), `ManagementSessionHandler::PacketHandler` 97.8, `PostInfo::*` (2), `ComposeResponsePacket` x2, `parseDecInt`/`parseHexInt`. Card pod-4.
- **CG only**: `CacheDList::clear` 61.1, `RemoveSessionAll`, `MakeSessionAll`, `LoadCachedListConfigFile`, `Initialize`; `CacheD::Verify`/`Initialize`,
  `CacheDChannel::onClose`, `HandleCacheGateHello` 87.2, `HandleCacheGateHelloFail`, `ClientManager::~ClientManager`, `ClientSideDaemonChannel::~ClientSideDaemonChannel`. Card cg-4.
- **Stop list** (do not try again without a new idea, lessons D): `aes128Table*` x4, `Session::Session`, `StaticPageMemoryManager::Initialize`,
  `ThreadManager::Initialize`, `Daemon::Start`, `PipeConsole::run`, `PipeConsole::SetInvalidInfo`, `WindowConsole::Open` (ICF),
  `EventNotiJob::finalize`, `JobManager::Execute*`, `Finalize` `.tls` 0x18/0x10, `ZSTD_compressBegin_internal` (vendor).
  Removed from the stop list in round 3: `TimerQueue::clearShortTermQueueSlot`, `LogMedia::Write` (now MATCH, A20), CRT placement delete (A14).

## 6. Plan for round 4
Shared cards first. Each card is one cause area with a named function list and a stop rule (3 tries with no score gain).
The cards touch disjoint source files where possible. Queue: `Docs/Plan/queue/lift-parity-review-3.tsv`.

| Card | Model | Cause | Exes | Expected gain (estimate) |
| --- | --- | --- | --- | --- |
| lift-parity-crypto-4 | opus | crypto DIFFs (14 shared names, LG crypto) | LG, SCD, POD | LG +12, SCD +5, POD +5 |
| lift-parity-ehstate-4 | sonnet:high | EH state `-2` with `::new` and the global placement delete (A14) | all | CG +1, LG +2, SCD +2, POD +2 |
| lift-parity-net-4 | opus | Session, IoWorker, Network, send buffer | all | CG +2, LG +2, SCD +2, POD +2 |
| lift-parity-packet-4 | opus | PacketBuffer, FragmentPacket, ToPacket | all | CG +2, LG +4, SCD +2, POD +2 |
| lift-parity-console-4 | opus | PipeConsole, CrashHandler, service console, config | all | CG +2, LG +3, SCD +3, POD +2 |
| lift-parity-lg-4 | sonnet:high | LG handlers and LG modules (A23, A19, A10, A6) | LG | LG +15 |
| lift-parity-scd-4 | opus | SCD DB loaders, DChannelMgr, EventNotiJob, handlers | SCD | SCD +10 |
| lift-parity-pod-4 | opus | POD DB loaders, relay handlers, WorldConfigManager | POD | POD +12 |
| lift-parity-cg-4 | opus | CG CacheDList, CacheD, handlers (toward 95 %) | CG | CG +8 |
| lift-parity-review-4 | opus:high | review, tasks 5 and 6, rules-proposal | all | - |

Expected after round 4 (estimate): CG about 463 (94.3 %), LG about 665 (90.0 %), SCD about 607 (90.7 %), POD about 690 (90.9 %),
shared about 515/549 (93.8 %). LG has the smallest margin. If crypto-4 or lg-4 gives less than half of its estimate, LG stays below 90 %;
review-4 then applies the stall check.
