// LobbyGatePredefine.obj (LobbyGate PDB).
#include "LobbyGatePredefine.h"
#include <string.h>
#include <wchar.h>
#include "FragmentPacket.h"
#include "Memory.h"

#define PREDEFINE_FILE L"LobbyGatePredefine.cpp"

namespace
{
// ❓ Inlined size check before each Compose: the code allocates a new fragment when the free size is too small.
inline unsigned short FreeBody(FragmentPacket* fp)
{
    return fp->packet.CurHeader != nullptr ? static_cast<unsigned short>(4000 - fp->packet.CurHeader->size) : 0;
}

inline void Reserve(FragmentPacket* fp, unsigned long long size)
{
    Packet::Header* header = fp->packet.CurHeader;
    if (header == nullptr || static_cast<unsigned short>(4000 - header->size) < size)
        fp->packet.Allocate(&fp->composer);
}

inline void ReserveVar(FragmentPacket* fp, unsigned long long size)
{
    if (FreeBody(fp) < size)
        fp->packet.Allocate(&fp->composer);
}
}  // namespace

// 0x152a0
bool GoodsItem::Setup(FragmentPacketConcatenater* fpc)
{
    PacketConcatenateBuffer::VarData varCustomizedItemAttribute_1;
    PacketConcatenateBuffer::VarData varCustomizedItemAttribute_2;

    if (fpc == nullptr || !fpc->Decompose(3, &itemNumber, &itemAmount, &itemDataId))
        return false;
    if (static_cast<unsigned short>(fpc->Decompose(&varCustomizedItemAttribute_1)) == 0 ||
        static_cast<unsigned short>(fpc->Decompose(&varCustomizedItemAttribute_2)) == 0)
        return false;

    if (*varCustomizedItemAttribute_1.size > 0)
    {
        customizedItemAttribute_1 = static_cast<char*>(
            Memory::_Manager[2]->AllocZero(*varCustomizedItemAttribute_1.size, PREDEFINE_FILE, 33));
        customizedItemAttribute_1_Size = *varCustomizedItemAttribute_1.size;
        memcpy(customizedItemAttribute_1, varCustomizedItemAttribute_1.buffer, *varCustomizedItemAttribute_1.size);
    }
    if (*varCustomizedItemAttribute_2.size > 0)
    {
        customizedItemAttribute_2 = static_cast<char*>(
            Memory::_Manager[2]->AllocZero(*varCustomizedItemAttribute_2.size, PREDEFINE_FILE, 40));
        customizedItemAttribute_2_Size = *varCustomizedItemAttribute_2.size;
        memcpy(customizedItemAttribute_2, varCustomizedItemAttribute_2.buffer, *varCustomizedItemAttribute_2.size);
    }
    return true;
}

// 0x153c0
bool GoodsItem::Fetch(FragmentPacket* fp)
{
    if (fp == nullptr)
        return false;
    Reserve(fp, 4);
    if (fp->Compose(1, itemNumber) == 0)
        return false;
    Reserve(fp, 4);
    if (fp->Compose(1, itemAmount) == 0)
        return false;
    Reserve(fp, 4);
    if (fp->Compose(1, itemDataId) == 0)
        return false;
    ReserveVar(fp, customizedItemAttribute_1_Size + 2LL);
    if (fp->Compose(1, customizedItemAttribute_1, customizedItemAttribute_1_Size) == 0)
        return false;
    ReserveVar(fp, customizedItemAttribute_2_Size + 2LL);
    return fp->Compose(1, customizedItemAttribute_2, customizedItemAttribute_2_Size) != 0;
}

// 0x15570
bool Goods::Setup(FragmentPacketConcatenater* fpc)
{
    PacketConcatenateBuffer::VarData varGoodsRestrictionCondition;
    PacketConcatenateBuffer::VarData varCustomizedGoodsAttribute;

    if (fpc == nullptr)
        return false;
    if (!fpc->Decompose(11, &goodsId, &goodsNumber, &isRefundable, &useRefundExpirationDate, &refundExpirationDate,
                        &deliveryDate, senderDesc, 51, senderMessage, 81, &goodsIconId, goodsName, 81, goodsDesc, 201))
        return false;
    int i = 0;
    if (static_cast<unsigned short>(fpc->Decompose(&varGoodsRestrictionCondition)) == 0 ||
        static_cast<unsigned short>(fpc->Decompose(&varCustomizedGoodsAttribute)) == 0)
        return false;

    if (*varGoodsRestrictionCondition.size > 0)
    {
        goodsRestrictionCondition = static_cast<char*>(
            Memory::_Manager[2]->AllocZero(*varGoodsRestrictionCondition.size, PREDEFINE_FILE, 112));
        goodsRestrictionConditionSize = *varGoodsRestrictionCondition.size;
        memcpy(goodsRestrictionCondition, varGoodsRestrictionCondition.buffer, *varGoodsRestrictionCondition.size);
    }
    if (*varCustomizedGoodsAttribute.size > 0)
    {
        customizedGoodsAttribute = static_cast<char*>(
            Memory::_Manager[2]->AllocZero(*varCustomizedGoodsAttribute.size, PREDEFINE_FILE, 119));
        customizedGoodsAttributeSize = *varCustomizedGoodsAttribute.size;
        memcpy(customizedGoodsAttribute, varCustomizedGoodsAttribute.buffer, *varCustomizedGoodsAttribute.size);
    }

    short count = static_cast<short>(fpc->decomposer.PushRepeatCount(&fpc->buffer[fpc->decomposer.offset],
                                                                       fpc->size - fpc->decomposer.offset));
    goodsItemCount = count;
    if (count > 0)
    {
        goodsItemList = static_cast<GoodsItem*>(
            Memory::_Manager[2]->AllocZero(sizeof(GoodsItem) * count, PREDEFINE_FILE, 127));
        for (; i < goodsItemCount; ++i)
        {
            if (!goodsItemList[i].Setup(fpc))
                return false;
            // Inlined RepeatPacketDecomposer step to the next repeat entry.
            int top = fpc->decomposer.top;
            fpc->decomposer.index = fpc->decomposer.start[top] + 1;
            --fpc->decomposer.counts[top];
        }
    }
    fpc->decomposer.PopRepeatCount();
    return true;
}

// 0x15810
void Goods::Cleanup()
{
    if (goodsRestrictionCondition != nullptr)
    {
        Memory::_Manager[2]->Free(goodsRestrictionCondition, PREDEFINE_FILE, 144);
        goodsRestrictionCondition = nullptr;
    }
    if (customizedGoodsAttribute != nullptr)
    {
        Memory::_Manager[2]->Free(customizedGoodsAttribute, PREDEFINE_FILE, 146);
        customizedGoodsAttribute = nullptr;
    }
    if (goodsItemList != nullptr)
    {
        for (int i = 0; i < goodsItemCount; ++i)
        {
            // Inlined GoodsItem cleanup (LobbyGatePredefine.cpp lines 51 and 53).
            GoodsItem* item = &goodsItemList[i];
            if (item->customizedItemAttribute_1 != nullptr)
            {
                Memory::_Manager[2]->Free(item->customizedItemAttribute_1, PREDEFINE_FILE, 51);
                item->customizedItemAttribute_1 = nullptr;
            }
            if (item->customizedItemAttribute_2 != nullptr)
            {
                Memory::_Manager[2]->Free(item->customizedItemAttribute_2, PREDEFINE_FILE, 53);
                item->customizedItemAttribute_2 = nullptr;
            }
        }
        Memory::_Manager[2]->Free(goodsItemList, PREDEFINE_FILE, 154);
        goodsItemList = nullptr;
    }
}

// 0x15960
bool Goods::Fetch(FragmentPacket* fp)
{
    Reserve(fp, 8);
    if (fp->Compose(1, goodsId) == 0)
        return false;
    Reserve(fp, 4);
    if (fp->Compose(1, goodsNumber) == 0)
        return false;
    Reserve(fp, 1);
    if (fp->Compose(1, static_cast<int>(isRefundable)) == 0)
        return false;
    Reserve(fp, 1);
    if (fp->Compose(1, static_cast<int>(useRefundExpirationDate)) == 0)
        return false;
    Reserve(fp, 8);
    if (fp->Compose(1, refundExpirationDate) == 0)
        return false;
    Reserve(fp, 8);
    if (fp->Compose(1, deliveryDate) == 0)
        return false;
    // The original takes 2 * (wcslen + 1) for each string.
    ReserveVar(fp, 2 * (wcslen(senderDesc) + 1));
    if (fp->Compose(1, senderDesc) == 0)
        return false;
    ReserveVar(fp, 2 * (wcslen(senderMessage) + 1));
    if (fp->Compose(1, senderMessage) == 0)
        return false;
    Reserve(fp, 4);
    if (fp->Compose(1, goodsIconId) == 0)
        return false;
    ReserveVar(fp, 2 * (wcslen(goodsName) + 1));
    if (fp->Compose(1, goodsName) == 0)
        return false;
    ReserveVar(fp, 2 * (wcslen(goodsDesc) + 1));
    if (fp->Compose(1, goodsDesc) == 0)
        return false;
    ReserveVar(fp, goodsRestrictionConditionSize + 2LL);
    if (fp->Compose(1, goodsRestrictionCondition, goodsRestrictionConditionSize) == 0)
        return false;
    ReserveVar(fp, customizedGoodsAttributeSize + 2LL);
    if (fp->Compose(1, customizedGoodsAttribute, customizedGoodsAttributeSize) == 0)
        return false;

    fp->StartRepeat();
    if (goodsItemList != nullptr)
    {
        for (int i = 0; i < goodsItemCount; ++i)
        {
            if (!goodsItemList[i].Fetch(fp))
                return false;
            fp->IncRepeatCount();
        }
    }
    fp->composer.PopRepeatCount();
    return true;
}
