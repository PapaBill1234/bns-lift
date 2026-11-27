// postofficeagentchannel.h: postofficeagentchannel.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "cachedaemonchannel.h"

class PostOfficeAgentChannel
{
public:
    void __cdecl Initialize(short);  // 0x196660
    bool __cdecl SendHello(void);  // 0x196790
};

class PostOfficeAgentChannelManager
{
public:
    bool __cdecl Initialize(short, short *const);  // 0x197080
    void __cdecl Destroy(void);  // 0x1973e0
private:
    ::PostOfficeAgentChannel * __cdecl acquire(unsigned int);  // 0x197550
public:
    bool __cdecl Send(short, char const *, ...);  // 0x197620
    bool __cdecl Send(short, ::Packet const *);  // 0x197710
    void __cdecl SendDeliverPostReq(::Pc *, char, char, short, __int64, wchar_t *, wchar_t *, wchar_t *, ::CachedChannel::AttachedItem *const, short);  // 0x197800
};

class PostOfficeAgentSessionHandler
{
public:
    virtual bool __cdecl OnAccept(::Session const *) const;  // 0x1961b0
    virtual bool __cdecl OnConnect(::Session const *, bool) const;  // 0x1961f0
    virtual void __cdecl OnClose(::Session const *, bool) const;  // 0x196420
    virtual bool __cdecl PacketHandler(::Session const *, ::Packet const *) const;  // 0x196600
};

bool __cdecl HandlePostOfficeServiceCheckPostCapacityOk(::Session const *, ::Packet const *);  // 0x196930
bool __cdecl HandlePostOfficeServiceCheckPostCapacityFail(::Session const *, ::Packet const *);  // 0x1969d0
bool __cdecl HandlePostOfficeServiceRetrieveCharacterInfoOk(::Session const *, ::Packet const *);  // 0x196b60
bool __cdecl HandlePostOfficeServiceRetrieveCharacterInfoFail(::Session const *, ::Packet const *);  // 0x196cf0
bool __cdecl HandlePostOfficeServiceHelloOk(::Session const *, ::Packet const *);  // 0x196e80
bool __cdecl HandlePostOfficeServiceHelloFail(::Session const *, ::Packet const *);  // 0x196f80
