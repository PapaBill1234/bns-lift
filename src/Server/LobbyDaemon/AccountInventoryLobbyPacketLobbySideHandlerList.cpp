// AccountInventoryLobbyPacketLobbySideHandlerList (LobbyDaemon PDB, 2019 + PDB, data only).
// LIFT: PDB global at .data rva 0x203520. The PDB gives no module for it. The original is a data-only definition, so the
// compiler cannot fold the entries into AccountInventorySessionHandler::PacketHandler (0x82f0). This file keeps it in its
// own translation unit, as LobbyInfoGatePacketLobbySideHandlerList.cpp does.
#include "AccountInventoryLobbyPacketHandler.h"

#define AI_H(f) reinterpret_cast<void*>(&(f))
// Entries read from .data at rva 0x203520 (handler, auth, fragment). All 23 handlers have auth 1. The fragment handlers
// are ListGoodsOk (8), TakeGoodsOk (11), RetrieveLobbyServiceItemListOk (14) and GoodsInventoryChangedNotify (34).
// All other entries are null.
AccountInventoryLobbyPacketHandlerDef AccountInventoryLobbyPacketLobbySideHandlerList[37] = {
    /*  0 */ {nullptr, false, false},
    /*  1 */ {nullptr, false, false},
    /*  2 */ {AI_H(HandleAccountInventoryLobby_HelloOk), true, false},
    /*  3 */ {AI_H(HandleAccountInventoryLobby_HelloFail), true, false},
    /*  4 */ {nullptr, false, false},
    /*  5 */ {AI_H(HandleAccountInventoryLobby_GetGoodsCountOk), true, false},
    /*  6 */ {AI_H(HandleAccountInventoryLobby_GetGoodsCountFail), true, false},
    /*  7 */ {nullptr, false, false},
    /*  8 */ {AI_H(HandleAccountInventoryLobby_ListGoodsOk), true, true},
    /*  9 */ {AI_H(HandleAccountInventoryLobby_ListGoodsFail), true, false},
    /* 10 */ {nullptr, false, false},
    /* 11 */ {AI_H(HandleAccountInventoryLobby_TakeGoodsOk), true, true},
    /* 12 */ {AI_H(HandleAccountInventoryLobby_TakeGoodsFail), true, false},
    /* 13 */ {nullptr, false, false},
    /* 14 */ {AI_H(HandleAccountInventoryLobby_RetrieveLobbyServiceItemListOk), true, true},
    /* 15 */ {AI_H(HandleAccountInventoryLobby_RetrieveLobbyServiceItemListFail), true, false},
    /* 16 */ {nullptr, false, false},
    /* 17 */ {AI_H(HandleAccountInventoryLobby_RetrieveSingleWarehouseItemOk), true, false},
    /* 18 */ {AI_H(HandleAccountInventoryLobby_RetrieveSingleWarehouseItemFail), true, false},
    /* 19 */ {nullptr, false, false},
    /* 20 */ {AI_H(HandleAccountInventoryLobby_TryWarehouseItemConsumptionOk), true, false},
    /* 21 */ {AI_H(HandleAccountInventoryLobby_TryWarehouseItemConsumptionFail), true, false},
    /* 22 */ {nullptr, false, false},
    /* 23 */ {AI_H(HandleAccountInventoryLobby_FinishWarehouseItemConsumptionOk), true, false},
    /* 24 */ {AI_H(HandleAccountInventoryLobby_FinishWarehouseItemConsumptionFail), true, false},
    /* 25 */ {nullptr, false, false},
    /* 26 */ {AI_H(HandleAccountInventoryLobby_CancelWarehouseItemConsumptionOk), true, false},
    /* 27 */ {AI_H(HandleAccountInventoryLobby_CancelWarehouseItemConsumptionFail), true, false},
    /* 28 */ {nullptr, false, false},
    /* 29 */ {AI_H(HandleAccountInventoryLobby_ConsumeWarehouseItemOk), true, false},
    /* 30 */ {AI_H(HandleAccountInventoryLobby_ConsumeWarehouseItemFail), true, false},
    /* 31 */ {nullptr, false, false},
    /* 32 */ {AI_H(HandleAccountInventoryLobby_RetrieveCharacterGoodsCountOk), true, false},
    /* 33 */ {AI_H(HandleAccountInventoryLobby_RetrieveCharacterGoodsCountFail), true, false},
    /* 34 */ {AI_H(HandleAccountInventoryLobby_GoodsInventoryChangedNotify), true, true},
    /* 35 */ {nullptr, false, false},
    /* 36 */ {nullptr, false, false}};
#undef AI_H
