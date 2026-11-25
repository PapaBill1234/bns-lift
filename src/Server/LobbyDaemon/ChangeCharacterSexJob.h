// ChangeCharacterSexJob.obj (LobbyDaemon PDB, 2019 + PDB). Layouts from tools/pdbcls.py LobbyDaemon <Class>.
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

// PDB ChangeCharacterSexWithAccountInventoryItemReqParam (sizeof 0x138). The lobby-gate handler fills it. init reads it.
struct ChangeCharacterSexWithAccountInventoryItemReqParam
{
    LobbyGateChannel* lgate;
    id128 slotid;
    char newSex;
    char makingData[256];
    short makingDataSize;
    unsigned long long labelId;
    unsigned long long itemInstanceId;
    unsigned int itemDataId;
};
static_assert(sizeof(ChangeCharacterSexWithAccountInventoryItemReqParam) == 0x138, "sizeof ChangeCharacterSexWithAccountInventoryItemReqParam");
static_assert(offsetof(ChangeCharacterSexWithAccountInventoryItemReqParam, slotid) == 0x8, "ChangeCharacterSexWithAccountInventoryItemReqParam::slotid");
static_assert(offsetof(ChangeCharacterSexWithAccountInventoryItemReqParam, newSex) == 0x18, "ChangeCharacterSexWithAccountInventoryItemReqParam::newSex");
static_assert(offsetof(ChangeCharacterSexWithAccountInventoryItemReqParam, makingData) == 0x19, "ChangeCharacterSexWithAccountInventoryItemReqParam::makingData");
static_assert(offsetof(ChangeCharacterSexWithAccountInventoryItemReqParam, makingDataSize) == 0x11a, "ChangeCharacterSexWithAccountInventoryItemReqParam::makingDataSize");
static_assert(offsetof(ChangeCharacterSexWithAccountInventoryItemReqParam, labelId) == 0x120, "ChangeCharacterSexWithAccountInventoryItemReqParam::labelId");
static_assert(offsetof(ChangeCharacterSexWithAccountInventoryItemReqParam, itemInstanceId) == 0x128, "ChangeCharacterSexWithAccountInventoryItemReqParam::itemInstanceId");
static_assert(offsetof(ChangeCharacterSexWithAccountInventoryItemReqParam, itemDataId) == 0x130, "ChangeCharacterSexWithAccountInventoryItemReqParam::itemDataId");

// PDB ChangeCharacterSexOkParam (sizeof 0x10). The gamed handler fills it. changeCharacterSexOk reads it.
struct ChangeCharacterSexOkParam
{
    char* showcaseData;
    short showcaseDataSize;
};
static_assert(sizeof(ChangeCharacterSexOkParam) == 0x10, "sizeof ChangeCharacterSexOkParam");
static_assert(offsetof(ChangeCharacterSexOkParam, showcaseDataSize) == 0x8, "ChangeCharacterSexOkParam::showcaseDataSize");

// LIFT: PDB layout (sizeof 0xb8, CliSessionJob base). Layout from tools/pdbcls.py LobbyDaemon ChangeCharacterSexJob.
class ChangeCharacterSexJob : public CliSessionJob
{
public:
    enum State
    {
        INIT = 0,
        CHECK_ACCOUNT_INVENTORY_ITEM = 1,
        REGISTER_SERVICE_ENTRY = 2,
        TRY_CONSUME_ACCOUNT_INVENTORY_ITEM = 3,
        CHANGE_CHARACTER_SEX = 4,
        FIN_CONSUME_ACCOUNT_INVENTORY_ITEM = 5,
        FIN_SERVICE_ENTRY = 6,
        FIN = 7,
    };

    virtual LobbyJobDef const* GetDefinition() const;  // 0x22a60
    ChangeCharacterSexJob(CliSession*);  // 0x22ac0
    virtual ~ChangeCharacterSexJob();  // 0x22b60
    bool Initialize(LobbyGateChannel*);  // LIFT: PDB method; no own symbol in the lift scope.
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x22a70
    virtual bool work(int, void*);  // 0x22c10
    bool init(void*);  // 0x22db0
    bool checkAccountInventoryItem();  // 0x23a10
    bool checkAccountInventoryItemOk(void*);  // 0x23bc0
    bool checkAccountInventoryItemFail(void*);  // 0x24030
    bool checkAccountInventoryItemTimeout();  // 0x242a0
    bool registerServiceEntry();  // 0x243c0
    bool tryConsumeAccountInventoryItem();  // 0x24a10
    bool tryConsumeAccountInventoryItemOk(void*);  // 0x24bd0
    bool tryConsumeAccountInventoryItemFail(void*);  // 0x24eb0
    bool tryConsumeAccountInventoryItemTimeout();  // 0x25110
    bool changeCharacterSex();  // 0x25240
    bool changeCharacterSexOk(void*);  // 0x25490
    bool changeCharacterSexFail(void*);  // 0x25a20
    bool changeCharacterSexTimeout();  // 0x25c80
    bool finConsumeAccountInventoryItem();  // 0x25db0
    bool finConsumeAccountInventoryItemOk(void*);  // 0x25f70
    bool finConsumeAccountInventoryItemFail(void*);  // 0x26240
    bool finConsumeAccountInventoryItemTimeout();  // 0x264a0
    bool finServiceEntry();  // 0x265d0
    bool releasePcServiceStatus();  // 0x229a0 (ICF with the Race and Appearance copies)

private:
    friend struct ChangeCharacterSexJobLayoutCheck;  // LIFT: checks the private PDB offsets.

    LobbyJobTransaction* _tran;  // +0x58
    LobbyGateChannel* _lgate;  // +0x60
    AccountInventoryChannel* _acciv;  // +0x68
    GamedChannel* _gamed;  // +0x70
    id128 _slotid;  // +0x78
    unsigned long long _labelId;  // +0x88
    unsigned long long _itemInstanceId;  // +0x90
    char _newSex;  // +0x98
    char* _makingData;  // +0xa0
    int _makingDataSize;  // +0xa8
    unsigned int _itemDataId;  // +0xac
    unsigned long long _serviceId;  // +0xb0

public:
    static ObjPool _pool;
    static LobbyJobDef _def;
};
static_assert(sizeof(ChangeCharacterSexJob) == 0xb8, "sizeof ChangeCharacterSexJob");
struct ChangeCharacterSexJobLayoutCheck
{
    static_assert(offsetof(ChangeCharacterSexJob, _tran) == 0x58, "ChangeCharacterSexJob::_tran");
    static_assert(offsetof(ChangeCharacterSexJob, _lgate) == 0x60, "ChangeCharacterSexJob::_lgate");
    static_assert(offsetof(ChangeCharacterSexJob, _acciv) == 0x68, "ChangeCharacterSexJob::_acciv");
    static_assert(offsetof(ChangeCharacterSexJob, _gamed) == 0x70, "ChangeCharacterSexJob::_gamed");
    static_assert(offsetof(ChangeCharacterSexJob, _slotid) == 0x78, "ChangeCharacterSexJob::_slotid");
    static_assert(offsetof(ChangeCharacterSexJob, _labelId) == 0x88, "ChangeCharacterSexJob::_labelId");
    static_assert(offsetof(ChangeCharacterSexJob, _itemInstanceId) == 0x90, "ChangeCharacterSexJob::_itemInstanceId");
    static_assert(offsetof(ChangeCharacterSexJob, _newSex) == 0x98, "ChangeCharacterSexJob::_newSex");
    static_assert(offsetof(ChangeCharacterSexJob, _makingData) == 0xa0, "ChangeCharacterSexJob::_makingData");
    static_assert(offsetof(ChangeCharacterSexJob, _makingDataSize) == 0xa8, "ChangeCharacterSexJob::_makingDataSize");
    static_assert(offsetof(ChangeCharacterSexJob, _itemDataId) == 0xac, "ChangeCharacterSexJob::_itemDataId");
    static_assert(offsetof(ChangeCharacterSexJob, _serviceId) == 0xb0, "ChangeCharacterSexJob::_serviceId");
};
