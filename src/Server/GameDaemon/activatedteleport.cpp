// activatedteleport.cpp: activatedteleport.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "activatedteleport.h"
#include "propertysync.h"
#include "LiftStub.h"

// LIFT: keep the lifted virtual functions until the callers are lifted (the vftable and the callers are stubs;
// /OPT:REF drops them). Card lift-gamedaemon-0d.
#pragma comment(linker, "/INCLUDE:?TypeId@ActivatedTeleport@@UEBA?BHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Name@ActivatedTeleport@@UEBAPEB_WXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?FieldMax@ActivatedTeleport@@MEBAHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?FieldDefine@ActivatedTeleport@@MEBAPEBUDef@Field@@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SyncMax@ActivatedTeleport@@MEBAHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SyncDefine@ActivatedTeleport@@MEBAPEBUDef@SyncBuffer@@XZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x193e0
__cdecl ActivatedTeleport::~ActivatedTeleport(void)
{
    LIFT_STUB(0x193e0);
}

// 0x193f0
int const __cdecl ActivatedTeleport::TypeId(void) const
{
    return 13;
}

// 0x19400
wchar_t const * __cdecl ActivatedTeleport::Name(void) const
{
    return L"ActivatedTeleport";
}

// 0x19410
int __cdecl ActivatedTeleport::FieldMax(void) const
{
    return fieldMax;
}

// 0x19420
::Field::Def const * __cdecl ActivatedTeleport::FieldDefine(void) const
{
    return fieldDefine;
}

// 0x19430
int __cdecl ActivatedTeleport::SyncMax(void) const
{
    return syncMax;
}

// 0x19440
::SyncBuffer::Def const * __cdecl ActivatedTeleport::SyncDefine(void) const
{
    return syncDefine;
}

// LIFT: definitions of the PDB static data members (see the PDB data records of the class). Pilot of card lift-gamedaemon-0d.
int ActivatedTeleport::fieldMax;
::Field::Def const * ActivatedTeleport::fieldDefine;
int ActivatedTeleport::syncMax;
::SyncBuffer::Def const * ActivatedTeleport::syncDefine;
