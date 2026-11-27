// summonedproperty.cpp: summonedproperty.h (GameDaemon PDB, 2019 + PDB).
#include "summonedproperty.h"
#include "propertysync.h"
#include "LiftStub.h"

// LIFT: keep the lifted virtual functions until the callers are lifted. Card lift-gamedaemon-gap-013-e13.
#pragma comment(linker, "/INCLUDE:?Name@SummonedProperty@@UEBAPEB_WXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?FieldMax@SummonedProperty@@MEBAHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?FieldDefine@SummonedProperty@@MEBAPEBUDef@Field@@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SyncMax@SummonedProperty@@MEBAHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SyncDefine@SummonedProperty@@MEBAPEBUDef@SyncBuffer@@XZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x1a220
__cdecl SummonedProperty::~SummonedProperty(void)
{
    LIFT_STUB(0x1a220);
}

// 0x1a240
wchar_t const * __cdecl SummonedProperty::Name(void) const
{
    return L"SummonedProperty";
}

// 0x1a250
int __cdecl SummonedProperty::FieldMax(void) const
{
    return fieldMax;
}

// 0x1a260
::Field::Def const * __cdecl SummonedProperty::FieldDefine(void) const
{
    return fieldDefine;
}

// 0x1a270
int __cdecl SummonedProperty::SyncMax(void) const
{
    return syncMax;
}

// 0x1a280
::SyncBuffer::Def const * __cdecl SummonedProperty::SyncDefine(void) const
{
    return syncDefine;
}

// LIFT: definitions of the PDB static data members.
int SummonedProperty::fieldMax;
::Field::Def const * SummonedProperty::fieldDefine;
int SummonedProperty::syncMax;
::SyncBuffer::Def const * SummonedProperty::syncDefine;
