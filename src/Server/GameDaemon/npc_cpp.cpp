// npc_cpp.cpp: npc.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "npc.h"
#include "action.h"
#include "combatsequence.h"
#include "contribution.h"
#include "creature.h"
#include "gameobject.h"
#include "item.h"
#include "npcspawn.h"
#include "pc.h"
#include "raiddungeon.h"
#include "zone.h"
#include "LiftStub.h"

// 0x40f630
__cdecl Npc::Npc(::Zone *, ::Data::NpcRecordPtr, ::NpcSpawnInfo)
{
    LIFT_STUB(0x40f630);
}

// 0x40f950
__cdecl Npc::~Npc(void)
{
    LIFT_STUB(0x40f950);
}

// 0x40fba0
bool __cdecl Npc::Initialize(unsigned __int64, ::NpcSpawnParam const &)
{
    LIFT_STUB(0x40fba0);
}

// 0x40fd30
void __cdecl Npc::EnterZone(::EnterReason, bool, unsigned int)
{
    LIFT_STUB(0x40fd30);
}

// 0x4101a0
void __cdecl Npc::EnterBossChallengeAttraction(::EnterReason, bool, unsigned int, unsigned __int64 *const, char)
{
    LIFT_STUB(0x4101a0);
}

// 0x4102b0
void __cdecl Npc::EnterAttraction(void)
{
    LIFT_STUB(0x4102b0);
}

// 0x410500
::NpcContribution * __cdecl Npc::createContribution(void)
{
    LIFT_STUB(0x410500);
}

// 0x410680
::Data::ContributionRewardRecordPtr __cdecl Npc::getContributionRewardData(void)
{
    LIFT_STUB(0x410680);
}

// 0x410750
void __cdecl Npc::LeaveZone(::LeaveReason)
{
    LIFT_STUB(0x410750);
}

// 0x410810
void __cdecl Npc::GetImmuneEffectAttributeValueFromData(unsigned __int64 &, unsigned __int64 &, unsigned __int64 &)
{
    LIFT_STUB(0x410810);
}

// 0x4108a0
bool __cdecl Npc::ProgressRaidDungeonStep(unsigned __int64)
{
    LIFT_STUB(0x4108a0);
}

// 0x410c00
bool __cdecl Npc::SetDead(bool, ::ChangedProperty *, unsigned __int64, unsigned __int64, unsigned __int64, bool, bool)
{
    LIFT_STUB(0x410c00);
}

// 0x410ee0
void __cdecl Npc::loadData(void)
{
    LIFT_STUB(0x410ee0);
}

// 0x411540
bool __cdecl Npc::SetScript(unsigned __int64)
{
    LIFT_STUB(0x411540);
}

// 0x4115d0
void __cdecl Npc::SetImmuneBreakDisable(bool)
{
    LIFT_STUB(0x4115d0);
}

// 0x411650
bool __cdecl Npc::CheckImmuneBreak(::Creature *, ::Data::EffectRecord const *, ::ChangedProperty *)
{
    LIFT_STUB(0x411650);
}

// 0x411890
bool __cdecl Npc::Think(::ScriptEvent const *)
{
    LIFT_STUB(0x411890);
}

// 0x411930
bool __cdecl Npc::ChangeBrain(::Data::NpcBrainType, bool, bool)
{
    LIFT_STUB(0x411930);
}

// 0x411c90
void __cdecl Npc::ActionFinished(::Action *, ::NpcActionQueue::ActionExpiredReason)
{
    LIFT_STUB(0x411c90);
}

// 0x411d70
void __cdecl Npc::OnSpawn(void)
{
    LIFT_STUB(0x411d70);
}

// 0x411ed0
void __cdecl Npc::OnDespawn(void)
{
    LIFT_STUB(0x411ed0);
}

// 0x411fd0
bool __cdecl Npc::CreateDeadbody(void)
{
    LIFT_STUB(0x411fd0);
}

// 0x4131c0
void __cdecl Npc::SetDespawnSocial(unsigned __int64)
{
    LIFT_STUB(0x4131c0);
}

// 0x413210
bool __cdecl Npc::DespawnIfPending(void)
{
    LIFT_STUB(0x413210);
}

// 0x413250
void __cdecl Npc::ReserveDespawn(bool, bool, unsigned __int64, long)
{
    LIFT_STUB(0x413250);
}

// 0x4134f0
void __cdecl Npc::ReservePlaySocial(unsigned int, unsigned __int64, long, bool)
{
    LIFT_STUB(0x4134f0);
}

// 0x413710
void __cdecl Npc::OnAttacked(::Zone *, ::GameObject *, unsigned __int64, short)
{
    LIFT_STUB(0x413710);
}

// 0x4137c0
void __cdecl Npc::OnDamaged(::Zone *, ::GameObject *, unsigned int, __int64, __int64)
{
    LIFT_STUB(0x4137c0);
}

// 0x413d50
unsigned __int64 __cdecl Npc::Detect(void)
{
    LIFT_STUB(0x413d50);
}

// 0x413eb0
void __cdecl Npc::Rotate(short, bool)
{
    LIFT_STUB(0x413eb0);
}

// 0x414040
::Pointer2< ::RaidDungeon> __cdecl Npc::getRaidDungeon(::Pc *, ::Pc *, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x414040);
}

// 0x414290
int __cdecl Npc::getNewbieCount(::Pc *)
{
    LIFT_STUB(0x414290);
}

// 0x4143f0
void __cdecl Npc::OnKilled(::Zone *, ::GameObject *, unsigned __int64)
{
    LIFT_STUB(0x4143f0);
}

// 0x415400
void __cdecl Npc::sendNpcKilledEvent(::Pc *, unsigned __int64)
{
    LIFT_STUB(0x415400);
}

// 0x415600
void __cdecl Npc::sendNpcKilledEventParty(int, unsigned __int64 *const, bool, __int64, __int64)
{
    LIFT_STUB(0x415600);
}

// 0x4159d0
void __cdecl Npc::OnInvokeEffect(::Zone *, unsigned __int64, unsigned int, __int64, __int64, __int64)
{
    LIFT_STUB(0x4159d0);
}

// 0x415b60
void __cdecl Npc::OnInvokedEffect(::Zone *, unsigned __int64, unsigned int, __int64, __int64, __int64, char)
{
    LIFT_STUB(0x415b60);
}

// 0x415dd0
void __cdecl Npc::OnAttack(::Zone *, ::GameObject *, unsigned __int64, short)
{
    LIFT_STUB(0x415dd0);
}

// 0x415df0
void __cdecl Npc::OnDamage(::Zone *, ::GameObject *, unsigned int, __int64)
{
    LIFT_STUB(0x415df0);
}

// 0x415e10
void __cdecl Npc::OnKill(::Zone *, ::GameObject *, unsigned __int64, char, char)
{
    LIFT_STUB(0x415e10);
}

// 0x416010
void __cdecl Npc::distributeExp(::Pc &)
{
    LIFT_STUB(0x416010);
}

// 0x417870
void __cdecl Npc::giveFactionScore(::Pc &)
{
    LIFT_STUB(0x417870);
}

// 0x4179b0
void __cdecl Npc::SetAttackable(bool)
{
    LIFT_STUB(0x4179b0);
}

// 0x417a60
void __cdecl Npc::SetExceptionTarget(bool, ::ChangedProperty *)
{
    LIFT_STUB(0x417a60);
}

// 0x417ba0
bool __cdecl Npc::setFirstAttacker(::GameObject &)
{
    LIFT_STUB(0x417ba0);
}

// 0x417dc0
::GameFailReason __cdecl Npc::TalkStart(unsigned __int64)
{
    LIFT_STUB(0x417dc0);
}

// 0x417f10
void __cdecl Npc::TalkStop(unsigned __int64)
{
    LIFT_STUB(0x417f10);
}

// 0x417fd0
void __cdecl Npc::OnCombatStart(::Creature *, bool)
{
    LIFT_STUB(0x417fd0);
}

// 0x4185f0
void __cdecl Npc::OnCombatEnd(void)
{
    LIFT_STUB(0x4185f0);
}

// 0x418ad0
bool __cdecl Npc::DropFieldItem(::Pc *, short, char, bool, __int64, __int64, __int64, int, ::Pc *)
{
    LIFT_STUB(0x418ad0);
}

// 0x418e50
bool __cdecl Npc::CheckToManipulate(::Pc *, ::Item *, ::QuestRequiredItems const *)
{
    LIFT_STUB(0x418e50);
}

// 0x419180
void __cdecl Npc::Manipulate(::Pc *, ::Item *, ::QuestRequiredItems const *)
{
    LIFT_STUB(0x419180);
}

// 0x4199e0
void __cdecl Npc::UpdateWaypoint(void)
{
    LIFT_STUB(0x4199e0);
}

// 0x419a60
::HideType __cdecl Npc::CanChangeHide(bool, unsigned __int64 &)
{
    LIFT_STUB(0x419a60);
}

// 0x419b30
bool __cdecl Npc::Hide(::HideType)
{
    LIFT_STUB(0x419b30);
}

// 0x41a220
::CombatSequence * __cdecl Npc::GetCombatSequence(void) const
{
    LIFT_STUB(0x41a220);
}

// 0x41a260
bool __cdecl Npc::SetActSequence(unsigned __int64)
{
    LIFT_STUB(0x41a260);
}

// 0x41a2c0
bool __cdecl Npc::SetCombatSequence(unsigned __int64)
{
    LIFT_STUB(0x41a2c0);
}

// 0x41a320
unsigned __int64 __cdecl Npc::GetNextStopSocial(short &)
{
    LIFT_STUB(0x41a320);
}

// 0x41a4a0
::vector16 const __cdecl Npc::GetInitialCombatStartPos(void)
{
    LIFT_STUB(0x41a4a0);
}

// 0x41a5c0
bool __cdecl Npc::HandleStance(char, unsigned __int64 const *, int, ::ChangedProperty *)
{
    LIFT_STUB(0x41a5c0);
}

// 0x41a5f0
bool __cdecl Npc::changeMoveState(::CreatureMoveState, short, wchar_t *)
{
    LIFT_STUB(0x41a5f0);
}

// 0x41aa60
bool __cdecl Npc::IsExpiredCombatTimer(char)
{
    LIFT_STUB(0x41aa60);
}

// 0x41ab10
::Pointer2< ::Creature> __cdecl Npc::getFirstAttackerCreaturePtr(::Zone *)
{
    LIFT_STUB(0x41ab10);
}

// 0x41b1a0
bool __cdecl Npc::HasContribution(::Data::NpcRecordPtr)
{
    LIFT_STUB(0x41b1a0);
}

// 0x41b1e0
unsigned __int64 __cdecl Npc::GetTodayReward(::Data::NpcRecordPtr)
{
    LIFT_STUB(0x41b1e0);
}

// 0x41b2d0
unsigned __int64 __cdecl Npc::GetTodayPeaktimeReward(::Data::NpcRecordPtr)
{
    LIFT_STUB(0x41b2d0);
}

// 0x41b4f0
unsigned __int64 __cdecl Npc::GetTodayContributionReward(::Data::NpcRecordPtr)
{
    LIFT_STUB(0x41b4f0);
}

// 0x41b5e0
unsigned __int64 __cdecl Npc::GetTodayContributionPeaktimeReward(::Data::NpcRecordPtr)
{
    LIFT_STUB(0x41b5e0);
}

// 0x41b800
void __cdecl Npc::TakeFactionScore(::GameObject *)
{
    LIFT_STUB(0x41b800);
}

// 0x41ba20
__int64 __cdecl Npc::calculateAdditionalExpBonusByTestServer(__int64)
{
    LIFT_STUB(0x41ba20);
}

// 0x41ba80
void __cdecl Npc::TransferDamageToLeader(::GameObject *, __int64)
{
    LIFT_STUB(0x41ba80);
}
