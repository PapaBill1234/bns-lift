# lift-smartcoupondaemon-4: SmartCouponDaemon lift: coupon app modules, full exe

Repo: bns-lift (PRIVATE). IDA database: `/home/ubuntu/Documents/Codex/private-project/ida/lift/SmartCouponDaemon/SmartCouponDaemon.exe`. PDB: `/home/ubuntu/Documents/Codex/private-project/Service_348_8349/Service/SmartCouponDaemon/bin/SmartCouponDaemon.pdb`.
Read `Docs/Plan/plan.md` "Lift method" first. Read the handoffs of the earlier lift cards for the state of `src/common/` and `src/SmartCouponDaemon/`.

## Modules (one `.cpp` + `.h` per PDB module, in `src/SmartCouponDaemon/`)
Function counts are PDB symbol counts. They include EH funclets and scalar deleting destructors.
- SmartCouponDaemon (43), SmartCouponDB (25), CouponJob (32), EventNotiJob (22), GameEventWorker (28), CouponGameEventConfig (24)
- DaemonChannel (38), DaemonPacketHandler (9), ManagerChannel (8), ManagerPacketHandler (8), SharedChannel (7)
- Data only (no function symbols): SmartCouponManagerServerSideHandlerList, SmartCouponPacketSmartCouponSideHandlerList, SmartCouponConfig (config definition table).
- About 244 functions.
- Find the startup path from the original entry point to `wmain` (`wcrtexe.obj`). Use `src/crt/` for CRT parts. Do not lift CRT modules (wcrtexe, ehvecctr, ehvecdtr, gshandler, chkstk, atonexit, pesect, merr, ti_inst, unhandld, gs_*, _initsect_).

## Tasks
1. List the functions of each module from the PDB (`llvm-pdbutil dump -symbols`, section of the module) or from IDA.
2. Decompile them in batches to `.scratch/`. Lift them to C++ with the PDB types.
3. Add the CMake target `SmartCouponDaemon` (exe with `lift_exe`; link `lift_smartcoupondaemon` and `lift_common`; system libs incl. odbc32, iphlpapi, version, shlwapi, ws2_32). At the end the exe links with no stub bodies, or the handoff lists each stub.
4. Run `tools/gate.sh` after each module.

## Files
- `src/SmartCouponDaemon/`
- `src/crt/`
- `src/common/`
- `CMakeLists.txt`

## Done when
- All functions of the modules are in C++, or listed in the handoff as Not done with the address.
- `tools/gate.sh` prints `gate ok`.
