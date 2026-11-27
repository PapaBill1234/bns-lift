// attractionstate_cpp.cpp: attractionstate.cpp (GameDaemon PDB, 2019 + PDB).
#include "attractionstate.h"
#include "controlledcreature.h"
#include "creature.h"
#include "envobj.h"
#include "fielditem.h"
#include "gameobject.h"
#include "npc.h"
#include "pc.h"
#include "tendencymanager.h"
#include "zone.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?AvailableNextStep@BossChallengeAttractionState@@UEAA_NH_J@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?EnableInfiniteHyperEnergy@BossChallengeAttractionState@@UEBA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?DrainTendencyScores@TendencyFieldAttractionState@@QEAA_NPEAH@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?EnableInfiniteHyperEnergy@TendencyFieldAttractionState@@UEBA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?DisableMoveToArena@TendencyFieldAttractionState@@UEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?DisableMoveToSkillTrainingRoom@TendencyFieldAttractionState@@UEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?EnableChangeFactionCostume@TendencyFieldAttractionState@@UEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?EnableSetGuildMeetingPlace@TendencyFieldAttractionState@@UEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?EnableWarpToGuildMember@TendencyFieldAttractionState@@UEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetGameType@DuelAttractionState@@UEBA?BW4GameType@@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?OnZoneAttractionEventTimer@DuelAttractionState@@UEAAXPEAVZone@@@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?CanResurrect@DuelAttractionState@@UEAA_NPEBVControlledCreature@@@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?CanTakeAchievementReward@DuelAttractionState@@UEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?CanResurrect@PartyBattleFieldAttractionState@@UEAA_NPEBVControlledCreature@@@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?CanTakeAchievementReward@PartyBattleFieldAttractionState@@UEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?CanProgressQuest@PartyBattleFieldAttractionState@@UEAA_N_K@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?OnDead@PartyBattleFieldAttractionState@@UEAAXPEAVZone@@_KPEAVCreature@@@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?OnDamagedEvent@PartyBattleFieldAttractionState@@UEAAXPEAVZone@@QEAVControlledCreature@@PEAVCreature@@_J@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?OnEnvManipulated@PartyBattleFieldAttractionState@@UEAAXPEAVPc@@PEAVEnv@@AEBVZoneEnv2RecordPtr@Data@@DD@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?OnCanceledEnvManipulation@PartyBattleFieldAttractionState@@UEAAXPEAVEnv@@AEAVZoneEnv2RecordPtr@Data@@DD@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?DisposeFieldItem@PartyBattleFieldAttractionState@@UEAA_NPEAVPc@@PEAVFieldItem@@@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Leave@PartyBattleFieldAttractionState@@UEAA_NPEAVPc@@@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?EnableInfiniteHyperEnergy@PartyBattleFieldAttractionState@@UEBA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?CheckToManipulateEnv@PartyBattleFieldAttractionState@@UEAA_NPEAVPc@@PEAVEnv@@AEBVZoneEnv2RecordPtr@Data@@@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?TryToManipulateEnv@PartyBattleFieldAttractionState@@UEAA_NPEAVPc@@PEAVEnv@@AEAVZoneEnv2RecordPtr@Data@@@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?OnEnterFootSwitch@PartyBattleFieldAttractionState@@UEAAXPEAVCreature@@PEAVEnv@@AEBVZoneEnv2RecordPtr@Data@@@Z")  // LIFT: dead-strip keep (no live caller yet)

namespace
{
// LIFT: views of PDB classes that have no layout in the skeleton yet. Only the read fields and the called
// virtual slots are declared. Slot numbers and offsets are from the PDB.

// LIFT: view of GameObject (Id at +0x28). The high 16 bits of Id hold the object type (1 = Pc, 4 = Npc).
struct GameObjectView
{
    char lift_pad_0[0x28];
    unsigned __int64 Id;  // +40 (0x28)
};

inline unsigned short liftObjectType(void const *object)  // LIFT: no PDB name (inline HIWORD(Id))
{
    return static_cast<unsigned short>(static_cast<GameObjectView const *>(object)->Id >> 48);
}

inline unsigned __int64 liftObjectId(void const *object)  // LIFT: no PDB name (inline read of GameObject::Id)
{
    return static_cast<GameObjectView const *>(object)->Id;
}

// LIFT: view of Data::TendencyFieldRecord (size 0x208).
struct TendencyFieldRecordView
{
    char lift_pad_0[0x200];
    bool enable_infinite_hyper_energy;          // +512 (0x200)
    bool disable_move_to_arena;                 // +513 (0x201)
    bool disable_move_to_skill_training_room;   // +514 (0x202)
    bool enable_change_faction_costume;         // +515 (0x203)
    bool enable_set_guild_meeting_place;        // +516 (0x204)
    bool enable_warp_to_guild_member;           // +517 (0x205)
};

// LIFT: view of DuelRule (vfptr, 5 slots used).
class DuelRuleView
{
public:
    virtual void lift_slot0(void) = 0;  // ~DuelRule
    virtual void lift_slot1(void) = 0;  // CalcRoundResult
    virtual void lift_slot2(void) = 0;  // IsGameDone
    virtual void lift_slot3(void) = 0;  // CalcGameResult
    virtual bool CanResurrect(::Pc const *const) const = 0;  // slot 4
};

// LIFT: view of DuelManager (size 0xD4B0).
class DuelManagerView
{
public:
    virtual void lift_slot0(void) = 0;  // ~DuelManager
    virtual ::GameType const GetGameType(void) const = 0;  // slot 1
    virtual void lift_slot2(void) = 0;  // verifyDuelType
    virtual void lift_slot3(void) = 0;  // instantiateDuelRule
    virtual void lift_slot4(void) = 0;  // instantiateDuelTeam
    virtual void lift_slot5(void) = 0;  // handleOnDead
    virtual void lift_slot6(void) = 0;  // handleOnLeave
    virtual void OnEventTimer(void) = 0;  // slot 7

    char lift_pad_8[0x10];      // _data, _zone
    DuelRuleView *_rule;        // +24 (0x18)
    char lift_pad_20[0x20];     // _memberRule, _teams, _emcee
    int _gameState;             // +64 (0x40) PDB type DuelGameState
};

// LIFT: view of Data::PartyBattleFieldZoneRecord (size 0x140).
struct PartyBattleFieldZoneRecordView
{
    char lift_pad_0[0x104];
    bool enable_infinite_hyper_energy;  // +260 (0x104)
};

// LIFT: view of ArenaLobbyRoomInfo.
struct ArenaLobbyRoomInfoView
{
    char lift_pad_0[0x28];
    int _detailRule;  // +40 (0x28) PDB type Data::ArenaMatchingRuleDetailType
};

// LIFT: view of PartyBattleManager (size 0xD5F0, slots 0 to 23 declared).
class PartyBattleManagerView
{
public:
    virtual void lift_slot0(void) = 0;   // ~PartyBattleManager
    virtual void lift_slot1(void) = 0;   // GetGameType
    virtual void lift_slot2(void) = 0;   // Init
    virtual bool EnterByRevive(::Pc *) = 0;  // slot 3
    virtual bool Enter(::Pc *) = 0;  // slot 4
    virtual bool Leave(::Pc *) = 0;  // slot 5
    virtual void lift_slot6(void) = 0;   // Ready
    virtual void lift_slot7(void) = 0;   // EnterNpc
    virtual void lift_slot8(void) = 0;   // Start
    virtual void lift_slot9(void) = 0;   // Vote
    virtual void lift_slot10(void) = 0;  // Finish
    virtual void lift_slot11(void) = 0;  // OnTimer
    virtual void lift_slot12(void) = 0;  // CheckToFinishGame
    virtual bool CanResurrect(::Pc *) = 0;  // slot 13
    virtual bool CanTakeAchievementReward(void) = 0;  // slot 14
    virtual void lift_slot15(void) = 0;  // GetNearRespawnArea
    virtual bool CheckToManipulateEnv(::Pc *, ::Env *, ::Data::ZoneEnv2RecordPtr const &) = 0;  // slot 16
    virtual bool TryToManipulateEnv(::Pc *, ::Env *, ::Data::ZoneEnv2RecordPtr &) = 0;  // slot 17
    virtual void OnEnterFootSwitch(::Creature *, ::Env *, ::Data::ZoneEnv2RecordPtr const &) = 0;  // slot 18
    virtual void DisposeFieldItem(::Pc *, ::FieldItem *) = 0;  // slot 19
    virtual void OnDamaged(unsigned __int64, ::Creature *, __int64) = 0;  // slot 20
    virtual void OnDead(unsigned __int64, ::Pc *) = 0;  // slot 21
    virtual void OnEnvManipulated(::Pc *, ::Env *, ::Data::ZoneEnv2RecordPtr const &, char, char) = 0;  // slot 22
    virtual void OnCanceledEnvManipulation(::Env *, ::Data::ZoneEnv2RecordPtr &, char, char) = 0;  // slot 23

    PartyBattleFieldZoneRecordView const *_data;  // +8 (0x8) PDB type Data::PartyBattleFieldZoneRecordPtr (one pointer _record)
    char lift_pad_10[0x40];                       // _zone to _isGiveReward
    ArenaLobbyRoomInfoView _roomInfo;             // +80 (0x50)
};

inline DuelManagerView *liftDuel(::DuelManager *duelMgr)
{
    return reinterpret_cast<DuelManagerView *>(duelMgr);
}

inline PartyBattleManagerView *liftPartyBattle(::PartyBattleManager *partyBattleMgr)
{
    return reinterpret_cast<PartyBattleManagerView *>(partyBattleMgr);
}

inline TendencyFieldRecordView const *liftTendencyRecord(void const *record)
{
    return static_cast<TendencyFieldRecordView const *>(record);
}
}  // namespace

// 0x4c4c0
void __cdecl AttractionReward::SetReward(unsigned __int64, unsigned __int64 *const, char *const, int)
{
    LIFT_STUB(0x4c4c0);
}

// 0x4c540
bool __cdecl AttractionReward::SetRewardForBattleRoyalField(char, unsigned __int64, short)
{
    LIFT_STUB(0x4c540);
}

// 0x4c750
::GameFailReason __cdecl AttractionReward::TakeReward(::Pc *, short)
{
    LIFT_STUB(0x4c750);
}

// 0x4cb70
void __cdecl AttractionReward::SendAttractionRewardNotify(::Pc *)
{
    LIFT_STUB(0x4cb70);
}

// 0x4cd90
void __cdecl AttractionReward::Reset(void)
{
    LIFT_STUB(0x4cd90);
}

// 0x4ce90
void __cdecl AttractionState::FetchInZoneAttractionState(::FragmentPacket &)
{
    LIFT_STUB(0x4ce90);
}

// 0x4cf20
void __cdecl AttractionState::LeaveZone(::Pc *, ::Data::ZonePcSpawnRecordPtr const &, ::LeaveReason, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x4cf20);
}

// 0x4d030
bool __cdecl AttractionState::doNpcOperation(::Zone *, ::Data::NpcResetStageRecordPtr const &) const
{
    LIFT_STUB(0x4d030);
}

// 0x4d330
void __cdecl AttractionState::doEnvOperation(::Zone *, ::Data::NpcResetStageRecordPtr const &) const
{
    LIFT_STUB(0x4d330);
}

// 0x4d4e0
bool __cdecl BossChallengeAttractionState::Init(::Zone *, bool)
{
    LIFT_STUB(0x4d4e0);
}

// 0x4d560
void __cdecl BossChallengeAttractionState::OnNpcKilled(::Zone *, ::GameObject *, ::Npc *, ::Data::ZoneNpcSpawnRecordPtr)
{
    LIFT_STUB(0x4d560);
}

// 0x4d840
bool __cdecl BossChallengeAttractionState::AvailableNextStep(int step, __int64 value)
{
    if (step == 0)
    {
        return true;
    }

    if (step == 1)
    {
        // LIFT: inline body of the PDB function BossChallengeAttractionState::accumulateScore(short).
        short score = static_cast<short>(value);
        if (_currentScore + score > _requireScore)
        {
            score = _requireScore - _currentScore;
        }
        if (score > 0)
        {
            _currentScore += score;
        }
        return _currentScore >= _requireScore;
    }

    if (step == 2)
    {
        return value == _currentBossNpc;
    }

    return false;
}

// 0x4d8a0
bool __cdecl BossChallengeAttractionState::PostExecute(::Zone *, int, bool &)
{
    LIFT_STUB(0x4d8a0);
}

// 0x4d8f0
bool __cdecl BossChallengeAttractionState::nextRound(bool &)
{
    LIFT_STUB(0x4d8f0);
}

// 0x4d9c0
void __cdecl BossChallengeAttractionState::spawnRoundNpcReset(::Zone *) const
{
    LIFT_STUB(0x4d9c0);
}

// 0x4db30
void __cdecl BossChallengeAttractionState::spawnRoundBossNpc(::Zone *) const
{
    LIFT_STUB(0x4db30);
}

// 0x4dbd0
bool __cdecl BossChallengeAttractionState::EnableInfiniteHyperEnergy(void) const
{
    return _isInfiniteHyperEnergyZone;
}

// 0x4dbe0
__cdecl TendencyFieldAttractionState::TendencyFieldAttractionState(void)
{
    LIFT_STUB(0x4dbe0);
}

// 0x4dcf0
void __cdecl TendencyFieldAttractionState::AddTendencyScore(char, int)
{
    LIFT_STUB(0x4dcf0);
}

// 0x4dd80
bool __cdecl TendencyFieldAttractionState::DrainTendencyScores(int *scores)
{
    bool drained = false;

    AcquireSRWLockExclusive(&_tendencyScoreLock);
    for (int i = 0; i < 4; ++i)
    {
        int const score = _tendencyScore[i];
        scores[i] = score;
        _tendencyScore[i] = 0;
        drained |= score > 0;
    }
    ReleaseSRWLockExclusive(&_tendencyScoreLock);

    return drained;
}

// 0x4de00
void __cdecl TendencyFieldAttractionState::SetStateByEvent(::Zone *, int, unsigned __int64, char, __int64, __int64, char)
{
    LIFT_STUB(0x4de00);
}

// 0x4dfa0
void __cdecl TendencyFieldAttractionState::OnNotifyEvent(::Zone *, ::TendencyField::EventData const &)
{
    LIFT_STUB(0x4dfa0);
}

// 0x4e400
bool __cdecl TendencyFieldAttractionState::eventStandBy(::Zone *, __int64)
{
    LIFT_STUB(0x4e400);
}

// 0x4e770
bool __cdecl TendencyFieldAttractionState::eventStart(::Zone *, __int64)
{
    LIFT_STUB(0x4e770);
}

// 0x4e830
bool __cdecl TendencyFieldAttractionState::eventInProgress(::Zone *, __int64)
{
    LIFT_STUB(0x4e830);
}

// 0x4e930
bool __cdecl TendencyFieldAttractionState::onInProgress(::Zone *, __int64)
{
    LIFT_STUB(0x4e930);
}

// 0x4eea0
bool __cdecl TendencyFieldAttractionState::eventFinish(::Zone *, __int64)
{
    LIFT_STUB(0x4eea0);
}

// 0x4f1c0
bool __cdecl TendencyFieldAttractionState::onFinish(::Zone *, __int64)
{
    LIFT_STUB(0x4f1c0);
}

// 0x4f590
bool __cdecl TendencyFieldAttractionState::Init(::Zone *, bool)
{
    LIFT_STUB(0x4f590);
}

// 0x4f920
bool __cdecl TendencyFieldAttractionState::OnZoneOpen(::Zone *, bool)
{
    LIFT_STUB(0x4f920);
}

// 0x4f930
void __cdecl TendencyFieldAttractionState::FetchInZoneAttractionState(::FragmentPacket &)
{
    LIFT_STUB(0x4f930);
}

// 0x4fa50
bool __cdecl TendencyFieldAttractionState::IsPcSpawnWithSummoned(::EnterReason, short)
{
    // LIFT: needs the PDB vtable order (GetGameType is slot 3); the skeleton class has another order. See handoff e18.
    LIFT_STUB(0x4fa50);
}

// 0x4fa90
void __cdecl TendencyFieldAttractionState::OnLeaved(::Zone *, ::Creature *, ::LeaveReason)
{
    LIFT_STUB(0x4fa90);
}

// 0x4fae0
void __cdecl TendencyFieldAttractionState::OnNpcKilled(::Zone *, ::GameObject *, ::Npc *, ::Data::ZoneNpcSpawnRecordPtr)
{
    LIFT_STUB(0x4fae0);
}

// 0x4fc00
::AttractionState::ERROR_REASON __cdecl TendencyFieldAttractionState::CanTeamAttractionWithTarget(::Pc *, ::Creature *)
{
    LIFT_STUB(0x4fc00);
}

// 0x4fd30
int __cdecl TendencyFieldAttractionState::GetAdditionalBonus(::Pc *, ::ADDITIONAL_BONUS_TYPE)
{
    LIFT_STUB(0x4fd30);
}

// 0x4fdc0
void __cdecl TendencyFieldAttractionState::OnZoneAttractionTimer(::Zone *)
{
    LIFT_STUB(0x4fdc0);
}

// 0x4fea0
void __cdecl TendencyFieldAttractionState::LeaveAttractionZone(::Pc *)
{
    LIFT_STUB(0x4fea0);
}

// 0x50060
bool __cdecl TendencyFieldAttractionState::CanChangeChannel(short, short &)
{
    LIFT_STUB(0x50060);
}

// 0x50120
bool __cdecl TendencyFieldAttractionState::EnableInfiniteHyperEnergy(void) const
{
    if (liftTendencyFieldView(this)->_targetType == 0)  // TENDENCYFIELDTARGETTYPE_UNKNOWN; LIFT: form (jne to the read block)
    {
        return false;
    }
    return liftTendencyRecord(liftTendencyFieldView(this)->_tendencyFieldRecord)->enable_infinite_hyper_energy;
}

// 0x50140
bool __cdecl TendencyFieldAttractionState::CanManifestTendency(::Zone *) const
{
    LIFT_STUB(0x50140);
}

// 0x501f0
bool __cdecl TendencyFieldAttractionState::DisableMoveToArena(void)
{
    return liftTendencyRecord(liftTendencyFieldView(this)->_tendencyFieldRecord)->disable_move_to_arena;
}

// 0x50200
bool __cdecl TendencyFieldAttractionState::DisableMoveToSkillTrainingRoom(void)
{
    return liftTendencyRecord(liftTendencyFieldView(this)->_tendencyFieldRecord)->disable_move_to_skill_training_room;
}

// 0x50210
bool __cdecl TendencyFieldAttractionState::EnableChangeFactionCostume(void)
{
    return liftTendencyRecord(liftTendencyFieldView(this)->_tendencyFieldRecord)->enable_change_faction_costume;
}

// 0x50220
bool __cdecl TendencyFieldAttractionState::EnableSetGuildMeetingPlace(void)
{
    return liftTendencyRecord(liftTendencyFieldView(this)->_tendencyFieldRecord)->enable_set_guild_meeting_place;
}

// 0x50230
bool __cdecl TendencyFieldAttractionState::EnableWarpToGuildMember(void)
{
    return liftTendencyRecord(liftTendencyFieldView(this)->_tendencyFieldRecord)->enable_warp_to_guild_member;
}

// 0x50240
void __cdecl TendencyFieldAttractionState::executeStandByNpcResetStage(::Zone *, char) const
{
    LIFT_STUB(0x50240);
}

// 0x50450
void __cdecl TendencyFieldAttractionState::executeTendencyNpcResetStage(::Zone *, char) const
{
    LIFT_STUB(0x50450);
}

// 0x505f0
void __cdecl TendencyFieldAttractionState::executeVictoryNpcResetStage(::Zone *, char) const
{
    LIFT_STUB(0x505f0);
}

// 0x50750
void __cdecl TendencyFieldAttractionState::initEnvOperation(::Zone *) const
{
    LIFT_STUB(0x50750);
}

// 0x50a70
::GameType const __cdecl DuelAttractionState::GetGameType(void) const
{
    if (_duelMgr == nullptr)  // LIFT: form (cmp [rcx+8],0; jne to the call block)
    {
        return static_cast< ::GameType>(0);  // GAMETYPE_INVALID
    }
    return liftDuel(_duelMgr)->GetGameType();
}

// 0x50a90
bool __cdecl DuelAttractionState::Init(::Zone *, bool)
{
    LIFT_STUB(0x50a90);
}

// 0x50c50
void __cdecl DuelAttractionState::FetchInZoneAttractionState(::FragmentPacket &)
{
    LIFT_STUB(0x50c50);
}

// 0x50db0
void __cdecl DuelAttractionState::FetchMembers(::FragmentPacket &)
{
    LIFT_STUB(0x50db0);
}

// 0x50dc0
void __cdecl DuelAttractionState::OnZoneAttractionTimer(::Zone *)
{
    LIFT_STUB(0x50dc0);
}

// 0x50dd0
void __cdecl DuelAttractionState::OnZoneAttractionEventTimer(::Zone *)
{
    liftDuel(_duelMgr)->OnEventTimer();
}

// 0x50de0
bool __cdecl DuelAttractionState::CanResurrect(::ControlledCreature const *creature)
{
    // LIFT: DuelManager::CanResurrect(Pc const *) is inline here: it calls DuelRule::CanResurrect (slot 4).
    return creature != nullptr
        && liftObjectType(creature) == 1
        && liftDuel(_duelMgr)->_rule->CanResurrect(reinterpret_cast< ::Pc const *>(creature));
}

// 0x50e10
bool __cdecl DuelAttractionState::CanTakeAchievementReward(void)
{
    return liftDuel(_duelMgr)->_gameState != 3;  // DUELGAMESTATE_FINISHED
}

// 0x50e20
void __cdecl DuelAttractionState::OnDead(::Zone *, unsigned __int64, ::Creature *)
{
    LIFT_STUB(0x50e20);
}

// 0x50e50
void __cdecl DuelAttractionState::OnPostDead(::Zone *, ::Creature *)
{
    LIFT_STUB(0x50e50);
}

// 0x50e80
void __cdecl DuelAttractionState::OnDamagedEvent(::Zone *, ::ControlledCreature *const, ::Creature *, __int64)
{
    LIFT_STUB(0x50e80);
}

// 0x50eb0
void __cdecl DuelAttractionState::SetRoomInfo(::Zone *, ::ArenaLobbyRoomInfo const &, bool)
{
    LIFT_STUB(0x50eb0);
}

// 0x50ec0
void __cdecl DuelAttractionState::OnEntered(::Zone *, ::Creature *, ::EnterReason)
{
    LIFT_STUB(0x50ec0);
}

// 0x50f00
bool __cdecl DuelAttractionState::Leave(::Pc *)
{
    LIFT_STUB(0x50f00);
}

// 0x50f80
bool __cdecl PartyBattleFieldAttractionState::Init(::Zone *, bool)
{
    LIFT_STUB(0x50f80);
}

// 0x51100
void __cdecl PartyBattleFieldAttractionState::FetchInZoneAttractionState(::FragmentPacket &)
{
    LIFT_STUB(0x51100);
}

// 0x51200
void __cdecl PartyBattleFieldAttractionState::FetchMembers(::FragmentPacket &)
{
    LIFT_STUB(0x51200);
}

// 0x51210
void __cdecl PartyBattleFieldAttractionState::OnZoneAttractionTimer(::Zone *)
{
    LIFT_STUB(0x51210);
}

// 0x51260
bool __cdecl PartyBattleFieldAttractionState::CanResurrect(::ControlledCreature const *creature)
{
    // ❓ PartyBattleManager::CanResurrect takes a non-const Pc *; the cast of the const creature is an assumption.
    return creature != nullptr
        && liftObjectType(creature) == 1
        && liftPartyBattle(_partyBattleMgr)->CanResurrect(const_cast< ::Pc *>(reinterpret_cast< ::Pc const *>(creature)));
}

// 0x51280
bool __cdecl PartyBattleFieldAttractionState::CanTakeAchievementReward(void)
{
    return liftPartyBattle(_partyBattleMgr)->CanTakeAchievementReward();
}

// 0x51290
bool __cdecl PartyBattleFieldAttractionState::CanProgressQuest(unsigned __int64)
{
    // ❓ detail rules 3 to 5 of Data::ArenaMatchingRuleDetailType block quest progress; the enum names are not resolved.
    int const detailRule = liftPartyBattle(_partyBattleMgr)->_roomInfo._detailRule;
    return static_cast<unsigned int>(detailRule - 3) > 2;
}

// 0x512b0
void __cdecl PartyBattleFieldAttractionState::OnDead(::Zone *, unsigned __int64 attackerId, ::Creature *victim)
{
    if (victim != nullptr && liftObjectType(victim) == 1)
    {
        liftPartyBattle(_partyBattleMgr)->OnDead(attackerId, reinterpret_cast< ::Pc *>(victim));
    }
}

// 0x512e0
void __cdecl PartyBattleFieldAttractionState::OnDamagedEvent(::Zone *, ::ControlledCreature *const attacker, ::Creature *victim, __int64 damage)
{
    if (victim != nullptr && attacker != nullptr)
    {
        liftPartyBattle(_partyBattleMgr)->OnDamaged(liftObjectId(attacker), victim, damage);
    }
}

// 0x51320
void __cdecl PartyBattleFieldAttractionState::OnEnvManipulated(::Pc *pc, ::Env *env, ::Data::ZoneEnv2RecordPtr const &envData, char preState, char state)
{
    liftPartyBattle(_partyBattleMgr)->OnEnvManipulated(pc, env, envData, preState, state);
}

// 0x51350
void __cdecl PartyBattleFieldAttractionState::OnCanceledEnvManipulation(::Env *env, ::Data::ZoneEnv2RecordPtr &envData, char preState, char state)
{
    liftPartyBattle(_partyBattleMgr)->OnCanceledEnvManipulation(env, envData, preState, state);
}

// 0x51370
void __cdecl PartyBattleFieldAttractionState::SetRoomInfo(::Zone *, ::ArenaLobbyRoomInfo const &, bool)
{
    LIFT_STUB(0x51370);
}

// 0x51380
bool __cdecl PartyBattleFieldAttractionState::DisposeFieldItem(::Pc *pc, ::FieldItem *fieldItem)
{
    liftPartyBattle(_partyBattleMgr)->DisposeFieldItem(pc, fieldItem);
    return true;
}

// 0x513a0
void __cdecl PartyBattleFieldAttractionState::OnEntered(::Zone *, ::Creature *, ::EnterReason)
{
    LIFT_STUB(0x513a0);
}

// 0x513f0
bool __cdecl PartyBattleFieldAttractionState::Leave(::Pc *pc)
{
    return liftPartyBattle(_partyBattleMgr)->Leave(pc);
}

// 0x51400
bool __cdecl PartyBattleFieldAttractionState::EnableInfiniteHyperEnergy(void) const
{
    return liftPartyBattle(_partyBattleMgr)->_data->enable_infinite_hyper_energy;
}

// 0x51410
bool __cdecl PartyBattleFieldAttractionState::CheckToManipulateEnv(::Pc *pc, ::Env *env, ::Data::ZoneEnv2RecordPtr const &envData)
{
    return liftPartyBattle(_partyBattleMgr)->CheckToManipulateEnv(pc, env, envData);
}

// 0x51420
bool __cdecl PartyBattleFieldAttractionState::TryToManipulateEnv(::Pc *pc, ::Env *env, ::Data::ZoneEnv2RecordPtr &envData)
{
    return liftPartyBattle(_partyBattleMgr)->TryToManipulateEnv(pc, env, envData);
}

// 0x51430
void __cdecl PartyBattleFieldAttractionState::OnEnterFootSwitch(::Creature *creature, ::Env *env, ::Data::ZoneEnv2RecordPtr const &envData)
{
    liftPartyBattle(_partyBattleMgr)->OnEnterFootSwitch(creature, env, envData);
}
