// npc.h: npc.cpp, npc.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"
#include "action.h"

class Npc
{
public:
    virtual short __cdecl GetAttackHitValueModify(void);  // 0x27380
    virtual short __cdecl GetAttackCriticalValueModify(void);  // 0x27390
    virtual short __cdecl GetDefendCriticalValueModify(void);  // 0x273a0
    virtual short __cdecl GetDefendDodgeValueModify(void);  // 0x273b0
    virtual short __cdecl GetDefendParryValueModify(void);  // 0x273c0
    virtual short __cdecl GetDefendPhysicalValueModify(void);  // 0x273d0
    virtual short __cdecl GetDefendForceValueModify(void);  // 0x273e0
    virtual short __cdecl GetAttackStiffDurationValueModify(void);  // 0x273f0
    virtual short __cdecl GetDefendStiffDurationValueModify(void);  // 0x27400
    virtual short __cdecl GetCastDurationValueModify(void);  // 0x27410
    virtual short __cdecl GetAttackCriticalDamageModify(void);  // 0x27420
    virtual short __cdecl GetDefendCriticalDamageModify(void);  // 0x27430
    virtual short __cdecl GetAttackPierceModify(void);  // 0x27440
    virtual short __cdecl GetAttackParryPierceModify(void);  // 0x27450
    virtual short __cdecl GetDefendParryReduceModify(void);  // 0x27460
    virtual short __cdecl GetAttackPerfectParryDamageModify(void);  // 0x27470
    virtual short __cdecl GetDefendPerfectParryReduceModify(void);  // 0x27480
    virtual short __cdecl GetAttackCounterDamageModify(void);  // 0x27490
    virtual short __cdecl GetDefendCounterReduceModify(void);  // 0x274a0
    virtual short __cdecl GetHealPowerModify(void);  // 0x274b0
    virtual short __cdecl GetAOEDefendPowerModify(void);  // 0x274c0
    virtual short __cdecl GetAbnormalAttackPowerModify(void);  // 0x274d0
    virtual short __cdecl GetAbnormalDefendPowerModify(void);  // 0x274e0
    virtual short __cdecl GetHatePowerModify(void);  // 0x274f0
    virtual short __cdecl GetAttackAttributeModify(void);  // 0x27500
    virtual short __cdecl GetRAttackAoePierceModify(void);  // 0x27510
    virtual short __cdecl GetRAttackAbnormalHitModify(void);  // 0x27520
    virtual short __cdecl GetRDefendAbnormalDodgeModify(void);  // 0x27530
    virtual short __cdecl GetRSupportPowerModify(void);  // 0x27540
    virtual short __cdecl GetRHypermovePowerModify(void);  // 0x27550
    __cdecl Npc(::Zone *, ::Data::NpcRecordPtr, ::NpcSpawnInfo);  // 0x40f630
    virtual __cdecl ~Npc(void);  // 0x40f950
    virtual bool __cdecl Initialize(unsigned __int64, ::NpcSpawnParam const &);  // 0x40fba0
    virtual void __cdecl EnterZone(::EnterReason, bool, unsigned int);  // 0x40fd30
    void __cdecl EnterBossChallengeAttraction(::EnterReason, bool, unsigned int, unsigned __int64 *const, char);  // 0x4101a0
    void __cdecl EnterAttraction(void);  // 0x4102b0
private:
    ::NpcContribution * __cdecl createContribution(void);  // 0x410500
    ::Data::ContributionRewardRecordPtr __cdecl getContributionRewardData(void);  // 0x410680
public:
    virtual void __cdecl LeaveZone(::LeaveReason);  // 0x410750
    virtual void __cdecl GetImmuneEffectAttributeValueFromData(unsigned __int64 &, unsigned __int64 &, unsigned __int64 &);  // 0x410810
    bool __cdecl ProgressRaidDungeonStep(unsigned __int64);  // 0x4108a0
    virtual bool __cdecl SetDead(bool, ::ChangedProperty *, unsigned __int64, unsigned __int64, unsigned __int64, bool, bool);  // 0x410c00
private:
    void __cdecl loadData(void);  // 0x410ee0
public:
    bool __cdecl SetScript(unsigned __int64);  // 0x411540
    void __cdecl SetImmuneBreakDisable(bool);  // 0x4115d0
    virtual bool __cdecl CheckImmuneBreak(::Creature *, ::Data::EffectRecord const *, ::ChangedProperty *);  // 0x411650
    virtual bool __cdecl Think(::ScriptEvent const *);  // 0x411890
    bool __cdecl ChangeBrain(::Data::NpcBrainType, bool, bool);  // 0x411930
    void __cdecl ActionFinished(::Action *, ::NpcActionQueue::ActionExpiredReason);  // 0x411c90
    virtual void __cdecl OnSpawn(void);  // 0x411d70
    virtual void __cdecl OnDespawn(void);  // 0x411ed0
    bool __cdecl CreateDeadbody(void);  // 0x411fd0
    void __cdecl SetDespawnSocial(unsigned __int64);  // 0x4131c0
    bool __cdecl DespawnIfPending(void);  // 0x413210
    void __cdecl ReserveDespawn(bool, bool, unsigned __int64, long);  // 0x413250
    void __cdecl ReservePlaySocial(unsigned int, unsigned __int64, long, bool);  // 0x4134f0
    virtual void __cdecl OnAttacked(::Zone *, ::GameObject *, unsigned __int64, short);  // 0x413710
    virtual void __cdecl OnDamaged(::Zone *, ::GameObject *, unsigned int, __int64, __int64);  // 0x4137c0
    unsigned __int64 __cdecl Detect(void);  // 0x413d50
    void __cdecl Rotate(short, bool);  // 0x413eb0
    ::Pointer2< ::RaidDungeon> __cdecl getRaidDungeon(::Pc *, ::Pc *, unsigned __int64, unsigned __int64);  // 0x414040
    int __cdecl getNewbieCount(::Pc *);  // 0x414290
    void __cdecl OnKilled(::Zone *, ::GameObject *, unsigned __int64);  // 0x4143f0
private:
    void __cdecl sendNpcKilledEvent(::Pc *, unsigned __int64);  // 0x415400
    void __cdecl sendNpcKilledEventParty(int, unsigned __int64 *const, bool, __int64, __int64);  // 0x415600
public:
    void __cdecl OnInvokeEffect(::Zone *, unsigned __int64, unsigned int, __int64, __int64, __int64);  // 0x4159d0
    void __cdecl OnInvokedEffect(::Zone *, unsigned __int64, unsigned int, __int64, __int64, __int64, char);  // 0x415b60
    virtual void __cdecl OnAttack(::Zone *, ::GameObject *, unsigned __int64, short);  // 0x415dd0
    virtual void __cdecl OnDamage(::Zone *, ::GameObject *, unsigned int, __int64);  // 0x415df0
    void __cdecl OnKill(::Zone *, ::GameObject *, unsigned __int64, char, char);  // 0x415e10
private:
    void __cdecl distributeExp(::Pc &);  // 0x416010
    void __cdecl giveFactionScore(::Pc &);  // 0x417870
public:
    void __cdecl SetAttackable(bool);  // 0x4179b0
    void __cdecl SetExceptionTarget(bool, ::ChangedProperty *);  // 0x417a60
private:
    bool __cdecl setFirstAttacker(::GameObject &);  // 0x417ba0
public:
    ::GameFailReason __cdecl TalkStart(unsigned __int64);  // 0x417dc0
    void __cdecl TalkStop(unsigned __int64);  // 0x417f10
    virtual void __cdecl OnCombatStart(::Creature *, bool);  // 0x417fd0
    virtual void __cdecl OnCombatEnd(void);  // 0x4185f0
    bool __cdecl DropFieldItem(::Pc *, short, char, bool, __int64, __int64, __int64, int, ::Pc *);  // 0x418ad0
    bool __cdecl CheckToManipulate(::Pc *, ::Item *, ::QuestRequiredItems const *);  // 0x418e50
    void __cdecl Manipulate(::Pc *, ::Item *, ::QuestRequiredItems const *);  // 0x419180
    void __cdecl UpdateWaypoint(void);  // 0x4199e0
    ::HideType __cdecl CanChangeHide(bool, unsigned __int64 &);  // 0x419a60
    bool __cdecl Hide(::HideType);  // 0x419b30
    ::CombatSequence * __cdecl GetCombatSequence(void) const;  // 0x41a220
    bool __cdecl SetActSequence(unsigned __int64);  // 0x41a260
    bool __cdecl SetCombatSequence(unsigned __int64);  // 0x41a2c0
    unsigned __int64 __cdecl GetNextStopSocial(short &);  // 0x41a320
private:
    ::vector16 const __cdecl GetInitialCombatStartPos(void);  // 0x41a4a0
public:
    virtual bool __cdecl HandleStance(char, unsigned __int64 const *, int, ::ChangedProperty *);  // 0x41a5c0
private:
    virtual bool __cdecl changeMoveState(::CreatureMoveState, short, wchar_t *);  // 0x41a5f0
public:
    bool __cdecl IsExpiredCombatTimer(char);  // 0x41aa60
private:
    ::Pointer2< ::Creature> __cdecl getFirstAttackerCreaturePtr(::Zone *);  // 0x41ab10
public:
    static bool __cdecl HasContribution(::Data::NpcRecordPtr);  // 0x41b1a0
    static unsigned __int64 __cdecl GetTodayReward(::Data::NpcRecordPtr);  // 0x41b1e0
    static unsigned __int64 __cdecl GetTodayPeaktimeReward(::Data::NpcRecordPtr);  // 0x41b2d0
    static unsigned __int64 __cdecl GetTodayContributionReward(::Data::NpcRecordPtr);  // 0x41b4f0
    static unsigned __int64 __cdecl GetTodayContributionPeaktimeReward(::Data::NpcRecordPtr);  // 0x41b5e0
    virtual void __cdecl TakeFactionScore(::GameObject *);  // 0x41b800
private:
    __int64 __cdecl calculateAdditionalExpBonusByTestServer(__int64);  // 0x41ba20
public:
    void __cdecl TransferDamageToLeader(::GameObject *, __int64);  // 0x41ba80
};

