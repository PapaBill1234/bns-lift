# lift-marketdealerdaemon-6: MarketDealerDaemon lift: MarketDB part 3 (expire, status), DeliveryTimer, TimeoutTimer

Repo: bns-lift (PRIVATE). IDA database: `<work-root>/ida/lift/MarketDealerDaemon/MarketDealerDaemon.exe`. PDB: `<work-root>/Service_348_8349/Service/MarketDealerDaemon/bin/MarketDealerDaemon.pdb`.
Read `Docs/Plan/plan.md` "Lift method" and `Docs/layout.md` first. Read the handoffs of `lift-marketdealerdaemon-1` to `-5`.

## Modules (in `src/Server/Economy/MarketDealerDaemon/`, one `.cpp` + `.h` per PDB module)
Function counts are real functions without EH funclets and scalar deleting destructors. Pseudocode: `.scratch/hr/<Module>.c` (copy of `~/.cache/bns-lift/hr/MarketDealerDaemon/`). Before you lift a function, look for it in `src/` (grep the PDB name). Do not lift it two times.
- MarketDB part 3 (11 functions, lines 4,685 to 6,443 of `MarketDB.c`): ExpireSale 0x24100, ExpireAuction 0x24490, UpdateStatusToReporting 0x24e90, UpdateStatusToReportSuccess 0x25110, UpdateStatusToPawnRemovalSuccess 0x25320, UpdateStatusToPawnRemovalFailure 0x25530, UpdateStatusToPostRegistrationSuccess 0x25740, UpdateStatusToPostRegistrationFailure 0x259b0, UpdateStatusToRetryReady 0x25bc0, LoadRetryReadySingleDelivery 0x25dd0, ResetUncompletedDeliveryStatus 0x27230.
- DeliveryTimer (2, 209 lines): checkDelivery, HandleEvent. TimeoutTimer (3, 333 lines): checkSaleExpiration, postTimeoutEvent, HandleEvent. TimerId and TimerClass of both are in `MarketDealerDaemon.obj` (card 15). Put them in the headers if they are inline.
- Total: 16 functions, about 2,300 pseudocode lines.

Pattern: `src/Server/Economy/PostOfficeDaemon/PostOfficeDB.cpp`. Pattern: `src/Server/Economy/PostOfficeDaemon/RelayTimeoutChecker.cpp` (timer). Read each pattern one time. Do not search other servers.

## Tasks
1. Read `MarketDB.c` lines 4,685 to 6,443 only. Lift the functions to C++ with the PDB types (`include/pdb/MarketDealerDaemon/types.h`). Calls to code of later cards stay as declarations.
2. Add the new `.cpp` files to `lift_marketdealerdaemon` in `CMakeLists.txt`.
3. Run `.scratch/gate_errors.sh` after each module. CacheGate, SmartCouponDaemon, LobbyGate and PostOfficeDaemon must still link.

## Files
- `src/Server/Economy/MarketDealerDaemon/`
- `include/pdb/`
- `include/vs2010/`
- `CMakeLists.txt`

## Done when
- All functions of the modules are in C++, or listed in the handoff as Not done with the address.
- `tools/gate.sh` prints `gate ok`.
