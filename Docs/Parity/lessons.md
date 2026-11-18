# Parity lessons

Cleaned in lift-parity-review-1 (2026-11-18). Equal patterns are merged. The list is sorted by the number of functions
fixed (sum over the 4 exes; a shared function counts once per exe). Old numbers are in brackets: (P11) = old Pattern 11.
Each new card adds its patterns at the end of section A or B. The next review sorts them again.

## A. Patterns that worked

### A1. Funcdiff noise fixes (tool, lift-parity-0): 396
- Branch targets counted as constants, jump tables read as code, calls through a slot with no symbol, `__chkstk` frame
  size. Proof of each in `noise.md`. CG +77, LG +97, SCD +109, POD +113.
- Rule: fix a tool error before a source change. A tool error hides real progress and makes good changes look bad (see C1).

### A2. Third-party code: vendor the exact upstream commit (P18): 73
- zstd: upstream `dev` commit bb6eaf64 (2018-05), not v1.3.5. See `vendor/zstd/README.md`. CG +16, LG +25, SCD +12, POD +20.
- Method: count the calls of one function on both sides (for example `ZSTD_litLengthContribution`) and bisect the commits.

### A3. `__declspec(noinline)` on a function that the original calls from its only caller (P11, P19, P24, P48): 53+
- Cause: our LTCG build inlines a small function. The function is a miss and its caller is a DIFF.
- Use it only when the original never inlines the function (check all callers in all exes). Mark it `// LIFT:`.
- Examples: `WinServiceConsole::reportStatusToSCManager` 0x17a20; `Session::Recv`, `SessionSendBuffer::clearPacketBufferList`,
  `PortListener::Clear`; `AlertSender::createSocket`, `LogMedia::Add`, `DbTransaction::close`; PipeConsole `connectPipe`,
  `disconnectAndReconnect`, `addNode`; POD `convertFailReason` x2, `CachedWatchdog::CachedWatchdog` 0x3d20,
  `AttachedItemContext::operator=`, `composeRelayHeader(FragmentPacket&)`, `combineFragmentRelayFormat` (POD +17).
- LTCG also moves a callee null check into the callers. noinline keeps it in the callee
  (SCD `DbTransaction::BindParam` 0x20fd0, the 10 callers score +1.3 to +3.8).
- Side effect: a caller can change its inline choice. Example: SCD `NPServiceChannelManager::OnConnect` inlined
  `SetInvalidInfo` after `addNode` became noinline. Check the callers of the changed function.
- Opposite form (P32): `__forceinline` on an in-class ctor that the original never emits (`CacheD::CacheD`).
- (noinline-2) A noinline function that no source code calls is removed by the linker. It stays orig-only.
  Check the orig xrefs in IDA when Hex-Rays shows no caller: Hex-Rays can drop calls.
  LG `LobbyGate::initialize` 0x12e70 calls `LobbyGateConfig::Dump` 0x13086, `BnsCommonConfig::Dump` 0x1308b and
  `ContentsRuleConfig::Dump` 0x13090 after `fclose`. The pseudocode has none of them. Three calls added: LG 528 MATCH (+6).
  `LobbyGateConfig::Dump` must be `const` (mangled `QEBAXXZ`).
- (noinline-2) funcdiff pairs by mangled name. A name pairs by PDB name only when it is unique on both sides.
  An overload with another signature does not pair. Open cases: SCD `Network::OpenPort` 0x1a8b0 (orig has the 9-arg overload,
  ours calls the 5-arg one); POD `Packet::Decompose` 0x220d0 (orig `QEBAGIHPEBDZZ` = offset, n, format, ...; ours only
  `Decompose(char const*, ...)`, and the 8 `CacheEconomyPacketHandler` handlers call the orig overload with 0x18, 6).
- (noinline-2) `Log::FlushInline` pattern: the orig inlines `Log::Flush` in Daemon and calls it only from CrashHandler.
- (noinline-2) CG, SCD and POD inline `Session::deallocateCrypt` in `~Session`. Our standalone copy (94 B) is ONLY-OURS there.
- (noinline-2) POD `PostOfficeDaemon::initialize` 0x132b0: the block 0x1344a-0x134eb (`wcsncpy` of the Daemon version string,
  `DaemonConfig::Dump` 0x13498, `LoadBnsCommonConfig`, `BnsCommonConfig::Dump`) is dead in the control flow of the orig
  (no path reaches `esi == 0` there). The pseudocode drops it, so `DaemonConfig::Dump` stays orig-only in POD. Not lifted.

### A4. Virtual call on a global object through a base reference (P1): 49
- Cause: `BaseMemoryManager::_Instance.Alloc(...)` binds statically and LTCG inlines `HeapMemoryManager::Alloc`.
  The original calls through the vtable (`<indirect>`).
- Source: macro `BASE_MEMORY_MANAGER` = `static_cast<MemoryManager const&>(BaseMemoryManager::_Instance)` at all 59 sites.
- Example: `BaseRefCntObj::deallocate_me` CG 0x18460: `import:HeapFree` -> MATCH. CG +9, LG +11, SCD +15, POD +14.

### A5. Per-exe path literal of a shared file (P30, P35, P41, P45 cause 1): 45
- Cause: the original builds each shared `.cpp` in each exe project. `__FILE__`-style literals are relative to the
  project (`..\Shared\` in LG/SCD, `..\..\Shared\` in CG/POD) and header paths contain the exe name, with a per-exe
  case (`e:\dailybuild02\<exe>-common-0.0.348\...` or `E:\DailyBuild02\<Exe>-Common-...`).
- Source: the literal is a macro with an `#ifndef` default. A wrapper `.cpp` per exe sets the macro and includes the
  shared `.cpp` (`BnsCommonConfigDefinitionShortPath.cpp`, `RefCntObject<Exe>.cpp`, `MemoryManager<Exe>.cpp`).
  For a header (`StlMemory.h`, `LIFT_STLMEMORY_FILE`) an exe-only `.cpp` defines the macro before the first include.
- Build: `tools/vs2010/build.sh` compiles each source one time and has no per-target define, so a wrapper file is
  necessary. Keep the object order of CG (`LIFT_COMMON_SOURCES`, `lift_common_cg`), else the data layout moves.
- Examples: LG `BnsCommonConfig::Dump`, POD `ThreadFreePacketPump::Initialize`, SCD `RefCntObject::addReferenceCount` 0x6890,
  SCD `NPServiceChannelManager::OnClose`. Gains: s3 +14, lg-1 +26, scd-1 +5.
- paths-2 (worked, CG +1, LG +6, SCD +4, POD +6, no MATCH lost): macros `LIFT_PACKETUTIL_H_PATH` (narrow, CG default),
  `LIFT_CHANNEL_H_FILE` (wide, CG default), `LIFT_FRAGMENTPACKET_PATH` (narrow, `..\..\Packet\` default). Wrappers
  `{Port,Timer,Channel}<Exe>.cpp`, `PacketUtil{LobbyGate,PostOfficeDaemon}.cpp`, `FragmentPacketLobbyGate.cpp`.
  CMake: `LIFT_COMMON_PATH_SOURCES` leave `lift_common`; `lift_common_{lg,scd,pod}` take the wrapper if it exists, else the plain file.
  `LIFT_STLMEMORY_FILE` added to LG `Client.cpp` (upper case), POD `PostOfficeDaemon.cpp`, `WorldConfigManager.cpp`, `LobbyDaemon/ObjectPool.cpp` (SCD).
- VS2010 `cl` gives C2308 for `L"" MACRO`. For a narrow macro that needs a wide twin, use `LIFT_WIDEN(x)` = `L##x` with a 2-step macro.
- Did not work: `__declspec(noinline)` on `RefCntObject::removeReferenceCount` (all 4 exes lose MATCH: CG -2, LG -2, POD -1)
  and on `AutoCS::~AutoCS`/`Leave` (POD loses `CachedWatchdogManager::initWatchdogManager`). The LTCG inline choice moves. Undone.
- Cause of `TimerQueue::~TimerQueue` (DIFF in LG, SCD, POD): the wrapper `Timer<Exe>.obj` has only the exe path. The dtor inlines
  `StlAllocator<Timer*,2>::deallocate` (COMDAT). The /LTCG linker keeps the first copy. Objects of `lift_<exe>` and of `lift_common`
  that come first in the link order have the CG path (their `.obj` has the CG literal). So the CG copy wins.
  Fix (not done): the VS2010 build must give each exe-library source a `-DLIFT_EXE_<X>` and `StlMemory.h` must choose the literal from it.
  `tools/vs2010/build.sh` compiles one object per source path with fixed flags, and `tools/` is outside the files of paths-2.
  A CMake `target_compile_definitions` only changes the clang build, so it has no effect on parity. Tried and undone.
  Shared objects (`Daemon`, `Connection`, `Network`, ...) would also need a wrapper per exe. Expected gain: +3 (one per exe) and some `StlMemory.h` refs.
- Not path causes (inline choice, `noinline` fails): `Lock.h` refs in POD (7 functions), `RefCntObject.h` refs in `LogMedia::Write` and
  `TimerQueue::clearShortTermQueueSlot`, `source\Memory.cpp` refs in `BloodDaemonMain` and `Daemon::start` (the original inlines the
  Memory init and calls `printUsage` before `makeConsole`).

### A6. Branch order follows the original address order (P3, P7, P10, P20, P25, P33, P39): 30
- VS2010 lays out the `if` body first. Write first the branch that is first in the original code.
- The HR condition can be the inverse of the source condition (P33): HR `if (x != 0) A else B` came from source
  `if (x == 0) { B } else { A }` (`CacheDChannel::onConnect` 0x3c80).
- Error path first with an early return when the original has `jg` to the good path (P7, `RefCntObject::addReferenceCount`).
- Good path first, `Log::Write` at the end (P20: `Db::AllocTransaction`, `initEnv`, `Execute`; SCD +6, POD +7).
- Nested success-first `if` for handle chains (P10, `WinServiceConsole::InstallService` 0x17c80).
- `buffer == nullptr` first in `ClientPacketBufferHandler::Clone` 0x21920 (P39).
- Rule: there is no fixed direction. Read the original block order in the disassembly, then try one form and measure.

### A7. Member types exactly as in the PDB: no extra `volatile` (P15): 25+
- Cause: `long volatile _ref` in `RefCntObject.h`. The PDB type is plain `long`. A volatile store is a barrier, so
  VS2010 keeps the dead base ctor stores.
- Example: `PacketBufferPool::allocate` CG 0x128d0 -> MATCH. CG +7, all 4 exes up.
- Rule: check each `volatile` member with `pdbq <EXE> type <Class>`.

### A8. CRT template overloads (P9): 25
- The original calls `swprintf_s<N>` out of line. Source: the 2-argument form with an array destination.
- Use it only when the size argument is the full array size. Clang build: `include/vs2010/crt_cpp_overload.h` under `#if defined(__clang__)`.
- Example: `WinServiceConsole::ServiceMain` 0x177d0. CG +3, LG +7, SCD +2, POD +13.

### A9. Map allocator with a non-const pair key, as in the PDB (P22 cg-1, P38, P44): 18
- Cause: PDB names are `StlAllocator<std::pair<K,V>,2>` (key not const). Ours used `pair<K const,V>`.
- Source: the typedef uses `std::pair<K, V>`. Insert with `std::pair<K, V>(k, v)`, not `value_type(k, v)`.
- Examples: `ClientManager::ReleaseSession` CG 0x6250, LG `ClientManager::RemoveClient` 0x60c0, SCD `JobManager::Clear` 0x6ff0 (SCD +11).
- POD (P47): the same change was undone only because of tool noise (C1). Try again after the tool fix.

### A10. Loop forms that VS2010 compiles as the original (P16, P26, P43): 18
- `for (i = 0; i < 128; ++i) { ...; if (!f(i)) break; } if (i >= 128) return true;` is not unrolled (`PortListener::Initialize` 0x31fd0).
- Count down and step the pointers: `for (; count > 0; --count, ++defList, ++loadDefList)` (BnsCommonConfig, CG +4, POD +4, LG +2, SCD +2).
- Hex dump: walk a byte pointer and write `temp[k++]` three times (SCD `NPChannel::handlePacket` 0x57d0).

### A11. Copy the original refs and reads one to one (P22 s3, P23, P40, P43, P45): 20
- `return _log != nullptr ? _log : L"";` (original refs `L""`): `LogBuffer::GetLog`. Pass the literal `L""`, not a named array.
- Put a new object in a local, store it once, call through the local (`LogBufferAllocator::initAllocator`, `GameEventManager::GameEventManager` 0xaae0).
- One local for a repeated expression keeps the constant (`short logBytes = 2 * logCount`, `AlertSender::writev2`).
- Compare with the global: `id[0] == ID128_GUID_ZERO.id[0]` (SCD `RegisterGameEventLog` 0x10b00); split return tails.
- Member stores in the init list when the original orders them so (`CouponJob`, `EventNotiJob` 0x99f0).
- Log the `GetLastError()` value when the HR shows a second `GetLastError` call (`DChannelMgr::CreateDaemonListXml` 0xd5c0).

### A12. Error blocks and cleanup tails as in the original (P14, P36, lg-1 stage 3, P13 s1): 12
- One full error block per failed call when the original calls `WSAGetLastError` in each (`Network::initializeSocketInterface` 0xda30, `Session::sendNext` 0xfdc0).
- One shared cleanup tail (`goto cleanup;`) when the original has one tail (`TakeGoodsOk` 0x113e0).
- `__try { ... __leave; } __finally { ... }` when the HR shows `$__FINALLY_n` (`ListLobbyServiceItemInfoOk` 0x117a0).
- Early `return true` after each error block, no explicit `p.Clear()` (the dtor clears): `BypassPacket` 0x121d0.

### A13. Compiler-generated destructors (P42, P29, P39): 12
- No user-declared dtor when the original dtor is a thunk with no vtable store (`EventObject`, `DynamicEventObject`; CG +1, LG +1, POD +5, SCD +2).
- An inline dtor with a member dtor gives the EH state of the original (`inline Db::~Db()`, `db->~Db();` in `Db::Clear`).
- Empty body when the member dtor does the work (`FragmentPacket::~FragmentPacket` 0x24e0).

### A14. Allocation forms (P46, P28, P37): 10
- Placement array new: `new (Alloc(sizeof(T)*n+8, file, line)) T[n]` (macro `liftArrayNew`, POD +8).
- Null-checked placement new before the null test: `T* p = mem != nullptr ? new (mem) T() : nullptr; if (p == nullptr) {fail}`.
- Inlined Packet ctor: `Packet packet = {nullptr, false};` then the 4 pool stores (`ClientManager::BroadcastAnnounceNotify`).

### A15. Handler prologue as `static __forceinline`, crash block last (P34): 5
- LobbyD handlers: the helper form `if (ch != nullptr) return ch; Log; Alert; return nullptr;`; `ch->GetId()` in each log call.
- Also found a lift error: `HandleLobbyLobbyGate_HelloFail` did not call `SetEvent`. A parity check finds missing calls.

### A16. Small source forms: 1 or 2 each
- UTF-8 BOM for a file with Korean literals (P13 s2; signal `??_C@_1IA@` against `??_C@_1KI@`).
- `switch` gives dec/dec; `if/else if` gives `cmp 2` (P6, `RefCntHistory::dump`).
- Keep a member pointer in a local before a lock call (P4, `Daemon::setState`).
- Pass the address of the variable, not a copy (P5, `CrashHandler::MakeCrash`).
- One `htonl` for a range test (P8, `Daemon::setAddress`).
- String literal size: `L"\0\0"` when the original literal has 6 bytes (P12).
- Tail call: `if (handler == nullptr) return false; return handler(s, p);` (P31, `CacheDChannel::PacketHandler`).
- SQLRETURN compare with the constant first: `0 == r || 1 == r` (P21).
- Inline ctor copies `ID128_GUID_ZERO` (P27, score only).

### A17. BloodLib block order and register locals (lift-parity-bloodlib-2): +5 each exe
- Block order: write the good path first and the error `Log` block last, as the pseudocode shows. Example:
  `SessionBuffer.cpp` (`Add`, `RemoveSentBuffer`, `increaseBuffer`, `Initialize`: +4), `Session::handlePacket` 0xf750
  (error Log 998 last, local `recvdSize`: +1).
- Read a member pointer one time into a local when the original keeps it in a register (`Port::clearPool`: `pool`
  for lock and `_valid`).
- Copy the body of an inlined `noinline` function into the caller, with a `// LIFT:` mark (`Port::Clear` gets the
  `PortListener::Clear` body: MATCH in CG).
- Inlined ctor with a folded tag: set `_tag = 778` and `memset` the context in the ctor body
  (`PortListener` ctor; `Port::Initialize` score +2.6, no MATCH: only the EH state const -2 is missing).

## B. Patterns that did not work (do not try again without a new idea)
- `!wcscmp(...)` or `int r = wcscmp(...)` to keep the -1/0/1 value (`PipeCommandProcess::processCommand`).
- Body of `removeReferenceCount` in the header, or `inline` (LTCG inline choice does not change).
- One search loop per branch in `PipeConsole::SetInvalidInfo` (caller inlines it).
- Label place, `switch` or `if` chain for `PipeConsole::run` (block order stays).
- `WSANETWORKEVENTS events = {0};` (VS2010 cl gives `memset`), merged FD_CONNECT/FD_WRITE branch (`AlertSender::run`).
- `LogFile::writeFile` loop forms (93.9 best), `DbTransaction::connect` fully nested (worse).
- Else-if chain in `HandleCacheGateHello` (score up, no MATCH), nested version ifs (worse).
- Inlined PipeConsole find forms (`CacheD::Initialize`, const 0x278), placement new in `CacheDList::Initialize`.
- `noinline` on `_Tree::clear`; fail test first in `CacheD::Verify`.
- Positive conditions first in LG handlers (the original puts error blocks first).
- Remove the `UpdatePostStatus` helper (P49) and POD map keys (P47): MATCH +2 and more, but undone for tool noise only (C1).
- Read `_connectContext` in `Session::HandleEvent` (worse).
- Source `goto` to merge the 780/838 `LT_ERROR` tails in `Session::HandleEvent` (score 98.5 -> 97.1). cl does the
  tail merge itself; a goto changes the block order.
- A global `noinline` on `RefCntHistory::add` is wrong (found by analysis, not built): only `SessionSendBuffer::clearPacketBufferList` calls it out of line.

- (noinline-2) `noinline` on `TimerQueue::Remove` / `removeShortTermQueue` (POD): no gain.
- (noinline-2) LG `Session::allocateCrypt` 0x19460: `__declspec(noinline)` is set (`Session.cpp:960`) but ours has no symbol.
  Not solved (callers `SetHandshakeParameter` 0x14f10, `ToPacket` 0x107b0 show no call).

## C. Tool and build facts
### C1. funcdiff reads a vtable ref as a string (FIXED in lift-parity-tool-2)
- `Image.string_at()` ran before `target_name()`. A vtable whose slot 0 holds `0x1400074xx` read as `" t"`, `"PI"`, `"@c"`.
  Each code size change moved 2 to 8 MATCH (ctors and dtors of Console, LogFile, Thread, PipeConsole, WinMsgHandler,
  AlertSender, CrashHandler, Channel). It made 2 good changes look bad.
- Fix: the `??_7` symbol at the exact RVA is used first (`noise.md`, fix 5). The 47 lines of `allow-worse.txt` are removed.
- Patterns 47 (POD map keys) and 49 (POD `UpdatePostStatus`) were undone only for this noise. Try them again (card pod-2).

### C2. `.tls` variable order (FIXED in lift-parity-tool-2)
- The immediate after `mov rax, gs:[0x58]` is the `.tls` offset of a thread variable. Ours groups the variables by object.
  Signals: const 0x18/0x20 against 0x88/0x90 in `Log::Write`, `Log::WriteV`, `LogBuffer::deallocate_me`,
  `Packet::Allocate`, `PacketBuffer::deallocate_me`, `Session::SendV`, `ThreadManager::entry`, `Daemon::setAddress`.
- No source fix. Tool fix: the offset is named from PDB `S_LTHREAD32`/`S_GTHREAD32` and counted as a ref `tls:<name>`
  (`noise.md`, fix 6). The guard needs `[reg + reg]` use next to a `gs:` operand. A rule with only "the function reads `gs:`"
  named plain sizes (0x40) by chance and lowered scores.
- Result of fixes 5 to 8 together: CG +18, LG +19, SCD +23, POD +20, shared 369 -> 397 of 489. 0 MATCH lost.
- A new `tls:` DIFF is real: the original and ours use other variables (for example a thread variable that we add or do not have).

### C3. Name forms in the PDB (FIXED in lift-parity-tool-2)
- `_Buynode<std::pair<K const ,V>>` (original) against `<K const,V>` (ours): `CacheDList::add` 0x3490, `ClientManager::AddSession` 0x6120.
  `name_form()` in funcdiff removes the space before a comma (`noise.md`, fix 7).
- The original PDB has `?Setup@PacketCrypt@@SA?AW4ErrCode@1@H@Z` not demangled (`Network::Initialize`).
  `simple_demangle()` gives `PacketCrypt::Setup` (`noise.md`, fix 8).
- ICF folds give other names (`Packet::~Packet` shows as `Packet::Clear`; `PingRelayContext::GetRequestWid`). Open, not tool noise.

### C4. Build facts
- `tools/vs2010/build.sh` tracks headers (lift-parity-tool-2). `cl /showIncludes` writes the repo headers of each object to
  `build-vs2010/obj/<src>.dep`. An object is built again when the `.cpp` or one of these headers is newer, or when the
  `.dep` file is missing. Test: no change = 0 objects built; `touch Log.h` = 31 CacheGate objects built (all includers).
  No `touch` of the `.cpp` files is necessary. A new `build-vs2010/obj` from an older build has no `.dep`: it builds all once.
  (5 cards found the old stale-object problem.)
- Include `crt_cpp_overload.h` only under `#if defined(__clang__)`.
- The link sorts the objects of each target. A new object in a target moves the data layout (and C1 noise).
- Helper tools: `.scratch/dis2.py <EXE> '<regex>'` (orig and ours disassembly), `.scratch/strxref.py <EXE> '<text>'`.

## D. Open causes (not solved, not tool noise)
- LTCG inline choice: `TimerQueue::clearShortTermQueueSlot`, `LogMedia::Write` inline `removeReferenceCount`;
  `TimerQueue::Remove` / `removeShortTermQueue` (noinline gave POD -2 then).
- Constant propagation: `ThreadManager::Initialize(128)` (5 exes), `Network::OpenPort` assert, `Session::Connect` timeout (LG, SCD).
- Constant CSE: `EventNotiJob::finalize` 0x9cc0, `JobManager::Execute` 0x71a0.
- Merged `Log::Write` tails: `Session::HandleEvent` 0xf1c0, `CacheDList::MakeSessionAll` 0x27d0, `Client::Send*Ok`.
- `Session::handlePacket` 0xf750: one extra `Packet::Clear` tail.
- `_instance` reload in LG `KickNotify`, `CloseSessionNotify`.
- SmartCouponDB `ProcessCharacterGameEventLog` 0x117c0: the original inlines only the first BindCol.
- Crypto misses (lift-parity-crypto-2): NOT compile flags. The LG PDB `S_COMPILE3` of BloodLib `Port.obj` and of BloodCrypto
  `rsa.obj`, `BigInteger.obj` is the same: `ltcg | security checks | hot patchable` (no `S_ENVBLOCK` in LTCG objects).
  Cause: the original links `Security\lib\BloodPacketCrypt64.lib` (BloodPacketCrypt, NoPacketCrypt, HandshakePacketCrypt,
  SessionPacketCrypt, BroadcastPacketCrypt) and `BloodCert64.lib` (BloodCert, ssn, CertDec, nic, ModuleCodeString, Cert).
  Their `S_COMPILE3` has `no dbg info`, so they have no `S_GPROC32` and no pseudocode in `hr/`. They call `Crypto::Create`,
  `Rsa::Rsa`, `Dh::Dh`, `RsaPrivate::~RsaPrivate` (IDA xrefs, LG 0x14004cf70, 0x14004c5d0). Ours has
  `PacketCrypt::Create` / `InstanceSize` as stubs (`TODO(lift-lobbygate-4)`, `Session.cpp`). Fix = lift these 2 libs.
- Crypto consts: source form, not flags. `aes128TableEncrypt`/`Decrypt` in the original use the rijndael-alg-fst loop
  (`r = 10 >> 1; for (;;) { t = round(s, rk+4); rk += 8; if (--r == 0) break; s = round(t, rk); }`): consts 0x4, 0x20.
  Result of the fst form: still DIFF (ours has 2 `add rbp,0x20`, orig 1; orig loads the image base 3 times, ours 1).
  Orig shape: `lea r14,[rk+0x10]`; 4 passes {t-round, s-round, `add r14,0x20`, 64-bit `dec rbx`}; then t-round + final.
- Fixed (+1 MATCH in each of the 4 exes): blowfish `encrypt`. Cause: `s[256 + (x & 0xFF)]` is a 32-bit unsigned index, so
  the compiler adds 0x100/0x200/0x300 before the load. `(s + 256)[x & 0xFF]` is a pointer offset: disp 0x400/0x800/0xc00.
- Fixed (+1 MATCH in each exe): `Ctr::Encrypt`. Use `if (++_counter[j] != 0) break;`, not `_counter[j]++ != 0xFF`.
- `Prng::setSeed` 0x35d60: orig has `and eax,0x800000ff; jge; dec; or eax,0xffffff00; inc` = `rand() % 256`.
  Fixed (+1 MATCH in each exe) with `rand() % 256` and a touch of prng.cpp.
- Fixed (+1 MATCH in each exe): `Prng::addEntropy` 0x35e10. The original uses `_alloca(size + 20)` (frame pointer
  `lea rbp`, probe `mov eax,[rsp]`, `sub rsp,0xa0`). LTCG folds `size` to 128. `hashSize = 20` comes before `_alloca`.
  The old fixed `buf[148]` form let LTCG inline it into setSeed, also with `__declspec(noinline)` on the declaration.
- Fixed (+1 MATCH in each exe): blowfish `decrypt` 0x360a0. Use
  `for (long long i = round - 1; i > 0; i -= 2) { t = F(r) ^ l; l = pbox[i-1] ^ t; r = F(t) ^ pbox[i] ^ r; }`.
- `Blowfish::Setup` 0x361d0: orig puts the error 5 path after the body (`ja` to the end). Source form
  `if ((unsigned)(keySize - 4) <= 0x34) { body; return true; } _error = 5; return false;` gives this layout.
  Still DIFF 98.2: inside the inlined `encrypt`, ours keeps `rbp = this+0x14` (pbox) live and makes a trip counter;
  orig indexes `[this + r11*4 + 0x14]`. Register allocation; key loop is the same.
- Did not work: aes128Table fst form (no MATCH gain; reverted).
- `aes128TableSetupEncKey` 0x38370: orig unrolls the 10-pass loop 5 times (size 589, `add rbp,0x28` on Rcon,
  `add rsi,0x50` on rk, end `cmp rbp,r13`). Ours (both the for form and the fst form) is not unrolled (size 293).

## noinline-2, stage 5 (verified 2026-11-18)

- POD `Packet::Decompose` 0x220d0 is `Decompose(int offset, int n, char const* format, ...)` (`?Decompose@Packet@@QEBAGIHPEBDZZ`).
  Added as `__declspec(noinline)` in `Packet.cpp` (assert line 472). The 8 calls in `CacheEconomyPacketHandler.cpp` use `(0x18, 6, fmt, ...)`.
  Result: POD MATCH 553 (no change), 1 ONLY-ORIG less. `Channel::Send` 0x2c160 is also paired now (it was a call-target effect).
- SCD `Network::OpenPort` 0x1a8b0 is the 9-arg overload (`?OpenPort@Network@@SA_NIGHPEBVSessionHandler@@PEBVPacketBufferHandler@@I_N22@Z`)
  with LTCG-folded constants (initialMode 2, enableAccept false, enableRecv true, nagle false). A separate 5-arg overload never pairs.
  Fix: SCD calls the 9-arg overload with `2, handler, pbh, max, false, true, false`; the 5-arg overload is removed. Result: SCD MATCH 504 (no change),
  ONLY-ORIG and ONLY-OURS for OpenPort gone (-2 ONLY entries).
- `Session::Send(Packet const*)`: the orig calls it out of line only in CG (0xfa40) and LG (0x18f00). SCD and POD inline it at every call site.
  Our noinline in `Session.cpp:801` makes it ONLY-OURS in SCD (0x13fa0) and POD (0x150a0). `tools/vs2010/build.sh` has no per-target define,
  so a per-exe split needs a wrapper `.cpp` per exe (pattern A5). Not done. Same for `Session::deallocateCrypt` (ONLY-OURS in SCD/POD; orig has it only in LG 0x194c0).
- `CriticalSection::CriticalSection` (orig 24 B, `ObjectPool.obj`): no caller names it in any orig pseudocode. Dead or folded in the orig. Not fixable by noinline.

## helpers-2, stage 1 (2026-11-18, in progress)

- A15 extension: a lift helper in an anonymous namespace or a plain `static` function is NOT inlined by VS2010 LTCG.
  Ours then has the log strings only in the helper, so each caller has fewer refs (`L"Client.cpp"`, `Channel.h`, "invalid session"
  text). Fix: `static __forceinline` on each helper. LG `Client.cpp` (`acquireSendSession`, `failSend`, `okSend`,
  `finalizeFragment`, `reserveFragment`): refs of `Client::Send*Ok` 78 -> 100.
- Same step for `LobbyDPacketHandler.cpp` helpers (`LobbyDHandlerRelease`, `LobbyDRepeatNext`, `LobbyDFpReserve`,
  `LobbyDBroadcastReload`): no measured change yet (the handlers still DIFF for other causes).
- A12 extension: no explicit `fp.packet.Clear()` before `return` in `failSend` / `okSend`. The `FragmentPacket` dtor clears.
  An explicit Clear gives 2 `Packet::Clear` calls where the original has 1. Result: LG MATCH 528 -> 530
  (`Client::SendListGoodsOk` 0x4b20, `Client::SendGetServiceEntryListOk`), 0 lost.
- Open (Client.cpp): `Client::SendTakeGoodsOk` 0x4ed0, `SendListLobbyServiceItemInfoOk` 0x5320: orig call order is
  `SetFormat, Allocate, Compose ...`; ours is `SetFormat, Compose, Clear, Allocate, Allocate`. The original HR has the
  positive form `if (Compose(goodsId) != 0) { reserve; loop...; send; ok } else { error 538 block }` (error block last).
  Ours has `if (Compose == 0) return failSend(...)` first. Not tried yet: write the positive form.
  `SendGetCharacterInfoListOk` (const 0x18 and Compose before Allocate order) not analysed.
- Tool facts: LG-only parity run `tools/parity.sh LobbyGate` takes about 32 s; the full run about 3.3 min.
  `.scratch/dl.py <EXE> '<regex>'` lists DIFF functions with scores (made in this card, not in git).
- `operator delete[]` (`??_V@YAXPEAX0@Z`, orig `CouponJob.c` 0x6850, 59 B): orig has it in LG/SCD/POD. Not tested.

## helpers-2, stage 2 (2026-11-18): POD `CacheEconomyPacketHandler.cpp`, all 13 handlers MATCH (POD 553 -> 566, 0 lost)
- Literal as a pointer variable: `static wchar_t const* const X = L"..."` at namespace scope makes VS2010 load the pointer.
  The literal then has no ref in the caller (refs r22 in the `Hello*`/`Fail`/`RemovePawn*` handlers). Fix: `#define X L"..."`.
  With the 4 helpers `static __forceinline`, 5 handlers MATCH (553 -> 558).
- A12 extension (shared END tail): the original has one `<END PACKET HANDLER>` log at the end of the handler. All failure paths
  go there. Only the success path has its own END log. Ours had one END log per failure path (extra `Log::Write` calls).
  Fix: failure paths `goto done;`, the helper does not log END on failure, the handler has `done: logEnd(...); return false;`.
  Put `ResponseLines` in an inner block (a `goto` must not jump past an initialised local). Score 85 -> 92.
- Branch order in the helper decides the block layout: `else if (!ProcessRelayResponse()) { Log fail } else { removeReferenceCount;
  logEnd; return true; }` gives the original call order (fail Log before `removeReferenceCount`). The positive form gave the other order.
- Inlined static local of a static member function: the original handlers inline `RelayHeader::GetMemberOffset()`
  (PDB: `static int const`, no standalone function). It has `static RelayHeader header;` + guard, zero-fill init, and it is the
  first argument of `Packet::Decompose` (value 0x18 = offset of `_reserved`). Fix: `RelayHeader()` zero ctor and an inline
  `GetMemberOffset()` in `RelayContext.h`; use it in each `Decompose` call. Gave +8 MATCH (558 -> 566). No other POD function lost a MATCH
  from the new ctor. Header edit: touch the .cpp files before `tools/parity.sh` (see vs2010-build-header-deps).
- Not done: `PostOfficeDB::UpdateStatusTo*` refs r21: the same literal pointer variable (`static wchar_t const* const MODULE_NAME`,
  `POSTOFFICEDB_FILE`, `FAIL_*` in `PostOfficeDB.cpp` line 17 ff.) is likely the cause. Try `#define` first.
- `PostOfficeDB::Load*Post*`: ours has `memset`/`PostInfo::PostInfo` before `Db::AllocTransaction`, the original after the acquire log.
  Orig inlines 17 ODBC `SQLBindCol` calls (import ODBC32 #4), ours calls `DbTransaction::BindCol`. Not analysed further.

## helpers-2, stage 3 (2026-11-18): POD `PostOfficeDB.cpp` (POD 566 -> 570, 0 lost; `tools/parity.sh PostOfficeDaemon` ok)
- `MODULE_NAME` as `#define` literal alone gave no change. The `UpdateStatusToDelivery*` MATCH needed the helper form:
  `UpdatePostStatus` (shared by the two functions, `__declspec(noinline)` wrappers) as `static __forceinline` so that the literals
  (`fn`, `query`, line numbers) become constants in each wrapper. The original has 4 error blocks inline in each. +2 MATCH.
- `paramLen` zero-init after `Prepare` (not at declaration): `unsigned long long paramLen[2];` then `paramLen[0] = 0; ...` after the
  prepare check. The original zero-fills only on the success path of `Prepare`.
- `ResetAllDeliveryFailurePost`: the original has one `Db::ReleaseTransaction` per return. `return *dbRetValue == 0;` merges the tails.
  Write `if (*dbRetValue != 0) return false; return true;`. +1 MATCH.
- `UpdateStatusToRetryReady` (const `0xffffffffffffffff` ref): `if (invoiceId == 0) nullInd = -1;` with `long long nullInd = 0`
  then `paramLen[2] = nullInd` matches. The `? kNullData : 0` form gave const `kNullData` in a different place (score 98.4). +1 MATCH.
- Did not work: `DbTransaction::BindCol` (6-argument, `Db.cpp` 0x2d010) in the positive form (`if (StmtHandle != nullptr) {...}`)
  loses the BindCol MATCH (calls 67 %) and does not inline into `LoadSinglePost`. Reverted. The original BindCol MATCH needs the
  `Log::Write` "Not initialized" block first. The original inlines BindCol 17 times in `Load*` with one shared "Not initialized" tail.
- Not done: `LoadPostList` 0x14e50, `LoadRetryReadyPostList`, `LoadRetryReadySinglePost`, `LoadSinglePost` 0x15fa0 (orig order: `memset`
  and `PostInfo::PostInfo` after the first acquire `Log::Write`; ours before `Db::AllocTransaction`), `RegisterPost` (84).

## helpers-2, stage 4 (2026-11-18): gate link fix and a try that did not work
- Gate link fail: the inline `static RelayHeader header;` in `RelayHeader::GetMemberOffset()` makes clang-cl emit `_Init_thread_header/_footer/_epoch`.
  The gate link is `/nodefaultlib` and has no such symbols. Fix in `CMakeLists.txt`: `add_compile_options(/Zc:threadSafeInit-)` for C++
  (VS2010 has no thread-safe statics, so the parity build is the same). Put it in `CMakeLists.txt` and not in the toolchain file, because an old `CMakeCache.txt` keeps the old `_INIT` flags.
- Did not work: `Client::SendTakeGoodsOk` in the positive form (`if (Compose != 0) { ... } else { failSend }`). Score 98.9 -> 93.8, calls 97 -> 81:
  the whole fail block moves to the end. The original has `Allocate` before the first `Compose`, and the fail block (`Log::Write`,
  `removeReferenceCount`, `Packet::Clear`) directly after it. The negative form stays. Reverted.

## pod-2, stage 1 (2026-11-18): Pattern 47 applied (POD 570 -> 574, 0 lost, `tools/parity.sh PostOfficeDaemon` ok)
- Pattern 47 (A9) works now that C1 is fixed. POD map typedefs use `StlAllocator<std::pair<K, V>, 2>` (key not const):
  `PostContext.h`, `RelayContext.h`, `RelayTimeContext.h` (K = CompoundKey), `WorldChannel.h`, `WorldConfig.h`.
  Insert calls use `std::pair<K, V>(k, v)` (`PostContext.cpp:318`, `RelayContext.cpp:274`, `RelayTimeContext.cpp:74`,
  `WorldChannel.cpp:180`, `WorldConfigManager.cpp:364` was `std::make_pair`). The PDB names confirm the non-const key for all 5 maps.
  Effect: `AddContext`, `RemoveContext` of the context managers rise (for example `RelayContextManager::AddContext` 89.7 -> 94.9).
- Pattern 49 (`UpdatePostStatus`) is already done by helpers-2 stage 3 (`static __forceinline` helper). `UpdateStatusToDelivery*` are MATCH. Nothing to do.
- Worktree setup: `vendor/zstd/src` is not in a new worktree. Copy it from `private-project/bns-lift/vendor/zstd/src`, then
  `git fetch --shallow-since=2018-05-01 origin dev; git checkout bb6eaf64` inside it. Set `LIFT_IDA_DIR=.../private-project/ida/lift`.
- Baseline at the start of pod-2 (after helpers-2): CG 420, LG 530, SCD 504, POD 570/759.
- (Fixed in stage 2, see "Block order" below) Get/Add/Remove block order (A6): `RelayContextManager::GetContext` 0x1c910 (85.8, calls 60). Orig call order (address order):
  `Log Alert | Enter Leave | Log Alert | addRef Leave | Log Alert` (3 crash pairs, the found path does `addRef` then jumps back to the shared `Leave`;
  second `L"RelayContext.cpp"` ref). Ours: `Log Alert | Enter Leave addRef Leave Leave Log | Log Alert`. Same shape in
  `PostContextManager::GetContext` and `WorldChannelManager::GetWorldChannel`. `AddContext`: orig puts `addRef` after the `_Linsert` and
  `Leave` of the error path after it (`_Linsert, Leave, Log, addRef, Leave, Log`); ours puts `addRef, Leave` first. Not fixed yet.
- Tool: `.scratch/fdfull.py` (copy of funcdiff with full diff context, `n=200`) works. `.scratch/dis2.py` fails at
  `from capstone.x86 import X86` (use the import form that `tools/funcdiff.py` uses). Both files are not in git.
  Fix: `from capstone import x86_const as X86`. Run with
  `uv run -q --no-project --with capstone --with pefile python .scratch/dis2.py <Exe> '<name regex>'` (needs `LIFT_IDA_DIR`).
  `tools/funcdiff.py <Exe> --build build-vs2010 --show '<regex>'` also needs `uv run ... --with capstone --with pefile`.

### Block order (A6) of the context managers: fixed, POD 574 -> 584 (0 lost, `tools/parity.sh PostOfficeDaemon` ok)
Rule: VS2010 puts the `if` body inline and the code after it behind a jump. So write the source in the order of the original blocks.
Find the order with `dis2.py` (look at the first `jne`/`je` after the `find` code and at the `ret` positions).
- `Get*` (`RelayContextManager::GetContext`, `PostContextManager::GetContext`, `WorldChannelManager::GetWorldChannel`): the original has one
  shared `Leave` for the found and not-found paths. Source form: `T* p = nullptr; Enter; it = find(k); if (it != end) { p = it->second;
  if (p == nullptr) { Leave; crash; return nullptr; } p->addReferenceCount(...); } Leave; return p;`. +1 MATCH each (3 functions).
- `Add*` (Relay, Post, WorldChannel, RelayTime `AddContext`/`AddWorldChannel`): error path first. Form: `if (!insert(...).second)
  { Leave; Log::Write(...); [free]; return false; } addReferenceCount; Increment; Leave; return true;`. +1 MATCH each (4 functions).
- `Remove*` (Relay, Post, RelayTime `RemoveContext`, `WorldChannel::RemoveWorldChannel`): null path first. Form: `if (p == nullptr)
  { Leave; crash; return false; } erase(it); removeReferenceCount; Decrement; Leave; return true;`. +1 MATCH each (3 functions).
- Not fixed: `WorldChannelManager::RemoveWorldChannel` 0x? (97.4): the original calls its own `_Tree<unsigned short,WorldChannel*>::erase`;
  our link folds it (ICF) into `_Tree<__int64,PostContext*>::erase`. Cause is the linker, not the source. Do not try to fix it in source.
- `initContextManager` x4 (refs 86 to 88): ours has 4 extra `Lock.h` assert crash blocks (`Log Alert MakeCrash`, line 113 and 122).
  The original has the `this == nullptr` assert before the first `Enter` (line 113) and one at each `Leave` (line 122): 2 at the end
  (`LABEL_29` and the "already exists" path) and not at every exit. Ours inlines the assert at every `Leave`. Not fixed.
- `DeliverPostRelayContext::initResponse`, `RetrieveCharacterInfoRelayContext::initResponse`: consts 0. Ours has an extra
  `0xfffffffffffffff8` (`-8`) that the original lacks. Not fixed.

## pod-2, stage 2
- `UnsentPostContextManager::initContextManager` 0xc6d0 and `updateWorldList` 0xcae0: the original has 1 assert at Lock.h line 113 (Enter)
  and 1 at line 122 on each exit, and no call to `AutoCS::~AutoCS`. A local `AutoCS` object gives one extra dtor call (assert + Leave)
  per exit. Form that works: no `AutoCS`; `CriticalSection* lock = &_reloadLock;` with local macros `UNSENT_LOCK_ENTER` and
  `UNSENT_LOCK_LEAVE_RETURN` (assert, `LeaveCriticalSection`, return). Scores: initContextManager 92.7 -> 92.9, updateWorldList 90.5. No new MATCH.
  Still open: block order (the original puts the out-of-range exit after the loop) and the const `-2` (unwind state) that the original has.
- `RetrieveCharacterInfoRelayRequest()` (WorldPacketHandler.h): the loop `for (i < 33) _targetCharacterName[i] = 0` gives no `memset` call.
  `memset(_targetCharacterName, 0, sizeof(...))` gives the `memset` call of the original. `HandlePostOfficeServiceRetrieveCharacterInfoReq`
  is MATCH now (POD 584 -> 585). Rule: an inline ctor that the original compiles to `memset` must call `memset`, not a loop.
- Tool noise, not fixable in source (do not try): string-literal ref duplicates (`L"world packet handler"` and similar x2 or x3),
  `PostOfficeDaemon::_instance` ref count, `tls:__delv_buf__` refs. Example: `CacheGateSessionHandler::OnConnect`, `AgentSessionHandler::OnClose`.
- `PingRelayContext::processRelayResponse` 0xabd0 (97.6): source has the same crash blocks as the original (64, 86, 92). One
  `AlertSender::Write` is missing in our call order. Cause not found (clang block layout). Not fixed.

## pod-2, stage 3
- `PostInfo::PostInfo` 0x11140: the original copies `ID128_GUID_ZERO` into `_reservedHint` and `_senderAccountId` (4 qword loads from data).
  Source `_reservedHint = ID128_GUID_ZERO; _senderAccountId = ID128_GUID_ZERO;` gives the refs: score 66.7 -> 88.9. Not MATCH:
  the original loads the constant twice, in the middle of the other stores. Ours loads it once and hoists it (refs 67). Not fixed.
- `PostInfo::CheckValidityPostData` 0x11290: the original compares `_senderAccountId` with `ID128_GUID_ZERO` (4 uses, one per case).
  Source with `.id[0] != ID128_GUID_ZERO.id[0] || .id[1] != ...` (macro `POST_HAS_ACCOUNT_ID`) fixes the refs: 57.6 -> 90.9.
  Open: consts. The original has 0x2 and 0x7, ours has 0x5 (switch lowering of cases 1, 2, 7). No new MATCH from both edits (POD stays 585).
- `PostOfficeDB::LoadSinglePost` 0x15fa0 (same cause in `LoadPostList` 0x14e50, `LoadRetryReadySinglePost` 0x18010,
  `LoadRetryReadyPostList` 0x190f0). Facts from the pseudocode (not yet applied, patch in `.scratch/postofficedb-bindcol-macros.patch`):
  1. The original has no helper function for the column binds. It inlines `DbTransaction::BindCol` (6-arg, 0x2d010) for the 17 post columns
     (each with `StmtHandle` check, `*len = -3`, `SQLBindCol`, `BoundCol = true`). The item loop (7 columns x 10) calls `BindCol` out of line.
     Our lift helper `BindPostColumns` gives 18 out-of-line `BindCol` calls. Try: macros that expand the `&&` chain in each loader.
  2. The original declares `paramLen`, `postLen`, `itemLen`, `PostInfo`, `attachedItemInfo` after the `Prepare` check, so `memset`/`PostInfo::PostInfo`
     come after the first `Log::Write`. Ours declares them first. Move the declarations.
  3. The original initialises the 10 `AttachedItemInfo` with an inline loop (fields = 0, then `memset(_itemXmlData, 0, 0x802)` each).
     Ours has one `memset` of the whole array. Needs an inline ctor `AttachedItemInfo()`. Check `AgentPacketHandler.cpp:126` and
     `WorldPacketHandler.cpp:443` (they declare `AttachedItemInfo`) for MATCH loss.
- Tool note: `.scratch/dis2.py` works after `from capstone import x86_const as X86`.

## pod-2, stage 4 (2026-11-18): POD 585 -> 588 (0 lost; `tools/parity.sh PostOfficeDaemon` ok)
- `WorldChannel::SendRelayResponse` 0x1e570 (97.6 -> MATCH): remove the explicit `packet.Clear()` before each `return`. The `Packet` dtor
  clears. The original has 2 `Packet::Clear` calls, ours had 4. Same rule as A12 (no explicit `p.Clear()`).
- `initResponse` of Deliver 0xfb50 and Retrieve 0x1f770 (66.7 -> MATCH, +2). The response classes have a vptr at 0 and `RelayResponse` at +8.
  Deliver: `static_cast<RelayResponse&>(_response) = *response;` (same body as `CheckPostCapacityRelayContext::initResponse`, which was MATCH).
  Do not read fields through `static_cast<DeliverPostRelayResponse*>(response)` (this gave an extra const `-8`).
  Retrieve: keep a local `RetrieveCharacterInfoRelayResponse* r = static_cast<...>(response);`, copy the base with `= *r`, then `_resultPcId = r->_resultPcId`.
  The one downcast gives the `-8` const that the original has.
- Did not work: `HandlePostOfficeRegisterPostReq` 0x1aaa0 (98.0): the `attachedItemCount > 10` error block (Log line 208) moved to after the
  success `return true` with a `goto` label. The compiler keeps the block early. Score unchanged. Reverted.
- Did not work (score unchanged, 77.8 and 75.2): `CheckPostCapacityRelayContext::ComposeResponsePacket` 0x9570 and
  `RetrieveCharacterInfoRelayContext::ComposeResponsePacket` 0x1e230 as `if (==SUCCESS) {...} else {...} return true;` with `<= RESULTSTATE_SUCCESS`
  for the range test. The original puts the failure `Compose` + 2 `Log::Write` at the END of the function (after the crash block), and has consts
  4/8 (Check) and 4/5 (Retrieve) where ours has 2 and the cmd 0x78/0x79. The if/else form stays in source (compiles, no loss). A next try:
  failure branch as the fall-through, success `Compose` after the crash block.
- Not done: `PostOfficeDB` loaders (`LoadPostList` 0x14e50, `LoadSinglePost` 0x15fa0, `LoadRetryReadySinglePost` 0x18010,
  `LoadRetryReadyPostList` 0x190f0; scores 60 to 72). The original inlines 17+70 `BindCol` calls per loader. A MATCH is not likely; low value.
- `CachedWatchdogManager::updateWorldList` (95.5) and `UnsentPostContextManager::updateWorldList` (90.5): the original has the assert-crash
  block (`Log::Write`, `AlertSender::Write`, `CrashHandler::MakeCrash`) after the loop; ours has it before. Not tried.
- Worked (score 77.8 to 90.5, calls now equal, no MATCH change): `CheckPostCapacityRelayContext::ComposeResponsePacket` 0x9570 and
  `RetrieveCharacterInfoRelayContext::ComposeResponsePacket` 0x1e230. Write the failure branch first: `if (resultState != SUCCESS) {crash block;
  convertFailReason; failure Compose + 2 Log} else {success Compose + 2 Log} return true;`. The call order then equals the original.
  The consts stay different (line numbers and cmd ids in the unwind and `Log::Write` setup). No more source change is known.
