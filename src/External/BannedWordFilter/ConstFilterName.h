// ConstFilterName.obj (LobbyDaemon PDB, 2019 + PDB).
// ❓ The folder name src/External/BannedWordFilter is not verified.
#pragma once
#include <string>
#include "STLMemory.h"

// PDB: the string type of str (type 0x7FB8). LIFT: the PDB has no typedef name for it.
typedef std::basic_string<wchar_t, std::char_traits<wchar_t>, BannedWordFilterAllocator<wchar_t> > BannedWordFilterString;

bool ConstFilterName(BannedWordFilterString& str);  // 0x119870
