// RelayTimeoutChecker.obj (PostOfficeDaemon PDB). Layouts from include/pdb/PostOfficeDaemon/types.h.
#pragma once
#include "TimerQueue.h"

class RelayContext;

class RelayTimeoutChecker : public Timer
{
public:
    // ❓ The bodies are folded (ICF) with other functions. Not in index.tsv.
    virtual unsigned int TimerClass() const { return 2; }         // ❓ folded body 0x4f5c0
    virtual unsigned long long TimerId() const { return 0; }      // ❓ value
    virtual bool HandleEvent(EventContext* context, unsigned long bytes);  // 0x1d700
    virtual ~RelayTimeoutChecker() {}  // ❓ folded with Timer dtor 0x12c60

private:
    void checkRelayTimeout();  // 0x1d830
    static bool occurTimeoutEvent(unsigned long long relayTid, RelayContext* const relayContext);  // 0x1db40 ❓ static
};
static_assert(sizeof(RelayTimeoutChecker) == 0x38, "sizeof RelayTimeoutChecker");
