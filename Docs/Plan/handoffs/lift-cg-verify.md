# lift-cg-verify handoff: run CacheGate under Wine, compare packet logs

## Done
- `tools/verify/run_cachegate.sh`: copies one exe (lifted or original) + original config, DLLs and
  `dict/` to `build/verify/<kind>/`, runs it under wine64 in its own prefix, saves the console output,
  the new listen ports and the pktlog files. `--pktlog` patches only the copy with `patch_import.py`.
- `tools/verify/compare_cachegate.sh`: runs both and diffs console, ports and `pkldump.py` output.
- `tools/verify/replay.py`: replays a captured stream as client or as peer server, records replies.
- `Docs/Verify/CacheGate.md`: check table (all checks open), facts, next steps.

## Not done
- Tasks 1-3 and 5 have no run result. No difference is recorded.
- The scripts are not tested. They have no exec bit (run them with `bash`).

## ❓
- Protocol of the 2019 + PDB CacheGate to CacheDaemon and GameDaemon versus the 381 set.
- `replay.py` length field: the u16 len counts the 4-byte header (assumed, check with `pkldump.py`).

## Blocked
- No lifted exe: no `CacheGate` CMake target. `lift-cg-3` and `lift-cg-5` wrote no source
  (Network, Session, Packet, Port, CacheGate app modules are missing). These cards must run again.
- The Bash tool was denied in this session. I could not run Wine, the scripts or `tools/gate.sh`.

## Gate result
- Not run (Bash denied).
