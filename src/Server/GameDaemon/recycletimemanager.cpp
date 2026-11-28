// recycletimemanager.cpp: recycletimemanager.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "recycletimemanager.h"
#include "Daemon.h"
#include "LiftStub.h"

namespace
{
// LIFT: view of the PDB struct RecycleTimeManager::RecycleTime (size 0x18).
struct RecycleTimeEntryView
{
    __int64 time;        // +0 (0x0)
    bool confirmed;      // +8 (0x8)
    __int64 actualTime;  // +16 (0x10)
};

// LIFT: view of the PDB class RecycleTimeManager (size 0xBD8). Only the members that the lifted bodies use are declared.
struct RecycleTimeView
{
    void *owner;                                 // +0 (0x0) Creature *
    RecycleTimeEntryView _grobalRecycleGroup[20];  // +8 (0x8)
    RecycleTimeEntryView *_recycleGroup[6];        // +488 (0x1E8)
};
}

// 0x60fa40
__cdecl RecycleTimeManager::RecycleTimeManager(void)
{
    LIFT_STUB(0x60fa40);
}

// 0x60fc80
void __cdecl RecycleTimeManager::InitializeRecycleTime2(char)
{
    LIFT_STUB(0x60fc80);
}

// 0x60fe70
void __cdecl RecycleTimeManager::InitializeRecycleTime2(char, short)
{
    LIFT_STUB(0x60fe70);
}

// 0x60ff70
void __cdecl RecycleTimeManager::SetRecycleTime2(char, short, long)
{
    LIFT_STUB(0x60ff70);
}

// 0x610090
void __cdecl RecycleTimeManager::ExtendLimitTime2(char, short, long)
{
    LIFT_STUB(0x610090);
}

// 0x6101c0
#pragma comment(linker, "/INCLUDE:?SetGlobalRecycleTime2@RecycleTimeManager@@QEAAXFJ@Z")  // LIFT: dead-strip keep (no live caller yet)
void __cdecl RecycleTimeManager::SetGlobalRecycleTime2(short id, long duration)
{
    // LIFT: the original inlines setGlobalRecycleTime2 (id range 1..GLOBAL_RECYCLE_GROUP_COUNT = 20).
    RecycleTimeView *self = reinterpret_cast<RecycleTimeView *>(this);
    int groupId = id;
    __int64 time = duration + (GetTickCount64() - Daemon::Instance->StartSystemTick64);
    if (groupId >= 1 && groupId <= 20)
        self->_grobalRecycleGroup[groupId - 1].time = time;
}

// 0x610220
void __cdecl RecycleTimeManager::ModifyRecycleTime2(char, long)
{
    LIFT_STUB(0x610220);
}

// 0x610320
void __cdecl RecycleTimeManager::ModifyRecycleTime2(char, short, long)
{
    LIFT_STUB(0x610320);
}

// 0x610370
bool __cdecl RecycleTimeManager::IsAvailableRecycleTime2(char, short)
{
    LIFT_STUB(0x610370);
}

// 0x610440
bool __cdecl RecycleTimeManager::IsAvailableGlobalRecycleTime2(short)
{
    LIFT_STUB(0x610440);
}

// 0x6104f0
short __cdecl RecycleTimeManager::FetchList(short *, char *, unsigned short)
{
    LIFT_STUB(0x6104f0);
}

// 0x6105f0
int __cdecl RecycleTimeManager::SetDbList(short, char const *, int)
{
    LIFT_STUB(0x6105f0);
}

// 0x610860
bool __cdecl RecycleTimeManager::ConfirmRecycleTime(short)
{
    LIFT_STUB(0x610860);
}

// 0x610900
void __cdecl RecycleTimeManager::ApplyAccountRecycleTime(::std::vector< ::AccountRecycleTime, ::StlAllocator< ::AccountRecycleTime, 2> >)
{
    LIFT_STUB(0x610900);
}

// 0x610a90
__int64 __cdecl RecycleTimeManager::GetLimitTime2(char, short)
{
    LIFT_STUB(0x610a90);
}

// 0x610af0
__int64 __cdecl RecycleTimeManager::GetRemainRecycleTime2(char, short)
{
    LIFT_STUB(0x610af0);
}

// 0x610be0
__int64 __cdecl RecycleTimeManager::GetRemainGlobalRecycleTime2(short)
{
    LIFT_STUB(0x610be0);
}

// 0x610ca0
char __cdecl RecycleTimeManager::getRecycleTimeMaxId(char)
{
    LIFT_STUB(0x610ca0);
}

// 0x610cf0
void __cdecl RecycleTimeManager::modifyRecycleTime2(char, short, long)
{
    LIFT_STUB(0x610cf0);
}

// 0x610dd0
void __cdecl RecycleTimeManager::sendCache2(short, __int64)
{
    LIFT_STUB(0x610dd0);
}

// 0x610fd0
#pragma comment(linker, "/INCLUDE:?confirmRecycleTime2@RecycleTimeManager@@AEAAXF@Z")  // LIFT: dead-strip keep (no live caller yet)
void __cdecl RecycleTimeManager::confirmRecycleTime2(short id)
{
    RecycleTimeView *self = reinterpret_cast<RecycleTimeView *>(this);
    char index = static_cast<char>(id - 1);
    // LIFT: 25 = DB_RECYCLE_GROUP_COUNT; _recycleGroup[4] is the db group.
    if (index < 0 || index >= 25)
    {
        Log::Write(Log::LT_ERROR, L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\gamedaemon\\RecycleTimeManager.cpp", 619,
                   L"[recycle time manager], confirmRecycleTime, invalid groupId %d", id);
        return;
    }
    self->_recycleGroup[4][index].confirmed = true;
}

// 0x611020
void __cdecl RecycleTimeManager::FetchAllAccountRecycleTime(::std::vector< ::AccountRecycleTime, ::StlAllocator< ::AccountRecycleTime, 2> > &)
{
    LIFT_STUB(0x611020);
}
