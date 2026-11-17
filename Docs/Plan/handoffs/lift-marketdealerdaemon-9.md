# lift-marketdealerdaemon-9: handoff

## Done
- JobContext.cpp part 2 (JobContext.obj, pseudocode lines 2,189 to 4,417). 22 functions lifted:
  - ReserveSaleJob (5): Initialize 0xb6d0, ReplySuccess 0xb9c0, ReplyFailure 0xbae0, verifyParameter 0xbc10, handleJob 0xbe20.
  - CancelSaleReservationJob (4): Initialize 0xc160, ReplySuccess 0xc2c0, verifyParameter 0xc3d0, handleJob 0xc450.
  - RegisterSaleJob (4): Initialize 0xc8a0, ReplySuccess 0xcc50, verifyParameter 0xcd60, handleJob 0xd170.
  - UpdateSalePriceJob (5): Initialize 0xd700, ReplySuccess 0xd870, ReplyFailure 0xd980, verifyParameter 0xdaa0, handleJob 0xdb30.
  - AbandonSaleJob (4): Initialize 0xe1d0, ReplySuccess 0xe330, verifyParameter 0xe440, handleJob 0xe4c0.
- AutoCS::AutoCS (inlined, Lock.h line 113 assert) is now in JobContext.cpp. Same code as PostOfficeDaemon CachedWatchdog.cpp.
- JobContext.h: member functions of the 5 sale jobs (Initialize, Reply*, verifyParameter, handleJob).
- MarketDealerDefine.h: fail reasons 22..31, packet commands 0xD..0x1B, enum EconomySaleType (PDB values).
- No new .cpp file. CMake not changed.

## Not done
- AutoCS::Enter 0x8780: Lock.h is not in the files of this card. AbandonSaleJob::handleJob uses the inline AutoCS ctor in its place.
- The job destructors (AgentPacketHandler.obj, later card).

## BUG marks
- 0xbe20 ReserveSaleJob::handleJob: no null check after the SaleContext alloc.
- 0xe4c0 AbandonSaleJob::handleJob: no null check after the DeliveryContext alloc (the lock and AddContext use it).

## ❓
- ReplySuccess of the 5 jobs returns void in the exe (no return value). The PDB signature is not checked.
- CancelSaleReservationJob, RegisterSaleJob and AbandonSaleJob have no ReplyFailure in index.tsv (maybe COMDAT folded). Not declared.
- ECONOMY_MARKET_DELIVERYREASON_SALE_ABANDONMENT is a local constant (the enum is not in src/).

## Blocked
- None.

## Gate result
- `.scratch/gate_errors.sh`: no build errors, `gate ok`. CacheGate, SCD, LobbyGate, POD still link.
