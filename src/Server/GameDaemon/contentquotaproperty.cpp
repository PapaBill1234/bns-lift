// contentquotaproperty.cpp: contentquotaproperty.h (GameDaemon PDB, 2019 + PDB).
#include "contentquotaproperty.h"
#include "propertysync.h"
#include "LiftStub.h"


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
