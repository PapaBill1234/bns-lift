// questproperty.cpp: questproperty.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "questproperty.h"
#include "propertysync.h"
#include "LiftStub.h"

// LIFT: keep the lifted virtual functions until the callers are lifted (the vftable and the callers are stubs;
// /OPT:REF drops them). Card lift-gamedaemon-e4.
#pragma comment(linker, "/INCLUDE:?Name@QuestProperty@@UEBAPEB_WXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?FieldMax@QuestProperty@@MEBAHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?FieldDefine@QuestProperty@@MEBAPEBUDef@Field@@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SyncMax@QuestProperty@@MEBAHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SyncDefine@QuestProperty@@MEBAPEBUDef@SyncBuffer@@XZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x19cf0
__cdecl QuestProperty::~QuestProperty(void)
{
    LIFT_STUB(0x19cf0);
}

// 0x19d00
wchar_t const * __cdecl QuestProperty::Name(void) const
{
    return L"QuestProperty";
}

// 0x19d10
int __cdecl QuestProperty::FieldMax(void) const
{
    return fieldMax;
}

// 0x19d20
::Field::Def const * __cdecl QuestProperty::FieldDefine(void) const
{
    return fieldDefine;
}

// 0x19d30
int __cdecl QuestProperty::SyncMax(void) const
{
    return syncMax;
}

// 0x19d40
::SyncBuffer::Def const * __cdecl QuestProperty::SyncDefine(void) const
{
    return syncDefine;
}

// LIFT: definitions of the PDB static data members (card lift-gamedaemon-e4).
int QuestProperty::fieldMax;
::Field::Def const * QuestProperty::fieldDefine;
int QuestProperty::syncMax;
::SyncBuffer::Def const * QuestProperty::syncDefine;
