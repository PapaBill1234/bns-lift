// SecondPasswordGetStatusJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

struct LobbyJobDef;

class SecondPasswordGetStatusJob
{
public:
    virtual LobbyJobDef const* GetDefinition() const;  // 0x71550
    static void* _vtbl();  // 0x715b0
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x71560
    virtual bool work(int, void*);  // 0x71680
    bool init(void*);  // 0x71700
    bool requestGetStatus();  // 0x71a60
    bool responseGetStatus(void*);  // 0x71ce0
    bool expireGetStatus();  // 0x72010
};
