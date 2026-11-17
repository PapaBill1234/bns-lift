// AgentChannel.obj (MarketDealerDaemon PDB). Layouts from include/pdb/MarketDealerDaemon/types.h.
// The functions of this module come from a later card.
#pragma once
#include <stddef.h>
#include "Channel.h"
#include "Lock.h"

class AgentChannel : public Channel
{
public:
    virtual ~AgentChannel();
    virtual unsigned long long GetId();

    unsigned short const _agentWid;
    char const _connectionType;
};
static_assert(sizeof(AgentChannel) == 0x30, "sizeof AgentChannel");
static_assert(offsetof(AgentChannel, _agentWid) == 0x28, "AgentChannel::_agentWid");
static_assert(offsetof(AgentChannel, _connectionType) == 0x2A, "AgentChannel::_connectionType");

class AgentChannelManager
{
public:
    AgentChannel* GetMarketAgentChannel();  // 0x3860. Adds a reference. Later card.

    CriticalSection _lock;
    AgentChannel* _marketAgentChannel;
};
static_assert(sizeof(AgentChannelManager) == 0x30, "sizeof AgentChannelManager");
static_assert(offsetof(AgentChannelManager, _marketAgentChannel) == 0x28, "AgentChannelManager::_marketAgentChannel");
