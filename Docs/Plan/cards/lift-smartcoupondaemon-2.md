# lift-smartcoupondaemon-2: SmartCouponDaemon lift: network, session, packet (common)

Repo: bns-lift (PRIVATE). IDA database: `/home/ubuntu/Documents/Codex/private-project/ida/lift/SmartCouponDaemon/SmartCouponDaemon.exe`. PDB: `/home/ubuntu/Documents/Codex/private-project/Service_348_8349/Service/SmartCouponDaemon/bin/SmartCouponDaemon.pdb`.
Read `Docs/Plan/plan.md` "Lift method" first. Read the handoffs of the earlier lift cards (`lift-cg-*`, `lift-smartcoupondaemon-1`) for the state of `src/common/`.

## Modules (one `.cpp` + `.h` per PDB module, BloodLib, in `src/common/`)
Function counts are PDB symbol counts. They include EH funclets and scalar deleting destructors.
- Network (20), Packet (6), Session (36), Channel (9) (71)
- PacketBufferHandler (12), PacketBuffer (12), SessionBuffer (8) (32)
- Port (43), IoWorkerThread (6), Connection (8), Listener (9) (66)
- About 169 functions.

## Notes
- `lift-cg-3` did not write source for these modules (see its handoff). Its function list is for CacheGate. CacheGate also has FragmentPacket and PacketUtil. SmartCouponDaemon does not. Do not lift them here.
- `Network.h` exists with declarations (for example Network::GetAddressStringW). Complete it.
- Port holds `std::deque<Session*>`. If `include/vs2010/` has no deque, add it with the VS2010 layout from the PDB.
- If a later run of `lift-cg-3` added a module of this card to `src/common/`, lift only the missing functions.
- Write the SmartCouponDaemon RVA as `// 0x<rva> (SmartCouponDaemon)`.

## Tasks
1. List the functions of each module from the PDB (`llvm-pdbutil dump -symbols`, section of the module) or from IDA.
2. Decompile them in batches to `.scratch/`. Lift them to C++ with the PDB types.
3. Add the files to `lift_common` in `CMakeLists.txt`.
4. Run `tools/gate.sh` after each module.

## Files
- `src/common/`
- `include/vs2010/`
- `CMakeLists.txt`

## Done when
- All functions of the modules are in C++, or listed in the handoff as Not done with the address.
- `tools/gate.sh` prints `gate ok`.
