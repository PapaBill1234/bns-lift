// RenameCharacterJob.obj (LobbyDaemon PDB, 2019 + PDB). Layout from tools/pdbcls.py LobbyDaemon RenameCharacterJob.
#pragma once
#include <stddef.h>
#include "CliSessionJob.h"
#include "StringUtil.h"

class AccountInventoryChannel;
class CliSession;
class GamedChannel;
class LobbyGateChannel;
class LobbyJobTransaction;
class ObjPool;
struct LobbyJobDef;

// PDB layout (sizeof 0x138, CliSessionJob base). The PDB also has Initialize(LobbyGateChannel*). The binary has no
// body for it. It is not declared here.
class RenameCharacterJob : public CliSessionJob
{
public:
    enum State
    {
        INIT = 0,
        CHECK_ACCOUNT_INVENTORY_ITEM = 1,
        REGISTER_SERVICE_ENTRY = 2,
        TRY_CONSUME_ACCOUNT_INVENTORY_ITEM = 3,
        RENAME_CHARACTER = 4,
        FIN_CONSUME_ACCOUNT_INVENTORY_ITEM = 5,
        FIN_SERVICE_ENTRY = 6,
        FIN = 7
    };
    // PDB nested enum RenameCharacterJob::FriendMessageLength.
    enum FriendMessageLength
    {
        KEY_NAME_LENGTH = 5,
        VALUE_NAME_LENGTH = 72
    };

    RenameCharacterJob(CliSession* owner);  // 0x66b40
    virtual ~RenameCharacterJob();  // 0x66c50
    virtual LobbyJobDef const* GetDefinition() const;  // 0x66ae0
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x66af0
    virtual bool work(int, void*);  // 0x66cd0
    bool init(void*);  // 0x66e70
    bool checkAccountInventoryItem();  // 0x68e80
    bool checkAccountInventoryItemOk(void*);  // 0x69100
    bool checkAccountInventoryItemFail(void*);  // 0x694c0
    bool checkAccountInventoryItemTimeout();  // 0x69730
    bool registerServiceEntry();  // 0x69850
    bool tryConsumeAccountInventoryItem();  // 0x69f70
    bool tryConsumeAccountInventoryItemOk(void*);  // 0x6a120
    bool tryConsumeAccountInventoryItemFail(void*);  // 0x6a3f0
    bool tryConsumeAccountInventoryItemTimeout();  // 0x6a650
    bool renameCharacter();  // 0x6a770
    bool renameCharacterOk(void*);  // 0x6a9a0
    bool renameCharacterFail(void*);  // 0x6ae30
    bool renameCharacterTimeout();  // 0x6b090
    bool finConsumeAccountInventoryItem();  // 0x6b1b0
    bool finConsumeAccountInventoryItemOk(void*);  // 0x6b360
    bool finConsumeAccountInventoryItemFail(void*);  // 0x6b630
    bool finConsumeAccountInventoryItemTimeout();  // 0x6b890
    bool finServiceEntry();  // 0x6b9b0
    void sendFriendMessageToNP();  // 0x6bc50

    LobbyJobTransaction* _tran;  // +0x58
    LobbyGateChannel* _lgate;  // +0x60
    AccountInventoryChannel* _acciv;  // +0x68
    GamedChannel* _gamed;  // +0x70
    bool _isTargetPc;  // +0x78
    id128 _slotid;  // +0x80
    unsigned long long _labelId;  // +0x90
    unsigned long long _itemInstanceId;  // +0x98
    unsigned int _itemDataId;  // +0xA0
    unsigned long long _serviceId;  // +0xA8
    wchar_t _oldName[33];  // +0xB0
    wchar_t _newName[33];  // +0xF2

public:
    static ObjPool _pool;
    static LobbyJobDef _def;

    friend struct RenameCharacterJobLayoutCheck;
};

struct RenameCharacterJobLayoutCheck
{
    static_assert(sizeof(RenameCharacterJob) == 0x138, "sizeof RenameCharacterJob");
    static_assert(offsetof(RenameCharacterJob, _tran) == 0x58, "RenameCharacterJob::_tran");
    static_assert(offsetof(RenameCharacterJob, _gamed) == 0x70, "RenameCharacterJob::_gamed");
    static_assert(offsetof(RenameCharacterJob, _isTargetPc) == 0x78, "RenameCharacterJob::_isTargetPc");
    static_assert(offsetof(RenameCharacterJob, _slotid) == 0x80, "RenameCharacterJob::_slotid");
    static_assert(offsetof(RenameCharacterJob, _itemDataId) == 0xA0, "RenameCharacterJob::_itemDataId");
    static_assert(offsetof(RenameCharacterJob, _serviceId) == 0xA8, "RenameCharacterJob::_serviceId");
    static_assert(offsetof(RenameCharacterJob, _oldName) == 0xB0, "RenameCharacterJob::_oldName");
    static_assert(offsetof(RenameCharacterJob, _newName) == 0xF2, "RenameCharacterJob::_newName");
};
