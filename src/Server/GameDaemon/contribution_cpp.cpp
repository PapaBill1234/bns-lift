// contribution_cpp.cpp: contribution.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "contribution.h"
#include "gameobject.h"
#include "npc.h"
#include "npcdeadbody.h"
#include "pc.h"
#include "LiftStub.h"

// 0x984d0
void __cdecl PcContribution::Reset(::Pc *, __int64)
{
    LIFT_STUB(0x984d0);
}

// 0x985e0
void __cdecl ContributionPouch::writeGameLog(::Pc *, ::NpcDeadBody *, unsigned __int64, short)
{
    LIFT_STUB(0x985e0);
}

// 0x98b30
void __cdecl NpcContribution::IncreaseContribution(::Npc *, ::GameObject *, __int64)
{
    LIFT_STUB(0x98b30);
}

// 0x98ba0
void __cdecl FactionContribution::IncreaseContribution(::Npc *, ::GameObject *, __int64)
{
    LIFT_STUB(0x98ba0);
}

// 0x98ca0
void __cdecl FactionContribution::DecreaseContribution(::Npc *, __int64, __int64)
{
    LIFT_STUB(0x98ca0);
}

// 0x98cf0
void __cdecl FactionContribution::updateTopContribution(::Npc *, __int64)
{
    LIFT_STUB(0x98cf0);
}

// 0x98dd0
__int64 __cdecl FactionContribution::TopContributionGroupId(void)
{
    LIFT_STUB(0x98dd0);
}

// 0x98e00
__int64 __cdecl FactionContribution::TotalDamage(void)
{
    LIFT_STUB(0x98e00);
}

// 0x98e40
void __cdecl FactionContribution::Reset(void)
{
    LIFT_STUB(0x98e40);
}

// 0x98e60
void __cdecl GuildContribution::IncreaseContribution(::Npc *, ::GameObject *, __int64)
{
    LIFT_STUB(0x98e60);
}

// 0x98f10
void __cdecl GuildContribution::updateTopContribution(::Npc *, __int64, __int64)
{
    LIFT_STUB(0x98f10);
}

// 0x99320
void __cdecl GuildContribution::DecreaseContribution(::Npc *, __int64, __int64)
{
    LIFT_STUB(0x99320);
}

// 0x994e0
__int64 __cdecl GuildContribution::TopContributionGroupId(void)
{
    LIFT_STUB(0x994e0);
}

// 0x99500
__int64 __cdecl GuildContribution::TotalDamage(void)
{
    LIFT_STUB(0x99500);
}

// 0x99520
void __cdecl GuildContribution::Reset(void)
{
    LIFT_STUB(0x99520);
}
