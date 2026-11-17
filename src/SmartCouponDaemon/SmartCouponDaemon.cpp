// SmartCouponDaemon.obj (SmartCouponDaemon PDB).
#include "SmartCouponDaemon.h"

#include <winsock2.h>
#include <windows.h>
#include <sql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wchar.h>
#include <new>

#include "AlertSender.h"
#include "BnsCommonConfigDefinition.h"
#include "Console.h"
#include "CouponGameEventConfig.h"
#include "CouponJob.h"
#include "CrashHandler.h"
#include "DaemonChannel.h"
#include "Db.h"
#include "EventNotiJob.h"
#include "GameEventWorker.h"
#include "Log.h"
#include "LogFile.h"
#include "ManagerChannel.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "NPChannel.h"
#include "Network.h"
#include "ObjectPool.h"
#include "PacketBufferHandler.h"
#include "PipeConsole.h"
#include "SendPublicationEvent.h"
#include "SmartCouponDB.h"
#include "SysInfo.h"
#include "TimerQueue.h"

static wchar_t const* const kFile = L"SmartCouponDaemon.cpp";

SmartCouponDaemon* SmartCouponDaemon::_instance = nullptr;
SmartCouponObjPoolMemoryAllocator* GObjPoolMemAlloc = nullptr;  // rva 0x84B18
ObjPoolTimer* GObjPoolTimer = nullptr;                          // rva 0x84B20
static volatile long long _seed__ = 0;                          // ❓ GenerateJobid counter

// Default values of SmartCouponConfig::_Def. The names come from the PDB (SmartCouponConfig.obj).
static int const DEFAULT_DUMPTYPE = 1;
static int const NP_PORT = 6601;
static int const DEFAULT_MANAGE_LISTEN_PORT = 32000;
static int const DEFAULT_DAEMON_LISTEN_PORT = 22000;
static int const DEFAULT_SERVICE_WORLD_ID = 1;

XmlCfgDef const SmartCouponConfig::_Def[23] = {
    {static_cast<unsigned long long>(-1), nullptr, 0, 0, nullptr, L"path"},
    {offsetof(SmartCouponConfig, _rootPath), L"root-path", XmlCfgDef::CFG_DIR, 1, nullptr, L"full root path"},
    {offsetof(SmartCouponConfig, _logPath), L"log-path", XmlCfgDef::CFG_DIR, 1, nullptr, L"full log path"},
    {offsetof(SmartCouponConfig, _configPath), L"config-path", XmlCfgDef::CFG_DIR, 1, nullptr, L"full config path"},
    {static_cast<unsigned long long>(-1), nullptr, 0, 0, nullptr, L"certification"},
    {offsetof(SmartCouponConfig, _certFile), L"cert-file", XmlCfgDef::CFG_ANSI, 1, nullptr, L"certification file path"},
    {static_cast<unsigned long long>(-1), nullptr, 0, 0, nullptr, L"system configuration"},
    {offsetof(SmartCouponConfig, _workerThreadCount), L"worker-thread", XmlCfgDef::CFG_INT, 0, nullptr,
     L"0 is system recommend"},
    {offsetof(SmartCouponConfig, _gameEventWorkerThreadCount), L"game-event-worker-thread", XmlCfgDef::CFG_INT, 0, nullptr,
     L"0 is system recommend"},
    {offsetof(SmartCouponConfig, _maxDaemonSessionCount), L"max-world", XmlCfgDef::CFG_INT, 0, nullptr,
     L"0 is default = 1000"},
    {offsetof(SmartCouponConfig, _dumpType), L"dump-type", XmlCfgDef::CFG_INT, 0, &DEFAULT_DUMPTYPE,
     L"0: no dump, 1: minimal dump(default), 2: full dump"},
    {offsetof(SmartCouponConfig, _initJobCount), L"init-job-count", XmlCfgDef::CFG_INT, 1, nullptr,
     L"job initial object pool size. 0 means no preparance"},
    {offsetof(SmartCouponConfig, _reuseWaitTime), L"wait-time-for-reuse-pool-object", XmlCfgDef::CFG_INT, 0, nullptr,
     L"msec. for debugging. 0 means pool object be reused immediately. caution, in service mode, pool object do not "
     L"wait for reuse"},
    {offsetof(SmartCouponConfig, _jobHashCount), L"job-hash-count", XmlCfgDef::CFG_INT, 0, nullptr,
     L"job hash count. 0 means system default."},
    {static_cast<unsigned long long>(-1), nullptr, 0, 0, nullptr, L"network configuration"},
    {offsetof(SmartCouponConfig, _npEnabled), L"np-enabled", XmlCfgDef::CFG_BOOL, 1, nullptr, L"work with next-platform "},
    {offsetof(SmartCouponConfig, _npAddress), L"np-address", XmlCfgDef::CFG_IP, 0, L"127.0.0.1",  /* 0x72948 text, no PDB name */
     L"next-platform\taddress"},
    {offsetof(SmartCouponConfig, _npPort), L"np-port", XmlCfgDef::CFG_INT, 0, &NP_PORT, L"next-platform access port"},
    {offsetof(SmartCouponConfig, _manageListenPort), L"manage-listen-port", XmlCfgDef::CFG_INT, 0,
     &DEFAULT_MANAGE_LISTEN_PORT, L"management listen port"},
    {offsetof(SmartCouponConfig, _daemonListenPort), L"daemon-listen-port", XmlCfgDef::CFG_INT, 0,
     &DEFAULT_DAEMON_LISTEN_PORT, L"daemon listen port"},
    {static_cast<unsigned long long>(-1), nullptr, 0, 0, nullptr, L"smart coupon service configuration"},
    {offsetof(SmartCouponConfig, _serviceWid), L"service-world-id", XmlCfgDef::CFG_INT, 1, &DEFAULT_SERVICE_WORLD_ID,
     L"service world id"},
    {offsetof(SmartCouponConfig, _npRewardChangeoverEnable), L"np-reward-changeover-enable", XmlCfgDef::CFG_BOOL, 0,
     nullptr, L"np reward changeover enable. nshop np"},
};

// 0x14a00 SystemEvent::~SystemEvent is inline in Lock.h.

// 0x14a30
wchar_t const* SmartCouponDaemon::ShortName() { return L"smartcoupond"; }

// 0x14a40
wchar_t const* SmartCouponDaemon::Name() { return L"SmartCouponDaemon"; }

// 0x14a50
wchar_t const* SmartCouponDaemon::ServiceName() { return L"BnS smartcoupond"; }

// 0x14a60
wchar_t const* SmartCouponDaemon::Descriptions() { return L"Blade&Soul SmartCoupon Daemon"; }

// 0x14a70
long SmartCouponDaemon::GetTimerInterval() { return 1000; }

// 0x14a80
long SmartCouponDaemon::GetTimerMaxTime() { return 20; }

// 0x14a90
bool SmartCouponDaemon::setArgument(int, wchar_t const**) { return false; }

// 0x14ab0
void* SmartCouponObjPoolMemoryAllocator::Alloc(unsigned long long size, wchar_t const*, int)
{
    unsigned long long const sz = _alignment * ((_alignment + size - 1) / _alignment);
    _lock.Enter();
    if (static_cast<unsigned long long>(_end - _mem) < sz)
    {
        // BUG: 0x14ab0 the rest of the old block leaks, and the VirtualAlloc result is not checked.
        _mem = static_cast<unsigned char*>(VirtualAlloc(nullptr, _systemAllocationGranularity, MEM_COMMIT | MEM_RESERVE,
                                                        PAGE_READWRITE));
        _end = _mem + _systemAllocationGranularity;
    }
    unsigned char* const ret = _mem;
    _mem += sz;
    _lock.Leave();
    return ret;
}

// 0x14b50
unsigned long long GenerateJobid()
{
    return static_cast<unsigned long long>(_InterlockedIncrement64(&_seed__));
}

// 0x14b70
extern "C" int __cdecl wmain(int argc, wchar_t** argv)
{
    SmartCouponDaemon daemon;
    SmartCouponDaemon::_instance = &daemon;
    BloodDaemonMain(argc, argv);
    return 0;
}

// 0x14c80
SmartCouponDaemon::~SmartCouponDaemon()
{
    if (_logFile != nullptr)
    {
        _logFile->~LogFile();
        Memory::_Manager[2]->Free(_logFile, kFile, 73);
        _logFile = nullptr;
    }
    if (BnsCommonConfig::ConfigNoReload != nullptr)
    {
        // BUG: 0x14c80 ConfigNoReload is not set to null after the free.
        Memory::_Manager[1]->Free(BnsCommonConfig::ConfigNoReload, L"source\\DaemonConfig.cpp", 115);
    }
    if (BnsCommonConfig::Config != nullptr)
    {
        Memory::_Manager[2]->Free(BnsCommonConfig::Config, L"..\\Shared\\BnsCommonConfigDefinition.cpp", 295);
        BnsCommonConfig::Config = nullptr;
    }
    while (BnsCommonConfig::ConfigOlds != nullptr)
    {
        BnsCommonConfig* const next = BnsCommonConfig::ConfigOlds->_NEXT;
        Memory::_Manager[2]->Free(BnsCommonConfig::ConfigOlds, L"..\\Shared\\BnsCommonConfigDefinition.cpp", 301);
        BnsCommonConfig::ConfigOlds = next;
    }
    // The member destructors close _managerChannelLock and _npInitialConnectEvent.
}

// 0x14df0
void SmartCouponDaemon::SetManagerChannel(ManagerChannel* managerChannel)
{
    _instance->_managerChannelLock.Enter();
    _instance->_managerChannel = managerChannel;
    _instance->_managerChannelLock.Leave();
}

// 0x14e30
void SmartCouponDaemon::PrintDependency()
{
    wprintf(L"packet smartcoupon-game %d.0\n", 1);
    wprintf(L"packet smartcouponmanager %d.0\n", 2);
    wprintf(L"lib xmlreader %s.0\n", L"15");
    wprintf(L"lib stsmsglib %s.0\n", L"119");
    wprintf(L"security cert %d.0\n", 6);
    wprintf(L"config bns-common-config %d\n", 2);
}

// 0x14eb0
void SmartCouponDaemon::FailedEventObjectHandler(EventObject* eventObject)
{
    if (eventObject == nullptr)
    {
        Log::Write(Log::LT_ERROR, kFile, 130, L"== CRASH == [scd], invalid parameter, eventObject:0x%p", nullptr);
        AlertSender::Write(kFile, 130, L"== CRASH == [scd], invalid parameter, eventObject:0x%p", nullptr);
        return;
    }
    eventObject->EventId();  // ❓ the switch on the id has no case
    Log::Write(Log::LT_DEBUG, kFile, 143, L"[scd], unknown event object id, id: %d, object: %p", eventObject->EventId(),
               eventObject);
}

// 0x14f40
bool SmartCouponDaemon::initLog()
{
    _config = static_cast<SmartCouponConfig const*>(DaemonConfig::Load(
        SmartCouponConfig::_Def, 23, sizeof(SmartCouponConfig), L"smartcoupond.config.xml", Daemon::Instance->ShortName(),
        false));
    if (_config == nullptr)
    {
        Log::Write(Log::LT_ERROR, kFile, 150, L"[scd], failed to load config, config:0x%p", nullptr);
        return false;
    }
    SetCurrentDirectoryW(_config->_rootPath);

    int dumpType = 261;
    if (_config->_dumpType < 0)
        return false;
    if (_config->_dumpType == 2)
        dumpType = 327;
    else if (_config->_dumpType > 2)
        return false;
    CrashHandler::Instance->_option = 7;
    CrashHandler::Instance->_dumpType = dumpType;
    CrashHandler::SetLogPath(_config->_logPath);

    // BUG: 0x14f40 the result of Alloc is not checked.
    void* const buffer = Memory::_Manager[2]->Alloc(sizeof(LogFile), kFile, 177);
    _logFile = new (buffer) LogFile(_config->_logPath, 1, 0);  // ❓ fileType and logType
    // ❓ _logFile->_enable[2] = false; the _enable member is not in LogFile.h.

    if (!Log::InitMedia(console))
    {
        Log::Write(Log::LT_ERROR, kFile, 188, L"[scd], failed to initialize console media");
        return false;
    }
    if (!Log::InitMedia(_logFile))
    {
        Log::Write(Log::LT_ERROR, kFile, 192, L"[scd], failed to initialize log file media");
        return false;
    }
    if (_config->_workerThreadCount >= 0 && _config->_gameEventWorkerThreadCount >= 0 && _config->_serviceWid > 0)
        return true;
    Log::Write(Log::LT_ERROR, kFile, 197, L"[scd], invalid configuration");
    return false;
}

// 0x150e0
bool SmartCouponDaemon::initialize()
{
    char buffer[1000];
    char dsn[1024];
    wchar_t wdsn[1024];
    FILE* fp = nullptr;
    _time64(nullptr);

    int err = 0;
    if (_config->_certFile == nullptr)
        err = 2;
    else if (fopen_s(&fp, _config->_certFile, "rb") != 0 || fp == nullptr ||
             static_cast<long long>(fread(buffer, 1, sizeof(buffer), fp)) <= 0)
        err = 3;
    if (err != 0)
    {
        // BUG: 0x150e0 null dereference when err is 2 (certFile is null). The fp is not closed when err is 3.
        memset(_config->_certFile, 0, strlen(_config->_certFile));
        Log::Write(Log::LT_ERROR, kFile, 222, L"cannot execute, error:%d", err);
        return false;
    }
    fclose(fp);
    wdsn[1023] = 0;
    MultiByteToWideChar(CP_ACP, 0, buffer, -1, wdsn, 1023);
    memset(dsn, 0, sizeof(dsn));

    if (Daemon::Instance->publicAddress == 0)
    {
        Daemon::Instance->publicAddress = Daemon::Instance->internalAddress;
        wcsncpy(Daemon::Instance->publicAddrString, Daemon::Instance->internalAddrString, 20);
    }
    const_cast<unsigned short&>(_wid) = static_cast<unsigned short>(_config->_serviceWid);
    DaemonConfig::Dump(L"config", _config, SmartCouponConfig::_Def, 23);

    if (!BnsCommonConfig::LoadBnsCommonConfig())
    {
        Log::Write(Log::LT_ERROR, kFile, 243, L"[scd], initialize, failed to initialize bns common config");
        Sleep(3000);
        return false;
    }
    BnsCommonConfig::Dump();

    void* mem = Memory::_Manager[1]->Alloc(sizeof(SmartCouponObjPoolMemoryAllocator), kFile, 252);
    GObjPoolMemAlloc = mem ? new (mem) SmartCouponObjPoolMemoryAllocator(SysInfo::_Granularity, 16) : nullptr;
    mem = Memory::_Manager[2]->Alloc(sizeof(ObjPoolTimer), kFile, 253);
    GObjPoolTimer = mem ? new (mem) ObjPoolTimer() : nullptr;

    {
        // The pool reads the vtable of a sample object. The original (0x153E9) builds it on the stack
        // and never calls its destructor. A destructor call logs "ref:1, tag:0xfa" (RefCntObject.h,129).
        alignas(EventNotiJob) unsigned char tmpStorage[sizeof(EventNotiJob)];
        EventNotiJob* tmp = new (tmpStorage) EventNotiJob();
        EventNotiJob::_pool.Initialize(*reinterpret_cast<void**>(tmp), _config->_initJobCount,
                                       _config->_reuseWaitTime);
        GObjPoolTimer->Add(&EventNotiJob::_pool);
    }

    mem = Memory::_Manager[2]->Alloc(sizeof(JobManager), kFile, 261);
    _jobMgr = mem ? new (mem) JobManager(GenerateJobid) : nullptr;
    int hashCount = _config->_jobHashCount;
    if (hashCount <= 0)
        hashCount = 2 * SysInfo::_ProcessorCount;
    if (!_jobMgr->Initialize(hashCount))
    {
        Log::Write(Log::LT_ERROR, kFile, 263, L"[scd], initialize job manager fail");
        return false;
    }

    if (!Db::Initialize(1, wdsn))
    {
        Log::Write(Log::LT_ERROR, kFile, 270, L"[scd], failed to initialize db, dbId:%d", 1);
        return false;
    }

    mem = Memory::_Manager[2]->Alloc(sizeof(GameEventConfig), kFile, 277);
    _gameEventConfig = mem ? new (mem) GameEventConfig() : nullptr;
    if (!_gameEventConfig->Load(_config->_configPath))
        return false;
    _gameEventConfig->Dump();

    if (_config->_npEnabled &&
        !NPChannel::Setup(BnsCommonConfig::Config->_npProgramId, BnsCommonConfig::Config->_npGameCode))
    {
        Log::Write(Log::LT_ERROR, kFile, 293, L"[scd], init np channel failed");
        return false;
    }

    mem = Memory::_Manager[2]->Alloc(sizeof(NPServiceChannelManager), kFile, 298);
    _npChannelMgr = mem ? new (mem) NPServiceChannelManager() : nullptr;

    GameEventManager::Initialize(FailedEventObjectHandler, Daemon::Instance->threadManager,
                                 _config->_gameEventWorkerThreadCount);  // ❓ handler argument
    return true;
}

// 0x155f0
bool SmartCouponDaemon::initNetwork()
{
    if (!Network::Initialize(FailedEventObjectHandler, _config->_workerThreadCount))  // ❓ handler argument
    {
        Log::Write(Log::LT_ERROR, kFile, 312, L"[scd], failed to initialize network");
        return false;
    }

    if (_config->_npEnabled)
    {
        RawPacketBufferHandler raw;
        if (!Network::OpenPort(1, 0, NPChannel::_sessionHandler, &raw, 0))
        {
            Log::Write(Log::LT_ERROR, kFile, 333, L"[scd], setup np port fail");
            return false;
        }
    }

    TrustedPacketBufferHandler pbh;
    void* mem = Memory::_Manager[1]->Alloc(sizeof(DChannelMgr), kFile, 344);
    _daemonChannelMgr = mem ? new (mem) DChannelMgr() : nullptr;
    Log::Write(Log::LT_DEBUG, L"DaemonChannel.cpp", 39, L"[ch-mgr], daemon session manager initialized");

    wchar_t name[260] = {0};
    if (_wmakepath_s(name, 260, nullptr, _config->_configPath, L"gamed-list.config.xml", nullptr) != 0)
    {
        Log::Write(kFile, 353, static_cast<long>(GetLastError()),
                   L"[scd], failed to make world config file path, configPath:%s, configFileName:%s",
                   _config->_configPath, L"gamed-list.config.xml");
        return false;
    }
    if (!_daemonChannelMgr->SetupDaemonListFromXml(name))
    {
        Log::Write(Log::LT_ERROR, kFile, 358, L"[scd], setup world list fail, worldConfigFileName:%s", name);
        DChannelMgr::CreateDaemonListXml(name);
        return false;
    }

    unsigned int const maxSession = _config->_maxDaemonSessionCount ? _config->_maxDaemonSessionCount + 1 : 0;
    if (!Network::OpenPort(2, static_cast<unsigned short>(_config->_daemonListenPort), _daemonChannelMgr, &pbh,
                           maxSession))
    {
        Log::Write(Log::LT_ERROR, kFile, 373, L"[scd], failed to open gamed listen port, portId:%u, portNumber:%u", 2,
                   _config->_daemonListenPort);
        return false;
    }

    mem = Memory::_Manager[1]->Alloc(sizeof(ManagerSessionHandler), kFile, 377);
    _managerSessionHandler = mem ? new (mem) ManagerSessionHandler() : nullptr;
    if (!Network::OpenPort(3, static_cast<unsigned short>(_config->_manageListenPort), _managerSessionHandler, &pbh,
                           0))
    {
        Log::Write(Log::LT_ERROR, kFile, 388, L"[craftd], open manager port fail");
        return false;
    }
    return true;
}

// 0x159e0
bool SmartCouponDaemon::onStart()
{
    ObjPoolTimer::Start(1000);  // LTCG put 1000 in the body of 0x1940
    if (_config->_npEnabled && !startNPChannel())
    {
        Log::Write(Log::LT_ERROR, kFile, 407, L"[scd], start np fail");
        return false;
    }
    if (!loadUnhandledCouponPublication() || !loadUnhandledGameEventLog())
        return false;
    if (!Network::OpenPort(2))
    {
        Log::Write(Log::LT_ERROR, kFile, 420, L"[scd], open gamed port fail");
        return false;
    }
    if (!Network::OpenPort(3))
    {
        Log::Write(Log::LT_ERROR, kFile, 425, L"[scd], open managed port fail");
        return false;
    }
    Log::Write(Log::LT_NOTICE, kFile, 430, L"[scd], open managed port ok");
    _instance->_serviceAvailable = true;
    if (pipeConsole != nullptr)
        pipeConsole->SetDetectFrozenThread(true, 0);  // ❓ arguments
    return true;
}

// 0x15ad0
void SmartCouponDaemon::shutdown()
{
    Network::ClosePort(2);
    if (_config->_npEnabled)
        Network::ClosePort(1);
    Network::ClosePort(3);
    Network::Clear();
    GameEventManager::Clear();
    NPChannel::Cleanup();

    if (_managerSessionHandler != nullptr)
    {
        _managerSessionHandler->~ManagerSessionHandler();
        Memory::_Manager[1]->Free(_managerSessionHandler, kFile, 461);
        _managerSessionHandler = nullptr;
    }
    if (_daemonChannelMgr != nullptr)
    {
        _daemonChannelMgr->Finalize();
        _daemonChannelMgr->~DChannelMgr();
        Memory::_Manager[1]->Free(_daemonChannelMgr, kFile, 468);
        _daemonChannelMgr = nullptr;
    }
    if (_gameEventConfig != nullptr)
    {
        _gameEventConfig->~GameEventConfig();
        Memory::_Manager[2]->Free(_gameEventConfig, kFile, 474);
        _gameEventConfig = nullptr;
    }
    if (_jobMgr != nullptr)
    {
        _jobMgr->Clear();
        _jobMgr->~JobManager();
        Memory::_Manager[2]->Free(_jobMgr, kFile, 481);
        _jobMgr = nullptr;
    }
    if (GObjPoolTimer != nullptr)
    {
        if (GObjPoolTimer->_run)
        {
            GObjPoolTimer->_run = false;
            Daemon::Instance->GlobalTimerQueue->Remove(GObjPoolTimer);  // ❓
            Log::Write(Log::LT_DEBUG, L"..\\LobbyDaemon\\ObjectPool.cpp", 372,
                       L"[objpool], objpool timer stopped, uptime:%I64d",
                       static_cast<long long>(GetTickCount64()) - Daemon::Instance->StartSystemTick64);
        }
        GObjPoolTimer->removeReferenceCount(kFile, 489);
    }
    EventNotiJob::_pool.Finalize();

    if (Db::EnvHandle != nullptr)
    {
        SQLFreeHandle(SQL_HANDLE_ENV, Db::EnvHandle);
        Db::EnvHandle = nullptr;
    }
    for (unsigned int i = 1; i <= 40; ++i)
    {
        if (Db::Instance[i] != nullptr)
            Db::Clear(i);
    }
}

// 0x15cf0
bool SmartCouponDaemon::reload(wchar_t** argv, int argc)
{
    if (argc <= 0)
    {
        Log::Write(Log::LT_ERROR, kFile, 501, L"reload fail; invalid argument, argv:%p, argc:%d", argv, argc);
        return true;
    }
    Log::Write(Log::LT_DEBUG, kFile, 505, L"reload start");
    if (argc == 1)
    {
        wchar_t name[260] = {0};
        errno_t const errcode =
            _wmakepath_s(name, 260, nullptr, _config->_configPath, L"gamed-list.config.xml", nullptr);
        if (errcode != 0)
        {
            Log::Write(kFile, 512, errcode,
                       L"failed to make gamed config file path, configPath:%s, configFileName:%s",
                       _config->_configPath, L"gamed-list.config.xml");
            return true;
        }
        if (!_daemonChannelMgr->SetupDaemonListFromXml(name))
        {
            Log::Write(Log::LT_ERROR, kFile, 517, L"setup gamed list fail, gamedConfigFileName:%s", name);
            return true;
        }
        if (!_gameEventConfig->Load(_config->_configPath))
            return false;
    }

    bool changed = false;
    Log::Write(Log::LT_NOTICE, kFile, 529, L"[scd], bns common config reloading...");
    if (BnsCommonConfig::ReloadBnsCommonConfig(changed))
    {
        if (changed)
        {
            BnsCommonConfig::Dump();
            Log::Write(Log::LT_NOTICE, kFile, 543, L"[scd], bns common config reload complete, done");
        }
        else
        {
            Log::Write(Log::LT_NOTICE, kFile, 538, L"[scd], bns common config reload complete, not changed");
        }
    }
    else
    {
        Log::Write(Log::LT_ERROR, kFile, 532, L"[scd], bns common config reload fail");
    }
    Log::Write(Log::LT_DEBUG, kFile, 547, L"reload(%s) success", argv[0]);
    return true;
}

// 0x15f20
bool SmartCouponDaemon::cooldown()
{
    _instance->_serviceAvailable = false;
    Log::Write(Log::LT_NOTICE, kFile, 554, L"cooldowned");
    return true;
}

// 0x15f60
bool SmartCouponDaemon::startNPChannel()
{
    if (!Network::OpenPort(1))
    {
        Log::Write(Log::LT_ERROR, kFile, 562, L"start np channel fail; open np port fail");
        return false;
    }
    _npInitialConnectEvent.Event = CreateEventW(nullptr, FALSE, FALSE, nullptr);
    if (_npChannelMgr == nullptr)
    {
        Log::Write(Log::LT_ERROR, kFile, 570, L"start np channel fail; np channel manager is null");
        return false;
    }
    if (!_npChannelMgr->Initialize(1, _config->_npAddress, static_cast<unsigned short>(_config->_npPort), 5))
    {
        Log::Write(Log::LT_ERROR, kFile, 575,
                   L"[scd], start np channel fail; initialize np service channel manager fail");
        return false;
    }
    if (_npInitialConnectEvent.Event != nullptr && WaitForSingleObject(_npInitialConnectEvent.Event, 6000) == 0)
    {
        Log::Write(Log::LT_NOTICE, kFile, 584, L"[scd], start np channel ok");
        return true;
    }
    Log::Write(Log::LT_ERROR, kFile, 580, L"[scd], start np channel fail; wait initiali connect fail");
    return false;
}

// 0x16050
bool SmartCouponDaemon::loadUnhandledGameEventLog()
{
    Log::Write(Log::LT_DEBUG, kFile, 590, L"load unhandled game-event-log");
    RetrieveEventLogContext context(128);
    int dbRetValue = 0;
    if (!SmartCouponDB::LoadGameEventLogList(&dbRetValue, &context))
    {
        Log::Write(Log::LT_ERROR, kFile, 596, L"failed to load GameEventLogList, dbRetValue:%d", dbRetValue);
        return false;
    }
    Log::Write(Log::LT_DEBUG, kFile, 600, L"load unhandled game-event-log, count:%d", context._count);
    if (context._count <= 0)
        return true;
    return GameEventManager::PostGameEventLogList(&context);
}

// 0x161a0
bool SmartCouponDaemon::loadUnhandledCouponPublication()
{
    Log::Write(Log::LT_DEBUG, kFile, 610, L"load unhandled coupon-publication");
    RetrievePublicationContext context(128);
    int dbRetValue = 0;
    if (!SmartCouponDB::LoadCouponPublicationList(&dbRetValue, &context))
    {
        Log::Write(Log::LT_ERROR, kFile, 616, L"failed to load coupon-publication-list, dbRetValue:%d", dbRetValue);
        return false;
    }
    Log::Write(Log::LT_DEBUG, kFile, 620, L"load unhandled coupon-publication, count:%d", context._count);
    for (int i = 0; i < context._count; ++i)
    {
        PublicationInfo const* const info = context.GetPublicationInfo(i);
        if (info == nullptr)
        {
            Log::Write(Log::LT_ERROR, kFile, 627, L"unhandled coupon-publication, invalid info, index:%d, count:%d", i,
                       context._count);
            continue;
        }
        void* const mem = Memory::_Manager[2]->Alloc(sizeof(SendPublicationEvent), kFile, 631);
        SendPublicationEvent* const ev =
            mem ? new (mem) SendPublicationEvent(info->publicationId, info->gameAccountId, info->couponEventId) : nullptr;
        // BUG: 0x161a0 ev is not checked for null before the post.
        PostQueuedCompletionStatus(Network::iocpHandle(), 0, reinterpret_cast<ULONG_PTR>(ev), nullptr);
        // BUG: 0x161a0 ev is read after the post. A worker can free it first.
        unsigned char const* const guid = ev->_gameAccountId.guid;
        Log::Write(Log::LT_DEBUG, kFile, 634,
                   L"post publication event, publication-id:%I64d, "
                   L"acc:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, coupon-event-id:%d",
                   ev->_publicationId, *reinterpret_cast<unsigned int const*>(guid),
                   *reinterpret_cast<unsigned short const*>(guid + 4),
                   *reinterpret_cast<unsigned short const*>(guid + 6), guid[8], guid[9], guid[10], guid[11], guid[12],
                   guid[13], guid[14], guid[15], ev->_couponEventId);
    }
    return true;
}
