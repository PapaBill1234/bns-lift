// attractionstate_h.cpp: attractionstate.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "attractionstate.h"
#include "LiftStub.h"

// 0x35ea0
bool __cdecl AttractionState::CanChangeChannel(short, short &)
{
    LIFT_STUB(0x35ea0);
}

// 0x35ec0
wchar_t const * __cdecl BossChallengeAttractionState::GetTypeName(void)
{
    LIFT_STUB(0x35ec0);
}

// 0x35ed0
wchar_t const * __cdecl TendencyFieldAttractionState::GetTypeName(void)
{
    LIFT_STUB(0x35ed0);
}

// 0x35ee0
::GameType const __cdecl TendencyFieldAttractionState::GetGameType(void) const
{
    LIFT_STUB(0x35ee0);
}

// 0x35ef0
wchar_t const * __cdecl DuelAttractionState::GetTypeName(void)
{
    LIFT_STUB(0x35ef0);
}

// 0x35f00
wchar_t const * __cdecl PartyBattleFieldAttractionState::GetTypeName(void)
{
    LIFT_STUB(0x35f00);
}
