// recycletimeproperty.cpp: recycletimeproperty.h (GameDaemon PDB, 2019 + PDB).
#include "recycletimeproperty.h"
#include "propertysync.h"
#include "LiftStub.h"

// LIFT: keep the lifted virtual functions until the callers are lifted. Card lift-gamedaemon-e4.
#pragma comment(linker, "/INCLUDE:?Name@RecycleTimeProperty@@UEBAPEB_WXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?FieldMax@RecycleTimeProperty@@MEBAHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?FieldDefine@RecycleTimeProperty@@MEBAPEBUDef@Field@@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SyncMax@RecycleTimeProperty@@MEBAHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SyncDefine@RecycleTimeProperty@@MEBAPEBUDef@SyncBuffer@@XZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x19f30
__cdecl RecycleTimeProperty::~RecycleTimeProperty(void)
{
    LIFT_STUB(0x19f30);
}

// 0x19f40
wchar_t const * __cdecl RecycleTimeProperty::Name(void) const
{
    return L"RecycleTimeProperty";
}

// 0x19f50
int __cdecl RecycleTimeProperty::FieldMax(void) const
{
    return fieldMax;
}

// 0x19f60
::Field::Def const * __cdecl RecycleTimeProperty::FieldDefine(void) const
{
    return fieldDefine;
}

// 0x19f70
int __cdecl RecycleTimeProperty::SyncMax(void) const
{
    return syncMax;
}

// 0x19f80
::SyncBuffer::Def const * __cdecl RecycleTimeProperty::SyncDefine(void) const
{
    return syncDefine;
}

// LIFT: definitions of the PDB static data members (card lift-gamedaemon-e4).
int RecycleTimeProperty::fieldMax;
::Field::Def const * RecycleTimeProperty::fieldDefine;
int RecycleTimeProperty::syncMax;
::SyncBuffer::Def const * RecycleTimeProperty::syncDefine;
