// UnsentPostChecker.obj (PostOfficeDaemon PDB). Layouts from include/pdb/PostOfficeDaemon/types.h.
#pragma once
#include "TimerQueue.h"

class UnsentPostChecker : public Timer
{
public:
    // ❓ The bodies are folded (ICF) with other functions (TimerClass at 0x29950). Not in index.tsv.
    virtual unsigned int TimerClass() const { return 2; }         // ❓ value
    virtual unsigned long long TimerId() const { return 0; }      // ❓ value
    virtual bool HandleEvent(EventContext* context, unsigned long bytes);  // 0xd770
    virtual ~UnsentPostChecker() {}  // ❓ folded with Timer dtor 0x12c60
};
static_assert(sizeof(UnsentPostChecker) == 0x38, "sizeof UnsentPostChecker");
