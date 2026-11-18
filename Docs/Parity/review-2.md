# Parity review 2 (lift-parity-review-2, 2026-11-18)

## 1. Measurement

`tools/gate.sh`: gate ok. `tools/parity.sh`: parity ok, MATCH -> DIFF 0 in all 4 exes. No source change in this card.
`tools/parity_shared.py build-vs2010`: shared library 421/499 = 84.4 %.

| Exe | Review 1 | Review 2 (now) | Change | 90 % needs | Gap to 90 % | Misses (orig only) |
| --- | ---: | ---: | ---: | ---: | ---: | ---: |
| CacheGate | 387/491 = 78.8 % | 420/491 = **85.5 %** | +33 | 442 | 22 | 4 |
| LobbyGate | 487/739 = 65.9 % | 530/739 = **71.7 %** | +43 | 665 | 135 | 81 (72 crypto) |
| SmartCouponDaemon | 461/669 = 68.9 % | 510/669 = **76.2 %** | +49 | 602 | 92 | 50 (47 crypto) |
| PostOfficeDaemon | 509/759 = 67.1 % | 588/759 = **77.5 %** | +79 | 683 | 95 | 53 (47 crypto) |
| Shared library | 369/489 = 75.5 % | 421/499 = **84.4 %** | +52 | 99 % = 494 | 73 | - |

Each exe is below 90 %. So this review queues round 3 (task 5), not a 90+ round. The shared denominator changed
from 489 to 499: more functions pair now (tool-2 fix 8, noinline-2 overloads).

## 2. What worked (round 2)

| Card | CG | LG | SCD | POD | Sum | Turns | MATCH per 100 turns | Main cause fixed |
| --- | ---: | ---: | ---: | ---: | ---: | ---: | ---: | --- |
| lift-parity-tool-2 | +18 | +19 | +23 | +20 | 80 | not given | - | funcdiff: vtable symbol before `string_at`, `.tls` offset as ref, name forms; build.sh header deps |
| lift-parity-paths-2 | +1 | +6 | +4 | +6 | 17 | 38 | 45 | per-exe path literals (`PacketUtil.h`, `Channel.h`, `FragmentPacket.cpp`, `StlMemory.h`) |
| lift-parity-crypto-2 | +5 | +5 | +5 | +5 | 20 | 74 | 27 | crypto source forms (blowfish index, `Ctr` carry, `rand() % 256`, `_alloca`, decrypt loop) |
| lift-parity-bloodlib-2 | +7 | +5 | +5 | +5 | 22 | 84 | 26 | block order in `SessionBuffer.cpp`, `Session::handlePacket`; `Port` body copy |
| lift-parity-noinline-2 | +2 | +6 | +6 | +8 | 22 | about 120 | 18 | noinline on misses; missing `Dump` calls; overload pairing |
| lift-parity-helpers-2 | 0 | +2 | 0 | +17 | 19 | about 85 | 22 | `static __forceinline` helpers, literal `#define`, shared END tail |
| lift-parity-pod-2 | 0 | 0 | 0 | +18 | 18 | about 100 | 18 | block order of `Get/Add/Remove`, map key (P47), `memset` ctor, `initResponse` |
| lift-parity-scd-2 | 0 | 0 | +6 | 0 | 6 | 79 | 8 | placement `new[]`/`delete[]` replacement, `_instance->` at each use |
| **Sum** | **+33** | **+43** | **+49** | **+79** | **204** | about 580 | 35 | |

- The tool card again gave the most MATCH (80 of 204). The review-1 estimate was +63.
- Shared cards (tool, paths, crypto, bloodlib, noinline) gave 161 of 204. Exe-only cards gave 43.
- The best rate after the tool card: paths-2 (45 per 100 turns). The worst: scd-2 (8 per 100 turns). The exe-only
  cards spent most turns on single functions with a score of 90 to 99.
- Estimates of review 1 against the result: paths-2 +30 -> +17; crypto-2 up to +160 -> +20 (the misses have another
  cause, see section 3); bloodlib-2 +20 -> +22; noinline-2 +30 -> +22; helpers-2 +35 -> +19; pod-2 +10 -> +18; scd-2 +15 -> +6.

## 3. What did not work
- Crypto compile flags (review-1 M5): wrong cause. The flags are equal. The crypto misses come from 2 libraries
  with no debug info (`BloodPacketCrypt64.lib`, `BloodCert64.lib`). They call `Crypto::Create`, `Rsa::Rsa`, `Dh::Dh`.
  Ours has `PacketCrypt::Create` / `InstanceSize` as stubs, so the crypto functions are not linked (misses: LG 72, SCD 47, POD 47).
- Per-exe inline choice of one shared function (`Session::Send`, `Session::deallocateCrypt`, `Port::Clear`,
  `TimerQueue::~TimerQueue` COMDAT): `tools/vs2010/build.sh` has no per-exe define. Two cards stopped here.
- LTCG choices again: `removeReferenceCount` noinline (-5 MATCH), `AutoCS` noinline (-1), `aes128Table*` fst form (0),
  `Session::HandleEvent` goto (score down). Register allocation in `Blowfish::Setup`.
- Block layout that the source order does not move: `HandleSmartCoupon_GameEventByAccountReq` 0x8e80,
  `HandlePostOfficeRegisterPostReq` 0x1aaa0, `Client::SendTakeGoodsOk` 0x4ed0 (positive form 98.9 -> 93.8).
- DB loaders with inlined `SQLBindCol` (SCD `SmartCouponDB::Load*`/`Process*`, POD `PostOfficeDB::Load*`): no form found.
- `tools/vs2010/build.sh` header deps are fixed (tool-2), but helpers-2 still touched `.cpp` files (old memory note). No cost now.

## 4. Turn cost
- Round 2: about 580 turns for 204 MATCH = 2.8 turns per MATCH (round 1 had no turn counts).
- Cards stopped by turn budget with known open items: bloodlib-2, helpers-2, scd-2.
- The cost of a MATCH rises: the easy shared causes are done. The causes that are left are larger (a closed library lift,
  a per-exe build define) or single-function block layout.

## 5. DIFF functions that are left, by cause class
Classifier: `.scratch/classify.py` on `funcdiff.py --show . --only` (rule by signal, as `triage.md`). One entry = one function
in one exe. "Shared" = DIFF in 2 or more exes.

| Cause class | Shared entries | Exe-only entries | Round 3 card |
| --- | ---: | ---: | --- |
| Constants only (EH state, LTCG folding, line numbers, stack) | 79 | 35 | consts-3 |
| Other callee (inline choice, inlined STL/ODBC, array new) | 30 | 64 | inline-3, arraynew-3, dbbind-3, handlers-3 |
| Refs (+ consts) | 37 | 25 | consts-3, handlers-3 |
| Call order (block layout) | 29 | 27 | order-3, handlers-3 |
| Orig calls more (ours inlines) | 29 | 15 | inline-3 |
| Ours calls more (helper or explicit `Clear`) | 13 | 24 | inline-3, handlers-3 |
| Path literal | 6 | 4 | perexe-3 |
| Call count | 2 | 3 | order-3 |
| **Sum** | **225** | **197** | |

Per exe: CG 67 DIFF + 4 misses, LG 128 + 81, SCD 109 + 50, POD 118 + 53.

### Named causes with function lists
- **Closed crypto libraries** (LG 72, SCD 47, POD 47 misses): `BigInteger::*` (26), `Dh::*` (10), `RsaPrivate::*`, `RsaPublic::*`,
  `Rsa::*`, `OaepEncoder::*`, `CryptoKey::*`, `Crypto::*`, `Prng::*`, `i2os`, `os2i`, `MaskGenerator::generate`, `Ripemd128/160`,
  `Aes128::~Aes128`. Ours also has LG `BroadcastPacketCrypt::*` (5, ONLY-OURS): the original has them in the closed lib.
  Fix: lift the callers in `BloodPacketCrypt64.lib` and `BloodCert64.lib` from the disassembly. Card cryptolib-3.
- **Placement array new with `eh vector constructor iterator`** (scd-2 pattern): LG `GateKeyManager::Initialize` (32.6),
  `ClientManager::Initialize`/`Finalize`/`broadcast`, `GateKeyManager::Finalize`, orig-only `CriticalSection::CriticalSection`,
  `operator delete[]` (LG, POD), placement `operator delete` (CG, SCD, POD, LG: score 0, Memory.h:173 crash log). Card arraynew-3.
- **Per-exe build define**: `TimerQueue::~TimerQueue` (LG, SCD, POD), `Session::Send` and `Session::deallocateCrypt`
  (ONLY-OURS in SCD, POD), `Port::Clear`/`clearPool`. Card perexe-3.
- **Orig calls more / ours calls more, shared**: `Log::Initialize`, `Session::~Session`, `String::GetId128FromGuidString`,
  `WinServiceConsole::UninstallService`, `PipeConsole::SetInvalidInfo`, `Network::OpenPort` (x2), `PacketBuffer::Compose`,
  `CrashHandler::handleCrash`, `Session::HandleEvent`. Exe-only: LG `LobbyD::Send*` (6, extra `Packet::Clear`),
  `LobbyDSessionHandler::*`, POD `RelayContext::Process*` (3), `*PacketBufferHandler::Destroy` (2). Card inline-3.
- **Block order, shared**: `BloodDaemonMain`, `Daemon::start`, `makeConsole`, `BnsCommonConfig::LoadBnsCommonConfig`,
  `DaemonConfig::Load`, `LogFile::writeFile`, `PipeConsole::run`. Exe-only (not handlers): SCD `DChannelMgr::SetupDaemonList`,
  `Channel::MakeSession`, `GameEventManager::PostGameEventLogList`; POD `UnsentPostContextManager::*` (3); LG `IdleStateTable::scan`,
  `PipeConsole::SetRunningInfo`. Card order-3.
- **Constants and refs with no known cause, shared**: `Session::Accept`, `recv`, `HandleFailedEvent`, `Session::Session`,
  `Session::initialize`, `Daemon::Start`, `Daemon::setAddress`, `SysInfo::*`, `Network::Clear`, `Network::Network`,
  `Network::initWorkerThread`, `Network::GetAddressStringW`, `PacketBuffer::Decompose`, `PacketBuffer::CheckCompose`,
  `TrustedPacketBufferHandler::ToPacket`, `StaticPageMemoryManager::Initialize`, `PacketBufferAllocator::initAllocator`,
  `WindowConsole::Open`, `Port::Initialize` (EH state -2), `FragmentPacketConcatenater::*`, `RepeatPacketComposer::PushRepeatCount`. Card consts-3.
- **Packet handlers** (A6, A12, A15, P31 tail call): LG `HandleLobbyLobbyGate_*` (12), `HandleLobbyGate_*` (5), `Client::Send*Ok` (3);
  SCD `HandleSmartCoupon*` (6), `ManagerChannel::Send*` (2), `*Event::HandleEvent` (4); POD `*SessionHandler::PacketHandler` (5),
  `HandlePostOffice*` (8), `HandleCacheGateRelay*` (3); CG `HandleCacheGate*` (3). Card handlers-3.
- **DB loaders with inlined `SQLBindCol`**: SCD `SmartCouponDB::Load*` (4), `Process*GameEventLog` (2), `DbTransaction::BindCol`;
  POD `PostOfficeDB::Load*` (4), `RegisterPost`. Half patch in the pod-2 worktree (`.scratch/postofficedb-bindcol-macros.patch`, not in git). Card dbbind-3.
- **Stop list** (do not try again, M9): `.tls` layout (`__delv_buf__`), `ThreadManager::Initialize`, `EventNotiJob::finalize`,
  `JobManager::Execute*`, ICF names and folds (`WorldChannelManager::RemoveWorldChannel`), `wmain$dtor$0`, CRT `operator delete`
  (`Console::Flush`, `RefCntObject::operator delete`), `TimerQueue::clearShortTermQueueSlot`, `LogMedia::Write` (removeReferenceCount
  inline), `Blowfish::Setup` (register allocation), `aes128Table*` (unroll and fst form tried), POD `DaemonConfig::Dump` (dead flow).

## 6. Plan for round 3
Shared cards first. Each card is one cause. Queue: `Docs/Plan/queue/lift-parity-review-2.tsv`.

| Card | Cause | Exes | Expected gain (estimate) |
| --- | --- | --- | --- |
| lift-parity-perexe-3 | per-exe define in `tools/vs2010/build.sh`; per-exe inline choice and COMDAT path | all | +6 |
| lift-parity-cryptolib-3 | lift the callers in `BloodPacketCrypt64.lib` and `BloodCert64.lib`; crypto misses | LG, SCD, POD | LG +50, SCD +33, POD +33 |
| lift-parity-inline-3 | orig calls more / ours calls more (noinline, forceinline, no explicit `Clear`) | all | +25 |
| lift-parity-order-3 | block order and call order (shared and exe-only, not handlers) | all | +20 |
| lift-parity-consts-3 | constants and refs with no known cause (shared) | all | +16 |
| lift-parity-arraynew-3 | placement array new, `eh vector constructor iterator`, placement `operator delete` | all | +10 |
| lift-parity-handlers-3 | packet handler form | all | +25 |
| lift-parity-dbbind-3 | DB loaders with inlined `SQLBindCol` | SCD, POD | +6 |
| lift-parity-review-3 | review, tasks 5 and 6 | all | - |

Expected after round 3 (estimate): CG about 440 (89.6 %), LG about 625 (84.6 %), SCD about 585 (87.4 %), POD about 670 (88.3 %).
The largest single gain is cryptolib-3. If it fails, LG cannot get to 90 % (the misses are 9.7 % of LG).
