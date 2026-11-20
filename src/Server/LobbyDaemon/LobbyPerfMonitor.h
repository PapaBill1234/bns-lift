// LobbyPerfMonitor.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

struct EventContext;

class SystemPerfMonitor
{
public:
    virtual ~SystemPerfMonitor();  // 0x59ce0
    bool Initialize();  // 0x59d60
    bool Start();  // 0x59e30
    virtual bool HandleEvent(EventContext*, unsigned long);  // 0x59ee0
private:
    void update();  // 0x59f40
};
