// InfoGateChannel.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: InfoGateChannel and InfoGateChannelManager have their PDB layouts (ld-23 batch 4).
#pragma once
#include <stddef.h>
#include "Channel.h"
#include "Lock.h"
#include "SharedChannel.h"

class InfoGateChannel;
class Packet;
class Session;
union id128;

class InfoGateChannel : public SharedChannel
{
public:
    // LIFT: inlined in HandleLobbyInfoGate_HelloReq (0x56d40): vftable, _broadcastable = false.
    InfoGateChannel() : _broadcastable(false) {}
    // LIFT: PDB inline methods (type 0x53EC, 0x53ED, 0x53EA). The bodies are not in the PDB; they come from the inlined code at the callers.
    short GetWid()
    {
        short wid = 0;
        if (_rawChannel != nullptr)
            wid = static_cast<short>(_rawChannel->GetId());
        return wid;
    }
    bool IsBroadcastable() const { return _broadcastable; }
    void StartBroadcast() { _broadcastable = true; }
    void SendAuthTokenOk(unsigned long long, unsigned long long, id128 const&);  // 0x2e6d0
    void SendAuthTokenFail(unsigned long long, unsigned long long, short);  // 0x2e870
    void SendGetWorldInfoListFail(short);  // 0x2e980

private:
    bool _broadcastable;  // PDB: private
    // LIFT: offsetof of a private member is only legal inside the class.
    static void CheckLayout() { static_assert(offsetof(InfoGateChannel, _broadcastable) == 0x20, "InfoGateChannel::_broadcastable"); }
};
static_assert(sizeof(InfoGateChannel) == 0x28, "sizeof InfoGateChannel");

class InfoGateChannelManager : public SessionHandler
{
public:
    InfoGateChannelManager() {}  // LIFT: PDB inline ctor. Inlined in LobbyDaemon::initNetwork (0x9d520).
    virtual ~InfoGateChannelManager();  // 0x2ea70
    // LIFT: PDB inline Initialize(short, short). Inlined in LobbyDaemon::initNetwork (0x9d520).
    bool Initialize(short idmin, short idmax);
    bool Add(InfoGateChannel*);  // 0x2eb50
    void Remove(short);  // 0x2ec10
    InfoGateChannel* Acquire(short);  // 0x2ed20
    void BroadcastBoastEventInWorldNotify(short, wchar_t const*, short);  // 0x2edf0
    bool Broadcast(Packet const*);  // 0x2ef40
    virtual bool OnAccept(Session const*) const;  // 0x2f040
    virtual bool OnConnect(Session const*, bool) const;  // 0x2f0b0
    virtual void OnClose(Session const*, bool) const;  // 0x2f170
    virtual bool PacketHandler(Session const*, Packet const*) const;  // 0x2f300

    SharedChannelList _channels;
    CriticalSection _lock;
};
static_assert(sizeof(InfoGateChannelManager) == 0x48, "sizeof InfoGateChannelManager");
static_assert(offsetof(InfoGateChannelManager, _channels) == 0x8, "InfoGateChannelManager::_channels");
static_assert(offsetof(InfoGateChannelManager, _lock) == 0x20, "InfoGateChannelManager::_lock");
