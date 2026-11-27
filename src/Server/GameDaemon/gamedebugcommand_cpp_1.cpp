// gamedebugcommand_cpp_1.cpp: gamedebugcommand.cpp part 1 (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "gamedebugcommand.h"
#include "creature.h"
#include "envobj.h"
#include "geoworld.h"
#include "pc.h"
#include "zone.h"
#include "LiftStub.h"

// 0x283cb0
__cdecl GameDebugTask::~GameDebugTask(void)
{
    LIFT_STUB(0x283cb0);
}

// 0x283cc0
bool __cdecl GameDebugTask::Initialize(unsigned __int64)
{
    LIFT_STUB(0x283cc0);
}

// 0x283d40
bool __cdecl GameDebugTask::Initialize(unsigned __int64, wchar_t const *)
{
    LIFT_STUB(0x283d40);
}

// 0x283e30
bool __cdecl GameDebugTask::Initialize(::Zone *, ::Creature *)
{
    LIFT_STUB(0x283e30);
}

// 0x283ed0
void __cdecl GameDebugTask::TimerExpired(unsigned int, long)
{
    LIFT_STUB(0x283ed0);
}

// 0x284030
::Pointer2< ::Creature> __cdecl GameDebugTask::GetCreature(unsigned __int64)
{
    LIFT_STUB(0x284030);
}

// 0x2842d0
::Pointer2< ::Creature> __cdecl GameDebugTask::GetCreature(wchar_t const *)
{
    LIFT_STUB(0x2842d0);
}

// 0x284440
::Pointer2< ::Pc> __cdecl GameDebugTask::GetPc(unsigned __int64)
{
    LIFT_STUB(0x284440);
}

// 0x284530
::Pointer2< ::Pc> __cdecl GameDebugTask::GetPc(wchar_t const *)
{
    LIFT_STUB(0x284530);
}

// 0x2846a0
::Pointer2< ::Env> __cdecl GameDebugTask::GetEnv(unsigned __int64, wchar_t const *)
{
    LIFT_STUB(0x2846a0);
}

// 0x284830
::Pointer2< ::Env> __cdecl GameDebugTask::GetEnv(unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x284830);
}

// 0x284960
bool __cdecl GameDebugTask::GetDataId(wchar_t const *, unsigned int *)
{
    LIFT_STUB(0x284960);
}

// 0x2849c0
bool __cdecl GameDebugTask::isHex(wchar_t const *)
{
    LIFT_STUB(0x2849c0);
}

// 0x284a40
bool __cdecl GameDebugTask::getHexId(wchar_t const *, __int64 &)
{
    LIFT_STUB(0x284a40);
}

// 0x284b60
bool __cdecl GameDebugTask::getDecId(wchar_t const *, __int64 &)
{
    LIFT_STUB(0x284b60);
}

// 0x284c60
void __cdecl KillDebugTask::start(void)
{
    LIFT_STUB(0x284c60);
}

// 0x284ec0
bool __cdecl KillDebugTask::Initialize(unsigned __int64, wchar_t const *)
{
    LIFT_STUB(0x284ec0);
}

// 0x284fb0
void __cdecl Kill2DebugTask::start(void)
{
    LIFT_STUB(0x284fb0);
}

// 0x285210
bool __cdecl Kill2DebugTask::Initialize(::Zone *, ::Creature *, wchar_t const *)
{
    LIFT_STUB(0x285210);
}

// 0x285310
bool __cdecl SpawnNpcDebugTask::Initialize(unsigned __int64, wchar_t const *, wchar_t const *, char, char)
{
    LIFT_STUB(0x285310);
}

// 0x285490
bool __cdecl SpawnNpcDebugTask::Initialize(unsigned __int64, wchar_t const *, wchar_t const *, short, short, short, char, char)
{
    LIFT_STUB(0x285490);
}

// 0x285630
void __cdecl SpawnNpcDebugTask::start(void)
{
    LIFT_STUB(0x285630);
}

// 0x285a70
void __cdecl SpawnZoneNpcDebugTask::start(void)
{
    LIFT_STUB(0x285a70);
}

// 0x285bc0
void __cdecl DespawnNpcDebugTask::start(void)
{
    LIFT_STUB(0x285bc0);
}

// 0x285ca0
bool __cdecl SpawnDuelBotDebugTask::Initialize(unsigned __int64, wchar_t const *, wchar_t const *, char)
{
    LIFT_STUB(0x285ca0);
}

// 0x285e20
void __cdecl SpawnDuelBotDebugTask::start(void)
{
    LIFT_STUB(0x285e20);
}

// 0x286070
void __cdecl DespawnDuelBotDebugTask::start(void)
{
    LIFT_STUB(0x286070);
}

// 0x2861a0
void __cdecl CombatDuelBotDebugTask::start(void)
{
    LIFT_STUB(0x2861a0);
}

// 0x286650
void __cdecl SetEnvStateDebugTask::start(void)
{
    LIFT_STUB(0x286650);
}

// 0x286700
void __cdecl DiffEnvHpDebugTask::start(void)
{
    LIFT_STUB(0x286700);
}

// 0x2867c0
void __cdecl SetEnvHpDebugTask::start(void)
{
    LIFT_STUB(0x2867c0);
}

// 0x286880
void __cdecl SetEnvEnableDebugTask::start(void)
{
    LIFT_STUB(0x286880);
}

// 0x286950
void __cdecl SetEnvEnableToggleIntervalDebugTask::start(void)
{
    LIFT_STUB(0x286950);
}

// 0x286a10
void __cdecl AcquireFieldItemDebugTask::start(void)
{
    LIFT_STUB(0x286a10);
}

// 0x286a90
void __cdecl SpawnSummonedDebugTask::start(void)
{
    LIFT_STUB(0x286a90);
}

// 0x286c50
bool __cdecl MakeSummonedDebugTask::Initialize(::Zone *const, ::Pc *const, char, int, wchar_t const *const)
{
    LIFT_STUB(0x286c50);
}

// 0x286f90
void __cdecl MakeSummonedDebugTask::start(void)
{
    LIFT_STUB(0x286f90);
}

// 0x287300
bool __cdecl ChangeSummonedDebugTask::Initialize(::Zone *const, ::Pc *const, char const *const)
{
    LIFT_STUB(0x287300);
}

// 0x287410
void __cdecl ChangeSummonedDebugTask::start(void)
{
    LIFT_STUB(0x287410);
}

// 0x2875c0
bool __cdecl QuestDebugTask::Initialize(::Zone *, ::Creature *, ::QuestDebugTask::QuestDebugType, wchar_t const *, char, __int64, char)
{
    LIFT_STUB(0x2875c0);
}

// 0x2876b0
void __cdecl QuestDebugTask::start(void)
{
    LIFT_STUB(0x2876b0);
}

// 0x287830
void __cdecl SetTendencyVictoryTendencyDebugTask::start(void)
{
    LIFT_STUB(0x287830);
}

// 0x287950
void __cdecl DisposeBuffDebugTask::start(void)
{
    LIFT_STUB(0x287950);
}

// 0x2879d0
void __cdecl ResetBuffDebugTask::start(void)
{
    LIFT_STUB(0x2879d0);
}

// 0x287a00
void __cdecl AcquireItemDebugTask::start(void)
{
    LIFT_STUB(0x287a00);
}

// 0x287c90
void __cdecl DisposeItemDebugTask::start(void)
{
    LIFT_STUB(0x287c90);
}

// 0x287d80
bool __cdecl ExpandInventoryDebugTask::Initialize(::Zone *, ::Creature *, wchar_t *, char)
{
    LIFT_STUB(0x287d80);
}

// 0x287e90
void __cdecl WarpToPosDebugTask::start(void)
{
    LIFT_STUB(0x287e90);
}

// 0x287ec0
void __cdecl WarpToPosDebugTask::warp(void)
{
    LIFT_STUB(0x287ec0);
}

// 0x287fd0
void __cdecl WarpToPosDebugTask::zoneTransition(void)
{
    LIFT_STUB(0x287fd0);
}

// 0x288260
void __cdecl WarpToPhaseMainZoneDebugTask::start(void)
{
    LIFT_STUB(0x288260);
}

// 0x2882d0
void __cdecl WarpToPhaseMainZoneDebugTask::warp(void)
{
    LIFT_STUB(0x2882d0);
}

// 0x2883e0
__cdecl WarpToCreatureDebugTask::WarpToCreatureDebugTask(void)
{
    LIFT_STUB(0x2883e0);
}

// 0x288480
bool __cdecl WarpToCreatureDebugTask::Initialize(::Zone *, ::Creature *, ::Creature *)
{
    LIFT_STUB(0x288480);
}

// 0x288510
bool __cdecl WarpToCreatureDebugTask::Initialize(unsigned __int64, wchar_t const *, wchar_t const *)
{
    LIFT_STUB(0x288510);
}

// 0x288680
void __cdecl WarpToCreatureDebugTask::start(void)
{
    LIFT_STUB(0x288680);
}

// 0x2886e0
void __cdecl WarpToCreatureDebugTask::warp(void)
{
    LIFT_STUB(0x2886e0);
}

// 0x2887f0
void __cdecl WarpToCreatureDebugTask::zoneTransition(void)
{
    LIFT_STUB(0x2887f0);
}

// 0x288b10
void __cdecl RecallPartyDebugTask::start(void)
{
    LIFT_STUB(0x288b10);
}

// 0x288e20
void __cdecl WarpToRespawnDebugTask::start(void)
{
    LIFT_STUB(0x288e20);
}

// 0x288ea0
void __cdecl WarpToRespawnDebugTask::warp(void)
{
    LIFT_STUB(0x288ea0);
}

// 0x289060
void __cdecl WarpToRespawnDebugTask::zoneTransition(void)
{
    LIFT_STUB(0x289060);
}

// 0x289330
void __cdecl WarpToAreaDebugTask::start(void)
{
    LIFT_STUB(0x289330);
}

// 0x2893e0
void __cdecl WarpToAreaDebugTask::warp(void)
{
    LIFT_STUB(0x2893e0);
}

// 0x289560
void __cdecl WarpToPcSpawnDebugTask::start(void)
{
    LIFT_STUB(0x289560);
}

// 0x289610
void __cdecl WarpToPcSpawnDebugTask::warp(void)
{
    LIFT_STUB(0x289610);
}

// 0x2897b0
void __cdecl WarpToEnvDebugTask::start(void)
{
    LIFT_STUB(0x2897b0);
}

// 0x289860
bool __cdecl getEnvActionPos(::GeoZone const *, ::GeoEnvObj const *, ::vector16 &)
{
    LIFT_STUB(0x289860);
}

// 0x289990
void __cdecl WarpToEnvDebugTask::warp(void)
{
    LIFT_STUB(0x289990);
}

// 0x289b10
void __cdecl ReturnTownDebugTask::start(void)
{
    LIFT_STUB(0x289b10);
}

// 0x289c40
void __cdecl CreateTeamDebugTask::start(void)
{
    LIFT_STUB(0x289c40);
}

// 0x289e60
void __cdecl ReEnterZoneDebugTask::start(void)
{
    LIFT_STUB(0x289e60);
}

// 0x289ff0
void __cdecl InitializeRecycleTimeTask::start(void)
{
    LIFT_STUB(0x289ff0);
}
