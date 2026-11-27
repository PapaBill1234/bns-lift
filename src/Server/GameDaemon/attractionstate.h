// attractionstate.h: attractionstate.cpp, attractionstate.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "tendencymanager.h"

class AttractionReward
{
public:
    void __cdecl SetReward(unsigned __int64, unsigned __int64 *const, char *const, int);  // 0x4c4c0
    bool __cdecl SetRewardForBattleRoyalField(char, unsigned __int64, short);  // 0x4c540
    ::GameFailReason __cdecl TakeReward(::Pc *, short);  // 0x4c750
    void __cdecl SendAttractionRewardNotify(::Pc *);  // 0x4cb70
    void __cdecl Reset(void);  // 0x4cd90
};

class AttractionState
{
public:
    enum ERROR_REASON {};
public:
    virtual __cdecl ~AttractionState(void);  // 0x35e90
    virtual bool __cdecl CanChangeChannel(short, short &);  // 0x35ea0
    virtual void __cdecl FetchInZoneAttractionState(::FragmentPacket &);  // 0x4ce90
    void __cdecl LeaveZone(::Pc *, ::Data::ZonePcSpawnRecordPtr const &, ::LeaveReason, unsigned __int64, unsigned __int64);  // 0x4cf20
protected:
    bool __cdecl doNpcOperation(::Zone *, ::Data::NpcResetStageRecordPtr const &) const;  // 0x4d030
    void __cdecl doEnvOperation(::Zone *, ::Data::NpcResetStageRecordPtr const &) const;  // 0x4d330
};

class BossChallengeAttractionState
{
public:
    virtual wchar_t const * __cdecl GetTypeName(void);  // 0x35ec0
    virtual bool __cdecl Init(::Zone *, bool);  // 0x4d4e0
    virtual void __cdecl OnNpcKilled(::Zone *, ::GameObject *, ::Npc *, ::Data::ZoneNpcSpawnRecordPtr);  // 0x4d560
    virtual bool __cdecl AvailableNextStep(int, __int64);  // 0x4d840
    virtual bool __cdecl PostExecute(::Zone *, int, bool &);  // 0x4d8a0
private:
    bool __cdecl nextRound(bool &);  // 0x4d8f0
    void __cdecl spawnRoundNpcReset(::Zone *) const;  // 0x4d9c0
    void __cdecl spawnRoundBossNpc(::Zone *) const;  // 0x4db30
public:
    virtual bool __cdecl EnableInfiniteHyperEnergy(void) const;  // 0x4dbd0
private:
    // PDB layout (size 0x38). The base AttractionState holds only the vfptr (+0).
    int _bossChallengeDataId;          // +8 (0x8)
    short _requireScore;               // +12 (0xC)
    short _lastRound;                  // +14 (0xE)
    bool _isInfiniteHyperEnergyZone;   // +16 (0x10)
    __int64 _currentBossNpc;           // +24 (0x18)
    __int64 _currentSpawnBossNpc;      // +32 (0x20)
    __int64 _roundNpcReset;            // +40 (0x28)
    long _bossSpawnDelay;              // +48 (0x30)
    short _currentRound;               // +52 (0x34)
    short _currentScore;               // +54 (0x36)
};

class DuelAttractionState
{
public:
    virtual wchar_t const * __cdecl GetTypeName(void);  // 0x35ef0
    virtual ::GameType const __cdecl GetGameType(void) const;  // 0x50a70
    virtual bool __cdecl Init(::Zone *, bool);  // 0x50a90
    virtual void __cdecl FetchInZoneAttractionState(::FragmentPacket &);  // 0x50c50
    virtual void __cdecl FetchMembers(::FragmentPacket &);  // 0x50db0
    virtual void __cdecl OnZoneAttractionTimer(::Zone *);  // 0x50dc0
    virtual void __cdecl OnZoneAttractionEventTimer(::Zone *);  // 0x50dd0
    virtual bool __cdecl CanResurrect(::ControlledCreature const *);  // 0x50de0
    virtual bool __cdecl CanTakeAchievementReward(void);  // 0x50e10
    virtual void __cdecl OnDead(::Zone *, unsigned __int64, ::Creature *);  // 0x50e20
    virtual void __cdecl OnPostDead(::Zone *, ::Creature *);  // 0x50e50
    virtual void __cdecl OnDamagedEvent(::Zone *, ::ControlledCreature *const, ::Creature *, __int64);  // 0x50e80
    virtual void __cdecl SetRoomInfo(::Zone *, ::ArenaLobbyRoomInfo const &, bool);  // 0x50eb0
    virtual void __cdecl OnEntered(::Zone *, ::Creature *, ::EnterReason);  // 0x50ec0
    virtual bool __cdecl Leave(::Pc *);  // 0x50f00
private:
    // PDB layout (size 0x18). The base AttractionState holds only the vfptr (+0).
    ::DuelManager *_duelMgr;               // +8 (0x8)
    ::GameObjectTimer *_duelEventTimer;    // +16 (0x10)
};

class PartyBattleFieldAttractionState
{
public:
    virtual wchar_t const * __cdecl GetTypeName(void);  // 0x35f00
    virtual bool __cdecl Init(::Zone *, bool);  // 0x50f80
    virtual void __cdecl FetchInZoneAttractionState(::FragmentPacket &);  // 0x51100
    virtual void __cdecl FetchMembers(::FragmentPacket &);  // 0x51200
    virtual void __cdecl OnZoneAttractionTimer(::Zone *);  // 0x51210
    virtual bool __cdecl CanResurrect(::ControlledCreature const *);  // 0x51260
    virtual bool __cdecl CanTakeAchievementReward(void);  // 0x51280
    virtual bool __cdecl CanProgressQuest(unsigned __int64);  // 0x51290
    virtual void __cdecl OnDead(::Zone *, unsigned __int64, ::Creature *);  // 0x512b0
    virtual void __cdecl OnDamagedEvent(::Zone *, ::ControlledCreature *const, ::Creature *, __int64);  // 0x512e0
    virtual void __cdecl OnEnvManipulated(::Pc *, ::Env *, ::Data::ZoneEnv2RecordPtr const &, char, char);  // 0x51320
    virtual void __cdecl OnCanceledEnvManipulation(::Env *, ::Data::ZoneEnv2RecordPtr &, char, char);  // 0x51350
    virtual void __cdecl SetRoomInfo(::Zone *, ::ArenaLobbyRoomInfo const &, bool);  // 0x51370
    virtual bool __cdecl DisposeFieldItem(::Pc *, ::FieldItem *);  // 0x51380
    virtual void __cdecl OnEntered(::Zone *, ::Creature *, ::EnterReason);  // 0x513a0
    virtual bool __cdecl Leave(::Pc *);  // 0x513f0
    virtual bool __cdecl EnableInfiniteHyperEnergy(void) const;  // 0x51400
    virtual bool __cdecl CheckToManipulateEnv(::Pc *, ::Env *, ::Data::ZoneEnv2RecordPtr const &);  // 0x51410
    virtual bool __cdecl TryToManipulateEnv(::Pc *, ::Env *, ::Data::ZoneEnv2RecordPtr &);  // 0x51420
    virtual void __cdecl OnEnterFootSwitch(::Creature *, ::Env *, ::Data::ZoneEnv2RecordPtr const &);  // 0x51430
private:
    // PDB layout (size 0x18). The base AttractionState holds only the vfptr (+0).
    ::PartyBattleManager *_partyBattleMgr;         // +8 (0x8)
    ::GameObjectTimer *_partyBattleEventTimer;     // +16 (0x10)
};

class TendencyFieldAttractionState
{
public:
    virtual wchar_t const * __cdecl GetTypeName(void);  // 0x35ed0
    virtual ::GameType const __cdecl GetGameType(void) const;  // 0x35ee0
    __cdecl TendencyFieldAttractionState(void);  // 0x4dbe0
    void __cdecl AddTendencyScore(char, int);  // 0x4dcf0
    bool __cdecl DrainTendencyScores(int *);  // 0x4dd80
    void __cdecl SetStateByEvent(::Zone *, int, unsigned __int64, char, __int64, __int64, char);  // 0x4de00
    void __cdecl OnNotifyEvent(::Zone *, ::TendencyField::EventData const &);  // 0x4dfa0
private:
    bool __cdecl eventStandBy(::Zone *, __int64);  // 0x4e400
    bool __cdecl eventStart(::Zone *, __int64);  // 0x4e770
    bool __cdecl eventInProgress(::Zone *, __int64);  // 0x4e830
    bool __cdecl onInProgress(::Zone *, __int64);  // 0x4e930
    bool __cdecl eventFinish(::Zone *, __int64);  // 0x4eea0
    bool __cdecl onFinish(::Zone *, __int64);  // 0x4f1c0
public:
    virtual bool __cdecl Init(::Zone *, bool);  // 0x4f590
    virtual bool __cdecl OnZoneOpen(::Zone *, bool);  // 0x4f920
    virtual void __cdecl FetchInZoneAttractionState(::FragmentPacket &);  // 0x4f930
    virtual bool __cdecl IsPcSpawnWithSummoned(::EnterReason, short);  // 0x4fa50
    virtual void __cdecl OnLeaved(::Zone *, ::Creature *, ::LeaveReason);  // 0x4fa90
    virtual void __cdecl OnNpcKilled(::Zone *, ::GameObject *, ::Npc *, ::Data::ZoneNpcSpawnRecordPtr);  // 0x4fae0
    virtual ::AttractionState::ERROR_REASON __cdecl CanTeamAttractionWithTarget(::Pc *, ::Creature *);  // 0x4fc00
    virtual int __cdecl GetAdditionalBonus(::Pc *, ::ADDITIONAL_BONUS_TYPE);  // 0x4fd30
    virtual void __cdecl OnZoneAttractionTimer(::Zone *);  // 0x4fdc0
    virtual void __cdecl LeaveAttractionZone(::Pc *);  // 0x4fea0
    virtual bool __cdecl CanChangeChannel(short, short &);  // 0x50060
    virtual bool __cdecl EnableInfiniteHyperEnergy(void) const;  // 0x50120
    bool __cdecl CanManifestTendency(::Zone *) const;  // 0x50140
    virtual bool __cdecl DisableMoveToArena(void);  // 0x501f0
    virtual bool __cdecl DisableMoveToSkillTrainingRoom(void);  // 0x50200
    virtual bool __cdecl EnableChangeFactionCostume(void);  // 0x50210
    virtual bool __cdecl EnableSetGuildMeetingPlace(void);  // 0x50220
    virtual bool __cdecl EnableWarpToGuildMember(void);  // 0x50230
private:
    void __cdecl executeStandByNpcResetStage(::Zone *, char) const;  // 0x50240
    void __cdecl executeTendencyNpcResetStage(::Zone *, char) const;  // 0x50450
    void __cdecl executeVictoryNpcResetStage(::Zone *, char) const;  // 0x505f0
    void __cdecl initEnvOperation(::Zone *) const;  // 0x50750
private:
    // PDB layout (size 0x228). The base AttractionState holds only the vfptr (+0).
    // LIFT: only the fields that the lifted bodies read are declared. The pads keep the PDB offsets.
    char lift_pad_8[0x48];              // ❓ PDB fields +8 to +0x4F (_tendencyScoreLock to _playable) are not declared yet
    void const *_tendencyFieldRecord;   // +80 (0x50) LIFT: PDB type Data::TendencyFieldRecordPtr (one pointer _record)
    char lift_pad_58[0x1C0];            // ❓ PDB fields +0x58 to +0x217 (_tendencyFieldDataKey to _victoryNpcResetStageTendency) are not declared yet
    int _targetType;                    // +536 (0x218) PDB type TendencyFieldTargetType
    bool _mainZone;                     // +540 (0x21C)
    ::GameType _gameType;               // +544 (0x220)
    int _eventStartStep;                // +548 (0x224) PDB type TendencyFieldAttractionState::EventStartStep
};

