// util.h: util.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

namespace DrUtil {
bool __cdecl GenerateMD5Checksum(unsigned char const *, unsigned __int64, unsigned char *);  // 0x6fed30
bool __cdecl Copy(wchar_t *, int, wchar_t const *);  // 0x6fee40
int __cdecl Length(wchar_t const *);  // 0x6fee60
}
