// skillaction_h.cpp: skillaction.h (GameDaemon PDB, 2019 + PDB).
#include "skillaction.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:??1TargetSelectorForDamageTransferNpcSquad@@UEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?getDashAngle@SkillAction@@MEAAF_K@Z")  // LIFT: dead-strip keep (no live caller yet)

// 0x27560
__cdecl TargetSelectorForDamageTransferNpcSquad::~TargetSelectorForDamageTransferNpcSquad(void)
{
}

// 0x275e0
::ActionPriorityClass __cdecl SkillAction::getPriority(void) const
{
    LIFT_STUB(0x275e0);
}

// 0x27600
short __cdecl SkillAction::getDashAngle(unsigned __int64)
{
    return _dashAngle;
}
