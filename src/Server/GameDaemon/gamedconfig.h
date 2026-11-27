// gamedconfig.h: gamedconfig.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class GamedConfig
{
public:
    static ::GamedConfig * __cdecl Load(void);  // 0x343940
    void __cdecl Reload(void);  // 0x343a20
    static void __cdecl Destroy(::GamedConfig *);  // 0x343f20
private:
    void __cdecl setPerfGeoZone(wchar_t const *);  // 0x343ff0
    void __cdecl setSkipActionPacketList(wchar_t const *);  // 0x344290
    void __cdecl setZoneRecommendPcCount(wchar_t const *, bool);  // 0x345cb0
protected:
    void __cdecl setExceptLastChangedPropertyList(wchar_t const *);  // 0x346060
public:
    bool __cdecl UsePerfGeoZone(::GeoZone const *) const;  // 0x346250

    // PDB data members (PDB size 0x660). LIFT: the members after _arenaId (+0xFC to +0x660) follow in later waves.
    // LIFT: the PDB access is private. The lifted GameDaemon static getters read them directly (inlined accessors).
public:
    wchar_t * _rootPath;                        // +0x00
    wchar_t * _logPath;                         // +0x08
    wchar_t * _dataPath;                        // +0x10
    char * _certFile;                           // +0x18
    wchar_t * _alertSendAddress;                // +0x20
    int _workerThreadCount;                     // +0x28
    int _maxClientSession;                      // +0x2C
    int _dumpType;                              // +0x30
    bool _createDumpBeforeStop;                 // +0x34
    int _createLogFileTimeType;                 // +0x38
    int _cooldownDisconnectDelay;               // +0x3C
    int _cooldownCompleteDelay;                 // +0x40
    bool _maxIdleTimeEnable;                    // +0x44
    bool _disconnectAfterIdleTime;              // +0x45
    int _maxIdleTime;                           // +0x48
    bool _transactionExpiredCheckEnable;        // +0x4C
    int _transactionExpiredDuration;            // +0x50
    wchar_t * _supportLanguages;                // +0x58
    wchar_t * _publisher;                       // +0x60
    int _logCodePage;                           // +0x68
    bool _wordFilterEnable;                     // +0x6C
    int _trialPlayLimitLevel;                   // +0x70
    int _trialPlayExpiredCloseWaitDuration;     // +0x74
    wchar_t * _publicAddrRange;                 // +0x78
    wchar_t * _internalAddrRange;               // +0x80
    __int64 _serviceAddr;                       // +0x88
    int _publicPort;                            // +0x90
    int _internalPort;                          // +0x94
    int _managePort;                            // +0x98
    int _builderPort;                           // +0x9C
    bool _managePortEnable;                     // +0xA0
    bool _managementdEnable;                    // +0xA1
    int _managementdPort;                       // +0xA4
    bool _petitiondEnable;                      // +0xA8
    __int64 _petitiondAddress;                  // +0xB0
    int _petitiondPort;                         // +0xB8
    __int64 _logdAddress;                       // +0xC0
    int _logdPort;                              // +0xC8
    __int64 _lobbyAddress;                      // +0xD0
    int _lobbyPort;                             // +0xD8
    __int64 _cachedAddress;                     // +0xE0
    int _cachedPort;                            // +0xE8
    bool _npAuthEnabled;                        // +0xEC
    bool _arenaEnabled;                         // +0xED
    int _maxArenaId;                            // +0xF0
    int _maxWorldId;                            // +0xF4
    int _arenaId;                               // +0xF8
};

