// tendencymanager_h.cpp: tendencymanager.h (GameDaemon PDB, 2019 + PDB).
#include "tendencymanager.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:??1TendencyAttractionQuestPack@@UEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x1edf30
// The body only stores the own vftable (no base and no member dtor work).
__cdecl TendencyAttractionQuestPack::~TendencyAttractionQuestPack(void)
{
}
