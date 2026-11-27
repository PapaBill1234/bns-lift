// contentquotaproperty.cpp: contentquotaproperty.h (GameDaemon PDB, 2019 + PDB).
#include "contentquotaproperty.h"
#include "propertysync.h"
#include "LiftStub.h"

// LIFT: keep the lifted virtual functions until the callers are lifted. Card lift-gamedaemon-gap-002-e2.
#pragma comment(linker, "/INCLUDE:?Name@ContentQuotaProperty@@UEBAPEB_WXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?FieldMax@ContentQuotaProperty@@MEBAHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?FieldDefine@ContentQuotaProperty@@MEBAPEBUDef@Field@@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SyncMax@ContentQuotaProperty@@MEBAHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SyncDefine@ContentQuotaProperty@@MEBAPEBUDef@SyncBuffer@@XZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x19620
wchar_t const * __cdecl ContentQuotaProperty::Name(void) const
{
    return L"ContentQuotaProperty";
}

// 0x19630
int __cdecl ContentQuotaProperty::FieldMax(void) const
{
    return fieldMax;
}

// 0x19640
::Field::Def const * __cdecl ContentQuotaProperty::FieldDefine(void) const
{
    return fieldDefine;
}

// 0x19650
int __cdecl ContentQuotaProperty::SyncMax(void) const
{
    return syncMax;
}

// 0x19660
::SyncBuffer::Def const * __cdecl ContentQuotaProperty::SyncDefine(void) const
{
    return syncDefine;
}

// LIFT: definitions of the PDB static data members.
int ContentQuotaProperty::fieldMax;
::Field::Def const * ContentQuotaProperty::fieldDefine;
int ContentQuotaProperty::syncMax;
::SyncBuffer::Def const * ContentQuotaProperty::syncDefine;
