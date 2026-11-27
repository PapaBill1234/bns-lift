// gamelocale.h: gamelocale.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class GameLocale
{
public:
    struct ThaiCell {};
    enum VietToneMarkType {};
    enum VietVowelType {};
public:
    bool __cdecl IsAllowedChar(wchar_t, bool, wchar_t const *);  // 0xd4aa0
    static int __cdecl GetLanguageTypeOfChar(wchar_t);  // 0xd4d10
    static bool __cdecl IsMonolingualString(wchar_t const *, int, ::GameLocaleSet const &);  // 0xd4ea0
    static bool __cdecl IsSentenceCase(wchar_t const *, int);  // 0xd4fb0
    static bool __cdecl IsWupperNotApplied(wchar_t);  // 0xd50d0
    static int __cdecl GetNextThaiCell(wchar_t const *, int, ::GameLocale::ThaiCell *);  // 0xd5110
    static ::GameLocale::VietVowelType __cdecl GetVietVowelType(wchar_t);  // 0xd5250
    static ::GameLocale::VietToneMarkType __cdecl GetVietToneMarkType(wchar_t);  // 0xd5450
    static int __cdecl GetStringLengthWithCellCombination(wchar_t const *, int);  // 0xd5490
};

bool __cdecl IsVietnamese(wchar_t);  // 0xd55c0
