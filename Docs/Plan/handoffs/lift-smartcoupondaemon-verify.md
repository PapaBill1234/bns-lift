# lift-smartcoupondaemon-verify

## Done
- `tools/verify/run_smartcoupondaemon.sh`: runs the lifted or the original exe under wine64 (own prefix, wineconsole on Xvfb :77).
  Options: `--pktlog`, `--peer` (replay.py as NP 6601 and GameDaemon 20100), `--client` (replay.py on 32000 and 22000).
  It polls the listen ports every 0.1 s. It writes a placeholder cert DSN with `keyhere` values (`SCD_CERT`).
- `tools/verify/compare_smartcoupondaemon.sh`: makes 7 diffs (log, ports, peer-np, peer-gamed, client-manager, client-daemon, pkl).
  It removes the noise. It exits 3 if there is no lifted exe.
- Self test (original against original, 15 s, `--pktlog`): 0 changed lines in all 7 diffs, 2 runs.
- Reference behaviour of the original: it listens on 22000 and 32000 and sends the STS `/Sts/Connect` to NP.
  The first DB call fails (no ODBC driver), then `onStart fail` and the exe stops.
- `Docs/Verify/SmartCouponDaemon.md`: the run facts, the reference behaviour, the noise and 9 checks.
- `replay.py` and the CacheGate scripts did not change.

## Not done
- All lifted checks. `build/SmartCouponDaemon.exe` does not exist: there is no CMake target and no `src/SmartCouponDaemon/`
  (lift-smartcoupondaemon-4 lifted 0 functions). Done-when "lifted exe listens on the same ports" is not met.
- GameDaemon peer and manage/daemon clients: the original stops about 2 s after start (DB fail), before these steps.

## ❓
- The 2023 production log shows `cannot execute, error:10`. I did not find the error-10 path in `initialize` (0x1400150E0).
- I did not test whether a 381 NP or GameDaemon accepts the 2019 protocol.

## Blocked
- Lifted compare: no lifted exe. Next: lift the exe, then run `tools/verify/compare_smartcoupondaemon.sh 15 --pktlog`.
- Steps after onStart: they need an ODBC driver and a SmartCouponDB schema.

## Gate result
- `tools/gate.sh`: `gate ok`, rc 0 (51/51 steps, warnings only). This card changed no source code.
