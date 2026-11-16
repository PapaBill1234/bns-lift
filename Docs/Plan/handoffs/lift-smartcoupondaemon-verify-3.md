# lift-smartcoupondaemon-verify-3 handoff

## Done
- Gate build of 1013fcb (368128 B), then `SCD_CERT=sql tools/verify/compare_smartcoupondaemon.sh 20 --pktlog` 2 times. Same result in each run.
- Lifted exe passes the DB step, listens on 22000 and 32000 (same as the original), sends the same STS `/Sts/Connect` (254 B) to NP, accepts the manager and daemon clients. 96 log lines in each exe.
- 6 of 7 diffs: 0 changed lines (ports, peer-np, peer-gamed, client-manager, client-daemon, pkl).
- Checks 1, 3-8 pass. Check 2 fails on the version string only. Check 9 open.
- `Docs/Verify/SmartCouponDaemon.md`: status, noise, checks, differences and next steps updated.
- Script fix (`tools/verify/compare_smartcoupondaemon.sh`): 3 new noise rules: `event object handle failed, id: N`, `loading time: N`, ephemeral port in `accepted from ... port:N, socket:`.

## First difference
- log `Daemon.cpp,496` and `Daemon.cpp,545`: `version:` original `0.0.348.352`, lifted empty.
- `Daemon::LoadVersion` 0xBB30 reads the VERSIONINFO resource. The lifted exe has no VERSIONINFO resource. Build fault, not a code fault.

## Not queued
- No lift-smartcoupondaemon-7 / verify-4 cards. The first fault is not new (open since round 1, address 0xBB30 is already lifted and correct). The fix is a resource in `cmake/` or `CMakeLists.txt`, not a src lift.
- Suggested build card: add a VERSIONINFO resource (FileVersion 0.0.348.352) to the SmartCouponDaemon target.

## ❓
- Check 9 (381 NP / GameDaemon accepts the 2019 protocol): no 381 NP or GameDaemon runs (only `bns-mssql`).
- Handlers 0x7DC0, 0x8360, 0x8E80 are not tested with data (no Hello input stream).

## Blocked
- Nothing.

## Gate result
`gate ok` (before the runs; no src change in this card).
