// BannedWordFilterLoader.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
// ❓ The folder name src/External/BannedWordFilter is not verified.
#pragma once

class BannedWordFilterLoader
{
public:
    ~BannedWordFilterLoader();  // 0x118fa0
    static bool InitBannedWordFilterLoader();  // 0x119170
    static bool LoadNameFilter(char*);  // 0x1191f0
    static char* CreateFileBuffer(wchar_t const*);  // 0x119430
};
