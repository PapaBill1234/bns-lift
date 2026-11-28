// zone_cpp_1.cpp: zone.cpp part 1 (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "zone.h"
#include "campfire.h"
#include "convoy.h"
#include "creature.h"
#include "droppedpouch.h"
#include "effect.h"
#include "envobj.h"
#include "fielditem.h"
#include "gameobject.h"
#include "gathersource.h"
#include "geoworld.h"
#include "npc.h"
#include "npcdeadbody.h"
#include "npcparty.h"
#include "npcsquad.h"
#include "pc.h"
#include "systemaction.h"
#include "LiftStub.h"

// 0x228470
char __cdecl Zone::GetMaxInstantHeartCount(int, char)
{
    LIFT_STUB(0x228470);
}

// 0x228660
::GameFailReason __cdecl Zone::CheckAttractionAvailableTime(unsigned __int64, ::GeoZone const *)
{
    LIFT_STUB(0x228660);
}

// 0x228770
__cdecl Zone::Zone(bool)
{
    LIFT_STUB(0x228770);
}

// 0x228b40
__cdecl Zone::~Zone(void)
{
    LIFT_STUB(0x228b40);
}

// 0x228cb0
bool __cdecl Zone::Open(unsigned __int64, ::GeoZone const *, bool, unsigned __int64, char, short, char)
{
    LIFT_STUB(0x228cb0);
}

// 0x22af50
void __cdecl Zone::PreClose(void)
{
    LIFT_STUB(0x22af50);
}

// 0x22b190
void __cdecl Zone::Close(void)
{
    LIFT_STUB(0x22b190);
}

// 0x22cf30
bool __cdecl Zone::IsEnableSendInfomationToDuelBotDaemon(void)
{
    LIFT_STUB(0x22cf30);
}

// 0x22cfc0
void __cdecl Zone::SetDuelBotBrainId(__int64)
{
    LIFT_STUB(0x22cfc0);
}

// 0x22d550
void __cdecl Zone::SetDuelBotCombatSide(unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x22d550);
}

// 0x22ded0
bool __cdecl Zone::Reserve(::Creature *, ::Zone::ReserveResult *)
{
    LIFT_STUB(0x22ded0);
}

// 0x22e170
bool __cdecl Zone::Enter(::Creature *, int, int, int, int, unsigned __int64, ::EnterReason, unsigned __int64, bool, bool, unsigned int)
{
    LIFT_STUB(0x22e170);
}

// 0x22e680
bool __cdecl Zone::Leave(::Creature *, unsigned __int64)
{
    LIFT_STUB(0x22e680);
}

// 0x22e810
bool __cdecl Zone::ReturnToArenaLobby(::Pc *, unsigned __int64)
{
    LIFT_STUB(0x22e810);
}

// 0x22e900
::Env * __cdecl Zone::GetEnvWithGeoId(short) const
{
    LIFT_STUB(0x22e900);
}

// 0x22e960
::Env * __cdecl Zone::GetEnv(unsigned __int64) const
{
    LIFT_STUB(0x22e960);
}

// 0x22e9b0
::Pointer2< ::Env> __cdecl Zone::GetEnvPtr(unsigned __int64) const
{
    LIFT_STUB(0x22e9b0);
}

// 0x22ea90
::Pointer2< ::GatherSource> __cdecl Zone::GetGatherSourcePtr(unsigned __int64) const
{
    LIFT_STUB(0x22ea90);
}

// 0x22eb70
::NpcParty * __cdecl Zone::GetNpcParty(::dr_tref) const
{
    LIFT_STUB(0x22eb70);
}

// 0x22ec00
::NpcSquad * __cdecl Zone::GetNpcSquad(unsigned __int64) const
{
    LIFT_STUB(0x22ec00);
}

// 0x22ec50
::Convoy * __cdecl Zone::GetConvoy(unsigned __int64) const
{
    LIFT_STUB(0x22ec50);
}

// 0x22eca0
bool __cdecl Zone::GetNearCreature(int, int, int, unsigned __int64 *const, int *)
{
    LIFT_STUB(0x22eca0);
}

// 0x22ee30
bool __cdecl Zone::GetNearContributionPc(::vector16 const &, ::Npc *, unsigned __int64 *const, int *)
{
    LIFT_STUB(0x22ee30);
}

// 0x22f050
bool __cdecl Zone::GetZoneContributionPc(::Npc *, unsigned __int64 *const, int *)
{
    LIFT_STUB(0x22f050);
}

// 0x22f1d0
bool __cdecl Zone::GetPcList(unsigned __int64 *const, int *)
{
    LIFT_STUB(0x22f1d0);
}

// 0x22f260
bool __cdecl Zone::GetNearEnvObj(int, int, int, unsigned __int64 *const, int *)
{
    LIFT_STUB(0x22f260);
}

// 0x22f400
void __cdecl Zone::regeneration(void)
{
    LIFT_STUB(0x22f400);
}

// 0x22f5d0
unsigned __int64 __cdecl Zone::Detect(::Npc &, ::Data::ActSequenceDetectType)
{
    LIFT_STUB(0x22f5d0);
}

// 0x22fb80
bool __cdecl Zone::AcquireEnemyCreatureInDetectRange(::Npc &, ::Creature **const, int *)
{
    LIFT_STUB(0x22fb80);
}

// 0x22fdc0
bool __cdecl Zone::enter(::Creature *, int, int, int, ::EnterReason, unsigned __int64, bool, unsigned int)
{
    LIFT_STUB(0x22fdc0);
}

// 0x230220
bool __cdecl Zone::leave(::LeaveAction *)
{
    LIFT_STUB(0x230220);
}

// 0x230400
void __cdecl Zone::transferCreature(::LeaveAction *)
{
    LIFT_STUB(0x230400);
}

// 0x230a10
void __cdecl Zone::removeLeavingCreature(void)
{
    LIFT_STUB(0x230a10);
}

// 0x231270
void __cdecl Zone::spawnByFieldZoneRule(void)
{
    LIFT_STUB(0x231270);
}

// 0x231510
void __cdecl Zone::spawnEnd(::PcSpawnAction *, wchar_t const *)
{
    LIFT_STUB(0x231510);
}

// 0x231590
void __cdecl Zone::PostExecuteEvent(void)
{
    LIFT_STUB(0x231590);
}

// 0x2315f0
bool __cdecl Zone::initBossChallenge(void)
{
    LIFT_STUB(0x2315f0);
}

// 0x2316b0
bool __cdecl Zone::initGuildBattleField(int)
{
    LIFT_STUB(0x2316b0);
}

// 0x231a50
bool __cdecl Zone::isEventStageChannel(void)
{
    LIFT_STUB(0x231a50);
}

// 0x231be0
bool __cdecl Zone::initNpcSpawnEvent(void)
{
    LIFT_STUB(0x231be0);
}

// 0x231dd0
bool __cdecl Zone::initEventStage(void)
{
    LIFT_STUB(0x231dd0);
}

// 0x232050
bool __cdecl Zone::initDuel(void)
{
    LIFT_STUB(0x232050);
}

// 0x232300
bool __cdecl Zone::initZoneRule(void)
{
    LIFT_STUB(0x232300);
}

// 0x232400
bool __cdecl Zone::initJockPotBossZone(void)
{
    LIFT_STUB(0x232400);
}

// 0x232520
bool __cdecl Zone::initFactionBattleFieldZone(void)
{
    LIFT_STUB(0x232520);
}

// 0x232600
bool __cdecl Zone::sendCreateDuelBotBrain(void)
{
    LIFT_STUB(0x232600);
}

// 0x2327b0
bool __cdecl Zone::initDuelBotAttrationState(void)
{
    LIFT_STUB(0x2327b0);
}

// 0x232980
bool __cdecl Zone::initTendencyField(bool)
{
    LIFT_STUB(0x232980);
}

// 0x232cd0
bool __cdecl Zone::initSkillTrainingRoom(void)
{
    LIFT_STUB(0x232cd0);
}

// 0x232dc0
bool __cdecl Zone::initPublicRaid(void)
{
    LIFT_STUB(0x232dc0);
}

// 0x2330c0
bool __cdecl Zone::initChallengeParty(char)
{
    LIFT_STUB(0x2330c0);
}

// 0x2333b0
bool __cdecl Zone::initBattleRoyalField(void)
{
    LIFT_STUB(0x2333b0);
}

// 0x233520
bool __cdecl Zone::initWarField(void)
{
    LIFT_STUB(0x233520);
}

// 0x233620
void __cdecl Zone::initDuelBotSpawn(char)
{
    LIFT_STUB(0x233620);
}

// 0x233890
bool __cdecl Zone::initPartyBattleField(void)
{
    LIFT_STUB(0x233890);
}

// 0x233b60
void __cdecl Zone::executePcAttachedZSO(void)
{
    LIFT_STUB(0x233b60);
}

// 0x233d10
bool __cdecl Zone::SpawnFieldItem(unsigned __int64, unsigned int, ::vector16, short, short, unsigned __int64)
{
    LIFT_STUB(0x233d10);
}

// 0x234060
bool __cdecl Zone::CreateFieldItem(::Pc *, unsigned int, unsigned __int64)
{
    LIFT_STUB(0x234060);
}

// 0x234380
#pragma comment(linker, "/INCLUDE:?GetFieldItem@Zone@@QEBAPEAVFieldItem@@_K@Z")  // LIFT: dead-strip keep (no live caller yet)
::FieldItem * __cdecl Zone::GetFieldItem(unsigned __int64 id) const
{
    // LIFT: the 2019 body has an inlined index search of FieldItemList (no PDB name).
    ::FieldItemList *const fieldItemList = reinterpret_cast< ::ZoneMemberView const *>(this)->fieldItemList;
    int index = -1;
    for (int i = 0; i < fieldItemList->Count; ++i)
    {
        if (reinterpret_cast< ::GameObjectIdView const *>(fieldItemList->FieldItems[i])->Id == id)
        {
            index = i;
            break;
        }
    }
    if (index < 0)
        return NULL;
    return fieldItemList->FieldItems[index];
}

// 0x2343d0
bool __cdecl Zone::PickupFieldItem(::FieldItem *, unsigned __int64)
{
    LIFT_STUB(0x2343d0);
}

// 0x234500
bool __cdecl Zone::DropFieldItem(::FieldItem *, unsigned __int64, ::vector16, ::FieldItemDropState)
{
    LIFT_STUB(0x234500);
}

// 0x234760
bool __cdecl Zone::RemoveFieldItem(::FieldItem *, char)
{
    LIFT_STUB(0x234760);
}

// 0x2348d0
unsigned __int64 __cdecl Zone::SelectFieldItem(unsigned __int64 *, char *, int)
{
    LIFT_STUB(0x2348d0);
}

// 0x234950
bool __cdecl Zone::DropFieldItemAtFrontNpc(unsigned __int64, ::Npc &, unsigned __int64)
{
    LIFT_STUB(0x234950);
}

// 0x234c80
bool __cdecl Zone::DropFieldItemAtArea(unsigned __int64, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x234c80);
}

// 0x234ef0
bool __cdecl Zone::canDropFieldItem(::Pc *, unsigned __int64, short, char, bool)
{
    LIFT_STUB(0x234ef0);
}

// 0x2351a0
bool __cdecl Zone::IsZoneFull(::Creature *)
{
    LIFT_STUB(0x2351a0);
}

// 0x235350
::NpcDeadBody * __cdecl Zone::CreateNpcDeadBody(::vector16)
{
    LIFT_STUB(0x235350);
}

// 0x235500
::NpcDeadBody * __cdecl Zone::GetNpcDeadBody(unsigned __int64) const
{
    LIFT_STUB(0x235500);
}

// 0x235570
bool __cdecl Zone::RemoveNpcDeadBody(::NpcDeadBody *)
{
    LIFT_STUB(0x235570);
}

// 0x2356a0
::DroppedPouch * __cdecl Zone::GetDroppedPouch(unsigned __int64) const
{
    LIFT_STUB(0x2356a0);
}

// 0x235710
bool __cdecl Zone::RemoveDroppedPouch(::DroppedPouch *)
{
    LIFT_STUB(0x235710);
}

// 0x235840
bool __cdecl Zone::CreateDroppedPouch(void)
{
    LIFT_STUB(0x235840);
}

// 0x235f60
bool __cdecl Zone::SpawnDroppedPouch(short, ::vector16)
{
    LIFT_STUB(0x235f60);
}

// 0x2361d0
bool __cdecl Zone::CreateCampfire(unsigned int, unsigned __int64, ::vector16)
{
    LIFT_STUB(0x2361d0);
}

// 0x236460
bool __cdecl Zone::CreateCampfireByZone(unsigned int, ::vector16)
{
    LIFT_STUB(0x236460);
}

// 0x236630
#pragma comment(linker, "/INCLUDE:?GetCampfire@Zone@@QEBAPEAVCampfire@@_K@Z")  // LIFT: dead-strip keep (no live caller yet)
::Campfire * __cdecl Zone::GetCampfire(unsigned __int64 id) const
{
    // LIFT: the 2019 body has an inlined index search of CampfireList (no PDB name).
    ::CampfireList *const campfireList = reinterpret_cast< ::ZoneMemberView const *>(this)->campfireList;
    int index = -1;
    for (int i = 0; i < campfireList->Count; ++i)
    {
        if (reinterpret_cast< ::GameObjectIdView const *>(campfireList->Campfires[i])->Id == id)
        {
            index = i;
            break;
        }
    }
    if (index < 0)
        return NULL;
    return campfireList->Campfires[index];
}

// 0x236680
bool __cdecl Zone::RemoveCampfire(::Campfire *)
{
    LIFT_STUB(0x236680);
}

// 0x2367b0
void __cdecl Zone::BroadcastPacketInSight(::vector16, ::Packet *, ::BroadcastPacketType) const
{
    LIFT_STUB(0x2367b0);
}

// 0x236950
void __cdecl Zone::BroadcastPacket(::Packet const *, ::BroadcastPacketType) const
{
    LIFT_STUB(0x236950);
}

// 0x236b50
bool __cdecl Zone::AddClientMoveBroadcast(::vector16, unsigned __int64, short, short, short, short, short, char, short, ::MoveTypeList *)
{
    LIFT_STUB(0x236b50);
}

// 0x2370c0
bool __cdecl Zone::AddSkillBroadcast(::vector16, unsigned __int64, unsigned int, char, char, char, short, short, short, short, char, ::SkillFlowCode, short, ::CancelTime, unsigned int, unsigned int, char const *, int, ...)
{
    LIFT_STUB(0x2370c0);
}

// 0x2371b0
bool __cdecl Zone::AddSkillBroadcast(::vector16, unsigned __int64, unsigned int, char, char, char, short, short, short, short, char, ::SkillFlowCode, short, ::CancelTime, unsigned int, unsigned int, char const *, int, char *)
{
    LIFT_STUB(0x2371b0);
}

// 0x2375c0
bool __cdecl Zone::AddSimultaneousGroundSkillBroadcast(::vector16, unsigned __int64, unsigned int, char, char, char, short, short, short, short, char, ::SkillFlowCode, short, ::CancelTime, unsigned int, unsigned int, char const *, char, short, short, short)
{
    LIFT_STUB(0x2375c0);
}

// 0x2379c0
bool __cdecl Zone::AddSimultaneousCasterSkillBroadcast(::vector16, unsigned __int64, unsigned int, char, char, char, short, short, short, short, char, ::SkillFlowCode, short, ::CancelTime, unsigned int, unsigned int, char const *, char, unsigned __int64)
{
    LIFT_STUB(0x2379c0);
}

// 0x237db0
bool __cdecl Zone::AddMultigroundSkillBroadcast(::vector16, unsigned __int64, unsigned int, char, char, char, short, short, short, short, char, ::SkillFlowCode, short, ::CancelTime, unsigned int, unsigned int, char const *, char, ::vector16 *const, int)
{
    LIFT_STUB(0x237db0);
}

// 0x238280
bool __cdecl Zone::AddLinkLaserSkillBroadcast(::vector16, unsigned __int64, unsigned int, char, char, char, short, short, short, short, char, ::SkillFlowCode, short, ::CancelTime, unsigned int, unsigned int, char const *, char, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x238280);
}

// 0x2386a0
bool __cdecl Zone::AddSkillHitBroadcast(::vector16, unsigned __int64, unsigned __int64, unsigned int, char, char, char, ::SkillFlowCode, ::SkillHitCode)
{
    LIFT_STUB(0x2386a0);
}

// 0x238920
bool __cdecl Zone::AddEffectBroadcast(::vector16, unsigned int, char, short, unsigned __int64, ::GameObject *, char, char, ::ChangedProperty *, char const *, int, ...)
{
    LIFT_STUB(0x238920);
}

// 0x2389b0
bool __cdecl Zone::AddEffectBroadcast(::vector16, unsigned int, char, short, unsigned __int64, ::GameObject *, char, char, ::ChangedProperty *, char const *, int, char *)
{
    LIFT_STUB(0x2389b0);
}

// 0x239180
bool __cdecl Zone::AddEffectZoneBroadcast(unsigned int, short, unsigned __int64, unsigned __int64, char, char, ::ChangedProperty *, char const *, int, ...)
{
    LIFT_STUB(0x239180);
}

// 0x2391e0
bool __cdecl Zone::AddEffectZoneBroadcast(unsigned int, short, unsigned __int64, unsigned __int64, char, char, ::ChangedProperty *, char const *, int, char *)
{
    LIFT_STUB(0x2391e0);
}

// 0x239760
bool __cdecl Zone::AddPassiveEffectFullSyncBroadcast(::vector16, ::GameObject *, ::PassiveEffect *, bool, bool)
{
    LIFT_STUB(0x239760);
}

// 0x239db0
bool __cdecl Zone::AddPassiveEffectDetachCountSyncBroadcast(::vector16, ::GameObject *, char, short, char, bool)
{
    LIFT_STUB(0x239db0);
}

// 0x23a2a0
bool __cdecl Zone::AddPassiveEffectDetachBroadcast(::vector16, ::GameObject *, char, short, bool)
{
    LIFT_STUB(0x23a2a0);
}

// 0x23a800
bool __cdecl Zone::AddEquipBroadcast(::vector16, unsigned __int64, ::EquipType, ::ActionState, int, short)
{
    LIFT_STUB(0x23a800);
}

// 0x23aa60
bool __cdecl Zone::AddNpcChangeWeaponAndStanceBroadcast(::vector16, unsigned __int64, unsigned __int64, char, char, char)
{
    LIFT_STUB(0x23aa60);
}

// 0x23acc0
bool __cdecl Zone::AddManipulateActionBroadcast(::vector16, unsigned __int64, unsigned __int64, char, short, int)
{
    LIFT_STUB(0x23acc0);
}

// 0x23afd0
bool __cdecl Zone::AddEnvDiceResultActionBroadcast(::vector16, unsigned __int64, unsigned __int64, char)
{
    LIFT_STUB(0x23afd0);
}

// 0x23b220
bool __cdecl Zone::AddNpcManipulateActionBroadcast(::vector16, unsigned __int64, unsigned __int64, char)
{
    LIFT_STUB(0x23b220);
}
