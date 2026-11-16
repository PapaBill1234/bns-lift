# SmartCouponDaemon verify (card lift-smartcoupondaemon-verify)

Status: **original done, lifted blocked**. `tools/gate.sh` builds `build/SmartCouponDaemon.exe`, but the
lifted exe does not get to LISTEN:
- Committed `src/`: the exe stops at once with 0xc0000417 (0 log lines). Cause: the order of the
  `XmlConfigReader::Initialize` overloads in `src/common/DaemonConfig.h` (same as CacheGate check 1).
- Test copy with the `src/common` part of `Docs/Verify/CacheGate-fixes.patch`
  (`tools/verify/fixsrc_smartcoupondaemon.sh`): 32 log lines, then a page fault in the object pool step.
  After that step, `JobManager::Initialize` is a link stub that returns false. Thus initialize fails before LISTEN
  until lift-smartcoupondaemon-5 lifts the stub modules.

## How to run
| Command | Use |
| --- | --- |
| `tools/verify/run_smartcoupondaemon.sh lifted\|original [SECONDS] [--pktlog] [--peer] [--client]` | Runs one exe under wine64 in its own prefix (`build/verify/wineprefix`). Output in `build/verify/scd-<kind>/`: `log.txt`, `console.txt`, `ports.txt`, `exit.txt`, `peer-np.txt`, `peer-gamed.txt`, `client-manager.txt`, `client-daemon.txt`, `pktlog/*.pkl`. |
| `tools/verify/compare_smartcoupondaemon.sh [SECONDS] [--pktlog]` | Runs both kinds with `--peer --client`, writes 7 diffs in `build/verify/scd-compare/`: log, ports, peer-np, peer-gamed, client-manager, client-daemon, pkl. Exit 0 = no difference, 1 = difference, 3 = no lifted exe. |
| `tools/verify/fixsrc_smartcoupondaemon.sh` | Copies the source to `build/verify/scd-fixsrc/`, applies the `src/common` part of `Docs/Verify/CacheGate-fixes.patch`, builds `build/verify/scd-fixsrc/build/SmartCouponDaemon.exe`. The worktree `src/` does not change. Use it with `SCD_LIFTED_EXE=<that exe>`. |
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
Lifted = fixsrc exe (`build/verify/scd-fixsrc/build/SmartCouponDaemon.exe`, 168448 B), run with
`compare_smartcoupondaemon.sh 15 --pktlog`. The committed-src exe (`build/SmartCouponDaemon.exe`, 167936 B)
stops before check 2 (0xc0000417, 0 log lines).

| # | Check | Original | Lifted | Result |
| --- | --- | --- | --- | --- |
| 1 | Exe starts under wine64 | yes, exit 0 | committed src: 0xc0000417 at start. fixsrc: starts, page fault after 32 lines, exit 124 (timeout) | fail |
| 2 | Startup log lines (to the DB error) | 74 to 76 lines | 32 lines (to the bns-common-config dump). Diff: 92 changed lines | fail |
| 3 | Listen ports (polled every 0.1 s) | 22000, 32000 | none | fail |
| 4 | Bytes to NP peer (`peer-np`) | 1 STS `/Sts/Connect`, 254 B | no connect | fail |
| 5 | Bytes to GameDaemon peer (`peer-gamed`) | no connect (stops before) | no connect | same (0 lines) |
| 6 | Manager / daemon client (`client-*`) | connection refused (ports closed) | connection refused | same (0 lines) |
| 7 | Packet log, same input (`pkldump.py`) | 2 LISTEN, NP CONNECT, 1 STS | no records. Diff: 15 lines | fail |
| 8 | Behaviour after the DB step (DB OK) | not run: no ODBC driver | not run | blocked |
| 9 | 381 NP / GameDaemon accepts the 2019 protocol ❓ | not run | not run | open |

## Differences
| Packet | Field | Original value | Lifted value | Function address |
| --- | --- | --- | --- | --- |
| startup | process exit | runs to `onStart fail`, exit 0 | committed src: 0xc0000417 in `XmlReader_sv64.dll` +0x649D, `_wcsicmp(NULL, L"root-path")` | `XmlConfigReader::Initialize` overload order, `src/common/DaemonConfig.h` (CacheGate-fixes.patch) |
| log | config dump tag | `[config]` | `[smartcoupond]` | `SmartCouponDaemon::initialize` 0x150E0, `DaemonConfig::Dump` call (`SmartCouponDaemon.cpp:288`). Same LTCG constant issue as CacheGate: pass `L"config"` |
| log | version (`Daemon.cpp,496`) | `version: 0.0.348.352` | empty | No VERSIONINFO resource in the lifted exe |
| log | extra line | none | `CrashHandler.cpp,490 [crash-mail], PrintMailInfo...` | CrashHandler. CacheGate shows it in some runs only ❓ |
| log | `[objpool] initialized ... 4096 EventNotiJob` | yes | page fault, read at 0x20, lifted 0x14000BC88 (`cmp [rcx+0x20],0`, null `this`) | `EventNotiJob::_pool`: original is a static `ObjPool` object (dynamic init 0x52A30). Lifted is a null `ObjPool*` (`LinkStubs.cpp:66`, `EventNotiJob.h:18`) |
| log | job-mgr and all later lines | job manager (hash-count 16), game-event config, np, workers, daemon list | not reached | `JobManager::Initialize` is a stub that returns false (`LinkStubs.cpp:40`), called in 0x150E0 after the pool |
| LISTEN | ports | 22000, 32000 | none | follows from the rows above |
| STS | `/Sts/Connect` to NP | 254 B | not sent | follows from the rows above |

## Next steps
1. Apply the `src/common` part of `Docs/Verify/CacheGate-fixes.patch` to `src/` (a src card).
2. Make `EventNotiJob::_pool` a static `ObjPool` object, as in 0x52A30. Pass `L"config"` to `DaemonConfig::Dump`.
3. Lift the stub modules in `LinkStubs.cpp` (lift-smartcoupondaemon-5), first `JobManager`.
4. Run `tools/verify/compare_smartcoupondaemon.sh 15 --pktlog` again and update the tables.
5. Checks 5, 6 and 8 need a working DB (an ODBC driver in the Wine prefix or in unixODBC, and a
   SmartCouponDB schema). Then set `SCD_CERT` to a file with that DSN, and use `SCD_*_STREAM` with captured streams.
