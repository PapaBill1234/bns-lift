# lift-lobbygate-1: LobbyGate lift: session, network delta, crash handler (common)

Repo: bns-lift (PRIVATE). IDA database: `<work-root>/ida/lift/LobbyGate/LobbyGate.exe`. PDB: `<work-root>/Service_348_8349/Service/LobbyGate/bin/LobbyGate.pdb`.
Read `Docs/Plan/plan.md` "Lift method" first. Read the handoffs of the earlier lift cards (CacheGate, SmartCouponDaemon, LobbyGate) for the state of `src/common/`.

## Modules (in `src/common/`, one `.cpp` + `.h` per PDB module)
Function counts are PDB symbol counts. They include EH funclets (`dtor$N`, `catch$N`) and scalar deleting destructors. The real lift count is lower. Before you lift a function, look for it in `src/common/` (grep the PDB name). Do not lift it two times.
- New in `src/common/` (BloodLib): Session (43, with ReconnectTimer), PacketUtil (16: PacketConcatenateBuffer, RepeatPacketComposer/Decomposer), Security (4: BroadcastCrypt, zstdPacketCompress), CrashHandler (18), IdleWatcher (6).
- Missing functions in modules that `src/common/` already holds: Port (31: SessionPool, `std::deque<Session*>` with StlAllocator), Network (9: NetworkEndEvent, CloseSession, SetMaxIdleTime), PacketBufferHandler (6: ClientPacketBufferHandler), Packet (5: Add, Finalize, Encrypt, Copy, ComposeV), PacketBuffer (5: CheckCompose), Channel (4: Send x2), Listener (2: PortListener), SessionBuffer (2), Connection (1), IoWorkerThread (1).
- About 153 symbols.
- Add `std::deque` to `include/vs2010/` with the VS2010 layout from the PDB, if it is not there.
- `src/common/Session.h` and `src/common/CrashHandler.h` exist. There is no `Session.cpp` and no `CrashHandler.cpp` yet.

## Tasks
1. List the functions of each module from the PDB (`llvm-pdbutil dump -modules -symbols`, section of the module). Compare the names with `src/common/`.
2. Decompile the missing functions in batches to `.scratch/`. Lift them to C++ with the PDB types (make `include/pdb/LobbyGate/types.h` with `tools/pdb2h.py` if it is not there).
3. Add each new `.cpp` to `lift_common` in `CMakeLists.txt`.
4. Run `tools/gate.sh` after each module.

## Files
- `src/common/`
- `include/vs2010/`
- `include/pdb/`
- `CMakeLists.txt`

## Done when
- All functions of the modules are in C++, or listed in the handoff as Not done with the address.
- `tools/gate.sh` prints `gate ok`.
