# lift-smartcoupondaemon-verify-3: run the lifted SmartCouponDaemon again after the OpenPort fix

Repo: bns-lift (PRIVATE). No IDA unless a difference needs it (`/home/ubuntu/Documents/Codex/private-project/ida/lift/SmartCouponDaemon/SmartCouponDaemon.exe`).
Read `Docs/Verify/SmartCouponDaemon.md` and `Docs/Plan/handoffs/lift-smartcoupondaemon-6.md` and `Docs/Plan/handoffs/lift-smartcoupondaemon-verify-2.md` first.

## Goal
The lifted SmartCouponDaemon starts under Wine, passes the DB step and sends the same packets as the original 2019 + PDB SmartCouponDaemon for the same input.

## Facts
- `SCD_CERT=sql` uses the real SmartCouponDB in Docker `bns-mssql` (127.0.0.1:14333). Run `docker start bns-mssql` first. The script installs ODBC Driver 17 in the verify prefix once.
- With `SCD_CERT=sql` the original passes the DB step, opens ports 22000 and 32000 and logs `start ... loading time: 2255` (2026-11-16).
- The cfg file `E:\Service\cert\smartcoupond.cfg` holds the sa password. Never print it, copy it or commit it. Write `keyhere`.
- The original does not connect to the GameDaemon. The GameDaemon connects to 22000 (`--client`). `SCD_GAMED_PEER=1` turns on the old listener.

## Tasks
1. Run `SCD_CERT=sql tools/verify/compare_smartcoupondaemon.sh 20 --pktlog`.
2. Update each check row and the "Differences" table in `Docs/Verify/SmartCouponDaemon.md`. Run checks 5, 6 and 8.
3. Run check 9 if a 381 NP or GameDaemon is available. Else leave it open.
4. Write each new difference: packet, field, original value, lifted value, function address.
5. If the lifted exe still differs and a src change can fix it, queue the next pair. Write
   `Docs/Plan/cards/lift-smartcoupondaemon-7.md` (src fix, same format as `lift-smartcoupondaemon-6.md`) and
   `Docs/Plan/cards/lift-smartcoupondaemon-verify-4.md` (same format as this card, with this step 5 for the next pair).
   Then write the 2 rows in `Docs/Plan/queue/lift-smartcoupondaemon-verify-3.tsv` (same columns as `tools/slices/queue.tsv` in bns-server;
   copy the rows of `lift-smartcoupondaemon-6` and this card, change id, deps and title). The runner adds them after this card.
   Do this only if the first fault is new (a new address). Never queue a card past `lift-smartcoupondaemon-9`.

## Files
- `tools/verify/`
- `Docs/Verify/`
- `Docs/Plan/cards/`
- `Docs/Plan/queue/`

## Done when
- The lifted exe listens on the same ports as the original with `SCD_CERT=sql`, or the handoff gives the first difference with its address.
- `Docs/Verify/SmartCouponDaemon.md` lists the result of each check with `SCD_CERT=sql`.
