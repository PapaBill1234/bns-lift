// UnsentPostChecker.obj (PostOfficeDaemon PDB). Layouts from include/pdb/PostOfficeDaemon/types.h.
#pragma once
#include "TimerQueue.h"

class UnsentPostChecker : public Timer
{
public:
    // The bodies are folded (ICF) with other functions. Not in index.tsv.
    virtual unsigned int TimerClass() const { return 3; }         // 0x29950
    virtual unsigned long long TimerId() const { return 0; }      // 0x5d860
    virtual bool HandleEvent(EventContext* context, unsigned long bytes);  // 0xd770
    virtual ~UnsentPostChecker() {}  // ❓ folded with Timer dtor 0x12c60
};
static_assert(sizeof(UnsentPostChecker) == 0x38, "sizeof UnsentPostChecker");
