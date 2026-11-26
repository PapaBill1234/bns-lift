// BannedWordFilterLib.obj (LobbyDaemon PDB, 2019 + PDB). BannedWordFilterLib: sizeof 1, no members.
// LIFT: the PDB lists also LoadChatFilterFile, LoadChatFilterBuffer, LoadNameFilterBuffer, FilterChat and the private
// clear. These functions are not in this binary (inlined or not used). Initialize and LoadNameFilterFile are inline.
// ❓ The folder name src/External/BannedWordFilter is not verified.
#pragma once
#include "BannedWordFilterLoader.h"
#include "STLMemory.h"

class BannedWordFilterLib
{
public:
    BannedWordFilterLib() {}
    ~BannedWordFilterLib() {}

    // LIFT: inline. LobbyDaemon::initialize (0x9b300) has this body (line 1485 checks the result).
    bool Initialize(BannedWordFilterMemoryManager* const memoryManager)
    {
        if (!BannedWordFilterMemory::SetupMemoryManager(memoryManager))
            return false;
        return BannedWordFilterLoader::InitBannedWordFilterLoader();
    }
    // LIFT: inline. LobbyDaemon::initialize (0x9b300) has this body (line 1496 checks the result).
    bool LoadNameFilterFile(wchar_t* fileFullPath)
    {
        if (BannedWordFilterMemory::Memory() == NULL)
            return false;
        if (BannedWordFilterLoader::GetInstance() == NULL)
            return false;
        return BannedWordFilterLoader::LoadNameFilter(BannedWordFilterLoader::CreateFileBuffer(fileFullPath));
    }
    bool FilterName(wchar_t const* const nameStr, bool* const isFiltered);  // 0x118a70
};
