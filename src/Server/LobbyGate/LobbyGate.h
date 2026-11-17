// LobbyGate.obj (LobbyGate PDB). Layouts from include/pdb/LobbyGate/types.h.
#pragma once
#include <stddef.h>
#include "Daemon.h"
#include "DaemonConfig.h"
#include "Security.h"
#include "TimerQueue.h"

class EventObject;
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
    void Dump();  // 0x13e20

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

    static XmlCfgDef const _Def[29];  // 0x140092d40
};
static_assert(sizeof(LobbyGateConfig) == 0x70, "sizeof LobbyGateConfig");
static_assert(offsetof(LobbyGateConfig, _useChannelDelayedRelease) == 0x5C, "LobbyGateConfig::_useChannelDelayedRelease");

class LobbyGate : public Daemon
{
public:
    // LIFT: The constructor is inlined in wmain (0x128b0).
    LobbyGate()
        : _config(nullptr), _sessionHandlerList(nullptr), _sessionHandlerCount(0), _lobbyD(nullptr),
          _gatekeyManager(nullptr), _clientManager(nullptr), _worldListManger(nullptr),
          _pcCafeMileageFeverTimeScheduleListManager(nullptr), _logfile(nullptr), _restoreReloadTimer(nullptr)
    {
    }
    virtual ~LobbyGate();                                       // 0x129c0
    virtual void PrintDependency();                             // 0x12b60
    virtual wchar_t const* ShortName();                         // 0x12690
    virtual wchar_t const* Name();                              // 0x126a0
    virtual wchar_t const* ServiceName();                       // 0x126b0
    virtual wchar_t const* Descriptions();                      // 0x126c0
    virtual long GetTimerInterval();                            // 0x12cd0
    virtual long GetTimerMaxTime();                             // 0x12ce0
    virtual bool initLog();                                     // 0x12d40
    virtual bool setArgument(int argc, wchar_t const** argv);   // 0x12e60
    virtual bool initialize();                                  // 0x12e70
    virtual bool initNetwork();                                 // 0x13220
    virtual bool onStart();                                     // 0x13550
    virtual void shutdown();                                    // 0x13580
    virtual bool reload(wchar_t** argv, int argc);              // 0x13770
    virtual bool cooldown();                                    // 0x13d20

    void AddJobTimer(unsigned long long gateKey, char reason);  // 0x12bf0
    static void FailedEventObjectHandler(EventObject* eventObject);  // 0x12cf0

    static LobbyGate* _instance;

    LobbyGateConfig const* _config;
    SessionHandler** _sessionHandlerList;
    int _sessionHandlerCount;
    LobbyD* _lobbyD;
    GateKeyManager* _gatekeyManager;
    ClientManager* _clientManager;
    WorldListManager* _worldListManger;
    PcCafeMileageFeverTimeScheduleListManager* _pcCafeMileageFeverTimeScheduleListManager;  // PDB LF_MEMBER offset 1920
    LogFile* _logfile;
    BroadcastCrypt _broadcastCrypt;
    Timer* _restoreReloadTimer;
};
static_assert(sizeof(LobbyGate) == 0x7B0, "sizeof LobbyGate");
static_assert(offsetof(LobbyGate, _config) == 0x748, "LobbyGate::_config");
static_assert(offsetof(LobbyGate, _lobbyD) == 0x760, "LobbyGate::_lobbyD");
static_assert(offsetof(LobbyGate, _pcCafeMileageFeverTimeScheduleListManager) == 0x780, "LobbyGate::_pcCafeMileageFeverTimeScheduleListManager");
static_assert(offsetof(LobbyGate, _broadcastCrypt) == 0x790, "LobbyGate::_broadcastCrypt");
static_assert(offsetof(LobbyGate, _restoreReloadTimer) == 0x7A8, "LobbyGate::_restoreReloadTimer");

class LobbyGateCooldownTimer : public Timer
{
public:
    // LIFT: The constructor is inlined in LobbyGate::cooldown (0x13d20).
    explicit LobbyGateCooldownTimer(int completeDelay)
        : _elapsed(0), _completeDelay(completeDelay), _disconnectStarted(false)
    {
        StartTick = 0;
        next = nullptr;
        prev = nullptr;
        SlotIndex = -1;
        InLtq = false;
    }
    virtual ~LobbyGateCooldownTimer();                                          // 0x13bb0
    virtual unsigned int TimerClass() const;                                    // 0x28750 (folded with TimerId)
    virtual unsigned long long TimerId() const;                                 // 0x28750
    virtual unsigned int EventId() const;                                       // 0x13ba0
    virtual bool HandleEvent(EventContext* context, unsigned long numOfBytes);  // 0x13bf0

    int _elapsed;
    int _completeDelay;
    bool _disconnectStarted;
};
static_assert(sizeof(LobbyGateCooldownTimer) == 0x48, "sizeof LobbyGateCooldownTimer");

class LobbyGateReloadInvalidRestoreTimer : public Timer
{
public:
    // LIFT: The constructor is inlined in LobbyGate::reload (0x13770).
    LobbyGateReloadInvalidRestoreTimer() : _isExecuted(false)
    {
        StartTick = 0;
        next = nullptr;
        prev = nullptr;
        SlotIndex = -1;
        InLtq = false;
    }
    virtual ~LobbyGateReloadInvalidRestoreTimer();                              // 0x13bb0
    virtual unsigned int TimerClass() const;                                    // 0x21830 (folded with TimerId)
    virtual unsigned long long TimerId() const;                                 // 0x21830
    virtual unsigned int EventId() const;                                       // 0x12780
    virtual bool HandleEvent(EventContext* context, unsigned long numOfBytes);  // 0x12790

    void restoreInvalid();  // 0x127a0

    static wchar_t const* INVALID_REASON_STR[3];

    bool _isExecuted;
};
static_assert(sizeof(LobbyGateReloadInvalidRestoreTimer) == 0x40, "sizeof LobbyGateReloadInvalidRestoreTimer");

// LobbyDPacketHandler.obj (this card).
extern void* LobbyLobbyGatePacketLobbyGateSideHandlerList[111];
extern void* LobbyLobbyGatePacketLobbyGateSideFragmentHandlerList[111];
