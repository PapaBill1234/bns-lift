# lift-postofficedaemon-4: PostOfficeDaemon lift: post context, post relays, CacheEconomy handler

Repo: bns-lift (PRIVATE). IDA database: `<work-root>/ida/lift/PostOfficeDaemon/PostOfficeDaemon.exe`. PDB: `<work-root>/Service_348_8349/Service/PostOfficeDaemon/bin/PostOfficeDaemon.pdb`.
Read `Docs/Plan/plan.md` "Lift method" first. Read the handoffs of `lift-postofficedaemon-1` to `-3`.

## Modules (in `src/PostOfficeDaemon/`, one `.cpp` + `.h` per PDB module)
Function counts are PDB symbol counts without EH funclets. Before you lift a function, look for it in `src/` (grep the PDB name).
- PostContext (25, with `std::map<__int64, PostContext*>`).
- PostDeliveryEvent (6).
- DeliverPostRelay (13), CheckPostCapacityRelay (7), RetrieveCharacterInfoRelay (7).
- CacheEconomyPacketHandler (16) and CacheEconomyClientSideHandlerList (data table only).
- About 74 functions.

## Tasks
1. Read `.scratch/hr/<Module>.c` for each module. Use IDA for vtables and handler tables.
2. Lift the functions to C++ with the PDB types (`include/pdb/PostOfficeDaemon/types.h`).
3. Remove the declarations from cards 2 and 3 that this card now defines.
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
