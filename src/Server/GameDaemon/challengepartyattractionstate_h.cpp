// challengepartyattractionstate_h.cpp: challengepartyattractionstate.h (GameDaemon PDB, 2019 + PDB).
#include "challengepartyattractionstate.h"
#include "LiftStub.h"
#pragma comment(linker, "/INCLUDE:?GetType@ChallengePartyAttractionState@@UEAA?AW4ATTRACTION_STATE_TYPE@@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetTypeName@ChallengePartyAttractionState@@UEAAPEB_WXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SetAttractionOption@ChallengePartyAttractionState@@UEAAXD@Z")  // LIFT: dead-strip keep (no live caller yet)

// 0x35f20 (shared body with AirDashAction::getPriority)
::ATTRACTION_STATE_TYPE __cdecl ChallengePartyAttractionState::GetType(void)
{
    return (::ATTRACTION_STATE_TYPE)9;
}

// 0x35f30
wchar_t const * __cdecl ChallengePartyAttractionState::GetTypeName(void)
{
    return L"ChallengeParty";
}

// 0x35f40
void __cdecl ChallengePartyAttractionState::SetAttractionOption(char use)
{
    _attractionOption = use;
}
