// ListGoodsJob.obj (LobbyDaemon PDB, 2019 + PDB). Layout from tools/pdbcls.py LobbyDaemon ListGoodsJob.
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
class ListGoodsJob : public CliSessionJob
{
public:
    enum State
    {
        INIT = 0,
        LIST_GOODS = 1,
        FIN = 2
    };

    static void* _vtbl();  // 0x54f40
    ListGoodsJob(CliSession* owner, LobbyGateChannel* lgate);  // 0x54fc0
    virtual ~ListGoodsJob();  // 0x55050
    virtual LobbyJobDef const* GetDefinition() const;  // 0x54ee0
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x54ef0
    virtual bool work(int, void*);  // 0x550c0
    bool init(void*);  // 0x55160
    bool listGoodsReq();  // 0x55490
    bool listGoodsOk(void*);  // 0x55620
    bool listGoodsFail(void*);  // 0x55820
    bool listGoodsTimeout();  // 0x55a20

    char _languageCode;  // +0x58
    LobbyGateChannel* _lgate;  // +0x60
    AccountInventoryChannel* _acciv;  // +0x68
    LobbyJobTransaction* _tran;  // +0x70

public:
    static ObjPool _pool;
    static LobbyJobDef _def;

    friend struct ListGoodsJobLayoutCheck;
};

struct ListGoodsJobLayoutCheck
{
    static_assert(sizeof(ListGoodsJob) == 0x78, "sizeof ListGoodsJob");
    static_assert(offsetof(ListGoodsJob, _languageCode) == 0x58, "ListGoodsJob::_languageCode");
    static_assert(offsetof(ListGoodsJob, _lgate) == 0x60, "ListGoodsJob::_lgate");
    static_assert(offsetof(ListGoodsJob, _acciv) == 0x68, "ListGoodsJob::_acciv");
    static_assert(offsetof(ListGoodsJob, _tran) == 0x70, "ListGoodsJob::_tran");
};
