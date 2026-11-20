// GameTimeSchedule.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "GameTimeSchedule.h"
#include "LiftStub.h"

// 0x4b8e0
bool IDEV612_TimeTable::Initialize(char const*)
{
    LIFT_STUB(0x4b8e0);
}

// 0x4b9a0
GameTimeQueue::GameTimeQueue()
{
    LIFT_STUB(0x4b9a0);
}

// 0x4b9e0
GameTimeQueue::~GameTimeQueue()
{
    LIFT_STUB(0x4b9e0);
}

// 0x4ba80
bool GameTimeQueue::Pushback(GameTimeScheduleNode*)
{
    LIFT_STUB(0x4ba80);
}

// 0x4bb80
void GameTimeQueue::Block()
{
    LIFT_STUB(0x4bb80);
}

// 0x4bf90
void GameTimeQueue::Release()
{
    LIFT_STUB(0x4bf90);
}

// 0x4c020
GameTimeScheduler::GameTimeScheduler()
{
    LIFT_STUB(0x4c020);
}

// 0x4c0e0
GameTimeScheduler::~GameTimeScheduler()
{
    LIFT_STUB(0x4c0e0);
}

// 0x4c150
bool GameTimeScheduler::Start()
{
    LIFT_STUB(0x4c150);
}

// 0x4c2e0
bool GameTimeScheduler::HandleEvent(EventContext*, unsigned long)
{
    LIFT_STUB(0x4c2e0);
}

// 0x4c390
bool GameTimeScheduler::Schedule(CliSession*, IDEV612_TimeTable const&, long long*)
{
    LIFT_STUB(0x4c390);
}

// 0x4c6a0
void GameTimeScheduler::Unschedule(CliSession*, GameTimeScheduleNode*)
{
    LIFT_STUB(0x4c6a0);
}
