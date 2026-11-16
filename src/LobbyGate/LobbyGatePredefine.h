// LobbyGatePredefine.obj (LobbyGate PDB). Layouts from include/pdb/LobbyGate/types.h.
#pragma once
#include <stddef.h>

class FragmentPacket;
class FragmentPacketConcatenater;

struct GoodsItem
{
    bool Setup(FragmentPacketConcatenater* fpc);  // 0x152a0
    bool Fetch(FragmentPacket* fp);               // 0x153c0

    unsigned int itemNumber;
    int itemAmount;
    unsigned int itemDataId;
    char* customizedItemAttribute_1;
    int customizedItemAttribute_1_Size;
    char* customizedItemAttribute_2;
    int customizedItemAttribute_2_Size;
};
static_assert(sizeof(GoodsItem) == 0x30, "sizeof GoodsItem");

struct Goods
{
    bool Setup(FragmentPacketConcatenater* fpc);  // 0x15570
    void Cleanup();                               // 0x15810
    bool Fetch(FragmentPacket* fp);               // 0x15960

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
