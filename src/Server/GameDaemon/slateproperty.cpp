// slateproperty.cpp: slateproperty.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "slateproperty.h"
#include "propertysync.h"
#include "LiftStub.h"

// 0x9750
int const __cdecl SlateProperty::TypeId(void) const
{
    LIFT_STUB(0x9750);
}

// 0x9760
wchar_t const * __cdecl SlateProperty::Name(void) const
{
    LIFT_STUB(0x9760);
}

// 0x9770
int __cdecl SlateProperty::FieldMax(void) const
{
    LIFT_STUB(0x9770);
}

// 0x9780
::Field::Def const * __cdecl SlateProperty::FieldDefine(void) const
{
    LIFT_STUB(0x9780);
}

// 0x9790
int __cdecl SlateProperty::SyncMax(void) const
{
    LIFT_STUB(0x9790);
}

// 0x97a0
::SyncBuffer::Def const * __cdecl SlateProperty::SyncDefine(void) const
{
    LIFT_STUB(0x97a0);
}
