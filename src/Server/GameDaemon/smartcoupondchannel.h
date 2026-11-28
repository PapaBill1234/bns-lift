// smartcoupondchannel.h: smartcoupondchannel.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

// PDB: SmartCouponSessionHandler (GameDaemon), size 0x8, base SessionHandler +0.
class SmartCouponSessionHandler : public SessionHandler
{
public:
    virtual bool __cdecl OnAccept(::Session const *) const;  // 0x28030
    virtual bool __cdecl OnConnect(::Session const *, bool) const;  // 0x28070
    virtual void __cdecl OnClose(::Session const *, bool) const;  // 0x282a0
    virtual bool __cdecl PacketHandler(::Session const *, ::Packet const *) const;  // 0x28480
};

class SmartCoupondChannel
{
public:
    void __cdecl Initialize(short);  // 0x284e0
    bool __cdecl SendHello(void);  // 0x28610
};

class SmartCoupondChannelManager
{
public:
    bool __cdecl Initialize(short, short *const);  // 0x28780
    void __cdecl Destroy(void);  // 0x28ad0
private:
    ::SmartCoupondChannel * __cdecl acquire(unsigned int);  // 0x28c40
public:
    bool __cdecl Send(short, char const *, ...);  // 0x28d10
    bool __cdecl LoadGameEventConfig(wchar_t const *);  // 0x28e00
    bool __cdecl SendGameEventByCharacterReq(short, int, ::id128 const &, unsigned __int64);  // 0x28eb0
private:
    bool __cdecl checkGameEventConfig(int, ::id128 const &);  // 0x29170
};

unsigned __int64 __cdecl GenerateGameEventTid(void);  // 0x27fe0
