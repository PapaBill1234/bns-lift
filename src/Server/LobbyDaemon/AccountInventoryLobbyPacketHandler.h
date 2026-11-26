// AccountInventoryLobbyPacketHandler.obj (LobbyDaemon PDB, 2019 + PDB).
#pragma once

class FragmentPacketConcatenater;
class Packet;
class SharedChannel;

bool HandleAccountInventoryLobby_HelloOk(SharedChannel*, Packet const*);  // 0x87d0
bool HandleAccountInventoryLobby_HelloFail(SharedChannel*, Packet const*);  // 0x8820
bool HandleAccountInventoryLobby_GetGoodsCountOk(SharedChannel*, Packet const*);  // 0x88b0
bool HandleAccountInventoryLobby_GetGoodsCountFail(SharedChannel*, Packet const*);  // 0x8ad0
bool HandleAccountInventoryLobby_ListGoodsOk(SharedChannel*, FragmentPacketConcatenater*);  // 0x8d00
bool HandleAccountInventoryLobby_ListGoodsFail(SharedChannel*, Packet const*);  // 0x9550
bool HandleAccountInventoryLobby_TakeGoodsOk(SharedChannel*, FragmentPacketConcatenater*);  // 0x9750
bool HandleAccountInventoryLobby_TakeGoodsFail(SharedChannel*, Packet const*);  // 0x9a60
bool HandleAccountInventoryLobby_RetrieveLobbyServiceItemListOk(SharedChannel*, FragmentPacketConcatenater*);  // 0x9c60
bool HandleAccountInventoryLobby_RetrieveLobbyServiceItemListFail(SharedChannel*, Packet const*);  // 0x9f60
bool HandleAccountInventoryLobby_RetrieveSingleWarehouseItemOk(SharedChannel*, Packet const*);  // 0xa160
bool HandleAccountInventoryLobby_RetrieveSingleWarehouseItemFail(SharedChannel*, Packet const*);  // 0xa440
bool HandleAccountInventoryLobby_TryWarehouseItemConsumptionOk(SharedChannel*, Packet const*);  // 0xa680
bool HandleAccountInventoryLobby_TryWarehouseItemConsumptionFail(SharedChannel*, Packet const*);  // 0xa780
bool HandleAccountInventoryLobby_FinishWarehouseItemConsumptionOk(SharedChannel*, Packet const*);  // 0xa9c0
bool HandleAccountInventoryLobby_FinishWarehouseItemConsumptionFail(SharedChannel*, Packet const*);  // 0xaac0
bool HandleAccountInventoryLobby_CancelWarehouseItemConsumptionOk(SharedChannel*, Packet const*);  // 0xad00
bool HandleAccountInventoryLobby_CancelWarehouseItemConsumptionFail(SharedChannel*, Packet const*);  // 0xad40
bool HandleAccountInventoryLobby_ConsumeWarehouseItemOk(SharedChannel*, Packet const*);  // 0xad80
bool HandleAccountInventoryLobby_ConsumeWarehouseItemFail(SharedChannel*, Packet const*);  // 0xae80
bool HandleAccountInventoryLobby_RetrieveCharacterGoodsCountOk(SharedChannel*, Packet const*);  // 0xb0c0
bool HandleAccountInventoryLobby_RetrieveCharacterGoodsCountFail(SharedChannel*, Packet const*);  // 0xb310
bool HandleAccountInventoryLobby_GoodsInventoryChangedNotify(SharedChannel*, FragmentPacketConcatenater*);  // 0xb510

// PDB AccountInventoryLobbyPacketHandlerDef (sizeof 16).
struct AccountInventoryLobbyPacketHandlerDef
{
    void* handler;
    bool auth;
    bool fragment;
};
static_assert(sizeof(AccountInventoryLobbyPacketHandlerDef) == 0x10, "sizeof AccountInventoryLobbyPacketHandlerDef");

// PDB global at .data rva 0x203520 (37 entries). AccountInventoryLobbyPacketLobbySideHandlerList.cpp has the definition.
extern AccountInventoryLobbyPacketHandlerDef AccountInventoryLobbyPacketLobbySideHandlerList[37];
