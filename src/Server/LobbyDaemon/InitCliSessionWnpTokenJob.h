// InitCliSessionWnpTokenJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

struct LobbyJobDef;

class InitCliSessionWnpTokenJob
{
public:
    virtual LobbyJobDef const* GetDefinition() const;  // 0x3c080
    static void* _vtbl();  // 0x98120
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x3c090
    virtual bool work(int, void*);  // 0x981a0
    bool init(int, void*);  // 0x981c0
};
