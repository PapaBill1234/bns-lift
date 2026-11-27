// autokeytable_h.cpp: autokeytable.h (GameDaemon PDB, 2019 + PDB).
#include "autokeytable.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?IsValid@DrAutoKeyInnerIter@@EEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Ptr@DrAutoKeyInnerIter@@EEAAPEAUDrEl@@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Next@DrAutoKeyInnerIter@@EEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x6fd300
bool __cdecl DrAutoKeyInnerIter::IsValid(void)
{
    if (elCount <= 0)
        return false;
    if (index < elCount && index >= 1)
        return true;
    return false;
}

// 0x6fd450
::DrEl * __cdecl DrAutoKeyInnerIter::Ptr(void)
{
    if (IsValid())
        return (*elPtrArray)[index];
    return nullptr;
}

// 0x6fd480
bool __cdecl DrAutoKeyInnerIter::Next(void)
{
    for (++index; index < elCount; ++index)
    {
        if ((*elPtrArray)[index] != nullptr)
            break;
    }
    return IsValid();
}
