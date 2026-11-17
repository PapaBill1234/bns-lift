# Parity lessons

## 1. Virtual call on a global object (WORKED, lift-parity-s1)
- Cause: ours called `BaseMemoryManager::_Instance.Alloc(...)` on the object. The call binds statically and LTCG inlines
  `HeapMemoryManager::Alloc` (ours: `import:HeapAlloc`, the file and line constants are gone).
  The original calls through the vtable (`<indirect>`, 2 refs to `BaseMemoryManager::_Instance`: vptr load and `this`).
- Source change: macro `BASE_MEMORY_MANAGER` in `MemoryManager.h` =
  `static_cast<MemoryManager const&>(BaseMemoryManager::_Instance)`. All 59 call sites use it. VS2010 does not devirtualize it.
- Example: `BaseRefCntObj::deallocate_me` (CG 0x18460). Before: `import:HeapFree` + `<data>`. After: MATCH.
- Result: CG 293→302, LG 377→388, SCD 334→349, POD 375→389.
- Use this for each call on a global object of a class with virtual functions when the original has `<indirect>`.

## 2. funcdiff: vtable read as a string (NOISE, not fixed, tooling card)
- `Image.string_at()` runs before `target_name()`. A vtable whose slot 0 holds `0x1400074xx` has the bytes `20 74 00`
  and reads as `" t"`.
- Proof: CG ours `??_7Blowfish@@6B@` at 0x57220 = `2074004001000000`. `Crypto::Destroy` became DIFF only for this.
- Fix idea (tooling card): prefer a named symbol at the exact RVA before the string test.

## Pattern 3 (worked): branch order follows the source order
- Cause: VS2010 lays out the `if` body first. funcdiff lists calls in address order, so a swapped `if`/`else` gives a call-order DIFF.
- Change: write the branch that is first in the original code first (invert the condition).
- Examples (CacheGate): `HeapMemoryManager::Realloc`/`ReallocZero` 0x19fa0/0x19fc0 (`ptr == nullptr` first),
  `TimerQueue::Add` 0x16680 (`slice < StqSize` first), `makeDirectory` 0x7840 (`wcslen(drive) != 0` first),
  `Daemon::timerMain` 0xc370 (`wait > 0` first).

## Pattern 4 (worked): keep a member pointer in a local before a lock call
- Cause: a member read after an import call is read again (alias). Extra consts such as `add rcx, 0x30`.
- Change: `PipeConsole* pipe = pipeConsole;` in `Daemon::setState`. Fixes `Daemon::Reload` 0xaf30, `Daemon::Cooldown` 0xb050.

## Pattern 5 (worked): pass the address of the variable, not a copy
- `CrashHandler::MakeCrash` 0x8790: `RaiseException(..., 1, (ULONG_PTR const*)&info)`. The original keeps `info` in memory (const 0xc = `add rcx, 0xc`).

## Pattern 6 (worked): `switch` gives dec/dec, `if/else if` gives `cmp 2`
- `RefCntHistory::dump` 0x100b0: `switch (item._op)` removes the extra const 0x2.

## Pattern 7 (worked): crash branch first (early return)
- Cause: the original lays out the error path first (`jg` to the good path). Source form: `if (_ref <= 0) { Log; Alert; return 0; }`.
- `RefCntObject::addReferenceCount` 0x2150 and `removeReferenceCount` 0x2230: both MATCH. CG 311 -> 315 (fast build).

## Not fixed: header `__FILE__` path per exe (BLOCKED in a source card)
- LG/SCD/POD: `RefCntObject::~RefCntObject`, `StaticPageMemoryManager::*` refs use `<Exe>-Common-0.0.348\...\include\X.h`.
- `tools/vs2010/build.sh` compiles each shared source one time for all 4 exes (no per-exe define). So one literal
  can match only one exe. Fix needs a build tooling card: a per-exe `/D` define and per-exe objects for BloodLib.

## Not fixed: LTCG inlining choices (TimerQueue)
- `TimerQueue::clearShortTermQueueSlot` 0x16900: ours inlines `removeReferenceCount`, orig calls it.
- `TimerQueue::Remove` 0x167a0: ours inlines `removeShortTermQueue` 0x16890, orig calls it.
- Orig inlines `removeReferenceCount` in Channel, DelayedRelease, Packet, SessionBuffer, so `noinline` on it is wrong. Not tried.
- Stage 6: `__declspec(noinline)` on `removeShortTermQueue` (pattern 11; only caller `Remove` in all exes).
  POD: `Remove` and `removeShortTermQueue` MATCH. Totals vs the stage-6 swprintf run: CG +2, LG +3, SCD +2, POD -2 (406 -> 404).
  The 2 POD functions that went to DIFF are not known yet (the parity gate passes; they are not baseline MATCH).
  `clearShortTermQueueSlot` is still DIFF (score 43.9).

## Not fixed: `ThreadManager::Initialize` 0x12dd0 constant propagation
- Ours: LTCG puts 128 (0x80, 0x400) into `Initialize`; `Daemon::Start` loses const 0x80. Orig passes `0x80u` in all 5 exes
  (only caller). The source (`Initialize(128)`, Daemon.cpp:320) is equal. Cause not known. ❓

## Pattern 8 (worked, partly): one `htonl` call for a range test
- `Daemon::setAddress` 0xbda0: orig `and 0xfff00000; add 0x53f00000; cmp 0xf0000` (one `htonl`).
  Source form: `(htonl(a) & 0xFFF00000) - 0xAC100000 <= 0xF0000`. A `>= && <=` form gives 2 `htonl` calls and no fold.
- Orig inlines `Network::GetAddressStringW` (TLS buffers of Network.obj). Ours had a copy in Daemon.cpp. Now it calls
  `Network::GetAddressStringW`. PDB name: `__ip_addr_string_w__` (S_LTHREAD32, .tls+0x60). CG consts 89 -> 98.
  Last DIFF: const 0x60 (TLS offset, see the TLS order group).

## Not fixed: TLS variable order (LTCG / link order)
- Orig CG .tls: 0x08 prng `_Instance`, 0x10 `IoWorker::WorkerId`, 0x18 `LogBufferAllocator::_Local`,
  0x20 `PacketBufferAllocator::_Local`, 0x28 `Thread::Current`, 0x30 `IoWorker::ZstdCCtx`, 0x38 `__delv_buf__`,
  0x40 ip a, 0x60 `__ip_addr_string_w__`.
- Ours: 0x10 WorkerId, 0x18 ZstdCCtx, 0x20/0x40 ip a/w, 0x80 prng, 0x88 PacketBuffer, 0x90 LogBuffer, 0x98 Thread::Current.
- Not the module order of the orig PDB. `__delv_buf__` is missing in ours. Fix needs a tooling card (link order).
  Affects `ThreadManager::entry` 0x13140, `Daemon::setAddress` 0xbda0.

## Not worked: `wcscmp` result kept (`sbb eax,eax; sbb eax,-1; test`)
- `PipeCommandProcess::processCommand` 0x14ad0, `PipeConsole::processCommand` 0x14fa0: orig keeps the -1/0/1 value.
  Ours folds it to `repe cmpsw; jne`. Tried `!wcscmp(...)` and `int result = wcscmp(...)`: no change. Cause not known. ❓

## Noise: SCD `Console::Console`, `~Console`, `LogFile::LogFile`, `~LogFile` (string_at, see 2)
- After stage 3, ours vtable refs read as `" a"`. Same cause as `Crypto::Destroy`. Add to allow-worse.txt if still lost.

## Noise: LG `PipeCommandProcess::~PipeCommandProcess`, `PipeConsole::~PipeConsole`, `Thread::~Thread`, POD `Session::initialize`
- Stage 4: a data shift makes funcdiff read a vtable ref as a 2-byte string (`"`I"`, `" Y"`). Same cause as 2. In allow-worse.txt.
- Stage 6: same noise in LG and POD `Console::Console`, `~Console`, `LogFile::LogFile`, `~LogFile` (`"@c"`), LG `Channel::~Channel` (`"PV"`).
  Each data change can move this noise to other functions. Check the refs diff with `--show` before you add a line.

## Pattern 9 (worked): VS2010 template overload `swprintf_s<N>`
- Orig calls `swprintf_s<520>` (out of line). Ours called `swprintf_s(dst, _countof(dst), ...)` (import).
- Source: `swprintf_s(Daemon::Instance->confDir, argv[i] + 7)` (2-arg form, array argument). The Wine headers do not have
  the template, so the clang build includes `include/vs2010/crt_cpp_overload.h` under `#if defined(__clang__)`.
  Example: `WinServiceConsole::ServiceMain` 0x177d0. Other sites: AlertSender (`<64>`, `<260>`), DaemonConfig (`<780>`), Daemon.cpp 0xc5d0.
- Stage 6: same change in AlertSender.cpp, DaemonConfig.cpp, Daemon.cpp (`BloodDaemonMain`). MATCH CG +3, LG +7, SCD +2, POD +13.
  Use the template form only when the destination is an array and the size argument is its full size
  (`Daemon::setCurrentDirectory` uses `cur[264]` with size 260: keep the explicit size).

## Pattern 10 (worked): nested success-first `if` for handle chains
- Orig layout: success path first, error blocks at the end in reverse order (`OpenSCManager` error last).
- Source: `if (h != nullptr) { if (s != nullptr) {...} else {err} } else {err}`. Early `if (h == nullptr) return` puts the errors first.
  Example: `WinServiceConsole::InstallService` 0x17c80. `UninstallService` 0x17f00 is 99.5: VS2010 merges one
  `CloseServiceHandle` tail that the orig keeps. Not fixed.

## Pattern 11 (worked): `__declspec(noinline)` for a function that the orig calls from its only caller
- `WinServiceConsole::reportStatusToSCManager` 0x17a20 (one caller: `controlHandler` 0x179e0). Mark it `// LIFT:`.
  Use it only when the orig never inlines the function (check all callers in all exes). CG +2 (both functions MATCH).

## Pattern 12 (worked): string literal size
- `CreateServiceW` dependencies: orig literal is 6 bytes (`??_C@_15...`), so the source is `L"\0\0"`, not `L""`.

## Tool
- `.scratch/dis2.py <EXE> '<regex>'` prints the disassembly of orig and ours (uses `funcdiff.Image`).

## Stage 6 facts (lift-parity-s1)
- `tools/vs2010/build.sh` rebuilds an object only when its `.cpp` is newer than the `.obj`. It does not track headers.
  After a header change, run `rm -rf build-vs2010/obj` before `tools/parity.sh`. Else the link fails or the result is stale.
- `__declspec(noinline)` on `TimerQueue::removeShortTermQueue` (Timer.cpp): POD gains `TimerQueue::Remove`,
  `Session::initialize`, `removeShortTermQueue`, loses 5 to string_at noise (`AlertSender::AlertSender`, `Thread::~Thread`,
  `WinMsgHandler::~WinMsgHandler`, `PipeConsole::~PipeConsole`, `PipeCommandProcess::~PipeCommandProcess`: vtable read as "pI"/"`J").
  These 5 were not MATCH in the baseline. Kept.
- `RefCntObject::removeReferenceCount`: the original log `__FILE__` is `include\RefCntObject.h` line 177, so the body is
  inline in the header. Our build (body in .cpp) inlines it wrongly in `TimerQueue::clearShortTermQueueSlot` (SCD 0x264F0)
  and `LogMedia::Write` only. Tried (did not work): body moved to RefCntObject.h, declaration marked `inline`.
  `clearShortTermQueueSlot` and `LogMedia::Write` stay DIFF (same scores). SCD loses 5 MATCH (`Console::Console`,
  `Console::~Console`, `LogFile::LogFile`, `LogFile::~LogFile`, `WindowConsole::~WindowConsole`), LG gains 1
  (`Channel::~Channel`). Undone: body is in RefCntObject.cpp again.

## Stage 8 facts (lift-parity-s1)
- Include `crt_cpp_overload.h` only under `#if defined(__clang__)`. VS2010 cl does not find it (C1083) and has the template.
- PipeConsole (measured with VS2010 build, before the gate fix): `__declspec(noinline)` on `connectPipe` 0x15c80,
  `disconnectAndReconnect` 0x15d20, `addNode` 0x15ed0, and the 2-arg `swprintf_s(array, fmt, ...)` in `checkFrozenThread`
  0x15190 and `initPipe` 0x15af0. Gains: CG +4, POD +4 (`checkFrozenThread`, `initPipe`, `swprintf_s<128>`, `swprintf_s<256>`),
  SCD +5 (also `addNode`), LG +4.
- Side effect: SCD `NPServiceChannelManager::OnConnect` (baseline MATCH) now inlines `SetInvalidInfo` (orig calls it).
  Cause: `SetInvalidInfo` is smaller when `addNode` is not inlined. Not yet fixed.
- Rewrite of `SetInvalidInfo` with one search loop in each branch (as in the orig pseudocode): no gain. Undone.
- LG `CrashHandler::CrashHandler` loss is string_at noise (`??_7CrashHandler@@6B@` read as "@d").

## Stage 9 facts (lift-parity-s1)
- SCD `NPServiceChannelManager::OnConnect` is MATCH again with the stage 8 PipeConsole changes and the one-loop
  `SetInvalidInfo`. The rewrite with one search loop in each branch makes `SetInvalidInfo` inline into `OnConnect`
  (SCD loses a MATCH). Do not split the search loop.
- Pattern 13 (partial): one `goto reconnect` target for all error paths of `PipeConsole::run` 0x157b0. The orig has one
  `disconnectAndReconnect` call site. Separate calls give 2 call sites (calls 59). One label gives 1 call site (calls 89).
  The block order of the label stays different. Label place (end of loop, or in the read case), `switch` or `if` chain
  for the 2 state tests: no change. Not MATCH.
- SCD and LG losses of vtable-only functions (`Thread::~Thread`, `PipeConsole::~PipeConsole`,
  `PipeCommandProcess::~PipeCommandProcess`, `GameEventManager::initWorkerThread`, `CrashHandler::CrashHandler`) are
  string_at noise. They come and go when the data layout changes. They are in `allow-worse.txt`.

## lift-parity-s2 facts (stage 1, no source change yet)
- `??_7RefCntObject@@6B@` is not novtable. Orig CG refs it only in `RefCntObject::~RefCntObject` 0xccd0 (dtor stores it).
  Ours refs it in 13 constructors/allocators (`Session::Session` x2, `Network::Network`, `SessionPool::SessionPool`,
  `PacketBufferPool::allocate`, `PacketBufferAllocator::allocate`, `Session::Connect`, `Port::Initialize`, `CacheD::CacheD`,
  `DelayedRelease::Release`, `LogBufferPool::allocate`, `LogBufferAllocator::allocate`).
- VS2010 test (`/O2`, `build/nvt/t.cpp`): `__declspec(novtable)` removes the vptr store from the ctor AND the dtor, so it is wrong.
  Without novtable, VS2010 removes the dead base vptr store in a simple inline ctor. So our build keeps it for another reason ❓
  (ours stores `_tag=10` before the vptr; orig stores `_ref=1`, `_tag=10`, then only the derived vptr).
- `const 0x20` (orig) against `0x88` (ours) in `Packet::Allocate`, `Packet::Concatenate`, `PacketBuffer::deallocate_me`,
  `PacketBufferAllocator::Initialize`, `Session::SendV`: TLS offset of `PacketBufferAllocator::_Local` (TLS order group).
- `tools/vs2010/build.sh` links the objects in `sort -u` path order. Our TLS order is not that order either.

## Pattern 11 again (worked, lift-parity-s2): noinline for `Session::Recv`, `SessionSendBuffer::clearPacketBufferList`, `PortListener::Clear`
- All 4 orig exes have these as separate functions. CG +3 (`SessionSendBuffer::Clear` 0x1a750 is now MATCH).

## Pattern 13 (worked): UTF-8 BOM for a source file with Korean string literals
- VS2010 reads a UTF-8 file without a BOM in the ANSI code page. A Korean character becomes 3 wide characters.
- Signal: orig literal `??_C@_1IA@` (0x80 bytes), ours `??_C@_1KI@` (0xA8 bytes), same text.
- Fix: add a UTF-8 BOM. Done: `PacketBuffer.cpp`, `LogBuffer.cpp`. Not done (not in the s2 file list):
  `src/Server/LobbyGate/ContentsRuleConfigDefinition.cpp`. Example: `PacketBufferPool::allocate` 0x128d0.

## Pattern 14 (worked): one error block per failed call, not a shared `goto` label
- Orig `Network::initializeSocketInterface` 0xda30 calls `WSAGetLastError` in each failed branch. VS2010 merges
  the `Log::Write` + `closesocket` tails, but not the `WSAGetLastError` calls. Source: a full error block per branch.
- `Session::sendNext` 0xfdc0: `if (WSASend(..) == SOCKET_ERROR) { int error = WSAGetLastError(); if (error != WSA_IO_PENDING) {Log; return false;} }`.
  One `WSAGetLastError` call. `Connection::AsyncSend` also MATCH after this change.

## Not fixable in source: `Network::Initialize` callee name
- Orig PDB names the callee `?Setup@PacketCrypt@@SA?AW4ErrCode@1@H@Z` (not demangled). Ours is `PacketCrypt::Setup`. Same function: tooling card.

## RefCntObject vptr store (open)
- Ours `PacketBufferPool::allocate`: the inlined `RefCntObject()` stores `_tag=0xa`, `_history`, `_ref=1`, the RefCntObject vptr,
  then `PacketBuffer()` stores the PacketBuffer vptr, `_ref=1`, `_tag=0x50a`, `_history` again. Orig stores only once
  (`_ref=1`, `_history`, vptr, `_tag=0x50a`). So VS2010 does not merge the base ctor stores with the derived stores.
- Solved (pattern 15). Cause: our header had `long volatile _ref`. The PDB type is plain `long` (0x0012). A volatile
  store is a barrier: VS2010 cannot remove the dead base stores (`_tag=0xa`, RefCntObject vptr) before it.
- Fix: `long _ref;` in `RefCntObject.h`. `InterlockedIncrement(&_ref)` still compiles (`long*` → `long volatile*`).
- Example: `PacketBufferPool::allocate` CG 0x128d0 DIFF → MATCH. Also `PacketBufferAllocator::allocate`, `Session::Session()`.
  Gain: CG +7, all 4 exes up (LG 424, SCD 387, POD 421).
- Did not work: remove `_ref = 1; _history = nullptr;` from the `PacketBuffer()` body (no change; kept removed, base ctor stores them).
- Rule: check each `volatile` member against the PDB type. `pdbq <EXE> type <Class>` shows a plain type as `0x0012 (long)`.

## Pattern 16 (worked, lift-parity-s2 stage 4): write the loop in the form that VS2010 does not unroll
- `PortListener::Initialize` 0x31fd0: `for (i = 0; i < 128; ++i) { ...; if (!asyncAccept(i)) break; } if (i >= 128) return true;`.
  The old loop form gave an extra `memset` + a 2nd `asyncAccept` call (unrolled). Now MATCH in all 4 exes.
- `Session::Connect` 0xe570: null test of `this + 1`, stores through `_connectContext`, failure branch first. MATCH in CG and POD.
  The `sin_*` stores before the timeout store put `htons` before `GetTickCount64` (LG 94.7 -> 97.8).

## Pattern 17 (score up, no MATCH): `Packet packet = {nullptr, false};` in place of `memset` or `= {}`
- Orig sets `Splitter`, `IsFragmentPacket`, then an inline 28-byte zero fill. `= {}` or `memset` gives a `memset` call.
- No explicit `packet.Clear()` before a return: `~Packet()` calls it (orig has 1 unwind state).
- Example: `Session::handlePacket` 0xf750 90.5 -> 94.4, `Session::SendV` 0xfaa0 91.1 -> 92.3 (CG).
- Still DIFF: orig shares one `Clear; return false` tail for the error paths; ours has one more `Clear` block. Source form unknown.

## Did not work
- `Session::HandleEvent` 0xf1c0: read `_connectContext` in place of the `context` argument (hr line 1074). Score 98.5 -> 97.4. Undone.
- `Session::HandleEvent`: orig merges the 796 and 814 `Log::Write` calls (line in a register). Ours does not. Cause unknown.
