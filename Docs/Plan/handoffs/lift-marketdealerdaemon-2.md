# lift-marketdealerdaemon-2: handoff

## Done
- DeliveryContext.cpp: 10 functions. DeliveryInfo ctor 0x7100, DeliveryContext ctors 0x72a0 and 0x7370,
  dtor (inlined in 0x70c0), ComposeReportPacket 0x7420, DeliveryContextManager InitContextManager 0x7710,
  GetContext 0x78a0, AddContext 0x7b10, RemoveContext 0x7d70.
- No code needed (COMDAT copies of common code): CriticalSection ctor 0x6ff0, operator delete[] 0x7010,
  FragmentPacket::FreeSize 0x7050, FragmentPacket::Compose 0x7070. The 12 std::map instances
  (0x8020..0x8260, 0x2b210, 0x2d000..0x2d580) come from include/vs2010.
- DeliveryContext.h: full class, DeliveryContextManager added (Container typedef, inline ctor as SaleContextManager).
- TaxRateDataManager.cpp/.h: 4 functions (0x2eb30, 0x2ecd0, 0x2f040, 0x2f4f0). Tax rate data/table classes in the header.
- MarketDB.h: declarations SetSaleIncomeTaxRateTable, SetGrossIncomeTaxRateTable (later card).
- CMake: 2 new files in lift_marketdealerdaemon.
- Total: 14 functions lifted.

## Not done
- None of the card functions. Later cards must define: MarketDB::SetSaleIncomeTaxRateTable,
  MarketDB::SetGrossIncomeTaxRateTable, TaxRateDataManager ctor (inlined, no body in this card).

## Notes
- setSale/GrossIncomeTaxRateTable: LTCG removed the unused `this`. The binary gives doc in rcx. The C++ keeps the
  PDB member signature.

## ❓
- MarketDB::Set*TaxRateTable return type (PDB type 0x1626, taken as `bool const`).
- ComposeReportPacket constants postType 1 and serviceWorldType 2 have no names.

## Blocked
- None.

## Gate result
- `.scratch/gate_errors.sh`: no build errors, `gate ok`. CacheGate, SCD, LobbyGate, POD still link.
