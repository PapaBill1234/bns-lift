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

Cleaned again in lift-parity-review-4 (2026-11-26). The round-4 card sections (crypto-4, net-4, packet-4, scd-4, pod-4, console-4) are merged into A, B and D.
Mapping review 3 -> review 4: A1 to A29 keep their numbers (no renumbering; the order changed little). New: A30 (packet buffer forms, packet-4),
A31 (log-macro argument form, scd-4), A32 (SCD daemon forms, scd-4). Counts changed: A2 97 -> about 111, A11 26 -> 32, A17 19 -> 23, A20 8 -> 12, A26 2 -> 6.
A25 (38) and A30 (18) would sort to places 8 and 15. The numbers stay; the next review with a large order change sorts them.
The `ld-*` sections at the end belong to the LobbyDaemon system. This review does not merge them.

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

### A2. Block order and statement order follow the original (r2 A5; P3, P7, P10, P20, P25, P33, P39; order-3, consts-3, handlers-3, manual; net-4, scd-4, packet-4): about 111
- Round 4: block order of the cold error tails from the log line numbers (packet-4: `Compose`, `Decompose`, `CheckCompose`; 10).
  Branch with the lower log line numbers first (LG `ClientPacketBufferHandler::ToPacket`; 1). Invert an `if` test to move a block; this also stops the tail merge
  of equal `Log::Write` calls (SCD `NPServiceChannelCmdDispatcher`, `GameEventConfig::Load`; 2). Member reads and `memset` in source order (LG `Session::Connect`; 1).
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

### A11. Loop forms that VS2010 compiles as the original (r2 A13; P16, P26, P43; consts-3; scd-4): 32
- scd-4: DB fetch loops as `do { } while (Fetch)` and `int` params (the `int` gives the `lea` const). SCD `SmartCouponDB` loaders (6).
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

### A17. Error blocks and cleanup tails as in the original (r2 A14; P14, P36, P13 s1; inline-3; net-4): 23
- net-4: `Session::HandleFailedEvent` x4: `Close` and `Leave` in each case, not one shared tail (4).
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

### A20. `#pragma inline_depth(0)` on one caller (manual; net-4): 12
- net-4: `SessionSendBuffer::clearPacketBufferList` x4: `inline_depth(0)` and the `removeReferenceCount` body written out by hand (4).
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
- Rule (crypto-4): `noinline` on one helper changes the inline choice in all its callers. Measure all callers after each change.

### A26. Read globals and fields again at each use (pod-4, net-4): 6
- net-4: `Network::Clear` x4: keep `Port*` in a local only for the null test; read `_port[i]` again for each use (4).
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

### A30. Packet buffer source forms (packet-4): 18
- Pointer loop over the format with the index check in the loop (`PacketBuffer::Compose` x4, `Decompose` x4).
- Signed `short` for sizes and headers; the store then uses 0xFFFF8000 (`Compose` x4, `TextStreamPacketBufferHandler::ToBuffer`).
- 64-bit pointer form for the destination (`Decompose` x4). Case `s` before `K` and `b` (source order of the switch, `Decompose` x4).
- Single exit with a size variable (`CheckCompose` LG, POD). Expression computed two times, no local (`PushRepeatCount` LG, POD).
- Test `CurHeader` first, then two `allocate` calls (LG `Packet::Copy`). Test the enum variable, not `header >> 14` (LG `ToPacket`, removes const 0xC000).
- `Destroy`: test `buffer == nullptr` first; `Free` is then a tail call (SCD `RawPacketBufferHandler::Destroy`, POD `TextStreamPacketBufferHandler::Destroy`).
- One `Log::Write` with a literal line in each case, not a shared label with a line variable (POD `PacketBuffer::DecomposeText`).
- One function can need 3 of these forms together. Count in the handoff: 18 MATCH (CG 2, LG 6, SCD 3, POD 7).

### A31. Log-macro argument form (scd-4): 3
- The original log calls test the pointer like a log macro: `job ? job->_id : 0`, and -1 for type and state (SCD `EventNotiJob::Initialize`, `eventNotiReq`, `eventNotiRes`).
- With it: compare a GUID with the `ID128_GUID_ZERO` global, not with 0 (A28). `switch` on the error gives the original `sub` chain. Call a getter again for each log, as the original does.

### A32. SCD daemon source forms (scd-4): 13
- `DChannelMgr` source form (+6) and the handler contexts (+5). See the scd-4 handoff, commits f4ba49f and 93296be.
- `NPTransactionRegistry::Register`: allocation on the PDB line, `if (id != nullptr)`, one `return inserted;` for both paths (+1).
- `GameEventLogEvent::HandleEvent`: `switch` on the target type, default block first; copy `info` to a local before `PostQueuedCompletionStatus` (+1).
- Small forms with score only: a `char` local keeps `mov bl,imm`; `wchar_t x[260] = {0}` gives `x[0]=0` and `memset` 0x206 (`= {}` gives 0x208);
  inline `wcslen(s) == 0` gives `repne scasw`; a pointer-step loop gives one table ref and const 0x8.

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

- net-4 (do not try again without a new idea):
  - A local non-static `const` array for the max-session table: the compiler copies it to the stack. Keep it `static`.
  - `Port` ctor with body assignments: the store order is correct, but no MATCH (`OpenPort` refs differ: the original table has no PDB name).
- packet-4 (do not try again without a new idea):
  - `PacketBuffer::Compose` case P: 2 more `memcpy` forms for the tail merge. `CheckCompose`: 64-bit form without the single exit (97.4).
  - LG `FragmentPacket::StartRepeat`: free size as ternary, as a local with `sizeof`, a local `Packet*` (3 tries). Register allocation.
  - LG/POD `FragmentPacketConcatenater::Add`: 3 pointer forms for the dead `add rax,4`; a single `Log::Write` exit (98.4, no MATCH).
  - LG `PacketConcatenateBuffer::Decompose(VarData*)`: read buffer and offset again after `++index` (2 tries). VS2010 does CSE on the pointer.
- scd-4 (do not try again without a new idea):
  - `goto` form of the DB fetch loop. `SetupGameEventListFromXml` own `NextElement` call for the 137 block (4 tries, 99.7; VS2010 merges the 2 sites).
  - `SendRetryCouponPublicationOk` const 0x71 (register allocation). `HelloReq` `> 0` test. `RetryCouponPublicationEvent` `goto` fail path.
  - `HandleSmartCoupon_GameEventByAccountReq`: `goto` shared fail path (93.9), one `Log` for lines 262/271 (95.2), decompose-fail block at the end (95.2).
  - `SmartCouponDaemon::initialize`: blocked. The original exe has a patched-out cert-decode call (NOPs at 0x151D4, 0x15256).

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
Review 4 (2026-11-26): solved in round 4 and removed from the lists below in effect: `clearPacketBufferList`, `Network::Clear`, `Session::SendV`, SCD `Network::OpenPort`,
`InitSymbol`, `UninstallService`, `PacketBuffer::Compose`/`Decompose`, `OaepEncoder::*`, `BigInteger::Mul`/`mul`/`sub`/`Sqr`/`expMod`, `RsaPublic::*`, SCD DB loaders,
POD `PostInfo::PostInfo`. The current DIFF list with causes is in `review-4.md` section 5. Round-4 additions to the stop list:
POD `PingGenerator::sendPing` and `checkCacheGateServiceState` (LTCG `this` propagation), `PipeConsole::processCommand` and `PipeCommandProcess::processCommand`
(`wcscmp` `sbb` form), `Rsa::decrypt` (VS2010 turns the zero-fill loop into `memset`), `FragmentPacket::StartRepeat`, `FragmentPacketConcatenater::Add`,
`PacketConcatenateBuffer::Decompose` (register allocation and CSE), SCD `SmartCouponDaemon::initialize` (patched original), POD `PostOfficeDB::LoadPostList`/`LoadRetryReadyPostList` (99.1, loop header).
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

## ld-1

Card lift-lobbydaemon-1: common modules and missing Part A functions. 39 lifted, 3 covered by an existing lift, 4 Not done.
LD MATCH 49 -> 49. CG, LG, SCD, POD: +0, no MATCH lost.

What worked:
- Grep `src/` for the PDB name and the RVA before each lift. 3 card functions already had a body or are compiler-generated
  (`BigInteger` ctor/dtor inline in `BigInteger.h`, `EventObject::~EventObject`). Add the LD RVA to the comment. Do not lift again.
- Per-exe path literals with `#if defined(LIFT_EXE_LD)` in `SharedChannel.cpp` (A6). SCD keeps its literals.
- An inlined helper is a check of the source form: `Network::GetAddress` 0xe4900 has the `String::UnicodeToMultibyte`
  body with count 32.
- STL functions of a module come from the STL headers with the PDB allocator (`BannedWordFilterAllocator`). Do not write them by hand.

What failed:
- LD gain is 0. The LD callers are still `LIFT_STUB` bodies, and LTCG drops code with no caller. A common-module card
  on LD gives MATCH only after the callers are lifted. Plan LD cards from the callers down, or accept a 0 gain.
- A new worktree has no `vendor/zstd/src` (it is in `.gitignore`). The VS2010 link then fails with `ZSTD_*` unresolved
  in all 5 exes. Fix: copy `vendor/zstd/src` (bb6eaf64) from the main checkout, then run `cmake <build dir>` again,
  because CMake adds `lift_zstd` only at configure time.
- The LD `ContentsRuleConfig` is a different class from the LobbyGate one (other members, literals and `_Def` counts).
  The card pattern file is wrong for LD. A later wave must add an LD owner file.
- The Wine headers do not declare `_mkgmtime64`. Declare the msvcr100 export in the source (same as `_vswprintf_c_l` in `Db.cpp`).

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

## ld-3

Card lift-lobbydaemon-3: CliSessionTable part 1 and containers (37 functions).

| Item | Result |
| --- | --- |
| Lifted | 37 (CliSessionTable 21, BoundedList 4, RefCntList 4, WaitQueue 8) |
| Not done | 0 |
| New layouts | `CliSessionTable` (0x80), `GateNode` (0x38) |
| LD MATCH | 49 -> 49 (+0). The other 4 exes: +0, no MATCH lost. |

What worked:
- The HR pseudocode was enough for all bodies except the account hash. Check the hash in the disasm of 0x3e670: the
  source adds the 4 dwords of the `id128` as 64-bit values.
- The `Free` line numbers in the dtor give the source order of the 10 delete blocks.
- A16 placement array new from `CouponJob.cpp` works for arrays of `std::map`, `CriticalSection` and `RefCntList`.
- The `std::map::~map` at 0x3d8f0 needs no code. The typedef instantiates it.

What failed:
- LD MATCH gain is 0 again (same cause as ld-2). `/OPT:REF` removes each function that only `LIFT_STUB` bodies call.
  Check with `grep -a -c -F '?Name@Class' build-vs2010/LobbyDaemon.pdb`.
- LTCG changes the signature of a small function in the binary (0x3ec40 gets the hash in place of `wid`). Lift the
  PDB source form and add a `// LIFT:` note. Do not copy the LTCG form.
- The Write tool refuses a file that was read only through Bash. Use a Bash heredoc in that case.

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

## ld-8

- Use the PDB line map to check the order of the log, list walk, vector insert, and reference increment in `CliSessionTable::Select_index_gate` (1 MATCH).
- Use the existing VS2010 map and vector types with the PDB allocator (23 card functions). Do not write the STL internals by hand. Funcdiff skips `std::` functions.
- Restore the PDB base and member offsets before you lift the constructor (1 MATCH). Keep the reference release in the source destructor. The original emits it in the deleting destructor.
- Retain the two public symbols while their callers are stubs (2 retained symbols). The base destructor also matched (1 additional MATCH). LobbyDaemon gained 3 MATCH in total.
- No source variant failed. Both new card bodies matched on the first comparison.
- Do not infer a layout from a stub. The token checks need the LobbyDaemon and LobbyConfig layouts. The expiration path needs the job layouts. The desk needs its own PDB layout (9 functions not done).

## ld-10

- Follow the original flow. Do not add a null check that the original does not have, even if the score does not change. `Start` (`0x5c300`), `GradeChanged` (`0x5ca20`) and `Register` (`0x60be0`) had added checks. The guard removal was blocked, so these three functions are stubs again.
- When a lifted caller becomes a stub, LTCG can remove its callees. `GradeService::GetGrade` and the `std::vector<Section<__int64>>` ctor (`0x9f540`) went out of the build with `Start`. ❓ `RefCntList::Pushback` was probably inlined into its last caller `Tick`. Use `/INCLUDE` with a `// LIFT:` reason only for bodies in the card's own files.
- The VS2010 STL emits the `std::vector<Section<__int64>,StlAllocator<Section<__int64>,2> >` functions through the normal container calls. Check the decorated names in the built PDB. The parity count excludes these STL functions.

## ld-7

| Function | RVA | Trial | Score before → after | Result |
| --- | --- | --- | ---: | --- |
| `CliSession::FetchCharacterInfoList` | `0x379b0` | A20: disable inlining for this caller. Write the original inline lock and `StartRepeat` code in the body. | 98.0 → 93.3 | Reverted. The calls match. The constants do not. |
| `CliSession::FetchCharacterInfo` | `0x37af0` | A8: compare the ID with the PDB global `ID128_ID_ZERO` instead of literal zero. | 90.3 → 97.0 | Kept. The references match. One extra constant remains. |
| `CliSession::FetchServiceEntryList` | `0x37c70` | A20: disable inlining for this caller. Write the original inline lock and `StartRepeat` code in the body. | 98.0 → 97.0 | Reverted. The calls match. The constants do not. |

The two A20 trials made `FragmentPacket::IncRepeatCount` pair and match. Neither caller improved. Do not apply A20 to these two callers without a new source form.

| Function | RVA | Repair trial | Score before → after | Result |
| --- | --- | --- | ---: | --- |
| `CliSession::BindCharacterSlot` | `0x37eb0` | A8: use `ID128_ID_ZERO` for both slot ID tests. | 64.3 → 73.3 | Kept. The references and constants improve. |
| `CliSession::FetchCharacterInfoList` | `0x379b0` | A2: test states in the original order. | 98.0 → 98.0 | Reverted. The score did not increase. |

Resumed run (codegen pass on the DIFF functions above 85 %):

| Function | RVA | Trial | Score before → after | Result |
| --- | --- | --- | ---: | --- |
| `CliSession::setContentBans` | `0x366e0` | A20: `#pragma inline_depth(0)` on the caller, so `push_back` stays out of line. | 85.2 → 91.7 | Reverted. The calls pair, but `clear`, `begin`, `end` and the iterator steps also become calls. The original inlines them. The 0x18 step constant goes away. The code is further from the original. |
| `CliSession::NotifyChangedGradeLevel` | `0x36170` | None. The disassembly is the same as the original. | 88.9 | Tool noise. Funcdiff drops an immediate below the image size as an RVA. The original image is larger, so `0x40000` is dropped only on the original side. |
| `CliSession::NotifyChangedGrade` | `0x360a0` | None. | 85.7 | LTCG inlines the `GradeService::ApplyChangedGrade` stub. Wait for the callee card. |
| `CliSession::UpdateCharacterData` | `0x381c0` | None. | 55.0 | LTCG inlines the `getCharacter` stub (`0x35cf0`, noreturn). The rest of the body is dead. Wait for part 1. |

- Do not use A20 when the original inlines other STL calls in the same function. A20 removes all inlining in the caller.
- A small constant can differ only because our image is smaller than the original. Check the disassembly before a source trial.


## ld-11

| Item | Result |
| --- | --- |
| Lifted | 33 (LobbyService part 2: 23, LobbyLocale: 10) |
| Not done | 0 |
| LD MATCH | 82 -> 91 (+9). 8 are card functions. The other 4 exes: +0, no MATCH lost, no MATCH name gone. |

What worked:
- Write a digit test in the same form as the original. The original keeps the constants `0x30` and `0x39`, so write
  `(c < L'0' || c > L'9')`. The form `static_cast<unsigned short>(c - L'0') > 9` changes the consts signal.
  `IsSentenceCase` went from 94.1 to 98.0. `IsMonolingualString` went from 88.9 to 96.3.
- Keep the test order of the original: the digit test first, then the space test.

What failed:
- An `unsigned int` index in place of an `unsigned short` index for a range-checked table read gave no change
  (`GetLanguageTypeOfChar`, 99.4 before and after).
- The original LobbyLocale tables are one byte table (`byte_140161BD0`) with fixed offsets. Separate tables and a bit
  table for kanji leave a consts gap near 98. Do not change it in a slice card. It is a large data change.
- The service functions without the client session key in the log calls stay near 60. This is a known cost.
- A caller of a `LIFT_STUB` cannot score above 0. /LTCG sees that the stub does not return and removes the code
  after the call. `/OPT:ICF` then folds callers with the same prefix into one body (`0x6f000`, `0x6fc10`, `0x70900`
  share one address). `__declspec(noinline)` on the stub does not help: the call stays, but the rest is still removed.
  Fix: lift the callee first (`0x6c330`). Check folding with `llvm-pdbutil dump --publics` (same `addr`).

Verify round (ld-11):

| Function | Change | Before | After | Kept |
| --- | --- | ---: | ---: | --- |
| `GetStringLengthWithCellCombination` (0x584a0) | Original shape from the PDB line map (lines 635-669): `for` loop with `i += count`, `cell` at function scope, `str + i` null tests in the Thai and Vietnamese branches, one `count <= 0` test after both branches. A safety null test on `str` stays before the loop. | 75.0 | 81.5 | yes |
| `GetStringLengthWithCellCombination` (0x584a0) | Read `str[i]` in each range test in place of one local `c` | 81.5 | 81.5 | no (reverted) |
| 19 null-owner and compose-fail log blocks (0x6edf0 to 0x71350) | `Xxx const* s = this;` and a `s != nullptr ? s->_db.field : 0` test for each log argument (ld-2 form) | 40.7-63.7 | 40.7-63.7 | yes (source form of the original; no score change) |

- The remaining consts gap of 0x584a0 is the Thai range test. The original compares with `0xe01`, `0xe3a`, `0xe3f` and `0xe5b`
  in four short-circuit tests. Our build uses a subtract-and-compare form (`0x1c`). Two source forms gave the same code.
- A21 and A10 for `GetStringLengthWithCellCombination` (0x584a0): declare the PDB `LobbyLocale::VietCell` (ctor, dtor, `Reset`), the `ThaiCell` ctor, dtor and `Reset`, and a `static __forceinline GetNextVietCell` (inlined at 0x58562). Score 81.5 before and after. Kept as the source form of the PDB.
- The `this` null test in the service log blocks does not change the score. The missing client session key arguments set the score.

## ld-9

- Keep `GameWorld::EnterUser` (`0x4cf40`) with its original PDB public name until the caller is lifted. The function pairs at 88.0. It was unpaired before. The body did not change.
- A2/A8, `GameWorld::Setup` (`0x4c880`): explicit flag branches and ordered reads for log arguments lowered the score from 96.3 to 91.7. Reverted.
- A2/A8, `GameWorld::FetchWorldInfo` (`0x4cc40`): a direct capacity test, a cluster DB snapshot, and ordered crowdness tests lowered the score from 97.0 to 90.9. Reverted.
- A8, `GameWorldCluster::addGameWorld` (`0x4e4f0`): a separate local pointer for `push_back` gave the same score, 94.4. Reverted.
- A16/A17, `GameWorldReporter::WriteReport` (`0x4fa80`): `T* next = mem != nullptr ? ::new (mem) T : nullptr; if (next == nullptr) return false;` alone kept 90.0. Both error blocks first (registry test inverted, `Write` failure before the success path) gave 100.0 MATCH. The allocation guard stays. Kept.
- A8/A17, `GameWorld::EnterUser` (`0x4cf40`): error blocks first, one `if`/`else` with two separate `TLobbyError` stores, and `_db.characterCreationLimited` read after `Log::Write` raised the score from 88.0 to 96.7. Kept. The rest is the `enterUser` stub body.
- The `/INCLUDE` for `GameWorldReporter::HandleEvent` (`0x4fa30`) is not needed. The kept destructor stores the vftable. The function stays MATCH without it. Removed.
- `SystemPerfMonitor::Start` (`0x59e30`) and `HandleEvent` (`0x59ee0`) go back to stubs. The original uses `LobbyDaemon::_instance->GlobalTimerQueue`, not `Daemon::Instance`. They return when the `LobbyDaemon` layout exists (ld-15, ld-20).
- A stub body is identical code for every stub, so ICF folds the stubs. funcdiff pairs the folded body with one name. Moving a function to a stub can drop another stub from the paired list (`wmain`, DIFF 33.3). This is not a MATCH loss.
- A8, `SystemPerfMonitor::Initialize` (`0x59d60`): an inline `CounterSet::create` with an extra handle test and `return _instance != nullptr` scored MATCH 100.0 but was not the same code (extra `test rcx,rcx`, `setne al`, `test al,al`). funcdiff does not see these. Fix: no handle test, and `create` returns the instance pointer, so the caller emits `mov [rbx+48h],rax; test rax,rax; je` as the original does. The bytes now agree with the original. Check disassembly of a MATCH 100 function that has an inline `bool` helper.
- Review 4, `CounterSet::create` (`0x59d60`): the PDB return type is `bool`. With `bool` and no handle test (`return _instance != nullptr;`), the score stays MATCH 100.0, but VS2010 emits `setne al; test al,al` after `test rax,rax`. The original has only `test rax,rax; je`. The PDB type is kept. The difference is recorded in the handoff.

## ld-12

Card lift-lobbydaemon-12: AuctionEscrow, LobbyStats, LobbyTick, TencentUIC, LobbyMessage (26 functions).

| Item | Result |
| --- | --- |
| Lifted | 23 |
| Not done | 3 (`CliSessionMileageInterimDepositMessage::Dispatch`, `LobbyStats::update`, `sprintf_s<1024>`) |
| LD MATCH | 130 -> 155 over main ef056b3 (+25: 16 card functions, 9 shared functions). The other 4 exes: +0, no MATCH lost. |

What worked (count = functions made MATCH):
- The `/INCLUDE` dead-strip rule gives the first real LD gain. Leaf modules with no layout dependency (LobbyTick, TencentUIC,
  LobbyMessage) reach MATCH at once, and they pull shared code (`TimerQueue::Add`, `RefCntList::Pushback`) into the exe: +9 shared.
- A17 error block first: `LobbyTick::Add` 58.3 -> 100, `LobbyTick::Remove` 80.6 -> 100, `TencentUIC::Initialize` 95.2 -> 100 (3).
  The HR pseudocode shows `if (p != nullptr) { ... } else { log }`, but the original layout has the log block first.
  Read the disassembly order, not the HR branch order.
- A4 `__declspec(noinline)` on `LobbyTickEvent::~LobbyTickEvent`: the scalar deleting destructor calls it out of line (1).
  Without it, VS2010 inlines the body into `_G` and funcdiff has no pair.

What failed or is blocked (tries):
- `LobbyStats::Initialize` 93.3 and both AuctionEscrow functions (94.9, 82.1): LTCG folds caller constants (`L"lobby"`, `L"stats"`,
  `bufsizeInWords = 1025`) into the original body. A function that only `/INCLUDE` keeps has no caller, so no fold. 0 tries; retry
  after the callers (LobbyDaemon::initialize, the auction handlers) are lifted.
- `LobbyStats::HandleEvent` 33.3: its callee `update` is a `LIFT_STUB`, so the abort is inlined. Not a source-form problem.
- funcdiff skips names that start with `__` (`SKIP_NAME`). `__printXml` is in the built PDB but has no score.
- MSVC puts overloaded virtual functions in the vtable in reverse declaration order. Take the slot order from the PDB method
  list, then declare the overloads in reverse. Check with `clang-cl -Xclang -fdump-vtable-layouts -Xclang -emit-llvm-only`.
  Funcdiff records indirect calls without a displacement, so a wrong slot still scores MATCH (`LobbyMessage::Dispatch` x3).
- Retry after ld-10 landed: `CliSessionGradeChangedMessage::Dispatch` lifts at 83.3. The only DIFF is the callee
  `MembershipMileage::GradeChanged`, still a `LIFT_STUB` (inlined abort). No source form to try.
- Do not edit a source file of another card, even for a one-line stub (`CliSession.cpp` `0x32b60`). Write it in the handoff.

## ld-15

Card lift-lobbydaemon-15: LobbyDaemon part 1 (33 functions, 30 lifted, 3 Not done: `~LobbyDaemon`, `initLog`, `initialize`).

| Item | Result |
| --- | --- |
| LD MATCH | 301 -> 436 (+135) over main 9ca5a30, measured after the merge (25 of the 30 card functions MATCH). The other 4 exes: +0, no MATCH lost. |

What worked:
- The `/INCLUDE` pragma finds wrong signatures. A name that the original PDB has and the lift does not define is an undefined symbol at link time.
  3 first-lift signatures were wrong: `static` for a member (`CoolDown::Start`), public for private (`restoreInvalid`), pointer for reference
  (`GetNextResetTimeUTC`). Copy the decorated name first. Fix the declaration until it links.
- A19 for a constant string copy: `wcscpy(delimiter, L";")` in HR is two stores in the original. Write `d[0] = L';'; d[1] = 0;`.
  `ServiceItems::Add` 94.1 -> 98.7 (refs and consts now equal).
- A17 variant: HR shows `v5 = line; ... Log::Write(v5)` after the branches. The original source has one `Log::Write` per branch (the lines 1140, 1148, 1153 differ).
  Write one call per branch. `FailedEventObjectHandler` 91.7 -> 93.3. The call order (`GetLastError` before `EventId`) is not done yet.

Review trials (after the merge of main 9ca5a30):
- A2, error block first (`CoolDown::Start`): write `if (!AddTimer) { log 325; _run = false; return false; } log 330; return true;`. 95.0 -> 100.0 (calls and refs agree).
- A2 and A8 (`CoolDown::HandleEvent`): put the cooldown-end block first (`if (!((size > 0 || elapsed < halfEnd) && elapsed < _end))`), `size <= 0` log (line 270) first
  inside it, the AddTimer failure (line 297) in the `else`. Add `remainCsList.clear()` after log 286: the pseudocode `if (Myfirst != i) memmove(Myfirst, i, 0)` is `clear()`.
  The source line numbers (270, 281, 286, 297) give the block order. 94.3 -> 100.0.
- A8, a false BUG (`PrintDependency`): the original passes a second argument 0 (`xor r8d, r8d`). The pseudocode hides it. Check the register setup in the disassembly before a `// BUG:`
  mark. `wprintf(L"... %d.%d\n", 65, 0)`. 96.7 -> 100.0.
- `GetNextResetTimeUTC` 66.7, 3 forms, no gain: (1) read `scheduleTime.startTimeUTC` at each use in the else branch, (2) the `startTimeUTC > conditionTimeUTC` block first,
  (3) `targetType == 0` inline first. Form 3 gives the original size (193) and layout. The only DIFF is `add rax, -0x15180` (ours) against `sub rax, 0x15180` (original).
  VS2010 folds `x - 86400` to an add of a negative constant. Open: try a named day-length constant or an unsigned type.

What failed:
- A8/A2 plus a source form: `FailedEventObjectHandler` 93.3 -> 100.0. Locals for `GetLastError()` and `EventId()` in the original order did not change the call order.
  A `switch (EventId())` with `case 3`, `case 5` and `default` and one `Log::Write` per case gave the original layout (MATCH).
- A variadic helper is never inlined by VS2010, even with `__forceinline`. It stays a PDB function and an extra call. Lift the real variadic member
  instead (`Packet::Compose(PacketComposer*, int, ...)`, 0xde140, in `Packet.cpp`). `TimeBasedPlaySeasonSchedule::Compose` 81.5 -> 89.9. Then pointer loops: 90.0.
  `Compose` loop with `unsigned short == 0xFFFF` instead of `== -1`: no change.
- `Daemon::Instance->GlobalTimerQueue->Add(...)` does not compile. `TimerQueue::Add` is protected. LTCG inlines `Daemon::AddTimer` in the original.
  Funcdiff already expands `AddTimer` to `TimerQueue::Add`. The extra call in `CoolDown::Start` came from the block order, not from the expansion (see the review trials above). Keep `Daemon::AddTimer`.
- `restoreInvalid` refs 80: the loop end pointer is the address of the next global. The original has `CONFIG_FILENAME`. Ours has `TextConsole::COLOR_TABLE`.
  This depends on the data order, not on the source form.

Other facts:
- A worktree without `vendor/zstd/src` fails the VS2010 link with 3 `ZSTD_*` errors in all 5 exes. Copy the directory from another worktree.
- A13 for `std::sort`: the clang shim `include/vs2010/algorithm` had no `std::sort`. The VS2010 parity build uses the real headers and does not need it.
  Write `std::sort(v.begin(), v.end())` with no empty guard. `ServiceItems::Add` 98.7 -> 100.0 (MATCH). A heap sort and a guard are a wrong form.
  The 6 instances (`_Sort`, `_Unguarded_partition`, `_Median`, `_Make_heap`, `_Sort_heap`, `_Insertion_sort1`) are 100.0 when funcdiff does not skip `std::`.
  Check STL instances this way: copy `tools/funcdiff.py` to a temp file and remove `std::` from `SKIP_NAME`. Do not commit the copy.
- Use the PDB inline member (`RepeatPacketComposer::IncRepeatCount`, in the class header) instead of an anonymous-namespace helper. Same code, PDB name.
- A static counter has the PDB type `unsigned __int64`. Cast to `volatile __int64*` at the `_Interlocked*64` calls. No code change.


## ld-14

Card lift-lobbydaemon-14: LobbyDB part 1 (14 functions: 11 lifted, 3 Not done). Codegen trials: 6 (6 kept).

| Function | RVA | Trial | Score before → after | Result |
| --- | --- | --- | ---: | --- |
| `LobbyDB::UpdateLastLogout` | `0xa1580` | A8: compare the `id128` argument with the PDB global `ID128_ID_ZERO` (`id[0]` and `id[1]`), not with literal zero. | 97.4 → 100 | Kept. |
| `LobbyDB::TryCharacterCreation` | `0xa39b0` | A8: same form for both ids (`gameAccountId`, `slotid`). | 97.4 → 100 | Kept. |
| `LobbyDB::FinishCharacterCreation` | `0xa3da0` | A17: write `if (dbrtn == 0) return true; return false;` after `Execute`. `return dbrtn == 0;` lets VS2010 merge the two `Db::ReleaseTransaction` blocks. The original has two. | 99.1 → 100 | Kept. |
| `LobbyDB::UpdateGameAccountTimeBasedPlayInfo` | `0xa0a40` | A8: same form (repair round 2). | 97.4 → 100 | Kept. |
| `LobbyDB::LoadGameAccount` | `0x9fe00` | A8: same form (repair round 2). | 78.9 → 80.5 | Kept (score up). |
| `LobbyDB::LoadCharacterList` | `0xa17f0` | A8: same form (repair round 2). | 78.1 → 79.0 | Kept (score up). |

New pattern (A8, id128 zero test): every LobbyDB function that tests an `id128` argument for zero uses `ID128_ID_ZERO` (the refs show `<data>` and `ID128_ID_ZERO`). Disassembly of `0x9fe00` (`LoadGameAccount`) loads both qwords from `0x14012d870` and `0x14012d878`. That is `ID128_ID_ZERO` (PE data, 0 and 0), not a literal zero. All 5 functions (6 call sites) now use it. A first lift wrote a helper with a false comment ("not the ID128_GUID_ZERO symbol"). Check the comment against the disassembly, not against the idea of the source.
The limit of 3 trials is per function, not per card.

What did not reach MATCH (below 85 %, not tried beyond A8):
- `LoadCharacterList` 79.0, `LoadGameAccount` 80.5, `LoadGameWorld` 77.5, `LoadGameWorldCluster` 84.2.
- `LoadGameAccount` (`0x9fe00`) has one shared `statmentErrorLog` block for all bind-column errors. Try a `static __forceinline` BindCol helper (A10) with one shared error tail (A17) on this function.
- `LoadCharacterList` (`0xa17f0`), `LoadGameWorldCluster` (`0xa24c0`) and `LoadGameWorld` (`0xa2dd0`) have one `statmentErrorLog` call for each `SQLBindCol` failure (`LobbyDB.c`). Do not use the shared tail on them. The `DB_BIND_COL_NI` form (one call per column) is the right shape. Look for the difference in the refs and the call order first.
- Repair 3, `LoadGameWorldCluster`: columns 6 and 7 used `SQL_C_SLONG` (-16). The original passes `SQL_C_LONG` (4) (`LobbyDB.c`, `SQLBindCol` and `statmentErrorLog`). Fixed. The score stays 84.2. The constant is correct, but it is not the cause of the gap. Check all `SQLBindCol` type constants against the pseudocode first (a script over all 39 calls found only these 2).
- Binding the PDB parameters directly (`&wid`, `&pcid`, `&job`, `&level`) instead of a local copy keeps `TryCharacterCreation`, `FinishCharacterCreation` and `CancelCharacterCreation` at 100.0. Do not add a copy of a by-value parameter for `BindParam`.
- Dead-strip: 7 of the 10 `LobbyDB` card functions have only stub callers (`CliSession`, `GameWorldRegistry`, `CreateCharacterJob::init`). The other 3 (`TryCharacterCreation`, `FinishCharacterCreation`, `CancelCharacterCreation`) have lifted callers `Character::TryCreation`, `FinishCreation`, `CancelCreation`, but those are dead-stripped because `CreateCharacterJob::tryCreateCharacter`, `createCharacterOk` and `createCharacterFail` are still stubs. All 10 need `/INCLUDE`. Name the stub caller in the pragma comment, not the lifted one. Without it, 0 card functions pair. With it, `~AutoDbTran` is reached and the 15 shared `Db::*` functions pair and match for the first time.

## ld-13

Card lift-lobbydaemon-13: CliSession part 3, CliSessionManager (56 functions).

| Item | Result |
| --- | --- |
| Lifted | 25 |
| Not done | 31 (most need the `LobbyDaemon`, `LobbyGateChannel` or LobbyJob layouts; `CliSession::_pool` needs the LD ObjectPool module) |
| LD MATCH | 195 -> 218 over main 75f0769 (+23: 19 card functions, 4 shared functions). The other 4 exes: +0, no MATCH lost. |

- The clang gate links static libs. An object with an unresolved symbol passes the gate when no other object pulls it. The VS2010
  parity build links each object and fails. Example: a `CliSession::_pool` definition needs `ObjPool::ObjPool`, but `ObjectPool.cpp`
  is only in `lift_smartcoupondaemon`. Run parity before you write "links" in a handoff.
- Virtual functions of a class with no lifted ctor have no reference. `/OPT:REF` removes them. Keep them with `/INCLUDE` (21 pragmas
  in `CliSession.cpp`). Take the decorated names from `llvm-pdbutil dump -publics` on the original PDB.
- A small `GetKind` can fold (ICF) with a function of another module. funcdiff then scores it under the other name
  (`LeaveGameWorldToken::GetKind`, `Aes128::GetType`). A `return 0` body folds with many names and gets no new score.
- funcdiff `SKIP_NAME` also skips `std::` and backtick names. STL instances and `dynamic initializer` / `atexit` functions have no score.
- An inlined loop over a small enum (`Authority::Merge`, `for i < OP_MAX`) gives the same code as separate `|=` stores (A19, no change).
- `CliSession::setRole` (`0x39f70`, 93.3, one extra `0x4`): A8 (`int const role = roles[i]`) gave 88.9, with `int` or `long long` index. A11 alone
  worked: `for (long long i = 0; i < roleCount; ++i)` with `roles[i]` read in place gives 100.0 (MATCH). The original steps a 64-bit index,
  not a pointer. Try the index type before you add a local.
- An STL instance (`std::vector<...>::~vector`) is not in the PDB when no lifted caller makes it. Do not list it as Lifted (skeptic check 2b).
- The 4 `CliSessionTable` index functions paired for the first time when their presence callers were lifted (shared gain).

## ld-17

| Item | Fact |
| --- | --- |
| Dead-strip, handler table | A handler that only the (stub) handler table calls needs `/INCLUDE:` too. `HandleLobbyLobbyGate_CheckCharacterNameReq` was unpaired until the pragma was added. Then it was MATCH 100.0 (+1). |
| Build input | A new worktree can lack the ignored `vendor/zstd/src`. All 5 VS2010 links fail with `ZSTD_*` unresolved. Copy the source from another worktree. Check `git rev-parse HEAD` = bb6eaf64. Delete `build-vs2010/obj/vendor` after the copy. |
| Trials | None. 16 of 17 functions need layouts that main does not have. |
## ld-18

Card lift-lobbydaemon-18: GamedChannel part 1 (35 functions) and AccountInventoryChannel (19 functions).

| Item | Result |
| --- | --- |
| Lifted | 50 (incl. 2 shared: `Network::iocpHandle`, `swprintf_s<129>`) |
| Not done | 5 (`AccountInventoryChannel::Connect`, `AccountInventorySessionHandler::OnConnect`, `AccountInventorySessionHandler::OnClose`, `AccountInventorySessionHandler` scalar deleting destructor, `GamedChannelManager::OnClose`) |
| LD MATCH | 219 -> 279 over main bfb4c98 (+60: 43 card functions, 17 shared functions), measured after the merge. The other 4 exes: +0. No MATCH lost. |

What worked (count = functions made MATCH):
- A19 separate stores for the inlined `Packet` constructor, in the PDB order: `CurHeader`, `Splitter`, `ListHead`, `ListTail`,
  `IsFragmentPacket`, `FragmentPacketCmd`, then `p.Allocate()`. `memset` and `= {}` do not fold `Allocate`. All 30 `Send*` functions
  use it (try 1 of each; about 56.7 -> 91.7).
- A4 `__declspec(noinline)` on `SharedChannel::Send(Packet const*)` (0x4ba0). The original `Send*` functions call it out of line.
  Ours inlined it (calls 40, consts 50). One edit: +21 MATCH, and `SharedChannel::Send` itself becomes MATCH. The other 4 exes lose nothing.
- Zero register form: the original keeps a zero in a callee-saved register (`cmp r12w, ax`, `lea r8d, [r12 + cmd]`). The source form of
  the `Compose` test decides this. Same code, three forms (counts are functions that reached 100):

  | Form | Result |
  | --- | --- |
  | `if (p.Compose(...) != 0)` | `SendStartChargeOk` 95.2 (consts: ours has an extra immediate) |
  | `if (0 != p.Compose(...))` | `SendStartChargeOk` 100 (+1). The same change on the other 18 `GamedChannel` functions with a `!= 0` test. |
  | `if (0 == p.Compose(...)) { log; return false; } return TSend(t, &p);` | With the `TSend` fixes below: 242 -> 253 MATCH in total |
  | `if (p.Compose(...) == 0)` | `SendChangeCharacterAppearanceReq` 100 (the `0 ==` form gave 96.3: the `0x39` immediate moved to a `lea`) |

- A4 plus an ICF guard on the `TransactionChannel::TSend` stub (0x7b2b0). The stub is a `LIFT_STUB`. Three effects:
  1. LTCG inlined the stub as `abort`. The callers lost `TSend` and the second `Packet::Clear` (calls 80). `noinline` fixes it.
  2. `/OPT:ICF` folded the stub into `GamedChannelManager::OnClose` (another stub). The call then scored as `OnClose`.
     A volatile write in the body keeps it unique.
  3. The stub is noreturn (`abort`, `__assume(0)`), so LTCG dropped the `Packet::Clear` after the call. A volatile flag test and a
     `return false` stop that. +11 MATCH. The next card (ld-28) lifts `TSend` and must delete these workarounds.

What failed or is blocked (tries):
- `SendListGoodsReq` 96.3 and `SendFinishWarehouseItemConsumptionReq` 97.0 (3 forms each, consts 89 to 91):
  1. `if (p.Compose(...) == 0) { log; return false; }` (first lift): consts 80 to 91.
  2. `if (0 == p.Compose(...))`: best (consts 89 to 91, calls 100). Kept.
  3. Success first, `if (0 != p.Compose(...)) return TSend(t, &p); log; return false;`: consts 100 for `Create`, but calls 75 to 80.
     The original puts the error block first (A17). Reverted.
  The only DIFF left is one immediate (`0x14`, `0x79`, `0x16`) against a `lea` from the zero register.
- `SendCreateCharacterReq` (repair 3): form 1 `p.Compose(...) == 0` scored 97.0 (consts 91). Form 2 `0 == p.Compose(...)` scored 100 (MATCH, +1 in the +60 total). Form 2 kept.
- `GamedChannel::SendAccountInventoryNotify` 79.1 (calls 56): the original calls `Packet::Allocate()` out of line from the inlined
  `Packet::Allocate(PacketComposer*)`. Ours inlines both. `noinline` on `Packet::Allocate()` would break the `Send*` functions
  that inline it (BloodLib, shared by all 5 exes). Below 85: no tries.
- `GamedChannelManager::PacketHandler` 82.2 and `AccountInventorySessionHandler::PacketHandler` 76.9: the original calls a handler
  through the table, and `LobbyGamePacketLobbySideHandlerList` and `AccountInventoryLobbyPacketLobbySideHandlerList` are empty here
  (null tables, owners ld-16 / ld-21 / ld-26 and the AccountInventory handler card). Below 85: no tries.
- A /INCLUDE for a function with a wrong signature fails the link (`LNK2001`). The PDB public name encodes the signature, so the
  failure points to the exact mistake: a missing `short` parameter (`SendFinishWarehouseItemConsumptionReq`), a pointer for a
  reference (`SendCreateCharacterReq`). Take the decorated names with `llvm-pdbutil dump -publics`.
- A class with a virtual function and no `virtual` destructor declared emits no vtable and no scalar deleting destructor, so an
  /INCLUDE of `??_G` does not link (`AccountInventorySessionHandler`).
- A /INCLUDE for a stub that another card owns is not allowed here. Define a local stub with a LIFT comment and list it in the handoff.

## ld-16
What worked:
- The gate (clang static libs) does not link the exes. A body that needs a symbol with no definition passes the gate and fails the VS2010 link in `tools/parity.sh`.
  Run `tools/parity.sh` (or `link.exe` through it) before you trust "obj compiles" from a checkpoint.
- `ObjPool::Checkout` and `X::_pool` have no LobbyDaemon definition (SCD form only). A handler that checks out a job from a pool is Not done until the LD ObjectPool card lands (same as ld-2, ld-13).
- `BnsCommonConfig::Config` and `LobbyErrorDesc` are plain data. A placeholder with `// LIFT:` links. Read the table from `.data` (`llvm-pdbutil dump -publics` gives `section:offset` in decimal).
- A fresh worktree has no `vendor/zstd/src` (ignored). Copy it from another worktree and check `git -C vendor/zstd/src rev-parse HEAD` = `bb6eaf64...`.

What failed or is blocked (tries):
- Low scores (18.9 to 65.8) on lifted handlers with `import:abort` in the funcdiff call list: a stub callee (`ExecuteW`, `Find`, `SendRequestPresenceKick`) ends in `abort()`.
  LTCG sees a noreturn call and removes the code after it. The source form is not the cause. Do not try forms. Wait for the callee card.
- Checkpoints can list non-functions (`0x8be40`, `0x8be50`: no `.pdata`, inside an epilogue). Check `.pdata` before you list an RVA.

## ld-19

Card lift-lobbydaemon-19: LobbyDB part 2 (26 functions, `0xa4320` to `0xa8a00`).

| Item | Result |
| --- | --- |
| Lifted | 26 (0 Not done) |
| LD MATCH | 436 -> 462 over main 480a25b (+26: 24 card functions, `Character::SetLevel`, `Character::SetSlotId`). The other 4 exes: +0. |

What worked (count = functions made MATCH):
- Dead-strip pragmas: 24 `/INCLUDE:<public name>` lines took the card from +3 to +21 MATCH. Public names come from `llvm-pdbutil dump -publics`.
  Name the real stub caller in the comment. A lifted `Character::*` caller is dead-stripped too when its own callers are stubs.
  A test removal of the `LobbyDB::UpdateCharacterData` pragma lost one pair and one MATCH (the lifted `CliSession::UpdateCharacterData` calls the stub `getCharacter` first). Keep it.
- A17 tail form: `if (dbrtn == 0) return true; return false;` after `Execute` instead of `return dbrtn == 0;`.
  `UpdateCharacterLevel` 98.9, `UpdateCharacterData` 99.0, `RegisterGameAccountExpInfo` 99.0: all 100 (+3). Same as ld-15 `FinishCharacterCreation`.
- New (A10/A17 family, +2 and large score gains): use the `DbTransaction::BindCol` member call (`tran.Tran->BindCol(i, &buf, 0, type, &collen[i-1])`, `goto BIND_ERROR`) for the
  columns of a loader, not the `DB_BIND_COL_NI` macro. VS2010 inlines it and then merges the error paths into one `statmentErrorLog` site as the original does.
  The macro kept one site for each column. Scores: `LoadGameAccounExpInfo` 86.5 -> 100, `LoadJumpingCharacterCreationQuota` 98.0 -> 100 (with column 1 as member call too),
  `LoadGameAccountContentQuotaList` 80.6 -> 95.3, `RetrieveExpiredDeletionWaitingList` 89.2 -> 97.8.
  Inline choices are global: changing one loader moved `LoadJumpingCharacterCreationQuota` 100 -> 97.3 until its column 1 used the member call too. Change all loaders of one file together.
- do-while fetch loop (scd-4) plus the A17 tail and the `ID128_ID_ZERO` copy (A8) on the 4 loaders: small gains (+1.9 to +0.5) and the base for the BindCol form.

Trials (max 3 forms per function; each loader used 2):

| Function | Form | Result |
| --- | --- | --- |
| `LoadGameAccounExpInfo` | 1 do-while, A17, A8; 2 BindCol member | 86.5, 88.4, 100 |
| `LoadJumpingCharacterCreationQuota` | 1 do-while, A17, A8; 2 BindCol member for column 1 | 98.0 -> 100, 97.3 (after neighbour change), 100 |
| `LoadGameAccountContentQuotaList` | 1 do-while, A17, A8; 2 BindCol member | 80.6, 82.5, 95.3 |
| `RetrieveExpiredDeletionWaitingList` | 1 do-while; 2 BindCol member | 89.2, 89.7, 97.8 |

What did not reach MATCH:
- `LoadGameAccountContentQuotaList` 95.3: the original calls `vector<AccountContentQuota>::push_back` out of line; ours inlines it. The other callers are stubs. A `noinline` wrapper would only fool funcdiff.
- `RetrieveExpiredDeletionWaitingList` 97.8: the original calls `vector<LobbyService::DB*>::_Reserve` (linker folding of pointer-vector code, other PDB name) and `vector::clear` out of line.
- Next card idea: try the BindCol member form on `LoadGameAccount` 80.5, `LoadCharacterList` 79.0, `LoadGameWorldCluster` 84.2, `LoadGameWorld` 77.5 (they use the macro). The ld-17 note said "one `statmentErrorLog` per column" for the last three. Check it with the disassembly first.

Build facts:
- A new worktree can lack the ignored `vendor/zstd/src` (same as ld-17). Copy it before `tools/parity.sh`.
- A full `tools/parity.sh` right after `gate.sh` gave LD 460 once, while the same source gave 462 in `tools/parity.sh LobbyDaemon` and in a second full run. Run parity twice when the LD count looks low. ❓ (cause not found)

## ld-20

Card lift-lobbydaemon-20: LobbyDaemon part 2 (21 functions) and BLDaemonInfo (9 functions). LD MATCH 436 -> 464 (+28) over main 9d0ef81.

| Item | Fact |
| --- | --- |
| A15 again, ICF side effect | `BLDaemonInfoTable::add` (0x40e30) inserted `value_type`. Ours made `_Buynode<std::pair<BLDaemonID const,...>>`; the PDB has `_Buynode<std::pair<BLDaemonID,...>>`. `/OPT:ICF` folds this node builder with the one of `CliSessionTable::Insert_index_pcid`, so that MATCH function turned DIFF (100 -> 93.3, calls 80). Insert `std::pair<K, V>(k, v)`: `add` 95.2 -> 100 and `Insert_index_pcid` back to 100. A new map instance can break a MATCH in another module through ICF. Check the whole LD diff after each new map. |
| A27 works with a `throw()` placement new | `LobbyDaemon::cooldown` (0x9ef40): `GCoolDown = mem ? new (mem) CoolDown() : nullptr;` stored the global in each branch and reloaded it (refs 93). `GCoolDown = ::new (Alloc(...)) CoolDown();` gives the null test (PlacementNew.h is `throw()`), one store, and MATCH (97.8 -> 100). |
| Range check form | `LobbyDaemon::CheckServiceItemDataId` (0x9f340): the original has `cmp 7; ja`. `(unsigned)type >= SERVICEITEMTYPE_MAX` gave `cmp 8` (consts 50, 83.3). `(unsigned)type > SERVICEITEMTYPE_RENAME_CHARACTER_BY_SYSTEM` (the form of `ServiceItems::Add`) gives MATCH. |
| Dead-strip | 7 `/INCLUDE:` pragmas (4 `BLDaemonInfoTable`, `FilterBannedWord`, `CheckServiceItemDataId`, `GetAddressStringWForLogs`) paired 14 functions: `load` and `add` come with `Load`/`Update`; `Find` and `Clear` need no pragma (`Update` and `~BLDaemonInfoTable` reach them), and `FilterName`, `StrNormalize`, `ConstFilterName` with `FilterBannedWord`. |
| Not tried | `BLDaemonInfoTable::load` 70.6 (the original interleaves the 5 inlined element blocks; ours groups the `_wcsicmp` calls) and `BLDaemonInfoTable::Clear` 57.8 (the original calls `_Tree::clear` out of line; ours inlines it into `_Erase`). Both below 85 and over the trial limit. |

## ld-23

Card lift-lobbydaemon-23: GamedChannel part 2, InfoGateChannel, LobbyInfoGatePacketHandler (45 functions, 0 Not done).

| Item | Result |
| --- | --- |
| LD MATCH | 436 -> 480 over main 9d0ef81 (+44: 41 card functions, 3 shared). The other 4 exes: +0. No MATCH lost. |

What worked (count = functions made MATCH):
- A17 for a `void` `Send*` function: error block first. `if (0 == p.Compose(...)) { Log::Write(...); } else Send(&p);`
  The first lift had `if (0 != Compose) Send(&p); else Log::Write(...)`. Funcdiff showed `SharedChannel::Send` before `Log::Write` (calls 80, one extra immediate).
  Form 1 on 19 functions: all reach MATCH (93.3 or 88.6 -> 100). The trial limit is 3 forms per function, not 3 functions in total.
  Rule: a `Send*` with a log in the else branch uses the error-first form from the start. The ld-18 form `0 != Compose` is for functions with no log.
- `BroadcastBoastEventInWorldNotify` (87.5 -> 100, +1): error block first with `return`, then the broadcast block also ends in `if (!Broadcast(&p)) { Log; return; }`.
  The original has 3 `Packet::Clear` calls (compose fail, broadcast fail, broadcast ok). Two `return` statements and the fall-through give the same 3 inlined destructor calls. A single `if` with no `return` gives 2.
- A PDB line map gives the source order of a handler. `HandleLobbyInfoGate_AuthTokenReq`: line 136 (mismatch) lies before line 142 (OK) in the source and after it in the code (the compiler moves the error block).

What failed or is blocked (tries):
- `HandleLobbyInfoGate_AuthTokenReq` 97.7 (2 forms): the OK path and the mismatch path both end in `removeReferenceCount(cliSession, FILE, line)`. VS2010 merges the tails and loads `r8d` per path.
  The original keeps 2 calls because the mismatch log reads the session token from a saved copy of the session pointer. Ours writes zeros in place of the token (safety), so the tails merge. Not fixable without logging the secret.
  Form 1 (OK first) and form 2 (mismatch first) both give 97.7.
- `InfoGateChannelManager::PacketHandler` 77.3 (1 form): the table now holds 3 entries and none is a fragment handler. LTCG folds the table into `PacketHandler` and drops the fragment branch.
  A separate translation unit for the table does not stop it (LTCG sees all `/GL` objects). The original has one `lea` to the table and keeps the fragment branch. ❓ Why is not known. Below 85 at the start: no more tries.

Notes:
- A function that only a null handler table reaches is dead-stripped. When the table is filled, remove the `/INCLUDE` pragmas of the handlers. A caller that is lifted in the same card does not need a pragma.
- A worktree without `vendor/zstd/src` fails to link all 5 exes (`ZSTD_freeCDict`, `ZSTD_createCCtx_advanced`, `ZSTD_compress_usingCDict`). Copy it from another worktree (it is git-ignored).
- A caller that calls a noreturn `LIFT_STUB` (`BLDaemonInfoTable::Find`) loses all code after the call under LTCG. `HandleLobbyInfoGate_HelloReq` scored 30.4 for this reason. It is not a source error.
- A header of another card of the same wave is not edited. Read the 2 fields with a local layout struct and a `// LIFT:` comment.
- PDB inline methods (`InfoGateChannel::GetWid`, `IsBroadcastable`, `StartBroadcast`) belong in the class header as inline members, not as a file-local helper.

## ld-21

- A card that compiles with clang can still fail the VS2010 link. Run `tools/parity.sh` (or `tools/vs2010/build.sh LobbyDaemon`) before you accept a checkpoint. New references to a non-lifted `static ObjPool _pool` or to data without a definition give LNK2001.
- LTCG inlines a `LIFT_STUB` (noreturn `abort`) into its caller. The caller then loses all code after the call. Scores of 11 to 65 on handlers that call stubs are a stub effect, not a codegen miss. Do not spend tries on them.
- An in-class body of a virtual function in a header (`AuctionEscrow.h` `_StsMsgRequest`) gives LNK2005 when another TU defines the same function (`NPChannel2.cpp`). Use declarations in headers.
- A4 worked for `String::UnicodeToMultibyte` (`__declspec(noinline)` on the shared definition): `SetAppDataNotify` 96.4 to 97.2 and the callee is MATCH.
- A worktree without `vendor/zstd/src` links with the stub zstd in the clang build. The VS2010 link then fails for all 5 exes (`ZSTD_*` unresolved). Copy the ignored checkout (bb6eaf64) in first.
- Checkpoint rows can name a cold chunk or an inner address (`0x8d990`, `0x8e620`) instead of the index entry. Check each card row against `index.tsv`.
- A10 worked on a plain-`static` helper set (`assertCrash`, `LobbyErrorText`, `UpdateFailCode`, `ChannelIdOf`, `WorkerIdOf`, `SetupDecomposer`, `HandleShowcaseOk`): `static __forceinline` made `SetAppDataNotify` 97.2 to 99.2 and the 3 `ChangeCharacter*Ok` handlers 11.9 to 44.3. Try A10 on every DIFF handler of a card before you call the score a stub effect.
- A8 on `ChannelIdOf` (drop the `channel != nullptr` test, read `_rawChannel` only): no score change in any function. The original has the channel test in most handlers (`channel != nullptr && channel->_rawChannel != nullptr`) and in the log lines of `0x907e0`. Keep the test there. The `Select_index_pcid` wid of `0x907e0` and the wid and log code of `0x8c660` read `_rawChannel` alone.
- Two LobbyDaemon header families define `StsMsgLib` (`StsMsgGrade.h`/`AuctionEscrow.h` and `SmartCouponDaemon/NPChannel.h`). Do not put a second `class NPChannel` in a LobbyDaemon header (ODR). Include `NPChannelBase.h`, and do not include `AuctionEscrow.h` in the same TU.
- Merging two cards that each added a file-scope helper for the same inlined code (`LgpChannelId` and `ChannelIdOf`): keep one `static __forceinline` helper with a `const` argument. The scores did not change. Also check for a second definition of a placeholder (`BnsCommonConfig::Config`) when the later card adds the real file.
- A7 on `skipRepeatFormat` (`static_cast<PacketFormatIterator&>(pdr).skipRepeatFormat();`): the original calls it through the vtable, it does not inline it. A call on a local `PacketDecomposer` binds statically in VS2010. The cast gives the `call [rax+0x38]`. It is needed for MATCH, but alone it did not change the score of `SetAppDataNotify` (99.2).
- Layout of a ternary after a repeat end (`SetAppDataNotify` 0x907e0): the original puts the `GetId` call of the wid in a far block (`cmp [rdi+0x18],rbx; jne far`). Three forms for `short wid`: `p != nullptr ? GetId : 0` 99.2, `short wid = 0; if (p != nullptr) wid = GetId` 97.7, `p == nullptr ? 0 : GetId` 100.0 (MATCH, +1). Try the reversed ternary when the original has a `jne` to a far block.

## ld-24

Card lift-lobbydaemon-24: LobbyGateChannel part 1 (41), PostOfficeChannel (7), PostOfficeClientSideHandlerList (1), PostOfficePacketHandler (4).

| Item | Result |
| --- | --- |
| LD MATCH | 436 -> 523 (+87 over main 9d0ef81: 40 card functions, 47 shared functions). The other 4 exes: +0. |
| Dead-strip | The final code has 40 `/INCLUDE` pragmas in `LobbyGateChannel.cpp` and 6 in `PostOfficeChannel.cpp` (46 in total). Without them the `Send*` functions were unpaired and not counted. The `SendCloseAnonymousSessionNotify` pragma (removed in d5cbf87) and the `SendHelloReq` pragma (removed in repair 2) are not needed, because lifted callers reference those functions. |
| Build input | The worktree had no `vendor/zstd/src` (see ld-17). Copy it before the first parity run. |

What worked:
- A21 and A10: a local pointer to the member list (`PipeConsole::ItemList* const invalidList = &console->_invalid;`) and one to the lock, taken as in the pseudocode (`p_invalid`, `p_CS`).
  `PostOfficeChannel::Connect` 90.3 -> 97.0 and `PostOfficeSessionHandler::OnClose` 93.3 -> 97.0 (consts 80 and 89 -> 100). The extra `0x278` and missing `0x60` immediates came from `_invalid` and the key offset
  being computed at each use. Only a `L""` reference (`valueString`) is left (see B, `addNode`).
- A data table that a lifted handler reads needs its own definition in the table module (`PostOfficePacketClientSideHandlerList`, `0x203770`). Read the entries from the exe with `pefile` (value - image base = RVA).
  Take the type from the public name (`PAP6A_NPEBVSession@@PEBVPacket@@@ZA` = `Daemon::PacketHandler[]`), not `void*`. A checkpoint that says "compile ok" does not test this. Only the VS2010 link does.
- A call into a module with no owner card (`Goods::Fetch` `0x6010`) fails the link. Make a skeleton file with a `LIFT_STUB` body and a LIFT comment. Do not lift it inside another card.

What failed (1 try each):
- `PostOfficeSessionHandler::PacketHandler` 97.6: `if (session != nullptr && packet != nullptr) { ... } crash block last`. No change. The compiler puts the block first in both forms.

Repair 2 (kept):
- `PostOfficeSessionHandler::PacketHandler` 97.6 -> 100.0 MATCH with A23: `void* iocpHandle = nullptr;` at the top, `short const* const pCmd = &header[1].size;` tested for `nullptr`,
  `*pCmd` at each use (no `cmd` local), `iocpHandle = Network::iocpHandle()` in the pump branch.
- `HandlePostOfficeHelloFail` 93.3 -> 100.0 MATCH with the constant first: `if (0 == packet->Decompose(&pdr, 1, &reason))` (A24, P21 form). The first try (decomposer field order) did not change the score.
  The same form in `HandlePostOfficeRegisterPostOk` and `HandlePostOfficeRegisterPostFail` raised 38.1 -> 40.0 and 36.7 -> 40.0. Kept.
- `/INCLUDE` for `SendHelloReq` removed. The lifted `OnConnect` calls it, so `/OPT:REF` keeps it. LD MATCH 521 -> 523 (the +87 total above).

## ld-22
What worked:
- Run `tools/parity.sh LobbyDaemon` on a checkpoint before you trust "lifted". The gate builds clang static libs and never links the exe.
  Checkpoint 4 listed 5 lifted job-start handlers. All 5 failed the VS2010 link (`<Job>::_pool`, `ObjPool::Checkout`).

What failed or is blocked:
- A handler that calls `ObjPool::Checkout(&X::_pool)` is Not done until a LobbyDaemon ObjectPool card defines `ObjPool` and the `_pool` statics. This holds even when the job layouts are lifted from the PDB (same as ld-16).
  The VS2010 link resolves all externals of `LobbyLobbyGatePacketHandler.obj`, even of functions that `/OPT:REF` removes later. A missing `<Job>::_pool` or `ObjPool::Checkout` fails the link.
- `GetServiceEntryListReq` 77.9 -> 78.5 (calls 61 -> 63): the first lift had an explicit `fp.packet.Clear()` on each path. `~FragmentPacket` -> `~Packet` already calls `Packet::Clear` (inlined destructor), so every path ran Clear twice. Remove the explicit calls and let the destructor do the one Clear (A-pattern: destructor alone, as in `Client.cpp`). No other form was tried (below 85).
- `GetServiceEntryListReq` 78.5 -> 80.4 (calls 63 -> 69): error block first (A17/A29). The PDB line map for 0xc8aa0 has the failure block at lines 1376-1394 and the success path at 1397-1404. Write `if (!FetchServiceEntryList(&fp)) { error mapping; Log 1390; SendGetServiceEntryListFail; removeReferenceCount 1393; return true; }` and then the success path. Kept. Still below 85, so no other form was tried.

Build facts:
- A new worktree has no ignored `vendor/zstd/src`. All 5 exes then fail with `ZSTD_*` unresolved. Copy it from another worktree (`bb6eaf64`) and run `tools/gate.sh` again.
- A lifted handler can pull a neighbour into the link and pair it (`CliSessionTable::Select`). On main this neighbour is already MATCH, so the card adds +0 MATCH there.

## lg-5a
What worked:
- `OnConnect`/`OnClose` MATCH: an inline `repe cmpsw` against a literal (count = length + 1) is `wcscmp(p, L"literal") == 0`. Do not write the loop by hand.
- `LobbyD::Hello` MATCH: two Leave calls in the original mean one Leave in each branch after the call.
- `StartSessionWith*TokenOk` 88.7/89.5 -> 97.3/96.7: `#pragma inline_depth(0)` keeps the `FragmentPacket` ctor, `Allocate` and `PopRepeatCount` out of line; `__forceinline` helpers still inline. Compose-fail branch first.

What failed:
- `StartSessionWith*TokenOk`: under `inline_depth(0)` the `~FragmentPacket` call is shared; the original has one inlined `Packet::Clear` per exit. No MATCH.
- `HelloOk` 99.3, `HelloReq` 94.1: score only (register choice). Reverted. `CloseSessionNotify` success-first: worse.

## gd-wave0 (GameDaemon cards 0a to 0e)
What worked:
- Split a new-exe card in two lanes: `tools/*` and Docs in the tools lane (0 new, 0 lost MATCH), `src/*` in the card lane. The card lane refuses pinned paths (`tools/*`, `Docs/Parity/*`, `cmake/*`, `*.cmake`, `vendor/*`).
- Per-file TUs give the same codegen as one unity TU for GameDaemon (card 0d: equal MATCH sets on all paired functions). Keep the per-file skeleton.
- A lifted leaf with no live caller is dropped by `/OPT:REF` (`wmain` is a stub). Keep it with `#pragma comment(linker, "/INCLUDE:<public name>")  // LIFT: dead-strip keep (no live caller yet)`. One pragma per leaf. Remove the pragma when a real caller lands.

What failed or is blocked:
- A pragma line without a `// LIFT:` note fails the public guard. With the note, the item goes to review (no automatic credit).
- A new exe block in `CMakeLists.txt` plus a new `*.cmake` source list fails the card lane (CMake structure edit, pinned path). The first skeleton of a new exe needs an operator land.
- Do not push to main while a check or land of a card is in flight. The land push then fails (non-fast-forward).
- Rebase the card commit onto main yourself before the check. With an old base, cherry-pick only the card commits.
- Wait for a long job with a background task and its notification. A `pgrep -f "<text>"` loop matches its own command line and never ends.

Build facts:
- First full GameDaemon build on the remote build host: 3:40 wall (563 objects, compile span 148 s, link tail 16 s, funcdiff 38 s). Local cold build (card 0d): 7:03; warm: 2:00.

## gd-wave-e (GameDaemon easy-leaf cards E1 to E16)
What worked:
- A card with many stems needs a work order in the card: one stem at a time, a commit per stem, the first commit before turn 12, and no full read of `types.h`. Without it, the author read all stems first and its context split before the first edit (E12, E14).
- Small form rejects (condition code or immediate): test the source forms on a scratch file with the VS2010 compiler (`cl /c /O2 /GR-`, then `llvm-objdump -d`). Then fix the card source by hand. Examples (E14): `(PostQueuedCompletionStatus(...) != FALSE) - 1` gives `setne; lea eax,[rcx-1]` (a `? 0 : -1` gives `neg; sbb`). `!(1 <= id && id <= max)` gives `mov eax,1; cmp ax,dx`. A `bool` result returned as `unsigned` needs `? 1 : 0` for `setne` (else `movzx`).
- MSVC puts same-name virtual overloads in the vtable in reverse declaration order.

What failed or is blocked:
- A GameDaemon function that writes a crash log (`Log::Write`, `AlertSender::Write`) keeps the shared BloodLib log functions alive. Their shared form is not the GameDaemon form (`AlertSender::writev2` frame size, TLS offset of `LogBufferAllocator::_Local`, 3-arg `addReferenceCount` in `LogBuffer::Acquire`, store order in `LogMedia::Add`). The review rejects them. Until card `lift-gamedaemon-s2` lands, keep such callers as `LIFT_STUB` (E12, E16).
- After a rebase of the card commits onto a newer main, the author driver guard still diffs against the old queue base and parks the card. Run the card check on the rebased commit instead.
- A padded member (`char _x[N]`) that hides PDB members fails the layout check when its alignment is wrong. Declare the PDB members at their offsets, then pad the rest (E15).
