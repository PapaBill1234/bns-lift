// BoundedList.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "BoundedList.h"
#include "LiftStub.h"

// 0x18540
bool BoundedList::Init(int)
{
    LIFT_STUB(0x18540);
}

// 0x18650
short BoundedList::Pushback(void*)
{
    LIFT_STUB(0x18650);
}

// 0x186f0
void* BoundedList::Popfront()
{
    LIFT_STUB(0x186f0);
}

// 0x18790
bool BoundedList::Remove(short)
{
    LIFT_STUB(0x18790);
}
