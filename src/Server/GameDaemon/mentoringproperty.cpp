// mentoringproperty.cpp: mentoringproperty.h (GameDaemon PDB, 2019 + PDB).
#include "mentoringproperty.h"
#include "propertysync.h"
#include "LiftStub.h"

// 0x19bd0
__cdecl MentoringProperty::~MentoringProperty(void)
{
    LIFT_STUB(0x19bd0);
}

// 0x19be0
wchar_t const * __cdecl MentoringProperty::Name(void) const
{
    return L"MentoringProperty";
}

// 0x19bf0
int __cdecl MentoringProperty::FieldMax(void) const
{
    return fieldMax;
}

// 0x19c00
::Field::Def const * __cdecl MentoringProperty::FieldDefine(void) const
{
    return fieldDefine;
}

// 0x19c10
int __cdecl MentoringProperty::SyncMax(void) const
{
    return syncMax;
}

// 0x19c20
::SyncBuffer::Def const * __cdecl MentoringProperty::SyncDefine(void) const
{
    return syncDefine;
}

// 0x66ee00 ItemBase<AccessoryTrait>::GetFieldCount: LIFT: no body in wave 0 (member of a class template). Not done.

// LIFT: definitions of the PDB static data members (set at start-up by Property::initInstance, a later wave).
int MentoringProperty::fieldMax;
::Field::Def const * MentoringProperty::fieldDefine;
int MentoringProperty::syncMax;
::SyncBuffer::Def const * MentoringProperty::syncDefine;
