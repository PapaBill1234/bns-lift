// discoveryarea.cpp: discoveryarea.h (GameDaemon PDB, 2019 + PDB).
#include "discoveryarea.h"
#include "propertysync.h"
#include "LiftStub.h"

// LIFT: keep the lifted virtual functions until the callers are lifted. Card lift-gamedaemon-gap-002-e2.
#pragma comment(linker, "/INCLUDE:?TypeId@DiscoveryArea@@UEBA?BHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Name@DiscoveryArea@@UEBAPEB_WXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?FieldMax@DiscoveryArea@@MEBAHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?FieldDefine@DiscoveryArea@@MEBAPEBUDef@Field@@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SyncMax@DiscoveryArea@@MEBAHXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SyncDefine@DiscoveryArea@@MEBAPEBUDef@SyncBuffer@@XZ")  // LIFT: dead-strip keep (no live caller yet)


// 0x19740
__cdecl DiscoveryArea::~DiscoveryArea(void)
{
    LIFT_STUB(0x19740);
}

// 0x19750
int const __cdecl DiscoveryArea::TypeId(void) const
{
    return 12;
}

// 0x19760
wchar_t const * __cdecl DiscoveryArea::Name(void) const
{
    return L"DiscoveryArea";
}

// 0x19770
int __cdecl DiscoveryArea::FieldMax(void) const
{
    return fieldMax;
}

// 0x19780
::Field::Def const * __cdecl DiscoveryArea::FieldDefine(void) const
{
    return fieldDefine;
}

// 0x19790
int __cdecl DiscoveryArea::SyncMax(void) const
{
    return syncMax;
}

// 0x197a0
::SyncBuffer::Def const * __cdecl DiscoveryArea::SyncDefine(void) const
{
    return syncDefine;
}

// LIFT: definitions of the PDB static data members.
int DiscoveryArea::fieldMax;
::Field::Def const * DiscoveryArea::fieldDefine;
int DiscoveryArea::syncMax;
::SyncBuffer::Def const * DiscoveryArea::syncDefine;
