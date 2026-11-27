// npctask.cpp: npctask.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "npctask.h"
#include "npc.h"
#include "zone.h"
#include "LiftStub.h"

// 0x456560
__cdecl NpcSpawnTask::NpcSpawnTask(void)
{
    LIFT_STUB(0x456560);
}

// 0x4565e0
bool __cdecl NpcSpawnTask::Initialize(::Zone &, ::Data::NpcRecordPtr, ::Data::ZoneNpcSpawnRecordPtr, int, short, short, short, short, short, ::NpcSpawnParam const &, ::EnterReason)
{
    LIFT_STUB(0x4565e0);
}

// 0x456860
bool __cdecl NpcSpawnTask::Initialize(::Zone &, ::Data::NpcRecordPtr, ::Data::ZoneNpcRandomSpawnRecordPtr, int, int, short, short, short, short, short, ::NpcSpawnParam const &, ::EnterReason)
{
    LIFT_STUB(0x456860);
}

// 0x456ae0
void __cdecl NpcSpawnTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x456ae0);
}

// 0x456ea0
bool __cdecl NpcSpawnTask::spawn(unsigned __int64)
{
    LIFT_STUB(0x456ea0);
}

// 0x4574d0
bool __cdecl NpcDespawnTask::Initialize(::Zone *, ::Npc *, bool, bool, unsigned __int64, long)
{
    LIFT_STUB(0x4574d0);
}

// 0x4575d0
void __cdecl NpcDespawnTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x4575d0);
}

// 0x4576b0
bool __cdecl ResumeRaidBossDeadTask::Initialize(::Zone *, ::Npc *, unsigned __int64, __int64)
{
    LIFT_STUB(0x4576b0);
}

// 0x457790
void __cdecl ResumeRaidBossDeadTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x457790);
}

// 0x457a00
bool __cdecl NpcPlaySocialTask::Initialize(::Zone *, ::Npc *, unsigned int, unsigned __int64, long, bool)
{
    LIFT_STUB(0x457a00);
}

// 0x457b70
void __cdecl NpcPlaySocialTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x457b70);
}
