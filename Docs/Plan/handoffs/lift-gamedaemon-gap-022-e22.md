# lift-gamedaemon-gap-022-e22 handoff (round 1)

## Lifted

- `BoardGachaRetrieveSeasonInfoWSO::SendFail` (0xd9e0)
- `BoardGachaSessionCloseWSO::SendFail` (0xde40)
- `BoardGachaBoardInfoReqWSO::SendFail` (0xdff0)
- `BoardGachaRetrieveParticipationInfoAllWSO::SendFail` (0xe200)

Each body sends `Send("hE", opcode, 2)`. The `failReason` argument is unused in the original. A keep pragma is in `boardgacha.cpp`.

## Not done

- `BoardGacha::SendSeasonInfoPacket` (0xbb50): the Log::Write call uses 3 string literals in the data section (format, function name, module name). The pseudocode shows only data offsets. One look-up does not give the text.
- `BoardGacha::SendBoardInfo` (0xc3b0): same reason.

## Files changed

- `src/Server/GameDaemon/boardgacha.cpp`
- `Docs/Plan/handoffs/lift-gamedaemon-gap-022-e22.md`
