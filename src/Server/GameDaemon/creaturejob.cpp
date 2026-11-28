// creaturejob.cpp: creaturejob.cpp (GameDaemon PDB, 2019 + PDB). Wave 0 stubs and lifted leaves. A stub is not a lift.
#include "creaturejob.h"
#include "creature.h"
#include "gameobject.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?OnDamaged@DestroyerRule@@UEAAXPEAVGameObject@@_J@Z")  // LIFT: dead-strip keep (no live caller yet)

// 0x99560
void __cdecl BladeMasterRule::OnAttackResultEvent(::GameObject *, ::SkillResult, short)
{
    LIFT_STUB(0x99560);
}

// 0x995c0
void __cdecl BladeMasterRule::OnAttackedResultEvent(::GameObject *, ::SkillResult, bool)
{
    LIFT_STUB(0x995c0);
}

// 0x99680
void __cdecl BladeMasterRule::OnRegeneration(::ChangedProperty *)
{
    LIFT_STUB(0x99680);
}

// 0x996f0
void __cdecl BladeMasterRule::OnPointZero(::CreatureJobRule::PointType, ::ChangedProperty *)
{
    LIFT_STUB(0x996f0);
}

// 0x99730
void __cdecl BladeMasterRule::OnCombatModeChanged(bool, ::ChangedProperty *)
{
    LIFT_STUB(0x99730);
}

// 0x99770
bool __cdecl BladeMasterRule::CheckToChangeStance(char)
{
    LIFT_STUB(0x99770);
}

// 0x99790
void __cdecl SwordMasterRule::OnAttackResultEvent(::GameObject *, ::SkillResult, short)
{
    LIFT_STUB(0x99790);
}

// 0x997f0
void __cdecl SwordMasterRule::OnAttackedResultEvent(::GameObject *, ::SkillResult, bool)
{
    LIFT_STUB(0x997f0);
}

// 0x998b0
void __cdecl SwordMasterRule::OnRegeneration(::ChangedProperty *)
{
    LIFT_STUB(0x998b0);
}

// 0x99920
void __cdecl SwordMasterRule::OnPointZero(::CreatureJobRule::PointType, ::ChangedProperty *)
{
    LIFT_STUB(0x99920);
}

// 0x99960
void __cdecl SwordMasterRule::OnCombatModeChanged(bool, ::ChangedProperty *)
{
    LIFT_STUB(0x99960);
}

// 0x999a0
bool __cdecl SwordMasterRule::CheckToChangeStance(char)
{
    LIFT_STUB(0x999a0);
}

// 0x999c0
void __cdecl WarlockRule::OnCastSkill(void)
{
    LIFT_STUB(0x999c0);
}

// 0x99b00
void __cdecl SummonerRule::OnLevelUp(char, char)
{
    LIFT_STUB(0x99b00);
}

// 0x99bb0
void __cdecl KungFuFighterRule::OnAttackResultEvent(::GameObject *, ::SkillResult, short)
{
    LIFT_STUB(0x99bb0);
}

// 0x99c00
void __cdecl KungFuFighterRule::OnAttackedResultEvent(::GameObject *, ::SkillResult, bool)
{
    LIFT_STUB(0x99c00);
}

// 0x99c50
void __cdecl KungFuFighterRule::OnCombatModeChanged(bool, ::ChangedProperty *)
{
    LIFT_STUB(0x99c50);
}

// 0x99c90
void __cdecl ForceMasterRule::OnAttackResultEvent(::GameObject *, ::SkillResult, short)
{
    LIFT_STUB(0x99c90);
}

// 0x99ce0
void __cdecl ForceMasterRule::OnAttackedResultEvent(::GameObject *, ::SkillResult, bool)
{
    LIFT_STUB(0x99ce0);
}

// 0x99d30
void __cdecl ShooterRule::OnAttackResultEvent(::GameObject *, ::SkillResult, short)
{
    LIFT_STUB(0x99d30);
}

// 0x99d80
void __cdecl ShooterRule::OnAttackedResultEvent(::GameObject *, ::SkillResult, bool)
{
    LIFT_STUB(0x99d80);
}

// 0x99dd0
void __cdecl DestroyerRule::OnAttackResultEvent(::GameObject *, ::SkillResult, short)
{
    LIFT_STUB(0x99dd0);
}

// 0x99e20
void __cdecl DestroyerRule::OnAttackedResultEvent(::GameObject *, ::SkillResult, bool)
{
    LIFT_STUB(0x99e20);
}

// 0x99fc0
void __cdecl DestroyerRule::OnRegeneration(::ChangedProperty *)
{
    LIFT_STUB(0x99fc0);
}

// 0x9a010
void __cdecl DestroyerRule::OnDamaged(::GameObject *target, __int64 damage)
{
}

// 0x9a040
void __cdecl DestroyerRule::OnCombatModeChanged(bool, ::ChangedProperty *)
{
    LIFT_STUB(0x9a040);
}

// 0x9a080
void __cdecl SummonerRule::OnAttackResultEvent(::GameObject *, ::SkillResult, short)
{
    LIFT_STUB(0x9a080);
}

// 0x9a1a0
void __cdecl SummonerRule::OnAttackedResultEvent(::GameObject *, ::SkillResult, bool)
{
    LIFT_STUB(0x9a1a0);
}

// 0x9a1f0
void __cdecl SummonerRule::OnCombatModeChanged(bool, ::ChangedProperty *)
{
    LIFT_STUB(0x9a1f0);
}

// 0x9a2b0
void __cdecl AssassinRule::OnAttackResultEvent(::GameObject *, ::SkillResult, short)
{
    LIFT_STUB(0x9a2b0);
}

// 0x9a300
void __cdecl AssassinRule::OnAttackedResultEvent(::GameObject *, ::SkillResult, bool)
{
    LIFT_STUB(0x9a300);
}

// 0x9a3d0
void __cdecl AssassinRule::OnCombatModeChanged(bool, ::ChangedProperty *)
{
    LIFT_STUB(0x9a3d0);
}

// 0x9a410
void __cdecl SoulFighterRule::OnCombatModeChanged(bool, ::ChangedProperty *)
{
    LIFT_STUB(0x9a410);
}

// 0x9a450
void __cdecl WarriorRule::OnAttackResultEvent(::GameObject *, ::SkillResult, short)
{
    LIFT_STUB(0x9a450);
}

// 0x9a4a0
void __cdecl WarriorRule::OnAttackedResultEvent(::GameObject *, ::SkillResult, bool)
{
    LIFT_STUB(0x9a4a0);
}

// 0x9a4f0
void __cdecl WarriorRule::OnCombatModeChanged(bool, ::ChangedProperty *)
{
    LIFT_STUB(0x9a4f0);
}

// 0x9a530
void __cdecl ArcherRule::OnAttackResultEvent(::GameObject *, ::SkillResult, short)
{
    LIFT_STUB(0x9a530);
}

// 0x9a580
void __cdecl ArcherRule::OnAttackedResultEvent(::GameObject *, ::SkillResult, bool)
{
    LIFT_STUB(0x9a580);
}

// 0x9a5d0
void __cdecl ArcherRule::OnRegeneration(::ChangedProperty *)
{
    LIFT_STUB(0x9a5d0);
}

// 0x9a600
void __cdecl ArcherRule::OnCombatModeChanged(bool, ::ChangedProperty *)
{
    LIFT_STUB(0x9a600);
}

// 0x9a640
void __cdecl ArcherRule::OnEnterWorld(::ChangedProperty *)
{
    LIFT_STUB(0x9a640);
}

// 0x9a670
void __cdecl SpearMasterRule::OnAttackResultEvent(::GameObject *, ::SkillResult, short)
{
    LIFT_STUB(0x9a670);
}

// 0x9a6c0
void __cdecl SpearMasterRule::OnAttackedResultEvent(::GameObject *, ::SkillResult, bool)
{
    LIFT_STUB(0x9a6c0);
}

// 0x9a710
void __cdecl SpearMasterRule::OnCombatModeChanged(bool, ::ChangedProperty *)
{
    LIFT_STUB(0x9a710);
}

// 0x9a750
void __cdecl ThundererRule::OnAttackResultEvent(::GameObject *, ::SkillResult, short)
{
    LIFT_STUB(0x9a750);
}

// 0x9a7a0
void __cdecl ThundererRule::OnAttackedResultEvent(::GameObject *, ::SkillResult, bool)
{
    LIFT_STUB(0x9a7a0);
}

// 0x9a7f0
void __cdecl ThundererRule::OnCombatModeChanged(bool, ::ChangedProperty *)
{
    LIFT_STUB(0x9a7f0);
}

// 0x9a830
::CreatureJobRule * __cdecl CreatureJobRuleFactory::CreateCreatureJobRule(char)
{
    LIFT_STUB(0x9a830);
}

// 0x9ac60
char __cdecl CreatureJobRuleFactory::GetDefaultStance(char)
{
    LIFT_STUB(0x9ac60);
}
