// AuctionRollbackEscrowJob.obj (LobbyDaemon PDB, 2019 + PDB). Layouts from tools/pdbcls.py LobbyDaemon <Class>.
// LIFT: header layouts only (fix7). The function bodies are still LIFT_STUB.
#pragma once
#include <stddef.h>
#include "LobbyJob.h"

class LobbyJobTransaction;
class ObjPool;
class PostOfficeChannel;
struct LobbyJobDef;

// LIFT: PDB layout (sizeof 0x78, LobbyJob base). Layout from tools/pdbcls.py LobbyDaemon AuctionRollbackEscrowJob.
class AuctionRollbackEscrowJob : public LobbyJob
{
public:
    enum State
    {
        TRY_ROLLBACK_ESCROW = 0,
        FIN_ROLLBACK_ESCROW = 1,
        FIN = 2,
    };

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

private:
    friend struct AuctionRollbackEscrowJobLayoutCheck;  // LIFT: checks the private PDB offsets.

    LobbyJobTransaction* _tran;  // +0x50
    PostOfficeChannel* _postoffice;  // +0x58
    int _txnId;  // +0x60
    unsigned long long _escrowId;  // +0x68
    unsigned long long _deliveryId;  // +0x70

public:
    static ObjPool _pool;  // .data 0x203bd0
    static void* _vtbl();  // LIFT: PDB declares it; no RVA (inlined in LobbyDaemon::initialize 0x9b300)
    static LobbyJobDef _def;
};
static_assert(sizeof(AuctionRollbackEscrowJob) == 0x78, "sizeof AuctionRollbackEscrowJob");
struct AuctionRollbackEscrowJobLayoutCheck
{
    static_assert(offsetof(AuctionRollbackEscrowJob, _tran) == 0x50, "AuctionRollbackEscrowJob::_tran");
    static_assert(offsetof(AuctionRollbackEscrowJob, _postoffice) == 0x58, "AuctionRollbackEscrowJob::_postoffice");
    static_assert(offsetof(AuctionRollbackEscrowJob, _txnId) == 0x60, "AuctionRollbackEscrowJob::_txnId");
    static_assert(offsetof(AuctionRollbackEscrowJob, _escrowId) == 0x68, "AuctionRollbackEscrowJob::_escrowId");
    static_assert(offsetof(AuctionRollbackEscrowJob, _deliveryId) == 0x70, "AuctionRollbackEscrowJob::_deliveryId");
};
