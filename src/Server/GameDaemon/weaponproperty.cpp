// weaponproperty.cpp: weaponproperty.h (GameDaemon PDB, 2019 + PDB).
#include "weaponproperty.h"
#include "propertysync.h"
#include "LiftStub.h"

// LIFT: keep the lifted virtual functions until the callers are lifted. Card lift-gamedaemon-gap-013-e13.
#pragma comment(linker, "/INCLUDE:?Name@WeaponProperty@@UEBAPEB_WXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?FieldMax@WeaponProperty@@MEBAHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?FieldDefine@WeaponProperty@@MEBAPEBUDef@Field@@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SyncMax@WeaponProperty@@MEBAHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SyncDefine@WeaponProperty@@MEBAPEBUDef@SyncBuffer@@XZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x1a2c0
__cdecl WeaponProperty::~WeaponProperty(void)
{
    LIFT_STUB(0x1a2c0);
}

// 0x1a2d0
wchar_t const * __cdecl WeaponProperty::Name(void) const
{
    return L"WeaponProperty";
}

// 0x1a2e0
int __cdecl WeaponProperty::FieldMax(void) const
{
    return fieldMax;
}

// 0x1a2f0
::Field::Def const * __cdecl WeaponProperty::FieldDefine(void) const
{
    return fieldDefine;
}

// 0x1a300
int __cdecl WeaponProperty::SyncMax(void) const
{
    return syncMax;
}

// 0x1a310
::SyncBuffer::Def const * __cdecl WeaponProperty::SyncDefine(void) const
{
    return syncDefine;
}

// LIFT: definitions of the PDB static data members.
int WeaponProperty::fieldMax;
::Field::Def const * WeaponProperty::fieldDefine;
int WeaponProperty::syncMax;
::SyncBuffer::Def const * WeaponProperty::syncDefine;
