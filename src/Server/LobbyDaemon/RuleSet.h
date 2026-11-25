// RuleSet.obj (LobbyDaemon PDB, 2019 + PDB). Layout from tools/pdbcls.py LobbyDaemon RuleSet.
#pragma once

struct LobbyLocaleSet;

// PDB class RuleSet (sizeof 0x1). It has only the static CheckName.
class RuleSet
{
public:
    enum CheckNameResult
    {
        CHECKNAME_OK = 0,
        CHECKNAME_UNKNOWN = 1,
        CHECKNAME_SYSTEM_ERROR = 2,
        CHECKNAME_INVALID_PARAMTER = 3,
        CHECKNAME_TOO_SHORT = 4,
        CHECKNAME_TOO_LONG = 5,
        CHECKNAME_NOT_ALLOWED = 6,
        CHECKNAME_SIDE_SPACE = 7,
        CHECKNAME_DOUBLE_SPACE = 8,
        CHECKNAME_SPACE_OVERFLOW = 9,
        CHECKNAME_SENTENCE_CASE = 10,
        CHECKNAME_MULTILINGUAL = 11,
        CHECKNAME_FORBIDDEN = 12,
        CHECKNAME_SIDE_SPECIAL_CHAR = 13,
        CHECKNAME_DOUBLE_SPECIAL_CHAR = 14,
        CHECKNAME_SPECIAL_CHAR_OVERFLOW = 15,
    };

    static CheckNameResult CheckName(LobbyLocaleSet const& lcset, wchar_t const* name, int allowedMinLength,
                                     int allowedMaxLength, int allowSpaceAmount, bool enableNumeric,
                                     bool forceSentenceCase, bool enableMultilingual,
                                     wchar_t const* forbiddenCharacters);  // 0x6bfc0
};
