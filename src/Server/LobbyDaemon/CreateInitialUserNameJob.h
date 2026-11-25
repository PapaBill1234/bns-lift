// CreateInitialUserNameJob.obj (LobbyDaemon PDB, 2019 + PDB). Layout from tools/pdbcls.py LobbyDaemon
// CreateInitialUserNameJob.
#pragma once
#include <stddef.h>
#include "CliSessionJob.h"

class CliSession;
class LobbyGateChannel;
class ObjPool;
struct LobbyJobDef;

// PDB layout (sizeof 0x68, CliSessionJob base).
class CreateInitialUserNameJob : public CliSessionJob
{
public:
    enum State
    {
        INIT = 0,
        CHANGE_USER_NAME = 1,
        FIN = 2
    };

    // LIFT: the constructor has no own RVA. It is inlined in _vtbl (0x2fc80) and in the job factory.
    CreateInitialUserNameJob(CliSession* owner) : CliSessionJob(owner), _lgate(nullptr), _newUserName(nullptr) {}
    virtual LobbyJobDef const* GetDefinition() const;  // 0x2fc20
    static void* _vtbl();  // 0x2fc80
    virtual ~CreateInitialUserNameJob();  // 0x2fd20
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x2fc30
    virtual bool work(int, void*);  // 0x2fda0
    bool init(void*);  // 0x2fe20
    bool changeUserNameReq();  // 0x30660
    bool changeUserNameAck(void*);  // 0x30980
    bool changeUserNameExpire();  // 0x30d90

    LobbyGateChannel* _lgate;  // +0x58
    wchar_t* _newUserName;  // +0x60

public:
    static ObjPool _pool;
    static LobbyJobDef _def;

    friend struct CreateInitialUserNameJobLayoutCheck;
};

struct CreateInitialUserNameJobLayoutCheck
{
    static_assert(sizeof(CreateInitialUserNameJob) == 0x68, "sizeof CreateInitialUserNameJob");
    static_assert(offsetof(CreateInitialUserNameJob, _lgate) == 0x58, "CreateInitialUserNameJob::_lgate");
    static_assert(offsetof(CreateInitialUserNameJob, _newUserName) == 0x60, "CreateInitialUserNameJob::_newUserName");
};
