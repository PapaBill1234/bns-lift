// LobbyJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

struct EventContext;
class LobbyJob;
class LobbyJobTaskParam;

class LobbyJob
{
public:
    virtual ~LobbyJob();  // 0x12270
protected:
    virtual bool dispatch_work(int, void*);  // 0x122b0
    bool transit(int);  // 0xc1710
};

class LobbyJobManager
{
public:
    ~LobbyJobManager();  // 0xc1a60
    bool Initialize(int);  // 0xc1b40
    bool Register(LobbyJob*);  // 0xc1c90
    void Clear();  // 0xc1d20
    bool Start(LobbyJob*, int, void*);  // 0xc1ed0
    bool Postpone(LobbyJob*, int, LobbyJobTaskParam*);  // 0xc1f30
    void Execute(LobbyJob*, int, void*);  // 0xc2020
    bool ExecuteW(unsigned long long, int, void*);  // 0xc20a0
    bool ResumeW(unsigned long long, int, int, void*);  // 0xc2140
private:
    bool add(LobbyJob*);  // 0xc21f0
    void remove(unsigned long long);  // 0xc22d0
    LobbyJob* find(unsigned long long);  // 0xc23d0
};

class LobbyJobTaskEvent
{
public:
    virtual ~LobbyJobTaskEvent();  // 0xc1670
    virtual bool HandleEvent(EventContext*, unsigned long);  // 0xc24c0
};
