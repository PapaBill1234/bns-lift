// gemproperty.cpp: gemproperty.h (GameDaemon PDB, 2019 + PDB).
#include "gemproperty.h"
#include "propertysync.h"
#include "LiftStub.h"

// 0x19ac0
wchar_t const * __cdecl GemProperty::Name(void) const
{
    return L"GemProperty";
}

// 0x19ad0
int __cdecl GemProperty::FieldMax(void) const
{
    return fieldMax;
}

// 0x19ae0
::Field::Def const * __cdecl GemProperty::FieldDefine(void) const
{
    return fieldDefine;
}

// 0x19af0
int __cdecl GemProperty::SyncMax(void) const
{
    return syncMax;
}

// 0x19b00
::SyncBuffer::Def const * __cdecl GemProperty::SyncDefine(void) const
{
    return syncDefine;
}

// LIFT: definitions of the PDB static data members (set at start-up by Property::initInstance, a later wave).
int GemProperty::fieldMax;
::Field::Def const * GemProperty::fieldDefine;
int GemProperty::syncMax;
::SyncBuffer::Def const * GemProperty::syncDefine;
