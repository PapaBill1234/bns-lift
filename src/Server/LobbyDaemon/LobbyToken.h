// LobbyToken.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

class CliSession;
class LobbyToken;

class LobbyToken
{
public:
    LobbyToken(CliSession*);  // 0x96750
    bool Verify(int, unsigned long long, unsigned long long, unsigned long) const;  // 0x96830
    virtual void Expire();  // 0x96b00
};

class LobbyTokenDesk
{
public:
    LobbyTokenDesk(long, unsigned long long (__cdecl*)(void));  // 0x96c30
    virtual ~LobbyTokenDesk();  // 0x96d70
    bool Issue(LobbyToken*);  // 0x96e20
    LobbyToken* Verify(int, unsigned long long, unsigned long long, unsigned long, bool&);  // 0x96fb0
    virtual bool Tick(long long);  // 0x97240
};
