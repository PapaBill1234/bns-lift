// WorldPacketHandler.obj (PostOfficeDaemon PDB). Source: .scratch/hr/WorldPacketHandler.c
#include <winsock2.h>
#include <windows.h>
#include <string.h>
#include <wchar.h>
#include <new>
#include "WorldPacketHandler.h"
#include "AlertSender.h"
#include "CacheGateChannel.h"
#include "Log.h"
#include "Memory.h"
#include "Network.h"
#include "Packet.h"
#include "PacketUtil.h"
#include "PostContext.h"
#include "PostOfficeDB.h"
#include "PostOfficeDaemon.h"
#include "Session.h"
#include "WorldChannel.h"
#include "WorldConfig.h"
#include "PostOfficeServicePacketCommand.h"

namespace
{
wchar_t const* const WORLD_PACKET_HANDLER_FILE = L"WorldPacketHandler.cpp";  // LIFT: No PDB symbol. The binary uses the literal.
static wchar_t const* const MODULE_NAME = L"world packet handler";  // PDB MODULE_NAME

// LIFT: inline of the RelayContextManager id generator
unsigned long long liftNextRelayTid()
{
    long long volatile* const idSeed = reinterpret_cast<long long volatile*>(&RelayContextManager::_idSeed);
    unsigned long long relayTid = static_cast<unsigned long long>(InterlockedIncrement64(idSeed));
    if (relayTid == 0)
        relayTid = static_cast<unsigned long long>(InterlockedIncrement64(idSeed));
    return relayTid;
}
}

// 0x1f650
RetrieveCharacterInfoRelayContext::RetrieveCharacterInfoRelayContext(EconomyHeader const& economyHeader,
                                                                     RetrieveCharacterInfoRelayRequest const& request)
    : RelayContext(economyHeader), _request(request)
{
    _response._resultState = RelayResponse::RESULTSTATE_INVALID;
    _response._failReason = 0;
    _response._resultPcId = 0;
}

// 0x1f770
void RetrieveCharacterInfoRelayContext::initResponse(RelayResponse* const response)
{
    static_cast<RelayResponse&>(_response) = *response;
    _response._resultPcId = static_cast<RetrieveCharacterInfoRelayResponse*>(response)->_resultPcId;
}

// 0x1f800
unsigned short const CheckPostCapacityRelayContext::GetRequestWid() const
{
    return _request._requestWid;
}

// 0x1f800 LIFT: folded: the vtable of RetrieveCharacterInfoRelayContext points to the same body.
unsigned short const RetrieveCharacterInfoRelayContext::GetRequestWid() const
{
    return _request._requestWid;
}

// 0x1f810
void CheckPostCapacityRelayContext::initResponse(RelayResponse* const response)
{
    static_cast<RelayResponse&>(_response) = *response;
}

// 0x1f890
bool HandlePostOfficeServiceHelloReq(Session const* session, Packet const* packet)
{
    Log::Write(Log::LT_DEBUG, WORLD_PACKET_HANDLER_FILE, 39, L"[%s], %s; <BEGIN PACKET HANDLER>",
               MODULE_NAME, L"HandlePostOfficeServiceHelloReq");
    short cmd = 0;
    short postofficeServicePacketVersion = 0;
    short economyCommonPacketVersion = 0;
    unsigned short wid = 0;
    unsigned int ipAddress = 0;
    unsigned short portNo = 0;
    short failReason = 0;
    void* memory = nullptr;
    WorldChannel* worldChannel = nullptr;
    WorldChannel* oldWorldChannel = nullptr;

    if (packet->Decompose("hhhhih", &cmd, &postofficeServicePacketVersion, &economyCommonPacketVersion, &wid,
                          &ipAddress, &portNo) == 0)
    {
        Log::Write(Log::LT_ERROR, WORLD_PACKET_HANDLER_FILE, 57, L"[%s], %s; failed to decompose packet",
                   MODULE_NAME, L"HandlePostOfficeServiceHelloReq");
        failReason = 2;
        goto $_ERROR;
    }
    Log::Write(Log::LT_DEBUG, WORLD_PACKET_HANDLER_FILE, 62,
               L"[%s], %s; decomposed packet, postoffice-service-packet-version:%d, economy-common-packet-version:%d, wid:%u, ipAddress:%s, portNo:%u",
               MODULE_NAME, L"HandlePostOfficeServiceHelloReq",
               static_cast<int>(postofficeServicePacketVersion), static_cast<int>(economyCommonPacketVersion),
               static_cast<unsigned int>(wid), Network::GetAddressStringW(ipAddress), static_cast<unsigned int>(portNo));
    if (postofficeServicePacketVersion <= 0 || economyCommonPacketVersion <= 0 || wid == 0 || ipAddress == 0 ||
        portNo == 0)
    {
        Log::Write(Log::LT_ERROR, WORLD_PACKET_HANDLER_FILE, 67,
                   L"[%s], %s; invalid parameter, postoffice-service-packet-version:%d, economy-common-packet-version:%d, wid:%u, ipAddress:%d, portNo:%u",
                   MODULE_NAME, L"HandlePostOfficeServiceHelloReq",
                   static_cast<int>(postofficeServicePacketVersion), static_cast<int>(economyCommonPacketVersion),
                   static_cast<unsigned int>(wid), ipAddress, static_cast<unsigned int>(portNo));
        failReason = 5;
        goto $_ERROR;
    }
    if (postofficeServicePacketVersion != 16)
    {
        Log::Write(Log::LT_ERROR, WORLD_PACKET_HANDLER_FILE, 74,
                   L"[%s], %s; postoffice service packet version is not same, request version:%d, my version:%d",
                   MODULE_NAME, L"HandlePostOfficeServiceHelloReq",
                   static_cast<int>(postofficeServicePacketVersion), 16);
        failReason = 6;
        goto $_ERROR;
    }
    if (economyCommonPacketVersion != 10)
    {
        Log::Write(Log::LT_ERROR, WORLD_PACKET_HANDLER_FILE, 79,
                   L"[%s], %s; economy common packet version is not same, request version:%d, my version:%d",
                   MODULE_NAME, L"HandlePostOfficeServiceHelloReq",
                   static_cast<int>(economyCommonPacketVersion), 10);
        failReason = 7;
        goto $_ERROR;
    }
    if (!PostOfficeDaemon::_instance->_worldConfigManager->CheckWorldConfig(wid, ipAddress, portNo))
    {
        Log::Write(Log::LT_ERROR, WORLD_PACKET_HANDLER_FILE, 86,
                   L"[%s], %s; world config mismatch, wid:%u, ipAddress:%s, port:%u", MODULE_NAME,
                   L"HandlePostOfficeServiceHelloReq", static_cast<unsigned int>(wid),
                   Network::GetAddressStringW(ipAddress), static_cast<unsigned int>(portNo));
        failReason = 8;
        goto $_ERROR;
    }

    memory = Memory::_Manager[2]->Alloc(sizeof(WorldChannel), WORLD_PACKET_HANDLER_FILE, 91);
    worldChannel = memory != nullptr ? ::new (memory) WorldChannel(wid, ipAddress, portNo) : nullptr;
    // BUG: 0x1f890 no null check after the Alloc. A failed Alloc gives a null call in AddWorldChannel.
    if (!PostOfficeDaemon::_instance->_worldChannelManager->AddWorldChannel(worldChannel))
    {
        oldWorldChannel = PostOfficeDaemon::_instance->_worldChannelManager->GetWorldChannel(wid);
        if (oldWorldChannel != nullptr)
        {
            Log::Write(Log::LT_ERROR, WORLD_PACKET_HANDLER_FILE, 97,
                       L"[%s], %s; world channel duplication; kick old world channel, wid:%u", MODULE_NAME,
                       L"HandlePostOfficeServiceHelloReq", static_cast<unsigned int>(wid));
            PostOfficeDaemon::_instance->_worldChannelManager->RemoveWorldChannel(wid);
            oldWorldChannel->Close();
            oldWorldChannel->removeReferenceCount(WORLD_PACKET_HANDLER_FILE, 100);
            failReason = 9;
        }
        else
        {
            Log::Write(Log::LT_ERROR, WORLD_PACKET_HANDLER_FILE, 104, L"[%s], %s; failed to add world channel, wid:%u",
                       MODULE_NAME, L"HandlePostOfficeServiceHelloReq", static_cast<unsigned int>(wid));
            failReason = 2;
        }
        goto $_ERROR;
    }
    worldChannel->SetSession(session);
    worldChannel->removeReferenceCount(WORLD_PACKET_HANDLER_FILE, 111);
    session->Send("h", PostOfficeService_HelloOkCmd);
    Log::Write(Log::LT_NOTICE, WORLD_PACKET_HANDLER_FILE, 114, L"[%s], %s; sent hello success ack, wid:%u",
               MODULE_NAME, L"HandlePostOfficeServiceHelloReq", static_cast<unsigned int>(wid));
    Log::Write(Log::LT_DEBUG, WORLD_PACKET_HANDLER_FILE, 116, L"[%s], %s; <END PACKET HANDLER>",
               MODULE_NAME, L"HandlePostOfficeServiceHelloReq");
    return true;

$_ERROR:
    session->Send("hh", PostOfficeService_HelloFailCmd, static_cast<int>(failReason));
    Log::Write(Log::LT_NOTICE, WORLD_PACKET_HANDLER_FILE, 121, L"[%s], %s; sent hello failure ack, wid:%u, failReason:%d",
               MODULE_NAME, L"HandlePostOfficeServiceHelloReq", static_cast<unsigned int>(wid),
               static_cast<int>(failReason));
    if (worldChannel != nullptr)
        worldChannel->removeReferenceCount(WORLD_PACKET_HANDLER_FILE, 124);
    Log::Write(Log::LT_DEBUG, WORLD_PACKET_HANDLER_FILE, 126, L"[%s], %s; <END PACKET HANDLER>",
               MODULE_NAME, L"HandlePostOfficeServiceHelloReq");
    return false;
}

// 0x1fdd0
bool HandlePostOfficeServiceRetrieveCharacterInfoReq(Session const* session, Packet const* packet)
{
    Log::Write(Log::LT_DEBUG, WORLD_PACKET_HANDLER_FILE, 133, L"[%s], %s; <BEGIN PACKET HANDLER>",
               MODULE_NAME, L"HandlePostOfficeServiceRetrieveCharacterInfoReq");
    RetrieveCharacterInfoRelayRequest request;
    short cmd = 0;
    short failReason = 0;
    unsigned short requestWid = 0;
    CacheGateChannel* cachegateChannel = nullptr;
    EconomyHeader economyHeader;
    void* memory = nullptr;
    RetrieveCharacterInfoRelayContext* relayContext = nullptr;

    requestWid = WorldChannel::GetWid(session);
    if (requestWid == 0)
    {
        Log::Write(Log::LT_ERROR, WORLD_PACKET_HANDLER_FILE, 141,
                   L"[%s], %s; unknown world channel, sessionId:0x%I64X, portId:%u, sessionIndex:%u",
                   MODULE_NAME, L"HandlePostOfficeServiceRetrieveCharacterInfoReq", session->_id,
                   static_cast<unsigned int>(session->_id >> 32), static_cast<unsigned int>(session->_id));
        failReason = 2;
        goto $_ERROR;
    }
    if (packet->Decompose("hqhs", &cmd, &request._gameTid, &request._targetWid, request._targetCharacterName, 33) == 0)
    {
        Log::Write(Log::LT_ERROR, WORLD_PACKET_HANDLER_FILE, 150, L"[%s], %s; failed to decompose packet",
                   MODULE_NAME, L"HandlePostOfficeServiceRetrieveCharacterInfoReq");
        failReason = 2;
        goto $_ERROR;
    }
    Log::Write(Log::LT_DEBUG, WORLD_PACKET_HANDLER_FILE, 154,
               L"[%s], %s; decomposed packet, requestWid:%u, gameTid:0x%I64X, targetWid:%u, targetCharacterName:%s",
               MODULE_NAME, L"HandlePostOfficeServiceRetrieveCharacterInfoReq",
               static_cast<unsigned int>(requestWid), request._gameTid, static_cast<unsigned int>(request._targetWid),
               request._targetCharacterName);
    // 0x1ff6e-0x1ff98: repne scasw; not; dec; je. The check is for an empty name.
    if (request._gameTid == 0 || request._targetWid == 0 || wcslen(request._targetCharacterName) == 0)
    {
        Log::Write(Log::LT_ERROR, WORLD_PACKET_HANDLER_FILE, 158,
                   L"[%s], %s; invalid parameter, requestWid:%u, gameTid:0x%I64X, targetWid:%u, targetCharacterName:%s",
                   MODULE_NAME, L"HandlePostOfficeServiceRetrieveCharacterInfoReq",
                   static_cast<unsigned int>(requestWid), request._gameTid,
                   static_cast<unsigned int>(request._targetWid), request._targetCharacterName);
        failReason = 10;
        goto $_ERROR;
    }
    if (requestWid == request._targetWid)
    {
        Log::Write(Log::LT_ERROR, WORLD_PACKET_HANDLER_FILE, 163,
                   L"[%s], %s; from-wid and to-wid are same, gameTid:0x%I64X, fromWid:%u, toWid:%u",
                   MODULE_NAME, L"HandlePostOfficeServiceRetrieveCharacterInfoReq", request._gameTid,
                   static_cast<unsigned int>(requestWid), static_cast<unsigned int>(request._targetWid));
        failReason = 12;
        goto $_ERROR;
    }
    request._requestWid = requestWid;
    cachegateChannel = PostOfficeDaemon::checkDestinationServiceState(request._targetWid);
    if (cachegateChannel == nullptr)
    {
        Log::Write(Log::LT_ERROR, WORLD_PACKET_HANDLER_FILE, 173,
                   L"[%s], %s; cannot send retrieve character info relay request", MODULE_NAME,
                   L"HandlePostOfficeServiceRetrieveCharacterInfoReq");
        failReason = 4;
        goto $_ERROR;
    }

    economyHeader._fromWid = PostOfficeDaemon::_instance->_serviceWid;
    economyHeader._toWid = request._targetWid;
    economyHeader._relayTid = liftNextRelayTid();
    memory = Memory::_Manager[2]->Alloc(sizeof(RetrieveCharacterInfoRelayContext), WORLD_PACKET_HANDLER_FILE,
                                        181);
    if (memory != nullptr)
        relayContext = ::new (memory) RetrieveCharacterInfoRelayContext(economyHeader, request);
    // BUG: 0x1fdd0 no null check after the Alloc. A failed Alloc gives a null call.
    if (!relayContext->ProcessRelayRequest(cachegateChannel))
    {
        Log::Write(Log::LT_ERROR, WORLD_PACKET_HANDLER_FILE, 184,
                   L"[%s], %s; failed to send retrieve character info relay request, relayTid:0x%I64X",
                   MODULE_NAME, L"HandlePostOfficeServiceRetrieveCharacterInfoReq",
                   economyHeader._relayTid);
        relayContext->removeReferenceCount(WORLD_PACKET_HANDLER_FILE, 185);
        cachegateChannel->removeReferenceCount(WORLD_PACKET_HANDLER_FILE, 186);
        failReason = 2;
        goto $_ERROR;
    }
    relayContext->removeReferenceCount(WORLD_PACKET_HANDLER_FILE, 192);
    cachegateChannel->removeReferenceCount(WORLD_PACKET_HANDLER_FILE, 193);
    Log::Write(Log::LT_DEBUG, WORLD_PACKET_HANDLER_FILE, 196, L"[%s], %s; <END PACKET HANDLER>",
               MODULE_NAME, L"HandlePostOfficeServiceRetrieveCharacterInfoReq");
    return true;

$_ERROR:
    session->Send("hqE", PostOfficeService_RetrieveCharacterInfoFailCmd, request._gameTid, static_cast<int>(failReason));
    Log::Write(Log::LT_NOTICE, WORLD_PACKET_HANDLER_FILE, 201,
               L"[%s], %s; sent retrieve character info failure ack, requestWid:%u, gameTid:0x%I64X, failReason:%d",
               MODULE_NAME, L"HandlePostOfficeServiceRetrieveCharacterInfoReq",
               static_cast<unsigned int>(requestWid), request._gameTid, static_cast<int>(failReason));
    Log::Write(Log::LT_DEBUG, WORLD_PACKET_HANDLER_FILE, 203, L"[%s], %s; <END PACKET HANDLER>",
               MODULE_NAME, L"HandlePostOfficeServiceRetrieveCharacterInfoReq");
    return true;
}

// 0x20250
bool HandlePostOfficeServiceCheckPostCapacityReq(Session const* session, Packet const* packet)
{
    Log::Write(Log::LT_DEBUG, WORLD_PACKET_HANDLER_FILE, 210, L"[%s], %s; <BEGIN PACKET HANDLER>",
               MODULE_NAME, L"HandlePostOfficeServiceCheckPostCapacityReq");
    CheckPostCapacityRelayRequest request;
    short cmd = 0;
    short failReason = 0;
    unsigned short requestWid = 0;
    CacheGateChannel* cachegateChannel = nullptr;
    EconomyHeader economyHeader;
    void* memory = nullptr;
    CheckPostCapacityRelayContext* relayContext = nullptr;

    requestWid = WorldChannel::GetWid(session);
    if (requestWid == 0)
    {
        Log::Write(Log::LT_ERROR, WORLD_PACKET_HANDLER_FILE, 218,
                   L"[%s], %s; unknown world channel, sessionId:0x%I64X, portId:%u, sessionIndex:%u",
                   MODULE_NAME, L"HandlePostOfficeServiceCheckPostCapacityReq", session->_id,
                   static_cast<unsigned int>(session->_id >> 32), static_cast<unsigned int>(session->_id));
        failReason = 2;
        goto $_ERROR;
    }
    if (packet->Decompose("hqhq", &cmd, &request._gameTid, &request._targetWid, &request._targetPcId) == 0)
    {
        Log::Write(Log::LT_ERROR, WORLD_PACKET_HANDLER_FILE, 227, L"[%s], %s; failed to decompose packet",
                   MODULE_NAME, L"HandlePostOfficeServiceCheckPostCapacityReq");
        failReason = 2;
        goto $_ERROR;
    }
    Log::Write(Log::LT_DEBUG, WORLD_PACKET_HANDLER_FILE, 231,
               L"[%s], %s; decomposed packet, requestWid:%u, gameTid:0x%I64X, targetWid:%u, targetPcId:0x%I64X",
               MODULE_NAME, L"HandlePostOfficeServiceCheckPostCapacityReq",
               static_cast<unsigned int>(requestWid), request._gameTid, static_cast<unsigned int>(request._targetWid),
               request._targetPcId);
    if (request._gameTid == 0 || request._targetWid == 0 || request._targetPcId == 0)
    {
        Log::Write(Log::LT_ERROR, WORLD_PACKET_HANDLER_FILE, 235,
                   L"[%s], %s; invalid parameter, requestWid:%u, gameTid:0x%I64X, targetWid:%u, targetPcId:0x%I64X",
                   MODULE_NAME, L"HandlePostOfficeServiceCheckPostCapacityReq",
                   static_cast<unsigned int>(requestWid), request._gameTid,
                   static_cast<unsigned int>(request._targetWid), request._targetPcId);
        failReason = 15;
        goto $_ERROR;
    }
    if (requestWid == request._targetWid)
    {
        Log::Write(Log::LT_ERROR, WORLD_PACKET_HANDLER_FILE, 240,
                   L"[%s], %s; from-wid and to-wid are same, gameTid:0x%I64X, fromWid:%u, toWid:%u",
                   MODULE_NAME, L"HandlePostOfficeServiceCheckPostCapacityReq", request._gameTid,
                   static_cast<unsigned int>(requestWid), static_cast<unsigned int>(request._targetWid));
        failReason = 18;
        goto $_ERROR;
    }
    request._requestWid = requestWid;
    cachegateChannel = PostOfficeDaemon::checkDestinationServiceState(request._targetWid);
    if (cachegateChannel == nullptr)
    {
        Log::Write(Log::LT_ERROR, WORLD_PACKET_HANDLER_FILE, 250,
                   L"[%s], %s; cannot send check post capacity relay request", MODULE_NAME,
                   L"HandlePostOfficeServiceCheckPostCapacityReq");
        failReason = 4;
        goto $_ERROR;
    }

    economyHeader._fromWid = PostOfficeDaemon::_instance->_serviceWid;
    economyHeader._toWid = request._targetWid;
    economyHeader._relayTid = liftNextRelayTid();
    memory = Memory::_Manager[2]->Alloc(sizeof(CheckPostCapacityRelayContext), WORLD_PACKET_HANDLER_FILE,
                                        258);
    if (memory != nullptr)
        relayContext = ::new (memory) CheckPostCapacityRelayContext(economyHeader, request);
    // BUG: 0x20250 no null check after the Alloc. A failed Alloc gives a null call.
    if (!relayContext->ProcessRelayRequest(cachegateChannel))
    {
        Log::Write(Log::LT_ERROR, WORLD_PACKET_HANDLER_FILE, 261,
                   L"[%s], %s; failed to send check post capacity relay request, relayTid:0x%I64X",
                   MODULE_NAME, L"HandlePostOfficeServiceCheckPostCapacityReq", economyHeader._relayTid);
        relayContext->removeReferenceCount(WORLD_PACKET_HANDLER_FILE, 262);
        cachegateChannel->removeReferenceCount(WORLD_PACKET_HANDLER_FILE, 263);
        failReason = 2;
        goto $_ERROR;
    }
    relayContext->removeReferenceCount(WORLD_PACKET_HANDLER_FILE, 269);
    cachegateChannel->removeReferenceCount(WORLD_PACKET_HANDLER_FILE, 270);
    Log::Write(Log::LT_DEBUG, WORLD_PACKET_HANDLER_FILE, 273, L"[%s], %s; <END PACKET HANDLER>",
               MODULE_NAME, L"HandlePostOfficeServiceCheckPostCapacityReq");
    return true;

$_ERROR:
    session->Send("hqE", PostOfficeService_CheckPostCapacityFailCmd, request._gameTid, static_cast<int>(failReason));
    Log::Write(Log::LT_NOTICE, WORLD_PACKET_HANDLER_FILE, 278,
               L"[%s], %s; sent check post capacity failure ack, requestWid:%u, gameTid:0x%I64X, failReason:%d",
               MODULE_NAME, L"HandlePostOfficeServiceCheckPostCapacityReq",
               static_cast<unsigned int>(requestWid), request._gameTid, static_cast<int>(failReason));
    Log::Write(Log::LT_DEBUG, WORLD_PACKET_HANDLER_FILE, 280, L"[%s], %s; <END PACKET HANDLER>",
               MODULE_NAME, L"HandlePostOfficeServiceCheckPostCapacityReq");
    return true;
}

// The log formats of HandlePostOfficeServiceRegisterPostReq. LIFT: the binary has one full literal per Log::Write call.
#define ITEM_LOG_ARGS L", tid:0x%I64X, invoiceId:0x%I64X, itemNo:%d, itemType:%d, itemCategory:%d, itemInstanceId:0x%I64X, itemDataId:%d, itemLevel:%d, itemAmount:%I64d, itemXmlData:%s"
#define POST_LOG_ARGS L", tid:0x%I64X, invoiceId:0x%I64X, postType:%d, deliveryReason:%d, postHint:0x%I64X, reservedHint:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, senderServiceType:%d, senderWid:%d, senderPcId:0x%I64X, senderAccountId:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, senderWorldName:%s, senderName:%s, recipientWid:%d, recipientPcId:0x%I64X, recipientName:%s, postTitle:%s, postMessage:%s"
#define POST_LOG_VALUES                                                                                              \
    tid, postInfo._invoiceId, static_cast<int>(postInfo._postType), static_cast<int>(postInfo._deliveryReason),      \
        postInfo._postHint, static_cast<unsigned int>(postInfo._reservedHint.guid.id1),                               \
        static_cast<unsigned int>(postInfo._reservedHint.guid.id2),                                                   \
        static_cast<unsigned int>(postInfo._reservedHint.guid.id3),                                                   \
        static_cast<unsigned int>(postInfo._reservedHint.guid.id4[0]),                                                \
        static_cast<unsigned int>(postInfo._reservedHint.guid.id4[1]),                                                \
        static_cast<unsigned int>(postInfo._reservedHint.guid.id4[2]),                                                \
        static_cast<unsigned int>(postInfo._reservedHint.guid.id4[3]),                                                \
        static_cast<unsigned int>(postInfo._reservedHint.guid.id4[4]),                                                \
        static_cast<unsigned int>(postInfo._reservedHint.guid.id4[5]),                                                \
        static_cast<unsigned int>(postInfo._reservedHint.guid.id4[6]),                                                \
        static_cast<unsigned int>(postInfo._reservedHint.guid.id4[7]), static_cast<int>(postInfo._senderServiceType), \
        static_cast<int>(postInfo._senderWid), postInfo._senderPcId,                                                  \
        static_cast<unsigned int>(postInfo._senderAccountId.guid.id1),                                                \
        static_cast<unsigned int>(postInfo._senderAccountId.guid.id2),                                                \
        static_cast<unsigned int>(postInfo._senderAccountId.guid.id3),                                                \
        static_cast<unsigned int>(postInfo._senderAccountId.guid.id4[0]),                                             \
        static_cast<unsigned int>(postInfo._senderAccountId.guid.id4[1]),                                             \
        static_cast<unsigned int>(postInfo._senderAccountId.guid.id4[2]),                                             \
        static_cast<unsigned int>(postInfo._senderAccountId.guid.id4[3]),                                             \
        static_cast<unsigned int>(postInfo._senderAccountId.guid.id4[4]),                                             \
        static_cast<unsigned int>(postInfo._senderAccountId.guid.id4[5]),                                             \
        static_cast<unsigned int>(postInfo._senderAccountId.guid.id4[6]),                                             \
        static_cast<unsigned int>(postInfo._senderAccountId.guid.id4[7]), postInfo._senderWorldName,                  \
        postInfo._senderName, static_cast<int>(postInfo._recipientWid), postInfo._recipientPcId,                      \
        postInfo._recipientName, postInfo._postTitle, postInfo._postMessage
#define ITEM_LOG_VALUES                                                                                              \
    tid, postInfo._invoiceId, static_cast<int>(itemInfo._itemNo), static_cast<int>(itemInfo._itemType),              \
        static_cast<int>(itemInfo._itemCategory), itemInfo._itemInstanceId, itemInfo._itemDataId,                     \
        static_cast<int>(itemInfo._itemLevel), itemInfo._itemAmount, itemInfo._itemXmlData

// 0x20720
bool HandlePostOfficeServiceRegisterPostReq(Session const* session, Packet const* packet)
{
    Log::Write(Log::LT_DEBUG, WORLD_PACKET_HANDLER_FILE, 287, L"[%s], %s; <BEGIN PACKET HANDLER>",
               MODULE_NAME, L"HandlePostOfficeServiceRegisterPostReq");
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
        Log::Write(Log::LT_ERROR, WORLD_PACKET_HANDLER_FILE, 341, L"[%s], %s; failed to decompose packet",
                   MODULE_NAME, L"HandlePostOfficeServiceRegisterPostReq");
        goto $_ERROR;
    }
    Log::Write(Log::LT_DEBUG, WORLD_PACKET_HANDLER_FILE, 345, L"[%s], %s; decomposed post data packet" POST_LOG_ARGS,
               MODULE_NAME, L"HandlePostOfficeServiceRegisterPostReq", POST_LOG_VALUES);
    if (postInfo._postType <= 0 || !postInfo.CheckValidityPostData())
    {
        Log::Write(Log::LT_ERROR, WORLD_PACKET_HANDLER_FILE, 348, L"[%s], %s; invalid post data" POST_LOG_ARGS,
                   MODULE_NAME, L"HandlePostOfficeServiceRegisterPostReq", POST_LOG_VALUES);
        failReason = 23;
        goto $_ERROR;
    }

    attachedItemCount = static_cast<short>(pcb->decomposer.PushRepeatCount(
        &pcb->buffer[pcb->decomposer.offset], pcb->size - pcb->decomposer.offset));
    if (static_cast<unsigned int>(attachedItemCount) > 10)
    {
        Log::Write(Log::LT_ERROR, WORLD_PACKET_HANDLER_FILE, 355,
                   L"[%s], %s; invalid attached item count, attachedItemCount:%d, maxAttachedItemCount:%d",
                   MODULE_NAME, L"HandlePostOfficeServiceRegisterPostReq",
                   static_cast<int>(attachedItemCount), 10);
        failReason = 24;
        goto $_ERROR;
    }
    if (attachedItemCount > 0)
        attachedItemList = liftArrayNew(AttachedItemContext, attachedItemCount, WORLD_PACKET_HANDLER_FILE, 361);

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
            Log::Write(Log::LT_ERROR, WORLD_PACKET_HANDLER_FILE, 374, L"[%s], %s; failed to decompose packet",
                       MODULE_NAME, L"HandlePostOfficeServiceRegisterPostReq");
            failReason = 2;
            goto $_ERROR;
        }
        Log::Write(Log::LT_DEBUG, WORLD_PACKET_HANDLER_FILE, 378, L"[%s], %s; decomposed item data packet" ITEM_LOG_ARGS,
                   MODULE_NAME, L"HandlePostOfficeServiceRegisterPostReq", ITEM_LOG_VALUES);

        itemError = itemInfo._itemType <= 0 ? 1 : itemInfo.CheckValidityItemData();
        if (itemError != 0)
        {
            switch (itemError)
            {
            case 1:
                Log::Write(Log::LT_ERROR, WORLD_PACKET_HANDLER_FILE, 384, L"[%s], %s; invalid item data" ITEM_LOG_ARGS,
                           MODULE_NAME, L"HandlePostOfficeServiceRegisterPostReq", ITEM_LOG_VALUES);
                failReason = 24;
                break;
            case 2:
                Log::Write(Log::LT_ERROR, WORLD_PACKET_HANDLER_FILE, 388,
                           L"[%s], %s; invalid money item data" ITEM_LOG_ARGS, MODULE_NAME,
                           L"HandlePostOfficeServiceRegisterPostReq", ITEM_LOG_VALUES);
                failReason = 25;
                break;
            case 3:
                Log::Write(Log::LT_ERROR, WORLD_PACKET_HANDLER_FILE, 392,
                           L"[%s], %s; invalid default item data" ITEM_LOG_ARGS, MODULE_NAME,
                           L"HandlePostOfficeServiceRegisterPostReq", ITEM_LOG_VALUES);
                failReason = 26;
                break;
            case 4:
                Log::Write(Log::LT_ERROR, WORLD_PACKET_HANDLER_FILE, 396,
                           L"[%s], %s; invalid custom item data" ITEM_LOG_ARGS, MODULE_NAME,
                           L"HandlePostOfficeServiceRegisterPostReq", ITEM_LOG_VALUES);
                failReason = 27;
                break;
            case 5:
                Log::Write(Log::LT_ERROR, WORLD_PACKET_HANDLER_FILE, 400, L"[%s], %s; unknown item type" ITEM_LOG_ARGS,
                           MODULE_NAME, L"HandlePostOfficeServiceRegisterPostReq", ITEM_LOG_VALUES);
                failReason = 28;
                break;
            default:
                Log::Write(Log::LT_ERROR, WORLD_PACKET_HANDLER_FILE, 404, L"[%s], %s; unknown error" ITEM_LOG_ARGS,
                           MODULE_NAME, L"HandlePostOfficeServiceRegisterPostReq", ITEM_LOG_VALUES);
                failReason = 1;
                break;
            }
            goto $_ERROR;
        }

        // BUG: 0x20720 if the Alloc at line 361 fails, this writes through a null attachedItemList.
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
        Log::Write(Log::LT_ERROR, WORLD_PACKET_HANDLER_FILE, 419,
                   L"[%s], %s; failed to register post, dbRetValue:%d, tid:0x%I64X, invoiceId:0x%I64X",
                   MODULE_NAME, L"HandlePostOfficeServiceRegisterPostReq", dbRetValue, tid,
                   postInfo._invoiceId);
        failReason = dbRetValue == 2 ? 29 : 3;
        goto $_ERROR;
    }

    postId = postInfo._postId;
    recipientWid = static_cast<unsigned short>(postInfo._recipientWid);
    postInfo._postStatus = 1;
    session->Send("hqq", PostOfficeService_RegisterPostOkCmd, tid, postInfo._postId);
    Log::Write(Log::LT_NOTICE, WORLD_PACKET_HANDLER_FILE, 437,
               L"[%s], %s; sent post registration success ack, tid:0x%I64X, invoiceId:0x%I64X, postId:0x%I64X",
               MODULE_NAME, L"HandlePostOfficeServiceRegisterPostReq", tid, postInfo._invoiceId, postId);

    cachegateChannel = PostOfficeDaemon::checkDestinationServiceState(recipientWid);
    if (cachegateChannel != nullptr)
    {
        void* const memory = Memory::_Manager[2]->Alloc(sizeof(PostContext), WORLD_PACKET_HANDLER_FILE, 443);
        if (memory != nullptr)
            postContext = ::new (memory) PostContext();
        // BUG: 0x20720 no null check after the Alloc at line 443.
        postContext->_postInfo = postInfo;
        // 0x11630: InitAttachedItemInfo fails only for a null list (the count is > 0 here). The path has nothing to free.
        if (attachedItemCount > 0 && !postContext->InitAttachedItemInfo(attachedItemList, attachedItemCount))
        {
            Log::Write(Log::LT_ERROR, WORLD_PACKET_HANDLER_FILE, 447,
                       L"== CRASH == [%s], %s; exception occurred; failed to initialize attached item info, tid:0x%I64X, postId:0x%I64X",
                       MODULE_NAME, L"HandlePostOfficeServiceRegisterPostReq", tid, postId);
            AlertSender::Write(WORLD_PACKET_HANDLER_FILE, 447,
                               L"== CRASH == [%s], %s; exception occurred; failed to initialize attached item info, tid:0x%I64X, postId:0x%I64X",
                               MODULE_NAME, L"HandlePostOfficeServiceRegisterPostReq", tid, postId);
        }
        if (!PostOfficeDaemon::_instance->_postContextManager->AddContext(postContext))
        {
            Log::Write(Log::LT_ERROR, WORLD_PACKET_HANDLER_FILE, 452,
                       L"== CRASH == [%s], %s; exception occurred; failed to add post context, postId:0x%I64X",
                       MODULE_NAME, L"HandlePostOfficeServiceRegisterPostReq", postId);
            AlertSender::Write(WORLD_PACKET_HANDLER_FILE, 452,
                               L"== CRASH == [%s], %s; exception occurred; failed to add post context, postId:0x%I64X",
                               MODULE_NAME, L"HandlePostOfficeServiceRegisterPostReq", postId);
        }
        if (!PostDeliveryEvent::OccurEvent(postContext, cachegateChannel))
        {
            Log::Write(Log::LT_ERROR, WORLD_PACKET_HANDLER_FILE, 456,
                       L"[%s], %s; exception occurred; failed to occur post delivery event, postId:0x%I64X",
                       MODULE_NAME, L"HandlePostOfficeServiceRegisterPostReq", postId);
            if (!PostOfficeDaemon::_instance->_postContextManager->RemoveContext(postId))
            {
                Log::Write(Log::LT_ERROR, WORLD_PACKET_HANDLER_FILE, 459,
                           L"== CRASH == [%s], %s; exception occurred; failed to remove post context, postId:0x%I64X",
                           MODULE_NAME, L"HandlePostOfficeServiceRegisterPostReq", postId);
                AlertSender::Write(WORLD_PACKET_HANDLER_FILE, 459,
                                   L"== CRASH == [%s], %s; exception occurred; failed to remove post context, postId:0x%I64X",
                                   MODULE_NAME, L"HandlePostOfficeServiceRegisterPostReq", postId);
            }
        }
        postContext->removeReferenceCount(WORLD_PACKET_HANDLER_FILE, 463);
        cachegateChannel->removeReferenceCount(WORLD_PACKET_HANDLER_FILE, 464);
    }
    else
    {
        Log::Write(Log::LT_ERROR, WORLD_PACKET_HANDLER_FILE, 468,
                   L"[%s], %s; cannot send deliver post relay request, recipientWid:%u, postId:0x%I64X",
                   MODULE_NAME, L"HandlePostOfficeServiceRegisterPostReq",
                   static_cast<unsigned int>(recipientWid), postId);
        Memory::_Manager[2]->Free(attachedItemList, WORLD_PACKET_HANDLER_FILE, 469);
        if (!PostOfficeDaemon::_instance->_unsentPostContextManager->RegisterUnsentPost(recipientWid, postId, false))
            Log::Write(Log::LT_ERROR, WORLD_PACKET_HANDLER_FILE, 472,
                       L"[%s], %s; exception occurred; failed to register unsent post, recipientWid:%u, postId:0x%I64X",
                       MODULE_NAME, L"HandlePostOfficeServiceRegisterPostReq",
                       static_cast<unsigned int>(recipientWid), postId);
    }
    Log::Write(Log::LT_DEBUG, WORLD_PACKET_HANDLER_FILE, 476, L"[%s], %s; <END PACKET HANDLER>",
               MODULE_NAME, L"HandlePostOfficeServiceRegisterPostReq");
    return true;

$_ERROR:
    session->Send("hqE", PostOfficeService_RegisterPostFailCmd, tid, static_cast<int>(failReason));
    Log::Write(Log::LT_NOTICE, WORLD_PACKET_HANDLER_FILE, 481,
               L"[%s], %s; sent post registration failure ack, tid:0x%I64X, failReason:%d", MODULE_NAME,
               L"HandlePostOfficeServiceRegisterPostReq", tid, static_cast<int>(failReason));
    if (pcb != nullptr)
        pcb->Clear();
    if (attachedItemList != nullptr)
        Memory::_Manager[2]->Free(attachedItemList, WORLD_PACKET_HANDLER_FILE, 486);
    Log::Write(Log::LT_DEBUG, WORLD_PACKET_HANDLER_FILE, 488, L"[%s], %s; <END PACKET HANDLER>",
               MODULE_NAME, L"HandlePostOfficeServiceRegisterPostReq");
    return true;
}

#undef ITEM_LOG_VALUES
#undef POST_LOG_VALUES
#undef ITEM_LOG_ARGS
#undef POST_LOG_ARGS
