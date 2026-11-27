// groceryproperty.cpp: groceryproperty.h (GameDaemon PDB, 2019 + PDB).
#include "groceryproperty.h"
#include "propertysync.h"
#include "LiftStub.h"

// LIFT: keep the lifted virtual functions until the callers are lifted (card lift-gamedaemon-gap-003-e3).
#pragma comment(linker, "/INCLUDE:?Version@GroceryProperty@@UEBAHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Name@GroceryProperty@@UEBAPEB_WXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?FieldMax@GroceryProperty@@MEBAHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?FieldDefine@GroceryProperty@@MEBAPEBUDef@Field@@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SyncMax@GroceryProperty@@MEBAHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SyncDefine@GroceryProperty@@MEBAPEBUDef@SyncBuffer@@XZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x19b40
int __cdecl GroceryProperty::Version(void) const
{
    return 18;
}

// 0x19b50
wchar_t const * __cdecl GroceryProperty::Name(void) const
{
    return L"GroceryProperty";
}

// 0x19b60
int __cdecl GroceryProperty::FieldMax(void) const
{
    return fieldMax;
}

// 0x19b70
::Field::Def const * __cdecl GroceryProperty::FieldDefine(void) const
{
    return fieldDefine;
}

// 0x19b80
int __cdecl GroceryProperty::SyncMax(void) const
{
    return syncMax;
}

// 0x19b90
::SyncBuffer::Def const * __cdecl GroceryProperty::SyncDefine(void) const
{
    return syncDefine;
}

// LIFT: definitions of the PDB static data members (set at start-up by Property::initInstance, a later wave).
int GroceryProperty::fieldMax;
::Field::Def const * GroceryProperty::fieldDefine;
int GroceryProperty::syncMax;
::SyncBuffer::Def const * GroceryProperty::syncDefine;
