# lift-marketdealerdaemon-plan handoff

## Done
- Checks: exe and PDB exist. PDB GUID 83735B7E-0FA8-4B65-B5E4-F8F5663FE8CF matches the exe RSDS. Imports: system DLLs, MSVCR100/MSVCP100, ODBC32. No game DLLs.
- PDB: 995 real functions (no EH funclets, no deleting destructors). I removed the CRT modules and the zstd modules (vendor). BloodLib, BloodCrypto, FragmentPacket, ThreadFreePacketPump and BnsCommonConfigDefinition are already in `src/`. Only Db::ConvertTime (0x3c9f0) is missing (card 1).
- Pseudocode line counts: `~/.cache/bns-lift/hr/MarketDealerDaemon/index.tsv` (export done 2026-11-17).
- Cards (about 375 functions, all at 2,430 pseudocode lines or fewer):
  - `-1` types, SaleContext, BidContext, PurchaseContext, Postman, Db::ConvertTime.
  - `-2` DeliveryContext, TaxRateDataManager. `-3` SaleTimeContext, AgentChannel, ManagerChannel.
  - `-4` to `-7` MarketDB (7,447 lines) in 4 parts by address. `-6` adds DeliveryTimer, TimeoutTimer. `-7` adds ManagementJobContext and the JobContext base class.
  - `-8` to `-12` JobContext (11,032 lines, 135 functions) in 5 parts by class.
  - `-13` TimeoutEvent, ManagerPacketHandler, manager handler list. `-14` AgentPacketHandler, agent handler lists.
  - `-15` MarketDealerDaemon app, config, full exe.
  - `-verify` Wine run and packet log compare (MSSQL setup of the earlier verify cards).
- Next planner: `lift-infogatedaemon-plan` (dep `lift-marketdealerdaemon-15`).
- Queue: `Docs/Plan/queue/lift-marketdealerdaemon-plan.tsv`, 17 rows, 9 columns each.

## Not done
- None.

## ❓
- The source folder is `src/Server/Economy/MarketDealerDaemon/` (PDB path `server\economy\marketdealerdaemon`). The task text says `src/<Server>/`, but `Docs/layout.md` rules apply.
- PurchaseContext::GetDealingType is not in the export (folded code ❓). Card 1 gets it from IDA.
- Cards 4 to 7 have few functions, but each MarketDB function is large (ODBC binds).
- The market DB procedures can be missing in the MSSQL container (verify card).

## Blocked
- None.

## Gate result
- `tools/gate.sh` prints `gate ok` (rc 0).
