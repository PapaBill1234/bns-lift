// PcCafe.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

class CliSession;
class TencentNetBar;

class TencentNetBar
{
public:
    static TencentNetBar* CreateFromExternalAuthData(char const*, CliSession const*);  // 0x62e90
private:
    virtual void onSet(CliSession*);  // 0x63350
};
