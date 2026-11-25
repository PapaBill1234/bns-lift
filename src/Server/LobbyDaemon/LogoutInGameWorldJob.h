// LogoutInGameWorldJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include <stddef.h>
#include "CliSessionJob.h"

class CliSession;
class ObjPool;
struct LobbyJobDef;

// LIFT: PDB layout (CliSessionJob base). The constructor is not in the PDB. It is inlined in the packet handler.
class LogoutInGameWorldJob : public CliSessionJob
{
public:
    LogoutInGameWorldJob(CliSession* owner) : CliSessionJob(owner), _wid(0) {}
    virtual ~LogoutInGameWorldJob() {}
    virtual LobbyJobDef const* GetDefinition() const;  // 0x5aa80
    static void* _vtbl();  // 0x5aae0
    bool Initialize(short);  // 0x5ab90
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x5aa90
    virtual bool work(int, void*);  // 0x5ac80
    bool init();  // 0x5acc0
    bool logout();  // 0x5af30

public:
    short _wid;

    static ObjPool _pool;  // LIFT: no definition yet (like CliSession::_pool).
    static LobbyJobDef _def;  // 0x201b58
};
static_assert(sizeof(LogoutInGameWorldJob) == 0x60, "sizeof LogoutInGameWorldJob");
static_assert(offsetof(LogoutInGameWorldJob, _wid) == 0x58, "LogoutInGameWorldJob::_wid");
