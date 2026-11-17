# lift-marketdealerdaemon-7: MarketDealerDaemon lift: MarketDB part 4, ManagementJobContext

Repo: bns-lift (PRIVATE). IDA database: `/home/ubuntu/Documents/Codex/private-project/ida/lift/MarketDealerDaemon/MarketDealerDaemon.exe`. PDB: `/home/ubuntu/Documents/Codex/private-project/Service_348_8349/Service/MarketDealerDaemon/bin/MarketDealerDaemon.pdb`.
Read `Docs/Plan/plan.md` "Lift method" and `Docs/layout.md` first. Read the handoffs of `lift-marketdealerdaemon-1` to `-6`.

## Modules (in `src/Server/Economy/MarketDealerDaemon/`, one `.cpp` + `.h` per PDB module)
Function counts are real functions without EH funclets and scalar deleting destructors. Pseudocode: `.scratch/hr/<Module>.c` (copy of `~/.cache/bns-lift/hr/MarketDealerDaemon/`). Before you lift a function, look for it in `src/` (grep the PDB name). Do not lift it two times.
- MarketDB part 4 (5 functions, lines 6,444 to 7,447 of `MarketDB.c`): SuspendSaleByManager 0x27440, ResetDeliveryFailureByManager 0x276b0, ResetAllDeliveryFailureByManager 0x27970, LoadRetryReadyDeliveryList 0x27b50, UpdateStatusToReportFailure 0x28f50.
- ManagementJobContext (18, 1,185 lines): SuspendSaleManagementJob, RetrySingleDeliveryFailureManagementJob, RetryAllDeliveryFailureManagementJob, UpdateStatusToReportFailureManagementJob (Initialize, verifyParameter, handleJob, destructors). Write `JobContext.h` with the base class `JobContext` (PDB layout and virtual functions) in this card. Card 8 adds the job classes of `JobContext.obj`.
- Total: 23 functions, about 2,190 pseudocode lines.

Pattern: `src/Server/Economy/PostOfficeDaemon/PostOfficeDB.cpp`. Pattern: `src/Server/SmartCouponDaemon/CouponJob.cpp` (job classes). Read each pattern one time. Do not search other servers.

## Tasks
1. Read `MarketDB.c` lines 6,444 to 7,447 only. Lift the functions to C++ with the PDB types (`include/pdb/MarketDealerDaemon/types.h`). Calls to code of later cards stay as declarations.
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
