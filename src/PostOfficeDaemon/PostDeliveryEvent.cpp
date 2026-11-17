// PostDeliveryEvent.obj (PostOfficeDaemon PDB).
#include "PostDeliveryEvent.h"
#include <new>
#include <windows.h>
#include "Log.h"
#include "AlertSender.h"
#include "Memory.h"
#include "Network.h"
#include "Lock.h"
#include "PostContext.h"
#include "DeliverPostRelay.h"
#include "CacheGateChannel.h"
#include "PostOfficeDB.h"
#include "PostOfficeDaemon.h"

#define POST_DELIVERY_EVENT_FILE L"PostDeliveryEvent.cpp"
#define POST_DELIVERY_EVENT_TAG L"post delivery event"

#define POST_DELIVERY_EVENT_CRASH(line, fmt, ...)                                      \
    do                                                                                 \
    {                                                                                  \
        Log::Write(Log::LT_ERROR, POST_DELIVERY_EVENT_FILE, line, fmt, __VA_ARGS__);   \
        AlertSender::Write(POST_DELIVERY_EVENT_FILE, line, fmt, __VA_ARGS__);          \
    } while (0)

// 0x10470
unsigned int PostDeliveryEvent::EventId() const
{
    return 128;
}

// 0x10480
PostDeliveryEvent::PostDeliveryEvent(PostContext* const postContext, CacheGateChannel* const cachegateChannel)
    : _postContext(postContext), _cachegateChannel(cachegateChannel)
{
    if (postContext != nullptr)
        postContext->addReferenceCount(POST_DELIVERY_EVENT_FILE, 30);
    if (_cachegateChannel != nullptr)
        _cachegateChannel->addReferenceCount(POST_DELIVERY_EVENT_FILE, 32);
}

// 0x10530
PostDeliveryEvent::~PostDeliveryEvent()
{
    if (_postContext != nullptr)
    {
        _postContext->removeReferenceCount(POST_DELIVERY_EVENT_FILE, 38);
        _postContext = nullptr;
    }
    if (_cachegateChannel != nullptr)
    {
        _cachegateChannel->removeReferenceCount(POST_DELIVERY_EVENT_FILE, 42);
        _cachegateChannel = nullptr;
    }
}

// 0x105b0
bool PostDeliveryEvent::OccurEvent(PostContext* const postContext, CacheGateChannel* const cachegateChannel)
{
    if (postContext == nullptr || cachegateChannel == nullptr)
    {
        POST_DELIVERY_EVENT_CRASH(50, L"== CRASH == [%s], %s; invalid parameter, postContext:0x%p, cachegateChannel:0x%p",
                                  POST_DELIVERY_EVENT_TAG, L"PostDeliveryEvent::OccurEvent", postContext, cachegateChannel);
        return false;
    }

    void* const memory = Memory::_Manager[2]->Alloc(sizeof(PostDeliveryEvent), POST_DELIVERY_EVENT_FILE, 53);  // ❓ line
    PostDeliveryEvent* const postDeliveryEvent =
        memory != nullptr ? ::new (memory) PostDeliveryEvent(postContext, cachegateChannel) : nullptr;

    if (PostQueuedCompletionStatus(Network::iocpHandleOrNull(), 0, reinterpret_cast<ULONG_PTR>(postDeliveryEvent), nullptr))
        return true;

    Log::Write(POST_DELIVERY_EVENT_FILE, 57, GetLastError(),
               L"[%s], %s; exception occurred; failed to occur post delivery event, postId:0x%I64X",
               POST_DELIVERY_EVENT_TAG, L"PostDeliveryEvent::OccurEvent", postContext->_postInfo._postId);
    // BUG: 0x105b0 postDeliveryEvent can be null here (Alloc failed); the call does not check it.
    postDeliveryEvent->removeReferenceCount(POST_DELIVERY_EVENT_FILE, 58);
    return false;
}

// 0x10730
bool PostDeliveryEvent::HandleEvent(EventContext* context, unsigned long param)
{
    Log::Write(Log::LT_DEBUG, POST_DELIVERY_EVENT_FILE, 69, L"[%s], %s; <BEGIN EVENT HANDLER>",
               POST_DELIVERY_EVENT_TAG, L"PostDeliveryEvent::HandleEvent");

    unsigned short const recipientWid = static_cast<unsigned short>(_postContext->_postInfo._recipientWid);
    long long const postId = _postContext->_postInfo._postId;
    if (!deliverPost(recipientWid, postId))
    {
        if (!PostOfficeDaemon::_instance->_postContextManager->RemoveContext(postId))
        {
            POST_DELIVERY_EVENT_CRASH(76, L"== CRASH == [%s], %s; exception occurred; failed to remove post context, postId:0x%I64X",
                                      POST_DELIVERY_EVENT_TAG, L"PostDeliveryEvent::HandleEvent", postId);
        }
        if (!PostOfficeDaemon::_instance->_unsentPostContextManager->RegisterUnsentPost(recipientWid, postId, false))
        {
            Log::Write(Log::LT_ERROR, POST_DELIVERY_EVENT_FILE, 80,
                       L"[%s], %s; exception occurred; failed to register unsent post, recipientWid:%u, postId:0x%I64X",
                       POST_DELIVERY_EVENT_TAG, L"PostDeliveryEvent::HandleEvent", static_cast<unsigned int>(recipientWid),
                       postId);
        }
    }

    Log::Write(Log::LT_DEBUG, POST_DELIVERY_EVENT_FILE, 84, L"[%s], %s; <END EVENT HANDLER>",
               POST_DELIVERY_EVENT_TAG, L"PostDeliveryEvent::HandleEvent");
    removeReferenceCount(POST_DELIVERY_EVENT_FILE, 86);
    return true;
}

// 0x108c0
bool PostDeliveryEvent::deliverPost(unsigned short recipientWid, long long postId)
{
    AutoCS autoLock(&_postContext->_lock);

    char const postStatus = _postContext->_postInfo._postStatus;
    if (postStatus != 1 && postStatus != 2)
    {
        Log::Write(Log::LT_ERROR, POST_DELIVERY_EVENT_FILE, 98, L"[%s], %s; invalid post status, postId:0x%I64X, postStatus:%d",
                   POST_DELIVERY_EVENT_TAG, L"PostDeliveryEvent::deliverPost", postId, static_cast<int>(postStatus));
        return false;
    }

    unsigned long long relayTid = InterlockedIncrement64(reinterpret_cast<LONGLONG volatile*>(&RelayContextManager::_idSeed));
    if (relayTid == 0)
        relayTid = InterlockedIncrement64(reinterpret_cast<LONGLONG volatile*>(&RelayContextManager::_idSeed));

    EconomyHeader economyHeader;
    economyHeader._fromWid = PostOfficeDaemon::_instance->_serviceWid;
    economyHeader._toWid = recipientWid;
    economyHeader._relayTid = relayTid;

    void* const memory = Memory::_Manager[2]->Alloc(sizeof(DeliverPostRelayContext), POST_DELIVERY_EVENT_FILE, 106);  // ❓ line
    DeliverPostRelayContext* const relayContext =
        memory != nullptr ? ::new (memory) DeliverPostRelayContext(economyHeader, _postContext) : nullptr;

    // BUG: 0x108c0 relayContext can be null here (Alloc failed); the call does not check it.
    if (relayContext->ProcessRelayRequest(_cachegateChannel))
    {
        relayContext->removeReferenceCount(POST_DELIVERY_EVENT_FILE, 115);
        _postContext->_postInfo._postStatus = 3;
        return true;
    }

    Log::Write(Log::LT_ERROR, POST_DELIVERY_EVENT_FILE, 110, L"[%s], %s; failed to send deliver post relay request, relayTid:0x%I64X",
               POST_DELIVERY_EVENT_TAG, L"PostDeliveryEvent::deliverPost", relayTid);
    relayContext->removeReferenceCount(POST_DELIVERY_EVENT_FILE, 111);
    return false;
}
