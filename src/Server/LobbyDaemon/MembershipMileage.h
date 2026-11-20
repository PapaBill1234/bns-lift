// MembershipMileage.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

class CliSession;
class LobbyMessage;
class MileageConfig;

class MembershipMileage
{
public:
    virtual void Accept(LobbyMessage*);  // 0x5bff0
    virtual bool Initialize(MileageConfig const&, long long);  // 0x5c040
    virtual bool Start(CliSession*, long long);  // 0x5c300
    virtual bool Stop(CliSession*, long long, long long*);  // 0x5c6c0
};
