// bossskillaction_cpp.cpp: bossskillaction.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "bossskillaction.h"
#include "action.h"
#include "creature.h"
#include "geoworld.h"
#include "npc.h"
#include "skillaction.h"
#include "LiftStub.h"

// 0x5c050
bool __cdecl BossRushSkillAction::prepareAction(void)
{
    LIFT_STUB(0x5c050);
}

// 0x5c2a0
void __cdecl BossRushSkillAction::intervalAction(long)
{
    LIFT_STUB(0x5c2a0);
}

// 0x5c330
void __cdecl BossRushSkillAction::stateReturn(void)
{
    LIFT_STUB(0x5c330);
}

// 0x5c510
void __cdecl BossRushSkillAction::executeMove(long)
{
    LIFT_STUB(0x5c510);
}

// 0x5c770
bool __cdecl BossRushSkillAction::move(::vector16 const &, long)
{
    LIFT_STUB(0x5c770);
}

// 0x5ca10
bool __cdecl BossRushSkillAction::isSameCell(::vector16 const &, ::vector16 const &)
{
    LIFT_STUB(0x5ca10);
}

// 0x5cbe0
::vector16 __cdecl BossRushSkillAction::getPosInBoundary(::GeoZone const *, ::vector16 const &, ::vector16 const &)
{
    LIFT_STUB(0x5cbe0);
}

// 0x5cd00
bool __cdecl BossRushSkillAction::invokeExecute(char, unsigned short &)
{
    LIFT_STUB(0x5cd00);
}

// 0x5cf60
void __cdecl BossRushSkillAction::gatherTarget(char)
{
    LIFT_STUB(0x5cf60);
}

// 0x5d320
bool __cdecl BossRushSkillAction::invokeEffect(unsigned __int64, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x5d320);
}

// 0x5d3a0
bool __cdecl BossRepeaterSkillAction::checkTargetExceptCond(void)
{
    LIFT_STUB(0x5d3a0);
}

// 0x5d480
bool __cdecl BossRepeaterSkillAction::prepareAction(void)
{
    LIFT_STUB(0x5d480);
}

// 0x5d5c0
void __cdecl BossRepeaterSkillAction::stateReturn(void)
{
    LIFT_STUB(0x5d5c0);
}

// 0x5d7b0
unsigned __int64 __cdecl BossRepeaterSkillAction::getNextTarget(void)
{
    LIFT_STUB(0x5d7b0);
}

// 0x5d900
__cdecl BossRepeaterGroundSkillAction::BossRepeaterGroundSkillAction(bool, char, unsigned __int64)
{
    LIFT_STUB(0x5d900);
}

// 0x5d990
bool __cdecl BossRepeaterGroundSkillAction::checkTargetExceptCond(void)
{
    LIFT_STUB(0x5d990);
}

// 0x5da70
bool __cdecl BossRepeaterGroundSkillAction::prepareAction(void)
{
    LIFT_STUB(0x5da70);
}

// 0x5dbb0
void __cdecl BossRepeaterGroundSkillAction::stateFly(void)
{
    LIFT_STUB(0x5dbb0);
}

// 0x5dc30
void __cdecl BossRepeaterGroundSkillAction::stateReturn(void)
{
    LIFT_STUB(0x5dc30);
}

// 0x5de20
unsigned __int64 __cdecl BossRepeaterGroundSkillAction::getNextTarget(void)
{
    LIFT_STUB(0x5de20);
}

// 0x5dfa0
bool __cdecl BossMultigroundSkillAction::prepareAction(void)
{
    LIFT_STUB(0x5dfa0);
}

// 0x5dff0
bool __cdecl BossMultigroundSkillAction::setTargetPositions(void)
{
    LIFT_STUB(0x5dff0);
}

// 0x5e150
void __cdecl BossMultigroundSkillAction::broadcastSkill(::SkillFlowCode)
{
    LIFT_STUB(0x5e150);
}

// 0x5e170
void __cdecl BossMultigroundSkillAction::broadcastMultigroundSkill(::SkillFlowCode)
{
    LIFT_STUB(0x5e170);
}

// 0x5e4b0
bool __cdecl BossMultigroundSkillAction::invokeExecute(char, unsigned short &)
{
    LIFT_STUB(0x5e4b0);
}

// 0x5e630
void __cdecl BossMultigroundSkillAction::stateReturn(void)
{
    LIFT_STUB(0x5e630);
}

// 0x5e800
void __cdecl BossMultigroundSkillAction::gatherTarget(char)
{
    LIFT_STUB(0x5e800);
}

// 0x5ec80
bool __cdecl BossSimultaneousGroundSkillAction::prepareAction(void)
{
    LIFT_STUB(0x5ec80);
}

// 0x5ed90
void __cdecl BossSimultaneousGroundSkillAction::broadcastSkill(::SkillFlowCode)
{
    LIFT_STUB(0x5ed90);
}

// 0x5f110
void __cdecl BossSimultaneousCasterSkillAction::stateExecute(void)
{
    LIFT_STUB(0x5f110);
}

// 0x5f150
bool __cdecl BossSimultaneousCasterSkillAction::prepareAction(void)
{
    LIFT_STUB(0x5f150);
}

// 0x5f260
void __cdecl BossSimultaneousCasterSkillAction::broadcastSkill(::SkillFlowCode)
{
    LIFT_STUB(0x5f260);
}

// 0x5f580
void __cdecl BossSimultaneousCasterSkillAction::stateCast(void)
{
    LIFT_STUB(0x5f580);
}

// 0x5f5e0
void __cdecl BossSimultaneousCasterSkillAction::stateReturn(void)
{
    LIFT_STUB(0x5f5e0);
}

// 0x5f800
bool __cdecl BossSimultaneousCasterSkillAction::invokeExecute(char, unsigned short &)
{
    LIFT_STUB(0x5f800);
}

// 0x5f8f0
void __cdecl BossSimultaneousCasterSkillAction::gatherTarget(char)
{
    LIFT_STUB(0x5f8f0);
}

// 0x5fd20
bool __cdecl BossLinkLaserSkillAction::InitializeLinkLaser(::Data::CombatSequenceActionBossLinkLaserAttack const &, ::ScriptEvent const &)
{
    LIFT_STUB(0x5fd20);
}

// 0x60050
bool __cdecl BossLinkLaserSkillAction::prepareAction(void)
{
    LIFT_STUB(0x60050);
}

// 0x602d0
bool __cdecl BossLinkLaserSkillAction::invokeExecute(char, unsigned short &)
{
    LIFT_STUB(0x602d0);
}

// 0x60d10
void __cdecl BossLinkLaserSkillAction::stateExecute(void)
{
    LIFT_STUB(0x60d10);
}

// 0x60d50
void __cdecl BossLinkLaserSkillAction::stateReturn(void)
{
    LIFT_STUB(0x60d50);
}

// 0x60fa0
void __cdecl BossLinkLaserSkillAction::gatherTarget(char)
{
    LIFT_STUB(0x60fa0);
}

// 0x61120
void __cdecl BossLinkLaserSkillAction::gatherTargetByCube(unsigned __int64, unsigned __int64, unsigned __int64 *const, char *)
{
    LIFT_STUB(0x61120);
}

// 0x61c00
void __cdecl BossLinkLaserSkillAction::gatherTargetBounceAngle(::LinkLaserGatheredTargetStruct &)
{
    LIFT_STUB(0x61c00);
}

// 0x61f10
bool __cdecl BossLinkLaserSkillAction::executeLinkTerminate(::Data::CombatSequenceLinkLaserTerminateCondType)
{
    LIFT_STUB(0x61f10);
}

// 0x62180
void __cdecl BossLinkLaserSkillAction::broadcastSkill(::SkillFlowCode)
{
    LIFT_STUB(0x62180);
}

// 0x621b0
void __cdecl BossLinkLaserSkillAction::cancelAction(::Action::CancelReason, wchar_t const *, int)
{
    LIFT_STUB(0x621b0);
}

// 0x62200
short __cdecl BossLinkLaserSkillAction::getDashAngle(unsigned __int64)
{
    LIFT_STUB(0x62200);
}

// 0x62280
void __cdecl BossLinkLaserSkillAction::broadcastLinkLaserSkill(::SkillFlowCode)
{
    LIFT_STUB(0x62280);
}

// 0x625e0
::SkillAction * __cdecl BossSkillFactory::CreateBossRushSkillAction(::Npc &, unsigned __int64, ::vector16, short, unsigned __int64, unsigned __int64, bool)
{
    LIFT_STUB(0x625e0);
}

// 0x62850
::SkillAction * __cdecl BossSkillFactory::CreateBossRepeaterSkillAction(::Npc &, unsigned __int64, ::Creature *, bool, char)
{
    LIFT_STUB(0x62850);
}

// 0x62b60
::SkillAction * __cdecl BossSkillFactory::CreateBossSimultaneousGroundSkillAction(::Npc &, unsigned __int64, ::Creature *, long)
{
    LIFT_STUB(0x62b60);
}

// 0x62d50
::SkillAction * __cdecl BossSkillFactory::CreateBossSimultaneousCasterSkillAction(::Npc &, ::Creature *, unsigned __int64, long)
{
    LIFT_STUB(0x62d50);
}

// 0x62f10
::SkillAction * __cdecl BossSkillFactory::CreateBossLinkLaserSkillAction(::Npc &, ::Data::CombatSequenceActionBossLinkLaserAttack const &, ::ScriptEvent const &)
{
    LIFT_STUB(0x62f10);
}
