// creatureproperty.cpp: creatureproperty.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "creatureproperty.h"
#include "propertysync.h"
#include "LiftStub.h"

// LIFT: keep the lifted virtual functions until the callers are lifted (the vftable and the callers are stubs;
// /OPT:REF drops them). Card lift-gamedaemon-0d.
#pragma comment(linker, "/INCLUDE:?Version@CreatureProperty@@UEBAHXZ")
#pragma comment(linker, "/INCLUDE:?Name@CreatureProperty@@UEBAPEB_WXZ")
#pragma comment(linker, "/INCLUDE:?FieldMax@CreatureProperty@@MEBAHXZ")
#pragma comment(linker, "/INCLUDE:?FieldDefine@CreatureProperty@@MEBAPEBUDef@Field@@XZ")
#pragma comment(linker, "/INCLUDE:?SyncMax@CreatureProperty@@MEBAHXZ")
#pragma comment(linker, "/INCLUDE:?SyncDefine@CreatureProperty@@MEBAPEBUDef@SyncBuffer@@XZ")

// 0x19340
__cdecl CreatureProperty::~CreatureProperty(void)
{
    LIFT_STUB(0x19340);
}

// 0x19350
int __cdecl CreatureProperty::Version(void) const
{
    return 293;
}

// 0x19360
wchar_t const * __cdecl CreatureProperty::Name(void) const
{
    return L"CreatureProperty";
}

// 0x19370
int __cdecl CreatureProperty::FieldMax(void) const
{
    return fieldMax;
}

// 0x19380
::Field::Def const * __cdecl CreatureProperty::FieldDefine(void) const
{
    return fieldDefine;
}

// 0x19390
int __cdecl CreatureProperty::SyncMax(void) const
{
    return syncMax;
}

// 0x193a0
::SyncBuffer::Def const * __cdecl CreatureProperty::SyncDefine(void) const
{
    return syncDefine;
}

// LIFT: definitions of the PDB static data members (see the PDB data records of the class). Pilot of card lift-gamedaemon-0d.
int CreatureProperty::fieldMax;
::Field::Def const * CreatureProperty::fieldDefine;
int CreatureProperty::syncMax;
::SyncBuffer::Def const * CreatureProperty::syncDefine;
