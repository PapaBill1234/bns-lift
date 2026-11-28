# Handoff: lift-gamedaemon-gap-037-e37 (card lift-gamedaemon-e37)

Round 2 (repair) is in progress. This file records the state after each stem.

## Stem status

- `instantpaymenttran_cpp`: round 2 lifted both `setExtraParam` bodies. `sendFailPacket` (0x135260) is **Not done**.
- `marketdealeragentchannel`: round 2 lifted 9 bodies. `PacketHandler` (0x15b380) is **Not done**.
- `guildjointicket_cpp`: complete. Round 1 lifted both bodies (0x115dc0, 0x118370). Round 2 has no change for this stem.
- The other stems: in progress.

## Not done (so far)

| RVA | Function | Reason |
| --- | --- | --- |
| 0x135260 | `InstantPaymentTransformItemSubJob::sendFailPacket` | `Channel::Send` on `User` is not lifted in the GameDaemon headers. |
| 0x15b380 | `MarketDealerAgentSessionHandler::PacketHandler` | The global `MarketServicePacketClientSideHandlerList` has no definition in the GameDaemon source. |
