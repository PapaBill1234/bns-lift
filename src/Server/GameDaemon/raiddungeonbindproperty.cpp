// raiddungeonbindproperty.cpp: raiddungeonbindproperty.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "raiddungeonbindproperty.h"
#include "propertysync.h"
#include "LiftStub.h"

// LIFT: keep the lifted virtual functions until the callers are lifted. Card lift-gamedaemon-e4.
#pragma comment(linker, "/INCLUDE:?Name@RaidDungeonBindProperty@@UEBAPEB_WXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?FieldMax@RaidDungeonBindProperty@@MEBAHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?FieldDefine@RaidDungeonBindProperty@@MEBAPEBUDef@Field@@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SyncMax@RaidDungeonBindProperty@@MEBAHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SyncDefine@RaidDungeonBindProperty@@MEBAPEBUDef@SyncBuffer@@XZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x19d80
wchar_t const * __cdecl RaidDungeonBindProperty::Name(void) const
{
    return L"RaidDungeonBindProperty";
}

// 0x19d90
int __cdecl RaidDungeonBindProperty::FieldMax(void) const
{
    return fieldMax;
}

// 0x19da0
::Field::Def const * __cdecl RaidDungeonBindProperty::FieldDefine(void) const
{
    return fieldDefine;
}

// 0x19db0
int __cdecl RaidDungeonBindProperty::SyncMax(void) const
{
    return syncMax;
}

// 0x19dc0
::SyncBuffer::Def const * __cdecl RaidDungeonBindProperty::SyncDefine(void) const
{
    return syncDefine;
}

// LIFT: definitions of the PDB static data members (card lift-gamedaemon-e4).
int RaidDungeonBindProperty::fieldMax;
::Field::Def const * RaidDungeonBindProperty::fieldDefine;
int RaidDungeonBindProperty::syncMax;
::SyncBuffer::Def const * RaidDungeonBindProperty::syncDefine;
