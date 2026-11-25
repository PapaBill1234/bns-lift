# lift-marketdealerdaemon-15: MarketDealerDaemon lift: MarketDealerDaemon app, config, full exe

Repo: bns-lift (PRIVATE). IDA database: `<work-root>/ida/lift/MarketDealerDaemon/MarketDealerDaemon.exe`. PDB: `<work-root>/Service_348_8349/Service/MarketDealerDaemon/bin/MarketDealerDaemon.pdb`.
Read `Docs/Plan/plan.md` "Lift method" and `Docs/layout.md` first. Read the handoffs of `lift-marketdealerdaemon-1` to `-14`.

## Modules (in `src/Server/Economy/MarketDealerDaemon/`, one `.cpp` + `.h` per PDB module)
Function counts are real functions without EH funclets and scalar deleting destructors. Pseudocode: `.scratch/hr/<Module>.c` (copy of `~/.cache/bns-lift/hr/MarketDealerDaemon/`). Before you lift a function, look for it in `src/` (grep the PDB name). Do not lift it two times.
- MarketDealerDaemon (30, 1,219 lines, with `wmain`): MarketDealerDaemon (Name, ShortName, ServiceName, Descriptions, setArgument, startTimer, shutdown, cooldown, FailedEventObjectHandler, PrintDependency, GetTimerInterval, GetTimerMaxTime), SessionHandler::OnCreated/OnDestroyed, DeliveryTimer and TimeoutTimer TimerId/TimerClass.
- MarketDealerConfig (no functions: the config definition table, `market_dealerd.config.xml`). BnsCommonConfigDefinition (10) is already in `src/Server/Shared/`. Only compare its `_Def` tables. Write a difference in the handoff.
- The exe imports ODBC32 (MarketDB). It loads `XmlReader_sv64.dll`, `bsConsole_sv64.dll` and `dbghelp.dll` at run time ❓ (check the strings). Keep the run-time load. Do not link them.
- Find the startup path from the original entry point to `wmain` (`wcrtexe.obj`). Use `src/crt/` for CRT parts. Do not lift CRT modules (wcrtexe, wdllargv, ehvecdtr, gshandler*, amdsecgs, chkstk, atonexit, pesect, merr, ti_inst, unhandld, gs_*, _initsect_).
- Total: 30 functions, 1,219 pseudocode lines.

Pattern: `src/Server/Economy/PostOfficeDaemon/PostOfficeDaemon.cpp` (daemon main module). Read each pattern one time. Do not search other servers.

## Tasks
1. Add the CMake target `MarketDealerDaemon` (exe with `lift_exe`; link `lift_marketdealerdaemon`, `lift_common` and `lift_zstd`; system libs user32, advapi32, shell32, ole32, odbc32, shlwapi, version, ws2_32, iphlpapi). Pattern: the `PostOfficeDaemon` target. Add a `.rc` with the version info if the original has one (pattern: `src/Server/LobbyGate/LobbyGate.rc`).
2. Remove each stub body in `LinkStubs.cpp` that a lifted function now gives. At the end the exe links with no stub bodies, or the handoff lists each stub.
3. Read `.scratch/hr/<Module>.c` of each module one time. Lift the functions to C++ with the PDB types (`include/pdb/MarketDealerDaemon/types.h`). Calls to code of later cards stay as declarations.
4. Add the new `.cpp` files to `lift_marketdealerdaemon` in `CMakeLists.txt`.
5. Run `.scratch/gate_errors.sh` after each module. CacheGate, SmartCouponDaemon, LobbyGate and PostOfficeDaemon must still link.

## Files
- `src/Server/Economy/MarketDealerDaemon/`
- `src/crt/`
- `src/Server/BloodLib/`
- `src/Server/Shared/`
- `include/pdb/`
- `CMakeLists.txt`

## Done when
- All functions of the modules are in C++, or listed in the handoff as Not done with the address.
- The `MarketDealerDaemon` exe links.
- `tools/gate.sh` prints `gate ok`.
