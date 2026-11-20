// GetChargeInfoJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

class CliSession;
class LobbyGateChannel;
struct LobbyJobDef;

class GetChargeInfoJob
{
public:
    virtual LobbyJobDef const* GetDefinition() const;  // 0x50550
    static void* _vtbl();  // 0x505b0
    GetChargeInfoJob(CliSession*, LobbyGateChannel*);  // 0x50630
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x50560
    virtual bool work(int, void*);  // 0x506e0
    bool init();  // 0x50760
    bool requestChargeGetInfo();  // 0x50970
    bool responseChargeGetInfo(void*);  // 0x50c30
    bool expireChargeGetInfo();  // 0x51360
};
