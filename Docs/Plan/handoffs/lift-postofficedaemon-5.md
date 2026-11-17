# lift-postofficedaemon-5 handoff

## Done
- PostOfficeDaemon.cpp (36, with wmain, _instance, PostOfficeConfig::_Def), PostOfficeDB.cpp (10, with AutoDbTran dtor 0x14e00),
  WorldConfigManager.cpp (24), UnsentPostContext.cpp (9), UnsentPostChecker.cpp (1). Total 80 functions.
- CacheGateChannel.cpp: ~CacheGateChannel 0x12c30, GetId 0x5d860 (ICF fold, returns 0), ~CacheGateSessionHandler 0x12c20.
- CMake: exe PostOfficeDaemon (lift_exe). XmlReader_sv64.dll, bsConsole_sv64.dll, dbghelp.dll still load at run time.
  vendor/zstd is not in this worktree, so the exe links src/crt/zstd_stub.c when the lift_zstd target is missing.
- common: id128 in StringUtil.h (PDB guid layout + id[2]); Db.h/.cpp full-signature BindCol 0x2d010, BindParam 0x2d190.

## PostOfficeConfig::_Def (0x97ab0, 23 rows) vs BnsCommonConfig.cpp:43-90
- PostOfficeConfig has no p-type, np-program-id, np-game-code, np-app-id or np-client-app-id rows. It does not use BnsCommonConfig.
- It has its own rows: path (root/log/config), cert-file, worker-thread, max-agent/world-session-count, dump-type (2),
  relay-timeout-interval (15), ping-interval (60), delivery-retry-interval (5), agent/world/manage port (20500/20501/30500),
  cachegate-ip-address ("127.0.0.1"), cachegate_listen-port (20800, "_" in the original), service-world-id (1010, required).

## Not done / stubs
- src/PostOfficeDaemon/LinkStubs.cpp: ClientSideDaemonChannel::onAccept (CacheGate 0x40B0). The PostOfficeDaemon has
  no ClientSideDaemonChannel vftable; Channel.cpp emits it, so the link needs a body. TODO(lift-postofficedaemon-5).

## ❓
- PostOfficeDB: Fetch(0) argument; BindCol size 0 for fixed types; the no-row text tail at 0x18010 ("recipientPcId").
  The 87 binds and the row-to-PostContext code are inlined in each loader; I wrote them as local helpers (not PDB names).
- BUG marks: 0x14e50 (and the other loaders) no null check after both Allocs; 0x16f20 null attachedItemList logs, no return.
- From the earlier stages: MakeSession args (0,true), nagle, LogFile args (1,0)/_enable, fopen "rb", buffer 1008,
  _Def desc tails (rows 11, 13), a127001 = 3276849, addNode L"", IsServiceAvailable/GetCacheGateChannel names, id128 ops.

## Blocked
- None.

## Gate result
- `tools/gate.sh`: `gate ok`. PostOfficeDaemon.exe links.
