// contribution_h.cpp: contribution.h (GameDaemon PDB, 2019 + PDB).
#include "contribution.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?Reset@NpcContribution@@UEAAXXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:??0PcContribution@@QEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x8c2a0
void __cdecl NpcContribution::Reset(void)
{
    _totalDamage = 0;
}

// 0x455480
__cdecl PcContribution::PcContribution(void)
{
    // PDB: PcContribution::reset (inline).
    _npcId = 0;
    _combatStartTime = 0;
    _contributionType = 0;
    _damage[0] = 0;
    _damage[1] = 0;
}

// 0x4554a0
__cdecl ContributionPouch::ContributionPouch(void)
{
    LIFT_STUB(0x4554a0);
}
