// seasoncontentscombatrecord.cpp: seasoncontentscombatrecord.h (GameDaemon PDB, 2019 + PDB).
#include "seasoncontentscombatrecord.h"
#include "propertysync.h"
#include "LiftStub.h"

// LIFT: keep the lifted virtual functions until the callers are lifted. Card lift-gamedaemon-e4.
#pragma comment(linker, "/INCLUDE:?TypeId@SeasonContentsCombatRecord@@UEBA?BHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Name@SeasonContentsCombatRecord@@UEBAPEB_WXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?FieldMax@SeasonContentsCombatRecord@@MEBAHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?FieldDefine@SeasonContentsCombatRecord@@MEBAPEBUDef@Field@@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SyncMax@SeasonContentsCombatRecord@@MEBAHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SyncDefine@SeasonContentsCombatRecord@@MEBAPEBUDef@SyncBuffer@@XZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x19fc0
int const __cdecl SeasonContentsCombatRecord::TypeId(void) const
{
    return 32;
}

// 0x19fd0
wchar_t const * __cdecl SeasonContentsCombatRecord::Name(void) const
{
    return L"SeasonContentsCombatRecord";
}

// 0x19fe0
int __cdecl SeasonContentsCombatRecord::FieldMax(void) const
{
    return fieldMax;
}

// 0x19ff0
::Field::Def const * __cdecl SeasonContentsCombatRecord::FieldDefine(void) const
{
    return fieldDefine;
}

// 0x1a000
int __cdecl SeasonContentsCombatRecord::SyncMax(void) const
{
    return syncMax;
}

// 0x1a010
::SyncBuffer::Def const * __cdecl SeasonContentsCombatRecord::SyncDefine(void) const
{
    return syncDefine;
}

// LIFT: definitions of the PDB static data members (card lift-gamedaemon-e4).
int SeasonContentsCombatRecord::fieldMax;
::Field::Def const * SeasonContentsCombatRecord::fieldDefine;
int SeasonContentsCombatRecord::syncMax;
::SyncBuffer::Def const * SeasonContentsCombatRecord::syncDefine;
