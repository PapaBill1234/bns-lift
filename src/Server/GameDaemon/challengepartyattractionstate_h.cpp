// challengepartyattractionstate_h.cpp: challengepartyattractionstate.h (GameDaemon PDB, 2019 + PDB).
#include "challengepartyattractionstate.h"
#include "LiftStub.h"

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
