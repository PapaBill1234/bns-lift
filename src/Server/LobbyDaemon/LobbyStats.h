// LobbyStats.obj (LobbyDaemon 2019 + PDB).
#pragma once
#include "TimerQueue.h"

class LobbyStats : public Timer
{
public:
    // LIFT: inline constructor at the allocation site in LobbyDaemon::initialize (0x5a0b0 caller).
    LobbyStats() : _run(false), _period(0)
    {
        _dir[0] = 0;
        _fname[0] = 0;
        _fext[0] = 0;
    }

    bool Initialize(wchar_t const* dir, wchar_t const* fname, wchar_t const* fext, long period);  // 0x5a0b0
    virtual bool HandleEvent(EventContext*, unsigned long);  // 0x5a1d0
    virtual unsigned int TimerClass() const { return 0; }  // 0x5a0a0 (folded)
    virtual unsigned long long TimerId() const { return 0; }  // 0x5a0a0 (folded)

private:
    bool update();  // 0x5a210

    bool _run;
    wchar_t _dir[260];
    wchar_t _fname[260];
    wchar_t _fext[260];
    long _period;
};
static_assert(sizeof(LobbyStats) == 0x658, "sizeof LobbyStats");
