// LeaveGameWorldJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include <stddef.h>
#include "CliSessionJob.h"

class CliSession;
class GamedChannel;
class ObjPool;
struct LobbyJobDef;

// LIFT: PDB layout (CliSessionJob base). The constructor is not in the PDB. It is inlined in the packet handler.
class LeaveGameWorldJob : public CliSessionJob
{
public:
    LeaveGameWorldJob(CliSession* owner) : CliSessionJob(owner), _gamed(nullptr), _gametid(0), _pcid(0), _leaveWorldTokenKey(0) {}
    virtual ~LeaveGameWorldJob() {}
    virtual LobbyJobDef const* GetDefinition() const;  // 0x877b0
    static void* _vtbl();  // 0x87810
    bool Initialize(GamedChannel*, unsigned long long, unsigned long long);  // 0x878e0
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x877c0
    virtual bool work(int, void*);  // 0x87a00
    bool init();  // 0x87a40
    bool leaveGameWorld();  // 0x87e90

public:
    GamedChannel* _gamed;
    unsigned long long _gametid;
    unsigned long long _pcid;
    unsigned long long _leaveWorldTokenKey;

    static ObjPool _pool;  // LIFT: no definition yet (like CliSession::_pool).
};
static_assert(sizeof(LeaveGameWorldJob) == 0x78, "sizeof LeaveGameWorldJob");
static_assert(offsetof(LeaveGameWorldJob, _gamed) == 0x58, "LeaveGameWorldJob::_gamed");

