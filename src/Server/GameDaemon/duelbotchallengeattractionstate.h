// duelbotchallengeattractionstate.h: duelbotchallengeattractionstate.cpp, duelbotchallengeattractionstate.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class DuelBotChallengeAttractionState
{
public:
    virtual wchar_t const * __cdecl GetTypeName(void);  // 0x97740
    __cdecl DuelBotChallengeAttractionState(void);  // 0xa3910
    virtual bool __cdecl Init(::Zone *, bool);  // 0xa3a00
private:
    bool __cdecl shuffleFloors(void);  // 0xa3b10
    bool __cdecl shuffleStrategicTools(void);  // 0xa3cb0
public:
    void __cdecl Start(::Pc *);  // 0xa3d50
    virtual void __cdecl OnEntered(::Zone *, ::Creature *, ::EnterReason);  // 0xa3ec0
    virtual void __cdecl OnLeaved(::Zone *, ::Creature *, ::LeaveReason);  // 0xa41b0
    virtual void __cdecl OnKill(::Zone *, ::GameObject *, ::Creature *);  // 0xa4370
    virtual void __cdecl OnZoneAttractionTimer(::Zone *);  // 0xa4480
    virtual void __cdecl OnCombatStart(::Zone *, ::Creature *, ::Creature *);  // 0xa4620
    bool __cdecl PickStrategicTool(::Pc *, char);  // 0xa48b0
    bool __cdecl UseStrategicTool(::Pc *, unsigned __int64);  // 0xa49e0
    virtual void __cdecl TakeAttractionReward(::Pc *);  // 0xa4bc0
    virtual void __cdecl ReviveByAttractionRule(::Pc *);  // 0xa4d80
    virtual void __cdecl LeaveAttractionZone(::Pc *);  // 0xa4dd0
    virtual void __cdecl FetchInZoneAttractionState(::FragmentPacket &);  // 0xa4eb0
private:
    void __cdecl onDuelBotKilled(::Zone *);  // 0xa4f60
    int __cdecl getStartFloor(int);  // 0xa51e0
    ::Pc * __cdecl getPlayer(::Zone *);  // 0xa5260
    void __cdecl initPlayerState(::Pc *);  // 0xa52c0
    void __cdecl finish(::Zone *, ::DuelBotChallengeEvent, int);  // 0xa56a0
    void __cdecl finishBySystemError(::Zone *);  // 0xa5a10
    void __cdecl giveRewardForSystemError(::Pc *);  // 0xa5bb0
    void __cdecl onFloorChanged(::Zone *);  // 0xa5e20
    unsigned __int64 __cdecl getNextDuelBotId(void);  // 0xa5ef0
    void __cdecl spawnDuelBot(::Zone *, unsigned __int64, long);  // 0xa6050
    void __cdecl combatDuelBot(::Zone *, unsigned __int64);  // 0xa6250
};

class DuelBotChallengeGameLog
{
public:
    static void __cdecl WriteDuelBotChallengeStageStart(::Pc *, ::GameLogDuelBotChallengeStageStartCode, wchar_t *, __int64, unsigned __int64 *const, __int64, char, bool, __int64, __int64, ::Data::DuelBotChallengeRecordPtr &, ::dr_vector16, __int64);  // 0xa6400
    static void __cdecl WriteDuelBotChallengeStageEnd(::Pc *, ::GameLogDuelBotChallengeStateCode, wchar_t *, __int64, unsigned __int64 *const, __int64, char, bool, __int64, __int64, __int64, __int64, __int64, ::Data::DuelBotChallengeRecordPtr &, __int64);  // 0xa68c0
    static void __cdecl WriteDuelBotChallengeReward(::Pc *, ::GameLogDuelBotChallengeStateCode, wchar_t *, __int64, __int64, __int64, __int64, __int64);  // 0xa6df0
    static void __cdecl WriteDuelBotChallengeRewardItem(::Pc *, ::GameLogDuelBotChallengeStateCode, wchar_t *, ::AttractionRewardItem);  // 0xa7100
    static void __cdecl WriteDuelBotChallengeScoreChange(::Pc *, ::GameLogDuelBotChallengeStateCode, wchar_t *, __int64, __int64, __int64, __int64, __int64, __int64, int, __int64, __int64);  // 0xa72c0
private:
    static unsigned __int64 * __cdecl getEffectKey(::Data::DuelBotChallengeRecordPtr &, short);  // 0xa7610
    static __int64 __cdecl getPcAttackPower(::Pc *);  // 0xae770
};

