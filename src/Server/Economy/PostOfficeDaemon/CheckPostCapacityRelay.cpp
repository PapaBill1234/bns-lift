// CheckPostCapacityRelay.obj (PostOfficeDaemon PDB). Class declarations are in WorldPacketHandler.h.
#include "WorldPacketHandler.h"
#include "Log.h"
#include "AlertSender.h"
#include "Packet.h"
#include "CacheGateChannel.h"
#include "WorldChannel.h"
#include "PostOfficeDaemon.h"

#define CHECK_POST_CAPACITY_RELAY_FILE L"CheckPostCapacityRelay.cpp"
static wchar_t const* const MODULE_NAME = L"relay context";  // PDB MODULE_NAME

#define CHECK_POST_CAPACITY_RELAY_CRASH(line, fmt, ...)                                     \
    do                                                                                      \
    {                                                                                       \
        Log::Write(Log::LT_ERROR, CHECK_POST_CAPACITY_RELAY_FILE, line, fmt, __VA_ARGS__);  \
        AlertSender::Write(CHECK_POST_CAPACITY_RELAY_FILE, line, fmt, __VA_ARGS__);         \
    } while (0)

// LIFT: folded with 0x34c40
bool CheckPostCapacityRelayContext::ComposeRequestPacket(FragmentPacket&) const
{
    return true;
}

// LIFT: folded with 0x34c40
bool CheckPostCapacityRelayContext::ComposeResponsePacket(FragmentPacket&) const
{
    return true;
}

// 0x9180
bool CheckPostCapacityRelayContext::processRelayRequest(Channel* const channel) const
{
    if (channel == nullptr)
    {
        CHECK_POST_CAPACITY_RELAY_CRASH(30, L"== CRASH == [%s], %s; invalid parameter, channel:0x%p",
                                        MODULE_NAME, L"CheckPostCapacityRelayContext::processRelayRequest",
                                        static_cast<Channel*>(nullptr));
        return false;
    }

    unsigned long long const relayTid = _economyHeader._relayTid;
    if (!static_cast<CacheGateChannel*>(channel)->SendRelayRequest(this))
    {
        Log::Write(Log::LT_ERROR, CHECK_POST_CAPACITY_RELAY_FILE, 37,
                   L"[%s], %s; failed to send check post capacity relay request, relayTid:0x%I64X",
                   MODULE_NAME, L"CheckPostCapacityRelayContext::processRelayRequest", relayTid);
        return false;
    }

    Log::Write(Log::LT_NOTICE, CHECK_POST_CAPACITY_RELAY_FILE, 41,
               L"[%s], %s; sent check post capacity relay request, relayTid:0x%I64X", MODULE_NAME,
               L"CheckPostCapacityRelayContext::processRelayRequest", relayTid);
    return true;
}

// 0x9280
bool CheckPostCapacityRelayContext::processRelayResponse() const
{
    unsigned long long const relayTid = _economyHeader._relayTid;
    WorldChannel* const worldChannel = PostOfficeDaemon::_instance->_worldChannelManager->GetWorldChannel(GetRequestWid());
    if (worldChannel == nullptr)
    {
        Log::Write(Log::LT_ERROR, CHECK_POST_CAPACITY_RELAY_FILE, 51,
                   L"[%s], %s; world is not connecting; cannot send packet, relayTid:0x%I64X",
                   MODULE_NAME, L"CheckPostCapacityRelayContext::processRelayResponse", relayTid);
        return false;
    }

    if (!worldChannel->SendRelayResponse(this))
    {
        Log::Write(Log::LT_ERROR, CHECK_POST_CAPACITY_RELAY_FILE, 56,
                   L"[%s], %s; failed to send check post capacity %s response ack, relayTid:0x%I64X",
                   MODULE_NAME, L"CheckPostCapacityRelayContext::processRelayResponse",
                   _response._resultState == RelayResponse::RESULTSTATE_SUCCESS ? L"success" : L"failure", relayTid);
        worldChannel->removeReferenceCount(CHECK_POST_CAPACITY_RELAY_FILE, 57);
        return false;
    }

    Log::Write(Log::LT_NOTICE, CHECK_POST_CAPACITY_RELAY_FILE, 61,
               L"[%s], %s; sent check post capacity %s response ack, relayTid:0x%I64X", MODULE_NAME,
               L"CheckPostCapacityRelayContext::processRelayResponse",
               _response._resultState == RelayResponse::RESULTSTATE_SUCCESS ? L"success" : L"failure", relayTid);
    worldChannel->removeReferenceCount(CHECK_POST_CAPACITY_RELAY_FILE, 62);
    return true;
}

// 0x9400
bool CheckPostCapacityRelayContext::processRelayTimeout()
{
    CheckPostCapacityRelayResponse response(RelayResponse::RESULTSTATE_RELAY_TIMEOUT, 19);
    initResponse(&response);
    return processRelayResponse();
}

// 0x9450
RelayHeader const CheckPostCapacityRelayContext::MakeRelayHeader() const
{
    RelayHeader relayHeader;
    relayHeader._fromWid = PostOfficeDaemon::_instance->_serviceWid;
    relayHeader._toWid = _economyHeader._toWid;
    relayHeader._relayTid = _economyHeader._relayTid;
    relayHeader._hint = 1040;
    relayHeader._reserved = 0;
    return relayHeader;
}

// 0x9490
bool CheckPostCapacityRelayContext::ComposeRequestPacket(Packet& packet) const
{
    bool const composed = packet.Compose("hhhqqq", 1040, static_cast<int>(_economyHeader._fromWid),
                                         static_cast<int>(_economyHeader._toWid), _economyHeader._relayTid,
                                         _request._gameTid, _request._targetPcId) != 0;
    long long const targetPcId = _request._targetPcId;
    long long const gameTid = _request._gameTid;
    unsigned long long const relayTid = _economyHeader._relayTid;
    unsigned int const toWid = _economyHeader._toWid;
    unsigned int const fromWid = _economyHeader._fromWid;
    if (!composed)
    {
        Log::Write(Log::LT_ERROR, CHECK_POST_CAPACITY_RELAY_FILE, 87,
                   L"[%s], %s; failed to compose check post capacity relay request packet, fromWid:%u, toWid:%u, relayTid:0x%I64X, gameTid:0x%I64X, targetPcId:0x%I64X",
                   MODULE_NAME, L"CheckPostCapacityRelayContext::ComposeRequestPacket", fromWid, toWid,
                   relayTid, gameTid, targetPcId);
        return false;
    }

    Log::Write(Log::LT_DEBUG, CHECK_POST_CAPACITY_RELAY_FILE, 91,
               L"[%s], %s; composed check post capacity relay request packet, fromWid:%u, toWid:%u, relayTid:0x%I64X, gameTid:0x%I64X, targetPcId:0x%I64X",
               MODULE_NAME, L"CheckPostCapacityRelayContext::ComposeRequestPacket", fromWid, toWid,
               relayTid, gameTid, targetPcId);
    return true;
}

// 0x9570
bool CheckPostCapacityRelayContext::ComposeResponsePacket(Packet& packet) const
{
    int const resultState = _response._resultState;
    unsigned long long const relayTid = _economyHeader._relayTid;
    if (resultState == RelayResponse::RESULTSTATE_SUCCESS)
    {
        bool const composed = packet.Compose("hq", 8, _request._gameTid) != 0;
        if (!composed)
        {
            Log::Write(Log::LT_ERROR, CHECK_POST_CAPACITY_RELAY_FILE, 106,
                       L"[%s], %s; failed to compose check post capacity success response packet, gameTid:0x%I64X",
                       MODULE_NAME, L"CheckPostCapacityRelayContext::ComposeResponsePacket",
                       _request._gameTid);
            return false;
        }
        Log::Write(Log::LT_DEBUG, CHECK_POST_CAPACITY_RELAY_FILE, 109,
                   L"[%s], %s; composed check post capacity success response packet, gameTid:0x%I64X",
                   MODULE_NAME, L"CheckPostCapacityRelayContext::ComposeResponsePacket", _request._gameTid);
        return true;
    }

    if (resultState < RelayResponse::RESULTSTATE_FAILURE || resultState > RelayResponse::RESULTSTATE_RELAY_TIMEOUT)
    {
        CHECK_POST_CAPACITY_RELAY_CRASH(127,
                                        L"== CRASH == [%s], %s; invalid response result state, relayTid:0x%I64X, resultState:%d",
                                        MODULE_NAME, L"CheckPostCapacityRelayContext::ComposeResponsePacket",
                                        relayTid, resultState);
        return false;
    }

    int const failReason = convertFailReason(static_cast<RelayResponse::ResultState>(resultState), _response._failReason);
    bool const composed = packet.Compose("hqE", 9, _request._gameTid, failReason) != 0;
    if (!composed)
    {
        Log::Write(Log::LT_ERROR, CHECK_POST_CAPACITY_RELAY_FILE, 120,
                   L"[%s], %s; failed to compose check post capacity failure response packet, gameTid:0x%I64X, failReason:%d",
                   MODULE_NAME, L"CheckPostCapacityRelayContext::ComposeResponsePacket", _request._gameTid,
                   failReason);
        return false;
    }
    Log::Write(Log::LT_DEBUG, CHECK_POST_CAPACITY_RELAY_FILE, 123,
               L"[%s], %s; composed check post capacity failure response packet, gameTid:0x%I64X, failReason:%d",
               MODULE_NAME, L"CheckPostCapacityRelayContext::ComposeResponsePacket", _request._gameTid,
               failReason);
    return true;
}

// 0x9740
__declspec(noinline) short const CheckPostCapacityRelayContext::convertFailReason(RelayResponse::ResultState const resultState, short const failReason) const
{
    switch (resultState)
    {
    case RelayResponse::RESULTSTATE_FAILURE:
        switch (failReason)
        {
        case 14:
            return 15;
        case 15:
            return 16;
        case 16:
            return 17;
        default:
            break;
        }
        break;
    case RelayResponse::RESULTSTATE_RELAY_ERROR:
        switch (failReason)
        {
        case 3:
        case 9:
            return 4;
        case 8:
            return 20;
        case 10:
        case 11:
            return 2;
        default:
            break;
        }
        break;
    case RelayResponse::RESULTSTATE_RELAY_TIMEOUT:
        return 19;
    default:
        break;
    }
    return 1;
}
