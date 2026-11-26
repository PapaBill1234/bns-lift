# Handoff: lift-parity-pod-5a (POD relay, CacheGate channel, DB)

Branch: `slice/lift-parity-pod-5a`. Not merged. Not pushed.

## MATCH per exe

| Exe | Before | After | Change |
| --- | --- | --- | --- |
| CacheGate | 456/491 | 456/491 | 0 |
| LobbyGate | 658/739 | 658/739 | 0 |
| SmartCouponDaemon | 630/669 | 630/669 | 0 |
| PostOfficeDaemon | 694/759 | 705/759 | +11 |
| LobbyDaemon | 1024 | 1024 | 0 |

No MATCH is lost. `tools/gate.sh` and `tools/parity.sh` pass.

## New MATCH (PostOfficeDaemon)

| Function | File |
| --- | --- |
| HandleCacheGateRelayFail | CacheGatePacketHandler.cpp |
| HandleCacheGateRelayInvalid | CacheGatePacketHandler.cpp |
| HandleCacheGateRelay | CacheGatePacketHandler.cpp |
| HandleCacheGateFragmentRelay | CacheGatePacketHandler.cpp |
| CacheGateChannel::SendRelayRequest | CacheGateChannel.cpp |
| CacheGateChannel::combineFragmentRelayFormat | CacheGateChannel.cpp, DeliverPostRelay.cpp |
| RelayTimeoutChecker::checkRelayTimeout | RelayTimeoutChecker.cpp |
| DeliverPostRelayContext::processRelayResponse | DeliverPostRelay.cpp |
| PostDeliveryEvent::deliverPost | PostDeliveryEvent.cpp, DeliverPostRelay.h |
| PostOfficeDB::LoadSinglePost | PostOfficeDB.cpp |
| PostOfficeDB::LoadRetryReadySinglePost | PostOfficeDB.cpp |

## Lessons (pod-5a)

### Worked

| Function | Before | After | Count | Fix |
| --- | --- | --- | --- | --- |
| HandleCacheGateRelay* (4) | DIFF | MATCH | 4 | Put the failure branch first. Use the original test order. |
| checkRelayTimeout | DIFF | MATCH | 1 | Read `manager->_containerList[index]` again at each `end()` test. Invert the `occurTimeoutEvent` test. |
| DeliverPostRelayContext::processRelayResponse | DIFF | MATCH | 1 | Put `AutoCS` in a block scope. Do not call `Leave()`. |
| PostDeliveryEvent::deliverPost | DIFF | MATCH | 1 | Use a stack request object and pass it to the ctor. This adds an EH state and stops tail merging. |
| LoadSinglePost | 88.4 | 100 | 1 | Use a `__forceinline` copy of the `DbTransaction::BindCol` body, so that the compiler merges the 17 error tails. Remove `ClearRow` before the single `Fetch`. |
| LoadRetryReadySinglePost | 88.8 | 100 | 1 | Same as LoadSinglePost. Put the failed register block first. Read `_instance` for AddContext, then once more for register and remove. |
| ComposeResponsePacket (2) | 90.5 | 94.4 | 0 | Use a switch and `0 < packet.Compose(...)`. Gain, but not MATCH. |

### Failed

| Function | Before | After | Count | Try |
| --- | --- | --- | --- | --- |
| SendFragmentRelayRequest | 88.5 | lower | 1 | `#pragma inline_depth`. Reverted. |
| ComposeResponsePacket (2) | 94.4 | 94.4 | 3 | Switch form, compare form, case order. No gain. |
| PingRelayContext::processRelayResponse | 97.6 | 97.6 | 2 | Failure first, block scope. No gain. |

## Unfixed DIFF functions

- CheckPostCapacityRelayContext::ComposeResponsePacket: consts 0x4 vs 0x2. Cause: the switch range lowering is different. Stopped after 3 tries with no gain.
- RetrieveCharacterInfoRelayContext::ComposeResponsePacket: consts 0x4 vs 0x2. Cause: the same as CheckPostCapacity. Stopped after 3 tries with no gain.
- PingRelayContext::processRelayResponse (97.6): call order. Cause: our build merges the AlertSender tails of crash lines 64 and 86. The original does not. Stopped: 2 tries with no gain, and no source form found.
- CacheGateChannel::SendFragmentRelayRequest (88.5): calls. Cause: our build inlines `Packet::Allocate(PacketComposer*)`. Stopped: the fix needs a change outside the Files list.
- PostOfficeDB::RegisterPost (84.0): consts and refs. Cause: the original unrolls the binds with constant indices 2..0x11, and the SQL string length is different. Stopped: a large rewrite. Not in the time budget.
- PostOfficeDB::LoadPostList and LoadRetryReadyPostList (99.1): calls. Cause: our build has an extra memset/memset/Fetch. Stopped: on the stop list; a loop form change is the next idea.

Turns: 160
