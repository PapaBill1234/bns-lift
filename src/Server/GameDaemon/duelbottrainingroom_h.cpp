// duelbottrainingroom_h.cpp: duelbottrainingroom.h (GameDaemon PDB, 2019 + PDB).
#include "duelbottrainingroom.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?GetTypeName@DuelBotTrainingRoom@@UEAAPEB_WXZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x97770
wchar_t const * __cdecl DuelBotTrainingRoom::GetTypeName(void)
{
    return L"DuelBotTrainingRoom";
}
