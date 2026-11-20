// InitCliSessionWlobbyTokenJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

class LobbyGateChannel;
struct LobbyJobDef;

class InitCliSessionWlobbyTokenJob
{
public:
    virtual LobbyJobDef const* GetDefinition() const;  // 0x54830
    static void* _vtbl();  // 0x54890
    bool Initialize(LobbyGateChannel*, unsigned long long);  // 0x54960
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x54840
    virtual bool work(int, void*);  // 0x54aa0
    bool init();  // 0x54ae0
    bool initOk();  // 0x54c40
};
