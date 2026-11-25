// ChangeUserNameJob.obj (LobbyDaemon PDB, 2019 + PDB). Layout from tools/pdbcls.py LobbyDaemon ChangeUserNameJob.
#pragma once
#include <stddef.h>
#include "CliSessionJob.h"

class AccountInventoryChannel;
class CliSession;
class LobbyGateChannel;
class LobbyJobTransaction;
class ObjPool;
struct LobbyJobDef;

// PDB layout (sizeof 0x110, CliSessionJob base).
class ChangeUserNameJob : public CliSessionJob
{
public:
    enum State
    {
        INIT = 0,
        CHECK_ACCOUNT_INVENTORY_ITEM = 1,
        CHANGE_USER_NAME = 2,
        CONSUME_LOBBY_SERVICE_ITEM = 3,
        FIN_LOBBY_SERVICE = 4,
        FIN = 5
    };

    virtual LobbyJobDef const* GetDefinition() const;  // 0x26990
    static void* _vtbl();  // 0x269f0
    ChangeUserNameJob(CliSession*);  // 0x26a70
    virtual ~ChangeUserNameJob();  // 0x26ae0
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x269a0
    virtual bool work(int, void*);  // 0x26b50
    bool init(void*);  // 0x26c80
    bool checkAccountInventoryItem();  // 0x275f0
    bool checkAccountInventoryItemOk(void*);  // 0x27790
    bool checkAccountInventoryItemFail(void*);  // 0x27bc0
    bool checkAccountInventoryItemTimeout();  // 0x27e50
    bool changeUserName();  // 0x27f70
    bool changeUserNameResponse(void*);  // 0x28580
    bool changeUserNameExpire();  // 0x28a80
    bool consumeLobbyServiceItem();  // 0x28bd0
    bool consumeLobbyServiceItemOk(void*);  // 0x28dc0
    bool consumeLobbyServiceItemFail(void*);  // 0x28ed0
    bool consumeLobbyServiceItemTimeout();  // 0x291f0
    bool finLobbyService();  // 0x29350
    void releaseService();  // 0x29630

    LobbyJobTransaction* _tran;  // +0x58
    LobbyGateChannel* _lgate;  // +0x60
    AccountInventoryChannel* _acciv;  // +0x68
    wchar_t _newUserName[65];  // +0x70
    unsigned long long _labelId;  // +0xF8
    unsigned long long _itemInstanceId;  // +0x100
    unsigned int _itemDataId;  // +0x108

public:
    static ObjPool _pool;
    static LobbyJobDef _def;

    friend struct ChangeUserNameJobLayoutCheck;
};

struct ChangeUserNameJobLayoutCheck
{
    static_assert(sizeof(ChangeUserNameJob) == 0x110, "sizeof ChangeUserNameJob");
    static_assert(offsetof(ChangeUserNameJob, _tran) == 0x58, "ChangeUserNameJob::_tran");
    static_assert(offsetof(ChangeUserNameJob, _acciv) == 0x68, "ChangeUserNameJob::_acciv");
    static_assert(offsetof(ChangeUserNameJob, _newUserName) == 0x70, "ChangeUserNameJob::_newUserName");
    static_assert(offsetof(ChangeUserNameJob, _labelId) == 0xF8, "ChangeUserNameJob::_labelId");
    static_assert(offsetof(ChangeUserNameJob, _itemDataId) == 0x108, "ChangeUserNameJob::_itemDataId");
};
