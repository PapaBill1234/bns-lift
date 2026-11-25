// InitCliSessionWlobbyTokenJob.obj (LobbyDaemon PDB, 2019 + PDB). Layout from tools/pdbcls.py LobbyDaemon InitCliSessionWlobbyTokenJob.
#pragma once
#include <stddef.h>
#include "CliSessionJob.h"

class CliSession;
class LobbyGateChannel;
class ObjPool;
struct LobbyJobDef;

// LIFT: PDB layout (CliSessionJob base). The PDB constructor has no body. It is inlined in the callers.
class InitCliSessionWlobbyTokenJob : public CliSessionJob
{
public:
    enum State
    {
        INIT = 0,
        INIT_CLISESSION_OK = 1,
        FIN = 2
    };

    InitCliSessionWlobbyTokenJob(CliSession* owner) : CliSessionJob(owner), _lgate(nullptr), _gatekey(0) {}
    virtual ~InitCliSessionWlobbyTokenJob();  // 0x54910 (scalar deleting destructor)
    virtual LobbyJobDef const* GetDefinition() const;  // 0x54830
    static void* _vtbl();  // 0x54890
    bool Initialize(LobbyGateChannel*, unsigned long long);  // 0x54960
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x54840
    virtual bool work(int, void*);  // 0x54aa0
    bool init();  // 0x54ae0
    bool initOk();  // 0x54c40

    LobbyGateChannel* _lgate;
    unsigned long long _gatekey;

public:
    static ObjPool _pool;
    static LobbyJobDef _def;
};
static_assert(sizeof(InitCliSessionWlobbyTokenJob) == 0x68, "sizeof InitCliSessionWlobbyTokenJob");
