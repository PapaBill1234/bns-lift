// CacheEconomyPacketHandler.obj (PostOfficeDaemon PDB). Source: .scratch/hr/CacheEconomyPacketHandler.c
// Each handler inlines the static guard init of RelayHeader::GetMemberOffset. The lift skips it (no effect here).
// Each Decompose call in the original is Packet::Decompose(packet, 0x18, 6, fmt, ...). ❓ Packet.h has no overload
// with these two arguments. The lift calls Decompose(fmt, ...).
#include <winsock2.h>
#include <windows.h>
#include "CacheEconomyPacketHandler.h"
#include "DeliverPostRelay.h"
#include "Log.h"
#include "Packet.h"
#include "PingRelay.h"
#include "PostOfficeDaemon.h"
#include "RelayContext.h"
#include "Session.h"
#include "WorldPacketHandler.h"

namespace
{
wchar_t const* const CEPH_FILE = L"CacheEconomyPacketHandler.cpp";  // ❓ name
wchar_t const* const CEPH_TAG = L"cache economy packet handler";    // ❓ name

// ❓ Not in the PDB. The original inlines these line numbers in each handler.
struct ResponseLines
{
    int noContext;
    int mismatch;
    int processFail;
    int okRef;
    int okEnd;
    int failRef;
    int end;
};

// ❓ Not in the PDB. Helper for the BEGIN/END logs that each handler inlines.
void logBegin(wchar_t const* funcName, int line)
{
    Log::Write(Log::LT_DEBUG, CEPH_FILE, line, L"[%s], %s; <BEGIN PACKET HANDLER>", CEPH_TAG, funcName);
}

void logEnd(wchar_t const* funcName, int line)
{
    Log::Write(Log::LT_DEBUG, CEPH_FILE, line, L"[%s], %s; <END PACKET HANDLER>", CEPH_TAG, funcName);
}

// ❓ Not in the PDB. The original inlines this sequence in each handler (find context, check header, process response).
bool processEconomyResponse(wchar_t const* funcName, EconomyHeader const& economyHeader, RelayResponse* const response,
                            wchar_t const* processFailText, ResponseLines const& lines)
{
    unsigned long long const relayTid = economyHeader._relayTid;
    RelayContext* const relayContext = PostOfficeDaemon::_instance->_relayContextManager->GetContext(relayTid);
    if (relayContext == nullptr)
    {
        Log::Write(Log::LT_ERROR, CEPH_FILE, lines.noContext,
                   L"[%s], %s; no such relay context, relayTid:0x%I64X, relayContext:0x%p", CEPH_TAG, funcName, relayTid,
                   static_cast<RelayContext*>(nullptr));
        logEnd(funcName, lines.end);
        return false;
    }

    EconomyHeader const& requestHeader = relayContext->_economyHeader;
    if (requestHeader._fromWid != economyHeader._fromWid || requestHeader._toWid != economyHeader._toWid ||
        requestHeader._relayTid != economyHeader._relayTid)
    {
        Log::Write(Log::LT_ERROR, CEPH_FILE, lines.mismatch,
                   L"[%s], %s; economy header mismatch; invalid economy header, [request] fromWid:%u, toWid:%u, relayTid:0x%I64X, [response] fromWid:%u, toWid:%u, relayTid:0x%I64X",
                   CEPH_TAG, funcName, static_cast<unsigned int>(requestHeader._fromWid),
                   static_cast<unsigned int>(requestHeader._toWid), requestHeader._relayTid,
                   static_cast<unsigned int>(economyHeader._fromWid), static_cast<unsigned int>(economyHeader._toWid),
                   economyHeader._relayTid);
    }
    else if (relayContext->ProcessRelayResponse(response))
    {
        relayContext->removeReferenceCount(CEPH_FILE, lines.okRef);
        logEnd(funcName, lines.okEnd);
        return true;
    }
    else
    {
        Log::Write(Log::LT_ERROR, CEPH_FILE, lines.processFail, processFailText, CEPH_TAG, funcName, relayTid);
    }

    relayContext->removeReferenceCount(CEPH_FILE, lines.failRef);
    logEnd(funcName, lines.end);
    return false;
}

void clearHeader(EconomyHeader& economyHeader)
{
    economyHeader._fromWid = 0;
    economyHeader._toWid = 0;
    economyHeader._relayTid = 0;
}

bool notSupported(wchar_t const* funcName, int beginLine)
{
    logBegin(funcName, beginLine);
    Log::Write(Log::LT_ERROR, CEPH_FILE, beginLine + 2, L"[%s], %s; not support packet command", CEPH_TAG, funcName);
    logEnd(funcName, beginLine + 4);
    return true;
}
}  // namespace

// 0x5120
bool HandleCacheEconomyPingOk(Session const* session, Packet const* packet)
{
    (void)session;
    wchar_t const* const funcName = L"HandleCacheEconomyPingOk";
    logBegin(funcName, 34);
    short cmd = 0;
    EconomyHeader economyHeader;
    clearHeader(economyHeader);
    PingRelayResponse response;
    response._resultState = RelayResponse::RESULTSTATE_SUCCESS;
    response._failReason = 0;
    response._pingSeq = 0;

    if (packet->Decompose("hhhqq", &cmd, &economyHeader._fromWid, &economyHeader._toWid, &economyHeader._relayTid,
                          &response._pingSeq) == 0)
    {
        Log::Write(Log::LT_ERROR, CEPH_FILE, 46, L"[%s], %s; failed to decompose packet", CEPH_TAG, funcName);
        logEnd(funcName, 85);
        return false;
    }
    Log::Write(Log::LT_DEBUG, CEPH_FILE, 49,
               L"[%s], %s; decomposed packet, fromWid:%u, toWid:%u, relayTid:0x%I64X, pingSeq:%I64u", CEPH_TAG, funcName,
               static_cast<unsigned int>(economyHeader._fromWid), static_cast<unsigned int>(economyHeader._toWid),
               economyHeader._relayTid, response._pingSeq);
    if (economyHeader._relayTid == 0)
    {
        Log::Write(Log::LT_ERROR, CEPH_FILE, 53, L"[%s], %s; invalid parameter, relayTid:0x%I64X", CEPH_TAG, funcName,
                   economyHeader._relayTid);
        logEnd(funcName, 85);
        return false;
    }

    ResponseLines const lines = {60, 67, 72, 76, 78, 83, 85};
    return processEconomyResponse(funcName, economyHeader, &response,
                                  L"[%s], %s; failed to process ping ok response, relayTid:0x%I64X", lines);
}

// 0x5490
bool HandleCacheEconomyPingFail(Session const* session, Packet const* packet)
{
    (void)session;
    wchar_t const* const funcName = L"HandleCacheEconomyPingFail";
    logBegin(funcName, 92);
    short cmd = 0;
    EconomyHeader economyHeader;
    clearHeader(economyHeader);
    PingRelayResponse response;
    // ❓ The binary stores the raw value 2 here. With the RESULTSTATE values in RelayContext.h this is RELAY_ERROR.
    // It can be FAILURE if the PDB enum starts at 1 (see convertFailReason).
    response._resultState = 2;
    response._failReason = 0;
    response._pingSeq = 0;

    if (packet->Decompose("hhhqqE", &cmd, &economyHeader._fromWid, &economyHeader._toWid, &economyHeader._relayTid,
                          &response._pingSeq, &response._failReason) == 0)
    {
        Log::Write(Log::LT_ERROR, CEPH_FILE, 105, L"[%s], %s; failed to decompose packet", CEPH_TAG, funcName);
        logEnd(funcName, 144);
        return false;
    }
    Log::Write(Log::LT_DEBUG, CEPH_FILE, 108,
               L"[%s], %s; decomposed packet, fromWid:%u, toWid:%u, relayTid:0x%I64X, pingSeq:%I64u, failReason:%d",
               CEPH_TAG, funcName, static_cast<unsigned int>(economyHeader._fromWid),
               static_cast<unsigned int>(economyHeader._toWid), economyHeader._relayTid, response._pingSeq,
               static_cast<int>(response._failReason));
    if (economyHeader._relayTid == 0)
    {
        Log::Write(Log::LT_ERROR, CEPH_FILE, 112, L"[%s], %s; invalid parameter, relayTid:0x%I64X", CEPH_TAG, funcName,
                   economyHeader._relayTid);
        logEnd(funcName, 144);
        return false;
    }

    ResponseLines const lines = {119, 126, 131, 135, 137, 142, 144};
    // BUG: 0x5490 the log text says "deliver post fail" but this is the ping fail handler (copy-paste in the original).
    return processEconomyResponse(funcName, economyHeader, &response,
                                  L"[%s], %s; failed to process deliver post fail response, relayTid:0x%I64X", lines);
}

// 0x57f0
bool HandleCacheEconomyRetrieveCharacterInfoOk(Session const* session, Packet const* packet)
{
    (void)session;
    wchar_t const* const funcName = L"HandleCacheEconomyRetrieveCharacterInfoOk";
    logBegin(funcName, 151);
    short cmd = 0;
    EconomyHeader economyHeader;
    clearHeader(economyHeader);
    unsigned long long gameTid = 0;
    RetrieveCharacterInfoRelayResponse response;
    response._resultState = RelayResponse::RESULTSTATE_SUCCESS;
    response._failReason = 0;
    response._resultPcId = 0;

    if (packet->Decompose("hhhqqq", &cmd, &economyHeader._fromWid, &economyHeader._toWid, &economyHeader._relayTid,
                          &gameTid, &response._resultPcId) == 0)
    {
        Log::Write(Log::LT_ERROR, CEPH_FILE, 165, L"[%s], %s; failed to decompose packet", CEPH_TAG, funcName);
        logEnd(funcName, 204);
        return false;
    }
    Log::Write(Log::LT_DEBUG, CEPH_FILE, 168,
               L"[%s], %s; decomposed packet, fromWid:%u, toWid:%u, relayTid:0x%I64X, gameTid:0x%I64X, resultPcId:0x%I64X",
               CEPH_TAG, funcName, static_cast<unsigned int>(economyHeader._fromWid),
               static_cast<unsigned int>(economyHeader._toWid), economyHeader._relayTid, gameTid, response._resultPcId);
    if (economyHeader._relayTid == 0 || gameTid == 0 || response._resultPcId == 0)
    {
        Log::Write(Log::LT_ERROR, CEPH_FILE, 172,
                   L"[%s], %s; invalid parameter, relayTid:0x%I64X, gameTid:0x%I64X, resultPcId:0x%I64X", CEPH_TAG,
                   funcName, economyHeader._relayTid, gameTid, response._resultPcId);
        logEnd(funcName, 204);
        return false;
    }

    ResponseLines const lines = {179, 186, 191, 195, 197, 202, 204};
    return processEconomyResponse(
        funcName, economyHeader, &response,
        L"[%s], %s; failed to process retrieve character info ok response, relayTid:0x%I64X", lines);
}

// 0x5b80
bool HandleCacheEconomyRetrieveCharacterInfoFail(Session const* session, Packet const* packet)
{
    (void)session;
    wchar_t const* const funcName = L"HandleCacheEconomyRetrieveCharacterInfoFail";
    logBegin(funcName, 211);
    short cmd = 0;
    EconomyHeader economyHeader;
    clearHeader(economyHeader);
    unsigned long long gameTid = 0;
    RetrieveCharacterInfoRelayResponse response;
    response._resultState = RelayResponse::RESULTSTATE_FAILURE;
    response._failReason = 0;
    response._resultPcId = 0;

    if (packet->Decompose("hhhqqE", &cmd, &economyHeader._fromWid, &economyHeader._toWid, &economyHeader._relayTid,
                          &gameTid, &response._failReason) == 0)
    {
        Log::Write(Log::LT_ERROR, CEPH_FILE, 225, L"[%s], %s; failed to decompose packet", CEPH_TAG, funcName);
        logEnd(funcName, 264);
        return false;
    }
    Log::Write(Log::LT_DEBUG, CEPH_FILE, 228,
               L"[%s], %s; decomposed packet, fromWid:%u, toWid:%u, relayTid:0x%I64X, gameTid:0x%I64X, failReason:%d",
               CEPH_TAG, funcName, static_cast<unsigned int>(economyHeader._fromWid),
               static_cast<unsigned int>(economyHeader._toWid), economyHeader._relayTid, gameTid,
               static_cast<int>(response._failReason));
    if (economyHeader._relayTid == 0 || gameTid == 0)
    {
        Log::Write(Log::LT_ERROR, CEPH_FILE, 232, L"[%s], %s; invalid parameter, relayTid:0x%I64X, gameTid:0x%I64X",
                   CEPH_TAG, funcName, economyHeader._relayTid, gameTid);
        logEnd(funcName, 264);
        return false;
    }

    ResponseLines const lines = {239, 246, 251, 255, 257, 262, 264};
    return processEconomyResponse(
        funcName, economyHeader, &response,
        L"[%s], %s; failed to process retrieve character info fail response, relayTid:0x%I64X", lines);
}

// 0x5ee0
bool HandleCacheEconomyCheckPostCapacityOk(Session const* session, Packet const* packet)
{
    (void)session;
    wchar_t const* const funcName = L"HandleCacheEconomyCheckPostCapacityOk";
    logBegin(funcName, 271);
    short cmd = 0;
    EconomyHeader economyHeader;
    clearHeader(economyHeader);
    unsigned long long gameTid = 0;
    CheckPostCapacityRelayResponse response;
    response._resultState = RelayResponse::RESULTSTATE_SUCCESS;
    response._failReason = 0;

    if (packet->Decompose("hhhqq", &cmd, &economyHeader._fromWid, &economyHeader._toWid, &economyHeader._relayTid,
                          &gameTid) == 0)
    {
        Log::Write(Log::LT_ERROR, CEPH_FILE, 284, L"[%s], %s; failed to decompose packet", CEPH_TAG, funcName);
        logEnd(funcName, 323);
        return false;
    }
    Log::Write(Log::LT_DEBUG, CEPH_FILE, 287,
               L"[%s], %s; decomposed packet, fromWid:%u, toWid:%u, relayTid:0x%I64X, gameTid:0x%I64X", CEPH_TAG,
               funcName, static_cast<unsigned int>(economyHeader._fromWid),
               static_cast<unsigned int>(economyHeader._toWid), economyHeader._relayTid, gameTid);
    if (economyHeader._relayTid == 0 || gameTid == 0)
    {
        Log::Write(Log::LT_ERROR, CEPH_FILE, 291, L"[%s], %s; invalid parameter, relayTid:0x%I64X, gameTid:0x%I64X",
                   CEPH_TAG, funcName, economyHeader._relayTid, gameTid);
        logEnd(funcName, 323);
        return false;
    }

    ResponseLines const lines = {298, 305, 310, 314, 316, 321, 323};
    return processEconomyResponse(funcName, economyHeader, &response,
                                  L"[%s], %s; failed to process check post capacity ok response, relayTid:0x%I64X",
                                  lines);
}

// 0x6260
bool HandleCacheEconomyCheckPostCapacityFail(Session const* session, Packet const* packet)
{
    (void)session;
    wchar_t const* const funcName = L"HandleCacheEconomyCheckPostCapacityFail";
    logBegin(funcName, 330);
    short cmd = 0;
    EconomyHeader economyHeader;
    clearHeader(economyHeader);
    unsigned long long gameTid = 0;
    CheckPostCapacityRelayResponse response;
    response._resultState = RelayResponse::RESULTSTATE_FAILURE;
    response._failReason = 0;

    if (packet->Decompose("hhhqqE", &cmd, &economyHeader._fromWid, &economyHeader._toWid, &economyHeader._relayTid,
                          &gameTid, &response._failReason) == 0)
    {
        Log::Write(Log::LT_ERROR, CEPH_FILE, 344, L"[%s], %s; failed to decompose packet", CEPH_TAG, funcName);
        logEnd(funcName, 383);
        return false;
    }
    Log::Write(Log::LT_DEBUG, CEPH_FILE, 347,
               L"[%s], %s; decomposed packet, fromWid:%u, toWid:%u, relayTid:0x%I64X, gameTid:0x%I64X, failReason:%d",
               CEPH_TAG, funcName, static_cast<unsigned int>(economyHeader._fromWid),
               static_cast<unsigned int>(economyHeader._toWid), economyHeader._relayTid, gameTid,
               static_cast<int>(response._failReason));
    if (economyHeader._relayTid == 0 || gameTid == 0)
    {
        Log::Write(Log::LT_ERROR, CEPH_FILE, 351, L"[%s], %s; invalid parameter, relayTid:0x%I64X, gameTid:0x%I64X",
                   CEPH_TAG, funcName, economyHeader._relayTid, gameTid);
        logEnd(funcName, 383);
        return false;
    }

    ResponseLines const lines = {358, 365, 370, 374, 376, 381, 383};
    return processEconomyResponse(funcName, economyHeader, &response,
                                  L"[%s], %s; failed to process check post capacity fail response, relayTid:0x%I64X",
                                  lines);
}

// 0x65c0
bool HandleCacheEconomyDeliverPostOk(Session const* session, Packet const* packet)
{
    (void)session;
    wchar_t const* const funcName = L"HandleCacheEconomyDeliverPostOk";
    logBegin(funcName, 390);
    short cmd = 0;
    EconomyHeader economyHeader;
    clearHeader(economyHeader);
    DeliverPostRelayResponse response;
    response._resultState = RelayResponse::RESULTSTATE_SUCCESS;
    response._failReason = 0;

    if (packet->Decompose("hhhq", &cmd, &economyHeader._fromWid, &economyHeader._toWid, &economyHeader._relayTid) == 0)
    {
        Log::Write(Log::LT_ERROR, CEPH_FILE, 401, L"[%s], %s; failed to decompose packet", CEPH_TAG, funcName);
        logEnd(funcName, 440);
        return false;
    }
    Log::Write(Log::LT_DEBUG, CEPH_FILE, 404, L"[%s], %s; decomposed packet, fromWid:%u, toWid:%u, relayTid:0x%I64X",
               CEPH_TAG, funcName, static_cast<unsigned int>(economyHeader._fromWid),
               static_cast<unsigned int>(economyHeader._toWid), economyHeader._relayTid);
    if (economyHeader._relayTid == 0)
    {
        // The original passes the constant 0 (the relayTid is 0 on this path).
        Log::Write(Log::LT_ERROR, CEPH_FILE, 408, L"[%s], %s; invalid parameter, relayTid:0x%I64X", CEPH_TAG, funcName,
                   0ULL);
        logEnd(funcName, 440);
        return false;
    }

    ResponseLines const lines = {415, 422, 427, 431, 433, 438, 440};
    return processEconomyResponse(funcName, economyHeader, &response,
                                  L"[%s], %s; failed to process deliver post ok response, relayTid:0x%I64X", lines);
}

// 0x6920
bool HandleCacheEconomyDeliverPostFail(Session const* session, Packet const* packet)
{
    (void)session;
    wchar_t const* const funcName = L"HandleCacheEconomyDeliverPostFail";
    logBegin(funcName, 447);
    short cmd = 0;
    EconomyHeader economyHeader;
    clearHeader(economyHeader);
    DeliverPostRelayResponse response;
    response._resultState = RelayResponse::RESULTSTATE_FAILURE;
    response._failReason = 0;

    if (packet->Decompose("hhhqE", &cmd, &economyHeader._fromWid, &economyHeader._toWid, &economyHeader._relayTid,
                          &response._failReason) == 0)
    {
        Log::Write(Log::LT_ERROR, CEPH_FILE, 459, L"[%s], %s; failed to decompose packet", CEPH_TAG, funcName);
        logEnd(funcName, 498);
        return false;
    }
    Log::Write(Log::LT_DEBUG, CEPH_FILE, 462,
               L"[%s], %s; decomposed packet, fromWid:%u, toWid:%u, relayTid:0x%I64X, failReason:%d", CEPH_TAG,
               funcName, static_cast<unsigned int>(economyHeader._fromWid),
               static_cast<unsigned int>(economyHeader._toWid), economyHeader._relayTid,
               static_cast<int>(response._failReason));
    if (economyHeader._relayTid == 0)
    {
        // The original passes the constant 0 (the relayTid is 0 on this path).
        Log::Write(Log::LT_ERROR, CEPH_FILE, 466, L"[%s], %s; invalid parameter, relayTid:0x%I64X", CEPH_TAG, funcName,
                   0ULL);
        logEnd(funcName, 498);
        return false;
    }

    ResponseLines const lines = {473, 480, 485, 489, 491, 496, 498};
    return processEconomyResponse(funcName, economyHeader, &response,
                                  L"[%s], %s; failed to process deliver post fail response, relayTid:0x%I64X", lines);
}

// 0x6c90
bool HandleCacheEconomyHelloOk(Session const* session, Packet const* packet)
{
    (void)session;
    (void)packet;
    return notSupported(L"HandleCacheEconomyHelloOk", 510);
}

// 0x6d30
bool HandleCacheEconomyHelloFail(Session const* session, Packet const* packet)
{
    (void)session;
    (void)packet;
    return notSupported(L"HandleCacheEconomyHelloFail", 521);
}

// 0x6dd0
bool HandleCacheEconomyFail(Session const* session, Packet const* packet)
{
    (void)session;
    (void)packet;
    return notSupported(L"HandleCacheEconomyFail", 532);
}

// 0x6e70
bool HandleCacheEconomyRemovePawnOk(Session const* session, Packet const* packet)
{
    (void)session;
    (void)packet;
    return notSupported(L"HandleCacheEconomyRemovePawnOk", 543);
}

// 0x6f10
bool HandleCacheEconomyRemovePawnFail(Session const* session, Packet const* packet)
{
    (void)session;
    (void)packet;
    return notSupported(L"HandleCacheEconomyRemovePawnFail", 554);
}
