// skillskinproperty.cpp: skillskinproperty.h (GameDaemon PDB, 2019 + PDB).
#include "skillskinproperty.h"
#include "propertysync.h"
#include "LiftStub.h"

// LIFT: keep the lifted virtual functions until the callers are lifted. Card lift-gamedaemon-gap-013-e13.
#pragma comment(linker, "/INCLUDE:?TypeId@SkillSkinProperty@@UEBA?BHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Name@SkillSkinProperty@@UEBAPEB_WXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?FieldMax@SkillSkinProperty@@MEBAHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?FieldDefine@SkillSkinProperty@@MEBAPEBUDef@Field@@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SyncMax@SkillSkinProperty@@MEBAHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SyncDefine@SkillSkinProperty@@MEBAPEBUDef@SyncBuffer@@XZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x1a180
__cdecl SkillSkinProperty::~SkillSkinProperty(void)
{
    LIFT_STUB(0x1a180);
}

// 0x1a190
int const __cdecl SkillSkinProperty::TypeId(void) const
{
    return 34;
}

// 0x1a1a0
wchar_t const * __cdecl SkillSkinProperty::Name(void) const
{
    return L"SkillSkinProperty";
}

// 0x1a1b0
int __cdecl SkillSkinProperty::FieldMax(void) const
{
    return fieldMax;
}

// 0x1a1c0
::Field::Def const * __cdecl SkillSkinProperty::FieldDefine(void) const
{
    return fieldDefine;
}

// 0x1a1d0
int __cdecl SkillSkinProperty::SyncMax(void) const
{
    return syncMax;
}

// 0x1a1e0
::SyncBuffer::Def const * __cdecl SkillSkinProperty::SyncDefine(void) const
{
    return syncDefine;
}

// LIFT: definitions of the PDB static data members.
int SkillSkinProperty::fieldMax;
::Field::Def const * SkillSkinProperty::fieldDefine;
int SkillSkinProperty::syncMax;
::SyncBuffer::Def const * SkillSkinProperty::syncDefine;
