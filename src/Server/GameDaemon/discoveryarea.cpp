// discoveryarea.cpp: discoveryarea.h (GameDaemon PDB, 2019 + PDB).
#include "discoveryarea.h"
#include "propertysync.h"
#include "LiftStub.h"


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
