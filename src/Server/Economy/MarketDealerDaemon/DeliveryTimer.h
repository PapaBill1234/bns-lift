// DeliveryTimer.obj (MarketDealerDaemon PDB). Layout from include/pdb/MarketDealerDaemon/types.h.
#pragma once
#include "TimerQueue.h"

class MarketDealerDaemon;

class DeliveryTimer : public Timer
{
public:
    // TimerClass and TimerId are in MarketDealerDaemon.obj. The bodies are folded (ICF) with other functions.
    virtual unsigned int TimerClass() const { return 2; }     // 0x29220 (MARKETTIMER_DELIVERY_TIMER)
    virtual unsigned long long TimerId() const { return 0; }  // 0x6ee0
    virtual bool HandleEvent(EventContext* context, unsigned long bytes);  // 0x82e0

private:
    friend class MarketDealerDaemon;  // LIFT: the PDB ctor is private. MarketDealerDaemon makes the timer.
    DeliveryTimer() {}
    DeliveryTimer(DeliveryTimer const&);
    virtual ~DeliveryTimer() {}  // ❓ body not in index.tsv (folded)
    DeliveryTimer& operator=(DeliveryTimer const&);

    void checkDelivery() const;  // 0x8420
};
static_assert(sizeof(DeliveryTimer) == 0x38, "sizeof DeliveryTimer");
