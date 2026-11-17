// CacheGatePacketHandler.obj (PostOfficeDaemon PDB). Source: .scratch/hr/CacheGatePacketHandler.c
#include <winsock2.h>
#include <windows.h>
#include "CacheGatePacketHandler.h"
#include "CacheGateChannel.h"
#include "CachedWatchdog.h"
#include "Log.h"
#include "Packet.h"
#include "PacketUtil.h"
#include "PostOfficeDaemon.h"
#include "RelayContext.h"
#include "Session.h"
#include "ThreadFreePacketPump.h"

extern Daemon::PacketHandler CacheEconomyPacketClientSideHandlerList[22];  // CacheEconomyClientSideHandlerList.cpp

namespace
{
wchar_t const* const CGPH_FILE = L"CacheGatePacketHandler.cpp";  // LIFT: No PDB symbol. The binary uses the literal.
static wchar_t const* const MODULE_NAME = L"cachegate packet handler";  // PDB MODULE_NAME

// PDB enum CacheEconomyPacketCommand (PostOfficeDaemon type 0x2C8F).
enum
{
    ECONOMY_CMD_BASE = 1024,  // LIFT: The PDB enum has no 1024 entry. The binary uses the literal.
    CacheEconomy_PingReqCmd = 1031,
    CacheEconomy_RetrieveCharacterInfoReqCmd = 1037,
    CacheEconomy_CheckPostCapacityReqCmd = 1040,
    CacheEconomy_DeliverPostReqCmd = 1043,
};

void logBegin(int line, wchar_t const* func)
{
    Log::Write(Log::LT_DEBUG, CGPH_FILE, line, L"[%s], %s; <BEGIN PACKET HANDLER>", MODULE_NAME, func);
}

void logEnd(int line, wchar_t const* func)  // LIFT: lift helper name, not in any PDB
{
    Log::Write(Log::LT_DEBUG, CGPH_FILE, line, L"[%s], %s; <END PACKET HANDLER>", MODULE_NAME, func);
}

void logInvalidDestination(int line, wchar_t const* func, unsigned short serviceWid, RelayHeader const& relayHeader)  // LIFT: lift helper name, not in any PDB
{
    Log::Write(Log::LT_ERROR, CGPH_FILE, line,
               L"[%s], %s; invalid destination, postofficeServiceWid:%u, fromWid:%u, toWid:%u, relayTid:0x%I64X, hint:%u, reserved:%I64u",
               MODULE_NAME, func, static_cast<unsigned int>(serviceWid), static_cast<unsigned int>(relayHeader._fromWid),
               static_cast<unsigned int>(relayHeader._toWid), relayHeader._relayTid,
               static_cast<unsigned int>(relayHeader._hint), relayHeader._reserved);
}
}

// 0x7e90
bool HandleCacheGateHelloOk(Session const* session, Packet const* packet)
{
    Channel* const channel = session->GetChannel();
    if (channel == nullptr)
    {
        Log::Write(Log::LT_ERROR, CGPH_FILE, 42, L"[%s], %s; cachegate channel is null, cachegateChannel:0x%p", MODULE_NAME,
                   L"HandleCacheGateHelloOk", static_cast<void*>(nullptr));
        return false;
    }
    static_cast<CacheGateChannel*>(channel)->SetServiceState(CacheGateChannel::SERVICE_STATE_AVAILABLE);
    channel->removeReferenceCount(CGPH_FILE, 47);
    Log::Write(Log::LT_NOTICE, CGPH_FILE, 49, L"[%s], %s; hello success", MODULE_NAME, L"HandleCacheGateHelloOk");
    return true;
}

// 0x7fc0
bool HandleCacheGateHelloFail(Session const* session, Packet const* packet)
{
    short cmd = 0;
    short failReason = 0;
    if (packet->Decompose("hE", &cmd, &failReason) == 0)
        Log::Write(Log::LT_ERROR, CGPH_FILE, 61, L"[%s], %s; failed to decompose packet", MODULE_NAME,
                   L"HandleCacheGateHelloFail");
    else
        Log::Write(Log::LT_ERROR, CGPH_FILE, 65, L"[%s], %s; hello failure, failReason:%d", MODULE_NAME,
                   L"HandleCacheGateHelloFail", static_cast<int>(failReason));
    return false;
}

// 0x8070
bool HandleCacheGateRelay(Session const* session, Packet const* packet)
{
    wchar_t const* const func = L"HandleCacheGateRelay";
    logBegin(73, func);

    short cachegateCmd = 0;
    short economyCmd = 0;
    RelayHeader relayHeader;
    relayHeader._fromWid = 0;
    relayHeader._toWid = 0;
    relayHeader._relayTid = 0;
    relayHeader._hint = 0;
    relayHeader._reserved = 0;

    int endLine = 109;
    if (packet->Decompose("hhhqhqh", &cachegateCmd, &relayHeader._fromWid, &relayHeader._toWid, &relayHeader._relayTid,
                          &relayHeader._hint, &relayHeader._reserved, &economyCmd) == 0)
    {
        Log::Write(Log::LT_ERROR, CGPH_FILE, 86, L"[%s], %s; failed to decompose packet", MODULE_NAME, func);
    }
    else
    {
        Log::Write(Log::LT_DEBUG, CGPH_FILE, 89,
                   L"[%s], %s; decomposed packet, fromWid:%u, toWid:%u, relayTid:0x%I64X, hint:%u, reserved:%I64u, economyCmd:%d",
                   MODULE_NAME, func, static_cast<unsigned int>(relayHeader._fromWid),
                   static_cast<unsigned int>(relayHeader._toWid), relayHeader._relayTid,
                   static_cast<unsigned int>(relayHeader._hint), relayHeader._reserved, static_cast<int>(economyCmd));
        unsigned short const serviceWid = PostOfficeDaemon::_instance->_serviceWid;
        if (serviceWid != relayHeader._toWid)
        {
            logInvalidDestination(93, func, serviceWid, relayHeader);
        }
        else
        {
            // BUG: 0x8070 economyCmd - 1024 has no bounds check before the table read.
            Daemon::PacketHandler const handler = CacheEconomyPacketClientSideHandlerList[economyCmd - ECONOMY_CMD_BASE];
            if (handler != nullptr)
            {
                handler(session, packet);
                endLine = 105;
            }
            else
            {
                Log::Write(Log::LT_ERROR, CGPH_FILE, 99, L"[%s], %s; invalid cache economy packet command, command:%d",
                           MODULE_NAME, func, static_cast<int>(economyCmd));
            }
        }
    }
    logEnd(endLine, func);
    return true;
}

// 0x82c0
bool HandleCacheGateFragmentRelay(Session const* session, Packet const* packet)
{
    wchar_t const* const func = L"HandleCacheGateFragmentRelay";
    logBegin(116, func);

    // The fragment pump gives a PacketConcatenateBuffer in place of a Packet.
    PacketConcatenateBuffer* const pcb = reinterpret_cast<PacketConcatenateBuffer*>(const_cast<Packet*>(packet));
    short economyCmd = 0;
    RelayHeader relayHeader;
    relayHeader._fromWid = 0;
    relayHeader._toWid = 0;
    relayHeader._relayTid = 0;
    relayHeader._hint = 0;
    relayHeader._reserved = 0;
    pcb->decomposer.SetFormat("hihhqhqh", 2);

    int endLine = 181;
    if (!pcb->Decompose(6, &relayHeader._fromWid, &relayHeader._toWid, &relayHeader._relayTid, &relayHeader._hint,
                        &relayHeader._reserved, &economyCmd))
    {
        Log::Write(Log::LT_ERROR, CGPH_FILE, 155, L"[%s], %s; failed to decompose packet", MODULE_NAME, func);
        pcb->Clear();
    }
    else
    {
        Log::Write(Log::LT_DEBUG, CGPH_FILE, 158,
                   L"[%s], %s; decomposed packet, fromWid:%u, toWid:%u, relayTid:0x%I64X, hint:%u, reserved:%I64u, economyCmd:%d",
                   MODULE_NAME, func, static_cast<unsigned int>(relayHeader._fromWid),
                   static_cast<unsigned int>(relayHeader._toWid), relayHeader._relayTid,
                   static_cast<unsigned int>(relayHeader._hint), relayHeader._reserved, static_cast<int>(economyCmd));
        unsigned short const serviceWid = PostOfficeDaemon::_instance->_serviceWid;
        if (serviceWid != relayHeader._toWid)
        {
            logInvalidDestination(162, func, serviceWid, relayHeader);
            pcb->Clear();
        }
        else
        {
            // BUG: 0x82c0 economyCmd - 1024 has no bounds check before the table read.
            Daemon::PacketHandler const handler = CacheEconomyPacketClientSideHandlerList[economyCmd - ECONOMY_CMD_BASE];
            if (handler != nullptr)
            {
                handler(session, packet);
                endLine = 174;
            }
            else
            {
                Log::Write(Log::LT_ERROR, CGPH_FILE, 168, L"[%s], %s; invalid cache economy packet command, command:%d",
                           MODULE_NAME, func, static_cast<int>(economyCmd));
                pcb->Clear();
            }
        }
    }
    logEnd(endLine, func);
    return true;
}

// 0x8540
bool HandleCacheGateRelayFail(Session const* session, Packet const* packet)
{
    wchar_t const* const func = L"HandleCacheGateRelayFail";
    logBegin(188, func);

    short cachegateCmd = 0;
    RelayHeader relayHeader;
    relayHeader._fromWid = 0;
    relayHeader._toWid = 0;
    relayHeader._relayTid = 0;
    relayHeader._hint = 0;
    relayHeader._reserved = 0;
    short relayFailReason = 0;

    if (packet->Decompose("hhhqhqE", &cachegateCmd, &relayHeader._fromWid, &relayHeader._toWid, &relayHeader._relayTid,
                          &relayHeader._hint, &relayHeader._reserved, &relayFailReason) == 0)
    {
        Log::Write(Log::LT_ERROR, CGPH_FILE, 202, L"[%s], %s; failed to decompose packet", MODULE_NAME, func);
        logEnd(284, func);
        return true;
    }

    Log::Write(Log::LT_DEBUG, CGPH_FILE, 205,
               L"[%s], %s; decomposed packet, fromWid:%u, toWid:%u, relayTid:0x%I64X, hint:%u, reserved:%I64u, relayFailReason:%d",
               MODULE_NAME, func, static_cast<unsigned int>(relayHeader._fromWid),
               static_cast<unsigned int>(relayHeader._toWid), relayHeader._relayTid,
               static_cast<unsigned int>(relayHeader._hint), relayHeader._reserved, static_cast<int>(relayFailReason));
    unsigned short const serviceWid = PostOfficeDaemon::_instance->_serviceWid;
    if (serviceWid != relayHeader._toWid)
    {
        logInvalidDestination(209, func, serviceWid, relayHeader);
        logEnd(284, func);
        return true;
    }

    unsigned long long const relayTid = relayHeader._relayTid;
    RelayContext* const relayContext = PostOfficeDaemon::_instance->_relayContextManager->GetContext(relayTid);
    if (relayContext == nullptr)
    {
        Log::Write(Log::LT_ERROR, CGPH_FILE, 216, L"[%s], %s; no such relay context, relayTid:0x%I64X, relayContext:0x%p",
                   MODULE_NAME, func, relayTid, static_cast<void*>(nullptr));
        logEnd(284, func);
        return true;
    }

    int errorLine = 0;
    wchar_t const* errorText = nullptr;
    wchar_t const* failText = nullptr;
    int failLine = 0;
    switch (relayHeader._hint)
    {
    case CacheEconomy_PingReqCmd:
        errorLine = 224;
        errorText = L"[%s], %s; ping relay error, relayTid:0x%I64X, relayFailReason:%d";
        failLine = 229;
        failText = L"[%s], %s; failed to process ping relay error response, relayTid:0x%I64X";
        break;
    case CacheEconomy_RetrieveCharacterInfoReqCmd:
        errorLine = 236;
        errorText = L"[%s], %s; retrieve character info relay error, relayTid:0x%I64X, relayFailReason:%d";
        failLine = 241;
        failText = L"[%s], %s; failed to process retrieve character info relay error response, relayTid:0x%I64X";
        break;
    case CacheEconomy_CheckPostCapacityReqCmd:
        errorLine = 248;
        errorText = L"[%s], %s; check post capacity relay error, relayTid:0x%I64X, relayFailReason:%d";
        failLine = 253;
        failText = L"[%s], %s; failed to process check post capacity relay error response, relayTid:0x%I64X";
        break;
    case CacheEconomy_DeliverPostReqCmd:
        errorLine = 260;
        errorText = L"[%s], %s; deliver post relay error, relayTid:0x%I64X, relayFailReason:%d";
        failLine = 265;
        failText = L"[%s], %s; failed to process deliver post relay error response, relayTid:0x%I64X";
        break;
    default:
        Log::Write(Log::LT_ERROR, CGPH_FILE, 271, L"[%s], %s; invalid request packet command, command:%d", MODULE_NAME, func,
                   static_cast<int>(static_cast<short>(relayHeader._hint)));
        relayContext->removeReferenceCount(CGPH_FILE, 282);
        logEnd(284, func);
        return true;
    }

    // The original has one case body for each hint. All case bodies are the same except the text.
    Log::Write(Log::LT_ERROR, CGPH_FILE, errorLine, errorText, MODULE_NAME, func, relayTid, static_cast<int>(relayFailReason));
    DeliverPostRelayResponse response;  // ❓ the original uses this response class for all hints
    response._resultState = RelayResponse::RESULTSTATE_RELAY_ERROR;
    response._failReason = relayFailReason;
    if (!relayContext->ProcessRelayResponse(&response))
    {
        Log::Write(Log::LT_ERROR, CGPH_FILE, failLine, failText, MODULE_NAME, func, relayTid);
        relayContext->removeReferenceCount(CGPH_FILE, 282);
        logEnd(284, func);
        return true;
    }
    relayContext->removeReferenceCount(CGPH_FILE, 275);
    logEnd(277, func);
    return true;
}

// 0x8a60
bool HandleCacheGateRelayInvalid(Session const* session, Packet const* packet)
{
    wchar_t const* const func = L"HandleCacheGateRelayInvalid";
    logBegin(291, func);

    short cachegateCmd = 0;
    RelayHeader relayHeader;
    relayHeader._fromWid = 0;
    relayHeader._toWid = 0;
    relayHeader._relayTid = 0;
    relayHeader._hint = 0;
    relayHeader._reserved = 0;
    unsigned short toWid = 0;
    short relayInvalidReason = 0;

    if (packet->Decompose("hhhqhqhh", &cachegateCmd, &relayHeader._fromWid, &relayHeader._toWid, &relayHeader._relayTid,
                          &relayHeader._hint, &relayHeader._reserved, &toWid, &relayInvalidReason) == 0)
    {
        Log::Write(Log::LT_ERROR, CGPH_FILE, 307, L"[%s], %s; failed to decompose packet", MODULE_NAME, func);
        logEnd(389, func);
        return true;
    }

    Log::Write(Log::LT_DEBUG, CGPH_FILE, 310,
               L"[%s], %s; decomposed packet, fromWid:%u, toWid:%u, relayTid:0x%I64X, hint:%u, reserved:%I64u, toWid:%u, relayInvalidReason:%d",
               MODULE_NAME, func, static_cast<unsigned int>(relayHeader._fromWid),
               static_cast<unsigned int>(relayHeader._toWid), relayHeader._relayTid,
               static_cast<unsigned int>(relayHeader._hint), relayHeader._reserved, static_cast<unsigned int>(toWid),
               static_cast<int>(relayInvalidReason));
    unsigned short const serviceWid = PostOfficeDaemon::_instance->_serviceWid;
    if (serviceWid != relayHeader._toWid)
    {
        logInvalidDestination(314, func, serviceWid, relayHeader);
        logEnd(389, func);
        return true;
    }

    unsigned long long const relayTid = relayHeader._relayTid;
    RelayContext* const relayContext = PostOfficeDaemon::_instance->_relayContextManager->GetContext(relayTid);
    if (relayContext == nullptr)
    {
        Log::Write(Log::LT_ERROR, CGPH_FILE, 321, L"[%s], %s; no such relay context, relayTid:0x%I64X, relayContext:0x%p",
                   MODULE_NAME, func, relayTid, static_cast<void*>(nullptr));
        logEnd(389, func);
        return true;
    }

    int errorLine = 0;
    wchar_t const* errorText = nullptr;
    wchar_t const* failText = nullptr;
    int failLine = 0;
    switch (relayHeader._hint)
    {
    case CacheEconomy_PingReqCmd:
        errorLine = 329;
        errorText = L"[%s], %s; invalid ping relay, relayTid:0x%I64X, relayFailReason:%d";
        failLine = 334;
        failText = L"[%s], %s; failed to process ping relay error response, relayTid:0x%I64X";
        break;
    case CacheEconomy_RetrieveCharacterInfoReqCmd:
        errorLine = 341;
        errorText = L"[%s], %s; invalid retrieve character info relay, relayTid:0x%I64X, relayFailReason:%d";
        failLine = 346;
        failText = L"[%s], %s; failed to process retrieve character info relay error response, relayTid:0x%I64X";
        break;
    case CacheEconomy_CheckPostCapacityReqCmd:
        errorLine = 353;
        errorText = L"[%s], %s; invalid check post capacity relay, relayTid:0x%I64X, relayFailReason:%d";
        failLine = 358;
        failText = L"[%s], %s; failed to process check post capacity relay error response, relayTid:0x%I64X";
        break;
    case CacheEconomy_DeliverPostReqCmd:
        errorLine = 365;
        errorText = L"[%s], %s; invalid deliver post relay, relayTid:0x%I64X, relayFailReason:%d";
        failLine = 370;
        failText = L"[%s], %s; failed to process deliver post relay error response, relayTid:0x%I64X";
        break;
    default:
        Log::Write(Log::LT_ERROR, CGPH_FILE, 376, L"[%s], %s; invalid request packet command, command:%d", MODULE_NAME, func,
                   static_cast<int>(relayHeader._hint));
        relayContext->removeReferenceCount(CGPH_FILE, 387);
        logEnd(389, func);
        return true;
    }

    Log::Write(Log::LT_ERROR, CGPH_FILE, errorLine, errorText, MODULE_NAME, func, relayTid,
               static_cast<int>(relayInvalidReason));
    DeliverPostRelayResponse response;  // ❓ the original uses this response class for all hints
    response._resultState = RelayResponse::RESULTSTATE_RELAY_ERROR;
    response._failReason = relayInvalidReason;
    if (!relayContext->ProcessRelayResponse(&response))
    {
        Log::Write(Log::LT_ERROR, CGPH_FILE, failLine, failText, MODULE_NAME, func, relayTid);
        relayContext->removeReferenceCount(CGPH_FILE, 387);
        logEnd(389, func);
        return true;
    }
    relayContext->removeReferenceCount(CGPH_FILE, 380);
    logEnd(382, func);
    return true;
}

// 0x8fa0
bool HandleCacheGateHello(Session const* session, Packet const* packet)
{
    logBegin(401, L"HandleCacheGateHello");
    Log::Write(Log::LT_ERROR, CGPH_FILE, 403, L"[%s], %s; not support packet", MODULE_NAME, L"HandleCacheGateHello");
    logEnd(405, L"HandleCacheGateHello");
    return true;
}

// 0x9040
bool HandleCacheGateTheOtherSideListReq(Session const* session, Packet const* packet)
{
    logBegin(412, L"HandleCacheGateTheOtherSideListReq");
    Log::Write(Log::LT_ERROR, CGPH_FILE, 414, L"[%s], %s; not support packet", MODULE_NAME,
               L"HandleCacheGateTheOtherSideListReq");
    logEnd(416, L"HandleCacheGateTheOtherSideListReq");
    return true;
}

// 0x90e0
bool HandleCacheGateTheOtherSideListAck(Session const* session, Packet const* packet)
{
    logBegin(423, L"HandleCacheGateTheOtherSideListAck");
    Log::Write(Log::LT_ERROR, CGPH_FILE, 425, L"[%s], %s; not support packet", MODULE_NAME,
               L"HandleCacheGateTheOtherSideListAck");
    logEnd(427, L"HandleCacheGateTheOtherSideListAck");
    return true;
}
