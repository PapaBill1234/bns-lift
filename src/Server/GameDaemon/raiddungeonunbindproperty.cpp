// raiddungeonunbindproperty.cpp: raiddungeonunbindproperty.h (GameDaemon PDB, 2019 + PDB).
#include "raiddungeonunbindproperty.h"
#include "propertysync.h"
#include "LiftStub.h"

// LIFT: keep the lifted virtual functions until the callers are lifted. Card lift-gamedaemon-e4.
#pragma comment(linker, "/INCLUDE:?TypeId@RaidDungeonUnbindProperty@@UEBA?BHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Name@RaidDungeonUnbindProperty@@UEBAPEB_WXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?FieldMax@RaidDungeonUnbindProperty@@MEBAHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?FieldDefine@RaidDungeonUnbindProperty@@MEBAPEBUDef@Field@@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SyncMax@RaidDungeonUnbindProperty@@MEBAHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SyncDefine@RaidDungeonUnbindProperty@@MEBAPEBUDef@SyncBuffer@@XZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x19e00
int const __cdecl RaidDungeonUnbindProperty::TypeId(void) const
{
    return 30;
}

// 0x19e10
wchar_t const * __cdecl RaidDungeonUnbindProperty::Name(void) const
{
    return L"RaidDungeonUnbindProperty";
}

// 0x19e20
int __cdecl RaidDungeonUnbindProperty::FieldMax(void) const
{
    return fieldMax;
}

// 0x19e30
::Field::Def const * __cdecl RaidDungeonUnbindProperty::FieldDefine(void) const
{
    return fieldDefine;
}

// 0x19e40
int __cdecl RaidDungeonUnbindProperty::SyncMax(void) const
{
    return syncMax;
}

// 0x19e50
::SyncBuffer::Def const * __cdecl RaidDungeonUnbindProperty::SyncDefine(void) const
{
    return syncDefine;
}

// LIFT: definitions of the PDB static data members (card lift-gamedaemon-e4).
int RaidDungeonUnbindProperty::fieldMax;
::Field::Def const * RaidDungeonUnbindProperty::fieldDefine;
int RaidDungeonUnbindProperty::syncMax;
::SyncBuffer::Def const * RaidDungeonUnbindProperty::syncDefine;
