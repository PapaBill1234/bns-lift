# lift-marketdealerdaemon-verify: run the lifted MarketDealerDaemon under Wine and compare packet logs

Repo: bns-lift (PRIVATE). No IDA unless a difference needs it (`/home/ubuntu/Documents/Codex/private-project/ida/lift/MarketDealerDaemon/MarketDealerDaemon.exe`).

## Goal
The lifted MarketDealerDaemon starts under Wine and sends the same packets as the original 2019 + PDB MarketDealerDaemon for the same input.

## Facts
- Original exe and config: `/home/ubuntu/Documents/Codex/private-project/Service_348_8349/Service/MarketDealerDaemon/bin/` (`MarketDealerDaemon.exe`, `market_dealerd.config.xml`). Do not use `MarketDealerDaemon2019.exe` (other PDB GUID). Do not print config values that are passwords or keys. Write `keyhere`.
- The exe can load `XmlReader_sv64.dll`, `bsConsole_sv64.dll` and `dbghelp.dll` at run time. Copy them from the same folder next to both exes.
- The exe imports ODBC32 (MarketDB). Use the SQL setup of `lift-smartcoupondaemon-verify-3` and `lift-postofficedaemon-verify` (`Docs/Verify/SmartCouponDaemon.md`, `Docs/Verify/PostOfficeDaemon.md`, `bns-mssql` container, ODBC Driver 17). Read the password at run time. Never write it. The market DB procedures can be missing in the container ❓. If they are missing, write the failing calls in the result and compare the startup only.
- Peers: market agent (AgentChannel), market manager (ManagerChannel). Timers: DeliveryTimer, TimeoutTimer.
- Packet log tools: `/home/ubuntu/Documents/Codex/bns-wine/pktlog/` (`patch_import.py`, `pkldump.py`, `pktcover.py`). Read their usage lines only.
- The Wine server set in `bns-wine/` is the 381 set. The 2019 + PDB MarketDealerDaemon can have a different protocol to its peers ❓.
- `tools/verify/` holds scripts from the earlier verify cards (`replay.py`, `run_*.sh`, `compare_*.sh`). Reuse them. Do not change their behavior for the other servers.

## Tasks
1. Write `tools/verify/run_marketdealerdaemon.sh`: copy the lifted exe, the run-time DLLs and the original config into a temp dir under `build/`, run it under wine64 for a fixed time, and save the console output.
2. Do the same for the original exe. Compare the startup output (log lines, listen ports).
3. Patch both exes with `patch_import.py` (the copies in `build/` only). Give both the same input. Compare the packet logs with `pkldump.py`.
4. If the peers need the 2019 protocol and the 381 set does not give it, use or extend `tools/verify/replay.py`: it replays a captured stream to the exe and records the replies.
5. Write each difference in `Docs/Verify/MarketDealerDaemon.md`: packet, field, original value, lifted value, function address.

## Files
- `tools/verify/`
- `Docs/Verify/`

## Done when
- The lifted exe starts and listens on the same ports as the original.
- `Docs/Verify/MarketDealerDaemon.md` lists the result of each check.
