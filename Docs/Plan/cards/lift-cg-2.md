# lift-cg-2: CacheGate lift: console, daemon, config

Repo: bns-lift (PRIVATE). IDA database: `/home/ubuntu/Documents/Codex/private-project/ida/lift/CacheGate/CacheGate.exe`. PDB: `/home/ubuntu/Documents/Codex/private-project/Service_348_8349/Service/CacheGate/bin/CacheGate.pdb`.
Read `Docs/Plan/plan.md` "Lift method" first. Read the handoffs of the earlier lift cards for the state of `src/common/`.

## Modules (one `.cpp` + `.h` per PDB module)
- Console, PipeConsole, WindowConsole, TextConsole, WinServiceConsole (about 106)
- Daemon, DaemonConfig (about 25)
- BnsCommonConfigDefinition (10)

## Tasks
1. List the functions of each module from the PDB (`llvm-pdbutil dump -symbols`, section of the module) or from IDA.
2. Decompile them in batches to `.scratch/`. Lift them to C++ with the PDB types (`include/pdb/CacheGate/types.h`).
3. Add the files to the CMake target `lift_common` (static library; create it if it does not exist).
4. Run `tools/gate.sh` after each module.

## Files
- `src/common/`
- `CMakeLists.txt`
- `include/vs2010/`

## Done when
- All functions of the modules are in C++, or listed in the handoff as Not done with the address.
- `tools/gate.sh` prints `gate ok`.
