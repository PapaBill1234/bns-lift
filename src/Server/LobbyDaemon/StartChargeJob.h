// StartChargeJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

class GamedChannel;
struct LobbyJobDef;

class StartChargeJob
{
public:
    virtual LobbyJobDef const* GetDefinition() const;  // 0x75570
    static void* _vtbl();  // 0x755d0
    bool Initialize(GamedChannel*, unsigned long long, unsigned long long);  // 0x756a0
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x75580
    virtual bool work(int, void*);  // 0x757b0
    bool init();  // 0x75830
    bool requestStartCharge();  // 0x75a60
    bool responseStartCharge(void*);  // 0x75c10
    bool expireStartCharge();  // 0x76150
};
