// winserviceconsole_h.cpp: winserviceconsole.h (GameDaemon PDB, 2019 + PDB).
#include "winserviceconsole_gd.h"
#include "actsequenceloader.h"
#pragma comment(linker, "/INCLUDE:?ReadFromBuffer@ActSequenceLoader@@UEAA_NAEBVDrElReader@@AEBUDrLoaderDef@@PEBE_K@Z")  // LIFT: dead-strip keep (no live caller yet)

// 0x455420
// LIFT: the PDB names this slot ActSequenceLoader::ReadFromBuffer; the body is in winserviceconsole.h.
bool __cdecl ActSequenceLoader::ReadFromBuffer(::DrElReader const &, ::DrLoaderDef const &, unsigned char const *, unsigned __int64)
{
    return false;
}
