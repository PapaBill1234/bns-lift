// reaction.h: reaction.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class AcquireFieldItemReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x4601b0
};

class ActResumeReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x461840
};

class ActivateTeleportReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x461ae0
};

class AddZoneScore
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x462a40
};

class CopyNpcHateReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x45e150
};

class DamageReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x459360
};

class DeactivateTeleportReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x461ca0
};

class DecomposeSummoned
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x462c30
};

class DespawnNpcGroupsReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x45ccd0
};

class DespawnNpcIndexReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x45cae0
};

class DespawnNpcReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x45c980
};

class DiffFactionReputationReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x45b8d0
};

class DiffNpcHateReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x45dd60
};

class DiffNpcNumberReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x460760
};

class DiffPartyNumberReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x460980
};

class DispelBuffReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x459e40
};

class DispelByAttrReaction
{
private:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x45a1a0
};

class DispelByTypeReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x45a080
};

class DispelDebuffReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x459f60
};

class DropNpcWeaponReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x460410
};

class ExpandInventoryFirstReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x461940
};

class HealMaxReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x459870
};

class HealReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x4596e0
};

class InOutDetectStartReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x458f20
};

class InOutDetectStopReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x4590f0
};

class InvokeEffectReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x459a00
};

class KillReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x459520
};

class NpcFireSpecialReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x45fb50
};

class NpcTalkFinishReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x45fa60
};

class PatternStartReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x4629d0
};

class PatternSuccessReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x462a00
};

class PlayCinematicReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x461550
};

class PlayIndexedSocialReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x4610c0
};

class PlaySocialReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x460e60
};

class PlaySurroundSocialReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x461340
};

class ReactionFactory
{
private:
    void __cdecl clear(void);  // 0x462d80
public:
    bool __cdecl Initialize(void);  // 0x462e00
    ::Reaction * __cdecl CreateReaction(short) const;  // 0x463ed0
};

class ReferenceNpcHateEndReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x45e550
};

class ReferenceNpcHateStartReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x45e350
};

class RemoveFieldItemReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x4602f0
};

class RequestClanHelpReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x4604e0
};

class ResetNpcAllHateReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x45e060
};

class ResetNpcHateReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x45def0
};

class ResetStageReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x461e60
private:
    bool __cdecl DoDespawnNpcGroup(::Data::NpcResetStageRecordPtr const &, ::ScriptEvent const *) const;  // 0x462210
    bool __cdecl DoSpawnNpcGroup(::Data::NpcResetStageRecordPtr const &, ::ScriptEvent const *) const;  // 0x4622e0
    bool __cdecl DoDespawnMyParty(::ScriptParam &, ::ScriptEvent const *) const;  // 0x462400
    bool __cdecl DoSpawnMyParty(::ScriptParam &, ::ScriptEvent const *) const;  // 0x4624e0
    bool __cdecl DoEnvOperation(::Data::NpcResetStageRecordPtr const &, ::ScriptEvent const *) const;  // 0x462630
};

class ResetZoneObjectReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x4592b0
};

class ResetZoneTimerReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x458ec0
};

class SetEnvEnableReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x45eba0
};

class SetEnvEnableToggleIntervalReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x45ed60
};

class SetEnvInitEnableReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x45ec80
};

class SetEnvStateReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x45eac0
};

class SetNpcActReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x45f3f0
};

class SetNpcAttackableReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x45e790
};

class SetNpcBrainReaction
{
private:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x45f5d0
};

class SetNpcCombatModeReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x45fce0
};

class SetNpcFollowReaction
{
private:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x45f830
};

class SetNpcHateOnReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x45e870
};

class SetNpcIndexedActReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x45f4d0
};

class SetNpcInteractiveReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x45e960
};

class SetNpcNumberReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x4606a0
};

class SetNpcScriptReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x45e6b0
};

class SetPartyNumberReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x460860
};

class SetPartyObjectReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x460ad0
};

class SetPublicRaidEventReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x462790
};

class SetUndyingReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x460cd0
};

class SetZoneObjectReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x459110
};

class SetZoneTimerReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x458e50
};

class SpawnFieldItemReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x45fec0
};

class SpawnNpcGroupsReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x45cea0
};

class SpawnNpcIndexReaction
{
private:
    static void __cdecl spawn(::NpcSpawn *, unsigned __int64 const *, int, char const *, int, short, short, bool, short, ::NpcSpawnParam &, ::ScriptParam const &, ::Creature *);  // 0x45ba40
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x45bcd0
};

class SpawnNpcReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x45c2c0
private:
    void __cdecl spawn(::NpcSpawn *, unsigned __int64 const *, int, short, short, bool, short, ::NpcSpawnParam &, ::ScriptParam const &, ::Creature *) const;  // 0x45c6e0
};

class SpawnRandomNpcGroupReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x45da50
};

class SpawnRandomNpcReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x45d190
};

class TransitNpcBerserkReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x45f220
};

class TransitNpcCombatIndexReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x45f030
};

class TransitNpcCombatReaction
{
public:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x45ee80
};

class WarpPartyReaction
{
private:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x45ab60
};

class WarpReaction
{
private:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x45a470
};

class WarpToReentranceReaction
{
private:
    virtual bool __cdecl Do(::Data::ScriptReaction const *, ::ScriptEvent const *) const;  // 0x45b360
};

void __cdecl GetSpawnPos(::Creature &, short, short, bool, ::vector16 &);  // 0x457d50
unsigned __int64 __cdecl GetAttackTargetId(::ScriptParam const &);  // 0x458600
