// gamedebugcommand.h: gamedebugcommand.cpp, gamedebugcommand.h (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class AbandonChargeDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x28e100
};

class AchievementAddRegisterDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x28edc0
};

class AchievementResetAllDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x28ee70
};

class AchievementResetCompletedDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x28ee40
};

class AchievementSetRegisterDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x28ee00
};

class AcquireFieldItemDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x286a10
};

class AcquireFishDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x291260
public:
    __cdecl AcquireFishDebugTask(void);  // 0x351150
    bool __cdecl Initialize(::Zone *, ::Creature *, wchar_t const *, int, unsigned __int64);  // 0x351190
};

class AcquireItemDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x287a00
};

class AcquireJackpotBossFactionScoreDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x28c570
};

class ActivateGradeDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x28e920
};

class AttachHateViewerDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x28df00
};

class ChangeChannelDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x290ba0
};

class ChangeSummonedDebugTask
{
public:
    bool __cdecl Initialize(::Zone *const, ::Pc *const, char const *const);  // 0x287300
private:
    virtual void __cdecl start(void);  // 0x287410
};

class CombatDuelBotDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x2861a0
};

class CreateTeamDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x289c40
};

class DespawnDuelBotDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x286070
};

class DespawnNpcDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x285bc0
};

class DetachHateViewerDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x28e000
};

class DiffEnvHpDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x286700
};

class DiffGradeExpirationTimeDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x28eaa0
};

class DisposeBuffDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x287950
};

class DisposeItemDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x287c90
};

class ExpandInventoryDebugTask
{
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, wchar_t *, char);  // 0x287d80
};

class GameDebugTask
{
public:
    virtual __cdecl ~GameDebugTask(void);  // 0x283cb0
    bool __cdecl Initialize(unsigned __int64);  // 0x283cc0
    bool __cdecl Initialize(unsigned __int64, wchar_t const *);  // 0x283d40
    bool __cdecl Initialize(::Zone *, ::Creature *);  // 0x283e30
private:
    virtual void __cdecl TimerExpired(unsigned int, long);  // 0x283ed0
public:
    static ::Pointer2< ::Creature> __cdecl GetCreature(unsigned __int64);  // 0x284030
    static ::Pointer2< ::Creature> __cdecl GetCreature(wchar_t const *);  // 0x2842d0
    static ::Pointer2< ::Pc> __cdecl GetPc(unsigned __int64);  // 0x284440
    static ::Pointer2< ::Pc> __cdecl GetPc(wchar_t const *);  // 0x284530
    static ::Pointer2< ::Env> __cdecl GetEnv(unsigned __int64, wchar_t const *);  // 0x2846a0
    static ::Pointer2< ::Env> __cdecl GetEnv(unsigned __int64, unsigned __int64);  // 0x284830
    static bool __cdecl GetDataId(wchar_t const *, unsigned int *);  // 0x284960
protected:
    static bool __cdecl isHex(wchar_t const *);  // 0x2849c0
    static bool __cdecl getHexId(wchar_t const *, __int64 &);  // 0x284a40
    static bool __cdecl getDecId(wchar_t const *, __int64 &);  // 0x284b60
};

class GetBotScoreInfoDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x290810
};

class GetCubeIndexDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x28c9b0
public:
    __cdecl GetCubeIndexDebugTask(::Session *);  // 0x350d70
};

class GetZonPcCountDebugTask
{
public:
    __cdecl GetZonPcCountDebugTask(::Session const *, bool);  // 0x28efc0
private:
    virtual void __cdecl start(void);  // 0x28f0b0
};

class HealthyDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x28c740
};

class IgnoreMoveChannelCooltimeTask
{
private:
    virtual void __cdecl start(void);  // 0x28a110
};

class IgnoreRecycleTimeTask
{
private:
    virtual void __cdecl start(void);  // 0x28a090
};

class IgnoreSkillConsumePointTask
{
private:
    virtual void __cdecl start(void);  // 0x28a0d0
};

class InitializeRecycleTimeTask
{
private:
    virtual void __cdecl start(void);  // 0x289ff0
};

class InvokeEffectDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x28cc10
public:
    bool __cdecl Initialize(unsigned __int64, wchar_t const *, wchar_t const *, wchar_t const *);  // 0x350e50
};

class JoinFaction2DebugTask
{
private:
    virtual void __cdecl start(void);  // 0x28d1e0
};

class JoinFactionDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x28cf10
};

class Kill2DebugTask
{
private:
    virtual void __cdecl start(void);  // 0x284fb0
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, wchar_t const *);  // 0x285210
};

class KillDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x284c60
public:
    bool __cdecl Initialize(unsigned __int64, wchar_t const *);  // 0x284ec0
};

class KnockBackDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x28ca80
};

class LeaveFaction2DebugTask
{
private:
    virtual void __cdecl start(void);  // 0x28d3e0
};

class LeaveFactionDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x28d110
};

class MakeSummonedDebugTask
{
public:
    bool __cdecl Initialize(::Zone *const, ::Pc *const, char, int, wchar_t const *const);  // 0x286c50
private:
    virtual void __cdecl start(void);  // 0x286f90
public:
    __cdecl MakeSummonedDebugTask(void);  // 0x350cc0
};

class NcguardDetectBotDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x290a10
};

class NpcCombatDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x28d9e0
};

class NpcRelationDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x28d5b0
};

class QuestDebugTask
{
public:
    enum QuestDebugType {};
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, ::QuestDebugTask::QuestDebugType, wchar_t const *, char, __int64, char);  // 0x2875c0
private:
    virtual void __cdecl start(void);  // 0x2876b0
public:
    __cdecl QuestDebugTask(void);  // 0x350d30
};

class RandomStorePremiumDrawCountDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x28c880
};

class ReEnterZoneDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x289e60
};

class RecallPartyDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x288b10
};

class RechargeContentQuotaDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x28ef70
};

class RechargeVitalityDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x28e630
};

class ResetBuffDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x2879d0
};

class ResetMasteryLevelDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x28c2b0
};

class ResurrectDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x28c650
};

class ReturnTownDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x289b10
};

class SetAbilityDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x28aa20
};

class SetBattleRoyalFieldStateDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x28f250
};

class SetBotScoreDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x290470
};

class SetBotScoreIgnoreDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x290640
};

class SetBuilderRightDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x28dd60
};

class SetChattingAvailableDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x28de80
public:
    bool __cdecl Initialize(::Zone *, ::Creature *, bool);  // 0x3510d0
};

class SetClosestEndTimeDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x2910c0
};

class SetContentQuotaDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x28eea0
};

class SetContentsBanDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x290ad0
};

class SetDuelTeamDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x28b080
};

class SetEnvEnableDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x286880
};

class SetEnvEnableToggleIntervalDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x286950
};

class SetEnvHpDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x2867c0
};

class SetEnvStateDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x286650
};

class SetFactionScoreDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x28c4e0
};

class SetGradeLevelDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x28e870
};

class SetHeartCountDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x28c440
};

class SetInvincibleDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x28aae0
};

class SetInvisibleDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x28c5c0
};

class SetMasteryLevelDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x28c1e0
};

class SetMentoringFinishCountDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x291230
};

class SetNpcActDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x28dc50
};

class SetPcCafeCodeDebugTask
{
public:
    __cdecl SetPcCafeCodeDebugTask(::Session const *, bool);  // 0x28eaf0
private:
    virtual void __cdecl start(void);  // 0x28ebf0
};

class SetScriptDebugTask
{
public:
    enum ScriptDebugType {};
private:
    virtual void __cdecl start(void);  // 0x28ccf0
public:
    __cdecl SetScriptDebugTask(void);  // 0x351000
    bool __cdecl Initialize(unsigned __int64, ::SetScriptDebugTask::ScriptDebugType, unsigned __int64, unsigned int);  // 0x351040
};

class SetSeasonContentsCombatRecordDebugTask
{
public:
    bool __cdecl Initialize(unsigned __int64, wchar_t const *, char, int, int, int, int, int, int, int);  // 0x28b0a0
private:
    virtual void __cdecl start(void);  // 0x28b1c0
};

class SetSeasonContentsCombatRecordWithRankingDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x28b660
};

class SetSeasonContentsTimeAttackRecordDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x28bd40
};

class SetStateDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x28a150
    void __cdecl setLevel(char, ::ChangedProperty *);  // 0x28a7e0
    void __cdecl setAccountExp(__int64, ::ChangedProperty *);  // 0x28a8f0
};

class SetTendencyVictoryTendencyDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x287830
};

class SetTimeBasedPlayDurationDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x290fe0
};

class SetUserAdminDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x28e210
};

class SetVitalityDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x28e350
};

class SetVitalityRechargeStateDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x28e770
};

class ShowCombatmodeStateDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x28fdd0
    void __cdecl sendCombatmodeMessage(::Pc *, ::Pc *);  // 0x2900c0
};

class ShowNpcTargetPlayerDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x28f360
    void __cdecl sendNpcTargetMessage(unsigned __int64 *const, int, ::Pc *, ::Pc **const, int, ::Summoned **const, int);  // 0x28f830
};

class SpawnDuelBotDebugTask
{
public:
    bool __cdecl Initialize(unsigned __int64, wchar_t const *, wchar_t const *, char);  // 0x285ca0
private:
    virtual void __cdecl start(void);  // 0x285e20
};

class SpawnNpcDebugTask
{
public:
    bool __cdecl Initialize(unsigned __int64, wchar_t const *, wchar_t const *, char, char);  // 0x285310
    bool __cdecl Initialize(unsigned __int64, wchar_t const *, wchar_t const *, short, short, short, char, char);  // 0x285490
private:
    virtual void __cdecl start(void);  // 0x285630
};

class SpawnSummonedDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x286a90
};

class SpawnZoneNpcDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x285a70
};

class TransferFaction2DebugTask
{
private:
    virtual void __cdecl start(void);  // 0x28d2e0
};

class TransferFactionDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x28cff0
};

class UsePerfMonTask
{
private:
    virtual void __cdecl start(void);  // 0x28dd30
};

class WarpToAreaDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x289330
    void __cdecl warp(void);  // 0x2893e0
};

class WarpToCreatureDebugTask
{
public:
    __cdecl WarpToCreatureDebugTask(void);  // 0x2883e0
    bool __cdecl Initialize(::Zone *, ::Creature *, ::Creature *);  // 0x288480
    bool __cdecl Initialize(unsigned __int64, wchar_t const *, wchar_t const *);  // 0x288510
private:
    virtual void __cdecl start(void);  // 0x288680
    void __cdecl warp(void);  // 0x2886e0
    void __cdecl zoneTransition(void);  // 0x2887f0
};

class WarpToEnvDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x2897b0
    void __cdecl warp(void);  // 0x289990
};

class WarpToPcSpawnDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x289560
    void __cdecl warp(void);  // 0x289610
};

class WarpToPhaseMainZoneDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x288260
    void __cdecl warp(void);  // 0x2882d0
};

class WarpToPosDebugTask
{
public:
    __cdecl WarpToPosDebugTask(void);  // 0x283bc0
private:
    virtual void __cdecl start(void);  // 0x287e90
    void __cdecl warp(void);  // 0x287ec0
    void __cdecl zoneTransition(void);  // 0x287fd0
};

class WarpToRespawnDebugTask
{
private:
    virtual void __cdecl start(void);  // 0x288e20
    void __cdecl warp(void);  // 0x288ea0
    void __cdecl zoneTransition(void);  // 0x289060
};

bool __cdecl getEnvActionPos(::GeoZone const *, ::GeoEnvObj const *, ::vector16 &);  // 0x289860
