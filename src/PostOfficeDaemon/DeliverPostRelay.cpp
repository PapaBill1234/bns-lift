// DeliverPostRelay.obj (PostOfficeDaemon PDB).
#include "DeliverPostRelay.h"
#include "Log.h"
#include "AlertSender.h"
#include "Lock.h"
#include "FragmentPacket.h"
#include "PostContext.h"
#include "CacheGateChannel.h"
#include "PostOfficeDB.h"
#include "PostOfficeDaemon.h"

#define DELIVER_POST_RELAY_FILE L"DeliverPostRelay.cpp"
static wchar_t const* const MODULE_NAME = L"relay context";  // PDB MODULE_NAME

#define DELIVER_POST_RELAY_CRASH(line, fmt, ...)                                     \
    do                                                                               \
    {                                                                                \
        Log::Write(Log::LT_ERROR, DELIVER_POST_RELAY_FILE, line, fmt, __VA_ARGS__);  \
        AlertSender::Write(DELIVER_POST_RELAY_FILE, line, fmt, __VA_ARGS__);         \
    } while (0)

// 0xfb50
void DeliverPostRelayContext::initResponse(RelayResponse* const response)
{
    DeliverPostRelayResponse* const deliverPostResponse = static_cast<DeliverPostRelayResponse*>(response);
    // BUG: 0xfb50 a null response is read through a null pointer; the code does not check it.
    _response._resultState = deliverPostResponse->_resultState;
    _response._failReason = deliverPostResponse->_failReason;
}

// 0xfb80
DeliverPostRelayContext::DeliverPostRelayContext(EconomyHeader const& economyHeader, PostContext* const postContext)
    : RelayContext(economyHeader), _postContext(postContext)
{
    _response._resultState = RelayResponse::RESULTSTATE_INVALID;
    _response._failReason = 0;
    if (postContext != nullptr)
        postContext->addReferenceCount(DELIVER_POST_RELAY_FILE, 35);
}

// 0xfc70
DeliverPostRelayContext::~DeliverPostRelayContext()
{
    if (_postContext != nullptr)
    {
        _postContext->removeReferenceCount(DELIVER_POST_RELAY_FILE, 41);
        _postContext = nullptr;
    }
}

// LIFT: folded with 0xfb40 (PingRelayContext::GetRequestWid)
unsigned short const DeliverPostRelayContext::GetRequestWid() const
{
    return _economyHeader._fromWid;
}

// LIFT: folded with 0x34c40
bool DeliverPostRelayContext::ComposeRequestPacket(Packet&) const
{
    return true;
}

// LIFT: folded with 0x34c40
bool DeliverPostRelayContext::ComposeResponsePacket(FragmentPacket&) const
{
    return true;
}

// LIFT: folded with 0x34c40
bool DeliverPostRelayContext::ComposeResponsePacket(Packet&) const
{
    return true;
}

// 0xfd00
bool DeliverPostRelayContext::processRelayRequest(Channel* const channel) const
{
    if (channel == nullptr)
    {
        DELIVER_POST_RELAY_CRASH(49, L"== CRASH == [%s], %s; invalid parameter, channel:0x%p", MODULE_NAME,
                                 L"DeliverPostRelayContext::processRelayRequest", static_cast<Channel*>(nullptr));
        return false;
    }

    unsigned long long const relayTid = _economyHeader._relayTid;
    // LIFT: LTCG folded economyFormat (PDB offset 0). The call (0xFD88) sets only rcx and rdx. The callee (0x71E0) does not read r8.
    if (!static_cast<CacheGateChannel*>(channel)->SendFragmentRelayRequest(this, nullptr))
    {
        Log::Write(Log::LT_ERROR, DELIVER_POST_RELAY_FILE, 56, L"[%s], %s; failed to send deliver post relay request, relayTid:0x%I64X",
                   MODULE_NAME, L"DeliverPostRelayContext::processRelayRequest", relayTid);
        return false;
    }

    Log::Write(Log::LT_NOTICE, DELIVER_POST_RELAY_FILE, 60, L"[%s], %s; sent deliver post relay request, relayTid:0x%I64X",
               MODULE_NAME, L"DeliverPostRelayContext::processRelayRequest", relayTid);
    return true;
}

// 0xfe00
bool DeliverPostRelayContext::processRelayResponse() const
{
    unsigned long long const relayTid = _economyHeader._relayTid;
    long long const postId = _postContext->_postInfo._postId;
    unsigned short const recipientWid = static_cast<unsigned short>(_postContext->_postInfo._recipientWid);
    int const resultState = _response._resultState;
    bool needRegister = false;

    AutoCS autoLock(&_postContext->_lock);
    char const postStatus = _postContext->_postInfo._postStatus;
    if (postStatus != 3)
    {
        Log::Write(Log::LT_ERROR, DELIVER_POST_RELAY_FILE, 77,
                   L"[%s], %s; invalid post status, relayTid:0x%I64X, postId:0x%I64X, postStatus:%d",
                   MODULE_NAME, L"DeliverPostRelayContext::processRelayResponse", relayTid, postId,
                   static_cast<int>(postStatus));
        return false;
    }

    int dbRetValue;
    switch (resultState)
    {
    case RelayResponse::RESULTSTATE_SUCCESS:
        dbRetValue = 0;
        if (!PostOfficeDB::UpdateStatusToDeliverySuccess(&dbRetValue, postId))
        {
            Log::Write(Log::LT_ERROR, DELIVER_POST_RELAY_FILE, 86,
                       L"[%s], %s; exception occurred; failed to update post status [delivery success status], dbRetValue:%d, relayTid:0x%I64X, postId:0x%I64X",
                       MODULE_NAME, L"DeliverPostRelayContext::processRelayResponse", dbRetValue, relayTid, postId);
        }
        _postContext->_postInfo._postStatus = 4;
        break;

    case RelayResponse::RESULTSTATE_FAILURE:
        dbRetValue = 0;
        if (_response._failReason == 18)
        {
            if (!PostOfficeDB::UpdateStatusToDeliverySuccess(&dbRetValue, postId))
            {
                Log::Write(Log::LT_ERROR, DELIVER_POST_RELAY_FILE, 99,
                           L"[%s], %s; exception occurred; failed to update post status [incomplete delivery status], dbRetValue:%d, relayTid:0x%I64X, postId:0x%I64X",
                           MODULE_NAME, L"DeliverPostRelayContext::processRelayResponse", dbRetValue, relayTid,
                           postId);
            }
            _postContext->_postInfo._postStatus = 6;
        }
        else
        {
            if (!PostOfficeDB::UpdateStatusToDeliveryFailure(&dbRetValue, postId))
            {
                Log::Write(Log::LT_ERROR, DELIVER_POST_RELAY_FILE, 108,
                           L"[%s], %s; exception occurred; failed to update post status [delivery failure status], dbRetValue:%d, relayTid:0x%I64X, postId:0x%I64X",
                           MODULE_NAME, L"DeliverPostRelayContext::processRelayResponse", dbRetValue, relayTid,
                           postId);
            }
            _postContext->_postInfo._postStatus = 5;
        }
        break;

    case RelayResponse::RESULTSTATE_RELAY_ERROR:
    case RelayResponse::RESULTSTATE_RELAY_TIMEOUT:
        _postContext->_postInfo._postStatus = 1;
        needRegister = true;
        break;

    default:
        DELIVER_POST_RELAY_CRASH(125,
                                 L"== CRASH == [%s], %s; invalid response result state, relayTid:0x%I64X, postId:0x%I64X, resultState:%d",
                                 MODULE_NAME, L"DeliverPostRelayContext::processRelayResponse", relayTid, postId,
                                 resultState);
        return false;
    }
    autoLock.Leave();

    if (!PostOfficeDaemon::_instance->_postContextManager->RemoveContext(postId))
    {
        DELIVER_POST_RELAY_CRASH(131, L"== CRASH == [%s], %s; exception occurred; failed to remove post context, postId:0x%I64X",
                                 MODULE_NAME, L"DeliverPostRelayContext::processRelayResponse", postId);
    }
    if (needRegister && !PostOfficeDaemon::_instance->_unsentPostContextManager->RegisterUnsentPost(recipientWid, postId, false))
    {
        Log::Write(Log::LT_ERROR, DELIVER_POST_RELAY_FILE, 136,
                   L"[%s], %s; exception occurred; failed to register unsent post, recipientWid:%u, postId:0x%I64X",
                   MODULE_NAME, L"DeliverPostRelayContext::processRelayResponse",
                   static_cast<unsigned int>(recipientWid), postId);
    }
    return true;
}

// 0x102c0
bool DeliverPostRelayContext::processRelayTimeout()
{
    DeliverPostRelayResponse response(RelayResponse::RESULTSTATE_RELAY_TIMEOUT, 0);
    initResponse(&response);
    return processRelayResponse();
}

// 0x10310
RelayHeader const DeliverPostRelayContext::MakeRelayHeader() const
{
    RelayHeader relayHeader;
    relayHeader._fromWid = PostOfficeDaemon::_instance->_serviceWid;
    relayHeader._toWid = _economyHeader._toWid;
    relayHeader._relayTid = _economyHeader._relayTid;
    relayHeader._hint = 1043;
    relayHeader._reserved = 0;
    return relayHeader;
}

// 0x10350
bool DeliverPostRelayContext::ComposeRequestPacket(FragmentPacket& packet) const
{
    unsigned short const fromWid = _economyHeader._fromWid;
    unsigned short const toWid = _economyHeader._toWid;
    unsigned long long const relayTid = _economyHeader._relayTid;
    if (!packet.Compose(4, 1043, static_cast<int>(fromWid), static_cast<int>(toWid), relayTid))
    {
        Log::Write(Log::LT_ERROR, DELIVER_POST_RELAY_FILE, 159,
                   L"[%s], %s; failed to compose deliver post relay request packet, fromWid:%u, toWid:%u, relayTid:0x%I64X",
                   MODULE_NAME, L"DeliverPostRelayContext::ComposeRequestPacket", static_cast<unsigned int>(fromWid),
                   static_cast<unsigned int>(toWid), relayTid);
        return false;
    }

    Log::Write(Log::LT_DEBUG, DELIVER_POST_RELAY_FILE, 162,
               L"[%s], %s; composed deliver post relay request packet, fromWid:%u, toWid:%u, relayTid:0x%I64X",
               MODULE_NAME, L"DeliverPostRelayContext::ComposeRequestPacket", static_cast<unsigned int>(fromWid),
               static_cast<unsigned int>(toWid), relayTid);

    if (!_postContext->ComposeDeliveryPacket(packet))
    {
        Log::Write(Log::LT_ERROR, DELIVER_POST_RELAY_FILE, 165,
                   L"[%s], %s; failed to compose deliver post packet in context, relayTid:0x%I64X, postId:0x%I64X",
                   MODULE_NAME, L"DeliverPostRelayContext::ComposeRequestPacket", relayTid,
                   _postContext->_postInfo._postId);
        return false;
    }
    return true;
}
