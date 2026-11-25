// ActivateGradeJob.obj (LobbyDaemon PDB, 2019 + PDB). Layout from tools/pdbcls.py LobbyDaemon ActivateGradeJob.
#pragma once
#include <stddef.h>
#include "CliSessionJob.h"

class CliSession;
class GamedChannel;
class LobbyGateChannel;
class ObjPool;
struct LobbyJobDef;

// PDB LobbyGate_ActivateGradeReqParam (sizeof 0x10). The lobby-gate packet handler gives it with task 28.
struct LobbyGate_ActivateGradeReqParam
{
    LobbyGateChannel* lgate;
    int gameGradeKey;
    int gradeId;
};
static_assert(sizeof(LobbyGate_ActivateGradeReqParam) == 0x10, "sizeof LobbyGate_ActivateGradeReqParam");

// PDB Game_ActivateGradeReqParam (sizeof 0x20). The game packet handler gives it with task 134.
struct Game_ActivateGradeReqParam
{
    GamedChannel* gamed;
    unsigned long long gameTid;
    unsigned long long pcid;
    int gameGradeKey;
    int gradeId;
};
static_assert(sizeof(Game_ActivateGradeReqParam) == 0x20, "sizeof Game_ActivateGradeReqParam");
static_assert(offsetof(Game_ActivateGradeReqParam, gameGradeKey) == 0x18, "Game_ActivateGradeReqParam::gameGradeKey");

// PDB layout (sizeof 0x80, CliSessionJob base).
class ActivateGradeJob : public CliSessionJob
{
public:
    enum State
    {
        INIT = 0,
        ACTIVATE_GRADE = 1,
        FIN = 2
    };
    enum ErrCode
    {
        ERR_UNKNOWN_ERROR = 0,
        ERR_SYSTEM_ERROR = 1,
        ERR_INVALID_SESSION_STATE = 2,
        ERR_INVALID_PARAMETER = 3,
        ERR_EXISTS_ACTIVATED_USERGRADE = 4,
        ERR_NO_AVAILABLE_USERGRADE = 5
    };

    virtual LobbyJobDef const* GetDefinition() const;  // 0xbac0
    static void* _vtbl();  // 0xbb20
    ActivateGradeJob(CliSession*);  // 0xbba0
    virtual ~ActivateGradeJob();  // 0xbc00
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0xbad0
    virtual bool work(int, void*);  // 0xbc70
    bool initFromLobbyGate(LobbyGate_ActivateGradeReqParam*);  // 0xbd00
    bool initFromGame(Game_ActivateGradeReqParam*);  // 0xc1a0
    bool activateGradeReq();  // 0xc670
    bool activateGradeResponse(void*);  // 0xca10
    bool activateGradeExpire();  // 0xcf50
    void sendFail(int);  // 0xd0a0
    void sendOk(int, int, long long, long long);  // PDB inline (inlined in activateGradeResponse)

public:
    LobbyGateChannel* _lgate;
    GamedChannel* _gamed;
    unsigned long long _gameTid;
    unsigned long long _pcid;
    int _gameGradeKey;
    int _gradeId;

    static ObjPool _pool;
    static LobbyJobDef _def;
};
static_assert(sizeof(ActivateGradeJob) == 0x80, "sizeof ActivateGradeJob");
static_assert(offsetof(ActivateGradeJob, _lgate) == 0x58, "ActivateGradeJob::_lgate");
static_assert(offsetof(ActivateGradeJob, _gamed) == 0x60, "ActivateGradeJob::_gamed");
static_assert(offsetof(ActivateGradeJob, _gameTid) == 0x68, "ActivateGradeJob::_gameTid");
static_assert(offsetof(ActivateGradeJob, _pcid) == 0x70, "ActivateGradeJob::_pcid");
static_assert(offsetof(ActivateGradeJob, _gameGradeKey) == 0x78, "ActivateGradeJob::_gameGradeKey");
static_assert(offsetof(ActivateGradeJob, _gradeId) == 0x7C, "ActivateGradeJob::_gradeId");
