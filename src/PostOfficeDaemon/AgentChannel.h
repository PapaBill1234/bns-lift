// AgentChannel.obj (PostOfficeDaemon PDB). Layouts from include/pdb/PostOfficeDaemon/types.h.
#pragma once
#include <stddef.h>
#include "Channel.h"
#include "Lock.h"

class Session;
class Packet;

class AgentChannel : public Channel
{
public:
    // ❓ Inlined in HandlePostOfficeHelloReq (0x1a6f0).
    AgentChannel(unsigned short agentWid, char connectionType) : _agentWid(agentWid), _connectionType(connectionType) {}
    virtual ~AgentChannel();                  // 0x1f620 (scalar deleting destructor)
    virtual unsigned long long GetId();       // 0x1a6e0

    unsigned short const _agentWid;
    char const _connectionType;
};
static_assert(sizeof(AgentChannel) == 0x30, "sizeof AgentChannel");
static_assert(offsetof(AgentChannel, _agentWid) == 0x28, "AgentChannel::_agentWid");
static_assert(offsetof(AgentChannel, _connectionType) == 0x2A, "AgentChannel::_connectionType");

class AgentChannelManager
{
public:
    bool initChannelManager();  // 0x36c0

    CriticalSection _lock;
    AgentChannel* _postAgentChannel;

    // ❓ Inlined at 0x14090.
    AgentChannelManager() : _lock(4000), _postAgentChannel(nullptr) {}
};
static_assert(sizeof(AgentChannelManager) == 0x30, "sizeof AgentChannelManager");
static_assert(offsetof(AgentChannelManager, _postAgentChannel) == 0x28, "AgentChannelManager::_postAgentChannel");

class AgentSessionHandler : public SessionHandler
{
public:
    virtual ~AgentSessionHandler();
    virtual bool OnAccept(Session const* session) const;                             // 0x3760
    virtual bool OnConnect(Session const* session, bool firstConnected) const;       // 0x37c0
    virtual void OnClose(Session const* session, bool tryReconnect) const;           // 0x3820
    virtual bool PacketHandler(Session const* session, Packet const* packet) const;  // 0x3a00
};
static_assert(sizeof(AgentSessionHandler) == 0x8, "sizeof AgentSessionHandler");
