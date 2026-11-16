# lift-lobbygate-3 handoff

## Done
- 4 modules in `src/LobbyGate/` (one .h and one .cpp each). All are in the static lib `lift_lobbygate`.
  - ThreadFreePacketPump, FragmentPacket, Client: all functions in index.tsv.
  - LobbyDChannel: 14 functions (0x9200 to 0xad20).
- Support headers: LobbyGate.h, LobbyGatePacketHandler.h, LobbyGatePredefine.h.
- Friend lines (❓) in `src/common/Session.h`, `src/common/PipeConsole.h` (LobbyD, LobbyDSessionHandler) and `src/common/Network.h` (LobbyDSessionHandler).

## Not done
- `LobbyD::~LobbyD`, `LobbyD::GetId`, `LobbyDSessionHandler::~LobbyDSessionHandler`: declared only. They are not in index.tsv for LobbyDChannel.
- Globals `bypassHandler[2]` and `bypassHandlerFF[2]`: extern only. The definition comes from a later card.

## ❓
- `LobbyD::Hello` 0x9bd0: argument names, and `MakeSession` arguments 3..5 (pseudocode shows 2; the code passes 0, 0, false).
- Inlined `PipeConsole::SetInvalidInfo`: the value argument is the global `valueString`. The code passes L"". addNode does not use it.
- `OnConnect` 0x9310: the file string of `Memory::Free` (0x1400857D8) is not known. The code passes L"" and line 837.
- `PacketHandler` 0x9660: the offset argument of `TFPP_PumpPacket` is 0.
- `SendLostAnonymousConnectionNotify` 0xab20: the parameter type is `long long` from the PDB. The pseudocode shows unsigned.
- `id128` GUID fields are read with a local struct `GuidFields`.

## BUG marks
- 0x9d80 `LobbyD::hello`: Send is called when the session is null.
- 0xa280 `SendStartSessionWithNPTokenReq`: the format "hqoo" does not use the ipAddress argument.

## Blocked
- None.

## Gate result
- `gate ok` (25/25, lift_lobbygate.lib links).
