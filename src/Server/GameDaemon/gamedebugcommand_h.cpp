// gamedebugcommand_h.cpp: gamedebugcommand.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "gamedebugcommand.h"
#include "creature.h"
#include "zone.h"
#include "LiftStub.h"

// 0x283bc0
__cdecl WarpToPosDebugTask::WarpToPosDebugTask(void)
{
    LIFT_STUB(0x283bc0);
}

// 0x350cc0
__cdecl MakeSummonedDebugTask::MakeSummonedDebugTask(void)
{
    LIFT_STUB(0x350cc0);
}

// 0x350d30
__cdecl QuestDebugTask::QuestDebugTask(void)
{
    LIFT_STUB(0x350d30);
}

// 0x350d70
__cdecl GetCubeIndexDebugTask::GetCubeIndexDebugTask(::Session *)
{
    LIFT_STUB(0x350d70);
}

// 0x350e50
bool __cdecl InvokeEffectDebugTask::Initialize(unsigned __int64, wchar_t const *, wchar_t const *, wchar_t const *)
{
    LIFT_STUB(0x350e50);
}

// 0x351000
__cdecl SetScriptDebugTask::SetScriptDebugTask(void)
{
    LIFT_STUB(0x351000);
}

// 0x351040
bool __cdecl SetScriptDebugTask::Initialize(unsigned __int64, ::SetScriptDebugTask::ScriptDebugType, unsigned __int64, unsigned int)
{
    LIFT_STUB(0x351040);
}

// 0x3510d0
bool __cdecl SetChattingAvailableDebugTask::Initialize(::Zone *, ::Creature *, bool)
{
    LIFT_STUB(0x3510d0);
}

// 0x351150
__cdecl AcquireFishDebugTask::AcquireFishDebugTask(void)
{
    LIFT_STUB(0x351150);
}

// 0x351190
bool __cdecl AcquireFishDebugTask::Initialize(::Zone *, ::Creature *, wchar_t const *, int, unsigned __int64)
{
    LIFT_STUB(0x351190);
}
