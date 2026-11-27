// envobj_cpp.cpp: envobj.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "envobj.h"
#include "controlledcreature.h"
#include "creature.h"
#include "gameobject.h"
#include "item.h"
#include "itempouch.h"
#include "pc.h"
#include "zone.h"
#include "LiftStub.h"

// 0x596ac0
__cdecl Env::Env(void)
{
    LIFT_STUB(0x596ac0);
}

// 0x596bc0
__cdecl Env::~Env(void)
{
    LIFT_STUB(0x596bc0);
}

// 0x596c30
bool __cdecl Env::Initialize(unsigned __int64, ::Zone *, ::GeoEnvObj const *)
{
    LIFT_STUB(0x596c30);
}

// 0x596eb0
bool __cdecl Env::Think(::ScriptEvent const *)
{
    LIFT_STUB(0x596eb0);
}

// 0x596f20
void __cdecl Env::SetEnable(bool)
{
    LIFT_STUB(0x596f20);
}

// 0x5971c0
bool __cdecl Env::invokeEffect(::Creature *, ::Creature *, unsigned __int64)
{
    LIFT_STUB(0x5971c0);
}

// 0x597270
bool __cdecl Env::invokeMainFactionEffect(::Creature *, char)
{
    LIFT_STUB(0x597270);
}

// 0x597520
bool __cdecl Env::SetSession(unsigned __int64)
{
    LIFT_STUB(0x597520);
}

// 0x597560
void __cdecl Env::OnTimer(::Zone *, unsigned short)
{
    LIFT_STUB(0x597560);
}

// 0x5975a0
void __cdecl Env::onStateChange(::Zone *, char, char)
{
    LIFT_STUB(0x5975a0);
}

// 0x5976f0
void __cdecl Env::onEnableChange(::Zone *, bool)
{
    LIFT_STUB(0x5976f0);
}

// 0x597800
bool __cdecl Env::checkToManipulateQuestEnv(::Pc *, ::Item *, ::QuestRequiredItems const *, short &)
{
    LIFT_STUB(0x597800);
}

// 0x597ba0
bool __cdecl Env::checkToManipulateNormalEnv(::Pc *, unsigned __int64, short, ::Item *, unsigned __int64, short &)
{
    LIFT_STUB(0x597ba0);
}

// 0x597dc0
void __cdecl Env::manipulate(::Pc *, ::Item *, ::QuestRequiredItems const *)
{
    LIFT_STUB(0x597dc0);
}

// 0x598260
bool __cdecl Env::IsQuestEnv(void)
{
    LIFT_STUB(0x598260);
}

// 0x5982a0
bool __cdecl Env::DropFieldItem(::Pc *, short, char)
{
    LIFT_STUB(0x5982a0);
}

// 0x598550
::Env * __cdecl Env::Create(int, ::Zone *, ::GeoEnvObj const *)
{
    LIFT_STUB(0x598550);
}

// 0x5989f0
void __cdecl Env::setQuestLootItemProb(void)
{
    LIFT_STUB(0x5989f0);
}

// 0x598d70
bool __cdecl Env::LootQuestCase(::Pc *, char, unsigned short, char, char, ::LootFailReason &)
{
    LIFT_STUB(0x598d70);
}

// 0x5990c0
void __cdecl Env::FetchExceptLootCase(::FragmentPacket *)
{
    LIFT_STUB(0x5990c0);
}

// 0x599240
bool __cdecl Env::GetPos(::vector16 &)
{
    LIFT_STUB(0x599240);
}

// 0x599280
bool __cdecl Env::GetActionPoint(::vector16 &)
{
    LIFT_STUB(0x599280);
}

// 0x5992b0
bool __cdecl Env::GetManipulationCylinder(::cylinder16 &)
{
    LIFT_STUB(0x5992b0);
}

// 0x599310
bool __cdecl Env::CheckToManipulate(::Pc *, ::Item *, ::QuestRequiredItems const *, char, short &)
{
    LIFT_STUB(0x599310);
}

// 0x599570
void __cdecl Env::Manipulate(::Pc *, ::Item *, ::QuestRequiredItems const *, char)
{
    LIFT_STUB(0x599570);
}

// 0x599cb0
void __cdecl Env::ChangeState(char)
{
    LIFT_STUB(0x599cb0);
}

// 0x599d40
void __cdecl Env::DiffHp(::Creature *, int, short, unsigned __int64, unsigned int)
{
    LIFT_STUB(0x599d40);
}

// 0x599f20
bool __cdecl Env::IsMoveBlock(void)
{
    LIFT_STUB(0x599f20);
}

// 0x599f40
::ItemPouch * __cdecl Env::makeItemPouch(::Pc *, int)
{
    LIFT_STUB(0x599f40);
}

// 0x59a230
void __cdecl Env::InitState(void)
{
    LIFT_STUB(0x59a230);
}

// 0x59a3b0
bool __cdecl Env::UpdateItemPouch(void)
{
    LIFT_STUB(0x59a3b0);
}

// 0x59a410
bool __cdecl Env::CheckToLoot(::Pc *)
{
    LIFT_STUB(0x59a410);
}

// 0x59a430
void __cdecl Env::OnKilled(::Zone *, ::GameObject *, unsigned __int64)
{
    LIFT_STUB(0x59a430);
}

// 0x59a530
void __cdecl Env::OnDamaged(::Zone *, ::GameObject *, unsigned int, __int64)
{
    LIFT_STUB(0x59a530);
}

// 0x59a550
void __cdecl Env::OnAttacked(::Zone *, ::GameObject *, unsigned __int64, short)
{
    LIFT_STUB(0x59a550);
}

// 0x59a570
void __cdecl Env::setGuildBattleFieldGateEnable(bool)
{
    LIFT_STUB(0x59a570);
}

// 0x59a6a0
void __cdecl Env::SetGuildBattleFieldGateEnableOnly(bool)
{
    LIFT_STUB(0x59a6a0);
}

// 0x59a800
bool __cdecl Refiner::Initialize(unsigned __int64, ::Zone *, ::GeoEnvObj const *)
{
    LIFT_STUB(0x59a800);
}

// 0x59a840
void __cdecl Refiner::OnTimer(::Zone *, unsigned short)
{
    LIFT_STUB(0x59a840);
}

// 0x59aa40
::Refiner::Operation __cdecl Refiner::GetOperation(char, char)
{
    LIFT_STUB(0x59aa40);
}

// 0x59aab0
bool __cdecl Refiner::TakeReward(::Pc *)
{
    LIFT_STUB(0x59aab0);
}

// 0x59add0
bool __cdecl Refiner::CheckToGiveFactionScore(::Pc *)
{
    LIFT_STUB(0x59add0);
}

// 0x59ae20
bool __cdecl Refiner::GiveFactionScore(::Pc *, int &)
{
    LIFT_STUB(0x59ae20);
}

// 0x59b170
long __cdecl Refiner::GetManipulateDuration(char)
{
    LIFT_STUB(0x59b170);
}

// 0x59b250
bool __cdecl Refiner::CheckToManipulate(::Pc *, ::Item *, ::QuestRequiredItems const *, char, short &)
{
    LIFT_STUB(0x59b250);
}

// 0x59b3f0
void __cdecl Refiner::Manipulate(::Pc *, ::Item *, ::QuestRequiredItems const *, char)
{
    LIFT_STUB(0x59b3f0);
}

// 0x59b830
void __cdecl Refiner::ChangeState(char)
{
    LIFT_STUB(0x59b830);
}

// 0x59b960
void __cdecl Refiner::onOccopied(void)
{
    LIFT_STUB(0x59b960);
}

// 0x59b9c0
bool __cdecl Refiner::invokeGuildEffect(bool, unsigned __int64)
{
    LIFT_STUB(0x59b9c0);
}

// 0x59bc80
void __cdecl Refiner::InitState(void)
{
    LIFT_STUB(0x59bc80);
}

// 0x59bf40
bool __cdecl ControlPoint::CheckToManipulate(::Pc *, ::Item *, ::QuestRequiredItems const *, char, short &)
{
    LIFT_STUB(0x59bf40);
}

// 0x59c190
void __cdecl ControlPoint::Manipulate(::Pc *, ::Item *, ::QuestRequiredItems const *, char)
{
    LIFT_STUB(0x59c190);
}

// 0x59c1e0
void __cdecl ControlPoint::ChangeState(char)
{
    LIFT_STUB(0x59c1e0);
}

// 0x59c200
void __cdecl ControlPoint::InitState(void)
{
    LIFT_STUB(0x59c200);
}

// 0x59c310
void __cdecl ControlPoint::CancelOccupation(void)
{
    LIFT_STUB(0x59c310);
}

// 0x59c390
bool __cdecl ControlPoint::Initialize(unsigned __int64, ::Zone *, ::GeoEnvObj const *)
{
    LIFT_STUB(0x59c390);
}

// 0x59c3b0
bool __cdecl MultipleLoop::CheckToManipulate(::Pc *, ::Item *, ::QuestRequiredItems const *, char, short &)
{
    LIFT_STUB(0x59c3b0);
}

// 0x59c430
void __cdecl MultipleLoop::Manipulate(::Pc *, ::Item *, ::QuestRequiredItems const *, char)
{
    LIFT_STUB(0x59c430);
}

// 0x59c480
void __cdecl MultipleLoop::ChangeState(char)
{
    LIFT_STUB(0x59c480);
}

// 0x59c4a0
void __cdecl MultipleLoop::InitState(void)
{
    LIFT_STUB(0x59c4a0);
}

// 0x59c5e0
void __cdecl Portal::OnEntered(::Zone *, ::Creature *)
{
    LIFT_STUB(0x59c5e0);
}

// 0x59c8c0
void __cdecl EffectRegion::OnLeaved(::Zone *, ::Creature *)
{
    LIFT_STUB(0x59c8c0);
}

// 0x59c9e0
bool __cdecl Portal::GetPos(::vector16 &)
{
    LIFT_STUB(0x59c9e0);
}

// 0x59ca30
bool __cdecl Portal::GetActionPoint(::vector16 &)
{
    LIFT_STUB(0x59ca30);
}

// 0x59ca70
short __cdecl Portal::GetActionRadius(void)
{
    LIFT_STUB(0x59ca70);
}

// 0x59ca90
bool __cdecl Portal::GetManipulationCylinder(::cylinder16 &)
{
    LIFT_STUB(0x59ca90);
}

// 0x59cb00
bool __cdecl Portal::CheckToManipulate(::Pc *, ::Item *, ::QuestRequiredItems const *, char, short &)
{
    LIFT_STUB(0x59cb00);
}

// 0x59cd40
void __cdecl Portal::Manipulate(::Pc *, ::Item *, ::QuestRequiredItems const *, char)
{
    LIFT_STUB(0x59cd40);
}

// 0x59cdf0
bool __cdecl Portal::selectZone(::Creature *, int &, short &)
{
    LIFT_STUB(0x59cdf0);
}

// 0x59cff0
::GameFailReason __cdecl Portal::ApplyTransit(::Creature *)
{
    LIFT_STUB(0x59cff0);
}

// 0x59d500
bool __cdecl Portal::selectZoneByDungeonStep(unsigned __int64, ::Pc *, int &, short &)
{
    LIFT_STUB(0x59d500);
}

// 0x59d750
::GameFailReason __cdecl Portal::checkTransit(::Pc *, ::Data::ZoneRecordPtr)
{
    LIFT_STUB(0x59d750);
}

// 0x59e330
void __cdecl EffectRegion::InitState(void)
{
    LIFT_STUB(0x59e330);
}

// 0x59e360
void __cdecl EffectRegion::OnEntered(::Zone *, ::Creature *)
{
    LIFT_STUB(0x59e360);
}

// 0x59e620
void __cdecl EffectRegion::ApplyEffect(::Creature *, bool)
{
    LIFT_STUB(0x59e620);
}

// 0x59e780
void __cdecl EffectRegion::SetEnable(bool)
{
    LIFT_STUB(0x59e780);
}

// 0x59eb20
void __cdecl EffectRegion::OnTimer(::Zone *, unsigned short)
{
    LIFT_STUB(0x59eb20);
}

// 0x59ebb0
void __cdecl FootSwitch::OnEntered(::Zone *, ::Creature *)
{
    LIFT_STUB(0x59ebb0);
}

// 0x59eec0
void __cdecl FootSwitch::OnLeaved(::Zone *, ::Creature *)
{
    LIFT_STUB(0x59eec0);
}

// 0x59f010
short __cdecl AirDash::CheckAvailableAirDash(::Pc *)
{
    LIFT_STUB(0x59f010);
}

// 0x59f240
bool __cdecl AirDash::ExecuteAirDash(::ControlledCreature *, long &)
{
    LIFT_STUB(0x59f240);
}

// 0x59f810
short __cdecl AirDashLeave::CheckAvailableAirDash(::Pc *)
{
    LIFT_STUB(0x59f810);
}

// 0x59f970
bool __cdecl AirDashLeave::ExecuteAirDash(::Pc *)
{
    LIFT_STUB(0x59f970);
}

// 0x59fc50
void __cdecl OceanicRegion::OnEntered(::Zone *, ::Creature *)
{
    LIFT_STUB(0x59fc50);
}

// 0x59fcc0
void __cdecl OceanicRegion::OnLeaved(::Zone *, ::Creature *)
{
    LIFT_STUB(0x59fcc0);
}

// 0x59fcf0
void __cdecl OceanicRegion::ApplyEffect(::Creature *, bool)
{
    LIFT_STUB(0x59fcf0);
}

// 0x59fef0
void __cdecl OceanicRegion::OnTimer(::Zone *, unsigned short)
{
    LIFT_STUB(0x59fef0);
}

// 0x59ffb0
void __cdecl FallDeathRegion::OnEntered(::Zone *, ::Creature *)
{
    LIFT_STUB(0x59ffb0);
}

// 0x5a0020
void __cdecl FallDeathRegion::ApplyEffect(::Creature *, bool)
{
    LIFT_STUB(0x5a0020);
}

// 0x5a01f0
void __cdecl FallDeathRegion::OnTimer(::Zone *, unsigned short)
{
    LIFT_STUB(0x5a01f0);
}

// 0x5a0280
bool __cdecl FishingPoint::CheckToManipulate(::Pc *, ::Item *, ::QuestRequiredItems const *, char, short &)
{
    LIFT_STUB(0x5a0280);
}

// 0x5a02c0
void __cdecl FishingPoint::Manipulate(::Pc *, ::Item *, ::QuestRequiredItems const *, char)
{
    LIFT_STUB(0x5a02c0);
}

// 0x5a02d0
bool __cdecl FishingPoint::SetInfo(::Item *, unsigned __int64 &, __int64 &, __int64 &)
{
    LIFT_STUB(0x5a02d0);
}
