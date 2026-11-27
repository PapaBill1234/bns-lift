// gamebuildertask_cpp.cpp: gamebuildertask.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "gamebuildertask.h"
#include "creature.h"
#include "pc.h"
#include "zone.h"
#include "LiftStub.h"

// 0x27a3f0
::Pointer2< ::Creature> __cdecl GetCreature(unsigned __int64)
{
    LIFT_STUB(0x27a3f0);
}

// 0x27a5d0
::Pointer2< ::Pc> __cdecl GetPcFromName(wchar_t const *)
{
    LIFT_STUB(0x27a5d0);
}

// 0x27a620
bool __cdecl validateBuilder(wchar_t const *, ::Zone *, ::Creature *)
{
    LIFT_STUB(0x27a620);
}

// 0x27a6f0
bool __cdecl validateTarget(wchar_t const *, ::Zone *, ::Creature *, ::Creature *)
{
    LIFT_STUB(0x27a6f0);
}

// 0x27a800
void __cdecl AuditLogDIC(::Creature *, ::Creature *, wchar_t const *, int, wchar_t const *, ...)
{
    LIFT_STUB(0x27a800);
}

// 0x27ab10
bool __cdecl UndyingTask::Initialize(::Session const *, ::Zone *, ::Creature *, char)
{
    LIFT_STUB(0x27ab10);
}

// 0x27abb0
void __cdecl UndyingTask::start(void)
{
    LIFT_STUB(0x27abb0);
}

// 0x27ace0
bool __cdecl GmHideTask::Initialize(::Session const *, ::Zone *, ::Creature *)
{
    LIFT_STUB(0x27ace0);
}

// 0x27ad70
void __cdecl GmHideTask::start(void)
{
    LIFT_STUB(0x27ad70);
}

// 0x27aef0
bool __cdecl HealthyTask::Initialize(::Session const *, ::Zone *, ::Creature *)
{
    LIFT_STUB(0x27aef0);
}

// 0x27af80
void __cdecl HealthyTask::start(void)
{
    LIFT_STUB(0x27af80);
}

// 0x27b150
bool __cdecl ResurrectTask::Initialize(::Session const *, ::Zone *, ::Creature *, ::Creature *, ::ResurrectTask::CommandType)
{
    LIFT_STUB(0x27b150);
}

// 0x27b250
void __cdecl ResurrectTask::start(void)
{
    LIFT_STUB(0x27b250);
}

// 0x27b5d0
bool __cdecl KillMeTask::Initialize(::Session const *, ::Zone *, ::Creature *)
{
    LIFT_STUB(0x27b5d0);
}

// 0x27b660
void __cdecl KillMeTask::start(void)
{
    LIFT_STUB(0x27b660);
}

// 0x27b870
bool __cdecl DespawnNpcTask::Initialize(::Session const *, ::Zone *, ::Creature *, ::Creature *)
{
    LIFT_STUB(0x27b870);
}

// 0x27b9a0
void __cdecl DespawnNpcTask::start(void)
{
    LIFT_STUB(0x27b9a0);
}

// 0x27bc40
bool __cdecl SummonTask::Initialize(::Session const *, ::Zone *, ::Creature *, __int64, short)
{
    LIFT_STUB(0x27bc40);
}

// 0x27bcf0
void __cdecl SummonTask::start(void)
{
    LIFT_STUB(0x27bcf0);
}

// 0x27c010
bool __cdecl SetSkillTask::Initialize(::Session const *, ::Zone *, ::Creature *, ::Creature *, int)
{
    LIFT_STUB(0x27c010);
}

// 0x27c0e0
void __cdecl SetSkillTask::start(void)
{
    LIFT_STUB(0x27c0e0);
}

// 0x27c200
bool __cdecl DelSkillTask::Initialize(::Session const *, ::Zone *, ::Creature *, ::Creature *, int)
{
    LIFT_STUB(0x27c200);
}

// 0x27c2d0
void __cdecl DelSkillTask::start(void)
{
    LIFT_STUB(0x27c2d0);
}

// 0x27c3f0
bool __cdecl RemoveSkillDelay::Initialize(::Session const *, ::Zone *, ::Creature *)
{
    LIFT_STUB(0x27c3f0);
}

// 0x27c480
void __cdecl RemoveSkillDelay::start(void)
{
    LIFT_STUB(0x27c480);
}

// 0x27c560
bool __cdecl LocTask::Initialize(::Session const *, ::Zone *, ::Creature *)
{
    LIFT_STUB(0x27c560);
}

// 0x27c5f0
void __cdecl LocTask::start(void)
{
    LIFT_STUB(0x27c5f0);
}

// 0x27c6d0
bool __cdecl DispelAllTask::Initialize(::Session const *, ::Zone *, ::Creature *, ::Creature *)
{
    LIFT_STUB(0x27c6d0);
}

// 0x27c7a0
void __cdecl DispelAllTask::start(void)
{
    LIFT_STUB(0x27c7a0);
}

// 0x27c8b0
bool __cdecl RecallTask::Initialize(::Session const *, ::Zone *, ::Creature *, ::Creature *)
{
    LIFT_STUB(0x27c8b0);
}

// 0x27c980
void __cdecl RecallTask::start(void)
{
    LIFT_STUB(0x27c980);
}

// 0x27cba0
void __cdecl RecallTask::warp(void)
{
    LIFT_STUB(0x27cba0);
}

// 0x27cd40
bool __cdecl RecallTask::zoneTransition(void)
{
    LIFT_STUB(0x27cd40);
}

// 0x27d070
bool __cdecl SendHomeTask::Initialize(::Session const *, ::Zone *, ::Creature *, ::Creature *)
{
    LIFT_STUB(0x27d070);
}

// 0x27d140
void __cdecl SendHomeTask::start(void)
{
    LIFT_STUB(0x27d140);
}

// 0x27d410
bool __cdecl PartyHomeTask::Initialize(::Session const *, ::Zone *, ::Creature *, ::Creature *)
{
    LIFT_STUB(0x27d410);
}

// 0x27d4e0
void __cdecl PartyHomeTask::start(void)
{
    LIFT_STUB(0x27d4e0);
}

// 0x27d830
bool __cdecl SetParamTask::Initialize(::Session const *, ::Zone *, ::Creature *, ::Creature *, wchar_t *, __int64)
{
    LIFT_STUB(0x27d830);
}

// 0x27d9e0
void __cdecl SetParamTask::start(void)
{
    LIFT_STUB(0x27d9e0);
}

// 0x27dc80
bool __cdecl SetParamTask::setLevel(char, ::ChangedProperty *)
{
    LIFT_STUB(0x27dc80);
}

// 0x27ddb0
bool __cdecl ServerStatTask::Initialize(::Session const *, ::Zone *, ::Creature *)
{
    LIFT_STUB(0x27ddb0);
}

// 0x27de40
void __cdecl ServerStatTask::start(void)
{
    LIFT_STUB(0x27de40);
}

// 0x27df80
bool __cdecl WhoTask::Initialize(::Session const *, ::Zone *, ::Creature *)
{
    LIFT_STUB(0x27df80);
}

// 0x27e010
void __cdecl WhoTask::start(void)
{
    LIFT_STUB(0x27e010);
}

// 0x27e180
bool __cdecl GmOnTask::Initialize(::Session const *, ::Zone *, ::Creature *)
{
    LIFT_STUB(0x27e180);
}

// 0x27e210
void __cdecl GmOnTask::GmOn(::Pc &)
{
    LIFT_STUB(0x27e210);
}

// 0x27e350
void __cdecl GmOnTask::start(void)
{
    LIFT_STUB(0x27e350);
}

// 0x27e400
bool __cdecl TeleportToTask::Initialize(::Session const *, ::Zone *, ::Creature *, ::Creature *)
{
    LIFT_STUB(0x27e400);
}

// 0x27e4d0
void __cdecl TeleportToTask::start(void)
{
    LIFT_STUB(0x27e4d0);
}

// 0x27e6d0
void __cdecl TeleportToTask::warp(void)
{
    LIFT_STUB(0x27e6d0);
}

// 0x27e870
void __cdecl TeleportToTask::zoneTransition(void)
{
    LIFT_STUB(0x27e870);
}

// 0x27ea70
bool __cdecl TeleportTask::Initialize(::Session const *, ::Zone *, ::Creature *, int, int, int, int)
{
    LIFT_STUB(0x27ea70);
}

// 0x27eb30
void __cdecl TeleportTask::start(void)
{
    LIFT_STUB(0x27eb30);
}

// 0x27ec00
void __cdecl TeleportTask::warp(void)
{
    LIFT_STUB(0x27ec00);
}

// 0x27ed60
void __cdecl TeleportTask::zoneTransition(void)
{
    LIFT_STUB(0x27ed60);
}

// 0x27ef50
bool __cdecl AddQuestTask::Initialize(::Session const *, ::Zone *, ::Creature *, ::Creature *, __int64)
{
    LIFT_STUB(0x27ef50);
}

// 0x27f030
void __cdecl AddQuestTask::start(void)
{
    LIFT_STUB(0x27f030);
}

// 0x27f220
bool __cdecl DeleteQuestTask::Initialize(::Session const *, ::Zone *, ::Creature *, ::Creature *, __int64)
{
    LIFT_STUB(0x27f220);
}

// 0x27f300
void __cdecl DeleteQuestTask::start(void)
{
    LIFT_STUB(0x27f300);
}

// 0x27f510
bool __cdecl GetPcAssetTask::Initialize(::Session const *, ::Zone *, ::Creature *, ::Creature *)
{
    LIFT_STUB(0x27f510);
}

// 0x27f5e0
void __cdecl GetPcAssetTask::start(void)
{
    LIFT_STUB(0x27f5e0);
}

// 0x27f950
bool __cdecl PartyShowTask::Initialize(::Session const *, ::Zone *, ::Creature *, ::Creature *)
{
    LIFT_STUB(0x27f950);
}

// 0x27fa20
void __cdecl PartyShowTask::start(void)
{
    LIFT_STUB(0x27fa20);
}

// 0x27fdf0
bool __cdecl SequesterItemTask::Initialize(::Session const *, ::Zone *, ::Creature *, ::Creature *, char, short, bool)
{
    LIFT_STUB(0x27fdf0);
}

// 0x27fee0
void __cdecl SequesterItemTask::start(void)
{
    LIFT_STUB(0x27fee0);
}

// 0x2800b0
bool __cdecl SilenceTask::Initialize(::Session const *, ::Zone *, ::Creature *, ::Creature *, char)
{
    LIFT_STUB(0x2800b0);
}

// 0x280170
void __cdecl SilenceTask::start(void)
{
    LIFT_STUB(0x280170);
}

// 0x2802c0
bool __cdecl AnnounceZoneTask::Initialize(::Session const *, ::Zone *, ::Creature *, wchar_t const *, char, char)
{
    LIFT_STUB(0x2802c0);
}

// 0x2803b0
void __cdecl AnnounceZoneTask::start(void)
{
    LIFT_STUB(0x2803b0);
}

// 0x280550
bool __cdecl AasSetTimeTask::Initialize(::Session const *, ::Zone *, ::Creature *, ::Creature *, char, char, int, int)
{
    LIFT_STUB(0x280550);
}

// 0x280650
void __cdecl AasSetTimeTask::start(void)
{
    LIFT_STUB(0x280650);
}

// 0x280890
void __cdecl SpawnZoneNpcBuilderTask::start(void)
{
    LIFT_STUB(0x280890);
}

// 0x2809e0
void __cdecl ReturnToArenaLobbyBuilderTask::start(void)
{
    LIFT_STUB(0x2809e0);
}

// 0x280d20
wchar_t * __cdecl QuestBuilderTask::getcommandstr(::QuestBuilderTask::QuestBuilderType)
{
    LIFT_STUB(0x280d20);
}

// 0x280da0
bool __cdecl QuestBuilderTask::Initialize(::Session const *, ::Zone *, ::Creature *, ::Creature *, unsigned short, char, char, int &)
{
    LIFT_STUB(0x280da0);
}

// 0x280ed0
void __cdecl QuestBuilderTask::start(void)
{
    LIFT_STUB(0x280ed0);
}

// 0x281080
void __cdecl QuestBuilderTask::sendsuccess(void)
{
    LIFT_STUB(0x281080);
}

// 0x281380
void __cdecl QuestBuilderTask::sendfailure(int)
{
    LIFT_STUB(0x281380);
}

// 0x281510
bool __cdecl AchievementSetRegisterBuilderTask::Initialize(::Session const *, ::Zone *, ::Creature *, short, __int64)
{
    LIFT_STUB(0x281510);
}

// 0x2815c0
void __cdecl AchievementSetRegisterBuilderTask::start(void)
{
    LIFT_STUB(0x2815c0);
}

// 0x281680
bool __cdecl SpawnNpcTask::Initialize(::Session const *, ::Zone *, ::Creature *, wchar_t const *, char)
{
    LIFT_STUB(0x281680);
}

// 0x2817a0
void __cdecl SpawnNpcTask::start(void)
{
    LIFT_STUB(0x2817a0);
}

// 0x281b90
bool __cdecl InvokeEffectTask::Initialize(::Session const *, ::Zone *, ::Creature *, wchar_t const *)
{
    LIFT_STUB(0x281b90);
}

// 0x281ca0
void __cdecl InvokeEffectTask::start(void)
{
    LIFT_STUB(0x281ca0);
}

// 0x281e70
bool __cdecl DisposeItemAllTask::Initialize(::Session const *, ::Zone *, ::Creature *)
{
    LIFT_STUB(0x281e70);
}

// 0x281f00
void __cdecl DisposeItemAllTask::start(void)
{
    LIFT_STUB(0x281f00);
}

// 0x281fa0
bool __cdecl SetActivatedTeleportAllTask::Initialize(::Session const *, ::Zone *, ::Creature *)
{
    LIFT_STUB(0x281fa0);
}

// 0x282030
void __cdecl SetActivatedTeleportAllTask::start(void)
{
    LIFT_STUB(0x282030);
}

// 0x2820b0
bool __cdecl ResetActivatedTeleportAllTask::Initialize(::Session const *, ::Zone *, ::Creature *)
{
    LIFT_STUB(0x2820b0);
}

// 0x282140
void __cdecl ResetActivatedTeleportAllTask::start(void)
{
    LIFT_STUB(0x282140);
}

// 0x2821c0
bool __cdecl SetSeasonContentsCombatRatingScoreBuilderTask::Initialize(::Session const *, ::Zone *, ::Creature *, char, int)
{
    LIFT_STUB(0x2821c0);
}

// 0x282270
void __cdecl SetSeasonContentsCombatRatingScoreBuilderTask::start(void)
{
    LIFT_STUB(0x282270);
}

// 0x282930
bool __cdecl ChangeChannelBuilderTask::Initialize(::Session const *, ::Zone *, ::Creature *, int)
{
    LIFT_STUB(0x282930);
}

// 0x2829d0
void __cdecl ChangeChannelBuilderTask::start(void)
{
    LIFT_STUB(0x2829d0);
}

// 0x282ea0
bool __cdecl StartBattleRoyalFieldTask::Initialize(::Session const *, ::Zone *, ::Creature *)
{
    LIFT_STUB(0x282ea0);
}

// 0x282f30
void __cdecl StartBattleRoyalFieldTask::start(void)
{
    LIFT_STUB(0x282f30);
}

// 0x2830b0
bool __cdecl RemoveTraceTask::Initialize(::Session const *, ::Zone *, ::Creature *, char)
{
    LIFT_STUB(0x2830b0);
}

// 0x283150
void __cdecl RemoveTraceTask::start(void)
{
    LIFT_STUB(0x283150);
}
