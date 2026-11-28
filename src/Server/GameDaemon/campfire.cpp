// campfire.cpp: campfire.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "campfire.h"
#include "zone.h"
#include "Daemon.h"
#include "LiftStub.h"

namespace
{
// LIFT: view of the PDB class CampfireIdManager (size 0x48). The skeleton class has no members yet.
struct CampfireIdManagerView
{
    char lift_pad_0[0x38];
    ::Zone const * Zone;  // +56 (0x38)
};

// LIFT: view of the PDB class Campfire (size 0x208). Only the members that the lifted bodies use are declared.
struct CampfireView
{
    char lift_pad_0[0x58];
    long _remainDuration;  // +88 (0x58)
    __int64 _updateTime;   // +96 (0x60)
};
}

// 0x63fe0
#pragma comment(linker, "/INCLUDE:?IsExist@CampfireIdManager@@MEAA_N_K@Z")  // LIFT: dead-strip keep (no live caller yet)
bool __cdecl CampfireIdManager::IsExist(unsigned __int64 id)
{
    ::Zone const *zone = reinterpret_cast<CampfireIdManagerView *>(this)->Zone;
    return reinterpret_cast<::ZoneMemberView const *>(zone)->campfireList->Get(id) != nullptr;
}

// 0x64030
__cdecl Campfire::Campfire(unsigned __int64)
{
    LIFT_STUB(0x64030);
}

// 0x64160
bool __cdecl Campfire::Initialize(unsigned int, unsigned __int64, ::vector16, ::Zone *, ::CampfireType)
{
    LIFT_STUB(0x64160);
}

// 0x64350
#pragma comment(linker, "/INCLUDE:?GetRemainDuration@Campfire@@QEBAJXZ")  // LIFT: dead-strip keep (no live caller yet)
long __cdecl Campfire::GetRemainDuration(void) const
{
    CampfireView const *self = reinterpret_cast<CampfireView const *>(this);
    __int64 now = GetTickCount64() - Daemon::Instance->StartSystemTick64;
    long remain = self->_remainDuration - static_cast<long>((now - self->_updateTime) / 100) * 100;
    if (remain < 0)
        return 0;
    return remain;
}

// 0x643b0
void __cdecl Campfire::OnTimer(::Zone *, unsigned short)
{
    LIFT_STUB(0x643b0);
}

// 0x643d0
void __cdecl Campfire::remove(void)
{
    LIFT_STUB(0x643d0);
}

// 0x64550
__cdecl CampfireList::~CampfireList(void)
{
    LIFT_STUB(0x64550);
}

// 0x646e0
bool __cdecl CampfireList::Initialize(::Zone *, int)
{
    LIFT_STUB(0x646e0);
}

// 0x647d0
::Campfire * __cdecl CampfireList::CreateCampfire(void)
{
    LIFT_STUB(0x647d0);
}

// 0x64880
bool __cdecl CampfireList::Remove(unsigned __int64)
{
    LIFT_STUB(0x64880);
}
