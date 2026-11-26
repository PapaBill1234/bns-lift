// LobbyCharacterDeletionScheduler.obj (LobbyDaemon PDB, 2019 + PDB). Layout from tools/pdbcls.py LobbyDaemon LobbyCharacterDeletionScheduler.
// LIFT: header layout only (fix7). The function bodies are still LIFT_STUB.
#pragma once
#include <stddef.h>
#include "TimerQueue.h"

struct EventContext;

// LIFT: PDB layout (sizeof 0x48, Timer base). The PDB dtor and Stop have no own symbol in the lift scope.
// They are not declared.
class LobbyCharacterDeletionScheduler : public Timer
{
public:
    // LIFT: inline at the allocation site in LobbyDaemon::initialize (0x9b300, line 1506).
    LobbyCharacterDeletionScheduler() : _run(false), _period(0), _concurrentProcessingCount(0) {}
    // LIFT: vftable 0x160180 slots 6 and 7 are 0x5a0a0 (folded "return 0").
    virtual unsigned int TimerClass() const { return 0; }
    virtual unsigned long long TimerId() const { return 0; }
    bool Start(long, int);  // 0x56780
    virtual bool HandleEvent(EventContext*, unsigned long);  // 0x568a0
private:
    bool process();  // 0x568e0

    friend struct LobbyCharacterDeletionSchedulerLayoutCheck;  // LIFT: checks the private PDB offsets.

    bool _run;  // +0x38
    long _period;  // +0x3c
    int _concurrentProcessingCount;  // +0x40
};
static_assert(sizeof(LobbyCharacterDeletionScheduler) == 0x48, "sizeof LobbyCharacterDeletionScheduler");
struct LobbyCharacterDeletionSchedulerLayoutCheck
{
    static_assert(offsetof(LobbyCharacterDeletionScheduler, _run) == 0x38, "LobbyCharacterDeletionScheduler::_run");
    static_assert(offsetof(LobbyCharacterDeletionScheduler, _period) == 0x3c, "LobbyCharacterDeletionScheduler::_period");
    static_assert(offsetof(LobbyCharacterDeletionScheduler, _concurrentProcessingCount) == 0x40,
                  "LobbyCharacterDeletionScheduler::_concurrentProcessingCount");
};
