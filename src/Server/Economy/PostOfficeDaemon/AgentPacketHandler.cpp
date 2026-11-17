// AgentPacketHandler.obj (PostOfficeDaemon PDB). Source: .scratch/hr/AgentPacketHandler.c
// 0x1a6e0 AgentChannel::GetId and 0x1f620 ~AgentChannel are in AgentChannel.cpp.
#include <winsock2.h>
#include <windows.h>
#include <string.h>
#include <wchar.h>
#include <new>
#include "AgentPacketHandler.h"
#include "AgentChannel.h"
#include "AlertSender.h"
#include "CacheGateChannel.h"
#include "Log.h"
#include "Memory.h"
#include "Packet.h"
#include "PacketUtil.h"
#include "PostContext.h"
#include "PostOfficeDB.h"
#include "PostOfficeDaemon.h"
#include "Session.h"

namespace
{
wchar_t const* const AGENT_PACKET_HANDLER_FILE = L"AgentPacketHandler.cpp";  // LIFT: No PDB symbol. The binary uses the literal.
static wchar_t const* const MODULE_NAME = L"agent packet handler";  // PDB MODULE_NAME
}

// 0x1a6f0
bool HandlePostOfficeHelloReq(Session const* session, Packet const* packet)
{
    Log::Write(Log::LT_DEBUG, AGENT_PACKET_HANDLER_FILE, 38, L"[%s], %s; <BEGIN PACKET HANDLER>",
               MODULE_NAME, L"HandlePostOfficeHelloReq");
    short cmd = 0;
    short postofficePacketVersion = 0;
    short postofficeAgentPacketVersion = 0;
    short economyCommonPacketVersion = 0;
    unsigned short agentWid = 0;
    char connectionType = 0;
    short failReason = 0;
    void* memory = nullptr;
    AgentChannel* channel = nullptr;

    if (packet->Decompose("hhhhhQ", &cmd, &postofficePacketVersion, &postofficeAgentPacketVersion,
                          &economyCommonPacketVersion, &agentWid, &connectionType) == 0)
    {
        Log::Write(Log::LT_ERROR, AGENT_PACKET_HANDLER_FILE, 56, L"[%s], %s; failed to decompose packet",
                   MODULE_NAME, L"HandlePostOfficeHelloReq");
        failReason = 2;
        goto $_ERROR;
    }
    Log::Write(Log::LT_DEBUG, AGENT_PACKET_HANDLER_FILE, 61,
               L"[%s], %s; decomposed packet, postoffice-packet-version:%d, postofficeAgent-packet-version:%d, economy-common-packet-version:%d, agentWid:%u, connectionType:%d",
               MODULE_NAME, L"HandlePostOfficeHelloReq", static_cast<int>(postofficePacketVersion),
               static_cast<int>(postofficeAgentPacketVersion), static_cast<int>(economyCommonPacketVersion),
               static_cast<unsigned int>(agentWid), static_cast<int>(connectionType));
    if (connectionType != 0)
    {
        // 0x1a829-0x1a896: type 1 writes line 80 (0x50), other types write line 65 (0x41). Both give failReason 4.
        if (connectionType == 1)
            Log::Write(Log::LT_ERROR, AGENT_PACKET_HANDLER_FILE, 80,
                       L"[%s], %s; invalid connection type, agentWid:%u, connectionType:%d", MODULE_NAME,
                       L"HandlePostOfficeHelloReq", static_cast<unsigned int>(agentWid), 1);
        else
            Log::Write(Log::LT_ERROR, AGENT_PACKET_HANDLER_FILE, 65,
                       L"[%s], %s; invalid connection type, connectionType:%d", MODULE_NAME,
                       L"HandlePostOfficeHelloReq", static_cast<int>(connectionType));
        failReason = 4;
        goto $_ERROR;
    }
    if (postofficePacketVersion != 15 || economyCommonPacketVersion != 10)
    {
        Log::Write(Log::LT_ERROR, AGENT_PACKET_HANDLER_FILE, 73,
                   L"[%s], %s; invalid packet version, my postoffice-packet-version:%d, client version:%d, my economy-common-packet-version:%d, client version:%d",
                   MODULE_NAME, L"HandlePostOfficeHelloReq", 15, static_cast<int>(postofficePacketVersion),
                   10, static_cast<int>(economyCommonPacketVersion));
        failReason = 5;
        goto $_ERROR;
    }

    // LIFT: The inlined ctor writes WorldChannel::`vftable' (identical COMDAT folding with AgentChannel).
    memory = Memory::_Manager[2]->Alloc(sizeof(AgentChannel), AGENT_PACKET_HANDLER_FILE, 95);
    channel = memory != nullptr ? ::new (memory) AgentChannel(agentWid, connectionType) : nullptr;
    // BUG: 0x1a6f0 no null check after the Alloc. A failed Alloc gives a null call.
    channel->SetSession(session);
    channel->removeReferenceCount(AGENT_PACKET_HANDLER_FILE, 118);
    session->Send("h", 2);
    Log::Write(Log::LT_NOTICE, AGENT_PACKET_HANDLER_FILE, 121,
               L"[%s], %s; sent hello success ack, agentWid:%u, connectionType:%d", MODULE_NAME,
               L"HandlePostOfficeHelloReq", static_cast<unsigned int>(agentWid), static_cast<int>(connectionType));
    Log::Write(Log::LT_DEBUG, AGENT_PACKET_HANDLER_FILE, 123, L"[%s], %s; <END PACKET HANDLER>",
               MODULE_NAME, L"HandlePostOfficeHelloReq");
    return true;

$_ERROR:
    session->Send("hh", 3, static_cast<int>(failReason));
    Log::Write(Log::LT_NOTICE, AGENT_PACKET_HANDLER_FILE, 128,
               L"[%s], %s; sent hello failure ack, agentWid:%u, connectionType:%d, failReason:%d",
               MODULE_NAME, L"HandlePostOfficeHelloReq", static_cast<unsigned int>(agentWid),
               static_cast<int>(connectionType), static_cast<int>(failReason));
    Log::Write(Log::LT_DEBUG, AGENT_PACKET_HANDLER_FILE, 133, L"[%s], %s; <END PACKET HANDLER>",
               MODULE_NAME, L"HandlePostOfficeHelloReq");
    return false;
}

// The item log format of HandlePostOfficeRegisterPostReq. LIFT: the binary has one full literal per Log::Write call.
#define ITEM_LOG_ARGS L", tid:0x%I64X, invoiceId:0x%I64X, itemNo:%d, itemType:%d, itemCategory:%d, itemInstanceId:0x%I64X, itemDataId:%d, itemLevel:%d, itemAmount:%I64d, itemXmlData:%s"
#define POST_LOG_ARGS L", tid:0x%I64X, invoiceId:0x%I64X, postType:%d, deliveryReason:%d, postHint:0x%I64X, reservedHint:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, senderServiceType:%d, senderWid:%d, senderPcId:0x%I64X, senderAccountId:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, senderWorldName:%s, senderName:%s, recipientWid:%d, recipientPcId:0x%I64X, recipientName:%s, postTitle:%s, postMessage:%s"

// 0x1aaa0
bool HandlePostOfficeRegisterPostReq(Session const* session, Packet const* packet)
{
    Log::Write(Log::LT_DEBUG, AGENT_PACKET_HANDLER_FILE, 140, L"[%s], %s; <BEGIN PACKET HANDLER>",
               MODULE_NAME, L"HandlePostOfficeRegisterPostReq");
    // The fragment pump gives a PacketConcatenateBuffer in place of a Packet.
    PacketConcatenateBuffer* pcb = reinterpret_cast<PacketConcatenateBuffer*>(const_cast<Packet*>(packet));
    long long tid = 0;
    PostInfo postInfo;
    AttachedItemContext* attachedItemList = nullptr;
    short failReason = 2;
    short attachedItemCount = 0;
    int dbRetValue = 0;
    long long postId = 0;
    unsigned short recipientWid = 0;
    CacheGateChannel* cachegateChannel = nullptr;
    PostContext* postContext = nullptr;
    AttachedItemInfo itemInfo;
    int itemError = 0;

    pcb->decomposer.SetFormat("hiqqQcqoQhqosshqsssCQQqihqs;", 2);
    if (!pcb->Decompose(17, &tid, &postInfo._invoiceId, &postInfo._postType, &postInfo._deliveryReason,
                        &postInfo._postHint, &postInfo._reservedHint, &postInfo._senderServiceType,
                        &postInfo._senderWid, &postInfo._senderPcId, &postInfo._senderAccountId,
                        postInfo._senderWorldName, 33, postInfo._senderName, 33, &postInfo._recipientWid,
                        &postInfo._recipientPcId, postInfo._recipientName, 33, postInfo._postTitle, 65,
                        postInfo._postMessage, 1025))
    {
        Log::Write(Log::LT_ERROR, AGENT_PACKET_HANDLER_FILE, 194, L"[%s], %s; failed to decompose packet",
                   MODULE_NAME, L"HandlePostOfficeRegisterPostReq");
        goto $_ERROR;
    }
    Log::Write(Log::LT_DEBUG, AGENT_PACKET_HANDLER_FILE, 198, L"[%s], %s; decomposed post data packet" POST_LOG_ARGS,
               MODULE_NAME, L"HandlePostOfficeRegisterPostReq", tid, postInfo._invoiceId,
               static_cast<int>(postInfo._postType), static_cast<int>(postInfo._deliveryReason), postInfo._postHint,
               static_cast<unsigned int>(postInfo._reservedHint.guid.id1),
               static_cast<unsigned int>(postInfo._reservedHint.guid.id2),
               static_cast<unsigned int>(postInfo._reservedHint.guid.id3),
               static_cast<unsigned int>(postInfo._reservedHint.guid.id4[0]),
               static_cast<unsigned int>(postInfo._reservedHint.guid.id4[1]),
               static_cast<unsigned int>(postInfo._reservedHint.guid.id4[2]),
               static_cast<unsigned int>(postInfo._reservedHint.guid.id4[3]),
               static_cast<unsigned int>(postInfo._reservedHint.guid.id4[4]),
               static_cast<unsigned int>(postInfo._reservedHint.guid.id4[5]),
               static_cast<unsigned int>(postInfo._reservedHint.guid.id4[6]),
               static_cast<unsigned int>(postInfo._reservedHint.guid.id4[7]),
               static_cast<int>(postInfo._senderServiceType), static_cast<int>(postInfo._senderWid),
               postInfo._senderPcId, static_cast<unsigned int>(postInfo._senderAccountId.guid.id1),
               static_cast<unsigned int>(postInfo._senderAccountId.guid.id2),
               static_cast<unsigned int>(postInfo._senderAccountId.guid.id3),
               static_cast<unsigned int>(postInfo._senderAccountId.guid.id4[0]),
               static_cast<unsigned int>(postInfo._senderAccountId.guid.id4[1]),
               static_cast<unsigned int>(postInfo._senderAccountId.guid.id4[2]),
               static_cast<unsigned int>(postInfo._senderAccountId.guid.id4[3]),
               static_cast<unsigned int>(postInfo._senderAccountId.guid.id4[4]),
               static_cast<unsigned int>(postInfo._senderAccountId.guid.id4[5]),
               static_cast<unsigned int>(postInfo._senderAccountId.guid.id4[6]),
               static_cast<unsigned int>(postInfo._senderAccountId.guid.id4[7]), postInfo._senderWorldName,
               postInfo._senderName, static_cast<int>(postInfo._recipientWid), postInfo._recipientPcId,
               postInfo._recipientName, postInfo._postTitle, postInfo._postMessage);
    if (postInfo._postType <= 0 || !postInfo.CheckValidityPostData())
    {
        Log::Write(Log::LT_ERROR, AGENT_PACKET_HANDLER_FILE, 201, L"[%s], %s; invalid post data" POST_LOG_ARGS,
                   MODULE_NAME, L"HandlePostOfficeRegisterPostReq", tid, postInfo._invoiceId,
                   static_cast<int>(postInfo._postType), static_cast<int>(postInfo._deliveryReason),
                   postInfo._postHint, static_cast<unsigned int>(postInfo._reservedHint.guid.id1),
                   static_cast<unsigned int>(postInfo._reservedHint.guid.id2),
                   static_cast<unsigned int>(postInfo._reservedHint.guid.id3),
                   static_cast<unsigned int>(postInfo._reservedHint.guid.id4[0]),
                   static_cast<unsigned int>(postInfo._reservedHint.guid.id4[1]),
                   static_cast<unsigned int>(postInfo._reservedHint.guid.id4[2]),
                   static_cast<unsigned int>(postInfo._reservedHint.guid.id4[3]),
                   static_cast<unsigned int>(postInfo._reservedHint.guid.id4[4]),
                   static_cast<unsigned int>(postInfo._reservedHint.guid.id4[5]),
                   static_cast<unsigned int>(postInfo._reservedHint.guid.id4[6]),
                   static_cast<unsigned int>(postInfo._reservedHint.guid.id4[7]),
                   static_cast<int>(postInfo._senderServiceType), static_cast<int>(postInfo._senderWid),
                   postInfo._senderPcId, static_cast<unsigned int>(postInfo._senderAccountId.guid.id1),
                   static_cast<unsigned int>(postInfo._senderAccountId.guid.id2),
                   static_cast<unsigned int>(postInfo._senderAccountId.guid.id3),
                   static_cast<unsigned int>(postInfo._senderAccountId.guid.id4[0]),
                   static_cast<unsigned int>(postInfo._senderAccountId.guid.id4[1]),
                   static_cast<unsigned int>(postInfo._senderAccountId.guid.id4[2]),
                   static_cast<unsigned int>(postInfo._senderAccountId.guid.id4[3]),
                   static_cast<unsigned int>(postInfo._senderAccountId.guid.id4[4]),
                   static_cast<unsigned int>(postInfo._senderAccountId.guid.id4[5]),
                   static_cast<unsigned int>(postInfo._senderAccountId.guid.id4[6]),
                   static_cast<unsigned int>(postInfo._senderAccountId.guid.id4[7]), postInfo._senderWorldName,
                   postInfo._senderName, static_cast<int>(postInfo._recipientWid), postInfo._recipientPcId,
                   postInfo._recipientName, postInfo._postTitle, postInfo._postMessage);
        failReason = 6;
        goto $_ERROR;
    }

    attachedItemCount = static_cast<short>(pcb->decomposer.PushRepeatCount(
        &pcb->buffer[pcb->decomposer.offset], pcb->size - pcb->decomposer.offset));
    if (static_cast<unsigned int>(attachedItemCount) > 10)
    {
        Log::Write(Log::LT_ERROR, AGENT_PACKET_HANDLER_FILE, 208,
                   L"[%s], %s; invalid attached item count, attachedItemCount:%d, maxAttachedItemCount:%d",
                   MODULE_NAME, L"HandlePostOfficeRegisterPostReq", static_cast<int>(attachedItemCount), 10);
        failReason = 7;
        goto $_ERROR;
    }
    if (attachedItemCount > 0)
    {
        // 0x1aead-0x1aec6: Alloc(count * 0x828 + 8). The code stores no count and uses the raw pointer.
        attachedItemList = static_cast<AttachedItemContext*>(Memory::_Manager[2]->Alloc(
            sizeof(AttachedItemContext) * static_cast<long long>(attachedItemCount) + 8, AGENT_PACKET_HANDLER_FILE,
            214));
        if (attachedItemList != nullptr)
        {
            for (int i = 0; i < attachedItemCount; ++i)
            {
                attachedItemList[i]._itemNo = 0;
                attachedItemList[i]._itemType = 0;
                attachedItemList[i]._itemCategory = 0;
                attachedItemList[i]._itemInstanceId = 0;
                attachedItemList[i]._itemDataId = 0;
                attachedItemList[i]._itemLevel = 0;
                attachedItemList[i]._itemAmount = 0;
                memset(attachedItemList[i]._itemXmlData, 0, sizeof(attachedItemList[i]._itemXmlData));
            }
        }
    }

    for (int i = 0; i < attachedItemCount; ++i)
    {
        itemInfo._itemType = 0;
        itemInfo._itemCategory = 0;
        itemInfo._itemInstanceId = 0;
        itemInfo._itemDataId = 0;
        itemInfo._itemLevel = 0;
        itemInfo._itemAmount = 0;
        memset(itemInfo._itemXmlData, 0, sizeof(itemInfo._itemXmlData));
        itemInfo._itemNo = static_cast<char>(i + 1);
        if (!pcb->Decompose(7, &itemInfo._itemType, &itemInfo._itemCategory, &itemInfo._itemInstanceId,
                            &itemInfo._itemDataId, &itemInfo._itemLevel, &itemInfo._itemAmount,
                            itemInfo._itemXmlData, 1025))
        {
            Log::Write(Log::LT_ERROR, AGENT_PACKET_HANDLER_FILE, 227, L"[%s], %s; failed to decompose packet",
                       MODULE_NAME, L"HandlePostOfficeRegisterPostReq");
            failReason = 2;
            goto $_ERROR;
        }
        Log::Write(Log::LT_DEBUG, AGENT_PACKET_HANDLER_FILE, 231, L"[%s], %s; decomposed item data packet" ITEM_LOG_ARGS,
                   MODULE_NAME, L"HandlePostOfficeRegisterPostReq", tid, postInfo._invoiceId,
                   static_cast<int>(itemInfo._itemNo), static_cast<int>(itemInfo._itemType),
                   static_cast<int>(itemInfo._itemCategory), itemInfo._itemInstanceId, itemInfo._itemDataId,
                   static_cast<int>(itemInfo._itemLevel), itemInfo._itemAmount, itemInfo._itemXmlData);

        itemError = itemInfo._itemType <= 0 ? 1 : itemInfo.CheckValidityItemData();
        if (itemError != 0)
        {
            switch (itemError)
            {
            case 1:
                Log::Write(Log::LT_ERROR, AGENT_PACKET_HANDLER_FILE, 237, L"[%s], %s; invalid item data" ITEM_LOG_ARGS,
                           MODULE_NAME, L"HandlePostOfficeRegisterPostReq", tid, postInfo._invoiceId,
                           static_cast<int>(itemInfo._itemNo), static_cast<int>(itemInfo._itemType),
                           static_cast<int>(itemInfo._itemCategory), itemInfo._itemInstanceId, itemInfo._itemDataId,
                           static_cast<int>(itemInfo._itemLevel), itemInfo._itemAmount, itemInfo._itemXmlData);
                failReason = 7;
                break;
            case 2:
                Log::Write(Log::LT_ERROR, AGENT_PACKET_HANDLER_FILE, 241,
                           L"[%s], %s; invalid money item data" ITEM_LOG_ARGS, MODULE_NAME,
                           L"HandlePostOfficeRegisterPostReq", tid, postInfo._invoiceId,
                           static_cast<int>(itemInfo._itemNo), static_cast<int>(itemInfo._itemType),
                           static_cast<int>(itemInfo._itemCategory), itemInfo._itemInstanceId, itemInfo._itemDataId,
                           static_cast<int>(itemInfo._itemLevel), itemInfo._itemAmount, itemInfo._itemXmlData);
                failReason = 8;
                break;
            case 3:
                Log::Write(Log::LT_ERROR, AGENT_PACKET_HANDLER_FILE, 245,
                           L"[%s], %s; invalid default item data" ITEM_LOG_ARGS, MODULE_NAME,
                           L"HandlePostOfficeRegisterPostReq", tid, postInfo._invoiceId,
                           static_cast<int>(itemInfo._itemNo), static_cast<int>(itemInfo._itemType),
                           static_cast<int>(itemInfo._itemCategory), itemInfo._itemInstanceId, itemInfo._itemDataId,
                           static_cast<int>(itemInfo._itemLevel), itemInfo._itemAmount, itemInfo._itemXmlData);
                failReason = 9;
                break;
            case 4:
                Log::Write(Log::LT_ERROR, AGENT_PACKET_HANDLER_FILE, 249,
                           L"[%s], %s; invalid custom item data" ITEM_LOG_ARGS, MODULE_NAME,
                           L"HandlePostOfficeRegisterPostReq", tid, postInfo._invoiceId,
                           static_cast<int>(itemInfo._itemNo), static_cast<int>(itemInfo._itemType),
                           static_cast<int>(itemInfo._itemCategory), itemInfo._itemInstanceId, itemInfo._itemDataId,
                           static_cast<int>(itemInfo._itemLevel), itemInfo._itemAmount, itemInfo._itemXmlData);
                failReason = 10;
                break;
            case 5:
                Log::Write(Log::LT_ERROR, AGENT_PACKET_HANDLER_FILE, 253, L"[%s], %s; unknown item type" ITEM_LOG_ARGS,
                           MODULE_NAME, L"HandlePostOfficeRegisterPostReq", tid, postInfo._invoiceId,
                           static_cast<int>(itemInfo._itemNo), static_cast<int>(itemInfo._itemType),
                           static_cast<int>(itemInfo._itemCategory), itemInfo._itemInstanceId, itemInfo._itemDataId,
                           static_cast<int>(itemInfo._itemLevel), itemInfo._itemAmount, itemInfo._itemXmlData);
                failReason = 11;
                break;
            default:
                Log::Write(Log::LT_ERROR, AGENT_PACKET_HANDLER_FILE, 257, L"[%s], %s; unknown error" ITEM_LOG_ARGS,
                           MODULE_NAME, L"HandlePostOfficeRegisterPostReq", tid, postInfo._invoiceId,
                           static_cast<int>(itemInfo._itemNo), static_cast<int>(itemInfo._itemType),
                           static_cast<int>(itemInfo._itemCategory), itemInfo._itemInstanceId, itemInfo._itemDataId,
                           static_cast<int>(itemInfo._itemLevel), itemInfo._itemAmount, itemInfo._itemXmlData);
                failReason = 1;
                break;
            }
            goto $_ERROR;
        }

        // BUG: 0x1aaa0 if the Alloc at line 214 fails, this writes through a null attachedItemList.
        attachedItemList[i]._itemNo = itemInfo._itemNo;
        attachedItemList[i]._itemType = itemInfo._itemType;
        attachedItemList[i]._itemCategory = itemInfo._itemCategory;
        attachedItemList[i]._itemInstanceId = itemInfo._itemInstanceId;
        attachedItemList[i]._itemDataId = itemInfo._itemDataId;
        attachedItemList[i]._itemLevel = itemInfo._itemLevel;
        attachedItemList[i]._itemAmount = itemInfo._itemAmount;
        wcsncpy(attachedItemList[i]._itemXmlData, itemInfo._itemXmlData, 0x401);
        {
            // LIFT: inlined RepeatPacketDecomposer step to the next repeat.
            int const top = pcb->decomposer.top;
            pcb->decomposer.index = pcb->decomposer.start[top] + 1;
            --pcb->decomposer.counts[top];
        }
    }
    pcb->decomposer.PopRepeatCount();
    pcb->Clear();
    pcb = nullptr;

    dbRetValue = 0;
    if (!PostOfficeDB::RegisterPost(&dbRetValue, &postInfo, attachedItemList, attachedItemCount))
    {
        Log::Write(Log::LT_ERROR, AGENT_PACKET_HANDLER_FILE, 272,
                   L"[%s], %s; failed to register post, dbRetValue:%d, tid:0x%I64X, invoiceId:0x%I64X",
                   MODULE_NAME, L"HandlePostOfficeRegisterPostReq", dbRetValue, tid, postInfo._invoiceId);
        failReason = dbRetValue == 2 ? 12 : 3;
        goto $_ERROR;
    }

    postId = postInfo._postId;
    recipientWid = static_cast<unsigned short>(postInfo._recipientWid);
    postInfo._postStatus = 1;
    session->Send("hqq", 5, tid, postInfo._postId);
    Log::Write(Log::LT_NOTICE, AGENT_PACKET_HANDLER_FILE, 290,
               L"[%s], %s; sent post registration success ack, tid:0x%I64X, invoiceId:0x%I64X, postId:0x%I64X",
               MODULE_NAME, L"HandlePostOfficeRegisterPostReq", tid, postInfo._invoiceId, postId);

    cachegateChannel = PostOfficeDaemon::checkDestinationServiceState(recipientWid);
    if (cachegateChannel != nullptr)
    {
        void* const memory = Memory::_Manager[2]->Alloc(sizeof(PostContext), AGENT_PACKET_HANDLER_FILE, 296);
        if (memory != nullptr)
            postContext = ::new (memory) PostContext();
        // BUG: 0x1aaa0 no null check after the Alloc at line 296.
        postContext->_postInfo = postInfo;
        if (attachedItemCount > 0 && !postContext->InitAttachedItemInfo(attachedItemList, attachedItemCount))
        {
            Log::Write(Log::LT_ERROR, AGENT_PACKET_HANDLER_FILE, 300,
                       L"== CRASH == [%s], %s; exception occurred; failed to initialize attached item info, tid:0x%I64X, postId:0x%I64X",
                       MODULE_NAME, L"HandlePostOfficeRegisterPostReq", tid, postId);
            AlertSender::Write(AGENT_PACKET_HANDLER_FILE, 300,
                               L"== CRASH == [%s], %s; exception occurred; failed to initialize attached item info, tid:0x%I64X, postId:0x%I64X",
                               MODULE_NAME, L"HandlePostOfficeRegisterPostReq", tid, postId);
        }
        if (!PostOfficeDaemon::_instance->_postContextManager->AddContext(postContext))
        {
            Log::Write(Log::LT_ERROR, AGENT_PACKET_HANDLER_FILE, 304,
                       L"== CRASH == [%s], %s; exception occurred; failed to add post context, postId:0x%I64X",
                       MODULE_NAME, L"HandlePostOfficeRegisterPostReq", postId);
            AlertSender::Write(AGENT_PACKET_HANDLER_FILE, 304,
                               L"== CRASH == [%s], %s; exception occurred; failed to add post context, postId:0x%I64X",
                               MODULE_NAME, L"HandlePostOfficeRegisterPostReq", postId);
        }
        if (!PostDeliveryEvent::OccurEvent(postContext, cachegateChannel))
        {
            Log::Write(Log::LT_ERROR, AGENT_PACKET_HANDLER_FILE, 308,
                       L"[%s], %s; failed to occur post delivery event, postId:0x%I64X", MODULE_NAME,
                       L"HandlePostOfficeRegisterPostReq", postId);
            if (!PostOfficeDaemon::_instance->_postContextManager->RemoveContext(postId))
            {
                Log::Write(Log::LT_ERROR, AGENT_PACKET_HANDLER_FILE, 311,
                           L"== CRASH == [%s], %s; exception occurred; failed to remove post context, postId:0x%I64X",
                           MODULE_NAME, L"HandlePostOfficeRegisterPostReq", postId);
                AlertSender::Write(AGENT_PACKET_HANDLER_FILE, 311,
                                   L"== CRASH == [%s], %s; exception occurred; failed to remove post context, postId:0x%I64X",
                                   MODULE_NAME, L"HandlePostOfficeRegisterPostReq", postId);
            }
        }
        postContext->removeReferenceCount(AGENT_PACKET_HANDLER_FILE, 315);
        cachegateChannel->removeReferenceCount(AGENT_PACKET_HANDLER_FILE, 316);
    }
    else
    {
        Log::Write(Log::LT_ERROR, AGENT_PACKET_HANDLER_FILE, 320,
                   L"[%s], %s; cannot send deliver post relay request, recipientWid:%u, postId:0x%I64X",
                   MODULE_NAME, L"HandlePostOfficeRegisterPostReq", static_cast<unsigned int>(recipientWid),
                   postId);
        Memory::_Manager[2]->Free(attachedItemList, AGENT_PACKET_HANDLER_FILE, 321);
        if (!PostOfficeDaemon::_instance->_unsentPostContextManager->RegisterUnsentPost(recipientWid, postId, false))
            Log::Write(Log::LT_ERROR, AGENT_PACKET_HANDLER_FILE, 324,
                       L"[%s], %s; exception occurred; failed to register unsent post, recipientWid:%u, postId:0x%I64X",
                       MODULE_NAME, L"HandlePostOfficeRegisterPostReq",
                       static_cast<unsigned int>(recipientWid), postId);
    }
    Log::Write(Log::LT_DEBUG, AGENT_PACKET_HANDLER_FILE, 328, L"[%s], %s; <END PACKET HANDLER>",
               MODULE_NAME, L"HandlePostOfficeRegisterPostReq");
    return true;

$_ERROR:
    session->Send("hqqE", 6, tid, postInfo._postId, static_cast<int>(failReason));
    Log::Write(Log::LT_NOTICE, AGENT_PACKET_HANDLER_FILE, 333,
               L"[%s], %s; sent post registration failure ack, tid:0x%I64X, postId:0x%I64X, failReason:%d",
               MODULE_NAME, L"HandlePostOfficeRegisterPostReq", tid, postInfo._postId,
               static_cast<int>(failReason));
    if (pcb != nullptr)
        pcb->Clear();
    if (attachedItemList != nullptr)
        Memory::_Manager[2]->Free(attachedItemList, AGENT_PACKET_HANDLER_FILE, 338);
    Log::Write(Log::LT_DEBUG, AGENT_PACKET_HANDLER_FILE, 340, L"[%s], %s; <END PACKET HANDLER>",
               MODULE_NAME, L"HandlePostOfficeRegisterPostReq");
    return true;
}

#undef ITEM_LOG_ARGS
#undef POST_LOG_ARGS
