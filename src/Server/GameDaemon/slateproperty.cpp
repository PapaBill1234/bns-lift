// slateproperty.cpp: slateproperty.h (GameDaemon PDB, 2019 + PDB).
#include "slateproperty.h"
#include "propertysync.h"
#include "LiftStub.h"

// LIFT: keep the lifted virtual functions until the callers are lifted (the vftable and the callers are stubs;
// /OPT:REF drops them). Card lift-gamedaemon-gap-005-e5.
#pragma comment(linker, "/INCLUDE:?TypeId@SlateProperty@@UEBA?BHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?FieldMax@SlateProperty@@MEBAHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?FieldDefine@SlateProperty@@MEBAPEBUDef@Field@@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SyncMax@SlateProperty@@MEBAHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SyncDefine@SlateProperty@@MEBAPEBUDef@SyncBuffer@@XZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x9750
int const __cdecl SlateProperty::TypeId(void) const
{
    return 39;
}

// 0x9760
wchar_t const * __cdecl SlateProperty::Name(void) const
{
    LIFT_STUB(0x9760);
}

// 0x9770
int __cdecl SlateProperty::FieldMax(void) const
{
    return fieldMax;
}

// 0x9780
::Field::Def const * __cdecl SlateProperty::FieldDefine(void) const
{
    return fieldDefine;
}

// 0x9790
int __cdecl SlateProperty::SyncMax(void) const
{
    return syncMax;
}

// 0x97a0
::SyncBuffer::Def const * __cdecl SlateProperty::SyncDefine(void) const
{
    return syncDefine;
}

// LIFT: definitions of the PDB static data members (see creatureproperty.h).
int SlateProperty::fieldMax;
::Field::Def const * SlateProperty::fieldDefine;
int SlateProperty::syncMax;
::SyncBuffer::Def const * SlateProperty::syncDefine;
