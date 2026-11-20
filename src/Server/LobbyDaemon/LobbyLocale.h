// LobbyLocale.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

struct LobbyLocaleSet;

class LobbyLocale
{
public:
    bool IsAllowedChar(wchar_t, bool, wchar_t const*);  // 0x57ab0
    static int GetLanguageTypeOfChar(wchar_t);  // 0x57d20
    static bool IsMonolingualString(wchar_t const*, int, LobbyLocaleSet const&);  // 0x57eb0
    static bool IsSentenceCase(wchar_t const*, int);  // 0x57fc0
    static bool IsWupperNotApplied(wchar_t);  // 0x580e0
    static int GetStringLengthWithCellCombination(wchar_t const*, int);  // 0x584a0
};

bool IsVietnamese(wchar_t);  // 0x585d0
