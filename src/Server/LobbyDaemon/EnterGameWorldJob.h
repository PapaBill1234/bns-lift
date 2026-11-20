// EnterGameWorldJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

class GamedChannel;
struct LobbyJobDef;

class EnterGameWorldJob
{
public:
    virtual LobbyJobDef const* GetDefinition() const;  // 0x84e00
    static void* _vtbl();  // 0x84e60
    bool Initialize(GamedChannel*, unsigned long long, unsigned long long);  // 0x84f30
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x84e10
    virtual bool work(int, void*);  // 0x85080
    bool init();  // 0x850c0
    bool enterGameWorld();  // 0x85240
};
