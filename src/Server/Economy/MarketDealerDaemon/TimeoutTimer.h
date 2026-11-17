// TimeoutTimer.obj (MarketDealerDaemon PDB). Layout from include/pdb/MarketDealerDaemon/types.h.
#pragma once
#include "TimerQueue.h"

class SaleContext;
class MarketDealerDaemon;

class TimeoutTimer : public Timer
{
public:
    // TimerClass and TimerId are in MarketDealerDaemon.obj. The bodies are folded (ICF) with other functions.
    virtual unsigned int TimerClass() const { return 1; }     // 0x63c60 (MARKETTIMER_TIMEOUT_TIMER)
    virtual unsigned long long TimerId() const { return 0; }  // 0x6ee0
    virtual bool HandleEvent(EventContext* context, unsigned long bytes);  // 0x319d0

private:
    friend class MarketDealerDaemon;  // LIFT: the PDB ctor is private. MarketDealerDaemon makes the timer.
    TimeoutTimer() {}
    TimeoutTimer(TimeoutTimer const&);
    virtual ~TimeoutTimer() {}  // ❓ body not in index.tsv (folded)
    TimeoutTimer& operator=(TimeoutTimer const&);

    void checkSaleExpiration() const;                                                                     // 0x31b10
    bool postTimeoutEvent(long long const saleId, char const saleType, SaleContext* const saleContext) const;  // 0x31e20
};
static_assert(sizeof(TimeoutTimer) == 0x38, "sizeof TimeoutTimer");
