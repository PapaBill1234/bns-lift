// EnterGameWorldJob.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include <stddef.h>
#include "CliSessionJob.h"

class CliSession;
class GamedChannel;
class ObjPool;
struct LobbyJobDef;

// LIFT: PDB layout (CliSessionJob base). The constructor is not in the PDB. It is inlined in the packet handler.
class EnterGameWorldJob : public CliSessionJob
{
public:
    EnterGameWorldJob(CliSession* owner) : CliSessionJob(owner), _gamed(nullptr), _gametid(0), _pcid(0) {}
    virtual ~EnterGameWorldJob() {}
    virtual LobbyJobDef const* GetDefinition() const;  // 0x84e00
    static void* _vtbl();  // 0x84e60
    bool Initialize(GamedChannel*, unsigned long long, unsigned long long);  // 0x84f30
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x84e10
    virtual bool work(int, void*);  // 0x85080
    bool init();  // 0x850c0
    bool enterGameWorld();  // 0x85240

public:
    GamedChannel* _gamed;
    unsigned long long _gametid;
    unsigned long long _pcid;

    static ObjPool _pool;  // LIFT: no definition yet (like CliSession::_pool).
};
static_assert(sizeof(EnterGameWorldJob) == 0x70, "sizeof EnterGameWorldJob");
static_assert(offsetof(EnterGameWorldJob, _gamed) == 0x58, "EnterGameWorldJob::_gamed");

