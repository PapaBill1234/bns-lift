// lock.cpp: lock.h (GameDaemon PDB, 2019 + PDB).
#include "lock_gd.h"
#include "accountinventorychannel_gd.h"
#include "../BloodLib/include/Lock.h"
#include "../BloodLib/include/Log.h"
#include "../BloodLib/include/AlertSender.h"
#include "../BloodLib/include/CrashHandler.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?Enter@AutoCS@@QEAAXXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Leave@AutoCS@@QEAAXXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:??1AccountInventoryChannelManager@@QEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:??1AutoSRW@@QEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)

// A6: per-exe path literal of Lock.h.
#define LOCK_H_WIDE L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\bloodlib\\include\\Lock.h"
#define LOCK_H_NARROW "e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\bloodlib\\include\\Lock.h"

// LIFT: inlined assert of BloodLib (Log, alert, crash). No PDB name. Same form as MarketDealerDaemon JobContext.cpp.
#define LOCK_ASSERT_CRASH(line)                                                     \
    do                                                                              \
    {                                                                               \
        Log::Write(Log::LT_ERROR, LOCK_H_WIDE, line, L"== CRASH == ASSERT CRASH"); \
        AlertSender::Write(LOCK_H_WIDE, line, L"== CRASH == ASSERT CRASH");        \
        CrashHandler::MakeCrash(LOCK_H_NARROW, line, L"");                          \
    } while (0)

// 0x1cbc0 AutoCS::~AutoCS: LIFT: no body in wave 0 (shared class AutoCS has another form or the change needs codegen (W1, pattern 35)).

// 0x1cbd0
void AutoCS::Enter()
{
    if (CS == nullptr)
        LOCK_ASSERT_CRASH(113);
    if (EnterCount == 0)
        EnterCriticalSection(&CS->CS);
    ++EnterCount;
}

// 0x1cc50
void AutoCS::Leave()
{
    if (CS == nullptr)
        LOCK_ASSERT_CRASH(122);
    if (EnterCount == 1)
        LeaveCriticalSection(&CS->CS);
    --EnterCount;
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
