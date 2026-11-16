# lift-postofficedaemon-plan handoff

## Done
- Checks: exe and PDB exist. The PDB GUID E5D2030D-7658-4B87-A4D0-2F7B9DD5980D matches the exe RSDS. Imports are system DLLs, MSVCR100/MSVCP100 and ODBC32 only. There are no game DLLs.
- PDB: 1,234 function symbols. I removed the CRT modules (about 33) and the zstd modules (vendor).
- Cards (about 345 real functions):
  - `-1` common delta (about 40): TextStreamPacketBufferHandler, PacketBuffer and Packet text compose, StopPort, GrowingBuffer::Add, HeapMemoryManager::Clear, Rsa::Rsa, Port/Timer STL. It also moves Db (from src/SmartCouponDaemon/), FragmentPacket and ThreadFreePacketPump (from src/LobbyGate/) to src/common/.
  - `-2` relay core, ping, watchdog (74).
  - `-3` channels and packet handlers (77).
  - `-4` post context, post relays, CacheEconomy handler (74).
  - `-5` app, PostOfficeDB, WorldConfigManager, unsent posts, full exe (about 80).
  - `-verify` Wine run and packet log compare. It needs the MSSQL setup of the SmartCouponDaemon verify.
- Next planner: `lift-marketdealerdaemon-plan` (dep `lift-postofficedaemon-5`).
- Queue: `Docs/Plan/queue/lift-postofficedaemon-plan.tsv`, 7 rows, 9 columns each.

## Not done
- None.

## ❓
- Card 1 is larger than its function count, because it moves 3 modules between targets. If it is too long, split the moves into a new card.
- The run-time DLLs (XmlReader_sv64, bsConsole_sv64, dbghelp) are in the bin folder. Card 5 must check the load strings.
- The 381 Wine peer set can use another protocol than the 2019 exe (verify card).
- Many server module counts include `std::_Tree` instances. The real lift work can be less than the counts.

## Blocked
- None.

## Gate result
- `tools/gate.sh` prints `gate ok` (only warnings: offsetof on Session).
