// LobbyLocale.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "LobbyLocale.h"
#include "LiftStub.h"

// 0x57ab0
bool LobbyLocale::IsAllowedChar(wchar_t, bool, wchar_t const*)
{
    LIFT_STUB(0x57ab0);
}

// 0x57d20
int LobbyLocale::GetLanguageTypeOfChar(wchar_t)
{
    LIFT_STUB(0x57d20);
}

// 0x57eb0
bool LobbyLocale::IsMonolingualString(wchar_t const*, int, LobbyLocaleSet const&)
{
    LIFT_STUB(0x57eb0);
}

// 0x57fc0
bool LobbyLocale::IsSentenceCase(wchar_t const*, int)
{
    LIFT_STUB(0x57fc0);
}

// 0x580e0
bool LobbyLocale::IsWupperNotApplied(wchar_t)
{
    LIFT_STUB(0x580e0);
}

// 0x584a0
int LobbyLocale::GetStringLengthWithCellCombination(wchar_t const*, int)
{
    LIFT_STUB(0x584a0);
}

// 0x585d0
bool IsVietnamese(wchar_t)
{
    LIFT_STUB(0x585d0);
}
