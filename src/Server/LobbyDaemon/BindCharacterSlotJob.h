// BindCharacterSlotJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

struct LobbyJobDef;

class BindCharacterSlotJob
{
public:
    virtual LobbyJobDef const* GetDefinition() const;  // 0x16e90
    static void* _vtbl();  // 0x16ef0
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x16ea0
    virtual bool work(int, void*);  // 0x16fc0
    bool init(void*);  // 0x17050
    bool reqGetSlot();  // 0x17840
    bool responseGetSlot(void*);  // 0x179e0
    bool expireGetSlot();  // 0x17ff0
    bool bindCharacterSlot();  // 0x18100
};
