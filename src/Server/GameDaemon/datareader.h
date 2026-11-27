// datareader.h: datareader.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

wchar_t const * __cdecl GetDataReaderInterfaceVersion(void);  // 0x6eb2a0
bool __cdecl SetupDataReader(long, ::DrLog *, ::DrMemory *, ::DrMemory *);  // 0x6eb2b0
void __cdecl CloseDataReader(void);  // 0x6eb2c0
::DrDataReader * __cdecl CreateDataReader(void);  // 0x6eb2d0
::DrLog * __cdecl Logger(void);  // 0x6eb320
void __cdecl ReleaseDataReader(::DrDataReader *&);  // 0x6eb330
