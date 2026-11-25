// StartCliSessionWnpTokenJob.obj (LobbyDaemon PDB, 2019 + PDB). Lifted from the pseudocode with PDB types.
// LIFT: the functions that still have LIFT_STUB bodies are not done (gap-13 and later cards).
#include <new>
#include <stdlib.h>
#include <wchar.h>
#include <winsock2.h>
#include <windows.h>
#if defined(__clang__)
#include "crt_cpp_overload.h"
#endif
#include "StartCliSessionWnpTokenJob.h"
#include "AlertSender.h"
#include "BnsCommonConfigDefinition.h"
#include "CliSession.h"
#include "LiftStub.h"
#include "LobbyDaemon.h"
#include "LobbyGateChannel.h"
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "NPServiceChannel.h"

static wchar_t const kFile[] = L"StartCliSessionWnpTokenJob.cpp";

// The log suffix of all LobbyJob logs. The original reads the owner state 2 times (HIWORD and LOWORD).
#define JOB_LOG(logType, line, msg, fmt, ...)                                                                          \
    Log::Write(logType, kFile, line, msg L", tid:0x%I64X, type:%d, state:%d, cli-key:0x%I64X, cli-state:%d.%d" fmt,   \
               this != nullptr ? _id : 0, this != nullptr ? GetDefinition()->type : -1,                            \
               this != nullptr ? _state : -1, this != nullptr && _owner != nullptr ? _owner->_clikey : 0,          \
               HIWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0),                                  \
               LOWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0), ##__VA_ARGS__)

// The "== CRASH ==" form: the log and then the alert with the same text. Each call reads its arguments again.
#define JOB_CRASH(line, msg)                                                                                         \
    do                                                                                                               \
    {                                                                                                                \
        JOB_LOG(Log::LT_ERROR, line, msg, L"");                                                                      \
        AlertSender::Write(kFile, line, msg L", tid:0x%I64X, type:%d, state:%d, cli-key:0x%I64X, cli-state:%d.%d",   \
                           this != nullptr ? _id : 0, this != nullptr ? GetDefinition()->type : -1,                 \
                           this != nullptr ? _state : -1,                                                            \
                           this != nullptr && _owner != nullptr ? _owner->_clikey : 0,                              \
                           HIWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0),                       \
                           LOWORD(this != nullptr && _owner != nullptr ? _owner->_state : 0));                      \
    } while (0)

namespace
{
LobbyJobStateDef const StateDef[] = {{0, L"INIT"},
                                     {1, L"CONSUME_TOKEN"},
                                     {2, L"CHECK_SECOND_PASSWD"},
                                     {3, L"CHECK_ACTIVITY_LIST_USER_LAST_PRESENCES"},
                                     {4, L"CHECK_ACTIVITY_LIST_SLOTS"},
                                     {5, L"CHECK_ACTIVITY_CREATE_SLOTS"},
                                     {6, L"CHECK_ACTIVITY_SET_SLOT_DATA"},
                                     {7, L"PRESENCE_LOGIN"},
                                     {8, L"GET_USER_PROFILE"},
                                     {9, L"GET_GAME_TIME"},
                                     {10, L"GET_GRADE_LEVEL"},
                                     {11, L"LIST_ALL_GRADES"},
                                     {12, L"GET_CONTENT_BAN"},
                                     {13, L"GET_RMS_INQUIRY"},
                                     {14, L"GET_GET_USER_PROMOTION_STATUS"},
                                     {15, L"LOGIN_ACCOUNT"},
                                     {16, L"FIN"}};  // 0x12d890
}

LobbyJobDef StartCliSessionWnpTokenJob::_def = {2, StateDef, 16, L"StartCliSessionWnpTokenJob"};  // 0x201248
// LIFT: StartCliSessionWnpTokenJob::_pool (0x2056b0) has no definition. The LobbyDaemon ObjectPool module is not in
// lift_lobbydaemon (see CliSession.cpp).

// 0xd2340
LobbyJobDef const* StartCliSessionWnpTokenJob::GetDefinition() const
{
    return &_def;
}

// 0xd2350
// LIFT: Not done. The body calls _pool.Checkin. ObjPool is not in lift_lobbydaemon.
void StartCliSessionWnpTokenJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0xd2350);
}

// 0xd23a0
StartCliSessionWnpTokenJob::StartCliSessionWnpTokenJob(CliSession* owner)
    : CliSessionJob(owner), _lgate(nullptr), _clikey(0),
      _nptoken(ID128_ID_ZERO), _portalAccountId(ID128_ID_ZERO), _gameAccountId(ID128_ID_ZERO), _userId(ID128_ID_ZERO),
      _activityStatus(0), _activitySlotId(ID128_ID_ZERO), _gameTimeSchedule(nullptr),
      _lastGetUserPromotionStatusTargetType(0), _lastGetUserPromotionStatusPromotionId(0)
{
    // The original copies the zero ids from the global ID128_ID_ZERO (rva 0x12D870).
    _gameAccountName[0] = 0;
    _userName[0] = 0;
    _timeBasedPromotionIds[0] = 0;
    _timeBasedPromotionIds[1] = 0;
}

// 0xd24a0 (scalar deleting destructor 0xd2480)
StartCliSessionWnpTokenJob::~StartCliSessionWnpTokenJob()
{
    // The original clears the NP token first (copy of ID128_ID_ZERO).
    _nptoken = ID128_ID_ZERO;
    if (_lgate != nullptr)
        _lgate->removeReferenceCount(kFile, 132);
    if (_gameTimeSchedule != nullptr)
    {
        Memory::_Manager[2]->Free(_gameTimeSchedule, kFile, 135);
        _gameTimeSchedule = nullptr;
    }
}

// 0xd2530
bool StartCliSessionWnpTokenJob::work(int task, void* param)
{
    bool result = false;
    if (_state == INIT && task == 8)
    {
        result = init(task, param);
        task = 0;
    }
    if (_state == CONSUME_TOKEN)
    {
        if (task == 0)
            result = consumeToken(task, param);
        else if (task == 34)
        {
            result = consumeTokenResponse(task, param);
            task = 0;
        }
        else if (task == 35)
        {
            result = consumeTokenExpire();
            task = 0;
        }
    }
    if (_state == CHECK_ACTIVITY_LIST_USER_LAST_PRESENCES)
    {
        if (task == 0)
            result = listUserLastPresencesReq();
        else if (task == 72)
        {
            result = listUserLastPresencesResponse(param);
            task = 0;
        }
        else if (task == 73)
        {
            result = listUserLastPresencesExpire();
            task = 0;
        }
    }
    if (_state == CHECK_ACTIVITY_LIST_SLOTS)
    {
        if (task == 0)
            result = listSlotsReq();
        else if (task == 39)
        {
            result = listSlotsResponse(param);
            task = 0;
        }
        else if (task == 40)
        {
            result = listSlotsExpire();
            task = 0;
        }
    }
    if (_state == CHECK_ACTIVITY_CREATE_SLOTS)
    {
        if (task == 0)
            result = createSlotsReq();
        else if (task == 41)
        {
            result = createSlotsResponse(param);
            task = 0;
        }
        else if (task == 42)
        {
            result = createSlotsExpire();
            task = 0;
        }
    }
    if (_state == CHECK_ACTIVITY_SET_SLOT_DATA)
    {
        if (task == 0)
            result = setSlotDataReq();
        else if (task == 43)
        {
            result = setSlotDataResponse(param);
            task = 0;
        }
        else if (task == 44)
        {
            result = setSlotDataExpire();
            task = 0;
        }
    }
    if (_state == PRESENCE_LOGIN)
    {
        if (task == 0)
            result = presenceLoginReq();
        else if (task == 45)
        {
            result = presenceLoginResponse(param);
            task = 0;
        }
        else if (task == 46)
        {
            result = presenceLoginExpire();
            task = 0;
        }
    }
    if (_state == GET_USER_PROFILE)
    {
        if (task == 0)
            result = getUserProfileReq();
        else if (task == 93)
        {
            result = getUserProfileResponse(param);
            task = 0;
        }
        else if (task == 94)
        {
            result = getUserProfileExpire();
            task = 0;
        }
    }
    if (_state == GET_GAME_TIME)
    {
        if (task == 0)
            result = getGameTimeReq();
        else if (task == 95)
        {
            result = getGameTimeResponse(param);
            task = 0;
        }
        else if (task == 96)
        {
            result = getGameTimeExpire();
            task = 0;
        }
    }
    if (_state == GET_GRADE_LEVEL)
    {
        if (task == 0)
            result = getGradeLevelReq();
        else if (task == 78)
        {
            result = getGradeLevelResponse(param);
            task = 0;
        }
        else if (task == 79)
        {
            result = getGradeLevelExpire();
            task = 0;
        }
    }
    if (_state == LIST_ALL_GRADES)
    {
        if (task == 0)
            result = listAllGradesReq();
        else if (task == 76)
        {
            result = listAllGradesResponse(param);
            task = 0;
        }
        else if (task == 77)
        {
            result = listAllGradesExpire();
            task = 0;
        }
    }
    if (_state == GET_CONTENT_BAN)
    {
        if (task == 0)
            result = listUserBansReq();
        else if (task == 87)
        {
            result = listUserBansResponse(param);
            task = 0;
        }
        else if (task == 88)
        {
            result = listUserBansExpire();
            task = 0;
        }
    }
    if (_state == GET_RMS_INQUIRY)
    {
        if (task == 0)
            result = getRMSInquiryReq();
        else if (task == 89)
        {
            result = getRMSInquiryResponse(param);
            task = 0;
        }
        else if (task == 90)
        {
            result = getRMSInquiryExpire();
            task = 0;
        }
    }
    if (_state == GET_GET_USER_PROMOTION_STATUS)
    {
        if (task == 0)
            result = getUserPromotionStatusReq();
        else if (task == 101)
        {
            result = getUserPromotionStatusResponse(param);
            task = 0;
        }
        else if (task == 102)
        {
            result = getUserPromotionStatusExpire();
            task = 0;
        }
    }
    if (_state == LOGIN_ACCOUNT && task == 0)
        return loginAccount();
    return result;
}

// 0xd2840
// LIFT: Not done. The body builds a LobbyGatePresence (PDB inline constructor). CliSession.h has no copy of it yet.
bool StartCliSessionWnpTokenJob::init(int, void*)
{
    LIFT_STUB(0xd2840);
}

// 0xd31e0
bool StartCliSessionWnpTokenJob::consumeToken(int, void*)
{
    NPGameServiceChannel* const gs = LobbyDaemon::_instance->_npServchmgr->_gameServChannel;
    if (gs == nullptr)
    {
        JOB_CRASH(420, L"== CRASH == [job], game-service channel unavailable");
        _lgate->SendStartSessionWithNPTokenFail(_owner->_clikey, 2);
        _owner->_state = 0x60000;  // PDB ECliSessionState CSS_FIN
        _owner->finalize();
        return false;
    }
    NPLobbyJobTransaction* const tr = new (Memory::_Manager[2]->Alloc(sizeof(NPLobbyJobTransaction), kFile, 427))
        NPLobbyJobTransaction;
    if (!gs->SendRequestConsumeGameToken(tr->Set(this, 35), _portalAccountId, _nptoken, _owner->_ipv4))
    {
        JOB_LOG(Log::LT_ERROR, 429, L"[job], send request consume game token fail; unsent", L"");
        _lgate->SendStartSessionWithNPTokenFail(_owner->_clikey, 2);
        _owner->_state = 0x60000;  // PDB ECliSessionState CSS_FIN
        _owner->finalize();
        delete tr;
        Memory::_Manager[2]->Free(tr, kFile, 433);
        return false;
    }
    return true;
}

// 0xd3500
bool StartCliSessionWnpTokenJob::consumeTokenResponse(int, void*)
{
    LIFT_STUB(0xd3500);
}

// 0xd3bc0
bool StartCliSessionWnpTokenJob::consumeTokenExpire()
{
    JOB_LOG(Log::LT_ERROR, 491, L"[job], consume game-token expired", L"");
    _lgate->SendStartSessionWithNPTokenFail(_owner->_clikey, 2);
    _owner->_state = 0x60000;  // PDB ECliSessionState CSS_FIN
    _owner->finalize();
    transit(FIN);
    return true;
}

// 0xd3ce0
bool StartCliSessionWnpTokenJob::listUserLastPresencesReq()
{
    NPGameServiceChannel* const gs = LobbyDaemon::_instance->_npServchmgr->_gameServChannel;
    if (gs == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 506, L"[job], np game-service channel not available", L"");
        _lgate->SendStartSessionWithNPTokenFail(_owner->_clikey, 2);
        _owner->_state = 0x60000;  // PDB ECliSessionState CSS_FIN
        _owner->finalize();
        return false;
    }
    NPLobbyJobTransaction* const tr = new (Memory::_Manager[2]->Alloc(sizeof(NPLobbyJobTransaction), kFile, 513))
        NPLobbyJobTransaction;
    if (!gs->SendRequestListUserLastPresences(tr->Set(this, 73), _userId))
    {
        JOB_LOG(Log::LT_ERROR, 515, L"[job], send request list user last presences fail; unsent", L"");
        _lgate->SendStartSessionWithNPTokenFail(_owner->_clikey, 2);
        _owner->_state = 0x60000;  // PDB ECliSessionState CSS_FIN
        _owner->finalize();
        delete tr;
        Memory::_Manager[2]->Free(tr, kFile, 519);
        return false;
    }
    JOB_LOG(Log::LT_DEBUG, 523, L"[job], send request list user last presences ok", L"");
    return true;
}

// 0xd4050
bool StartCliSessionWnpTokenJob::listUserLastPresencesResponse(void*)
{
    LIFT_STUB(0xd4050);
}

// 0xd46c0
bool StartCliSessionWnpTokenJob::listUserLastPresencesExpire()
{
    JOB_LOG(Log::LT_ERROR, 595, L"[job], list user last presences expired", L"");
    _lgate->SendStartSessionWithNPTokenFail(_owner->_clikey, 2);
    _owner->_state = 0x60000;  // PDB ECliSessionState CSS_FIN
    _owner->finalize();
    transit(FIN);
    return true;
}

// 0xd47e0
bool StartCliSessionWnpTokenJob::listSlotsReq()
{
    NPGameServiceChannel* const gs = LobbyDaemon::_instance->_npServchmgr->_gameServChannel;
    if (gs == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 610, L"[job], np game-service channel not available", L"");
        _lgate->SendStartSessionWithNPTokenFail(_owner->_clikey, 2);
        _owner->_state = 0x60000;  // PDB ECliSessionState CSS_FIN
        _owner->finalize();
        return false;
    }
    NPLobbyJobTransaction* const tr = new (Memory::_Manager[2]->Alloc(sizeof(NPLobbyJobTransaction), kFile, 617))
        NPLobbyJobTransaction;
    if (!gs->SendRequestSlotListSlots(tr->Set(this, 40), _userId, L"activity"))
    {
        JOB_LOG(Log::LT_ERROR, 619, L"[job], send request list slots fail; unsent", L"");
        _lgate->SendStartSessionWithNPTokenFail(_owner->_clikey, 2);
        _owner->_state = 0x60000;  // PDB ECliSessionState CSS_FIN
        _owner->finalize();
        delete tr;
        Memory::_Manager[2]->Free(tr, kFile, 623);
        return false;
    }
    JOB_LOG(Log::LT_DEBUG, 627, L"[job], send request list slots ok", L"");
    return true;
}

// 0xd4b90
bool StartCliSessionWnpTokenJob::listSlotsResponse(void*)
{
    LIFT_STUB(0xd4b90);
}

// 0xd5190
bool StartCliSessionWnpTokenJob::listSlotsExpire()
{
    JOB_LOG(Log::LT_ERROR, 670, L"[job], list slots expired", L"");
    _lgate->SendStartSessionWithNPTokenFail(_owner->_clikey, 2);
    _owner->_state = 0x60000;  // PDB ECliSessionState CSS_FIN
    _owner->finalize();
    transit(FIN);
    return true;
}

// 0xd52b0
bool StartCliSessionWnpTokenJob::createSlotsReq()
{
    if (_activityStatus == 0)
    {
        JOB_CRASH(684, L"== CRASH == [job], in this step, activity status must not be normal.");
        _lgate->SendStartSessionWithNPTokenFail(_owner->_clikey, 2);
        _owner->_state = 0x60000;  // PDB ECliSessionState CSS_FIN
        _owner->finalize();
        return false;
    }
    NPGameServiceChannel* const gs = LobbyDaemon::_instance->_npServchmgr->_gameServChannel;
    if (gs == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 693, L"[job], np game-service channel not available", L"");
        _lgate->SendStartSessionWithNPTokenFail(_owner->_clikey, 2);
        _owner->_state = 0x60000;  // PDB ECliSessionState CSS_FIN
        _owner->finalize();
        return false;
    }
    NPLobbyJobTransaction* const tr = new (Memory::_Manager[2]->Alloc(sizeof(NPLobbyJobTransaction), kFile, 700))
        NPLobbyJobTransaction;
    wchar_t tkey[129];
    swprintf_s(tkey, L"/bns/%s/lobby/%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X", BnsCommonConfig::Config->_npGameCode,
               _userId.guid.id1, _userId.guid.id2, _userId.guid.id3, _userId.guid.id4[0], _userId.guid.id4[1],
               _userId.guid.id4[2], _userId.guid.id4[3], _userId.guid.id4[4], _userId.guid.id4[5], _userId.guid.id4[6],
               _userId.guid.id4[7]);
    if (!gs->SendRequestSlotCreateActivitySlots(tr->Set(this, 42), _userId, L"activity", _activityStatus, 1, tkey))
    {
        JOB_LOG(Log::LT_ERROR, 706, L"[job], send request create slots fail; unsent", L", activity-status:0x%I64X", _activityStatus);
        _lgate->SendStartSessionWithNPTokenFail(_owner->_clikey, 2);
        _owner->_state = 0x60000;  // PDB ECliSessionState CSS_FIN
        _owner->finalize();
        delete tr;
        Memory::_Manager[2]->Free(tr, kFile, 710);
        return false;
    }
    JOB_LOG(Log::LT_DEBUG, 714, L"[job], send request create slots ok", L"");
    return true;
}

// 0xd5770
bool StartCliSessionWnpTokenJob::createSlotsResponse(void*)
{
    LIFT_STUB(0xd5770);
}

// 0xd5db0
bool StartCliSessionWnpTokenJob::createSlotsExpire()
{
    JOB_LOG(Log::LT_ERROR, 755, L"[job], create slots expired", L"");
    _lgate->SendStartSessionWithNPTokenFail(_owner->_clikey, 2);
    _owner->_state = 0x60000;  // PDB ECliSessionState CSS_FIN
    _owner->finalize();
    transit(FIN);
    return true;
}

// 0xd5ed0
bool StartCliSessionWnpTokenJob::setSlotDataReq()
{
    if (_activityStatus == 0)
    {
        JOB_CRASH(769, L"== CRASH == [job], in this step, activity status must not be normal.");
        _lgate->SendStartSessionWithNPTokenFail(_owner->_clikey, 2);
        _owner->_state = 0x60000;  // PDB ECliSessionState CSS_FIN
        _owner->finalize();
        return false;
    }
    NPGameServiceChannel* const gs = LobbyDaemon::_instance->_npServchmgr->_gameServChannel;
    if (gs == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 778, L"[job], np game-service channel not available", L"");
        _lgate->SendStartSessionWithNPTokenFail(_owner->_clikey, 2);
        _owner->_state = 0x60000;  // PDB ECliSessionState CSS_FIN
        _owner->finalize();
        return false;
    }
    NPLobbyJobTransaction* const tr = new (Memory::_Manager[2]->Alloc(sizeof(NPLobbyJobTransaction), kFile, 785))
        NPLobbyJobTransaction;
    if (!gs->SendRequestSlotSetActivitySlotData(tr->Set(this, 44), _userId, _activitySlotId, _activityStatus))
    {
        JOB_LOG(Log::LT_ERROR, 788, L"[job], send request set slot data fail; unsent", L", activity-status:0x%I64X", _activityStatus);
        _lgate->SendStartSessionWithNPTokenFail(_owner->_clikey, 2);
        _owner->_state = 0x60000;  // PDB ECliSessionState CSS_FIN
        _owner->finalize();
        delete tr;
        Memory::_Manager[2]->Free(tr, kFile, 792);
        return false;
    }
    JOB_LOG(Log::LT_DEBUG, 796, L"[job], send request set slot data ok", L"");
    return true;
}

// 0xd62b0
bool StartCliSessionWnpTokenJob::setSlotDataResponse(void* param)
{
    StsMsgLib::_StsMsgResponse* const res = static_cast<StsMsgLib::_StsMsgResponse*>(param);
    JOB_LOG(Log::LT_DEBUG, 802, L"[job], response set slot data recv", L"");
    if (_owner->_state != 0x10002)  // PDB ECliSessionState CSS_INIT_verify
    {
        JOB_LOG(Log::LT_ERROR, 805, L"[job], not INIT.verify state", L"");
        _lgate->SendStartSessionWithNPTokenFail(_owner->_clikey, 5);
        return false;
    }
    unsigned int const status = res->msgInfo.errInfo.nStatusCode;
    if (status == 200 ||
        (status == 400 &&
         _wcsicmp(L"Success", res->msgInfo.errInfo.pwszReason != nullptr ? res->msgInfo.errInfo.pwszReason : L"null") == 0))
    {
        // The original format has no comma before "np-tid".
        JOB_LOG(Log::LT_DEBUG, 823, L"[job], response set slot data",
                L"np-tid:%u, cmd:%d, type:%d, status-code:%u, reason:%s, error-code:%d", res->GetTransactionId(),
                res->GetCommand(), res->GetMessageType(), res->msgInfo.errInfo.nStatusCode,
                res->msgInfo.errInfo.pwszReason != nullptr ? res->msgInfo.errInfo.pwszReason : L"null",
                res->msgInfo.errInfo.nErrorCode);
        transit(PRESENCE_LOGIN);
        return true;
    }
    JOB_LOG(Log::LT_ERROR, 812, L"[job], set slot data failed",
            L", np-tid:%u, cmd:%d, type:%d, status-code:%u, reason:%s, error-code:%d", res->GetTransactionId(),
            res->GetCommand(), res->GetMessageType(), res->msgInfo.errInfo.nStatusCode,
            res->msgInfo.errInfo.pwszReason != nullptr ? res->msgInfo.errInfo.pwszReason : L"null",
            res->msgInfo.errInfo.nErrorCode);
    _lgate->SendStartSessionWithNPTokenFail(_owner->_clikey, 15);
    _owner->_state = 0x60000;
    _owner->finalize();
    return false;
}

// 0xd66b0
bool StartCliSessionWnpTokenJob::setSlotDataExpire()
{
    JOB_LOG(Log::LT_ERROR, 831, L"[job], set slot data expired", L"");
    _lgate->SendStartSessionWithNPTokenFail(_owner->_clikey, 2);
    _owner->_state = 0x60000;  // PDB ECliSessionState CSS_FIN
    _owner->finalize();
    transit(FIN);
    return true;
}

// 0xd67d0
bool StartCliSessionWnpTokenJob::presenceLoginReq()
{
    NPGameServiceChannel* const gs = LobbyDaemon::_instance->_npServchmgr->_gameServChannel;
    if (gs == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 846, L"[job], np game-service channel not available", L"");
        _lgate->SendStartSessionWithNPTokenFail(_owner->_clikey, 2);
        _owner->_state = 0x60000;  // PDB ECliSessionState CSS_FIN
        _owner->finalize();
        return false;
    }
    NPLobbyJobTransaction* const tr = new (Memory::_Manager[2]->Alloc(sizeof(NPLobbyJobTransaction), kFile, 853))
        NPLobbyJobTransaction;
    if (!gs->SendRequestPresenceLogin(tr->Set(this, 46), _gameAccountName, _userName, L"", _gameAccountId, _owner->_ipv4))
    {
        JOB_LOG(Log::LT_ERROR, 855, L"[job], send request presence login fail; unsent", L"");
        _lgate->SendStartSessionWithNPTokenFail(_owner->_clikey, 2);
        _owner->_state = 0x60000;  // PDB ECliSessionState CSS_FIN
        _owner->finalize();
        delete tr;
        Memory::_Manager[2]->Free(tr, kFile, 859);
        return false;
    }
    JOB_LOG(Log::LT_DEBUG, 863, L"[job], send request presence login ok", L"");
    return true;
}

// 0xd6ad0
bool StartCliSessionWnpTokenJob::presenceLoginResponse(void*)
{
    LIFT_STUB(0xd6ad0);
}

// 0xd74a0
bool StartCliSessionWnpTokenJob::presenceLoginExpire()
{
    JOB_LOG(Log::LT_ERROR, 1013, L"[job], presence login expired", L"");
    _lgate->SendStartSessionWithNPTokenFail(_owner->_clikey, 2);
    _owner->_state = 0x60000;  // PDB ECliSessionState CSS_FIN
    _owner->finalize();
    transit(FIN);
    return true;
}

// 0xd75c0
bool StartCliSessionWnpTokenJob::getUserProfileReq()
{
    NPGameServiceChannel* const gs = LobbyDaemon::_instance->_npServchmgr->_gameServChannel;
    if (gs == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 1028, L"[job], np game-service channel not available", L"");
        _lgate->SendStartSessionWithNPTokenFail(_owner->_clikey, 2);
        _owner->_state = 0x60000;  // PDB ECliSessionState CSS_FIN
        _owner->finalize();
        return false;
    }
    NPLobbyJobTransaction* const tr = new (Memory::_Manager[2]->Alloc(sizeof(NPLobbyJobTransaction), kFile, 1035))
        NPLobbyJobTransaction;
    if (!gs->SendRequestProfileGetUserProfile(tr->Set(this, 94), _gameAccountId))
    {
        JOB_LOG(Log::LT_ERROR, 1039, L"[job], send request profile get user profile; unsent", L"");
        _lgate->SendStartSessionWithNPTokenFail(_owner->_clikey, 2);
        _owner->_state = 0x60000;  // PDB ECliSessionState CSS_FIN
        _owner->finalize();
        delete tr;
        Memory::_Manager[2]->Free(tr, kFile, 1043);
        return false;
    }
    JOB_LOG(Log::LT_DEBUG, 1047, L"[job], send request profile get user profile ok", L"");
    return true;
}

// 0xd7930
bool StartCliSessionWnpTokenJob::getUserProfileResponse(void*)
{
    LIFT_STUB(0xd7930);
}

// 0xd7ec0
bool StartCliSessionWnpTokenJob::getUserProfileExpire()
{
    LIFT_STUB(0xd7ec0);
}

// 0xd7fe0
bool StartCliSessionWnpTokenJob::getGameTimeReq()
{
    LIFT_STUB(0xd7fe0);
}

// 0xd8360
bool StartCliSessionWnpTokenJob::getGameTimeResponse(void*)
{
    LIFT_STUB(0xd8360);
}

// 0xd8b10
bool StartCliSessionWnpTokenJob::getGameTimeExpire()
{
    LIFT_STUB(0xd8b10);
}

// 0xd8c30
bool StartCliSessionWnpTokenJob::getGradeLevelReq()
{
    LIFT_STUB(0xd8c30);
}

// 0xd8f60
bool StartCliSessionWnpTokenJob::getGradeLevelResponse(void*)
{
    LIFT_STUB(0xd8f60);
}

// 0xd9420
bool StartCliSessionWnpTokenJob::getGradeLevelExpire()
{
    LIFT_STUB(0xd9420);
}

// 0xd9540
bool StartCliSessionWnpTokenJob::listAllGradesReq()
{
    LIFT_STUB(0xd9540);
}

// 0xd98b0
bool StartCliSessionWnpTokenJob::listAllGradesResponse(void*)
{
    LIFT_STUB(0xd98b0);
}

// 0xd9da0
bool StartCliSessionWnpTokenJob::listAllGradesExpire()
{
    LIFT_STUB(0xd9da0);
}

// 0xd9ec0
bool StartCliSessionWnpTokenJob::listUserBansReq()
{
    LIFT_STUB(0xd9ec0);
}

// 0xda1a0
bool StartCliSessionWnpTokenJob::listUserBansResponse(void*)
{
    LIFT_STUB(0xda1a0);
}

// 0xda680
bool StartCliSessionWnpTokenJob::listUserBansExpire()
{
    LIFT_STUB(0xda680);
}

// 0xda7a0
bool StartCliSessionWnpTokenJob::getRMSInquiryReq()
{
    LIFT_STUB(0xda7a0);
}

// 0xdaa90
bool StartCliSessionWnpTokenJob::getRMSInquiryResponse(void*)
{
    LIFT_STUB(0xdaa90);
}

// 0xdaf60
bool StartCliSessionWnpTokenJob::getRMSInquiryExpire()
{
    LIFT_STUB(0xdaf60);
}

// 0xdb080
bool StartCliSessionWnpTokenJob::getUserPromotionStatusReq()
{
    LIFT_STUB(0xdb080);
}

// 0xdb400
bool StartCliSessionWnpTokenJob::getUserPromotionStatusResponse(void*)
{
    LIFT_STUB(0xdb400);
}

// 0xdb830
bool StartCliSessionWnpTokenJob::getUserPromotionStatusExpire()
{
    LIFT_STUB(0xdb830);
}

// 0xdb950
bool StartCliSessionWnpTokenJob::loginAccount()
{
    LIFT_STUB(0xdb950);
}

// 0xdc310
bool StartCliSessionWnpTokenJob::checkIntialUserName(wchar_t const*)
{
    LIFT_STUB(0xdc310);
}
