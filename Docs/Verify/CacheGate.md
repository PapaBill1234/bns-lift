# CacheGate verify (card lift-cg-verify)

Status: **original done, lifted open**. The scripts work with the original exe. The lifted exe
`build/CacheGate.exe` does not exist yet: the CMake file has no `CacheGate` target, and `src/CacheGate/`
has only `CacheD.h` (see `Docs/Plan/handoffs/lift-cg-5.md`). Run the compare again when that card is done.

## How to run
| Command | Use |
| --- | --- |
| `tools/verify/run_cachegate.sh lifted\|original [SECONDS] [--pktlog] [--peer] [--client]` | Runs one exe under wine64 in its own prefix (`build/verify/wineprefix`). Output in `build/verify/<kind>/`: `log.txt`, `ports.txt`, `exit.txt`, `peer.txt`, `client.txt`, `pktlog/*.pkl`. |
| `tools/verify/compare_cachegate.sh [SECONDS] [--pktlog]` | Runs both kinds with `--peer --client`, writes `build/verify/compare/{log,ports,peer,client,pkl}.diff`. Exit 0 = no difference, 3 = no lifted exe. |
| `tools/verify/replay.py connect HOST:PORT\|listen PORT STREAM OUT` | Peer or client. Sends STREAM, records each received packet as `<ms> <len> <id> <hex>`. |

Self test: `CG_LIFTED_EXE=<original exe> tools/verify/compare_cachegate.sh 20 --pktlog` gives 0 changed lines in all 5 diffs.

## Run facts (found with the original exe)
- The exe must have a console window. Without one it starts in service mode and crashes (page fault).
  The script runs it in `wineconsole` on a hidden Xvfb display `:77`. Give the full Windows path of the exe.
- Paths from the config: `E:\Service\CacheGate\{bin,config}`, `E:\log\CacheGate\`. pktlog writes to
  `D:\Logs\pktlog\`. The script points E: and D: into `build/verify/<kind>/`.
- The exe stops at start if `config\cached-list.config.xml` is missing. With `--peer` the script sets its
  `ip-address` to 127.0.0.1, and `replay.py listen` is the CacheD peer on the economy port (20202).
- `exit.txt` = 124 is correct: the script stops the exe with SIGINT after SECONDS.

## Reference behaviour (original, 2019 + PDB, version 0.0.348.524)
- Listen port: 20800 (`public-port`). No other listen port.
- Log: 36 lines. Config dump, bns-common-config, CacheD session 200000001 connect,
  `[cg], cached connect, hello send, wid:1`, `network initialize ok.`, `start`.
- To CacheD (economy port) it sends one 10-byte hello: `0a 00 01 00 04 00 0a 00 01 00`.
- Client connect with no data: accept (session 100000001), `recv zero`, `on close, portid : 1`, remove. No bytes sent to the client.

## Noise (removed by compare_cachegate.sh)
- Time stamps, pointers, socket handles, local ports, the host name and addresses.
- `[worker], event object handle failed, id: N`: N changes from run to run.
- The order of `Cached channel connected` and the connect lines changes (threads). The log diff ignores line order.

## Checks
| # | Check | Original | Lifted | Result |
| --- | --- | --- | --- | --- |
| 1 | Exe starts under wine64 | yes | no exe | open |
| 2 | Startup log lines | 36 lines, see above | no exe | open |
| 3 | Listen ports | 20800 | no exe | open |
| 4 | Bytes to CacheD peer (`replay.py listen`) | 10 B hello | no exe | open |
| 5 | Client on 20800, no data | accept, recv zero, close | no exe | open |
| 6 | Packet log, same input (`pkldump.py`) | 7 records, same as 4 and 5 | no exe | open |
| 7 | 381 CacheDaemon accepts the 2019 hello ❓ | not run | not run | open |

## Differences
| Packet | Field | Original value | Lifted value | Function address |
| --- | --- | --- | --- | --- |
| - | - | - | - | - |

None recorded. No lifted exe.

## Next steps
1. Finish lift-cg-5 (CMake target `CacheGate`, output `build/CacheGate.exe`).
2. `tools/verify/compare_cachegate.sh 20 --pktlog`. Write each changed line in the table above.
3. For packet data tests: set `CG_PEER_STREAM` / `CG_CLIENT_STREAM` to a captured stream (Hello, Relay).
