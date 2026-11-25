// StopChargeJob.obj (LobbyDaemon PDB, 2019 + PDB). Layout from tools/pdbcls.py LobbyDaemon StopChargeJob.
#pragma once
#include <stddef.h>
#include "CliSessionJob.h"

class CliSession;
class GamedChannel;
class ObjPool;
struct LobbyJobDef;

// LIFT: PDB layout (CliSessionJob base). The constructor is not in the PDB. It is inlined in the packet handler (0x8b9b0).
class StopChargeJob : public CliSessionJob
{
public:
    enum State
    {
        INIT = 0,
        STOP_CHARGE = 1,
        FIN = 2
    };

    StopChargeJob(CliSession* owner) : CliSessionJob(owner), _gamed(nullptr), _gametid(0), _pcid(0) { _chargeKey[0] = 0; }
    virtual ~StopChargeJob();  // LIFT: inlined in the scalar deleting destructor. It removes the reference on _gamed.
    virtual LobbyJobDef const* GetDefinition() const;  // 0x77c90
    static void* _vtbl();  // 0x77cf0
    bool Initialize(GamedChannel*, unsigned long long, unsigned long long, wchar_t*);  // 0x77dc0
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x77ca0
    virtual bool work(int, void*);  // 0x77f50
    bool init();  // 0x77fd0
    bool requestChargeStop();  // 0x78290
    bool responseChargeStop(void*);  // 0x78430
    bool expireChargeStop();  // 0x78790

public:
    GamedChannel* _gamed;
    unsigned long long _gametid;
    unsigned long long _pcid;
    wchar_t _chargeKey[65];

    static ObjPool _pool;  // LIFT: defined in the .cpp (gap-26).
    static LobbyJobDef _def;
};
static_assert(sizeof(StopChargeJob) == 0xF8, "sizeof StopChargeJob");
static_assert(offsetof(StopChargeJob, _gamed) == 0x58, "StopChargeJob::_gamed");
static_assert(offsetof(StopChargeJob, _gametid) == 0x60, "StopChargeJob::_gametid");
static_assert(offsetof(StopChargeJob, _pcid) == 0x68, "StopChargeJob::_pcid");
