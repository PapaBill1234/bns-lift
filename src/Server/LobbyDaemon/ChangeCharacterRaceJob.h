// ChangeCharacterRaceJob.obj (LobbyDaemon PDB, 2019 + PDB). Layouts from tools/pdbcls.py LobbyDaemon <Class>.
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

// PDB ChangeCharacterRaceWithAccountInventoryItemReqParam (sizeof 0x138). The lobby-gate handler fills it. init reads it.
struct ChangeCharacterRaceWithAccountInventoryItemReqParam
{
    LobbyGateChannel* lgate;
    id128 slotid;
    char newRace;
    char newSex;
    char makingData[256];
    short makingDataSize;
    unsigned long long labelId;
    unsigned long long itemInstanceId;
    unsigned int itemDataId;
};
static_assert(sizeof(ChangeCharacterRaceWithAccountInventoryItemReqParam) == 0x138, "sizeof ChangeCharacterRaceWithAccountInventoryItemReqParam");
static_assert(offsetof(ChangeCharacterRaceWithAccountInventoryItemReqParam, slotid) == 0x8, "ChangeCharacterRaceWithAccountInventoryItemReqParam::slotid");
static_assert(offsetof(ChangeCharacterRaceWithAccountInventoryItemReqParam, newRace) == 0x18, "ChangeCharacterRaceWithAccountInventoryItemReqParam::newRace");
static_assert(offsetof(ChangeCharacterRaceWithAccountInventoryItemReqParam, newSex) == 0x19, "ChangeCharacterRaceWithAccountInventoryItemReqParam::newSex");
static_assert(offsetof(ChangeCharacterRaceWithAccountInventoryItemReqParam, makingData) == 0x1a, "ChangeCharacterRaceWithAccountInventoryItemReqParam::makingData");
static_assert(offsetof(ChangeCharacterRaceWithAccountInventoryItemReqParam, makingDataSize) == 0x11a, "ChangeCharacterRaceWithAccountInventoryItemReqParam::makingDataSize");
static_assert(offsetof(ChangeCharacterRaceWithAccountInventoryItemReqParam, labelId) == 0x120, "ChangeCharacterRaceWithAccountInventoryItemReqParam::labelId");
static_assert(offsetof(ChangeCharacterRaceWithAccountInventoryItemReqParam, itemInstanceId) == 0x128, "ChangeCharacterRaceWithAccountInventoryItemReqParam::itemInstanceId");
static_assert(offsetof(ChangeCharacterRaceWithAccountInventoryItemReqParam, itemDataId) == 0x130, "ChangeCharacterRaceWithAccountInventoryItemReqParam::itemDataId");

// PDB ChangeCharacterRaceOkParam (sizeof 0x10). The gamed handler fills it. changeCharacterRaceOk reads it.
struct ChangeCharacterRaceOkParam
{
    char* showcaseData;
    short showcaseDataSize;
};
static_assert(sizeof(ChangeCharacterRaceOkParam) == 0x10, "sizeof ChangeCharacterRaceOkParam");
static_assert(offsetof(ChangeCharacterRaceOkParam, showcaseDataSize) == 0x8, "ChangeCharacterRaceOkParam::showcaseDataSize");

// LIFT: PDB layout (sizeof 0xb8, CliSessionJob base). Layout from tools/pdbcls.py LobbyDaemon ChangeCharacterRaceJob.
class ChangeCharacterRaceJob : public CliSessionJob
{
public:
    enum State
    {
        INIT = 0,
        CHECK_ACCOUNT_INVENTORY_ITEM = 1,
        REGISTER_SERVICE_ENTRY = 2,
        TRY_CONSUME_ACCOUNT_INVENTORY_ITEM = 3,
        CHANGE_CHARACTER_RACE = 4,
        FIN_CONSUME_ACCOUNT_INVENTORY_ITEM = 5,
        FIN_SERVICE_ENTRY = 6,
        FIN = 7,
    };

    static void* _vtbl();  // LIFT: PDB declares it; no RVA (inlined in LobbyDaemon::initialize 0x9b300)
    virtual LobbyJobDef const* GetDefinition() const;  // 0x1ea40
    ChangeCharacterRaceJob(CliSession*);  // 0x1eaa0
    virtual ~ChangeCharacterRaceJob();  // 0x1eb40
    bool Initialize(LobbyGateChannel*);  // LIFT: PDB method; no own symbol in the lift scope.
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x1ea50
    virtual bool work(int, void*);  // 0x1ebf0
    bool init(void*);  // 0x1ed90
    bool checkAccountInventoryItem();  // 0x1fa00
    bool checkAccountInventoryItemOk(void*);  // 0x1fbb0
    bool checkAccountInventoryItemFail(void*);  // 0x20020
    bool checkAccountInventoryItemTimeout();  // 0x20290
    bool registerServiceEntry();  // 0x203b0
    bool tryConsumeAccountInventoryItem();  // 0x20a10
    bool tryConsumeAccountInventoryItemOk(void*);  // 0x20bd0
    bool tryConsumeAccountInventoryItemFail(void*);  // 0x20eb0
    bool tryConsumeAccountInventoryItemTimeout();  // 0x21110
    bool changeCharacterRace();  // 0x21240
    bool changeCharacterRaceOk(void*);  // 0x214a0
    bool changeCharacterRaceFail(void*);  // 0x21a30
    bool changeCharacterRaceTimeout();  // 0x21c90
    bool finConsumeAccountInventoryItem();  // 0x21dc0
    bool finConsumeAccountInventoryItemOk(void*);  // 0x21f80
    bool finConsumeAccountInventoryItemFail(void*);  // 0x22250
    bool finConsumeAccountInventoryItemTimeout();  // 0x224b0
    bool finServiceEntry();  // 0x225e0
    bool releasePcServiceStatus();  // 0x229a0 (ICF with the Sex and Appearance copies)

private:
    friend struct ChangeCharacterRaceJobLayoutCheck;  // LIFT: checks the private PDB offsets.

    LobbyJobTransaction* _tran;  // +0x58
    LobbyGateChannel* _lgate;  // +0x60
    AccountInventoryChannel* _acciv;  // +0x68
    GamedChannel* _gamed;  // +0x70
    id128 _slotid;  // +0x78
    unsigned long long _labelId;  // +0x88
    unsigned long long _itemInstanceId;  // +0x90
    char _newRace;  // +0x98
    char _newSex;  // +0x99
    char* _makingData;  // +0xa0
    int _makingDataSize;  // +0xa8
    unsigned int _itemDataId;  // +0xac
    unsigned long long _serviceId;  // +0xb0

public:
    static ObjPool _pool;
    static LobbyJobDef _def;
};
static_assert(sizeof(ChangeCharacterRaceJob) == 0xb8, "sizeof ChangeCharacterRaceJob");
struct ChangeCharacterRaceJobLayoutCheck
{
    static_assert(offsetof(ChangeCharacterRaceJob, _tran) == 0x58, "ChangeCharacterRaceJob::_tran");
    static_assert(offsetof(ChangeCharacterRaceJob, _lgate) == 0x60, "ChangeCharacterRaceJob::_lgate");
    static_assert(offsetof(ChangeCharacterRaceJob, _acciv) == 0x68, "ChangeCharacterRaceJob::_acciv");
    static_assert(offsetof(ChangeCharacterRaceJob, _gamed) == 0x70, "ChangeCharacterRaceJob::_gamed");
    static_assert(offsetof(ChangeCharacterRaceJob, _slotid) == 0x78, "ChangeCharacterRaceJob::_slotid");
    static_assert(offsetof(ChangeCharacterRaceJob, _labelId) == 0x88, "ChangeCharacterRaceJob::_labelId");
    static_assert(offsetof(ChangeCharacterRaceJob, _itemInstanceId) == 0x90, "ChangeCharacterRaceJob::_itemInstanceId");
    static_assert(offsetof(ChangeCharacterRaceJob, _newRace) == 0x98, "ChangeCharacterRaceJob::_newRace");
    static_assert(offsetof(ChangeCharacterRaceJob, _newSex) == 0x99, "ChangeCharacterRaceJob::_newSex");
    static_assert(offsetof(ChangeCharacterRaceJob, _makingData) == 0xa0, "ChangeCharacterRaceJob::_makingData");
    static_assert(offsetof(ChangeCharacterRaceJob, _makingDataSize) == 0xa8, "ChangeCharacterRaceJob::_makingDataSize");
    static_assert(offsetof(ChangeCharacterRaceJob, _itemDataId) == 0xac, "ChangeCharacterRaceJob::_itemDataId");
    static_assert(offsetof(ChangeCharacterRaceJob, _serviceId) == 0xb0, "ChangeCharacterRaceJob::_serviceId");
};
