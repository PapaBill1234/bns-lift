// accessoryproperty.cpp: accessoryproperty.h (GameDaemon PDB, 2019 + PDB).
#include "accessoryproperty.h"
#include "gamedaemon.h"
#include "propertysync.h"
#include "LiftStub.h"

// LIFT: keep the lifted virtual functions until the callers are lifted (the vftable and the callers are stubs;
// /OPT:REF drops them). Card lift-gamedaemon-gap-005-e5.
#pragma comment(linker, "/INCLUDE:?TypeId@AccessoryProperty@@UEBA?BHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Version@AccessoryProperty@@UEBAHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Name@AccessoryProperty@@UEBAPEB_WXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?FieldMax@AccessoryProperty@@MEBAHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?FieldDefine@AccessoryProperty@@MEBAPEBUDef@Field@@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SyncMax@AccessoryProperty@@MEBAHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SyncDefine@AccessoryProperty@@MEBAPEBUDef@SyncBuffer@@XZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x191d0
int const __cdecl AccessoryProperty::TypeId(void) const
{
    return 15;
}

// 0x191e0
// LIFT: the PDB names this RVA AccessoryProperty::Version; the old stub name GameDaemon::GetTimerMaxTime is the same code (return 20).
int __cdecl AccessoryProperty::Version(void) const
{
    return 20;
}

// 0x191e0 (same code under the GameDaemon vftable slot; the class has no live caller yet)
long __cdecl GameDaemon::GetTimerMaxTime(void)
{
    return 20;
}

// 0x191f0
wchar_t const * __cdecl AccessoryProperty::Name(void) const
{
    return L"AccessoryProperty";
}

// 0x19200
int __cdecl AccessoryProperty::FieldMax(void) const
{
    return fieldMax;
}

// 0x19210
::Field::Def const * __cdecl AccessoryProperty::FieldDefine(void) const
{
    return fieldDefine;
}

// 0x19220
int __cdecl AccessoryProperty::SyncMax(void) const
{
    return syncMax;
}

// 0x19230
::SyncBuffer::Def const * __cdecl AccessoryProperty::SyncDefine(void) const
{
    return syncDefine;
}

// LIFT: definitions of the PDB static data members (see creatureproperty.h).
int AccessoryProperty::fieldMax;
::Field::Def const * AccessoryProperty::fieldDefine;
int AccessoryProperty::syncMax;
::SyncBuffer::Def const * AccessoryProperty::syncDefine;
