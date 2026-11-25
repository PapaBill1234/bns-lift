# lift-lobbygate-3: LobbyGate lift: packet pump, fragment packets, Client, LobbyD channel

Repo: bns-lift (PRIVATE). IDA database: `<work-root>/ida/lift/LobbyGate/LobbyGate.exe`. PDB: `<work-root>/Service_348_8349/Service/LobbyGate/bin/LobbyGate.pdb`.
Read `Docs/Plan/plan.md` "Lift method" first. Read the handoffs of the earlier lift cards (CacheGate, SmartCouponDaemon, LobbyGate) for the state of `src/common/`.

## Modules (in `src/LobbyGate/`, one `.cpp` + `.h` per PDB module)
Function counts are PDB symbol counts. They include EH funclets (`dtor$N`, `catch$N`) and scalar deleting destructors. The real lift count is lower. Before you lift a function, look for it in `src/common/` (grep the PDB name). Do not lift it two times.
- ThreadFreePacketPump (37: ThreadFreePacketPump, ThreadFreeFragmentPacketPump, TFPP_PumpPacket). The module has inline copies of RefCntObject and EventObject members. These are already in `src/common/`. Do not lift them again.
- FragmentPacket (27: FragmentPacket, FragmentPacketConcatenater, FragmentPacketSplitter, PacketFormatIterator).
- Client (103).
- LobbyDChannel (20).
- About 187 symbols. The PDB puts these modules in the LobbyGate project (`intermediate\LobbyGate\service`), so they go in `src/LobbyGate/`.

## Tasks
1. List the functions of each module from the PDB (`llvm-pdbutil dump -modules -symbols`, section of the module) or from IDA.
2. Decompile them in batches to `.scratch/`. Lift them to C++ with the PDB types (`include/pdb/LobbyGate/types.h`).
3. Add the static library `lift_lobbygate` in `CMakeLists.txt` with these files. Do not add the exe yet.
4. Run `tools/gate.sh` after each module.

## Files
- `src/LobbyGate/`
- `src/common/`
- `include/pdb/`
- `include/vs2010/`
- `CMakeLists.txt`

## Done when
- All functions of the modules are in C++, or listed in the handoff as Not done with the address.
- `tools/gate.sh` prints `gate ok`.
