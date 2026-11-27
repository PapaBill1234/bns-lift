// skillaction_h.cpp: skillaction.h (GameDaemon PDB, 2019 + PDB).
#include "skillaction.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:??1TargetSelectorForDamageTransferNpcSquad@@UEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?getDashAngle@SkillAction@@MEAAF_K@Z")  // LIFT: dead-strip keep (no live caller yet)

namespace
{
// LIFT: view of the PDB class SkillAction (base Action). Only the field that the lifted body reads is declared.
struct SkillActionView
{
    char lift_pad_0[0xE6];  // ❓ no PDB name: vfptr, base Action and fields +0 to +0xE5 are not declared yet
    short _dashAngle;       // +230 (0xE6)
};
}

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
    return reinterpret_cast<SkillActionView const *>(this)->_dashAngle;
}
