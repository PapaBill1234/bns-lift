# lift-postofficedaemon-verify: run the lifted PostOfficeDaemon under Wine and compare packet logs

Repo: bns-lift (PRIVATE). No IDA unless a difference needs it (`<work-root>/ida/lift/PostOfficeDaemon/PostOfficeDaemon.exe`).

## Goal
The lifted PostOfficeDaemon starts under Wine and sends the same packets as the original 2019 + PDB PostOfficeDaemon for the same input.

## Facts
- Original exe and config: `<work-root>/Service_348_8349/Service/PostOfficeDaemon/bin/` (`PostOfficeDaemon.exe`, `postofficed.config.xml`). Do not use `PostOfficeDaemon2019.exe` (other PDB GUID). Do not print config values that are passwords or keys. Write `keyhere`.
- The exe can load `XmlReader_sv64.dll`, `bsConsole_sv64.dll` and `dbghelp.dll` at run time. Copy them from the same folder next to both exes.
- The exe imports ODBC32 (PostOfficeDB). Use the SQL setup of `lift-smartcoupondaemon-verify-3` (`Docs/Verify/SmartCouponDaemon.md`, `bns-mssql` container, ODBC Driver 17). Read the password at run time. Never write it.
- Peers: CacheGate (CacheGateChannel), CacheEconomy, Agent, Management and World channels.
- Packet log tools: `<bns-wine>/pktlog/` (`patch_import.py`, `pkldump.py`, `pktcover.py`). Read their usage lines only.
- The Wine server set in `bns-wine/` is the 381 set. The 2019 + PDB PostOfficeDaemon can have a different protocol to its peers ❓.
- `tools/verify/` holds scripts from the earlier verify cards (`replay.py`, `run_*.sh`, `compare_*.sh`). Reuse them. Do not change their behavior for the other servers.

## Tasks
1. Write `tools/verify/run_postofficedaemon.sh`: copy the lifted exe, the run-time DLLs and the original config into a temp dir under `build/`, run it under wine64 for a fixed time, and save the console output.
2. Do the same for the original exe. Compare the startup output (log lines, listen ports).
3. Patch both exes with `patch_import.py` (the copies in `build/` only). Give both the same input. Compare the packet logs with `pkldump.py`.
4. If the peers need the 2019 protocol and the 381 set does not give it, use or extend `tools/verify/replay.py`: it replays a captured stream to the exe and records the replies.
5. Write each difference in `Docs/Verify/PostOfficeDaemon.md`: packet, field, original value, lifted value, function address.

## Files
- `tools/verify/`
- `Docs/Verify/`

## Done when
- The lifted exe starts and listens on the same ports as the original.
- `Docs/Verify/PostOfficeDaemon.md` lists the result of each check.
