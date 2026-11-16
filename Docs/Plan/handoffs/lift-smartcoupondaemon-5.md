# lift-smartcoupondaemon-5 handoff

## Done
- Applied the `src/common/` part of `Docs/Verify/CacheGate-fixes.patch` (DaemonConfig.h Initialize order and more). CacheGate and LobbyGate still build.
- `EventNotiJob::_pool` is a static `ObjPool` object (0x52A30). `Dump(L"config")` in 0x150E0.
- Lifted modules (new .cpp, in CMakeLists.txt): CouponJob, Db, EventNotiJob, SmartCouponDB, GameEventWorker, DaemonChannel, DaemonPacketHandler, SmartCouponPacketSmartCouponSideHandlerList, CouponGameEventConfig, NPChannel2 (0x4350..0x5D50), NPServiceChannel (9 functions, 0xFD80..0x10700), NPMessageHandler (0xFBC0).
- NPChannel.h rewritten. `Connection::GetLocalAddress` 0x2AEA0 added to `src/common/Connection.cpp`; `friend class NPChannel` in Connection.h.
- LinkStubs.cpp: no `TODO(lift-smartcoupondaemon-5)` stub. Only `ClientSideDaemonChannel::onAccept` (❓) stays.

## Not done (not in this card)
- HandleSmartCoupon_HelloReq 0x7DC0, HandleSmartCoupon_GameEventByCharacterReq 0x8360, HandleSmartCoupon_GameEventByAccountReq 0x8E80, GameEventLogEvent::EventId 0x7D80.

## Smoke test (`run_smartcoupondaemon.sh lifted 15`)
- 55 log lines. No 0xc0000417. No `_pool` page fault. The pool initializes (id:1 EventNotiJob, 4096).
- New fault 1: right after the pool init: `RefCntObject.h,129 destructring with not zero reference count, ref:1, tag:0xfa`. Probably a RefCntObject on the stack or freed too early in the 0x150E0 path (JobManager/TimerQueue?).
- Workers start (GameEventWorker run lines).
- New fault 2 (last line before crash mail): `Network.cpp,175,(error),== CRASH == ASSERT CRASH`. No port listens.

## ❓
onAccept body; Console/Session/TimerQueue/Connection friends; GetKind, EventId; TLS buffers; registry ctor; ReleaseAll vector type; JobManager::ExecuteW args; ~NPServiceChannel; GuidParts helper; second registry check in 0xFD80.

## Blocked
None.

## Gate result
`gate ok` (CacheGate.exe, SmartCouponDaemon.exe link).
