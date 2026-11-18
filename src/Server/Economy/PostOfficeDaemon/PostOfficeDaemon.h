// PostOfficeDaemon.obj (PostOfficeDaemon PDB). Layouts from include/pdb/PostOfficeDaemon/types.h.
#pragma once
#include <stddef.h>
#include <string.h>
#include "Daemon.h"
#include "Channel.h"
#include "DaemonConfig.h"

class SessionHandler;
class EventObject;
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

    static XmlCfgDef const _Def[23];  // 0x97ab0
};
static_assert(sizeof(PostOfficeConfig) == 0x58, "sizeof PostOfficeConfig");
static_assert(offsetof(PostOfficeConfig, _relayTimeoutInterval) == 0x30, "PostOfficeConfig::_relayTimeoutInterval");
static_assert(offsetof(PostOfficeConfig, _pingInterval) == 0x34, "PostOfficeConfig::_pingInterval");
static_assert(offsetof(PostOfficeConfig, _serviceWid) == 0x50, "PostOfficeConfig::_serviceWid");

#include "CacheGateChannel.h"

class PostOfficeDaemon : public Daemon
{
public:
    enum PostEvent
    {
        POSTEVENT_POST_DELIVERY_EVENT = 0x80,
        POSTEVENT_RELAY_TIMEOUT_EVENT = 0x81,
        POSTEVENT_PACKET_PUMP_EVENT = 0x82
    };
    // Inline constructor. The binary writes it in wmain (0x12ca0).
    PostOfficeDaemon() : _config(nullptr), _serviceWid(0)
    {
        memset(&_worldConfigManager, 0, 88);
        memset(_sessionHandler, 0, sizeof(_sessionHandler));
    }
    virtual ~PostOfficeDaemon();  // 0x12dd0

    virtual wchar_t const* ServiceName();   // 0x12bd0
    virtual wchar_t const* ShortName();     // 0x12bb0
    virtual wchar_t const* Name();          // 0x12bc0
    virtual wchar_t const* Descriptions();  // 0x12be0
    virtual long GetTimerInterval();        // 0x12bf0
    virtual long GetTimerMaxTime();         // 0x12c00
    virtual void PrintDependency();         // 0x12f50

    static void FailedEventObjectHandler(EventObject* eventObject);  // 0x12fe0

    CacheGateChannel* checkCacheGateServiceState();                                         // 0x14930
    static CacheGateChannel* checkDestinationServiceState(unsigned short destinationWid);  // 0x147d0

protected:
    virtual bool initLog();                                  // 0x130c0
    virtual bool setArgument(int argc, wchar_t const** argv);  // 0x12c10
    virtual bool initialize();                               // 0x132b0
    virtual bool initNetwork();                              // 0x135e0
    virtual bool onStart();                                  // 0x13ca0
    virtual void shutdown();                                 // 0x14a30
    virtual bool reload(wchar_t** args, int count);          // 0x14b80

private:
    bool initWorldConfigDependencyManager();      // 0x13d30
    bool initChannelManager(int bucketCount);     // 0x14090
    bool initContextManager(int bucketCount);     // 0x14280
    bool loadAllUnsentPostFromDB();               // 0x14460
    bool openListenPort();                        // 0x14520
    bool startTimer();                            // 0x14660

public:
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

    static PostOfficeDaemon* _instance;  // rva 0x98BD8
};
static_assert(sizeof(PostOfficeDaemon) == 0x878, "sizeof PostOfficeDaemon");
static_assert(offsetof(PostOfficeDaemon, _config) == 0x748, "PostOfficeDaemon::_config");
static_assert(offsetof(PostOfficeDaemon, _cachedWatchdogManager) == 0x828, "PostOfficeDaemon::_cachedWatchdogManager");
static_assert(offsetof(PostOfficeDaemon, _relayContextManager) == 0x850, "PostOfficeDaemon::_relayContextManager");
static_assert(offsetof(PostOfficeDaemon, _relayTimeoutChecker) == 0x868, "PostOfficeDaemon::_relayTimeoutChecker");
