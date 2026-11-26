// InitCliSessionWnpTokenJob.obj (LobbyDaemon PDB, 2019 + PDB). Layout from tools/pdbcls.py LobbyDaemon InitCliSessionWnpTokenJob.
#pragma once
#include "CliSessionJob.h"

class CliSession;
class ObjPool;
struct LobbyJobDef;

// PDB layout (sizeof 0x58, CliSessionJob base, no own members).
class InitCliSessionWnpTokenJob : public CliSessionJob
{
public:
    enum State
    {
        INIT = 0,
        FIN = 1
    };

    static void* _vtbl();  // 0x98120
    // The PDB constructor and destructor have no own bodies. The binary inlines them (scalar deleting destructor 0x3c0e0).
    InitCliSessionWnpTokenJob(CliSession* owner) : CliSessionJob(owner) {}
    virtual ~InitCliSessionWnpTokenJob() {}
    virtual LobbyJobDef const* GetDefinition() const;  // 0x3c080
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x3c090
    virtual bool work(int, void*);  // 0x981a0
    bool init(int, void*);  // 0x981c0

public:
    static ObjPool _pool;  // .data 0x2055f0
    static LobbyJobDef _def;
};
static_assert(sizeof(InitCliSessionWnpTokenJob) == 0x58, "sizeof InitCliSessionWnpTokenJob");
