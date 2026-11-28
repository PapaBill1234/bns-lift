# Handoff: lift-gamedaemon-gap-037-e37 (card lift-gamedaemon-e37)

## Lifted

- `0x133900` `InstantPaymentJob::tryAbortImpl`. It calls the virtual `postFailProc` and returns true.
- `0x135f00` `InstantPaymentBuyCollectionItemsSubJob::DataId`. It returns `_buyParam.buyItem[idx].chargeItem`.

- `0x115dc0` `GuildJoinTicket::GuildJoinTicket`. The member initializer list sets the fields to zero. The `CriticalSection` member constructor calls `InitializeCriticalSection`.
- `0x118370` `GuildJoinTicketListPerGuild::GuildJoinTicketListPerGuild`. Same form, then `memset` of `_ticketList`.
- `0x14b0e0` `HandleLobbyGame_UpdateAccountContentQuotaOk`. It decomposes `"hqq"` and returns true. Formtest verdict: SAME.

Each lifted body has a dead-strip keep pragma.

`guildjointicket.h` now has the PDB layouts of `GuildJoinTicket` (0x68) and `GuildJoinTicketListPerGuild` (0x200). Both derive from `DynamicRefCntObj`. The PDB virtual destructor of `GuildJoinTicketListPerGuild` has no declared body yet, so the implicit destructor stands in for it.

`instantpaymenttran.h` now has the PDB layout of `InstantPaymentJob` (vtable in PDB slot order, members to 0x158), of `InstantPaymentTryBuyCollectionItemsParam` and of its `BuyItem`. `InstantPaymentBuyCollectionItemsSubJob` now derives from `InstantPaymentJob` and has `_buyParam` at 0x158. `_goodsInfo` and `reserved` are opaque storage of the PDB size, because their types are not lifted yet.

## Not done

| RVA | Function | Reason |
| --- | --- | --- |
| 0x1351e0 | `InstantPaymentTransformItemSubJob::setExtraParam` | log path (E16) |
| 0x135260 | `InstantPaymentTransformItemSubJob::sendFailPacket` | `UserTran::_user` and `Channel::Send` (on `User`) are not lifted in the GameDaemon headers. The class has no base yet. |
| 0x135e20 | `InstantPaymentBuyCollectionItemsSubJob::setExtraParam` | log path (E16) |
| 0x15af30 | `MarketDealerAgentSessionHandler::OnAccept` | log path (E16) |
| 0x15b380 | `MarketDealerAgentSessionHandler::PacketHandler` | log path (E16) |
| 0x15b8f0 | `HandleMarketServiceCancelPurchaseReservationFail` | log path (E16) |
| 0x15b960 | `HandleMarketServiceCancelPurchaseReservationOk` | log path (E16) |
| 0x15c3d0 | `HandleMarketServiceCancelBidReservationFail` | log path (E16) |
| 0x15c440 | `HandleMarketServiceCancelBidReservationOk` | log path (E16) |
| 0x15d010 | `HandleMarketServiceCancelSaleReservationFail` | log path (E16) |
| 0x15d090 | `HandleMarketServiceCancelSaleReservationOk` | log path (E16) |
| 0x15eb10 | `HandleMarketServiceHelloFail` | log path (E16) |
| 0x15eb40 | `HandleMarketServiceHelloOk` | log path (E16) |
| 0x13e280 | `LobbyDaemonSessionHandler::OnAccept` | log path (E16) |
| 0x13e6d0 | `LobbyDaemonSessionHandler::PacketHandler` | log path (E16) |
| 0x140250 | `HandleLobbyGame_CloseSessionNotify` | log path (E16) |
| 0x14b060 | `HandleLobbyGame_UpdateAccountExpFail` | log path (E16) |
| 0x14b120 | `HandleLobbyGame_UpdateAccountContentQuotaFail` | log path (E16) |
| 0x14b1a0 | `HandleLobbyGame_UpdateAccountRecycleTimeFail` | log path (E16) |
| 0x1961b0 | `PostOfficeAgentSessionHandler::OnAccept` | log path (E16) |
| 0x196600 | `PostOfficeAgentSessionHandler::PacketHandler` | log path (E16) |
| 0x29390 | `AccountInventorySessionHandler::OnAccept` | log path (E16) |
| 0x297e0 | `AccountInventorySessionHandler::PacketHandler` | log path (E16) |
| 0x2da60 | `HandleAccountInventoryGame_RefundInstantPaymentOk` | log path (E16) |
| 0x2dae0 | `HandleAccountInventoryGame_RefundInstantPaymentFail` | log path (E16) |
| 0x2db50 | `HandleAccountInventoryGame_BoardGachaRetrieveSeasonScheduleFail` | log path (E16) |
| 0x30a40 | `HandleAccountInventoryGame_BoardGachaFinishDrawByItemRecoveryFail` | log path (E16) |
| 0x30ac0 | `HandleAccountInventoryGame_BoardGachaCancelDrawByItemOk` | log path (E16) |
| 0x30b30 | `HandleAccountInventoryGame_BoardGachaCancelDrawByItemFail` | log path (E16) |
| 0x36480 | `ArenaGameSessionHandler::OnAccept` | log path (E16) |
| 0x37030 | `HandleArenaGameArenaHelloFail` | log path (E16) |
| 0x3d2c0 | `ArenaSideArenaLobbyChannel::SendPing` | log path (E16) |
| 0x3d850 | `HandleArenaLobbyArenaHelloFail` | log path (E16) |
| 0x3da90 | `HandleArenaLobbyArenaRelayFailNotify` | log path (E16) |
| 0xa7f70 | `HandleDuelBotGameGameHelloFail` | log path (E16) |

## Changed files

- `src/Server/GameDaemon/instantpaymenttran.h`
- `src/Server/GameDaemon/instantpaymenttran_cpp.cpp`
- `src/Server/GameDaemon/guildjointicket.h`
- `src/Server/GameDaemon/guildjointicket_cpp.cpp`
- `src/Server/GameDaemon/lobbydaemonchannel_cpp.cpp`
- `Docs/Plan/handoffs/lift-gamedaemon-gap-037-e37.md`

The driver runs the gate and the MATCH comparison.
