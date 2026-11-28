// lock.cpp: lock.h (GameDaemon PDB, 2019 + PDB).
#include "lock_gd.h"
#include "accountinventorychannel_gd.h"
#include "../BloodLib/include/Lock.h"
#include "../BloodLib/include/Log.h"
#include "../BloodLib/include/AlertSender.h"
#include "../BloodLib/include/CrashHandler.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:??1AccountInventoryChannelManager@@QEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:??1AutoSRW@@QEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x1cbc0 AutoCS::~AutoCS: LIFT: no body in wave 0 (shared class AutoCS has another form or the change needs codegen (W1, pattern 35)).

// 0x1cbd0
// LIFT: log path (E16): the inlined assert calls Log::Write and AlertSender::Write.
void AutoCS::Enter()
{
    LIFT_STUB(0x1cbd0);
}

// 0x1cc50
// LIFT: log path (E16): the inlined assert calls Log::Write and AlertSender::Write.
void AutoCS::Leave()
{
    LIFT_STUB(0x1cc50);
}

// 0x18d060
// LIFT: the linker folded this body with CriticalSection::~CriticalSection (DeleteCriticalSection thunk).
__cdecl AccountInventoryChannelManager::~AccountInventoryChannelManager(void)
{
}

// 0x1dc200
__cdecl AutoSRW::~AutoSRW(void)
{
    if (_lock != nullptr)
    {
        if (_mode == EXCLUSIVE)
            ReleaseSRWLockExclusive(const_cast<PSRWLOCK>(_lock));
        else
            ReleaseSRWLockShared(const_cast<PSRWLOCK>(_lock));
    }
}
