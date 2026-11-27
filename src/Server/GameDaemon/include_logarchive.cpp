// include_logarchive.cpp: logarchive.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "logarchive.h"
#pragma comment(linker, "/INCLUDE:?Name@LogArchive@@UEAAPEB_WXZ")  // LIFT: dead-strip keep (no live caller yet)

// 0x694060
wchar_t const * __cdecl LogArchive::Name(void)
{
    return L"LogArchive";
}
