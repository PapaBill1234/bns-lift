# lift-marketdealerdaemon-4: MarketDealerDaemon lift: MarketDB part 1 (load lists)

Repo: bns-lift (PRIVATE). IDA database: `<work-root>/ida/lift/MarketDealerDaemon/MarketDealerDaemon.exe`. PDB: `<work-root>/Service_348_8349/Service/MarketDealerDaemon/bin/MarketDealerDaemon.pdb`.
Read `Docs/Plan/plan.md` "Lift method" and `Docs/layout.md` first. Read the handoffs of `lift-marketdealerdaemon-1` to `-3`.

## Modules (in `src/Server/Economy/MarketDealerDaemon/`, one `.cpp` + `.h` per PDB module)
Function counts are real functions without EH funclets and scalar deleting destructors. Pseudocode: `.scratch/hr/<Module>.c` (copy of `~/.cache/bns-lift/hr/MarketDealerDaemon/`). Before you lift a function, look for it in `src/` (grep the PDB name). Do not lift it two times.
- MarketDB part 1 (7 functions, lines 1 to 2,428 of `MarketDB.c`): AutoDbTran::~AutoDbTran 0x1b170, SetSaleIncomeTaxRateTable 0x1b1c0, SetGrossIncomeTaxRateTable 0x1b4f0, LoadSaleList 0x1b820, LoadBidList 0x1cf40, LoadPurchaseList 0x1d9b0, LoadDeliveryList 0x1e400.
- Write the class `MarketDB` (header with all 38 member declarations) in this card. Cards 5, 6 and 7 add the other bodies to `MarketDB.cpp`.
- Total: 7 functions (large ODBC functions), 2,428 pseudocode lines.

Pattern: `src/Server/Economy/PostOfficeDaemon/PostOfficeDB.cpp` (DB class on `Db`). Read each pattern one time. Do not search other servers.

## Tasks
1. Read `MarketDB.c` lines 1 to 2,428 only (two parts of about 1,200 lines). Lift the functions to C++ with the PDB types (`include/pdb/MarketDealerDaemon/types.h`). Calls to code of later cards stay as declarations.
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
