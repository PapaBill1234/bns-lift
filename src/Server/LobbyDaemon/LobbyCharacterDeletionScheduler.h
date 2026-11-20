// LobbyCharacterDeletionScheduler.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

struct EventContext;

class LobbyCharacterDeletionScheduler
{
public:
    bool Start(long, int);  // 0x56780
    virtual bool HandleEvent(EventContext*, unsigned long);  // 0x568a0
private:
    bool process();  // 0x568e0
};
