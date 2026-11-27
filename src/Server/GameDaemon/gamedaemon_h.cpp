// gamedaemon_h.cpp: gamedaemon.h (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "gamedaemon.h"
#include "rankingreward.h"
#include "gamedconfig.h"
#include "LiftStub.h"
#include <string.h>

#pragma comment(linker, "/INCLUDE:?IsArenaDaemon@GameDaemon@@SA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?IsArenaDungeonDaemon@GameDaemon@@SA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?IsArenaEnabledGameDaemon@GameDaemon@@SA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SetEventReplyCacheHello@GameDaemon@@SA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:??0Rule@TimeBasedPlaySeasonSchedule@@QEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?ShortName@GameDaemon@@UEAAPEB_WXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Name@GameDaemon@@UEAAPEB_WXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?GetTimerInterval@GameDaemon@@UEAAJXZ")  // LIFT: dead-strip keep (no live caller yet)

// LIFT: the PDB puts GamedInstance in the globals (rva 0xF9DDC0). gamedaemon.cpp defines it in the original. This file holds it until that file is lifted.
::GameDaemon * GameDaemon::GamedInstance = nullptr;

// 0x27f80
bool __cdecl GameDaemon::IsArenaDaemon(void)
{
    return GamedInstance->config->_arenaEnabled && GamedInstance->config->_arenaId != 0;
}

// 0x27fb0
bool __cdecl GameDaemon::IsArenaDungeonDaemon(void)
{
    return GamedInstance->config->_arenaEnabled && GamedInstance->config->_arenaId != 0 && GamedInstance->arenaAttraction == 2;
}

// 0x971d0
::RankingResult * __cdecl GameDaemon::GetRankingResult(void)
{
    LIFT_STUB(0x971d0);
}

// 0x1107f0
bool __cdecl GameDaemon::IsArenaEnabledGameDaemon(void)
{
    return GamedInstance->config->_arenaEnabled && GamedInstance->config->_arenaId == 0;
}

// 0x180ca0
bool __cdecl GameDaemon::InitializeRankingResult(void)
{
    LIFT_STUB(0x180ca0);
}

// 0x180e10
bool __cdecl GameDaemon::SetEventReplyCacheHello(void)
{
    void *event = GamedInstance->replyCacheHelloEvent.Event;
    return event != nullptr && SetEvent(event) != FALSE;
}

// 0x1ee590
__cdecl TimeBasedPlaySeasonSchedule::Rule::Rule(void)
{
    // LIFT: the PDB has Rule::Clear; the 2019 build inlines the same stores here.
    minutes = -1;
    memset(rewardList, 0, sizeof(rewardList));
}

// 0x1ee5b0
__cdecl TimeBasedPlaySeasonSchedule::Data::Data(void)
{
    LIFT_STUB(0x1ee5b0);
}

// 0x1ee630
__cdecl TimeBasedPlaySeasonSchedule::TimeBasedPlaySeasonSchedule(void)
{
    LIFT_STUB(0x1ee630);
}

// 0x1ee6f0
wchar_t const * __cdecl GameDaemon::ShortName(void)
{
    return L"gamed";
}

// 0x1ee700
wchar_t const * __cdecl GameDaemon::Name(void)
{
    return L"GameDaemon";
}

// 0x1ee710
long __cdecl GameDaemon::GetTimerInterval(void)
{
    return 100;
}
