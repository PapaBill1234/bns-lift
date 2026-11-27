// attractionstate_h.cpp: attractionstate.h (GameDaemon PDB, 2019 + PDB).
#include "attractionstate.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?CanChangeChannel@AttractionState@@UEAA_NFAEAF@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetTypeName@BossChallengeAttractionState@@UEAAPEB_WXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetTypeName@TendencyFieldAttractionState@@UEAAPEB_WXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetGameType@TendencyFieldAttractionState@@UEBA?BW4GameType@@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetTypeName@DuelAttractionState@@UEAAPEB_WXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetTypeName@PartyBattleFieldAttractionState@@UEAAPEB_WXZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x35ea0
bool __cdecl AttractionState::CanChangeChannel(short channel, short &error)
{
    if (0 == channel)  // LIFT: form (xor eax,eax; cmp ax,dx; jne)
    {
        error = 1189;  // ❓ no PDB enum name found for the error code 1189
        return false;
    }
    return true;
}

// 0x35ec0
wchar_t const * __cdecl BossChallengeAttractionState::GetTypeName(void)
{
    return L"BossChallenge";
}

// 0x35ed0
wchar_t const * __cdecl TendencyFieldAttractionState::GetTypeName(void)
{
    return L"TendencyField";
}

// 0x35ee0
::GameType const __cdecl TendencyFieldAttractionState::GetGameType(void) const
{
    return liftTendencyFieldView(this)->_gameType;
}

// 0x35ef0
wchar_t const * __cdecl DuelAttractionState::GetTypeName(void)
{
    return L"Duel";
}

// 0x35f00
wchar_t const * __cdecl PartyBattleFieldAttractionState::GetTypeName(void)
{
    return L"PartyBattleField";
}
