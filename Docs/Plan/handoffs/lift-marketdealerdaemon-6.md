# lift-marketdealerdaemon-6: handoff

## Done
- MarketDB.cpp: 11 functions added. ExpireSale 0x24100, ExpireAuction 0x24490, UpdateStatusToReporting 0x24e90,
  UpdateStatusToReportSuccess 0x25110, UpdateStatusToPawnRemovalSuccess 0x25320, UpdateStatusToPawnRemovalFailure 0x25530,
  UpdateStatusToPostRegistrationSuccess 0x25740, UpdateStatusToPostRegistrationFailure 0x259b0,
  UpdateStatusToRetryReady 0x25bc0, LoadRetryReadySingleDelivery 0x25dd0, ResetUncompletedDeliveryStatus 0x27230.
- DeliveryTimer.cpp/.h: HandleEvent 0x82e0, checkDelivery 0x8420. TimeoutTimer.cpp/.h: HandleEvent 0x319d0,
  checkSaleExpiration 0x31b10, postTimeoutEvent 0x31e20. TimerClass/TimerId are inline in the headers
  (ICF folds: TimeoutTimer 0x63c60 = 1, DeliveryTimer 0x29220 = 2, TimerId 0x6ee0 = 0).
- New headers: DeliveryRelation.h (layout), TimeoutEvent.h (InstantSaleTimeoutEvent, AuctionTimeoutEvent: layout,
  inlined ctors, virtuals declared only). JobContext.h: 6 UpdateStatusTo*Job classes (layout only).
- MarketDB.h: parameter names of ExpireSale, ExpireAuction, ResetUncompletedDeliveryStatus from the PDB locals.
- CMake: DeliveryTimer.cpp and TimeoutTimer.cpp added to lift_marketdealerdaemon.
- Total: 16 functions.

## Not done
- MarketDB card 7 functions (0x27440..0x28f50).
- TimeoutEvent.obj virtuals (EventId, HandleEvent, dtors), the 6 new job virtuals, timer dtors (later cards).

## BUG marks
- 0x25dd0 LoadRetryReadySingleDelivery: no null check after the DeliveryContext Alloc.
- 0x31e20 postTimeoutEvent: removeReferenceCount on a null event when Alloc fails.

## ❓
- postTimeoutEvent Alloc line numbers (93, 104) are guesses. The call site has the line folded.
- ~TimeoutTimer and ~DeliveryTimer bodies are not in index.tsv (taken as empty inline).

## Blocked
- None.

## Gate result
- `.scratch/gate_errors.sh`: no build errors, `gate ok`. CacheGate, SCD, LobbyGate, POD still link.
