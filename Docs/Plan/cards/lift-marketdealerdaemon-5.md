# lift-marketdealerdaemon-5: MarketDealerDaemon lift: MarketDB part 2 (sale, bid, purchase)

Repo: bns-lift (PRIVATE). IDA database: `<work-root>/ida/lift/MarketDealerDaemon/MarketDealerDaemon.exe`. PDB: `<work-root>/Service_348_8349/Service/MarketDealerDaemon/bin/MarketDealerDaemon.pdb`.
Read `Docs/Plan/plan.md` "Lift method" and `Docs/layout.md` first. Read the handoffs of `lift-marketdealerdaemon-1` to `-4`.

## Modules (in `src/Server/Economy/MarketDealerDaemon/`, one `.cpp` + `.h` per PDB module)
Function counts are real functions without EH funclets and scalar deleting destructors. Pseudocode: `.scratch/hr/<Module>.c` (copy of `~/.cache/bns-lift/hr/MarketDealerDaemon/`). Before you lift a function, look for it in `src/` (grep the PDB name). Do not lift it two times.
- MarketDB part 2 (17 functions, lines 2,429 to 4,684 of `MarketDB.c`): RetrieveSaleList 0x1f840, RetrieveBidList 0x20000, RetrieveReservationList 0x20760, ReserveSale 0x20b90, CancelSaleReservation 0x21150, RegisterSale 0x213c0, UpdateSalePrice 0x21b00, AbandonSale 0x21ec0, ReserveBid 0x222a0, CancelBidReservation 0x22710, RegisterBid 0x22980, UpdateBidPrice 0x22d20, AbandonBid 0x23070, ReservePurchase 0x23450, CancelPurchaseReservation 0x238d0, RegisterPurchase 0x23b40.
- Add the bodies to `MarketDB.cpp` (card 4 wrote the class).
- Total: 17 functions, 2,256 pseudocode lines.

Pattern: `src/Server/Economy/PostOfficeDaemon/PostOfficeDB.cpp`. Read each pattern one time. Do not search other servers.

## Tasks
1. Read `MarketDB.c` lines 2,429 to 4,684 only. Lift the functions to C++ with the PDB types (`include/pdb/MarketDealerDaemon/types.h`). Calls to code of later cards stay as declarations.
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
