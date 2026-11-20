// LogoutInGameWorldJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

struct LobbyJobDef;

class LogoutInGameWorldJob
{
public:
    virtual LobbyJobDef const* GetDefinition() const;  // 0x5aa80
    static void* _vtbl();  // 0x5aae0
    bool Initialize(short);  // 0x5ab90
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x5aa90
    virtual bool work(int, void*);  // 0x5ac80
    bool init();  // 0x5acc0
    bool logout();  // 0x5af30
};
