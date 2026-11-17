// CacheGate.obj (CacheGate PDB).
#include "CacheGate.h"

#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <new>

#include "AlertSender.h"
#include "BnsCommonConfigDefinition.h"
#include "CacheGateSessionHandler.h"
#include "ClientManager.h"
#include "Console.h"
#include "CrashHandler.h"
#include "Log.h"
#include "LogFile.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "Network.h"
#include "PacketBufferHandler.h"
#include "TimerQueue.h"

static wchar_t const CACHEGATE_FILE[] = L"CacheGate.cpp";
static wchar_t const CACHED_LIST_CONFIG_FILE[] = L"cached-list.config.xml";

CacheGate* CacheGate::_instance = nullptr;

static int const DEFAULT_DUMPTYPE = 1;                 // 0x46314 (CacheGateConfig.obj)
static int const CACHEGATE_PUBLIC_PORT_VALUE = 20800;  // 0x4611C (CacheGateConfig.obj)

// 0x596c0
XmlCfgDef const CacheGateConfig::_Def[13] = {
    {static_cast<unsigned long long>(-1), nullptr, 0, 0, nullptr, L"path"},
    {offsetof(CacheGateConfig, _rootPath), L"root-path", XmlCfgDef::CFG_DIR, 1, nullptr, L"full root path"},
    {offsetof(CacheGateConfig, _logPath), L"log-path", XmlCfgDef::CFG_DIR, 1, nullptr, L"full log path"},
    {offsetof(CacheGateConfig, _configPath), L"config-path", XmlCfgDef::CFG_DIR, 1, nullptr, L"full config path"},
    {static_cast<unsigned long long>(-1), nullptr, 0, 0, nullptr, L"system configuration"},
    {offsetof(CacheGateConfig, _workerThreadCount), L"worker-thread", XmlCfgDef::CFG_INT, 0, nullptr,
     L"0 is system recommend"},
    {offsetof(CacheGateConfig, _dumpType), L"dump-type", XmlCfgDef::CFG_INT, 0, &DEFAULT_DUMPTYPE,
     L"0: no dump, 1: minimal dump(default), 2: full dump"},
    {offsetof(CacheGateConfig, _maxCachedSessionCount), L"max-cached-session-count", XmlCfgDef::CFG_INT, 1, nullptr,
     L"max session count for connect to cached. 0 is system default."},
    {offsetof(CacheGateConfig, _maxPublicSessionCount), L"max-public-session-count", XmlCfgDef::CFG_INT, 1, nullptr,
     L"max session count for public port. 0 is system default."},
    {static_cast<unsigned long long>(-1), nullptr, 0, 0, nullptr, L"network configuration"},
    {offsetof(CacheGateConfig, _publicPort), L"public-port", XmlCfgDef::CFG_INT, 0, &CACHEGATE_PUBLIC_PORT_VALUE,
     L"daemon public access port"},
    {static_cast<unsigned long long>(-1), nullptr, 0, 0, nullptr, L"economy service configuration"},
    {offsetof(CacheGateConfig, _wid), L"wid", XmlCfgDef::CFG_INT, 0, nullptr, L"cachegate wid"},
};

// 0x4050
wchar_t const* CacheGate::ShortName()
{
    return L"cacheGate";
}

// 0x4060
wchar_t const* CacheGate::Name()
{
    return L"CacheGate";
}

// 0x4070
wchar_t const* CacheGate::ServiceName()
{
    return L"BnS CacheGate";
}

// 0x4080
wchar_t const* CacheGate::Descriptions()
{
    return L"Blade&Soul OuterWorld CacheGate";
}

// 0x4090
long CacheGate::GetTimerInterval()
{
    return 1000;
}

// 0x40a0
long CacheGate::GetTimerMaxTime()
{
    return 20;
}

// 0x4180
extern "C" int __cdecl wmain(int argc, wchar_t** argv)
{
    CacheGate daemonInstance;
    CacheGate::_instance = &daemonInstance;
    BloodDaemonMain(argc, argv);
    return 0;
}

// 0x4290
CacheGate::~CacheGate()
{
    if (_clientManager != nullptr)
    {
        _clientManager->~ClientManager();
        Memory::_Manager[2]->Free(_clientManager, CACHEGATE_FILE, 45);
    }
    // Inlined DaemonConfig free (source\DaemonConfig.cpp line 115).
    if (BnsCommonConfig::ConfigNoReload != nullptr)
        Memory::_Manager[1]->Free(BnsCommonConfig::ConfigNoReload, L"source\\DaemonConfig.cpp", 115);
    if (BnsCommonConfig::Config != nullptr)
    {
        Memory::_Manager[2]->Free(BnsCommonConfig::Config, L"..\\..\\Shared\\BnsCommonConfigDefinition.cpp", 295);
        BnsCommonConfig::Config = nullptr;
    }
    BnsCommonConfig* old = BnsCommonConfig::ConfigOlds;
    while (old != nullptr)
    {
        BnsCommonConfig* next = old->_NEXT;
        Memory::_Manager[2]->Free(old, L"..\\..\\Shared\\BnsCommonConfigDefinition.cpp", 301);
        old = next;
        BnsCommonConfig::ConfigOlds = next;
    }
}

// 0x43f0
bool CacheGate::initLog()
{
    _config = static_cast<CacheGateConfig const*>(DaemonConfig::Load(
        CacheGateConfig::_Def, 13, sizeof(CacheGateConfig), L"cachegate.config.xml", Daemon::Instance->ShortName(), false));
    if (_config == nullptr)
        return false;

    SetCurrentDirectoryW(_config->_rootPath);

    int dumpType = 261;
    int option = 3;
    int configDumpType = _config->_dumpType;
    if (configDumpType >= 0)
    {
        if (configDumpType <= 1)
        {
            option = 7;
        }
        else if (configDumpType == 2)
        {
            dumpType = 327;
            option = 7;
        }
    }
    CrashHandler::Instance->_option = option;
    CrashHandler::Instance->_dumpType = dumpType;
    CrashHandler::SetLogPath(_config->_logPath);

    void* buffer = Memory::_Manager[2]->Alloc(sizeof(LogFile), CACHEGATE_FILE, 78);
    LogFile* logFile = buffer != nullptr ? new (buffer) LogFile(_config->_logPath, 2, 0) : nullptr;  // LIFT: LTCG folded the args. initialize 0x10da5 sets _filetype = 2. logType is not read.
    Log::InitMedia(console);
    Log::InitMedia(logFile);
    return true;
}

// 0x40B0 (size 3: returns true)
bool CacheGate::setArgument(int argc, wchar_t const** argv)
{
    return true;
}

// 0x4510
bool CacheGate::initialize()
{
    // LIFT: the call (0x4535) passes only rcx = _config (+0x748). DaemonConfig::Dump (0xCA10) has the
    // name (L"cachegate config", 0xCA45) and the definitions as constants. The lift passes them.
    DaemonConfig::Dump(L"cachegate config", _config, CacheGateConfig::_Def, 13);
    if (!BnsCommonConfig::LoadBnsCommonConfig())
    {
        Log::Write(Log::LT_ERROR, CACHEGATE_FILE, 111, L"[cg], initialize, failed to initialize bns common config");
        Sleep(3000);
        return false;
    }
    BnsCommonConfig::Dump();

    if (_clientManager != nullptr)
    {
        Log::Write(Log::LT_ERROR, CACHEGATE_FILE, 117, L"== CRASH == ASSERT CRASH");
        AlertSender::Write(CACHEGATE_FILE, 117, L"== CRASH == ASSERT CRASH");
        CrashHandler::MakeCrash("CacheGate.cpp", 117, L"");
    }

    void* buffer = Memory::_Manager[2]->Alloc(sizeof(ClientManager), CACHEGATE_FILE, 119);
    _clientManager = buffer != nullptr ? new (buffer) ClientManager() : nullptr;
    if (_clientManager == nullptr)
    {
        Log::Write(Log::LT_ERROR, CACHEGATE_FILE, 121, L"[cg], failed to allocate, client manager.");
        return false;
    }

    _cachedList.Initialize();

    wchar_t cachedListConfigFileName[MAX_PATH] = {0};
    if (_wmakepath_s(cachedListConfigFileName, MAX_PATH, nullptr, _config->_configPath, CACHED_LIST_CONFIG_FILE,
                     nullptr) != 0)
    {
        Log::Write(CACHEGATE_FILE, 130, GetLastError(),
                   L"[cg], failed to make cached list config file path, configPath:%s, configFileName:%s",
                   _config->_configPath, CACHED_LIST_CONFIG_FILE);
        return false;
    }
    if (!_cachedList.LoadCachedListConfigFile(cachedListConfigFileName, false))
    {
        Log::Write(Log::LT_ERROR, CACHEGATE_FILE, 134, L"[cg], failed to load cached list config file, configFilePath:%s",
                   cachedListConfigFileName);
        _cachedList.CreateCachedListConfigFile(cachedListConfigFileName);
        return false;
    }
    if (!_clientManager->Initialize())
    {
        Log::Write(Log::LT_ERROR, CACHEGATE_FILE, 140, L"[cg], failed to initialize client manager.");
        return false;
    }
    return true;
}

// 0x4770
bool CacheGate::initNetwork()
{
    if (!Network::Initialize(FailedEventObjectHandler, _config->_workerThreadCount))
    {
        Log::Write(Log::LT_ERROR, CACHEGATE_FILE, 150, L"[cg], failed to initialize network.");
        return false;
    }

    _sessionHandler[2] = &_cachedChannel;
    TrustedPacketBufferHandler trustedHandler;
    unsigned int maxSession = _config->_maxCachedSessionCount > 0 ? _config->_maxCachedSessionCount + 1 : 0;
    // LIFT: LTCG folded the bool arguments. The calls (0x4801, 0x48C0) pass 6 of 9 PDB arguments. OpenPort stores
    // 1 at 0xD564 and 0xD568 (accept, recv). Port::Initialize stores _nagle = 0 at 0x18C0A.
    if (!Network::OpenPort(2, 0, 2, &_cachedChannel, &trustedHandler, maxSession, true, true, false))
    {
        Log::Write(Log::LT_ERROR, CACHEGATE_FILE, 165, L"[cg], cannot open cached port, port-id:%d", 2);
        return false;
    }
    CacheGate::_instance->_cachedList.MakeSessionAll();

    TrustedPacketBufferHandler cachegateHandler;
    void* buffer = Memory::_Manager[1]->Alloc(sizeof(CacheGateSessionHandler), CACHEGATE_FILE, 172);
    SessionHandler* handler = buffer != nullptr ? new (buffer) CacheGateSessionHandler() : nullptr;
    _sessionHandler[1] = handler;
    unsigned int maxPublicSession = _config->_maxPublicSessionCount > 0 ? _config->_maxPublicSessionCount + 1 : 0;
    if (!Network::OpenPort(1, static_cast<unsigned short>(_config->_publicPort), 1, handler, &cachegateHandler,
                           maxPublicSession, true, true, false))  // LIFT: bools folded, see 0x4801
    {
        Log::Write(Log::LT_ERROR, CACHEGATE_FILE, 182, L"[cg], cannot open cachegate port, %d",
                   static_cast<int>(static_cast<unsigned short>(_config->_publicPort)));
        return false;
    }
    Log::Write(Log::LT_DEBUG, CACHEGATE_FILE, 186, L"[cg], network initialize ok.");
    return true;
}

// 0x4930
void CacheGate::shutdown()
{
    Network::ClosePort(1);
    Network::ClosePort(2);
    CacheGate::_instance->_cachedList.RemoveSessionAll();
    Network::Clear();
}

// 0x4970
bool CacheGate::reload(wchar_t** argv, int argc)
{
    Log::Write(Log::LT_DEBUG, CACHEGATE_FILE, 211, L"[cg], reload start");
    wchar_t cachedListConfigFileName[MAX_PATH] = {0};
    if (_wmakepath_s(cachedListConfigFileName, MAX_PATH, nullptr, _config->_configPath, CACHED_LIST_CONFIG_FILE,
                     nullptr) != 0)
    {
        Log::Write(CACHEGATE_FILE, 216, GetLastError(),
                   L"[cg], reload fail; failed to make cached list config file path, configPath:%s, configFileName:%s",
                   _config->_configPath, CACHED_LIST_CONFIG_FILE);
    }
    else if (!_cachedList.LoadCachedListConfigFile(cachedListConfigFileName, true))
    {
        Log::Write(Log::LT_ERROR, CACHEGATE_FILE, 220,
                   L"[cg], reload fail; failed to load cached list config file, configFilePath:%s",
                   cachedListConfigFileName);
    }
    else
    {
        bool isChanged = false;
        Log::Write(Log::LT_NOTICE, CACHEGATE_FILE, 226, L"[scd], bns common config reloading...");
        if (!BnsCommonConfig::ReloadBnsCommonConfig(isChanged))
        {
            Log::Write(Log::LT_ERROR, CACHEGATE_FILE, 229, L"[cg], bns common config reload fail");
        }
        else if (isChanged)
        {
            BnsCommonConfig::Dump();
            Log::Write(Log::LT_NOTICE, CACHEGATE_FILE, 240, L"[cg], bns common config reload complete, done");
        }
        else
        {
            Log::Write(Log::LT_NOTICE, CACHEGATE_FILE, 235, L"[cg], bns common config reload complete, not changed");
        }
        Log::Write(Log::LT_DEBUG, CACHEGATE_FILE, 252, L"[cg], reload success");
    }
    return true;
}

// 0x4b40
void CacheGate::FailedEventObjectHandler(EventObject* eventObject)
{
    unsigned int id = eventObject->EventId();
    if (id != 3 && id != 5)
        Log::Write(Log::LT_DEBUG, CACHEGATE_FILE, 267, L"[cg], unknown event object id, id: %d, object: %p",
                   eventObject->EventId(), eventObject);
}

// 0x4b90
void CacheGate::PrintDependency()
{
    wprintf_s(L"packet cachegate %d.0\n", 4);
    wprintf(L"lib xmlreader %s.0\n", L"15");
    wprintf(L"config bns-common-config %d\n", 2);
}

// 0xcd80 (folded: the same code is "return true" for other functions)
bool CacheGate::onStart()
{
    return true;
}
