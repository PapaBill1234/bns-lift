// LobbyTick.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

#include "RefCntList.h"

struct EventContext;

class LobbyTick
{
public:
    class Listener : public RefCntListNode
    {
    public:
        // LIFT: The ctor is inline at MileageInterimDepositTimer::MileageInterimDepositTimer (0x60a80).
        // LIFT: ld-12 owns this class. Merge ld-12 first, then keep only this ctor line from ld-10.
        Listener() : _listen(false) {}
        bool IsListen() { return _listen; }
        void SetListen(bool listen) { _listen = listen; }
        virtual bool Tick(long long elapsed) = 0;

    private:
        volatile bool _listen;
    };

    virtual ~LobbyTick();  // 0x5a610
    virtual bool HandleEvent(EventContext*, unsigned long);  // 0x5a7f0
private:
    void process();  // 0x5a830
};

class LobbyTickEvent
{
public:
    virtual ~LobbyTickEvent();  // 0x5a9b0
    virtual bool HandleEvent(EventContext*, unsigned long);  // 0x5aa20
};
static_assert(sizeof(LobbyTick::Listener) == 0x38, "sizeof LobbyTick::Listener");
