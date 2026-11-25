// ExtendJumpingCharacterCreationQuotaJob.obj (LobbyDaemon PDB, 2019 + PDB). Layouts from tools/pdbcls.py LobbyDaemon <Class>.
// LIFT: header layouts only (fix7). The function bodies are still LIFT_STUB.
#pragma once
#include <stddef.h>
#include "CliSessionJob.h"

class AccountInventoryChannel;
class GamedChannel;
class LobbyGateChannel;
class LobbyJobTransaction;
class ObjPool;
class CliSession;
struct LobbyJobDef;

// LIFT: PDB layout (sizeof 0xa0, CliSessionJob base). Layout from tools/pdbcls.py LobbyDaemon ExtendJumpingCharacterCreationQuotaJob.
class ExtendJumpingCharacterCreationQuotaJob : public CliSessionJob
{
public:
    enum State
    {
        INIT = 0,
        CHECK_ACCOUNT_INVENTORY_ITEM = 1,
        REGISTER_SERVICE_ENTRY = 2,
        TRY_CONSUME_ACCOUNT_INVENTORY_ITEM = 3,
        EXTEND_JUMPING_CHARACTER_CREATION_QUOTA = 4,
        FIN_CONSUME_ACCOUNT_INVENTORY_ITEM = 5,
        FIN_SERVICE_ENTRY = 6,
        FIN = 7,
    };

    virtual LobbyJobDef const* GetDefinition() const;  // 0x2a300
    static void* _vtbl();  // 0x2a3c0
    ExtendJumpingCharacterCreationQuotaJob(CliSession*);  // 0x2a440
    virtual ~ExtendJumpingCharacterCreationQuotaJob();  // 0x2a4c0
    bool Initialize(LobbyGateChannel*);  // LIFT: PDB method; no own symbol in the lift scope.
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x2a310
    virtual bool work(int, void*);  // 0x2a540
    bool init(void*);  // 0x2a6a0
    bool checkAccountInventoryItem();  // 0x2b0a0
    bool checkAccountInventoryItemOk(void*);  // 0x2b220
    bool checkAccountInventoryItemFail(void*);  // 0x2b640
    bool checkAccountInventoryItemTimeout();  // 0x2b890
    bool registerServiceEntry();  // 0x2b990
    bool tryConsumeAccountInventoryItem();  // 0x2bdf0
    bool tryConsumeAccountInventoryItemOk(void*);  // 0x2bf80
    bool tryConsumeAccountInventoryItemFail(void*);  // 0x2c220
    bool tryConsumeAccountInventoryItemTimeout();  // 0x2c450
    bool extendJumpingCharacterCreationQuota();  // 0x2c550
    bool finConsumeAccountInventoryItem();  // 0x2c730
    bool finConsumeAccountInventoryItemOk(void*);  // 0x2c8c0
    bool finConsumeAccountInventoryItemFail(void*);  // 0x2cb60
    bool finConsumeAccountInventoryItemTimeout();  // 0x2cd90
    bool finServiceEntry();  // 0x2ce90
    void sendFailReason(short);  // 0x2d140

private:
    friend struct ExtendJumpingCharacterCreationQuotaJobLayoutCheck;  // LIFT: checks the private PDB offsets.

    LobbyJobTransaction* _tran;  // +0x58
    LobbyGateChannel* _lgate;  // +0x60
    GamedChannel* _gamed;  // +0x68
    unsigned long long _gamedTid;  // +0x70
    AccountInventoryChannel* _acciv;  // +0x78
    unsigned long long _labelId;  // +0x80
    unsigned long long _itemInstanceId;  // +0x88
    unsigned int _itemDataId;  // +0x90
    unsigned long long _serviceId;  // +0x98

public:
    static ObjPool _pool;
    static LobbyJobDef _def;
};
static_assert(sizeof(ExtendJumpingCharacterCreationQuotaJob) == 0xa0, "sizeof ExtendJumpingCharacterCreationQuotaJob");
struct ExtendJumpingCharacterCreationQuotaJobLayoutCheck
{
    static_assert(offsetof(ExtendJumpingCharacterCreationQuotaJob, _tran) == 0x58, "ExtendJumpingCharacterCreationQuotaJob::_tran");
    static_assert(offsetof(ExtendJumpingCharacterCreationQuotaJob, _lgate) == 0x60, "ExtendJumpingCharacterCreationQuotaJob::_lgate");
    static_assert(offsetof(ExtendJumpingCharacterCreationQuotaJob, _gamed) == 0x68, "ExtendJumpingCharacterCreationQuotaJob::_gamed");
    static_assert(offsetof(ExtendJumpingCharacterCreationQuotaJob, _gamedTid) == 0x70, "ExtendJumpingCharacterCreationQuotaJob::_gamedTid");
    static_assert(offsetof(ExtendJumpingCharacterCreationQuotaJob, _acciv) == 0x78, "ExtendJumpingCharacterCreationQuotaJob::_acciv");
    static_assert(offsetof(ExtendJumpingCharacterCreationQuotaJob, _labelId) == 0x80, "ExtendJumpingCharacterCreationQuotaJob::_labelId");
    static_assert(offsetof(ExtendJumpingCharacterCreationQuotaJob, _itemInstanceId) == 0x88, "ExtendJumpingCharacterCreationQuotaJob::_itemInstanceId");
    static_assert(offsetof(ExtendJumpingCharacterCreationQuotaJob, _itemDataId) == 0x90, "ExtendJumpingCharacterCreationQuotaJob::_itemDataId");
    static_assert(offsetof(ExtendJumpingCharacterCreationQuotaJob, _serviceId) == 0x98, "ExtendJumpingCharacterCreationQuotaJob::_serviceId");
};

// LIFT: PDB layout (sizeof 0x80, CliSessionJob base). Layout from tools/pdbcls.py LobbyDaemon UpgradeJumpingCharacterStateJob.
class UpgradeJumpingCharacterStateJob : public CliSessionJob
{
public:
    enum State
    {
        INIT = 0,
        UPGRADE_JUMPING_CHARACTER_STATE = 1,
        FIN = 2,
    };

    virtual LobbyJobDef const* GetDefinition() const;  // 0x2a360
    static void* _vtbl();  // 0x2d440
    UpgradeJumpingCharacterStateJob(CliSession*);  // 0x2d4c0
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x2a370
    virtual bool work(int, void*);  // 0x2d550
    bool init(int, void*);  // 0x2d580
    bool upgradeJumpingCharacterState();  // 0x2d9c0

private:
    friend struct UpgradeJumpingCharacterStateJobLayoutCheck;  // LIFT: checks the private PDB offsets.

    GamedChannel* _gamed;  // +0x58
    unsigned long long _gamedTid;  // +0x60
    short _wid;  // +0x68
    unsigned long long _pcId;  // +0x70
    char _jumpingCharacterState;  // +0x78
    bool _consumeCreationQuota;  // +0x79

public:
    static ObjPool _pool;
    static LobbyJobDef _def;
};
static_assert(sizeof(UpgradeJumpingCharacterStateJob) == 0x80, "sizeof UpgradeJumpingCharacterStateJob");
struct UpgradeJumpingCharacterStateJobLayoutCheck
{
    static_assert(offsetof(UpgradeJumpingCharacterStateJob, _gamed) == 0x58, "UpgradeJumpingCharacterStateJob::_gamed");
    static_assert(offsetof(UpgradeJumpingCharacterStateJob, _gamedTid) == 0x60, "UpgradeJumpingCharacterStateJob::_gamedTid");
    static_assert(offsetof(UpgradeJumpingCharacterStateJob, _wid) == 0x68, "UpgradeJumpingCharacterStateJob::_wid");
    static_assert(offsetof(UpgradeJumpingCharacterStateJob, _pcId) == 0x70, "UpgradeJumpingCharacterStateJob::_pcId");
    static_assert(offsetof(UpgradeJumpingCharacterStateJob, _jumpingCharacterState) == 0x78, "UpgradeJumpingCharacterStateJob::_jumpingCharacterState");
    static_assert(offsetof(UpgradeJumpingCharacterStateJob, _consumeCreationQuota) == 0x79, "UpgradeJumpingCharacterStateJob::_consumeCreationQuota");
};
