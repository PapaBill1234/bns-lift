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
