# lift-smartcoupondaemon-verify (round 1)

## Done
- `tools/gate.sh` builds `build/SmartCouponDaemon.exe`. The compare ran with the lifted exe.
- New `tools/verify/fixsrc_smartcoupondaemon.sh`: builds a test copy in `build/verify/scd-fixsrc/` with
  the `src/common` part of `Docs/Verify/CacheGate-fixes.patch`. The worktree `src/` does not change.
- `Docs/Verify/SmartCouponDaemon.md`: result of checks 1 to 9 and a differences table with addresses.
- Original: ports 22000 and 32000, 76 log lines, 1 STS `/Sts/Connect` (254 B) to NP. Self test 0 diffs.

## Not done
- The lifted exe does not listen. Done-when (same ports) is not met.
  - Committed src: 0xc0000417 at start (`XmlConfigReader::Initialize` overload order, DaemonConfig.h).
  - fixsrc: page fault at 0x14000BC88. `EventNotiJob::_pool` is a null `ObjPool*`. The original has a
    static `ObjPool` object (init 0x52A30).
  - Next: `JobManager::Initialize` is a stub that returns false (LinkStubs.cpp:40), in 0x150E0.
- Log differences: dump tag `[config]` vs `[smartcoupond]` (0x150E0), empty version (no VERSIONINFO),
  extra crash-mail line.

## ❓
- Crash-mail line: in some CacheGate runs only. Cause not known.
- Check 9 (381 NP / GameDaemon accepts the 2019 protocol): not run.

## Blocked
- Fixes are in `src/`, outside the Files of this card: apply CacheGate-fixes common part, fix
  `EventNotiJob::_pool`, `L"config"` tag. Lift stub modules (lift-smartcoupondaemon-5). Then run
  `tools/verify/compare_smartcoupondaemon.sh 15 --pktlog` again.
- Check 8 needs an ODBC driver and a SmartCouponDB schema.

## Gate result
- `tools/gate.sh`: gate ok (SmartCouponDaemon.exe, CacheGate.exe, lift_selftest.exe link).
