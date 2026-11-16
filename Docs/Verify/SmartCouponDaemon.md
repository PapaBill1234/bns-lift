# SmartCouponDaemon verify (card lift-smartcoupondaemon-verify)

Status: **original done, lifted open**. The scripts work with the original exe. The lifted exe
`build/SmartCouponDaemon.exe` does not exist yet: the CMake file has no `SmartCouponDaemon` target, and
there is no `src/SmartCouponDaemon/` (lift-smartcoupondaemon-4 lifted 0 functions, see its handoff).
Run the compare again when that card is done.

## How to run
| Command | Use |
| --- | --- |
| `tools/verify/run_smartcoupondaemon.sh lifted\|original [SECONDS] [--pktlog] [--peer] [--client]` | Runs one exe under wine64 in its own prefix (`build/verify/wineprefix`). Output in `build/verify/scd-<kind>/`: `log.txt`, `console.txt`, `ports.txt`, `exit.txt`, `peer-np.txt`, `peer-gamed.txt`, `client-manager.txt`, `client-daemon.txt`, `pktlog/*.pkl`. |
| `tools/verify/compare_smartcoupondaemon.sh [SECONDS] [--pktlog]` | Runs both kinds with `--peer --client`, writes 7 diffs in `build/verify/scd-compare/`: log, ports, peer-np, peer-gamed, client-manager, client-daemon, pkl. Exit 0 = no difference, 1 = difference, 3 = no lifted exe. |
| `tools/verify/replay.py` | No change. Used as the NP peer and the GameDaemon peer (`listen`) and as the manager and daemon clients (`connect`). |

Self test: `SCD_LIFTED_EXE=<original exe> tools/verify/compare_smartcoupondaemon.sh 15 --pktlog` gives
0 changed lines in all 7 diffs (2 runs, rc 0).

## Run facts (found with the original exe, version 0.0.348.352)
- Original = `bin/SmartCouponDaemon.exe` (the exe of the IDA copy). `SmartCouponDaemon2019.exe` is not used.
- Same as CacheGate: the exe needs a console window (wineconsole on Xvfb `:77`, full Windows path).
- Paths: `E:\Service\SmartCouponDaemon\{bin,config}`, `E:\log\SmartCouponDaemon\`, cert file
  `E:\Service\cert\smartcoupond.cfg`. pktlog writes to `D:\Logs\pktlog\`. E: and D: point into `build/verify/scd-<kind>/`.
- The cert file is not in the service folder. `SmartCouponDaemon::initialize` (0x150E0) reads it with
  `fread` (max 1000 B) and uses the text as the ODBC connection string. No file: `cannot execute, error:3`
  and exit (error 2 = no cert-file option). The script writes a placeholder DSN with `keyhere` values
  (`SCD_CERT=placeholder`, the default). `SCD_CERT=none` gives the error-3 run.
- `Db::Initialize` does not connect, so it passes. The first DB call fails: unixODBC has no driver here.
- With `--peer` the script sets `np-address` and the gamed `ip-address` to 127.0.0.1. `replay.py listen`
  is the NP peer (6601) and the GameDaemon peer (20100).

## Reference behaviour (original, with placeholder DSN and `--peer`)
1. Config dump, bns-common-config dump, object pool (4096 EventNotiJob), job manager (hash-count 16),
   game-event config (id 10001 LevelUp15), `[np], setup np channel success`, 16 game-event workers.
2. Daemon list: 1 gamed (wid 1, 127.0.0.1:20100). LISTEN on 22000 (daemon) and 32000 (manage).
3. Connect to NP 127.0.0.1:6601, send one STS message (254 B, body 218 B):
   `POST /Sts/Connect STS/1.0`, body `<Connect>` with ConnType 401, Address 127.0.0.1, ProductType 0,
   AppIndex 1, Epoch (changes), Program 302, Build 4000, Process (pid, changes).
4. `load unhandled coupon-publication` -> `[db], failed to acquire transaction, dbId:1, load-coupon-publication`
   -> `failed to load coupon-publication-list, dbRetValue:0` -> `[smartcoupond], onStart fail`. Exit 0.
5. The listen ports are open for about 0.1 s only (step 2 to step 4, about 2 s after start). The exe does
   not connect to the GameDaemon. Manager and daemon clients get "connection refused".

## Noise (removed by compare_smartcoupondaemon.sh)
- Time stamps, pointers, host name and addresses, ephemeral local ports, pids.
- `worker run, id:N(k)`: thread ids. STS body: `<Epoch>` and `<Process>`.
- Race: `[np], np channel connected` and `[np-session-handler], connected` are in some runs only (the NP
  I/O thread and the onStart stop run at the same time). The log diff ignores these 2 lines.
- Line order of the log changes (threads). The log diff ignores line order.

## Checks
| # | Check | Original | Lifted | Result |
| --- | --- | --- | --- | --- |
| 1 | Exe starts under wine64 | yes | no exe | open |
| 2 | Startup log lines (to the DB error) | 74 to 76 lines, see above | no exe | open |
| 3 | Listen ports (polled every 0.1 s) | 22000, 32000 | no exe | open |
| 4 | Bytes to NP peer (`peer-np`) | 1 STS `/Sts/Connect`, 254 B | no exe | open |
| 5 | Bytes to GameDaemon peer (`peer-gamed`) | no connect (stops before) | no exe | open |
| 6 | Manager / daemon client (`client-*`) | connection refused (ports closed) | no exe | open |
| 7 | Packet log, same input (`pkldump.py`) | 2 LISTEN, NP CONNECT, 1 STS | no exe | open |
| 8 | Behaviour after the DB step (DB OK) | not run: no ODBC driver | not run | blocked |
| 9 | 381 NP / GameDaemon accepts the 2019 protocol ❓ | not run | not run | open |

## Differences
| Packet | Field | Original value | Lifted value | Function address |
| --- | --- | --- | --- | --- |
| - | - | - | - | - |

None recorded. No lifted exe.

## Next steps
1. Finish the SmartCouponDaemon lift (CMake target `SmartCouponDaemon`, output `build/SmartCouponDaemon.exe`).
2. `tools/verify/compare_smartcoupondaemon.sh 15 --pktlog`. Write each changed line in the table above.
3. Checks 5, 6 and 8 need a working DB (an ODBC driver in the Wine prefix or in unixODBC, and a
   SmartCouponDB schema). Then set `SCD_CERT` to a file with that DSN, and use `SCD_*_STREAM` with captured streams.
