# lift-marketdealerdaemon-13: MarketDealerDaemon lift: TimeoutEvent, ManagerPacketHandler, manager handler list

Repo: bns-lift (PRIVATE). IDA database: `/home/ubuntu/Documents/Codex/private-project/ida/lift/MarketDealerDaemon/MarketDealerDaemon.exe`. PDB: `/home/ubuntu/Documents/Codex/private-project/Service_348_8349/Service/MarketDealerDaemon/bin/MarketDealerDaemon.pdb`.
Read `Docs/Plan/plan.md` "Lift method" and `Docs/layout.md` first. Read the handoffs of `lift-marketdealerdaemon-1` to `-12`.

## Modules (in `src/Server/Economy/MarketDealerDaemon/`, one `.cpp` + `.h` per PDB module)
Function counts are real functions without EH funclets and scalar deleting destructors. Pseudocode: `.scratch/hr/<Module>.c` (copy of `~/.cache/bns-lift/hr/MarketDealerDaemon/`). Before you lift a function, look for it in `src/` (grep the PDB name). Do not lift it two times.
- TimeoutEvent (8, 1,527 lines): AuctionTimeoutEvent, InstantSaleTimeoutEvent (EventId, processTimeout, HandleEvent).
- ManagerPacketHandler (5, 317 lines): HandleMarketManagerHelloReq, ...SuspendSaleReq, ...RetrySingleDeliveryFailureReq, ...RetryAllDeliveryFailureReq, ...UpdateStatusToReportFailureReq.
- MarketManagerServerSideHandlerList (no functions: the handler table). Add the packet command header for the market manager protocol to `src/Server/Packet/` if it is missing.
- Total: 13 functions, about 1,850 pseudocode lines.

Pattern: `src/Server/Economy/PostOfficeDaemon/RelayTimeoutEvent.cpp` (timeout event). Pattern: `src/Server/SmartCouponDaemon/ManagerPacketHandler.cpp` (manager handlers). Pattern: `src/Server/Economy/PostOfficeDaemon/PostOfficeManagementPacketHandlerList.cpp` (handler table). Read each pattern one time. Do not search other servers.

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
