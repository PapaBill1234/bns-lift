// contribution_cpp.cpp: contribution.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "contribution.h"
#include "gameobject.h"
#include "npc.h"
#include "npcdeadbody.h"
#include "pc.h"
#include "LiftStub.h"
#include <string.h>

#pragma comment(linker, "/INCLUDE:?TopContributionGroupId@FactionContribution@@UEAA_JXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Reset@GuildContribution@@UEAAXXZ")  // LIFT: dead-strip keep (no live caller yet)

// Partial PDB layouts. The class declarations in contribution.h hold no data members.
// FactionContribution : NpcContribution (size 0x38).
struct FactionContributionView
{
    void *vfptr;                    // +0
    __int64 _totalDamage;           // +8 (NpcContribution)
    char _firstAttackFaction;       // +16
    __int64 _mainFaction1Damage[2]; // +24
    __int64 _mainFaction2Damage[2]; // +40
};

// GuildContribution : NpcContribution (size 0xB8).
struct GuildContributionInfoView
{
    unsigned __int64 guildId;       // +0
    short attackOrder;              // +8
    __int64 damage[2];              // +16
};

struct GuildContributionView
{
    void *vfptr;                                // +0
    __int64 _totalDamage;                       // +8 (NpcContribution)
    GuildContributionInfoView _contributionList[5]; // +16
    char _contributionListCount;                // +176
    short _attackOrder;                         // +178
};

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
    FactionContributionView *self = reinterpret_cast<FactionContributionView *>(this);
    __int64 v1 = self->_mainFaction1Damage[0];
    __int64 v2 = self->_mainFaction2Damage[0];
    if (v1 > v2)
        return 1;
    if (v1 < v2)
        return 2;
    return self->_firstAttackFaction;
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
    GuildContributionView *self = reinterpret_cast<GuildContributionView *>(this);
    self->_totalDamage = 0;
    self->_attackOrder = 0;
    memset(self->_contributionList, 0, sizeof(self->_contributionList));
    self->_contributionListCount = 0;
}
