# Parity lessons

Cleaned in lift-parity-review-3 (2026-11-18). The stage notes of round 3 are merged into the patterns. The list is sorted by
the number of functions fixed (sum over the 4 exes; a shared function counts once per exe). Old numbers are in brackets:
(r2 A5) = A5 of review 2, (P11) = old Pattern 11. Each new card adds its patterns at the end of section A or B. The next review sorts them again.

Mapping review 1 -> review 2: A1=A1, A2->A3, A3->A2, A4->A6, A5->A4, A6->A5, A7->A8, A8->A9, A9->A11, A10->A13, A11->A7,
A12->A14, A13->A15, A14->A16, A15->A10, A16+A17->A17, new A12 (crypto source forms).

Mapping review 2 -> review 3: A1=A1, A2->A4, A3->A5, A4->A6, A5->A2, A6->A7, A7->A8, A8->A12, A9->A13, A10=A10, A11->A15,
A12->A9, A13->A11, A14->A17, A15->A18, A16=A16, A17->A24. New: A3 (closed-lib callers), A14 (global placement delete, `::new`),
A19 (separate stores), A20 (`inline_depth(0)`), A21 (PDB facts first), A22 (per-exe source form), A23 (PacketHandler form).
Section E (perexe-3) and the round-3 stage notes are merged into A to D. Section F keeps the manual notes of round 3.

## A. Patterns that worked

### A1. Funcdiff noise fixes (tool cards; r2 A1): 496
- lift-parity-0 (396): branch targets counted as constants, jump tables read as code, calls through a slot with no symbol,
  `__chkstk` frame size. CG +77, LG +97, SCD +109, POD +113.
- lift-parity-tool-2 (80): vtable symbol before `string_at` (fix 5), `.tls` offset as ref `tls:<name>` (fix 6),
  `<K const ,V>` name form (fix 7), `?Setup@PacketCrypt@@...` demangle (fix 8). CG +18, LG +19, SCD +23, POD +20. Details: C1 to C3.
- Proof of each fix in `noise.md`.
- Rule: fix a tool error before a source change. A tool error hides real progress and makes good changes look bad (C1).
- Round 3 (manual): fix 9 (a TLS address that the compiler forms in separate blocks: the offset load can be before a loop, the address can use `add`;
  15: CG 3, LG 5, SCD 4, POD 3) and fix 10 (all public names at a folded vtable address; 5). Details in F and `noise.md`.
- Rule (round 3): before a source change on a `tls:` or vtable-name DIFF, check the tool. Fix 9 and fix 10 gave 20 MATCH with no source change.

### A2. Block order and statement order follow the original (r2 A5; P3, P7, P10, P20, P25, P33, P39; order-3, consts-3, handlers-3, manual): about 97
- VS2010 puts the `if` body inline and the code after it behind a jump. Write the source in the order of the original blocks.
  Find the order with `dis2.py` (the first `jne`/`je` after the test, and the `ret` positions). There is no fixed direction.
- The HR condition can be the inverse of the source condition (P33, `CacheDChannel::onConnect` 0x3c80).
- Error path first with an early return when the original has `jg` to the good path (P7, `RefCntObject::addReferenceCount`).
- Good path first, `Log::Write` at the end (P20: `Db::AllocTransaction`, `initEnv`, `Execute`; SCD +6, POD +7;
  bloodlib-2: `SessionBuffer.cpp` `Add`, `RemoveSentBuffer`, `increaseBuffer`, `Initialize` and `Session::handlePacket` 0xf750, +5 each exe).
- Nested success-first `if` for handle chains (P10, `WinServiceConsole::InstallService` 0x17c80); `buffer == nullptr` first (P39).
- POD context managers (pod-2, +10):
  `Get*`: one shared `Leave`: `T* p = nullptr; Enter; it = find(k); if (it != end) { p = it->second; if (p == nullptr) { Leave; crash;
  return nullptr; } p->addReferenceCount(...); } Leave; return p;`.
  `Add*`: error path first: `if (!insert(...).second) { Leave; Log::Write(...); [free]; return false; } addReferenceCount; Increment; Leave; return true;`.
  `Remove*`: null path first: `if (p == nullptr) { Leave; crash; return false; } erase(it); removeReferenceCount; Decrement; Leave; return true;`.
- Failure branch first gives the original call order (score only, no MATCH): POD `ComposeResponsePacket` 0x9570, 0x1e230 (77.8 -> 90.5).
- Branch order in a helper decides the layout: `else if (!ProcessRelayResponse()) { Log fail } else { removeReferenceCount; logEnd; return true; }`.
- Register locals: read a member pointer one time into a local when the original keeps it in a register (`Port::clearPool`: `pool`).
  Copy the body of an inlined `noinline` function into the caller with `// LIFT:` (`Port::Clear` gets the `PortListener::Clear` body: CG +2).
- order-3 (+23, CG 6, LG 5, SCD 7, POD 5): `Daemon::start` 0xb140 tests `GetTimerInterval() == 0` first. `DaemonConfig::Load` 0xc600:
  `if (module != nullptr) { body } else { fail }` (the `LoadLibraryW` failure block is last). `BloodDaemonMain`: `if (GetConsoleWindow() == nullptr)
  { RunMode = DAEMON_MODE; } else { loop }` and one shared tail `makeConsole` + `Daemon::Start` (an early return duplicates the tail).
  `makeConsole`: `switch (RunMode)` with a `default` error case (the `if` chains did not match).
- `LogFile::writeFile`: first `CreateFileW` before the retry; `do { Sleep; CreateFileW; if ok goto opened; } while (++tries < 100);`, error code, `return`, `opened:`.
  A `while (true)` with the error inside unrolled one more `Sleep`/`CreateFileW`.
- `BnsCommonConfig::LoadBnsCommonConfig` 0x13e0: write each error exit in full (`Config = nullptr; Log::Write(...)`). The compiler merges the tails itself.
  A hand-written `goto failed` tail did not match. Keep the new object in a local and test the local (one `Config` read less).
- SCD `GameEventManager::PostGameEventLogList` 0xb140: read `Instance->_gameEventHandle` once into a local, test the local. The null log is then the last block.
- `Session::recv`: take the context pointer local before the stores; the `!AsyncRecv` failure block first (consts-3, +4).
- POD management handlers (handlers-3, +5): failure branch first, success last:
  `if (DecomposeText(...) == 0) { fail } else { if (!DbCall(...)) { fail } else { success; return true; } }`, then the common failure tail.
- Manual: SCD `DbTransaction::BindCol` 0x20e40 null statement handle first, return after the log (as POD 0x2d010). SCD `SendPublicationEvent::HandleEvent`
  0xbe30 null job log before `CouponJob::execute`. POD `UnsentPostContextManager::deliverUnsentPost` `OccurEvent` failure first, each release with its line.
  SCD `SmartCouponDaemon::reload`: reload failure and the unchanged case before the `Dump` case; log `GetLastError()` when `_wmakepath_s` fails.
- The direction is per function. Success-first lowered `WorldConfigManager::loadWorldConfigFile`; failure-first lowered `PingRelayContext::processRelayResponse`
  (97.6 -> 95.1). Measure each change.
- SCD `DChannelMgr::SetupDaemonList` 0xd270 (82.8 -> 96.3): `if (second != nullptr)` first, the alloc path last, one shared `Log::Write` after both.

### A3. Lift the callers in a closed library from the disassembly (cryptolib-3): 90
- Cause: the original links `BloodPacketCrypt64.lib` and `BloodCert64.lib` (no debug info). Their objects call `Crypto::Create`, `Rsa::Rsa`, `Dh::Dh`.
  Our stubs called nothing, so the BloodCrypto functions were misses (LG 72, SCD 47, POD 47).
- Lift `PacketCrypt` (LG 0x4cc60-0x4da60) and `BloodCert`/`CertDec`/`SSN`/`NIC` (LG 0x4bf70-0x4ca10) from the disassembly with `// LIFT:` names. LG +36.
- The original links each lib object whole. Keep an uncalled object with `#pragma comment(linker, "/INCLUDE:<IsValid>")` under `LIFT_EXE_LG/SCD/POD`:
  SCD +26, POD +26, LG +2. CG has no such object.
- The original BloodCert functions have no PDB symbol. Ours are ONLY-OURS. This does not change the MATCH count.
- Result: crypto orig-only 0 in each exe. The crypto functions now pair; 14 shared names are still DIFF (review-3 section 5).

### A4. `__declspec(noinline)` on a function that the original calls out of line (r2 A2; P11, P19, P24, P48; round 3): about 88
- Cause: our LTCG build inlines a small function. The function is a miss and its caller is a DIFF.
- Use it only when the original never inlines the function (check all callers in all exes). Mark it `// LIFT:`.
- Examples: `WinServiceConsole::reportStatusToSCManager` 0x17a20; `Session::Recv`, `SessionSendBuffer::clearPacketBufferList`,
  `PortListener::Clear`; `AlertSender::createSocket`, `LogMedia::Add`, `DbTransaction::close`; PipeConsole `connectPipe`,
  `disconnectAndReconnect`, `addNode`; POD `convertFailReason` x2, `CachedWatchdog::CachedWatchdog` 0x3d20,
  `AttachedItemContext::operator=`, `composeRelayHeader(FragmentPacket&)`, `combineFragmentRelayFormat` (pod-1: POD +17);
  `Log::Flush`, `Log::Initialize`, `DelayedRelease::Cleanup`, `Prng::addEntropy`, LG `Dump`/`Initialize` (noinline-2: +22).
- LTCG also moves a callee null check into the callers. noinline keeps it in the callee
  (SCD `DbTransaction::BindParam` 0x20fd0, the 10 callers score +1.3 to +3.8).
- Side effect: a caller can change its inline choice (SCD `NPServiceChannelManager::OnConnect` inlined `SetInvalidInfo`
  after `addNode` became noinline). Check the callers of the changed function.
- Opposite form (P32): `__forceinline` on an in-class ctor that the original never emits (`CacheD::CacheD`).
- A noinline function that no source code calls is removed by the linker. It stays orig-only. Check the orig xrefs in IDA when
  Hex-Rays shows no caller: Hex-Rays can drop calls. LG `LobbyGate::initialize` 0x12e70 calls `LobbyGateConfig::Dump` 0x13086,
  `BnsCommonConfig::Dump` 0x1308b, `ContentsRuleConfig::Dump` 0x13090 after `fclose`; the pseudocode has none. 3 calls added: LG +6.
  `LobbyGateConfig::Dump` must be `const` (mangled `QEBAXXZ`).
- funcdiff pairs by mangled name, or by PDB name when it is unique on both sides. An overload with another signature does not pair.
  Lift the overload of the original: POD `Packet::Decompose(int offset, int n, char const* format, ...)` 0x220d0
  (`QEBAGIHPEBDZZ`, 8 calls with `(0x18, 6, ...)`); SCD `Network::OpenPort` 9-arg form 0x1a8b0 with the folded constants
  (`2, handler, pbh, max, false, true, false`), the 5-arg overload removed.
- Per-exe inline choice: the original inlines `Log::Flush` in Daemon and calls it only from CrashHandler (`Log::FlushInline`).
  CG and LG call `Session::Send(Packet const*)` and `Session::deallocateCrypt` out of line; SCD and POD inline them. One source
  cannot match all 4 exes without a per-exe define (card perexe-3).
- Round 3: `InitSymbol` (CrashHandler.cpp, CG 0x7de0; else LTCG hoists `LoadLibraryW(L"dbghelp.dll")` into the 4 call sites, +4).
  `CryptoKey::Initialize` under `LIFT_EXE_LG/SCD/POD` (+3; without the guard CG loses `Network::Initialize`). LG `Session::send` 0xfe90
  (`ClientManager::broadcast` 76.9 -> MATCH). LG `Crypto::InstanceSize`, `RsaPrivate::RsaPrivate`, `BigInteger::IsPrime`, `Session::completeHandshake`
  (4 orig-only now pair). Manual: LG `BigInteger::RightShift` out of line (`LeftShift` tail-jumps to it at 0x59bca);
  `CryptoKey::generateBigNumber` out of line (both LG callers; `Dh::Start` MATCH).
- `__forceinline` on a helper also inlines its callees. Add `noinline` on the callee that the original calls (`initMemorySection` ->
  `Memory::CreateManager`; without it CG lost 1 MATCH).

### A5. Third-party code: vendor the exact upstream commit (r2 A3; P18): 73
- zstd: upstream `dev` commit bb6eaf64 (2018-05), not v1.3.5. See `vendor/zstd/README.md`. CG +16, LG +25, SCD +12, POD +20.
- Method: count the calls of one function on both sides (for example `ZSTD_litLengthContribution`) and bisect the commits.

### A6. Per-exe path literal of a shared file (r2 A4; P30, P35, P41, P45; perexe-3): 68
- Cause: the original builds each shared `.cpp` in each exe project. `__FILE__`-style literals are relative to the
  project (`..\Shared\` in LG/SCD, `..\..\Shared\` in CG/POD) and header paths contain the exe name, with a per-exe
  case (`e:\dailybuild02\<exe>-common-0.0.348\...` or `E:\DailyBuild02\<Exe>-Common-...`).
- Source: the literal is a macro with an `#ifndef` default. A wrapper `.cpp` per exe sets the macro and includes the
  shared `.cpp` (`BnsCommonConfigDefinitionShortPath.cpp`, `RefCntObject<Exe>.cpp`, `MemoryManager<Exe>.cpp`,
  `{Port,Timer,Channel}<Exe>.cpp`, `PacketUtil{LobbyGate,PostOfficeDaemon}.cpp`, `FragmentPacketLobbyGate.cpp`).
  For a header (`StlMemory.h`, `LIFT_STLMEMORY_FILE`) an exe-only `.cpp` defines the macro before the first include.
- Macros: `LIFT_PACKETUTIL_H_PATH` (narrow, CG default), `LIFT_CHANNEL_H_FILE` (wide, CG default), `LIFT_FRAGMENTPACKET_PATH`
  (narrow, `..\..\Packet\` default), `LIFT_STLMEMORY_FILE`.
- CMake: `LIFT_COMMON_PATH_SOURCES` leave `lift_common`; `lift_common_{lg,scd,pod}` take the wrapper if it exists, else the plain file.
  Keep the object order of CG (`LIFT_COMMON_SOURCES`, `lift_common_cg`), else the data layout moves.
- VS2010 `cl` gives C2308 for `L"" MACRO`. For a narrow macro that needs a wide twin, use `LIFT_WIDEN(x)` = `L##x` with a 2-step macro.
- Examples: LG `BnsCommonConfig::Dump`, POD `ThreadFreePacketPump::Initialize`, SCD `RefCntObject::addReferenceCount` 0x6890.
  Gains: s3 +14, lg-1 +26, scd-1 +5, paths-2 +17.
- Limit: an inlined COMDAT (for example `StlAllocator<Timer*,2>::deallocate` in `TimerQueue::~TimerQueue`) keeps the copy of the first
  object in the link order. That copy has the CG path. Fix needs a per-exe define in `tools/vs2010/build.sh` (card perexe-3).
- perexe-3 (+6): `LIFT_STLMEMORY_FILE` default depends on `LIFT_EXE_*` (`TimerQueue::~TimerQueue` MATCH in LG, SCD, POD).
  Orig POD has 2 case forms of the `StlMemory.h` path: mixed case in `PostContext`, `RelayContext`, `RelayTimeContext`, lower case in the others.
  One lower-case path made our link fold `_Tree<ushort,WorldChannel*>::_Erase` into the `<__int64,PostContext*>` copy. Define the mixed case in the 3 modules.
  Count the forms: `grep -o 'L"[Ee]:[^"]*StlMemory.h"' ~/.cache/bns-lift/hr/<EXE>/*.c`. Mixed case: LG Client; SCD CouponGameEventConfig; POD the 3 modules; CG none.

### A7. Virtual call on a global object through a base reference (r2 A6; P1): 49
- Cause: `BaseMemoryManager::_Instance.Alloc(...)` binds statically and LTCG inlines `HeapMemoryManager::Alloc`.
  The original calls through the vtable (`<indirect>`).
- Source: macro `BASE_MEMORY_MANAGER` = `static_cast<MemoryManager const&>(BaseMemoryManager::_Instance)` at all 59 sites.
- Example: `BaseRefCntObj::deallocate_me` CG 0x18460: `import:HeapFree` -> MATCH. CG +9, LG +11, SCD +15, POD +14.

### A8. Copy the original refs and reads one to one (r2 A7; P22 s3, P23, P40, P43, P45; round 3): about 36
- `return _log != nullptr ? _log : L"";` (original refs `L""`): pass the literal `L""`, not a named array.
- A literal as a pointer variable (`static wchar_t const* const X = L"..."`) makes VS2010 load the pointer; the caller has no
  literal ref. Write `#define X L"..."` (helpers-2, POD handlers).
- Put a new object in a local, store it once, call through the local (`LogBufferAllocator::initAllocator`, `GameEventManager` 0xaae0).
- One local for a repeated expression keeps the constant (`short logBytes = 2 * logCount`, `AlertSender::writev2`).
- Compare with the global: `id[0] == ID128_GUID_ZERO.id[0]` (SCD `RegisterGameEventLog` 0x10b00; POD `PostInfo::CheckValidityPostData`).
- Write `SmartCouponDaemon::_instance->` at each use (Enter, read, Leave), no local copy: SCD `SendRetryCouponPublication{Ok,Fail}Event::HandleEvent` (+2).
- NULL indicator: `long long v = 0; if (x == nullptr) v = -1;` (const -1), not `x ? len : kNullData`
  (SCD `UpdateStatusToPublicationSuccess` 0x129c0, POD `UpdateStatusToRetryReady`; +2).
- Base copy through a downcast: POD `DeliverPostRelayContext::initResponse` 0xfb50 `static_cast<RelayResponse&>(_response) = *response;`;
  `RetrieveCharacterInfoRelayContext::initResponse` 0x1f770 keeps one local downcast `r` (gives the `-8` const). +2.
- Member stores in the init list when the original orders them so (`CouponJob`, `EventNotiJob` 0x99f0).
- Log the `GetLastError()` value when the HR shows a second `GetLastError` call (`DChannelMgr::CreateDaemonListXml` 0xd5c0).
- `Session::Accept` (+4): read the members (`_port->_sessionHandler`, `_id`), not the params. The idle block is one `SetBusyWithPos(id).pos` call (PDB union `IdleStateTable::Pos`).
- `TrustedPacketBufferHandler::ToPacket` (+4): no short local for the header size. Read `*size` through a `short const*` two times (a local gives a range check with 0xf9e).
- WPO folds a global with a constant initializer, also when it is not `const`. `volatile int CONFIG_DIR_OPTION_LEN` keeps the 2 reads of the original.
- `finiMemorySection` (inlined in `Daemon::start`): read `Memory::_Manager[section]` again after the dtor call (`Free` reads it again).
- Hex-Rays folds reads of zero data (`ID128_GUID_ZERO`) to `0`. When funcdiff shows an orig ref that the pseudocode shows as zero, write the global
  (`_gameAccountId(ID128_GUID_ZERO)` in `GameEventLogEvent::GameEventLogEvent`).
- POD `RelayContext::ProcessRelayRequest`: read `PostOfficeDaemon::_instance->` at each use (99.5 -> MATCH).
- SCD `NPChannel::sendInitialConnectMessage`: use the shared narrow IP buffer of `Network.cpp`, not `t_addressBuffer`. Get the local address before the buffer clear (+1).
- LG `IdleWatcher`: read the watcher before `IdleStateTable::Create` and keep the pointer for the later table write.

### A9. Crypto source forms (r2 A12; crypto-2, manual): about 30
- Blowfish `encrypt`: `(s + 256)[x & 0xFF]` (pointer offset, disp 0x400/0x800/0xc00), not `s[256 + (x & 0xFF)]` (32-bit index add).
- Blowfish `decrypt` 0x360a0: `for (long long i = round - 1; i > 0; i -= 2) { t = F(r) ^ l; l = pbox[i-1] ^ t; r = F(t) ^ pbox[i] ^ r; }`.
- `Ctr::Encrypt`: `if (++_counter[j] != 0) break;`, not `_counter[j]++ != 0xFF`.
- `Prng::setSeed` 0x35d60: `rand() % 256` (orig `and eax,0x800000ff; jge; dec; or; inc`).
- `Prng::addEntropy` 0x35e10: `_alloca(size + 20)` with `hashSize = 20` before it. A fixed `buf[148]` let LTCG inline it.
- Manual: `Blowfish::Setup`: the inlined round code steps the index after the first P-box read; read the second entry at the new index minus 1.
  `BigInteger::sqr`: add 31 to the bit count, shift right by 4, clear the low bit. `BigInteger::Sub`: different signs call `add` first; equal signs select the operands
  and the sign before one `sub` call. `BigInteger::montgomeryNormalize`: `Pow2` first in source order, one `Set(1LL)` on the other branch.

### A10. Lift helpers as `static __forceinline`, shared END tail (r2 A10; P34, helpers-2; inline-3): 28
- A lift helper in an anonymous namespace or a plain `static` function is NOT inlined by VS2010 LTCG. The caller then has fewer
  refs (`L"Client.cpp"`, `Channel.h`). Make each helper `static __forceinline` and mark it `// LIFT:`.
- LobbyD handlers: `if (ch != nullptr) return ch; Log; Alert; return nullptr;`; `ch->GetId()` in each log call (lg-1, +5).
- Shared END tail: the original has one `<END PACKET HANDLER>` log at the end of the handler. All failure paths `goto done;`.
  Put `ResponseLines` in an inner block (a `goto` must not jump past an initialised local). POD `CacheEconomyPacketHandler.cpp`: 13 handlers MATCH.
- Inlined static local of a static member function: POD handlers inline `RelayHeader::GetMemberOffset()` (`static RelayHeader header;`
  + guard, value 0x18). Inline `GetMemberOffset()` in `RelayContext.h` and a zero ctor (+8). Gate needs `/Zc:threadSafeInit-` (C4).
- Helper shared by 2 functions: POD `UpdatePostStatus` as `static __forceinline` so that the literals become constants in each
  `__declspec(noinline)` wrapper (`UpdateStatusToDelivery*`, +2).
- A local struct with a `static __forceinline` member can reach a private member through a `friend` line (SCD `DaemonPacketHandlerSend`).
- `Log::Initialize` (+4): `__forceinline` on the private in-class `Log::Log`. The ctor writes 11 explicit stores `mediaCountPerList[0..10] = 0;` and one
  `memset(mediaList, 0, 88)`. A second `memset` gave an extra call; a `for` loop gave a rolled loop.
- A lift helper in an anonymous namespace that the original inlines shows as ONLY-OURS (`initMemorySection`, 133 bytes). Use `__forceinline` and see A4.
- LG `findDisconnectedNode`, `clearDisconnectedInfo` (`LobbyDChannel.cpp`) as `__forceinline` with an inline 20-character compare loop: score only.

### A11. Loop forms that VS2010 compiles as the original (r2 A13; P16, P26, P43; consts-3): 26
- `for (i = 0; i < 128; ++i) { ...; if (!f(i)) break; } if (i >= 128) return true;` is not unrolled (`PortListener::Initialize` 0x31fd0).
- Count down and step the pointers: `for (; count > 0; --count, ++defList, ++loadDefList)` (BnsCommonConfig, CG +4, POD +4, LG +2, SCD +2).
- Hex dump: walk a byte pointer and write `temp[k++]` three times (SCD `NPChannel::handlePacket` 0x57d0).
- `SysInfo::IpAddress` 0x144f0 (+4): the adapter retry loop in the MS sample form `do { malloc; if null break; result = GetAdaptersAddresses(...);
  if (result != ERROR_BUFFER_OVERFLOW) break; free; p = nullptr; ++retry; } while (result == ERROR_BUFFER_OVERFLOW && retry < 3);`. A `for (;;)` rotated
  the loop. Write `if (hostname == nullptr) { if (gethostname(...) == 0) {...} } else { WideCharToMultiByte }`.
- `SysInfo::Hostname` 0x14390 (+4): `sockaddr addr; memset; sockaddr_in* in = reinterpret_cast<sockaddr_in*>(&addr);` stores through `in` keep the struct (frame 0x600).
  Body in `if (hostname != nullptr) { ... return result; } return 3;`; tail `if (result == 0) { '.' loop } else { inet_ntoa }`.

### A12. Member types exactly as in the PDB: no extra `volatile` (r2 A8; P15): 25
- Cause: `long volatile _ref` in `RefCntObject.h`. The PDB type is plain `long`. A volatile store keeps the dead base ctor stores.
- Example: `PacketBufferPool::allocate` CG 0x128d0 -> MATCH. Rule: check each `volatile` member with `pdbq <EXE> type <Class>`.

### A13. CRT template overloads (r2 A9; P9): 25
- The original calls `swprintf_s<N>` out of line. Source: the 2-argument form with an array destination.
- Only when the size argument is the full array size. Clang build: `include/vs2010/crt_cpp_overload.h` under `#if defined(__clang__)`.
- Example: `WinServiceConsole::ServiceMain` 0x177d0. CG +3, LG +7, SCD +2, POD +13.

### A14. Global placement delete with the crash body, `::new`, construct before assign (manual beb4669, round 3): 22
- Cause: the original global placement `operator delete(void*, void*)` (CG 0x1000) calls `Log::Write` and `AlertSender::Write` (`Memory.h:173`).
  VS2010 calls it in the unwind code of each placement new. Our CRT form was empty: DIFF score 0 in each exe, and EH state `-2` was missing.
- Include `PlacementNew.h` before the CRT headers. Use the path of each original binary (last part `Memory.h`). All 4 placement deletes MATCH.
- `Port::Initialize`: write `::new` for the session pool and the listener. VS2010 then uses the global placement delete if a ctor throws (EH state `-2` in all 4 exes).
  The declaration and body of the placement delete alone did not give the state.
- Construct before assign: `Network::Network` constructs the end event, then assigns the allocation pointer to `EndEventObject` once (MATCH in CG, LG, POD;
  SCD has another ICF vtable name). Same form in `NPChannel::Setup` (`_sessionHandler`).
- POD `UnsentPostContextManager::addUnsentPostContextList`: allocate the header node in the list ctor (unwind state of the critical section).
  POD `PostContext::~PostContext`: write the allocation pointer to `__delv_buf__` before `Free`.
- Side effect: `Console::Flush` MATCH in CG and SCD (the empty functions shared a linker address before).

### A15. Map allocator with a non-const pair key, as in the PDB (r2 A11; P22 cg-1, P38, P44, P47): 22
- Cause: PDB names are `StlAllocator<std::pair<K,V>,2>` (key not const). Ours used `pair<K const,V>`.
- Source: the typedef uses `std::pair<K, V>`. Insert with `std::pair<K, V>(k, v)`, not `value_type(k, v)` or `std::make_pair`.
- Examples: `ClientManager::ReleaseSession` CG 0x6250, LG `ClientManager::RemoveClient` 0x60c0, SCD `JobManager::Clear` 0x6ff0 (SCD +11),
  POD `PostContext.h`, `RelayContext.h`, `RelayTimeContext.h`, `WorldChannel.h`, `WorldConfig.h` (pod-2, +4).

### A16. Allocation forms (r2 A16; P46, P28, P37, scd-2; arraynew-3, consts-3): 20
- Placement array new: `new (Alloc(sizeof(T)*n+8, file, line)) T[n]` (macro `liftArrayNew`, POD +8).
- Placement array new of a type with a ctor and dtor (orig calls `eh vector constructor iterator`): SCD `CouponJob.cpp`
  `#define __PLACEMENT_VEC_NEW_INLINE` before all includes, own `operator new[](size_t, void*) throw()`, own
  `operator delete[](void*, void*)` with the Memory.h:181 crash Log + Alert, `inline operator delete[](void* p) { __delv_buf__ = p; }`,
  dtor `delete[] _jobs; Free(__delv_buf__, ...)`. `JobManager::Initialize` 0x6e10 and `operator delete[]` 0x6850 MATCH (+2).
  `__delv_buf__` is a PDB `S_GTHREAD32`; no exe imports `??_V@YAXPEAX@Z`. Same shape in LG `GateKeyManager::Initialize` (card arraynew-3).
- Null-checked placement new before the null test: `T* p = mem != nullptr ? new (mem) T() : nullptr; if (p == nullptr) {fail}`.
- Inlined Packet ctor: `Packet packet = {nullptr, false};` then the 4 pool stores (`ClientManager::BroadcastAnnounceNotify`).
- arraynew-3 (LG +4): the scd-2 vec-new form in LG `Client.cpp`. Macro `liftArrayNew1(T, n, line)` = `new (Memory::_Manager[1]->Alloc(sizeof(T)*n+8, L"Client.cpp", line)) T[n]`;
  delete form `delete[] p; Memory::_Manager[1]->Free(__delv_buf__, L"Client.cpp", line);`. MATCH: `GateKeyManager::Initialize`, `ClientManager::Initialize`,
  `operator delete[]`, `CriticalSection::CriticalSection` (the vec ctor needs the real function).
- `PacketBufferAllocator::initAllocator` (+4): plain placement new and a ctor that assigns in the body, so that `InitializeCriticalSection` comes before the stores.
  `x = mem ? new (mem) T(...) : nullptr` with an init-list ctor moved the stores.

### A17. Error blocks and cleanup tails as in the original (r2 A14; P14, P36, P13 s1; inline-3): 19
- One full error block per failed call when the original calls `WSAGetLastError` in each (`Network::initializeSocketInterface` 0xda30).
- One shared cleanup tail (`goto cleanup;`) when the original has one tail (`TakeGoodsOk` 0x113e0).
- `__try { ... __leave; } __finally { ... }` when the HR shows `$__FINALLY_n` (`ListLobbyServiceItemInfoOk` 0x117a0).
- No explicit `p.Clear()` / `fp.packet.Clear()` before `return`: the dtor clears. An explicit Clear gives one more `Packet::Clear` call
  (`BypassPacket` 0x121d0; LG `Client::SendListGoodsOk` 0x4b20 +2; POD `WorldChannel::SendRelayResponse` 0x1e570 +1).
- One `Db::ReleaseTransaction` per return: `if (*ret != 0) return false; return true;`, not `return *ret == 0;` (POD `ResetAllDeliveryFailurePost`, +1).
- Zero-fill after the `Prepare` check, not at the declaration (POD `PostOfficeDB` `paramLen`).
- POD `RelayContext::ProcessRelayRequest/Response/Timeout` (+3): write the `AutoCS` in a `{ }` scope block and remove each explicit `lock.Leave()`.
  The original has the `AutoCS` dtor inline at scope end (one Lock.h line-122 assert tail per exit). Explicit `Leave()` plus the dtor gives 2 tails.
  For a failure path after the lock: set a flag in the scope, `return true` in the scope, run the failure code after the scope.
- LG `ClientManager::BroadcastAnnounceNotify`: let the packet dtor call `Clear` (95.8 -> 97.8, score only).

### A18. Compiler-generated destructors (r2 A15; P42, P29, P39): 12
- No user-declared dtor when the original dtor is a thunk with no vtable store (`EventObject`, `DynamicEventObject`; CG +1, LG +1, POD +5, SCD +2).
- An inline dtor with a member dtor gives the EH state of the original (`inline Db::~Db()`, `db->~Db();` in `Db::Clear`).
- Empty body when the member dtor does the work (`FragmentPacket::~FragmentPacket` 0x24e0).

### A19. Struct and packet init with separate stores, no aggregate init (inline-3, handlers-3, manual 27d5420): about 11
- LG `LobbyD::Send*` (+6): `Packet packet; packet.Splitter = nullptr; packet.IsFragmentPacket = false; memset(&packet.FragmentPacketCmd, 0, 28);`
  and no explicit `packet.Clear()`. `Packet packet = {};` gives a `memset` over the whole struct.
- `AlertSender::run` (CG 0x98f0, +4): set each socket event field with a separate store (`WSANETWORKEVENTS events = {0};` emits `memset`). Branch directly to the
  reconnect and stop blocks; this keeps the separate `sendRemain` sites for `FD_CONNECT` and `FD_WRITE`.
- POD `ManagementPacketHandler.cpp` `initReply`: set `CurHeader`, `Splitter`, `ListHead`, `ListTail`, `IsFragmentPacket`, `FragmentPacketCmd` one by one, then `Allocate()`
  (HelloReq 97.0 -> MATCH).

### A20. `#pragma inline_depth(0)` on one caller (manual): 8
- When the original calls `RefCntObject::removeReferenceCount` out of line in one function but inlines it elsewhere, put `#pragma inline_depth(0)` before that caller and
  set the default depth again after it. `LogMedia::Write` (CG 0x13910) and `TimerQueue::clearShortTermQueueSlot` (CG 0x16900) MATCH in all 4 exes.
- These 2 were on the stop list. A global `noinline` on the callee lost MATCH in all 4 exes (B).
- `inline_depth(1)` had no effect on `SessionSendBuffer::clearPacketBufferList`.

### A21. Read the PDB facts before a source change (cryptolib-3, manual): about 8
- A removed param: `BigInteger::Set(int, uchar const*, int)` has param 1 = sign and each caller gives 1. LTCG removes it as in the original (+3). Read the mangled name before you write `LIFT:`.
- A PDB global, not a member: `CryptoKey::s_initializedCount` (also the decrement in `Network::Clear`).
- An enum value: POD `POSTEVENT_PACKET_PUMP_EVENT` = 0x82 (Agent, CacheGate, World handlers; `TFPP_PumpPacket` MATCH).
- A return type: LG `PacketConcatenateBuffer::Decompose(VarData*)` 0x1bce0 returns `unsigned short` (the `int` form did not pair).
- Flag values: LG `ContentsRuleConfig::ConvPacketElement` 0x8ce0 `FormatMessageW` flags 0x3100. A folded argument: `L"LOBBYGATE"` to `AlertSender::init`;
  LG `Daemon::LoadVersion` passes its length argument to `swprintf_s`.
- ICF: check all public names at a vtable address before a source change (fix 10).

### A22. Per-exe source form (perexe-3, manual): about 6
- `tools/vs2010/build.sh` gives `-DLIFT_EXE_<CG|LG|SCD|POD>` to each source that has the token `LIFT_EXE_` (itself or in a repo header).
  Object: `build-vs2010/obj/<TAG>/<src>.obj`. `xargs -L1` joins a line that ends with a blank: write `"$s${tag:+ $tag}"`.
- `Session::Send(Packet const*)` `noinline` only for CG, LG; `Session::deallocateCrypt` `noinline` only for LG (0x194c0) with `if (crypt == nullptr) return;` (+1).
- `deallocateCrypt` type test as a compare chain `type == 0 || ((r1 = type - 1) != 0 && ((r2 = r1 - 1) == 0 || (unsigned)(r2 - 1) <= 1))`, not a `switch`
  (`Session::~Session` MATCH in CG, SCD, POD; LG inlines it twice under `#if LIFT_EXE_LG`, +1).
- A per-exe file when only one exe has another form: `ChannelSmartCouponDaemon.cpp` (`Channel::MakeSession` SCD 0x1f2b0 checks `portId - 1` and logs the missing port
  after the create branch; the same form in all 4 exes lost 3 MATCH).

### A23. PacketHandler form (handlers-3): 5
- POD `WorldSessionHandler`, `AgentSessionHandler`, `CacheGateSessionHandler`, SCD `ManagerSessionHandler`, LG `ClientSessionHandler::PacketHandler`.
- `void* iocpHandle = nullptr;` at the top, set it in the pump branch. `short const* const pCmd = &packet->CurHeader[1].size; if (pCmd == nullptr)`. Read `*pCmd`
  and `session->_id` at each use (no locals).
- Inline `Session::GetChannel` by hand where the original does (POD World, LG): `if (session->_channel != nullptr && !session->_waitForRelease) { addReferenceCount; channel = ...; }`.
  SCD 0xe980 calls `GetChannel`.
- `bool result = false;` after the channel block, `channel == nullptr` first, one `return result;`. LG list tests are signed (`*pCmd >= 0 && *pCmd < 0x6E`).

### A24. Small source forms: 1 or 2 each (r2 A17)
- UTF-8 BOM for a file with Korean literals (P13 s2; signal `??_C@_1IA@` against `??_C@_1KI@`).
- `switch` gives dec/dec; `if/else if` gives `cmp 2` (P6, `RefCntHistory::dump`).
- Keep a member pointer in a local before a lock call (P4, `Daemon::setState`).
- Pass the address of the variable, not a copy (P5, `CrashHandler::MakeCrash`).
- One `htonl` for a range test (P8, `Daemon::setAddress`).
- String literal size: `L"\0\0"` when the original literal has 6 bytes (P12).
- Tail call: `if (handler == nullptr) return false; return handler(s, p);` (P31, `CacheDChannel::PacketHandler`).
- SQLRETURN compare with the constant first: `0 == r || 1 == r` (P21).
- An inline ctor that the original compiles to `memset` must call `memset`, not a loop (POD `RetrieveCharacterInfoRelayRequest`, +1).
- Inlined ctor with a folded tag: set `_tag = 778` and `memset` the context in the ctor body (`PortListener`, score only).
- Inline ctor copies `ID128_GUID_ZERO` (P27; POD `PostInfo::PostInfo` 66.7 -> 88.9, score only).
- `wchar_t buffer[40] = L"{";` (the compiler emits the `memset` for the rest; `String::GetId128FromGuidString`).
- LG `ContentsRuleConfig::MakeListPacket` calls `FragmentPacket::FreeSize` in the option loop (0x8b1a); the opening and closing elements use the inlined check.

### A25. BloodCrypto source forms (crypto-4): 38
- `Rsa` dtor body and a non-virtual `Ripemd128` dtor (+4).
- `BigInteger::Mul` bit-count compare, inline `completeHandshake` body, `#pragma inline_depth(0)` on `allocateCrypt` (+5).
- `BigInteger::Sqr` bit-count compare, `inline_depth(0)`, `__forceinline` helpers (+3).
- `RsaPublic::Setup` / `RsaPrivate::Setup`: `if` form and `% 64` (+4).
- `sub`: one index and a `long long` borrow. `mul`: comba loop on 32-bit words with a 64-bit carry (+9).
- `expMod`: `M1 = M[1]`, no explicit `memset`, odd-modulus block with its own `return` (+3).
- `BigInteger::Divide(uint)`: table search as a `for` loop with `break`. The compiler then does not peel the first compare (LG +1).
- `OaepEncoder` `Setup`/`encode`/`decode`: call `_hash.Size()` again at each use, as the original does. Test `&_hash` for null in `Setup` (+9: LG, SCD, POD x3).

### A26. Read globals and fields again at each use (pod-4): 2
- POD `CacheGateSessionHandler::OnConnect`/`OnClose`: no locals for `PostOfficeDaemon::_instance` or `session->_channel`. Write the full expression at each use.
  The original loads them again after each call.

### A27. Single-expression placement new (pod-4): 1
- POD `HandlePostOfficeServiceCheckPostCapacityReq` (0x2047c): `ctx = ::new (Memory::_Manager[2]->Alloc(...)) T(...);` with no `memory` local and no null test
  (`// BUG:` no null check, 0x20250). Set the `_response` member in the ctor init list, not in the body (a body store left a dead store, 0x20556).
- It does not always work: `MakePostContext` (4 loaders worse) and `HandlePostOfficeRegisterPostReq` (no change). See B.

### A28. Const global and a block copy for an id128 member (pod-4): 5
- `ID128_GUID_ZERO` is `id128 const` (PDB `?ID128_GUID_ZERO@@3Tid128@@B` in all 4 exes). This alone gives POD `PostInfo::PostInfo` (+1).
- `BnsCommonConfig` ctor (`BnsCommonConfigDefinition.h`), per-exe form (A22): SCD and POD store the scalars first and then
  `memcpy(&_npAppId, &ID128_GUID_ZERO, sizeof(id128))`. The original (POD 0x1974) loads the global again for each qword.
  CG and LG keep the struct assignment (they MATCH with it). SCD +2, POD +2 (`LoadBnsCommonConfig`, `ReloadBnsCommonConfig`).

### A29. PDB line maps give the source shape (console-4): 11
- Read the PDB line map of the original before a source change: `LIFT_IDA_DIR=... tools/pdbq.py <EXE> lines <lo> <hi>` (hex rva).
  The line numbers show the number of statements, the exits and the order of the blocks.
- One exit block per lookup (`InitSymbol`, CG 0x7de0; 4). The PDB gives one line per `GetProcAddress` and puts `FreeLibrary` on the last
  lookup line. Write one `if (... == nullptr) { FreeLibrary; return false; }` per lookup. VS2010 merges the blocks. A single `||` chain fails (B).
- One result exit (`WinServiceConsole::UninstallService`, CG 0x17f00; 4). The PDB gives one `return` for all paths. Use `bool result = false;`,
  set it on success, call each `CloseServiceHandle` once after its block. VS2010 then duplicates the tails as in the original.
- Match-node search with a list reference (LG `PipeConsole::SetRunningInfo` 0x2A5A0; 1). `ItemList& list = _running; ItemNode* node = nullptr;`
  and `node = item; break;` on a match. The loop end needs no null test, and the tail address comes from the list address.
- An `if / else if` chain where the PDB lines give it (LG `IdleStateTable::scan` 0x24E8C, lines 154, 158, 169; 1). The `switch` gave another shape.
- Constant folding, not a per-exe source (LG `PipeConsole::addNode` 0x2a6d0; 1). `addNode` is the same source in all 4 exes (PDB lines 841-859).
  LTCG folds the `L""` argument in CG/SCD/POD. Keep one source form that copies `valueString`.
  Check for constant folding before you add a per-exe form or a `// BUG:` mark.
  Compare the same function and its callers in all 4 exes before you write `BUG:`.

## B. Patterns that did not work (do not try again without a new idea)
- `!wcscmp(...)` or `int r = wcscmp(...)` to keep the -1/0/1 value (`PipeCommandProcess::processCommand`).
- Body of `removeReferenceCount` in the header, `inline`, or `__declspec(noinline)` (all 4 exes lose MATCH: CG -2, LG -2, POD -1).
- `__declspec(noinline)` on `AutoCS::~AutoCS`/`Leave` (POD loses `CachedWatchdogManager::initWatchdogManager`).
- `__declspec(noinline)` on `TimerQueue::Remove` / `removeShortTermQueue` (POD: no gain), on `_Tree::clear`.
- A global `noinline` on `RefCntHistory::add`: only `SessionSendBuffer::clearPacketBufferList` calls it out of line.
- One search loop per branch in `PipeConsole::SetInvalidInfo` (caller inlines it).
- Label place, `switch` or `if` chain for `PipeConsole::run` (block order stays).
- `WSANETWORKEVENTS events = {0};` (VS2010 cl gives `memset`), merged FD_CONNECT/FD_WRITE branch (`AlertSender::run`).
- `LogFile::writeFile` loop forms (93.9 best), `DbTransaction::connect` fully nested (worse).
- Else-if chain in `HandleCacheGateHello` (score up, no MATCH), nested version ifs (worse).
- Inlined PipeConsole find forms (`CacheD::Initialize`, const 0x278), placement new in `CacheDList::Initialize`; fail test first in `CacheD::Verify`.
- Positive conditions first in LG handlers (the original puts error blocks first).
- Read `_connectContext` in `Session::HandleEvent` (worse). Source `goto` to merge the 780/838 `LT_ERROR` tails (98.5 -> 97.1).
- CMake `target_compile_definitions` for a per-exe literal: it changes only the clang build, not parity (paths-2).
- `aes128TableEncrypt`/`Decrypt` in the rijndael-alg-fst loop form: still DIFF (orig loads the image base 3 times). Reverted.
- `Client::SendTakeGoodsOk` in the positive form (`if (Compose != 0) {...} else { failSend }`): 98.9 -> 93.8. Reverted.
- POD `HandlePostOfficeRegisterPostReq` 0x1aaa0: move the Log 208 block after the success return with a `goto`: no change.
- POD `DbTransaction::BindCol` (6-arg) in the positive form: loses the BindCol MATCH and does not inline. Reverted.
- POD `MODULE_NAME` as `#define` alone (no helper change): no change.
- POD lock asserts: local macros instead of `AutoCS` in `UnsentPostContextManager` (score +0.2, no MATCH).
- Round 3 (do not try again without a new idea):
  - `WinServiceConsole::UninstallService` (CG 0x17f00, orig 5 `CloseServiceHandle`, ours 4): swapped `DeleteService` branches (95.1, worse) and a
    `wprintf` select. VS2010 tail-merges the fail path. Compiler cross-jump.
  - `PipeConsole::SetInvalidInfo` (CG 0x15d90, orig 2 `addNode` sites): loop split per branch, `node == &tail || node == nullptr`, `goto` form. VS2010 merges the calls.
  - `PipeConsole::run`: 3 more forms in order-3. Stop.
  - `Channel::MakeSession` port-first in all 4 exes: CG, LG, POD lose MATCH. Use the per-exe file (A22).
  - POD `UnsentPostContextManager::initContextManager`/`updateWorldList`: `goto` form and RAII form give the same layout.
  - `PacketBuffer::Compose` case P: `memcpy` tail merge (96.3 -> 93.0). `Session::HandleEvent`: common log (98.5 stays).
  - `HandleCacheGateRelay` (CG): 3 forms, 93.3 best.
  - AES: key setup in groups of 5, dec key pointer form. `BigInteger::mul` pointer loop. `ObjPool` init list.
  - Success-first: `CacheD::Verify` mismatch-first, SCD `loadUnhandledGameEventLog`, POD `WorldConfigManager::loadWorldConfigFile` (lower score).
  - Failure-first: POD `PingRelayContext::processRelayResponse` (97.6 -> 95.1).
  - `InitSymbol` common unload. GUID word loads. `#pragma inline_depth(1)` on `SessionSendBuffer::clearPacketBufferList`.
  - `Network::Clear` countdown loop or cached port. `CacheDList::LoadCachedListConfigFile` loop forms (96.3).
  - An explicit `Packet::Allocate` in LG `Client::Send*` (the allocator then inlined).
  - SCD DB loaders with all columns inline: the original inlines only column 1 (dbbind-3).
  - LG `ClientManager::BroadcastAnnounceNotify` branch swap: no gain (97.8 came from A17).
- pod-4 (do not try again without a new idea):
  - POD `MakePostContext` single-expression `::new` (A27): 4 DB loaders worse. `HandlePostOfficeRegisterPostReq` single-expression `::new`: no change.
  - POD `PostOfficeDB::LoadPostList` success-first reorder: worse. The loop header stays duplicated (3 tries, 99.1).
  - `ID128_GUID_ZERO` const alone, or an element copy `.id[0]`/`.id[1]`, in the `BnsCommonConfig` ctor: VS2010 still merges the loads. Use `memcpy` (A28).

- crypto-4 (do not try again without a new idea):
  - Remove `__declspec(noinline)` from `RightShift`: `LeftShift` loses its tail-jump MATCH and `invMod` loses score.
  - `#pragma inline_depth(0)` on `LeftShift`: no gain.
  - `expMod` with one exit (`if/else`): one extra `memset` stays.
  - `Rsa::decrypt` zero fill (LG 0x52de0, 91.7): pointer byte loop, `while (c < blockSize)` with a hoisted size, `buf` at function scope. VS2010 makes a `memset` each time. The original keeps a byte loop.

- console-4 (do not try again without a new idea):
  - `PipeConsole::processCommand`, `PipeCommandProcess::processCommand`: `wcscmp` result in the `sbb` form (2 forms more, no gain).
  - CG `DaemonConfig::Dump` and `_Def` (97.9): the original has RTTI data next to `_Def`. We build with `/GR-`. The const pointer form gave 0.
  - SCD `DaemonConfig::Dump` (97.9, refs 94): the PDB const pointer `LOCALHOST_IP` (SmartCouponConfig.obj) in the `_Def` initializer gave +1
    on the old base (eaba76b). On main after pod-4 it gives 0. Keep `LOCALHOST_IP` only because it is the PDB name.
  - SCD, POD `ReloadBnsCommonConfig`, `LoadBnsCommonConfig`: `const`, the init list and per-qword copies did not stop VS2010 from merging the
    `ID128_GUID_ZERO` loads. pod-4 solved it with `memcpy` (A28).
  - LG `PipeConsole::addNode` without `noinline` (LG only): `LobbyD::Hello` 91.5 -> 78.9, `OnClose` 93.8 -> 81.7. Reverted.

## C. Tool and build facts
### C1. funcdiff reads a vtable ref as a string (FIXED in lift-parity-tool-2)
- `Image.string_at()` ran before `target_name()`. A vtable whose slot 0 holds `0x1400074xx` read as `" t"`, `"PI"`, `"@c"`.
  Each code size change moved 2 to 8 MATCH. Fix 5 (`noise.md`): the `??_7` symbol at the exact RVA is used first.

### C2. `.tls` variable order (FIXED in lift-parity-tool-2)
- The immediate after `mov rax, gs:[0x58]` is the `.tls` offset of a thread variable. Fix 6: the offset is named from PDB
  `S_LTHREAD32`/`S_GTHREAD32` and counted as a ref `tls:<name>`. The guard needs `[reg + reg]` use next to a `gs:` operand.
- A `tls:` DIFF that is left is real or a layout DIFF: the orig `.tls` order is `_Instance` 0x8, `IoWorker::WorkerId` 0x10,
  `LogBufferAllocator::_Local` 0x18, `__delv_buf__` 0x20, `PacketBufferAllocator::_Local` 0x28, `Thread::Current` 0x30,
  `IoWorker::ZstdCCtx` 0x38, `NPChannel::_buffer` 0x40. Ours also has `t_addressBuffer`, `__ip_addr_string_a__/_w__`. Not fixed.

### C3. Name forms in the PDB (FIXED in lift-parity-tool-2)
- `<K const ,V>` (original) against `<K const,V>` (ours): `name_form()` removes the space (fix 7).
- `?Setup@PacketCrypt@@SA?AW4ErrCode@1@H@Z` not demangled in the original PDB: `simple_demangle()` (fix 8).
- ICF folds give other names (`Packet::~Packet` as `Packet::Clear`; `PingRelayContext::GetRequestWid`;
  our link folds `_Tree<unsigned short,WorldChannel*>::erase` into `_Tree<__int64,PostContext*>::erase`). Not source causes.
- Noise that is left (do not fix in source): string-literal ref duplicates (`L"world packet handler"` x2 or x3),
  `PostOfficeDaemon::_instance` ref count (`CacheGateSessionHandler::OnConnect`, `AgentSessionHandler::OnClose`).

### C4. Build facts
- `tools/vs2010/build.sh` tracks headers (tool-2): `cl /showIncludes` writes `build-vs2010/obj/<src>.dep`. No `touch` is necessary for these headers (see the round-3 line below).
  A new `build-vs2010/obj` builds all objects once (about 5 minutes in a new worktree).
- `tools/vs2010/build.sh` compiles one object per source path with fixed flags. The per-exe define exists now (A22).
- Gate link has no `_Init_thread_*`: `add_compile_options(/Zc:threadSafeInit-)` in `CMakeLists.txt` (not the toolchain file; an
  old `CMakeCache.txt` keeps old flags). VS2010 has no thread-safe statics, so parity does not change.
- Include `crt_cpp_overload.h` only under `#if defined(__clang__)`.
- The link sorts the objects of each target. A new object in a target moves the data layout.
- Worktree setup: copy `vendor/zstd/src` from the main checkout, then `git fetch --shallow-since=2018-05-01 origin dev; git checkout bb6eaf64`
  in it. Set `LIFT_IDA_DIR=.../private-project/ida/lift`.
- Times: full `tools/parity.sh` about 3.3 min (warm objects); `tools/parity.sh LobbyGate` about 32 s.
- Helpers (not in git, copy them from an older worktree or write them again): `.scratch/dis2.py <EXE> '<regex>'` (orig and ours disassembly;
  import `from capstone import x86_const as X86`), `.scratch/fdfull.py` (funcdiff with full diff context), `.scratch/classify.py` (review-2 classifier).
  Run with `uv run -q --no-project --with capstone --with pefile python ...`.
- Round 3: the `.dep` files list only the `BloodLib/include` headers. After a change in another header, `touch` the `.cpp`.
  A lowercase `/showIncludes` path is fixed. A new worktree can have no `<EXE>.funcdiff.json`: run `.scratch/fd.sh` or one parity run first.
- Quick loop for one exe (about 30 to 45 s): `tools/vs2010/build.sh <EXE>`, `funcdiff.py <EXE> --build build-vs2010 --json x.json`, then compare with
  a copy of `build-vs2010/<EXE>.funcdiff.json` (`parity.sh` overwrites it). Per-exe objects are in `build-vs2010/obj/<TAG>/`.
- Do not name a script `dis.py`: it shadows the stdlib `dis` (capstone import). Import `funcdiff.Image` for the disassembly of one function.
- `tools/parity_shared.py --list` showed DIFF for `Session::~Session` and `TimerQueue::~TimerQueue` while `<EXE>.funcdiff.json` showed MATCH (perexe-3). ❓
  Check `parity_shared.py` input before you trust a single DIFF entry.
- IDA: a broken `.i64` does not open (status 4). Copy the exe to a scratch directory and open the copy.

## D. Open causes (not solved, not tool noise)
Solved in round 3 and removed: closed crypto libraries (A3), `Port::Initialize` EH state -2 and scalar placement delete (A14),
`TimerQueue::clearShortTermQueueSlot` and `LogMedia::Write` (A20).

- Stop list (no source change without a new idea): `aes128TableEncrypt/Decrypt/SetupEncKey/SetupDecKey` (orig loads the image base 3 times; orig unrolls 5 times),
  `Session::Session` and `StaticPageMemoryManager::Initialize` (LTCG address fold), `ThreadManager::Initialize(128)` and `Daemon::Start` (constant propagation),
  `PipeConsole::run`, `PipeConsole::SetInvalidInfo`, `WindowConsole::Open` (ICF), `EventNotiJob::finalize` 0x9cc0 and `JobManager::Execute` 0x71a0 (constant CSE),
  `Finalize` `.tls` 0x18/0x10, `ZSTD_compressBegin_internal` (vendor).
- EH state `-2` without a known `::new` site: `wmain` x4 (CG 61.9, LG 66.7, SCD 66.7, POD 85.2), `FragmentPacketConcatenater::Clone` (LG, POD 93.3),
  LG `IdleWatcher::run`, SCD `NPServiceChannelManager::HandleMessage`, POD `operator delete[]` (score 0). Try A14 first.
- Crypto (14 shared names in LG, SCD, POD): `BigInteger::Mul` (consts 0x1000/0xffffffe0, `_alloca`), `mul` x2, `sub`, `Sqr`, `Divide` 76.7, `InvMod`, `invMod`
  (ours inlines `LeftShift`, `add`, `sub`, `RightShift`), `expMod`, `OaepEncoder::Setup/encode/decode`, `Rsa::decrypt`, `RsaPublic::Setup`,
  `RsaPublic::~RsaPublic` (orig refs `??_7Ripemd128` and `??_7RsaPublic`, ours `??_7Rsa`). LG only: `Crypto::Create` 34.0, `InstanceSize` 44.4,
  `allocateCrypt` 67.4, `Dh::*`, `RsaPrivate::*`, `IsPrime` 82.2, `isPrimeMR` 88.4, `completeHandshake` 55.6.
- Merged `Log::Write` tails: `Session::HandleEvent` 0xf1c0 (98.5), `CacheDList::MakeSessionAll` 0x27d0, SCD `CouponJob::transit` 0x6990.
- Constant propagation: `Network::OpenPort` assert (orig CG has 3 crash sequences, lines 170, 175, 177; orig test `purpose != 1 && purpose != 2`), `Session::Connect` timeout (LG, SCD).
- `_instance` reload in LG `KickNotify`, `CloseSessionNotify`.
- `Session::SendV` (CG 0xfaa0): the orig `Compose` call has the const 0xf9e twice; ours once. Not checked in the disassembly.
- `SessionSendBuffer::clearPacketBufferList` x4: orig calls `RefCntHistory::add`. A global `noinline` lost MATCH (B); `inline_depth(1)` had no effect.
- `IoWorker::run` x4 (84.9), `Network::Clear` x4 (97.2), `PipeConsole::processCommand` x4, `PipeCommandProcess::processCommand` x4.
- DB loaders (dbbind-3): SCD `SmartCouponDB::Load*`/`Process*` 95.0 to 97.8: ours has one more `DbTransaction::Fetch`, consts 0x2/0x3/0x5 (column index), one more `L"db"` ref.
  POD 0x14e50 98.3, 0x190f0 98.6: rotated fetch loop (one more `memset, memset, Fetch`), const 0x23 missing.
  POD 0x15fa0 88.4, 0x18010 88.8: orig merges the 17 `statmentErrorLog` calls into one site and logs "Not initialized" before the binds. POD `RegisterPost` 84.0 not examined.
- POD `HandleCacheGateRelayFail/Invalid` 82.7: the original has 3 `ProcessRelayResponse` calls (not tried). POD `Packet::Allocate` pool index: orig 0x28, ours 0x90.
- POD `ManagementSessionHandler::PacketHandler` 97.8: the handler call is at the end in the original.
- Block layout that the source order did not move: SCD 0x8e80, POD 0x1aaa0, LG `Client::SendTakeGoodsOk` 0x4ed0, POD `updateWorldList` x3,
  SCD `DChannelMgr::SetupDaemonList` 96.3 (ref order and const 0x178 left).
- Constants with no known cause: POD `PostInfo::CheckValidityPostData` (switch lowering 0x2/0x7 vs 0x5), POD `ComposeResponsePacket` x2, `Blowfish::Setup`.
- LG `GateKeyManager::MakeGateKey` 94.3 (not tried). LG `ContentsRuleConfig` 4 path literals.

## F. Manual parity notes (round 3)
The manual work of round 3 (commits 27d5420, 46fe9c1, beb4669 and later). The patterns are merged into A; the notes stay for the details.

### AlertSender socket event loop

- Commit `27d5420` added one match in each of the four executables.
- `AlertSender::run` (CacheGate 0x98f0): Initialize each socket event field
  with a separate store. Aggregate initialization emitted a `memset` call.
  Branch directly to the reconnect and stop blocks. This keeps the separate
  `sendRemain` call sites for `FD_CONNECT` and `FD_WRITE`.

### Manual server parity checks

- Commit `46fe9c1` added six matches in LobbyGate, two in
  SmartCouponDaemon, and three in PostOfficeDaemon.
- The original `CryptoKey::Initialize` uses the PDB global
  `s_initializedCount`. A class member gave a different data reference.
  Use the same global for the decrement in `Network::Clear`.
- Both LobbyGate callers call `CryptoKey::generateBigNumber` out of line.
  Keeping that call restores the range check and matches both
  `CryptoKey::generateBigNumber` and `Dh::Start`.
- LobbyGate reads the idle watcher before `IdleStateTable::Create`.
  Keep that pointer for the later table write.
- The PostOfficeDaemon PDB gives `POSTEVENT_PACKET_PUMP_EVENT` the value
  `0x82`. Use this enum value at the Agent, CacheGate, and World
  session handler calls. This matches `TFPP_PumpPacket`.
- In `BigInteger::Sub`, handle different signs with `add` first.
  For equal signs, select the operands and sign before one call to `sub`.
- In LobbyGate `ContentsRuleConfig::ConvPacketElement` (0x8ce0), the
  `FormatMessageW` flags are `0x3100`. Use `FORMAT_MESSAGE_ALLOCATE_BUFFER`,
  `FORMAT_MESSAGE_FROM_SYSTEM`, and `FORMAT_MESSAGE_ARGUMENT_ARRAY`.
- Testing the last `InitSymbol` lookup separately and jumping to a
  common unload block gave no new match. A common log block in
  `Session::HandleEvent` also gave no new match.

### Placement delete and shared functions

- Commit `beb4669` added five matches in CacheGate, five in LobbyGate,
  six in SmartCouponDaemon, and six in PostOfficeDaemon. All previous
  matches held.
- The original placement delete at CacheGate 0x1000 calls `Log::Write`
  and `AlertSender::Write`. Include `PlacementNew.h` before the CRT
  headers. Use the path in each original binary, with the last component
  spelled `Memory.h`. All four placement delete functions match.
- In `Port::Initialize`, use `::new` for the session pool and the listener.
  VS2010 then uses the global placement delete if a constructor throws.
  This gives the `-2` unwind state in all four executables. The declaration
  and body of the global placement delete alone did not give that state.
- In `Network::Network`, construct the end event before the assignment
  to `EndEventObject`. Use the allocation pointer for that assignment.
  This gives one store to the global pointer. The function matches in
  CacheGate, LobbyGate, and PostOfficeDaemon. SmartCouponDaemon still
  has a different vtable name after the linker folds identical code.
- In `Blowfish::Setup`, the inlined round code advances the index after
  the first P-box read. Read the second entry at the new index minus one.
- In `BigInteger::sqr`, add 31 to the bit count. Shift the result right
  by four and clear the low bit.
  This gives twice the digit count in the same form as the original.
- In `SmartCouponDaemon::reload`, log `GetLastError()` when
  `_wmakepath_s` fails. Put the configuration reload failure and
  the unchanged case before the case that calls `Dump`.
- In `UnsentPostContextManager::addUnsentPostContextList`, allocate the
  header node in the list constructor. This gives the original unwind
  state for the critical section.
- The new placement delete also let `Console::Flush` match in CacheGate
  and SmartCouponDaemon. The empty functions previously shared a
  linker address.
- These tests gave no new match. The AES table key setup tests used
  groups of five encryption key steps and a pointer to the middle of
  the last decryption key. The `CacheD::Verify` test put the mismatch
  branch first. The `loadUnhandledGameEventLog` test put the
  successful load branch first.

### Manual parity for arithmetic, startup, and cleanup

- The full build added six matches in LobbyGate, four in SmartCouponDaemon,
  and four in PostOfficeDaemon. All previous matches held.
- LobbyGate `BigInteger::LeftShift` jumps to `RightShift` at 0x59bca.
  Keep `RightShift` out of line so VS2010 emits that jump.
- In `BigInteger::montgomeryNormalize`, call `Pow2` first in source
  order. Use one `Set(1LL)` on the other branch. `Set` clears the digits.
- LobbyGate `Daemon::LoadVersion` passes its length argument to
  `swprintf_s` at 0x1f21c. Use that argument so the daemon and alert
  sender can pass their own buffer lengths.
- Pass `L"LOBBYGATE"` to the alert sender in `LobbyGate::initNetwork`.
  The original folds the service name into `AlertSender::init`.
- In `NPChannel::Setup`, construct the handler before the assignment
  to `_sessionHandler`. Assign the allocation pointer once.
- In `EventNotiJob::eventNotiExpire`, use the same log arguments as
  `EventNotiJob::init`. The original uses ID 0 and type and state -1
  for a null log argument.
- In `PostContext::~PostContext`, write the allocation pointer to
  the PDB thread variable `__delv_buf__` before calling `Free`.
- In `UnsentPostContextManager::deliverUnsentPost`, put the failure
  path for `OccurEvent` before the success path. Keep each release
  with its original line number.
- LobbyGate `ContentsRuleConfig::MakeListPacket` calls
  `FragmentPacket::FreeSize` in the option loop at 0x8b1a.
  The opening and closing elements use the inlined check.
- The LobbyGate PDB gives `PacketConcatenateBuffer::Decompose(VarData*)`
  at 0x1bce0 an `unsigned short` return type. The previous `int` type
  gave a different symbol for this overload. The result now pairs at
  95.2. A separate pointer increment did not change the score.
- In PostOfficeDaemon `WorldConfigManager::loadWorldConfigFile`, read
  the XML reader version once. The original uses `_wcsicmp` and logs
  the same value on a mismatch. The call order still differs. The
  test that put all successful branches first gave a lower score.
- A pointer loop in `BigInteger::mul(unsigned int)` did not add a match.
  Explicit initial allocation in `Client::SendTakeGoodsOk` and
  `Client::SendListLobbyServiceItemInfoOk` inlined the allocator.

### Manual parity for logging, timers, and job dispatch

- This pass added two matches in CacheGate, two in LobbyGate, four in
  SmartCouponDaemon, and two in PostOfficeDaemon. It added three
  shared matches. All previous matches held.
- In the four-argument `DbTransaction::BindCol` (SmartCouponDaemon
  0x20e40), check the null statement handle first and return after the
  log call. Then bind the column and return on error. This gives the
  original order of the log and ODBC calls.
- In `SendPublicationEvent::HandleEvent` (SmartCouponDaemon 0xbe30),
  put the null job log before the call to `CouponJob::execute`.
- Use `#pragma inline_depth(0)` on the caller when the original calls
  `RefCntObject::removeReferenceCount` out of line. Set the default
  depth again after the caller. This lets other callers still inline
  the release. See `LogMedia::Write` (CacheGate 0x13910) and
  `TimerQueue::clearShortTermQueueSlot` (CacheGate 0x16900). These two
  functions match in all four binaries.
- VS2010 can give a lowercase path in `/showIncludes`. The case-sensitive
  filter dropped that path. For example, it dropped `Timer.cpp` from
  the dependencies of `TimerLobbyGate.cpp`. Match the Windows path
  without a case check. Use `winepath -u` to get the path on disk.
- The following tests did not add a match. Selecting the message before
  calling `wprintf` in `WinServiceConsole::UninstallService` did not
  restore the calls to close the service handles. Loading each GUID
  word separately did not change the BnsCommonConfig scores. Putting
  the failure branch first in `PingRelayContext::processRelayResponse`
  lowered its score from 97.6 to 95.1.
- An inline depth of 1 had no effect on
  `SessionSendBuffer::clearPacketBufferList`. A countdown and a cached
  completion port handle had no effect on `Network::Clear`. A loop to
  compare the XML element name and a common release call in
  `CacheDList::LoadCachedListConfigFile` lowered its score to 96.3.
- Initializing the pool lists in the `ObjPool` constructor initializer
  list and using a local node in `ObjPool::Finalize` did not change
  their scores.
- In `ClientManager::BroadcastAnnounceNotify` (LobbyGate 0x62c0),
  let the packet destructor call `Clear`. This removes the extra
  call and raises the score from 95.8 to 97.8. The remaining
  difference is one merged log call.
- In CacheGate `Network::initWorkerThread`, the original sets
  `r14d` to the TLS offset at 0xd94f, before the loop. It uses the
  register at 0xd9c9 to clear `IoWorker::ZstdCCtx`. The original and
  build PDBs give offsets 0x30 and 0x18 for that variable. The
  six-instruction check missed the address use. See fix 9 in
  [noise.md](noise.md).

### TLS addresses that the compiler forms in separate blocks

- Use the TLS block load and the offset definition to check each
  address. The offset can occur before a loop. The address can use an
  ADD instruction. See fix 9 in [noise.md](noise.md).
- After the tool fix, SmartCouponDaemon
  `NPChannel::sendInitialConnectMessage` showed a different TLS variable.
  The original uses the shared narrow IP address buffer, at 0xfa40.
  The lift used `t_addressBuffer` from `NPChannel2.cpp`. Use the buffer
  from `Network.cpp`. Get the local address before clearing the buffer.
  The function now matches.
- SmartCouponDaemon `Channel::MakeSession` at 0x1f2b0 checks
  `portId - 1` against the last valid index before it reads the
  port array. It puts the missing-port log after the session creation
  branch. Use this form from `ChannelSmartCouponDaemon.cpp`. The
  other original builds use a fixed port ID. Applying the same
  source form across all four builds changed the log order in those
  three builds and lost their matches.

### Public names of folded virtual tables

- Check all public names at the address before changing the source.
  The CacheGate build gives the `SessionRecvBuffer` table in
  `Session::initialize` a second name, `CrashHandler`. Use the
  name that the two PDBs share. See fix 10 in [noise.md](noise.md).

## crypto-4

| Result | Count |
| --- | ---: |
| MATCH gain (LG +16, SCD +11, POD +11, CG +0) | 38 |
| MATCH lost | 0 |
| Working forms (A25) | 8 |
| Failed forms (B, crypto-4) | 4 |

- Worked: copy the call pattern of the original. Call a virtual getter at each use. Use the loop form of the original (`for` with `break`). Use the word size of the original in `sub`/`mul`.
- Worked: `#pragma inline_depth(0)` on one caller when the original calls a helper out of line.
- Failed: VS2010 changes a zero-fill byte loop into `memset`. No source form kept the byte loop.
- Failed: `noinline` on one helper changes the inline choice in other callers. Check all callers after each change.
- Open: big `BigInteger::Divide` (76.7), `invMod` (83.1), `InvMod` (89.7), `IsPrime`, `isPrimeMR`, `Crypto::Create`, DH and `BroadcastCrypt`. See the crypto-4 handoff.

## net-4

### A. Worked (+15 MATCH, 0 lost)

| Function | Form | Gain |
| --- | --- | --- |
| `SessionSendBuffer::clearPacketBufferList` | `inline_depth(0)` and the `removeReferenceCount` body by hand (A20) | +4 |
| `Session::HandleFailedEvent` | Close and `Leave` in each case, not one shared tail | +4 |
| `Network::Clear` | Cache `Port*` only for the null test; read `_port[i]` again for each use | +4 |
| `Session::Connect` (LG) | Member reads and `memset` in source order | +1 |
| `Session::SendV` (CG) | Give `Compose` the fields of the header | +1 |
| `Network::OpenPort` (SCD) | `id < 1 \|\| id > 24`; `initialMode` list 0..3 | +1 |

### B. Failed (2)

- Local non-static `const` array for the max-session table: the compiler copies it to the stack. Keep it `static`.
- `Port` ctor with body assignments: the store order is correct, but no MATCH. `OpenPort` refs still differ, because the original table has no PDB name.
- Open: SCD `Session::Connect` keeps a `reconnect` test in the original. Our LTCG propagates the constant. Look at the callers, not the body.

## packet-4

### A. Patterns that worked (count = functions made MATCH)

| Pattern | Count | Example |
| --- | --- | --- |
| Pointer loop over the format with the index check in the loop | 8 | `PacketBuffer::Compose` x4, `Decompose` x4 |
| Block order of the cold error tails from the log line numbers | 10 | `Compose`, `Decompose`, `CheckCompose` |
| Signed `short` for sizes and headers (the store uses 0xFFFF8000) | 5 | `Compose` x4, `TextStreamPacketBufferHandler::ToBuffer` |
| 64-bit pointer form for the destination | 4 | `Decompose` x4 |
| Single exit with a size variable | 2 | `CheckCompose` (LG, POD) |
| Expression computed two times (no local) | 2 | `PushRepeatCount` (LG, POD) |
| Case `s` before `K` and `b` (source order of the switch) | 4 | `Decompose` x4 |
| Test `CurHeader` first, then two `allocate` calls | 1 | `Packet::Copy` (LG) |
| Branch with the lower log line numbers first | 1 | `ClientPacketBufferHandler::ToPacket` (LG) |
| Test the enum variable (`algorithm == ALGORITHM_DEFAULT`), not `header >> 14` | 1 | `ToPacket` (removes const 0xC000) |
| `Destroy`: test `buffer == nullptr` first; Free is then a tail call | 2 | `RawPacketBufferHandler::Destroy` (SCD), `TextStreamPacketBufferHandler::Destroy` (POD) |
| Log::Write with a literal line in each case, not a shared label with a line variable | 1 | `PacketBuffer::DecomposeText` (POD) |

### B. Patterns that did not work (count = tries)

| Pattern | Count | Function |
| --- | --- | --- |
| `memcpy` variants for the case P tail merge | 2 | `PacketBuffer::Compose` |
| 64-bit form only, without the single exit (97.4) | 1 | `CheckCompose` |
| Free size forms: ternary, local with sizeof, local `Packet*` | 3 | `FragmentPacket::StartRepeat` |
| Pointer forms for the dead `add rax,4` | 3 | `FragmentPacketConcatenater::Add` |
| Single Log::Write exit (score +11, no MATCH) | 1 | `FragmentPacketConcatenater::Add` |
| Read buffer and offset again after `++index` | 2 | `PacketConcatenateBuffer::Decompose(VarData*)` |

## scd-4

SmartCouponDaemon 582 -> 608 MATCH (+26). Other exes +0, MATCH lost 0.

### A. What worked (26 MATCH)

| Change | MATCH |
| --- | ---: |
| DChannelMgr source form | +6 |
| Handlers and handler contexts | +5 |
| DB loaders: do-while fetch loops and int params (int gives the `lea` const) | +6 |
| A count local before Log (loadUnhandledGameEventLog) | +1 |
| else-if chain with one shared `return false` (CouponJob::transit tail-merge) | +1 |
| `switch` on the target type gives the orig block order, default block first (GameEventLogEvent::HandleEvent) | +1 (with the next line) |
| A local copy of the info before PostQueuedCompletionStatus removes the biased pointer const 0x16 (codegen only; main already logged from info, not from ev). | (same +1) |
| NPTransactionRegistry::Register: orig alloc line 131, `if (id != nullptr)`, one `return inserted;` for both paths (the result stays in `bl`, `this` dies, `add rbx,0x10` appears) | +1 |
| A `char` local keeps `mov bl,imm` (retry failReason) | score only |
| Log args test the job pointer like a log macro (`job ? job->_id : 0`, -1 for type and state) (EventNotiJob Initialize, eventNotiReq, eventNotiRes) | +3 (with the 3 rows below) |
| Compare the GUID with the ID128_GUID_ZERO global, not with 0 (EventNotiJob::Initialize) | (same +3) |
| `switch` on err gives the orig sub chain (eventNotiRes) | (same +3) |
| Call GetCommand again for the 270 log, as the orig does (eventNotiRes) | (same +3) |
| Block order follows the if/else order. Invert a test to move a block. This also stops the tail merge of equal Log::Write and WriteStartLog calls (NPServiceChannelCmdDispatcher, GameEventConfig::Load) | +2 |
| `wchar_t x[260] = {0}` gives `x[0]=0` and memset 0x206. `= {}` gives memset 0x208 (GameEventConfig::Load) | (same +2) |
| An inline `wcslen(s) == 0` gives repne scasw and the const -1. `*s == 0` does not (SetupGameEventListFromXml) | score only |
| A loop with a pointer step gives one table ref and the const 0x8. An index loop or a while loop unrolls (SetupGameEventListFromXml) | score only |

### B. What failed (0 MATCH)

| Try | Result |
| --- | --- |
| goto form of the DB fetch loop | no gain |
| SetupGameEventListFromXml: own NextElement call for the 137 block (`continue` form). VS2010 merges the 2 call sites (4 tries) | no gain, 99.7 |
| SendRetryCouponPublicationOk const 0x71 (register allocation) | no gain |
| HelloReq `> 0` test form | no gain |
| RetryCouponPublicationEvent goto fail path | no change; the orig needs the read-after-post bug |
| GameEventByAccountReq goto shared fail path | 93.0 -> 93.9, score only |
| GameEventByAccountReq one Log for lines 262/271 (format and line locals) | 95.2, score only |
| GameEventByAccountReq decompose-fail block at the function end | 95.2, no change |
| NPTransactionRegistry::Register local lock and dict pointers | no change (not needed) |
| SmartCouponDaemon::initialize | blocked: the orig exe has a patched-out cert-decode call |

## pod-4
Card lift-parity-pod-4 (2026-11-19). POD 665 -> 671, SCD 582 -> 584, CG and LG +0. Total +8. Goal 684 not met.

| Pattern | Result | Functions |
| --- | --- | --- |
| A26 reload at each use | +2 POD | `CacheGateSessionHandler::OnConnect`, `OnClose` |
| A27 single-expression `::new` | +1 POD; worse or no change in 2 | `CheckPostCapacityReq`; not `MakePostContext`, `RegisterPostReq` |
| A28 const `ID128_GUID_ZERO` and `memcpy` ctor | +3 POD, +2 SCD | `PostInfo::PostInfo`, `LoadBnsCommonConfig`, `ReloadBnsCommonConfig` |
| `AutoDbTran(dbId, timeoutSec)` ctor | score only | `LoadPostList`, `LoadRetryReadyPostList` 99.1 |
| Named `PingRelayRequest` local before `Alloc` | score only | `PingGenerator::sendPing` 97.0 -> 99.2 |

What worked:
- Compare the order of the loads of globals in the original. A reload at each use or a `memcpy` from a `const` global gives the same loads.
- A named local for a temporary that the original builds on the stack before the call (an unwind `dtor$0` shows it).

What failed:
- The single-expression `::new` is not a general rule. Measure it per function.
- LTCG `this` propagation: POD `checkCacheGateServiceState` is called only with `_instance`. /GL /LTCG folds `this` into the callee (ours loads `_instance`
  inside; orig uses `rcx`). `sendPing` and `checkCacheGateServiceState` stay DIFF. No legitimate source form is known. Add to the stop list.
- Literal register allocation: `setupWorldConfigList` (orig loads the literal more often) and `AgentSessionHandler::OnClose` (ours loads it more often). Not fixed.

## console-4

Card lift-parity-console-4 (PipeConsole, CrashHandler, config). MATCH +11 over main (95ad5be): CG 454 -> 456 (+2), LG 653 -> 658 (+5), SCD 628 -> 630 (+2), POD 692 -> 694 (+2). MATCH lost: 0.

| Function | Exe | Form | MATCH |
| --- | --- | --- | --- |
| `InitSymbol` | all 4 | one unload block per lookup | +4 |
| `WinServiceConsole::UninstallService` | all 4 | one result exit | +4 |
| `PipeConsole::SetRunningInfo` | LG | match-node search, list reference | +1 |
| `IdleStateTable::scan` | LG | `if / else if` chain from the PDB lines | +1 |
| `PipeConsole::addNode` | LG | one form: copy `valueString` (LTCG folds `L""` in CG/SCD/POD) | +1 |

What worked:
- The PDB line maps (`tools/pdbq.py <EXE> lines`) and the PDB data symbols gave every win. Read them first.
- Compare one function in all 4 exes. `addNode` is the same source in all 4 exes. LTCG folds the `L""` argument in CG/SCD/POD.
  Check for constant folding before you add a per-exe form or a `// BUG:` mark.

What failed:
- `wcscmp` `sbb` form, CG `_Def` RTTI neighbour, LG `addNode` inline (see B).
- SCD `DaemonConfig::Dump`: the `LOCALHOST_IP` const pointer gave +1 on the old base. After the merge with main (pod-4) it gives 0 (97.9).
  Measure again after each merge with main. A data-layout win can go away when other cards change globals.
- LG `checkFrozenThread` (91.0): the original inlines `SetInvalidInfo` and `addNode`, with the match-node search. This needs a change in
  `SetInvalidInfo` (stop list). Without `noinline` on `addNode`, LG loses score in 2 other functions.

## ld-0

Card lift-lobbydaemon-0: LobbyDaemon skeleton and stubs. Wave 0 lifts no logic.

| Item | Result |
| --- | --- |
| Module files | 96 server modules + 6 common modules, generated from the PDB publics |
| Stubs (`LIFT_STUB`) | 1400 functions |
| Not done without stub | 521 functions |
| Lifted | 0 |

What worked:
- A generator that reads the PDB publics, the HR index and the module list. It writes one `.h` and one `.cpp` per module,
  and one table of the functions that it cannot declare. Run it once. Fix the rest by hand.
- One marker macro (`LIFT_STUB(rva)`). `grep -rn "LIFT_STUB(" src` finds all stubs. The stub stops the process,
  so it never reports success.
- `tools/pdb2h.py` failed on types that are local to a member function (`__l46::SortByStartTime`).
  The fix prefixes the `sizeof` and `offsetof` asserts with `pdb_local::`. The other exes' `types.h` do not change.
- The exe `VERSIONINFO` resource gives the `.rc` values. Copy them. Do not write a version label from them.

What failed:
- The clang path links static libs and pulls only the referenced objects. The VS2010 path links ALL objects.
  So a latent reference in any lib object breaks only the VS2010 link. Always build the new exe with
  `tools/vs2010/build.sh <EXE>` before the full `tools/parity.sh`. It takes minutes, not 10+.
- VS2010 `stdlib.h` does not declare `abort` noreturn. A stub with a return type gives error C4716 at LTCG code generation.
  The clang gate does not show this. The fix: `__assume(0)` after `::abort()` in `LIFT_STUB`.
- `src/Server/LobbyDaemon/ObjectPool.cpp` is SCD code. It uses `GObjPoolMemAlloc` as `SmartCouponObjPoolMemoryAllocator*`.
  The LD PDB gives `LobbyObjPoolMemAllocator*`. Do not link it into LD. A later wave must give LD its own form.
- `ClientSideDaemonChannel::onAccept`: BloodLib `Channel.cpp` emits the vftable, so every exe needs a body.
  LD has no symbol for it. Without `LinkStubs.cpp`, the LD-only owner is `LobbyDaemon.cpp` (`LIFT_STUB(0)`).
- The gate ran per batch of modules, not per module. The generator writes all modules at once, so a per-module gate adds no data.
- `tools/funcdiff.py` crashed on the first LD run: `is_tls_index` read a register from `mov [mem], <.tls offset>`.
  The fix returns False for a destination that is not a register. Run funcdiff on a new exe alone before `tools/parity.sh`.

## ld-2

Card lift-lobbydaemon-2: CliSession part 1 (RVA 0x329d0 to 0x35eb0, 29 functions).

| Item | Result |
| --- | --- |
| Lifted | 15 |
| Not done | 14 |
| New layouts | `CliSession` (0x8D0), `GameAccount` (0x198), `ServiceLocation` (0x10), `RefCntPoolObj` (0x18). `_gradeService` is opaque 0x40 storage; ld-4 owns the `GradeService` layout. |
| LD MATCH | 49 -> 49 (+0). The other 4 exes: +0, no MATCH lost. |

What worked:
- The HR pseudocode was enough. IDA was not opened.
- `static_assert` on each member offset of `CliSession` found layout errors at compile time, before the VS2010 build.
- The `Free` line number in the pseudocode shows inlined callers. `finalize` frees `_presence` with line 1313, which is the
  `setPresence` line. So `finalize` calls `setPresence(nullptr)`.
- A `this` null test in a log call (`cs != nullptr ? cs->_clikey : 0`) comes from a local `CliSession const* cs = this;`.

What failed:
- LD MATCH gain is 0. The new functions have no live caller (their callers are `LIFT_STUB` bodies), so `/OPT:REF`
  removes them. The built `LobbyDaemon.pdb` has no public for them. funcdiff cannot pair a function that is not in the exe.
  Check this with `grep -a -F '?name@Class' build-vs2010/LobbyDaemon.pdb` before you expect a gain on LD.
- The original global `operator delete(void*)` (0x32b50) is empty (ICF with `Console::Flush`). The source frees with
  `delete p;` and then `Memory::_Manager[2]->Free`. Our global `operator delete` is not empty. The first version had no
  guard (skeptic finding: double free when a subclass appears). Fix: `Presence` and `ServiceLocation` have an empty
  class `static void operator delete(void*) {}`. Use the same fix for each base class that a `delete p; Free(p)` site uses.
- Do not add the layout of a class that another card of the wave owns (skeptic finding: `GradeService.h` belongs to ld-4).
  Use opaque storage of the PDB size (`unsigned long long m[N]`, 8-aligned) and placement new with the declared ctor.
- `tools/vs2010/build.sh` needs the same `LIFT_BUILD_DIR` as the gate. Without it, it stops with "no build/build.ninja".

## ld-4

Card lift-lobbydaemon-4: Character, GradeService and GameTimeSchedule (49 functions).

| Item | Result |
| --- | --- |
| Lifted | 37 (Character 21, GradeService 15, GameTimeSchedule 1) |
| Not done | 12 (`GradeService::ApplyChangedGrade`, 11 `GameTimeQueue` / `GameTimeScheduler` functions) |
| New layouts | `Character` (0xA0), `GradeService`, `Grade`, the 4 grade StsMsg types (`StsMsgGrade.h`). `CliSession::_gradeService` is a real member again. |
| LD MATCH | 49 -> 49 (+0). The other 4 exes: +0, no MATCH lost, no MATCH name gone. |

What worked:
- The HR pseudocode and the PDB types were enough. IDA was not opened.
- LTCG constant propagation can remove an argument at the call site. Read the callee pseudocode: it shows the constant
  (`TryCharacterCreation` binds `char = 1` at 0xa39b0). Pass the constant and mark it `// LIFT:` + ❓.
- `_gradeList.insert(std::pair<int, Grade*>(k, g))` gives the original STL pair `_Linsert` / `_Buynode`. Restore STL
  calls this way; do not write the tree code by hand.
- After ld-4 owns the `GradeService` layout, the ld-2 opaque storage and placement new go away. The ctor init lists
  construct the member directly.

What failed:
- VS2010 refuses an opaque enum declaration (`enum ECommand : int;` gives C2059). The clang gate accepts it, so the gate
  did not find the error. Only the VS2010 build in `tools/parity.sh` found it. Define the full PDB enum. Run the VS2010
  build before the handoff, not only the gate.
- LD MATCH gain is 0 again. The callers of the new functions are still `LIFT_STUB` bodies, so `/OPT:REF` removes them
  (same as ld-2). The LD gain comes only when the caller cards land.
- GameTimeSchedule is blocked: 11 of 12 functions need the `RefCntList` layout, which ld-3 owns and which is not on
  main. Do not add it here. Put cards that share a base layout in a sequence, not in the same wave.
