// PostOfficeDaemon.obj (PostOfficeDaemon PDB). Layouts from include/pdb/PostOfficeDaemon/types.h.
// Card lift-postofficedaemon-2 declares only the data layout. A later card lifts the functions.
#pragma once
#include <stddef.h>
#include "Daemon.h"
#include "Channel.h"

class SessionHandler;
class WorldConfigManager;
class CachedWatchdogManager;
class AgentChannelManager;
class WorldChannelManager;
class CacheGateChannelManager;
class PostContextManager;
class RelayContextManager;
class RelayTimeContextManager;
class UnsentPostContextManager;
class RelayTimeoutChecker;
class UnsentPostChecker;
class RelayContext;

class PostOfficeConfig
{
public:
    wchar_t* _rootPath;
    wchar_t* _logPath;
    wchar_t* _configPath;
    char* _certFile;
    int _workerThreadCount;
    int _maxAgentSessionCount;
    int _maxWorldSessionCount;
    int _dumpType;
    int _relayTimeoutInterval;
    int _pingInterval;
    int _deliveryRetryInterval;
    int _agentListenPort;
    int _worldListenPort;
    int _managePort;
    unsigned long _cachegateIpAddr;
    int _cachegateListenPort;
    int _serviceWid;
};
static_assert(offsetof(PostOfficeConfig, _relayTimeoutInterval) == 0x30, "PostOfficeConfig::_relayTimeoutInterval");
static_assert(offsetof(PostOfficeConfig, _pingInterval) == 0x34, "PostOfficeConfig::_pingInterval");

#include "CacheGateChannel.h"

class PostOfficeDaemon : public Daemon
{
public:
    CacheGateChannel* checkCacheGateServiceState();  // 0x14930 (later card)
    static CacheGateChannel* checkDestinationServiceState(unsigned short destinationWid);  // 0x147d0 (later card)

    PostOfficeConfig const* _config;
    unsigned short const _serviceWid;
    SessionHandler* _sessionHandler[25];
    WorldConfigManager* _worldConfigManager;
    CachedWatchdogManager* _cachedWatchdogManager;
    AgentChannelManager* _agentChannelManager;
    WorldChannelManager* _worldChannelManager;
    CacheGateChannelManager* _cachegateChannelManager;
    PostContextManager* _postContextManager;
    RelayContextManager* _relayContextManager;
    RelayTimeContextManager* _relayTimeContextManager;
    UnsentPostContextManager* _unsentPostContextManager;
    RelayTimeoutChecker* _relayTimeoutChecker;
    UnsentPostChecker* _unsentPostChecker;

    static PostOfficeDaemon* _instance;  // ❓ defined in PostOfficeDaemon.cpp (later card)

private:
    PostOfficeDaemon();  // later card
};
static_assert(sizeof(PostOfficeDaemon) == 0x878, "sizeof PostOfficeDaemon");
static_assert(offsetof(PostOfficeDaemon, _config) == 0x748, "PostOfficeDaemon::_config");
static_assert(offsetof(PostOfficeDaemon, _cachedWatchdogManager) == 0x828, "PostOfficeDaemon::_cachedWatchdogManager");
static_assert(offsetof(PostOfficeDaemon, _relayContextManager) == 0x850, "PostOfficeDaemon::_relayContextManager");
static_assert(offsetof(PostOfficeDaemon, _relayTimeoutChecker) == 0x868, "PostOfficeDaemon::_relayTimeoutChecker");
