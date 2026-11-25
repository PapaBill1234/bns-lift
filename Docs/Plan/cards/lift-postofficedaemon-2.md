# lift-postofficedaemon-2: PostOfficeDaemon lift: relay core, ping, watchdog

Repo: bns-lift (PRIVATE). IDA database: `<work-root>/ida/lift/PostOfficeDaemon/PostOfficeDaemon.exe`. PDB: `<work-root>/Service_348_8349/Service/PostOfficeDaemon/bin/PostOfficeDaemon.pdb`.
Read `Docs/Plan/plan.md` "Lift method" first. Read the handoffs of `lift-postofficedaemon-1` and the LobbyGate cards for the state of `src/common/`.

## Modules (in `src/PostOfficeDaemon/`, one `.cpp` + `.h` per PDB module)
Function counts are PDB symbol counts without EH funclets. They include STL instances (`std::_Tree<...>`). Put them back as STL calls. Before you lift a function, look for it in `src/` (grep the PDB name).
- RelayContext (19): `RelayContext`, relay map `std::map<unsigned __int64, RelayContext*>`.
- RelayTimeContext (16): `std::map<CompoundKey, RelayTimeContext*>`.
- RelayTimeoutChecker (3), RelayTimeoutEvent (2).
- PingRelay (5: `PingRelayContext`), PingGenerator (12).
- CachedWatchdog (17: `CachedWatchdog`, `CachedWatchdogManager`).
- About 74 functions.

## Tasks
1. Read `.scratch/hr/<Module>.c` for each module. Use IDA for vtables and data only.
2. Lift the functions to C++ with the PDB types (`include/pdb/PostOfficeDaemon/types.h`).
3. Add the CMake library `lift_postofficedaemon` (static, links `lift_common`). Put calls to code of later cards behind declarations.
4. Run `tools/gate.sh` after each module.

## Files
- `src/PostOfficeDaemon/`
- `src/common/`
- `include/pdb/`
- `include/vs2010/`
- `CMakeLists.txt`

## Done when
- All functions of the modules are in C++, or listed in the handoff as Not done with the address.
- `tools/gate.sh` prints `gate ok`.
