// InfoGateChannel.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

class InfoGateChannel;
class Packet;
class Session;
union id128;

class InfoGateChannel
{
public:
    void SendAuthTokenOk(unsigned long long, unsigned long long, id128 const&);  // 0x2e6d0
    void SendAuthTokenFail(unsigned long long, unsigned long long, short);  // 0x2e870
    void SendGetWorldInfoListFail(short);  // 0x2e980
};

class InfoGateChannelManager
{
public:
    virtual ~InfoGateChannelManager();  // 0x2ea70
    bool Add(InfoGateChannel*);  // 0x2eb50
    void Remove(short);  // 0x2ec10
    InfoGateChannel* Acquire(short);  // 0x2ed20
    void BroadcastBoastEventInWorldNotify(short, wchar_t const*, short);  // 0x2edf0
    bool Broadcast(Packet const*);  // 0x2ef40
    virtual bool OnAccept(Session const*) const;  // 0x2f040
    virtual bool OnConnect(Session const*, bool) const;  // 0x2f0b0
    virtual void OnClose(Session const*, bool) const;  // 0x2f170
    virtual bool PacketHandler(Session const*, Packet const*) const;  // 0x2f300
};
