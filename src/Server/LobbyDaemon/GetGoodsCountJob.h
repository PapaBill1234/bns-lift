// GetGoodsCountJob.obj (LobbyDaemon PDB, 2019 + PDB). Layout from tools/pdbcls.py LobbyDaemon GetGoodsCountJob.
#pragma once
#include <stddef.h>
#include "CliSessionJob.h"

class AccountInventoryChannel;
class CliSession;
class LobbyGateChannel;
class LobbyJobTransaction;
class ObjPool;
struct LobbyJobDef;

// PDB layout (sizeof 0x70, CliSessionJob base). The PDB also has Initialize(LobbyGateChannel*). The binary has no
// body for it. It is not declared here.
class GetGoodsCountJob : public CliSessionJob
{
public:
    enum State
    {
        INIT = 0,
        GET_GOODS_COUNT = 1,
        FIN = 2
    };

    static void* _vtbl();  // 0x514c0
    GetGoodsCountJob(CliSession* owner, LobbyGateChannel* lgate);  // 0x51540
    virtual ~GetGoodsCountJob();  // 0x515d0
    virtual LobbyJobDef const* GetDefinition() const;  // 0x51460
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x51470
    virtual bool work(int, void*);  // 0x51640
    bool init();  // 0x516e0
    bool getGoodsCountReq();  // 0x51a00
    bool getGoodsCountOk(void*);  // 0x51b80
    bool getGoodsCountFail(void*);  // 0x51d60
    bool getGoodsCountTimeout();  // 0x51f60

    LobbyGateChannel* _lgate;  // +0x58
    AccountInventoryChannel* _acciv;  // +0x60
    LobbyJobTransaction* _tran;  // +0x68

public:
    static ObjPool _pool;
    static LobbyJobDef _def;

    friend struct GetGoodsCountJobLayoutCheck;
};

struct GetGoodsCountJobLayoutCheck
{
    static_assert(sizeof(GetGoodsCountJob) == 0x70, "sizeof GetGoodsCountJob");
    static_assert(offsetof(GetGoodsCountJob, _lgate) == 0x58, "GetGoodsCountJob::_lgate");
    static_assert(offsetof(GetGoodsCountJob, _acciv) == 0x60, "GetGoodsCountJob::_acciv");
    static_assert(offsetof(GetGoodsCountJob, _tran) == 0x68, "GetGoodsCountJob::_tran");
};
