# lift-lobbygate-4: LobbyGate lift: LobbyGate app modules, full exe

Repo: bns-lift (PRIVATE). IDA database: `/home/ubuntu/Documents/Codex/private-project/ida/lift/LobbyGate/LobbyGate.exe`. PDB: `/home/ubuntu/Documents/Codex/private-project/Service_348_8349/Service/LobbyGate/bin/LobbyGate.pdb`.
Read `Docs/Plan/plan.md` "Lift method" first. Read the handoffs of the earlier lift cards (CacheGate, SmartCouponDaemon, LobbyGate) for the state of `src/common/`.

## Modules (in `src/LobbyGate/`, one `.cpp` + `.h` per PDB module)
Function counts are PDB symbol counts. They include EH funclets (`dtor$N`, `catch$N`) and scalar deleting destructors. The real lift count is lower. Before you lift a function, look for it in `src/common/` (grep the PDB name). Do not lift it two times.
- LobbyDPacketHandler (80), LobbyGate (54, with `wmain`), LobbyGatePacketHandler (40), PcCafeMileageFeverTimeScheduleList (8), WorldListManager (7), LobbyGatePredefine (5: Goods, GoodsItem), LobbyGateConfig (1: Dump, and the config definition table).
- BnsCommonConfigDefinition (10) is already in `src/common/BnsCommonConfig.cpp`. Only compare its `_Def` tables with LobbyGate. Write a difference in the handoff.
- About 195 symbols.
- The exe loads `XmlReader_sv64.dll`, `bsConsole_sv64.dll` and `dbghelp.dll` at run time (strings in the exe, not imports). Keep the run-time load. Do not link them.
- Find the startup path from the original entry point to `wmain` (`wcrtexe.obj`). Use `src/crt/` for CRT parts. Do not lift CRT modules (wcrtexe, wdllargv, ehvecctr, ehvecdtr, gshandler*, amdsecgs, chkstk, atonexit, pesect, merr, ti_inst, unhandld, gs_*, _initsect_).

## Tasks
1. List the functions of each module from the PDB (`llvm-pdbutil dump -modules -symbols`, section of the module) or from IDA.
2. Decompile them in batches to `.scratch/`. Lift them to C++ with the PDB types (`include/pdb/LobbyGate/types.h`).
3. Add the CMake target `LobbyGate` (exe with `lift_exe`; link `lift_lobbygate`, `lift_common` and `lift_zstd`; system libs user32, advapi32, shell32, ole32, shlwapi, version, ws2_32, iphlpapi). At the end the exe links with no stub bodies, or the handoff lists each stub.
4. Run `tools/gate.sh` after each module.

## Files
- `src/LobbyGate/`
- `src/crt/`
- `src/common/`
- `CMakeLists.txt`

## Done when
- All functions of the modules are in C++, or listed in the handoff as Not done with the address.
- `tools/gate.sh` prints `gate ok`.
