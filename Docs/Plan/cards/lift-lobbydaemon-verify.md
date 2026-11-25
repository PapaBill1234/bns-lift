# lift-lobbydaemon-verify: run the lifted LobbyDaemon under Wine and compare packet logs

Repo: bns-lift (public). No IDA unless a difference needs it (`<work-root>/ida/lift/LobbyDaemon/LobbyDaemon.exe`).

## Goal
The lifted LobbyDaemon starts under Wine and sends the same packets as the original 2019 + PDB LobbyDaemon for the same input.

## Facts
- Source build: LobbyDaemon 2019 + PDB (VS2010 SP1). Exe `<work-root>/ida/lift/LobbyDaemon/LobbyDaemon.exe`. PDB `<work-root>/ida/lift/LobbyDaemon/LobbyDaemon.pdb`.
- Original exe and config: `<work-root>/Service_348_8349/Service/LobbyDaemon/bin/` (`LobbyDaemon.exe`, `lobbyd.config.xml`, `bns.common.config.xml`, `ContentsRule.lobbyd.config.xml`, `dict/`). That `LobbyDaemon.exe` has the same SHA-256 as the source exe. Do not use `LobbyDaemon2019.exe` or a 381 file. Do not print config values that are passwords or keys. Write `keyhere`.
- The exe names `XmlReader_sv64.dll`, `bsConsole_sv64.dll`, `StsMsgSrv64.dll` and `dbghelp.dll` as strings. It can load them at run time. Copy them from the same folder next to both exes. ❓ `XmlReader_sv64.dll` can need `libiconv_sv64.dll`. Copy it too if the load fails.
- The exe imports ODBC32 (LobbyDB). Use the SQL setup of `lift-smartcoupondaemon-verify-3` (`Docs/Verify/SmartCouponDaemon.md`, `bns-mssql` container, ODBC Driver 17). Read the password at run time. Never write it. ❓ The LobbyDaemon databases are not in `bns-mssql` yet.
- Ports in `lobbyd.config.xml`: world 21800, lobby-gate 21801, info-gate 21802, account-inventory 21700, manage 31800. Outgoing: NP service 6601, PostOffice 20500. ❓ Which ports the exe listens on and which it connects to is not verified.
- Peers: LobbyGate (LobbyGateChannel), GameDaemon (GamedChannel), InfoGate, PostOffice, NP service (NPServiceChannel), Transaction, AccountInventory and Manage channels.
- Packet log tools: `<bns-wine>/pktlog/` (`patch_import.py`, `pkldump.py`, `pktcover.py`). Read their usage lines only.
- The Wine server set in `bns-wine/` is the 381 set. The 2019 + PDB LobbyDaemon can have a different protocol to its peers ❓.
- `tools/verify/` holds scripts from the earlier verify cards (`replay.py`, `pkl_stream.py`, `pod_streams.py`, `strings_check.py`, `run_*.sh`, `compare_*.sh`). Reuse them. Do not change their behavior for the other servers.

## Tasks
1. Write `tools/verify/run_lobbydaemon.sh`: copy the lifted exe, the run-time DLLs and the original config into a temp dir under `build/`, run it under wine64 for a fixed time, and save the console output.
2. Do the same for the original exe. Compare the startup output (log lines, listen ports). Write `tools/verify/compare_lobbydaemon.sh` for this step.
3. Patch both exes with `patch_import.py` (the copies in `build/` only). Give both the same input. Compare the packet logs with `pkldump.py`.
4. If the peers need the 2019 protocol and the 381 set does not give it, use or extend `tools/verify/replay.py`: it replays a captured stream to the exe and records the replies.
5. Write each difference in `Docs/Verify/LobbyDaemon.md`: packet, field, original value, lifted value, function address.

## Files
- `tools/verify/`
- `Docs/Verify/`

## Done when
- The lifted exe starts and listens on the same ports as the original.
- `Docs/Verify/LobbyDaemon.md` lists the result of each check.
