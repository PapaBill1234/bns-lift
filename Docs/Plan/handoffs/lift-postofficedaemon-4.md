# lift-postofficedaemon-4 handoff

## Done
- PostContext.cpp/.h (13), PostDeliveryEvent.cpp/.h (6), DeliverPostRelay.cpp/.h (12),
  CheckPostCapacityRelay.cpp (9), RetrieveCharacterInfoRelay.cpp (9), CacheEconomyPacketHandler.cpp/.h (13),
  CacheEconomyClientSideHandlerList.cpp (2 tables: 0x976c0 with 22 entries, 0x98aa0 in .bss, all zero).
- 62 functions in total. Earlier-card declarations removed from WorldPacketHandler.h, CacheGatePacketHandler.h/.cpp, PostOfficeDB.h.
- CMakeLists.txt: 7 new sources in lift_postofficedaemon.

## Not done
- None. The card says 16 CacheEconomy handlers. The index and the IDA table have 13 (8 relay handlers 0x5120..0x6920,
  5 "not support" stubs 0x6c90..0x6f10). The other 3 table slots are null.

## ❓
- CacheEconomyPacketHandler: the original calls Packet::Decompose(packet, 0x18, 6, fmt, ...). Packet.h has no such overload.
  The lift calls Decompose(fmt, ...).
- CacheEconomyPacketHandler: the lift uses helpers in an anonymous namespace (processEconomyResponse, logBegin, logEnd,
  notSupported). They are not in the PDB. The original inlines this code in each handler. The line numbers are the same.
- HandleCacheEconomyPingFail 0x5490: the response resultState is the raw value 2. The process-fail log text says
  "deliver post fail" (copy-paste in the original, marked BUG).
- convertFailReason 0x9740 / 0x1e410: the case values 2/3/4 do not match RESULTSTATE in RelayContext.h. The PDB enum can start at 1.
- DeliverPostRelayContext::processRelayRequest 0xfd00: economyFormat is an uninitialized register. The lift passes nullptr.
- PostDeliveryEvent Alloc line numbers 53/106.
- SendRelayRequest / SendRelayResponse / SendFragmentRelayRequest take non-const pointers (const_cast).

## Blocked
- None. IDA opened the named .i64 one time for the handler tables.

## Gate result
- `tools/gate.sh`: gate ok (only offsetof warnings from the headers).
