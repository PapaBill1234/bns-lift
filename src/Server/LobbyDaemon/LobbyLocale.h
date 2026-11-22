// LobbyLocale.obj (LobbyDaemon PDB, 2019 + PDB).
#pragma once

struct LobbyLocaleSet;

class LobbyLocale
{
public:
    enum LanguageType
    {
        LANGUAGE_default = 0, LANGUAGE_korean, LANGUAGE_english, LANGUAGE_japanese,
        LANGUAGE_chineses, LANGUAGE_chineset, LANGUAGE_russian, LANGUAGE_french,
        LANGUAGE_german, LANGUAGE_thai, LANGUAGE_vietnamese, LANGUAGE_bportuguese,
        LANGUAGE_MAX
    };

    struct ThaiCell
    {
        wchar_t base;
        wchar_t hilo;
        wchar_t top;

        ThaiCell() { Reset(); }
        ~ThaiCell() {}
        void Reset() { base = 0; hilo = 0; top = 0; }
    };

    struct VietCell
    {
        wchar_t base;
        wchar_t top;

        VietCell() { Reset(); }
        ~VietCell() {}
        void Reset() { base = 0; top = 0; }
    };

    enum ThaiCharType
    {
        TYPE_NONE, TYPE_DIGIT, TYPE_PUNCT, TYPE_CONS, TYPE_LV,
        TYPE_FV1, TYPE_FV2, TYPE_FV3, TYPE_FV4, TYPE_BV1, TYPE_BV2, TYPE_BD,
        TYPE_AV1, TYPE_AV2, TYPE_AV3, TYPE_AD1, TYPE_AD2, TYPE_AD3, TYPE_TONE,
        TYPE_COUNT
    };

    enum ThaiCharOp { CP, AC, RJ };

    enum VietVowelType
    {
        VIETVOWEL_TYPE_NONE,
        VIETVOWEL_TYPE_CAPITAL_LETTER_A,
        VIETVOWEL_TYPE_CAPITAL_LETTER_A_CIRCUMFLEX,
        VIETVOWEL_TYPE_CAPITAL_LETTER_A_BREVE,
        VIETVOWEL_TYPE_CAPITAL_LETTER_E,
        VIETVOWEL_TYPE_CAPITAL_LETTER_E_CIRCUMFLEX,
        VIETVOWEL_TYPE_CAPITAL_LETTER_I,
        VIETVOWEL_TYPE_CAPITAL_LETTER_O,
        VIETVOWEL_TYPE_CAPITAL_LETTER_O_CIRCUMFLEX,
        VIETVOWEL_TYPE_CAPITAL_LETTER_O_HORN,
        VIETVOWEL_TYPE_CAPITAL_LETTER_U,
        VIETVOWEL_TYPE_CAPITAL_LETTER_U_HORN,
        VIETVOWEL_TYPE_CAPITAL_LETTER_Y,
        VIETVOWEL_TYPE_SMALL_LETTER_A,
        VIETVOWEL_TYPE_SMALL_LETTER_A_CIRCUMFLEX,
        VIETVOWEL_TYPE_SMALL_LETTER_A_BREVE,
        VIETVOWEL_TYPE_SMALL_LETTER_E,
        VIETVOWEL_TYPE_SMALL_LETTER_E_CIRCUMFLEX,
        VIETVOWEL_TYPE_SMALL_LETTER_I,
        VIETVOWEL_TYPE_SMALL_LETTER_O,
        VIETVOWEL_TYPE_SMALL_LETTER_O_CIRCUMFLEX,
        VIETVOWEL_TYPE_SMALL_LETTER_O_HORN,
        VIETVOWEL_TYPE_SMALL_LETTER_U,
        VIETVOWEL_TYPE_SMALL_LETTER_U_HORN,
        VIETVOWEL_TYPE_SMALL_LETTER_Y,
        VIETVOWEL_TYPE_COUNT
    };

    enum VietToneMarkType
    {
        VIETTONEMARK_TYPE_NONE,
        VIETTONEMARK_TYPE_GRAVEACCENT,
        VIETTONEMARK_TYPE_ACUTEACCENT,
        VIETTONEMARK_TYPE_HOOKABOVE,
        VIETTONEMARK_TYPE_TILDE,
        VIETTONEMARK_TYPE_DOTBELOW,
        VIETTONEMARK_TYPE_COUNT
    };

    bool IsAllowedChar(wchar_t, bool, wchar_t const*);  // 0x57ab0
    static int GetLanguageTypeOfChar(wchar_t);  // 0x57d20
    static bool IsMonolingualString(wchar_t const*, int, LobbyLocaleSet const&);  // 0x57eb0
    static bool IsSentenceCase(wchar_t const*, int);  // 0x57fc0
    static bool IsWupperNotApplied(wchar_t);  // 0x580e0
    static ThaiCharType GetThaiCharType(wchar_t);  // LIFT: Inlined at 0x58120.
    static int GetNextThaiCell(wchar_t const*, int, ThaiCell*);  // 0x58120
    static VietVowelType GetVietVowelType(wchar_t);  // 0x58260
    static VietToneMarkType GetVietToneMarkType(wchar_t);  // 0x58460
    static int GetNextVietCell(wchar_t const*, int, VietCell*);  // LIFT: Inlined at 0x58562.
    static int GetStringLengthWithCellCombination(wchar_t const*, int);  // 0x584a0

private:
    LobbyLocale();
    LobbyLocale(int);
    int _language;
};

struct LobbyLocaleSet
{
    LobbyLocale** locales;
    int count;
    bool languages[LobbyLocale::LANGUAGE_MAX];
};

static_assert(sizeof(LobbyLocale) == 4, "sizeof LobbyLocale");
static_assert(sizeof(LobbyLocale::ThaiCell) == 6, "sizeof LobbyLocale::ThaiCell");
static_assert(sizeof(LobbyLocale::VietCell) == 4, "sizeof LobbyLocale::VietCell");
static_assert(sizeof(LobbyLocaleSet) == 24, "sizeof LobbyLocaleSet");

bool IsVietnamese(wchar_t);  // 0x585d0
