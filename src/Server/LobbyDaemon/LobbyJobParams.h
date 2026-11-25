// Job parameter structs (LobbyDaemon PDB, 2019 + PDB). Filled by LobbyGamePacketHandler.cpp (0x8a560, 0x8a7c0, 0x8ad30).
// LIFT: the PDB has these as public structs without a home header. This header holds the layouts that lift-lobbydaemon-16 needs.
#pragma once
#include <stddef.h>
#include "StringUtil.h"

struct Goods;
struct LobbyServiceItem;
class LobbyGateChannel;

struct WorldKickFailParam
{
    short reason;
};
static_assert(sizeof(WorldKickFailParam) == 0x2, "sizeof WorldKickFailParam");
static_assert(offsetof(WorldKickFailParam, reason) == 0x0, "WorldKickFailParam::reason");

struct CreateCharacterOkParam
{
    short job;
    short level;
    char showcaseData[512];
    short showcaseDataSize;
};
static_assert(sizeof(CreateCharacterOkParam) == 0x206, "sizeof CreateCharacterOkParam");
static_assert(offsetof(CreateCharacterOkParam, job) == 0x0, "CreateCharacterOkParam::job");
static_assert(offsetof(CreateCharacterOkParam, level) == 0x2, "CreateCharacterOkParam::level");
static_assert(offsetof(CreateCharacterOkParam, showcaseData) == 0x4, "CreateCharacterOkParam::showcaseData");
static_assert(offsetof(CreateCharacterOkParam, showcaseDataSize) == 0x204, "CreateCharacterOkParam::showcaseDataSize");

struct DeleteCharacterOkParam
{
    short level;
};
static_assert(sizeof(DeleteCharacterOkParam) == 0x2, "sizeof DeleteCharacterOkParam");
static_assert(offsetof(DeleteCharacterOkParam, level) == 0x0, "DeleteCharacterOkParam::level");

// LIFT: fix7. AccountInventoryLobbyPacketHandler (0xb0c0) fills a local of this type.
struct GetCharacterGoodsCountOkParam
{
    int goodsCount;
    int takedGoodsCount;
};
static_assert(sizeof(GetCharacterGoodsCountOkParam) == 0x8, "sizeof GetCharacterGoodsCountOkParam");
static_assert(offsetof(GetCharacterGoodsCountOkParam, goodsCount) == 0x0, "GetCharacterGoodsCountOkParam::goodsCount");
static_assert(offsetof(GetCharacterGoodsCountOkParam, takedGoodsCount) == 0x4, "GetCharacterGoodsCountOkParam::takedGoodsCount");

// LIFT: fix7. AccountInventoryLobbyPacketHandler (0xa160) fills a local of this type.
struct RetrieveSingleWarehouseItemOkParam
{
    LobbyServiceItem* item;
};
static_assert(sizeof(RetrieveSingleWarehouseItemOkParam) == 0x8, "sizeof RetrieveSingleWarehouseItemOkParam");
static_assert(offsetof(RetrieveSingleWarehouseItemOkParam, item) == 0x0, "RetrieveSingleWarehouseItemOkParam::item");

// LIFT: gap-06. AccountInventoryLobbyPacketHandler fills a local of this type for ListGoodsJob.
struct ListGoodsOkParam
{
    Goods* goodsList;
    int goodsCount;
};
static_assert(sizeof(ListGoodsOkParam) == 0x10, "sizeof ListGoodsOkParam");
static_assert(offsetof(ListGoodsOkParam, goodsList) == 0x0, "ListGoodsOkParam::goodsList");
static_assert(offsetof(ListGoodsOkParam, goodsCount) == 0x8, "ListGoodsOkParam::goodsCount");

// LIFT: gap-06. AccountInventoryLobbyPacketHandler fills a local of this type for TakeGoodsJob.
struct TakeGoodsOkParam
{
    LobbyServiceItem* items;
    int itemCount;
};
static_assert(sizeof(TakeGoodsOkParam) == 0x10, "sizeof TakeGoodsOkParam");
static_assert(offsetof(TakeGoodsOkParam, items) == 0x0, "TakeGoodsOkParam::items");
static_assert(offsetof(TakeGoodsOkParam, itemCount) == 0x8, "TakeGoodsOkParam::itemCount");

// LIFT: gap-06. AccountInventoryLobbyPacketHandler fills a local of this type for ListLobbyServiceItemJob.
struct RetrieveLobbyServiceItemListOkParam
{
    int searchCount;
    LobbyServiceItem* items;
    int itemCount;
};
static_assert(sizeof(RetrieveLobbyServiceItemListOkParam) == 0x18, "sizeof RetrieveLobbyServiceItemListOkParam");
static_assert(offsetof(RetrieveLobbyServiceItemListOkParam, searchCount) == 0x0, "RetrieveLobbyServiceItemListOkParam::searchCount");
static_assert(offsetof(RetrieveLobbyServiceItemListOkParam, items) == 0x8, "RetrieveLobbyServiceItemListOkParam::items");
static_assert(offsetof(RetrieveLobbyServiceItemListOkParam, itemCount) == 0x10, "RetrieveLobbyServiceItemListOkParam::itemCount");

// LIFT: gap-11. LobbyGamePacketHandler fills a local of this type for RenameCharacterJob::init (0x66e70).
struct RenameCharacterWithAccountInventoryItemReqParam
{
    LobbyGateChannel* lgate;
    id128 slotid;
    wchar_t newName[33];
    unsigned long long labelId;
    unsigned long long itemInstanceId;
    unsigned int itemDataId;
};
static_assert(sizeof(RenameCharacterWithAccountInventoryItemReqParam) == 0x78, "sizeof RenameCharacterWithAccountInventoryItemReqParam");
static_assert(offsetof(RenameCharacterWithAccountInventoryItemReqParam, slotid) == 0x8, "RenameCharacterWithAccountInventoryItemReqParam::slotid");
static_assert(offsetof(RenameCharacterWithAccountInventoryItemReqParam, newName) == 0x18, "RenameCharacterWithAccountInventoryItemReqParam::newName");
static_assert(offsetof(RenameCharacterWithAccountInventoryItemReqParam, labelId) == 0x60, "RenameCharacterWithAccountInventoryItemReqParam::labelId");
static_assert(offsetof(RenameCharacterWithAccountInventoryItemReqParam, itemDataId) == 0x70, "RenameCharacterWithAccountInventoryItemReqParam::itemDataId");

// LIFT: gap-11. LobbyGamePacketHandler fills a local of this type for ChangeUserNameJob::init (0x26c80).
struct ChangeUserNameWithAccountInventoryItemReqParam
{
    LobbyGateChannel* lgate;
    wchar_t newUserName[65];
    unsigned long long labelId;
    unsigned long long itemInstanceId;
    unsigned int itemDataId;
};
static_assert(sizeof(ChangeUserNameWithAccountInventoryItemReqParam) == 0xA8, "sizeof ChangeUserNameWithAccountInventoryItemReqParam");
static_assert(offsetof(ChangeUserNameWithAccountInventoryItemReqParam, newUserName) == 0x8, "ChangeUserNameWithAccountInventoryItemReqParam::newUserName");
static_assert(offsetof(ChangeUserNameWithAccountInventoryItemReqParam, labelId) == 0x90, "ChangeUserNameWithAccountInventoryItemReqParam::labelId");
static_assert(offsetof(ChangeUserNameWithAccountInventoryItemReqParam, itemDataId) == 0xA0, "ChangeUserNameWithAccountInventoryItemReqParam::itemDataId");

// LIFT: gap-11. LobbyGamePacketHandler fills a local of this type for CreateInitialUserNameJob::init (0x2fe20).
struct CreateInitialUserNameReqParam
{
    LobbyGateChannel* lgate;
    wchar_t newUserName[65];
};
static_assert(sizeof(CreateInitialUserNameReqParam) == 0x90, "sizeof CreateInitialUserNameReqParam");
static_assert(offsetof(CreateInitialUserNameReqParam, newUserName) == 0x8, "CreateInitialUserNameReqParam::newUserName");

// LIFT: gap-09. PDB CancelWaitCharacterDeletionReqParam (type 0x5276, sizeof 0x18). The task parameter of
// TASK_CANCEL_WAIT_CHARACTER_DELETION_REQ (12). HandleLobbyLobbyGate_CancelWaitCharacterDeletionReq (0xc67e0) fills it.
#include "StringUtil.h"
class LobbyGateChannel;
struct CancelWaitCharacterDeletionReqParam
{
    LobbyGateChannel* lgate;
    id128 slotid;
};
static_assert(sizeof(CancelWaitCharacterDeletionReqParam) == 0x18, "sizeof CancelWaitCharacterDeletionReqParam");
static_assert(offsetof(CancelWaitCharacterDeletionReqParam, lgate) == 0x0, "CancelWaitCharacterDeletionReqParam::lgate");
static_assert(offsetof(CancelWaitCharacterDeletionReqParam, slotid) == 0x8, "CancelWaitCharacterDeletionReqParam::slotid");

// LIFT: gap-09. PDB CreateCharacterReqParam (sizeof 0x160). The task parameter of TASK_CREATE_CHARACTER_REQ (10).
// HandleLobbyLobbyGate_CreateCharacterReq (0xc5b10) fills it. CreateCharacterJob::init (0x41b10) reads it.
struct CreateCharacterReqParam
{
    LobbyGateChannel* lgate;
    id128 slotid;
    short wid;
    wchar_t characterName[33];
    char characterMakeData[256];
    short characterMakeDataSize;
    bool jumpingCharacter;
};
static_assert(sizeof(CreateCharacterReqParam) == 0x160, "sizeof CreateCharacterReqParam");
static_assert(offsetof(CreateCharacterReqParam, lgate) == 0x0, "CreateCharacterReqParam::lgate");
static_assert(offsetof(CreateCharacterReqParam, slotid) == 0x8, "CreateCharacterReqParam::slotid");
static_assert(offsetof(CreateCharacterReqParam, wid) == 0x18, "CreateCharacterReqParam::wid");
static_assert(offsetof(CreateCharacterReqParam, characterName) == 0x1A, "CreateCharacterReqParam::characterName");
static_assert(offsetof(CreateCharacterReqParam, characterMakeData) == 0x5C, "CreateCharacterReqParam::characterMakeData");
static_assert(offsetof(CreateCharacterReqParam, characterMakeDataSize) == 0x15C, "CreateCharacterReqParam::characterMakeDataSize");
static_assert(offsetof(CreateCharacterReqParam, jumpingCharacter) == 0x15E, "CreateCharacterReqParam::jumpingCharacter");

// LIFT: gap-09. PDB DeleteCharacterReqParam (sizeof 0x18). The task parameter of TASK_DELETE_CHARACTER_REQ (11).
// DeleteCharacterJob::init (0x453a0) reads it. StringUtil.h (id128) and class LobbyGateChannel are declared above.
struct DeleteCharacterReqParam
{
    LobbyGateChannel* lgate;
    id128 slotid;
};
static_assert(sizeof(DeleteCharacterReqParam) == 0x18, "sizeof DeleteCharacterReqParam");
static_assert(offsetof(DeleteCharacterReqParam, lgate) == 0x0, "DeleteCharacterReqParam::lgate");
static_assert(offsetof(DeleteCharacterReqParam, slotid) == 0x8, "DeleteCharacterReqParam::slotid");

// LIFT: gap-14. AddSlotJob::init (0xd570) reads this type.
struct AddSlotWithAccountInventoryItemReqParam
{
    LobbyGateChannel* lgate;
    unsigned long long labelId;
    unsigned long long itemInstanceId;
    unsigned int itemDataId;
};
static_assert(sizeof(AddSlotWithAccountInventoryItemReqParam) == 0x20, "sizeof AddSlotWithAccountInventoryItemReqParam");
static_assert(offsetof(AddSlotWithAccountInventoryItemReqParam, labelId) == 0x8, "AddSlotWithAccountInventoryItemReqParam::labelId");
static_assert(offsetof(AddSlotWithAccountInventoryItemReqParam, itemInstanceId) == 0x10, "AddSlotWithAccountInventoryItemReqParam::itemInstanceId");
static_assert(offsetof(AddSlotWithAccountInventoryItemReqParam, itemDataId) == 0x18, "AddSlotWithAccountInventoryItemReqParam::itemDataId");

// LIFT: gap-14. BindCharacterSlotJob::init (0x17050) reads this type.
struct BindCharacterSlotReqParam
{
    LobbyGateChannel* lgate;
    id128 slotid;
    unsigned long long pcId;
};
static_assert(sizeof(BindCharacterSlotReqParam) == 0x20, "sizeof BindCharacterSlotReqParam");
static_assert(offsetof(BindCharacterSlotReqParam, slotid) == 0x8, "BindCharacterSlotReqParam::slotid");
static_assert(offsetof(BindCharacterSlotReqParam, pcId) == 0x18, "BindCharacterSlotReqParam::pcId");
