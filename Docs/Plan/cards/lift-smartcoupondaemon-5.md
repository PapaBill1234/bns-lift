# lift-smartcoupondaemon-5: SmartCouponDaemon lift: startup fixes and stub bodies

Repo: bns-lift (PRIVATE). IDA database: `<work-root>/ida/lift/SmartCouponDaemon/SmartCouponDaemon.exe`. PDB: `<work-root>/Service_348_8349/Service/SmartCouponDaemon/bin/SmartCouponDaemon.pdb`.
Read `Docs/Plan/plan.md` "Lift method" first. Read `Docs/Plan/handoffs/lift-smartcoupondaemon-4.md` and `Docs/Plan/handoffs/lift-smartcoupondaemon-verify.md`. Read `Docs/Verify/SmartCouponDaemon.md` "Differences" and "Next steps".

## Facts
- The lifted exe stops at once with 0xc0000417 (0 log lines): `_wcsicmp(NULL, L"root-path")` in `XmlReader_sv64.dll` +0x649D. Cause: the `XmlConfigReader::Initialize` overload order in `src/common/DaemonConfig.h`.
- `Docs/Verify/CacheGate-fixes.patch` has the fix. Its `src/common/` part was never applied to `src/`. Other LobbyGate cards may have changed `src/common/` since. Check each hunk before you apply it.
- `tools/verify/fixsrc_smartcoupondaemon.sh` applies the fixes to a copy. With it, the exe stops with a page fault at 0x14000BC88: `EventNotiJob::_pool` is a null `ObjPool*`. The original has a static `ObjPool` object (dynamic init 0x52A30).
- `JobManager::Initialize` is a stub that returns false (`LinkStubs.cpp:40`). 0x150E0 calls it after the pool.
- `src/SmartCouponDaemon/LinkStubs.cpp` has about 40 stubs marked `TODO(lift-smartcoupondaemon-5)`.

## Tasks
1. Apply the `src/common/` part of `Docs/Verify/CacheGate-fixes.patch` to `src/`. Do not break CacheGate or LobbyGate: `tools/gate.sh` builds all exes.
2. Make `EventNotiJob::_pool` a static `ObjPool` object, as in 0x52A30.
3. Pass `L"config"` to `DaemonConfig::Dump` in `SmartCouponDaemon::initialize` (0x150E0, `SmartCouponDaemon.cpp:288`).
4. Lift each stub in `LinkStubs.cpp` into its PDB module `.cpp`. Start with the startup path of 0x150E0: `JobManager`, `GameEventManager`, `DChannelMgr`, `NPChannel`, `NPServiceChannelManager`, `Db`, `SmartCouponDB`. Then remove the stub.
5. Run `tools/gate.sh` after each module.
6. Optional smoke test: `tools/verify/run_smartcoupondaemon.sh lifted 15`. Write the last log line in the handoff.

## Files
- `src/SmartCouponDaemon/`
- `src/common/`
- `include/pdb/`
- `include/vs2010/`
- `CMakeLists.txt`

## Done when
- `LinkStubs.cpp` has no `TODO(lift-smartcoupondaemon-5)` stub, or the handoff lists each one as Not done with the address.
- The lifted exe does not stop with 0xc0000417 or the `EventNotiJob::_pool` page fault.
- `tools/gate.sh` prints `gate ok`.
