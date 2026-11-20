// PcCafeMileage.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

class CliSession;
class LobbyMessage;

class PcCafeMileage
{
public:
    virtual void Accept(LobbyMessage*);  // 0x633b0
    virtual bool Start(CliSession*, long long);  // 0x63400
    virtual bool Stop(CliSession*, long long, long long*);  // 0x636b0
};
