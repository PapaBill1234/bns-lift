// CancelWaitCharacterDeletionJob.obj (LobbyDaemon PDB, 2019 + PDB). Layout from tools/pdbcls.py LobbyDaemon
// CancelWaitCharacterDeletionJob.
#pragma once
#include <stddef.h>
#include "CliSessionJob.h"
#include "StringUtil.h"

class CliSession;
class GamedChannel;
class LobbyGateChannel;
class LobbyJobTransaction;
class ObjPool;
struct CancelWaitCharacterDeletionReqParam;  // LobbyJobParams.h
struct LobbyJobDef;

// PDB layout (sizeof 0x80, CliSessionJob base).
class CancelWaitCharacterDeletionJob : public CliSessionJob
{
public:
    enum State
    {
        INIT = 0,
        RESTORE_LOBBY = 1,
        RESTORE_GAMEWORLD = 2,
        FIN = 3
    };

    static void* _vtbl();  // 0x188f0
    CancelWaitCharacterDeletionJob(CliSession* owner);  // 0x18970
    virtual ~CancelWaitCharacterDeletionJob();  // 0x189e0
    virtual LobbyJobDef const* GetDefinition() const;  // 0x18890
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x188a0
    virtual bool work(int, void*);  // 0x18a80
    bool init(CancelWaitCharacterDeletionReqParam* param);  // 0x18b40
    bool restore();  // 0x196f0
    bool restoreCharacterReq();  // 0x19ad0
    bool restoreCharacterOk();  // 0x19f30
    bool restoreCharacterFail(short* reason);  // 0x1a3b0
    bool restoreCharacterExpire();  // 0x1a860

    LobbyJobTransaction* _tran;  // +0x58
    LobbyGateChannel* _lgate;  // +0x60
    GamedChannel* _gamed;  // +0x68
    id128 _slotid;  // +0x70

public:
    static ObjPool _pool;
    static LobbyJobDef _def;

    friend struct CancelWaitCharacterDeletionJobLayoutCheck;
};

struct CancelWaitCharacterDeletionJobLayoutCheck
{
    static_assert(sizeof(CancelWaitCharacterDeletionJob) == 0x80, "sizeof CancelWaitCharacterDeletionJob");
    static_assert(offsetof(CancelWaitCharacterDeletionJob, _tran) == 0x58, "CancelWaitCharacterDeletionJob::_tran");
    static_assert(offsetof(CancelWaitCharacterDeletionJob, _lgate) == 0x60, "CancelWaitCharacterDeletionJob::_lgate");
    static_assert(offsetof(CancelWaitCharacterDeletionJob, _gamed) == 0x68, "CancelWaitCharacterDeletionJob::_gamed");
    static_assert(offsetof(CancelWaitCharacterDeletionJob, _slotid) == 0x70, "CancelWaitCharacterDeletionJob::_slotid");
};
