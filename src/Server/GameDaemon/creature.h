// creature.h: creature.cpp, creature.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include <set>
#include "GameDaemonFwd.h"

// LIFT: views of the PDB record Data::SkillModifyLimitRecord (base DrEl, size 0x30) and of Data::SkillModifyLimitRecordPtr.
// Only the fields that the lifted bodies read are declared.
struct SkillModifyLimitRecordView
{
    char lift_pad_0[0x18];  // DrEl base (+0), key (+8), alias (+0x10): not declared yet
    short recycle_duration_min_ratio_percent;  // +24 (0x18)
    short recycle_duration_max_ratio_percent;  // +26 (0x1A)
    short sp_consume_min_value;  // +28 (0x1C)
    short sp_consume_max_value;  // +30 (0x1E)
    short damage_power_percent_min_ratio_percent;  // +32 (0x20)
    short damage_power_percent_max_ratio_percent;  // +34 (0x22)
    short hp_drain_percent_min_ratio_percent;  // +36 (0x24)
    short hp_drain_percent_max_ratio_percent;  // +38 (0x26)
    short heal_percent_min_ratio_percent;  // +40 (0x28)
    short heal_percent_max_ratio_percent;  // +42 (0x2A)
};

class SkillModifyLimitRecordPtrView
{
public:
    ::SkillModifyLimitRecordView *_record;  // 0x0 (PDB: DrRecordPtr::_record, DrEl *)
};

class ApplySkillModifyInfo
{
public:
    long const __cdecl CalcRecycleDuration(long) const;  // 0x453650
    short const __cdecl CalcSpConsume(short) const;  // 0x4536f0
    int const __cdecl CalcDamagePowerPercent(int) const;  // 0x453740
    short const __cdecl CalcHealPercent(short) const;  // 0x4537e0
    short const __cdecl CalcHpDrainPercent(short) const;  // 0x453880
private:
    int _divideValue;  // +0 (0x0)
    bool _skillModify;  // +4 (0x4)
    short _recycleDurationModifyPercent;  // +6 (0x6)
    int _recycleDurationModifyDiff;  // +8 (0x8)
    int _spConsumeModifyDiff;  // +12 (0xC)
    short _damagePowerPercentModifyPercent;  // +16 (0x10)
    int _damagePowerPercentModifyDiff;  // +20 (0x14)
    short _hpDrainPercentModifyPercent;  // +24 (0x18)
    int _hpDrainPercentModifyDiff;  // +28 (0x1C)
    short _healPercentModifyPercent;  // +32 (0x20)
    int _healPercentModifyDiff;  // +36 (0x24)
    ::SkillModifyLimitRecordPtrView _skillModifyLimitData;  // +40 (0x28) (PDB type: Data::SkillModifyLimitRecordPtr)
};
static_assert(sizeof(ApplySkillModifyInfo) == 0x30, "sizeof ApplySkillModifyInfo");

class ChangedProperty
{
public:
    bool __cdecl AddProperty(::Creature *, unsigned short);  // 0x276930
    bool __cdecl AddExtraProperty(::Creature *, unsigned short);  // 0x276b10
};

class Creature
{
public:
    virtual void __cdecl AddChangedPropertyId(unsigned short);  // 0x1d240
    virtual void __cdecl AddChangedExtraPropertyId(unsigned short);  // 0x1d280
    bool __cdecl IsCreatureInDuelCombat(void) const;  // 0x1edbb0
    __cdecl Creature(void);  // 0x260cd0
    virtual __cdecl ~Creature(void);  // 0x260ef0
    bool __cdecl Initialize(unsigned __int64);  // 0x261050
    void __cdecl SetZone(::Zone *);  // 0x261180
    virtual void __cdecl EnterZone(::EnterReason, bool, unsigned int);  // 0x261250
    virtual void __cdecl LeaveZone(::LeaveReason);  // 0x261350
    virtual bool __cdecl SetDead(bool, ::ChangedProperty *, unsigned __int64, unsigned __int64, unsigned __int64, bool, bool);  // 0x2614b0
    unsigned short __cdecl FetchBroadcastOnEncounterProperty(char *, unsigned short);  // 0x2614c0
    unsigned short __cdecl FetchBroadcastOnChangeProperty(char *, unsigned short);  // 0x261520
    unsigned short __cdecl FetchDbSyncProperty(char *, unsigned short, short *);  // 0x261580
    short __cdecl GetExtraBroadcastOnChangePropertySize(void);  // 0x261650
    unsigned short __cdecl FetchExtraDbSyncProperty(char *, unsigned short, short *);  // 0x2616b0
    unsigned short __cdecl FetchEffectList(char *, unsigned short, int);  // 0x2617a0
    short __cdecl GetEffectListSize(void);  // 0x2618b0
    unsigned short __cdecl FetchDuelBotSyncProperty(char *, unsigned short);  // 0x261930
    unsigned short __cdecl FetchDuelBotDiffProperty(char *, unsigned short);  // 0x261a10
    unsigned short __cdecl FetchAllProperty(char *, unsigned short);  // 0x261aa0
    unsigned short __cdecl FetchAllExtraProperty(char *, unsigned short);  // 0x261b30
    bool __cdecl IsInTheAir(void) const;  // 0x261c40
    bool __cdecl ChangeMoveState(::CreatureMoveState, short, wchar_t *);  // 0x261d80
private:
    void __cdecl initMoveCtx(void);  // 0x261e60
public:
    bool __cdecl CheckCounterSkill(void);  // 0x261f10
    bool __cdecl ExecuteCounterSkill(unsigned __int64, unsigned __int64);  // 0x261fb0
    bool __cdecl CheckImmuneSkillResult(::SkillResult);  // 0x262050
    bool __cdecl DelayCasting(::SkillResult);  // 0x2620d0
    bool __cdecl IsAttackable(void);  // 0x2621b0
    bool __cdecl Unlink(void);  // 0x262200
    unsigned __int64 __cdecl GetZoneAttractionGroup(void);  // 0x262e30
    void __cdecl AddChangedProperty(::ChangedProperty *);  // 0x263290
    static int __cdecl GetDuelGrade(int);  // 0x263790
    static int __cdecl GetBattleFieldGrade(char, int);  // 0x263870
    static int __cdecl GetFactionLevel(int);  // 0x263960
    static bool __cdecl CanJoinFaction(char, __int64, __int64);  // 0x263a40
    static int __cdecl GetLevelModify(::Creature *, ::Creature *, bool);  // 0x263ab0
    static ::CreatureSide __cdecl CheckSide(::Creature *, ::Creature *);  // 0x263bf0
    static bool __cdecl CanSeeGhost(::Creature *, ::Creature *);  // 0x263dc0
    static bool __cdecl CanSeeGhost(::Creature *, ::Data::NpcRecordPtr &);  // 0x263e20
    static bool __cdecl CanAttack(::Creature *, ::Creature *);  // 0x263e80
    static bool __cdecl CheckCombatSideEnabled(::Creature *, ::Creature *);  // 0x264050
    static ::CreatureSide __cdecl CheckSideByCombatSide(::Creature *, ::Creature *);  // 0x264090
    static bool __cdecl IsSamePartyAndCombatSide(::Creature *, ::Creature *);  // 0x264130
    static bool __cdecl CanAttack(::Creature *, ::Data::NpcRecordPtr);  // 0x264240
    static bool __cdecl IsHostileFaction(char, char);  // 0x264350
    void __cdecl DistributeMoney(bool, ::vector16, int, __int64, bool, bool);  // 0x2643b0
    static int __cdecl CalcFactionScore(char, char, int);  // 0x264b00
    static bool __cdecl CanDetect(::Npc *, ::Creature *);  // 0x264c00
    static void __cdecl GetRelatedPcWithTarget(::GameObject *, ::Pc **, ::Npc **);  // 0x264e30
    bool __cdecl IsValidTargetState(::Creature *, ::Data::SkillTargetStateType);  // 0x264f00
    bool __cdecl CheckCampfireCylinder(::Campfire *);  // 0x265000
    bool __cdecl CheckEffectFlag(::Data::EffectFlagType) const;  // 0x2650e0
    ::AbnormalState __cdecl GetAbnormalState(void);  // 0x265160
private:
    __int64 __cdecl calcDamage(::Creature *, int, __int64, short, ::SkillResult, bool, bool);  // 0x2651d0
public:
    __int64 __cdecl CalcPhysicalDamage(int, __int64);  // 0x267090
    __int64 __cdecl CalcForceDamage(::Creature *, int, __int64, short, ::SkillResult, bool);  // 0x2672b0
    __int64 __cdecl CalcHeal(__int64, short);  // 0x2672f0
    void __cdecl GetSoulMaskId(char &, char &);  // 0x267400
    unsigned __int64 __cdecl GetSoulMaskSetKey(void);  // 0x2676e0
private:
    void __cdecl invokeStanceEffects(unsigned __int64 const *, int);  // 0x2679c0
public:
    bool __cdecl ExecuteMove(::vector16, ::GeoCell const *, char const *const, int, short, long, char, ::MoveType, short, ::MoveTypeList *);  // 0x267cc0
    bool __cdecl HandleAllAbility(__int64, short, ::ChangedProperty *);  // 0x267eb0
    bool __cdecl HandleAbility(unsigned short, __int64, __int64, short, ::ChangedProperty *);  // 0x268010
    bool __cdecl HandleBool(unsigned short, bool, ::ChangedProperty *);  // 0x268640
    bool __cdecl HandleFlag(unsigned short, ::f_flag8::Operation, ::ChangedProperty *);  // 0x2687e0
    bool __cdecl HandleDead(char, ::ChangedProperty *);  // 0x268950
    bool __cdecl SetMasteryLevel(char, ::ChangedProperty *, bool);  // 0x268c70
    bool __cdecl HandleMasteryExp(__int64, ::ChangedProperty *, short);  // 0x268d10
    bool __cdecl HandleExp(__int64, ::ChangedProperty *, short);  // 0x269030
    bool __cdecl HandleExpAAA(__int64, ::ChangedProperty *, short);  // 0x26a1c0
    void __cdecl InitLevel(void);  // 0x26a320
    bool __cdecl HandleLevel(char, ::ChangedProperty *);  // 0x26a4e0
    bool __cdecl HandleMasteryLevel(char, ::ChangedProperty *);  // 0x26a5e0
    bool __cdecl HandleMoney(__int64, ::ChangedProperty *, short, bool);  // 0x26a6e0
    bool __cdecl HandleHpDamage(__int64 &, unsigned __int64, __int64, short, unsigned __int64, unsigned __int64, ::ChangedProperty *, char, int, bool, bool, bool);  // 0x26b080
    bool __cdecl HandleHpHeal(unsigned __int64, __int64, short, ::ChangedProperty *);  // 0x26bc00
    bool __cdecl HandleGuardGaugeDamage(unsigned __int64, __int64, short, ::ChangedProperty *);  // 0x26bd10
    bool __cdecl HandleGuardGaugeHeal(unsigned __int64, __int64, short, ::ChangedProperty *);  // 0x26be90
    bool __cdecl HandleSpDamage(unsigned __int64, int, short, ::ChangedProperty *);  // 0x26c040
    bool __cdecl HandleSpHeal(unsigned __int64, int, short, ::ChangedProperty *);  // 0x26c190
    bool __cdecl HandleSp(short, ::ChangedProperty *);  // 0x26c2a0
    bool __cdecl HandleMove(::vector16, ::GeoCell const *, char const *const, int, ::Effect *, ::ChangedProperty *);  // 0x26c380
    bool __cdecl HandleYaw(short, ::ChangedProperty *);  // 0x26cde0
    virtual bool __cdecl HandleStance(char, unsigned __int64 const *, int, ::ChangedProperty *);  // 0x26ceb0
    bool __cdecl HandleLink(unsigned __int64, char, char, char, ::ChangedProperty *);  // 0x26d080
    bool __cdecl HandleActionTarget(char, unsigned __int64, ::ChangedProperty *);  // 0x26d320
    bool __cdecl HandleAdditionalHp(int, short, ::ChangedProperty *);  // 0x26d420
    bool __cdecl HandleDebugFlag(unsigned short, ::f_flag8::Operation, ::ChangedProperty *);  // 0x26d4f0
    bool __cdecl HandleTarget(__int64, ::ChangedProperty *);  // 0x26d640
    bool __cdecl HandleEquipment(unsigned short, int, ::ChangedProperty *);  // 0x26d810
    bool __cdecl HandleEquipmentBodyGuildId(unsigned __int64, ::ChangedProperty *);  // 0x26d970
private:
    bool __cdecl handleEquipmentCustom(unsigned short, char, char *const, char, ::ChangedProperty *);  // 0x26da50
public:
    bool __cdecl HandleInventorySize(char, char, ::ChangedProperty *);  // 0x26dbc0
    bool __cdecl CheckToJoinFaction(char);  // 0x26dd10
    bool __cdecl HandleJoinFaction(char, ::ChangedProperty *);  // 0x26ddd0
    bool __cdecl HandleTransferFaction(char, ::ChangedProperty *, char);  // 0x26e2d0
    bool __cdecl HandleLeaveFaction(::ChangedProperty *);  // 0x26e550
    bool __cdecl HandleFactionReputation(int, ::ChangedProperty *, short);  // 0x26e740
    bool __cdecl HandleFactionScore(int, ::ChangedProperty *const);  // 0x26ebe0
    bool __cdecl HandleFactionScoreNpc(int, int, ::ChangedProperty *);  // 0x26ee40
    bool __cdecl HandleActivatedFaction(char, ::ChangedProperty *, bool, unsigned short);  // 0x26ef50
    bool __cdecl CheckToJoinFaction2(char);  // 0x26f020
    bool __cdecl HandleJoinFaction2(char, ::ChangedProperty *);  // 0x26f0e0
    bool __cdecl CheckToTransferFaction2(char);  // 0x26f5b0
    bool __cdecl HandleTransferFaction2(char, ::ChangedProperty *);  // 0x26f6a0
    bool __cdecl HandleLeaveFaction2(::ChangedProperty *);  // 0x26f880
    bool __cdecl IsJoinedFaction(unsigned __int64);  // 0x26fad0
private:
    bool __cdecl increaseEffectAttrCount(bool, ::Data::EffectAttributeType);  // 0x26fb80
    bool __cdecl decreaseEffectAttrCount(bool, ::Data::EffectAttributeType);  // 0x26fc40
    bool __cdecl decreaseEffectAttrCount2(int, bool, ::Data::EffectAttributeType);  // 0x26fd10
public:
    bool __cdecl AttachEffectAttr(bool, short *, short, unsigned __int64, unsigned __int64, unsigned __int64, ::ChangedProperty *);  // 0x26fdc0
    bool __cdecl DetachEffectAttr(int, bool, short *, short, unsigned __int64, unsigned __int64, unsigned __int64, ::ChangedProperty *);  // 0x26ffe0
    bool __cdecl HandleEffectAttribute(unsigned __int64, unsigned __int64, unsigned __int64, ::ChangedProperty *);  // 0x270330
    bool __cdecl HandleStyleScore(short, ::ChangedProperty *);  // 0x2704a0
    bool __cdecl HandleImmuneEffectAttribute(unsigned __int64, unsigned __int64, unsigned __int64, ::ChangedProperty *);  // 0x270550
    bool __cdecl HandleImmuneBreakerAttribute(short, short, ::ChangedProperty *);  // 0x2706c0
    bool __cdecl HandleEffectFlag(short, bool, ::ChangedProperty *);  // 0x2707e0
    bool __cdecl HandleFieldItem(unsigned __int64, ::ChangedProperty *);  // 0x270cc0
    bool __cdecl HandleSummoned(unsigned __int64, ::ChangedProperty *);  // 0x270dc0
    bool __cdecl HandleAchievementTitle(short, short, ::ChangedProperty *);  // 0x270ed0
    bool __cdecl HandleAchievementAbility(short, short, ::ChangedProperty *);  // 0x271070
    int const __cdecl GetMaxFactionScore(void) const;  // 0x271210
    bool __cdecl CheckToLockMasteryLevel(void);  // 0x2712e0
private:
    void __cdecl validateLevel(int, ::ChangedProperty *, bool);  // 0x271330
    void __cdecl validateMasteryLevel(__int64, ::ChangedProperty *, bool);  // 0x271650
public:
    bool __cdecl HandleConvoy(char, bool, ::ChangedProperty *);  // 0x2718a0
    bool __cdecl HandleSurvey(char, ::SurveyResult, ::ChangedProperty *);  // 0x271990
    bool __cdecl HandleGMMode(char, ::ChangedProperty *);  // 0x271b40
    bool __cdecl HandleGuildId(__int64, ::ChangedProperty *);  // 0x271c10
    bool __cdecl HandleGradeLevel(char, ::ChangedProperty *);  // 0x271dc0
    bool __cdecl HandleBindRaidDungeon(unsigned __int64, ::ChangedProperty *);  // 0x271ec0
    bool __cdecl HandlePvPSafeArea(bool, ::ChangedProperty *);  // 0x272080
    bool __cdecl HandlePvPMode(bool, ::ChangedProperty *);  // 0x272160
    bool __cdecl HandlePvPModeCoolTime(__int64, ::ChangedProperty *);  // 0x272240
    bool __cdecl HandleUnbindRaidDungeon(unsigned __int64, ::ChangedProperty *);  // 0x272360
    bool __cdecl HandleVitality(unsigned short, int, ::ChangedProperty *);  // 0x272520
    bool __cdecl HandleTopContributionGroupId(__int64, ::ChangedProperty *);  // 0x2727c0
    bool __cdecl HandleSkillSkinId(short, ::ChangedProperty *);  // 0x272870
    bool __cdecl HandleGuildInvitationRefusal(bool, ::ChangedProperty *);  // 0x272b40
    bool __cdecl HandleGhostType(char, ::ChangedProperty *);  // 0x272c50
    bool __cdecl AddDamageValue(__int64);  // 0x272d90
    bool __cdecl AddDamagedValue(unsigned __int64, __int64, ::ChangedProperty *);  // 0x272f60
    bool __cdecl HandleAccumulatedDamage(::Data::EffectAccumulateDamageSlotType, __int64, __int64, ::ChangedProperty *);  // 0x273070
    char __cdecl GetSurveyState(char);  // 0x273180
    bool __cdecl HandleFactionKilledCount(char, ::ChangedProperty *);  // 0x273290
    virtual bool __cdecl HandleCombatSide(char, ::ChangedProperty *);  // 0x2733a0
    bool __cdecl HandleDuelGrade(::ChangedProperty *);  // 0x2735d0
    bool __cdecl HandleDuelPoint(int, ::ChangedProperty *);  // 0x273830
    bool __cdecl HandlePartyBattlePoint(int, ::ChangedProperty *);  // 0x2738f0
    bool __cdecl HandleFieldPlayPoint(int, ::ChangedProperty *, short, int, int, int);  // 0x2739b0
    bool __cdecl HandleUsableSkillBuildUpPoint(short, ::ChangedProperty *, short, __int64, __int64, __int64, wchar_t *);  // 0x273d30
    short __cdecl InitUsableSkillBuildUpPoint(::ChangedProperty *);  // 0x274180
private:
    bool __cdecl handleAcquiredSkillBuildUpPoint(short, ::ChangedProperty *, short);  // 0x274380
public:
    bool __cdecl HandleInstantHeartCount(char, ::ChangedProperty *);  // 0x2744e0
    bool __cdecl HandleHeartCount(char, ::ChangedProperty *);  // 0x274600
    bool __cdecl HandleActivatedBadgePage(char, ::ChangedProperty *);  // 0x2746f0
    char __cdecl GetActivatedBadgeEquipSlot(void);  // 0x2749f0
    bool __cdecl IsActivatedBadgeEquipSlot(unsigned char);  // 0x274a10
    bool __cdecl HandleEquipBadgeGearScore(int, ::ChangedProperty *);  // 0x274a60
    bool __cdecl FetchChangedProperty(short &, short &, char *, short &, short &, char *, short &, short &, char *, short &, short &, char *);  // 0x274c20
    void __cdecl Regeneration(::ChangedProperty &);  // 0x275020
    bool __cdecl InitAccountExp(::AccountExpInfo const &);  // 0x275160
    bool __cdecl HandleAccountExpToAdd(__int64, ::ChangedProperty *, short);  // 0x275320
private:
    void __cdecl validateAccountLevel(__int64, ::ChangedProperty *, bool, short);  // 0x275760
public:
    bool __cdecl HandleAccountExpQuota(int, __int64, ::ChangedProperty *);  // 0x275a10
    bool __cdecl HandleAccountExpForApplyToLobby(__int64, ::ChangedProperty *, bool &);  // 0x275c20
    bool __cdecl HandleAccountExpAddedForRecover(::ChangedProperty *);  // 0x275ff0
private:
    bool __cdecl checkAccountExpQuota(__int64 &);  // 0x276400
public:
    bool __cdecl HandleAccountExpWithoutConsumeQuota(__int64, ::ChangedProperty *, short);  // 0x2764f0
    // LIFT: PDB type of _changedPropertyIdListSet and _changedExtraPropertyIdListSet.
    typedef std::set<unsigned short, std::less<__int64>, StlAllocator<unsigned short, 2> > ChangedPropertyIdSet;
};

// LIFT: view of the PDB class Creature (size 0xC50). Only the members that the lifted bodies use are declared.
struct CreatureMemberView
{
    char lift_pad_0[0x28];  // ❓ no PDB name: GameObject fields +0 to +0x27 are not declared yet
    unsigned __int64 Id;  // +40 (0x28) (PDB: GameObject::Id)
    char lift_pad_30[0x235 - 0x30];  // ❓ no PDB name: Prop (CreatureProperty, +0x30) is not declared yet
    char combat_side;  // +565 (0x235) (PDB: Prop.State.combat_side; State at Prop+0xD8, combat_side at State+0x12D)
    char lift_pad_236[0xC08 - 0x236];  // ❓ no PDB name: fields +0x236 to +0xC07 are not declared yet
    ::Creature::ChangedPropertyIdSet _changedPropertyIdListSet;  // +3080 (0xC08) (PDB: Creature::_changedPropertyIdListSet)
    ::Creature::ChangedPropertyIdSet _changedExtraPropertyIdListSet;  // +3112 (0xC28) (PDB: Creature::_changedExtraPropertyIdListSet)
    char lift_pad_c48[0xC50 - 0xC48];  // ❓ no PDB name: _instantDeathUnapplicable and others
};
static_assert(sizeof(CreatureMemberView) == 0xC50, "sizeof CreatureMemberView");

class CreatureStateKeeper
{
public:
    __cdecl ~CreatureStateKeeper(void);  // 0x1edbf0
    void __cdecl SnapshotCreatureState(void);  // 0x1edc40
    void __cdecl ReplaceCreatureState(void);  // 0x276ca0
};

