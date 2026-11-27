// posttran_h.cpp: posttran.h (GameDaemon PDB, 2019 + PDB). The GetDefinition getters are lifted.
// LIFT: the _def data is not lifted yet. The empty GameTranDef of the header stands in for the PDB data.
#include "posttran.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?GetDefinition@MarkExpressPostTran@@UEBAPEBUGameTranDef@@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetDefinition@DetachPostAttachmentTran_IndetachFixed@@UEBAPEBUGameTranDef@@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetDefinition@DeliverPostTran@@UEBAPEBUGameTranDef@@XZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x1960e0
::GameTranDef const * __cdecl MarkExpressPostTran::GetDefinition(void) const
{
    return &_def;
}

// 0x1960f0
::GameTranDef const * __cdecl DetachPostAttachmentTran_IndetachFixed::GetDefinition(void) const
{
    return &_def;
}

// 0x196100
::GameTranDef const * __cdecl DeliverPostTran::GetDefinition(void) const
{
    return &_def;
}

// 0x196130
__cdecl ResumeDeliverPostTranAfterUICTask::ResumeDeliverPostTranAfterUICTask(void)
{
    LIFT_STUB(0x196130);
}

::GameTranDef MarkExpressPostTran::_def;
::GameTranDef DetachPostAttachmentTran_IndetachFixed::_def;
::GameTranDef DeliverPostTran::_def;
