// EndWaitGameWorldJob.obj (LobbyDaemon PDB, 2019 + PDB). Layout from tools/pdbcls.py LobbyDaemon EndWaitGameWorldJob.
#pragma once
#include <stddef.h>
#include "CliSessionJob.h"

class CliSession;
class LobbyGateChannel;
class ObjPool;
struct LobbyJobDef;

// PDB layout (sizeof 0x60, CliSessionJob base). The constructor is inline (no body in the binary).
class EndWaitGameWorldJob : public CliSessionJob
{
public:
    enum State
    {
        INIT = 0,
        END_WAIT = 1,
        FIN = 2
    };

    static void* _vtbl();  // 0x4b040
    EndWaitGameWorldJob(CliSession* owner) : CliSessionJob(owner), _lgate(nullptr) {}
    virtual ~EndWaitGameWorldJob();  // 0x4b0c0 (scalar deleting destructor)
    virtual LobbyJobDef const* GetDefinition() const;  // 0x4afe0
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x4aff0
    virtual bool work(int, void*);  // 0x4b110
    bool init(int, void*);  // 0x4b150
    bool endWait();  // 0x4b460

    LobbyGateChannel* _lgate;  // +0x58

public:
    static ObjPool _pool;
    static LobbyJobDef _def;

    friend struct EndWaitGameWorldJobLayoutCheck;
};

struct EndWaitGameWorldJobLayoutCheck
{
    static_assert(sizeof(EndWaitGameWorldJob) == 0x60, "sizeof EndWaitGameWorldJob");
    static_assert(offsetof(EndWaitGameWorldJob, _lgate) == 0x58, "EndWaitGameWorldJob::_lgate");
};
