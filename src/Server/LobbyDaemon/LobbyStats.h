// LobbyStats.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

struct EventContext;

class LobbyStats
{
public:
    bool Initialize(wchar_t const*, wchar_t const*, wchar_t const*, long);  // 0x5a0b0
    virtual bool HandleEvent(EventContext*, unsigned long);  // 0x5a1d0
private:
    bool update();  // 0x5a210
};
