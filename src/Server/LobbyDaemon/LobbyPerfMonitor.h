// LobbyPerfMonitor.obj (LobbyDaemon PDB, 2019 + PDB).
#pragma once
#include "PerfCounterProvider.h"
#include "TimerQueue.h"

class SystemCounterSet : public CounterSet
{
public:
    // LIFT: Inlined in SystemPerfMonitor::Initialize (0x59d60).
    BL_PERF_COUNTERSET_INSTANCE* Create(wchar_t const* name) { return create(&ID, name); }
private:
    static GUID const ID;
};
static_assert(sizeof(SystemCounterSet) == 0x10, "sizeof SystemCounterSet");

class SystemPerfMonitor : public Timer
{
public:
    // LIFT: No separate constructor body in the PDB.
    SystemPerfMonitor() : _run(false) {}
    virtual ~SystemPerfMonitor();  // 0x59ce0
    virtual unsigned int TimerClass() const { return 0; }  // 0x5a0a0 (folded).
    virtual unsigned long long TimerId() const { return 0; }  // 0x5a0a0 (folded).
    bool Initialize();  // 0x59d60
    bool Start();  // 0x59e30
    virtual bool HandleEvent(EventContext*, unsigned long);  // 0x59ee0
private:
    void update();  // 0x59f40
    bool _run;
    SystemCounterSet _systemCounterSet;
};
static_assert(sizeof(SystemPerfMonitor) == 0x50, "sizeof SystemPerfMonitor");
