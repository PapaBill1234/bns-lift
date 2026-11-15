# CacheGate verify (card lift-cg-verify)

Status: **not run**. The checks below have no result yet.

## Why not run
1. No lifted exe. The CMake file has no `CacheGate` target. The handoffs `lift-cg-3` and `lift-cg-5`
   show that Network, Session, Packet, Port and all CacheGate app modules are not lifted
   (no source in `src/`). Only `lift_common` (memory, thread, console, daemon, config, crypto) builds.
2. The Bash tool was denied in this session. I could not run Wine, the original exe, or the scripts.

## Tools (written in this card, not tested)
| File | Use |
| --- | --- |
| `tools/verify/run_cachegate.sh lifted\|original [SECONDS] [--pktlog]` | Copies the exe, the original config, DLLs and `dict/` to `build/verify/<kind>/Server/CacheGate/bin/`. Runs it under wine64 in its own prefix (`build/verify/wineprefix`, D: points to the run folder). Saves `console.txt`, `ports.txt` (new TCP listen ports), `exit.txt`, `pktlog/*.pkl`. |
| `tools/verify/compare_cachegate.sh [SECONDS] [--pktlog]` | Runs both kinds and writes `build/verify/compare/{console,ports,pkl}.diff`. Removes time stamps, pids and addresses before the diff. |
| `tools/verify/replay.py connect\|listen ...` | Sends a captured stream (u16 len + u16 id cut) to the exe as client or as peer server. Records the replies, one line per packet. |

Run the scripts with `bash tools/verify/<name>.sh` (the files have no exec bit yet).

## Facts
- Original exe: `Service_348_8349/Service/CacheGate/bin/CacheGate.exe`. Do not use `CacheGate2019.exe`
  in the same folder (plan: its PDB GUID does not match).
- `cachegate.config.xml`: `public-port` = 20800. This is the expected listen port.
- pktlog.dll writes to `D:\Logs\pktlog\<name>-<pid>-<time>.pkl`. `<name>` comes from the
  `<name>\bin\` folder, so the script uses `Server/CacheGate/bin/` for both exes.
- The peers in `bns-wine/` are the 381 set. The protocol of the 2019 + PDB CacheGate to CacheDaemon
  and GameDaemon is not known ❓. If the 381 CacheDaemon does not accept it, use `replay.py listen`
  as the CacheDaemon peer.

## Checks
| # | Check | Original | Lifted | Result |
| --- | --- | --- | --- | --- |
| 1 | Exe starts under wine64 | not run | no exe | open |
| 2 | Startup log lines | not run | no exe | open |
| 3 | Listen ports (expected 20800) | not run | no exe | open |
| 4 | Packet log, same input (`pkldump.py`) | not run | no exe | open |
| 5 | Replay to CacheDaemon peer (2019 protocol) | not run | no exe | open |

## Differences
| Packet | Field | Original value | Lifted value | Function address |
| --- | --- | --- | --- | --- |
| - | - | - | - | - |

None recorded. No run was possible.

## Next steps
1. Run cards `lift-cg-3` and `lift-cg-5` again (with Bash) to get `build/CacheGate.exe`.
2. `bash tools/verify/run_cachegate.sh original 20` to get the reference output, also before step 1.
3. `bash tools/verify/compare_cachegate.sh 20 --pktlog`. Write each line of the diffs in the table above.
