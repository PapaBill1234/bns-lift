// RuleSet.obj (LobbyDaemon PDB, 2019 + PDB). Lifted from the pseudocode with PDB types.
#include <wchar.h>
#include "RuleSet.h"
#include "LobbyDaemon.h"
#include "LobbyLocale.h"
#include "Memory.h"
#include "MemoryManager.h"

namespace
{
// PDB struct JapaneseSpecialCharRule (sizeof 0xC).
struct JapaneseSpecialCharRule
{
    wchar_t ch;
    int amount;
    bool onlyInfix;
    bool iterative;
};
static_assert(sizeof(JapaneseSpecialCharRule) == 0xC, "sizeof JapaneseSpecialCharRule");

// PDB S_LDATA32 japanSpecialCharRuleList (.data 0003:2640, 3 entries). Values from the 2019 + PDB exe.
JapaneseSpecialCharRule japanSpecialCharRuleList[] = {
    {0x30FB, 2, false, false},
    {0x3005, 2, false, false},
    {0x30FC, 2, false, false},
};
int const kJapanSpecialCharRuleCount = sizeof(japanSpecialCharRuleList) / sizeof(japanSpecialCharRuleList[0]);
}

// 0x6bfc0
RuleSet::CheckNameResult RuleSet::CheckName(LobbyLocaleSet const& lcset, wchar_t const* name, int allowedMinLength,
                                            int allowedMaxLength, int allowSpaceAmount, bool enableNumeric,
                                            bool forceSentenceCase, bool enableMultilingual,
                                            wchar_t const* forbiddenCharacters)
{
    int length = static_cast<int>(wcslen(name));
    if (lcset.languages[LobbyLocale::LANGUAGE_thai] || lcset.languages[LobbyLocale::LANGUAGE_vietnamese])
    {
        int const cellLength = LobbyLocale::GetStringLengthWithCellCombination(name, length);
        if (cellLength != 0)
            length = cellLength;
    }
    if (length < allowedMinLength)
        return CHECKNAME_TOO_SHORT;
    if (length > allowedMaxLength)
        return CHECKNAME_TOO_LONG;

    CheckNameResult result = CHECKNAME_OK;
    int const nameLength = static_cast<int>(wcslen(name));
    int spaceAmount = 0;
    int continuousSpace = 0;
    int japaneseSpecialCharacterCount[3] = {0, 0, 0};
    wchar_t prev = 0;
    wchar_t* const word = static_cast<wchar_t*>(Memory::_Manager[2]->AllocZero(sizeof(wchar_t) * (nameLength + 1), L"RuleSet.cpp", 62));
    wchar_t* out = word;

    if (forceSentenceCase && !LobbyLocale::IsSentenceCase(name, nameLength))
    {
        result = CHECKNAME_SENTENCE_CASE;
        goto $_fin;
    }
    if (!enableMultilingual && !LobbyLocale::IsMonolingualString(name, nameLength, lcset))
    {
        result = CHECKNAME_MULTILINGUAL;
        goto $_fin;
    }

    for (int i = 0; i < nameLength; ++i)
    {
        wchar_t const ch = name[i];
        bool allowed = false;
        for (LobbyLocale** locale = lcset.locales; locale != lcset.locales + lcset.count; ++locale)
        {
            if (*locale != nullptr && (*locale)->IsAllowedChar(ch, enableNumeric, forbiddenCharacters))
            {
                allowed = true;
                break;
            }
        }
        if (allowed)
        {
            continuousSpace = 0;
        }
        else if (ch == L' ')
        {
            ++continuousSpace;
            if (++spaceAmount > allowSpaceAmount)
            {
                result = CHECKNAME_SPACE_OVERFLOW;
                goto $_fin;
            }
            if (i == 0 || i == nameLength - 1)
            {
                result = CHECKNAME_SIDE_SPACE;
                goto $_fin;
            }
            if (continuousSpace > 1)
            {
                result = CHECKNAME_DOUBLE_SPACE;
                goto $_fin;
            }
            prev = ch;
            continue;
        }
        else
        {
            int rule = -1;
            if (lcset.languages[LobbyLocale::LANGUAGE_japanese])
            {
                for (int k = 0; k < kJapanSpecialCharRuleCount; ++k)
                {
                    if (japanSpecialCharRuleList[k].ch == ch)
                    {
                        rule = k;
                        break;
                    }
                }
            }
            if (rule < 0)
            {
                result = CHECKNAME_NOT_ALLOWED;
                goto $_fin;
            }
            if (++japaneseSpecialCharacterCount[rule] > japanSpecialCharRuleList[rule].amount)
            {
                result = CHECKNAME_SPECIAL_CHAR_OVERFLOW;
                goto $_fin;
            }
            if (japanSpecialCharRuleList[rule].onlyInfix && (i == 0 || i == nameLength - 1))
            {
                result = CHECKNAME_SIDE_SPECIAL_CHAR;
                goto $_fin;
            }
            if (!japanSpecialCharRuleList[rule].iterative && ch == prev)
            {
                result = CHECKNAME_DOUBLE_SPECIAL_CHAR;
                goto $_fin;
            }
        }
        *out++ = ch;
        prev = ch;
    }

    switch (LobbyDaemon::_instance->FilterBannedWord(word))
    {
    case LobbyDaemon::SWF_OK:
        break;
    case LobbyDaemon::SWF_INVALID_PARAMETER:
        result = CHECKNAME_INVALID_PARAMTER;
        break;
    case LobbyDaemon::SWF_FORBIDDEN:
        result = CHECKNAME_FORBIDDEN;
        break;
    default:
        result = CHECKNAME_SYSTEM_ERROR;
        break;
    }

$_fin:
    if (word != nullptr)
        Memory::_Manager[2]->Free(word, L"RuleSet.cpp", 196);
    return result;
}
