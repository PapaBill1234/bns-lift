# lift-marketdealerdaemon-14: MarketDealerDaemon lift: AgentPacketHandler, agent handler lists

Repo: bns-lift (PRIVATE). IDA database: `<work-root>/ida/lift/MarketDealerDaemon/MarketDealerDaemon.exe`. PDB: `<work-root>/Service_348_8349/Service/MarketDealerDaemon/bin/MarketDealerDaemon.pdb`.
Read `Docs/Plan/plan.md` "Lift method" and `Docs/layout.md` first. Read the handoffs of `lift-marketdealerdaemon-1` to `-13`.

## Modules (in `src/Server/Economy/MarketDealerDaemon/`, one `.cpp` + `.h` per PDB module)
Function counts are real functions without EH funclets and scalar deleting destructors. Pseudocode: `.scratch/hr/<Module>.c` (copy of `~/.cache/bns-lift/hr/MarketDealerDaemon/`). Before you lift a function, look for it in `src/` (grep the PDB name). Do not lift it two times.
- AgentPacketHandler (29, 1,767 lines): HandleMarketDealerHelloReq 0x40d0 and the 24 HandleMarketDealer...Req handlers (0x45b0 to 0x6d80). The job destructors in this module are already in `JobContext.cpp` (cards 8 to 12).
- MarketDealerServerSideHandlerList and MarketAgentClientSideHandlerList (no functions: the handler tables). Add the packet command headers of the market dealer protocol to `src/Server/Packet/` if they are missing.
- Total: 29 functions, 1,767 pseudocode lines.

Pattern: `src/Server/Economy/PostOfficeDaemon/AgentPacketHandler.cpp` (agent handlers). Pattern: `src/Server/Economy/PostOfficeDaemon/PostOfficePacketServerSideHandlerList.cpp` (handler table). Read each pattern one time. Do not search other servers.

## Tasks
1. Read `.scratch/hr/<Module>.c` of each module one time. Lift the functions to C++ with the PDB types (`include/pdb/MarketDealerDaemon/types.h`). Calls to code of later cards stay as declarations.
2. Add the new `.cpp` files to `lift_marketdealerdaemon` in `CMakeLists.txt`.
3. Run `.scratch/gate_errors.sh` after each module. CacheGate, SmartCouponDaemon, LobbyGate and PostOfficeDaemon must still link.

## Files
- `src/Server/Economy/MarketDealerDaemon/`
- `src/Server/Packet/`
- `include/pdb/`
- `include/vs2010/`
- `CMakeLists.txt`

## Done when
- All functions of the modules are in C++, or listed in the handoff as Not done with the address.
- `tools/gate.sh` prints `gate ok`.
