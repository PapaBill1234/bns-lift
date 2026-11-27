// challengelistproperty.cpp: challengelistproperty.h (GameDaemon PDB, 2019 + PDB).
#include "challengelistproperty.h"
#include "propertysync.h"
#include "LiftStub.h"

// LIFT: keep the lifted virtual functions until the callers are lifted (the vftable and the callers are stubs;
// /OPT:REF drops them). Card lift-gamedaemon-gap-005-e5.
#pragma comment(linker, "/INCLUDE:?TypeId@ChallengeListProperty@@UEBA?BHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?FieldMax@ChallengeListProperty@@MEBAHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?FieldDefine@ChallengeListProperty@@MEBAPEBUDef@Field@@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SyncMax@ChallengeListProperty@@MEBAHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SyncDefine@ChallengeListProperty@@MEBAPEBUDef@SyncBuffer@@XZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x96c0
int const __cdecl ChallengeListProperty::TypeId(void) const
{
    return 38;
}

// 0x96d0
wchar_t const * __cdecl ChallengeListProperty::Name(void) const
{
    LIFT_STUB(0x96d0);
}

// 0x96e0
int __cdecl ChallengeListProperty::FieldMax(void) const
{
    return fieldMax;
}

// 0x96f0
::Field::Def const * __cdecl ChallengeListProperty::FieldDefine(void) const
{
    return fieldDefine;
}

// 0x9700
int __cdecl ChallengeListProperty::SyncMax(void) const
{
    return syncMax;
}

// 0x9710
::SyncBuffer::Def const * __cdecl ChallengeListProperty::SyncDefine(void) const
{
    return syncDefine;
}

// LIFT: definitions of the PDB static data members (see creatureproperty.h).
int ChallengeListProperty::fieldMax;
::Field::Def const * ChallengeListProperty::fieldDefine;
int ChallengeListProperty::syncMax;
::SyncBuffer::Def const * ChallengeListProperty::syncDefine;
