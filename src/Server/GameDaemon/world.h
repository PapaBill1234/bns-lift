// world.h: world.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class GuildTimerJobPriorityQueue
{
public:
    bool __cdecl Push(::GuildPriorityQueueJob *);  // 0x3fb800
    void __cdecl Clear(void);  // 0x3fb930
};

class PcIdManager
{
protected:
    virtual bool __cdecl IsExist(unsigned __int64);  // 0x3ec290
};

class SummonedIdManager
{
protected:
    virtual bool __cdecl IsExist(unsigned __int64);  // 0x3ec300
};

class World
{
public:
    struct ChannelList {};
public:
    __cdecl World(void);  // 0x3ec370
    __cdecl ~World(void);  // 0x3ec570
    void __cdecl PreInitialize(void);  // 0x3ed0a0
    bool __cdecl Initialize(void);  // 0x3ed400
    void __cdecl ChangeZoneBroadcastEncryptParam(int);  // 0x3ed8a0
    void __cdecl ChangeZoneRecommendPcCount(int *, int *, int);  // 0x3ed9f0
private:
    void __cdecl initZoneManager(void);  // 0x3edbb0
    void __cdecl initPcManager(void);  // 0x3eddc0
    void __cdecl initSummonedManager(void);  // 0x3edfd0
    void __cdecl initRaidDungeonManager(void);  // 0x3ee0d0
    void __cdecl initGuildManager(void);  // 0x3ee190
    void __cdecl initTradeShelfManager(void);  // 0x3ee5b0
public:
    void __cdecl Close(void);  // 0x3ee670
    bool __cdecl Start(char, char);  // 0x3ee940
private:
    void __cdecl clearTradeShelfManager(void);  // 0x3ef870
    void __cdecl clearZoneManager(void);  // 0x3ef9b0
    void __cdecl clearPcManager(void);  // 0x3efe30
    void __cdecl clearSummonedManager(void);  // 0x3efee0
    void __cdecl clearRaidDungeonManager(void);  // 0x3f0060
    void __cdecl clearGuildManager(void);  // 0x3f01a0
public:
    int __cdecl CreatePersistentZone(void);  // 0x3f0380
    bool __cdecl Enter(::Pc *, unsigned __int64, int, int, int, int);  // 0x3f0a20
    bool __cdecl EnterArena(::Pc *);  // 0x3f0e30
    bool __cdecl ReturnToGame(::Pc *, unsigned int, ::vector16, bool);  // 0x3f1570
private:
    void __cdecl leave(::Pc *, unsigned __int64, bool &, bool);  // 0x3f17a0
public:
    int __cdecl GetMaxChannelCount(unsigned int);  // 0x3f1af0
    unsigned __int64 __cdecl CreateZone(unsigned int, unsigned __int64, char, bool, bool, bool);  // 0x3f1b30
    void __cdecl DestroyZone(unsigned __int64);  // 0x3f1fa0
private:
    static void __cdecl destroyZone(::RefCntObject *, ::RefCntObject *, ::RefCntObject *);  // 0x3f21b0
    void __cdecl destroyZone(unsigned __int64, ::Zone *);  // 0x3f2210
public:
    void __cdecl DestroyExpiredZone(void);  // 0x3f22c0
    ::Zone * __cdecl AcquireZone(unsigned __int64);  // 0x3f2350
    ::Pointer2< ::Zone> __cdecl GetZonePtr(unsigned __int64);  // 0x3f23f0
protected:
    ::Zone * __cdecl findZone(unsigned int);  // 0x3f24e0
    ::Zone * __cdecl findPublicRaidZone(::Pc *, ::ArenaRoom *);  // 0x3f2540
public:
    void __cdecl DestroyPc(unsigned __int64, bool);  // 0x3f26d0
    ::BuilderChannel * __cdecl GetPcBuilderChannel(unsigned __int64);  // 0x3f2920
    void __cdecl SetPcBuilderChannel(::BuilderChannel *);  // 0x3f2a00
    void __cdecl ResetPcBuilderChannel(unsigned __int64);  // 0x3f2ac0
    unsigned __int64 __cdecl CreatePrePlayPc(::Pc **, char);  // 0x3f2b80
    bool __cdecl RegisterPc(::Pc *, unsigned __int64);  // 0x3f2d60
    bool __cdecl ReplacePc(::User *, ::Pc *, ::FragmentPacketConcatenater *);  // 0x3f30a0
    ::Pc * __cdecl AcquirePc(unsigned __int64);  // 0x3f3ab0
    ::Pointer2< ::Pc> __cdecl GetPcPtr(unsigned __int64, short);  // 0x3f3b90
    ::Pointer2< ::Pc> __cdecl GetPcPtr(wchar_t const *, short);  // 0x3f3d60
    ::Pointer2< ::Pc> __cdecl GetPcPtrWithBuilderId(unsigned __int64, short);  // 0x3f3fb0
    int __cdecl AcquireAllPc(::Pc **const);  // 0x3f40f0
    void __cdecl ReleaseAllPc(::Pc **const, int);  // 0x3f41a0
    unsigned __int64 __cdecl CreateSummoned(::Pc *, ::Summoned **);  // 0x3f42c0
    void __cdecl DestroySummoned(unsigned __int64);  // 0x3f45f0
    ::Pointer2< ::Summoned> __cdecl GetSummonedPtr(unsigned __int64);  // 0x3f46c0
    bool __cdecl PushGuildId(unsigned __int64);  // 0x3f47f0
    unsigned __int64 __cdecl PopGuildId(void);  // 0x3f4880
    unsigned __int64 __cdecl PopGuildIdForGuildContentsList(void);  // 0x3f48e0
    ::Pointer2< ::Guild> __cdecl AddGuild(::LoadGuildInfo const *);  // 0x3f4940
    bool __cdecl CreateGuild(unsigned __int64, char, char, wchar_t const *, __int64, ::Pc *);  // 0x3f4c60
    bool __cdecl CreateGuild(unsigned __int64, char, char, wchar_t const *, __int64, wchar_t const *, unsigned __int64, short, __int64);  // 0x3f52a0
    bool __cdecl RenameGuild(unsigned __int64, wchar_t const *, __int64);  // 0x3f57d0
    void __cdecl DestroyGuild(unsigned __int64);  // 0x3f5c10
    short __cdecl RenameGuildByManagement(unsigned __int64, wchar_t const *);  // 0x3f5cf0
    ::Pointer2< ::Guild> __cdecl GetGuildPtr(unsigned __int64);  // 0x3f6130
    ::Pointer2< ::Guild> __cdecl GetGuildPtr(wchar_t const *);  // 0x3f6210
    bool __cdecl JoinChattingChannel(char, ::Pc *, char &);  // 0x3f63b0
    bool __cdecl LeaveChattingChannel(char, short, ::Pc *);  // 0x3f6610
    void __cdecl SendMessageInChattingChannel(char, ::Pc *, int, wchar_t const *, wchar_t const *);  // 0x3f67a0
    void __cdecl SendPacketToWorldPc(char const *, ...);  // 0x3f6900
    void __cdecl DecreasePublicRaidReserveCount(::Pc *, unsigned __int64);  // 0x3f69e0
    bool __cdecl AvailableChannel(unsigned int, short, bool);  // 0x3f6b70
    bool __cdecl DisableChannel(unsigned int, short, bool);  // 0x3f6c80
private:
    bool __cdecl getChannelEnable(::World::ChannelList *, short);  // 0x3f6e00
protected:
    ::Guild * __cdecl findGuild(unsigned __int64);  // 0x3f6e50
    void __cdecl removeGuildList(unsigned __int64);  // 0x3f6ec0
    void __cdecl removeGuildName(wchar_t const *);  // 0x3f6f40
public:
    void __cdecl KeepSerializer(::ZoneSerializer *, unsigned __int64);  // 0x3f70d0
private:
    static bool __cdecl checkSerializer(void *);  // 0x3f71c0
    static void __cdecl deleteSerializer(void *);  // 0x3f7210
public:
    bool __cdecl PostWSO(::WorldSerializedObject *, long);  // 0x3f72a0
    bool __cdecl PostWSOFromExternal(::WorldSerializedObject *);  // 0x3f72e0
    bool __cdecl PostTSO(::WorldSerializedObject *, long);  // 0x3f7340
    void __cdecl AddArenaGuildName(unsigned __int64, char, wchar_t const *, bool, char *const);  // 0x3f7380
    bool __cdecl GetArenaGuildName(unsigned __int64, char, wchar_t *, int, bool &, char *const);  // 0x3f75d0
    void __cdecl RenameArenaGuild(unsigned __int64, wchar_t const *);  // 0x3f76e0
    bool __cdecl GetGuildName(unsigned __int64, wchar_t *, int);  // 0x3f77e0
    bool __cdecl ReserveZone(::Zone *, ::Pc *);  // 0x3f7900
private:
    bool __cdecl getGeoZoneByDeprecatedZone(unsigned int *, ::Pc *, unsigned __int64 *, int *);  // 0x3f7970
public:
    unsigned __int64 __cdecl GetReentrancePcSpawnKey(unsigned int, ::Pc *);  // 0x3f7ab0
private:
    unsigned __int64 __cdecl getZoneToEnter2(unsigned int *, ::Pc *, unsigned __int64 *, bool, char, bool);  // 0x3f7c00
    unsigned __int64 __cdecl getZoneToEnter2(unsigned int, ::Pc *, short);  // 0x3f86a0
    unsigned __int64 __cdecl getZoneInChannel2(unsigned int, ::Pc *, unsigned __int64);  // 0x3f88e0
    unsigned __int64 __cdecl getZoneInChannel2EventStageParty(unsigned int, ::Pc *, char, char, bool);  // 0x3f9040
    unsigned __int64 __cdecl getZoneInChannel2EventStageSolo(unsigned int, ::Pc *, char, char, bool);  // 0x3f9460
    unsigned __int64 __cdecl getZoneInChannel2EventStage(unsigned int, ::Pc *, char, char, bool);  // 0x3f9880
    unsigned __int64 __cdecl getZoneInChannel2FactionBattleField(unsigned int, ::Pc *);  // 0x3f9a00
    unsigned __int64 __cdecl getZoneInChannel2TendencyFactionBattleField(unsigned int, ::Pc *);  // 0x3f9f90
    unsigned __int64 __cdecl getZoneInChannel2GuildBattleField(unsigned int, ::Pc *);  // 0x3fa670
    unsigned __int64 __cdecl getZoneInChannel2WarField(unsigned int, ::Pc *);  // 0x3fa8f0
    unsigned __int64 __cdecl createZone2(unsigned int, bool, unsigned __int64, char, ::Pc *, short, ::ArenaRoom *, char);  // 0x3fab80
public:
    __int64 __cdecl AddTradeShelf(::TradeShelf2 *);  // 0x3fb150
    ::Pointer2< ::TradeShelf2> __cdecl RemoveTradeShelf(__int64);  // 0x3fb220
    bool __cdecl AddGuildPriorityQueueJob(::GuildPriorityQueueJob *);  // 0x3fb340
protected:
    void __cdecl processPQGuildCraftTimerJob(void);  // 0x3fb450
public:
    bool __cdecl ComposeGuildInfoList(::FragmentPacket &);  // 0x3fb9c0
};

class WorldClock
{
public:
    virtual __cdecl ~WorldClock(void);  // 0x3ebfb0
    virtual bool __cdecl HandleEvent(::EventContext *, unsigned long);  // 0x3ec040
protected:
    bool __cdecl start(char, char);  // 0x3ec0a0
    bool __cdecl reset(char, char);  // 0x3ec140
};

class ZoneIdManager
{
protected:
    virtual bool __cdecl IsExist(unsigned __int64);  // 0x3ec1f0
};

