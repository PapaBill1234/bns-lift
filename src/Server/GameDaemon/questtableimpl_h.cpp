// questtableimpl_h.cpp: questtableimpl.h (GameDaemon PDB, 2019 + PDB).
#include "questtableimpl.h"
#include "LiftStub.h"

// LIFT: keep the lifted virtual functions until the callers are lifted (the vftable and the callers are stubs;
// /OPT:REF drops them). Card lift-gamedaemon-gap-005-e5.
#pragma comment(linker, "/INCLUDE:?GetMaxQuestId@QuestTableImpl@@UEBAGXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetQuestByIndex@QuestTableImpl@@UEBAPEBVQuest@@H@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetMaxQuestNum@QuestTableImpl@@UEBAGXZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x6f86e0
unsigned short __cdecl QuestTableImpl::GetMaxQuestId(void) const
{
    return _maxQuestId;
}

// 0x6f86f0
::Quest const * __cdecl QuestTableImpl::GetQuestByIndex(int i) const
{
    return _questListArray[i];
}

// 0x6f8700
unsigned short __cdecl QuestTableImpl::GetMaxQuestNum(void) const
{
    return _questListSize;
}
