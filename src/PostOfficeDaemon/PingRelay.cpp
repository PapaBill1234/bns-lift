// PingRelay.obj (PostOfficeDaemon PDB).
#include "PingRelay.h"
#include "Log.h"
#include "AlertSender.h"
#include "Packet.h"
#include "PostOfficeDaemon.h"
#include "CachedWatchdog.h"

#define PING_RELAY_FILE L"PingRelay.cpp"
#define PING_RELAY_TAG L"relay context"

#define PING_RELAY_CRASH(line, fmt, ...)                                  \
    do                                                                    \
    {                                                                     \
        Log::Write(Log::LT_ERROR, PING_RELAY_FILE, line, fmt, __VA_ARGS__); \
        AlertSender::Write(PING_RELAY_FILE, line, fmt, __VA_ARGS__);      \
    } while (0)

// 0xaad0
bool PingRelayContext::processRelayRequest(Channel* const channel) const
{
    if (channel == nullptr)
    {
        PING_RELAY_CRASH(28, L"== CRASH == [%s], %s; invalid parameter, channel:0x%p", PING_RELAY_TAG,
                         L"PingRelayContext::processRelayRequest", static_cast<Channel*>(nullptr));
        return false;
    }

    unsigned long long const relayTid = _economyHeader._relayTid;
    // ❓ SendRelayRequest takes a non-const pointer.
    if (!static_cast<CacheGateChannel*>(channel)->SendRelayRequest(const_cast<PingRelayContext*>(this)))
    {
        Log::Write(Log::LT_ERROR, PING_RELAY_FILE, 35, L"[%s], %s; failed to send ping relay request, relayTid:0x%I64X",
                   PING_RELAY_TAG, L"PingRelayContext::processRelayRequest", relayTid);
        return false;
    }

    Log::Write(Log::LT_NOTICE, PING_RELAY_FILE, 39, L"[%s], %s; sent ping relay request, relayTid:0x%I64X",
               PING_RELAY_TAG, L"PingRelayContext::processRelayRequest", relayTid);
    return true;
}

// 0xabd0
bool PingRelayContext::processRelayResponse() const
{
    unsigned short const toWid = _economyHeader._toWid;
    unsigned long long const relayTid = _economyHeader._relayTid;
    CachedWatchdogManager* const cachedWatchdogManager = PostOfficeDaemon::_instance->_cachedWatchdogManager;
    int const resultState = _response._resultState;
    unsigned long long const currentPingSeq = cachedWatchdogManager->GetCurrentPingSeq(toWid);

    switch (resultState)
    {
    case RelayResponse::RESULTSTATE_SUCCESS:
        if (currentPingSeq != _response._pingSeq)
        {
            Log::Write(Log::LT_ERROR, PING_RELAY_FILE, 58,
                       L"[%s], %s; exception occurred; ping sequence number mismatch, relayTid:0x%I64X, destinationWid:%u, currentPingSeq:%I64u, responsePingSeq:%I64u",
                       PING_RELAY_TAG, L"PingRelayContext::processRelayResponse", relayTid, toWid, currentPingSeq,
                       _response._pingSeq);
            return false;
        }
        cachedWatchdogManager->SetServiceState(toWid, SERVICE_STATE_AVAILABLE);
        if (!cachedWatchdogManager->AddNextPing(toWid))
        {
            PING_RELAY_CRASH(64, L"== CRASH == [%s], %s; failed to add next ping, destinationWid:%u", PING_RELAY_TAG,
                             L"PingRelayContext::processRelayResponse", toWid);
            return false;
        }
        return true;

    case RelayResponse::RESULTSTATE_FAILURE:
        Log::Write(Log::LT_ERROR, PING_RELAY_FILE, 72,
                   L"[%s], %s; exception occurred; received ping failure ack, relayTid:0x%I64X, destinationWid:%u",
                   PING_RELAY_TAG, L"PingRelayContext::processRelayResponse", relayTid, toWid);
        if (currentPingSeq != _response._pingSeq)
        {
            Log::Write(Log::LT_ERROR, PING_RELAY_FILE, 77,
                       L"[%s], %s; exception occurred; ping sequence number mismatch, relayTid:0x%I64X, destinationWid:%u, currentPingSeq:%I64u, responsePingSeq:%I64u",
                       PING_RELAY_TAG, L"PingRelayContext::processRelayResponse", relayTid, toWid, currentPingSeq,
                       _response._pingSeq);
            return false;
        }
        break;

    case RelayResponse::RESULTSTATE_RELAY_ERROR:
    case RelayResponse::RESULTSTATE_RELAY_TIMEOUT:
        break;

    default:
        PING_RELAY_CRASH(92, L"== CRASH == [%s], %s; invalid result state, relayTid:0x%I64X, resultState:%d",
                         PING_RELAY_TAG, L"PingRelayContext::processRelayResponse", relayTid, resultState);
        return false;
    }

    cachedWatchdogManager->SetServiceState(toWid, SERVICE_STATE_UNAVAILABLE);
    if (!cachedWatchdogManager->AddNextPing(toWid))
    {
        PING_RELAY_CRASH(86, L"== CRASH == [%s], %s; failed to add next ping, destinationWid:%u", PING_RELAY_TAG,
                         L"PingRelayContext::processRelayResponse", toWid);
        return false;
    }
    return true;
}

// 0xaed0
bool PingRelayContext::processRelayTimeout()
{
    PingRelayResponse response;
    response._resultState = RelayResponse::RESULTSTATE_RELAY_TIMEOUT;
    response._failReason = 0;
    response._pingSeq = 0;
    initResponse(&response);
    return processRelayResponse();
}

// 0xaf30
RelayHeader const PingRelayContext::MakeRelayHeader() const
{
    RelayHeader relayHeader;
    relayHeader._fromWid = PostOfficeDaemon::_instance->_serviceWid;
    relayHeader._toWid = _economyHeader._toWid;
    relayHeader._relayTid = _economyHeader._relayTid;
    relayHeader._hint = 1031;
    relayHeader._reserved = 0;
    return relayHeader;
}

// 0xaf70
bool PingRelayContext::ComposeRequestPacket(Packet& packet) const
{
    unsigned short const fromWid = _economyHeader._fromWid;
    unsigned short const toWid = _economyHeader._toWid;
    unsigned long long const relayTid = _economyHeader._relayTid;
    if (!packet.Compose("hhhqq", 1031, fromWid, toWid, relayTid, _request._pingSeq))
    {
        Log::Write(Log::LT_ERROR, PING_RELAY_FILE, 117,
                   L"[%s], %s; failed to compose ping relay request packet, fromWid:%u, toWid:%u, relayTid:0x%I64X, pingSeq:%I64u",
                   PING_RELAY_TAG, L"PingRelayContext::ComposeRequestPacket", fromWid, toWid, relayTid, _request._pingSeq);
        return false;
    }

    Log::Write(Log::LT_DEBUG, PING_RELAY_FILE, 120,
               L"[%s], %s; composed ping relay request packet, fromWid:%u, toWid:%u, relayTid:0x%I64X, pingSeq:%I64u",
               PING_RELAY_TAG, L"PingRelayContext::ComposeRequestPacket", fromWid, toWid, relayTid, _request._pingSeq);
    return true;
}
