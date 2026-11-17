# lift-marketdealerdaemon-4: handoff

## Done
- MarketDB.h: full class MarketDB (38 static members in PDB order, private ctor/dtor/operator=), AutoDbTran,
  forward declarations of the 20 job classes. Signatures come from the PDB type records (0x30BA..0x30FC).
- MarketDB.cpp: 7 functions. AutoDbTran::~AutoDbTran 0x1b170, SetSaleIncomeTaxRateTable 0x1b1c0,
  SetGrossIncomeTaxRateTable 0x1b4f0, LoadSaleList 0x1b820, LoadBidList 0x1cf40, LoadPurchaseList 0x1d9b0,
  LoadDeliveryList 0x1e400.
- The inlined DbTransaction::BindCol calls are BindCol calls again. Column order, C types and buffer sizes
  are as in the binary. The SQL_NTS pre-sets of the WCHAR length slots are kept.
- LIFT helper BindTaxRateParams (template): the two tax rate setters have the same inlined bind loop.
- CMake: MarketDB.cpp added to lift_marketdealerdaemon.

## Not done
- Card 5, 6 and 7 functions of MarketDB (0x1f840..0x28f50). They are declarations only.

## BUG marks
- 0x1b820 LoadSaleList, 0x1e400 LoadDeliveryList: no null check after the context Alloc.

## ❓
- Return type of all members: PDB type 0x1626, taken as `bool const`.
- Parameter names of the job members (`job`), ExpireSale, ExpireAuction and ResetUncompletedDeliveryStatus
  (the PDB gives the types only).
- Sale type values 1 and 2 use EconomySaleType (types.h). No src header has this enum yet, so MarketDB.cpp
  has local constants.

## Blocked
- None.

## Gate result
- `.scratch/gate_errors.sh`: no build errors, `gate ok`. CacheGate, SCD, LobbyGate, POD still link.
