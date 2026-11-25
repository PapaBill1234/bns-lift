# lift-marketdealerdaemon-2: MarketDealerDaemon lift: DeliveryContext, TaxRateDataManager

Repo: bns-lift (PRIVATE). IDA database: `<work-root>/ida/lift/MarketDealerDaemon/MarketDealerDaemon.exe`. PDB: `<work-root>/Service_348_8349/Service/MarketDealerDaemon/bin/MarketDealerDaemon.pdb`.
Read `Docs/Plan/plan.md` "Lift method" and `Docs/layout.md` first. Read the handoffs of `lift-marketdealerdaemon-1` to `-1`.

## Modules (in `src/Server/Economy/MarketDealerDaemon/`, one `.cpp` + `.h` per PDB module)
Function counts are real functions without EH funclets and scalar deleting destructors. Pseudocode: `.scratch/hr/<Module>.c` (copy of `~/.cache/bns-lift/hr/MarketDealerDaemon/`). Before you lift a function, look for it in `src/` (grep the PDB name). Do not lift it two times.
- DeliveryContext (13 real + 12 STL instances, 1,565 lines): DeliveryInfo, DeliveryContext, DeliveryContextManager, CriticalSection::CriticalSection.
- TaxRateDataManager (4, 795 lines): initDataManager, SetTaxRateTable, setSaleIncomeTaxRateTable, setGrossIncomeTaxRateTable.
- Total: about 29 functions, about 2,360 pseudocode lines.

Pattern: `src/Server/Economy/PostOfficeDaemon/PostContext.cpp` (context manager). Pattern: `src/Server/Economy/PostOfficeDaemon/WorldConfigManager.cpp` (data manager with std::map). Read each pattern one time. Do not search other servers.

## Tasks
1. Read `.scratch/hr/<Module>.c` of each module one time. Lift the functions to C++ with the PDB types (`include/pdb/MarketDealerDaemon/types.h`). Calls to code of later cards stay as declarations.
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
