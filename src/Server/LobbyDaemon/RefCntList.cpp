// RefCntList.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "RefCntList.h"
#include "LiftStub.h"

// 0x64c80
RefCntList::RefCntList()
{
    LIFT_STUB(0x64c80);
}

// 0x64c90
RefCntList::~RefCntList()
{
    LIFT_STUB(0x64c90);
}

// 0x64d00
bool RefCntList::Pushback(RefCntListNode*)
{
    LIFT_STUB(0x64d00);
}

// 0x64da0
bool RefCntList::Remove(RefCntListNode*)
{
    LIFT_STUB(0x64da0);
}
