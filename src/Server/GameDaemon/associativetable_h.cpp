// associativetable_h.cpp: associativetable.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "associativetable.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?Ptr@DrMultiKeyInnerIter@@EEAAPEAUDrEl@@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Next@DrMultiKeyInnerIter@@EEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?IsValid@DrMultiKeyInnerIter@@EEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x6fb130
::DrEl * __cdecl DrMultiKeyInnerIter::Ptr(void)
{
    if (IsValid())
        return elArray[it].node;
    return nullptr;
}

// 0x6fb170
bool __cdecl DrMultiKeyInnerIter::Next(void)
{
    ++it;
    return IsValid();
}

// 0x6fb180
bool __cdecl DrMultiKeyInnerIter::IsValid(void)
{
    if (elCount <= 0)
        return false;
    if (it < elCount && it >= 0)
        return true;
    return false;
}

// 0x6fcd10
::DrEl *const __cdecl DrMultiKeyElMap::get(unsigned __int64) const
{
    LIFT_STUB(0x6fcd10);
}

// 0x6fd0f0
::DrEl * __cdecl DrMultiKeyElMap::set(unsigned __int64, ::DrEl *, bool)
{
    LIFT_STUB(0x6fd0f0);
}
