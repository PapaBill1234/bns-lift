# lift-smartcoupondaemon-verify: run the lifted SmartCouponDaemon under Wine and compare packet logs

Repo: bns-lift (PRIVATE). No IDA unless a difference needs it (`<work-root>/ida/lift/SmartCouponDaemon/SmartCouponDaemon.exe`).

## Goal
The lifted SmartCouponDaemon starts under Wine and sends the same packets as the original 2019 + PDB SmartCouponDaemon for the same input.

## Facts
- Original exe and config: `<work-root>/Service_348_8349/Service/SmartCouponDaemon/bin/` (`SmartCouponDaemon.exe` and the `*.config.xml` files in that folder). Do not print config values that are passwords or DB connection strings. Write `keyhere`.
- The exe uses ODBC32 (SmartCouponDB, Db). Under Wine the DB connection can fail. Then compare the behavior up to the DB error, and write it in the result.
- Packet log tools: `<bns-wine>/pktlog/` (`patch_import.py`, `pkldump.py`, `pktcover.py`). Read their usage lines only.
- The Wine server set in `bns-wine/` is the 381 set. The 2019 + PDB SmartCouponDaemon can have a different protocol to its peers (GameDaemon, the manager, NP service) ❓.
- `tools/verify/` can already hold scripts from `lift-cg-verify`. Reuse them. Do not change their CacheGate behavior.

## Tasks
1. Write `tools/verify/run_smartcoupondaemon.sh`: copy the lifted exe and the original config into a temp dir under `build/`, run it under wine64 for a fixed time, and save the console output.
2. Do the same for the original exe. Compare the startup output (log lines, listen ports).
3. Patch both exes with `patch_import.py` (the copies in `build/` only). Give both the same input. Compare the packet logs with `pkldump.py`.
4. If the peers need the 2019 protocol and the 381 set does not give it, use or extend `tools/verify/replay.py`: it replays a captured stream to the exe and records the replies.
5. Write each difference in `Docs/Verify/SmartCouponDaemon.md`: packet, field, original value, lifted value, function address.

## Files
- `tools/verify/`
- `Docs/Verify/`

## Done when
- The lifted exe starts and listens on the same ports as the original.
- `Docs/Verify/SmartCouponDaemon.md` lists the result of each check.
