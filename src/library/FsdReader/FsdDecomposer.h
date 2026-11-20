// FsdDecomposer.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

class FsdDecomposer
{
public:
    bool GetByte(char*);  // 0x119d00
    bool GetWord(short*);  // 0x119dd0
    bool GetDword(int*);  // 0x119ea0
    bool GetQword(long long*);  // 0x119f70
    int GetString(wchar_t*, int);  // 0x11a040
private:
    bool Decompose();  // 0x119c10
};
