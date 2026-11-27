// weaponproperty.cpp: weaponproperty.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "weaponproperty.h"
#include "propertysync.h"
#include "LiftStub.h"

// 0x1a2c0
__cdecl WeaponProperty::~WeaponProperty(void)
{
    LIFT_STUB(0x1a2c0);
}

// 0x1a2d0
wchar_t const * __cdecl WeaponProperty::Name(void) const
{
    LIFT_STUB(0x1a2d0);
}

// 0x1a2e0
int __cdecl WeaponProperty::FieldMax(void) const
{
    LIFT_STUB(0x1a2e0);
}

// 0x1a2f0
::Field::Def const * __cdecl WeaponProperty::FieldDefine(void) const
{
    LIFT_STUB(0x1a2f0);
}

// 0x1a300
int __cdecl WeaponProperty::SyncMax(void) const
{
    LIFT_STUB(0x1a300);
}

// 0x1a310
::SyncBuffer::Def const * __cdecl WeaponProperty::SyncDefine(void) const
{
    LIFT_STUB(0x1a310);
}
