// PostOfficeDaemon.obj (PostOfficeDaemon PDB).
#include "PostOfficeDaemon.h"

#include <winsock2.h>
#include <windows.h>
#include <sql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wchar.h>
#include <new>

#include "AgentChannel.h"
#include "AlertSender.h"
#include "BnsCommonConfigDefinition.h"
#include "CacheGateChannel.h"
#include "CachedWatchdog.h"
#include "Console.h"
#include "CrashHandler.h"
#include "Db.h"
#include "Log.h"
#include "LogFile.h"
#include "ManagementSessionHandler.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "Network.h"
#include "PacketBufferHandler.h"
#include "PipeConsole.h"
#include "PostContext.h"
#include "PostOfficeDB.h"
#include "RelayContext.h"
#include "RelayTimeContext.h"
#include "RelayTimeoutChecker.h"
#include "TimerQueue.h"
#include "UnsentPostChecker.h"
#include "UnsentPostContext.h"
#include "WorldChannel.h"
#include "WorldConfig.h"

static wchar_t const* const kFile = L"PostOfficeDaemon.cpp";
static wchar_t const* const MODULE_NAME = L"postofficed";  // PDB MODULE_NAME

PostOfficeDaemon* PostOfficeDaemon::_instance = nullptr;

// Default values of PostOfficeConfig::_Def. The names come from the PDB (PostOfficeConfig.obj).
static int const DEFAULT_DUMPTYPE = 2;
static int const DEFAULT_RELAY_TIMEOUT_INTERVAL = 15;
static int const DEFAULT_PING_INTERVAL = 60;
static int const DEFAULT_DELIVERY_RETRY_INTERVAL = 5;
static int const DEFAULT_AGENT_LISTEN_PORT = 20500;
static int const DEFAULT_WORLD_LISTEN_PORT = 20501;
static int const DEFAULT_MANAGE_PORT = 30500;
static wchar_t const* const LOOPBACK_ADDRESS = L"127.0.0.1";  // 0x6e608; the XML reader reads a CFG_IP default as text
static int const DEFAULT_CACHEGATE_LISTEN_PORT = 20800;
static int const DEFAULT_SERVICE_WORLD_ID = 1010;

// 0x97ab0
XmlCfgDef const PostOfficeConfig::_Def[23] = {
    {static_cast<unsigned long long>(-1), nullptr, 0, 0, nullptr, L"path"},
    {offsetof(PostOfficeConfig, _rootPath), L"root-path", XmlCfgDef::CFG_DIR, 1, nullptr, L"full root path"},
    {offsetof(PostOfficeConfig, _logPath), L"log-path", XmlCfgDef::CFG_DIR, 1, nullptr, L"full log path"},
    {offsetof(PostOfficeConfig, _configPath), L"config-path", XmlCfgDef::CFG_DIR, 1, nullptr, L"full config path"},
    {static_cast<unsigned long long>(-1), nullptr, 0, 0, nullptr, L"certification"},
    {offsetof(PostOfficeConfig, _certFile), L"cert-file", XmlCfgDef::CFG_ANSI, 1, nullptr, L"certification file path"},
    {static_cast<unsigned long long>(-1), nullptr, 0, 0, nullptr, L"system configuration"},
    {offsetof(PostOfficeConfig, _workerThreadCount), L"worker-thread", XmlCfgDef::CFG_INT, 0, nullptr,
     L"0 is system recommend"},
    {offsetof(PostOfficeConfig, _maxAgentSessionCount), L"max-agent-session-count", XmlCfgDef::CFG_INT, 0, nullptr,
     L"0 is default"},
    {offsetof(PostOfficeConfig, _maxWorldSessionCount), L"max-world-session-count", XmlCfgDef::CFG_INT, 0, nullptr,
     L"0 is default"},
    {offsetof(PostOfficeConfig, _dumpType), L"dump-type", XmlCfgDef::CFG_INT, 0, &DEFAULT_DUMPTYPE,
     L"0: no dump, 1: minimal dump(default), 2: full dump"},
    {offsetof(PostOfficeConfig, _relayTimeoutInterval), L"relay-timeout-interval", XmlCfgDef::CFG_INT, 0,
     &DEFAULT_RELAY_TIMEOUT_INTERVAL, L"relay timeout interval(sec). default = 15"},  // LIFT: full text in .rdata 0x7fec0
    {offsetof(PostOfficeConfig, _pingInterval), L"ping-interval", XmlCfgDef::CFG_INT, 0, &DEFAULT_PING_INTERVAL,
     L"ping interval with cached(sec). default = 60"},
    {offsetof(PostOfficeConfig, _deliveryRetryInterval), L"delivery-retry-interval", XmlCfgDef::CFG_INT, 0,
     &DEFAULT_DELIVERY_RETRY_INTERVAL, L"delivery retry interval(sec). default = 5"},  // LIFT: full text in .rdata 0x7fe00
    {static_cast<unsigned long long>(-1), nullptr, 0, 0, nullptr, L"network configuration"},
    {offsetof(PostOfficeConfig, _agentListenPort), L"agent-listen-port", XmlCfgDef::CFG_INT, 0, &DEFAULT_AGENT_LISTEN_PORT,
     L"agent listen port"},
    {offsetof(PostOfficeConfig, _worldListenPort), L"world-listen-port", XmlCfgDef::CFG_INT, 0, &DEFAULT_WORLD_LISTEN_PORT,
     L"world listen port"},
    {offsetof(PostOfficeConfig, _managePort), L"manage-port", XmlCfgDef::CFG_INT, 0, &DEFAULT_MANAGE_PORT,
     L"daemon debug port"},
    {static_cast<unsigned long long>(-1), nullptr, 0, 0, nullptr, L"cachegate configuration"},
    {offsetof(PostOfficeConfig, _cachegateIpAddr), L"cachegate-ip-address", XmlCfgDef::CFG_IP, 0, LOOPBACK_ADDRESS,
     L"cachegate ip address"},
    {offsetof(PostOfficeConfig, _cachegateListenPort), L"cachegate_listen-port", XmlCfgDef::CFG_INT, 0,
     &DEFAULT_CACHEGATE_LISTEN_PORT, L"cachegate listen port"},
    {static_cast<unsigned long long>(-1), nullptr, 0, 0, nullptr, L"economy service configuration"},
    {offsetof(PostOfficeConfig, _serviceWid), L"service-world-id", XmlCfgDef::CFG_INT, 1, &DEFAULT_SERVICE_WORLD_ID,
     L"service world id"},
};

// 0x12bb0
wchar_t const* PostOfficeDaemon::ShortName()
{
    return L"postofficed";
}

// 0x12bc0
wchar_t const* PostOfficeDaemon::Name()
{
    return L"PostOfficeDaemon";
}

// 0x12bd0
wchar_t const* PostOfficeDaemon::ServiceName()
{
    return L"BnS postofficed";
}

// 0x12be0
wchar_t const* PostOfficeDaemon::Descriptions()
{
    return L"Blade&Soul PostOffice Daemon";
}

// 0x12bf0
long PostOfficeDaemon::GetTimerInterval()
{
    return 1000;
}

// 0x12c00
long PostOfficeDaemon::GetTimerMaxTime()
{
    return 20;
}

// 0x12c10
bool PostOfficeDaemon::setArgument(int /*argc*/, wchar_t const** /*argv*/)
{
    return false;
}

// 0x12ca0
extern "C" int __cdecl wmain(int argc, wchar_t** argv)
{
    PostOfficeDaemon daemonInstance;
    PostOfficeDaemon::_instance = &daemonInstance;
    BloodDaemonMain(argc, argv);
    return 0;
}

// 0x12dd0
PostOfficeDaemon::~PostOfficeDaemon()
{
    if (_config != nullptr)
    {
        Memory::_Manager[1]->Free(const_cast<PostOfficeConfig*>(_config), L"source\\DaemonConfig.cpp", 115);
        _config = nullptr;
    }
    // BUG: 0x12dd0 ConfigNoReload is freed but not set to null.
    if (BnsCommonConfig::ConfigNoReload != nullptr)
        Memory::_Manager[1]->Free(BnsCommonConfig::ConfigNoReload, L"source\\DaemonConfig.cpp", 115);
    if (BnsCommonConfig::Config != nullptr)
    {
        Memory::_Manager[2]->Free(BnsCommonConfig::Config, L"..\\..\\Shared\\BnsCommonConfigDefinition.cpp", 295);
        BnsCommonConfig::Config = nullptr;
    }
    BnsCommonConfig* config = BnsCommonConfig::ConfigOlds;
    if (config != nullptr)
    {
        do
        {
            BnsCommonConfig* const next = config->_NEXT;
            Memory::_Manager[2]->Free(config, L"..\\..\\Shared\\BnsCommonConfigDefinition.cpp", 301);
            config = next;
            BnsCommonConfig::ConfigOlds = next;
        } while (config != nullptr);
    }
    for (int i = 0; i < 25; ++i)
    {
        SessionHandler* const handler = _sessionHandler[i];
        if (handler != nullptr)
        {
            handler->~SessionHandler();
            Memory::_Manager[1]->Free(handler, kFile, 80);
        }
    }
}

// 0x12f50
void PostOfficeDaemon::PrintDependency()
{
    wprintf(L"packet postoffice %d.0\n", 15);
    wprintf(L"packet postoffice-service %d.0\n", 16);
    wprintf(L"packet cachegate %d.0\n", 4);
    wprintf(L"packet cache-economy %d.0\n", 15);
    wprintf(L"packet economy-common %d.0\n", 10);
    wprintf(L"lib xmlreader %s.0\n", L"15");
    wprintf(L"config bns-common-config %d\n", 2);
}

// 0x12fe0
void PostOfficeDaemon::FailedEventObjectHandler(EventObject* eventObject)
{
    if (eventObject == nullptr)
    {
        Log::Write(Log::LT_ERROR, kFile, 138, L"== CRASH == [%s], %s; invalid parameter, eventObject:0x%p", MODULE_NAME,
                   L"PostOfficeDaemon::FailedEventObjectHandler", nullptr);
        AlertSender::Write(kFile, 138, L"== CRASH == [%s], %s; invalid parameter, eventObject:0x%p", MODULE_NAME,
                           L"PostOfficeDaemon::FailedEventObjectHandler", nullptr);
        return;
    }
    unsigned int const eventId = eventObject->EventId();
    if (eventId != 3 && eventId != 5)
    {
        Log::Write(Log::LT_ERROR, kFile, 149, L"[%s], %s; unknown event object id, id:%u, object:0x%p", MODULE_NAME,
                   L"PostOfficeDaemon::FailedEventObjectHandler", eventObject->EventId(), eventObject);
    }
}

// 0x130c0
bool PostOfficeDaemon::initLog()
{
    _config = static_cast<PostOfficeConfig const*>(DaemonConfig::Load(
        PostOfficeConfig::_Def, 23, sizeof(PostOfficeConfig), L"postofficed.config.xml", Daemon::Instance->ShortName(),
        false));
    if (_config == nullptr)
    {
        Log::Write(Log::LT_ERROR, kFile, 157, L"[%s], %s; failed to load config, config:0x%p", MODULE_NAME,
                   L"PostOfficeDaemon::initLog", nullptr);
        return false;
    }
    SetCurrentDirectoryW(_config->_rootPath);
    int dumpType = 261;
    if (_config->_dumpType < 0)
        return false;
    if (_config->_dumpType > 1)
    {
        if (_config->_dumpType != 2)
            return false;
        dumpType = 327;
    }
    CrashHandler::Instance->_option = 7;
    CrashHandler::Instance->_dumpType = dumpType;
    CrashHandler::SetLogPath(_config->_logPath);

    void* const buffer = Memory::_Manager[2]->Alloc(sizeof(LogFile), kFile, 183);
    LogFile* const logFile = buffer ? new (buffer) LogFile(_config->_logPath, 2, 0) : nullptr;  // LIFT: LTCG folded the args. initialize 0x2d935 sets _filetype = 2. logType is not read.
    logFile->_enable[2] = false;  // LogMedia::_enable +104 (PDB). The binary writes byte [rbx+6Ah] = 0 (0x131fa).
    // BUG: 0x130c0 the binary writes _enable[2] with no null check after the alloc.

    if (!Log::InitMedia(console))
    {
        Log::Write(Log::LT_ERROR, kFile, 197, L"[%s], %s; failed to initialize console media", MODULE_NAME,
                   L"PostOfficeDaemon::initLog");
        return false;
    }
    if (!Log::InitMedia(logFile))
    {
        Log::Write(Log::LT_ERROR, kFile, 201, L"[%s], %s; failed to initialize log file media", MODULE_NAME,
                   L"PostOfficeDaemon::initLog");
        return false;
    }
    if (_config->_workerThreadCount < 0 || _config->_maxAgentSessionCount < 0 || _config->_maxWorldSessionCount < 0 ||
        _config->_relayTimeoutInterval < 0 || _config->_pingInterval <= 0 || _config->_deliveryRetryInterval <= 0 ||
        _config->_serviceWid == 0)
    {
        Log::Write(Log::LT_ERROR, kFile, 206, L"[%s], %s; invalid configuration", MODULE_NAME, L"PostOfficeDaemon::initLog");
        return false;
    }
    return true;
}

// 0x132b0
bool PostOfficeDaemon::initialize()
{
    wchar_t dsn[1024] = {0};
    char certification[1024] = {0};
    char buffer[1008];  // LIFT: frame +1120 to +2128 (next local), 0x132b0
    FILE* fp = nullptr;
    int error;

    char* const certFile = _config->_certFile;
    _time64(nullptr);
    if (certFile == nullptr)
    {
        error = 2;
    }
    else if (fopen_s(&fp, certFile, "rb") != 0 || fp == nullptr ||  // LIFT: mode "rb" at .rdata 0x8cf40 (0x13356)
             static_cast<int>(fread(buffer, 1, 1000, fp)) <= 0)
    {
        error = 3;  // BUG: 0x132b0 fp is not closed when fread fails.
    }
    else
    {
        fclose(fp);
        dsn[1023] = L'\0';
        // BUG: 0x132b0 buffer is not null-terminated before the conversion.
        MultiByteToWideChar(CP_ACP, 0, buffer, -1, dsn, 1023);
        memset(certification, 0, sizeof(certification));
        if (!Db::Initialize(1, dsn))
        {
            Log::Write(Log::LT_ERROR, kFile, 256, L"[%s], %s; failed to initialize db, dbId:%d", MODULE_NAME,
                       L"PostOfficeDaemon::initialize", 1);
            return false;
        }
        Log::Write(Log::LT_NOTICE, kFile, 265, L"[%s], %s; daemon initialization success", MODULE_NAME,
                   L"PostOfficeDaemon::initialize");
        return true;
    }

    PostOfficeConfig* const config = const_cast<PostOfficeConfig*>(_config);
    memset(config->_certFile, 0, strlen(config->_certFile));  // BUG: 0x132b0 null dereference when error is 2.
    config->_certFile = nullptr;
    Log::Write(Log::LT_ERROR, kFile, 229, L"[%s], %s; cannot execute, error:%d", MODULE_NAME, L"PostOfficeDaemon::initialize",
               error);
    return false;
}

// 0x135e0
bool PostOfficeDaemon::initNetwork()
{
    if (!Network::Initialize(&PostOfficeDaemon::FailedEventObjectHandler, _config->_workerThreadCount))
    {
        Log::Write(Log::LT_ERROR, kFile, 273, L"[%s], %s; failed to initialize network", MODULE_NAME,
                   L"PostOfficeDaemon::initNetwork");
        return false;
    }
    if (!initWorldConfigDependencyManager() || !initChannelManager(Network::Instance->_workerThreadCount))
        return false;

    TrustedPacketBufferHandler trustedPacketBufferHandler;
    TextStreamPacketBufferHandler textPacketBufferHandler;

    void* mem = Memory::_Manager[1]->Alloc(sizeof(CacheGateSessionHandler), kFile, 291);
    SessionHandler* handler = mem ? new (mem) CacheGateSessionHandler() : nullptr;
    _sessionHandler[1] = handler;
    if (!Network::OpenPort(1, 0, 2, handler, &trustedPacketBufferHandler, 0, true, true, false))  // LIFT: LTCG folded enableRecv to true (0x28AB0). nagle = dl = 0 (0x136ff).
    {
        Log::Write(Log::LT_ERROR, kFile, 294, L"[%s], %s; failed to open cachegate connection port, portId:%u", MODULE_NAME,
                   L"PostOfficeDaemon::initNetwork", 1);
        return false;
    }

    PipeConsole* const pipeConsole = _instance->pipeConsole;
    if (pipeConsole != nullptr)
    {
        // Inlined PipeConsole::SetInvalidInfo(L"disconnected cachegate", true).
        pipeConsole->_lock.Enter();
        PipeConsole::ItemNode* node = pipeConsole->_invalid._head._next;
        while (node != &pipeConsole->_invalid._tail && wcscmp(node->_key, L"disconnected cachegate") != 0)
            node = node->_next;
        if (node == &pipeConsole->_invalid._tail)
            PipeConsole::addNode(pipeConsole->_invalid, L"disconnected cachegate", L"");  // LIFT: folded. r8 is not set (0x137fe). addNode copies the empty string 0x617e0 (0x33562).
        pipeConsole->_lock.Leave();
    }

    mem = Memory::_Manager[2]->Alloc(sizeof(CacheGateChannel), kFile, 301);
    CacheGateChannel* const cachegateChannel = mem ? new (mem) CacheGateChannel() : nullptr;
    if (!cachegateChannel->MakeSession(1, _config->_cachegateIpAddr,
                                       static_cast<unsigned short>(_config->_cachegateListenPort), 0, true))  // LIFT: portId, connectTimeout and reconnect are folded. The call sets only ip and port (0x13869). MakeSession 0x2bda0 does not read them.
    {
        Log::Write(Log::LT_ERROR, kFile, 303,
                   L"[%s], %s; failed to make cachegate session, portId:%u, cachegateIpAddr:%s, cachegatePort:%u", MODULE_NAME,
                   L"PostOfficeDaemon::initNetwork", 1, Network::GetAddressStringW(_config->_cachegateIpAddr),
                   static_cast<unsigned short>(_config->_cachegateListenPort));
        cachegateChannel->removeReferenceCount(kFile, 304);
        return false;
    }
    if (!_cachegateChannelManager->SetCacheGateChannel(cachegateChannel))
    {
        Log::Write(Log::LT_ERROR, kFile, 309, L"[%s], %s; failed to set cachegate channel", MODULE_NAME,
                   L"PostOfficeDaemon::initNetwork");
        cachegateChannel->Close();
        cachegateChannel->removeReferenceCount(kFile, 311);
        return false;
    }
    cachegateChannel->removeReferenceCount(kFile, 314);

    mem = Memory::_Manager[1]->Alloc(sizeof(AgentSessionHandler), kFile, 325);
    handler = mem ? new (mem) AgentSessionHandler() : nullptr;
    _sessionHandler[2] = handler;
    if (!Network::OpenPort(2, static_cast<unsigned short>(_config->_agentListenPort), 2, handler,
                           &trustedPacketBufferHandler, _config->_maxAgentSessionCount, false, true, false))
    {
        Log::Write(Log::LT_ERROR, kFile, 328, L"[%s], %s; failed to open agent listen port, portId:%u, postNumber:%u",
                   MODULE_NAME, L"PostOfficeDaemon::initNetwork", 2, static_cast<unsigned short>(_config->_agentListenPort));
        return false;
    }

    mem = Memory::_Manager[1]->Alloc(sizeof(WorldSessionHandler), kFile, 335);
    handler = mem ? new (mem) WorldSessionHandler() : nullptr;
    _sessionHandler[3] = handler;
    if (!Network::OpenPort(3, static_cast<unsigned short>(_config->_worldListenPort), 2, handler,
                           &trustedPacketBufferHandler, _config->_maxWorldSessionCount, false, true, false))
    {
        Log::Write(Log::LT_ERROR, kFile, 338, L"[%s], %s; failed to open world listen port, portId:%u, postNumber:%u",
                   MODULE_NAME, L"PostOfficeDaemon::initNetwork", 3, static_cast<unsigned short>(_config->_worldListenPort));
        return false;
    }

    mem = Memory::_Manager[1]->Alloc(sizeof(ManagementSessionHandler), kFile, 345);
    handler = mem ? new (mem) ManagementSessionHandler() : nullptr;
    _sessionHandler[4] = handler;
    if (!Network::OpenPort(4, static_cast<unsigned short>(_config->_managePort), 3, handler, &textPacketBufferHandler,
                           0, true, true, true))  // 0x13B59: autoOpen = 1, nagle = 1
    {
        Log::Write(Log::LT_ERROR, kFile, 348, L"[%s], %s; failed to open management port, portId:%u, postNumber:%u",
                   MODULE_NAME, L"PostOfficeDaemon::initNetwork", 4, static_cast<unsigned short>(_config->_managePort));
        return false;
    }
    Log::Write(Log::LT_NOTICE, kFile, 351, L"[%s], %s; opened management port successfully, portId:%u, portNumber:%u",
               MODULE_NAME, L"PostOfficeDaemon::initNetwork", 4, static_cast<unsigned short>(_config->_managePort));
    Log::Write(Log::LT_NOTICE, kFile, 354, L"[%s], %s; network initialization success", MODULE_NAME,
               L"PostOfficeDaemon::initNetwork");
    return true;
}

// 0x13ca0
bool PostOfficeDaemon::onStart()
{
    if (!initContextManager(Network::Instance->_workerThreadCount) || !loadAllUnsentPostFromDB() || !openListenPort() ||
        !startTimer())
        return false;
    Log::Write(Log::LT_NOTICE, kFile, 374, L"[%s], %s; service ready", MODULE_NAME, L"PostOfficeDaemon::onStart");
    return true;
}

// 0x13d30
bool PostOfficeDaemon::initWorldConfigDependencyManager()
{
    void* mem = Memory::_Manager[2]->Alloc(sizeof(WorldConfigManager), kFile, 382);
    _worldConfigManager = mem ? new (mem) WorldConfigManager() : nullptr;
    if (!_worldConfigManager->initConfigManager())
    {
        Log::Write(Log::LT_ERROR, kFile, 384, L"[%s], %s; failed to initialize world config manager", MODULE_NAME,
                   L"PostOfficeDaemon::initWorldConfigDependencyManager");
        return false;
    }
    WorldConfigList worldConfigList;
    if (!_worldConfigManager->loadWorldConfigFile(&worldConfigList))
    {
        Log::Write(Log::LT_ERROR, kFile, 390, L"[%s], %s; failed to load world config file", MODULE_NAME,
                   L"PostOfficeDaemon::initWorldConfigDependencyManager");
        return false;
    }
    if (!_worldConfigManager->updateWorldList(&worldConfigList))
    {
        Log::Write(Log::LT_ERROR, kFile, 394, L"[%s], %s; failed to update world config manager", MODULE_NAME,
                   L"PostOfficeDaemon::initWorldConfigDependencyManager");
        return false;
    }
    mem = Memory::_Manager[2]->Alloc(sizeof(CachedWatchdogManager), kFile, 398);
    _cachedWatchdogManager = mem ? new (mem) CachedWatchdogManager() : nullptr;
    if (!_cachedWatchdogManager->initWatchdogManager(&worldConfigList))
    {
        Log::Write(Log::LT_ERROR, kFile, 400, L"[%s], %s; failed to initialize cached watchdog manager", MODULE_NAME,
                   L"PostOfficeDaemon::initWorldConfigDependencyManager");
        return false;
    }
    mem = Memory::_Manager[2]->Alloc(sizeof(UnsentPostContextManager), kFile, 404);
    _unsentPostContextManager = mem ? new (mem) UnsentPostContextManager() : nullptr;
    if (!_unsentPostContextManager->initContextManager(&worldConfigList))
    {
        Log::Write(Log::LT_ERROR, kFile, 406, L"[%s], %s; failed to initialize unsent post context manager", MODULE_NAME,
                   L"PostOfficeDaemon::initWorldConfigDependencyManager");
        return false;
    }
    return true;
}

// 0x14090
bool PostOfficeDaemon::initChannelManager(int bucketCount)
{
    if (bucketCount <= 0)
    {
        Log::Write(Log::LT_ERROR, kFile, 435, L"== CRASH == [%s], %s; invalid parameter, bucketCount:%d", MODULE_NAME,
                   L"PostOfficeDaemon::initChannelManager", bucketCount);
        AlertSender::Write(kFile, 435, L"== CRASH == [%s], %s; invalid parameter, bucketCount:%d", MODULE_NAME,
                           L"PostOfficeDaemon::initChannelManager", bucketCount);
        return false;
    }
    void* mem = Memory::_Manager[2]->Alloc(sizeof(AgentChannelManager), kFile, 439);
    _agentChannelManager = mem ? new (mem) AgentChannelManager() : nullptr;
    if (!_agentChannelManager->initChannelManager())
    {
        Log::Write(Log::LT_ERROR, kFile, 441, L"[%s], %s; failed to initialize agent channel manager", MODULE_NAME,
                   L"PostOfficeDaemon::initChannelManager");
        return false;
    }
    mem = Memory::_Manager[2]->Alloc(sizeof(WorldChannelManager), kFile, 445);
    _worldChannelManager = mem ? new (mem) WorldChannelManager(bucketCount) : nullptr;
    if (!_worldChannelManager->initChannelManager())
    {
        Log::Write(Log::LT_ERROR, kFile, 447, L"[%s], %s; failed to initialize world channel manager", MODULE_NAME,
                   L"PostOfficeDaemon::initChannelManager");
        return false;
    }
    mem = Memory::_Manager[2]->Alloc(sizeof(CacheGateChannelManager), kFile, 451);
    _cachegateChannelManager = mem ? new (mem) CacheGateChannelManager() : nullptr;
    if (!_cachegateChannelManager->initChannelManager())
    {
        Log::Write(Log::LT_ERROR, kFile, 453, L"[%s], %s; failed to initialize cachegate channel manager", MODULE_NAME,
                   L"PostOfficeDaemon::initChannelManager");
        return false;
    }
    return true;
}

// 0x14280
bool PostOfficeDaemon::initContextManager(int bucketCount)
{
    if (bucketCount <= 0)
    {
        Log::Write(Log::LT_ERROR, kFile, 463, L"== CRASH == [%s], %s; invalid parameter, bucketCount:%d", MODULE_NAME,
                   L"PostOfficeDaemon::initContextManager", bucketCount);
        AlertSender::Write(kFile, 463, L"== CRASH == [%s], %s; invalid parameter, bucketCount:%d", MODULE_NAME,
                           L"PostOfficeDaemon::initContextManager", bucketCount);
        return false;
    }
    void* mem = Memory::_Manager[2]->Alloc(sizeof(PostContextManager), kFile, 467);
    _postContextManager = mem ? new (mem) PostContextManager(bucketCount) : nullptr;
    if (!_postContextManager->initContextManager())
    {
        Log::Write(Log::LT_ERROR, kFile, 469, L"[%s], %s; failed to initialize post context manager", MODULE_NAME,
                   L"PostOfficeDaemon::initContextManager");
        return false;
    }
    mem = Memory::_Manager[2]->Alloc(sizeof(RelayContextManager), kFile, 473);
    _relayContextManager = mem ? new (mem) RelayContextManager(bucketCount) : nullptr;
    if (!_relayContextManager->initContextManager())
    {
        Log::Write(Log::LT_ERROR, kFile, 475, L"[%s], %s; failed to initialize relay context manager", MODULE_NAME,
                   L"PostOfficeDaemon::initContextManager");
        return false;
    }
    mem = Memory::_Manager[2]->Alloc(sizeof(RelayTimeContextManager), kFile, 479);
    _relayTimeContextManager = mem ? new (mem) RelayTimeContextManager(bucketCount) : nullptr;
    if (!_relayTimeContextManager->initContextManager())
    {
        Log::Write(Log::LT_ERROR, kFile, 481, L"[%s], %s; failed to initialize relaytime context manager", MODULE_NAME,
                   L"PostOfficeDaemon::initContextManager");
        return false;
    }
    return true;
}

// 0x14460
bool PostOfficeDaemon::loadAllUnsentPostFromDB()
{
    int dbRetValue = 0;
    __time64_t const startTime = _time64(nullptr);
    if (!PostOfficeDB::LoadPostList(&dbRetValue))
    {
        Log::Write(Log::LT_ERROR, kFile, 495, L"[%s], %s; failed to load unsent post list, dbRetValue:%d", MODULE_NAME,
                   L"PostOfficeDaemon::loadAllUnsentPostFromDB", dbRetValue);
        return false;
    }
    Log::Write(Log::LT_NOTICE, kFile, 502, L"[%s], %s; database loading time:%I64dsec", MODULE_NAME,
               L"PostOfficeDaemon::loadAllUnsentPostFromDB", _time64(nullptr) - startTime);
    return true;
}

// 0x14520
bool PostOfficeDaemon::openListenPort()
{
    if (!Network::OpenPort(2))
    {
        Log::Write(Log::LT_ERROR, kFile, 510, L"[%s], %s; failed to open agent port, portId:%u, portNumber:%u", MODULE_NAME,
                   L"PostOfficeDaemon::openListenPort", 2, static_cast<unsigned short>(_config->_agentListenPort));
        return false;
    }
    Log::Write(Log::LT_NOTICE, kFile, 513, L"[%s], %s; opened agent port successfully, portId:%u, portNumber:%u", MODULE_NAME,
               L"PostOfficeDaemon::openListenPort", 2, static_cast<unsigned short>(_config->_agentListenPort));
    if (!Network::OpenPort(3))
    {
        Log::Write(Log::LT_ERROR, kFile, 516, L"[%s], %s; failed to open world port, portId:%u, portNumber:%u", MODULE_NAME,
                   L"PostOfficeDaemon::openListenPort", 3, static_cast<unsigned short>(_config->_worldListenPort));
        return false;
    }
    Log::Write(Log::LT_NOTICE, kFile, 519, L"[%s], %s; opened world port successfully, portId:%u, portNumber:%u", MODULE_NAME,
               L"PostOfficeDaemon::openListenPort", 3, static_cast<unsigned short>(_config->_worldListenPort));
    return true;
}

// 0x14660
bool PostOfficeDaemon::startTimer()
{
    if (_config->_relayTimeoutInterval > 0)
    {
        void* const mem = Memory::_Manager[2]->Alloc(sizeof(RelayTimeoutChecker), kFile, 527);
        _relayTimeoutChecker = mem ? new (mem) RelayTimeoutChecker() : nullptr;
        if (!AddTimer(1000, _relayTimeoutChecker))
        {
            Log::Write(Log::LT_ERROR, kFile, 529, L"[%s], %s; failed to add relay timeout checker timer", MODULE_NAME,
                       L"PostOfficeDaemon::startTimer");
            return false;
        }
    }
    void* const mem = Memory::_Manager[2]->Alloc(sizeof(UnsentPostChecker), kFile, 535);
    _unsentPostChecker = mem ? new (mem) UnsentPostChecker() : nullptr;
    if (!AddTimer(1000, _unsentPostChecker))
    {
        Log::Write(Log::LT_ERROR, kFile, 537, L"[%s], %s; failed to add unsent post checker timer", MODULE_NAME,
                   L"PostOfficeDaemon::startTimer");
        return false;
    }
    return true;
}

// 0x147d0
CacheGateChannel* PostOfficeDaemon::checkDestinationServiceState(unsigned short destinationWid)
{
    if (destinationWid == 0)
    {
        Log::Write(Log::LT_ERROR, kFile, 548, L"== CRASH == [%s], %s; invalid parameter, destinationWid:%u", MODULE_NAME,
                   L"PostOfficeDaemon::checkDestinationServiceState", 0);
        AlertSender::Write(kFile, 548, L"== CRASH == [%s], %s; invalid parameter, destinationWid:%u", MODULE_NAME,
                           L"PostOfficeDaemon::checkDestinationServiceState", 0);
        return nullptr;
    }
    // Inlined CachedWatchdogManager::IsServiceAvailable(destinationWid). LIFT: name from the log string 0x71d90
    CachedWatchdog* const cachedWatchdog = _instance->_cachedWatchdogManager->getCachedWatchdog(destinationWid);
    if (cachedWatchdog == nullptr)
    {
        Log::Write(Log::LT_ERROR, L"CachedWatchdog.cpp", 226,
                   L"[%s], %s; no such cached watchdog, wid:%u, cachedWatchdog:0x%p", L"cached watchdog",
                   L"CachedWatchdogManager::IsServiceAvailable", destinationWid, nullptr);
    }
    if (cachedWatchdog == nullptr || cachedWatchdog->_serviceState != CachedWatchdog::SERVICE_STATE_AVAILABLE)
    {
        Log::Write(Log::LT_ERROR, kFile, 553, L"[%s], %s; cached service state is unavailable, destinationWid:%u", MODULE_NAME,
                   L"PostOfficeDaemon::checkDestinationServiceState", destinationWid);
        return nullptr;
    }
    return _instance->checkCacheGateServiceState();
}

// 0x14930
CacheGateChannel* PostOfficeDaemon::checkCacheGateServiceState()
{
    CacheGateChannelManager* const manager = _cachegateChannelManager;
    // Inlined CacheGateChannelManager::GetCacheGateChannel. LIFT: the PDB type record has this public method. It has no body (inlined).
    manager->_lock.Enter();
    CacheGateChannel* const cachegateChannel = manager->_cachegateChannel;
    if (cachegateChannel != nullptr)
        cachegateChannel->addReferenceCount(L"CacheGateChannel.cpp", 168);
    manager->_lock.Leave();
    if (cachegateChannel == nullptr)
    {
        Log::Write(Log::LT_ERROR, kFile, 564, L"[%s], %s; cachegate service state is unavailable", MODULE_NAME,
                   L"PostOfficeDaemon::checkCacheGateServiceState");
        return nullptr;
    }
    if (cachegateChannel->_serviceState != CacheGateChannel::SERVICE_STATE_AVAILABLE)
    {
        Log::Write(Log::LT_ERROR, kFile, 569, L"[%s], %s; cachegate service state is unavailable", MODULE_NAME,
                   L"PostOfficeDaemon::checkCacheGateServiceState");
        cachegateChannel->removeReferenceCount(kFile, 570);
        return nullptr;
    }
    return cachegateChannel;
}

// 0x14a30
void PostOfficeDaemon::shutdown()
{
    Log::Write(Log::LT_NOTICE, kFile, 579, L"[%s], %s; service shutdown", MODULE_NAME, L"PostOfficeDaemon::shutdown");
    _cachedWatchdogManager->SetAllServiceState(CachedWatchdog::SERVICE_STATE_UNAVAILABLE);
    CacheGateChannelManager* const manager = _cachegateChannelManager;
    manager->_lock.Enter();
    if (manager->_cachegateChannel != nullptr)
        manager->_cachegateChannel->SetServiceState(CacheGateChannel::SERVICE_STATE_UNAVAILABLE);
    manager->_lock.Leave();
    Network::StopPort(2);
    Network::ClosePort(2);
    Network::StopPort(3);
    Network::ClosePort(3);
    Network::StopPort(1);
    Network::ClosePort(1);
    Network::Clear();
    // LIFT: inlined Db cleanup, no PDB name. The Db type record has no cleanup method (only Clear(uint) and initEnv).
    if (Db::EnvHandle != nullptr)
    {
        SQLFreeHandle(SQL_HANDLE_ENV, Db::EnvHandle);
        Db::EnvHandle = nullptr;
    }
    for (unsigned int dbId = 1; dbId <= 40; ++dbId)
    {
        if (Db::Instance[dbId] != nullptr)
            Db::Clear(dbId);
    }
}

// 0x14b80
bool PostOfficeDaemon::reload(wchar_t** /*args*/, int /*count*/)
{
    Log::Write(Log::LT_DEBUG, kFile, 601, L"[%s], %s; Reload start", MODULE_NAME, L"PostOfficeDaemon::reload");
    WorldConfigList worldConfigList;
    if (!_worldConfigManager->loadWorldConfigFile(&worldConfigList))
    {
        Log::Write(Log::LT_ERROR, kFile, 605, L"[%s], %s; failed to load world config file", MODULE_NAME,
                   L"PostOfficeDaemon::reload");
    }
    else if (!_unsentPostContextManager->updateWorldList(&worldConfigList))
    {
        Log::Write(Log::LT_ERROR, kFile, 610, L"[%s], %s; failed to update world list of unsent post context manager",
                   MODULE_NAME, L"PostOfficeDaemon::reload");
    }
    else if (!_cachedWatchdogManager->updateWorldList(&worldConfigList))
    {
        Log::Write(Log::LT_ERROR, kFile, 614, L"[%s], %s; failed to update world list of cached watchdog manager", MODULE_NAME,
                   L"PostOfficeDaemon::reload");
    }
    else if (!_worldConfigManager->updateWorldList(&worldConfigList))
    {
        Log::Write(Log::LT_ERROR, kFile, 618, L"[%s], %s; failed to update world list of world config manager", MODULE_NAME,
                   L"PostOfficeDaemon::reload");
    }
    else
    {
        Log::Write(Log::LT_NOTICE, kFile, 623, L"[%s], %s; bns common config reloading...", MODULE_NAME,
                   L"PostOfficeDaemon::reload");
        bool changed = false;
        if (!BnsCommonConfig::ReloadBnsCommonConfig(changed))
        {
            Log::Write(Log::LT_ERROR, kFile, 626, L"[%s], %s; bns common config reload fail", MODULE_NAME,
                       L"PostOfficeDaemon::reload");
        }
        else if (changed)
        {
            BnsCommonConfig::Dump();
            Log::Write(Log::LT_NOTICE, kFile, 637, L"[%s], %s; bns common config reload complete, done", MODULE_NAME,
                       L"PostOfficeDaemon::reload");
        }
        else
        {
            Log::Write(Log::LT_NOTICE, kFile, 632, L"[%s], %s; bns common config reload complete, not changed", MODULE_NAME,
                       L"PostOfficeDaemon::reload");
        }
        Log::Write(Log::LT_DEBUG, kFile, 641, L"[%s], %s; Reload success", MODULE_NAME, L"PostOfficeDaemon::reload");
    }
    return true;
}
