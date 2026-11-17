// LobbyGateConfig.obj (LobbyGate PDB).
#include <wchar.h>
#include "LobbyGate.h"
#include "Log.h"
#include "Network.h"

#define CONFIG_FILE L"LobbyGateConfig.cpp"

// Default values of LobbyGateConfig::_Def. The names come from the PDB (LobbyGateConfig.obj).
static int const DEFAULT_MAX_CLIENT_SESSION_COUNT = 200000;
static int const DEFAULT_DUMPTYPE = 1;
static int const DEFAULT_TIMER_INTERVAL = 1000;
static int const DEFAULT_TIMER_MAX_TIME = 20;
static int const DEFAULT_CLI_SESSION_HASH_COUNT = 1;
static int const DEFAULT_PREDEFINED_WORLD_ID = 4001;
static int const DEFAULT_INTERNAL_PORT = 20900;
static int const DEFAULT_CLIENT_PORT = 10900;
static int const DEFAULT_LOBBY_DAEMON_PORT = 21801;
static int const DEFAULT_IDLE_TIME = 300;
static int const DEFAULT_COOLDOWN_COMPLETE = 180;
static bool const DEFAULT_TRUE = true;  // ❓ unnamed data in the binary (bytes 0xFF)

// 0x140092d40
XmlCfgDef const LobbyGateConfig::_Def[29] = {
    {static_cast<unsigned long long>(-1), nullptr, 0, 0, nullptr, L"path"},
    {offsetof(LobbyGateConfig, _rootPath), L"root-path", XmlCfgDef::CFG_DIR, 1, nullptr, L"full root path"},
    {offsetof(LobbyGateConfig, _logPath), L"log-path", XmlCfgDef::CFG_DIR, 1, nullptr, L"full log path"},
    {offsetof(LobbyGateConfig, _configPath), L"config-path", XmlCfgDef::CFG_DIR, 1, nullptr, L"full config path"},
    {static_cast<unsigned long long>(-1), nullptr, 0, 0, nullptr, L"certification"},
    {offsetof(LobbyGateConfig, _certFile), L"cert", XmlCfgDef::CFG_ANSI, 1, nullptr, L"certification file path"},
    {static_cast<unsigned long long>(-1), nullptr, 0, 0, nullptr, L"system configuration"},
    {offsetof(LobbyGateConfig, _workerThreadCount), L"worker-thread", XmlCfgDef::CFG_INT, 0, nullptr,
     L"0 is system recommend"},
    {offsetof(LobbyGateConfig, _maxClientSession), L"max-client", XmlCfgDef::CFG_INT, 0,
     &DEFAULT_MAX_CLIENT_SESSION_COUNT, L"0 is default = 200000"},
    {offsetof(LobbyGateConfig, _dumpType), L"dump-type", XmlCfgDef::CFG_INT, 0, &DEFAULT_DUMPTYPE,
     L"0: no dump, 1: minimal dump(default), 2: full dump"},
    {offsetof(LobbyGateConfig, _timerInterval), L"timer-interval", XmlCfgDef::CFG_INT, 0, &DEFAULT_TIMER_INTERVAL,
     L"interval of timer(msec)"},
    {offsetof(LobbyGateConfig, _timerMaxTime), L"timer-max-time", XmlCfgDef::CFG_INT, 0, &DEFAULT_TIMER_MAX_TIME,
     L"max time of timer(sec)"},
    {offsetof(LobbyGateConfig, _initCliSessionCount), L"init-client-session-count", XmlCfgDef::CFG_INT, 0, nullptr,
     L"0 means no preparance of client session"},
    {offsetof(LobbyGateConfig, _cliSessionHashCount), L"client-session-hash-count", XmlCfgDef::CFG_INT, 0,
     &DEFAULT_CLI_SESSION_HASH_COUNT, L"client session hash count"},
    {offsetof(LobbyGateConfig, _predefinedWorldId), L"predefined-world-id", XmlCfgDef::CFG_INT, 1,
     &DEFAULT_PREDEFINED_WORLD_ID, L"predefined world id"},
    {offsetof(LobbyGateConfig, _closeTimeout), L"client-close-timeout", XmlCfgDef::CFG_INT, 1, nullptr,
     L"client session close timeout(msec). 0 means no timeout"},
    {static_cast<unsigned long long>(-1), nullptr, 0, 0, nullptr, L"network configuration"},
    {offsetof(LobbyGateConfig, _internalPort), L"internal-port", XmlCfgDef::CFG_INT, 1, &DEFAULT_INTERNAL_PORT,
     L"lobbygate access port"},
    {offsetof(LobbyGateConfig, _clientPort), L"client-port", XmlCfgDef::CFG_INT, 1, &DEFAULT_CLIENT_PORT, L"client port"},
    {offsetof(LobbyGateConfig, _lobbyAddr), L"lobby-daemon-addr", XmlCfgDef::CFG_IP, 1, L"127.0.0.1",  /* 0x7c298 text, no PDB name */
     L"lobby daemon ip address"},
    {offsetof(LobbyGateConfig, _lobbyPort), L"lobby-daemon-port", XmlCfgDef::CFG_INT, 1, &DEFAULT_LOBBY_DAEMON_PORT,
     L"lobby daemon port"},
    {offsetof(LobbyGateConfig, _maxIdleTimeEnable), L"max-idle-time-enable", XmlCfgDef::CFG_BOOL, 1, &DEFAULT_TRUE,
     L"max idle time enable / disable"},
    {offsetof(LobbyGateConfig, _disconnectAfterIdleTime), L"disconnect-after-idle-time", XmlCfgDef::CFG_BOOL, 0, nullptr,
     L"disconnect after idle time"},
    {offsetof(LobbyGateConfig, _maxIdleTime), L"max-idle-time", XmlCfgDef::CFG_INT, 0, &DEFAULT_IDLE_TIME,
     L"max idle time"},
    {offsetof(LobbyGateConfig, _useChannelDelayedRelease), L"use-channel-delayed-release", XmlCfgDef::CFG_BOOL, 0,
     nullptr, L"session-channel binding releases after some delay(10sec) default:no"},
    {offsetof(LobbyGateConfig, _alertSendAddress), L"alert-send-address", XmlCfgDef::CFG_STR, 0,
     L"",  // ❓ IDA name "valueString", first wchar is 0
     L"alert log send address (ip:port)"},
    {offsetof(LobbyGateConfig, _cooldownCompleteDelay), L"cooldown-complete-delay", XmlCfgDef::CFG_INT, 0,
     &DEFAULT_COOLDOWN_COMPLETE, L"cooldown"},
    {static_cast<unsigned long long>(-1), nullptr, 0, 0, nullptr, L"Configuration for logs"},
    {offsetof(LobbyGateConfig, _allowClientIPAddressInLogs), L"allow-client-ip-address-in-logs", XmlCfgDef::CFG_BOOL, 0,
     &DEFAULT_TRUE, L"allow client ip address in logs"},
};

// 0x13e20
void LobbyGateConfig::Dump()
{
    wchar_t lobbydAddr[20];

    Log::Write(Log::LT_NOTICE, CONFIG_FILE, 128, L"[lg], ==== path configuration ====");
    Log::Write(Log::LT_NOTICE, CONFIG_FILE, 129, L"[lg], root path   : %s", _rootPath);
    Log::Write(Log::LT_NOTICE, CONFIG_FILE, 130, L"[lg], log path    : %s", _logPath);
    Log::Write(Log::LT_NOTICE, CONFIG_FILE, 131, L"[lg], config path : %s", _configPath);
    Log::Write(Log::LT_NOTICE, CONFIG_FILE, 133, L"[lg], ==== system configuration ====");
    Log::Write(Log::LT_NOTICE, CONFIG_FILE, 134, L"[lg], worker thread count             : %d", _workerThreadCount);
    Log::Write(Log::LT_NOTICE, CONFIG_FILE, 135, L"[lg], max client session\t\t\t  : %d", _maxClientSession);
    Log::Write(Log::LT_NOTICE, CONFIG_FILE, 136, L"[lg], dump type                       : %d", _dumpType);
    Log::Write(Log::LT_NOTICE, CONFIG_FILE, 137, L"[lg], timer interval                  : %d(msec)", _timerInterval);
    Log::Write(Log::LT_NOTICE, CONFIG_FILE, 138, L"[lg], timer max time                  : %d(sec)", _timerMaxTime);
    Log::Write(Log::LT_NOTICE, CONFIG_FILE, 139, L"[lg], initial client session count    : %d", _initCliSessionCount);
    Log::Write(Log::LT_NOTICE, CONFIG_FILE, 140, L"[lg], client session hash count\t\t  : %d", _cliSessionHashCount);
    Log::Write(Log::LT_NOTICE, CONFIG_FILE, 142, L"[lg], client session close timeout    : %d", _closeTimeout);
    wcsncpy(lobbydAddr, Network::GetAddressStringW(_lobbyAddr), 20);
    Log::Write(Log::LT_NOTICE, CONFIG_FILE, 147, L"[lg], ==== network configuration ====");
    Log::Write(Log::LT_NOTICE, CONFIG_FILE, 148, L"[lg], internal port\t\t\t\t: %d", _internalPort);
    Log::Write(Log::LT_NOTICE, CONFIG_FILE, 149, L"[lg], client port\t\t\t\t: %d", _clientPort);
    Log::Write(Log::LT_NOTICE, CONFIG_FILE, 150, L"[lg], lobby daemon ip address\t: %s", lobbydAddr);
    Log::Write(Log::LT_NOTICE, CONFIG_FILE, 151, L"[lg], lobby daemon port\t\t\t: %d", _lobbyPort);
    Log::Write(Log::LT_NOTICE, CONFIG_FILE, 152, L"[lg], max idle time enable\t\t: %s", _maxIdleTimeEnable ? L"yes" : L"no");
    Log::Write(Log::LT_NOTICE, CONFIG_FILE, 153, L"[lg], disconnect after idle time : %s",
               _disconnectAfterIdleTime ? L"yes" : L"no");
    Log::Write(Log::LT_NOTICE, CONFIG_FILE, 154, L"[lg], max idle time\t\t\t\t: %d", _maxIdleTime);
    Log::Write(Log::LT_NOTICE, CONFIG_FILE, 155, L"[lg], %s\t\t\t\t\t\t: %s", L"use-channel-delayed-release",
               _useChannelDelayedRelease ? L"yes" : L"no");
    Log::Write(Log::LT_NOTICE, CONFIG_FILE, 156, L"[lg], alert send address\t\t: %s", _alertSendAddress);
    Log::Write(Log::LT_NOTICE, CONFIG_FILE, 157, L"[lg], cooldown complete delay   : %d", _cooldownCompleteDelay);
    Log::Write(Log::LT_NOTICE, CONFIG_FILE, 163, L"[lg], ==== Configuration for logs ====");
    Log::Write(Log::LT_NOTICE, CONFIG_FILE, 164, L"[lg], allow client ip address in logs\t: %s",
               _allowClientIPAddressInLogs ? L"yes" : L"no");
}
