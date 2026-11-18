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

## Pattern 18 (worked, lift-parity-s3): zstd version = upstream dev commit bb6eaf64
- v1.3.5 gave many zstd DIFFs. bb6eaf64 (2018-05, #1153) makes all zstd functions MATCH. See `vendor/zstd/README.md`.
- Gain: CG 345 -> 361, LG 425 -> 450, SCD 388 -> 400, POD 423 -> 443.
- Rule: if upstream code is DIFF, count the calls of one function (for example `ZSTD_litLengthContribution`) and bisect commits.

## Pattern 19 (worked, lift-parity-s3): noinline for more shared functions (see pattern 11)
- `AlertSender::createSocket` (callers run, init), `LogMedia::Add` (only caller `Log::Add`), `DbTransaction::close`.
- `Log::Add` and `LogMedia::Add` became MATCH in all 4 exes.

## Pattern 20 (worked, lift-parity-s3): first branch of the original first
- `LogFile::makeDirectory`: `if (wcslen(drive) != 0) {dir} else {GetCurrentDirectoryW}` -> MATCH.
- `Db::AllocTransaction`, `initEnv`, `Execute`, `BindCol`: good path first, `Log::Write` at the end.
  SCD +6, POD +7 (AllocTransaction, clearList, initEnv, Execute, Prepare, initStatement, BindParam).
- `LogFile::writeFile`: one `while ((file = CreateFileW(...)) == INVALID_HANDLE_VALUE)` loop, 91.7 -> 93.9 (still DIFF).
- Did not work: `DbTransaction::connect` fully nested (93.3 -> 87.8). The original returns early when `envHandle == nullptr`.

## Pattern 21 (found, lift-parity-s3): SQLRETURN compare with the constant first
- Orig (SCD 0x21118): `xor ecx,ecx; cmp cx,ax; mov ecx,1; cmp cx,ax`.
- VS2010 test: `0 == r || 1 == r` gives this code. `r == 0 || r == 1` gives `test ax,ax; cmp ax,1`.
  `r < 2` or `(r & ~1) == 0` gives `test ax,-2`. `switch` gives `cmp ecx,1`.
- Applied to all of `Db.cpp` (helper `sqlSucceeded`). Result not yet measured at the stage end.

## Pattern 22 (worked, lift-parity-s3): copy the original refs and member reads one to one
- `LogBuffer::GetLog`: `return _log != nullptr ? _log : L"";` (orig refs `L""`) -> MATCH in all 4 exes.
- `LogBufferAllocator::initAllocator`: put the new allocator in a local, then `_Allocator = allocator;
  allocator->Initialize(size)` (one less `_Allocator` read) -> MATCH in all 4 exes. Gain +2 per exe.

## Pattern 23 (worked, lift-parity-s3): VS2010 folds `2*n + 20` into `(n+10)*2`
- `AlertSender::writev2` (CG orig 0x9580): orig keeps const 0x14; ours did `lea ebx,[rax+0xa]; add bx,bx`.
- Fix: one `short logBytes = 2 * logCount` local, used in the size and in the two later writes.
  MATCH in all 4 exes (+1 each).

## Pattern 24 (worked, lift-parity-s3): LTCG moves a callee null check into the callers
- SCD `DbTransaction::BindParam` (orig 0x20fd0): ours had no `StmtHandle == nullptr` branch. The check and
  the "Not initialized" ref were in the 10 `SmartCouponDB` callers (find refs: `.scratch/strxref.py <EXE> '<text>'`).
- Fix: `__declspec(noinline)` on the function. SCD +1, and the 10 callers score +1.3 to +3.8.

## Pattern 25 (worked, lift-parity-s3): POD `DbTransaction::BindCol` (orig 0x2d010)
- Orig call order has `Log::Write` first. `if (StmtHandle == nullptr) {Log::Write; return false;}` first -> MATCH.
  (Opposite of pattern 20 for the SCD overload 0x20E40.)

## Did not work (lift-parity-s3)
- `AlertSender::run`: `WSANETWORKEVENTS events = {0};` in place of `memset`. The `memset` call stays (97.8).
- `LogFile::writeFile`: first `CreateFileW` out of the loop, then `for(;;){Sleep; CreateFileW; break; ++tries}`
  = HEAD form, 91.7. The one-loop form gives 93.9 (alert calls still after CloseHandle in the layout).
  `while ((file = CreateFileW(...)) == INVALID && ++tries < 100) Sleep(100);` then one alert block: also 93.9 (kept).

## Open cause (lift-parity-s3): .tls layout order
- Signal: const 0x18 (orig) vs 0x90 (ours) in `Log::Write`, `Log::WriteV`, `LogBuffer::deallocate_me`,
  `LogBufferAllocator::Initialize` (all 4 exes). The const is the .tls offset of `LogBufferAllocator::_Local`.
- CacheGate .tls offsets (llvm-pdbutil dump -globals -symbols). Orig: 8 `_Instance`, 16 `IoWorker::WorkerId`,
  24 `LogBufferAllocator::_Local`, 32 `PacketBufferAllocator::_Local`, 40 `Thread::Current`, 48 `IoWorker::ZstdCCtx`,
  56 `__delv_buf__`, 96 `__ip_addr_string_w__`. Ours: 16 WorkerId, 24 ZstdCCtx, 32 ip_a, 64 ip_w, 128 prng `_Instance`,
  136 PacketBuffer `_Local`, 144 LogBuffer `_Local`, 152 `Thread::Current`.
- Ours groups by obj, in definition order inside an obj. Orig splits WorkerId and ZstdCCtx, so the orig probably
  defines them in different objs. `__delv_buf__` is not in our source. Not fixed: link order of lib objs.

## Pattern 26 (worked, lift-parity-s3): BnsCommonConfig def-list loops
- Cause: ours used the next array as loop end. Orig counts `count` down and steps the pointers.
- Fix: `for (; count > 0; --count, ++defList, ++loadDefList)` form in `Dump`, `UpdateAllVariable`,
  `UpdateReloadedVariable`, `CheckMinMaxBoundary` (orig const 0x28 = sizeof step). `LoadBnsCommonConfig`: one
  `failed:` tail (errorLine, errorText), like orig CG 0x13e0.
- Result: CG +4, POD +4, LG +2, SCD +2 MATCH. LG/SCD `CheckMinMaxBoundary`, `Dump` stay DIFF only by the
  `FILE_NAME` literal (`..\Shared\` in LG/SCD, `..\..\Shared\` in CG/POD). One shared obj, see "header `__FILE__`".

## Build fact (lift-parity-s3): no header dependency tracking
- `tools/vs2010/build.sh` rebuilds an obj only when its `.cpp` is newer. A header change needs `touch` of the
  `.cpp` files that use it, or `.scratch/run.sh clean`.

## Pattern 27 (part worked, lift-parity-s3): inline BnsCommonConfig ctor copies ID128_GUID_ZERO
- Orig CG 0x13e0 / 0x1600: `mov rcx,[0x46be8]` / `mov rax,[0x46bf0]` (two qword loads), so the ctor does
  `_npAppId = ID128_GUID_ZERO; _npClientAppId = ID128_GUID_ZERO;`. 0x46be8 is in read-only data.
- Fix: `extern id128 ID128_GUID_ZERO;` in StringUtil.h, define in StringUtil.cpp (❓ module), assign in the ctor.
- Result: no MATCH, but Load/ReloadBnsCommonConfig score +1.0..+1.3 in all 4 exes. Kept.
- POD Reload still shows one `ID128_GUID_ZERO` ref less than orig (orig loads the global two times).

## Pattern 28 (worked, lift-parity-s3): null-checked placement new before the null test
- Cause: `if (memory == nullptr) {fail} new (memory) T();` puts the fail block inline. Orig puts it at the end.
- Fix: `T* p = memory != nullptr ? new (memory) T() : nullptr; if (p == nullptr) {fail}`.
- Example: `BnsCommonConfig::ReloadBnsCommonConfig` -> MATCH in CG; LG/SCD/POD score +2.2.

## Did not work (lift-parity-s3): move the `failed:` tail into the first error block
- `LoadBnsCommonConfig`: orig falls through from the "load failed" block into the tail. A `failed:` label
  inside that block gives the same code as the tail at the end. The Log::Write call-order diff stays.

## Pattern 29 (worked, lift-parity-s3): inline destructor with a member destructor gives the EH state
- Cause: orig `Db::Clear` stores EH state -2 (`#wind=1`). It calls an inlined `~Db()`: the Dsn free, then
  the member `~CriticalSection`. Open code (Free + DeleteCriticalSection) has no unwind map.
- Fix: `inline Db::~Db()` (Dsn free) in Db.cpp, `db->~Db();` in Clear.
- Example: `Db::Clear` -> MATCH in SCD and POD.

## Did not work (lift-parity-s3): merged FD_CONNECT/FD_WRITE branch in AlertSender::run
- Orig (CacheGate 0x98f0) zeroes the 44-byte WSANETWORKEVENTS with 5 qword + 1 dword inline stores.
  VS2010 cl (/O2) gives a `memset` call for both `= {0}` and `memset(&events, 0, 44)`.
- One `?:` error select with one sendRemain call: score 97.8 -> 94.4 (cmovne, const 0x12). Undone.

## 30. Per-exe source path literal (FIXED, stage 8)
- Cause: the original builds a shared .cpp in each exe project. The file literal is relative to the project
  directory. BnsCommonConfigDefinition.cpp: CG, POD `..\..\Shared\`; LG, SCD `..\Shared\`.
  ThreadFreePacketPump.cpp: LG `..\Economy\Shared\`; POD `..\Shared\`. One obj for 4 exes gives a ref DIFF.
- Change: the literal is a macro with `#ifndef` default. A wrapper .cpp (`BnsCommonConfigDefinitionShortPath.cpp`,
  `ThreadFreePacketPumpShortPath.cpp`) sets the macro and includes the .cpp. CMakeLists.txt puts the plain file or
  the wrapper in each exe target (not in lift_common). tools/vs2010/build.sh compiles each source one time
  and has no per-target defines, so a wrapper file is necessary.
- Example: LG BnsCommonConfig::Dump, POD ThreadFreePacketPump::Initialize -> MATCH. LG +7, SCD +2, POD +5.
- Side effect: .rdata moved, more string_at noise (lesson 2): LG Memory::CreateManager, POD Console/LogFile.

## Pattern 22 (worked, lift-parity-cg-1): PDB map allocator has no `const` in the pair
- Cause: PDB map types are `StlAllocator<std::pair<K, V>,2>`. Ours used `pair<K const, V>`, so the `_Tree` callee names differ.
- Source: `CacheD.h` CacheDMap, `ClientManager.h` SessionMap and IndexMap use `std::pair<K, V>`.
  With `ClientManager::GetSession` (2 `Leave` calls, null `second` exits) and the version-check `return false`
  in `CacheDList::LoadCachedListConfigFile`: CG MATCH 374 -> 380, other exes +0. Example: `ClientManager::ReleaseSession` 0x6250.

## Noise (lift-parity-cg-1): `_Buynode<std::pair<K const ,V>>` vs `<K const,V>`
- Orig PDB demangles with `const ,`, ours with `const,`. Only this differs in `CacheDList::add` 0x3490 and
  `ClientManager::AddSession` 0x6120. Not fixable in source. Tooling card: normalize `const ,`.

## Pattern 31 (worked, lift-parity-cg-1): handler table dispatch as a tail call
- Cause: `return handler != nullptr && handler(s, p);` converts the result to bool, so the call is not a tail jump.
- Source: `if (handler == nullptr) return false; return handler(s, p);`. Example: `CacheDChannel::PacketHandler` 0x4150 -> MATCH.

## Pattern 32 (worked, lift-parity-cg-1): `__forceinline` on an in-class ctor that the orig never emits
- Cause: ours emitted `CacheD::CacheD` out of line (only in ours). Source: `__forceinline CacheD()` in `CacheD.h`.

## Part worked (lift-parity-cg-1): HandleCacheGateHello 0x4c00 block order
- Early return for both version checks, then `if (GetSession == nullptr) {add path} else-tail {duplicate}`, read
  `CacheGate::_instance->_clientManager` at each call: calls 68 -> 88. Nested `==4`/`==10` ifs gave 63 (worse).
- Batch 2 (CacheD Verify/LoadCachedListConfigFile/Initialize swprintf_s, onConnect order, TryConnect noinline): CG 380 -> 382.
- Else-if chain with one shared `return false` (no early returns): score 87.2 -> 88.9, still DIFF. Undone (rule: MATCH only).

## Pattern 33 (worked, lift-parity-cg-1): branch order is the inverse of the HR `if`
- Cause: VS2010 puts the `else` block of the source first when the HR shows `if (x != 0) A else B`.
  The HR condition is the inverse of the source condition.
- Change: write `if (x == 0) { B } else { A }`. Example: CacheDChannel::onConnect 0x3c80
  (`if (ret == 0) { Send; Log 80 } else { Log 83 }`): DIFF 92.2 -> MATCH. CG 384 -> 385.

## Did not work (lift-parity-cg-1)
- Inlined PipeConsole find with `node = nullptr; for (...) { if (wcscmp == 0) { node = it; break; } } if (node == nullptr)`
  in CacheD::Initialize 0x2430 and CacheDChannel::onClose 0x3e40: const 0x278 stays (`add rbx,0x278`). No gain.
- `_cachedMap = new (Alloc(...)) CacheDMap();` in CacheDList::Initialize 0x2660 (compiler null check): const 0x3c stays
  in `lea r9d,[rdi+0x3c]`. No gain.
- CacheD::Verify 0x2530 with the fail test first (`!=`, early return): same score 91.7 as the HR form.
- `__declspec(noinline)` on `_Tree::clear`: no gain (CacheDList::clear, RemoveSessionAll still call `_Erase`).
- Tool fact: tools/vs2010/build.sh rebuilds an object only when the .cpp is newer than the obj. It does not
  track headers. After a header edit, run `rm -rf build-vs2010/obj`.

## Pattern 34 (worked, lift-parity-lg-1): force-inline the handler prologue, crash block last, GetId at the log call
- Cause: the LobbyD handlers call `LobbyDHandlerChannel` (lift helper, Session::GetChannel + crash log). VS2010 did
  not inline it (it is called 22 times). The orig inlines it, puts the crash log at the end of the function, and calls
  `Channel::GetId` inside each `Log::Write` argument list (after `Packet::Decompose`), not one time at the start.
- Source change (LobbyDPacketHandler.cpp): `static __forceinline` on the helper; helper form
  `if (ch != nullptr) return ch; Log; Alert; return nullptr;`; the `LD_ERR`/`LD_DBG` macros pass `ch->GetId()`; no `chId` local.
- Also a lift error: `HandleLobbyLobbyGate_HelloFail` 0xb750 did not call `SetEvent(LobbyD::_helloEvent)`. Added.
- Result: HelloFail, UpdateWorldInfoListNotify, CloseAnonymousSessionNotify, GetCharacterInfoListOk, ListGoodsOk MATCH;
  the other 17 LobbyD handlers +5..+30 score. Use the same form for the Client.cpp and LobbyGatePacketHandler.cpp helpers.

## Noise fact (lift-parity-lg-1): each layout move changes about 8 string_at MATCH in LG
- Any code size change moves vtable slot 0 addresses. LG then loses or gains vtable-only functions (Console, LogFile,
  Thread, PipeConsole, WinMsgHandler, WindowConsole, AlertSender ctor). A funcdiff tooling card (lesson 2) is needed to
  measure exe-only progress without this noise.
- Cause in tools/funcdiff.py line 230: `img.string_at(t)` is tried before `target_name(t)`. A fix is to prefer a
  `??_7` vtable name over string_at. tools/ is not in the files of this card (not changed).
- The parity gate fails when the MATCH count goes down (`m < bm`), also when allow-worse.txt has each lost name.

## Facts (lift-parity-lg-1, stage 2, not yet tried)
- `Packet::~Packet` is `{ Clear(); }` (Packet.cpp). ICF folds it with `Packet::Clear`, so funcdiff shows a dtor as
  `Packet::Clear`. The orig LobbyD handlers have one Clear per path: no explicit `p.Clear()`, a `return` in each
  branch (dtor). Ours has `p.Clear()` + dtor (BypassPacket 0x121d0: 2 extra Clear) or one merged dtor (KickNotify 0x10660).
- Orig tails merge `ch->removeReferenceCount(HANDLER_FILE, line)` with the line in a register (KickNotify 1454/1463,
  CloseSessionNotify 1408/1417, GetEnterWorldTokenOk 2110/2118, BypassPacket 2169/2178). Source form: if/else with
  one shared `return true`, no early return. The decompose-fail path keeps its own remove + return.
- HandleLobbyLobbyGate_TakeGoodsOk 0x113e0 has `$__FINALLY_0` in the HR: the source uses `__try { ... __leave; }
  __finally { if (itemList) Free 1850; pcb->Clear(); if (client) remove 1855; ch release }`. The decompose-ok path is
  first in the orig. Probably the same for GetServiceEntryListOk 0x11b60 and ListLobbyServiceItemInfoOk 0x117a0.

## Results (lift-parity-lg-1, stage 3)
- Worked: BypassPacket 0x121d0 -> MATCH. Source: no `p.Clear()`; `if (client == nullptr) {2168/2169} else {
  if (session == nullptr) {2176-2178} else { Packet p; ... each compose branch `return true;` } } return true;`.
- Worked: KickNotify 0x10660 84.2 -> 99.4. Source: early `return true` after each error block (null client, null
  session, compose fail), no `p.Clear()`. VS2010 cross-jumps the 1454/1463 removes by itself.
  Left: one `LobbyGate::_instance` ref (see below).
- Did not work: positive conditions first (`if (client != nullptr)`, `if (Compose)`). The orig puts the error
  blocks first in address order. KickNotify fell to 88.3, GetEnterWorldTokenOk to 94.0.
- GetEnterWorldTokenOk 0x11ee0: early-return form and if/else form both 98.1. Ours merges the decompose-fail
  remove (2101) into the shared remove tail. The orig keeps a separate remove for 2101 (HR line 5417). Cause unknown.
- CloseSessionNotify 0x10440: `client == nullptr` block first = 96.8 (better than 94.5). Left: one `_instance` ref.
- `_instance` reload: the orig reads `LobbyGate::_instance` again for AddJobTimer after AcquireClient. Ours (built
  with /GL /LTCG, tools/vs2010/build.sh) keeps it in a register. ClientManager::AcquireClient is MATCH. The orig
  writes `_instance` only in wmain 0x128b0, the same as ours. No `&LobbyGate::_instance` in the orig HR. Cause unknown.
- Shared: `RefCntObject::addReferenceCount` is DIFF 83.3 in LG only because `REFCNT_HEADER`
  (src/Server/BloodLib/source/RefCntObject.cpp:13) is the CacheGate path. The LG orig uses
  `lobbygate-common-0.0.348`. Same kind: StlMemory.h:9, MemoryManager.cpp:7, Channel.cpp:21 (CacheGate paths).
  A per-exe path macro (as `LOBBYGATE_CHANNEL_HEADER_FILE` in Channel.cpp:23) can fix this. Check all 4 exes.

## Pattern 35 (lift-parity-lg-1, stage 4): per-exe RefCntObject.h and MemoryManager.h paths
- Original paths: RefCntObject.h lower case `<exe>-common-0.0.348\...`; MemoryManager.h `<Exe>-Common-0.0.348\...`
  (CG, LG, SCD; POD pseudocode has no MemoryManager.h path).
- Source: `#ifndef` default (CG path) in RefCntObject.cpp and MemoryManager.cpp. Wrappers
  `RefCntObject<Exe>.cpp`, `MemoryManager<Exe>.cpp` (LG, SCD, POD). The 2 files leave lift_common.
- First try (files in CG SOURCES and in each exe lib): LG 462 -> 477, SCD +7, POD +4, but CG -1
  (Crypto::Destroy string_at noise) and SCD AlertSender::AlertSender, POD AlertSender, PipeCommandProcess,
  PipeConsole, Thread, WinMsgHandler destructors MATCH -> DIFF (string_at noise, refs only).
- Cause of the noise: tools/vs2010/build.sh sorts the objects of each target. Objects in CG SOURCES link before
  the Security objects, so the Blowfish vtable moves.
- Second try: libs `lift_common_cg/lg/scd/pod` whose names sort after lift_common. The libs need `/GR-` (else
  lld-link: undefined `type_info::vftable` from the RTTI of RefCntObject). CG was still -1: the 2 objects left
  their sorted place inside lift_common.
- Third try (worked): `LIFT_COMMON_SOURCES` list. `lift_common` = list without the 2 files (LG, SCD, POD + per-exe
  libs `lift_common_lg/scd/pod`). `lift_common_cg` = full list with the 2 files, so CG keeps its old object order.
  Result: CG 385 (+0), LG +15, SCD +7, POD +4. The SCD/POD MATCH -> DIFF losses are string_at noise (refs only);
  they are in allow-worse.txt.

## Pattern 36 (worked, lift-parity-lg-1): one shared cleanup tail and `__try/__finally`
- Cause: the original handler has one tail (`pcb->Clear()`, release). Our "decompose packet fail" branch had its
  own copy of `Clear()` + release + `return`: one extra `<indirect>` call.
- Source change: `goto cleanup;` in that branch. TakeGoodsOk 0x113e0, GetServiceEntryListOk 0x11b60: MATCH.
- When HR shows `$__FINALLY_n` and reloads the list pointer in the item loop, use `__try { ... __leave; }
  __finally { free }` inside an `else` of the decompose-fail `if`. ListLobbyServiceItemInfoOk 0x117a0: MATCH.
- Only these 4 LG functions have `$__FINALLY` in the HR (all MATCH now).

## Pattern 37 (worked, lift-parity-lg-1, stage 6): inlined Packet constructor with one pool buffer
- Orig `ClientManager::BroadcastAnnounceNotify` 0x62c0 sets `Splitter`, `IsFragmentPacket`, a 28-byte zero fill, then
  `ListTail = PacketBufferPool::allocate(TLS)`, `ListHead = ListTail`, `CurHeader = &Buffer[8]`, `size = 2`.
- Source: `Packet packet = {nullptr, false};` then the 4 stores with `PacketBufferAllocator::_Local->allocate()`.
  Also `__declspec(noinline)` on the function (our build inlined its first part into the caller).
- Gain: caller `HandleLobbyLobbyGate_AnnounceNotify` 0xbce0 MATCH (LG 480 -> 481). Callee 69.8 -> 92.1.
- Still DIFF in the callee: orig merges the two LT_ERROR `Log::Write` calls and has one `Packet::Clear`; ours has two.

## Tool fact (lift-parity-lg-1, stage 7): `tools/vs2010/build.sh` does not track headers
- It rebuilds an object only when the `.cpp` is newer than the `.obj`. After a header change, `touch` each `.cpp`
  that includes the header. Else parity measures the old code.

## Pattern 38 (worked, lift-parity-lg-1, stage 7): STL map allocator with a non-const pair key
- Cause: the orig PDB names are `StlAllocator<std::pair<__int64,X>,2>` (key not const). Ours had `pair<__int64 const,X>`.
  With ICF, the orig folds the `_Buynode`/`_Linsert`/`erase` of all 3 LG maps to the `Client *` names.
- Source change: `Client.h` typedefs use `StlAllocator<std::pair<long long, X>, 2>`. Insert with
  `std::pair<long long, X>(k, v)` (orig `_Buynode<std::pair<__int64,Client *>>`), not `value_type(k, v)`.
- Example: `ClientManager::RemoveClient` 0x60c0 MATCH.

## Pattern 39 (worked, lift-parity-lg-1, stage 7): branch order of `Clone` and an empty member destructor
- `ClientPacketBufferHandler::Clone` 0x21920: orig tests `buffer == nullptr` first (`lea r9d,[rdx+0x62]` uses the
  known zero). Write the alloc path in `if (buffer == nullptr) {...}`. MATCH (also `TrustedPacketBufferHandler::Clone`).
- `FragmentPacket::~FragmentPacket` 0x24e0: orig is `add rcx,8; jmp Packet::Clear`. The body must be empty: the
  member `~Packet` does the Clear. An explicit `packet.Clear()` gives two calls and an EH frame. MATCH.
