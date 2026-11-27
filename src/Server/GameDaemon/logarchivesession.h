// logarchivesession.h: logarchivesession.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class LogArchiveSession
{
public:
    virtual __cdecl ~LogArchiveSession(void);  // 0x6b9d00
    virtual bool __cdecl Connect(unsigned long, unsigned short);  // 0x6b9d60
    bool __cdecl Send(::Packet const *);  // 0x6b9fd0
    bool __cdecl Recv(::Packet *);  // 0x6ba1f0
private:
    int __cdecl recv(char *, int, int);  // 0x6ba300
public:
    virtual void __cdecl Close(void);  // 0x6ba510
};

