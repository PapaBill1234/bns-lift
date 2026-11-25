# lift-postofficedaemon-5: PostOfficeDaemon lift: PostOfficeDaemon app, DB, world config, unsent posts, full exe

Repo: bns-lift (PRIVATE). IDA database: `<work-root>/ida/lift/PostOfficeDaemon/PostOfficeDaemon.exe`. PDB: `<work-root>/Service_348_8349/Service/PostOfficeDaemon/bin/PostOfficeDaemon.pdb`.
Read `Docs/Plan/plan.md` "Lift method" first. Read the handoffs of `lift-postofficedaemon-1` to `-4`.

## Modules (in `src/PostOfficeDaemon/`, one `.cpp` + `.h` per PDB module)
Function counts are PDB symbol counts without EH funclets. Before you lift a function, look for it in `src/` (grep the PDB name).
- PostOfficeDaemon (36, with `wmain`), PostOfficeDB (10, uses `Db` in `src/common/`), WorldConfigManager (24, with `std::map<unsigned short, WorldConfig*>`).
- UnsentPostContext (9), UnsentPostChecker (1).
- PostOfficeConfig (no functions: the config definition table). BnsCommonConfigDefinition (10) is already in `src/common/BnsCommonConfigDefinition.cpp`. Only compare its `_Def` tables. Write a difference in the handoff.
- About 80 functions.
- The exe imports ODBC32 (PostOfficeDB). It loads `XmlReader_sv64.dll`, `bsConsole_sv64.dll` and `dbghelp.dll` at run time ❓ (check the strings). Keep the run-time load. Do not link them.
- Find the startup path from the original entry point to `wmain` (`wcrtexe.obj`). Use `src/crt/` for CRT parts. Do not lift CRT modules (wcrtexe, wdllargv, ehvecctr, ehvecdtr, gshandler*, amdsecgs, chkstk, atonexit, pesect, merr, ti_inst, unhandld, gs_*, _initsect_).

## Tasks
1. Read `.scratch/hr/<Module>.c` for each module. Lift the functions to C++ with the PDB types (`include/pdb/PostOfficeDaemon/types.h`).
2. Add the CMake target `PostOfficeDaemon` (exe with `lift_exe`; link `lift_postofficedaemon`, `lift_common` and `lift_zstd`; system libs user32, advapi32, shell32, ole32, odbc32, shlwapi, version, ws2_32, iphlpapi). At the end the exe links with no stub bodies, or the handoff lists each stub.
3. Run `tools/gate.sh` after each module.

## Files
- `src/PostOfficeDaemon/`
- `src/crt/`
- `src/common/`
- `CMakeLists.txt`

## Done when
- All functions of the modules are in C++, or listed in the handoff as Not done with the address.
- The `PostOfficeDaemon` exe links.
- `tools/gate.sh` prints `gate ok`.
