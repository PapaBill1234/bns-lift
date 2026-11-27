// creature_cpp_1.cpp: creature.cpp part 1 (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "creature.h"
#include "campfire.h"
#include "effect.h"
#include "gameobject.h"
#include "npc.h"
#include "pc.h"
#include "zone.h"
#include "LiftStub.h"

// 0x260cd0
__cdecl Creature::Creature(void)
{
    LIFT_STUB(0x260cd0);
}

// 0x260ef0
__cdecl Creature::~Creature(void)
{
    LIFT_STUB(0x260ef0);
}

// 0x261050
bool __cdecl Creature::Initialize(unsigned __int64)
{
    LIFT_STUB(0x261050);
}

// 0x261180
void __cdecl Creature::SetZone(::Zone *)
{
    LIFT_STUB(0x261180);
}

// 0x261250
void __cdecl Creature::EnterZone(::EnterReason, bool, unsigned int)
{
    LIFT_STUB(0x261250);
}

// 0x261350
void __cdecl Creature::LeaveZone(::LeaveReason)
{
    LIFT_STUB(0x261350);
}

// 0x2614b0
bool __cdecl Creature::SetDead(bool, ::ChangedProperty *, unsigned __int64, unsigned __int64, unsigned __int64, bool, bool)
{
    LIFT_STUB(0x2614b0);
}

// 0x2614c0
unsigned short __cdecl Creature::FetchBroadcastOnEncounterProperty(char *, unsigned short)
{
    LIFT_STUB(0x2614c0);
}

// 0x261520
unsigned short __cdecl Creature::FetchBroadcastOnChangeProperty(char *, unsigned short)
{
    LIFT_STUB(0x261520);
}

// 0x261580
unsigned short __cdecl Creature::FetchDbSyncProperty(char *, unsigned short, short *)
{
    LIFT_STUB(0x261580);
}

// 0x261650
short __cdecl Creature::GetExtraBroadcastOnChangePropertySize(void)
{
    LIFT_STUB(0x261650);
}

// 0x2616b0
unsigned short __cdecl Creature::FetchExtraDbSyncProperty(char *, unsigned short, short *)
{
    LIFT_STUB(0x2616b0);
}

// 0x2617a0
unsigned short __cdecl Creature::FetchEffectList(char *, unsigned short, int)
{
    LIFT_STUB(0x2617a0);
}

// 0x2618b0
short __cdecl Creature::GetEffectListSize(void)
{
    LIFT_STUB(0x2618b0);
}

// 0x261930
unsigned short __cdecl Creature::FetchDuelBotSyncProperty(char *, unsigned short)
{
    LIFT_STUB(0x261930);
}

// 0x261a10
unsigned short __cdecl Creature::FetchDuelBotDiffProperty(char *, unsigned short)
{
    LIFT_STUB(0x261a10);
}

// 0x261aa0
unsigned short __cdecl Creature::FetchAllProperty(char *, unsigned short)
{
    LIFT_STUB(0x261aa0);
}

// 0x261b30
unsigned short __cdecl Creature::FetchAllExtraProperty(char *, unsigned short)
{
    LIFT_STUB(0x261b30);
}

// 0x261c40
bool __cdecl Creature::IsInTheAir(void) const
{
    LIFT_STUB(0x261c40);
}

// 0x261d80
bool __cdecl Creature::ChangeMoveState(::CreatureMoveState, short, wchar_t *)
{
    LIFT_STUB(0x261d80);
}

// 0x261e60
void __cdecl Creature::initMoveCtx(void)
{
    LIFT_STUB(0x261e60);
}

// 0x261f10
bool __cdecl Creature::CheckCounterSkill(void)
{
    LIFT_STUB(0x261f10);
}

// 0x261fb0
bool __cdecl Creature::ExecuteCounterSkill(unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x261fb0);
}

// 0x262050
bool __cdecl Creature::CheckImmuneSkillResult(::SkillResult)
{
    LIFT_STUB(0x262050);
}

// 0x2620d0
bool __cdecl Creature::DelayCasting(::SkillResult)
{
    LIFT_STUB(0x2620d0);
}

// 0x2621b0
bool __cdecl Creature::IsAttackable(void)
{
    LIFT_STUB(0x2621b0);
}

// 0x262200
bool __cdecl Creature::Unlink(void)
{
    LIFT_STUB(0x262200);
}

// 0x262e30
unsigned __int64 __cdecl Creature::GetZoneAttractionGroup(void)
{
    LIFT_STUB(0x262e30);
}

// 0x263290
void __cdecl Creature::AddChangedProperty(::ChangedProperty *)
{
    LIFT_STUB(0x263290);
}

// 0x263790
int __cdecl Creature::GetDuelGrade(int)
{
    LIFT_STUB(0x263790);
}

// 0x263870
int __cdecl Creature::GetBattleFieldGrade(char, int)
{
    LIFT_STUB(0x263870);
}

// 0x263960
int __cdecl Creature::GetFactionLevel(int)
{
    LIFT_STUB(0x263960);
}

// 0x263a40
bool __cdecl Creature::CanJoinFaction(char, __int64, __int64)
{
    LIFT_STUB(0x263a40);
}

// 0x263ab0
int __cdecl Creature::GetLevelModify(::Creature *, ::Creature *, bool)
{
    LIFT_STUB(0x263ab0);
}

// 0x263bf0
::CreatureSide __cdecl Creature::CheckSide(::Creature *, ::Creature *)
{
    LIFT_STUB(0x263bf0);
}

// 0x263dc0
bool __cdecl Creature::CanSeeGhost(::Creature *, ::Creature *)
{
    LIFT_STUB(0x263dc0);
}

// 0x263e20
bool __cdecl Creature::CanSeeGhost(::Creature *, ::Data::NpcRecordPtr &)
{
    LIFT_STUB(0x263e20);
}

// 0x263e80
bool __cdecl Creature::CanAttack(::Creature *, ::Creature *)
{
    LIFT_STUB(0x263e80);
}

// 0x264050
bool __cdecl Creature::CheckCombatSideEnabled(::Creature *, ::Creature *)
{
    LIFT_STUB(0x264050);
}

// 0x264090
::CreatureSide __cdecl Creature::CheckSideByCombatSide(::Creature *, ::Creature *)
{
    LIFT_STUB(0x264090);
}

// 0x264130
bool __cdecl Creature::IsSamePartyAndCombatSide(::Creature *, ::Creature *)
{
    LIFT_STUB(0x264130);
}

// 0x264240
bool __cdecl Creature::CanAttack(::Creature *, ::Data::NpcRecordPtr)
{
    LIFT_STUB(0x264240);
}

// 0x264350
bool __cdecl Creature::IsHostileFaction(char, char)
{
    LIFT_STUB(0x264350);
}

// 0x2643b0
void __cdecl Creature::DistributeMoney(bool, ::vector16, int, __int64, bool, bool)
{
    LIFT_STUB(0x2643b0);
}

// 0x264b00
int __cdecl Creature::CalcFactionScore(char, char, int)
{
    LIFT_STUB(0x264b00);
}

// 0x264c00
bool __cdecl Creature::CanDetect(::Npc *, ::Creature *)
{
    LIFT_STUB(0x264c00);
}

// 0x264e30
void __cdecl Creature::GetRelatedPcWithTarget(::GameObject *, ::Pc **, ::Npc **)
{
    LIFT_STUB(0x264e30);
}

// 0x264f00
bool __cdecl Creature::IsValidTargetState(::Creature *, ::Data::SkillTargetStateType)
{
    LIFT_STUB(0x264f00);
}

// 0x265000
bool __cdecl Creature::CheckCampfireCylinder(::Campfire *)
{
    LIFT_STUB(0x265000);
}

// 0x2650e0
bool __cdecl Creature::CheckEffectFlag(::Data::EffectFlagType) const
{
    LIFT_STUB(0x2650e0);
}

// 0x265160
::AbnormalState __cdecl Creature::GetAbnormalState(void)
{
    LIFT_STUB(0x265160);
}

// 0x2651d0
__int64 __cdecl Creature::calcDamage(::Creature *, int, __int64, short, ::SkillResult, bool, bool)
{
    LIFT_STUB(0x2651d0);
}

// 0x267090
__int64 __cdecl Creature::CalcPhysicalDamage(int, __int64)
{
    LIFT_STUB(0x267090);
}

// 0x2672b0
__int64 __cdecl Creature::CalcForceDamage(::Creature *, int, __int64, short, ::SkillResult, bool)
{
    LIFT_STUB(0x2672b0);
}

// 0x2672f0
__int64 __cdecl Creature::CalcHeal(__int64, short)
{
    LIFT_STUB(0x2672f0);
}

// 0x267400
void __cdecl Creature::GetSoulMaskId(char &, char &)
{
    LIFT_STUB(0x267400);
}

// 0x2676e0
unsigned __int64 __cdecl Creature::GetSoulMaskSetKey(void)
{
    LIFT_STUB(0x2676e0);
}

// 0x2679c0
void __cdecl Creature::invokeStanceEffects(unsigned __int64 const *, int)
{
    LIFT_STUB(0x2679c0);
}

// 0x267cc0
bool __cdecl Creature::ExecuteMove(::vector16, ::GeoCell const *, char const *const, int, short, long, char, ::MoveType, short, ::MoveTypeList *)
{
    LIFT_STUB(0x267cc0);
}

// 0x267eb0
bool __cdecl Creature::HandleAllAbility(__int64, short, ::ChangedProperty *)
{
    LIFT_STUB(0x267eb0);
}

// 0x268010
bool __cdecl Creature::HandleAbility(unsigned short, __int64, __int64, short, ::ChangedProperty *)
{
    LIFT_STUB(0x268010);
}

// 0x268640
bool __cdecl Creature::HandleBool(unsigned short, bool, ::ChangedProperty *)
{
    LIFT_STUB(0x268640);
}

// 0x2687e0
bool __cdecl Creature::HandleFlag(unsigned short, ::f_flag8::Operation, ::ChangedProperty *)
{
    LIFT_STUB(0x2687e0);
}

// 0x268950
bool __cdecl Creature::HandleDead(char, ::ChangedProperty *)
{
    LIFT_STUB(0x268950);
}

// 0x268c70
bool __cdecl Creature::SetMasteryLevel(char, ::ChangedProperty *, bool)
{
    LIFT_STUB(0x268c70);
}

// 0x268d10
bool __cdecl Creature::HandleMasteryExp(__int64, ::ChangedProperty *, short)
{
    LIFT_STUB(0x268d10);
}

// 0x269030
bool __cdecl Creature::HandleExp(__int64, ::ChangedProperty *, short)
{
    LIFT_STUB(0x269030);
}

// 0x26a1c0
bool __cdecl Creature::HandleExpAAA(__int64, ::ChangedProperty *, short)
{
    LIFT_STUB(0x26a1c0);
}

// 0x26a320
void __cdecl Creature::InitLevel(void)
{
    LIFT_STUB(0x26a320);
}

// 0x26a4e0
bool __cdecl Creature::HandleLevel(char, ::ChangedProperty *)
{
    LIFT_STUB(0x26a4e0);
}

// 0x26a5e0
bool __cdecl Creature::HandleMasteryLevel(char, ::ChangedProperty *)
{
    LIFT_STUB(0x26a5e0);
}

// 0x26a6e0
bool __cdecl Creature::HandleMoney(__int64, ::ChangedProperty *, short, bool)
{
    LIFT_STUB(0x26a6e0);
}

// 0x26b080
bool __cdecl Creature::HandleHpDamage(__int64 &, unsigned __int64, __int64, short, unsigned __int64, unsigned __int64, ::ChangedProperty *, char, int, bool, bool, bool)
{
    LIFT_STUB(0x26b080);
}

// 0x26bc00
bool __cdecl Creature::HandleHpHeal(unsigned __int64, __int64, short, ::ChangedProperty *)
{
    LIFT_STUB(0x26bc00);
}

// 0x26bd10
bool __cdecl Creature::HandleGuardGaugeDamage(unsigned __int64, __int64, short, ::ChangedProperty *)
{
    LIFT_STUB(0x26bd10);
}

// 0x26be90
bool __cdecl Creature::HandleGuardGaugeHeal(unsigned __int64, __int64, short, ::ChangedProperty *)
{
    LIFT_STUB(0x26be90);
}

// 0x26c040
bool __cdecl Creature::HandleSpDamage(unsigned __int64, int, short, ::ChangedProperty *)
{
    LIFT_STUB(0x26c040);
}

// 0x26c190
bool __cdecl Creature::HandleSpHeal(unsigned __int64, int, short, ::ChangedProperty *)
{
    LIFT_STUB(0x26c190);
}

// 0x26c2a0
bool __cdecl Creature::HandleSp(short, ::ChangedProperty *)
{
    LIFT_STUB(0x26c2a0);
}

// 0x26c380
bool __cdecl Creature::HandleMove(::vector16, ::GeoCell const *, char const *const, int, ::Effect *, ::ChangedProperty *)
{
    LIFT_STUB(0x26c380);
}

// 0x26cde0
bool __cdecl Creature::HandleYaw(short, ::ChangedProperty *)
{
    LIFT_STUB(0x26cde0);
}

// 0x26ceb0
bool __cdecl Creature::HandleStance(char, unsigned __int64 const *, int, ::ChangedProperty *)
{
    LIFT_STUB(0x26ceb0);
}

// 0x26d080
bool __cdecl Creature::HandleLink(unsigned __int64, char, char, char, ::ChangedProperty *)
{
    LIFT_STUB(0x26d080);
}

// 0x26d320
bool __cdecl Creature::HandleActionTarget(char, unsigned __int64, ::ChangedProperty *)
{
    LIFT_STUB(0x26d320);
}

// 0x26d420
bool __cdecl Creature::HandleAdditionalHp(int, short, ::ChangedProperty *)
{
    LIFT_STUB(0x26d420);
}
