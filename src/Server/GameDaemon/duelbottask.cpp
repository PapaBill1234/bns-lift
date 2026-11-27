// duelbottask.cpp: duelbottask.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "duelbottask.h"
#include "duelbot.h"
#include "zone.h"
#include "LiftStub.h"

// 0xab600
__cdecl DuelBotSpawnTask::DuelBotSpawnTask(void)
{
    LIFT_STUB(0xab600);
}

// 0xab690
bool __cdecl DuelBotSpawnTask::Initialize(::Zone *, ::Data::DuelBotRecordPtr const &, int, long, short, short, short, short, short, ::EnterReason)
{
    LIFT_STUB(0xab690);
}

// 0xab810
void __cdecl DuelBotSpawnTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0xab810);
}

// 0xab9c0
bool __cdecl DuelBotSpawnTask::spawn(unsigned __int64)
{
    LIFT_STUB(0xab9c0);
}

// 0xac130
__cdecl DuelBotSetBrainTask::DuelBotSetBrainTask(void)
{
    LIFT_STUB(0xac130);
}

// 0xac1a0
bool __cdecl DuelBotSetBrainTask::Initialize(::Zone *, __int64, __int64, short)
{
    LIFT_STUB(0xac1a0);
}

// 0xac270
void __cdecl DuelBotSetBrainTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0xac270);
}

// 0xac2f0
__cdecl DuelBotSummonedSpawnTask::DuelBotSummonedSpawnTask(void)
{
    LIFT_STUB(0xac2f0);
}

// 0xac370
bool __cdecl DuelBotSummonedSpawnTask::Initialize(::Zone *, ::DuelBot *, short, short, short, short, short, ::EnterReason, unsigned __int64)
{
    LIFT_STUB(0xac370);
}

// 0xac4b0
void __cdecl DuelBotSummonedSpawnTask::start(void)
{
    LIFT_STUB(0xac4b0);
}

// 0xac4f0
bool __cdecl DuelBotSummonedSpawnTask::enter(void)
{
    LIFT_STUB(0xac4f0);
}

// 0xac8d0
bool __cdecl DuelBotSummonedSpawnTask::spawn(void)
{
    LIFT_STUB(0xac8d0);
}
