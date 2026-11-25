// EnterGameWorldJob.obj (LobbyDaemon PDB, 2019 + PDB). Layout from tools/pdbcls.py LobbyDaemon EnterGameWorldJob.
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
    enum State
    {
        INIT = 0,
        ENTER_GAME_WORLD = 1,
        FIN = 2
    };

    EnterGameWorldJob(CliSession* owner) : CliSessionJob(owner), _gamed(nullptr), _gametid(0), _pcid(0) {}
    virtual ~EnterGameWorldJob();  // 0x84ee0 (scalar deleting destructor)
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

    static ObjPool _pool;  // LIFT: defined in the .cpp (gap-26).
    static LobbyJobDef _def;
};
static_assert(sizeof(EnterGameWorldJob) == 0x70, "sizeof EnterGameWorldJob");
static_assert(offsetof(EnterGameWorldJob, _gamed) == 0x58, "EnterGameWorldJob::_gamed");

