// gamedaemon.h: gamedaemon.cpp, gamedaemon.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "Lock.h"

class SessionHandler;
class LogFile;

class BuilderSessionHandler
{
public:
    static ::Pointer2< ::Pc> __cdecl GetPcPtr(::Session const *);  // 0x33a9c0
    virtual bool __cdecl OnAccept(::Session const *) const;  // 0x33aaf0
    virtual bool __cdecl OnConnect(::Session const *, bool) const;  // 0x33ab30
    virtual void __cdecl OnClose(::Session const *, bool) const;  // 0x33ab70
    virtual bool __cdecl PacketHandler(::Session const *, ::Packet const *) const;  // 0x33ac20
};

class GameDaemon : public ::Daemon
{
public:
    virtual long __cdecl GetTimerMaxTime(void);  // 0x191e0
    static bool __cdecl IsArenaDaemon(void);  // 0x27f80
    static bool __cdecl IsArenaDungeonDaemon(void);  // 0x27fb0
    static ::RankingResult * __cdecl GetRankingResult(void);  // 0x971d0
    static bool __cdecl IsArenaEnabledGameDaemon(void);  // 0x1107f0
    static bool __cdecl InitializeRankingResult(void);  // 0x180ca0
    static bool __cdecl SetEventReplyCacheHello(void);  // 0x180e10
    // LIFT: 0x311c10 has SetEventReplyCacheHello inlined (header body in the original). The friend line gives the same access.
    friend bool __cdecl HandleCacheGame_InitializeMentoringFail(::Session const *, ::Packet const *);
    virtual wchar_t const * __cdecl ShortName(void);  // 0x1ee6f0
    virtual wchar_t const * __cdecl Name(void);  // 0x1ee700
    virtual long __cdecl GetTimerInterval(void);  // 0x1ee710
    __cdecl GameDaemon(void);  // 0x33b2d0
    virtual __cdecl ~GameDaemon(void);  // 0x33b9a0
protected:
    virtual bool __cdecl initLog(void);  // 0x33c520
    virtual void __cdecl FlushExtraLog(void);  // 0x33cc40
    virtual bool __cdecl initialize(void);  // 0x33cc60
private:
    bool __cdecl loadBannedWorldFilter(::XmlReaderIO *);  // 0x33e960
protected:
    virtual bool __cdecl initNetwork(void);  // 0x33eee0
public:
    static int __cdecl GetDuelRatingBeginnerConst(int);  // 0x340970
    void __cdecl SetDuelRatingBeginnerConst(void);  // 0x340a00
    static void __cdecl SetWorldIds(short, short *const);  // 0x340af0
    static bool __cdecl ValidWorldId(short);  // 0x340c70
    bool __cdecl SetPublisher(wchar_t const *);  // 0x340cc0
    bool __cdecl SetTimeZoneBias(void);  // 0x340d50
    static int __cdecl GetRandomStoreServiceState(char);  // 0x340e70
    static short __cdecl GetServerIdForDaemon(void);  // 0x340ea0
    static short __cdecl GetServerIdForNPChat(char);  // 0x340ee0
    static short __cdecl GetServerIdForChat(char);  // 0x340f20
protected:
    virtual bool __cdecl onStart(void);  // 0x340fc0
    virtual void __cdecl shutdown(void);  // 0x341230
private:
    bool __cdecl startGameDaemon(void);  // 0x341890
    bool __cdecl startNPChannel(void);  // 0x3419f0
    bool __cdecl initializePublisherLibs(void);  // 0x341cf0
protected:
    virtual bool __cdecl reload(wchar_t **, int);  // 0x342110
    virtual bool __cdecl cooldown(void);  // 0x342d80
public:
    static void __cdecl FailedEventObjectHandler(::EventObject *);  // 0x342f80
    virtual wchar_t const * __cdecl ServiceName(void);  // 0x343030
    virtual wchar_t const * __cdecl Descriptions(void);  // 0x343040
    virtual void __cdecl PrintDependency(void);  // 0x343140
    bool __cdecl NotCheckToPlayInWeek(char);  // 0x343650
    static void __cdecl WriteDump(bool);  // 0x3438f0
    static wchar_t const * __cdecl GetAddressStringWForLogs(unsigned long);  // 0x343910

    static ::GameDaemon * GamedInstance;
    ::RuleConfig * GetRuleConfig(void) { return ruleConfig; }  // PDB inline

    // PDB data members (PDB size 0x15378). LIFT: the members after arenaGameChannelEnable (+0x1038 to +0x15378) follow in later waves.
    // LIFT: a member with an `unsigned __int64 x[n]` type is a sized stand-in. Its comment gives the PDB type, which is not declared yet.
private:
    ::SystemEvent replyCacheHelloEvent;                          // +0x748
    ::SystemEvent replyArenaLobbyHelloEvent;                     // +0x750
    ::SystemEvent npInitialConnectEvent;                         // +0x758
    unsigned __int64 npRegisterGameServiceEvent[0x328 / 8];      // +0x760. LIFT: PDB type SystemMultiEvent
    ::SystemEvent npRegisterGameGroupServiceEvent;               // +0xA88
    long volatile _challengePartyListLoaded;                     // +0xA90
    long volatile _mentoringListLoaded;                          // +0xA94
public:
    ::PublisherLibsInterface * _plsInterface;                    // +0xA98
    void * _tlsInterface;                                        // +0xAA0. LIFT: PDB type TencentLibsInterface *
private:
    ::GamedConfig * config;                                      // +0xAA8
    ::RuleConfig * ruleConfig;                                   // +0xAB0
    int _pType;                                                  // +0xAB8. LIFT: PDB type PRODUCT_TYPE (enum)
    ::UserManager * userManager;                                 // +0xAC0
    ::CloseWaitManager * closeWaitManager;                       // +0xAC8
    ::BuilderOperationManager * builderOperationManager;         // +0xAD0
    void * bannedWordFilter;                                     // +0xAD8. LIFT: PDB type BannedWordFilterLib *
    ::BannedWordFilterDynamicMemoryManager * bannedWordFilterMemoryManager;  // +0xAE0
    unsigned __int64 localeSet[0x18 / 8];                        // +0xAE8. LIFT: PDB type GameLocaleSet
    unsigned __int64 petitionSessionHandler[0x8 / 8];            // +0xB00. LIFT: PDB type PetitionSessionHandler
    ::PetitionManager * petitionManager;                         // +0xB08
    ::SessionHandler * sessionHandler[25];                       // +0xB10
    ::LogFile * logFile;                                         // +0xBD8
    ::LogFile * logFgtFile;                                      // +0xBE0
    ::LogFile * auditLogFile;                                    // +0xBE8
    ::LogFile * surveyLogFile;                                   // +0xBF0
    ::LogFile * ncGuardLogFile;                                  // +0xBF8
    ::LogFile * clientLogFile;                                   // +0xC00
    unsigned __int64 broadcastCrypt[0x18 / 8];                   // +0xC08. LIFT: PDB type BroadcastCrypt
    unsigned __int64 cachedChannel[0x28 / 8];                    // +0xC20. LIFT: PDB type CachedChannel
    int * duelRatingBeginnerConst;                               // +0xC48
    unsigned __int64 randomStoreInitializationSchedule[0x18 / 8];  // +0xC50. LIFT: PDB type RandomStoreInitializationSchedule
    int gameMileageEffectiveDurationInDays;                      // +0xC68
    ::RankingSeasonManager * rankingSeasonMgr;                   // +0xC70
    unsigned __int64 timeBasedPlaySeasonSchedule[0x1E0 / 8];     // +0xC78. LIFT: PDB type TimeBasedPlaySeasonSchedule
    ::BoardGacha * boardGacha;                                   // +0xE58
    __int64 duelBotTraineeKey;                                   // +0xE60
    __int64 duelBotTrainerKey;                                   // +0xE68
    char recombat;                                               // +0xE70
    unsigned __int64 arenaSideArenaLobbyChannel[0x38 / 8];       // +0xE78. LIFT: PDB type ArenaSideArenaLobbyChannel
    unsigned __int64 arenaGameManager[0x38 / 8];                 // +0xEB0. LIFT: PDB type ArenaGameManager
    unsigned __int64 arenaGameSessionHandler[0x8 / 8];           // +0xEE8. LIFT: PDB type ArenaGameSessionHandler
    unsigned __int64 gameSideArenaLobbySessionHander[0x8 / 8];   // +0xEF0. LIFT: PDB type GameSideArenaLobbySessionHandler
    unsigned __int64 gameArenaLobbyManager[0xD0 / 8];            // +0xEF8. LIFT: PDB type GameArenaLobbyManager
    unsigned __int64 gameArenaManager[0x50 / 8];                 // +0xFC8. LIFT: PDB type GameArenaManager
    unsigned __int64 gameArenaSessionHandler[0x8 / 8];           // +0x1018. LIFT: PDB type GameArenaSessionHandler
    ::DisconnectedArenaSessionManager * disconnectedArenaSessionManager;  // +0x1020
    ::ArenaRoomManager * arenaRoomManager;                       // +0x1028
    char arenaAttraction;                                        // +0x1030
    bool arenaGameChannelEnable;                                 // +0x1031
};
static_assert(sizeof(::Daemon) == 0x748, "sizeof Daemon (GameDaemon base)");

class GamedCooldownTimer
{
public:
    virtual unsigned int __cdecl EventId(void) const;  // 0x342ae0
    virtual bool __cdecl HandleEvent(::EventContext *, unsigned long);  // 0x342af0
private:
    int __cdecl disconnectAll(void);  // 0x342c20
};

class GamedReloadInvalidRestoreTimer
{
public:
    virtual unsigned int __cdecl EventId(void) const;  // 0x33afc0
    virtual bool __cdecl HandleEvent(::EventContext *, unsigned long);  // 0x33afd0
private:
    void __cdecl restoreInvalid(void);  // 0x33afe0
};

class ManageSessionHandler
{
public:
    virtual bool __cdecl OnAccept(::Session const *) const;  // 0x33a210
    virtual bool __cdecl OnConnect(::Session const *, bool) const;  // 0x33a250
    virtual void __cdecl OnClose(::Session const *, bool) const;  // 0x33a290
    virtual bool __cdecl PacketHandler(::Session const *, ::Packet const *) const;  // 0x33a2d0
    static bool __cdecl QaCommandPacketHandler(::Session const *, ::Packet const *);  // 0x33a6c0
};

class NPMessageHandleEvent
{
public:
    virtual __cdecl ~NPMessageHandleEvent(void);  // 0x33aed0
    virtual bool __cdecl HandleEvent(::EventContext *, unsigned long);  // 0x33af60
};

class SeasonContentsTypes
{
public:
    bool __cdecl Add(wchar_t const *);  // 0x339f30
};

class TimeBasedPlaySeasonSchedule
{
public:
    struct Data;
    struct Rule;
public:
    __cdecl TimeBasedPlaySeasonSchedule(void);  // 0x1ee630
    bool __cdecl Decompose(::RepeatPacketDecomposer &, ::Packet const *);  // 0x33b040
};

struct TimeBasedPlaySeasonSchedule::Data
{
public:
    __cdecl Data(void);  // 0x1ee5b0
};

struct TimeBasedPlaySeasonSchedule::Rule
{
public:
    __cdecl Rule(void);  // 0x1ee590

    short minutes;      // +0x00
    int rewardList[4];  // +0x04
};
static_assert(sizeof(TimeBasedPlaySeasonSchedule::Rule) == 0x14, "sizeof TimeBasedPlaySeasonSchedule::Rule");

unsigned __int64 __cdecl GenerateTid(void);  // 0x339ee0
int wmain(int, wchar_t**);  // 0x33a190
