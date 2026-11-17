# lift-parity-s1 handoff

## Done
- MATCH against the baseline: CG 293 -> 331, LG 377 -> 400, SCD 334 -> 367, POD 375 -> 407. `tools/parity.sh`: parity ok. `tools/gate.sh`: gate ok.
- Patterns 1, 3-13 in `Docs/Parity/lessons.md` (BaseMemoryManager calls, swprintf_s<N>, noinline, if chains, string sizes, one reconnect label).
- Files: `include/MemoryManager.h`, `include/vs2010/crt_cpp_overload.h`, 15 files in `src/Server/BloodLib/source/`, `Docs/Parity/allow-worse.txt`, `Docs/Parity/lessons.md`.
- `allow-worse.txt`: only string_at noise (vtable symbol read as a 2-byte string). Each line gives the reason.

## Not done (function, signal, cause, why stopped)
- `PipeConsole::run` 0x157b0: calls 89. One call site now, block order differs. Label place, switch or if chain: no change.
- `PipeConsole::SetInvalidInfo` 0x15d90: calls 89. Orig has 2 `addNode` call sites (tail duplication). Split loops inline it into SCD `OnConnect`.
- `PipeConsole::SetRunningInfo` (LG): calls 60, consts 86. Not examined; time.
- `PipeConsole::processCommand` 0x14fa0, `PipeCommandProcess::processCommand` 0x14ad0: consts 89-91. `wcscmp` result kept. ❓
- `PipeConsole::checkFrozenThread`, `addNode` (LG only): refs 80-89. Probably string_at noise; not proved.
- `Daemon::start`: calls 96, refs 86-88. `Daemon::Start`: consts 89. `Daemon::Daemon`, `Daemon::LoadVersion` (LG): consts 89-92. Not examined; time.
- `Daemon::setAddress`: consts 92-98. TLS order (link order). Tooling card.
- `ThreadManager::entry` 0x13140: consts 0. TLS index order. Tooling card.
- `ThreadManager::Initialize`: consts 67. Constant propagation differs. No fix found.
- `CrashHandler::handleCrash` 0x8840: calls 96, refs 93, consts 95-98. `InitSymbol`: calls 91, refs 95. Not examined; time.
- `StaticPageMemoryManager::Initialize(void*, ...)`: refs 89. Header `__FILE__` per exe. ❓
- `StaticPageMemoryManager::AllocZero/Clear/Realloc/ReallocZero/Initialize(virtual)`, `RefCntObject::*`, `Thread::~Thread`, dtors with refs 0-67: string_at noise (vtable). Tooling.
- `TimerQueue::clearShortTermQueueSlot` 0x264f0: calls 36. LTCG inlines `removeReferenceCount`. Header-inline test: no gain.
- `TimerQueue::~TimerQueue` (SCD, POD): refs 83. Not examined.
- `WinServiceConsole::UninstallService` 0x17f00: calls 98. Orig merges the `CloseServiceHandle` tail.

## ❓
- TLS order, header `__FILE__` per exe, string_at noise: tooling card (`tools/funcdiff.py`).
- build.sh does not track headers: after a header change run `rm -rf build-vs2010/obj`.

## Blocked
- None.

## Gate result
- gate ok; parity ok (CG 331, LG 400, SCD 367, POD 407; no MATCH lost except allow-worse lines).
