# lift-marketdealerdaemon-1: handoff

## Done
- `include/pdb/MarketDealerDaemon/types.h` (356 types, tools/pdb2h.py) and `src/selftest/pdb_types_MarketDealerDaemon.cpp` (in lift_selftest).
- CMake: include path `src/Server/Economy/MarketDealerDaemon`, static library `lift_marketdealerdaemon` (/GR-).
- SaleContext.cpp: 21 functions (SaleInfo, SaleItemInfo, SaleContext, SaleContextManager). STL map code is std::map calls.
- BidContext.cpp: 2 (0x6ee0, 0x6f20). PurchaseContext.cpp: 1 (GetDealingType 0x63c60, ICF fold).
- Postman.cpp: 1 (DeliverPost 0x2aa60).
- BloodLib Db.cpp/Db.h: Db::ConvertTime (0x3c9f0 in MarketDealerDaemon).
- Total: 26 functions.
- Headers from the PDB types: Participant.h, MarketStatement.h, Dealings.h, MarketDealerDefine.h, SaleContext.h,
  BidContext.h, PurchaseContext.h, Postman.h.
- Layout-only headers for later cards (declarations, no bodies): MarketDealerDaemon.h (MarketDealerConfig,
  MarketDealerDaemon, `_instance`), AgentChannel.h (GetMarketAgentChannel 0x3860), DeliveryContext.h
  (ComposeReportPacket 0x7420), MarketDB.h (UpdateStatusToReporting 0x24e90).

## Not done
- None of the card functions. Later cards must define: MarketDealerDaemon virtuals and `_instance`,
  AgentChannel virtuals, AgentChannelManager::GetMarketAgentChannel, DeliveryContext dtor and ComposeReportPacket,
  MarketDB::UpdateStatusToReporting.
- Headers not made (no module needs them yet): DeliveryRelation.h, SearchContext.h, MarketDealerPreprocessor.h.

## BUG marks
- 0x2be00 AddBidContext, 0x2c3d0 AddPurchaseContext: no null check after Alloc.

## ❓
- Header placement of DealingInfo/BidInfo/PurchaseInfo/DealingContext (Dealings.h is a guess).
- Settled: DetermineBidUnitPrice divisor is 100.0 (rva 0xa9718, read in IDA).

## Blocked
- None.

## Gate result
- `.scratch/gate_errors.sh`: no build errors, `gate ok`. lift_marketdealerdaemon.lib builds. CacheGate, SCD, LobbyGate, POD still link.
