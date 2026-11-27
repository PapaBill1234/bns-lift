// publicraid_h.cpp: publicraid.h (GameDaemon PDB, 2019 + PDB).
#include "publicraid.h"
#include "attractionstate.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:??1AttractionState@@UEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetTypeName@PublicRaid@@UEAAPEB_WXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetMaxPcCount@PublicRaid@@UEAAHXZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x35e90
__cdecl AttractionState::~AttractionState(void)
{
}

// 0x180e50
wchar_t const * __cdecl PublicRaid::GetTypeName(void)
{
    return L"PublicRaid";
}

// 0x180e60
int __cdecl PublicRaid::GetMaxPcCount(void)
{
    if (_data._record == nullptr)
        return 0;
    return _data._record->max_pc_count;
}
