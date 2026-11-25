// GetLobbyServiceItemJob.obj (LobbyDaemon PDB, 2019 + PDB). Layout from tools/pdbcls.py LobbyDaemon GetLobbyServiceItemJob.
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
class GetLobbyServiceItemJob : public CliSessionJob
{
public:
    enum State
    {
        INIT = 0,
        GET_LOBBY_SERVICE_ITEM = 1,
        FIN = 2
    };

    static void* _vtbl();  // 0x520c0
    GetLobbyServiceItemJob(CliSession* owner, LobbyGateChannel* lgate, unsigned long long itemInstanceId);  // 0x52140
    virtual ~GetLobbyServiceItemJob();  // 0x521e0
    virtual LobbyJobDef const* GetDefinition() const;  // 0x52060
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x52070
    virtual bool work(int, void*);  // 0x52250
    bool init();  // 0x522f0
    bool getLobbyServiceItemReq();  // 0x52620
    bool getLobbyServiceItemOk(void*);  // 0x527b0
    bool getLobbyServiceItemFail(void*);  // 0x529d0
    bool getLobbyServiceItemTimeout();  // 0x52be0

    LobbyGateChannel* _lgate;  // +0x58
    AccountInventoryChannel* _acciv;  // +0x60
    LobbyJobTransaction* _tran;  // +0x68
    unsigned long long _itemInstanceId;  // +0x70

public:
    static ObjPool _pool;
    static LobbyJobDef _def;

    friend struct GetLobbyServiceItemJobLayoutCheck;
};

struct GetLobbyServiceItemJobLayoutCheck
{
    static_assert(sizeof(GetLobbyServiceItemJob) == 0x78, "sizeof GetLobbyServiceItemJob");
    static_assert(offsetof(GetLobbyServiceItemJob, _lgate) == 0x58, "GetLobbyServiceItemJob::_lgate");
    static_assert(offsetof(GetLobbyServiceItemJob, _acciv) == 0x60, "GetLobbyServiceItemJob::_acciv");
    static_assert(offsetof(GetLobbyServiceItemJob, _tran) == 0x68, "GetLobbyServiceItemJob::_tran");
    static_assert(offsetof(GetLobbyServiceItemJob, _itemInstanceId) == 0x70, "GetLobbyServiceItemJob::_itemInstanceId");
};
