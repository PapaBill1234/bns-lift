# Parity review 1 (lift-parity-review-1, 2026-11-18)

## 1. Measurement

`tools/gate.sh`: gate ok. `tools/parity.sh`: parity ok, MATCH -> DIFF 0 in all 4 exes. No source change in this card.

| Exe | Phase start | Round 1 end (now) | Change | 90 % needs | Gap |
| --- | ---: | ---: | ---: | ---: | ---: |
| CacheGate | 216/491 = 44.0 % | 387/491 = **78.8 %** | +171 | 442 | 55 |
| LobbyGate | 280/739 = 37.9 % | 487/739 = **65.9 %** | +207 | 665 | 178 |
| SmartCouponDaemon | 225/669 = 33.6 % | 461/669 = **68.9 %** | +236 | 602 | 141 |
| PostOfficeDaemon | 262/759 = 34.5 % | 509/759 = **67.1 %** | +247 | 683 | 174 |
| Shared library | 354/478 = 74.1 % (after s3) | 369/489 = **75.5 %** | +15 | 99 % = 484 | 115 |

Change since the start of this card: +0 in each exe (this card changes only docs).
Each exe is below 90 %. So this review queues round 2 (task 5), not a 90+ round.

### Measured effect of 2 funcdiff fixes (test copy `.scratch/funcdiff_exp.py`, not in `tools/`)
- Fix V: when a data ref has a `??_7` (vtable) symbol at the exact RVA, use the symbol, not `string_at()`.
- Fix T: when the function reads `gs:`, name a `mov` immediate that is a `.tls` offset of a PDB `S_*THREAD32` symbol.

| Exe | Now | Fix V | Fix V + T | MATCH lost |
| --- | ---: | ---: | ---: | ---: |
| CacheGate | 387 | 391 | 401 (81.7 %) | 0 |
| LobbyGate | 487 | 494 | 501 (67.8 %) | 0 |
| SmartCouponDaemon | 461 | 473 | 480 (71.7 %) | 0 |
| PostOfficeDaemon | 509 | 518 | 525 (69.2 %) | 0 |
| Shared library | 369 | - | 394/489 (80.6 %) | 0 |

These 63 functions have equal code. Only the tool reads them wrongly. The fixes also unblock Patterns 47 and 49
(POD), which were undone only because of this noise.

## 2. What worked (round 1: lift-parity-0, s1, s2, s3, cg-1, lg-1, scd-1, pod-1)

| Card | CG | LG | SCD | POD | Main cause fixed |
| --- | ---: | ---: | ---: | ---: | --- |
| lift-parity-0 (tool) | +77 | +97 | +109 | +113 | funcdiff noise: branch targets, jump tables, slot calls, `__chkstk` size |
| lift-parity-s1 | +38 | +23 | +33 | +32 | virtual call on a global, `swprintf_s<N>`, noinline, branch order |
| lift-parity-s2 | +14 | +25 | +21 | +16 | `volatile` member against PDB type, loop form, error block per call |
| lift-parity-s3 | +29 | +37 | +41 | +51 | zstd commit bb6eaf64, per-exe path literal, noinline, branch order |
| lift-parity-cg-1 | +11 | 0 | 0 | 0 | STL pair key, tail call, branch order |
| lift-parity-lg-1 | +1 | +24 | +8 | +5 | handler prologue forceinline, per-exe header paths, cleanup tail |
| lift-parity-scd-1 | +1 | +1 | +24 | +5 | ID128 compare, StlMemory path, EventObject dtor, map key |
| lift-parity-pod-1 | 0 | 0 | 0 | +25 | placement array new, noinline on exe-only misses |
| **Sum** | **+171** | **+207** | **+236** | **+247** | |

- The tool card (lift-parity-0) gave 396 of the 861 MATCH. Tool noise is the largest single cause.
- The shared cards (s1, s2, s3) gave 360 MATCH. A shared fix counts in each exe.
- The exe-only cards gave 105 MATCH. Each exe-only card stopped far below 90 %. Each handoff says that most of the gap is shared code, crypto misses or tool noise.
- Top patterns (functions fixed, all exes): zstd version 73, noinline 53, virtual call on a global 49, per-exe path literal 45,
  branch order 30, `volatile` 25+, `swprintf_s<N>` 25. Details: `lessons.md`.

## 3. What did not work
- funcdiff `string_at` noise (vtable read as a 2-byte string). It moved 2 to 8 MATCH per layout change. Two good fixes
  were undone (Pattern 47: POD map keys; Pattern 49: POD UpdatePostStatus, +2). Most lines of `allow-worse.txt` (47 lines) are for it.
- `.tls` variable order: seen in 4 cards, no source fix. It is a link artifact (Fix T above).
- LTCG inline choices (`removeReferenceCount` in `clearShortTermQueueSlot`, `LogMedia::Write`), constant propagation
  (`ThreadManager::Initialize`), register allocation, tail merge of `Log::Write`: about 10 tries, 0 MATCH.
- Exe-only scope: 90 % was not reachable in any exe-only card. The cards were cut by exe, but the causes are shared.
- Build tool: `tools/vs2010/build.sh` does not track headers. 5 cards found this again. Some measurements were stale.

## 4. Turn cost
The handoffs do not give the turn count of each card. Commit times give no cost either: some cards ran at the same time.
Proposal: the runner writes the turn count in `progress.tsv` or the handoff template has a "Turns" line.
Cost signal from the handoffs: s1, s3, lg-1 and pod-1 stopped with "time" or "budget" on open items.

## 5. DIFF functions that are left, by cause class (after Fix V + T)
Classifier: `.scratch/classify.py` on `funcdiff.py --show .` (rule by signal, like `triage.md`). One entry = one function in one exe.

| Cause class | Shared entries | Exe-only entries | Next card |
| --- | ---: | ---: | --- |
| Constants only (TLS left, LTCG folding, crypto tables, stack) | 115 | 29 | crypto-2, bloodlib-2 |
| `__FILE__` literal path or count | 61 | 82 | paths-2, helpers-2 |
| Refs only | 38 | 29 | paths-2, pod-2 |
| Call order or count (merged tails, block order) | 34 | 23 | bloodlib-2, helpers-2 |
| Other callee (inline choice) | 32 | 37 | noinline-2, helpers-2, scd-2 |
| Orig calls more (ours inlines) | 18 | 8 | noinline-2 |
| Ours calls more (lift helper not inlined) | 1 | 19 | helpers-2 |
| Tool noise left (vtable) | 4 | 0 | tool-2 |
| **Sum** | **303** | **227** | |

Per exe (DIFF shared + exe-only, misses): CG 70 + 12, 8 misses; LG 79 + 69, 90 misses; SCD 73 + 56, 60 misses; POD 81 + 90, 63 misses.

### Named causes with function lists
- **Crypto misses** (LG 60, SCD 39, POD 39): `BigInteger::*`, `Rsa::*`, `Oaep*`, DH, `i2os`, `os2i`, `MaskGenerator::generate`,
  `Ripemd128::Digest`, `Aes128::~Aes128`. The original pseudocode has no caller of `BigInteger::Divide` or `Rsa::*`
  outside the crypto modules. So the original keeps unreferenced crypto functions. Probable cause: the original
  BloodCrypto lib had other compile flags (no `/GL`, or no `/Gy`). Shared crypto DIFF with consts only
  (`Blowfish::Setup`, `Ctr::Encrypt`, `aes128Table*`, `encrypt`, `decrypt`, `Prng::setSeed`) agree with this. ❓
- **Per-exe header path** (Pattern 35/41 not complete): `PacketUtil.h` is the LobbyGate path in CG and POD
  (`PacketFormatIterator::SetFormat`); `StlMemory.h` is the CG path in LG (7 functions), SCD (6), POD (6), CG (3, upper/lower
  case); `FragmentPacket.cpp` is `..\..\Packet\` in ours, `..\Packet\` in LG (5 functions).
- **POD `Lock.h` literal**: ours refs the `Lock.h` path in 7 POD functions (36 refs), the original in none
  (`RelayContext::ProcessRelayResponse`, `ProcessRelayTimeout`, `*::updateWorldList`, `UnsentPostContextManager::initContextManager`).
- **`source\Memory.cpp` refs**: the original has 6 more in `BloodDaemonMain` and `Daemon::start` (4 exes).
- **Lift helpers that the original inlines**: LG `LobbyDPacketHandler.cpp` (6 handlers, 23 refs less), `Client.cpp`
  (7 functions); POD `CacheEconomyPacketHandler.cpp` (13 handlers, 44 refs less), `PostOfficeDB` Load*.
- **Exe-only misses (inlined in ours)**: LG `ContentsRuleConfig::Dump`, `LobbyGateConfig::Dump`, `ClientManager::Initialize`,
  `GateKeyManager::Initialize`, `CriticalSection::CriticalSection`, `Session::Send`, `Session::allocateCrypt`,
  `deallocateCrypt`; SCD `SetManagerChannel`, `EventNotiJob::eventNotiExpire`, `DbTransaction::BindCol`,
  `Network::OpenPort`; POD `Channel::Send`, `GrowingBuffer::Add`, `grow`, `Packet::Decompose`, `parseString`,
  `DaemonConfig::Dump`, `PostOfficeDB::UpdateStatusToDelivery*`; all exes `Log::Flush`, `Log::Initialize`,
  `DelayedRelease::Cleanup`, `Prng::addEntropy`, `Console::Flush`.
- **Not fixable in source** (stop list, do not try again): `.tls` order (tool), `ThreadManager::Initialize` constant
  propagation, `EventNotiJob::finalize` constant CSE, `JobManager::Execute*`, ICF names (`PingRelayContext::GetRequestWid`,
  `TimerClass`, `TimerId`), `wmain$dtor$0` funclet, `operator delete` (CRT).

## 6. Plan for round 2
Shared and tool cards first. Each card is one cause. Queue: `Docs/Plan/queue/lift-parity-review-1.tsv`.

| Card | Cause | Exes | Expected gain (estimate) |
| --- | --- | --- | --- |
| lift-parity-tool-2 | funcdiff Fix V + T, `const ,` names, build.sh header deps | all | +63 (measured) |
| lift-parity-paths-2 | per-exe header and source path literals, POD `Lock.h` | all | +30 |
| lift-parity-crypto-2 | BloodCrypto compile flags (misses + crypto consts) | all | up to +160 |
| lift-parity-bloodlib-2 | shared BloodLib DIFF left (Session, Port, SessionSendBuffer, Daemon) | all | +20 |
| lift-parity-noinline-2 | Pattern 11 on the misses | all | +30 |
| lift-parity-helpers-2 | lift helpers and handler form (LG, POD) | LG, POD | +35 |
| lift-parity-pod-2 | Patterns 47 and 49 again, block order of Get* | POD | +10 |
| lift-parity-scd-2 | SCD handler inline depth, SmartCouponDB BindCol | SCD | +15 |
| lift-parity-review-2 | review, tasks 5 and 6 | all | - |

CacheGate has no exe card: its exe-only DIFF (12) have causes from the stop list. Its gap closes with the shared cards.
