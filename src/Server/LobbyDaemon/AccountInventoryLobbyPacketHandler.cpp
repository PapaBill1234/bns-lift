// AccountInventoryLobbyPacketHandler.obj (LobbyDaemon PDB, 2019 + PDB).
#include <string.h>
#include <winsock2.h>
#include <windows.h>
#include "AccountInventoryLobbyPacketHandler.h"
#include "CliSession.h"
#include "CliSessionManager.h"
#include "CliSessionTable.h"
#include "FragmentPacket.h"
#include "GamedChannel.h"
#include "LobbyDaemon.h"
#include "LobbyGoodsTypes.h"
#include "LobbyJob.h"
#include "LobbyJobParams.h"
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "Packet.h"
#include "PacketUtil.h"
#include "StringUtil.h"

extern wchar_t const* LobbyErrorDesc[28];  // LIFT: PDB public LobbyErrorDesc (.data 0003:2032), defined in LobbyGamePacketHandler.cpp (placeholder, owner module not found).

namespace
{
wchar_t const* const AIL_FILE = L"AccountInventoryLobbyPacketHandler.cpp";  // LIFT: No PDB symbol. The binary uses the literal as the file string of the log calls (first use at 0x87d0).

// LIFT: The binary sets the decomposer fields by hand in each handler (0xa160, 0xa680, 0xa780): len = strlen(format), index = 1, offset = 2.
void setupDecomposer(PacketDecomposer& pdr, char const* format, int len)
{
    pdr.format = format;
    pdr.len = len;
    pdr.index = 1;
    pdr.offset = 2;
}

// LIFT: lift helper, not in the PDB. The binary inlines the repeat step after each repeated element: index = start[top] + 1; --counts[top].
__forceinline void repeatNext(PacketConcatenateBuffer* pcb)
{
    pcb->decomposer.index = pcb->decomposer.start[pcb->decomposer.top] + 1;
    --pcb->decomposer.counts[pcb->decomposer.top];
}

// LIFT: lift helper, not in the PDB. The PDB gives PushRepeatCount a short return value. The callers sign-extend it.
__forceinline short pushRepeatCount(PacketConcatenateBuffer* pcb)
{
    return static_cast<short>(
        pcb->decomposer.PushRepeatCount(&pcb->buffer[pcb->decomposer.offset], pcb->size - pcb->decomposer.offset));
}
}

// The game-account-id log arguments: id1 id2 id3 id4[0..7] (format %08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X).
// LIFT: lift-only macro, as in AccountInventoryChannel.cpp.
#define AIL_GUID_ARGS(a)                                                                                            \
    (a).guid.id1, (a).guid.id2, (a).guid.id3, (a).guid.id4[0], (a).guid.id4[1], (a).guid.id4[2], (a).guid.id4[3], \
        (a).guid.id4[4], (a).guid.id4[5], (a).guid.id4[6], (a).guid.id4[7]

// 0x87d0
bool HandleAccountInventoryLobby_HelloOk(SharedChannel*, Packet const*)
{
    void* const event = LobbyDaemon::_instance->_accountInventoryInitialConnectEvent.Event;
    if (event != nullptr)
        SetEvent(event);
    Log::Write(Log::LT_DEBUG, AIL_FILE, 29, L"[account-inventory], handle hello ok ok");
    return true;
}

// 0x8820
bool HandleAccountInventoryLobby_HelloFail(SharedChannel* channel, Packet const* packet)
{
    short cmd = 0;
    short reason = 0;
    if (packet->Decompose("hh", &cmd, &reason) == 0)
        Log::Write(Log::LT_ERROR, AIL_FILE, 45,
                   L"[account-inventory], handle hello fail fail; decompose fail, cmd:%d, reason:%d",
                   static_cast<int>(cmd), static_cast<int>(reason));
    else
        Log::Write(Log::LT_DEBUG, AIL_FILE, 49, L"[account-inventory], handle hello fail ok, cmd:%d, reason:%d",
                   static_cast<int>(cmd), static_cast<int>(reason));
    return false;
}

// 0x88b0
bool HandleAccountInventoryLobby_GetGoodsCountOk(SharedChannel* channel, Packet const* packet)
{
    short cmd = 0;
    unsigned long long tid = 0;
    int count = 0;
    if (packet->Decompose("hqi", &cmd, &tid, &count) == 0)
    {
        Log::Write(Log::LT_ERROR, AIL_FILE, 66,
                   L"[account-inventory], handle get goods count ok fail; decompose fail, cmd:%d, tid:0x%I64X, count:%d",
                   static_cast<int>(cmd), tid, count);
        return true;
    }
    if (!LobbyDaemon::_instance->_jobMgr->ExecuteW(tid, 144, &count))
    {
        // BUG: 0x88b0 the log text has the typo "acocunt". Kept for parity.
        Log::Write(Log::LT_ERROR, AIL_FILE, 72,
                   L"[acocunt-inventory], handle get goods count ok fail; execute job fail, cmd:%d, tid:0x%I64X, count:%d",
                   static_cast<int>(cmd), tid, count);
        return true;
    }
    Log::Write(Log::LT_DEBUG, AIL_FILE, 76,
               L"[account-inventory], handle get goods count ok ok, cmd:%d, tid:0x%I64X, count:%d",
               static_cast<int>(cmd), tid, count);
    return true;
}

// 0x8ad0
bool HandleAccountInventoryLobby_GetGoodsCountFail(SharedChannel* channel, Packet const* packet)
{
    short cmd = 0;
    unsigned long long tid = 0;
    short reason = 0;
    if (packet->Decompose("hqE", &cmd, &tid, &reason) == 0)
    {
        Log::Write(Log::LT_ERROR, AIL_FILE, 94,
                   L"[account-inventory], handle get goods count fail fail; decompose fail, cmd:%d, tid:0x%I64X, reason:%d",
                   static_cast<int>(cmd), tid, static_cast<int>(reason));
        return true;
    }
    if (!LobbyDaemon::_instance->_jobMgr->ExecuteW(tid, 145, &reason))
    {
        // BUG: 0x8ad0 the log text has the typo "acocunt". Kept for parity.
        Log::Write(Log::LT_ERROR, AIL_FILE, 100,
                   L"[acocunt-inventory], handle get goods count fail fail; execute job fail, cmd:%d, tid:0x%I64X, reason:%d",
                   static_cast<int>(cmd), tid, static_cast<int>(reason));
        return true;
    }
    Log::Write(Log::LT_DEBUG, AIL_FILE, 104,
               L"[account-inventory], handle get goods count ok fail, cmd:%d, tid:0x%I64X, reason:%d",
               static_cast<int>(cmd), tid, static_cast<int>(reason));
    return true;
}

// 0x8d00
bool HandleAccountInventoryLobby_ListGoodsOk(SharedChannel* channel, FragmentPacketConcatenater* fpc)
{
    ListGoodsOkParam param = {};
    unsigned long long tid = 0;
    PacketConcatenateBuffer::VarData goodsRestrictionCondition;
    PacketConcatenateBuffer::VarData customizedGoodsAttribute;
    PacketConcatenateBuffer::VarData customizedItemAttribute_1;
    PacketConcatenateBuffer::VarData customizedItemAttribute_2;

    fpc->decomposer.SetFormat("hiqCqiQQqqssissbbCiiibb;;", 2);
    if (!fpc->Decompose(1, &tid))
    {
        Log::Write(Log::LT_ERROR, AIL_FILE, 124,
                   L"[account-inventory], handle list goods ok fail; decompose tid fail, tid:0x%I64X, goods-count:%d", tid,
                   param.goodsCount);
        goto cleanup;
    }

    param.goodsCount = pushRepeatCount(fpc);
    if (param.goodsCount > 0)
    {
        param.goodsList = static_cast<Goods*>(
            Memory::_Manager[2]->AllocZero(sizeof(Goods) * param.goodsCount, AIL_FILE, 132));
        for (int i = 0; i < param.goodsCount; ++i)
        {
            Goods& goods = param.goodsList[i];
            if (!fpc->Decompose(11, &goods.goodsId, &goods.goodsNumber, &goods.isRefundable,
                                &goods.useRefundExpirationDate, &goods.refundExpirationDate, &goods.deliveryDate,
                                goods.senderDesc, 51, goods.senderMessage, 81, &goods.goodsIconId, goods.goodsName, 81,
                                goods.goodsDesc, 201))
            {
                Log::Write(Log::LT_ERROR, AIL_FILE, 154,
                           L"[account-inventory], handle list goods ok fail; decompose goods #%d body fail, tid:0x%I64X, goods-count:%d",
                           i, tid, param.goodsCount);
                goto cleanup;
            }
            if (fpc->Decompose(&goodsRestrictionCondition) == 0)
            {
                Log::Write(Log::LT_ERROR, AIL_FILE, 160,
                           L"[account-inventory], handle list goods ok fail; decompose goods #%d goods-restriction-condition fail, tid:0x%I64X, goods-count:%d",
                           i, tid, param.goodsCount);
                goto cleanup;
            }
            if (fpc->Decompose(&customizedGoodsAttribute) == 0)
            {
                Log::Write(Log::LT_ERROR, AIL_FILE, 166,
                           L"[account-inventory], handle list goods ok fail; decompose goods #%d customized-goods-attribute fail, tid:0x%I64X, goods-count:%d",
                           i, tid, param.goodsCount);
                goto cleanup;
            }
            if (*goodsRestrictionCondition.size > 0)
            {
                goods.goodsRestrictionCondition =
                    static_cast<char*>(Memory::_Manager[2]->AllocZero(*goodsRestrictionCondition.size, AIL_FILE, 172));
                goods.goodsRestrictionConditionSize = *goodsRestrictionCondition.size;
                memcpy(goods.goodsRestrictionCondition, goodsRestrictionCondition.buffer, *goodsRestrictionCondition.size);
            }
            if (*customizedGoodsAttribute.size > 0)
            {
                goods.customizedGoodsAttribute =
                    static_cast<char*>(Memory::_Manager[2]->AllocZero(*customizedGoodsAttribute.size, AIL_FILE, 179));
                goods.customizedGoodsAttributeSize = *customizedGoodsAttribute.size;
                memcpy(goods.customizedGoodsAttribute, customizedGoodsAttribute.buffer, *customizedGoodsAttribute.size);
            }

            goods.goodsItemCount = pushRepeatCount(fpc);
            if (goods.goodsItemCount > 0)
            {
                goods.goodsItemList = static_cast<GoodsItem*>(
                    Memory::_Manager[2]->AllocZero(sizeof(GoodsItem) * goods.goodsItemCount, AIL_FILE, 187));
                for (int j = 0; j < goods.goodsItemCount; ++j)
                {
                    GoodsItem& item = goods.goodsItemList[j];
                    if (!fpc->Decompose(3, &item.itemNumber, &item.itemAmount, &item.itemDataId))
                    {
                        Log::Write(Log::LT_ERROR, AIL_FILE, 197,
                                   L"[account-inventory], handle list goods ok fail; decompose goods #%d goods-item #%d body fail, tid:0x%I64X, goods-count:%d",
                                   i, j, tid, param.goodsCount);
                        goto cleanup;
                    }
                    if (fpc->Decompose(&customizedItemAttribute_1) == 0)
                    {
                        Log::Write(Log::LT_ERROR, AIL_FILE, 203,
                                   L"[account-inventory], handle list goods ok fail; decompose goods #%d goods-item #%d customized-item-attribute-1 fail, tid:0x%I64X, goods-count:%d",
                                   i, j, tid, param.goodsCount);
                        goto cleanup;
                    }
                    if (fpc->Decompose(&customizedItemAttribute_2) == 0)
                    {
                        Log::Write(Log::LT_ERROR, AIL_FILE, 209,
                                   L"[account-inventory], handle list goods ok fail; decompose goods #%d goods-item #%d customized-item-attribute-2 fail, tid:0x%I64X, goods-count:%d",
                                   i, j, tid, param.goodsCount);
                        goto cleanup;
                    }
                    if (*customizedItemAttribute_1.size > 0)
                    {
                        item.customizedItemAttribute_1 = static_cast<char*>(
                            Memory::_Manager[2]->AllocZero(*customizedItemAttribute_1.size, AIL_FILE, 215));
                        item.customizedItemAttribute_1_Size = *customizedItemAttribute_1.size;
                        memcpy(item.customizedItemAttribute_1, customizedItemAttribute_1.buffer,
                               *customizedItemAttribute_1.size);
                    }
                    if (*customizedItemAttribute_2.size > 0)
                    {
                        item.customizedItemAttribute_2 = static_cast<char*>(
                            Memory::_Manager[2]->AllocZero(*customizedItemAttribute_2.size, AIL_FILE, 222));
                        item.customizedItemAttribute_2_Size = *customizedItemAttribute_2.size;
                        memcpy(item.customizedItemAttribute_2, customizedItemAttribute_2.buffer,
                               *customizedItemAttribute_2.size);
                    }
                    repeatNext(fpc);
                }
            }
            fpc->decomposer.PopRepeatCount();
            repeatNext(fpc);
        }
    }
    fpc->decomposer.PopRepeatCount();

    if (!LobbyDaemon::_instance->_jobMgr->ExecuteW(tid, 147, &param))
        Log::Write(Log::LT_ERROR, AIL_FILE, 239,
                   L"[account-inventory], handle list goods ok fail; execute job fail, tid:0x%I64X, goods-count:%d", tid,
                   param.goodsCount);
    else
        Log::Write(Log::LT_DEBUG, AIL_FILE, 243,
                   L"[account-inventory], handle list goods ok ok, tid:0x%I64X, goods-count:%d", tid, param.goodsCount);

cleanup:
    // The job copies the goods. The handler frees its own copy on every path.
    if (param.goodsList != nullptr)
    {
        for (int i = 0; i < param.goodsCount; ++i)
        {
            Goods& goods = param.goodsList[i];
            if (goods.goodsRestrictionCondition != nullptr)
            {
                Memory::_Manager[2]->Free(goods.goodsRestrictionCondition, AIL_FILE, 252);
                goods.goodsRestrictionCondition = nullptr;
            }
            if (goods.customizedGoodsAttribute != nullptr)
            {
                Memory::_Manager[2]->Free(goods.customizedGoodsAttribute, AIL_FILE, 254);
                goods.customizedGoodsAttribute = nullptr;
            }
            if (goods.goodsItemList != nullptr)
            {
                for (int j = 0; j < goods.goodsItemCount; ++j)
                {
                    GoodsItem& item = goods.goodsItemList[j];
                    if (item.customizedItemAttribute_1 != nullptr)
                    {
                        Memory::_Manager[2]->Free(item.customizedItemAttribute_1, AIL_FILE, 260);
                        item.customizedItemAttribute_1 = nullptr;
                    }
                    if (item.customizedItemAttribute_2 != nullptr)
                    {
                        Memory::_Manager[2]->Free(item.customizedItemAttribute_2, AIL_FILE, 262);
                        item.customizedItemAttribute_2 = nullptr;
                    }
                }
                Memory::_Manager[2]->Free(goods.goodsItemList, AIL_FILE, 264);
            }
        }
        Memory::_Manager[2]->Free(param.goodsList, AIL_FILE, 267);
    }
    return true;
}

// 0x9550
bool HandleAccountInventoryLobby_ListGoodsFail(SharedChannel* channel, Packet const* packet)
{
    short cmd = 0;
    unsigned long long tid = 0;
    short reason = 0;
    if (packet->Decompose("hqE", &cmd, &tid, &reason) == 0)
    {
        Log::Write(Log::LT_ERROR, AIL_FILE, 286,
                   L"[account-inventory], handle list goods fail fail; decompose fail, tid:0x%I64X, reason:%d", tid,
                   static_cast<int>(reason));
        return true;
    }
    if (!LobbyDaemon::_instance->_jobMgr->ExecuteW(tid, 148, &reason))
    {
        Log::Write(Log::LT_ERROR, AIL_FILE, 292,
                   L"[account-inventory], handle list goods fail fail; execute job fail, tid:0x%I64X, reason:%d", tid,
                   static_cast<int>(reason));
        return true;
    }
    Log::Write(Log::LT_DEBUG, AIL_FILE, 296, L"[account-inventory], handle list goods fail ok, tid:0x%I64X, reason:%d",
               tid, static_cast<int>(reason));
    return true;
}

// 0x9750
bool HandleAccountInventoryLobby_TakeGoodsOk(SharedChannel* channel, FragmentPacketConcatenater* fpc)
{
    TakeGoodsOkParam param = {};
    unsigned long long tid = 0;

    fpc->decomposer.SetFormat("hiqCqqqiQ;", 2);
    if (!fpc->Decompose(1, &tid))
    {
        Log::Write(Log::LT_ERROR, AIL_FILE, 318,
                   L"[account-inventory], handle take-goods ok fail; decompose item tid fail, tid:0x%I64X, item-count:%d",
                   tid, param.itemCount);
    }
    else
    {
        param.itemCount = pushRepeatCount(fpc);
        if (param.itemCount > 0)
        {
            param.items = static_cast<LobbyServiceItem*>(
                Memory::_Manager[2]->AllocZero(sizeof(LobbyServiceItem) * param.itemCount, AIL_FILE, 326));
            for (int i = 0; i < param.itemCount; ++i)
            {
                LobbyServiceItem& item = param.items[i];
                if (!fpc->Decompose(5, &item.ownerPcId, &item.instanceId, &item.labelId, &item.dataId, &item.state))
                {
                    Log::Write(Log::LT_ERROR, AIL_FILE, 340,
                               L"[account-inventory], handle take-goods ok fail; decompose item #%d body fail, tid:0x%I64X, item-count:%d",
                               i, tid, param.itemCount);
                    goto cleanup;
                }
                repeatNext(fpc);
            }
        }
        fpc->decomposer.PopRepeatCount();

        if (!LobbyDaemon::_instance->_jobMgr->ExecuteW(tid, 150, &param))
            Log::Write(Log::LT_ERROR, AIL_FILE, 352,
                       L"[account-inventory], handle take-goods ok fail; start job fail, tid:0x%I64X, item-count:%d", tid,
                       param.itemCount);
        else
            Log::Write(Log::LT_DEBUG, AIL_FILE, 356,
                       L"[account-inventory], handle take-goods ok ok, tid:0x%I64X, item-count:%d", tid, param.itemCount);
    }

cleanup:
    if (param.items != nullptr)
        Memory::_Manager[2]->Free(param.items, AIL_FILE, 361);
    return true;
}

// 0x9a60
bool HandleAccountInventoryLobby_TakeGoodsFail(SharedChannel* channel, Packet const* packet)
{
    short cmd = 0;
    unsigned long long tid = 0;
    short reason = 0;
    if (packet->Decompose("hqE", &cmd, &tid, &reason) == 0)
    {
        Log::Write(Log::LT_ERROR, AIL_FILE, 380,
                   L"[account-inventory], handle take goods fail fail; decompose fail, tid:0x%I64X, reason:%d", tid,
                   static_cast<int>(reason));
        return true;
    }
    if (!LobbyDaemon::_instance->_jobMgr->ExecuteW(tid, 151, &reason))
    {
        Log::Write(Log::LT_ERROR, AIL_FILE, 386,
                   L"[account-inventory], handle take goods fail fail; execute job fail, tid:0x%I64X, reason:%d", tid,
                   static_cast<int>(reason));
        return true;
    }
    Log::Write(Log::LT_DEBUG, AIL_FILE, 390, L"[account-inventory], handle take goods fail ok, tid:0x%I64X, reason:%d",
               tid, static_cast<int>(reason));
    return true;
}

// 0x9c60
bool HandleAccountInventoryLobby_RetrieveLobbyServiceItemListOk(SharedChannel* channel, FragmentPacketConcatenater* fpc)
{
    RetrieveLobbyServiceItemListOkParam param;
    memset(&param, 0, sizeof(param));
    unsigned long long tid = 0;

    fpc->decomposer.SetFormat("hiqiCqqqiQ;", 2);
    // BUG: 0x9c60 the result of this Decompose is not checked. Kept for parity.
    fpc->Decompose(2, &tid, &param.searchCount);
    param.itemCount = pushRepeatCount(fpc);
    if (param.itemCount > 0)
    {
        param.items = static_cast<LobbyServiceItem*>(
            Memory::_Manager[2]->AllocZero(sizeof(LobbyServiceItem) * param.itemCount, AIL_FILE, 416));
        for (int i = 0; i < param.itemCount; ++i)
        {
            LobbyServiceItem& item = param.items[i];
            if (!fpc->Decompose(5, &item.ownerPcId, &item.instanceId, &item.labelId, &item.dataId, &item.state))
            {
                Log::Write(Log::LT_ERROR, AIL_FILE, 429,
                           L"[account-inventory], handle retrieve lobby serivce item list ok fail; decompose item #%d body fail, tid:0x%I64X, search-count:%d,  item-count:%d",
                           i, tid, param.searchCount, param.itemCount);
                goto cleanup;
            }
            repeatNext(fpc);
        }
    }
    fpc->decomposer.PopRepeatCount();

    if (!LobbyDaemon::_instance->_jobMgr->ExecuteW(tid, 153, &param))
        Log::Write(Log::LT_ERROR, AIL_FILE, 440,
                   L"[account-inventory], handle retrieve lobby serivce item list ok fail; start job fail, tid:0x%I64X, search-count:%d,  item-count:%d",
                   tid, param.searchCount, param.itemCount);
    else
        Log::Write(Log::LT_DEBUG, AIL_FILE, 444,
                   L"[account-inventory], handle retrieve lobby serivce item list ok ok, tid:0x%I64X, search-count:%d,  item-count:%d",
                   tid, param.searchCount, param.itemCount);

cleanup:
    if (param.items != nullptr)
        Memory::_Manager[2]->Free(param.items, AIL_FILE, 449);
    return true;
}

// 0x9f60
bool HandleAccountInventoryLobby_RetrieveLobbyServiceItemListFail(SharedChannel* channel, Packet const* packet)
{
    short cmd = 0;
    unsigned long long tid = 0;
    short reason = 0;
    if (packet->Decompose("hqE", &cmd, &tid, &reason) == 0)
    {
        Log::Write(Log::LT_ERROR, AIL_FILE, 467,
                   L"[account-inventory], handle retrieve lobby service item list fail; decompose fail, tid:0x%I64X, reason:%d",
                   tid, static_cast<int>(reason));
        return true;
    }
    if (!LobbyDaemon::_instance->_jobMgr->ExecuteW(tid, 154, &reason))
    {
        Log::Write(Log::LT_ERROR, AIL_FILE, 472,
                   L"[account-inventory], handle retrieve lobby service item list fail; start job fail, tid:0x%I64X, reason:%d",
                   tid, static_cast<int>(reason));
        return true;
    }
    Log::Write(Log::LT_DEBUG, AIL_FILE, 476,
               L"[account-inventory], handle retrieve lobby service item list fail ok, tid:0x%I64X, reason:%d", tid,
               static_cast<int>(reason));
    return true;
}

// 0xa160
bool HandleAccountInventoryLobby_RetrieveSingleWarehouseItemOk(SharedChannel* channel, Packet const* packet)
{
    LobbyServiceItem item;
    memset(&item, 0, sizeof(item));
    RetrieveSingleWarehouseItemOkParam param;
    param.item = nullptr;
    PacketDecomposer pdr;
    setupDecomposer(pdr, "hqqqqiQ", 7);
    unsigned long long tid = 0;
    if (packet->Decompose(&pdr, 6, &tid, &item.ownerPcId, &item.instanceId, &item.labelId, &item.dataId, &item.state) ==
        0)
    {
        Log::Write(Log::LT_ERROR, AIL_FILE, 498,
                   L"[account-inventory], handle retrieve single warehouse item fail; decompose fail, tid:0x%I64X, pcid:0x%I64X, item-instance-id:0x%I64X, label-id:0x%I64X, item-data-id:%u, state:%d",
                   tid, item.ownerPcId, item.instanceId, item.labelId, item.dataId, static_cast<int>(item.state));
        return true;
    }
    param.item = &item;
    if (!LobbyDaemon::_instance->_jobMgr->ExecuteW(tid, 156, &param))
    {
        Log::Write(Log::LT_ERROR, AIL_FILE, 505,
                   L"[account-inventory], handle retrieve single warehouse item fail; execute job fail, tid:0x%I64X, pcid:0x%I64X, item-instance-id:0x%I64X, label-id:0x%I64X, item-data-id:%u, state:%d",
                   tid, item.ownerPcId, item.instanceId, item.labelId, item.dataId, static_cast<int>(item.state));
        return true;
    }
    Log::Write(Log::LT_DEBUG, AIL_FILE, 509,
               L"[account-inventory], handle retrieve single warehouse item ok, tid:0x%I64X, pcid:0x%I64X, item-instance-id:0x%I64X, label-id:0x%I64X, item-data-id:%u, state:%d",
               tid, item.ownerPcId, item.instanceId, item.labelId, item.dataId, static_cast<int>(item.state));
    return true;
}

// LIFT: lift-only macro for the 4 warehouse fail handlers (0xa440, 0xa780, 0xaac0, 0xae80).
// Each one decomposes "hqE" with a PacketDecomposer and starts the job with the reason.
#define AIL_PDR_REASON_HANDLER(reasonInit, task, decLine, decText, execLine, execText, okLine, okText)                 \
    PacketDecomposer pdr;                                                                                         \
    setupDecomposer(pdr, "hqE", 3);                                                                               \
    unsigned long long tid = 0;                                                                                   \
    short reason = reasonInit;                                                                                    \
    if (packet->Decompose(&pdr, 2, &tid, &reason) == 0)                                                           \
    {                                                                                                             \
        Log::Write(Log::LT_ERROR, AIL_FILE, decLine, decText, tid, static_cast<int>(reason));                     \
        return true;                                                                                              \
    }                                                                                                             \
    if (!LobbyDaemon::_instance->_jobMgr->ExecuteW(tid, task, &reason))                                           \
    {                                                                                                             \
        Log::Write(Log::LT_ERROR, AIL_FILE, execLine, execText, tid, static_cast<int>(reason));                   \
        return true;                                                                                              \
    }                                                                                                             \
    Log::Write(Log::LT_DEBUG, AIL_FILE, okLine, okText, tid, static_cast<int>(reason));                           \
    return true

// LIFT: lift-only macro for the 3 warehouse ok handlers with only a tid (0xa680, 0xa9c0, 0xad80).
#define AIL_PDR_TID_HANDLER(task, decLine, decText, execLine, execText, okLine, okText)                            \
    PacketDecomposer pdr;                                                                                         \
    setupDecomposer(pdr, "hq", 2);                                                                                \
    unsigned long long tid = 0;                                                                                   \
    if (packet->Decompose(&pdr, 1, &tid) == 0)                                                                    \
    {                                                                                                             \
        Log::Write(Log::LT_ERROR, AIL_FILE, decLine, decText, tid);                                               \
        return true;                                                                                              \
    }                                                                                                             \
    if (!LobbyDaemon::_instance->_jobMgr->ExecuteW(tid, task, nullptr))                                           \
        Log::Write(Log::LT_ERROR, AIL_FILE, execLine, execText, tid);                                             \
    else                                                                                                          \
        Log::Write(Log::LT_DEBUG, AIL_FILE, okLine, okText, tid);                                                 \
    return true

// 0xa440
bool HandleAccountInventoryLobby_RetrieveSingleWarehouseItemFail(SharedChannel* channel, Packet const* packet)
{
    AIL_PDR_REASON_HANDLER(
        0, 157, 527, L"[account-inventory], handle retrieve single warehouse item fail fail; decompose fail, tid:0x%I64X, reason:%d",
        532, L"[account-inventory], handle retrieve single warehouse item fail fail; start job fail, tid:0x%I64X, reason:%d",
        536, L"[account-inventory], handle retrieve single warehouse item fail ok, tid:0x%I64X, reason:%d");
}

// 0xa680
bool HandleAccountInventoryLobby_TryWarehouseItemConsumptionOk(SharedChannel* channel, Packet const* packet)
{
    AIL_PDR_TID_HANDLER(
        159, 611, L"[account-inventory], handle try warehouse item consumption ok fail; decompose fail, tid:0x%I64X",
        616, L"[account-inventory], handle try warehouse item consumption ok fail; execute job fail, tid:0x%I64X",
        620, L"[account-inventory], handle try warehouse item consumption ok ok, tid:0x%I64X");
}

// 0xa780
bool HandleAccountInventoryLobby_TryWarehouseItemConsumptionFail(SharedChannel* channel, Packet const* packet)
{
    AIL_PDR_REASON_HANDLER(
        1, 160, 638, L"[account-inventory], handle try warehouse item consumption fail fail; decompose fail, tid:0x%I64X, reason:%d",
        643, L"[account-inventory], handle try warehouse item consumption fail fail; execute job fail, tid:0x%I64X, reason:%d",
        647, L"[account-inventory], handle try warehouse item consumption fail ok, tid:0x%I64X, reason:%d");
}

// 0xa9c0
bool HandleAccountInventoryLobby_FinishWarehouseItemConsumptionOk(SharedChannel* channel, Packet const* packet)
{
    AIL_PDR_TID_HANDLER(
        162, 664, L"[account-inventory], handle finish warehouse item consumption ok fail; decompose fail, tid:0x%I64X",
        669, L"[account-inventory], handle finish warehouse item consumption ok fail; execute job fail, tid:0x%I64X",
        673, L"[account-inventory], handle finish warehouse item consumption ok ok, tid:0x%I64X");
}

// 0xaac0
bool HandleAccountInventoryLobby_FinishWarehouseItemConsumptionFail(SharedChannel* channel, Packet const* packet)
{
    AIL_PDR_REASON_HANDLER(
        1, 163, 691, L"[account-inventory], handle finish warehouse item consumption fail fail; decompose fail, tid:0x%I64X, reason:%d",
        696, L"[account-inventory], handle finish warehouse item consumption fail fail; execute job fail, tid:0x%I64X, reason:%d",
        700, L"[account-inventory], handle finish warehouse item consumption fail ok, tid:0x%I64X, reason:%d");
}

// 0xad00
bool HandleAccountInventoryLobby_CancelWarehouseItemConsumptionOk(SharedChannel*, Packet const*)
{
    Log::Write(Log::LT_ERROR, AIL_FILE, 705, L"[account-inventory], %s; N/A",
               L"HandleAccountInventoryLobby_CancelWarehouseItemConsumptionOk");
    return true;
}

// 0xad40
bool HandleAccountInventoryLobby_CancelWarehouseItemConsumptionFail(SharedChannel*, Packet const*)
{
    Log::Write(Log::LT_ERROR, AIL_FILE, 706, L"[account-inventory], %s; N/A",
               L"HandleAccountInventoryLobby_CancelWarehouseItemConsumptionFail");
    return true;
}

// 0xad80
bool HandleAccountInventoryLobby_ConsumeWarehouseItemOk(SharedChannel* channel, Packet const* packet)
{
    AIL_PDR_TID_HANDLER(165, 720, L"[account-inventory], handle consume-warehouse-item-ok fail; decompose fail, tid:0x%I64X",
                        725, L"[account-inventory], handle consume-warehouse-item-ok fail; execute job fail, tid:0x%I64X",
                        729, L"[account-inventory], handle consume-warehouse-item-ok ok, tid:0x%I64X");
}

// 0xae80
bool HandleAccountInventoryLobby_ConsumeWarehouseItemFail(SharedChannel* channel, Packet const* packet)
{
    AIL_PDR_REASON_HANDLER(
        1, 166, 746, L"[account-inventory], handle consume-warehouse-item-fail fail; decompose fail, tid:0x%I64X, reason:%d",
        751, L"[account-inventory], handle consume-warehouse-item-fail fail; execute job fail, tid:0x%I64X, reason:%d",
        755, L"[account-inventory], handle consume-warehouse-item-fail ok, tid:0x%I64X, reason:%d");
}

// 0xb0c0
bool HandleAccountInventoryLobby_RetrieveCharacterGoodsCountOk(SharedChannel* channel, Packet const* packet)
{
    GetCharacterGoodsCountOkParam param = {};
    short cmd = 0;
    unsigned long long tid = 0;
    if (packet->Decompose("hqii", &cmd, &tid, &param.goodsCount, &param.takedGoodsCount) == 0)
    {
        Log::Write(Log::LT_ERROR, AIL_FILE, 774,
                   L"[account-inventory], handle retrieve character goods count ok fail; decompose fail, cmd:%d, tid:0x%I64X, count:%d, taked-count:%d",
                   static_cast<int>(cmd), tid, param.goodsCount, param.takedGoodsCount);
        return true;
    }
    if (!LobbyDaemon::_instance->_jobMgr->ExecuteW(tid, 168, &param))
    {
        // BUG: 0xb0c0 the log text has the typo "acocunt". Kept for parity.
        Log::Write(Log::LT_ERROR, AIL_FILE, 780,
                   L"[acocunt-inventory], handle retrieve character goods count ok fail; execute job fail, cmd:%d, tid:0x%I64X, count:%d, taked-count:%d",
                   static_cast<int>(cmd), tid, param.goodsCount, param.takedGoodsCount);
        return true;
    }
    Log::Write(Log::LT_DEBUG, AIL_FILE, 784,
               L"[account-inventory], handle retrieve character goods count ok ok, cmd:%d, tid:0x%I64X, count:%d, taked-count:%d",
               static_cast<int>(cmd), tid, param.goodsCount, param.takedGoodsCount);
    return true;
}

// 0xb310
bool HandleAccountInventoryLobby_RetrieveCharacterGoodsCountFail(SharedChannel* channel, Packet const* packet)
{
    short cmd = 0;
    unsigned long long tid = 0;
    short reason = 0;
    if (packet->Decompose("hqE", &cmd, &tid, &reason) == 0)
    {
        Log::Write(Log::LT_ERROR, AIL_FILE, 802,
                   L"[account-inventory], handle retrieve character goods count fail fail; decompose fail, tid:0x%I64X, reason:%d",
                   tid, static_cast<int>(reason));
        return true;
    }
    if (!LobbyDaemon::_instance->_jobMgr->ExecuteW(tid, 169, &reason))
    {
        Log::Write(Log::LT_ERROR, AIL_FILE, 808,
                   L"[account-inventory], handle retrieve character goods count fail fail; execute job fail, tid:0x%I64X, reason:%d",
                   tid, static_cast<int>(reason));
        return true;
    }
    Log::Write(Log::LT_DEBUG, AIL_FILE, 812,
               L"[account-inventory], handle retrieve character goods count fail ok, tid:0x%I64X, reason:%d", tid,
               static_cast<int>(reason));
    return true;
}

// 0xb510
bool HandleAccountInventoryLobby_GoodsInventoryChangedNotify(SharedChannel* channel, FragmentPacketConcatenater* fpc)
{
    GoodsInventoryChangedNotifyParam param = {};
    id128 gameAccountId = {};
    CliSession* session;

    fpc->decomposer.SetFormat("hioQCqqi;Qqq", 2);
    // BUG: 0xb510 the results of the two plain Decompose calls are not checked. Kept for parity.
    fpc->Decompose(2, &gameAccountId, &param.changedActionType);
    param.itemCount = pushRepeatCount(fpc);
    if (param.itemCount > 0)
    {
        param.items = static_cast<CharacterInventoryItem*>(
            Memory::_Manager[2]->AllocZero(sizeof(CharacterInventoryItem) * param.itemCount, AIL_FILE, 838));
        for (int i = 0; i < param.itemCount; ++i)
        {
            CharacterInventoryItem& item = param.items[i];
            if (!fpc->Decompose(3, &item.instanceId, &item.labelId, &item.dataId))
            {
                // BUG: 0xb510 the log text names the retrieve-lobby-service-item-list handler. Kept for parity.
                Log::Write(Log::LT_ERROR, AIL_FILE, 849,
                           L"[account-inventory], handle retrieve lobby serivce item list ok fail; decompose item #%d body fail, cmd:%d, game-account-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, changed-action-type:%d",
                           i, 0, AIL_GUID_ARGS(gameAccountId), static_cast<int>(param.changedActionType));
                goto cleanup;
            }
            repeatNext(fpc);
        }
    }
    fpc->decomposer.PopRepeatCount();
    fpc->Decompose(3, &param.itemRemain, &param.goodsLabelIdMin, &param.goodsItemInsIdMin);

    session = LobbyDaemon::_instance->_clisessionMgr->Select_index_account(gameAccountId);
    if (session == nullptr)
    {
        Log::Write(Log::LT_DEBUG, AIL_FILE, 864,
                   L"[account-inventory], handle goods inventory changed notify fail; unknown account, cmd:%d, game-account-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, changed-action-type:%d",
                   0, AIL_GUID_ARGS(gameAccountId), static_cast<int>(param.changedActionType));
    }
    else if (session->NotifyGoodsInventoryChangedAlongPresence(param) || TLobbyError == LOBERR_INVALID_SESSION_STATE)
    {
        Log::Write(Log::LT_DEBUG, AIL_FILE, 879,
                   L"[account-inventory], handle goods inventory changed notify ok, cmd:%d, game-account-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, changed-action-type:%d",
                   0, AIL_GUID_ARGS(gameAccountId), static_cast<int>(param.changedActionType));
        session->removeReferenceCount(AIL_FILE, 881);
    }
    else
    {
        unsigned int const error = static_cast<unsigned int>(TLobbyError);
        wchar_t const* const desc = error >= 28 ? L"LOBERR_UNDEFINED" : LobbyErrorDesc[error];
        Log::Write(Log::LT_ERROR, AIL_FILE, 873,
                   L"[account-inventory], handle goods inventory changed notify fail, error:%s, cmd:%d, game-account-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, changed-action-type:%d",
                   desc, 0, AIL_GUID_ARGS(gameAccountId), static_cast<int>(param.changedActionType));
        session->removeReferenceCount(AIL_FILE, 874);
    }

cleanup:
    if (param.items != nullptr)
        Memory::_Manager[2]->Free(param.items, AIL_FILE, 886);
    return true;
}
