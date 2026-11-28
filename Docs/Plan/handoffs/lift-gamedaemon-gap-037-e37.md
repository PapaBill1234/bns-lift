# Handoff: lift-gamedaemon-gap-037-e37 (card lift-gamedaemon-e37)

Round 2 (repair) is complete. The driver runs the gate and the proof.

## Stem status

- `duelbotdaemonchannel`: complete. Round 2 lifted `HandleDuelBotGameGameHelloFail` (0xa7f70).
- `guildjointicket_cpp`: complete. Round 1 lifted both bodies (0x115dc0, 0x118370). Round 2 has no change for this stem.
- `postofficeagentchannel`: Round 2 lifted `OnAccept` (0x1961b0). `PacketHandler` (0x196600) is **Not done**.
- `instantpaymenttran_cpp`: complete. Round 1 lifted `tryAbortImpl` (0x133900) and `DataId` (0x135f00). Round 2 lifted both `setExtraParam` bodies (0x1351e0, 0x135e20). `sendFailPacket` (0x135260) is **Not done**.
- `arenagamechannel_cpp`: Round 2 lifted `ArenaGameSessionHandler::OnAccept` (0x36480), `HandleArenaGameArenaHelloFail` (0x37030) and `HandleArenaLobbyArenaHelloFail` (0x3d850). Two bodies are **Not done**.
- `lobbydaemonchannel_cpp`: Round 2 lifted 6 bodies (0x13e280, 0x140250, 0x14b060, 0x14b0e0, 0x14b120, 0x14b1a0). `PacketHandler` (0x13e6d0) is **Not done**.
- `accountinventorychannel_cpp`: Round 2 lifted 7 bodies (0x29390, 0x2da60, 0x2dae0, 0x2db50, 0x30a40, 0x30ac0, 0x30b30). `PacketHandler` (0x297e0) is **Not done**.
- `marketdealeragentchannel`: Round 2 lifted 9 bodies. `PacketHandler` (0x15b380) is **Not done**.

Each lifted body with no live caller has a `/INCLUDE` keep pragma with a `// LIFT:` note.
`HandleAccountInventoryGame_BoardGachaFinishDrawByItemRecoveryFail` (0x30a40) has a `// BUG:` note. The format "hqE" has no field for `pcdbid`, so the log shows wrong values. This bug causes no memory error, so the lift keeps the original form.

## Not done

| RVA | Function | Reason |
| --- | --- | --- |
| 0x135260 | `InstantPaymentTransformItemSubJob::sendFailPacket` | `User` has no `Channel` base, and the GameDaemon source has no `Channel` class with `Send`. |
| 0x15b380 | `MarketDealerAgentSessionHandler::PacketHandler` | The global `MarketServicePacketClientSideHandlerList` has no definition in the GameDaemon source. |
| 0x196600 | `PostOfficeAgentSessionHandler::PacketHandler` | The global `PostOfficeServicePacketClientSideHandlerList` has no definition in the GameDaemon source. |
| 0x13e6d0 | `LobbyDaemonSessionHandler::PacketHandler` | Same cause: the client-side handler list global has no definition in the GameDaemon source. |
| 0x297e0 | `AccountInventorySessionHandler::PacketHandler` | Same cause: the client-side handler list global has no definition in the GameDaemon source. |
| 0x3d2c0 | `ArenaSideArenaLobbyChannel::SendPing` | `ArenaSideArenaLobbyChannel` has no PDB layout in the header (no `_pingSent`, no `releaseSession`). |
| 0x3da90 | `HandleArenaLobbyArenaRelayFailNotify` | The pseudocode shows the format "hiQciQcssqhqE" (13 fields) with only two targets. A lift in this form can write through stack values. This needs a check of the disassembly. |

None of these bodies is a stub only for the log path (E16).

## Files changed

- `src/Server/GameDaemon/GameDaemonFwd.h`
- `src/Server/GameDaemon/gametran.h`
- `src/Server/GameDaemon/instantpaymenttran.h`
- `src/Server/GameDaemon/instantpaymenttran_cpp.cpp`
- `src/Server/GameDaemon/lobbydaemonchannel_cpp.cpp`
- `src/Server/GameDaemon/marketdealeragentchannel.cpp`
- `src/Server/GameDaemon/postofficeagentchannel.cpp`
- `src/Server/GameDaemon/duelbotdaemonchannel.cpp`
- `src/Server/GameDaemon/arenagamechannel_cpp.cpp`
- `src/Server/GameDaemon/accountinventorychannel_cpp.cpp`
- `Docs/Plan/handoffs/lift-gamedaemon-gap-037-e37.md`

## Gate and MATCH

This session did not run the gate or funcdiff (session rule). The driver records them.
