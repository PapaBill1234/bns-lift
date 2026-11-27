// skillaction_cpp_2.cpp: skillaction.cpp part 2 (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "skillaction.h"
#include "creature.h"
#include "gameobject.h"
#include "LiftStub.h"

// 0x4a6270
void __cdecl SkillAction::initializeGlobalRecycleTime2(void)
{
    LIFT_STUB(0x4a6270);
}

// 0x4a62f0
void __cdecl SkillAction::initializeDuelBotGlobalRecycleTime2(void)
{
    LIFT_STUB(0x4a62f0);
}

// 0x4a6370
bool __cdecl SkillAction::checkDuelBotRecycleTime(::Creature *)
{
    LIFT_STUB(0x4a6370);
}

// 0x4a6550
__int64 __cdecl SkillAction::getConsumePoint(::Data::SkillPointTypeType, __int64, __int64, __int64, __int64)
{
    LIFT_STUB(0x4a6550);
}

// 0x4a65f0
void __cdecl SkillAction::consumePoint(void)
{
    LIFT_STUB(0x4a65f0);
}

// 0x4a6930
void __cdecl SkillAction::recoverPoint(void)
{
    LIFT_STUB(0x4a6930);
}

// 0x4a6a80
void __cdecl SkillAction::executeWeaponGemEffect(::Creature *, ::SkillResult, bool)
{
    LIFT_STUB(0x4a6a80);
}

// 0x4a6bb0
bool __cdecl SkillAction::calcChangeNpcYaw(short &, char &)
{
    LIFT_STUB(0x4a6bb0);
}

// 0x4a6e90
void __cdecl SkillAction::changeNpcYaw(void)
{
    LIFT_STUB(0x4a6e90);
}

// 0x4a6f60
void __cdecl SkillAction::onExecute(char, ::SkillResult &, ::Creature *, bool)
{
    LIFT_STUB(0x4a6f60);
}

// 0x4a74d0
bool __cdecl SkillAction::checkQuestEvent(::GameObject *)
{
    LIFT_STUB(0x4a74d0);
}

// 0x4a7670
void __cdecl SkillAction::transferQuestEvent(::GameObject *)
{
    LIFT_STUB(0x4a7670);
}

// 0x4a7890
bool __cdecl SkillAction::checkDirection(::Data::SkillDirType, short, ::vector16, ::vector16) const
{
    LIFT_STUB(0x4a7890);
}

// 0x4a7bc0
bool __cdecl SkillAction::isValidTarget(::Creature *)
{
    LIFT_STUB(0x4a7bc0);
}

// 0x4a7c40
bool __cdecl SkillAction::canExecDash(::vector16)
{
    LIFT_STUB(0x4a7c40);
}

// 0x4a7d10
char __cdecl SkillAction::getGatherType(char, bool &)
{
    LIFT_STUB(0x4a7d10);
}

// 0x4a7e20
bool __cdecl SkillAction::getCasterEffects(char, unsigned __int64 *&, char &)
{
    LIFT_STUB(0x4a7e20);
}

// 0x4a7f80
short __cdecl SkillAction::getTargetAngle(char)
{
    LIFT_STUB(0x4a7f80);
}

// 0x4a7ff0
bool __cdecl SkillAction::isExistInvokeEffect(char)
{
    LIFT_STUB(0x4a7ff0);
}

// 0x4a80c0
void __cdecl SkillAction::calcCheckPosition(::Creature *, ::vector16 &)
{
    LIFT_STUB(0x4a80c0);
}

// 0x4a8210
bool __cdecl SkillAction::calcDashPosition(::Data::SkillDashAttribute3RecordPtr, ::Creature *, ::vector16 &, short &)
{
    LIFT_STUB(0x4a8210);
}

// 0x4a87f0
bool __cdecl SkillAction::execDash(::Creature *, ::Creature *, ::vector16, short, long)
{
    LIFT_STUB(0x4a87f0);
}

// 0x4a8970
void __cdecl SkillAction::gatherTargetByPosition(::vector16 &, short, ::Data::SkillDirType, unsigned __int64 *const, char *, bool, int)
{
    LIFT_STUB(0x4a8970);
}

// 0x4a9020
bool __cdecl SkillAction::isLaserScope(::vector16, ::GameObject *, short, short, short, short, short, short, short, bool, bool, __int64 &)
{
    LIFT_STUB(0x4a9020);
}

// 0x4a94f0
void __cdecl SkillAction::gatherTargetByLaser(::vector16, short, unsigned __int64 *const, char *, int)
{
    LIFT_STUB(0x4a94f0);
}

// 0x4a9be0
void __cdecl SkillAction::gatherTargetByShiftingLaser(::vector16, short, unsigned __int64 *const, char *, int)
{
    LIFT_STUB(0x4a9be0);
}

// 0x4aa1c0
bool __cdecl SkillAction::calculateRange(short &, short &, ::GameObject *)
{
    LIFT_STUB(0x4aa1c0);
}

// 0x4aa260
bool __cdecl SkillAction::applySkillFormula(void)
{
    LIFT_STUB(0x4aa260);
}

// 0x4aa360
::Pointer2< ::Creature> __cdecl SkillAction::getCreaturePtr(unsigned __int64)
{
    LIFT_STUB(0x4aa360);
}

// 0x4aa3f0
void __cdecl SkillAction::execBounce(::Creature *)
{
    LIFT_STUB(0x4aa3f0);
}

// 0x4aa4c0
void __cdecl SkillAction::execTriggerSkill(void)
{
    LIFT_STUB(0x4aa4c0);
}

// 0x4aa5f0
bool __cdecl SkillAction::checkSkillResultValue(unsigned short, ::Data::SkillSkillResultType, ::SkillResult *)
{
    LIFT_STUB(0x4aa5f0);
}

// 0x4aa6a0
bool __cdecl SkillAction::applySkillResultRule(char, ::SkillResult &)
{
    LIFT_STUB(0x4aa6a0);
}

// 0x4aa930
bool __cdecl SkillAction::applySkillAttributeRule(::Creature *, ::SkillResult &, bool)
{
    LIFT_STUB(0x4aa930);
}

// 0x4aaa60
bool __cdecl SkillAction::calcFireMiss(void)
{
    LIFT_STUB(0x4aaa60);
}

// 0x4aab00
::SkillResult __cdecl SkillAction::calcSkillResult(::Creature *, bool)
{
    LIFT_STUB(0x4aab00);
}

// 0x4aac80
long const __cdecl SkillAction::calcCastDuration(long) const
{
    LIFT_STUB(0x4aac80);
}

// 0x4aae20
short __cdecl SkillAction::calcImmune(::Creature *, bool)
{
    LIFT_STUB(0x4aae20);
}

// 0x4aaf10
short __cdecl SkillAction::calcDodge(::Creature *, bool, short &)
{
    LIFT_STUB(0x4aaf10);
}

// 0x4ab350
short __cdecl SkillAction::calcParry(::Creature *, bool, short)
{
    LIFT_STUB(0x4ab350);
}

// 0x4ab5e0
short __cdecl SkillAction::calcCriticalHit(::Creature *, bool)
{
    LIFT_STUB(0x4ab5e0);
}

// 0x4aba70
bool __cdecl SkillAction::getDurationFromSpeed2(short, long &)
{
    LIFT_STUB(0x4aba70);
}

// 0x4abaf0
bool __cdecl SkillAction::getDurationFromSpeed(::vector16, short, long &)
{
    LIFT_STUB(0x4abaf0);
}

// 0x4abe80
void __cdecl SkillAction::setCastingFlag(bool)
{
    LIFT_STUB(0x4abe80);
}

// 0x4abf30
bool __cdecl SkillAction::addGatherTarget(unsigned __int64, unsigned __int64 *const, char *, int)
{
    LIFT_STUB(0x4abf30);
}

// 0x4abf80
void __cdecl SkillAction::resetTimer(void)
{
    LIFT_STUB(0x4abf80);
}

// 0x4abfb0
bool __cdecl SkillAction::calcSkillModifyWeight(char, ::ApplySkillModifyInfo *, ::ApplySkillModifyInfo &)
{
    LIFT_STUB(0x4abfb0);
}

// 0x4ac080
unsigned __int64 const __cdecl SkillAction::getSkillInstanceIdForGameLog(void)
{
    LIFT_STUB(0x4ac080);
}

// 0x4ac0c0
__cdecl CasterSkillAction::CasterSkillAction(void)
{
    LIFT_STUB(0x4ac0c0);
}

// 0x4ac100
bool __cdecl CasterSkillAction::SucceedTargetInfo(__int64, int, unsigned __int64 &, ::vector16 &, unsigned __int64 *const, char &)
{
    LIFT_STUB(0x4ac100);
}

// 0x4ac160
void __cdecl CasterSkillAction::modifyTargetPositionByOffset(char)
{
    LIFT_STUB(0x4ac160);
}

// 0x4ac3b0
void __cdecl CasterSkillAction::stateReturn(void)
{
    LIFT_STUB(0x4ac3b0);
}

// 0x4ac3c0
void __cdecl CasterSkillAction::gatherTarget(char)
{
    LIFT_STUB(0x4ac3c0);
}

// 0x4ac7e0
bool __cdecl CasterSkillAction::invokeExecute(char, unsigned short &)
{
    LIFT_STUB(0x4ac7e0);
}

// 0x4aca00
__cdecl TargetSkillAction::TargetSkillAction(void)
{
    LIFT_STUB(0x4aca00);
}

// 0x4aca40
bool __cdecl TargetSkillAction::isCastable(void)
{
    LIFT_STUB(0x4aca40);
}

// 0x4acb50
bool __cdecl TargetSkillAction::isFlyable(char)
{
    LIFT_STUB(0x4acb50);
}

// 0x4acc40
bool __cdecl TargetSkillAction::SucceedTargetInfo(__int64, int, unsigned __int64 &, ::vector16 &, unsigned __int64 *const, char &)
{
    LIFT_STUB(0x4acc40);
}

// 0x4acc90
void __cdecl TargetSkillAction::gatherTarget(char)
{
    LIFT_STUB(0x4acc90);
}

// 0x4ad150
bool __cdecl TargetSkillAction::invokeExecute(char, unsigned short &)
{
    LIFT_STUB(0x4ad150);
}

// 0x4ad470
bool __cdecl TargetSkillAction::isExecutable(char)
{
    LIFT_STUB(0x4ad470);
}

// 0x4ad580
__cdecl GroundRadiusSkillAction::GroundRadiusSkillAction(void)
{
    LIFT_STUB(0x4ad580);
}

// 0x4ad5e0
bool __cdecl GroundRadiusSkillAction::calcGroundPos(void)
{
    LIFT_STUB(0x4ad5e0);
}

// 0x4ad990
bool __cdecl GroundRadiusSkillAction::prepareAction(void)
{
    LIFT_STUB(0x4ad990);
}

// 0x4adc20
bool __cdecl GroundRadiusSkillAction::SucceedTargetInfo(__int64, int, unsigned __int64 &, ::vector16 &, unsigned __int64 *const, char &)
{
    LIFT_STUB(0x4adc20);
}

// 0x4adc80
void __cdecl GroundRadiusSkillAction::gatherTarget(char)
{
    LIFT_STUB(0x4adc80);
}

// 0x4ae240
void __cdecl GroundRadiusSkillAction::spawnNpc(char)
{
    LIFT_STUB(0x4ae240);
}

// 0x4ae500
bool __cdecl GroundRadiusSkillAction::invokeExecute(char, unsigned short &)
{
    LIFT_STUB(0x4ae500);
}

// 0x4ae710
bool __cdecl GroundRadiusSkillAction::isCastable(void)
{
    LIFT_STUB(0x4ae710);
}

// 0x4aed50
bool __cdecl GroundRadiusSkillAction::isFlyable(char)
{
    LIFT_STUB(0x4aed50);
}

// 0x4aef80
__cdecl ChainSkillAction::ChainSkillAction(void)
{
    LIFT_STUB(0x4aef80);
}

// 0x4af000
bool __cdecl ChainSkillAction::isCastable(void)
{
    LIFT_STUB(0x4af000);
}

// 0x4af0b0
bool __cdecl ChainSkillAction::isFlyable(char)
{
    LIFT_STUB(0x4af0b0);
}

// 0x4af1d0
bool __cdecl ChainSkillAction::isExecutable(char)
{
    LIFT_STUB(0x4af1d0);
}

// 0x4af2f0
bool __cdecl ChainSkillAction::SucceedTargetInfo(__int64, int, unsigned __int64 &, ::vector16 &, unsigned __int64 *const, char &)
{
    LIFT_STUB(0x4af2f0);
}

// 0x4af340
void __cdecl ChainSkillAction::gatherTarget(char)
{
    LIFT_STUB(0x4af340);
}

// 0x4af430
bool __cdecl ChainSkillAction::getDurationFromSpeed2(short, long &)
{
    LIFT_STUB(0x4af430);
}

// 0x4af4d0
bool __cdecl ChainSkillAction::invokeExecute(char, unsigned short &)
{
    LIFT_STUB(0x4af4d0);
}

// 0x4af850
bool __cdecl ChainSkillAction::getTargetPosition(unsigned __int64, ::vector16 &)
{
    LIFT_STUB(0x4af850);
}

// 0x4af990
bool __cdecl ChainSkillAction::gatherTargetByChain(void)
{
    LIFT_STUB(0x4af990);
}

// 0x4aff30
bool __cdecl NoneTargetSkillAction::isCastable(void)
{
    LIFT_STUB(0x4aff30);
}

// 0x4b0700
bool __cdecl NoneTargetSkillAction::isFlyable(char)
{
    LIFT_STUB(0x4b0700);
}

// 0x4b09d0
bool __cdecl NoneTargetSkillAction::isExecutable(char)
{
    LIFT_STUB(0x4b09d0);
}

// 0x4b09e0
bool __cdecl NoneTargetSkillAction::SucceedTargetInfo(__int64, int, unsigned __int64 &, ::vector16 &, unsigned __int64 *const, char &)
{
    LIFT_STUB(0x4b09e0);
}

// 0x4b0a00
bool __cdecl NoneTargetSkillAction::invokeExecute(char, unsigned short &)
{
    LIFT_STUB(0x4b0a00);
}

// 0x4b0ad0
bool __cdecl SummonSkillAction::prepareAction(void)
{
    LIFT_STUB(0x4b0ad0);
}

// 0x4b1070
bool __cdecl SummonSkillAction::isCastable(void)
{
    LIFT_STUB(0x4b1070);
}

// 0x4b1220
void __cdecl SummonSkillAction::execSummon(void)
{
    LIFT_STUB(0x4b1220);
}

// 0x4b1460
bool __cdecl SummonSkillAction::invokeExecute(char, unsigned short &)
{
    LIFT_STUB(0x4b1460);
}

// 0x4b1480
bool __cdecl MakeCampfireSkillAction::isCastable(void)
{
    LIFT_STUB(0x4b1480);
}

// 0x4b15d0
void __cdecl MakeCampfireSkillAction::makeCampfire(void)
{
    LIFT_STUB(0x4b15d0);
}

// 0x4b1660
bool __cdecl MakeCampfireSkillAction::canMakeCampfire(void)
{
    LIFT_STUB(0x4b1660);
}

// 0x4b18f0
bool __cdecl MakeCampfireSkillAction::invokeExecute(char, unsigned short &)
{
    LIFT_STUB(0x4b18f0);
}

// 0x4b1920
bool __cdecl SuccessionSkillAction::prepareAction(void)
{
    LIFT_STUB(0x4b1920);
}

// 0x4b1d10
bool __cdecl SuccessionSkillAction::isCastable(void)
{
    LIFT_STUB(0x4b1d10);
}

// 0x4b2330
bool __cdecl SuccessionSkillAction::isFlyable(char)
{
    LIFT_STUB(0x4b2330);
}

// 0x4b24c0
bool __cdecl SuccessionSkillAction::isExecutable(char)
{
    LIFT_STUB(0x4b24c0);
}

// 0x4b2570
bool __cdecl SuccessionSkillAction::invokeExecute(char, unsigned short &)
{
    LIFT_STUB(0x4b2570);
}

// 0x4b2710
bool __cdecl DuelTagSkillAction::isCastable(void)
{
    LIFT_STUB(0x4b2710);
}

// 0x4b2d40
bool __cdecl DuelTagSkillAction::isFlyable(char)
{
    LIFT_STUB(0x4b2d40);
}

// 0x4b3020
bool __cdecl DuelTagSkillAction::isExecutable(char)
{
    LIFT_STUB(0x4b3020);
}

// 0x4b3310
bool __cdecl DuelTagSkillAction::invokeExecute(char, unsigned short &)
{
    LIFT_STUB(0x4b3310);
}

// 0x4b3490
bool __cdecl DuelInterferenceSkillAction::isCastable(void)
{
    LIFT_STUB(0x4b3490);
}

// 0x4b3ac0
bool __cdecl DuelInterferenceSkillAction::isFlyable(char)
{
    LIFT_STUB(0x4b3ac0);
}

// 0x4b3da0
bool __cdecl DuelInterferenceSkillAction::isExecutable(char)
{
    LIFT_STUB(0x4b3da0);
}

// 0x4b40a0
bool __cdecl DuelInterferenceSkillAction::invokeExecute(char, unsigned short &)
{
    LIFT_STUB(0x4b40a0);
}

// 0x4b4220
::SkillAction *const __cdecl SkillActionFactory::CreateSkillAction3(unsigned __int64) const
{
    LIFT_STUB(0x4b4220);
}
