// TakeAccountTimeBasedPlayRewardJob.obj (LobbyDaemon PDB, 2019 + PDB). Layout from tools/pdbcls.py LobbyDaemon TakeAccountTimeBasedPlayRewardJob.
#pragma once
#include <stddef.h>
#include <string.h>
#include "CliSessionJob.h"

class CliSession;
class GamedChannel;
class ObjPool;
struct LobbyJobDef;

// PDB TakeAccountTimeBasedPlayRewardReqParam (sizeof 0x28). LobbyGamePacketHandler.cpp (0x94910) fills it.
struct TakeAccountTimeBasedPlayRewardReqParam
{
    GamedChannel* gamed;
    unsigned long long gameTid;
    unsigned long long pcdbid;
    int scheduleNumber;
    short playTime;
    char targetType;
    long long requestTimeUTC;
};
static_assert(sizeof(TakeAccountTimeBasedPlayRewardReqParam) == 0x28, "sizeof TakeAccountTimeBasedPlayRewardReqParam");
static_assert(offsetof(TakeAccountTimeBasedPlayRewardReqParam, playTime) == 0x1C, "TakeAccountTimeBasedPlayRewardReqParam::playTime");
static_assert(offsetof(TakeAccountTimeBasedPlayRewardReqParam, targetType) == 0x1E, "TakeAccountTimeBasedPlayRewardReqParam::targetType");
static_assert(offsetof(TakeAccountTimeBasedPlayRewardReqParam, requestTimeUTC) == 0x20, "TakeAccountTimeBasedPlayRewardReqParam::requestTimeUTC");

// PDB UserPromotionReward (sizeof 0x128). The PDB has an inline constructor. The job inlines it 3 times.
struct UserPromotionReward
{
    UserPromotionReward() : rewardCount(0)
    {
        memset(userPromotionRewardId, 0, sizeof(userPromotionRewardId));
        memset(rewardPolicyId, 0, sizeof(rewardPolicyId));
    }

    long long userPromotionRewardId[24];
    int rewardPolicyId[24];
    int rewardCount;
};
static_assert(sizeof(UserPromotionReward) == 0x128, "sizeof UserPromotionReward");
static_assert(offsetof(UserPromotionReward, rewardPolicyId) == 0xC0, "UserPromotionReward::rewardPolicyId");
static_assert(offsetof(UserPromotionReward, rewardCount) == 0x120, "UserPromotionReward::rewardCount");

// PDB layout (sizeof 0x90, CliSessionJob base). The PDB also has requestRewardDelivery(UserPromotionReward&). The
// binary has no body for it. It is not declared here.
class TakeAccountTimeBasedPlayRewardJob : public CliSessionJob
{
public:
    enum State
    {
        INIT = 0,
        TAKE_ACCOUNT_TIME_BASED_PLAY_REWARD = 1,
        FIN = 2
    };

    static void* _vtbl();  // 0x78900
    // The binary has no body for the constructor. The callers inline it.
    TakeAccountTimeBasedPlayRewardJob(CliSession* owner)
        : CliSessionJob(owner), _gamed(nullptr), _gameTid(0), _pcdbid(0), _scheduleNumber(0), _playTime(0), _targetType(0),
          _requestTimeUTC(0), _boardType(0)
    {
    }
    virtual ~TakeAccountTimeBasedPlayRewardJob();  // 0x78980 (scalar deleting destructor)
    virtual LobbyJobDef const* GetDefinition() const;  // 0x788a0
private:
    virtual void deallocate_me(void*, wchar_t const*, int);  // 0x788b0
    virtual bool work(int, void*);  // 0x789d0
    bool init(TakeAccountTimeBasedPlayRewardReqParam*);  // 0x78a50
    bool takeAccountTimeBasedPlayRewardReq();  // 0x78ec0
    bool takeAccountTimeBasedPlayRewardResponse(void*);  // 0x79220
    bool takeAccountTimeBasedPlayRewardExpire();  // 0x79a00
    void sendFail(short, int);  // 0x79eb0
    void sendOk(UserPromotionReward&, short);  // 0x79b30

    GamedChannel* _gamed;  // +0x58
    unsigned long long _gameTid;  // +0x60
    unsigned long long _pcdbid;  // +0x68
    int _scheduleNumber;  // +0x70
    int _playTime;  // +0x74
    char _targetType;  // +0x78
    long long _requestTimeUTC;  // +0x80
    short _boardType;  // +0x88

public:
    static ObjPool _pool;
    static LobbyJobDef _def;

    friend struct TakeAccountTimeBasedPlayRewardJobLayoutCheck;
};

struct TakeAccountTimeBasedPlayRewardJobLayoutCheck
{
    static_assert(sizeof(TakeAccountTimeBasedPlayRewardJob) == 0x90, "sizeof TakeAccountTimeBasedPlayRewardJob");
    static_assert(offsetof(TakeAccountTimeBasedPlayRewardJob, _gamed) == 0x58, "TakeAccountTimeBasedPlayRewardJob::_gamed");
    static_assert(offsetof(TakeAccountTimeBasedPlayRewardJob, _scheduleNumber) == 0x70, "TakeAccountTimeBasedPlayRewardJob::_scheduleNumber");
    static_assert(offsetof(TakeAccountTimeBasedPlayRewardJob, _playTime) == 0x74, "TakeAccountTimeBasedPlayRewardJob::_playTime");
    static_assert(offsetof(TakeAccountTimeBasedPlayRewardJob, _targetType) == 0x78, "TakeAccountTimeBasedPlayRewardJob::_targetType");
    static_assert(offsetof(TakeAccountTimeBasedPlayRewardJob, _requestTimeUTC) == 0x80, "TakeAccountTimeBasedPlayRewardJob::_requestTimeUTC");
    static_assert(offsetof(TakeAccountTimeBasedPlayRewardJob, _boardType) == 0x88, "TakeAccountTimeBasedPlayRewardJob::_boardType");
};
