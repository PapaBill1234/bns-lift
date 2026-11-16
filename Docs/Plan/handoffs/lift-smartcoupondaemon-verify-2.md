# lift-smartcoupondaemon-verify-2 handoff

## Done
- Ran `SCD_CERT=sql tools/verify/compare_smartcoupondaemon.sh 20 --pktlog` 2 times (lifted = gate build of 8e56145). Same result in each run.
- Original: DB step passes, LISTEN 22000 and 32000, `start ... loading time: 2180`, 96 log lines, accepts the manager and daemon clients.
- Lifted: 55 log lines, no LISTEN. Checks 1-8 updated in `Docs/Verify/SmartCouponDaemon.md` (check 5 = same, others fail; check 9 open).
- Task 3: the original does not connect to the GameDaemon by design. The GameDaemon connects to 22000. `gamed-list.config.xml` is the list of known GameDaemons. `DChannelMgr` has only accept handlers. Cause = test setup.
- Script fix (`tools/verify/run_smartcoupondaemon.sh`): the listener on the gamed internal-port is off by default (`SCD_GAMED_PEER=1` turns it on). The `--client` connect to 22000 is the GameDaemon role.

## First difference (lifted does not listen)
- `Network.cpp,175 == CRASH == ASSERT CRASH` about 2 s after start.
- Lifted `SmartCouponDaemon.cpp:362/390/400` call `Network::OpenPort` 0xD2C0 (9 arguments) with `initialMode` 0. The check at `src/common/Network.cpp:196` fails.
- Original 0x150E0 calls `Network::OpenPort` **0x1A8B0** (5 arguments: portId, portNo, sessionHandler, bufferHandler, maxSession). It has no line-175 check and uses the mode-2 maxSession rule.
- Fix (src card): lift 0x1A8B0 and call it for ports 1, 2, 3.

## Other differences
- `RefCntObject.h,129 ... ref:1, tag:0xfa` after the pool init in the 0x150E0 path ❓ address. Not fatal.
- `version:` empty (no VERSIONINFO), extra `CrashHandler.cpp,490` line (from round 1).

## ❓
- `Port::Initialize` arguments at 0x1AA1E..0x1AA48 (initial mode, nagle).
- RefCntObject tag 0xfa: which object.
- Check 9 (381 NP / GameDaemon accepts the 2019 protocol).

## Blocked
- Lifted behaviour after the DB step (checks 3, 4, 6, 7, 8): needs the src fix above. This card can change only `tools/verify/` and `Docs/Verify/`.

## Gate result
`gate ok` (before the runs; no src change in this card).
