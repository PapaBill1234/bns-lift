// binarydatafile.h: binarydatafile.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class BinaryDataFile
{
private:
    static bool __cdecl readFromMem(unsigned char *, int, ::DrElReader const &, ::DrLoaderDef *, int, bool, ::DrAliasMap &, unsigned __int64);  // 0x6fa370
    static bool __cdecl readFromFileStream(void *, int, ::DrElReader const &, ::DrLoaderDef *, int, ::DrAliasMap &, unsigned __int64);  // 0x6fa7b0
public:
    static bool __cdecl ReadFromMem(::DrDataReader *, unsigned char *, int, ::DrElReader const &, ::DrLoaderDef *, int, bool, ::DrAliasMap &, unsigned __int64);  // 0x6fac30
    static bool __cdecl ReadFromFileStream(::DrDataReader *, void *, int, ::DrElReader const &, ::DrLoaderDef *, int, bool, ::DrAliasMap &, unsigned __int64);  // 0x6fad10
    static bool __cdecl ReadFromFile(wchar_t const *, bool, ::DrDataReader *, ::DrElReader const &, ::DrLoaderDef *, int, ::DrAliasMap &, unsigned __int64);  // 0x6fade0
    static bool __cdecl ReadFromFileStream(wchar_t const *, bool, ::DrDataReader *, ::DrElReader const &, ::DrLoaderDef *, int, ::DrAliasMap &, unsigned __int64);  // 0x6faff0
};

