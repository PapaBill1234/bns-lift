// SmartCouponDaemon.obj (SmartCouponDaemon PDB). Layouts from include/pdb/SmartCouponDaemon/types.h.
#pragma once
#include <stddef.h>
#include <string.h>
#include "Daemon.h"
#include "DaemonConfig.h"
#include "Lock.h"

class EventObject;
class GameEventConfig;
class NPServiceChannelManager;
class DChannelMgr;
class JobManager;
class LogFile;
class ManagerSessionHandler;
class ManagerChannel;

class SmartCouponConfig
{
public:
    wchar_t* _rootPath;
    char* _certFile;
    wchar_t* _logPath;
    wchar_t* _configPath;
    int _workerThreadCount;
    int _gameEventWorkerThreadCount;
    int _maxDaemonSessionCount;
    int _dumpType;
    int _initJobCount;
    int _reuseWaitTime;
    int _jobHashCount;
    bool _npEnabled;
    unsigned long _npAddress;
    int _npPort;
    int _daemonListenPort;
    int _manageListenPort;
    int _serviceWid;
    bool _npRewardChangeoverEnable;

    static XmlCfgDef const _Def[23];
};
static_assert(sizeof(SmartCouponConfig) == 0x58, "sizeof SmartCouponConfig");
static_assert(offsetof(SmartCouponConfig, _serviceWid) == 0x50, "SmartCouponConfig::_serviceWid");

class SmartCouponDaemon : public Daemon
{
public:
    // LIFT: The constructor is inlined in wmain (0x14B70).
    SmartCouponDaemon() : _config(nullptr), _gameEventConfig(nullptr), _wid(0)
    {
        _npChannelMgr = nullptr;
        _daemonChannelMgr = nullptr;
        _jobMgr = nullptr;
        _logFile = nullptr;
        _managerSessionHandler = nullptr;
        _managerChannel = nullptr;
    }
    virtual ~SmartCouponDaemon();                               // 0x14C80
    virtual void PrintDependency();                             // 0x14E30
    virtual wchar_t const* ShortName();                         // 0x14A30
    virtual wchar_t const* Name();                              // 0x14A40
    virtual wchar_t const* ServiceName();                       // 0x14A50
    virtual wchar_t const* Descriptions();                      // 0x14A60
    virtual long GetTimerInterval();                            // 0x14A70
    virtual long GetTimerMaxTime();                             // 0x14A80
    virtual bool initLog();                                     // 0x14F40
    virtual bool setArgument(int argc, wchar_t const** argv);   // 0x14A90
    virtual bool initialize();                                  // 0x150E0
    virtual bool initNetwork();                                 // 0x155F0
    virtual bool onStart();                                     // 0x159E0
    virtual void shutdown();                                    // 0x15AD0
    virtual bool reload(wchar_t** argv, int argc);              // 0x15CF0
    virtual bool cooldown();                                    // 0x15F20

    static void SetManagerChannel(ManagerChannel* managerChannel);  // 0x14DF0
    static void FailedEventObjectHandler(EventObject* eventObject);  // 0x14EB0

    static SmartCouponDaemon* _instance;

    bool startNPChannel();                  // 0x15F60
    bool loadUnhandledGameEventLog();       // 0x16050
    bool loadUnhandledCouponPublication();  // 0x161A0

    SmartCouponConfig const* _config;
    GameEventConfig* _gameEventConfig;
    bool _serviceAvailable;
    unsigned short const _wid;
    NPServiceChannelManager* _npChannelMgr;
    SystemEvent _npInitialConnectEvent;
    DChannelMgr* _daemonChannelMgr;
    JobManager* _jobMgr;
    LogFile* _logFile;
    ManagerSessionHandler* _managerSessionHandler;
    ManagerChannel* _managerChannel;
    CriticalSection _managerChannelLock;
};
static_assert(sizeof(SmartCouponDaemon) == 0x7C0, "sizeof SmartCouponDaemon");
static_assert(offsetof(SmartCouponDaemon, _config) == 0x748, "SmartCouponDaemon::_config");
static_assert(offsetof(SmartCouponDaemon, _wid) == 0x75A, "SmartCouponDaemon::_wid");
static_assert(offsetof(SmartCouponDaemon, _npChannelMgr) == 0x760, "SmartCouponDaemon::_npChannelMgr");
static_assert(offsetof(SmartCouponDaemon, _logFile) == 0x780, "SmartCouponDaemon::_logFile");
static_assert(offsetof(SmartCouponDaemon, _managerChannel) == 0x790, "SmartCouponDaemon::_managerChannel");
static_assert(offsetof(SmartCouponDaemon, _managerChannelLock) == 0x798, "SmartCouponDaemon::_managerChannelLock");

unsigned long long GenerateJobid();  // 0x14B50 ❓ free function
