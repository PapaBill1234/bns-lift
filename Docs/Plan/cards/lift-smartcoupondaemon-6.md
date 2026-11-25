# lift-smartcoupondaemon-6: SmartCouponDaemon lift: OpenPort 0x1A8B0, RefCntObject fault, last handlers

Repo: bns-lift (PRIVATE). IDA database: `<work-root>/ida/lift/SmartCouponDaemon/SmartCouponDaemon.exe`. PDB: `<work-root>/Service_348_8349/Service/SmartCouponDaemon/bin/SmartCouponDaemon.pdb`.
Read `Docs/Plan/plan.md` "Lift method" first. Read `Docs/Plan/handoffs/lift-smartcoupondaemon-5.md` and `Docs/Plan/handoffs/lift-smartcoupondaemon-verify-2.md`.

## Facts
- The lifted exe stops with `Network.cpp,175 == CRASH == ASSERT CRASH` about 2 s after start. No port listens.
- Lifted `SmartCouponDaemon.cpp:362/390/400` call `Network::OpenPort` 0xD2C0 (9 arguments) with `initialMode` 0. The check at `src/common/Network.cpp:196` fails.
- Original 0x150E0 calls `Network::OpenPort` 0x1A8B0 (5 arguments: portId, portNo, sessionHandler, bufferHandler, maxSession). It has no line-175 check. It uses the mode-2 maxSession rule. `Port::Initialize` arguments at 0x1AA1E..0x1AA48 ❓.
- After the pool init the log has `RefCntObject.h,129 destructring with not zero reference count, ref:1, tag:0xfa`. The object is not known ❓. The original does not log it.
- Not lifted: HandleSmartCoupon_HelloReq 0x7DC0, HandleSmartCoupon_GameEventByCharacterReq 0x8360, HandleSmartCoupon_GameEventByAccountReq 0x8E80, GameEventLogEvent::EventId 0x7D80.
- CacheGate and LobbyGate use `src/common/Network.cpp` too. Keep the 0xD2C0 overload. Add 0x1A8B0 next to it.

## Tasks
1. Lift `Network::OpenPort` 0x1A8B0 into `src/common/Network.cpp`. Call it for ports 1, 2 and 3 in 0x150E0.
2. Find the object with tag 0xfa. Fix the lifetime to match the original.
3. Lift the 4 functions in the "Not lifted" list.
4. Run `tools/gate.sh` after each step.
5. Smoke test: `SCD_CERT=sql tools/verify/run_smartcoupondaemon.sh lifted 15` (run `docker start bns-mssql` first). Write the listen ports and the last log line in the handoff. Never print the cfg file.

## Files
- `src/SmartCouponDaemon/`
- `src/common/`
- `include/pdb/`
- `include/vs2010/`
- `CMakeLists.txt`

## Done when
- The lifted exe listens on 22000 and 32000 in the smoke test, or the handoff gives the next fault with its address.
- `tools/gate.sh` prints `gate ok`.
