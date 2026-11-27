// reaction.cpp: reaction.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "reaction.h"
#include "creature.h"
#include "npcparty.h"
#include "npcspawn.h"
#include "LiftStub.h"

// 0x457d50
void __cdecl GetSpawnPos(::Creature &, short, short, bool, ::vector16 &)
{
    LIFT_STUB(0x457d50);
}

// 0x458600
unsigned __int64 __cdecl GetAttackTargetId(::ScriptParam const &)
{
    LIFT_STUB(0x458600);
}

// 0x458690
static bool IsTraceAdditionalInfoSubjectSpawnNpcReaction(const unsigned __int64*, const int)
{
    LIFT_STUB(0x458690);
}

// 0x458760
static void TraceSpawnNpcReaction(const Data::ScriptReaction*, const ScriptEvent*, NpcParty*, const ScriptParam*, const ScriptParam*, const unsigned __int64*, const int, const bool)
{
    LIFT_STUB(0x458760);
}

// 0x458e50
bool __cdecl SetZoneTimerReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x458e50);
}

// 0x458ec0
bool __cdecl ResetZoneTimerReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x458ec0);
}

// 0x458f20
bool __cdecl InOutDetectStartReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x458f20);
}

// 0x4590f0
bool __cdecl InOutDetectStopReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x4590f0);
}

// 0x459110
bool __cdecl SetZoneObjectReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x459110);
}

// 0x4592b0
bool __cdecl ResetZoneObjectReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x4592b0);
}

// 0x459360
bool __cdecl DamageReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x459360);
}

// 0x459520
bool __cdecl KillReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x459520);
}

// 0x4596e0
bool __cdecl HealReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x4596e0);
}

// 0x459870
bool __cdecl HealMaxReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x459870);
}

// 0x459a00
bool __cdecl InvokeEffectReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x459a00);
}

// 0x459e40
bool __cdecl DispelBuffReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x459e40);
}

// 0x459f60
bool __cdecl DispelDebuffReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x459f60);
}

// 0x45a080
bool __cdecl DispelByTypeReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x45a080);
}

// 0x45a1a0
bool __cdecl DispelByAttrReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x45a1a0);
}

// 0x45a330
static bool getRandomPosInArea(unsigned, unsigned, short*, short*, short*)
{
    LIFT_STUB(0x45a330);
}

// 0x45a470
bool __cdecl WarpReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x45a470);
}

// 0x45ab60
bool __cdecl WarpPartyReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x45ab60);
}

// 0x45b360
bool __cdecl WarpToReentranceReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x45b360);
}

// 0x45b8d0
bool __cdecl DiffFactionReputationReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x45b8d0);
}

// 0x45ba40
void __cdecl SpawnNpcIndexReaction::spawn(::NpcSpawn *, unsigned __int64 const *, int, char const *, int, short, short, bool, short, ::NpcSpawnParam &, ::ScriptParam const &, ::Creature *)
{
    LIFT_STUB(0x45ba40);
}

// 0x45bcd0
bool __cdecl SpawnNpcIndexReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x45bcd0);
}

// 0x45c2c0
bool __cdecl SpawnNpcReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x45c2c0);
}

// 0x45c6e0
void __cdecl SpawnNpcReaction::spawn(::NpcSpawn *, unsigned __int64 const *, int, short, short, bool, short, ::NpcSpawnParam &, ::ScriptParam const &, ::Creature *) const
{
    LIFT_STUB(0x45c6e0);
}

// 0x45c980
bool __cdecl DespawnNpcReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x45c980);
}

// 0x45cae0
bool __cdecl DespawnNpcIndexReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x45cae0);
}

// 0x45ccd0
bool __cdecl DespawnNpcGroupsReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x45ccd0);
}

// 0x45cea0
bool __cdecl SpawnNpcGroupsReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x45cea0);
}

// 0x45d190
bool __cdecl SpawnRandomNpcReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x45d190);
}

// 0x45da50
bool __cdecl SpawnRandomNpcGroupReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x45da50);
}

// 0x45dd60
bool __cdecl DiffNpcHateReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x45dd60);
}

// 0x45def0
bool __cdecl ResetNpcHateReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x45def0);
}

// 0x45e060
bool __cdecl ResetNpcAllHateReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x45e060);
}

// 0x45e150
bool __cdecl CopyNpcHateReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x45e150);
}

// 0x45e350
bool __cdecl ReferenceNpcHateStartReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x45e350);
}

// 0x45e550
bool __cdecl ReferenceNpcHateEndReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x45e550);
}

// 0x45e6b0
bool __cdecl SetNpcScriptReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x45e6b0);
}

// 0x45e790
bool __cdecl SetNpcAttackableReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x45e790);
}

// 0x45e870
bool __cdecl SetNpcHateOnReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x45e870);
}

// 0x45e960
bool __cdecl SetNpcInteractiveReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x45e960);
}

// 0x45eac0
bool __cdecl SetEnvStateReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x45eac0);
}

// 0x45eba0
bool __cdecl SetEnvEnableReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x45eba0);
}

// 0x45ec80
bool __cdecl SetEnvInitEnableReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x45ec80);
}

// 0x45ed60
bool __cdecl SetEnvEnableToggleIntervalReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x45ed60);
}

// 0x45ee80
bool __cdecl TransitNpcCombatReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x45ee80);
}

// 0x45f030
bool __cdecl TransitNpcCombatIndexReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x45f030);
}

// 0x45f220
bool __cdecl TransitNpcBerserkReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x45f220);
}

// 0x45f3f0
bool __cdecl SetNpcActReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x45f3f0);
}

// 0x45f4d0
bool __cdecl SetNpcIndexedActReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x45f4d0);
}

// 0x45f5d0
bool __cdecl SetNpcBrainReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x45f5d0);
}

// 0x45f830
bool __cdecl SetNpcFollowReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x45f830);
}

// 0x45fa60
bool __cdecl NpcTalkFinishReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x45fa60);
}

// 0x45fb50
bool __cdecl NpcFireSpecialReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x45fb50);
}

// 0x45fce0
bool __cdecl SetNpcCombatModeReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x45fce0);
}

// 0x45fec0
bool __cdecl SpawnFieldItemReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x45fec0);
}

// 0x4601b0
bool __cdecl AcquireFieldItemReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x4601b0);
}

// 0x4602f0
bool __cdecl RemoveFieldItemReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x4602f0);
}

// 0x460410
bool __cdecl DropNpcWeaponReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x460410);
}

// 0x4604e0
bool __cdecl RequestClanHelpReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x4604e0);
}

// 0x4606a0
bool __cdecl SetNpcNumberReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x4606a0);
}

// 0x460760
bool __cdecl DiffNpcNumberReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x460760);
}

// 0x460860
bool __cdecl SetPartyNumberReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x460860);
}

// 0x460980
bool __cdecl DiffPartyNumberReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x460980);
}

// 0x460ad0
bool __cdecl SetPartyObjectReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x460ad0);
}

// 0x460cd0
bool __cdecl SetUndyingReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x460cd0);
}

// 0x460e60
bool __cdecl PlaySocialReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x460e60);
}

// 0x4610c0
bool __cdecl PlayIndexedSocialReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x4610c0);
}

// 0x461340
bool __cdecl PlaySurroundSocialReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x461340);
}

// 0x461550
bool __cdecl PlayCinematicReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x461550);
}

// 0x461840
bool __cdecl ActResumeReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x461840);
}

// 0x461940
bool __cdecl ExpandInventoryFirstReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x461940);
}

// 0x461ae0
bool __cdecl ActivateTeleportReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x461ae0);
}

// 0x461ca0
bool __cdecl DeactivateTeleportReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x461ca0);
}

// 0x461e60
bool __cdecl ResetStageReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x461e60);
}

// 0x462210
bool __cdecl ResetStageReaction::DoDespawnNpcGroup(::Data::NpcResetStageRecordPtr const &, ::ScriptEvent const *) const
{
    LIFT_STUB(0x462210);
}

// 0x4622e0
bool __cdecl ResetStageReaction::DoSpawnNpcGroup(::Data::NpcResetStageRecordPtr const &, ::ScriptEvent const *) const
{
    LIFT_STUB(0x4622e0);
}

// 0x462400
bool __cdecl ResetStageReaction::DoDespawnMyParty(::ScriptParam &, ::ScriptEvent const *) const
{
    LIFT_STUB(0x462400);
}

// 0x4624e0
bool __cdecl ResetStageReaction::DoSpawnMyParty(::ScriptParam &, ::ScriptEvent const *) const
{
    LIFT_STUB(0x4624e0);
}

// 0x462630
bool __cdecl ResetStageReaction::DoEnvOperation(::Data::NpcResetStageRecordPtr const &, ::ScriptEvent const *) const
{
    LIFT_STUB(0x462630);
}

// 0x462790
bool __cdecl SetPublicRaidEventReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x462790);
}

// 0x4629d0
bool __cdecl PatternStartReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x4629d0);
}

// 0x462a00
bool __cdecl PatternSuccessReaction::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x462a00);
}

// 0x462a40
bool __cdecl AddZoneScore::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x462a40);
}

// 0x462c30
bool __cdecl DecomposeSummoned::Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const
{
    LIFT_STUB(0x462c30);
}

// 0x462d80
void __cdecl ReactionFactory::clear(void)
{
    LIFT_STUB(0x462d80);
}

// 0x462e00
bool __cdecl ReactionFactory::Initialize(void)
{
    LIFT_STUB(0x462e00);
}

// 0x463ed0
::Reaction * __cdecl ReactionFactory::CreateReaction(short) const
{
    LIFT_STUB(0x463ed0);
}
