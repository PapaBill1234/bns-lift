# lift-cg-1 handoff: CacheGate memory, thread, timer, log, crash

## Done
- Modules in `src/common/` (44 functions with `// 0x<rva>`):
  MemoryManager (20), RefCntObject (12), Thread (10), Memory (1), BaseMemory (1).
- Headers for the later modules (declarations only): Log.h, AlertSender.h, Daemon.h, Lock.h,
  StlMemory.h.
- `CMakeLists.txt`: static library `lift_common`.

## Not done
- DelayedRelease, Timer, StringUtil, SystemInformation: not lifted.
- Log, LogFile, LogBuffer, LogMedia: not lifted (only Log.h declarations).
- CrashHandler, AlertSender: not lifted (only AlertSender.h declarations).
- The earlier session did not record the addresses of these functions. Get them from the
  PDB module sections (`llvm-pdbutil dump -symbols`).

## ❓
- Lock.h Enter/Leave, Thread/ThreadManager/Log constructors: inlined, names not in the PDB.
- RefCntObject::addReferenceCount (0x2150): the PDB has a bool argument; the code does not.
- RefCntObject::operator delete (0x20f0): argument use differs from the PDB names.
- Daemon.h: 3 members are opaque byte arrays (Daemon::Version, _cidraddress).

## BUG marks
- 0xdd10, 0x12e40, 0x1a2f0 (see the source comments).

## Blocked
- None.

## Gate result
- `tools/gate.sh`: gate ok.
- Fix: added a usual `RefCntObject::operator delete(void*)` (❓) and a `LPCWSTR` cast for `PathFindFileNameW` in RefCntObject.cpp; this fixed 5 compile errors.
