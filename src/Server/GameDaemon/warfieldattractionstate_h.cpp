// warfieldattractionstate_h.cpp: warfieldattractionstate.h (GameDaemon PDB, 2019 + PDB).
#include "warfieldattractionstate.h"
#include "questtableimpl.h"
#include "LiftStub.h"
#pragma comment(linker, "/INCLUDE:?GetTypeName@WarFieldAttractionState@@UEAAPEB_WXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetTableType@QuestTableImpl@@UEAA?AW4TableType@@XZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x1ee750
wchar_t const * __cdecl WarFieldAttractionState::GetTypeName(void)
{
    return L"WarField";
}

// 0x6f86d0 (shared body with AcquiredSkill1::Version)
::TableType __cdecl QuestTableImpl::GetTableType(void)
{
    return (::TableType)11;
}
