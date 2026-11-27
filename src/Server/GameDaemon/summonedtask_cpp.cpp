// summonedtask_cpp.cpp: summonedtask.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "summonedtask.h"
#include "inventory.h"
#include "pc.h"
#include "zone.h"
#include "LiftStub.h"

// 0x1c0290
__cdecl SummonedSpawnTask::SummonedSpawnTask(void)
{
    LIFT_STUB(0x1c0290);
}

// 0x1c0310
bool __cdecl SummonedSpawnTask::Initialize(::Zone *, ::Pc *, short, short, short, short, short, ::EnterReason, unsigned __int64)
{
    LIFT_STUB(0x1c0310);
}

// 0x1c0450
void __cdecl SummonedSpawnTask::start(void)
{
    LIFT_STUB(0x1c0450);
}

// 0x1c0490
bool __cdecl SummonedSpawnTask::enter(void)
{
    LIFT_STUB(0x1c0490);
}

// 0x1c0e40
bool __cdecl SummonedSpawnTask::spawn(void)
{
    LIFT_STUB(0x1c0e40);
}

// 0x1c0fd0
bool __cdecl ChangeSummonedTask::Initialize(::Zone *const, ::Pc *const, unsigned __int64, char const *const, int)
{
    LIFT_STUB(0x1c0fd0);
}

// 0x1c1150
void __cdecl ChangeSummonedTask::start(void)
{
    LIFT_STUB(0x1c1150);
}

// 0x1c2240
bool __cdecl ChangeSummonedNameTask::Initialize(::Zone *const, ::Pc *const, wchar_t const *const, int, ::Inventory::DisposeOrderWithPos const *const)
{
    LIFT_STUB(0x1c2240);
}

// 0x1c2620
void __cdecl ChangeSummonedNameTask::start(void)
{
    LIFT_STUB(0x1c2620);
}
