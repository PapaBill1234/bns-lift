// StopChargeJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

class GamedChannel;
struct LobbyJobDef;

class StopChargeJob
{
public:
    virtual LobbyJobDef const* GetDefinition() const;  // 0x77c90
    static void* _vtbl();  // 0x77cf0
    bool Initialize(GamedChannel*, unsigned long long, unsigned long long, wchar_t*);  // 0x77dc0
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x77ca0
    virtual bool work(int, void*);  // 0x77f50
    bool init();  // 0x77fd0
    bool requestChargeStop();  // 0x78290
    bool responseChargeStop(void*);  // 0x78430
    bool expireChargeStop();  // 0x78790
};
