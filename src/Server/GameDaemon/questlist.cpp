// questlist.cpp: questlist.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
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
    LIFT_STUB(0x19c70);
}

// 0x19c80
int __cdecl QuestList::FieldMax(void) const
{
    LIFT_STUB(0x19c80);
}

// 0x19c90
::Field::Def const * __cdecl QuestList::FieldDefine(void) const
{
    LIFT_STUB(0x19c90);
}

// 0x19ca0
int __cdecl QuestList::SyncMax(void) const
{
    LIFT_STUB(0x19ca0);
}

// 0x19cb0
::SyncBuffer::Def const * __cdecl QuestList::SyncDefine(void) const
{
    LIFT_STUB(0x19cb0);
}
