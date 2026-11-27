// logarchivecontext.h: logarchivecontext.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class LogArchiveReadBuffer
{
public:
    __cdecl LogArchiveReadBuffer(void);  // 0x6d8430
    __cdecl ~LogArchiveReadBuffer(void);  // 0x6d84c0
    bool __cdecl ClearBuffer(void);  // 0x6d84f0
};

class LogArchiveWriteBuffer
{
protected:
    __cdecl LogArchiveWriteBuffer(int);  // 0x6d8560
public:
    bool __cdecl PushNetworkData(char const *const, unsigned int);  // 0x6d8650
    bool __cdecl PushFileData(char const *const, unsigned int);  // 0x6d8860
    bool __cdecl ClearNetworkBuffer(void);  // 0x6d89e0
    bool __cdecl ClearFileBuffer(void);  // 0x6d8aa0
protected:
    bool __cdecl growBufferChunkSize(unsigned int);  // 0x6d8b30
    bool __cdecl growBufferCount(unsigned int);  // 0x6d8ca0
};

class LogArchiveWriteContext
{
public:
    __cdecl LogArchiveWriteContext(int);  // 0x6d8de0
    __cdecl ~LogArchiveWriteContext(void);  // 0x6d8e80
    bool __cdecl SwitchStatus(void);  // 0x6d8f20
    ::LogArchiveWriteBuffer *const __cdecl GetWritingBuffer(void) const;  // 0x6d8fa0
};

