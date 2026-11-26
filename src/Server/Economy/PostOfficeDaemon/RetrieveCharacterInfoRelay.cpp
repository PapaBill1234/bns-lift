// RetrieveCharacterInfoRelay.obj (PostOfficeDaemon PDB). Class declarations are in WorldPacketHandler.h.
#include "WorldPacketHandler.h"
#include "Log.h"
#include "AlertSender.h"
#include "Packet.h"
#include "CacheGateChannel.h"
#include "WorldChannel.h"
#include "PostOfficeDaemon.h"

#define RETRIEVE_CHARACTER_INFO_RELAY_FILE L"RetrieveCharacterInfoRelay.cpp"
static wchar_t const* const MODULE_NAME = L"relay context";  // PDB MODULE_NAME

#define RETRIEVE_CHARACTER_INFO_RELAY_CRASH(line, fmt, ...)                                     \
    do                                                                                          \
    {                                                                                           \
        Log::Write(Log::LT_ERROR, RETRIEVE_CHARACTER_INFO_RELAY_FILE, line, fmt, __VA_ARGS__);  \
        AlertSender::Write(RETRIEVE_CHARACTER_INFO_RELAY_FILE, line, fmt, __VA_ARGS__);         \
    } while (0)

// LIFT: folded with 0x34c40
bool RetrieveCharacterInfoRelayContext::ComposeRequestPacket(FragmentPacket&) const
{
    return true;
}

// LIFT: folded with 0x34c40
bool RetrieveCharacterInfoRelayContext::ComposeResponsePacket(FragmentPacket&) const
{
    return true;
}

// 0x1de30
bool RetrieveCharacterInfoRelayContext::processRelayRequest(Channel* const channel) const
{
    if (channel == nullptr)
    {
        RETRIEVE_CHARACTER_INFO_RELAY_CRASH(30, L"== CRASH == [%s], %s; invalid parameter, channel:0x%p",
                                            MODULE_NAME,
                                            L"RetrieveCharacterInfoRelayContext::processRelayRequest",
                                            static_cast<Channel*>(nullptr));
        return false;
    }

    unsigned long long const relayTid = _economyHeader._relayTid;
    if (!static_cast<CacheGateChannel*>(channel)->SendRelayRequest(this))
    {
        Log::Write(Log::LT_ERROR, RETRIEVE_CHARACTER_INFO_RELAY_FILE, 37,
                   L"[%s], %s; failed to send retrieve character info relay request, relayTid:0x%I64X",
                   MODULE_NAME, L"RetrieveCharacterInfoRelayContext::processRelayRequest", relayTid);
        return false;
    }

    Log::Write(Log::LT_NOTICE, RETRIEVE_CHARACTER_INFO_RELAY_FILE, 41,
               L"[%s], %s; sent retrieve character info relay request, relayTid:0x%I64X", MODULE_NAME,
               L"RetrieveCharacterInfoRelayContext::processRelayRequest", relayTid);
    return true;
}

// 0x1df30
bool RetrieveCharacterInfoRelayContext::processRelayResponse() const
{
    unsigned long long const relayTid = _economyHeader._relayTid;
    WorldChannel* const worldChannel = PostOfficeDaemon::_instance->_worldChannelManager->GetWorldChannel(GetRequestWid());
    if (worldChannel == nullptr)
    {
        Log::Write(Log::LT_ERROR, RETRIEVE_CHARACTER_INFO_RELAY_FILE, 51,
                   L"[%s], %s; world is not connecting; cannot send packet, relayTid:0x%I64X",
                   MODULE_NAME, L"RetrieveCharacterInfoRelayContext::processRelayResponse", relayTid);
        return false;
    }

    if (!worldChannel->SendRelayResponse(this))
    {
        Log::Write(Log::LT_ERROR, RETRIEVE_CHARACTER_INFO_RELAY_FILE, 56,
                   L"[%s], %s; failed to send retrieve character info %s response ack, relayTid:0x%I64X",
                   MODULE_NAME, L"RetrieveCharacterInfoRelayContext::processRelayResponse",
                   _response._resultState == RelayResponse::RESULTSTATE_SUCCESS ? L"success" : L"failure", relayTid);
        worldChannel->removeReferenceCount(RETRIEVE_CHARACTER_INFO_RELAY_FILE, 57);
        return false;
    }

    Log::Write(Log::LT_NOTICE, RETRIEVE_CHARACTER_INFO_RELAY_FILE, 61,
               L"[%s], %s; sent retrieve character info %s response ack, relayTid:0x%I64X", MODULE_NAME,
               L"RetrieveCharacterInfoRelayContext::processRelayResponse",
               _response._resultState == RelayResponse::RESULTSTATE_SUCCESS ? L"success" : L"failure", relayTid);
    worldChannel->removeReferenceCount(RETRIEVE_CHARACTER_INFO_RELAY_FILE, 62);
    return true;
}

// 0x1e0b0
bool RetrieveCharacterInfoRelayContext::processRelayTimeout()
{
    RetrieveCharacterInfoRelayResponse response(RelayResponse::RESULTSTATE_RELAY_TIMEOUT, 13);
    initResponse(&response);
    return processRelayResponse();
}

// 0x1e110
RelayHeader const RetrieveCharacterInfoRelayContext::MakeRelayHeader() const
{
    RelayHeader relayHeader;
    relayHeader._fromWid = PostOfficeDaemon::_instance->_serviceWid;
    relayHeader._toWid = _economyHeader._toWid;
    relayHeader._relayTid = _economyHeader._relayTid;
    relayHeader._hint = 1037;
    relayHeader._reserved = 0;
    return relayHeader;
}

// 0x1e150
bool RetrieveCharacterInfoRelayContext::ComposeRequestPacket(Packet& packet) const
{
    wchar_t const* const targetCharacterName = _request._targetCharacterName;
    bool const composed = packet.Compose("hhhqqs", 1037, static_cast<int>(_economyHeader._fromWid),
                                         static_cast<int>(_economyHeader._toWid), _economyHeader._relayTid,
                                         _request._gameTid, targetCharacterName) != 0;
    long long const gameTid = _request._gameTid;
    unsigned long long const relayTid = _economyHeader._relayTid;
    unsigned int const toWid = _economyHeader._toWid;
    unsigned int const fromWid = _economyHeader._fromWid;
    if (!composed)
    {
        Log::Write(Log::LT_ERROR, RETRIEVE_CHARACTER_INFO_RELAY_FILE, 87,
                   L"[%s], %s; failed to compose retrieve character info relay request packet, fromWid:%u, toWid:%u, relayTid:0x%I64X, gameTid:0x%I64X, targetCharacterName:%s",
                   MODULE_NAME, L"RetrieveCharacterInfoRelayContext::ComposeRequestPacket", fromWid,
                   toWid, relayTid, gameTid, targetCharacterName);
        return false;
    }

    Log::Write(Log::LT_DEBUG, RETRIEVE_CHARACTER_INFO_RELAY_FILE, 91,
               L"[%s], %s; composed retrieve character info relay request packet, fromWid:%u, toWid:%u, relayTid:0x%I64X, gameTid:0x%I64X, targetCharacterName:%s",
               MODULE_NAME, L"RetrieveCharacterInfoRelayContext::ComposeRequestPacket", fromWid,
               toWid, relayTid, gameTid, targetCharacterName);
    return true;
}

// 0x1e230
bool RetrieveCharacterInfoRelayContext::ComposeResponsePacket(Packet& packet) const
{
    // PDB lines (0x1e230): one switch on the result state; the failure cases come first in the code, the crash case is the default.
    unsigned long long const relayTid = _economyHeader._relayTid;
    switch (_response._resultState)
    {
    case RelayResponse::RESULTSTATE_SUCCESS:
    {
        long long const resultPcId = _response._resultPcId;
        long long const gameTid = _request._gameTid;
        if (!(0 < packet.Compose("hqq", 5, _request._gameTid, _response._resultPcId)))
        {
            Log::Write(Log::LT_ERROR, RETRIEVE_CHARACTER_INFO_RELAY_FILE, 107,
                       L"[%s], %s; failed to compose retrieve character info success response packet, gameTid:0x%I64X, resultPcId:0x%I64X",
                       MODULE_NAME, L"RetrieveCharacterInfoRelayContext::ComposeResponsePacket",
                       gameTid, resultPcId);
            return false;
        }
        Log::Write(Log::LT_DEBUG, RETRIEVE_CHARACTER_INFO_RELAY_FILE, 110,
                   L"[%s], %s; composed retrieve character info success response packet, gameTid:0x%I64X, resultPcId:0x%I64X",
                   MODULE_NAME, L"RetrieveCharacterInfoRelayContext::ComposeResponsePacket", gameTid,
                   resultPcId);
    }
    break;
    case RelayResponse::RESULTSTATE_FAILURE:
    case RelayResponse::RESULTSTATE_RELAY_ERROR:
    case RelayResponse::RESULTSTATE_RELAY_TIMEOUT:
    {
        int const failReason = convertFailReason(static_cast<RelayResponse::ResultState>(_response._resultState), _response._failReason);
        bool const composed = 0 < packet.Compose("hqE", 6, _request._gameTid, failReason);
        if (!composed)
        {
            Log::Write(Log::LT_ERROR, RETRIEVE_CHARACTER_INFO_RELAY_FILE, 121,
                       L"[%s], %s; failed to compose retrieve character info failure response packet, gameTid:0x%I64X, failReason:%d",
                       MODULE_NAME, L"RetrieveCharacterInfoRelayContext::ComposeResponsePacket",
                       _request._gameTid, failReason);
            return false;
        }
        Log::Write(Log::LT_DEBUG, RETRIEVE_CHARACTER_INFO_RELAY_FILE, 124,
                   L"[%s], %s; composed retrieve character info failure response packet, gameTid:0x%I64X, failReason:%d",
                   MODULE_NAME, L"RetrieveCharacterInfoRelayContext::ComposeResponsePacket",
                   _request._gameTid, failReason);
    }
    break;
    default:
        RETRIEVE_CHARACTER_INFO_RELAY_CRASH(128,
                                            L"== CRASH == [%s], %s; invalid response result state, relayTid:0x%I64X, resultState:%d",
                                            MODULE_NAME,
                                            L"RetrieveCharacterInfoRelayContext::ComposeResponsePacket", relayTid,
                                            _response._resultState);
        return false;
    }
    return true;
}

// 0x1e410
__declspec(noinline) short const RetrieveCharacterInfoRelayContext::convertFailReason(RelayResponse::ResultState const resultState, short const failReason) const
{
    switch (resultState)
    {
    case RelayResponse::RESULTSTATE_FAILURE:
        if (failReason == 12)
            return 10;
        if (failReason == 11)
            return 11;
        break;
    case RelayResponse::RESULTSTATE_RELAY_ERROR:
        switch (failReason)
        {
        case 3:
        case 9:
            return 4;
        case 8:
            return 14;
        case 10:
        case 11:
            return 2;
        default:
            break;
        }
        break;
    case RelayResponse::RESULTSTATE_RELAY_TIMEOUT:
        return 13;
    default:
        break;
    }
    return 1;
}
