// TryEnterGameWorldJob.obj (LobbyDaemon PDB, 2019 + PDB). Layouts from tools/pdbcls.py LobbyDaemon <Class>.
// LIFT: gap-25 lifts part 1 of the bodies (TryEnterGameWorldJob.cpp). Part 2 is still LIFT_STUB.
#pragma once
#include <stddef.h>
#include "CliSessionJob.h"
#include "StringUtil.h"

class GamedChannel;
class LobbyJobTransaction;
class ObjPool;
class CliSession;
class LobbyGateChannel;
struct LobbyJobDef;

// LIFT: PDB layout (sizeof 0x90, CliSessionJob base). Layout from tools/pdbcls.py LobbyDaemon TryEnterGameWorldJob.
class TryEnterGameWorldJob : public CliSessionJob
{
public:
    enum State
    {
        INIT = 0,
        RESTORE_PC = 1,
        CHECK_SECOND_PASSWORD_STATUS = 2,
        CHECK_SECOND_PASSWORD_VERIFIED = 3,
        GET_SLOT = 4,
        GET_CHARGE_INFO = 5,
        TRY_ENTER_GAME_WORLD = 6,
        ISSUE_GAME_WORLD_TOKEN = 7,
        FIN = 8,
    };
    enum ChargeAppplyType
    {
        CHARGEAPPLYTYPE_INVALID = 0,
        CHARGEAPPLYTYPE_NEEDTOCHARGE = 1,
        CHARGEAPPLYTYPE_TRIAL = 2,
        CHARGEAPPLYTYPE_FREETOPLAY = 3,
    };

    virtual LobbyJobDef const* GetDefinition() const;  // 0x7b840
    static void* _vtbl();  // 0x7b8a0
    TryEnterGameWorldJob(CliSession*);  // 0x7b920
    virtual ~TryEnterGameWorldJob();  // 0x7b9a0
    bool Initialize(LobbyGateChannel*, id128 const&);  // 0x7ba40
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x7b850
    virtual bool work(int, void*);  // 0x7bb70
    bool init();  // 0x7bcf0
    bool restorePcReq();  // 0x7c660
    bool restorePcOk();  // 0x7c820
    bool restorePcFail(short*);  // 0x7cba0
    bool restorePcExpired();  // 0x7cfe0
    bool checkSecondPasswordStatus();  // 0x7d0e0
    bool checkSecondPasswordStatusResponse(void*);  // 0x7d400
    bool checkSecondPasswordStatusExpire();  // 0x7d900
    bool checkSecondPasswordVerified();  // 0x7daa0
    bool checkSecondPasswordVerifiedResponse(void*);  // 0x7ddc0
    bool checkSecondPasswordVerifiedExpire();  // 0x7e0f0
    bool requestGetSlot();  // 0x7e290
    bool responseGetSlot(void*);  // 0x7e570
    bool expireGetSlot();  // 0x7eb60
    bool requestChargeGetInfo();  // 0x7ecf0
    bool responseChargeGetInfo(void*);  // 0x7efd0
    bool expireChargeGetInfo();  // 0x7fa60
    bool tryEnterGameWorld();  // 0x7fbf0
    bool issueGameWorldToken();  // 0x7ffe0

private:
    friend struct TryEnterGameWorldJobLayoutCheck;  // LIFT: checks the private PDB offsets.

    LobbyJobTransaction* _tran;  // +0x58
    LobbyGateChannel* _lgate;  // +0x60
    GamedChannel* _gamed;  // +0x68
    id128 _slotid;  // +0x70
    unsigned long long _pcid;  // +0x80
    short _belongingWorld;  // +0x88
    ChargeAppplyType _chargeApplyType;  // +0x8c

public:
    static ObjPool _pool;  // .data 0x205280
    static LobbyJobDef _def;
};
static_assert(sizeof(TryEnterGameWorldJob) == 0x90, "sizeof TryEnterGameWorldJob");
struct TryEnterGameWorldJobLayoutCheck
{
    static_assert(offsetof(TryEnterGameWorldJob, _tran) == 0x58, "TryEnterGameWorldJob::_tran");
    static_assert(offsetof(TryEnterGameWorldJob, _lgate) == 0x60, "TryEnterGameWorldJob::_lgate");
    static_assert(offsetof(TryEnterGameWorldJob, _gamed) == 0x68, "TryEnterGameWorldJob::_gamed");
    static_assert(offsetof(TryEnterGameWorldJob, _slotid) == 0x70, "TryEnterGameWorldJob::_slotid");
    static_assert(offsetof(TryEnterGameWorldJob, _pcid) == 0x80, "TryEnterGameWorldJob::_pcid");
    static_assert(offsetof(TryEnterGameWorldJob, _belongingWorld) == 0x88, "TryEnterGameWorldJob::_belongingWorld");
    static_assert(offsetof(TryEnterGameWorldJob, _chargeApplyType) == 0x8c, "TryEnterGameWorldJob::_chargeApplyType");
};
