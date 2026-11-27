// envobj_h.cpp: envobj.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "envobj.h"
#include "item.h"
#include "pc.h"
#include "LiftStub.h"

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
    LIFT_STUB(0x455410);
}

// 0x455430
bool __cdecl AirDash::CheckToManipulate(::Pc *, ::Item *, ::QuestRequiredItems const *, char, short &)
{
    LIFT_STUB(0x455430);
}
