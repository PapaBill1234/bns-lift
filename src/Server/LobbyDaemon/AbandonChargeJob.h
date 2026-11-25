// AbandonChargeJob.obj (LobbyDaemon PDB, 2019 + PDB). Layout from tools/pdbcls.py LobbyDaemon AbandonChargeJob.
#pragma once
#include <stddef.h>
#include "CliSessionJob.h"

class CliSession;
class ObjPool;
struct LobbyJobDef;

// LIFT: PDB layout (CliSessionJob base). The constructor is not in the PDB. It is inlined in the packet handler (0x8be60).
// The inlined constructor sets _pcid and _chargeKey[0] only. It leaves _clikey as it is.
class AbandonChargeJob : public CliSessionJob
{
public:
    enum State
    {
        INIT = 0,
        ABANDON_CHARGE = 1,
        FIN = 2
    };

    AbandonChargeJob(CliSession* owner) : CliSessionJob(owner), _pcid(0) { _chargeKey[0] = 0; }
    virtual ~AbandonChargeJob() {}
    virtual LobbyJobDef const* GetDefinition() const;  // 0x4f70
    static void* _vtbl();  // 0x5020
    bool Initialize(unsigned long long, wchar_t const*);  // 0x50d0
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x4f80
    virtual bool work(int, void*);  // 0x5220
    bool init();  // 0x52a0
    bool requestChargeAbandon();  // 0x54a0
    bool responseChargeAbandon(void*);  // 0x5690
    bool expireChargeAbandon();  // 0x5b10

public:
    unsigned long long _clikey;
    unsigned long long _pcid;
    wchar_t _chargeKey[65];

    static ObjPool _pool;
    static LobbyJobDef _def;
};
static_assert(sizeof(AbandonChargeJob) == 0xF0, "sizeof AbandonChargeJob");
static_assert(offsetof(AbandonChargeJob, _clikey) == 0x58, "AbandonChargeJob::_clikey");
static_assert(offsetof(AbandonChargeJob, _pcid) == 0x60, "AbandonChargeJob::_pcid");
static_assert(offsetof(AbandonChargeJob, _chargeKey) == 0x68, "AbandonChargeJob::_chargeKey");
