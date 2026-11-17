# lift-marketdealerdaemon-12: handoff

## Done
- JobContext.cpp part 5 (JobContext.obj, pseudocode lines 8,934 to 11,032). 38 real functions lifted (the 2 scalar deleting destructors are compiler code):
  - UpdateStatusTo{ReportSuccess, PawnRemovalFailure, PawnRemovalSuccess, PostRegistrationFailure, PostRegistrationSuccess, RetryReady}Job: Initialize, ReplySuccess, verifyParameter, handleJob (24, 0x15aa0 to 0x17260).
  - RetrieveReservationListJob (8): ~dtor 0x17360, Initialize 0x17410, ReplySuccess 0x17570, ReplyFailure 0x178a0, verifyParameter 0x179d0, handleJob 0x17a50, addMyReservationInfo 0x17b00, composeResponsePacket 0x17c70.
  - CancelReservationListJob (6): ~dtor 0x17f30, Initialize 0x17fa0, ReplySuccess 0x18400, ReplyFailure 0x18520, verifyParameter 0x18650, handleJob 0x18780.
- JobContext.h: member functions of these jobs; new class CancelReservationListJob (PDB layout, size 0x30, static_asserts); RetrieveReservationListJob ctor declaration.
- MarketDealerDefine.h: fail reasons 90..99 + MARKETDEALER_GLOBAL_MAX, packet commands 0x34..0x4B (PDB values).
- No new .cpp file. CMake not changed.

## Not done
- RetrieveReservationListJob() and CancelReservationListJob() ctors: inlined in AgentPacketHandler.obj (0x6bb0, 0x6d80), later card. Declared only.
- The job destructors in AgentPacketHandler.obj (later card), and AutoCS::Enter 0x8780 (see card 8).

## BUG marks
- 0x17b00 addMyReservationInfo: no null check after the node alloc; the crash log reads _header fields when _header is null.
- 0x17c70 composeResponsePacket: the crash log reads _header fields when _header is null.
- 0x17fa0 CancelReservationListJob::Initialize: no null check after the array alloc.

## ❓
- Service type values 1, 2, 3 (sale, bid, purchase) in CancelReservationListJob: the PDB enum name is not checked.
- UpdateStatusToReportSuccessJob::handleJob uses the inline AutoCS ctor (same as cards 9 to 11).
- CancelReservationListJob::handleJob: sale case sets CancelSaleReservationJob::_saleId = serviceId (as in the exe).

## Blocked
- None.

## Gate result
- `.scratch/gate_errors.sh`: no build errors, `gate ok`. CacheGate, SCD, LobbyGate, POD still link.
