// skillpage.cpp: skillpage.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "skillpage.h"
#include "propertysync.h"
#include "LiftStub.h"

// 0x1a0e0
__cdecl SkillPage::~SkillPage(void)
{
    LIFT_STUB(0x1a0e0);
}

// 0x1a0f0
int const __cdecl SkillPage::TypeId(void) const
{
    LIFT_STUB(0x1a0f0);
}

// 0x1a100
wchar_t const * __cdecl SkillPage::Name(void) const
{
    LIFT_STUB(0x1a100);
}

// 0x1a110
int __cdecl SkillPage::FieldMax(void) const
{
    LIFT_STUB(0x1a110);
}

// 0x1a120
::Field::Def const * __cdecl SkillPage::FieldDefine(void) const
{
    LIFT_STUB(0x1a120);
}

// 0x1a130
int __cdecl SkillPage::SyncMax(void) const
{
    LIFT_STUB(0x1a130);
}

// 0x1a140
::SyncBuffer::Def const * __cdecl SkillPage::SyncDefine(void) const
{
    LIFT_STUB(0x1a140);
}
