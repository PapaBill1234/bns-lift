# Parity lessons

Cleaned in lift-parity-review-2 (2026-11-18). The stage notes of round 2 are merged into the patterns. The list is sorted by
the number of functions fixed (sum over the 4 exes; a shared function counts once per exe). Old numbers are in brackets:
(r1 A3) = A3 of review 1, (P11) = old Pattern 11. Each new card adds its patterns at the end of section A or B. The next review sorts them again.

Mapping review 1 -> review 2: A1=A1, A2->A3, A3->A2, A4->A6, A5->A4, A6->A5, A7->A8, A8->A9, A9->A11, A10->A13, A11->A7,
A12->A14, A13->A15, A14->A16, A15->A10, A16+A17->A17, new A12 (crypto source forms).

## A. Patterns that worked

### A1. Funcdiff noise fixes (tool cards): 476
- lift-parity-0 (396): branch targets counted as constants, jump tables read as code, calls through a slot with no symbol,
  `__chkstk` frame size. CG +77, LG +97, SCD +109, POD +113.
- lift-parity-tool-2 (80): vtable symbol before `string_at` (fix 5), `.tls` offset as ref `tls:<name>` (fix 6),
  `<K const ,V>` name form (fix 7), `?Setup@PacketCrypt@@...` demangle (fix 8). CG +18, LG +19, SCD +23, POD +20. Details: C1 to C3.
- Proof of each fix in `noise.md`.
- Rule: fix a tool error before a source change. A tool error hides real progress and makes good changes look bad (C1).

### A2. `__declspec(noinline)` on a function that the original calls out of line (r1 A3; P11, P19, P24, P48): 75
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

### A3. Third-party code: vendor the exact upstream commit (r1 A2; P18): 73
- zstd: upstream `dev` commit bb6eaf64 (2018-05), not v1.3.5. See `vendor/zstd/README.md`. CG +16, LG +25, SCD +12, POD +20.
- Method: count the calls of one function on both sides (for example `ZSTD_litLengthContribution`) and bisect the commits.

### A4. Per-exe path literal of a shared file (r1 A5; P30, P35, P41, P45): 62
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

### A5. Block order follows the original address order (r1 A6; P3, P7, P10, P20, P25, P33, P39, r1 A17): 60
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

### A6. Virtual call on a global object through a base reference (r1 A4; P1): 49
- Cause: `BaseMemoryManager::_Instance.Alloc(...)` binds statically and LTCG inlines `HeapMemoryManager::Alloc`.
  The original calls through the vtable (`<indirect>`).
- Source: macro `BASE_MEMORY_MANAGER` = `static_cast<MemoryManager const&>(BaseMemoryManager::_Instance)` at all 59 sites.
- Example: `BaseRefCntObj::deallocate_me` CG 0x18460: `import:HeapFree` -> MATCH. CG +9, LG +11, SCD +15, POD +14.

### A7. Copy the original refs and reads one to one (r1 A11; P22 s3, P23, P40, P43, P45): 26
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

### A8. Member types exactly as in the PDB: no extra `volatile` (r1 A7; P15): 25
- Cause: `long volatile _ref` in `RefCntObject.h`. The PDB type is plain `long`. A volatile store keeps the dead base ctor stores.
- Example: `PacketBufferPool::allocate` CG 0x128d0 -> MATCH. Rule: check each `volatile` member with `pdbq <EXE> type <Class>`.

### A9. CRT template overloads (r1 A8; P9): 25
- The original calls `swprintf_s<N>` out of line. Source: the 2-argument form with an array destination.
- Only when the size argument is the full array size. Clang build: `include/vs2010/crt_cpp_overload.h` under `#if defined(__clang__)`.
- Example: `WinServiceConsole::ServiceMain` 0x177d0. CG +3, LG +7, SCD +2, POD +13.

### A10. Lift helpers as `static __forceinline`, shared END tail (r1 A15; P34, helpers-2): 24
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

### A11. Map allocator with a non-const pair key, as in the PDB (r1 A9; P22 cg-1, P38, P44, P47): 22
- Cause: PDB names are `StlAllocator<std::pair<K,V>,2>` (key not const). Ours used `pair<K const,V>`.
- Source: the typedef uses `std::pair<K, V>`. Insert with `std::pair<K, V>(k, v)`, not `value_type(k, v)` or `std::make_pair`.
- Examples: `ClientManager::ReleaseSession` CG 0x6250, LG `ClientManager::RemoveClient` 0x60c0, SCD `JobManager::Clear` 0x6ff0 (SCD +11),
  POD `PostContext.h`, `RelayContext.h`, `RelayTimeContext.h`, `WorldChannel.h`, `WorldConfig.h` (pod-2, +4).

### A12. Crypto source forms (crypto-2): 20 (+5 each exe)
- Blowfish `encrypt`: `(s + 256)[x & 0xFF]` (pointer offset, disp 0x400/0x800/0xc00), not `s[256 + (x & 0xFF)]` (32-bit index add).
- Blowfish `decrypt` 0x360a0: `for (long long i = round - 1; i > 0; i -= 2) { t = F(r) ^ l; l = pbox[i-1] ^ t; r = F(t) ^ pbox[i] ^ r; }`.
- `Ctr::Encrypt`: `if (++_counter[j] != 0) break;`, not `_counter[j]++ != 0xFF`.
- `Prng::setSeed` 0x35d60: `rand() % 256` (orig `and eax,0x800000ff; jge; dec; or; inc`).
- `Prng::addEntropy` 0x35e10: `_alloca(size + 20)` with `hashSize = 20` before it. A fixed `buf[148]` let LTCG inline it.

### A13. Loop forms that VS2010 compiles as the original (r1 A10; P16, P26, P43): 18
- `for (i = 0; i < 128; ++i) { ...; if (!f(i)) break; } if (i >= 128) return true;` is not unrolled (`PortListener::Initialize` 0x31fd0).
- Count down and step the pointers: `for (; count > 0; --count, ++defList, ++loadDefList)` (BnsCommonConfig, CG +4, POD +4, LG +2, SCD +2).
- Hex dump: walk a byte pointer and write `temp[k++]` three times (SCD `NPChannel::handlePacket` 0x57d0).

### A14. Error blocks and cleanup tails as in the original (r1 A12; P14, P36, P13 s1): 16
- One full error block per failed call when the original calls `WSAGetLastError` in each (`Network::initializeSocketInterface` 0xda30).
- One shared cleanup tail (`goto cleanup;`) when the original has one tail (`TakeGoodsOk` 0x113e0).
- `__try { ... __leave; } __finally { ... }` when the HR shows `$__FINALLY_n` (`ListLobbyServiceItemInfoOk` 0x117a0).
- No explicit `p.Clear()` / `fp.packet.Clear()` before `return`: the dtor clears. An explicit Clear gives one more `Packet::Clear` call
  (`BypassPacket` 0x121d0; LG `Client::SendListGoodsOk` 0x4b20 +2; POD `WorldChannel::SendRelayResponse` 0x1e570 +1).
- One `Db::ReleaseTransaction` per return: `if (*ret != 0) return false; return true;`, not `return *ret == 0;` (POD `ResetAllDeliveryFailurePost`, +1).
- Zero-fill after the `Prepare` check, not at the declaration (POD `PostOfficeDB` `paramLen`).

### A15. Compiler-generated destructors (r1 A13; P42, P29, P39): 12
- No user-declared dtor when the original dtor is a thunk with no vtable store (`EventObject`, `DynamicEventObject`; CG +1, LG +1, POD +5, SCD +2).
- An inline dtor with a member dtor gives the EH state of the original (`inline Db::~Db()`, `db->~Db();` in `Db::Clear`).
- Empty body when the member dtor does the work (`FragmentPacket::~FragmentPacket` 0x24e0).

### A16. Allocation forms (r1 A14; P46, P28, P37, scd-2): 12
- Placement array new: `new (Alloc(sizeof(T)*n+8, file, line)) T[n]` (macro `liftArrayNew`, POD +8).
- Placement array new of a type with a ctor and dtor (orig calls `eh vector constructor iterator`): SCD `CouponJob.cpp`
  `#define __PLACEMENT_VEC_NEW_INLINE` before all includes, own `operator new[](size_t, void*) throw()`, own
  `operator delete[](void*, void*)` with the Memory.h:181 crash Log + Alert, `inline operator delete[](void* p) { __delv_buf__ = p; }`,
  dtor `delete[] _jobs; Free(__delv_buf__, ...)`. `JobManager::Initialize` 0x6e10 and `operator delete[]` 0x6850 MATCH (+2).
  `__delv_buf__` is a PDB `S_GTHREAD32`; no exe imports `??_V@YAXPEAX@Z`. Same shape in LG `GateKeyManager::Initialize` (card arraynew-3).
- Null-checked placement new before the null test: `T* p = mem != nullptr ? new (mem) T() : nullptr; if (p == nullptr) {fail}`.
- Inlined Packet ctor: `Packet packet = {nullptr, false};` then the 4 pool stores (`ClientManager::BroadcastAnnounceNotify`).

### A17. Small source forms: 1 or 2 each
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
- `tools/vs2010/build.sh` tracks headers (tool-2): `cl /showIncludes` writes `build-vs2010/obj/<src>.dep`. No `touch` is necessary.
  A new `build-vs2010/obj` builds all objects once (about 5 minutes in a new worktree).
- `tools/vs2010/build.sh` compiles one object per source path with fixed flags. It has no per-exe define (card perexe-3).
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

## D. Open causes (not solved, not tool noise)
- Closed crypto libraries (crypto-2): NOT compile flags. The LG PDB `S_COMPILE3` of BloodLib `Port.obj` and of BloodCrypto `rsa.obj`,
  `BigInteger.obj` is the same: `ltcg | security checks | hot patchable`. The original links `Security\lib\BloodPacketCrypt64.lib`
  (BloodPacketCrypt, NoPacketCrypt, HandshakePacketCrypt, SessionPacketCrypt, BroadcastPacketCrypt) and `BloodCert64.lib`
  (BloodCert, ssn, CertDec, nic, ModuleCodeString, Cert). They have `no dbg info`: no `S_GPROC32`, no pseudocode in `hr/`.
  They call `Crypto::Create`, `Rsa::Rsa`, `Dh::Dh`, `RsaPrivate::~RsaPrivate` (LG 0x14004cf70, 0x14004c5d0). Ours has
  `PacketCrypt::Create` / `InstanceSize` as stubs (`TODO(lift-lobbygate-4)`, `Session.cpp:945`, `:955`). Misses: LG 72, SCD 47, POD 47. Card cryptolib-3.
- LTCG inline choice: `TimerQueue::clearShortTermQueueSlot`, `LogMedia::Write` inline `removeReferenceCount` (stop list).
- Constant propagation: `ThreadManager::Initialize(128)`, `Network::OpenPort` assert, `Session::Connect` timeout (LG, SCD).
- Constant CSE: `EventNotiJob::finalize` 0x9cc0, `JobManager::Execute` 0x71a0 (stop list).
- Merged `Log::Write` tails: `Session::HandleEvent` 0xf1c0, `CacheDList::MakeSessionAll` 0x27d0, SCD `CouponJob::transit` 0x6990 (Alert tail merge).
- `_instance` reload in LG `KickNotify`, `CloseSessionNotify`.
- DB loaders: SCD `SmartCouponDB::Process*GameEventLog`, `Load*` inline only the first `BindCol` and have no `DbTransaction::Fetch` call.
  POD `PostOfficeDB::Load*` inline 17 `BindCol` (ODBC import #4) with one shared "Not initialized" tail; `memset`/`PostInfo::PostInfo`
  after the first acquire `Log::Write`; inline `AttachedItemInfo` ctor loop. Card dbbind-3.
- Block layout that the source order did not move: SCD 0x8e80, POD 0x1aaa0, LG `Client::SendTakeGoodsOk` 0x4ed0 (orig `Allocate` before
  the first `Compose`), POD `updateWorldList` x3 (crash block after the loop), `PingRelayContext::processRelayResponse` (one Alert less).
- Constants with no known cause: `Port::Initialize` EH state -2 (maybe a class `operator new(size,file,line)` + matching delete),
  POD `PostInfo::CheckValidityPostData` (switch lowering 0x2/0x7 vs 0x5), POD `ComposeResponsePacket` x2 (line numbers, unwind),
  `Blowfish::Setup` (register allocation), `aes128TableSetupEncKey` (orig unrolls 5 times), `aes128TableSetupDecKey` (not tried).
- Scalar placement `operator delete(void*, void*)` (Memory.h:173 crash Log): DIFF score 0 in CG, SCD, POD, orig-only in LG. Card arraynew-3.
