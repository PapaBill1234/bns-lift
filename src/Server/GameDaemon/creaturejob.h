// creaturejob.h: creaturejob.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class ArcherRule
{
public:
    virtual void __cdecl OnAttackResultEvent(::GameObject *, ::SkillResult, short);  // 0x9a530
    virtual void __cdecl OnAttackedResultEvent(::GameObject *, ::SkillResult, bool);  // 0x9a580
    virtual void __cdecl OnRegeneration(::ChangedProperty *);  // 0x9a5d0
    virtual void __cdecl OnCombatModeChanged(bool, ::ChangedProperty *);  // 0x9a600
    virtual void __cdecl OnEnterWorld(::ChangedProperty *);  // 0x9a640
};

class AssassinRule
{
public:
    virtual void __cdecl OnAttackResultEvent(::GameObject *, ::SkillResult, short);  // 0x9a2b0
    virtual void __cdecl OnAttackedResultEvent(::GameObject *, ::SkillResult, bool);  // 0x9a300
    virtual void __cdecl OnCombatModeChanged(bool, ::ChangedProperty *);  // 0x9a3d0
};

class BladeMasterRule
{
public:
    virtual void __cdecl OnAttackResultEvent(::GameObject *, ::SkillResult, short);  // 0x99560
    virtual void __cdecl OnAttackedResultEvent(::GameObject *, ::SkillResult, bool);  // 0x995c0
    virtual void __cdecl OnRegeneration(::ChangedProperty *);  // 0x99680
    virtual void __cdecl OnPointZero(::CreatureJobRule::PointType, ::ChangedProperty *);  // 0x996f0
    virtual void __cdecl OnCombatModeChanged(bool, ::ChangedProperty *);  // 0x99730
    virtual bool __cdecl CheckToChangeStance(char);  // 0x99770
};

class CreatureJobRuleFactory
{
public:
    static ::CreatureJobRule * __cdecl CreateCreatureJobRule(char);  // 0x9a830
    static char __cdecl GetDefaultStance(char);  // 0x9ac60
};

class DestroyerRule
{
public:
    virtual void __cdecl OnAttackResultEvent(::GameObject *, ::SkillResult, short);  // 0x99dd0
    virtual void __cdecl OnAttackedResultEvent(::GameObject *, ::SkillResult, bool);  // 0x99e20
    virtual void __cdecl OnRegeneration(::ChangedProperty *);  // 0x99fc0
    virtual void __cdecl OnDamaged(::GameObject *, __int64);  // 0x9a010
    virtual void __cdecl OnCombatModeChanged(bool, ::ChangedProperty *);  // 0x9a040
};

class ForceMasterRule
{
public:
    virtual void __cdecl OnAttackResultEvent(::GameObject *, ::SkillResult, short);  // 0x99c90
    virtual void __cdecl OnAttackedResultEvent(::GameObject *, ::SkillResult, bool);  // 0x99ce0
};

class KungFuFighterRule
{
public:
    virtual void __cdecl OnAttackResultEvent(::GameObject *, ::SkillResult, short);  // 0x99bb0
    virtual void __cdecl OnAttackedResultEvent(::GameObject *, ::SkillResult, bool);  // 0x99c00
    virtual void __cdecl OnCombatModeChanged(bool, ::ChangedProperty *);  // 0x99c50
};

class ShooterRule
{
public:
    virtual void __cdecl OnAttackResultEvent(::GameObject *, ::SkillResult, short);  // 0x99d30
    virtual void __cdecl OnAttackedResultEvent(::GameObject *, ::SkillResult, bool);  // 0x99d80
};

class SoulFighterRule
{
public:
    virtual void __cdecl OnCombatModeChanged(bool, ::ChangedProperty *);  // 0x9a410
};

class SpearMasterRule
{
public:
    virtual void __cdecl OnAttackResultEvent(::GameObject *, ::SkillResult, short);  // 0x9a670
    virtual void __cdecl OnAttackedResultEvent(::GameObject *, ::SkillResult, bool);  // 0x9a6c0
    virtual void __cdecl OnCombatModeChanged(bool, ::ChangedProperty *);  // 0x9a710
};

class SummonerRule
{
public:
    virtual void __cdecl OnLevelUp(char, char);  // 0x99b00
    virtual void __cdecl OnAttackResultEvent(::GameObject *, ::SkillResult, short);  // 0x9a080
    virtual void __cdecl OnAttackedResultEvent(::GameObject *, ::SkillResult, bool);  // 0x9a1a0
    virtual void __cdecl OnCombatModeChanged(bool, ::ChangedProperty *);  // 0x9a1f0
};

class SwordMasterRule
{
public:
    virtual void __cdecl OnAttackResultEvent(::GameObject *, ::SkillResult, short);  // 0x99790
    virtual void __cdecl OnAttackedResultEvent(::GameObject *, ::SkillResult, bool);  // 0x997f0
    virtual void __cdecl OnRegeneration(::ChangedProperty *);  // 0x998b0
    virtual void __cdecl OnPointZero(::CreatureJobRule::PointType, ::ChangedProperty *);  // 0x99920
    virtual void __cdecl OnCombatModeChanged(bool, ::ChangedProperty *);  // 0x99960
    virtual bool __cdecl CheckToChangeStance(char);  // 0x999a0
};

class ThundererRule
{
public:
    virtual void __cdecl OnAttackResultEvent(::GameObject *, ::SkillResult, short);  // 0x9a750
    virtual void __cdecl OnAttackedResultEvent(::GameObject *, ::SkillResult, bool);  // 0x9a7a0
    virtual void __cdecl OnCombatModeChanged(bool, ::ChangedProperty *);  // 0x9a7f0
};

class WarlockRule
{
public:
    virtual void __cdecl OnCastSkill(void);  // 0x999c0
};

class WarriorRule
{
public:
    virtual void __cdecl OnAttackResultEvent(::GameObject *, ::SkillResult, short);  // 0x9a450
    virtual void __cdecl OnAttackedResultEvent(::GameObject *, ::SkillResult, bool);  // 0x9a4a0
    virtual void __cdecl OnCombatModeChanged(bool, ::ChangedProperty *);  // 0x9a4f0
};

