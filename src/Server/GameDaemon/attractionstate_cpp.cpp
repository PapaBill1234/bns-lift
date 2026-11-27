// attractionstate_cpp.cpp: attractionstate.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
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
bool __cdecl BossChallengeAttractionState::AvailableNextStep(int, __int64)
{
    LIFT_STUB(0x4d840);
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
    LIFT_STUB(0x4dbd0);
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
bool __cdecl TendencyFieldAttractionState::DrainTendencyScores(int *)
{
    LIFT_STUB(0x4dd80);
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
    LIFT_STUB(0x50120);
}

// 0x50140
bool __cdecl TendencyFieldAttractionState::CanManifestTendency(::Zone *) const
{
    LIFT_STUB(0x50140);
}

// 0x501f0
bool __cdecl TendencyFieldAttractionState::DisableMoveToArena(void)
{
    LIFT_STUB(0x501f0);
}

// 0x50200
bool __cdecl TendencyFieldAttractionState::DisableMoveToSkillTrainingRoom(void)
{
    LIFT_STUB(0x50200);
}

// 0x50210
bool __cdecl TendencyFieldAttractionState::EnableChangeFactionCostume(void)
{
    LIFT_STUB(0x50210);
}

// 0x50220
bool __cdecl TendencyFieldAttractionState::EnableSetGuildMeetingPlace(void)
{
    LIFT_STUB(0x50220);
}

// 0x50230
bool __cdecl TendencyFieldAttractionState::EnableWarpToGuildMember(void)
{
    LIFT_STUB(0x50230);
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
    LIFT_STUB(0x50a70);
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
    LIFT_STUB(0x50dd0);
}

// 0x50de0
bool __cdecl DuelAttractionState::CanResurrect(::ControlledCreature const *)
{
    LIFT_STUB(0x50de0);
}

// 0x50e10
bool __cdecl DuelAttractionState::CanTakeAchievementReward(void)
{
    LIFT_STUB(0x50e10);
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
bool __cdecl PartyBattleFieldAttractionState::CanResurrect(::ControlledCreature const *)
{
    LIFT_STUB(0x51260);
}

// 0x51280
bool __cdecl PartyBattleFieldAttractionState::CanTakeAchievementReward(void)
{
    LIFT_STUB(0x51280);
}

// 0x51290
bool __cdecl PartyBattleFieldAttractionState::CanProgressQuest(unsigned __int64)
{
    LIFT_STUB(0x51290);
}

// 0x512b0
void __cdecl PartyBattleFieldAttractionState::OnDead(::Zone *, unsigned __int64, ::Creature *)
{
    LIFT_STUB(0x512b0);
}

// 0x512e0
void __cdecl PartyBattleFieldAttractionState::OnDamagedEvent(::Zone *, ::ControlledCreature *const, ::Creature *, __int64)
{
    LIFT_STUB(0x512e0);
}

// 0x51320
void __cdecl PartyBattleFieldAttractionState::OnEnvManipulated(::Pc *, ::Env *, ::Data::ZoneEnv2RecordPtr const &, char, char)
{
    LIFT_STUB(0x51320);
}

// 0x51350
void __cdecl PartyBattleFieldAttractionState::OnCanceledEnvManipulation(::Env *, ::Data::ZoneEnv2RecordPtr &, char, char)
{
    LIFT_STUB(0x51350);
}

// 0x51370
void __cdecl PartyBattleFieldAttractionState::SetRoomInfo(::Zone *, ::ArenaLobbyRoomInfo const &, bool)
{
    LIFT_STUB(0x51370);
}

// 0x51380
bool __cdecl PartyBattleFieldAttractionState::DisposeFieldItem(::Pc *, ::FieldItem *)
{
    LIFT_STUB(0x51380);
}

// 0x513a0
void __cdecl PartyBattleFieldAttractionState::OnEntered(::Zone *, ::Creature *, ::EnterReason)
{
    LIFT_STUB(0x513a0);
}

// 0x513f0
bool __cdecl PartyBattleFieldAttractionState::Leave(::Pc *)
{
    LIFT_STUB(0x513f0);
}

// 0x51400
bool __cdecl PartyBattleFieldAttractionState::EnableInfiniteHyperEnergy(void) const
{
    LIFT_STUB(0x51400);
}

// 0x51410
bool __cdecl PartyBattleFieldAttractionState::CheckToManipulateEnv(::Pc *, ::Env *, ::Data::ZoneEnv2RecordPtr const &)
{
    LIFT_STUB(0x51410);
}

// 0x51420
bool __cdecl PartyBattleFieldAttractionState::TryToManipulateEnv(::Pc *, ::Env *, ::Data::ZoneEnv2RecordPtr &)
{
    LIFT_STUB(0x51420);
}

// 0x51430
void __cdecl PartyBattleFieldAttractionState::OnEnterFootSwitch(::Creature *, ::Env *, ::Data::ZoneEnv2RecordPtr const &)
{
    LIFT_STUB(0x51430);
}
