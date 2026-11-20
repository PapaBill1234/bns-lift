// AbandonChargeJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

struct LobbyJobDef;

class AbandonChargeJob
{
public:
    virtual LobbyJobDef const* GetDefinition() const;  // 0x4f70
    static void* _vtbl();  // 0x5020
    bool Initialize(unsigned long long, wchar_t const*);  // 0x50d0
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x4f80
    virtual bool work(int, void*);  // 0x5220
    bool init();  // 0x52a0
    bool requestChargeAbandon();  // 0x54a0
    bool responseChargeAbandon(void*);  // 0x5690
    bool expireChargeAbandon();  // 0x5b10
};
