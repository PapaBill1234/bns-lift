// fishingproperty.cpp: fishingproperty.h (GameDaemon PDB, 2019 + PDB).
#include "fishingproperty.h"
#include "propertysync.h"
#include "LiftStub.h"

// 0x19a30
int const __cdecl FishingProperty::TypeId(void) const
{
    return 37;
}

// 0x19a40
wchar_t const * __cdecl FishingProperty::Name(void) const
{
    return L"FishingProperty";
}

// 0x19a50
int __cdecl FishingProperty::FieldMax(void) const
{
    return fieldMax;
}

// 0x19a60
::Field::Def const * __cdecl FishingProperty::FieldDefine(void) const
{
    return fieldDefine;
}

// 0x19a70
int __cdecl FishingProperty::SyncMax(void) const
{
    return syncMax;
}

// 0x19a80
::SyncBuffer::Def const * __cdecl FishingProperty::SyncDefine(void) const
{
    return syncDefine;
}

// LIFT: definitions of the PDB static data members (set at start-up by Property::initInstance, a later wave).
int FishingProperty::fieldMax;
::Field::Def const * FishingProperty::fieldDefine;
int FishingProperty::syncMax;
::SyncBuffer::Def const * FishingProperty::syncDefine;
