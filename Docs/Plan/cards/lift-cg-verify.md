# lift-cg-verify: run the lifted CacheGate under Wine and compare packet logs

Repo: bns-lift (PRIVATE). No IDA unless a difference needs it (`/home/ubuntu/Documents/Codex/private-project/ida/lift/CacheGate/CacheGate.exe`).

## Goal
The lifted CacheGate starts under Wine and sends the same packets as the original 2019 + PDB CacheGate for the same input.

## Facts
- Original exe and config: `/home/ubuntu/Documents/Codex/private-project/Service_348_8349/Service/CacheGate/bin/` (`CacheGate.exe`, `cachegate.config.xml`, `bns.common.config.xml`). Do not print config values that are passwords. Write `keyhere`.
- Packet log tools: `/home/ubuntu/Documents/Codex/bns-wine/pktlog/` (`patch_import.py`, `pkldump.py`, `pktcover.py`). Read their usage lines only.
- The Wine server set in `bns-wine/` is the 381 set. The 2019 + PDB CacheGate can have a different protocol to CacheDaemon and GameDaemon ❓.

## Tasks
1. Write `tools/verify/run_cachegate.sh`: copy the lifted exe and the original config into a temp dir under `build/`, run it under wine64 for a fixed time, and save the console output.
2. Do the same for the original exe. Compare the startup output (log lines, listen ports).
3. Patch both exes with `patch_import.py` (the copies in `build/` only). Give both the same input. Compare the packet logs with `pkldump.py`.
4. If the peers need the 2019 protocol and the 381 set does not give it, write `tools/verify/replay.py`: it replays a captured stream to the exe and records the replies.
5. Write each difference in `Docs/Verify/CacheGate.md`: packet, field, original value, lifted value, function address.

## Files
- `tools/verify/`
- `Docs/Verify/`

## Done when
- The lifted exe starts and listens on the same ports as the original.
- `Docs/Verify/CacheGate.md` lists the result of each check.
