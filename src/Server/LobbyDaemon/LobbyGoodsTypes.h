// Goods and LobbyServiceItem (LobbyDaemon PDB, 2019 + PDB). Layouts from include/pdb/LobbyDaemon/types.h.
#pragma once
#include <stddef.h>

class FragmentPacket;

// LIFT: gap-24. AccountInventoryLobbyPacketHandler fills an array of this type in HandleAccountInventoryLobby_ListGoodsOk (0x8d00).
struct GoodsItem
{
public:
    unsigned int itemNumber;
    int itemAmount;
    unsigned int itemDataId;
    char* customizedItemAttribute_1;
    int customizedItemAttribute_1_Size;
    char* customizedItemAttribute_2;
    int customizedItemAttribute_2_Size;
};
static_assert(sizeof(GoodsItem) == 0x30, "sizeof GoodsItem");
static_assert(offsetof(GoodsItem, customizedItemAttribute_1) == 0x10, "GoodsItem::customizedItemAttribute_1");
static_assert(offsetof(GoodsItem, customizedItemAttribute_2) == 0x20, "GoodsItem::customizedItemAttribute_2");

struct Goods
{
public:
    bool Fetch(FragmentPacket* fp);  // 0x6010 (AccountInventory; not lifted here)

    unsigned long long goodsId;
    int goodsNumber;
    char isRefundable;
    char useRefundExpirationDate;
    long long refundExpirationDate;
    long long deliveryDate;
    wchar_t senderDesc[51];
    wchar_t senderMessage[81];
    int goodsIconId;
    wchar_t goodsName[81];
    wchar_t goodsDesc[201];
    char* goodsRestrictionCondition;
    int goodsRestrictionConditionSize;
    char* customizedGoodsAttribute;
    int customizedGoodsAttributeSize;
    GoodsItem* goodsItemList;
    int goodsItemCount;
};
static_assert(sizeof(Goods) == 0x390, "sizeof Goods");

struct LobbyServiceItem
{
public:
    unsigned long long ownerPcId;
    unsigned long long instanceId;
    unsigned long long labelId;
    unsigned int dataId;
    char state;
};
static_assert(sizeof(LobbyServiceItem) == 0x20, "sizeof LobbyServiceItem");
static_assert(offsetof(LobbyServiceItem, dataId) == 0x18, "LobbyServiceItem::dataId");
static_assert(offsetof(LobbyServiceItem, state) == 0x1C, "LobbyServiceItem::state");

struct CharacterInventoryItem;

// LIFT: gap-24. HandleAccountInventoryLobby_GoodsInventoryChangedNotify (0xb510) fills a local of this type for
// CliSession::NotifyGoodsInventoryChangedAlongPresence (0x392c0).
struct GoodsInventoryChangedNotifyParam
{
    char changedActionType;
    CharacterInventoryItem* items;
    int itemCount;
    char itemRemain;
    unsigned long long goodsLabelIdMin;
    unsigned long long goodsItemInsIdMin;
};
static_assert(sizeof(GoodsInventoryChangedNotifyParam) == 0x28, "sizeof GoodsInventoryChangedNotifyParam");
static_assert(offsetof(GoodsInventoryChangedNotifyParam, items) == 0x8, "GoodsInventoryChangedNotifyParam::items");
static_assert(offsetof(GoodsInventoryChangedNotifyParam, itemCount) == 0x10, "GoodsInventoryChangedNotifyParam::itemCount");
static_assert(offsetof(GoodsInventoryChangedNotifyParam, itemRemain) == 0x14, "GoodsInventoryChangedNotifyParam::itemRemain");
static_assert(offsetof(GoodsInventoryChangedNotifyParam, goodsLabelIdMin) == 0x18, "GoodsInventoryChangedNotifyParam::goodsLabelIdMin");
static_assert(offsetof(GoodsInventoryChangedNotifyParam, goodsItemInsIdMin) == 0x20, "GoodsInventoryChangedNotifyParam::goodsItemInsIdMin");
