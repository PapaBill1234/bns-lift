// include_property.cpp: property.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "property.h"
#include "LiftStub.h"

// 0xe230
bool __cdecl Property::Set(unsigned short, bool)
{
    LIFT_STUB(0xe230);
}

// 0x1d120
bool __cdecl Property::GetFlag(unsigned short) const
{
    LIFT_STUB(0x1d120);
}

// 0x8c2b0
bool __cdecl Property::Set(unsigned short, wchar_t const *)
{
    LIFT_STUB(0x8c2b0);
}

// 0x1ed800
bool __cdecl Property::Set(unsigned short, unsigned char const *, short)
{
    LIFT_STUB(0x1ed800);
}
