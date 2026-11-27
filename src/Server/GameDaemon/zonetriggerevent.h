// zonetriggerevent.h: zonetriggerevent.cpp, zonetriggerevent.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class ZoneEventSingleStage
{
public:
    bool __cdecl Init(char, ::Data::ZoneTriggerEventStageRecordStagePtr *const);  // 0x682f30
};

class ZoneEventStage
{
public:
    __cdecl ZoneEventStage(void);  // 0x6820c0
protected:
    void __cdecl despawnNpcGroup(::Zone *, ::Data::NpcResetStageRecordPtr const &) const;  // 0x6821f0
    void __cdecl spawnNpcGroup(::Zone *, ::Data::NpcResetStageRecordPtr const &) const;  // 0x6822f0
    void __cdecl doEnvOperation(::Zone *, ::Data::NpcResetStageRecordPtr const &) const;  // 0x682430
    void __cdecl spawnNpcBySpawnIdRange(::Zone *, ::Data::NpcResetStageRecordPtr const &) const;  // 0x6825c0
    void __cdecl despawnNpcBySpawnIdRange(::Zone *, ::Data::NpcResetStageRecordPtr const &) const;  // 0x682810
public:
    bool __cdecl SetupNextStage(::Zone *, char, char);  // 0x6829a0
    bool __cdecl SetupFailStage(::Zone *, char);  // 0x682ab0
};

class ZoneTriggerEvent
{
public:
    enum TriggerEvent {};
public:
    static bool __cdecl Cmp(__int64, __int64, char, unsigned __int64);  // 0x6760f0
    char __cdecl NextBranch(void);  // 0x6832d0
};

class ZoneEventStageContext
{
public:
    bool __cdecl InitEventStage(::ZoneEventStageManager *, ::ZoneEventStage *);  // 0x683fe0
private:
    ::ZoneTriggerEvent * __cdecl createEvent(::Data::ZoneTriggerEventCondRecordPtr const &);  // 0x6842b0
public:
    void __cdecl SetZoneModeContext(::Zone const *);  // 0x684700
private:
    void __cdecl onNextStageStarted(::Zone const *, ::ZoneTriggerEvent *);  // 0x684790
    void __cdecl onStageFinished(::Zone *);  // 0x684880
    void __cdecl clear(void);  // 0x684a20
public:
    ::ZoneTriggerEvent * __cdecl CheckNextEvent(::Zone *, ::ZoneTriggerEvent::TriggerEvent, unsigned __int64);  // 0x684bf0
    ::ZoneTriggerEvent * __cdecl CheckFailEvent(::Zone *, ::ZoneTriggerEvent::TriggerEvent, unsigned __int64);  // 0x684d00
    bool __cdecl SetupNextStage(::Zone *, ::ZoneEventStageContext *, ::ZoneTriggerEvent *, bool &);  // 0x684e10
    bool __cdecl SetupFailStage(::Zone *, ::ZoneEventStageContext *, unsigned __int64);  // 0x684fd0
};

class ZoneEventStageManager
{
public:
    __cdecl ~ZoneEventStageManager(void);  // 0x6851e0
    bool __cdecl Init(::Zone *);  // 0x685290
    void __cdecl SetTotalDurationTime(char);  // 0x685880
    void __cdecl SetTimer(::Zone *);  // 0x685920
    void __cdecl HandleTriggerEvent(::Zone *, ::ZoneTriggerEvent::TriggerEvent, unsigned __int64);  // 0x685b00
private:
    bool __cdecl startNextStage(::Zone *, ::ZoneTriggerEvent *, bool &);  // 0x685e50
    bool __cdecl startFailStage(::Zone *, unsigned __int64);  // 0x6860f0
public:
    bool __cdecl FetchZoneModeInfo(::FragmentPacket &);  // 0x6862e0
private:
    void __cdecl writeDICLog(::Zone *, char, char, char, char);  // 0x686410
};

class ZoneEventStageStandBy
{
public:
    bool __cdecl Init(::Data::ZoneTriggerEventStageRecordPtr &);  // 0x682ba0
};

class ZoneTriggerBossChallengeBossNpcKilledEvent
{
public:
    virtual ::Data::ZoneTriggerEventCondRecordPtr __cdecl GetData(void);  // 0x6761c0
    virtual bool __cdecl CheckEventCond(::Zone *, unsigned __int64);  // 0x683e00
    virtual bool __cdecl PostExecute(::Zone *, bool &);  // 0x683f20
};

class ZoneTriggerBossChallengeRoundScoreEvent
{
public:
    virtual bool __cdecl CheckEventCond(::Zone *, unsigned __int64);  // 0x683c20
    virtual bool __cdecl PostExecute(::Zone *, bool &);  // 0x683dd0
};

class ZoneTriggerBossChallengeTimeoutEvent
{
public:
    virtual bool __cdecl CheckEventCond(::Zone *, unsigned __int64);  // 0x683ae0
    virtual bool __cdecl PostExecute(::Zone *, bool &);  // 0x683bf0
};

class ZoneTriggerNpcKilledEvent
{
public:
    virtual bool __cdecl CheckEventCond(::Zone *, unsigned __int64);  // 0x683620
    virtual void __cdecl ResetContext(void);  // 0x6836d0
};

class ZoneTriggerNpcKilledEvent2
{
public:
    virtual ::Data::ZoneTriggerEventCondRecordPtr __cdecl GetData(void);  // 0x6761d0
    virtual bool __cdecl CheckEventCond(::Zone *, unsigned __int64);  // 0x683700
    virtual void __cdecl ResetContext(void);  // 0x683780
};

class ZoneTriggerNpcSurvivedScoreDecisionTimeoutEvent
{
public:
    virtual bool __cdecl CheckEventCond(::Zone *, unsigned __int64);  // 0x683790
private:
    bool __cdecl checkScoreCond(::Zone *);  // 0x683960
};

class ZoneTriggerNpcSurvivedTimeoutEvent
{
public:
    virtual bool __cdecl CheckEventCond(::Zone *, unsigned __int64);  // 0x683a10
};

class ZoneTriggerTimeoutEvent
{
public:
    virtual bool __cdecl CheckEventCond(::Zone *, unsigned __int64);  // 0x683530
};

class ZoneTriggerWeeklyEvent
{
public:
    virtual bool __cdecl CheckEventCond(::Zone *, unsigned __int64);  // 0x683310
};

