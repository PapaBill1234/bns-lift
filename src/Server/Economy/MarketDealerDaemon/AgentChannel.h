// AgentChannel.obj (MarketDealerDaemon PDB). Layouts from include/pdb/MarketDealerDaemon/types.h.
#pragma once
#include <stddef.h>
#include "Channel.h"
#include "Daemon.h"
#include "Lock.h"

class Session;
class Packet;

class AgentChannel : public Channel
{
public:
    enum ConnectionType  // LIFT: no PDB enum. Values from AgentSessionHandler::PacketHandler (0x3cd0).
    {
        CONNECTION_MARKET_AGENT = 1,
    };

    virtual ~AgentChannel();             // later card
    virtual unsigned long long GetId();  // later card

    unsigned short const _agentWid;
    char const _connectionType;
};
static_assert(sizeof(AgentChannel) == 0x30, "sizeof AgentChannel");
static_assert(offsetof(AgentChannel, _agentWid) == 0x28, "AgentChannel::_agentWid");
static_assert(offsetof(AgentChannel, _connectionType) == 0x2A, "AgentChannel::_connectionType");

class AgentChannelManager
{
public:
    bool initChannelManager();                                       // 0x37c0
    AgentChannel* GetMarketAgentChannel();                           // 0x3860. Adds a reference.
    bool SetMarketAgentChannel(AgentChannel* const marketAgentChannel);  // 0x38b0
    void RemoveMarketAgentChannel();                                 // 0x39e0

    CriticalSection _lock;
    AgentChannel* _marketAgentChannel;
};
static_assert(sizeof(AgentChannelManager) == 0x30, "sizeof AgentChannelManager");
static_assert(offsetof(AgentChannelManager, _marketAgentChannel) == 0x28, "AgentChannelManager::_marketAgentChannel");

class AgentSessionHandler : public SessionHandler
{
public:
    virtual bool OnAccept(Session const* session) const;                             // 0x3a30
    virtual bool OnConnect(Session const* session, bool firstConnected) const;       // 0x3a90
    virtual void OnClose(Session const* session, bool tryReconnect) const;           // 0x3af0
    virtual bool PacketHandler(Session const* session, Packet const* packet) const;  // 0x3cd0
    virtual ~AgentSessionHandler() {}
};
static_assert(sizeof(AgentSessionHandler) == 0x8, "sizeof AgentSessionHandler");

// Handler list objects (data only, later card). PDB type in types.h is void*; the element type is Daemon::PacketHandler.
extern Daemon::PacketHandler MarketDealerPacketServerSideHandlerList[76];
extern Daemon::PacketHandler MarketDealerPacketServerSideFragmentHandlerList[76];
extern Daemon::PacketHandler MarketAgentPacketClientSideHandlerList[5];
extern Daemon::PacketHandler MarketAgentPacketClientSideFragmentHandlerList[5];
