// SecondPasswordIsVerifiedJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

struct LobbyJobDef;

class SecondPasswordIsVerifiedJob
{
public:
    virtual LobbyJobDef const* GetDefinition() const;  // 0x72110
    static void* _vtbl();  // 0x72170
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x72120
    virtual bool work(int, void*);  // 0x72240
    bool init(void*);  // 0x722c0
    bool requestIsVerified();  // 0x72640
    bool responseIsVerified(void*);  // 0x728d0
    bool expireIsVerified();  // 0x72bf0
};
