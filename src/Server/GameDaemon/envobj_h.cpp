// envobj_h.cpp: envobj.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "envobj.h"
#include "item.h"
#include "pc.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?GetOwnerId@Env@@UEAA_KXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?CheckToManipulate@AirDash@@UEAA_NPEAVPc@@PEAVItem@@PEBUQuestRequiredItems@@DAEAF@Z")  // LIFT: dead-strip keep (no live caller yet)

// 0x4553f0
short __cdecl Env::GetActionRadius(void)
{
    LIFT_STUB(0x4553f0);
}

// 0x455400
long __cdecl Env::GetManipulateDuration(char)
{
    LIFT_STUB(0x455400);
}

// 0x455410
unsigned __int64 __cdecl Env::GetOwnerId(void)
{
    return _ownerId;
}

// 0x455430
bool __cdecl AirDash::CheckToManipulate(::Pc *, ::Item *, ::QuestRequiredItems const *, char, short &failReason)
{
    failReason = 641;  // LIFT: GAME_MANIPULATEFAIL_FAILED_TO_CHECK_MANIPULATE (0x281). The enum GameFailReason has no values yet.
    return false;
}
