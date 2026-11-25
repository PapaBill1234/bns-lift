// ListLobbyServiceItemJob.obj (LobbyDaemon PDB, 2019 + PDB). Layout from tools/pdbcls.py LobbyDaemon ListLobbyServiceItemJob.
#pragma once
#include <stddef.h>
#include "CliSessionJob.h"

class AccountInventoryChannel;
class CliSession;
class LobbyGateChannel;
class LobbyJobTransaction;
class ObjPool;
struct LobbyJobDef;

// PDB layout (sizeof 0x80, CliSessionJob base). The PDB also has Initialize(LobbyGateChannel*). The binary has no
// body for it. It is not declared here.
class ListLobbyServiceItemJob : public CliSessionJob
{
public:
    enum State
    {
        INIT = 0,
        LIST_LOBBY_SERVICE_ITEM = 1,
        FIN = 2
    };

    static void* _vtbl();  // 0x55b80
    ListLobbyServiceItemJob(CliSession* owner, LobbyGateChannel* lgate, char searchType, unsigned long long searchKey);  // 0x55c00
    virtual ~ListLobbyServiceItemJob();  // 0x55cb0
    virtual LobbyJobDef const* GetDefinition() const;  // 0x55b20
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x55b30
    virtual bool work(int, void*);  // 0x55d20
    bool init();  // 0x55dc0
    bool listLobbyServiceItemReq();  // 0x560f0
    bool listLobbyServiceItemOk(void*);  // 0x56280
    bool listLobbyServiceItemFail(void*);  // 0x56490
    bool listLobbyServiceItemTimeout();  // 0x56670

    LobbyGateChannel* _lgate;  // +0x58
    AccountInventoryChannel* _acciv;  // +0x60
    LobbyJobTransaction* _tran;  // +0x68
    char _searchType;  // +0x70
    unsigned long long _searchKey;  // +0x78

public:
    static ObjPool _pool;
    static LobbyJobDef _def;

    friend struct ListLobbyServiceItemJobLayoutCheck;
};

struct ListLobbyServiceItemJobLayoutCheck
{
    static_assert(sizeof(ListLobbyServiceItemJob) == 0x80, "sizeof ListLobbyServiceItemJob");
    static_assert(offsetof(ListLobbyServiceItemJob, _lgate) == 0x58, "ListLobbyServiceItemJob::_lgate");
    static_assert(offsetof(ListLobbyServiceItemJob, _acciv) == 0x60, "ListLobbyServiceItemJob::_acciv");
    static_assert(offsetof(ListLobbyServiceItemJob, _tran) == 0x68, "ListLobbyServiceItemJob::_tran");
    static_assert(offsetof(ListLobbyServiceItemJob, _searchType) == 0x70, "ListLobbyServiceItemJob::_searchType");
    static_assert(offsetof(ListLobbyServiceItemJob, _searchKey) == 0x78, "ListLobbyServiceItemJob::_searchKey");
};
