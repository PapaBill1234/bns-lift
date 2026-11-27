// extracreatureproperty_h.cpp: extracreatureproperty.h (GameDaemon PDB, 2019 + PDB).
#include "extracreatureproperty.h"
#include "propertysync.h"
#include "LiftStub.h"

// 0x19940
__cdecl ExtraCreatureProperty::~ExtraCreatureProperty(void)
{
    LIFT_STUB(0x19940);
}

// 0x19950
int const __cdecl ExtraCreatureProperty::TypeId(void) const
{
    return 17;
}

// 0x19960
wchar_t const * __cdecl ExtraCreatureProperty::Name(void) const
{
    return L"ExtraCreatureProperty";
}

// 0x19970
int __cdecl ExtraCreatureProperty::FieldMax(void) const
{
    return fieldMax;
}

// 0x19980
::Field::Def const * __cdecl ExtraCreatureProperty::FieldDefine(void) const
{
    return fieldDefine;
}

// 0x19990
int __cdecl ExtraCreatureProperty::SyncMax(void) const
{
    return syncMax;
}

// 0x199a0
::SyncBuffer::Def const * __cdecl ExtraCreatureProperty::SyncDefine(void) const
{
    return syncDefine;
}

// LIFT: definitions of the PDB static data members (set at start-up by Property::initInstance, a later wave).
int ExtraCreatureProperty::fieldMax;
::Field::Def const * ExtraCreatureProperty::fieldDefine;
int ExtraCreatureProperty::syncMax;
::SyncBuffer::Def const * ExtraCreatureProperty::syncDefine;
