# lift-postofficedaemon-1: PostOfficeDaemon lift: common delta, move Db, FragmentPacket and ThreadFreePacketPump to common

Repo: bns-lift (PRIVATE). IDA database: `<work-root>/ida/lift/PostOfficeDaemon/PostOfficeDaemon.exe`. PDB: `<work-root>/Service_348_8349/Service/PostOfficeDaemon/bin/PostOfficeDaemon.pdb`.
Read `Docs/Plan/plan.md` "Lift method" first. Read the handoffs of the earlier lift cards (CacheGate, SmartCouponDaemon, LobbyGate) for the state of `src/common/`.

## Modules (in `src/common/`)
Function counts are PDB symbol counts without EH funclets. Before you lift a function, look for it in `src/` (grep the PDB name). Do not lift it two times.
- Missing BloodLib functions (about 35):
  - PacketBufferHandler: `TextStreamPacketBufferHandler` (7: MinimalPacketSize, Initialize, AllocSize, ToBuffer, Destroy, Clone, ToPacket).
  - PacketBuffer: `parseString`, `parseDecInt`, `parseHexInt`, `isHex`, `PacketBuffer::ComposeText`, `PacketBuffer::DecomposeText` (6).
  - Packet: `Packet::ComposeText`, `Packet::DecomposeText` (2).
  - Network `Network::StopPort`, Memory `GrowingBuffer::Add`, MemoryManager `HeapMemoryManager::Clear`, BaseMemory `MemoryManager::DumpLeak`, LogMedia `LogMedia::~LogMedia`, rsa `Rsa::Rsa` (6).
  - STL instances: Port (8, `std::deque<Session*>`), Timer (5, `std::priority_queue<Timer*>`). Put them back as STL calls. Add a missing container to `include/vs2010/` if necessary.
- Db (19, BloodLib `Db.obj`): it is lifted in `src/SmartCouponDaemon/Db.cpp`. Move `Db.cpp` + `Db.h` to `src/common/`. Update the SmartCouponDaemon target. PostOfficeDB (card 5) uses it.
- FragmentPacket (23) and ThreadFreePacketPump (21): the PostOfficeDaemon PDB has them too (server project, same code as LobbyGate). Compare `src/LobbyGate/` and `src/common/FragmentPacket.cpp` with the PostOfficeDaemon pseudocode. If they are the same, move them to `src/common/` and update the LobbyGate target. Lift the missing ones: `PacketFormatIterator::Allocated`, `__pump_fragment_packet`, `DynamicEventObject::deallocate_me` (check first, about 3).
- Write the module differences (PostOfficeDaemon vs LobbyGate) in the handoff.

## Tasks
1. Read `.scratch/hr/<Module>.c` for each module. Use IDA only for data that is not in the pseudocode.
2. Lift the functions to C++ with the PDB types (generate `include/pdb/PostOfficeDaemon/types.h` with `tools/pdb2h.py` if it does not exist).
3. Run `tools/gate.sh` after each module. CacheGate, SmartCouponDaemon and LobbyGate must still link.

## Files
- `src/common/`
- `src/SmartCouponDaemon/`
- `src/LobbyGate/`
- `include/vs2010/`
- `include/pdb/`
- `CMakeLists.txt`

## Done when
- All functions of the modules are in C++, or listed in the handoff as Not done with the address.
- `tools/gate.sh` prints `gate ok`.
