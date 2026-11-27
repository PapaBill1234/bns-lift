// creaturejob.cpp: creaturejob.cpp (GameDaemon PDB, 2019 + PDB). Wave 0 stubs and lifted leaves. A stub is not a lift.
#include "creaturejob.h"
#include "creature.h"
#include "gameobject.h"
#include "Log.h"
#include "AlertSender.h"
#include "LiftStub.h"

namespace
{
// LIFT: view of the PDB base class CreatureJobRule (size 0x10). The skeleton rule classes have no base yet.
struct CreatureJobRuleView
{
    void *lift_vfptr;     // ❓ no PDB name: vfptr
    ::Creature *_caster;  // +8 (0x8)
};

// LIFT: view of Creature::Prop.State (Prop +0x30, State +0xD8, sp +0x60). Only the field that the lifted bodies read is declared.
struct CreatureView
{
    char lift_pad_0[0x168];  // ❓ no PDB name: Creature +0 to +0x167 are not declared here
    short sp;                // Prop.State.sp, +360 (0x168)
};
}

// LIFT: build helper, no PDB name. It reads CreatureJobRule::_caster through the view.
#define CASTER() (reinterpret_cast<CreatureJobRuleView const *>(this)->_caster)

// LIFT: build helper, no PDB name. Each rule body of the original has the same caster check.
// ❓ The original bodies have a /GS cookie (a local buffer in the original check?). This form has none.
#define CREATURE_JOB_CHECK_CASTER(line) \
    if (CASTER() == nullptr) \
    { \
        Log::Write(Log::LT_ERROR, L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\gamedaemon\\CreatureJob.cpp", line, \
                   L"== CRASH == [creature-job-rule], invalid caster"); \
        AlertSender::Write(L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\gamedaemon\\CreatureJob.cpp", line, \
                           L"== CRASH == [creature-job-rule], invalid caster"); \
    }

#pragma comment(linker, "/INCLUDE:?OnAttackResultEvent@BladeMasterRule@@UEAAXPEAVGameObject@@W4SkillResult@@F@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?CheckToChangeStance@BladeMasterRule@@UEAA_ND@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?OnAttackResultEvent@SwordMasterRule@@UEAAXPEAVGameObject@@W4SkillResult@@F@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?CheckToChangeStance@SwordMasterRule@@UEAA_ND@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?OnAttackResultEvent@KungFuFighterRule@@UEAAXPEAVGameObject@@W4SkillResult@@F@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?OnAttackedResultEvent@KungFuFighterRule@@UEAAXPEAVGameObject@@W4SkillResult@@_N@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?OnAttackResultEvent@ForceMasterRule@@UEAAXPEAVGameObject@@W4SkillResult@@F@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?OnAttackedResultEvent@ForceMasterRule@@UEAAXPEAVGameObject@@W4SkillResult@@_N@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?OnAttackResultEvent@ShooterRule@@UEAAXPEAVGameObject@@W4SkillResult@@F@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?OnAttackedResultEvent@ShooterRule@@UEAAXPEAVGameObject@@W4SkillResult@@_N@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?OnAttackResultEvent@DestroyerRule@@UEAAXPEAVGameObject@@W4SkillResult@@F@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?OnDamaged@DestroyerRule@@UEAAXPEAVGameObject@@_J@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?OnAttackedResultEvent@SummonerRule@@UEAAXPEAVGameObject@@W4SkillResult@@_N@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?OnAttackResultEvent@AssassinRule@@UEAAXPEAVGameObject@@W4SkillResult@@F@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?OnAttackResultEvent@WarriorRule@@UEAAXPEAVGameObject@@W4SkillResult@@F@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?OnAttackedResultEvent@WarriorRule@@UEAAXPEAVGameObject@@W4SkillResult@@_N@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?OnAttackResultEvent@ArcherRule@@UEAAXPEAVGameObject@@W4SkillResult@@F@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?OnAttackedResultEvent@ArcherRule@@UEAAXPEAVGameObject@@W4SkillResult@@_N@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?OnAttackResultEvent@SpearMasterRule@@UEAAXPEAVGameObject@@W4SkillResult@@F@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?OnAttackedResultEvent@SpearMasterRule@@UEAAXPEAVGameObject@@W4SkillResult@@_N@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?OnAttackResultEvent@ThundererRule@@UEAAXPEAVGameObject@@W4SkillResult@@F@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?OnAttackedResultEvent@ThundererRule@@UEAAXPEAVGameObject@@W4SkillResult@@_N@Z")  // LIFT: dead-strip keep (no live caller yet)

// 0x99560
void __cdecl BladeMasterRule::OnAttackResultEvent(::GameObject *defender, ::SkillResult skillResult, short consumeSp)
{
    CREATURE_JOB_CHECK_CASTER(37);
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
bool __cdecl BladeMasterRule::CheckToChangeStance(char stance)
{
    return stance != 7 || 0 < reinterpret_cast<CreatureView const *>(CASTER())->sp;
}

// 0x99790
void __cdecl SwordMasterRule::OnAttackResultEvent(::GameObject *defender, ::SkillResult skillResult, short consumeSp)
{
    CREATURE_JOB_CHECK_CASTER(164);
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
bool __cdecl SwordMasterRule::CheckToChangeStance(char stance)
{
    return stance != 22 || 0 < reinterpret_cast<CreatureView const *>(CASTER())->sp;
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
void __cdecl KungFuFighterRule::OnAttackResultEvent(::GameObject *defender, ::SkillResult skillResult, short consumeSp)
{
    CREATURE_JOB_CHECK_CASTER(358);
}

// 0x99c00
void __cdecl KungFuFighterRule::OnAttackedResultEvent(::GameObject *attacker, ::SkillResult skillResult, bool backstab)
{
    CREATURE_JOB_CHECK_CASTER(367);
}

// 0x99c50
void __cdecl KungFuFighterRule::OnCombatModeChanged(bool, ::ChangedProperty *)
{
    LIFT_STUB(0x99c50);
}

// 0x99c90
void __cdecl ForceMasterRule::OnAttackResultEvent(::GameObject *defender, ::SkillResult skillResult, short consumeSp)
{
    CREATURE_JOB_CHECK_CASTER(435);
}

// 0x99ce0
void __cdecl ForceMasterRule::OnAttackedResultEvent(::GameObject *attacker, ::SkillResult skillResult, bool backstab)
{
    CREATURE_JOB_CHECK_CASTER(444);
}

// 0x99d30
void __cdecl ShooterRule::OnAttackResultEvent(::GameObject *defender, ::SkillResult skillResult, short consumeSp)
{
    CREATURE_JOB_CHECK_CASTER(505);
}

// 0x99d80
void __cdecl ShooterRule::OnAttackedResultEvent(::GameObject *attacker, ::SkillResult skillResult, bool backstab)
{
    CREATURE_JOB_CHECK_CASTER(514);
}

// 0x99dd0
void __cdecl DestroyerRule::OnAttackResultEvent(::GameObject *defender, ::SkillResult skillResult, short consumeSp)
{
    CREATURE_JOB_CHECK_CASTER(565);
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
void __cdecl SummonerRule::OnAttackedResultEvent(::GameObject *attacker, ::SkillResult skillResult, bool backstab)
{
    CREATURE_JOB_CHECK_CASTER(744);
}

// 0x9a1f0
void __cdecl SummonerRule::OnCombatModeChanged(bool, ::ChangedProperty *)
{
    LIFT_STUB(0x9a1f0);
}

// 0x9a2b0
void __cdecl AssassinRule::OnAttackResultEvent(::GameObject *defender, ::SkillResult skillResult, short consumeSp)
{
    CREATURE_JOB_CHECK_CASTER(841);
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
void __cdecl WarriorRule::OnAttackResultEvent(::GameObject *defender, ::SkillResult skillResult, short consumeSp)
{
    CREATURE_JOB_CHECK_CASTER(958);
}

// 0x9a4a0
void __cdecl WarriorRule::OnAttackedResultEvent(::GameObject *attacker, ::SkillResult skillResult, bool backstab)
{
    CREATURE_JOB_CHECK_CASTER(967);
}

// 0x9a4f0
void __cdecl WarriorRule::OnCombatModeChanged(bool, ::ChangedProperty *)
{
    LIFT_STUB(0x9a4f0);
}

// 0x9a530
void __cdecl ArcherRule::OnAttackResultEvent(::GameObject *defender, ::SkillResult skillResult, short consumeSp)
{
    CREATURE_JOB_CHECK_CASTER(1025);
}

// 0x9a580
void __cdecl ArcherRule::OnAttackedResultEvent(::GameObject *attacker, ::SkillResult skillResult, bool backstab)
{
    CREATURE_JOB_CHECK_CASTER(1034);
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
void __cdecl SpearMasterRule::OnAttackResultEvent(::GameObject *defender, ::SkillResult skillResult, short consumeSp)
{
    CREATURE_JOB_CHECK_CASTER(1100);
}

// 0x9a6c0
void __cdecl SpearMasterRule::OnAttackedResultEvent(::GameObject *attacker, ::SkillResult skillResult, bool backstab)
{
    CREATURE_JOB_CHECK_CASTER(1109);
}

// 0x9a710
void __cdecl SpearMasterRule::OnCombatModeChanged(bool, ::ChangedProperty *)
{
    LIFT_STUB(0x9a710);
}

// 0x9a750
void __cdecl ThundererRule::OnAttackResultEvent(::GameObject *defender, ::SkillResult skillResult, short consumeSp)
{
    CREATURE_JOB_CHECK_CASTER(1175);
}

// 0x9a7a0
void __cdecl ThundererRule::OnAttackedResultEvent(::GameObject *attacker, ::SkillResult skillResult, bool backstab)
{
    CREATURE_JOB_CHECK_CASTER(1184);
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
