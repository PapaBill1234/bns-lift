// BannedWordFilterLib.obj (LobbyDaemon PDB, 2019 + PDB): lines from the PDB line map.
// ❓ The folder name src/External/BannedWordFilter is not verified.
#include "BannedWordFilterLib.h"
#include "BannedWordFilterLoader.h"
#include "ConstFilterName.h"

// rva 0x209898. LIFT: the owner obj of the definition is not in the PDB (S_GDATA32 in globals).
// ❓ The original can define it in an STLMemory.cpp.
BannedWordFilterMemoryManager* BannedWordFilterMemory::_memoryManager = NULL;

// 0x118a70
bool BannedWordFilterLib::FilterName(wchar_t const* const nameStr, bool* const isFiltered)
{
    if (isFiltered == NULL)
        return false;

    if (BannedWordFilterMemory::Memory() == NULL)
        return false;

    if (BannedWordFilterLoader::GetInstance() == NULL)
        return false;

    BannedWordFilterString str(nameStr);
    *isFiltered = ConstFilterName(str);

    return true;
}
