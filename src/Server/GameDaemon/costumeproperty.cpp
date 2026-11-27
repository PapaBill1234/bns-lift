// costumeproperty.cpp: costumeproperty.h (GameDaemon PDB, 2019 + PDB).
#include "costumeproperty.h"
#include "propertysync.h"
#include "LiftStub.h"

// LIFT: keep the lifted virtual functions until the callers are lifted. Card lift-gamedaemon-gap-002-e2.
// ❓ Version is declared virtual with the PDB type int (this const). The public name is not checked.
#pragma comment(linker, "/INCLUDE:?Version@CostumeProperty@@UEBAHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Name@CostumeProperty@@UEBAPEB_WXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?FieldMax@CostumeProperty@@MEBAHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?FieldDefine@CostumeProperty@@MEBAPEBUDef@Field@@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SyncMax@CostumeProperty@@MEBAHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SyncDefine@CostumeProperty@@MEBAPEBUDef@SyncBuffer@@XZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x196a0
__cdecl CostumeProperty::~CostumeProperty(void)
{
    LIFT_STUB(0x196a0);
}

// 0x196b0
int __cdecl CostumeProperty::Version(void) const
{
    return 29;
}

// 0x196c0
wchar_t const * __cdecl CostumeProperty::Name(void) const
{
    return L"CostumeProperty";
}

// 0x196d0
int __cdecl CostumeProperty::FieldMax(void) const
{
    return fieldMax;
}

// 0x196e0
::Field::Def const * __cdecl CostumeProperty::FieldDefine(void) const
{
    return fieldDefine;
}

// 0x196f0
int __cdecl CostumeProperty::SyncMax(void) const
{
    return syncMax;
}

// 0x19700
::SyncBuffer::Def const * __cdecl CostumeProperty::SyncDefine(void) const
{
    return syncDefine;
}

// LIFT: definitions of the PDB static data members.
int CostumeProperty::fieldMax;
::Field::Def const * CostumeProperty::fieldDefine;
int CostumeProperty::syncMax;
::SyncBuffer::Def const * CostumeProperty::syncDefine;
