// gamelocale.cpp: gamelocale.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "gamelocale.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?IsWupperNotApplied@GameLocale@@SA_N_W@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetVietToneMarkType@GameLocale@@SA?AW4VietToneMarkType@1@_W@Z")  // LIFT: dead-strip keep (no live caller yet)

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
bool __cdecl GameLocale::IsWupperNotApplied(wchar_t c)
{
    return static_cast<unsigned short>(c + 21504) <= 0x2BAFu
        || static_cast<unsigned short>(c - 3585) <= 0x39u
        || static_cast<unsigned short>(c - 3647) <= 0x1Cu;
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
::GameLocale::VietToneMarkType __cdecl GameLocale::GetVietToneMarkType(wchar_t ch)
{
    switch (ch)
    {
    case 0x300:
        return VIETTONEMARK_TYPE_GRAVEACCENT;
    case 0x301:
        return VIETTONEMARK_TYPE_ACUTEACCENT;
    case 0x303:
        return VIETTONEMARK_TYPE_TILDE;
    case 0x309:
        return VIETTONEMARK_TYPE_HOOKABOVE;
    case 0x323:
        return VIETTONEMARK_TYPE_DOTBELOW;
    default:
        return VIETTONEMARK_TYPE_NONE;
    }
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
