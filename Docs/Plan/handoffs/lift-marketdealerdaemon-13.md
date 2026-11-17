# lift-marketdealerdaemon-13: handoff

## Done
- TimeoutEvent.cpp (TimeoutEvent.obj): 8 functions. EventId 0x2f9a0, 0x2f9b0; dtors 0x2f9c0, 0x30140; HandleEvent 0x2fa20, 0x301a0; processTimeout 0x2fac0, 0x30240. TimeoutEvent.h: processTimeout declared.
- ManagerPacketHandler.cpp + .h (ManagerPacketHandler.obj): 5 handlers, 0x1a940 to 0x1b040.
- MarketManagerServerSideHandlerList.cpp: MarketManagerCommandList (0xb5260), MarketManagerPacketServerSideHandlerList (0xb52e0), MarketManagerPacketServerSideFragmentHandlerList (0xb6df0, .bss, all null). Data from IDA.
- New `src/Server/Packet/MarketManagerPacketCommand.h`: enum MarketManagerPacketCommand moved from MarketDealerDefine.h (MarketDealerDefine.h includes it).
- ManagerChannel.h: inline ctor ManagerChannel(managerWid) (LIFT, inlined in 0x1a940), extern MarketManagerCommandList.
- ManagementJobContext.h/.cpp: inline default ctors of the 4 jobs (LIFT, inlined in the handlers); RetryAllDeliveryFailureManagementJob::ReplyFailure (LIFT, inlined in 0x1ae50, log lines 300/305).
- CMake: 3 new .cpp files in lift_marketdealerdaemon.

## Not done
- None of the card. ManagerChannel dtor and GetId stay declarations (later card).

## BUG marks
- 0x2fac0 InstantSaleTimeoutEvent::processTimeout: no null check after the DeliveryContext alloc.
- 0x30240 AuctionTimeoutEvent::processTimeout: a list entry stays null when a check fails or the alloc fails; the second loop locks and uses it.
- 0x1a940 HandleMarketManagerHelloReq: no null check after the ManagerChannel alloc.

## ❓
- 0x1ac40 HandleMarketManagerSuspendSaleReq: the exe calls only Initialize and ReplyFailure (no verifyParameter, handleJob, ReplySuccess). Kept as in the exe.
- Array delete in processTimeout: the original also writes the pointer to TLS block + 0x10 before Free (same as JobContext.cpp).
- DeliveryInfo locals call the DeliveryInfo ctor (0x7100); the exe pseudocode shows no call (same as JobContext.cpp).
- Packet versions 4 and 10 in the hello handler: literals, no PDB symbol.

## Blocked
- None.

## Gate result
- `.scratch/gate_errors.sh`: no build errors, `gate ok`. CacheGate, SCD, LobbyGate, POD still link.
