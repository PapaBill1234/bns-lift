// RelayTimeoutChecker.obj (PostOfficeDaemon PDB). Layouts from include/pdb/PostOfficeDaemon/types.h.
#pragma once
#include "TimerQueue.h"

class RelayContext;

class RelayTimeoutChecker : public Timer
{
public:
    // The bodies are folded (ICF) with other functions. Not in index.tsv.
    virtual unsigned int TimerClass() const { return 2; }         // 0x4f5c0
    virtual unsigned long long TimerId() const { return 0; }      // 0x5d860
    virtual bool HandleEvent(EventContext* context, unsigned long bytes);  // 0x1d700
    virtual ~RelayTimeoutChecker() {}  // LIFT: folded with Timer dtor 0x12c60

private:
    void checkRelayTimeout();  // 0x1d830
    bool occurTimeoutEvent(unsigned long long const relayTid, RelayContext* const relayContext) const;  // 0x1db40
};
static_assert(sizeof(RelayTimeoutChecker) == 0x38, "sizeof RelayTimeoutChecker");
