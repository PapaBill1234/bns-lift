// ChangeCharacterAppearanceJob.obj (LobbyDaemon PDB, 2019 + PDB). Layouts from tools/pdbcls.py LobbyDaemon <Class>.
// LIFT: header layouts only (fix7). The function bodies are still LIFT_STUB.
#pragma once
#include <stddef.h>
#include "CliSessionJob.h"
#include "StringUtil.h"

class AccountInventoryChannel;
class GamedChannel;
class LobbyGateChannel;
class LobbyJobTransaction;
class ObjPool;
class CliSession;
struct LobbyJobDef;

// LIFT: PDB layout (sizeof 0xb0, CliSessionJob base). Layout from tools/pdbcls.py LobbyDaemon ChangeCharacterAppearanceJob.
class ChangeCharacterAppearanceJob : public CliSessionJob
{
public:
    enum State
    {
        INIT = 0,
        CHECK_ACCOUNT_INVENTORY_ITEM = 1,
        REGISTER_SERVICE_ENTRY = 2,
        TRY_CONSUME_ACCOUNT_INVENTORY_ITEM = 3,
        CHANGE_APPEARANCE = 4,
        FIN_CONSUME_ACCOUNT_INVENTORY_ITEM = 5,
        FIN_SERVICE_ENTRY = 6,
        FIN = 7,
    };

    virtual LobbyJobDef const* GetDefinition() const;  // 0x1ab60
    ChangeCharacterAppearanceJob(CliSession*);  // 0x1abc0
    virtual ~ChangeCharacterAppearanceJob();  // 0x1ac50
    bool Initialize(LobbyGateChannel*);  // LIFT: PDB method; no own symbol in the lift scope.
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x1ab70
    virtual bool work(int, void*);  // 0x1ad00
    bool init(void*);  // 0x1aea0
    bool checkAccountInventoryItem();  // 0x1bae0
    bool checkAccountInventoryItemOk(void*);  // 0x1bc90
    bool checkAccountInventoryItemFail(void*);  // 0x1c100
    bool checkAccountInventoryItemTimeout();  // 0x1c370
    bool registerServiceEntry();  // 0x1c490
    bool tryConsumeAccountInventoryItem();  // 0x1cad0
    bool tryConsumeAccountInventoryItemOk(void*);  // 0x1cc90
    bool tryConsumeAccountInventoryItemFail(void*);  // 0x1cf70
    bool tryConsumeAccountInventoryItemTimeout();  // 0x1d1d0
    bool changeCharacterAppearance();  // 0x1d300
    bool changeCharacterAppearanceOk(void*);  // 0x1d540
    bool changeCharacterAppearanceFail(void*);  // 0x1dad0
    bool changeCharacterAppearanceTimeout();  // 0x1dd30
    bool finConsumeAccountInventoryItem();  // 0x1de60
    bool finConsumeAccountInventoryItemOk(void*);  // 0x1e020
    bool finConsumeAccountInventoryItemFail(void*);  // 0x1e2f0
    bool finConsumeAccountInventoryItemTimeout();  // 0x1e550
    bool finServiceEntry();  // 0x1e680
    bool releasePcServiceStatus();  // 0x229a0

private:
    friend struct ChangeCharacterAppearanceJobLayoutCheck;  // LIFT: checks the private PDB offsets.

    LobbyJobTransaction* _tran;  // +0x58
    LobbyGateChannel* _lgate;  // +0x60
    AccountInventoryChannel* _acciv;  // +0x68
    GamedChannel* _gamed;  // +0x70
    id128 _slotid;  // +0x78
    unsigned long long _labelId;  // +0x88
    unsigned long long _itemInstanceId;  // +0x90
    char* _makingData;  // +0x98
    int _makingDataSize;  // +0xa0
    unsigned int _itemDataId;  // +0xa4
    unsigned long long _serviceId;  // +0xa8

public:
    static ObjPool _pool;
    static LobbyJobDef _def;
};
static_assert(sizeof(ChangeCharacterAppearanceJob) == 0xb0, "sizeof ChangeCharacterAppearanceJob");
struct ChangeCharacterAppearanceJobLayoutCheck
{
    static_assert(offsetof(ChangeCharacterAppearanceJob, _tran) == 0x58, "ChangeCharacterAppearanceJob::_tran");
    static_assert(offsetof(ChangeCharacterAppearanceJob, _lgate) == 0x60, "ChangeCharacterAppearanceJob::_lgate");
    static_assert(offsetof(ChangeCharacterAppearanceJob, _acciv) == 0x68, "ChangeCharacterAppearanceJob::_acciv");
    static_assert(offsetof(ChangeCharacterAppearanceJob, _gamed) == 0x70, "ChangeCharacterAppearanceJob::_gamed");
    static_assert(offsetof(ChangeCharacterAppearanceJob, _slotid) == 0x78, "ChangeCharacterAppearanceJob::_slotid");
    static_assert(offsetof(ChangeCharacterAppearanceJob, _labelId) == 0x88, "ChangeCharacterAppearanceJob::_labelId");
    static_assert(offsetof(ChangeCharacterAppearanceJob, _itemInstanceId) == 0x90, "ChangeCharacterAppearanceJob::_itemInstanceId");
    static_assert(offsetof(ChangeCharacterAppearanceJob, _makingData) == 0x98, "ChangeCharacterAppearanceJob::_makingData");
    static_assert(offsetof(ChangeCharacterAppearanceJob, _makingDataSize) == 0xa0, "ChangeCharacterAppearanceJob::_makingDataSize");
    static_assert(offsetof(ChangeCharacterAppearanceJob, _itemDataId) == 0xa4, "ChangeCharacterAppearanceJob::_itemDataId");
    static_assert(offsetof(ChangeCharacterAppearanceJob, _serviceId) == 0xa8, "ChangeCharacterAppearanceJob::_serviceId");
};
