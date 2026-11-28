// leadtheballmanager_h.cpp: leadtheballmanager.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "leadtheballmanager.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?EventId@DeleteEvent@@UEBAIXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Context1@LeadTheBallManager@@UEAA_JXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Context2@LeadTheBallManager@@UEAA_JXZ")  // LIFT: dead-strip keep (no live caller yet)

namespace
{
// LIFT: view of the PDB base class PartyBattleManager. Only the fields that the lifted bodies read are declared.
struct PartyBattleManagerView
{
    char lift_pad_0[0x30];               // ❓ no PDB name: vfptr and PartyBattleManager +8 to +0x2F are not declared here
    char _inGameSubStep;                 // +48 (0x30)
    __int64 _inGameSubStepStartTime;     // +56 (0x38)
};
}

// 0x137a30
unsigned int __cdecl DeleteEvent::EventId(void) const
{
    return 7;
}

// 0x137a40
__int64 __cdecl LeadTheBallManager::Context1(void)
{
    return reinterpret_cast<PartyBattleManagerView const *>(this)->_inGameSubStep;
}

// 0x1ee470
// The binary folds this body with GameTranExpireToken::GetTid (load of +0x38).
__int64 __cdecl LeadTheBallManager::Context2(void)
{
    return reinterpret_cast<PartyBattleManagerView const *>(this)->_inGameSubStepStartTime;
}
