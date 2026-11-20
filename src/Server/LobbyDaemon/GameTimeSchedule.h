// GameTimeSchedule.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
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
};
