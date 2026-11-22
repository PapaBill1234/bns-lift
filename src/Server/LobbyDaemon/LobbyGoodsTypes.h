// Goods and LobbyServiceItem (LobbyDaemon PDB, 2019 + PDB). Layouts from include/pdb/LobbyDaemon/types.h.
#pragma once
#include <stddef.h>

class FragmentPacket;
struct GoodsItem;

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
