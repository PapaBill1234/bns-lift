// AddSlotJob.obj (LobbyDaemon PDB, 2019 + PDB). Layout from tools/pdbcls.py LobbyDaemon AddSlotJob.
#pragma once
#include <stddef.h>
#include "CliSessionJob.h"
#include "StringUtil.h"

class AccountInventoryChannel;
class CliSession;
class LobbyGateChannel;
class LobbyJobTransaction;
class ObjPool;
struct LobbyJobDef;

// PDB layout (sizeof 0xA0, CliSessionJob base). The PDB also has Initialize(LobbyGateChannel*). The binary has no
// body for it. It is not declared here.
class AddSlotJob : public CliSessionJob
{
public:
    enum State
    {
        INIT = 0,
        CHECK_ACCOUNT_INVENTORY_ITEM = 1,
        CHECK_SLOT_CAPACITY = 2,
        REGISTER_SERVICE_ENTRY = 3,
        TRY_CONSUME_ACCOUNT_INVENTORY_ITEM = 4,
        CREATE_SLOT = 5,
        FIN_CONSUME_ACCOUNT_INVENTORY_ITEM = 6,
        FIN_SERVICE_ENTRY = 7,
        FIN = 8
    };

    static void* _vtbl();  // 0xd240
    AddSlotJob(CliSession* owner);  // 0xd2c0
    virtual ~AddSlotJob();  // 0xd340
    virtual LobbyJobDef const* GetDefinition() const;  // 0xd1e0
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0xd1f0
    virtual bool work(int, void*);  // 0xd3b0
    bool init(void*);  // 0xd570
    bool checkAccountInventoryItem();  // 0xdc90
    bool checkAccountInventoryItemOk(void*);  // 0xde30
    bool checkAccountInventoryItemFail(void*);  // 0xe2a0
    bool checkAccountInventoryItemTimeout();  // 0xe500
    bool checkSlotCapacity();  // 0xe610
    bool checkSlotCapacityAck(void*);  // 0xe8b0
    bool checkSlotCapacityExpire();  // 0xedb0
    bool registerServiceEntry();  // 0xeec0
    bool tryConsumeAccountInventoryItem();  // 0xf370
    bool tryConsumeAccountInventoryItemOk(void*);  // 0xf510
    bool tryConsumeAccountInventoryItemFail(void*);  // 0xf7d0
    bool tryConsumeAccountInventoryItemTimeout();  // 0xfa20
    bool createSlot();  // 0xfb30
    bool createSlotAck(void*);  // 0xfe00
    bool createSlotExpire();  // 0x105a0
    bool finConsumeAccountInventoryItem();  // 0x106b0
    bool finConsumeAccountInventoryItemOk(void*);  // 0x10850
    bool finConsumeAccountInventoryItemFail(void*);  // 0x10b10
    bool finConsumeAccountInventoryItemTimeout();  // 0x10d60
    bool finServiceEntry();  // 0x10e70

    LobbyJobTransaction* _tran;  // +0x58
    LobbyGateChannel* _lgate;  // +0x60
    AccountInventoryChannel* _acciv;  // +0x68
    unsigned long long _labelId;  // +0x70
    unsigned long long _itemInstanceId;  // +0x78
    unsigned int _itemDataId;  // +0x80
    unsigned long long _serviceId;  // +0x88
    id128 _slotId;  // +0x90

public:
    static ObjPool _pool;
    static LobbyJobDef _def;

    friend struct AddSlotJobLayoutCheck;
};

struct AddSlotJobLayoutCheck
{
    static_assert(sizeof(AddSlotJob) == 0xA0, "sizeof AddSlotJob");
    static_assert(offsetof(AddSlotJob, _tran) == 0x58, "AddSlotJob::_tran");
    static_assert(offsetof(AddSlotJob, _lgate) == 0x60, "AddSlotJob::_lgate");
    static_assert(offsetof(AddSlotJob, _acciv) == 0x68, "AddSlotJob::_acciv");
    static_assert(offsetof(AddSlotJob, _labelId) == 0x70, "AddSlotJob::_labelId");
    static_assert(offsetof(AddSlotJob, _itemInstanceId) == 0x78, "AddSlotJob::_itemInstanceId");
    static_assert(offsetof(AddSlotJob, _itemDataId) == 0x80, "AddSlotJob::_itemDataId");
    static_assert(offsetof(AddSlotJob, _serviceId) == 0x88, "AddSlotJob::_serviceId");
    static_assert(offsetof(AddSlotJob, _slotId) == 0x90, "AddSlotJob::_slotId");
};
