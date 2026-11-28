// clientsessionhandler.h: clientsessionhandler.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

// PDB class ClientSessionData (GameDaemon, size 0x20). The constructor is inlined in ClientSessionHandler::OnAccept.
class ClientSessionData
{
public:
    ClientSessionData()
    {
        _lastRequestTime[0] = 0;
        _lastRequestTime[1] = 0;
        _lastArenaSpectateUpdateTime[0] = 0;
        _lastArenaSpectateUpdateTime[1] = 0;
    }
private:
    __int64 _lastRequestTime[2];  // +0x0
    __int64 _lastArenaSpectateUpdateTime[2];  // +0x10
};
static_assert(sizeof(ClientSessionData) == 0x20, "sizeof ClientSessionData");

class ClientSessionHandler
{
public:
    virtual void __cdecl OnCreated(::Session const *) const;  // 0x7d6b0
    virtual void __cdecl OnDestroyed(::Session const *) const;  // 0x7d730
    virtual bool __cdecl OnAccept(::Session const *) const;  // 0x7d7b0
    virtual bool __cdecl OnConnect(::Session const *, bool) const;  // 0x7d810
    virtual void __cdecl OnClose(::Session const *, bool) const;  // 0x7d850
    virtual bool __cdecl PacketHandler(::Session const *, ::Packet const *) const;  // 0x7da70
private:
    void __cdecl sendRightFailPacket(::Session const *, short) const;  // 0x7e310
    static unsigned short __cdecl getDataSize(short, char const *, unsigned __int64);  // 0x7e530
    void __cdecl logMaxRecvDisconnect(__int64, ::User *, __int64, __int64) const;  // 0x7e6d0
};

