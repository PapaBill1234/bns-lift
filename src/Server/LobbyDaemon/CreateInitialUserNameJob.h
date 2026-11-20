// CreateInitialUserNameJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

struct LobbyJobDef;

class CreateInitialUserNameJob
{
public:
    virtual LobbyJobDef const* GetDefinition() const;  // 0x2fc20
    static void* _vtbl();  // 0x2fc80
    virtual ~CreateInitialUserNameJob();  // 0x2fd20
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x2fc30
    virtual bool work(int, void*);  // 0x2fda0
    bool init(void*);  // 0x2fe20
    bool changeUserNameReq();  // 0x30660
    bool changeUserNameAck(void*);  // 0x30980
    bool changeUserNameExpire();  // 0x30d90
};
