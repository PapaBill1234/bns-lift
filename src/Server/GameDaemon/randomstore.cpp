// randomstore.cpp: randomstore.h (GameDaemon PDB, 2019 + PDB).
#include "randomstore.h"
#include "propertysync.h"
#include "LiftStub.h"

// LIFT: keep the lifted virtual functions until the callers are lifted. Card lift-gamedaemon-e4.
#pragma comment(linker, "/INCLUDE:?TypeId@RandomStore@@UEBA?BHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Name@RandomStore@@UEBAPEB_WXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?FieldMax@RandomStore@@MEBAHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?FieldDefine@RandomStore@@MEBAPEBUDef@Field@@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SyncMax@RandomStore@@MEBAHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SyncDefine@RandomStore@@MEBAPEBUDef@SyncBuffer@@XZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x19e90
__cdecl RandomStore::~RandomStore(void)
{
    LIFT_STUB(0x19e90);
}

// 0x19ea0
int const __cdecl RandomStore::TypeId(void) const
{
    return 28;
}

// 0x19eb0
wchar_t const * __cdecl RandomStore::Name(void) const
{
    return L"RandomStore";
}

// 0x19ec0
int __cdecl RandomStore::FieldMax(void) const
{
    return fieldMax;
}

// 0x19ed0
::Field::Def const * __cdecl RandomStore::FieldDefine(void) const
{
    return fieldDefine;
}

// 0x19ee0
int __cdecl RandomStore::SyncMax(void) const
{
    return syncMax;
}

// 0x19ef0
::SyncBuffer::Def const * __cdecl RandomStore::SyncDefine(void) const
{
    return syncDefine;
}

// LIFT: definitions of the PDB static data members (card lift-gamedaemon-e4).
int RandomStore::fieldMax;
::Field::Def const * RandomStore::fieldDefine;
int RandomStore::syncMax;
::SyncBuffer::Def const * RandomStore::syncDefine;
