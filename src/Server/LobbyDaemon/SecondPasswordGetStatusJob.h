// SecondPasswordGetStatusJob.obj (LobbyDaemon PDB, 2019 + PDB). Layout from tools/pdbcls.py LobbyDaemon SecondPasswordGetStatusJob.
#pragma once
#include <stddef.h>
#include "CliSessionJob.h"

class CliSession;
class GamedChannel;
class ObjPool;
struct LobbyJobDef;

// PDB GameSecondPasswordGetStatusReqParam (sizeof 0x20). LobbyGamePacketHandler.cpp (0x91ab0) fills it.
struct GameSecondPasswordGetStatusReqParam
{
    GamedChannel* gamed;
    unsigned long long gametid;
    unsigned long long pcid;
    char type;
};
static_assert(sizeof(GameSecondPasswordGetStatusReqParam) == 0x20, "sizeof GameSecondPasswordGetStatusReqParam");
static_assert(offsetof(GameSecondPasswordGetStatusReqParam, type) == 0x18, "GameSecondPasswordGetStatusReqParam::type");

// PDB layout (sizeof 0x78, CliSessionJob base).
class SecondPasswordGetStatusJob : public CliSessionJob
{
public:
    enum State
    {
        INIT = 0,
        GET_STATUS = 1,
        FIN = 2
    };

    static void* _vtbl();  // 0x715b0
    // The binary has no body for the constructor. The callers inline it.
    SecondPasswordGetStatusJob(CliSession* owner) : CliSessionJob(owner), _gamed(nullptr), _gametid(0), _pcid(0), _type(0) {}
    virtual ~SecondPasswordGetStatusJob();  // 0x71630 (scalar deleting destructor)
    virtual LobbyJobDef const* GetDefinition() const;  // 0x71550
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x71560
    virtual bool work(int, void*);  // 0x71680
    bool init(void*);  // 0x71700
    bool requestGetStatus();  // 0x71a60
    bool responseGetStatus(void*);  // 0x71ce0
    bool expireGetStatus();  // 0x72010

    GamedChannel* _gamed;  // +0x58
    unsigned long long _gametid;  // +0x60
    unsigned long long _pcid;  // +0x68
    char _type;  // +0x70

public:
    static ObjPool _pool;
    static LobbyJobDef _def;

    friend struct SecondPasswordGetStatusJobLayoutCheck;
};

struct SecondPasswordGetStatusJobLayoutCheck
{
    static_assert(sizeof(SecondPasswordGetStatusJob) == 0x78, "sizeof SecondPasswordGetStatusJob");
    static_assert(offsetof(SecondPasswordGetStatusJob, _gamed) == 0x58, "SecondPasswordGetStatusJob::_gamed");
    static_assert(offsetof(SecondPasswordGetStatusJob, _gametid) == 0x60, "SecondPasswordGetStatusJob::_gametid");
    static_assert(offsetof(SecondPasswordGetStatusJob, _pcid) == 0x68, "SecondPasswordGetStatusJob::_pcid");
    static_assert(offsetof(SecondPasswordGetStatusJob, _type) == 0x70, "SecondPasswordGetStatusJob::_type");
};
