// TakeAccountTimeBasedPlayRewardJob.obj (LobbyDaemon PDB, 2019 + PDB). Lifted from the pseudocode with PDB types.
#include <new>
#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <winsock2.h>
#include <windows.h>
#include "TakeAccountTimeBasedPlayRewardJob.h"
#include "AlertSender.h"
#include "BnsCommonConfigDefinition.h"
#include "CliSession.h"
#include "ContentsRuleConfigDefinition.h"
#include "GamedChannel.h"
#include "LiftStub.h"
#include "LobbyDaemon.h"
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "NPServiceChannel.h"
#include "Packet.h"
#include "PacketUtil.h"

static wchar_t const kFile[] = L"TakeAccountTimeBasedPlayRewardJob.cpp";

// LIFT: PDB StsMsgLib::_StsMsgResponsePromotionStampAttendPromotionSecured (sizeof 0xA0). The type is not in a
// LobbyDaemon header yet.
namespace StsMsgLib
{
struct _StsMsgResponsePromotionStampAttendPromotionSecured : public _StsMsgResponse
{
    struct _UserPromotionRewardInfo
    {
        long long nUserPromotionRewardId;
        int nRewardPolicyId;
        int nPlayedRound;
        int nDeliveryStatus;
        long long tRegistered;
    };
    int nPromotionId;
    int nLastPlayedRound;
    wchar_t* pwszAttendedMask;
    long long tNextPlayableDate;
    int nGainedPoint;
    int nAccumulatedPoint;
    int nRemainedCount;
    int nMaxPlayableCount;
    int nChanceType;
    _UserPromotionRewardInfo* pUserPromotionRewardList;
    int nUserPromotionRewardListCount;
};
static_assert(sizeof(_StsMsgResponsePromotionStampAttendPromotionSecured::_UserPromotionRewardInfo) == 0x20, "sizeof _UserPromotionRewardInfo");
static_assert(offsetof(_StsMsgResponsePromotionStampAttendPromotionSecured, nPromotionId) == 0x60, "nPromotionId");
static_assert(offsetof(_StsMsgResponsePromotionStampAttendPromotionSecured, nAccumulatedPoint) == 0x7C, "nAccumulatedPoint");
static_assert(offsetof(_StsMsgResponsePromotionStampAttendPromotionSecured, pUserPromotionRewardList) == 0x90, "pUserPromotionRewardList");
static_assert(offsetof(_StsMsgResponsePromotionStampAttendPromotionSecured, nUserPromotionRewardListCount) == 0x98, "nUserPromotionRewardListCount");
}  // namespace StsMsgLib

// The log suffix of all LobbyJob logs. The original reads the owner state 2 times (HIWORD and LOWORD).
#define JOB_LOG(logType, line, msg, fmt, ...)                                                                          \
    Log::Write(logType, kFile, line, msg L", tid:0x%I64X, type:%d, state:%d, cli-key:0x%I64X, cli-state:%d.%d" fmt,   \
               this != nullptr ? _id : 0, this != nullptr ? GetDefinition()->type : -1,                            \
               this != nullptr ? _state : -1, this != nullptr && _owner != nullptr ? _owner->_clikey : 0,          \
               HIWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0),                                  \
               LOWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0), ##__VA_ARGS__)

#define JOB_ALERT(line, msg)                                                                                           \
    AlertSender::Write(kFile, line, msg L", tid:0x%I64X, type:%d, state:%d, cli-key:0x%I64X, cli-state:%d.%d",        \
                       this != nullptr ? _id : 0, this != nullptr ? GetDefinition()->type : -1,                    \
                       this != nullptr ? _state : -1, this != nullptr && _owner != nullptr ? _owner->_clikey : 0,  \
                       HIWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0),                          \
                       LOWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0))

namespace
{
LobbyJobStateDef const StateDef[] = {{0, L"INIT"}, {1, L"TAKE_ACCOUNT_TIME_BASED_PLAY_REWARD"}, {2, L"FIN"}};  // 0x12dc00
}

LobbyJobDef TakeAccountTimeBasedPlayRewardJob::_def = {45, StateDef, 2, L"TakeAccountTimeBasedPlayRewardJob"};  // 0x201970

#include "ObjectPoolLobbyDaemon.h"

// .data 0x205120, dynamic init 0x11e3e0, atexit dtor 0x11f100.
// The exe .data holds id 1, objsize 0x90, desc L"TakeAccountTimeBasedPlayRewardJob".
ObjPool TakeAccountTimeBasedPlayRewardJob::_pool(1, 0x90, L"TakeAccountTimeBasedPlayRewardJob");

// 0x788a0
LobbyJobDef const* TakeAccountTimeBasedPlayRewardJob::GetDefinition() const
{
    return &_def;
}

// 0x788b0
// LIFT: Not done. The body calls _pool.Checkin. ObjPool is not in lift_lobbydaemon.
void TakeAccountTimeBasedPlayRewardJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x788b0);
}

// 0x78900
// The original constructs a job on the stack (null owner) and returns its vfptr. It does not run the destructor.
void* TakeAccountTimeBasedPlayRewardJob::_vtbl()
{
    char buf[sizeof(TakeAccountTimeBasedPlayRewardJob)];
    TakeAccountTimeBasedPlayRewardJob* job = ::new (buf) TakeAccountTimeBasedPlayRewardJob(nullptr);
    return *reinterpret_cast<void**>(job);
}

// 0x78980 (scalar deleting destructor)
TakeAccountTimeBasedPlayRewardJob::~TakeAccountTimeBasedPlayRewardJob()
{
    if (_gamed != nullptr)
        _gamed->removeReferenceCount(kFile, 73);
}

// 0x789d0
bool TakeAccountTimeBasedPlayRewardJob::work(int task, void* param)
{
    bool result = false;
    if (_state == INIT && task == 143)
    {
        result = init(static_cast<TakeAccountTimeBasedPlayRewardReqParam*>(param));
        task = 0;
    }
    if (_state == TAKE_ACCOUNT_TIME_BASED_PLAY_REWARD)
    {
        if (task == 0)
            return takeAccountTimeBasedPlayRewardReq();
        else if (task == 103)
            return takeAccountTimeBasedPlayRewardResponse(param);
        else if (task == 104)
            return takeAccountTimeBasedPlayRewardExpire();
    }
    return result;
}

// 0x78a50
bool TakeAccountTimeBasedPlayRewardJob::init(TakeAccountTimeBasedPlayRewardReqParam* param)
{
    if (param == nullptr || param->gamed == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 108, L"== CRASH == [job], init from game fail; invalid param", L"");
        JOB_ALERT(108, L"== CRASH == [job], init from game fail; invalid param");
        return false;
    }
    _gamed = param->gamed;
    _gameTid = param->gameTid;
    _pcdbid = param->pcdbid;
    _scheduleNumber = param->scheduleNumber;
    _playTime = param->playTime;
    _targetType = param->targetType;
    _requestTimeUTC = param->requestTimeUTC;
    short boardType = -1;
    if (_targetType == 0)
        boardType = 6;
    else if (_targetType == 1)
        boardType = 5;
    _boardType = boardType;
    if (_gamed != nullptr)
        _gamed->addReferenceCount(false, kFile, 123);
    if (_owner->_state != 0x40000)  // CSS_GAME_WORLD
    {
        JOB_LOG(Log::LT_ERROR, 127, L"[job], init from game fail; not in world state", L"");
        _gamed->SendTakeAccountTimeBasedPlayRewardFail(_gameTid, _pcdbid, _scheduleNumber, _targetType, _playTime,
                                                       _requestTimeUTC, 6, 0);
        return false;
    }
    if (!ContentsRuleConfig::GetContentsRuleConfig()->GetUseTimeBasedPlaySchedule())
    {
        JOB_LOG(Log::LT_ERROR, 134, L"[job], contents-rule-config, use-time-based-play-schedule is off", L"");
        sendFail(7, 0);
        return false;
    }
    JOB_LOG(Log::LT_DEBUG, 141, L"[job], init ok",
            L", wid:%d, game-tid:0x%I64X, pcid:0x%I64X, promotion-id:%d, board-type:%d, accumulated-point:%d, attended:%I64d",
            _gamed != nullptr ? (_gamed->_rawChannel != nullptr ? static_cast<short>(_gamed->_rawChannel->GetId()) : 0) : 0,
            _gameTid, _pcdbid, _scheduleNumber, _boardType, _playTime, _requestTimeUTC);
    transit(TAKE_ACCOUNT_TIME_BASED_PLAY_REWARD);
    return true;
}

// 0x78ec0
bool TakeAccountTimeBasedPlayRewardJob::takeAccountTimeBasedPlayRewardReq()
{
    NPGameServiceChannel* const gameServChannel = LobbyDaemon::_instance->_npServchmgr->_gameServChannel;
    if (gameServChannel == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 153, L"[job], req fail; np game-service channel N/A", L"");
        _gamed->SendTakeAccountTimeBasedPlayRewardFail(_gameTid, _pcdbid, _scheduleNumber, _targetType, _playTime,
                                                       _requestTimeUTC, 2, 0);
        return false;
    }
    NPLobbyJobTransaction* const tran =
        new (Memory::_Manager[2]->Alloc(sizeof(NPLobbyJobTransaction), kFile, 158)) NPLobbyJobTransaction;
    if (!gameServChannel->SendRequestPromotionStampAttendPromotionSecured(
            tran->Set(this, 104), _owner->_acb._userid, _scheduleNumber, _boardType, BnsCommonConfig::Config->_npGameCode,
            static_cast<short>(_playTime), _requestTimeUTC))
    {
        JOB_LOG(Log::LT_ERROR, 169, L"[job], req fail; send fail", L"");
        _gamed->SendTakeAccountTimeBasedPlayRewardFail(_gameTid, _pcdbid, _scheduleNumber, _targetType, _playTime,
                                                       _requestTimeUTC, 2, 0);
        tran->~NPLobbyJobTransaction();
        Memory::_Manager[2]->Free(tran, kFile, 171);
        return false;
    }
    JOB_LOG(Log::LT_DEBUG, 175, L"[job], req sent", L"");
    return true;
}

// 0x79220
bool TakeAccountTimeBasedPlayRewardJob::takeAccountTimeBasedPlayRewardResponse(void* param)
{
    StsMsgLib::_StsMsgResponsePromotionStampAttendPromotionSecured* const res =
        static_cast<StsMsgLib::_StsMsgResponsePromotionStampAttendPromotionSecured*>(param);
    if (res == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 182, L"[job], invalid parameter", L"");
        _gamed->SendTakeAccountTimeBasedPlayRewardFail(_gameTid, _pcdbid, _scheduleNumber, _targetType, _playTime,
                                                       _requestTimeUTC, 2, 0);
        return false;
    }
    unsigned int const statusCode = res->msgInfo.errInfo.nStatusCode;
    if (statusCode != 200 &&
        (statusCode != 400 ||
         _wcsicmp(L"Success", res->msgInfo.errInfo.pwszReason != nullptr ? res->msgInfo.errInfo.pwszReason : L"null") != 0))
    {
        JOB_LOG(Log::LT_ERROR, 189, L"[job], recv fail response",
                L", np-tid:%u, cmd:%d, type:%d, status-code:%u, reason:%s, error-code:%d", res->GetTransactionId(),
                res->GetCommand(), res->GetMessageType(), res->msgInfo.errInfo.nStatusCode,
                res->msgInfo.errInfo.pwszReason != nullptr ? res->msgInfo.errInfo.pwszReason : L"null",
                res->msgInfo.errInfo.nErrorCode);
        int const errorCode = res->msgInfo.errInfo.nErrorCode;
        short failReason = 94;
        switch (errorCode)
        {
        case 10:
            _gamed->SendTakeAccountTimeBasedPlayRewardFail(_gameTid, _pcdbid, _scheduleNumber, _targetType, _playTime,
                                                           _requestTimeUTC, 4, 10);
            return false;
        case 42:
            _gamed->SendTakeAccountTimeBasedPlayRewardFail(_gameTid, _pcdbid, _scheduleNumber, _targetType, _playTime,
                                                           _requestTimeUTC, 93, 42);
            return false;
        case 6723:
            _gamed->SendTakeAccountTimeBasedPlayRewardFail(_gameTid, _pcdbid, _scheduleNumber, _targetType, _playTime,
                                                           _requestTimeUTC, 95, 6723);
            return false;
        case 6725:
            _gamed->SendTakeAccountTimeBasedPlayRewardFail(_gameTid, _pcdbid, _scheduleNumber, _targetType, _playTime,
                                                           _requestTimeUTC, 97, 6725);
            return false;
        case 6726:
            failReason = 98;
            break;
        case 6727:
            _gamed->SendTakeAccountTimeBasedPlayRewardFail(_gameTid, _pcdbid, _scheduleNumber, _targetType, _playTime,
                                                           _requestTimeUTC, 99, 6727);
            return false;
        }
        _gamed->SendTakeAccountTimeBasedPlayRewardFail(_gameTid, _pcdbid, _scheduleNumber, _targetType, _playTime,
                                                       _requestTimeUTC, failReason, errorCode);
        return false;
    }
    JOB_LOG(Log::LT_DEBUG, 225, L"[job], attend promotion secured ok",
            L", promotion-id:%d, accumulated-point:%d, UserPromotionCount:%d, np-tid:%u, cmd:%d, type:%d, status-code:%u, "
            L"reason:%s, error-code:%d",
            res->nPromotionId, res->nAccumulatedPoint, res->nUserPromotionRewardListCount, res->GetTransactionId(),
            res->GetCommand(), res->GetMessageType(), res->msgInfo.errInfo.nStatusCode,
            res->msgInfo.errInfo.pwszReason != nullptr ? res->msgInfo.errInfo.pwszReason : L"null",
            res->msgInfo.errInfo.nErrorCode);

    UserPromotionReward deliveryUserPromotionRewards;
    UserPromotionReward deliverySuccessUserPromotionRewards;
    UserPromotionReward deliveryFailUserPromotionRewards;
    wchar_t failBuffCount[260] = {0};
    int count = res->nUserPromotionRewardListCount;
    if (count > 24)
        count = 24;
    for (int i = 0; i < count; ++i)
    {
        StsMsgLib::_StsMsgResponsePromotionStampAttendPromotionSecured::_UserPromotionRewardInfo const& info =
            res->pUserPromotionRewardList[i];
        deliveryUserPromotionRewards.userPromotionRewardId[deliveryUserPromotionRewards.rewardCount] = info.nUserPromotionRewardId;
        deliveryUserPromotionRewards.rewardPolicyId[deliveryUserPromotionRewards.rewardCount] = info.nRewardPolicyId;
        ++deliveryUserPromotionRewards.rewardCount;
        if (info.nDeliveryStatus == 3)
        {
            deliverySuccessUserPromotionRewards.userPromotionRewardId[deliverySuccessUserPromotionRewards.rewardCount] =
                info.nUserPromotionRewardId;
            deliverySuccessUserPromotionRewards.rewardPolicyId[deliverySuccessUserPromotionRewards.rewardCount] =
                info.nRewardPolicyId;
            ++deliverySuccessUserPromotionRewards.rewardCount;
        }
        else
        {
            deliveryFailUserPromotionRewards.userPromotionRewardId[deliveryFailUserPromotionRewards.rewardCount] =
                info.nUserPromotionRewardId;
            deliveryFailUserPromotionRewards.rewardPolicyId[deliveryFailUserPromotionRewards.rewardCount] =
                info.nRewardPolicyId;
            wchar_t idsStr[128] = {0};
            swprintf_s(idsStr, 128, L"%I64d|%d,",
                       deliveryFailUserPromotionRewards.userPromotionRewardId[deliveryFailUserPromotionRewards.rewardCount],
                       deliveryFailUserPromotionRewards.rewardPolicyId[deliveryFailUserPromotionRewards.rewardCount]);
            wcsncat(failBuffCount, idsStr, 128);
            ++deliveryFailUserPromotionRewards.rewardCount;
        }
    }
    _owner->UpdateTimeBasedPlayReward(_pcdbid, _scheduleNumber, _targetType, static_cast<short>(res->nAccumulatedPoint),
                                      deliverySuccessUserPromotionRewards, _requestTimeUTC);
    if (res->nUserPromotionRewardListCount == 0)
    {
        _gamed->SendTakeAccountTimeBasedPlayRewardFail(_gameTid, _pcdbid, _scheduleNumber, _targetType, _playTime,
                                                       _requestTimeUTC, 96, 0);
        return false;
    }
    sendOk(deliveryUserPromotionRewards, static_cast<short>(deliveryFailUserPromotionRewards.rewardCount));
    if (deliveryFailUserPromotionRewards.rewardCount > 0)
    {
        JOB_LOG(Log::LT_ERROR, 280, L"[job], attend promotion secured ok. but delivery failed found.",
                L", promotion-id:%d, accumulated-point:%d, UserPromotionCount:%d, "
                L"Failed(UserPromotionRewardIds|RewardPolicyId):[%s]",
                res->nPromotionId, res->nAccumulatedPoint, res->nUserPromotionRewardListCount, failBuffCount);
    }
    transit(FIN);
    return true;
}

// 0x79a00
bool TakeAccountTimeBasedPlayRewardJob::takeAccountTimeBasedPlayRewardExpire()
{
    JOB_LOG(Log::LT_ERROR, 317, L"[job], expired", L"");
    _gamed->SendTakeAccountTimeBasedPlayRewardFail(_gameTid, _pcdbid, _scheduleNumber, _targetType, _playTime,
                                                   _requestTimeUTC, 93, 42);
    transit(FIN);
    return true;
}

// 0x79b30
void TakeAccountTimeBasedPlayRewardJob::sendOk(UserPromotionReward& rewards, short deliveryFailCount)
{
    RepeatPacketComposer rpc;  // LIFT: inlined constructor
    rpc.format = nullptr;
    rpc.len = 0;
    rpc.index = 0;
    rpc.SetFormat("hqqiQhqhCQiqqihcccc;Cqi;", 0);
    rpc.top = -1;
    rpc.subTop = -1;
    Packet p;
    p.Allocate();
    if (p.Compose(&rpc, 8, 105, _gameTid, _pcdbid, _scheduleNumber, static_cast<int>(_targetType), _playTime,
                  _requestTimeUTC, static_cast<int>(deliveryFailCount)) == 0)
    {
        Log::Write(Log::LT_ERROR, kFile, 334,
                   L"[game-lobby], TakeAccountTimeBasedPlayRewardJob::sendOk, packet compose failed, gameTid:%#I64X, "
                   L"pcDbId:%#I64X, scheduleNumber:%d, targetType:%d, playTime:%d, requestTime:%I64d, deliveryFailCount:%d",
                   _gameTid, _pcdbid, _scheduleNumber, _targetType, _playTime, _requestTimeUTC, deliveryFailCount);
        return;
    }
    bool composed;
    {
        CliSession* const owner = _owner;
        EnterCriticalSection(&owner->_lock.CS);
        composed = owner->_acb._timeBasedPlayInfoList.Compose(rpc, p);
        LeaveCriticalSection(&owner->_lock.CS);
    }
    if (!composed)
    {
        Log::Write(Log::LT_ERROR, kFile, 341,
                   L"[game-lobby], TakeAccountTimeBasedPlayRewardJob::sendOk, packet compose failed2, gameTid:%#I64X, "
                   L"pcDbId:%#I64X, scheduleNumber:%d, targetType:%d, playTime:%d, requestTime:%I64d, deliveryFailCount:%d",
                   _gameTid, _pcdbid, _scheduleNumber, _targetType, _playTime, _requestTimeUTC, deliveryFailCount);
        return;
    }
    rpc.PushRepeatCount(&p);
    if (rewards.rewardCount > 0)
    {
        unsigned short const freeSize = p.CurHeader != nullptr ? static_cast<unsigned short>(4000 - p.CurHeader->size) : 0;
        if (freeSize < 12ull * rewards.rewardCount)
            p.Allocate();
    }
    for (int i = 0; i < rewards.rewardCount; ++i)
    {
        if (p.Compose(&rpc, 2, rewards.userPromotionRewardId[i], rewards.rewardPolicyId[i]) == 0)
            return;
        rpc.IncRepeatCount();
    }
    rpc.PopRepeatCount();
    _gamed->Send(&p);
}

// 0x79eb0
void TakeAccountTimeBasedPlayRewardJob::sendFail(short failReason, int errCode)
{
    _gamed->SendTakeAccountTimeBasedPlayRewardFail(_gameTid, _pcdbid, _scheduleNumber, _targetType, _playTime,
                                                   _requestTimeUTC, failReason, errCode);
}
