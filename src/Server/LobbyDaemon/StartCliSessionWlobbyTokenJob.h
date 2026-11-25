// StartCliSessionWlobbyTokenJob.obj (LobbyDaemon PDB, 2019 + PDB). Layout from tools/pdbcls.py LobbyDaemon StartCliSessionWlobbyTokenJob.
#pragma once
#include <stddef.h>
#include "CliSessionJob.h"

class CliSession;
class LobbyGateChannel;
class ObjPool;
struct LobbyJobDef;

// LIFT: PDB layout (CliSessionJob base). The PDB constructor has no body. It is inlined in the callers.
class StartCliSessionWlobbyTokenJob : public CliSessionJob
{
public:
    enum State
    {
        INIT = 0,
        GET_GRADE_LEVEL = 1,
        LIST_ALL_GRADES = 2,
        START = 3,
        FIN = 4
    };

    StartCliSessionWlobbyTokenJob(CliSession* owner) : CliSessionJob(owner), _lgate(nullptr) {}
    virtual ~StartCliSessionWlobbyTokenJob();  // 0x76330 (scalar deleting destructor)
    virtual LobbyJobDef const* GetDefinition() const;  // 0x76250
    static void* _vtbl();  // 0x762b0
    bool Initialize(LobbyGateChannel*);  // 0x76380
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x76260
    virtual bool work(int, void*);  // 0x76490
    bool init();  // 0x76550
    bool getGradeLevelReq();  // 0x76720
    bool getGradeLevelResponse(void*);  // 0x76a50
    bool getGradeLevelExpire();  // 0x76f30
    bool listAllGradesReq();  // 0x77050
    bool listAllGradesResponse(void*);  // 0x77340
    bool listAllGradesExpire();  // 0x777f0
    bool start();  // 0x77910

    LobbyGateChannel* _lgate;

public:
    static ObjPool _pool;
    static LobbyJobDef _def;
};
static_assert(sizeof(StartCliSessionWlobbyTokenJob) == 0x60, "sizeof StartCliSessionWlobbyTokenJob");
