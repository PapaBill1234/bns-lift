// LogoutJob.obj (LobbyDaemon PDB, 2019 + PDB). Layout from tools/pdbcls.py LobbyDaemon LogoutJob.
#pragma once
#include <stddef.h>
#include "CliSessionJob.h"

class CliSession;
class LobbyGateChannel;
class ObjPool;
struct LobbyJobDef;

// LIFT: PDB layout (CliSessionJob base).
class LogoutJob : public CliSessionJob
{
public:
    enum State
    {
        INIT = 0,
        LOGOUT = 1,
        FIN = 2
    };

    LogoutJob(CliSession*, LobbyGateChannel*, bool);  // 0x97af0
    virtual ~LogoutJob();  // 0x97b60 (scalar deleting destructor)
    virtual LobbyJobDef const* GetDefinition() const;  // 0x97a10
    static void* _vtbl();  // 0x97a70
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x97a20
    virtual bool work(int, void*);  // 0x97bb0
    bool init(int, void*);  // 0x97bf0
    bool logout();  // 0x97d30

    int _last;
    LobbyGateChannel* _lgate;
    bool _close;

public:
    static ObjPool _pool;
    static LobbyJobDef _def;
};
static_assert(sizeof(LogoutJob) == 0x70, "sizeof LogoutJob");
