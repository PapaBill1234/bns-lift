// TakeGoodsJob.obj (LobbyDaemon PDB, 2019 + PDB). Layout from tools/pdbcls.py LobbyDaemon TakeGoodsJob.
#pragma once
#include <stddef.h>
#include "CliSessionJob.h"

class AccountInventoryChannel;
class CliSession;
class LobbyGateChannel;
class LobbyJobTransaction;
class ObjPool;
struct LobbyJobDef;

// PDB layout (sizeof 0x78, CliSessionJob base). The PDB also has Initialize(LobbyGateChannel*). The binary has no
// body for it. It is not declared here.
class TakeGoodsJob : public CliSessionJob
{
public:
    enum State
    {
        INIT = 0,
        TAKE_GOODS = 1,
        FIN = 2
    };

    static void* _vtbl();  // 0x79f60
    TakeGoodsJob(CliSession* owner, LobbyGateChannel* lgate, unsigned long long goodsId);  // 0x79fe0
    virtual ~TakeGoodsJob();  // 0x7a080
    virtual LobbyJobDef const* GetDefinition() const;  // 0x79f00
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x79f10
    virtual bool work(int, void*);  // 0x7a0f0
    bool init();  // 0x7a190
    bool takeGoodsReq();  // 0x7a540
    bool takeGoodsOk(void*);  // 0x7a6d0
    bool takeGoodsFail(void*);  // 0x7a8d0
    bool takeGoodsTimeout();  // 0x7ab30

    LobbyGateChannel* _lgate;  // +0x58
    AccountInventoryChannel* _acciv;  // +0x60
    LobbyJobTransaction* _tran;  // +0x68
    unsigned long long _goodsId;  // +0x70

public:
    static ObjPool _pool;
    static LobbyJobDef _def;

    friend struct TakeGoodsJobLayoutCheck;
};

struct TakeGoodsJobLayoutCheck
{
    static_assert(sizeof(TakeGoodsJob) == 0x78, "sizeof TakeGoodsJob");
    static_assert(offsetof(TakeGoodsJob, _lgate) == 0x58, "TakeGoodsJob::_lgate");
    static_assert(offsetof(TakeGoodsJob, _acciv) == 0x60, "TakeGoodsJob::_acciv");
    static_assert(offsetof(TakeGoodsJob, _tran) == 0x68, "TakeGoodsJob::_tran");
    static_assert(offsetof(TakeGoodsJob, _goodsId) == 0x70, "TakeGoodsJob::_goodsId");
};
