// summoned.h: summoned.cpp, summoned.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class Summoned
{
public:
    virtual short __cdecl GetAttackHitValueModify(void);  // 0x455210
    virtual short __cdecl GetAttackCriticalValueModify(void);  // 0x455220
    virtual short __cdecl GetDefendCriticalValueModify(void);  // 0x455230
    virtual short __cdecl GetDefendDodgeValueModify(void);  // 0x455240
    virtual short __cdecl GetDefendParryValueModify(void);  // 0x455250
    virtual short __cdecl GetDefendPhysicalValueModify(void);  // 0x455260
    virtual short __cdecl GetDefendForceValueModify(void);  // 0x455270
    virtual short __cdecl GetAttackStiffDurationValueModify(void);  // 0x455280
    virtual short __cdecl GetDefendStiffDurationValueModify(void);  // 0x455290
    virtual short __cdecl GetCastDurationValueModify(void);  // 0x4552a0
    virtual short __cdecl GetAttackCriticalDamageModify(void);  // 0x4552b0
    virtual short __cdecl GetDefendCriticalDamageModify(void);  // 0x4552c0
    virtual short __cdecl GetAttackPierceModify(void);  // 0x4552d0
    virtual short __cdecl GetAttackParryPierceModify(void);  // 0x4552e0
    virtual short __cdecl GetDefendParryReduceModify(void);  // 0x4552f0
    virtual short __cdecl GetAttackPerfectParryDamageModify(void);  // 0x455300
    virtual short __cdecl GetDefendPerfectParryReduceModify(void);  // 0x455310
    virtual short __cdecl GetAttackCounterDamageModify(void);  // 0x455320
    virtual short __cdecl GetDefendCounterReduceModify(void);  // 0x455330
    virtual short __cdecl GetHealPowerModify(void);  // 0x455340
    virtual short __cdecl GetAOEDefendPowerModify(void);  // 0x455350
    virtual short __cdecl GetAbnormalAttackPowerModify(void);  // 0x455360
    virtual short __cdecl GetAbnormalDefendPowerModify(void);  // 0x455370
    virtual short __cdecl GetHatePowerModify(void);  // 0x455380
    virtual short __cdecl GetAttackAttributeModify(void);  // 0x455390
    virtual short __cdecl GetRAttackAoePierceModify(void);  // 0x4553a0
    virtual short __cdecl GetRAttackAbnormalHitModify(void);  // 0x4553b0
    virtual short __cdecl GetRDefendAbnormalDodgeModify(void);  // 0x4553c0
    virtual short __cdecl GetRSupportPowerModify(void);  // 0x4553d0
    virtual short __cdecl GetRHypermovePowerModify(void);  // 0x4553e0
    __cdecl Summoned(void);  // 0x611190
    virtual __cdecl ~Summoned(void);  // 0x611320
    bool __cdecl Initialize(unsigned __int64, ::Pc *, ::SummonedEntry *, ::Data::SummonedRecordPtr, ::Data::SummonedLevelRecordPtr);  // 0x6113d0
    virtual void __cdecl EnterZone(::EnterReason, bool, unsigned int);  // 0x611490
    virtual void __cdecl LeaveZone(::LeaveReason);  // 0x611830
    unsigned short __cdecl FetchAllSummonedProperty(char *, unsigned short);  // 0x6119d0
    virtual void __cdecl GetImmuneEffectAttributeValueFromData(unsigned __int64 &, unsigned __int64 &, unsigned __int64 &);  // 0x611a60
    virtual void __cdecl Send(char const *, ...);  // 0x611af0
    virtual void __cdecl Send(::Packet const *);  // 0x611b20
    virtual void __cdecl Send(::PacketList const *);  // 0x611b50
    virtual void __cdecl OnTimer(::Zone *, unsigned short);  // 0x611b80
    void __cdecl DespawnDelaying(void);  // 0x611ca0
    virtual void __cdecl SetCombatModeByAttack(bool, ::SourceLocation const &);  // 0x611d60
    virtual void __cdecl SetCombatModeByAttacked(::SourceLocation const &);  // 0x611d90
    virtual void __cdecl SetCombatModeByTargeted(::SourceLocation const &);  // 0x611dc0
    virtual void __cdecl ResetCombatModeByTargeted(::SourceLocation const &);  // 0x611df0
    virtual void __cdecl SetCombatModeByLink(::SourceLocation const &);  // 0x611e20
    virtual void __cdecl ResetCombatModeByLink(::SourceLocation const &);  // 0x611e50
    virtual void __cdecl ResetCombatMode(bool, ::SourceLocation const &);  // 0x611e80
    virtual bool __cdecl HandleCombatSide(char, ::ChangedProperty *);  // 0x611eb0
    void __cdecl Spawn(::EnterReason);  // 0x611f20
    void __cdecl Decompose(void);  // 0x612090
    void __cdecl Respawn(void);  // 0x6121c0
    void __cdecl SyncMasterState(void);  // 0x612380
    void __cdecl LoadData(void);  // 0x612530
    virtual bool __cdecl HandleStance(char, unsigned __int64 const *, int, ::ChangedProperty *);  // 0x612810
    bool __cdecl ApplyLevelData(::ChangedProperty *const, char, char);  // 0x612840
    ::Data::SummonedMasteryLevelRecordPtr const __cdecl GetSummonedMasterLevel(char);  // 0x612950
    bool __cdecl ValidateAbility(::ChangedProperty *const, char);  // 0x612a50
    bool __cdecl RemasterValidateAbility(::ChangedProperty *const, char);  // 0x612e70
    bool __cdecl EquipItems(::ChangedProperty *);  // 0x6133e0
    bool __cdecl ApplySummonerJobAbility(::ChangedProperty *, ::Data::SummonedLevelRecord const *);  // 0x6134d0
    virtual void __cdecl OnAttacked(::Zone *, ::GameObject *, unsigned __int64, short);  // 0x615250
    void __cdecl OnKill(::Zone *, ::Pc *, unsigned __int64, char, char);  // 0x615280
    virtual bool __cdecl SetDead(bool, ::ChangedProperty *, unsigned __int64, unsigned __int64, unsigned __int64, bool, bool);  // 0x615440
    void __cdecl SendSummonedPropertyChangedNotify(void);  // 0x6155b0
private:
    void __cdecl handleSpawningStateProperty(bool);  // 0x615800
    void __cdecl finishSpawning(bool);  // 0x615950
    virtual bool __cdecl changeMoveState(::CreatureMoveState, short, wchar_t *);  // 0x616c30
public:
    virtual void __cdecl StartCombat(void);  // 0x616f10
    virtual void __cdecl FinishCombat(void);  // 0x616f50
};

class SummonedEntry
{
public:
    __cdecl SummonedEntry(void);  // 0x96fb0
    __cdecl SummonedEntry(char);  // 0x97010
};

class SummonedManager
{
public:
    static ::Pc * __cdecl GetPc(::Creature *);  // 0x615b30
    __cdecl ~SummonedManager(void);  // 0x615b60
    void __cdecl SetSummonedJob(char);  // 0x615be0
    void __cdecl CreateSummoned(int);  // 0x615d30
    int __cdecl SetDbData(short, char const *, int);  // 0x615db0
    void __cdecl ConfirmAcquire(char);  // 0x616310
};

