// skilltrainingroom_h.cpp: skilltrainingroom.h (GameDaemon PDB, 2019 + PDB). Lifted: GetTypeName (card lift-gamedaemon-gap-006-e6).
#include "skilltrainingroom.h"
#include "LiftStub.h"

// LIFT: keep the lifted virtual until the callers are lifted (the vftable and the callers are stubs;
// /OPT:REF drops it). Card lift-gamedaemon-gap-006-e6.
#pragma comment(linker, "/INCLUDE:?GetTypeName@SkillTrainingRoom@@UEAAPEB_WXZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x180e40
wchar_t const * __cdecl SkillTrainingRoom::GetTypeName(void)
{
    return L"SkillTraningRoom";  // sic: the original string has this spelling
}
