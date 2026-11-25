# lift-smartcoupondaemon-1: SmartCouponDaemon lift: log, alert, crash, timer, Db (common)

Repo: bns-lift (PRIVATE). IDA database: `<work-root>/ida/lift/SmartCouponDaemon/SmartCouponDaemon.exe`. PDB: `<work-root>/Service_348_8349/Service/SmartCouponDaemon/bin/SmartCouponDaemon.pdb`.
Read `Docs/Plan/plan.md` "Lift method" first. Read the handoffs of the earlier lift cards (`lift-cg-*`) for the state of `src/common/`.

## Modules (one `.cpp` + `.h` per PDB module, BloodLib, in `src/common/`)
Function counts are PDB symbol counts. They include EH funclets (`dtor$N`) and scalar deleting destructors.
- Log (12), LogFile (17), LogBuffer (16), LogMedia (4), AlertSender (15), CrashHandler (18) (82)
- Timer (19), DelayedRelease (7), StringUtil (1), SystemInformation (2) (29)
- Db (20). The exe imports ODBC32. Wine has `libodbc32.a`. Add it to the link libs of `lift_common`.
- Missing functions in modules that `lift-cg-1`, `lift-cg-2` and `lift-cg-4` lifted (SmartCouponDaemon RVAs):
  GrowingBuffer::grow 0x195A0 (Memory), Console::~Console 0x28590 (TextConsole),
  PipeConsole::SetDetectFrozenThread 0x25000, swprintf_s<128> 0x25E70 and swprintf_s<256> 0x25E40 (STL/CRT inline, use the CRT call),
  WindowConsoleOnLogoff / WindowConsoleOnShutdown 0x14AA0 (folded), Ripemd160::~Ripemd160 0x48730,
  Aes128::~Aes128 0x48A30, Prng::Generate 0x4CBF0. About 10 functions.
- About 141 functions.

## Notes
- Headers `Log.h`, `AlertSender.h`, `CrashHandler.h`, `LogBuffer.h`, `LogMedia.h`, `DelayedRelease.h`, `StringUtil.h`, `SysInfo.h`, `TimerQueue.h` already exist with declarations. Complete them. Do not make a second copy.
- The `// 0x<rva>` comments in `src/common/` are CacheGate RVAs. For new functions, write the SmartCouponDaemon RVA as `// 0x<rva> (SmartCouponDaemon)`.
- If a later run of `lift-cg-*` added a module of this card to `src/common/`, lift only the missing functions.

## Tasks
1. List the functions of each module from the PDB (`llvm-pdbutil dump -symbols`, section of the module) or from IDA.
2. Decompile them in batches to `.scratch/`. Lift them to C++ with the PDB types.
3. Add the files to `lift_common` in `CMakeLists.txt`.
4. Run `tools/gate.sh` after each module.

## Files
- `src/common/`
- `include/vs2010/`
- `CMakeLists.txt`

## Done when
- All functions of the modules are in C++, or listed in the handoff as Not done with the address.
- `tools/gate.sh` prints `gate ok`.
