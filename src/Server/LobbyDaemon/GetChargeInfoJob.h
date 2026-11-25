// GetChargeInfoJob.obj (LobbyDaemon PDB, 2019 + PDB). Layout from tools/pdbcls.py LobbyDaemon GetChargeInfoJob.
#pragma once
#include <stddef.h>
#include "CliSessionJob.h"

class CliSession;
class LobbyGateChannel;
class ObjPool;
struct LobbyJobDef;

// PDB layout (sizeof 0x68, CliSessionJob base).
class GetChargeInfoJob : public CliSessionJob
{
public:
    enum State
    {
        INIT = 0,
        GET_CHARGE_INFO = 1,
        FIN = 2
    };

    virtual LobbyJobDef const* GetDefinition() const;  // 0x50550
    static void* _vtbl();  // 0x505b0
    GetChargeInfoJob(CliSession*, LobbyGateChannel*);  // 0x50630
    virtual ~GetChargeInfoJob();  // LIFT: inlined in the scalar deleting destructor. It removes the reference on _lgate.
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x50560
    virtual bool work(int, void*);  // 0x506e0
    bool init();  // 0x50760
    bool requestChargeGetInfo();  // 0x50970
    bool responseChargeGetInfo(void*);  // 0x50c30
    bool expireChargeGetInfo();  // 0x51360

public:
    unsigned long long _clikey;
    LobbyGateChannel* _lgate;

    static ObjPool _pool;
    static LobbyJobDef _def;
};
static_assert(sizeof(GetChargeInfoJob) == 0x68, "sizeof GetChargeInfoJob");
static_assert(offsetof(GetChargeInfoJob, _clikey) == 0x58, "GetChargeInfoJob::_clikey");
static_assert(offsetof(GetChargeInfoJob, _lgate) == 0x60, "GetChargeInfoJob::_lgate");
