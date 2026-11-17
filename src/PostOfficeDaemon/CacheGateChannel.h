// CacheGateChannel.obj (PostOfficeDaemon PDB). Layouts from include/pdb/PostOfficeDaemon/types.h.
#pragma once
#include <stddef.h>
#include "Channel.h"
#include "Lock.h"

class Session;
class Packet;
class FragmentPacket;
class RelayContext;
class RelayHeader;

class CacheGateChannel : public Channel
{
public:
    enum ServiceState
    {
        SERVICE_STATE_UNAVAILABLE = 0,
        SERVICE_STATE_AVAILABLE = 1,
    };

    virtual ~CacheGateChannel();
    virtual unsigned long long GetId();

    bool SendRelayRequest(RelayContext const* const relayContext);                                        // 0x7000
    bool SendFragmentRelayRequest(RelayContext const* const relayContext, char const* const economyFormat);  // 0x71e0

    // PDB method, inlined in 0x7b50 and 0x7e90.
    void SetServiceState(ServiceState const newState);

    ServiceState _serviceState;
};
static_assert(sizeof(CacheGateChannel) == 0x30, "sizeof CacheGateChannel");
static_assert(offsetof(CacheGateChannel, _serviceState) == 0x28, "CacheGateChannel::_serviceState");

class CacheGateChannelManager
{
public:
    bool initChannelManager();                                    // 0x7740
    bool SetCacheGateChannel(CacheGateChannel* const cachegateChannel);  // 0x77e0

    CriticalSection _lock;
    CacheGateChannel* _cachegateChannel;

    // PDB constructor, inlined at 0x14090.
    CacheGateChannelManager() : _lock(4000), _cachegateChannel(nullptr) {}
};
static_assert(sizeof(CacheGateChannelManager) == 0x30, "sizeof CacheGateChannelManager");
static_assert(offsetof(CacheGateChannelManager, _cachegateChannel) == 0x28, "CacheGateChannelManager::_cachegateChannel");

class CacheGateSessionHandler : public SessionHandler
{
public:
    virtual ~CacheGateSessionHandler();
    virtual bool OnAccept(Session const* session) const;                          // 0x7900
    virtual bool OnConnect(Session const* session, bool firstConnected) const;    // 0x7960
    virtual void OnClose(Session const* session, bool tryReconnect) const;        // 0x7b50
    virtual bool PacketHandler(Session const* session, Packet const* packet) const;  // 0x7d90
};
static_assert(sizeof(CacheGateSessionHandler) == 0x8, "sizeof CacheGateSessionHandler");
