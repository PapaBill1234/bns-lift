# lift-postofficedaemon-verify handoff

## Done
- `tools/verify/run_postofficedaemon.sh`: runs one exe under wine64 (log, ports, CacheGate peer, clients, pktlog, SQL DB).
- `tools/verify/compare_postofficedaemon.sh`: runs original and lifted, writes `build/verify/pod-compare/*.diff`.
- `tools/verify/fixsrc_postofficedaemon.sh`: builds a src copy with `Docs/Verify/PostOfficeDaemon-fixes.patch`.
- `tools/verify/pod_streams.py`: Task 4 input streams (CacheGate HelloOk, agent hello, world hello, manage text).
- `Docs/Verify/PostOfficeDaemon.md`: result of each check (9 checks) and each difference.

## Result
- Lifted exe of bd20e24 (gate build): crashes at start (`Network.cpp,175 ASSERT`, manage port 30500 not opened).
  Cause: `initNetwork` calls the CacheGate `Network::OpenPort` 0xD2C0, not the PostOfficeDaemon one 0x28AB0.
- Lifted exe with the fix patch: starts, listens on 20500 20501 30500 (same as original). CacheGate peer bytes,
  client replies (agent and world hello ack `04000200`), and pkl are the same with and without input streams.
- Log differences: only `version:` (no VERSIONINFO) and timing values (timer tick count, DB loading time).

## Not done
- The fix patch is not applied to `src/` (outside this card's files). A lift card must apply it:
  `Network::OpenPort` 0x28AB0 in src/common and the 4 calls in `PostOfficeDaemon::initNetwork`; log tags of
  CacheGateChannel.cpp and `WorldConfigManager::` prefixes in WorldConfigManager.cpp.

## ❓
- Nagle args of `OpenPort` calls: port 1 false, port 4 true (pseudocode arg order of 0x28AB0 calls).
- Manage text "Hello" gives no reply in both exes. The command format can be wrong; both exes act the same.

## Blocked
- None.

## Gate result
- `tools/gate.sh` not run: this card changes only `tools/verify/` and `Docs/`. The fixsrc build links.
  Last compare (fixsrc, 25 s, --pktlog, streams): ports 0, peer 0, clients 0, pkl 0, log 6 lines (known).
