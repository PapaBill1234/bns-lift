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
- `tools/vs2010/build.sh` compiles one object per source path with fixed flags. The per-exe define exists now (section E).
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

## E. perexe-3 (2026-11-18, final)
- Per-exe objects: `tools/vs2010/build.sh` gives `-DLIFT_EXE_<CG|LG|SCD|POD>` to each source that has the token `LIFT_EXE_` (itself or in
  a repo header, found by the python filter in `tools/vs2010/build.sh`). Object: `build-vs2010/obj/<TAG>/<src>.obj`. Other sources keep one shared object.
  `xargs -L1` joins a line that ends with a blank with the next line: write `"$s${tag:+ $tag}"`, no trailing blank.
- `StlMemory.h`: `LIFT_STLMEMORY_FILE` default depends on `LIFT_EXE_*`. `TimerQueue::~TimerQueue` MATCH in LG, SCD, POD (the inlined COMDAT copy had the CG path).
- `Session::Send(Packet const*)`: `noinline` only for CG, LG. `Session::deallocateCrypt`: `noinline` only for LG (0x194c0). The ONLY-OURS entries are gone in CG, SCD, POD.
- Measure after stage 1 (last run, parity ok): CG 421 (+1), LG 532 (+2), SCD 512 (+2), POD 592 (+4). Gate ok.
- Worked: ICF fold name. Orig POD has 2 case forms of the StlMemory.h path: `E:\DailyBuild02\PostOfficeDaemon-Common-...\Program\Server\...` (modules PostContext, RelayContext, RelayTimeContext)
  and lower case (others). With one lower-case path in all POD objects, ours folds `_Tree<ushort,WorldChannel*>::_Erase` into the `<__int64,PostContext*>` copy and
  `WorldConfigList::~WorldConfigList` loses MATCH. Fix: the 3 modules define `LIFT_STLMEMORY_FILE` in mixed case (POD +3 with the Session fixes).
  Count of path forms per exe: `grep -o 'L"[Ee]:[^"]*StlMemory.h"' ~/.cache/bns-lift/hr/<EXE>/*.c`. Mixed case: LG Client; SCD CouponGameEventConfig; POD 3 modules above; CG none.
- Worked: type test of `deallocateCrypt` as the compare chain `type == 0 || ((r1 = type - 1) != 0 && ((r2 = r1 - 1) == 0 || (unsigned)(r2 - 1) <= 1))`.
  A `switch` on 0, 2, 3, 4 keeps the constant 0x2. The chain removes consts 0x2,0x3,0x4: `Session::~Session` MATCH in CG, SCD, POD (+1 each).
- Worked: `if (crypt == nullptr) return;` inside `deallocateCrypt` (orig LG 0x194c0 has it): removes the tail-jump to `Free`, LG `deallocateCrypt` MATCH.
- Worked: LG `Session::~Session` 0x175a0 inlines `deallocateCrypt` twice by hand under `#if LIFT_EXE_LG`. A local macro with the chain test (not `switch`) gives MATCH (LG +1).
- Final measure (gate ok, parity ok): CG 421, LG 533, SCD 512, POD 592 (baseline 420/530/510/588). Shared 421/499 (no change: the shared count needs MATCH in all 4 exes).
- Fact: `tools/parity_shared.py --list` still says DIFF for `Session::~Session` (all 4 exes) and `TimerQueue::~TimerQueue` (LG, SCD, POD) after the full parity run,
  but `build-vs2010/<EXE>.funcdiff.json` says MATCH for each. The shared count stays 421/499. Cause not found (❓): `parity_shared.py` may compare the shared build, not `obj/<TAG>/`. Read it before the next card.
- Fact: IDA did not open `CacheGate.exe.i64` in this card (status 4). `Session::SendV` CG 0xfaa0 was not checked in disasm.
- Not a path literal: the remaining refs-only DIFFs (`Network::Network`, `PacketBufferAllocator::initAllocator`, `Session::Session`, `StaticPageMemoryManager::Initialize`,
  `DaemonConfig::Dump`) differ in the count of global data refs (`Network::EndEventObject`, `_Allocator`, `BaseMemoryManager::_Instance`), not in a path. They need a data-layout or init-order cause.
- Not a per-exe cause: scalar placement `operator delete(void*, void*)` (Memory.h:173) is DIFF score 0 in CG, SCD, POD (card arraynew-3). IDA did not open CG in this card; `Session::SendV` CG 0xfaa0 not fixed.
  The orig `Compose` call there has the const 0xf9e twice; our source has it once (`Compose(..., 0xF9E, format, -1, args)`).

## lift-parity-cryptolib-3 (closed crypto libraries)
- Worked: lift the callers in the closed libraries from disasm (`PacketCrypt` LG 0x4cc60-0x4da60, `BloodCert`/`CertDec`/`SSN`/`NIC` LG 0x4bf70-0x4ca10). LG +36: the callees in BloodCrypto get a caller and pair.
- Worked: `#pragma comment(linker, "/INCLUDE:<IsValid>")` under `LIFT_EXE_LG/SCD/POD` keeps an uncalled closed-lib object, as the original does (the lib object is linked whole). SCD +26, POD +26, LG +2. CG has no such object.
- Fact: the original BloodCert functions have no PDB symbol. Ours are ONLY-OURS. This does not change the MATCH count.
- Worked: PDB signature `BigInteger::Set(int,uchar const*,int)` with param 1 = sign and all callers give 1. LTCG removes the param as in the original. MATCH in LG, SCD, POD (+1 each).
  Read a removed param in the PDB mangled name before you write `LIFT:` for it.
- Worked: `noinline` on `CryptoKey::Initialize` under `LIFT_EXE_LG/SCD/POD` (+1 each). Did not work without the guard: CG loses `Network::Initialize` (CG original inlines it).
- Worked: `noinline` under `LIFT_EXE_LG` on `Crypto::InstanceSize`, `RsaPrivate::RsaPrivate`, `BigInteger::IsPrime`, `Session::completeHandshake`: 4 orig-only go to paired, LG +1 MATCH (IsPrime DIFF 82, completeHandshake DIFF 56).
- Final measure (gate ok, parity ok): CG 421, LG 574, SCD 540, POD 620. Crypto orig-only: 0 in each exe.

## inline-3 notes (stage 1, 2026-11-18, not yet sorted by the review)
- Worktree setup: copy `vendor/zstd/src` from the main checkout, then `git fetch --shallow-since=2018-05-01 origin dev; git checkout bb6eaf64`
  inside it. Set `LIFT_IDA_DIR`. Baseline before inline-3: CG 421/491, LG 574/739, SCD 540/669, POD 620/759 (gate ok, parity ok).
- Quick loop for one exe (about 45 s): `tools/vs2010/build.sh <EXE>`, then `funcdiff.py <EXE> --build build-vs2010 --json x.json`, then compare with the
  `build-vs2010/<EXE>.funcdiff.json` of the last parity run (copy it first: parity.sh overwrites it).
- Disassemble one function of the original or ours with capstone: import `funcdiff.Image` (never name the script `dis.py`: it shadows the stdlib `dis`).
- `Log::Initialize` (CG 0x9da0): our `Log::Log` was a call (`private` in-class ctor not inlined). `__forceinline` on it gives the inline stores.
  The original has `memset(mediaList, 0, 88)` as a call and 44 bytes of `mediaCountPerList` as inline stores. Source: two `memset` calls
  in the ctor, not a `for` loop (our loop became a rolled loop). Score 84.1 -> 93.0 in CG, still DIFF (see progress note).
- Worked (stage 2): `Log::Log` counts as 11 explicit stores `mediaCountPerList[0..10] = 0;` plus one `memset(mediaList, 0, 88)`. A second `memset` gave an extra call; a `for` loop gave a rolled loop.
  `Log::Initialize` MATCH in CG, LG, SCD, POD (+1 each, no loss). Together with `__forceinline` on `Log()`.
- Worked: `wchar_t buffer[40] = L"{";` in `String::GetId128FromGuidString` (CG 0xdd90). The compiler emits the `memset` call for the rest of the array, as the original does. MATCH in CG (+1). LG, SCD, POD not measured yet.
- Worked: `__declspec(noinline)` on `InitSymbol` (CrashHandler.cpp, orig 0x7de0). Without it, VS2010 LTCG hoists `LoadLibraryW(L"dbghelp.dll")` out of `InitSymbol` into the 4 call sites in `CrashHandler::handleCrash`. MATCH in CG (+1). Other exes not measured yet.
- Did not work: `WinServiceConsole::UninstallService` (CG 0x17f00, orig has 5 `CloseServiceHandle` calls, ours 4). VS2010 tail-merges the OpenService-fail path (`Close(manager); return false`) into the DeleteService-fail pair.
  Swapping the `if (DeleteService)` branches made it worse (score 95.1). Source is back to the original form. Cause class: compiler tail merge (cross-jump). Not fixed.
- Did not work: `PipeConsole::SetInvalidInfo` (CG 0x15d90, orig 2 `addNode` call sites, ours 1). Orig has the search loop twice (one per `isInvalid` branch) and `addNode` at two places
  (list end, and `node == nullptr` after a match). Three source forms tried: loop split per branch; `node == &tail || node == nullptr`; `goto` form like the pseudocode. VS2010 merges the calls each time. Source is back to the original form.
- Fact: `Network::OpenPort` (CG 0xd2c0): orig CG has 3 separate crash sequences (lines 170, 175, 177) inline. Ours has fewer `Log::Write`/`AlertSender::Write`/`MakeCrash` calls.
  Orig test for line 175 in CG is `purpose != 1 && purpose != 2`. Ours uses `initialMode < 0 || initialMode > 3` (❓ in the source). The macro is `NETWORK_ASSERT_CRASH` in `Network.cpp`. Not changed yet.
- Fact: `PacketBuffer::Compose` (CG): orig has 2 more `memcpy` calls than ours. `Session::HandleEvent` (CG): ours has one extra `Log::Write` and one extra `L"source\Session.cpp"` ref. Not looked at in the source yet.

### inline-3 stage 3 notes (2026-11-18)
- Worked (LG +6 MATCH, `LobbyD::Send*` x6): remove each explicit `packet.Clear()` (dtor clears; A14) and write the Packet ctor inline:
  `Packet packet; packet.Splitter = nullptr; packet.IsFragmentPacket = false; memset(&packet.FragmentPacketCmd, 0, 28);`.
  `Packet packet = {};` gives a `memset` call over the whole struct that the original does not have. `failCompose` has no `Clear` now.
- Worked: stage 2 changes (Log, StringUtil, CrashHandler) lose no MATCH in the 4 exes (CG 424, LG 577 before the Send* fix, SCD 543, POD 623).
- Did not work: `Network::OpenPort` CG form `initialMode != 1 && initialMode != 2` under `LIFT_EXE_CG`: score stays 90.8. The compiler drops the
  `id == 0` check (callers pass the constants 1 and 2); the original keeps it (orig line 170). Cause: constant propagation. Reverted.
- Did not work: `PacketBuffer::Compose` case `P` with `p` updated before the `memcpy`: memcpy calls 2 (orig 3) but the crash tails split (score 96.3 -> 93.0). Reverted.
  Cause: VS2010 merges the identical `memcpy` tails of cases K, P, s.
- `Session::HandleEvent` 0xf1c0: still one extra `Log::Write` (98.5). Not touched in stage 3.
- Worked (score only, no new MATCH): LG `findDisconnectedNode` and `clearDisconnectedInfo` (`LobbyDChannel.cpp`) as `__forceinline` with an inline 20-character compare loop (orig: `repe cmpsw`, 0x9310, 0x94c0).
  `LobbyDSessionHandler::OnConnect` 82.7 -> 94.4 (calls and refs 100); `OnClose` calls 100. Left: consts `0x2` (loop step) and `0x278` in ours only; the `L""` ref (`??_C@_11LOCGONAA`) is not in ours. `LobbyD::Hello` 92.1 -> 91.5 (still DIFF).
- Did not work: POD `TextStreamPacketBufferHandler::Destroy` (0x2c4a0): `Buffer.GrowingBuffer::~GrowingBuffer()` for `this->~TextStream...()`. Still one extra `<indirect>` (score 93.3). Not understood.
- Fact: POD `RelayContext::Process*` (0x1bb30, 0x1c090, ...): ours calls `AutoCS::Leave` and the Lock.h assert tail (`Log::Write`, `AlertSender::Write`, `MakeCrash`) more often than the original. The original inlines `AutoCS::Leave` with fewer assert copies. Not changed.

### inline-3 stage 5 notes (2026-11-18)
- Worked (POD +3 MATCH: `RelayContext::ProcessRelayRequest/Response/Timeout`): the original has the `AutoCS` dtor inline at scope end (one Lock.h line-122 assert tail per exit).
  Write the `AutoCS` in a `{ }` scope block and remove each explicit `lock.Leave()`. An explicit `Leave()` plus the dtor gives two assert tails per exit (A14 form for `AutoCS`).
  For the failure path that works after the lock: set a flag in the scope, `return true` inside the scope, and run the failure code after the scope.
- Worked: read `PostOfficeDaemon::_instance->` at each use. A cached local `daemon` merged the global loads; the original reloads it (2 more refs). Request went 99.5 -> MATCH.
- Did not work, reverted: POD `TextStreamPacketBufferHandler::Destroy` with `Buffer.GrowingBuffer::~GrowingBuffer()`. No score change.
- Not fixed: `Network::OpenPort` (CG, 2 overloads): per-exe purpose test and constant propagation; belongs to perexe-3.

## lift-parity-order-3 (stage 1, in progress)
- Fact: a lift helper in an anonymous namespace that the orig inlines shows as ONLY-OURS and its refs/consts are missing in the caller (`initMemorySection` in `BloodDaemonMain`, 133 bytes in all 4 exes). Fix form: `__forceinline` (A10).
- Warning: `__forceinline` on that helper also inlines the callee (`Memory::CreateManager` became `HeapCreate`): CG -1 MATCH. Add `noinline` on the callee when the orig calls it out of line. Check all 4 exes.
- Fact: `int const CONFIG_DIR_OPTION_LEN` folds into the code. The orig reads it from memory (2 refs). Use a non-const `int` and `extern int` in `Daemon.h`.
- Tool note: `funcdiff.py --show` prints 1 line of context. For the whole call list use a copy of the script with a larger `n` in `difflib.unified_diff` (do not edit `tools/funcdiff.py` outside a tooling card).

## lift-parity-order-3 (CacheGate only measured, 424 -> 427)

Worked:
- `__forceinline` on a helper that the orig inlines (`initMemorySection`) also inlines its callees. Add `__declspec(noinline)` on the callee the orig calls out of line (`Memory::CreateManager`). Without it CG lost 1 MATCH.
- WPO folds a global with a constant initializer, even when it is not `const`. The orig reads `CONFIG_DIR_OPTION_LEN` from memory. `volatile int` keeps the read (2 refs). Plain non-const `int` did not.
- `BloodDaemonMain`: `if (GetConsoleWindow() == nullptr) { RunMode = DAEMON_MODE; } else { ...loop... }` and one shared tail `makeConsole` + `Daemon::Start`. This puts the DAEMON path first, as in the orig. A duplicate tail (early `return` in the DAEMON branch) gave an extra `makeConsole`/`Start` call: do not use it.
- `makeConsole`: `switch (RunMode)` with `case DAEMON_MODE`, `TEXT_MODE`, `WINDOW_MODE`, `default` (error). The `if` chains in two orders did not match. The switch gives the orig block order.
- `LogFile::writeFile`: first `CreateFileW` before the retry; retry as `do { Sleep; CreateFileW; if ok goto opened; } while (++tries < 100);` then the error code, then `return`; label `opened:` after. A `while (true)` loop with the error inside was worse (the compiler unrolled one more `Sleep`/`CreateFileW`).

Not worked / open:
- `PipeConsole::run` 0x157b0 (score 96.3): `switch (pipe.dwState)` for the `GetOverlappedResult` result, and `reconnect:` label moved after case 2, did not change the call order. Orig order: Log(567), GetLastError, Log(538), Log(500), ..., `disconnectAndReconnect` after the `ReadFile` `GetLastError`, then Log(639). Ours has an extra Log before `GetLastError` and `disconnectAndReconnect` too early. Not solved.
- Not read yet: `Daemon::start` (orig calls `noTimerMain` before `timerMain`; one `Memory::_Manager` ref less in ours), `DaemonConfig::Load` (orig calls the `<indirect>` + `Sleep` after `FreeLibrary`), `BnsCommonConfig::LoadBnsCommonConfig` (orig `Log::Write` before `CheckMinMaxBoundary`; ours reads `BnsCommonConfig::Config` one more time).

## lift-parity-order-3 (stage 3, CacheGate measured 424 -> 430, all 4 exes +3 before these edits)
Worked:
- `Daemon::start` 0xb140: swap `if (GetTimerInterval() != 0) timerMain else noTimerMain` to `== 0` first. Call order then matches.
- `finiMemorySection` (inlined in `Daemon::start`): read `Memory::_Manager[section]` again after the destructor call (volatile global, the binary reads it again for `Free`). This removes the missing `Memory::_Manager` ref.
- `DaemonConfig::Load` 0xc600: the binary puts the `LoadLibraryW` failure block last. Use `if (module != nullptr) { body } else { fail }`. A `goto` over initialised locals is not legal C++.
- `BnsCommonConfig::LoadBnsCommonConfig` 0x13e0: write each error exit with its own `Config = nullptr; Log::Write(...)`. The compiler merges the tail and places it after the first error block. A hand-written `goto failed` tail (before or after the blocks) did NOT match. Also keep the allocated object in a local (`config`) and test the local: it removes one `BnsCommonConfig::Config` read.
Not done:
- `PipeConsole::run` 0x157b0: 3 tries used, no gain. Stop.
- SCD `DChannelMgr::SetupDaemonList` (82.8: AddDaemon / GetAddressStringW order, `DaemonChannel.cpp` string ref, consts 0x38 0x178), `Channel::MakeSession` (Log::Write order, consts 0x17 0x24), `GameEventManager::PostGameEventLogList` (Log::Write order, orig refs ID128_GUID_ZERO, ours `GameEventManager::Instance`): diffs seen only, no edit tried.

## lift-parity-order-3, stage 4 (SCD exe-only call order)

- Worked (partial): `DChannelMgr::SetupDaemonList` 0xd270. Source order must follow the original block order:
  `if (second != nullptr)` first (GetSession, error log, `goto release`, then the "changed" path), `else` alloc path last,
  one shared `Log::Write(LT_NOTICE, ..., line, fmt, wid, address, port)` after both. Calls now match (score 82.8 -> 96.3).
  Left: ref order (vtable before file string) and const 0x178 (line number of the inlined FindDaemon addReferenceCount). Not MATCH.
- Did not work: `Channel::MakeSession` 0x10450, port-first order (`if (port != nullptr) { ... } ` then the "cannot find port" log last). Measured with the wrapper objects rebuilt: CG, LG and POD lose MATCH (score 90.5 / 90.5 / 88.6) and SCD stays DIFF. Undone. The shared form (early `return false` for `port == nullptr`) stays.
- `touch` rule: the parity build tracks `.cpp` files only (see vs2010-build-header-deps). An `#include "X.cpp"` wrapper needs its own touch.
- Worked: SCD `GameEventManager::PostGameEventLogList` 0xb140 (MATCH). (1) Read `Instance->_gameEventHandle` one time into a local `gameEventHandle`, test the local; the "handle is null" `Log::Write` is then the last block. (2) Hex-Rays folds reads of zero-initialised data (`ID128_GUID_ZERO`) to `0`: when funcdiff shows an orig ref to a global that the pseudocode shows as constant zero, write the global in the inlined constructor (`_gameAccountId(ID128_GUID_ZERO)` in `GameEventLogEvent::GameEventLogEvent`).
- POD `UnsentPostContextManager::initContextManager` 0xc6d0 / `updateWorldList` 0xcae0 (seen only, no edit): in the binary the "return true" Leave tail (assert 122 + Leave) is the LAST call block; ours has it right after the `addUnsentPostContextList` call (loop-exit position). The RAII form `AutoCS` does not help: the original has no `~AutoCS` call (comment in `UnsentPostContext.cpp`). Next try: put the success tail after the error blocks (`goto`, or a `for` with the exit moved).
- POD `UnsentPostContextManager::addUnsentPostContextList` 0xce80: only const `-2` (EH state) differs: toolchain cause, see the `Port::Initialize` line above. `deliverUnsentPost` 0xd510: `removeReferenceCount` order differs, not looked at.
- Did not work: `Channel::MakeSession` port-first order (see stage 4 note above): measured and undone.

## lift-parity-order-3, stage 6 (final)
- Full run after all edits: CG 430, LG 588, SCD 550, POD 631 (baseline 424 / 583 / 543 / 626). MATCH lost: 0. Gate ok, parity ok.
- Did not work: POD `UnsentPostContextManager::initContextManager` 0xc6d0, `for (;; ++it) { if (it == end) goto success; ... } success: Leave; return true;`. The compiler gives the same block order (success tail after the loop exit). Undone. The note about this try also holds for `updateWorldList` 0xcae0 (same shape, not tried).

## lift-parity-consts-3, stage 1
- Quick CG measure (`.scratch/q.sh CacheGate`): 430 -> 434. New MATCH: `PacketBufferAllocator::initAllocator` 0x12b10, `Session::Accept` 0xe7c0, `Session::recv` 0xf0d0, `TrustedPacketBufferHandler::ToPacket` 0x11e90. LG, SCD and POD are not measured yet.
- Worked, `initAllocator`: `x = mem ? new (mem) T(...) : nullptr` with an init-list ctor moves or duplicates the stores. Use plain placement new and a ctor that assigns in the body, so that `InitializeCriticalSection` (member ctor) comes before the stores.
- Did not work, `Network::Network` 0xcdb0: the same placement-new change for `EndEventObject` gives no change (still 2 stores, orig has 1 merged store).
- Worked, `Session::Accept`: the orig reads the members (`_port->_sessionHandler`, `_id`), not the params. The idle block is one `SetBusyWithPos(id).pos` call (union `IdleStateTable::Pos` from the PDB).
- Worked, `Session::recv`: take a pointer-to-context local before the stores. Put the failure block (`!AsyncRecv` -> log, return false) first.
- Worked, `ToPacket`: no short local for the header size. Read `*size` through a `short const*` two times. A short local gives a range check with const 0xf9e.
- Build fact: the `.dep` files of `tools/vs2010/build.sh` list only headers in `BloodLib/include/`. An edit of a header in `BloodLib/source/` (for example `IdleWatcher.h`) does not rebuild. Touch the `.cpp` files.
- Not fixable here (stop list): TLS offsets in `Daemon::setAddress`, `Network::GetAddressStringW`, `Network::initWorkerThread`; const 0x80 in `Daemon::Start` (`ThreadManager::Initialize(128)` is constant-propagated); ICF vtable name in `Session::initialize` (`SessionRecvBuffer` vs `CrashHandler`); ICF name in `WindowConsole::Open`.
- `Session::HandleFailedEvent` 0xf5d0 is still DIFF. Cause: ours keeps `&_lock.CS` in rsi; orig computes `+0x18` again at each use and keeps `removed` in esi. Also ours reads the id with a 64-bit `mov rax`; orig uses `mov r8`, then `r9d = r8d >> 2`.

## lift-parity-consts-3, stage 2
- Measured with `.scratch/q.sh` on all 4 exes: CG 430 -> 434, LG 589 -> 593, SCD 550 -> 554, POD 631 -> 635. The same 4 functions are MATCH in each exe. No exe lost a MATCH.
- `Network::Network` placement-new edit reverted. `makeIdleStatePos` in Session.cpp removed (no caller).
- Did not work, `Session::HandleFailedEvent`: `_lock.Enter()` / `_lock.Leave()` in place of `EnterCriticalSection(&_lock.CS)` gives the same code. `static_cast<short>(id) & 3` in place of `static_cast<short>(id & 3)` in `SetNotAvailable` gives the same code. Both reverted.
- Cause found, not fixed: `Session::Session(unsigned, PacketBufferHandler const*)` and `StaticPageMemoryManager::Initialize(page,size,allocated,additional)` (CG 0x1a1a0). The only caller is the Session ctor. Orig LTCG folds `size` 2048 and `allocated` 584 into the callee, but still passes `&BaseMemoryManager::_Instance` in r8. Ours folds the address too. No source change is known that stops the address fold.
- `SysInfo::Hostname` CG 0x14390: orig keeps a 16-byte `sockaddr_in` on the stack (frame 0x600, ours 0x5f0). Stores: 0 (2 qwords), sin_addr, sin_family 2, then sin_port = htons(0). `memset` + this store order alone does not keep the struct (frame still 0x5f0). Orig puts the '.' loop on the fall-through path after `test edi,edi; jne`.
- `SysInfo::IpAddress` CG 0x144f0: orig tests `address == nullptr` before it reads `*count`; ours reads `*count` first (movsxd before the test). Orig uses r11 frame (`mov r11, rsp`). Call order differs: orig calls gethostname and WSACleanup before malloc.

## lift-parity-consts-3, stage 3
- Worked, `SysInfo::IpAddress` CG 0x144f0 (91.7 -> MATCH): (1) the adapter retry loop in the MS sample form `do { malloc; if null break; result = GetAdaptersAddresses(...); if (result != ERROR_BUFFER_OVERFLOW) break; free; p = nullptr; ++retry; } while (result == ERROR_BUFFER_OVERFLOW && retry < 3);`. The `for (;;)` form rotates the loop and calls `malloc` two times. (2) `if (hostname == nullptr) { if (gethostname(...) == 0) {...return 5;} } else { WideCharToMultiByte }`. The `if (hostname != nullptr) ... else if (gethostname...)` form moves the gethostname block to the end.
- Worked, `SysInfo::Hostname` CG 0x14390 (95.8 -> MATCH): `sockaddr addr; memset; sockaddr_in* in = reinterpret_cast<sockaddr_in*>(&addr);` stores through `in` keep the struct on the stack (frame 0x600). Body in `if (hostname != nullptr) { ... return result; } return 3;`. Tail: `if (result == 0) { '.' loop } else { inet_ntoa ... }`. The consts 0x3/0x4 came from the block order (`lea eax,[rsi+3]` against `[rsi+4]`).
- Cause found, `Port::Initialize` EH state -2: orig has `RefCntObject::operator delete(void*, wchar_t const*, int)` (CG 0x20f0, crash log line 0x8b). So orig creates `SessionPool` (derives `BaseRefCntObj`) with a class `operator new(size_t, wchar_t const*, int)` and the matching delete gives the EH region. Ours uses `Alloc` + plain placement new. Not yet tried.

## lift-parity-consts-3, stage 4
- Measured `SysInfo::Hostname` and `SysInfo::IpAddress` on LG, SCD, POD: both MATCH in each exe. Total for the card: LG 589 -> 595, SCD 550 -> 556, POD 631 -> 637, CG 430 -> 436. No exe lost a MATCH.
- Correction to stage 3, `Port::Initialize` EH state -2: the PDB has no `RefCntObject::operator new`. The real cause is the global placement delete. Orig `bloodlib\include\Memory.h:173` defines `operator delete(void* obj, void* buf)` with a crash body ("== CRASH == [memory], DO NOT USE THIS DEL OPERATOR", CG 0x1000). The body is not empty, so VS2010 keeps an unwind state (frame marker -2) for each `new (memory) T(...)` where the ctor of T is a call. Our `include/vs2010/new` (and the VS2010 `<new>`) has an empty inline body, so cl removes the state.
- Fix not applied: the fix is global (Memory.h must define `__PLACEMENT_NEW_INLINE` and the crash-body placement new/delete before `<new>`). It changes each placement-new site in all exes. Do it in a separate card and measure all 4 exes.

## lift-parity-arraynew-3, stage 1 (2026-11-18)
- Start measure (this worktree, same as baseline): CG 436, LG 595, SCD 556, POD 637, shared 465/546.
- Worked, LG `Client.cpp` (LG only measured, +4 MATCH, 595 -> 599): the scd-2 pattern of A16. `#define __PLACEMENT_VEC_NEW_INLINE` before all includes; own
  `operator new[](size_t, void*) throw()`, `operator delete[](void*, void*)` (Memory.h:181 crash Log + Alert, lower case LG path), `inline operator delete[](void* p) { __delv_buf__ = p; }`,
  `__declspec(thread) void* __delv_buf__`. Macro `liftArrayNew1(T, n, line)` = `new (Memory::_Manager[1]->Alloc(sizeof(T)*n+8, L"Client.cpp", line)) T[n]`.
  Delete form: `delete[] p; Memory::_Manager[1]->Free(__delv_buf__, L"Client.cpp", line);`.
  New MATCH: `GateKeyManager::Initialize` 0x3910 (32.6 -> 100), `ClientManager::Initialize` 0x5b90 (30.2 -> 100), `operator delete[]` 0x37a0 (was orig-only), `CriticalSection::CriticalSection` 0x3780 (was orig-only; the vec ctor needs the real function).
- Open after the change: `GateKeyManager::Finalize` 0x3b10 (97.0) and `ClientManager::Finalize` 0x5cf0 (95.2). Only diff: const 0x18 (orig) against 0x10 (ours). The orig HR reads `ThreadLocalStoragePointer[0] + 24` for `__delv_buf__`;
  ours has the TLS slot at +0x10. This is the TLS layout (the same cause as in the scd-2 note "__delv_buf__ shared TLS layout differs"). Not fixed.
- Not touched: `ClientManager::broadcast` 0x6410 (76.9: calls 81, consts 77, refs 73). Orig HR: the push_back is inlined with the `reserve`/`_Xlength_error` growth path twice (aliasing test `p_second >= Mylast || Myfirst > p_second`),
  `clients.clear()` is `memmove(Myfirst, Mylast, 0)`, and the vector buffer Free call has a 5th arg -2 (EH state/const). Not compared with ours yet.
- Not touched: scalar placement `operator delete(void*, void*)` (LG `??3@YAXPEAX0@Z` DIFF 0; CG, SCD, POD DIFF 0). See D section; fix is global (Memory.h crash-body placement delete, see consts-3 stage 4).
- Build fact: in a new worktree `tools/parity.sh` can build the 4 exes but leave no `build-vs2010/<EXE>.funcdiff.*` files. Run funcdiff by hand with `.scratch/fd.sh [EXE]`
  (`uv run -q --no-project --with capstone --with pefile python tools/funcdiff.py <EXE> --build build-vs2010 --json build-vs2010/<EXE>.funcdiff.json --worst 0 > build-vs2010/<EXE>.funcdiff.txt`). `LIFT_IDA_DIR` must be set.
- Setup fact: `vendor/zstd/src` copied from the main checkout is at 90ae502; `git fetch --shallow-since=2018-05-01 origin dev; git checkout bb6eaf64` inside it worked.

## lift-parity-arraynew-3, stage 2 (2026-11-18)
- Worked, LG `ClientManager::broadcast` 0x6410 (76.9 -> MATCH): `__declspec(noinline)` on `Session::send` (`BloodLib/source/Session.cpp`, 0xFE90). VS2010 /LTCG inlined `send` (WSASend, 3 Log::Write) into `broadcast`; the orig calls LG 0x19360. Measured: LG 599 -> 600, CG 436, SCD 556, POD 637 (no change). Run on all 4 exes: no MATCH lost.
- Did not work, LG `ClientManager::BroadcastAnnounceNotify` 0x62c0 (95.8): swapping the `Compose` branches (success first, as in the HR) gave no change. Diff: orig `Log::Write` before `ClientManager::broadcast` in address order, ours has 2 `Packet::Clear` (tail duplicate). It is block layout. Source reverted.
- Stop list, `GateKeyManager::Finalize` 0x3b10 (97.0) and `ClientManager::Finalize` 0x5cf0 (95.2): const 0x18 against 0x10 = `.tls` offset of `__delv_buf__`. Orig `.tls` raw data 0xa1 bytes, ours 0xb1 bytes: other TLS variables sit before it in orig (link order). Not fixable in source.
- `GateKeyManager::MakeGateKey` 0x? (94.3): orig calls `GateKeyEntry::scalar deleting destructor` where ours calls `RefCntObject::removeReferenceCount`, and the order of `LeaveCriticalSection` differs. Not tried.
- Facts for the scalar placement `operator delete(void*, void*)` (all 4 exes, score 0): LG orig 0x1000 (first function in the exe, PDB module ThreadFreePacketPump), crash body at `Memory.h:173`, Log::Write + AlertSender::Write, path lower case in LG (`e:\dailybuild02\lobbygate-common-0.0.348\depot\branch\348nc\program\server\bloodlib\include\memory.h`), mixed case in SCD (`E:\DailyBuild02\SmartCouponDaemon-Common-0.0.348\depot\Branch\348NC\Program\Server\BloodLib\include\Memory.h`). `include/vs2010/new` has an empty inline placement delete. Plan: declare it non-inline in `include/vs2010/new`, define the crash body once per exe (per-exe path with `LIFT_EXE_*`) in `BloodLib/source/Memory.cpp`. Not tried: it is global. The `bloodlib-2` card lists `operator delete` on its stop list.

## lift-parity-handlers-3, stage 2 (2026-11-18, PacketHandler form)
- WORKED: POD `WorldSessionHandler::PacketHandler` 0x1f270 is MATCH (POD 637 -> 638). Form, all parts needed:
  1. `void* iocpHandle = nullptr;` at the top, then `iocpHandle = Network::iocpHandle();` inside the pump branch (a zero register that stays alive: the range test stays 2 signed compares, const 0xd).
  2. `short const* const pCmd = &packet->CurHeader[1].size; if (pCmd == nullptr)` (orig `add rsi, 2` + ZF; the `CurHeader == nullptr` form and the `== -2` form are wrong). Read `*pCmd` at each use (orig reloads it after each call). Use `session->_id` at each use, no `sessionId` local (orig loads `[rdx+0x68]` in each block).
  3. Inline `Session::GetChannel` by hand: `T* channel = nullptr; if (session->_channel != nullptr && !session->_waitForRelease) { session->_channel->addReferenceCount(SESSION_FILE, 1051); channel = static_cast<T*>(session->_channel); }`.
  4. `bool result = false;` AFTER the GetChannel block, then `if (channel == nullptr) { if (*pCmd == 1 && list[1] != nullptr) result = list[1](session, packet); else Log; } else { if (range ok) result = TFPP_PumpPacket(...); else Log; channel->removeReferenceCount(...); } return result;` (one return, no early return after the CurHeader test).
  The `GetChannel()` call and the positive-first `if (channel != nullptr)` did not change the block order alone. Build time for one exe: about 30 s (`.scratch/try.sh <EXE> <regex> <file>`).
- Same signal (consts orig 0x2 + 0x7/0xa, ours 0x5/0x8; calls orig `<indirect>, Log::Write` after addRef) in POD `AgentSessionHandler` (list size 7), POD `CacheGateSessionHandler` (no channel; consts 0x2, 0xa), SCD `ManagerSessionHandler`. The CG/SCD form has no GetChannel: only fix 1 and 2 apply there.
- POD `ManagementSessionHandler::PacketHandler`: calls only. Ours has 2 extra `<indirect>` (before `Log::Write`, before `Packet::ComposeText`) and `Packet::Clear` where orig has `<indirect>`. Not worked on.

## lift-parity-handlers-3, stage 3 (session handlers)
- Worked (MATCH): the PacketHandler form of stage 2 for POD `AgentSessionHandler::PacketHandler` 0x3a00 (needs `SESSION_FILE`), POD `CacheGateSessionHandler::PacketHandler` 0x7d90, SCD `ManagerSessionHandler::PacketHandler` 0xe980, LG `ClientSessionHandler::PacketHandler` 0x6b70.
  The form: `short const* const pCmd = &packet->CurHeader[1].size;`, test `pCmd == nullptr`, read `*pCmd` each time, no `sessionId` local. Use `session->_id` in each Log::Write.
- SCD 0xe980: `Session::GetChannel` is a real call (not inline). One `bool result = false;` and one `return result;`. `channel == nullptr` first (cmd 1 then list[1]), else the list call and `removeReferenceCount(..., 101)`.
- LG 0x6b70: the list tests are signed: `*pCmd >= 0 && *pCmd < 0x6E` (Any list), `*pCmd >= 0 && *pCmd <= 0x6E` (Authed, NotAuthed). Do not use `unsigned short`. Inline GetChannel add-ref, then `Client* client = session->_channel` and `client->_state == 1` inside the same `if`. The NotAuthed code follows after it.
- Worked (partly): POD `ManagementSessionHandler::PacketHandler` 0x10d00: set the Packet fields one by one (`CurHeader`, `Splitter`, `ListHead`, `ListTail`, `IsFragmentPacket`, `FragmentPacketCmd`) instead of `memset`, and drop the explicit `reply.Clear()`. This removes the extra `Packet::Clear` and one `<indirect>` (Splitter test). Score 97.8.
- Did NOT work (POD 0x10d00): `int line = 61; if (index != 16) line = 68;` (adds const 0x3d). A `goto done` with `result = handler(...)` (no change). Open: orig puts the handler call (`call r8`) at the END of the function, after `Packet::Clear`. Ours puts it before the first `Log::Write`.
- Open: POD pool index in the inlined `Packet::Allocate` is 0x28 in orig and 0x90 in ours (`mov edx, ...` before `PacketBufferPool::allocate`). Not checked if it is the same in the MATCH functions.

## Handlers stage 4 (lift-parity-handlers-3)

Measured with `.scratch/try.sh PostOfficeDaemon <regex> <file>`. Result: POD 645 (was 640).

Worked:
- Local `Packet reply` with the packet init written field by field (CurHeader, Splitter, ListHead, ListTail,
  IsFragmentPacket, FragmentPacketCmd) and then `Allocate()`. Do not use `memset`. A `memset` adds an
  `<indirect>` call in the call list. File: `ManagementPacketHandler.cpp` `initReply`.
- Do not write `reply.Clear()` by hand. The destructor does it. A hand `Clear()` before a `return`
  gives a second `Packet::Clear` call. (HelloReq 97.0 -> MATCH.)
- Branch order in the management handlers: the failure branch comes first, the success branch last.
  Write `if (DecomposeText(...) == 0) { fail } else { ... if (!DbCall(...)) { fail } else { success; return true; } }`
  and then the common failure tail. Do not write `if (call) { success; return } fail`.
  (ResetAll 96.3 -> MATCH, LoadRetryReadyPostList, ResetPostStatus, LoadRetryReadySinglePost: all MATCH.)

Did not work:
- `goto done` with `bool result` instead of `return handler(...)` in
  `ManagementSessionHandler::PacketHandler` (0x10d00). No gain. Reverted.
- `HandleCacheGateRelay` (0x8070): `if (Decompose != 0)` first with `serviceWid == toWid` first gave 89.1
  (worse than 92.8). `== 0` first with `!=` first and explicit `endLine = 109` per branch gave 93.3.
  The orig has the Write(86) decompose failure block AFTER the success block (const order 73, 89, ..., 86).
  The version `!= 0` first with `serviceWid != toWid` first is written in the file and NOT measured.

Open facts:
- `HandleCacheGateRelayFail`/`RelayInvalid` (POD): the orig has three `RelayContext::ProcessRelayResponse`
  calls (one per relay request type, 3 vtable refs of CheckPostCapacityRelayRequest). Our code has one.
  Needs a switch with three inlined branches. Not tried.
