# lift-smartcoupondaemon-4 handoff
## Done
- Research only. Facts are in `.scratch/` (facts-scd4.md, def.txt, types_app.txt, sigs.txt, <Module>.min.c). `.scratch/` is not committed.
- Common header additions for later use: src/common/{TimerQueue,Network,PipeConsole,SysInfo,CrashHandler}.h (18 lines).
- Lifted functions: 0. No src/SmartCouponDaemon/ files. No CMake target. No exe.
## Not done (all module functions; RVA ranges)
- SmartCouponDaemon (43): 0x14A30-0x161A0 (wmain 0x14B70, GenerateJobid 0x14B50, shutdown 0x15AD0).
- SmartCouponDB (25): 0x108A0-0x145F0.
- CouponJob (32): 0x6990-0x7540, 0x9890, 0x98D0.
- EventNotiJob (22): 0x9920-0xA9D0.
- GameEventWorker (28): 0xAA80-0xC7D0.
- CouponGameEventConfig (24): 0x2A40-0x3580.
- DaemonChannel (38): 0xC8C0-0xDFE0.
- DaemonPacketHandler (9): 0x7DC0, 0x8360, 0x8E80.
- ManagerChannel (8): 0xE7A0-0xEEC0.
- ManagerPacketHandler (8): 0xEF40, 0xF2F0, 0xF7F0.
- SharedChannel (7): 0x4270-0x67B0.
- Data tables: SmartCouponConfig _Def, handler lists.
- src/crt/wcrt0.c (wmainCRTStartup), CMake targets lift_smartcoupondaemon and SmartCouponDaemon.
- Next session: follow steps 1-7 in lift-smartcoupondaemon-4-progress.md.
## ❓
- DaemonConfig::Dump name arg; OpenPort args in initNetwork; SetDetectFrozenThread(true,0); `__seed__` name.
- shutdown calls ObjPool::Finalize with timer ptr (BUG?); DbTransaction::BindParam last args.
- loadUnhandledCouponPublication reads event after PostQueuedCompletionStatus (BUG/race?).
## Blocked
- None.
## Gate result
- Gate failed first: the handoff file was missing. Fix: wrote this handoff file. Rerun: `gate ok`.
