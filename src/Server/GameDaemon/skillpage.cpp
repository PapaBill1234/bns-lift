// skillpage.cpp: skillpage.h (GameDaemon PDB, 2019 + PDB).
#include "skillpage.h"
#include "propertysync.h"
#include "LiftStub.h"

// LIFT: keep the lifted virtual functions until the callers are lifted. Card lift-gamedaemon-gap-013-e13.
#pragma comment(linker, "/INCLUDE:?TypeId@SkillPage@@UEBA?BHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Name@SkillPage@@UEBAPEB_WXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?FieldMax@SkillPage@@MEBAHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?FieldDefine@SkillPage@@MEBAPEBUDef@Field@@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SyncMax@SkillPage@@MEBAHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SyncDefine@SkillPage@@MEBAPEBUDef@SyncBuffer@@XZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x1a0e0
__cdecl SkillPage::~SkillPage(void)
{
    LIFT_STUB(0x1a0e0);
}

// 0x1a0f0
int const __cdecl SkillPage::TypeId(void) const
{
    return 26;
}

// 0x1a100
wchar_t const * __cdecl SkillPage::Name(void) const
{
    return L"SkillPage";
}

// 0x1a110
int __cdecl SkillPage::FieldMax(void) const
{
    return fieldMax;
}

// 0x1a120
::Field::Def const * __cdecl SkillPage::FieldDefine(void) const
{
    return fieldDefine;
}

// 0x1a130
int __cdecl SkillPage::SyncMax(void) const
{
    return syncMax;
}

// 0x1a140
::SyncBuffer::Def const * __cdecl SkillPage::SyncDefine(void) const
{
    return syncDefine;
}

// LIFT: definitions of the PDB static data members.
int SkillPage::fieldMax;
::Field::Def const * SkillPage::fieldDefine;
int SkillPage::syncMax;
::SyncBuffer::Def const * SkillPage::syncDefine;
