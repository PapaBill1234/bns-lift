// gamelocale.cpp: gamelocale.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "gamelocale.h"
#include "LiftStub.h"

// 0xd4aa0
bool __cdecl GameLocale::IsAllowedChar(wchar_t, bool, wchar_t const *)
{
    LIFT_STUB(0xd4aa0);
}

// 0xd4d10
int __cdecl GameLocale::GetLanguageTypeOfChar(wchar_t)
{
    LIFT_STUB(0xd4d10);
}

// 0xd4ea0
bool __cdecl GameLocale::IsMonolingualString(wchar_t const *, int, ::GameLocaleSet const &)
{
    LIFT_STUB(0xd4ea0);
}

// 0xd4fb0
bool __cdecl GameLocale::IsSentenceCase(wchar_t const *, int)
{
    LIFT_STUB(0xd4fb0);
}

// 0xd50d0
bool __cdecl GameLocale::IsWupperNotApplied(wchar_t)
{
    LIFT_STUB(0xd50d0);
}

// 0xd5110
int __cdecl GameLocale::GetNextThaiCell(wchar_t const *, int, ::GameLocale::ThaiCell *)
{
    LIFT_STUB(0xd5110);
}

// 0xd5250
::GameLocale::VietVowelType __cdecl GameLocale::GetVietVowelType(wchar_t)
{
    LIFT_STUB(0xd5250);
}

// 0xd5450
::GameLocale::VietToneMarkType __cdecl GameLocale::GetVietToneMarkType(wchar_t)
{
    LIFT_STUB(0xd5450);
}

// 0xd5490
int __cdecl GameLocale::GetStringLengthWithCellCombination(wchar_t const *, int)
{
    LIFT_STUB(0xd5490);
}

// 0xd55c0
bool __cdecl IsVietnamese(wchar_t)
{
    LIFT_STUB(0xd55c0);
}
