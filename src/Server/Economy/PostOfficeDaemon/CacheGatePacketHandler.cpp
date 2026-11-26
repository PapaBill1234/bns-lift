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
#include "PingRelay.h"
#include "WorldPacketHandler.h"
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

    if (0 == packet->Decompose("hhhqhqh", &cachegateCmd, &relayHeader._fromWid, &relayHeader._toWid, &relayHeader._relayTid,
                               &relayHeader._hint, &relayHeader._reserved, &economyCmd))
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
            if (handler == nullptr)
            {
                Log::Write(Log::LT_ERROR, CGPH_FILE, 99, L"[%s], %s; invalid cache economy packet command, command:%d",
                           MODULE_NAME, func, static_cast<int>(economyCmd));
            }
            else
            {
                handler(session, packet);
                logEnd(105, func);
                return true;
            }
        }
    }
    logEnd(109, func);
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
            if (handler == nullptr)
            {
                Log::Write(Log::LT_ERROR, CGPH_FILE, 168, L"[%s], %s; invalid cache economy packet command, command:%d",
                           MODULE_NAME, func, static_cast<int>(economyCmd));
                pcb->Clear();
            }
            else
            {
                handler(session, packet);
                logEnd(174, func);
                return true;
            }
        }
    }
    logEnd(181, func);
    return true;
}

// 0x8540
// LIFT: 0x8540 PDB lines 202-284: each hint case has its own typed response, its own ProcessRelayResponse call and a goto to one
// shared error tail ($_ERROR: removeReferenceCount line 282). The early exits go to one shared end log (line 284).
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
    unsigned short serviceWid;
    unsigned long long relayTid;
    RelayContext* relayContext;

    if (packet->Decompose("hhhqhqE", &cachegateCmd, &relayHeader._fromWid, &relayHeader._toWid, &relayHeader._relayTid,
                          &relayHeader._hint, &relayHeader._reserved, &relayFailReason) == 0)
    {
        Log::Write(Log::LT_ERROR, CGPH_FILE, 202, L"[%s], %s; failed to decompose packet", MODULE_NAME, func);
        goto $_END;
    }

    Log::Write(Log::LT_DEBUG, CGPH_FILE, 205,
               L"[%s], %s; decomposed packet, fromWid:%u, toWid:%u, relayTid:0x%I64X, hint:%u, reserved:%I64u, relayFailReason:%d",
               MODULE_NAME, func, static_cast<unsigned int>(relayHeader._fromWid),
               static_cast<unsigned int>(relayHeader._toWid), relayHeader._relayTid,
               static_cast<unsigned int>(relayHeader._hint), relayHeader._reserved, static_cast<int>(relayFailReason));
    serviceWid = PostOfficeDaemon::_instance->_serviceWid;
    if (serviceWid != relayHeader._toWid)
    {
        logInvalidDestination(209, func, serviceWid, relayHeader);
        goto $_END;
    }

    relayTid = relayHeader._relayTid;
    relayContext = PostOfficeDaemon::_instance->_relayContextManager->GetContext(relayTid);
    if (relayContext == nullptr)
    {
        Log::Write(Log::LT_ERROR, CGPH_FILE, 216, L"[%s], %s; no such relay context, relayTid:0x%I64X, relayContext:0x%p",
                   MODULE_NAME, func, relayTid, static_cast<void*>(nullptr));
        goto $_END;
    }

    switch (relayHeader._hint)
    {
    case CacheEconomy_PingReqCmd:
    {
        Log::Write(Log::LT_ERROR, CGPH_FILE, 224, L"[%s], %s; ping relay error, relayTid:0x%I64X, relayFailReason:%d", MODULE_NAME, func, relayTid,
                   static_cast<int>(relayFailReason));
        PingRelayResponse response(RelayResponse::RESULTSTATE_RELAY_ERROR, relayFailReason);
        if (!relayContext->ProcessRelayResponse(&response))
        {
            Log::Write(Log::LT_ERROR, CGPH_FILE, 229, L"[%s], %s; failed to process ping relay error response, relayTid:0x%I64X", MODULE_NAME, func, relayTid);
            goto $_ERROR;
        }
    }
    break;
    case CacheEconomy_RetrieveCharacterInfoReqCmd:
    {
        Log::Write(Log::LT_ERROR, CGPH_FILE, 236, L"[%s], %s; retrieve character info relay error, relayTid:0x%I64X, relayFailReason:%d", MODULE_NAME, func, relayTid,
                   static_cast<int>(relayFailReason));
        RetrieveCharacterInfoRelayResponse response(RelayResponse::RESULTSTATE_RELAY_ERROR, relayFailReason);
        if (!relayContext->ProcessRelayResponse(&response))
        {
            Log::Write(Log::LT_ERROR, CGPH_FILE, 241, L"[%s], %s; failed to process retrieve character info relay error response, relayTid:0x%I64X", MODULE_NAME, func, relayTid);
            goto $_ERROR;
        }
    }
    break;
    case CacheEconomy_CheckPostCapacityReqCmd:
    {
        Log::Write(Log::LT_ERROR, CGPH_FILE, 248, L"[%s], %s; check post capacity relay error, relayTid:0x%I64X, relayFailReason:%d", MODULE_NAME, func, relayTid,
                   static_cast<int>(relayFailReason));
        CheckPostCapacityRelayResponse response(RelayResponse::RESULTSTATE_RELAY_ERROR, relayFailReason);
        if (!relayContext->ProcessRelayResponse(&response))
        {
            Log::Write(Log::LT_ERROR, CGPH_FILE, 253, L"[%s], %s; failed to process check post capacity relay error response, relayTid:0x%I64X", MODULE_NAME, func, relayTid);
            goto $_ERROR;
        }
    }
    break;
    case CacheEconomy_DeliverPostReqCmd:
    {
        Log::Write(Log::LT_ERROR, CGPH_FILE, 260, L"[%s], %s; deliver post relay error, relayTid:0x%I64X, relayFailReason:%d", MODULE_NAME, func, relayTid,
                   static_cast<int>(relayFailReason));
        DeliverPostRelayResponse response(RelayResponse::RESULTSTATE_RELAY_ERROR, relayFailReason);
        if (!relayContext->ProcessRelayResponse(&response))
        {
            Log::Write(Log::LT_ERROR, CGPH_FILE, 265, L"[%s], %s; failed to process deliver post relay error response, relayTid:0x%I64X", MODULE_NAME, func, relayTid);
            goto $_ERROR;
        }
    }
    break;
    default:
        Log::Write(Log::LT_ERROR, CGPH_FILE, 271, L"[%s], %s; invalid request packet command, command:%d", MODULE_NAME, func,
                   static_cast<int>(static_cast<short>(relayHeader._hint)));
        goto $_ERROR;
    }
    relayContext->removeReferenceCount(CGPH_FILE, 275);
    logEnd(277, func);
    return true;

$_ERROR:
    relayContext->removeReferenceCount(CGPH_FILE, 282);
$_END:
    logEnd(284, func);
    return true;
}

// 0x8a60
// LIFT: 0x8a60 PDB lines 307-389: each hint case has its own typed response, its own ProcessRelayResponse call and a goto to one
// shared error tail ($_ERROR: removeReferenceCount line 387). The early exits go to one shared end log (line 389).
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
    unsigned short serviceWid;
    unsigned long long relayTid;
    RelayContext* relayContext;

    if (packet->Decompose("hhhqhqhh", &cachegateCmd, &relayHeader._fromWid, &relayHeader._toWid, &relayHeader._relayTid,
                          &relayHeader._hint, &relayHeader._reserved, &toWid, &relayInvalidReason) == 0)
    {
        Log::Write(Log::LT_ERROR, CGPH_FILE, 307, L"[%s], %s; failed to decompose packet", MODULE_NAME, func);
        goto $_END;
    }

    Log::Write(Log::LT_DEBUG, CGPH_FILE, 310,
               L"[%s], %s; decomposed packet, fromWid:%u, toWid:%u, relayTid:0x%I64X, hint:%u, reserved:%I64u, toWid:%u, relayInvalidReason:%d",
               MODULE_NAME, func, static_cast<unsigned int>(relayHeader._fromWid),
               static_cast<unsigned int>(relayHeader._toWid), relayHeader._relayTid,
               static_cast<unsigned int>(relayHeader._hint), relayHeader._reserved, static_cast<unsigned int>(toWid),
               static_cast<int>(relayInvalidReason));
    serviceWid = PostOfficeDaemon::_instance->_serviceWid;
    if (serviceWid != relayHeader._toWid)
    {
        logInvalidDestination(314, func, serviceWid, relayHeader);
        goto $_END;
    }

    relayTid = relayHeader._relayTid;
    relayContext = PostOfficeDaemon::_instance->_relayContextManager->GetContext(relayTid);
    if (relayContext == nullptr)
    {
        Log::Write(Log::LT_ERROR, CGPH_FILE, 321, L"[%s], %s; no such relay context, relayTid:0x%I64X, relayContext:0x%p",
                   MODULE_NAME, func, relayTid, static_cast<void*>(nullptr));
        goto $_END;
    }

    switch (relayHeader._hint)
    {
    case CacheEconomy_PingReqCmd:
    {
        Log::Write(Log::LT_ERROR, CGPH_FILE, 329, L"[%s], %s; invalid ping relay, relayTid:0x%I64X, relayFailReason:%d", MODULE_NAME, func, relayTid,
                   static_cast<int>(relayInvalidReason));
        PingRelayResponse response(RelayResponse::RESULTSTATE_RELAY_ERROR, relayInvalidReason);
        if (!relayContext->ProcessRelayResponse(&response))
        {
            Log::Write(Log::LT_ERROR, CGPH_FILE, 334, L"[%s], %s; failed to process ping relay error response, relayTid:0x%I64X", MODULE_NAME, func, relayTid);
            goto $_ERROR;
        }
    }
    break;
    case CacheEconomy_RetrieveCharacterInfoReqCmd:
    {
        Log::Write(Log::LT_ERROR, CGPH_FILE, 341, L"[%s], %s; invalid retrieve character info relay, relayTid:0x%I64X, relayFailReason:%d", MODULE_NAME, func, relayTid,
                   static_cast<int>(relayInvalidReason));
        RetrieveCharacterInfoRelayResponse response(RelayResponse::RESULTSTATE_RELAY_ERROR, relayInvalidReason);
        if (!relayContext->ProcessRelayResponse(&response))
        {
            Log::Write(Log::LT_ERROR, CGPH_FILE, 346, L"[%s], %s; failed to process retrieve character info relay error response, relayTid:0x%I64X", MODULE_NAME, func, relayTid);
            goto $_ERROR;
        }
    }
    break;
    case CacheEconomy_CheckPostCapacityReqCmd:
    {
        Log::Write(Log::LT_ERROR, CGPH_FILE, 353, L"[%s], %s; invalid check post capacity relay, relayTid:0x%I64X, relayFailReason:%d", MODULE_NAME, func, relayTid,
                   static_cast<int>(relayInvalidReason));
        CheckPostCapacityRelayResponse response(RelayResponse::RESULTSTATE_RELAY_ERROR, relayInvalidReason);
        if (!relayContext->ProcessRelayResponse(&response))
        {
            Log::Write(Log::LT_ERROR, CGPH_FILE, 358, L"[%s], %s; failed to process check post capacity relay error response, relayTid:0x%I64X", MODULE_NAME, func, relayTid);
            goto $_ERROR;
        }
    }
    break;
    case CacheEconomy_DeliverPostReqCmd:
    {
        Log::Write(Log::LT_ERROR, CGPH_FILE, 365, L"[%s], %s; invalid deliver post relay, relayTid:0x%I64X, relayFailReason:%d", MODULE_NAME, func, relayTid,
                   static_cast<int>(relayInvalidReason));
        DeliverPostRelayResponse response(RelayResponse::RESULTSTATE_RELAY_ERROR, relayInvalidReason);
        if (!relayContext->ProcessRelayResponse(&response))
        {
            Log::Write(Log::LT_ERROR, CGPH_FILE, 370, L"[%s], %s; failed to process deliver post relay error response, relayTid:0x%I64X", MODULE_NAME, func, relayTid);
            goto $_ERROR;
        }
    }
    break;
    default:
        Log::Write(Log::LT_ERROR, CGPH_FILE, 376, L"[%s], %s; invalid request packet command, command:%d", MODULE_NAME, func,
                   static_cast<int>(relayHeader._hint));
        goto $_ERROR;
    }
    relayContext->removeReferenceCount(CGPH_FILE, 380);
    logEnd(382, func);
    return true;

$_ERROR:
    relayContext->removeReferenceCount(CGPH_FILE, 387);
$_END:
    logEnd(389, func);
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
