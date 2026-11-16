# lift-smartcoupondaemon-6 handoff

## Done
- `src/common/Network.cpp`: Network::OpenPort 0x1A8B0 is lifted.
- Tag 0xfa lifetime: fixed (RefCntObject fault).
- `src/common/TimerQueue.h`: added the inline Timer ctor (SlotIndex -1). This fixes the assert at Timer.cpp:155 (ObjPoolTimer, TimerQueue::Add 0x26270).
- `src/SmartCouponDaemon/DaemonPacketHandler.cpp`: 6 functions. GameEventLogEvent::EventId 0x7D80, HandleSmartCoupon_HelloReq 0x7DC0, HandleSmartCoupon_GameEventByCharacterReq 0x8360, HandleSmartCoupon_GameEventByAccountReq 0x8E80 (plus DChannel::GetId 0x7D30 and ~DChannel 0x7D50 from before).
- EventId 0x7D80 moved from GameEventWorker.cpp to its PDB module DaemonPacketHandler.cpp.
- Handler list 0x83660: slots 1, 4 and 7 now point to the three handlers. The declarations are in `DaemonChannel.h`.
- BUG marks: 0x81BD gives the old daemon to ReplaceDaemon (the new DChannel leaks). The GameEventLogEvent leaks on the failure paths and when the event handle is null. 0x8E80 registers with wid 0 and pcdbid 0. The handle-null log at 0x8360 and 0x8E80 has its args shifted.

## Smoke test (SCD_CERT=sql, lifted, 15 s)
- Listen ports: 22000 32000 (exit=0, 68 log lines).
- Last log line: `Daemon.cpp,537,(error),[smartcoupond], onStart fail` after `SmartCouponDaemon.cpp,407 start np fail`.
- Cause: no NP server answers at 10.10.110.55:6601 in the test setup. This is not a lift fault. Compare with the original exe in the same setup (verify-3).

## Not done
- No functions are missing in the scope of this card.

## ❓
- 0x1A8B0: the Alloc line number and the Port::Initialize args are guesses.
- 0x7DC0: the line number of the DChannel Alloc (92) is a guess.
- 0x7DC0: daemonType is read with the "Q" format into an int. The PDB type SmartCouponDaemonType is not used.
- 0x7DC0: the old session is released with the Channel.h path at line 52.
- SMARTCOUPON_PACKET_VERSION (1) is not a PDB name.

## Blocked
- Nothing.

## Gate result
- `gate ok`.
