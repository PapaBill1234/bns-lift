# SmartCouponDaemon verify (cards lift-smartcoupondaemon-verify, lift-smartcoupondaemon-verify-2)

Status (verify-2, 2026-11-16, `SCD_CERT=sql`): **original done, lifted blocked**. The original passes the DB step,
listens on 22000 and 32000 and runs to the timeout. The lifted exe (`build/SmartCouponDaemon.exe` from commit
8e56145, 347136 B, built by `tools/gate.sh`) does not get to LISTEN. First difference: `Network.cpp,175`
ASSERT CRASH in `Network::OpenPort`, because the lifted callers give `initialMode` 0 to the generic overload
(0xD2C0). The original calls a 5-argument copy (0x1A8B0) that has no mode check. See "Differences".

## How to run
| Command | Use |
| --- | --- |
| `tools/verify/run_smartcoupondaemon.sh lifted\|original [SECONDS] [--pktlog] [--peer] [--client]` | Runs one exe under wine64 in its own prefix (`build/verify/wineprefix`). Output in `build/verify/scd-<kind>/`: `log.txt`, `console.txt`, `ports.txt`, `exit.txt`, `peer-np.txt`, `peer-gamed.txt`, `client-manager.txt`, `client-daemon.txt`, `pktlog/*.pkl`. |
| `tools/verify/compare_smartcoupondaemon.sh [SECONDS] [--pktlog]` | Runs both kinds with `--peer --client`, writes 7 diffs in `build/verify/scd-compare/`: log, ports, peer-np, peer-gamed, client-manager, client-daemon, pkl. Exit 0 = no difference, 1 = difference, 3 = no lifted exe. |
| `tools/verify/fixsrc_smartcoupondaemon.sh` | Round 1 only (src before 8e56145). Copies the source to `build/verify/scd-fixsrc/` and applies the `src/common` part of `Docs/Verify/CacheGate-fixes.patch`. Not necessary now: 8e56145 has these fixes. |
| `tools/verify/replay.py` | No change. Used as the NP peer (`listen`) and as the manager and daemon clients (`connect`). |

Self test: `SCD_LIFTED_EXE=<original exe> tools/verify/compare_smartcoupondaemon.sh 15 --pktlog` gives
0 changed lines in all 7 diffs (2 runs, rc 0).

## Run facts (found with the original exe, version 0.0.348.352)
- Original = `bin/SmartCouponDaemon.exe` (the exe of the IDA copy). `SmartCouponDaemon2019.exe` is not used.
- Same as CacheGate: the exe needs a console window (wineconsole on Xvfb `:77`, full Windows path).
- Paths: `E:\Service\SmartCouponDaemon\{bin,config}`, `E:\log\SmartCouponDaemon\`, cert file
  `E:\Service\cert\smartcoupond.cfg`. pktlog writes to `D:\Logs\pktlog\`. E: and D: point into `build/verify/scd-<kind>/`.
- The cert file is not in the service folder. `SmartCouponDaemon::initialize` (0x150E0) reads it with
  `fread` (max 1000 B) and uses the text as the ODBC connection string. No file: `cannot execute, error:3`
  and exit (error 2 = no cert-file option). `SCD_CERT=placeholder` (default) writes a DSN with `keyhere` values.
  `SCD_CERT=none` gives the error-3 run.
- `SCD_CERT=sql` uses the real SmartCouponDB in Docker `bns-mssql` (127.0.0.1:14333). Start the container first
  (`docker start bns-mssql`). The script installs ODBC Driver 17 in the verify prefix once
  (`bns-wine/dl/msodbcsql17_x64.msi`). It reads the sa password from the container env at run time. The password
  is `keyhere` in all docs. Never print the cfg file.
- With `--peer` the script sets `np-address` and the gamed `ip-address` to 127.0.0.1. `replay.py listen` is the NP
  peer (6601).
- **GameDaemon direction (verify-2, task 3).** The SmartCouponDaemon does not connect to the GameDaemon. The
  GameDaemon connects to `daemon-listen-port` (22000). `gamed-list.config.xml` is the list of known GameDaemons
  (`[daemon-mgr], daemon registered, ... ip:127.0.0.1, port:20100`), not a connect list. The original log shows
  `[daemon-ch], 0x0000000200000001, 0, accept` for the `--client` connect to 22000, then
  `close without channel` (no Hello packet). `DChannelMgr` has only accept and close handlers, no connect call.
  Thus the earlier "no connect to the GameDaemon peer in 20 s" was a test setup error, not a timing or config
  error. Script fix: the listener on `internal-port` (20100) is off by default (`SCD_GAMED_PEER=1` turns it on).
  The GameDaemon role is the `--client` connect to 22000 with `SCD_DAEMON_STREAM`.

## Reference behaviour (original, `SCD_CERT=sql`, `--peer --client`, 20 s)
1. Config dump, bns-common-config dump, object pool (4096 EventNotiJob), job manager (hash-count 16),
   game-event config (id 10001 LevelUp15), `[np], setup np channel success`, 16 game-event workers.
2. About 2 s later: `daemon session manager initialized`, 1 gamed registered (wid 1, 127.0.0.1:20100),
   objpool timer, `[np], initialize ok`, connect to NP 127.0.0.1:6601.
3. One STS message to NP (254 B, body 218 B): `POST /Sts/Connect STS/1.0`, body `<Connect>` with ConnType 401,
   Address 127.0.0.1, ProductType 0, AppIndex 1, Epoch (changes), Program 302, Build 4000, Process (pid, changes).
4. `load unhandled coupon-publication, count:0`, `load unhandled game-event-log, count:0`,
   `[scd], open managed port ok`, `start ... version: 0.0.348.352, loading time: 2180..2255`. LISTEN 22000, 32000.
5. Manager client (32000): `[ManagerSessionHandler], accepted manager session`, 2 s later `recv zero`,
   `closed connection with unknown manager session`. Daemon client (22000): `[daemon-ch] ... accept`,
   `close without channel`. No reply bytes to the clients (no input stream). 96 log lines, exit 124 (timeout).

## Noise (removed by compare_smartcoupondaemon.sh)
- Time stamps, pointers, host name and addresses, ephemeral local ports, pids.
- `worker run, id:N(k)`: thread ids. STS body: `<Epoch>` and `<Process>`.
- Race: `[np], np channel connected` and `[np-session-handler], connected` are in some runs only (placeholder DSN).
  The log diff ignores these 2 lines.
- Line order of the log changes (threads). The log diff ignores line order.

## Checks (verify-2: `SCD_CERT=sql tools/verify/compare_smartcoupondaemon.sh 20 --pktlog`, 2 runs, same result)
| # | Check | Original | Lifted | Result |
| --- | --- | --- | --- | --- |
| 1 | Exe starts under wine64 | yes, exit 124 (timeout, runs) | yes, no 0xc0000417. ASSERT CRASH at about 2 s, then exit 124 (timeout, hangs in crash handler) | fail |
| 2 | Startup log lines | 96 lines | 55 lines, to the 16 worker lines. Diff: 47 changed lines | fail |
| 3 | Listen ports (polled every 0.1 s) | 22000, 32000 (to the end) | none | fail |
| 4 | Bytes to NP peer (`peer-np`) | 1 STS `/Sts/Connect`, 254 B | no connect | fail |
| 5 | Bytes to GameDaemon peer (`peer-gamed`) | not applicable: the exe does not connect to the GameDaemon (see Run facts) | same | same (0 lines) |
| 6 | Manager / daemon client (`client-*`) | both accepted, 0 reply bytes | connection refused | fail (1 line each) |
| 7 | Packet log, same input (`pkldump.py`) | 2 LISTEN, NP CONNECT, 1 STS, 2 ACCEPT, 2 CLOSE | no records. Diff: 19 lines | fail |
| 8 | Behaviour after the DB step (DB OK) | coupon-publication count 0, game-event-log count 0, `open managed port ok`, `start ... loading time: 2180`, runs to timeout | not reached (crash before the DB step) | fail |
| 9 | 381 NP / GameDaemon accepts the 2019 protocol ❓ | not run | not run | open |

## Differences (verify-2, `SCD_CERT=sql`)
| Packet | Field | Original value | Lifted value | Function address |
| --- | --- | --- | --- | --- |
| log | `RefCntObject.h,129 destructring with not zero reference count, ref:1, tag:0xfa` | not in the log | after `[objpool] objpool added to timer, id:1`, before `[job-mgr] initialize ok` | 0x150E0 path between the pool init and `JobManager::Initialize` ❓ (a RefCntObject on the stack or freed early). Not fatal |
| startup | process | runs | `Network.cpp,175 == CRASH == ASSERT CRASH` (about 2 s after start, after the 16 workers) | Lifted calls `Network::OpenPort(1, 0, 0, ...)` 9-argument overload (0xD2C0, `src/common/Network.cpp:196`, check `initialMode != 1 && != 2`). Callers: `SmartCouponDaemon.cpp:362` (NP port 1), `:390` (port 2), `:400` (port 3), all with `initialMode` 0. Original calls `Network::OpenPort(portId, portNo, sessionHandler, bufferHandler, maxSession)` **0x1A8B0**: no line-175 check, maxSession 0 → `2 * workers + 1`, min 16 (mode-2 rule), then `Port::Initialize` 0x1AA48, `_enableAccept = false`, `_enableRecv = true`. Fix (src card): lift 0x1A8B0 as its own overload and call it from 0x150E0 |
| log | daemon list, np init, DB load, `open managed port ok`, `start` | 41 lines | not reached | follows from the ASSERT row |
| LISTEN | ports | 22000, 32000 | none | follows from the ASSERT row |
| STS | `/Sts/Connect` to NP | 254 B | not sent | follows from the ASSERT row |
| client | manager 32000 / daemon 22000 | accepted, 0 B reply | connection refused | follows from the ASSERT row |

Closed since round 1 (fixed in 8e56145): 0xc0000417 in `XmlConfigReader::Initialize`, `[config]` dump tag,
null `EventNotiJob::_pool`, `JobManager::Initialize` stub. Still open from round 1: `version:` empty in
`Daemon.cpp,496` (no VERSIONINFO resource in the lifted exe), extra `CrashHandler.cpp,490` line.

## Next steps
1. Src card: lift `Network::OpenPort` 0x1A8B0 (5 arguments) and use it in 0x150E0 for ports 1, 2 and 3.
   Check the `Port::Initialize` arguments at 0x1AA1E..0x1AA48 ❓ (initial mode, nagle, useUnusedSessionReadOnly).
2. Find the RefCntObject (tag 0xfa) that is destroyed with ref 1 in the 0x150E0 pool / job-manager step.
3. Run `SCD_CERT=sql tools/verify/compare_smartcoupondaemon.sh 20 --pktlog` again and update the tables.
4. Check 6 with data: capture a GameDaemon Hello stream (HandleSmartCoupon_HelloReq 0x7DC0, not lifted yet) and
   give it as `SCD_DAEMON_STREAM`.
