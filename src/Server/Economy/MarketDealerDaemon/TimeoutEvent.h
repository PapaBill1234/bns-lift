// TimeoutEvent.obj (MarketDealerDaemon PDB). Layouts from include/pdb/MarketDealerDaemon/types.h.
// The virtual functions are a later card (declarations only). The ctors are inlined in
// TimeoutTimer::postTimeoutEvent (0x31e20).
#pragma once
#include <stddef.h>
#include "TimerQueue.h"
#include "SaleContext.h"

class InstantSaleTimeoutEvent : public DynamicEventObject
{
public:
    // LIFT: inlined ctor (0x31e20). The addReferenceCount line is 35 (TimeoutEvent.cpp).
    InstantSaleTimeoutEvent(long long const saleId, SaleContext* const saleContext)
        : _saleId(saleId), _saleContext(saleContext)
    {
        _saleContext->addReferenceCount(L"TimeoutEvent.cpp", 35);
    }
    virtual ~InstantSaleTimeoutEvent();
    virtual unsigned int EventId() const;
    virtual bool HandleEvent(EventContext* context, unsigned long bytes);

    long long _saleId;
    SaleContext* _saleContext;
};
static_assert(sizeof(InstantSaleTimeoutEvent) == 0x28, "sizeof InstantSaleTimeoutEvent");
static_assert(offsetof(InstantSaleTimeoutEvent, _saleId) == 0x18, "InstantSaleTimeoutEvent::_saleId");
static_assert(offsetof(InstantSaleTimeoutEvent, _saleContext) == 0x20, "InstantSaleTimeoutEvent::_saleContext");

class AuctionTimeoutEvent : public DynamicEventObject
{
public:
    // LIFT: inlined ctor (0x31e20). The addReferenceCount line is 139 (TimeoutEvent.cpp).
    AuctionTimeoutEvent(long long const saleId, SaleContext* const saleContext)
        : _saleId(saleId), _saleContext(saleContext)
    {
        _saleContext->addReferenceCount(L"TimeoutEvent.cpp", 139);
    }
    virtual ~AuctionTimeoutEvent();
    virtual unsigned int EventId() const;
    virtual bool HandleEvent(EventContext* context, unsigned long bytes);

    long long _saleId;
    SaleContext* _saleContext;
};
static_assert(sizeof(AuctionTimeoutEvent) == 0x28, "sizeof AuctionTimeoutEvent");
static_assert(offsetof(AuctionTimeoutEvent, _saleId) == 0x18, "AuctionTimeoutEvent::_saleId");
static_assert(offsetof(AuctionTimeoutEvent, _saleContext) == 0x20, "AuctionTimeoutEvent::_saleContext");
