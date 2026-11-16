# lift-postofficedaemon-3: PostOfficeDaemon lift: channels and packet handlers (CacheGate, Agent, Management, World)

Repo: bns-lift (PRIVATE). IDA database: `/home/ubuntu/Documents/Codex/private-project/ida/lift/PostOfficeDaemon/PostOfficeDaemon.exe`. PDB: `/home/ubuntu/Documents/Codex/private-project/Service_348_8349/Service/PostOfficeDaemon/bin/PostOfficeDaemon.pdb`.
Read `Docs/Plan/plan.md` "Lift method" first. Read the handoffs of `lift-postofficedaemon-1` and `-2`.

## Modules (in `src/PostOfficeDaemon/`, one `.cpp` + `.h` per PDB module)
Function counts are PDB symbol counts without EH funclets. Before you lift a function, look for it in `src/` (grep the PDB name).
- CacheGateChannel (12), CacheGatePacketHandler (9).
- AgentChannel (6), AgentPacketHandler (3).
- ManagementSessionHandler (4), ManagementPacketHandler (5).
- WorldChannel (22, with `std::map<unsigned short, WorldChannel*>`), WorldPacketHandler (16).
- Handler list modules with no functions (data tables only): CacheGateClientSideHandlerList, PostOfficeManagementPacketHandlerList, PostOfficeServerSideHandlerList, PostOfficeServiceServerSideHandlerList. Lift the tables (read the data in IDA). CacheEconomyClientSideHandlerList goes to card 4.
- About 77 functions.
- `CacheGateChannel::...` has 4 name matches in `src/CacheGate/`. They are other classes of the CacheGate server. Do not reuse them.

## Tasks
1. Read `.scratch/hr/<Module>.c` for each module. Use IDA for vtables and handler tables.
2. Lift the functions to C++ with the PDB types (`include/pdb/PostOfficeDaemon/types.h`).
3. Put calls to code of later cards (post context, relays) behind declarations.
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
