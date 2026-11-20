// LobbyTick.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

struct EventContext;

class LobbyTick
{
public:
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
