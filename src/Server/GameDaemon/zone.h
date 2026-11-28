// zone.h: zone.cpp, zone.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "zonenpcspawnevent.h"

class Zone
{
public:
    enum ReserveResult {};
public:
    ::Pointer2< ::Creature> __cdecl GetCreaturePtr(unsigned __int64);  // 0x35f70
    void __cdecl ReleaseCreature(::Creature *);  // 0x35fa0
    ::Creature * __cdecl AcquireCreature(unsigned __int64);  // 0x180e80
    ::Pointer2< ::Creature> __cdecl GetMobileCreaturePtr(unsigned __int64);  // 0x1ee760
protected:
    int __cdecl getBroadcastCubeIndex(int, int, int) const;  // 0x1ee7a0
public:
    static char __cdecl GetMaxInstantHeartCount(int, char);  // 0x228470
    static ::GameFailReason __cdecl CheckAttractionAvailableTime(unsigned __int64, ::GeoZone const *);  // 0x228660
    __cdecl Zone(bool);  // 0x228770
    virtual __cdecl ~Zone(void);  // 0x228b40
    bool __cdecl Open(unsigned __int64, ::GeoZone const *, bool, unsigned __int64, char, short, char);  // 0x228cb0
    void __cdecl PreClose(void);  // 0x22af50
    void __cdecl Close(void);  // 0x22b190
    bool __cdecl IsEnableSendInfomationToDuelBotDaemon(void);  // 0x22cf30
    void __cdecl SetDuelBotBrainId(__int64);  // 0x22cfc0
    void __cdecl SetDuelBotCombatSide(unsigned __int64, unsigned __int64);  // 0x22d550
    bool __cdecl Reserve(::Creature *, ::Zone::ReserveResult *);  // 0x22ded0
    bool __cdecl Enter(::Creature *, int, int, int, int, unsigned __int64, ::EnterReason, unsigned __int64, bool, bool, unsigned int);  // 0x22e170
    bool __cdecl Leave(::Creature *, unsigned __int64);  // 0x22e680
    bool __cdecl ReturnToArenaLobby(::Pc *, unsigned __int64);  // 0x22e810
    ::Env * __cdecl GetEnvWithGeoId(short) const;  // 0x22e900
    ::Env * __cdecl GetEnv(unsigned __int64) const;  // 0x22e960
    ::Pointer2< ::Env> __cdecl GetEnvPtr(unsigned __int64) const;  // 0x22e9b0
    ::Pointer2< ::GatherSource> __cdecl GetGatherSourcePtr(unsigned __int64) const;  // 0x22ea90
    ::NpcParty * __cdecl GetNpcParty(::dr_tref) const;  // 0x22eb70
    ::NpcSquad * __cdecl GetNpcSquad(unsigned __int64) const;  // 0x22ec00
    ::Convoy * __cdecl GetConvoy(unsigned __int64) const;  // 0x22ec50
    bool __cdecl GetNearCreature(int, int, int, unsigned __int64 *const, int *);  // 0x22eca0
    bool __cdecl GetNearContributionPc(::vector16 const &, ::Npc *, unsigned __int64 *const, int *);  // 0x22ee30
    bool __cdecl GetZoneContributionPc(::Npc *, unsigned __int64 *const, int *);  // 0x22f050
    bool __cdecl GetPcList(unsigned __int64 *const, int *);  // 0x22f1d0
    bool __cdecl GetNearEnvObj(int, int, int, unsigned __int64 *const, int *);  // 0x22f260
private:
    void __cdecl regeneration(void);  // 0x22f400
public:
    unsigned __int64 __cdecl Detect(::Npc &, ::Data::ActSequenceDetectType);  // 0x22f5d0
    bool __cdecl AcquireEnemyCreatureInDetectRange(::Npc &, ::Creature **const, int *);  // 0x22fb80
protected:
    bool __cdecl enter(::Creature *, int, int, int, ::EnterReason, unsigned __int64, bool, unsigned int);  // 0x22fdc0
    bool __cdecl leave(::LeaveAction *);  // 0x230220
    static void __cdecl transferCreature(::LeaveAction *);  // 0x230400
private:
    void __cdecl removeLeavingCreature(void);  // 0x230a10
protected:
    void __cdecl spawnByFieldZoneRule(void);  // 0x231270
    void __cdecl spawnEnd(::PcSpawnAction *, wchar_t const *);  // 0x231510
public:
    void __cdecl PostExecuteEvent(void);  // 0x231590
private:
    bool __cdecl initBossChallenge(void);  // 0x2315f0
    bool __cdecl initGuildBattleField(int);  // 0x2316b0
    bool __cdecl isEventStageChannel(void);  // 0x231a50
    bool __cdecl initNpcSpawnEvent(void);  // 0x231be0
    bool __cdecl initEventStage(void);  // 0x231dd0
    bool __cdecl initDuel(void);  // 0x232050
    bool __cdecl initZoneRule(void);  // 0x232300
    bool __cdecl initJockPotBossZone(void);  // 0x232400
    bool __cdecl initFactionBattleFieldZone(void);  // 0x232520
    bool __cdecl sendCreateDuelBotBrain(void);  // 0x232600
    bool __cdecl initDuelBotAttrationState(void);  // 0x2327b0
    bool __cdecl initTendencyField(bool);  // 0x232980
    bool __cdecl initSkillTrainingRoom(void);  // 0x232cd0
    bool __cdecl initPublicRaid(void);  // 0x232dc0
    bool __cdecl initChallengeParty(char);  // 0x2330c0
    bool __cdecl initBattleRoyalField(void);  // 0x2333b0
    bool __cdecl initWarField(void);  // 0x233520
    void __cdecl initDuelBotSpawn(char);  // 0x233620
    bool __cdecl initPartyBattleField(void);  // 0x233890
    void __cdecl executePcAttachedZSO(void);  // 0x233b60
public:
    bool __cdecl SpawnFieldItem(unsigned __int64, unsigned int, ::vector16, short, short, unsigned __int64);  // 0x233d10
    bool __cdecl CreateFieldItem(::Pc *, unsigned int, unsigned __int64);  // 0x234060
    ::FieldItem * __cdecl GetFieldItem(unsigned __int64) const;  // 0x234380
    bool __cdecl PickupFieldItem(::FieldItem *, unsigned __int64);  // 0x2343d0
    bool __cdecl DropFieldItem(::FieldItem *, unsigned __int64, ::vector16, ::FieldItemDropState);  // 0x234500
    bool __cdecl RemoveFieldItem(::FieldItem *, char);  // 0x234760
    unsigned __int64 __cdecl SelectFieldItem(unsigned __int64 *, char *, int);  // 0x2348d0
    bool __cdecl DropFieldItemAtFrontNpc(unsigned __int64, ::Npc &, unsigned __int64);  // 0x234950
    bool __cdecl DropFieldItemAtArea(unsigned __int64, unsigned __int64, unsigned __int64);  // 0x234c80
private:
    bool __cdecl canDropFieldItem(::Pc *, unsigned __int64, short, char, bool);  // 0x234ef0
public:
    bool __cdecl IsZoneFull(::Creature *);  // 0x2351a0
    ::NpcDeadBody * __cdecl CreateNpcDeadBody(::vector16);  // 0x235350
    ::NpcDeadBody * __cdecl GetNpcDeadBody(unsigned __int64) const;  // 0x235500
    bool __cdecl RemoveNpcDeadBody(::NpcDeadBody *);  // 0x235570
    ::DroppedPouch * __cdecl GetDroppedPouch(unsigned __int64) const;  // 0x2356a0
    bool __cdecl RemoveDroppedPouch(::DroppedPouch *);  // 0x235710
    bool __cdecl CreateDroppedPouch(void);  // 0x235840
    bool __cdecl SpawnDroppedPouch(short, ::vector16);  // 0x235f60
    bool __cdecl CreateCampfire(unsigned int, unsigned __int64, ::vector16);  // 0x2361d0
    bool __cdecl CreateCampfireByZone(unsigned int, ::vector16);  // 0x236460
    ::Campfire * __cdecl GetCampfire(unsigned __int64) const;  // 0x236630
    bool __cdecl RemoveCampfire(::Campfire *);  // 0x236680
    void __cdecl BroadcastPacketInSight(::vector16, ::Packet *, ::BroadcastPacketType) const;  // 0x2367b0
    void __cdecl BroadcastPacket(::Packet const *, ::BroadcastPacketType) const;  // 0x236950
    bool __cdecl AddClientMoveBroadcast(::vector16, unsigned __int64, short, short, short, short, short, char, short, ::MoveTypeList *);  // 0x236b50
    bool __cdecl AddSkillBroadcast(::vector16, unsigned __int64, unsigned int, char, char, char, short, short, short, short, char, ::SkillFlowCode, short, ::CancelTime, unsigned int, unsigned int, char const *, int, ...);  // 0x2370c0
    bool __cdecl AddSkillBroadcast(::vector16, unsigned __int64, unsigned int, char, char, char, short, short, short, short, char, ::SkillFlowCode, short, ::CancelTime, unsigned int, unsigned int, char const *, int, char *);  // 0x2371b0
    bool __cdecl AddSimultaneousGroundSkillBroadcast(::vector16, unsigned __int64, unsigned int, char, char, char, short, short, short, short, char, ::SkillFlowCode, short, ::CancelTime, unsigned int, unsigned int, char const *, char, short, short, short);  // 0x2375c0
    bool __cdecl AddSimultaneousCasterSkillBroadcast(::vector16, unsigned __int64, unsigned int, char, char, char, short, short, short, short, char, ::SkillFlowCode, short, ::CancelTime, unsigned int, unsigned int, char const *, char, unsigned __int64);  // 0x2379c0
    bool __cdecl AddMultigroundSkillBroadcast(::vector16, unsigned __int64, unsigned int, char, char, char, short, short, short, short, char, ::SkillFlowCode, short, ::CancelTime, unsigned int, unsigned int, char const *, char, ::vector16 *const, int);  // 0x237db0
    bool __cdecl AddLinkLaserSkillBroadcast(::vector16, unsigned __int64, unsigned int, char, char, char, short, short, short, short, char, ::SkillFlowCode, short, ::CancelTime, unsigned int, unsigned int, char const *, char, unsigned __int64, unsigned __int64);  // 0x238280
    bool __cdecl AddSkillHitBroadcast(::vector16, unsigned __int64, unsigned __int64, unsigned int, char, char, char, ::SkillFlowCode, ::SkillHitCode);  // 0x2386a0
    bool __cdecl AddEffectBroadcast(::vector16, unsigned int, char, short, unsigned __int64, ::GameObject *, char, char, ::ChangedProperty *, char const *, int, ...);  // 0x238920
    bool __cdecl AddEffectBroadcast(::vector16, unsigned int, char, short, unsigned __int64, ::GameObject *, char, char, ::ChangedProperty *, char const *, int, char *);  // 0x2389b0
    bool __cdecl AddEffectZoneBroadcast(unsigned int, short, unsigned __int64, unsigned __int64, char, char, ::ChangedProperty *, char const *, int, ...);  // 0x239180
    bool __cdecl AddEffectZoneBroadcast(unsigned int, short, unsigned __int64, unsigned __int64, char, char, ::ChangedProperty *, char const *, int, char *);  // 0x2391e0
    bool __cdecl AddPassiveEffectFullSyncBroadcast(::vector16, ::GameObject *, ::PassiveEffect *, bool, bool);  // 0x239760
    bool __cdecl AddPassiveEffectDetachCountSyncBroadcast(::vector16, ::GameObject *, char, short, char, bool);  // 0x239db0
    bool __cdecl AddPassiveEffectDetachBroadcast(::vector16, ::GameObject *, char, short, bool);  // 0x23a2a0
    bool __cdecl AddEquipBroadcast(::vector16, unsigned __int64, ::EquipType, ::ActionState, int, short);  // 0x23a800
    bool __cdecl AddNpcChangeWeaponAndStanceBroadcast(::vector16, unsigned __int64, unsigned __int64, char, char, char);  // 0x23aa60
    bool __cdecl AddManipulateActionBroadcast(::vector16, unsigned __int64, unsigned __int64, char, short, int);  // 0x23acc0
    bool __cdecl AddEnvDiceResultActionBroadcast(::vector16, unsigned __int64, unsigned __int64, char);  // 0x23afd0
    bool __cdecl AddNpcManipulateActionBroadcast(::vector16, unsigned __int64, unsigned __int64, char);  // 0x23b220
    bool __cdecl AddEnvObjectBroadcast(int, short const *const, ::Env *);  // 0x23b470
    bool __cdecl AddRefinerEnvObjectBroadcast(::Refiner *);  // 0x23b7a0
    bool __cdecl AddTakeRefinerRewardBroadcast(unsigned __int64, unsigned __int64, __int64, short);  // 0x23ba10
    bool __cdecl AddPlayManipulateCinematicBroadcast(::vector16, unsigned __int64, unsigned __int64, unsigned __int64);  // 0x23bc50
    bool __cdecl AddGatherSourceBroadcast(::vector16, unsigned __int64, char);  // 0x23bea0
    bool __cdecl AddGatherActionBroadcast(::vector16, unsigned __int64, unsigned __int64, char);  // 0x23c0e0
    bool __cdecl AddLootActionBroadcast(::vector16, unsigned __int64, unsigned __int64, char);  // 0x23c330
    bool __cdecl AddRepairWithCampfireActionBroadcast(::vector16, unsigned __int64, unsigned __int64, short, int, char);  // 0x23c580
    bool __cdecl AddTeleportActionBroadcast(::vector16, unsigned __int64, char);  // 0x23c7e0
    bool __cdecl AddPickupItemActionBroadcast(::vector16, unsigned __int64, unsigned __int64, char);  // 0x23ca20
    bool __cdecl AddSocialBroadcast(::vector16, unsigned __int64, unsigned int, short, bool);  // 0x23cc70
    bool __cdecl AddCancelSocialBroadcast(::vector16, unsigned __int64, unsigned int);  // 0x23cec0
    bool __cdecl AddSurroundSocialBroadcast(::vector16, unsigned int);  // 0x23d100
    bool __cdecl AddCreateFieldItemBroadcast(::vector16, unsigned __int64, unsigned __int64, unsigned __int64, int, char, short);  // 0x23d330
    bool __cdecl AddSpawnFieldItemBroadcast(::vector16, unsigned __int64, unsigned int, short, short, short, char, short, short, short, short);  // 0x23d5a0
    bool __cdecl AddDropFieldItemBroadcast(::vector16, unsigned __int64, unsigned __int64, unsigned int, short, short, short, char, short, short, char);  // 0x23d830
    bool __cdecl AddCreateCampfireBroadcast(::vector16, unsigned __int64, unsigned int, unsigned __int64, short, short, short, short);  // 0x23dac0
    bool __cdecl AddDestroyCampfireBroadcast(::vector16, unsigned __int64);  // 0x23dd40
    bool __cdecl AddPickupFieldItemBroadcast(::vector16, unsigned __int64, unsigned __int64);  // 0x23df70
    bool __cdecl AddPickupFieldItemActionBroadcast(::vector16, unsigned __int64, unsigned __int64, ::ActionState);  // 0x23e1b0
    bool __cdecl AddPickupDeadBodyActionBroadcast(::vector16, unsigned __int64, unsigned __int64, ::ActionState);  // 0x23e400
    bool __cdecl AddPutdownFieldItemActionBroadcast(::vector16, unsigned __int64, unsigned __int64, ::vector16, ::ActionState);  // 0x23e650
    bool __cdecl AddRestorationActionBroadcast(::vector16, unsigned __int64, ::ActionState);  // 0x23e8c0
    bool __cdecl AddHelpRestorationActionBroadcast(::vector16, unsigned __int64, unsigned __int64, ::ActionState);  // 0x23eb00
    bool __cdecl AddDecomposeFieldItemBroadcast(::vector16, unsigned __int64, unsigned __int64, unsigned int, char);  // 0x23ed50
    bool __cdecl AddKillBossNpcByGuildBroadcast(int, wchar_t const *);  // 0x23efa0
    bool __cdecl AddSpawnNpcDeadBodyBroadcast(::vector16, unsigned __int64, ::NpcDeadBody *);  // 0x23f1c0
    bool __cdecl AddDecomposeNpcDeadBodyBroadcast(::vector16, unsigned __int64);  // 0x23f590
    bool __cdecl AddNpcDeadBodyBroadcast(::vector16, ::NpcDeadBody *, char, char, __int64);  // 0x23f7c0
    bool __cdecl AddSetDroppedPouchBroadcast(::vector16, short, ::DroppedPouch *);  // 0x23fb60
    bool __cdecl AddDecomposeDroppedPouchBroadcast(::vector16, unsigned __int64);  // 0x23fde0
    bool __cdecl AddDroppedPouchBroadcast(::vector16, ::DroppedPouch *);  // 0x240010
    bool __cdecl AddLootObjectBroadcast(::vector16, unsigned __int64, short, char, char);  // 0x240280
    bool __cdecl AddWarpBroadcast(::vector16, ::vector16, unsigned __int64, short, char, unsigned int, int);  // 0x2404e0
    bool __cdecl AddAirDashBroadcast(::vector16, ::vector16, unsigned __int64, unsigned __int64, short);  // 0x240900
    bool __cdecl AddEscapeFromCaveActionBroadcast(::vector16, unsigned __int64, char);  // 0x240d60
    bool __cdecl AddTakeFactionScoreBroadcast(::vector16, unsigned __int64, unsigned __int64, int, unsigned __int64 *const, int *const, int *const);  // 0x240fa0
    bool __cdecl AddGiveFactionScoreToRefinerBroadcast(::vector16, unsigned __int64, unsigned __int64, int, ::ActionState);  // 0x241330
    bool __cdecl AddZoneEventStepBroadCast(char);  // 0x241580
    bool __cdecl AddZoneModeBroadcast(char, char, short, __int64);  // 0x2417b0
    bool __cdecl AddZoneScoreBroadcast(void);  // 0x241a60
    bool __cdecl AddPartyBattleZoneScoreBroadcast(char);  // 0x241ca0
    bool __cdecl AddZoneAttractionStateBroadcast(void);  // 0x241ef0
    bool __cdecl AddZoneBossSpawnTimeBroadcast(__int64);  // 0x242140
    bool __cdecl AddZoneBossCombatStartTimeBroadcast(__int64);  // 0x242370
    bool __cdecl AddZoneBossHpBroadcast(char, unsigned __int64, __int64, __int64);  // 0x2425a0
    bool __cdecl AddLastOccupiedEffectGuildBroadcast(__int64);  // 0x2427f0
    bool __cdecl AddJackpotFactionScoreBroadcast(int, int);  // 0x242a20
    bool __cdecl AddWarpToGuildMemberActionBroadcast(::vector16 &, unsigned __int64, char);  // 0x242c40
    bool __cdecl AddCallGuildMemberActionBroadcast(::vector16 &, unsigned __int64, char);  // 0x242e80
    bool __cdecl AddWarpToGuildMeetingPlaceActionBroadcast(::vector16 &, unsigned __int64, char);  // 0x2430c0
    bool __cdecl AddDuelEnterBroadcast(unsigned __int64);  // 0x243300
    bool __cdecl AddDuelDelegateEmceeBroadcast(unsigned __int64);  // 0x243570
    bool __cdecl AddDuelLeaveBroadcast(unsigned __int64, bool);  // 0x2437e0
    bool __cdecl AddDuelOrderChosePcListBroadcast(unsigned __int64 const *const, int);  // 0x243a50
    bool __cdecl AddDuelOrderResultListBroadcast(::TagMatchDuelMember const **const, int);  // 0x243df0
    bool __cdecl AddDuelRoundReadiedPcListBroadcast(unsigned __int64 const *const, int);  // 0x2441b0
    bool __cdecl AddDuelTagTokenOwnerBroadcast(char, unsigned __int64);  // 0x244550
    bool __cdecl AddDuelGameStartBroadcast(unsigned __int64);  // 0x2447c0
    bool __cdecl AddDuelMemberDisplaySkillBroadcast(::Pc *const);  // 0x244a30
    bool __cdecl AddDuelRoundStartBroadcast(char);  // 0x244e70
    bool __cdecl AddDuelInterferenceBonusPcListBroadcast(unsigned __int64 const *const, int);  // 0x2450e0
    bool __cdecl AddDuelDeathBroadcast(unsigned __int64, unsigned __int64);  // 0x245480
    bool __cdecl AddDuelWinByDecisionBroadcast(__int64, __int64);  // 0x2456f0
    bool __cdecl AddDuelRoundFinishBroadcast(char, ::DuelRoundResult);  // 0x245960
    bool __cdecl AddDuelGameFinishBroadcast(::DuelGameResult, bool);  // 0x245bd0
    bool __cdecl AddPartyBattleDelegateEmceeBroadcast(unsigned __int64);  // 0x245e50
    bool __cdecl AddPartyBattleEnterBroadcast(unsigned __int64);  // 0x246080
    bool __cdecl AddPartyBattleLeaveBroadcast(unsigned __int64);  // 0x2462b0
    bool __cdecl AddPartyBattleReadyBroadcast(unsigned __int64);  // 0x2464e0
    bool __cdecl AddPartyBattleStartBroadcast(__int64);  // 0x246710
    bool __cdecl AddPartyBattleDeathBroadcast(unsigned __int64, unsigned __int64, short);  // 0x246940
    bool __cdecl AddPartyBattleContextBroadcast(__int64, __int64);  // 0x246b70
    bool __cdecl AddPartyBattleFinishBroadcast(::PartyBattleResult, bool);  // 0x246d90
    bool __cdecl AddPartyBattleVoteBroadcast(__int64, char);  // 0x246fc0
    bool __cdecl AddPartyBattleVoteFinishBroadcast(::PartyBattleVoteRecord);  // 0x2471f0
    bool __cdecl AddSpawnSquadCreatureBroadcast(unsigned __int64, unsigned __int64);  // 0x2474f0
    bool __cdecl AddBattleRoyalFieldStandByBroadcast(__int64);  // 0x247710
    bool __cdecl AddBattleRoyalFieldStartBroadcast(void);  // 0x247940
    bool __cdecl AddBattleRoyalFieldFinishBroadcast(void);  // 0x247b60
    bool __cdecl AddBattleRoyalFieldEnterBroadcast(unsigned __int64, unsigned __int64, char);  // 0x247d80
    bool __cdecl AddBattleRoyalFieldLeaveBroadcast(unsigned __int64);  // 0x247fc0
    bool __cdecl AddBattleRoyalFieldDeathBroadcast(unsigned __int64, unsigned __int64, short);  // 0x2481f0
    bool __cdecl AddBattleRoyalEventAreaInfoBroadcast(int, char, int, int);  // 0x248460
    void __cdecl SendBattleRoyalFieldInZoneNotify(unsigned __int64, char);  // 0x2486a0
private:
    void __cdecl addZoneEffectActionList(::GameObject const *, char, unsigned char, int, int, char *, short);  // 0x248a20
    void __cdecl addZoneActionList(int, int, char *, short, unsigned char);  // 0x248b30
    void __cdecl addZoneDuelbotActionList(char *, short, __int64);  // 0x248d20
    void __cdecl makeDuelbotActionPacket(::FragmentPacket *);  // 0x248f20
public:
    void __cdecl AddDuelBotSkillAction(unsigned __int64, __int64, unsigned int, char, char, char, short, short, char, ::SkillFlowCode, short, ::CancelTime, char const *, int, ...);  // 0x249090
    bool __cdecl AddDuelBotSkillHitBroadcast(unsigned __int64, __int64, unsigned __int64, unsigned int, char, char, char, ::SkillFlowCode, ::SkillHitCode);  // 0x249400
    bool __cdecl AddDuelBotEffectBroadcast(unsigned int, short, unsigned __int64, unsigned __int64, char, char, char const *, int, char *);  // 0x2496c0
    bool __cdecl AddPublicRaidStandByBroadcast(__int64);  // 0x2499a0
    bool __cdecl AddPublicRaidStartBroadcast(void);  // 0x249bd0
    bool __cdecl AddPublicRaidFinishBroadcast(void);  // 0x249df0
    bool __cdecl AddPublicRaidEnterBroadcast(unsigned __int64);  // 0x24a010
    bool __cdecl AddPublicRaidLeaveBroadcast(unsigned __int64);  // 0x24a240
private:
    void __cdecl makeCubeActionPacket(::BroadcastPacketType);  // 0x24a470
    void __cdecl makeCubeChangedPropertyAction(::ZoneBroadcastCube *);  // 0x24a840
public:
    __int64 __cdecl GetTickTime(void);  // 0x24ae90
private:
    void __cdecl updateCreatureProperty(void);  // 0x24aef0
    void __cdecl moveTo(::Creature *, int, int);  // 0x24b480
    void __cdecl checkLifeTime(void);  // 0x24bc60
    void __cdecl syncObjectData(void);  // 0x24bf70
    void __cdecl clearBroadcastPacket(void);  // 0x24c350
    void __cdecl makeEnterLeavePacket(::BroadcastPacketType);  // 0x24c610
    void __cdecl makeLeavePacket(::BroadcastPacketType);  // 0x24c6f0
    void __cdecl makeEnterPacket(::BroadcastPacketType);  // 0x24c900
    int __cdecl makeInZoneCreaturePacket(::BroadcastPacketType);  // 0x24d190
    void __cdecl makeCubeSyncPacket(::BroadcastPacketType);  // 0x24e710
    void __cdecl makeOutOfSightPacket(::ZoneBroadcastCube *, ::BroadcastPacketType);  // 0x24ee60
    void __cdecl makeEncounterPacket(::ZoneBroadcastCube *, ::BroadcastPacketType);  // 0x24f1f0
    int __cdecl makeInCubeCreaturePacket(::ZoneBroadcastCube *, ::BroadcastPacketType);  // 0x24f730
    int __cdecl makeOutCubeCreaturePacket(::ZoneBroadcastCube *, ::BroadcastPacketType);  // 0x24fcf0
    void __cdecl makeEnvObjectPacket(::ZoneBroadcastCube *, ::BroadcastPacketType);  // 0x2500f0
    void __cdecl makeFieldItemPacket(::ZoneBroadcastCube *, ::BroadcastPacketType);  // 0x2502b0
    void __cdecl makeGatherSourcePacket(::ZoneBroadcastCube *, ::BroadcastPacketType);  // 0x250520
    void __cdecl makeNpcDeadBodyPacket(::ZoneBroadcastCube *, ::BroadcastPacketType);  // 0x250660
    void __cdecl makeHoldingFieldItemPacket(::FragmentPacket *, ::BroadcastPacketType);  // 0x250930
    void __cdecl makeCampfirePacket(::ZoneBroadcastCube *, ::BroadcastPacketType);  // 0x250c40
    void __cdecl makeDroppedPouchPacket(::ZoneBroadcastCube *, ::BroadcastPacketType);  // 0x250e30
    void __cdecl makeOutCubeEnvObjectPacket(::ZoneBroadcastCube *, ::BroadcastPacketType);  // 0x250fe0
    void __cdecl makeOutCubeFieldItemPacket(::ZoneBroadcastCube *, ::BroadcastPacketType);  // 0x251150
    void __cdecl makeOutCubeGatherSourcePacket(::ZoneBroadcastCube *, ::BroadcastPacketType);  // 0x251270
    void __cdecl makeOutCubeNpcDeadBodyPacket(::ZoneBroadcastCube *, ::BroadcastPacketType);  // 0x2513a0
    void __cdecl makeOutCubeCampfirePacket(::ZoneBroadcastCube *, ::BroadcastPacketType);  // 0x2514c0
    void __cdecl makeOutCubeDroppedPouchPacket(::ZoneBroadcastCube *, ::BroadcastPacketType);  // 0x2515e0
    void __cdecl clearList(void);  // 0x251700
    void __cdecl clearLeaveList(void);  // 0x251980
    void __cdecl sendInZoneCreaturePacket(void);  // 0x251c90
    void __cdecl sendInCubeCreaturePacket(::ZoneBroadcastCube *);  // 0x251f00
    void __cdecl sendOutCubeCreaturePacket(::ZoneBroadcastCube *);  // 0x2521b0
    void __cdecl broadcastSyncPacket(void);  // 0x252460
    void __cdecl syncPropertyToDB(::Pc *, ::Packet &, ::RepeatPacketComposer &, int &);  // 0x2528c0
    void __cdecl syncPropertyToDB(void);  // 0x252c30
    void __cdecl syncPropertyToGamed(::Pc *);  // 0x253150
    void __cdecl syncPropertyToGamed(void);  // 0x2532c0
    void __cdecl syncPropertyToDuelBotD(void);  // 0x253590
public:
    virtual bool __cdecl Think(::ScriptEvent const *);  // 0x255690
    void __cdecl SetTriggerEventTimer(long);  // 0x255700
    void __cdecl SetAttractionTimer(long);  // 0x255770
    void __cdecl SetAttractionEventTimer(long);  // 0x2557e0
protected:
    void __cdecl OnOpen(void);  // 0x255850
    virtual void __cdecl OnTimer(::Zone *, unsigned short);  // 0x255930
private:
    void __cdecl doZoneRuleTimer(void);  // 0x255d20
    void __cdecl OnEnterZone(::Pc *);  // 0x256030
public:
    void __cdecl OnKill(::ControlledCreature *, ::GameObject *, unsigned __int64);  // 0x256260
    void __cdecl OnKilled(::ControlledCreature *, ::GameObject *, unsigned __int64);  // 0x256370
    bool __cdecl FindCell(short, short, short, short, ::GeoCell &) const;  // 0x256480
    bool __cdecl FindCell(short, short, short, ::GeoCell &) const;  // 0x256500
    int __cdecl InvokeEffectToAllPc(unsigned __int64);  // 0x256570
    void __cdecl HandleNpcSpawnEvent(::ZoneNpcSpawnEvent::SpawnEvent, unsigned __int64);  // 0x2567d0
    bool const __cdecl IsJumpingTutorialZone(char, char) const;  // 0x256830
    bool __cdecl PostZSO(::ZoneSerializedObject *);  // 0x2568a0
    bool __cdecl PostZSO2(::ZoneSerializedObject *, long);  // 0x256990
    bool __cdecl ExecuteZSO(::ZoneSerializedObject *);  // 0x256a70
    bool __cdecl ExecuteZSOLast(::ZoneSerializedObject *);  // 0x256ba0
    bool __cdecl AttachSimOperation(::Action *);  // 0x256cd0
    void __cdecl ClearSimOperations(unsigned __int64);  // 0x256ee0
    char __cdecl GetSimOpSlotId(void);  // 0x256f90
    bool __cdecl CanResurrect(::Pc *);  // 0x2570b0
private:
    void __cdecl increaseMainFactionPcCount(char);  // 0x257140
    void __cdecl decreaseMainFactionPcCount(char);  // 0x2573d0
public:
    void __cdecl OnDamagedEvent(::ControlledCreature *const, ::Creature *, __int64);  // 0x257640
    bool __cdecl IsAllowInvitePartyInArena(void);  // 0x2577b0
    int __cdecl GetMainFactionPcCount(char);  // 0x257830
    void __cdecl CheckAndEnableGuildBattleFieldGate(void);  // 0x257960
    ::DuelAttractionState * __cdecl GetDuelAttractionState(void);  // 0x257ad0
    ::PartyBattleFieldAttractionState * __cdecl GetPartyBattleFieldAttractionState(void);  // 0x257b10
    ::PublicRaid * __cdecl GetPublicRaid(void);  // 0x257b50
    ::EnterPublicRaidAttractionState * __cdecl GetEnterPublicRaidAttractionState(void);  // 0x257b90
    ::BattleRoyalField * __cdecl GetBattleRoyalFieldAttractionState(void);  // 0x257bd0
    void __cdecl UpdateZoneBroadcastBossNpcList(char, unsigned __int64, __int64, __int64);  // 0x257c10
    void __cdecl FetchInZoneAttractionState(::FragmentPacket &);  // 0x257db0
    void __cdecl FetchInZoneAttractionMemberState(::FragmentPacket &);  // 0x257e60
    static bool __cdecl GetGuildBattleFieldEntrance(::GeoZone const *, ::Data::FieldZoneRecordGuildBattleFieldEntrancePtr &);  // 0x257ef0
    void __cdecl MakeLeaveActionAllPc(bool);  // 0x257f70
    bool __cdecl CheckActivatedGuildBattleField(void);  // 0x2582a0
    void __cdecl ChangeZoneMode(char);  // 0x258340
    void __cdecl ChangeEventZoneMode(char, char, short, __int64, bool);  // 0x2585e0
    int __cdecl GetZoneScore(char);  // 0x258710
    short __cdecl GetZoneTypeGameLog(void) const;  // 0x258770
    void __cdecl SetZRegVar(int, __int64);  // 0x2587e0
    bool __cdecl InOutCreatureDetectStart(char, unsigned __int64, ::Data::ScriptDetectRefTypeType, unsigned __int64, unsigned __int64, short, long, short, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64);  // 0x258820
    unsigned char __cdecl GetPcBroadcastReceiverMask(unsigned __int64);  // 0x259ff0
    void __cdecl SetTransitableByNpcPortal(bool);  // 0x350390
};

// LIFT: view of the PDB class Zone (size 0x4698). Only the members that the lifted bodies read are declared.
struct ZoneMemberView
{
    char lift_pad_0[0x3FD0];  // ❓ no PDB name: Zone fields +0 to +0x3FCF are not declared yet
    ::Env **_envList;  // +16336 (0x3FD0) (PDB: Zone::_envList)
    char lift_pad_3fd8[0x3FE0 - 0x3FD8];  // ❓ no PDB name: _guildBattleFieldEnvList2
    ::FieldItemList *fieldItemList;  // +16352 (0x3FE0) (PDB: Zone::fieldItemList)
    char lift_pad_3fe8[0x4008 - 0x3FE8];  // ❓ no PDB name: npcDeadBodyList and others
    ::CampfireList *campfireList;  // +16392 (0x4008) (PDB: Zone::campfireList)
};

class ZonePerfMonitor
{
public:
    virtual __cdecl ~ZonePerfMonitor(void);  // 0x2593a0
    bool __cdecl Initialize(::Zone const *, unsigned int);  // 0x259440
    void __cdecl End(bool, int, int, int, int, int, int, __int64, __int64, __int64, __int64, __int64, __int64);  // 0x2594e0
    void __cdecl Report(void);  // 0x2595e0
private:
    bool __cdecl initialize(void);  // 0x259bb0
    bool __cdecl initZoneCounter(void);  // 0x259e40
public:
    void __cdecl EndZsoTest(int);  // 0x259f90

    struct ZsoTestResult
    {
        __int64 start;       // +0
        __int64 end;         // +8
        __int64 total;       // +16
        __int64 max;         // +24
        unsigned int count;  // +32
    };

private:
    // PDB layout (size 0x150). The vfptr is at +0.
    long StartClock;                        // +8 (0x8)
    long FinishClock;                       // +12 (0xC)
    unsigned int Count;                     // +16 (0x10)
    unsigned int ReportIntervalCount;       // +20 (0x14)
    __int64 Amount;                         // +24 (0x18)
    __int64 Max;                            // +32 (0x20)
    int AmountZso;                          // +40 (0x28)
    int MaxZso;                             // +44 (0x2C)
    int AmountPc;                           // +48 (0x30)
    int AmountNpc;                          // +52 (0x34)
    int AmountSummoned;                     // +56 (0x38)
    int AmountFieldItem;                    // +60 (0x3C)
    int AmountNpcDeadBody;                  // +64 (0x40)
    __int64 AmountEnterLeaveBytes;          // +72 (0x48)
    __int64 AmountAlreadyInZoneBytes;       // +80 (0x50)
    __int64 AmountSightBytes;               // +88 (0x58)
    __int64 AmountOutCubeCreatureBytes;     // +96 (0x60)
    __int64 AmountInCubeCreatureBytes;      // +104 (0x68)
    __int64 AmountActionBytes;              // +112 (0x70)
    ::Zone const *zone;                     // +120 (0x78)
    unsigned int geoZoneId;                 // +128 (0x80)
    ::LogFile *file;                        // +136 (0x88)
    char lift_pad_90[0x18];                 // ❓ PDB fields zoneCounter (ZoneCounterSet, +0x90) and initCounter (+0xA0) are not declared yet
    ZsoTestResult _zsoTestResult[3];        // +168 (0xA8)
    __int64 StartMsec;                      // +288 (0x120)
    __int64 EndMsec;                        // +296 (0x128)
    unsigned __int64 processCycleStart;     // +304 (0x130)
    unsigned __int64 processCycleEnd;       // +312 (0x138)
    unsigned __int64 threadCycleStart;      // +320 (0x140)
    unsigned __int64 threadCycleEnd;        // +328 (0x148)
};
static_assert(sizeof(ZonePerfMonitor) == 0x150, "sizeof ZonePerfMonitor");

class ZoneWaitingPcList
{
public:
    __cdecl ~ZoneWaitingPcList(void);  // 0x258920
    bool __cdecl Initialize(int);  // 0x2589c0
    bool __cdecl Add(::Pc *, unsigned __int64);  // 0x258a50
    bool __cdecl DeleteInvalidPc(unsigned __int64);  // 0x258d20
    bool __cdecl Find(::Pc *);  // 0x258f80
    bool __cdecl Remove(::Pc *, unsigned __int64);  // 0x259000
    void __cdecl RemoveAll(void);  // 0x2591d0
    unsigned int __cdecl GetCount(void);  // 0x259340
private:
    // PDB layout (size 0x50).
    ::Pc **pcList;                      // +0 (0x0)
    unsigned __int64 *pcId;             // +8 (0x8)
    __int64 *pcRegisterTime;            // +16 (0x10)
    int maxSize;                        // +24 (0x18)
    int count;                          // +28 (0x1C)
    int gmCount;                        // +32 (0x20)
    ::CriticalSection listLock;         // +40 (0x28)
};
static_assert(sizeof(ZoneWaitingPcList) == 0x50, "sizeof ZoneWaitingPcList");

// LIFT: view of the Zone PDB fields that the lifted bodies read (PDB size 0x4698). The pad keeps the PDB offset.
struct ZoneView
{
    char lift_pad_0[0x4270];            // ❓ PDB fields +0 to +0x426F are not declared here
    ::ZoneScore *_score;                // +17008 (0x4270)
    struct ZoneNpcSpawnEventManagerView *_npcSpawnEventManager;  // +17016 (0x4278) PDB type ZoneNpcSpawnEventManager *
    void *_eventStageManager;           // +17024 (0x4280) LIFT: PDB type not declared here
    struct AttractionStateView *_attractionState;  // +17032 (0x4288) PDB type AttractionState *
};

// LIFT: view of the AttractionState PDB vtable (slots 0 to 5). No object of this view is made, so no vtable is emitted.
struct AttractionStateView
{
    virtual ~AttractionStateView() = 0;                        // slot 0
    virtual ::ATTRACTION_STATE_TYPE GetType(void) = 0;         // slot 1
    virtual wchar_t const *GetTypeName(void) = 0;              // slot 2
    virtual int GetGameType(void) const = 0;                   // slot 3 LIFT: PDB return type GameType const
    virtual bool Init(::Zone *, bool) = 0;                     // slot 4
    virtual bool IsEnterPublicRaidAttractionState(void) = 0;   // slot 5
};

// LIFT: view of the ZoneNpcSpawnEvent PDB layout (size 0x18).
struct ZoneNpcSpawnEventView
{
    virtual ~ZoneNpcSpawnEventView() = 0;                                 // slot 0
    virtual void HandleNpcSpawnEvent(::Zone *, unsigned __int64) = 0;     // slot 1
    virtual void ResetContext(::Zone *) = 0;                              // slot 2
    ZoneNpcSpawnEventView *Next(void) { return _next; }                   // inline in the original

    char _type;                         // +8 (0x8)
    ZoneNpcSpawnEventView *_next;       // +16 (0x10)
};

// LIFT: view of the ZoneNpcSpawnEventManager PDB layout (size 0x10).
struct ZoneNpcSpawnEventManagerView
{
    // Inline in the original (inlined at Zone::HandleNpcSpawnEvent 0x2567d0).
    void HandleNpcSpawnEvent(::Zone *zone, ::ZoneNpcSpawnEvent::SpawnEvent e, unsigned __int64 dataKey)
    {
        for (ZoneNpcSpawnEventView *ev = _eventListHead[e]; ev != nullptr; ev = ev->Next())
            ev->HandleNpcSpawnEvent(zone, dataKey);
    }

    ZoneNpcSpawnEventView *_eventListHead[2];  // +0 (0x0)
};

inline ZoneView *liftZoneView(Zone *zone)  // LIFT: no PDB name
{
    return reinterpret_cast<ZoneView *>(zone);
}

