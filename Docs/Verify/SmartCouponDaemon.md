# SmartCouponDaemon verify (cards lift-smartcoupondaemon-verify, -verify-2, -verify-3)

Status (verify-3, 2026-11-16, `SCD_CERT=sql`): **lifted = original for all packets**. The lifted exe
(`build/SmartCouponDaemon.exe` from commit 1013fcb, 368128 B, built by `tools/gate.sh`) passes the DB step, listens
on 22000 and 32000, sends the same STS `/Sts/Connect` to NP and accepts the manager and daemon clients. 6 of 7 diffs
have 0 changed lines. The log diff has 4 changed lines: `version:` is empty in `Daemon.cpp,496` and `Daemon.cpp,545`
(no VERSIONINFO resource in the lifted exe). 2026-11-17 (parity-runtime): `.rc` VERSIONINFO added. The compare gives 0 changed lines in all diffs, also the log. Check 9 is open (no 381 NP or GameDaemon). Earlier status (verify-2):
`Network.cpp,175` ASSERT CRASH, fixed by lift-smartcoupondaemon-6 (0x1A8B0).

## How to run
| Command | Use |
| --- | --- |
| `tools/verify/run_smartcoupondaemon.sh lifted\|original [SECONDS] [--pktlog] [--peer] [--client]` | Runs one exe under wine64 in its own prefix (`build/verify/wineprefix`). Output in `build/verify/scd-<kind>/`: `log.txt`, `console.txt`, `ports.txt`, `exit.txt`, `peer-np.txt`, `peer-gamed.txt`, `client-manager.txt`, `client-daemon.txt`, `pktlog/*.pkl`. |
| `tools/verify/compare_smartcoupondaemon.sh [SECONDS] [--pktlog]` | Runs both kinds with `--peer --client`, writes 7 diffs in `build/verify/scd-compare/`: log, ports, peer-np, peer-gamed, client-manager, client-daemon, pkl. Exit 0 = no difference, 1 = difference, 3 = no lifted exe. |
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
- Added in verify-3: `event object handle failed, id: N` (worker id, changes from run to run), `loading time: N`,
  and the ephemeral client port in `accepted from, ... ip:127.0.0.1, port:N, socket:`.
- Race: `[np], np channel connected` and `[np-session-handler], connected` are in some runs only (placeholder DSN).
  The log diff ignores these 2 lines.
- Line order of the log changes (threads). The log diff ignores line order.

## Checks (verify-3: `SCD_CERT=sql tools/verify/compare_smartcoupondaemon.sh 20 --pktlog`, 2 runs, same result)
Lifted = gate build of 1013fcb (after lift-smartcoupondaemon-6). Verify-2 results are in git history.
| # | Check | Original | Lifted | Result |
| --- | --- | --- | --- | --- |
| 1 | Exe starts under wine64 | yes, exit 124 (timeout, runs) | yes, exit 124 (timeout, runs). No ASSERT, no RefCntObject line, no CrashHandler line | pass |
| 2 | Startup log lines | 96 lines | 96 lines. Diff: 4 changed lines (`version:` in 2 lines, see Differences) | fail (version only) |
| 3 | Listen ports (polled every 0.1 s) | 22000, 32000 (to the end) | 22000, 32000 (to the end) | pass (0 lines) |
| 4 | Bytes to NP peer (`peer-np`) | 1 STS `/Sts/Connect`, 254 B | 1 STS `/Sts/Connect`, 254 B, same bytes after noise | pass (0 lines) |
| 5 | Bytes to GameDaemon peer (`peer-gamed`) | not applicable: the exe does not connect to the GameDaemon (see Run facts) | same | pass (0 lines) |
| 6 | Manager / daemon client (`client-*`) | both accepted, 0 reply bytes, `close without channel` on 22000 | same | pass (0 lines). No Hello input stream yet |
| 7 | Packet log, same input (`pkldump.py`) | 2 LISTEN, NP CONNECT, 1 STS (218 B body), 2 ACCEPT, 2 CLOSE | same | pass (0 lines) |
| 8 | Behaviour after the DB step (DB OK) | coupon-publication count 0, game-event-log count 0, `open managed port ok`, `start ... loading time: 2178`, runs to timeout | same, `loading time: 2187` | pass |
| 9 | 381 NP / GameDaemon accepts the 2019 protocol ❓ | not run | not run | open (no 381 NP or GameDaemon: only `bns-mssql` runs) |

## Differences (verify-3, `SCD_CERT=sql`)
| Packet | Field | Original value | Lifted value | Function address |
| --- | --- | --- | --- | --- |
| log | `Daemon.cpp,496` Starting, `version:` | `0.0.348.352` | empty | `Daemon::LoadVersion` 0xBB30 reads the VERSIONINFO resource of the exe. The lifted code is correct. FIXED: `src/Server/SmartCouponDaemon/SmartCouponDaemon.rc` |
| log | `Daemon.cpp,545` start, `version:` | `0.0.348.352` | empty | same cause (0xBB30) |

Closed in verify-3 (fixed in 1013fcb): `Network.cpp,175` ASSERT CRASH (0x1A8B0), `RefCntObject.h,129 ... tag:0xfa`,
`CrashHandler.cpp,490` extra line. All verify-2 rows that followed from the ASSERT are closed.

## Next steps
1. DONE: add a VERSIONINFO resource to the SmartCouponDaemon target
   (FileVersion 0.0.348.352, same strings as the original exe). Needs a change in `cmake/` or `CMakeLists.txt`.
2. Check 6 with data: capture a GameDaemon Hello stream (HandleSmartCoupon_HelloReq 0x7DC0, lifted in 1013fcb)
   and give it as `SCD_DAEMON_STREAM`. Do the same for 0x8360 and 0x8E80.
3. Check 9 when a 381 NP or GameDaemon is available.
