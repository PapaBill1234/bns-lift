// SendPublicationEvent (SmartCouponDaemon PDB). ❓ The PDB module of this class is not known.
// Layouts from include/pdb/SmartCouponDaemon/types.h.
#pragma once
#include <stddef.h>
#include "TimerQueue.h"
#include "StringUtil.h"

class SendPublicationEvent : public DynamicEventObject
{
public:
    // ❓ Inlined in SmartCouponDaemon::loadUnhandledCouponPublication (0x161A0).
    SendPublicationEvent(long long publicationId, id128 const& gameAccountId, int couponEventId)
        : _publicationId(publicationId), _gameAccountId(gameAccountId), _couponEventId(couponEventId), _managementTid(0)
    {
    }
    virtual ~SendPublicationEvent();
    virtual unsigned int EventId() const;
    virtual bool HandleEvent(EventContext* ctx, unsigned long);

    long long _publicationId;
    id128 _gameAccountId;
    int _couponEventId;
    long long _managementTid;
};
static_assert(sizeof(SendPublicationEvent) == 0x40, "sizeof SendPublicationEvent");
static_assert(offsetof(SendPublicationEvent, _gameAccountId) == 0x20, "SendPublicationEvent::_gameAccountId");
static_assert(offsetof(SendPublicationEvent, _managementTid) == 0x38, "SendPublicationEvent::_managementTid");
