// questlist.cpp: questlist.h (GameDaemon PDB, 2019 + PDB).
#include "questlist.h"
#include "propertysync.h"
#include "LiftStub.h"

// 0x19c60
__cdecl QuestList::~QuestList(void)
{
    LIFT_STUB(0x19c60);
}

// 0x19c70
wchar_t const * __cdecl QuestList::Name(void) const
{
    return L"QuestList";
}

// 0x19c80
int __cdecl QuestList::FieldMax(void) const
{
    return fieldMax;
}

// 0x19c90
::Field::Def const * __cdecl QuestList::FieldDefine(void) const
{
    return fieldDefine;
}

// 0x19ca0
int __cdecl QuestList::SyncMax(void) const
{
    return syncMax;
}

// 0x19cb0
::SyncBuffer::Def const * __cdecl QuestList::SyncDefine(void) const
{
    return syncDefine;
}

// LIFT: definitions of the PDB static data members (set at start-up by Property::initInstance, a later wave).
int QuestList::fieldMax;
::Field::Def const * QuestList::fieldDefine;
int QuestList::syncMax;
::SyncBuffer::Def const * QuestList::syncDefine;
