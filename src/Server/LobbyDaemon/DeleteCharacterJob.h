// DeleteCharacterJob.obj (LobbyDaemon PDB, 2019 + PDB). Layout from tools/pdbcls.py LobbyDaemon DeleteCharacterJob.
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
struct DeleteCharacterOkParam;  // LobbyJobParams.h
struct LobbyJobDef;

// PDB layout (sizeof 0x90, CliSessionJob base).
class DeleteCharacterJob : public CliSessionJob
{
public:
    enum State
    {
        INIT = 0,
        CHECK_SECOND_PASSWORD_STATUS = 1,
        CHECK_SECOND_PASSWORD_VERIFIED = 2,
        CHECK_ACCOUNT_INVENTORY_CHARACTER_GOODS = 3,
        TRY_DELETION = 4,
        DIRECT_DELETION = 5,
        SCHEDULE_DELETION = 6,
        FIN = 7
    };

    static void* _vtbl();  // 0x450a0
    DeleteCharacterJob(CliSession* owner);  // 0x45120
    virtual ~DeleteCharacterJob();  // 0x451a0
    virtual LobbyJobDef const* GetDefinition() const;  // 0x45040
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x45050
    virtual bool work(int, void*);  // 0x45240
    bool init(int task, void* param);  // 0x453a0
    bool checkSecondPasswordStatus();  // 0x46440
    bool checkSecondPasswordStatusResponse(void* param);  // 0x46760
    bool checkSecondPasswordStatusExpire();  // 0x46d20
    bool checkSecondPasswordVerified();  // 0x46ed0
    bool checkSecondPasswordVerifiedResponse(void* param);  // 0x47200
    bool checkSecondPasswordVerifiedExpire();  // 0x47560
    bool getCharacterGoodsReq();  // 0x47710
    bool getCharacterGoodsCountOk(void* param);  // 0x47ac0
    bool getCharacterGoodsCountFail(void* param);  // 0x47d80
    bool getCharacterGoodsCountExpire();  // 0x47fa0
    bool deleteReq();  // 0x482b0
    bool deleteOk(DeleteCharacterOkParam* param);  // 0x48890
    bool deleteFail(void* param);  // 0x48a10
    bool deleteExpire();  // 0x49090
    bool directDelete();  // 0x493a0
    bool scheduleDelete();  // 0x49770

    LobbyJobTransaction* _tran;        // +0x58
    LobbyGateChannel* _lgate;          // +0x60
    GamedChannel* _gamed;              // +0x68
    AccountInventoryChannel* _acciv;   // +0x70
    id128 _slotid;                     // +0x78
    short _level;                      // +0x88

public:
    static ObjPool _pool;     // 0x204410
    static LobbyJobDef _def;  // 0x201d30

    friend struct DeleteCharacterJobLayoutCheck;
};

struct DeleteCharacterJobLayoutCheck
{
    static_assert(sizeof(DeleteCharacterJob) == 0x90, "sizeof DeleteCharacterJob");
    static_assert(offsetof(DeleteCharacterJob, _tran) == 0x58, "DeleteCharacterJob::_tran");
    static_assert(offsetof(DeleteCharacterJob, _lgate) == 0x60, "DeleteCharacterJob::_lgate");
    static_assert(offsetof(DeleteCharacterJob, _gamed) == 0x68, "DeleteCharacterJob::_gamed");
    static_assert(offsetof(DeleteCharacterJob, _acciv) == 0x70, "DeleteCharacterJob::_acciv");
    static_assert(offsetof(DeleteCharacterJob, _slotid) == 0x78, "DeleteCharacterJob::_slotid");
    static_assert(offsetof(DeleteCharacterJob, _level) == 0x88, "DeleteCharacterJob::_level");
};
