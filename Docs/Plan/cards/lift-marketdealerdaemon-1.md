# lift-marketdealerdaemon-1: MarketDealerDaemon lift: types, SaleContext, BidContext, PurchaseContext, Postman

Repo: bns-lift (PRIVATE). IDA database: `/home/ubuntu/Documents/Codex/private-project/ida/lift/MarketDealerDaemon/MarketDealerDaemon.exe`. PDB: `/home/ubuntu/Documents/Codex/private-project/Service_348_8349/Service/MarketDealerDaemon/bin/MarketDealerDaemon.pdb`.
Read `Docs/Plan/plan.md` "Lift method" and `Docs/layout.md` first. Read the handoffs of `lift-postofficedaemon-1` to `-5`.

## Modules (in `src/Server/Economy/MarketDealerDaemon/`, one `.cpp` + `.h` per PDB module)
Function counts are real functions without EH funclets and scalar deleting destructors. Pseudocode: `.scratch/hr/<Module>.c` (copy of `~/.cache/bns-lift/hr/MarketDealerDaemon/`). Before you lift a function, look for it in `src/` (grep the PDB name). Do not lift it two times.
- SaleContext (21 real + STL map instances, 1,638 lines): SaleInfo, SaleItemInfo, SaleContext, SaleContextManager.
- BidContext (2: GetDealingType 0x6ee0, SetNewBidPrice 0x6f20, 56 lines), PurchaseContext (1: GetDealingType, not in the export: get it from IDA), Postman (1: DeliverPost 0x2aa60, 131 lines).
- Headers with no functions in the PDB (make them from the PDB types when a module needs them): Dealings.h, DeliveryRelation.h, Participant.h, MarketStatement.h, SearchContext.h, MarketDealerDefine.h, MarketDealerPreprocessor.h.
- Common delta: Db::ConvertTime (0x3c9f0, 21 lines, BloodLib `Db.obj`) is not in `src/Server/BloodLib/source/Db.cpp`. Add it. The other BloodLib, BloodCrypto, FragmentPacket, ThreadFreePacketPump and BnsCommonConfigDefinition functions are already in `src/` (inline or lifted). Before you lift a function, grep its PDB name in `src/`.
- Total: about 25 functions, about 1,850 pseudocode lines.

Pattern: `src/Server/Economy/PostOfficeDaemon/PostContext.cpp` (context + context manager). Read each pattern one time. Do not search other servers.

## Tasks
1. Generate `include/pdb/MarketDealerDaemon/types.h` with `tools/pdb2h.py` and add `src/selftest/pdb_types_MarketDealerDaemon.cpp` (pattern: `src/selftest/pdb_types_PostOfficeDaemon.cpp`).
2. Add the static library `lift_marketdealerdaemon` to `CMakeLists.txt` and the include path `src/Server/Economy/MarketDealerDaemon`. Pattern: the `lift_postofficedaemon` block.
3. Read `.scratch/hr/<Module>.c` of each module one time. Lift the functions to C++ with the PDB types (`include/pdb/MarketDealerDaemon/types.h`). Calls to code of later cards stay as declarations.
4. Run `.scratch/gate_errors.sh` after each module. CacheGate, SmartCouponDaemon, LobbyGate and PostOfficeDaemon must still link.

## Files
- `src/Server/Economy/MarketDealerDaemon/`
- `src/Server/BloodLib/`
- `src/selftest/`
- `include/pdb/`
- `include/vs2010/`
- `CMakeLists.txt`

## Done when
- All functions of the modules are in C++, or listed in the handoff as Not done with the address.
- `tools/gate.sh` prints `gate ok`.
