// EndWaitGameWorldJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

struct LobbyJobDef;

class EndWaitGameWorldJob
{
public:
    virtual LobbyJobDef const* GetDefinition() const;  // 0x4afe0
    static void* _vtbl();  // 0x4b040
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x4aff0
    virtual bool work(int, void*);  // 0x4b110
    bool init(int, void*);  // 0x4b150
    bool endWait();  // 0x4b460
};
