// publicraid_h.cpp: publicraid.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "publicraid.h"
#include "attractionstate.h"
#include "LiftStub.h"

// 0x35e90
__cdecl AttractionState::~AttractionState(void)
{
    LIFT_STUB(0x35e90);
}

// 0x180e50
wchar_t const * __cdecl PublicRaid::GetTypeName(void)
{
    LIFT_STUB(0x180e50);
}

// 0x180e60
int __cdecl PublicRaid::GetMaxPcCount(void)
{
    LIFT_STUB(0x180e60);
}
