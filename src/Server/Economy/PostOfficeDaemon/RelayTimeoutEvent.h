// RelayTimeoutEvent.obj (PostOfficeDaemon PDB). Layouts from include/pdb/PostOfficeDaemon/types.h.
#pragma once
#include <stddef.h>
#include "TimerQueue.h"

class RelayContext;

class RelayTimeoutEvent : public DynamicEventObject
{
public:
    RelayTimeoutEvent(unsigned long long relayTid, RelayContext* const relayContext);  // LIFT: inlined in 0x1db40
    virtual unsigned int EventId() const;                                    // 0x1dcf0
    virtual bool HandleEvent(EventContext* context, unsigned long param);    // 0x1dd60
    virtual ~RelayTimeoutEvent();                                            // 0x1dd00

    unsigned long long const _relayTid;
    RelayContext* _relayContext;
};
static_assert(sizeof(RelayTimeoutEvent) == 0x28, "sizeof RelayTimeoutEvent");
static_assert(offsetof(RelayTimeoutEvent, _relayTid) == 0x18, "RelayTimeoutEvent::_relayTid");
static_assert(offsetof(RelayTimeoutEvent, _relayContext) == 0x20, "RelayTimeoutEvent::_relayContext");
