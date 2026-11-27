// collectingproperty.cpp: collectingproperty.h (GameDaemon PDB, 2019 + PDB).
#include "collectingproperty.h"
#include "propertysync.h"
#include "LiftStub.h"

// LIFT: keep the lifted virtual functions until the callers are lifted. Card lift-gamedaemon-gap-002-e2.
#pragma comment(linker, "/INCLUDE:?TypeId@CollectingProperty@@UEBA?BHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Name@CollectingProperty@@UEBAPEB_WXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?FieldMax@CollectingProperty@@MEBAHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?FieldDefine@CollectingProperty@@MEBAPEBUDef@Field@@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SyncMax@CollectingProperty@@MEBAHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SyncDefine@CollectingProperty@@MEBAPEBUDef@SyncBuffer@@XZ")  // LIFT: dead-strip keep (no live caller yet)


// 0x19570
__cdecl CollectingProperty::~CollectingProperty(void)
{
    LIFT_STUB(0x19570);
}

// 0x19580
int const __cdecl CollectingProperty::TypeId(void) const
{
    return 36;
}

// 0x195a0
wchar_t const * __cdecl CollectingProperty::Name(void) const
{
    return L"CollectingProperty";
}

// 0x195b0
int __cdecl CollectingProperty::FieldMax(void) const
{
    return fieldMax;
}

// 0x195c0
::Field::Def const * __cdecl CollectingProperty::FieldDefine(void) const
{
    return fieldDefine;
}

// 0x195d0
int __cdecl CollectingProperty::SyncMax(void) const
{
    return syncMax;
}

// 0x195e0
::SyncBuffer::Def const * __cdecl CollectingProperty::SyncDefine(void) const
{
    return syncDefine;
}

// LIFT: definitions of the PDB static data members.
int CollectingProperty::fieldMax;
::Field::Def const * CollectingProperty::fieldDefine;
int CollectingProperty::syncMax;
::SyncBuffer::Def const * CollectingProperty::syncDefine;
