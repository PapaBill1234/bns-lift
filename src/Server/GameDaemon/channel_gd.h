// channel_gd.h: channel.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class ClientSideHashedDaemonChannel
{
public:
    virtual __cdecl ~ClientSideHashedDaemonChannel(void);  // 0x69aa70
    bool __cdecl Send(unsigned __int64, char const *, ...);  // 0x69abf0
    bool __cdecl Send(unsigned __int64, ::Packet const *);  // 0x69ac40
protected:
    void __cdecl initialize(unsigned int, unsigned long, unsigned short);  // 0x69acc0
    bool __cdecl initSession(bool *, bool, bool);  // 0x69ad60
    virtual ::Session * __cdecl getSession(unsigned __int64);  // 0x69af30
    virtual void __cdecl releaseSession(::Session *);  // 0x69afb0
};

class ServerSideDaemonChannel
{
public:
    virtual __cdecl ~ServerSideDaemonChannel(void);  // 0x69b000
    bool __cdecl Initialize(int);  // 0x69b0a0
    void __cdecl CloseAll(void);  // 0x69b170
protected:
    virtual bool __cdecl onAccept(::Session const *);  // 0x69b260
    virtual void __cdecl onClose(::Session const *, bool, bool);  // 0x69b340
    virtual ::Session * __cdecl getSession(void);  // 0x69b4c0
    virtual void __cdecl releaseSession(::Session *);  // 0x69b670
};

