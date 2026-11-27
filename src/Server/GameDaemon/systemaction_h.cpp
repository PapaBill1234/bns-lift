// systemaction_h.cpp: systemaction.h (GameDaemon PDB, 2019 + PDB).
#include "systemaction.h"
#include "action.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?cancelAction@RestorationAction@@EEAAXW4CancelReason@Action@@PEB_WH@Z")  // LIFT: dead-strip keep (no live caller yet)

// 0x456530
void __cdecl RestorationAction::cancelAction(::Action::CancelReason reason, wchar_t const *file, int line)
{
    cancelAction(reason, file, line, 0);
}
