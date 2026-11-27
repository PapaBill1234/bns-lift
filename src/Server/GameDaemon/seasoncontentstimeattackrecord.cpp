// seasoncontentstimeattackrecord.cpp: seasoncontentstimeattackrecord.h (GameDaemon PDB, 2019 + PDB).
#include "seasoncontentstimeattackrecord.h"
#include "propertysync.h"
#include "LiftStub.h"

// LIFT: keep the lifted virtual functions until the callers are lifted. Card lift-gamedaemon-e4.
#pragma comment(linker, "/INCLUDE:?Name@SeasonContentsTimeAttackRecord@@UEBAPEB_WXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?FieldMax@SeasonContentsTimeAttackRecord@@MEBAHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?FieldDefine@SeasonContentsTimeAttackRecord@@MEBAPEBUDef@Field@@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SyncMax@SeasonContentsTimeAttackRecord@@MEBAHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SyncDefine@SeasonContentsTimeAttackRecord@@MEBAPEBUDef@SyncBuffer@@XZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x1a060
wchar_t const * __cdecl SeasonContentsTimeAttackRecord::Name(void) const
{
    return L"SeasonContentsTimeAttackRecord";
}

// 0x1a070
int __cdecl SeasonContentsTimeAttackRecord::FieldMax(void) const
{
    return fieldMax;
}

// 0x1a080
::Field::Def const * __cdecl SeasonContentsTimeAttackRecord::FieldDefine(void) const
{
    return fieldDefine;
}

// 0x1a090
int __cdecl SeasonContentsTimeAttackRecord::SyncMax(void) const
{
    return syncMax;
}

// 0x1a0a0
::SyncBuffer::Def const * __cdecl SeasonContentsTimeAttackRecord::SyncDefine(void) const
{
    return syncDefine;
}

// LIFT: definitions of the PDB static data members (card lift-gamedaemon-e4).
int SeasonContentsTimeAttackRecord::fieldMax;
::Field::Def const * SeasonContentsTimeAttackRecord::fieldDefine;
int SeasonContentsTimeAttackRecord::syncMax;
::SyncBuffer::Def const * SeasonContentsTimeAttackRecord::syncDefine;
