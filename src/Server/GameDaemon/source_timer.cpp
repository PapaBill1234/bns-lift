// source_timer.cpp: timer.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "GameDaemonFwd.h"
#include "../BloodLib/include/TimerQueue.h"
#include "LiftStub.h"

// 0x6b08d0 TimerQueue::~TimerQueue: LIFT: no body in wave 0 (shared class TimerQueue has another form or the change needs codegen (W1, pattern 35)).

// 0x6b0ec0
bool __cdecl TimerQueue::RemoveAndAdd(::Timer *, long, ::Timer *)
{
    LIFT_STUB(0x6b0ec0);
}
