// logserver.h: logserver.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class LogServer
{
public:
    virtual __cdecl ~LogServer(void);  // 0x6ba5a0
    bool __cdecl Initialize(bool, unsigned __int64);  // 0x6ba6b0
    virtual bool __cdecl Connect(unsigned long, unsigned short);  // 0x6ba780
    virtual void __cdecl Close(void);  // 0x6ba7a0
    void __cdecl ClearLogData(void);  // 0x6ba870
    bool __cdecl AsyncSend(void);  // 0x6ba900
    bool __cdecl SendComplete(void);  // 0x6bab30
    bool __cdecl RecvComplete(void);  // 0x6bad70
    bool __cdecl waitComplete(void);  // 0x6baf30
    bool __cdecl AsyncRecv(void);  // 0x6bb020
    virtual bool __cdecl HandlePacket(::Packet const *);  // 0x6bb0a0
};

