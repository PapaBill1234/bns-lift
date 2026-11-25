// LobbyTick.obj (LobbyDaemon 2019 + PDB).
#pragma once
#include "RefCntList.h"
#include "TimerQueue.h"

class LobbyTick : public Timer
{
public:
    class Listener : public RefCntListNode
    {
    public:
        // LIFT: The ctor is inline at MileageInterimDepositTimer::MileageInterimDepositTimer (0x60a80).
        Listener() : _listen(false) {}
        bool IsListen() { return _listen; }
        void SetListen(bool listen) { _listen = listen; }
        virtual bool Tick(long long elapsed) = 0;

    private:
        volatile bool _listen;
    };

    // LIFT: inline constructor at the allocation site in LobbyDaemon::initialize (0x5a610 dtor).
    explicit LobbyTick(long period) : _run(false), _period(period) {}
    virtual ~LobbyTick();  // 0x5a610
    bool Start();  // LIFT: no out-of-line body; LTCG inlines it in LobbyDaemon::onStart (0x9dca0).
    bool Add(Listener* listener);  // 0x5a6e0
    bool Remove(Listener* listener);  // 0x5a770
    virtual bool HandleEvent(EventContext*, unsigned long);  // 0x5a7f0
    virtual unsigned int TimerClass() const { return 0; }  // 0x5a0a0 (folded)
    virtual unsigned long long TimerId() const { return 0; }  // 0x5a0a0 (folded)

private:
    void process();  // 0x5a830

    bool _run;
    long _period;
    CriticalSection _lock;
    RefCntList _list;
};
static_assert(sizeof(LobbyTick) == 0x80, "sizeof LobbyTick");
static_assert(sizeof(LobbyTick::Listener) == 0x38, "sizeof LobbyTick::Listener");

class LobbyTickEvent : public DynamicEventObject
{
public:
    LobbyTickEvent(LobbyTick* owner, LobbyTick::Listener* listener, long long elapsed);  // 0x5a900
    virtual ~LobbyTickEvent();  // 0x5a9b0
    virtual unsigned int EventId() const { return 0; }  // 0x5a0a0 (folded)
    virtual bool HandleEvent(EventContext*, unsigned long);  // 0x5aa20

private:
    LobbyTick* _owner;
    LobbyTick::Listener* _listener;
    long long _elapsed;
};
static_assert(sizeof(LobbyTickEvent) == 0x30, "sizeof LobbyTickEvent");
