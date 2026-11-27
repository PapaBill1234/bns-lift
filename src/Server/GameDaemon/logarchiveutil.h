// logarchiveutil.h: logarchiveutil.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class LogArchiveUtil
{
public:
    static int const __cdecl GetUtf8StringSizeToTranslate(wchar_t const *const);  // 0x6b8130
    static bool __cdecl UnicodeToMultibyte(char *const, int, wchar_t const *const);  // 0x6b81e0
    static unsigned int __cdecl ComposeNetLogData(char *const, unsigned int, char const *const, char *);  // 0x6b82e0
    static unsigned int __cdecl ConvertNetDataToFileData(char *const, unsigned int, char const *const, char const *const);  // 0x6b8cf0
private:
    static bool __cdecl ReplaceOriginCharToSpecialChar(wchar_t *const);  // 0x6b9af0
    static unsigned int const __cdecl GetAlphabetCount(char const *const);  // 0x6b9ba0
};

