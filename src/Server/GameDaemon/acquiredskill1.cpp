// acquiredskill1.cpp: acquiredskill1.h (GameDaemon PDB, 2019 + PDB).
#include "acquiredskill1.h"
#include "propertysync.h"
#include "LiftStub.h"

// LIFT: keep the lifted virtual functions until the callers are lifted (the vftable and the callers are stubs;
// /OPT:REF drops them). Card lift-gamedaemon-gap-005-e5.
#pragma comment(linker, "/INCLUDE:?TypeId@AcquiredSkill1@@UEBAHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Name@AcquiredSkill1@@UEBAPEB_WXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?FieldMax@AcquiredSkill1@@MEBAHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?FieldDefine@AcquiredSkill1@@MEBAPEBUDef@Field@@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SyncMax@AcquiredSkill1@@MEBAHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SyncDefine@AcquiredSkill1@@MEBAPEBUDef@SyncBuffer@@XZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x19270
__cdecl AcquiredSkill1::~AcquiredSkill1(void)
{
    LIFT_STUB(0x19270);
}

// 0x19280
// LIFT: the old wave 0 note said "class template member". The PDB name of this RVA is AcquiredSkill1::TypeId (return 21).
int __cdecl AcquiredSkill1::TypeId(void) const
{
    return 21;
}

// 0x19290
wchar_t const * __cdecl AcquiredSkill1::Name(void) const
{
    return L"AcquiredSkill1";
}

// 0x192a0
int __cdecl AcquiredSkill1::FieldMax(void) const
{
    return fieldMax;
}

// 0x192b0
::Field::Def const * __cdecl AcquiredSkill1::FieldDefine(void) const
{
    return fieldDefine;
}

// 0x192c0
int __cdecl AcquiredSkill1::SyncMax(void) const
{
    return syncMax;
}

// 0x192d0
::SyncBuffer::Def const * __cdecl AcquiredSkill1::SyncDefine(void) const
{
    return syncDefine;
}

// LIFT: definitions of the PDB static data members (see creatureproperty.h).
int AcquiredSkill1::fieldMax;
::Field::Def const * AcquiredSkill1::fieldDefine;
int AcquiredSkill1::syncMax;
::SyncBuffer::Def const * AcquiredSkill1::syncDefine;
