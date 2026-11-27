// campfire.cpp: campfire.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "campfire.h"
#include "zone.h"
#include "LiftStub.h"

// 0x63fe0
bool __cdecl CampfireIdManager::IsExist(unsigned __int64)
{
    LIFT_STUB(0x63fe0);
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
long __cdecl Campfire::GetRemainDuration(void) const
{
    LIFT_STUB(0x64350);
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
