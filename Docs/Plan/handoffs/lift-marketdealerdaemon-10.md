# lift-marketdealerdaemon-10: handoff

## Done
- JobContext.cpp part 3 (JobContext.obj, pseudocode lines 4,418 to 6,682). 20 functions lifted:
  - ReserveBidJob (5): Initialize 0xecb0, ReplySuccess 0xef60, ReplyFailure 0xf080, verifyParameter 0xf1b0, handleJob 0xf3b0.
  - CancelBidReservationJob (5): Initialize 0xfae0, ReplySuccess 0xfc50, ReplyFailure 0xfd60, verifyParameter 0xfe80, handleJob 0xff10.
  - RegisterBidJob (5): Initialize 0x10540, ReplySuccess 0x106e0, ReplyFailure 0x10800, verifyParameter 0x10930, handleJob 0x109d0.
  - UpdateBidPriceJob (5): Initialize 0x11360, ReplySuccess 0x11510, ReplyFailure 0x11630, verifyParameter 0x11770, handleJob 0x11820.
- JobContext.h: member functions of the 4 bid jobs. The parameter name of verifyParameter/handleJob is now `failReason` (same as the sale jobs).
- MarketDealerDefine.h: fail reasons 32..69 and packet commands 0x1C..0x2A (PDB values from types.h).
- JobContext.cpp includes BidContext.h. No new .cpp file. CMake not changed.

## Not done
- The job destructors (AgentPacketHandler.obj, later card).
- AutoCS::Enter 0x8780 (Lock.h is not in the files of this card; see card 8).

## BUG marks
- 0x109d0 RegisterBidJob::handleJob: the two "insufficient bid price" paths set fail reason 39
  (RESERVEBIDFAIL_INSUFFICIENT_BID_PRICE), not 51 (REGISTERBIDFAIL_INSUFFICIENT_BID_PRICE).

## ❓
- ReplySuccess and ReplyFailure return void in the exe. The PDB signature is not checked (same as card 9).
- The handleJob functions use the inline AutoCS ctor and an explicit Leave(), as in card 9. The original
  has the lock/leave code inline (Lock.h lines 113 and 122).

## Blocked
- None.

## Gate result
- `.scratch/gate_errors.sh`: no build errors, `gate ok`. CacheGate, SCD, LobbyGate, POD still link.
