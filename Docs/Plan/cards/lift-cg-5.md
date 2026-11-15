# lift-cg-5: CacheGate lift: CacheGate app, full exe

Repo: bns-lift (PRIVATE). IDA database: `/home/ubuntu/Documents/Codex/private-project/ida/lift/CacheGate/CacheGate.exe`. PDB: `/home/ubuntu/Documents/Codex/private-project/Service_348_8349/Service/CacheGate/bin/CacheGate.pdb`.
Read `Docs/Plan/plan.md` "Lift method" first. Read the handoffs of the earlier lift cards for the state of `src/common/`.

## Modules (one `.cpp` + `.h` per PDB module)
- CacheGate, CacheD, CacheDChannel, ClientManager, CacheGateSessionHandler, CacheGateServerSideHandlerList (about 130)
- Find the startup path from the original entry point to `main`/`wmain` (`wcrtexe.obj`). Use `src/crt/` for CRT parts. Do not lift CRT modules (wcrtexe, ehvecdtr, gshandler, chkstk, atonexit, pesect, merr, ti_inst, unhandld, gs_*).

## Tasks
1. List the functions of each module from the PDB (`llvm-pdbutil dump -symbols`, section of the module) or from IDA.
2. Decompile them in batches to `.scratch/`. Lift them to C++ with the PDB types (`include/pdb/CacheGate/types.h`).
3. Add the files to the CMake target `CacheGate` (exe with `lift_exe`; link `lift_common`). At the end the exe links with no stub bodies, or the handoff lists each stub.
4. Run `tools/gate.sh` after each module.

## Files
- `src/CacheGate/`
- `src/crt/`
- `src/common/`
- `CMakeLists.txt`

## Done when
- All functions of the modules are in C++, or listed in the handoff as Not done with the address.
- `tools/gate.sh` prints `gate ok`.
