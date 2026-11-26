# Parity review 4 (lift-parity-review-4, 2026-11-26)

## 1. Measurement

`tools/gate.sh`: gate ok. `tools/parity.sh`: parity ok, MATCH -> DIFF 0 in all 5 exes (LobbyDaemon 1024/2204, excluded 127, unchanged).
`tools/parity_shared.py build-vs2010 --list`: shared library 516/549 = 94.0 %.
Main at commit a57d889. No source change in this card.

| Exe | Review 3 | Review 4 (now) | Change | 95 % needs | Gap to 95 % | Paired | Misses (orig only) | Mean score |
| --- | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: |
| CacheGate | 448/491 = 91.2 % | 456/491 = **92.9 %** | +8 (+1.6 %) | 467 | 11 | 488 | 3 | 99.3 |
| LobbyGate | 627/739 = 84.8 % | 658/739 = **89.0 %** | +31 (+4.2 %) | 703 | 45 | 736 | 3 | 98.9 |
| SmartCouponDaemon | 582/669 = 87.0 % | 630/669 = **94.2 %** | +48 (+7.2 %) | 636 | 6 | 667 | 2 | 99.5 |
| PostOfficeDaemon | 665/759 = 87.6 % | 694/759 = **91.4 %** | +29 (+3.8 %) | 722 | 28 | 754 | 5 | 99.1 |
| Shared library | 490/549 = 89.3 % | 516/549 = **94.0 %** | +26 | 99 %: 544 | 28 | - | - | - |

- LG is below the 90 % checkpoint. CG, SCD and POD are at 90 % or more. No exe is at the 95 % goal.
  So this review queues round 5 (task 5) with the target 95 % per exe (operator decision for this wave), not a 90+ round.
- CG gained 1.6 %, less than 2 %. Stall check (section 7): the cause is that the CG card (cg-4) was never built. It is not a stall of the method.
- Round 4 ran 6 of 9 cards. `lift-parity-ehstate-4`, `lift-parity-lg-4` and `lift-parity-cg-4` stayed `ready` (the queue stopped, wave 5 moved to LobbyDaemon).
  Their function lists are folded into the round-5 cards.
- No manual work after round 4 changed the 4 exes. The rows after console-4 in `progress.tsv` are LobbyDaemon cards; the 4 exe columns stay the same.

## 2. What worked (round 4)

Gain per card = change of the `progress.tsv` row against the row before it.

| Card | CG | LG | SCD | POD | Sum | Turns | MATCH per 100 turns | Estimate (review-3 section 6) | Main cause fixed |
| --- | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | --- |
| lift-parity-crypto-4 | 0 | +16 | +11 | +11 | 38 | 62 | 61 | +22 | BloodCrypto source forms (A25) |
| lift-parity-net-4 | +4 | +4 | +4 | +3 | 15 | 110 | 14 | +8 | `inline_depth(0)`, per-case tails, reload at each use (A20, A17, A26) |
| lift-parity-packet-4 | +2 | +6 | +3 | +7 | 18 | 95 | 19 | +10 | packet buffer forms, log line order (A30, A2) |
| lift-parity-scd-4 | 0 | 0 | +26 | 0 | 26 | 395 | 7 | +10 | DChannelMgr, DB loaders, log-macro args (A32, A11, A31) |
| lift-parity-pod-4 | 0 | 0 | +2 | +6 | 8 | 150 | 5 | +12 | reload at each use, `::new`, `ID128_GUID_ZERO` (A26 to A28) |
| lift-parity-console-4 | +2 | +5 | +2 | +2 | 11 | 95 | 12 | +10 | PDB line maps (A29) |
| lift-parity-ehstate-4 | - | - | - | - | - | - | - | +7 | not built |
| lift-parity-lg-4 | - | - | - | - | - | - | - | +15 | not built |
| lift-parity-cg-4 | - | - | - | - | - | - | - | +8 | not built |
| **Sum** | **+8** | **+31** | **+48** | **+29** | **116** | **907** | **12.8** | built cards +72 | |

- The 6 built cards gave 116 MATCH. The estimate for them was 72. Each built card except pod-4 reached its estimate or more.
- Estimates of review 3 against the result: CG 463 -> 456 (-7; cg-4 and ehstate-4 not built), LG 665 -> 658 (-7; lg-4 not built),
  SCD 607 -> 630 (+23), POD 690 -> 694 (+4).
- Best card: crypto-4 (61 per 100 turns). It applied one cause (BloodCrypto source forms) to 14 shared names. Next: packet-4 (19), net-4 (14).
- scd-4 gave the most MATCH for one exe (+26) but used 395 turns (3 repair rounds). pod-4 gave the lowest rate (5 per 100 turns).
- The best methods of round 4: the PDB line map (A29, every win of console-4), the original call pattern (call a getter again at each use: A25, A26, A31),
  and the order of the cold error tails from the log line numbers (A2, packet-4).

## 3. What did not work
- crypto-4: `Rsa::decrypt` zero fill (VS2010 makes `memset` from each byte-loop form, 3 tries), `invMod` (`RightShift` must stay `noinline`),
  `expMod` one exit. `BroadcastCrypt::Initialize` not tried (budget).
- net-4: `Network::OpenPort` CG/LG/POD (the original table has no PDB name; 3 tries). `Port` ctor with body stores (store order equal, no MATCH).
- packet-4: `FragmentPacket::StartRepeat`, `FragmentPacketConcatenater::Add`, `PacketConcatenateBuffer::Decompose` (register allocation and CSE; 3 tries each).
- scd-4: `HandleSmartCoupon_GameEventByAccountReq` (3 tries, 95.2 best), `SetupGameEventListFromXml` (4 tries, 99.7), `SmartCouponDaemon::initialize`
  (blocked: the original exe has a patched-out cert-decode call).
- pod-4: single-expression `::new` is not general (4 DB loaders worse). LTCG `this` propagation in `sendPing` and `checkCacheGateServiceState` (stop list).
  `LoadPostList` loop header (3 tries, 99.1).
- console-4: `wcscmp` `sbb` form (2 more forms), `DaemonConfig::Dump` RTTI neighbour (we build with `/GR-`). A data-layout win (SCD `LOCALHOST_IP`)
  went away after the merge with main: measure again after each merge.
- Process: 3 of 9 cards were never built. The queue stopped after console-4 when the work moved to LobbyDaemon. CG had no card in round 4.
- All in lessons B and D.

## 4. Turn cost
- Round 4: 907 turns for 116 MATCH = 7.8 turns per MATCH (12.8 MATCH per 100 turns). Round 3 cards: 3.5 turns per MATCH; without cryptolib-3, 6.1.
- Without scd-4 (395 turns): 512 turns for 90 MATCH = 5.7 turns per MATCH.
- The cost of a MATCH rises each round. The easy causes are gone. 78 of the 207 DIFF entries are on the stop list (section 5).
- Round 4 used a mix of `opus` and `sonnet:high` models. Round 5 uses `opus` (Opus 5.5, effort medium) for every card. Review 5 compares
  MATCH per 100 turns with the 12.8 of round 4 to measure the cost efficiency of this model.

## 5. DIFF functions that are left, by cause class
One entry = one function in one exe. Signal class from the baseline (`calls`, `refs`, `consts` below 100). 207 DIFF entries and 13 misses.

| Signal class | CG | LG | SCD | POD | Sum |
| --- | ---: | ---: | ---: | ---: | ---: |
| Consts only (LTCG folding, register allocation, line numbers) | 12 | 19 | 15 | 15 | 61 |
| Calls + refs + consts (another inline choice or another body) | 6 | 16 | 5 | 15 | 42 |
| Refs only (literal reload, vtable name, ref order) | 4 | 11 | 5 | 7 | 27 |
| Calls + refs (block layout, tail merge) | 3 | 7 | 4 | 9 | 23 |
| Calls only (call order, tail merge) | 4 | 8 | 4 | 5 | 21 |
| Calls + consts | 0 | 8 | 2 | 7 | 17 |
| Refs + consts | 3 | 9 | 2 | 2 | 16 |
| **DIFF** | **32** | **78** | **37** | **60** | **207** |
| Misses (orig only) | 3 | 3 | 2 | 5 | 13 |

By cause and owner (round 5):

| Cause | Entries | Owner card |
| --- | ---: | --- |
| Stop list (lessons D): `aes128Table*` x4 x4, `Daemon::Start` x4, `PipeConsole::run`/`processCommand` x4, `PipeCommandProcess::processCommand` x4, `Session::Session` x4, `StaticPageMemoryManager::Initialize` x4, `ThreadManager::Initialize` x4, `WindowConsole::Open` x4, `Session::HandleEvent` x4, `PipeConsole::SetInvalidInfo` x3, `Rsa::decrypt` x3, `Network::OpenPort` x3, `DaemonConfig::Dump` x2, packet register-allocation forms x4, `checkFrozenThread`, `ZSTD_compressBegin_internal`, POD LTCG `this` x2, SCD `JobManager` x2, `EventNotiJob::finalize`, SCD `initialize`, POD `LoadPostList` x2, SCD 2 handler/XML entries | about 78 | none |
| Crypto (`invMod`, `InvMod`, `Divide`, `IsPrime`, `isPrimeMR`, `Crypto::*`, `Dh::*`, `BroadcastCrypt::*`) | 17 | shared-5 |
| EH state -2 outside `wmain` (`FragmentPacketConcatenater::Clone` x2, `IdleWatcher::run`, POD `operator delete[]`) | 4 | shared-5 |
| BloodLib (`IoWorker::run` x4, `Channel::Send`, `AlertSender::init`, SCD `Session::Connect`) | 7 | shared-5 |
| Shared misses (`RefCntObject::operator delete` x4, `Packet::Concatenate`, `Packet::Decompose`, POD `DaemonConfig::Dump`, 3-byte `operator delete` x2) | 9 | shared-5 |
| `wmain` x4 (EH state -2, k0) and the `wmain$dtor$0` misses x4 | 8 | lg-5b, pod-5b, cgscd-5 |
| LG LobbyD handlers and channel | 21 | lg-5a |
| LG daemon, Client, config | 20 | lg-5b |
| POD relay, CacheGate channel, DB | 17 | pod-5a |
| POD daemon, world config, handlers | 15 | pod-5b |
| CG CacheDList, CacheD, handlers, dtors | 14 | cgscd-5 |
| SCD channels, handlers, `ObjPool` | 9 | cgscd-5 |

- The stop list caps each exe at about 97 % (CG 475, LG 719, SCD 647, POD 738) unless a new idea opens an entry.
- To reach 95 %, round 5 must fix: CG 11 of about 19 fixable entries, LG 45 of about 61, SCD 6 of about 17, POD 28 of about 44.
  SCD and CG can reach 95 % in round 5. LG and POD need a high hit rate; they likely need round 6.

## 6. Plan for round 5
One wave for the 4 server exes. No LobbyDaemon cards. All cards depend only on review-4 and touch disjoint files, so they build in parallel.
Every card has model `opus` (operator: Opus 5.5 medium for this wave). Each card writes its lessons in its handoff; review-5 merges them
(parallel cards would conflict on `lessons.md`). Queue: `Docs/Plan/queue/lift-parity-review-4.tsv`.

| Card | Model | Cause | Exes | Named entries | Expected gain (estimate) |
| --- | --- | --- | --- | ---: | --- |
| lift-parity-shared-5 | opus | crypto, BloodLib, EH state -2, shared misses | all | 37 | CG +1, LG +8, SCD +4, POD +5 |
| lift-parity-lg-5a | opus | LobbyD handlers and channel (fold of lg-4) | LG | 21 | LG +10 |
| lift-parity-lg-5b | opus | LG daemon, `wmain`, Client, ContentsRuleConfig (fold of lg-4, ehstate-4) | LG | 21 | LG +10 |
| lift-parity-pod-5a | opus | POD relay, CacheGate channel, DB | POD | 19 | POD +8 |
| lift-parity-pod-5b | opus | POD daemon, `wmain`, world config, handlers (fold of ehstate-4) | POD | 18 | POD +7 |
| lift-parity-cgscd-5 | opus | CG and SCD to 95 % (fold of cg-4, ehstate-4) | CG, SCD | 26 | CG +8, SCD +5 |
| lift-parity-review-5 | opus | review, lessons merge, next round | all | - | - |

Expected after round 5 (estimate): CG about 465 (94.7 %), LG about 686 (92.8 %), SCD about 639 (95.5 %), POD about 714 (94.1 %),
shared about 524/549 (95.4 %).

## 7. Stall check (CG, +1.6 % in round 4)
- Cause: no CG card was built in round 4. The 8 CG MATCH came from the shared cards (net-4 +4, packet-4 +2, console-4 +2).
- The CG DIFF list has 19 entries that are not on the stop list. None of them had a try in round 4.
- Fix: lift-parity-cgscd-5 takes the cg-4 list. This is not a method stall, so `zero_rounds` does not apply. If CG gains less than 2 % in round 5
  with its own card, review-5 applies the stall check again.
