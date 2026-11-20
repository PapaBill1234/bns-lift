// AuctionEscrowJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

struct LobbyJobDef;

class AuctionEscrowJob
{
public:
    virtual LobbyJobDef const* GetDefinition() const;  // 0x14cb0
    static void* _vtbl();  // 0x14d10
    virtual ~AuctionEscrowJob();  // 0x14db0
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x14cc0
    virtual bool work(int, void*);  // 0x14e20
    bool escrow(void*);  // 0x14ea0
    bool escrowOk();  // 0x15860
    bool escrowFail(void*);  // 0x15a60
    bool escrowExpire();  // 0x15e80
};
