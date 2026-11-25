// AuctionEscrowJob.obj (LobbyDaemon PDB, 2019 + PDB). Layouts from tools/pdbcls.py LobbyDaemon <Class>.
// LIFT: header layouts only (fix7). The function bodies are still LIFT_STUB.
#pragma once
#include <stddef.h>
#include "CliSessionJob.h"

class GamedChannel;
class LobbyJobTransaction;
class ObjPool;
struct LobbyJobDef;

// LIFT: PDB layout (sizeof 0x80, CliSessionJob base). Layout from tools/pdbcls.py LobbyDaemon AuctionEscrowJob.
class AuctionEscrowJob : public CliSessionJob
{
public:
    enum State
    {
        TRY_ESCROW = 0,
        FIN_ESCROW = 1,
        FIN = 2,
    };

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

private:
    friend struct AuctionEscrowJobLayoutCheck;  // LIFT: checks the private PDB offsets.

    LobbyJobTransaction* _tran;  // +0x58
    int _txnId;  // +0x60
    unsigned long long _escrowId;  // +0x68
    unsigned long long _pcid;  // +0x70
    GamedChannel* _gamed;  // +0x78

public:
    static ObjPool _pool;
    static LobbyJobDef _def;
};
static_assert(sizeof(AuctionEscrowJob) == 0x80, "sizeof AuctionEscrowJob");
struct AuctionEscrowJobLayoutCheck
{
    static_assert(offsetof(AuctionEscrowJob, _tran) == 0x58, "AuctionEscrowJob::_tran");
    static_assert(offsetof(AuctionEscrowJob, _txnId) == 0x60, "AuctionEscrowJob::_txnId");
    static_assert(offsetof(AuctionEscrowJob, _escrowId) == 0x68, "AuctionEscrowJob::_escrowId");
    static_assert(offsetof(AuctionEscrowJob, _pcid) == 0x70, "AuctionEscrowJob::_pcid");
    static_assert(offsetof(AuctionEscrowJob, _gamed) == 0x78, "AuctionEscrowJob::_gamed");
};
