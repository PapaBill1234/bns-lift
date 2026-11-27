# lift-gamedaemon-e37: Easy leaves (GameDaemon): instantpaymenttran_cpp, marketdealeragentchannel, guildjointicket_cpp, lobbydaemonchannel_cpp, ...

| Item | Value |
| --- | --- |
| Exe | GD |
| Source build | GameDaemon 2019 + PDB (VS2010 SP1) |
| Exe file | `<work-root>/ida/lift/GameDaemon/GameDaemon.exe` |
| PDB | `<work-root>/ida/lift/GameDaemon/GameDaemon.pdb` |
| Pseudocode | `~/.cache/bns-lift/hr/GameDaemon/<stem>.c` |
| Pseudocode index | `~/.cache/bns-lift/hr/GameDaemon/index.tsv` (stem, rva, name, first, last, status, source file, part) |
| Wave | E |
| Model | opus |
| Depends on | `lift-gamedaemon-0e` |
| Pattern | `src/Server/LobbyDaemon/AccountInventoryChannel.cpp` |
| Plan | `Docs/Plan/gamedaemon-lift.md` sections 1, 3, 5 |

## Read first

- Read "Lift method" in `Docs/Plan/plan.md`.
- Grep `Docs/Parity/lessons.md` for A2 (block order), A6 (per-exe path literals), A12 (PDB member types), A18 (destructors), A21 (PDB facts) and A22 (per-exe source form). Do not read it in full.
- Pattern: `src/Server/LobbyDaemon/AccountInventoryChannel.cpp`. Read it one time. Use its form for the functions of this card.

## Scope

40 functions, about 802 pseudocode lines (about 6,416 tokens). Stems: `instantpaymenttran_cpp`, `marketdealeragentchannel`, `guildjointicket_cpp`, `lobbydaemonchannel_cpp`, `postofficeagentchannel`, `accountinventorychannel_cpp`, `arenagamechannel_cpp`, `duelbotdaemonchannel`.

Wave E (owner order 2026-11-27: the easiest work first). Each function in this card is a leaf: its body calls no other counted function that needs a lift. Thus a `LIFT_STUB` callee cannot keep it DIFF. Each function has at most 30 pseudocode lines. Ease key: 20.1 cost per function (rule in `Docs/Plan/gamedaemon-lift.md` section 3).

Lift only the functions in the table. The other functions of these stems are in later W cards. Those cards depend on this card.

| n | Exe | RVA | PDB name | Stem | Lines | Form |
| ---: | --- | --- | --- | --- | ---: | --- |
| 1 | GD | `0x133900` | `InstantPaymentJob::tryAbortImpl` | instantpaymenttran_cpp | 8 | leaf |
| 2 | GD | `0x1351e0` | `InstantPaymentTransformItemSubJob::setExtraParam` | instantpaymenttran_cpp | 30 | leaf |
| 3 | GD | `0x135260` | `InstantPaymentTransformItemSubJob::sendFailPacket` | instantpaymenttran_cpp | 13 | leaf |
| 4 | GD | `0x135e20` | `InstantPaymentBuyCollectionItemsSubJob::setExtraParam` | instantpaymenttran_cpp | 29 | leaf |
| 5 | GD | `0x135f00` | `InstantPaymentBuyCollectionItemsSubJob::DataId` | instantpaymenttran_cpp | 9 | getter |
| 6 | GD | `0x15af30` | `MarketDealerAgentSessionHandler::OnAccept` | marketdealeragentchannel | 18 | leaf |
| 7 | GD | `0x15b380` | `MarketDealerAgentSessionHandler::PacketHandler` | marketdealeragentchannel | 26 | leaf |
| 8 | GD | `0x15b8f0` | `HandleMarketServiceCancelPurchaseReservationFail` | marketdealeragentchannel | 23 | leaf |
| 9 | GD | `0x15b960` | `HandleMarketServiceCancelPurchaseReservationOk` | marketdealeragentchannel | 18 | leaf |
| 10 | GD | `0x15c3d0` | `HandleMarketServiceCancelBidReservationFail` | marketdealeragentchannel | 23 | leaf |
| 11 | GD | `0x15c440` | `HandleMarketServiceCancelBidReservationOk` | marketdealeragentchannel | 18 | leaf |
| 12 | GD | `0x15d010` | `HandleMarketServiceCancelSaleReservationFail` | marketdealeragentchannel | 23 | leaf |
| 13 | GD | `0x15d090` | `HandleMarketServiceCancelSaleReservationOk` | marketdealeragentchannel | 18 | leaf |
| 14 | GD | `0x15eb10` | `HandleMarketServiceHelloFail` | marketdealeragentchannel | 12 | leaf |
| 15 | GD | `0x15eb40` | `HandleMarketServiceHelloOk` | marketdealeragentchannel | 12 | leaf |
| 16 | GD | `0x115dc0` | `GuildJoinTicket::GuildJoinTicket` | guildjointicket_cpp | 18 | leaf |
| 17 | GD | `0x118370` | `GuildJoinTicketListPerGuild::GuildJoinTicketListPerGuild` | guildjointicket_cpp | 22 | leaf |
| 18 | GD | `0x13e280` | `LobbyDaemonSessionHandler::OnAccept` | lobbydaemonchannel_cpp | 16 | leaf |
| 19 | GD | `0x13e6d0` | `LobbyDaemonSessionHandler::PacketHandler` | lobbydaemonchannel_cpp | 26 | leaf |
| 20 | GD | `0x140250` | `HandleLobbyGame_CloseSessionNotify` | lobbydaemonchannel_cpp | 17 | leaf |
| 21 | GD | `0x14b060` | `HandleLobbyGame_UpdateAccountExpFail` | lobbydaemonchannel_cpp | 23 | leaf |
| 22 | GD | `0x14b0e0` | `HandleLobbyGame_UpdateAccountContentQuotaOk` | lobbydaemonchannel_cpp | 12 | leaf |
| 23 | GD | `0x14b120` | `HandleLobbyGame_UpdateAccountContentQuotaFail` | lobbydaemonchannel_cpp | 23 | leaf |
| 24 | GD | `0x14b1a0` | `HandleLobbyGame_UpdateAccountRecycleTimeFail` | lobbydaemonchannel_cpp | 23 | leaf |
| 25 | GD | `0x1961b0` | `PostOfficeAgentSessionHandler::OnAccept` | postofficeagentchannel | 16 | leaf |
| 26 | GD | `0x196600` | `PostOfficeAgentSessionHandler::PacketHandler` | postofficeagentchannel | 26 | leaf |
| 27 | GD | `0x29390` | `AccountInventorySessionHandler::OnAccept` | accountinventorychannel_cpp | 16 | leaf |
| 28 | GD | `0x297e0` | `AccountInventorySessionHandler::PacketHandler` | accountinventorychannel_cpp | 26 | leaf |
| 29 | GD | `0x2da60` | `HandleAccountInventoryGame_RefundInstantPaymentOk` | accountinventorychannel_cpp | 21 | leaf |
| 30 | GD | `0x2dae0` | `HandleAccountInventoryGame_RefundInstantPaymentFail` | accountinventorychannel_cpp | 21 | leaf |
| 31 | GD | `0x2db50` | `HandleAccountInventoryGame_BoardGachaRetrieveSeasonScheduleFail` | accountinventorychannel_cpp | 19 | leaf |
| 32 | GD | `0x30a40` | `HandleAccountInventoryGame_BoardGachaFinishDrawByItemRecoveryFail` | accountinventorychannel_cpp | 25 | leaf |
| 33 | GD | `0x30ac0` | `HandleAccountInventoryGame_BoardGachaCancelDrawByItemOk` | accountinventorychannel_cpp | 19 | leaf |
| 34 | GD | `0x30b30` | `HandleAccountInventoryGame_BoardGachaCancelDrawByItemFail` | accountinventorychannel_cpp | 22 | leaf |
| 35 | GD | `0x36480` | `ArenaGameSessionHandler::OnAccept` | arenagamechannel_cpp | 16 | leaf |
| 36 | GD | `0x37030` | `HandleArenaGameArenaHelloFail` | arenagamechannel_cpp | 20 | leaf |
| 37 | GD | `0x3d2c0` | `ArenaSideArenaLobbyChannel::SendPing` | arenagamechannel_cpp | 29 | leaf |
| 38 | GD | `0x3d850` | `HandleArenaLobbyArenaHelloFail` | arenagamechannel_cpp | 22 | leaf |
| 39 | GD | `0x3da90` | `HandleArenaLobbyArenaRelayFailNotify` | arenagamechannel_cpp | 22 | leaf |
| 40 | GD | `0xa7f70` | `HandleDuelBotGameGameHelloFail` | duelbotdaemonchannel | 22 | leaf |

Same name in a lifted exe (a different body is possible): `AccountInventorySessionHandler::OnAccept` (src/Server/LobbyDaemon/AccountInventoryChannel.cpp), `AccountInventorySessionHandler::PacketHandler` (src/Server/LobbyDaemon/AccountInventoryChannel.cpp).

## Tasks

1. Use the listed exe and PDB only. Do not use a 381 file for logic. Do not open IDA. Use the pseudocode cache and `tools/pdbq.py`.
2. Select the functions of this card in `index.tsv` (stem and RVA). Read only their line ranges (`first` to `last`) in `<stem>.c`.
3. Replace the `LIFT_STUB` bodies in `src/Server/GameDaemon/<stem>.cpp` (skeleton `lift-gamedaemon-0c`). Put declarations in `src/Server/GameDaemon/<stem>.h`. Use the PDB types in `include/pdb/GameDaemon/types.h` and PDB names. Restore STL calls in place of inlined STL code.
4. Keep the original logic and the server checks. Mark a bug with `// BUG:`. Mark an open question with `// ❓`. Mark a name with no PDB name with `// LIFT:` and the RVA.
5. Run `tools/gate.sh`. Compare `tools/funcdiff.py` results for GameDaemon and the 5 other exes with the pre-card baseline. Use the same build settings for both runs.

## Files

- `src/Server/GameDaemon/instantpaymenttran_cpp.cpp`
- `src/Server/GameDaemon/instantpaymenttran_cpp.h`
- `src/Server/GameDaemon/marketdealeragentchannel.cpp`
- `src/Server/GameDaemon/marketdealeragentchannel.h`
- `src/Server/GameDaemon/guildjointicket_cpp.cpp`
- `src/Server/GameDaemon/guildjointicket_cpp.h`
- `src/Server/GameDaemon/lobbydaemonchannel_cpp.cpp`
- `src/Server/GameDaemon/lobbydaemonchannel_cpp.h`
- `src/Server/GameDaemon/postofficeagentchannel.cpp`
- `src/Server/GameDaemon/postofficeagentchannel.h`
- `src/Server/GameDaemon/accountinventorychannel_cpp.cpp`
- `src/Server/GameDaemon/accountinventorychannel_cpp.h`
- `src/Server/GameDaemon/arenagamechannel_cpp.cpp`
- `src/Server/GameDaemon/arenagamechannel_cpp.h`
- `src/Server/GameDaemon/duelbotdaemonchannel.cpp`
- `src/Server/GameDaemon/duelbotdaemonchannel.h`

## Handoff

Write `Docs/Plan/handoffs/lift-gamedaemon-e37.md`. List the functions that you lifted. List each remaining function under "Not done" with its RVA and the reason. Record the gate result and the MATCH comparison.

## Done when

- `tools/gate.sh` prints `gate ok`.
- Each function in this card is lifted or is listed as "Not done" with its RVA.
- CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon and LobbyDaemon lose no MATCH functions.
- The GameDaemon MATCH count does not decrease.
