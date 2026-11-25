// RecoverPcJob.obj (LobbyDaemon PDB, 2019 + PDB). Layout from tools/pdbcls.py LobbyDaemon RecoverPcJob.
#pragma once
#include <stddef.h>
#include "CliSessionJob.h"
#include "StringUtil.h"

class Character;
class CliSession;
class GamedChannel;
class LobbyGateChannel;
class LobbyJobTransaction;
class ObjPool;
struct LobbyJobDef;

// PDB layout (sizeof 0x88, CliSessionJob base).
class RecoverPcJob : public CliSessionJob
{
public:
    enum State
    {
        INIT = 0,
        RESTORE_GAMEWORLD_PC = 1,
        FIN = 2
    };

    static void* _vtbl();  // 0x64eb0
    RecoverPcJob(CliSession* owner);  // 0x64f30
    virtual ~RecoverPcJob();  // 0x64fa0
    bool Initialize(LobbyGateChannel* lgate, id128 const& slotid);  // 0x65040
    virtual LobbyJobDef const* GetDefinition() const;  // 0x64e50
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x64e60
    virtual bool work(int, void*);  // 0x65260
    bool init();  // 0x652f0
    bool restoreGameWorldPcReq();  // 0x65b40
    bool restoreGameWorldPcOk();  // 0x65d30
    bool restoreGameWorldPcFail(short* reason);  // 0x66070
    bool restoreGameWorldPcExpired();  // 0x664f0
    bool __restoreStuckPc(Character* pc, short& failReason);  // 0x66600

    LobbyJobTransaction* _tran;  // +0x58
    LobbyGateChannel* _lgate;  // +0x60
    GamedChannel* _gamed;  // +0x68
    id128 _slotid;  // +0x70
    unsigned long long _pcid;  // +0x80

public:
    static ObjPool _pool;
    static LobbyJobDef _def;

    friend struct RecoverPcJobLayoutCheck;
};

struct RecoverPcJobLayoutCheck
{
    static_assert(sizeof(RecoverPcJob) == 0x88, "sizeof RecoverPcJob");
    static_assert(offsetof(RecoverPcJob, _tran) == 0x58, "RecoverPcJob::_tran");
    static_assert(offsetof(RecoverPcJob, _lgate) == 0x60, "RecoverPcJob::_lgate");
    static_assert(offsetof(RecoverPcJob, _gamed) == 0x68, "RecoverPcJob::_gamed");
    static_assert(offsetof(RecoverPcJob, _slotid) == 0x70, "RecoverPcJob::_slotid");
    static_assert(offsetof(RecoverPcJob, _pcid) == 0x80, "RecoverPcJob::_pcid");
};
