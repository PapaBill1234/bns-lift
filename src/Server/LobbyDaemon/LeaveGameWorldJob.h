// LeaveGameWorldJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

class GamedChannel;
struct LobbyJobDef;

class LeaveGameWorldJob
{
public:
    virtual LobbyJobDef const* GetDefinition() const;  // 0x877b0
    static void* _vtbl();  // 0x87810
    bool Initialize(GamedChannel*, unsigned long long, unsigned long long);  // 0x878e0
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x877c0
    virtual bool work(int, void*);  // 0x87a00
    bool init();  // 0x87a40
    bool leaveGameWorld();  // 0x87e90
};
