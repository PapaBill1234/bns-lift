# lift-postofficedaemon-2 handoff

## Done
- Modules (src/PostOfficeDaemon/, .h + .cpp each): RelayContext, RelayTimeContext, RelayTimeoutChecker, RelayTimeoutEvent, PingRelay, PingGenerator, CachedWatchdog.
- Support headers: PostOfficeDaemon.h, WorldConfig.h (layout only). Friends added in src/common/Lock.h and src/common/TimerQueue.h.
- PingRelay: 0xaad0, 0xabd0, 0xaed0, 0xaf30, 0xaf70 (5).
- PingGenerator: 0x4cf0, 0xfb40, 0x34c40, 0x4d70, 0x4ed0, and 2 ICF-folded Compose functions (7).
- CachedWatchdog: 0x3d20, 0x3dc0, 0x3e80, 0x3f00, 0x4310, 0x46b0, 0x48b0, 0x49d0, 0x4a50, 0x4b60, 0x54a70, 0x5d860, and GetCurrentPingSeq (inlined) (13).
- CMake: static library `lift_postofficedaemon` (links `lift_common`) has all 7 .cpp files.

## Not done
- CachedWatchdogManager ctor/dtor: declared only. They go to the later PostOfficeDaemon card.
- CacheGateChannel::SendRelayRequest, PostOfficeDaemon::checkCacheGateServiceState: declarations only (later cards).

## ❓
- `ServiceState` enum name and values (0 = unavailable, 1 = available), from the CAS at 0x3e80.
- `CachedWatchdogManager::GetCurrentPingSeq`: name from the log text. It is inlined in 0xabd0.
- `PingRelayRequest::_pingSeq`, `isStopState` helper, inline virtual dtors of RelayRequest and PingGenerator.
- PingGenerator.cpp Alloc line number (59) in sendPing.
- SetAllServiceState 0x4a50: the binary uses UNAVAILABLE as a constant. The lift passes `newState`.
- ICF-folded ComposeRequestPacket(FragmentPacket&) / ComposeResponsePacket(FragmentPacket&): return value `true` is a guess.

## BUG
- 0x1db40 (RelayTimeoutChecker): see the comment in the source.
- 0x4ed0 sendPing and 0x46b0 addCachedWatchdog: Alloc result is not checked for null.

## Blocked
- None.

## Gate result
- `tools/gate.sh`: `gate ok` (warnings only: -Winvalid-offsetof in static_asserts).
