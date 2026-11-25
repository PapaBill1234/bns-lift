# lift-smartcoupondaemon-verify-2: run the lifted SmartCouponDaemon again, with the real DB

Repo: bns-lift (PRIVATE). No IDA unless a difference needs it (`<work-root>/ida/lift/SmartCouponDaemon/SmartCouponDaemon.exe`).
Read `Docs/Verify/SmartCouponDaemon.md` and `Docs/Plan/handoffs/lift-smartcoupondaemon-5.md` first.

## Goal
The lifted SmartCouponDaemon starts under Wine, passes the DB step and sends the same packets as the original 2019 + PDB SmartCouponDaemon for the same input.

## Facts
- `SCD_CERT=sql` uses the real SmartCouponDB in Docker `bns-mssql` (127.0.0.1:14333). Run `docker start bns-mssql` first. The script installs ODBC Driver 17 in the verify prefix once.
- With `SCD_CERT=sql` the original passes the DB step, opens ports 22000 and 32000 and logs `start ... loading time: 2255` (2026-11-16).
- The cfg file `E:\Service\cert\smartcoupond.cfg` holds the sa password. Never print it, copy it or commit it. Write `keyhere`.
- With `SCD_CERT=sql` the original did not connect to the GameDaemon peer in 20 s ❓.

## Tasks
1. Run `SCD_CERT=sql tools/verify/compare_smartcoupondaemon.sh 20 --pktlog`.
2. Update each check row and the "Differences" table in `Docs/Verify/SmartCouponDaemon.md`. Run checks 5, 6 and 8.
3. Find why the original does not connect to the GameDaemon peer (gamed list config, `ip-address`, timing). Fix the script if the cause is the test setup.
4. Write each new difference: packet, field, original value, lifted value, function address.

## Files
- `tools/verify/`
- `Docs/Verify/`

## Done when
- The lifted exe listens on the same ports as the original with `SCD_CERT=sql`, or the handoff gives the first difference with its address.
- `Docs/Verify/SmartCouponDaemon.md` lists the result of each check with `SCD_CERT=sql`.
