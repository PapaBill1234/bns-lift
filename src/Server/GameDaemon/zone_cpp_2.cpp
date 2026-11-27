// zone_cpp_2.cpp: zone.cpp part 2 (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "zone.h"
#include "droppedpouch.h"
#include "envobj.h"
#include "gameobject.h"
#include "npcdeadbody.h"
#include "pc.h"
#include "tagmatchduelmanager.h"
#include "zonebroadcast.h"
#include "LiftStub.h"

// 0x23b470
bool __cdecl Zone::AddEnvObjectBroadcast(int, short const *const, ::Env *)
{
    LIFT_STUB(0x23b470);
}

// 0x23b7a0
bool __cdecl Zone::AddRefinerEnvObjectBroadcast(::Refiner *)
{
    LIFT_STUB(0x23b7a0);
}

// 0x23ba10
bool __cdecl Zone::AddTakeRefinerRewardBroadcast(unsigned __int64, unsigned __int64, __int64, short)
{
    LIFT_STUB(0x23ba10);
}

// 0x23bc50
bool __cdecl Zone::AddPlayManipulateCinematicBroadcast(::vector16, unsigned __int64, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x23bc50);
}

// 0x23bea0
bool __cdecl Zone::AddGatherSourceBroadcast(::vector16, unsigned __int64, char)
{
    LIFT_STUB(0x23bea0);
}

// 0x23c0e0
bool __cdecl Zone::AddGatherActionBroadcast(::vector16, unsigned __int64, unsigned __int64, char)
{
    LIFT_STUB(0x23c0e0);
}

// 0x23c330
bool __cdecl Zone::AddLootActionBroadcast(::vector16, unsigned __int64, unsigned __int64, char)
{
    LIFT_STUB(0x23c330);
}

// 0x23c580
bool __cdecl Zone::AddRepairWithCampfireActionBroadcast(::vector16, unsigned __int64, unsigned __int64, short, int, char)
{
    LIFT_STUB(0x23c580);
}

// 0x23c7e0
bool __cdecl Zone::AddTeleportActionBroadcast(::vector16, unsigned __int64, char)
{
    LIFT_STUB(0x23c7e0);
}

// 0x23ca20
bool __cdecl Zone::AddPickupItemActionBroadcast(::vector16, unsigned __int64, unsigned __int64, char)
{
    LIFT_STUB(0x23ca20);
}

// 0x23cc70
bool __cdecl Zone::AddSocialBroadcast(::vector16, unsigned __int64, unsigned int, short, bool)
{
    LIFT_STUB(0x23cc70);
}

// 0x23cec0
bool __cdecl Zone::AddCancelSocialBroadcast(::vector16, unsigned __int64, unsigned int)
{
    LIFT_STUB(0x23cec0);
}

// 0x23d100
bool __cdecl Zone::AddSurroundSocialBroadcast(::vector16, unsigned int)
{
    LIFT_STUB(0x23d100);
}

// 0x23d330
bool __cdecl Zone::AddCreateFieldItemBroadcast(::vector16, unsigned __int64, unsigned __int64, unsigned __int64, int, char, short)
{
    LIFT_STUB(0x23d330);
}

// 0x23d5a0
bool __cdecl Zone::AddSpawnFieldItemBroadcast(::vector16, unsigned __int64, unsigned int, short, short, short, char, short, short, short, short)
{
    LIFT_STUB(0x23d5a0);
}

// 0x23d830
bool __cdecl Zone::AddDropFieldItemBroadcast(::vector16, unsigned __int64, unsigned __int64, unsigned int, short, short, short, char, short, short, char)
{
    LIFT_STUB(0x23d830);
}

// 0x23dac0
bool __cdecl Zone::AddCreateCampfireBroadcast(::vector16, unsigned __int64, unsigned int, unsigned __int64, short, short, short, short)
{
    LIFT_STUB(0x23dac0);
}

// 0x23dd40
bool __cdecl Zone::AddDestroyCampfireBroadcast(::vector16, unsigned __int64)
{
    LIFT_STUB(0x23dd40);
}

// 0x23df70
bool __cdecl Zone::AddPickupFieldItemBroadcast(::vector16, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x23df70);
}

// 0x23e1b0
bool __cdecl Zone::AddPickupFieldItemActionBroadcast(::vector16, unsigned __int64, unsigned __int64, ::ActionState)
{
    LIFT_STUB(0x23e1b0);
}

// 0x23e400
bool __cdecl Zone::AddPickupDeadBodyActionBroadcast(::vector16, unsigned __int64, unsigned __int64, ::ActionState)
{
    LIFT_STUB(0x23e400);
}

// 0x23e650
bool __cdecl Zone::AddPutdownFieldItemActionBroadcast(::vector16, unsigned __int64, unsigned __int64, ::vector16, ::ActionState)
{
    LIFT_STUB(0x23e650);
}

// 0x23e8c0
bool __cdecl Zone::AddRestorationActionBroadcast(::vector16, unsigned __int64, ::ActionState)
{
    LIFT_STUB(0x23e8c0);
}

// 0x23eb00
bool __cdecl Zone::AddHelpRestorationActionBroadcast(::vector16, unsigned __int64, unsigned __int64, ::ActionState)
{
    LIFT_STUB(0x23eb00);
}

// 0x23ed50
bool __cdecl Zone::AddDecomposeFieldItemBroadcast(::vector16, unsigned __int64, unsigned __int64, unsigned int, char)
{
    LIFT_STUB(0x23ed50);
}

// 0x23efa0
bool __cdecl Zone::AddKillBossNpcByGuildBroadcast(int, wchar_t const *)
{
    LIFT_STUB(0x23efa0);
}

// 0x23f1c0
bool __cdecl Zone::AddSpawnNpcDeadBodyBroadcast(::vector16, unsigned __int64, ::NpcDeadBody *)
{
    LIFT_STUB(0x23f1c0);
}

// 0x23f590
bool __cdecl Zone::AddDecomposeNpcDeadBodyBroadcast(::vector16, unsigned __int64)
{
    LIFT_STUB(0x23f590);
}

// 0x23f7c0
bool __cdecl Zone::AddNpcDeadBodyBroadcast(::vector16, ::NpcDeadBody *, char, char, __int64)
{
    LIFT_STUB(0x23f7c0);
}

// 0x23fb60
bool __cdecl Zone::AddSetDroppedPouchBroadcast(::vector16, short, ::DroppedPouch *)
{
    LIFT_STUB(0x23fb60);
}

// 0x23fde0
bool __cdecl Zone::AddDecomposeDroppedPouchBroadcast(::vector16, unsigned __int64)
{
    LIFT_STUB(0x23fde0);
}

// 0x240010
bool __cdecl Zone::AddDroppedPouchBroadcast(::vector16, ::DroppedPouch *)
{
    LIFT_STUB(0x240010);
}

// 0x240280
bool __cdecl Zone::AddLootObjectBroadcast(::vector16, unsigned __int64, short, char, char)
{
    LIFT_STUB(0x240280);
}

// 0x2404e0
bool __cdecl Zone::AddWarpBroadcast(::vector16, ::vector16, unsigned __int64, short, char, unsigned int, int)
{
    LIFT_STUB(0x2404e0);
}

// 0x240900
bool __cdecl Zone::AddAirDashBroadcast(::vector16, ::vector16, unsigned __int64, unsigned __int64, short)
{
    LIFT_STUB(0x240900);
}

// 0x240d60
bool __cdecl Zone::AddEscapeFromCaveActionBroadcast(::vector16, unsigned __int64, char)
{
    LIFT_STUB(0x240d60);
}

// 0x240fa0
bool __cdecl Zone::AddTakeFactionScoreBroadcast(::vector16, unsigned __int64, unsigned __int64, int, unsigned __int64 *const, int *const, int *const)
{
    LIFT_STUB(0x240fa0);
}

// 0x241330
bool __cdecl Zone::AddGiveFactionScoreToRefinerBroadcast(::vector16, unsigned __int64, unsigned __int64, int, ::ActionState)
{
    LIFT_STUB(0x241330);
}

// 0x241580
bool __cdecl Zone::AddZoneEventStepBroadCast(char)
{
    LIFT_STUB(0x241580);
}

// 0x2417b0
bool __cdecl Zone::AddZoneModeBroadcast(char, char, short, __int64)
{
    LIFT_STUB(0x2417b0);
}

// 0x241a60
bool __cdecl Zone::AddZoneScoreBroadcast(void)
{
    LIFT_STUB(0x241a60);
}

// 0x241ca0
bool __cdecl Zone::AddPartyBattleZoneScoreBroadcast(char)
{
    LIFT_STUB(0x241ca0);
}

// 0x241ef0
bool __cdecl Zone::AddZoneAttractionStateBroadcast(void)
{
    LIFT_STUB(0x241ef0);
}

// 0x242140
bool __cdecl Zone::AddZoneBossSpawnTimeBroadcast(__int64)
{
    LIFT_STUB(0x242140);
}

// 0x242370
bool __cdecl Zone::AddZoneBossCombatStartTimeBroadcast(__int64)
{
    LIFT_STUB(0x242370);
}

// 0x2425a0
bool __cdecl Zone::AddZoneBossHpBroadcast(char, unsigned __int64, __int64, __int64)
{
    LIFT_STUB(0x2425a0);
}

// 0x2427f0
bool __cdecl Zone::AddLastOccupiedEffectGuildBroadcast(__int64)
{
    LIFT_STUB(0x2427f0);
}

// 0x242a20
bool __cdecl Zone::AddJackpotFactionScoreBroadcast(int, int)
{
    LIFT_STUB(0x242a20);
}

// 0x242c40
bool __cdecl Zone::AddWarpToGuildMemberActionBroadcast(::vector16 &, unsigned __int64, char)
{
    LIFT_STUB(0x242c40);
}

// 0x242e80
bool __cdecl Zone::AddCallGuildMemberActionBroadcast(::vector16 &, unsigned __int64, char)
{
    LIFT_STUB(0x242e80);
}

// 0x2430c0
bool __cdecl Zone::AddWarpToGuildMeetingPlaceActionBroadcast(::vector16 &, unsigned __int64, char)
{
    LIFT_STUB(0x2430c0);
}

// 0x243300
bool __cdecl Zone::AddDuelEnterBroadcast(unsigned __int64)
{
    LIFT_STUB(0x243300);
}

// 0x243570
bool __cdecl Zone::AddDuelDelegateEmceeBroadcast(unsigned __int64)
{
    LIFT_STUB(0x243570);
}

// 0x2437e0
bool __cdecl Zone::AddDuelLeaveBroadcast(unsigned __int64, bool)
{
    LIFT_STUB(0x2437e0);
}

// 0x243a50
bool __cdecl Zone::AddDuelOrderChosePcListBroadcast(unsigned __int64 const *const, int)
{
    LIFT_STUB(0x243a50);
}

// 0x243df0
bool __cdecl Zone::AddDuelOrderResultListBroadcast(::TagMatchDuelMember const **const, int)
{
    LIFT_STUB(0x243df0);
}

// 0x2441b0
bool __cdecl Zone::AddDuelRoundReadiedPcListBroadcast(unsigned __int64 const *const, int)
{
    LIFT_STUB(0x2441b0);
}

// 0x244550
bool __cdecl Zone::AddDuelTagTokenOwnerBroadcast(char, unsigned __int64)
{
    LIFT_STUB(0x244550);
}

// 0x2447c0
bool __cdecl Zone::AddDuelGameStartBroadcast(unsigned __int64)
{
    LIFT_STUB(0x2447c0);
}

// 0x244a30
bool __cdecl Zone::AddDuelMemberDisplaySkillBroadcast(::Pc *const)
{
    LIFT_STUB(0x244a30);
}

// 0x244e70
bool __cdecl Zone::AddDuelRoundStartBroadcast(char)
{
    LIFT_STUB(0x244e70);
}

// 0x2450e0
bool __cdecl Zone::AddDuelInterferenceBonusPcListBroadcast(unsigned __int64 const *const, int)
{
    LIFT_STUB(0x2450e0);
}

// 0x245480
bool __cdecl Zone::AddDuelDeathBroadcast(unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x245480);
}

// 0x2456f0
bool __cdecl Zone::AddDuelWinByDecisionBroadcast(__int64, __int64)
{
    LIFT_STUB(0x2456f0);
}

// 0x245960
bool __cdecl Zone::AddDuelRoundFinishBroadcast(char, ::DuelRoundResult)
{
    LIFT_STUB(0x245960);
}

// 0x245bd0
bool __cdecl Zone::AddDuelGameFinishBroadcast(::DuelGameResult, bool)
{
    LIFT_STUB(0x245bd0);
}

// 0x245e50
bool __cdecl Zone::AddPartyBattleDelegateEmceeBroadcast(unsigned __int64)
{
    LIFT_STUB(0x245e50);
}

// 0x246080
bool __cdecl Zone::AddPartyBattleEnterBroadcast(unsigned __int64)
{
    LIFT_STUB(0x246080);
}

// 0x2462b0
bool __cdecl Zone::AddPartyBattleLeaveBroadcast(unsigned __int64)
{
    LIFT_STUB(0x2462b0);
}

// 0x2464e0
bool __cdecl Zone::AddPartyBattleReadyBroadcast(unsigned __int64)
{
    LIFT_STUB(0x2464e0);
}

// 0x246710
bool __cdecl Zone::AddPartyBattleStartBroadcast(__int64)
{
    LIFT_STUB(0x246710);
}

// 0x246940
bool __cdecl Zone::AddPartyBattleDeathBroadcast(unsigned __int64, unsigned __int64, short)
{
    LIFT_STUB(0x246940);
}

// 0x246b70
bool __cdecl Zone::AddPartyBattleContextBroadcast(__int64, __int64)
{
    LIFT_STUB(0x246b70);
}

// 0x246d90
bool __cdecl Zone::AddPartyBattleFinishBroadcast(::PartyBattleResult, bool)
{
    LIFT_STUB(0x246d90);
}

// 0x246fc0
bool __cdecl Zone::AddPartyBattleVoteBroadcast(__int64, char)
{
    LIFT_STUB(0x246fc0);
}

// 0x2471f0
bool __cdecl Zone::AddPartyBattleVoteFinishBroadcast(::PartyBattleVoteRecord)
{
    LIFT_STUB(0x2471f0);
}

// 0x2474f0
bool __cdecl Zone::AddSpawnSquadCreatureBroadcast(unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x2474f0);
}

// 0x247710
bool __cdecl Zone::AddBattleRoyalFieldStandByBroadcast(__int64)
{
    LIFT_STUB(0x247710);
}

// 0x247940
bool __cdecl Zone::AddBattleRoyalFieldStartBroadcast(void)
{
    LIFT_STUB(0x247940);
}

// 0x247b60
bool __cdecl Zone::AddBattleRoyalFieldFinishBroadcast(void)
{
    LIFT_STUB(0x247b60);
}

// 0x247d80
bool __cdecl Zone::AddBattleRoyalFieldEnterBroadcast(unsigned __int64, unsigned __int64, char)
{
    LIFT_STUB(0x247d80);
}

// 0x247fc0
bool __cdecl Zone::AddBattleRoyalFieldLeaveBroadcast(unsigned __int64)
{
    LIFT_STUB(0x247fc0);
}

// 0x2481f0
bool __cdecl Zone::AddBattleRoyalFieldDeathBroadcast(unsigned __int64, unsigned __int64, short)
{
    LIFT_STUB(0x2481f0);
}

// 0x248460
bool __cdecl Zone::AddBattleRoyalEventAreaInfoBroadcast(int, char, int, int)
{
    LIFT_STUB(0x248460);
}

// 0x2486a0
void __cdecl Zone::SendBattleRoyalFieldInZoneNotify(unsigned __int64, char)
{
    LIFT_STUB(0x2486a0);
}

// 0x248a20
void __cdecl Zone::addZoneEffectActionList(::GameObject const *, char, unsigned char, int, int, char *, short)
{
    LIFT_STUB(0x248a20);
}

// 0x248b30
void __cdecl Zone::addZoneActionList(int, int, char *, short, unsigned char)
{
    LIFT_STUB(0x248b30);
}

// 0x248d20
void __cdecl Zone::addZoneDuelbotActionList(char *, short, __int64)
{
    LIFT_STUB(0x248d20);
}

// 0x248f20
void __cdecl Zone::makeDuelbotActionPacket(::FragmentPacket *)
{
    LIFT_STUB(0x248f20);
}

// 0x249090
void __cdecl Zone::AddDuelBotSkillAction(unsigned __int64, __int64, unsigned int, char, char, char, short, short, char, ::SkillFlowCode, short, ::CancelTime, char const *, int, ...)
{
    LIFT_STUB(0x249090);
}

// 0x249400
bool __cdecl Zone::AddDuelBotSkillHitBroadcast(unsigned __int64, __int64, unsigned __int64, unsigned int, char, char, char, ::SkillFlowCode, ::SkillHitCode)
{
    LIFT_STUB(0x249400);
}

// 0x2496c0
bool __cdecl Zone::AddDuelBotEffectBroadcast(unsigned int, short, unsigned __int64, unsigned __int64, char, char, char const *, int, char *)
{
    LIFT_STUB(0x2496c0);
}

// 0x2499a0
bool __cdecl Zone::AddPublicRaidStandByBroadcast(__int64)
{
    LIFT_STUB(0x2499a0);
}

// 0x249bd0
bool __cdecl Zone::AddPublicRaidStartBroadcast(void)
{
    LIFT_STUB(0x249bd0);
}

// 0x249df0
bool __cdecl Zone::AddPublicRaidFinishBroadcast(void)
{
    LIFT_STUB(0x249df0);
}

// 0x24a010
bool __cdecl Zone::AddPublicRaidEnterBroadcast(unsigned __int64)
{
    LIFT_STUB(0x24a010);
}

// 0x24a240
bool __cdecl Zone::AddPublicRaidLeaveBroadcast(unsigned __int64)
{
    LIFT_STUB(0x24a240);
}

// 0x24a470
void __cdecl Zone::makeCubeActionPacket(::BroadcastPacketType)
{
    LIFT_STUB(0x24a470);
}

// 0x24a840
void __cdecl Zone::makeCubeChangedPropertyAction(::ZoneBroadcastCube *)
{
    LIFT_STUB(0x24a840);
}

// 0x24ae90
__int64 __cdecl Zone::GetTickTime(void)
{
    LIFT_STUB(0x24ae90);
}
