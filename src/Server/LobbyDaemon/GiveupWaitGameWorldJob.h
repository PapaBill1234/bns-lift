// GiveupWaitGameWorldJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

class LobbyGateChannel;
struct LobbyJobDef;

class GiveupWaitGameWorldJob
{
public:
    virtual LobbyJobDef const* GetDefinition() const;  // 0x52cf0
    static void* _vtbl();  // 0x52d50
    bool Initialize(LobbyGateChannel*);  // 0x52e20
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x52d00
    virtual bool work(int, void*);  // 0x52f30
    bool init();  // 0x52f70
    bool giveupWait();  // 0x530d0
};
