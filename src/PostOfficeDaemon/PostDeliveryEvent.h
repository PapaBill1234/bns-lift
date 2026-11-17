// PostDeliveryEvent.obj (PostOfficeDaemon PDB). Layouts from include/pdb/PostOfficeDaemon/types.h.
#pragma once
#include <stddef.h>
#include "TimerQueue.h"

class PostContext;
class CacheGateChannel;

class PostDeliveryEvent : public DynamicEventObject
{
public:
    PostDeliveryEvent(PostContext* const postContext, CacheGateChannel* const cachegateChannel);  // 0x10480
    virtual unsigned int EventId() const;                                    // 0x10470
    virtual bool HandleEvent(EventContext* context, unsigned long param);    // 0x10730
    virtual ~PostDeliveryEvent();                                            // 0x10530

    static bool OccurEvent(PostContext* const postContext, CacheGateChannel* const cachegateChannel);  // 0x105b0

private:
    bool deliverPost(unsigned short recipientWid, long long postId);         // 0x108c0

public:
    PostContext* _postContext;
    CacheGateChannel* _cachegateChannel;
};
static_assert(sizeof(PostDeliveryEvent) == 0x28, "sizeof PostDeliveryEvent");
static_assert(offsetof(PostDeliveryEvent, _postContext) == 0x18, "PostDeliveryEvent::_postContext");
static_assert(offsetof(PostDeliveryEvent, _cachegateChannel) == 0x20, "PostDeliveryEvent::_cachegateChannel");
