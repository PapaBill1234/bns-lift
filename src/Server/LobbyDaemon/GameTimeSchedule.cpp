// GameTimeSchedule.obj (LobbyDaemon PDB, 2019 + PDB). Lifted from the pseudocode with PDB types.
// A stub is not a lift. Each stub has a LIFT note with the reason.
#include <string.h>
#include "GameTimeSchedule.h"
#include "LiftStub.h"

// 0x4b8e0
// The string has 42 hex digits. Each digit gives 4 hours, most significant bit first.
bool IDEV612_TimeTable::Initialize(char const* timeTableStr)
{
    if (timeTableStr == nullptr || strlen(timeTableStr) != 42)
        return false;

    for (int i = 0; i < 42; ++i)
    {
        char c = timeTableStr[i];
        char value;
        if (c >= '0' && c <= '9')
            value = c - '0';
        else if (c >= 'a' && c <= 'f')
            value = c - 'a' + 10;
        else if (c >= 'A' && c <= 'F')
            value = c - 'A' + 10;
        else
            return false;

        for (int bit = 0; bit < 4; ++bit)
            _table[i * 4 + bit] = ((value << bit) & 8) != 0;
    }
    return true;
}

// 0x4b9a0
// LIFT: not lifted in card ld-4 (0x4b9a0). The body inlines the RefCntList ctor. The RefCntList layout
// belongs to card ld-3. Body: _index = 0; _block = false; InitializeCriticalSection; _queue zeroed.
GameTimeQueue::GameTimeQueue()
{
    LIFT_STUB(0x4b9a0);
}

// 0x4b9e0
// LIFT: not lifted in card ld-4 (0x4b9e0). The body inlines RefCntList::Popfront in a loop and calls
// removeReferenceCount(node, L"GameTimeSchedule.cpp", 112). Popfront and the layout belong to card ld-3.
GameTimeQueue::~GameTimeQueue()
{
    LIFT_STUB(0x4b9e0);
}

// 0x4ba80
// LIFT: not lifted in card ld-4 (0x4ba80). The body writes TLobbyError (card ld-2) and calls
// RefCntList::Pushback (layout in card ld-3).
bool GameTimeQueue::Pushback(GameTimeScheduleNode*)
{
    LIFT_STUB(0x4ba80);
}

// 0x4bb80
// LIFT: not lifted in card ld-4 (0x4bb80). The body writes TLobbyError and reads CliSession (card ld-2).
// It makes KickJob objects for LobbyJobManager through LobbyDaemon::_instance (cards ld-15, ld-20).
void GameTimeQueue::Block()
{
    LIFT_STUB(0x4bb80);
}

// 0x4bf90
// LIFT: not lifted in card ld-4 (0x4bf90). The body reads _index, _block and _lock. These members
// need the GameTimeQueue layout, and its size needs the RefCntList layout (card ld-3).
// Body: lock; if _block, clear it and log line 221; else log and alert line 216 (== CRASH ==); unlock.
void GameTimeQueue::Release()
{
    LIFT_STUB(0x4bf90);
}

// 0x4c020
// LIFT: not lifted in card ld-4 (0x4c020). The body needs the Timer base and GameTimeQueue _queues[168].
// The GameTimeQueue size needs the RefCntList layout (card ld-3).
GameTimeScheduler::GameTimeScheduler()
{
    LIFT_STUB(0x4c020);
}

// 0x4c0e0
// LIFT: not lifted in card ld-4 (0x4c0e0). Same reason as the ctor 0x4c020 (GameTimeQueue layout, card ld-3).
GameTimeScheduler::~GameTimeScheduler()
{
    LIFT_STUB(0x4c0e0);
}

// 0x4c150
// LIFT: not lifted in card ld-4 (0x4c150). The body calls TimerQueue::Add on
// LobbyDaemon::_instance->GlobalTimerQueue. The LobbyDaemon layout belongs to cards ld-15 and ld-20.
// Body: queue index = hour + 24 * (Monday-based weekday); Block it; Add(1000 * (start - now + 3600)).
bool GameTimeScheduler::Start()
{
    LIFT_STUB(0x4c150);
}

// 0x4c2e0
// LIFT: not lifted in card ld-4 (0x4c2e0). Same reason as Start 0x4c150 (LobbyDaemon::_instance,
// GlobalTimerQueue, GameTimeQueue layout).
bool GameTimeScheduler::HandleEvent(EventContext*, unsigned long)
{
    LIFT_STUB(0x4c2e0);
}

// 0x4c390
// LIFT: not lifted in card ld-4 (0x4c390). The body writes TLobbyError (26, 27, 1), reads
// CliSession::_clikey and calls CliSession::setScheduledEndTime (card ld-2). It also needs the
// GameTimeScheduleNode layout (RefCntListNode base, card ld-3).
bool GameTimeScheduler::Schedule(CliSession*, IDEV612_TimeTable const&, long long*)
{
    LIFT_STUB(0x4c390);
}

// 0x4c6a0
// LIFT: not lifted in card ld-4 (0x4c6a0). The body reads CliSession::_clikey (card ld-2) and calls
// RefCntList::Remove (layout in card ld-3).
void GameTimeScheduler::Unschedule(CliSession*, GameTimeScheduleNode*)
{
    LIFT_STUB(0x4c6a0);
}
