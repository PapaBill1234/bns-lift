// GameTimeSchedule.obj (LobbyDaemon PDB, 2019 + PDB). Layouts from include/pdb/LobbyDaemon/types.h.
// LIFT: GameTimeQueue (size 0x48: _index, _block, _lock, RefCntList _queue) and GameTimeScheduler
// (Timer base, GameTimeQueue _queues[168], _currentQueue, _currentQueueTime, _run) have no members yet.
// The RefCntList layout belongs to card ld-3. Card ld-4 does not add these layouts.
#pragma once

class CliSession;
struct EventContext;
class GameTimeScheduleNode;
class IDEV612_TimeTable;

class GameTimeQueue
{
public:
    GameTimeQueue();  // 0x4b9a0
    ~GameTimeQueue();  // 0x4b9e0
    bool Pushback(GameTimeScheduleNode*);  // 0x4ba80
    void Block();  // 0x4bb80
    void Release();  // 0x4bf90
};

class GameTimeScheduler
{
public:
    GameTimeScheduler();  // 0x4c020
    virtual ~GameTimeScheduler();  // 0x4c0e0
    bool Start();  // 0x4c150
    virtual bool HandleEvent(EventContext*, unsigned long);  // 0x4c2e0
    bool Schedule(CliSession*, IDEV612_TimeTable const&, long long*);  // 0x4c390
    void Unschedule(CliSession*, GameTimeScheduleNode*);  // 0x4c6a0
};

class IDEV612_TimeTable
{
public:
    bool Initialize(char const*);  // 0x4b8e0

    bool _table[168];  // 7 days x 24 hours
};
static_assert(sizeof(IDEV612_TimeTable) == 168, "sizeof IDEV612_TimeTable");
