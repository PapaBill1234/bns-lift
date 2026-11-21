// BannedWordFilterLib.obj (LobbyDaemon PDB, 2019 + PDB). BannedWordFilterLib: sizeof 1, no members.
// LIFT: the PDB lists also Initialize, LoadChatFilterFile, LoadChatFilterBuffer, LoadNameFilterFile,
// LoadNameFilterBuffer, FilterChat and the private clear. These functions are not in this binary (inlined or not used).
// ❓ The folder name src/External/BannedWordFilter is not verified.
#pragma once

class BannedWordFilterLib
{
public:
    bool FilterName(wchar_t const* const nameStr, bool* const isFiltered);  // 0x118a70
};
