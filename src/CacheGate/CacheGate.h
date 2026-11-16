// CacheGate.obj (CacheGate PDB). Layouts from include/pdb/CacheGate/types.h.
#pragma once
#include <stddef.h>
#include "CacheD.h"
#include "CacheDChannel.h"
#include "Daemon.h"
#include "DaemonConfig.h"

class ClientManager;
class EventObject;
class SessionHandler;

class CacheGateConfig
{
public:
    wchar_t* _rootPath;
    wchar_t* _logPath;
    wchar_t* _configPath;
    char* _certFile;
    int _workerThreadCount;
    int _dumpType;
    int _maxCachedSessionCount;
    int _maxPublicSessionCount;
    int _publicPort;
    int _wid;

    static XmlCfgDef const _Def[13];  // 0x596C0
};
static_assert(sizeof(CacheGateConfig) == 0x38, "sizeof CacheGateConfig");
static_assert(offsetof(CacheGateConfig, _workerThreadCount) == 0x20, "CacheGateConfig::_workerThreadCount");
static_assert(offsetof(CacheGateConfig, _wid) == 0x34, "CacheGateConfig::_wid");

class CacheGate : public Daemon
{
public:
    // ❓ The constructor is inlined in wmain (0x4180).
    CacheGate() : _clientManager(nullptr) {}
    virtual ~CacheGate();                                    // 0x4290
    virtual wchar_t const* ShortName();                      // 0x4050
    virtual wchar_t const* Name();                           // 0x4060
    virtual wchar_t const* ServiceName();                    // 0x4070
    virtual wchar_t const* Descriptions();                   // 0x4080
    virtual long GetTimerInterval();                         // 0x4090
    virtual long GetTimerMaxTime();                          // 0x40A0
    virtual void PrintDependency();                          // 0x4B90
    virtual bool initLog();                                  // 0x43F0
    virtual bool setArgument(int argc, wchar_t const** argv);  // ❓ not in index
    virtual bool initialize();                               // 0x4510
    virtual bool initNetwork();                              // 0x4770
    virtual bool onStart();                                  // 0xCD80
    virtual void shutdown();                                 // 0x4930
    virtual bool reload(wchar_t** argv, int argc);           // 0x4970

    static void FailedEventObjectHandler(EventObject* eventObject);  // 0x4B40

    static CacheGate* _instance;  // 0x5A3E0

    CacheGateConfig const* _config;
    SessionHandler* _sessionHandler[512];
    ClientManager* _clientManager;
    CacheDList _cachedList;
    CacheDChannel _cachedChannel;
};
static_assert(sizeof(CacheGate) == 0x17B8, "sizeof CacheGate");
static_assert(offsetof(CacheGate, _config) == 0x748, "CacheGate::_config");
static_assert(offsetof(CacheGate, _sessionHandler) == 0x750, "CacheGate::_sessionHandler");
static_assert(offsetof(CacheGate, _clientManager) == 0x1750, "CacheGate::_clientManager");
static_assert(offsetof(CacheGate, _cachedList) == 0x1758, "CacheGate::_cachedList");
static_assert(offsetof(CacheGate, _cachedChannel) == 0x1790, "CacheGate::_cachedChannel");
