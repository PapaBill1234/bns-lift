# lift-lobbydaemon-18: GamedChannel part 1, AccountInventoryChannel

Source: LobbyDaemon 2019 + PDB (VS2010 SP1). The lift uses the indexed pseudocode cache and the PDB types. IDA was not opened.
The index lists 55 functions in scope (the card says 54; `Network::iocpHandle` at `0x64e0` is the extra one). 50 are lifted. 5 are Not done.

`Network::iocpHandle` was already MATCH on main before this card. It adds no new MATCH.
Base: main 75f0769. All counts are measured against it.

## Result

| Item | Value |
| --- | --- |
| Lifted | 50 |
| Not done | 5 |
| Gate (`tools/gate.sh`, `LIFT_BUILD_DIR=build-ld-18`) | gate ok |
| Parity (`tools/parity.sh`) | parity ok |
| LobbyDaemon MATCH | 195 -> 254 (+59) over main 75f0769 |
| CacheGate, LobbyGate, SmartCouponDaemon, PostOfficeDaemon MATCH | 456, 658, 630, 694 (+0 each, no MATCH lost) |

The gain is 42 card functions and 17 shared functions. No MATCH function turns into DIFF or disappears.

New shared MATCH (17): `Connection::AsyncSend`, `FragmentPacket::FragmentPacket`, `FragmentPacket::~FragmentPacket`, `Network::GetAddressStringW`, `Packet::Add`,
`Packet::Compose`, `PacketBuffer::encrypt`, `Session::GetChannel`, `Session::Send`, `Session::send`, `SessionHandler::~SessionHandler`,
`SessionSendBuffer::Add`, `SessionSendBuffer::increaseBuffer`, `SharedChannel::Send(Packet const*)`, `SharedChannelList::Set`,
`SharedChannelList::~SharedChannelList`, `swprintf_s<129>`.

## Lifted

| Module | RVA | Function | Funcdiff score | MATCH |
| --- | --- | --- | ---: | --- |
| AccountInventoryChannel | `0x64e0` | `Network::iocpHandle` | 100.0 | yes |
| AccountInventoryChannel | `0x66b0` | `AccountInventoryChannel::SendHelloReq` | 100.0 | yes |
| AccountInventoryChannel | `0x67b0` | `AccountInventoryChannel::SendLoginNotify` | 100.0 | yes |
| AccountInventoryChannel | `0x68a0` | `AccountInventoryChannel::SendLogoutNotify` | 100.0 | yes |
| AccountInventoryChannel | `0x6990` | `AccountInventoryChannel::SendGetGoodsCountReq` | 100.0 | yes |
| AccountInventoryChannel | `0x6bd0` | `AccountInventoryChannel::SendListGoodsReq` | 96.3 | no |
| AccountInventoryChannel | `0x6e30` | `AccountInventoryChannel::SendTakeGoodsReq` | 100.0 | yes |
| AccountInventoryChannel | `0x7090` | `AccountInventoryChannel::SendRetrieveLobbyServiceItemListReq` | 100.0 | yes |
| AccountInventoryChannel | `0x72f0` | `AccountInventoryChannel::SendRetrieveSingleWarehouseItemReq` | 100.0 | yes |
| AccountInventoryChannel | `0x7590` | `AccountInventoryChannel::SendTryWarehouseItemConsumptionReq` | 100.0 | yes |
| AccountInventoryChannel | `0x7810` | `AccountInventoryChannel::SendFinishWarehouseItemConsumptionReq` | 97.0 | no |
| AccountInventoryChannel | `0x7ab0` | `AccountInventoryChannel::SendConsumeWarehouseItemReq` | 100.0 | yes |
| AccountInventoryChannel | `0x7d30` | `AccountInventoryChannel::SendRetrieveCharacterGoodsCountReq` | 100.0 | yes |
| AccountInventoryChannel | `0x8020` | `AccountInventorySessionHandler::OnAccept` | 100.0 | yes |
| AccountInventoryChannel | `0x82f0` | `AccountInventorySessionHandler::PacketHandler` | 76.9 | no |
| AccountInventoryChannel | `0x8790` | `swprintf_s<129>` | 100.0 | yes |
| GamedChannel | `0x80300` | `GamedChannelManager::~GamedChannelManager` | 100.0 | yes |
| GamedChannel | `0x803e0` | `GamedChannelManager::Add` | 100.0 | yes |
| GamedChannel | `0x804a0` | `GamedChannelManager::Remove` | 100.0 | yes |
| GamedChannel | `0x805b0` | `GamedChannelManager::Acquire` | 100.0 | yes |
| GamedChannel | `0x80680` | `GamedChannelManager::OnAccept` | 100.0 | yes |
| GamedChannel | `0x806e0` | `GamedChannelManager::OnConnect` | 100.0 | yes |
| GamedChannel | `0x80980` | `GamedChannelManager::PacketHandler` | 82.2 | no |
| GamedChannel | `0x80d50` | `GamedChannel::SendStopPlayNotify` | 100.0 | yes |
| GamedChannel | `0x80e20` | `GamedChannel::SendCreateCharacterReq` | 97.0 | no |
| GamedChannel | `0x81040` | `GamedChannel::SendDeleteCharacterReq` | 100.0 | yes |
| GamedChannel | `0x811c0` | `GamedChannel::SendRestoreCharacterReq` | 100.0 | yes |
| GamedChannel | `0x81320` | `GamedChannel::SendDeleteCharacterCompleteNotify` | 100.0 | yes |
| GamedChannel | `0x813e0` | `GamedChannel::SendCloseSessionNotify` | 100.0 | yes |
| GamedChannel | `0x814a0` | `GamedChannel::SendKickReq` | 100.0 | yes |
| GamedChannel | `0x81620` | `GamedChannel::SendEnterWorldFail` | 100.0 | yes |
| GamedChannel | `0x816f0` | `GamedChannel::SendLeaveWorldOk` | 100.0 | yes |
| GamedChannel | `0x817c0` | `GamedChannel::SendLeaveWorldFail` | 100.0 | yes |
| GamedChannel | `0x81890` | `GamedChannel::SendUpdateCharacterDataOk` | 100.0 | yes |
| GamedChannel | `0x81950` | `GamedChannel::SendUpdateCharacterDataFail` | 100.0 | yes |
| GamedChannel | `0x81a20` | `GamedChannel::SendUpdateAccountDataOk` | 100.0 | yes |
| GamedChannel | `0x81ae0` | `GamedChannel::SendUpdateAccountDataFail` | 100.0 | yes |
| GamedChannel | `0x81bb0` | `GamedChannel::SendTryRegisterGuildOk` | 100.0 | yes |
| GamedChannel | `0x81c80` | `GamedChannel::SendTryRegisterGuildFail` | 100.0 | yes |
| GamedChannel | `0x81d50` | `GamedChannel::SendTryRenameGuildOk` | 100.0 | yes |
| GamedChannel | `0x81e40` | `GamedChannel::SendTryRenameGuildFail` | 100.0 | yes |
| GamedChannel | `0x81f30` | `GamedChannel::SendAccountInventoryNotify` | 79.1 | no |
| GamedChannel | `0x821f0` | `GamedChannel::SendStartChargeOk` | 100.0 | yes |
| GamedChannel | `0x82300` | `GamedChannel::SendStartChargeFail` | 100.0 | yes |
| GamedChannel | `0x823d0` | `GamedChannel::SendStopChargeOk` | 100.0 | yes |
| GamedChannel | `0x82490` | `GamedChannel::SendStopChargeFail` | 100.0 | yes |
| GamedChannel | `0x82560` | `GamedChannel::SendUpdateChargeRemainTimeNotify` | 100.0 | yes |
| GamedChannel | `0x82650` | `GamedChannel::SendApplyNewChargeItemNotify` | 100.0 | yes |
| GamedChannel | `0x82750` | `GamedChannel::SendChangeCharacterAppearanceReq` | 100.0 | yes |
| GamedChannel | `0x82950` | `GamedChannel::SendChangeCharacterSexReq` | 100.0 | yes |

Other changes:
- The functions that have no lifted caller keep `#pragma comment(linker, "/INCLUDE:...")` with `// LIFT:` (dead-strip rule). The names come from `llvm-pdbutil dump -publics`.
- `SharedChannel::Send(Packet const*)` (`0x4ba0`, shared) gets `__declspec(noinline)` (A4). The original `Send*` functions call it out of line. One edit gives +21 MATCH. Parity of the 4 other exes is unchanged.
- The `Packet` constructor is inlined in the original. The lift writes the six stores in the PDB order, then `p.Allocate()` (A19).
- `GamedChannel.h`, `AccountInventoryChannel.h` and `TransactionChannel.h` get the PDB layouts and the new declarations. `CharacterInventoryItem` has the PDB layout.
- `AccountInventoryChannel::SendFinishWarehouseItemConsumptionReq` has the PDB parameter `short result`. The original never reads it (LTCG folded 0 into the body), so the body passes 0.

## Placeholders that later cards must remove

This card defines three items that belong to other cards. They let `LobbyDaemon.exe` link. Each has a `// LIFT:` comment. The owner card deletes the item when it lands. A second definition fails the link.

| Item | File | Owner | Note |
| --- | --- | --- | --- |
| `LobbyGamePacketHandlerDef LobbyGamePacketLobbySideHandlerList[116];` (null table) | `GamedChannel.cpp` | packet handler cards (ld-16, ld-21, ld-26) | Every packet is rejected with "handler not exists" until the table is filled. |
| `AccountInventoryLobbyPacketHandlerDef AccountInventoryLobbyPacketLobbySideHandlerList[37];` (null table) | `AccountInventoryChannel.cpp` | the AccountInventoryLobbyPacketHandler card | Same. |
| `TransactionChannel::TSend` (`0x7b2b0`) stub | `GamedChannel.cpp` | TransactionChannel card (ld-28) | Aborts when called. `noinline`, a volatile flag and `return false` keep LTCG and ICF from folding or dropping it. Remove all of it. |

The original tables have entries (handler, auth, fragment). ❓ This card did not read them.

## DIFF reasons

| Function | Score | Reason |
| --- | ---: | --- |
| `AccountInventoryChannel::SendListGoodsReq` | 96.3 | Consts 89: one immediate (`0x79`) where the original has a `lea` from the zero register. Three forms tried (see lessons ld-18). |
| `AccountInventoryChannel::SendFinishWarehouseItemConsumptionReq` | 97.0 | Consts 91: the original has the immediate `0x16`, ours a `lea`. Three forms tried. |
| `GamedChannel::SendCreateCharacterReq` | 97.0 | Consts 91: ours has the immediate `0x14`, the original a `lea`. Three forms tried. |
| `GamedChannel::SendAccountInventoryNotify` | 79.1 | Calls 56: the original calls `Packet::Allocate()` out of line from the inlined `Packet::Allocate(PacketComposer*)`. Ours inlines both. A `noinline` on the shared `Packet::Allocate()` breaks the other `Send*` functions. Below 85, no tries. |
| `GamedChannelManager::PacketHandler` | 82.2 | The handler table is a null placeholder. LTCG sees the `handler` entries as constants and drops the handler branches (calls 62: the original has the `ConcatenatePacket`, handler and log calls). Retry after the tables are filled. Below 85. |
| `AccountInventorySessionHandler::PacketHandler` | 76.9 | Same null table. Below 85. |
| `TransactionChannel::TSend` | 0.0 | The stub above (ld-28). It is not a card function. |

## Not done

| Module | RVA | Function | Reason |
| --- | --- | --- | --- |
| AccountInventoryChannel | `0x6500` | `AccountInventoryChannel::Connect` | Needs the `LobbyDaemon::pipeConsole` layout and the `PipeConsole` `_lock`, `_invalid` and `ItemNode` layouts (inline list walk). `AccountInventorySessionHandler::_connectLock` is also missing: the class has no layout. |
| AccountInventoryChannel | `0x7fe0` | `AccountInventorySessionHandler::`scalar deleting destructor'` | The constructor, vtable and virtual destructor of `AccountInventorySessionHandler` are not declared (no class layout). A `/INCLUDE` of `??_G` does not link without them. The destructor body is empty. |
| AccountInventoryChannel | `0x8080` | `AccountInventorySessionHandler::OnConnect` | The class has no layout (base, `_connectLock`). It also needs the `LobbyDaemon` layout (`pipeConsole`) for the invalid-info list. |
| AccountInventoryChannel | `0x81b0` | `AccountInventorySessionHandler::OnClose` | Same: no class layout and no `LobbyDaemon` layout. |
| GamedChannel | `0x80790` | `GamedChannelManager::OnClose` | Needs `LobbyDaemon::_instance` with `_gameWorldRegistry` and `_clisessionMgr`, the `GameWorldRegistry` accessors (`_min`, `_size`, `_worlds`) and `GameWorld::_live`. These layouts are not on main. |

The remaining `GamedChannel` functions from `0x82f0` on are part 2 of the module. They stay as `LIFT_STUB`, as the card says.

## Safety differences

| Function | Difference |
| --- | --- |
| `GamedChannelManager::PacketHandler`, `AccountInventorySessionHandler::PacketHandler` | The tables are empty. The `handler == nullptr` check (present in the original) now rejects every packet. The original called the handlers. This is temporary until the handler cards land. |
| `TransactionChannel::TSend` stub | Every `Send*` function with a transaction aborts at the `TSend` call. The original sends. Temporary until ld-28. |
| `SharedChannel::Send(Packet const*)` | Kept the original leak: it returns without `removeReferenceCount` when the session is not connected (marked `// BUG:` in `SharedChannel.cpp`). Not changed by this card. |
| All other lifted functions | No known difference. Packet formats, command numbers, log lines and error paths follow the pseudocode. |

## Follow-up for other cards

| Item | Owner | Note |
| --- | --- | --- |
| Remove the two null tables and the `TSend` stub | handler cards, ld-28 | See "Placeholders". |
| Lift the 5 Not done functions | after the `LobbyDaemon`, `PipeConsole` and `GameWorld` layouts land | Add the `AccountInventorySessionHandler` base, vtable and constructor first. |
| `SendAccountInventoryNotify` 79.1 | BloodLib follow-up | Find a form that makes LTCG call `Packet::Allocate()` out of line only from `Allocate(PacketComposer*)`. |
