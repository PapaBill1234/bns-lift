// AuctionDeliverJob.obj (LobbyDaemon PDB, 2019 + PDB). Layouts from tools/pdbcls.py LobbyDaemon <Class>.
// LIFT: header layouts only (fix7). The function bodies are still LIFT_STUB.
#pragma once
#include <stddef.h>
#include "LobbyJob.h"
#include "RefCntPoolObj.h"

class LobbyJobTransaction;
class ObjPool;
class PostOfficeChannel;
struct LobbyJobDef;

// LIFT: PDB layout (sizeof 0xd8, LobbyJob base). Layout from tools/pdbcls.py LobbyDaemon AuctionDeliverJob.
class AuctionDeliverJob : public LobbyJob
{
public:
    enum State
    {
        INIT = 0,
        WAIT_POST = 1,
        FIN = 2,
    };

    virtual LobbyJobDef const* GetDefinition() const;  // 0x12300
    AuctionDeliverJob();  // 0x12360
    virtual ~AuctionDeliverJob();  // 0x123f0
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x12310
    virtual bool work(int, void*);  // 0x12460
    bool init(void*);  // 0x124f0
    bool registerPostOk(void*);  // 0x12f30
    bool registerPostFail(void*);  // 0x13230
    bool registerPostTimeout();  // 0x13520

private:
    friend struct AuctionDeliverJobLayoutCheck;  // LIFT: checks the private PDB offsets.

    LobbyJobTransaction* _tran;  // +0x50
    PostOfficeChannel* _postoffice;  // +0x58
    int _txnId;  // +0x60
    wchar_t _requestId[51];  // +0x64
    unsigned long long _deliveryId;  // +0xd0

public:
    static ObjPool _pool;  // .data 0x203a70
    static void* _vtbl();  // LIFT: PDB declares it; no RVA (inlined in LobbyDaemon::initialize 0x9b300)
    static LobbyJobDef _def;
};
static_assert(sizeof(AuctionDeliverJob) == 0xd8, "sizeof AuctionDeliverJob");
struct AuctionDeliverJobLayoutCheck
{
    static_assert(offsetof(AuctionDeliverJob, _tran) == 0x50, "AuctionDeliverJob::_tran");
    static_assert(offsetof(AuctionDeliverJob, _postoffice) == 0x58, "AuctionDeliverJob::_postoffice");
    static_assert(offsetof(AuctionDeliverJob, _txnId) == 0x60, "AuctionDeliverJob::_txnId");
    static_assert(offsetof(AuctionDeliverJob, _requestId) == 0x64, "AuctionDeliverJob::_requestId");
    static_assert(offsetof(AuctionDeliverJob, _deliveryId) == 0xd0, "AuctionDeliverJob::_deliveryId");
};

