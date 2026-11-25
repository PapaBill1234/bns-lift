// GiveupWaitGameWorldJob.obj (LobbyDaemon PDB, 2019 + PDB). Layout from tools/pdbcls.py LobbyDaemon GiveupWaitGameWorldJob.
#pragma once
#include <stddef.h>
#include "CliSessionJob.h"

class CliSession;
class LobbyGateChannel;
class ObjPool;
struct LobbyJobDef;

// PDB layout (sizeof 0x60, CliSessionJob base). The constructor is inline (no body in the binary).
class GiveupWaitGameWorldJob : public CliSessionJob
{
public:
    enum State
    {
        INIT = 0,
        GIVEUP_WAIT = 1,
        FIN = 2
    };

    static void* _vtbl();  // 0x52d50
    GiveupWaitGameWorldJob(CliSession* owner) : CliSessionJob(owner), _lgate(nullptr) {}
    virtual ~GiveupWaitGameWorldJob();  // 0x52dd0 (scalar deleting destructor)
    virtual LobbyJobDef const* GetDefinition() const;  // 0x52cf0
    bool Initialize(LobbyGateChannel*);  // 0x52e20
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x52d00
    virtual bool work(int, void*);  // 0x52f30
    bool init();  // 0x52f70
    bool giveupWait();  // 0x530d0

    LobbyGateChannel* _lgate;  // +0x58

public:
    static ObjPool _pool;
    static LobbyJobDef _def;

    friend struct GiveupWaitGameWorldJobLayoutCheck;
};

struct GiveupWaitGameWorldJobLayoutCheck
{
    static_assert(sizeof(GiveupWaitGameWorldJob) == 0x60, "sizeof GiveupWaitGameWorldJob");
    static_assert(offsetof(GiveupWaitGameWorldJob, _lgate) == 0x58, "GiveupWaitGameWorldJob::_lgate");
};
