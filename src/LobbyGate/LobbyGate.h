// LobbyGate.obj (LobbyGate PDB). Layouts from include/pdb/LobbyGate/types.h.
// The methods of LobbyGate come from a later card. This header has only the data layout.
#pragma once
#include <stddef.h>
#include "Daemon.h"
#include "Security.h"
#include "TimerQueue.h"

class SessionHandler;
class LobbyD;
class GateKeyManager;
class ClientManager;
class WorldListManager;
class PcCafeMileageFeverTimeScheduleListManager;
class LogFile;

class LobbyGateConfig
{
public:
    wchar_t* _rootPath;
    wchar_t* _logPath;
    wchar_t* _configPath;
    char* _certFile;
    int _workerThreadCount;
    int _maxClientSession;
    int _dumpType;
    int _timerInterval;
    int _timerMaxTime;
    int _initCliSessionCount;
    int _cliSessionHashCount;
    int _predefinedWorldId;
    long _closeTimeout;
    int _internalPort;
    int _clientPort;
    unsigned long _lobbyAddr;
    int _lobbyPort;
    bool _maxIdleTimeEnable;
    bool _disconnectAfterIdleTime;
    int _maxIdleTime;
    bool _useChannelDelayedRelease;
    wchar_t* _alertSendAddress;
    int _cooldownCompleteDelay;
    bool _allowClientIPAddressInLogs;
};
static_assert(sizeof(LobbyGateConfig) == 0x70, "sizeof LobbyGateConfig");
static_assert(offsetof(LobbyGateConfig, _useChannelDelayedRelease) == 0x5C, "LobbyGateConfig::_useChannelDelayedRelease");

class LobbyGate : public Daemon
{
public:
    static LobbyGate* _instance;  // defined in LobbyGate.cpp (later card)

    LobbyGateConfig const* _config;
    SessionHandler** _sessionHandlerList;
    int _sessionHandlerCount;
    LobbyD* _lobbyD;
    GateKeyManager* _gatekeyManager;
    ClientManager* _clientManager;
    WorldListManager* _worldListManger;
    PcCafeMileageFeverTimeScheduleListManager* _pcCafeMileageFeverTimeScheduleListManager;  // ❓ member name
    LogFile* _logfile;
    BroadcastCrypt _broadcastCrypt;
    Timer* _restoreReloadTimer;
};
static_assert(sizeof(LobbyGate) == 0x7B0, "sizeof LobbyGate");
static_assert(offsetof(LobbyGate, _config) == 0x748, "LobbyGate::_config");
static_assert(offsetof(LobbyGate, _lobbyD) == 0x760, "LobbyGate::_lobbyD");
static_assert(offsetof(LobbyGate, _broadcastCrypt) == 0x790, "LobbyGate::_broadcastCrypt");
static_assert(offsetof(LobbyGate, _restoreReloadTimer) == 0x7A8, "LobbyGate::_restoreReloadTimer");
