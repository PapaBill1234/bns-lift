// contribution_h.cpp: contribution.h (GameDaemon PDB, 2019 + PDB).
#include "contribution.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?Reset@NpcContribution@@UEAAXXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:??0PcContribution@@QEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:??0ContributionPouch@@QEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)

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
    // ❓ The original probably calls ContributionPouch::Reset (inline). Reset is not declared in the skeleton yet.
    _rewardGroup = -2;
    _exceptLootCaseBitMap = 0;
    _id = 0;
    _deadBodyZoneIndex = 0;
    _rewardItemCount = 0;
    for (int i = 0; i < 2; ++i)
    {
        _rewardItem[i].itemKey = 0;
        _rewardItem[i].itemCount = 0;
        _rewardItem[i].isContribution = false;
    }
}
