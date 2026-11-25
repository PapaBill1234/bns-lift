// SecondPasswordIsVerifiedJob.obj (LobbyDaemon PDB, 2019 + PDB). Layout from tools/pdbcls.py LobbyDaemon SecondPasswordIsVerifiedJob.
#pragma once
#include <stddef.h>
#include "CliSessionJob.h"

class CliSession;
class GamedChannel;
class ObjPool;
struct LobbyJobDef;

// PDB GameSecondPasswordIsVerifiedReqParam (sizeof 0x20). LobbyGamePacketHandler.cpp (0x91e80) fills it.
struct GameSecondPasswordIsVerifiedReqParam
{
    GamedChannel* gamed;
    unsigned long long gametid;
    unsigned long long pcid;
    char type;
    char actionIndex;
};
static_assert(sizeof(GameSecondPasswordIsVerifiedReqParam) == 0x20, "sizeof GameSecondPasswordIsVerifiedReqParam");
static_assert(offsetof(GameSecondPasswordIsVerifiedReqParam, type) == 0x18, "GameSecondPasswordIsVerifiedReqParam::type");
static_assert(offsetof(GameSecondPasswordIsVerifiedReqParam, actionIndex) == 0x19, "GameSecondPasswordIsVerifiedReqParam::actionIndex");

// PDB layout (sizeof 0x78, CliSessionJob base).
class SecondPasswordIsVerifiedJob : public CliSessionJob
{
public:
    enum State
    {
        INIT = 0,
        IS_VERIFIED = 1,
        FIN = 2
    };

    static void* _vtbl();  // 0x72170
    // The binary has no body for the constructor. The callers inline it.
    SecondPasswordIsVerifiedJob(CliSession* owner) : CliSessionJob(owner), _gamed(nullptr), _gametid(0), _pcid(0), _type(0), _actionIndex(0) {}
    virtual ~SecondPasswordIsVerifiedJob();  // 0x721f0 (scalar deleting destructor)
    virtual LobbyJobDef const* GetDefinition() const;  // 0x72110
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x72120
    virtual bool work(int, void*);  // 0x72240
    bool init(void*);  // 0x722c0
    bool requestIsVerified();  // 0x72640
    bool responseIsVerified(void*);  // 0x728d0
    bool expireIsVerified();  // 0x72bf0

    GamedChannel* _gamed;  // +0x58
    unsigned long long _gametid;  // +0x60
    unsigned long long _pcid;  // +0x68
    char _type;  // +0x70
    char _actionIndex;  // +0x71

public:
    static ObjPool _pool;  // LIFT: defined in the .cpp (gap-26).
    static LobbyJobDef _def;

    friend struct SecondPasswordIsVerifiedJobLayoutCheck;
};

struct SecondPasswordIsVerifiedJobLayoutCheck
{
    static_assert(sizeof(SecondPasswordIsVerifiedJob) == 0x78, "sizeof SecondPasswordIsVerifiedJob");
    static_assert(offsetof(SecondPasswordIsVerifiedJob, _gamed) == 0x58, "SecondPasswordIsVerifiedJob::_gamed");
    static_assert(offsetof(SecondPasswordIsVerifiedJob, _gametid) == 0x60, "SecondPasswordIsVerifiedJob::_gametid");
    static_assert(offsetof(SecondPasswordIsVerifiedJob, _pcid) == 0x68, "SecondPasswordIsVerifiedJob::_pcid");
    static_assert(offsetof(SecondPasswordIsVerifiedJob, _type) == 0x70, "SecondPasswordIsVerifiedJob::_type");
    static_assert(offsetof(SecondPasswordIsVerifiedJob, _actionIndex) == 0x71, "SecondPasswordIsVerifiedJob::_actionIndex");
};
