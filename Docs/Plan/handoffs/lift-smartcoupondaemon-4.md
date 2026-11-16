# lift-smartcoupondaemon-4 handoff

## Done
- Static lib `lift_smartcoupondaemon` (CMakeLists.txt) with 5 modules, 44 functions:
  - SharedChannel.cpp (6), ManagerChannel.cpp (6), ManagerPacketHandler.cpp (5), SmartCouponManagerPacketSmartCouponSideHandlerList.cpp (2).
  - SmartCouponDaemon.cpp (25): getters, Alloc, GenerateJobid, wmain, dtor, init/net/start/shutdown/reload/cooldown, NP start, unhandled loads, `SmartCouponConfig::_Def[23]`.
- src/common/Session.{h,cpp}: Session::GetChannel (0x1D330).
- Headers only (declarations for later cards): ObjectPool.h, CouponJob.h, EventNotiJob.h, Db.h, NPChannel.h, DaemonChannel.h, CouponGameEventConfig.h, SendPublicationEvent.h, SmartCouponDB.h, GameEventWorker.h.

## Not done
- These modules are not lifted. The exe links only with the stubs in LinkStubs.cpp:
  - SmartCouponDB 0x10850-0x145F0, CouponJob 0x6990-0x7540, EventNotiJob 0x9890-0xA9D0.
  - GameEventWorker 0xAA80-0xC7D0, CouponGameEventConfig 0x2A40-0x3580.
  - DaemonChannel 0xC8C0-0xDFE0, DaemonPacketHandler 0x7D30-0x8E80, SmartCouponPacketSmartCouponSideHandlerList.
  - ObjectPool (ObjPool, ObjPoolTimer 0x1940, allocator Free), Db, NPChannel/NPServiceChannelManager.

## ❓
- Network::OpenPort mode and bool args (initNetwork). LogFile ctor args (1, 0). `_logFile->_enable[2]=false` is a comment only.
- ObjPoolTimer::Start(1000), SetDetectFrozenThread(true, 0), ObjPool::Initialize(vtbl, initJobCount, reuseWaitTime).
- ObjPool::Finalize receiver in shutdown. `_seed__` name. Default name `a127001` (3276849).
- Handler arg of Network::Initialize and GameEventManager::Initialize. DaemonConfig::Dump name arg.

## BUG marks
- 0x14AB0 old block leaks, VirtualAlloc not checked. 0x14C80 ConfigNoReload not set to null.
- 0x14F40 Alloc not checked. 0x150E0 strlen of null certFile, fp not closed. 0x161A0 no null check, event read after post.

## Blocked: None.
## Gate result: `tools/gate.sh` prints gate ok.
- Gate fix: `sizeof(ObjPool)` assert in ObjectPool.h changed from 0xA8 to 0xB0 (PDB size).
- Gate fix 2: `lift_exe(SmartCouponDaemon)` added. The exe links with stub bodies (`TODO(lift-smartcoupondaemon-5)`) in `src/SmartCouponDaemon/LinkStubs.cpp`, one per Not done symbol (incl. ❓ `ClientSideDaemonChannel::onAccept`). `src/crt/new_delete.c` now gives `operator new` (malloc), because the Wine msvcr100 import lib has no export for it.
