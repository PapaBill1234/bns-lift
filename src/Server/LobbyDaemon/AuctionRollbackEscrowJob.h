// AuctionRollbackEscrowJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

struct LobbyJobDef;

class AuctionRollbackEscrowJob
{
public:
    virtual LobbyJobDef const* GetDefinition() const;  // 0x15fa0
    AuctionRollbackEscrowJob();  // 0x16000
    virtual ~AuctionRollbackEscrowJob();  // 0x16090
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x15fb0
    virtual bool work(int, void*);  // 0x16100
    bool rollbackEscrow(void*);  // 0x16190
    bool registerPostOk(void*);  // 0x167c0
    bool registerPostFail(void*);  // 0x16a80
    bool registerPostExpire();  // 0x16d70
};
