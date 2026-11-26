// SetupNpScheduleInfoJob.obj (LobbyDaemon PDB, 2019 + PDB). Lifted from the pseudocode with PDB types.
#include <new>
#include <wchar.h>
#include <winsock2.h>
#include <windows.h>
#include "SetupNpScheduleInfoJob.h"
#include "BnsCommonConfigDefinition.h"
#include "LiftStub.h"
#include "LobbyDaemon.h"
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "NPServiceChannel.h"

static wchar_t const kFile[] = L"SetupNpScheduleInfoJob.cpp";

// LIFT: PDB StsMsgLib::_StsMsgResponsePromotionStampListCurrentPromotions (sizeof 0x70). The type is not in a
// LobbyDaemon header yet.
namespace StsMsgLib
{
struct _StsMsgResponsePromotionStampListCurrentPromotions : public _StsMsgResponse
{
    struct _PromotionInfo
    {
        int nPromotionId;
        int nBoardType;
        wchar_t* pwszBoardTemplateKey;
        int nUserAttendType;
    };
    int nPromotionListCount;
    _PromotionInfo* pPromotionList;
};
static_assert(sizeof(_StsMsgResponsePromotionStampListCurrentPromotions::_PromotionInfo) == 0x18, "sizeof _PromotionInfo");
static_assert(sizeof(_StsMsgResponsePromotionStampListCurrentPromotions) == 0x70, "sizeof _StsMsgResponsePromotionStampListCurrentPromotions");
static_assert(offsetof(_StsMsgResponsePromotionStampListCurrentPromotions, pPromotionList) == 0x68, "pPromotionList");
}  // namespace StsMsgLib

// The log suffix of the SetupNpScheduleInfoJob logs (LobbyJob base, no owner).
#define JOB_LOG(logType, line, msg, fmt, ...)                                                                          \
    Log::Write(logType, kFile, line, msg L", tid:0x%I64X, type:%d, state:%d" fmt, this != nullptr ? _id : 0,          \
               this != nullptr ? GetDefinition()->type : -1, this != nullptr ? _state : -1, ##__VA_ARGS__)

namespace
{
LobbyJobStateDef const StateDef[] = {{0, L"INIT_SETUP_NP_SCHEDULE_INFO"},
                                     {1, L"TRY_PROMOTIONSTAMP_LIST_CURRENT_PROMOTIONS"},
                                     {2, L"TRY_PROMOTIONSTAMP_GET_PROMOTION_POLICY"},
                                     {3, L"FIN_SETUP_NP_SCHEDULE_INFO_JOB"},
                                     {4, L"FIN"}};  // 0x12dce0
}

LobbyJobDef SetupNpScheduleInfoJob::_def = {44, StateDef, 4, L"SetupNpScheduleInfoJob"};  // 0x2019f0

#include "ObjectPoolLobbyDaemon.h"

// .data 0x204e60, dynamic init 0x11e2a0, atexit dtor 0x11f000.
// The exe .data holds id 1, objsize 0xb8, desc L"SetupNpScheduleInfoJob".
ObjPool SetupNpScheduleInfoJob::_pool(1, 0xb8, L"SetupNpScheduleInfoJob");

// LIFT: no RVA. LTCG inlined it into LobbyDaemon::initialize (0x9b300). The original constructs a job on the stack
// and returns its vfptr. It does not run the destructor.
void* SetupNpScheduleInfoJob::_vtbl()
{
    char buf[sizeof(SetupNpScheduleInfoJob)];
    SetupNpScheduleInfoJob* job = ::new (buf) SetupNpScheduleInfoJob();
    return *reinterpret_cast<void**>(job);
}

// 0x72cf0
LobbyJobDef const* SetupNpScheduleInfoJob::GetDefinition() const
{
    return &_def;
}

// 0x72d00
// LIFT: Not done. The body calls _pool.Checkin. ObjPool is not in lift_lobbydaemon.
void SetupNpScheduleInfoJob::deallocate_me(void*, wchar_t const*, int)
{
    LIFT_STUB(0x72d00);
}

// 0x72d90
SetupNpScheduleInfoJob::SetupNpScheduleInfoJob() : _tryGetPromotionPolicy(0)
{
}

// 0x72e40 (scalar deleting destructor 0x72e20)
SetupNpScheduleInfoJob::~SetupNpScheduleInfoJob()
{
    _tryGetPromotionPolicy = 0;
}

// 0x72eb0
bool SetupNpScheduleInfoJob::work(int task, void* param)
{
    bool result = false;
    if (_state == INIT_SETUP_NP_SCHEDULE_INFO && task == 6)
    {
        transit(TRY_PROMOTIONSTAMP_LIST_CURRENT_PROMOTIONS);
        result = true;
        task = 0;
    }
    if (_state == TRY_PROMOTIONSTAMP_LIST_CURRENT_PROMOTIONS)
    {
        switch (task)
        {
        case 0:
            result = tryListCurrentPromotions(nullptr);
            task = 0;
            break;
        case 97:
            result = listCurrentPromotionsAck(param);
            task = 0;
            break;
        case 98:
            JOB_LOG(Log::LT_ERROR, 195, L"[job], fail request list current promotions; expired", L"");
            result = false;
            task = 0;
            break;
        }
    }
    if (_state == TRY_PROMOTIONSTAMP_GET_PROMOTION_POLICY)
    {
        switch (task)
        {
        case 0:
            result = tryGetPromotionPolicy(nullptr);
            task = 0;
            break;
        case 99:
            result = getPromotionPolicyAck(param);
            task = 0;
            break;
        case 100:
            JOB_LOG(Log::LT_ERROR, 450, L"[job], get promotions policy failed; expired", L"");
            result = false;
            task = 0;
            break;
        }
    }
    if (_state == FIN_SETUP_NP_SCHEDULE_INFO_JOB && task == 0)
    {
        // PDB inline SystemEvent::Send: SetEvent when the event handle is set.
        if (LobbyDaemon::_instance->_setupNpScheduleInfoEvent.Event != nullptr)
            SetEvent(LobbyDaemon::_instance->_setupNpScheduleInfoEvent.Event);
        transit(FIN);
        return true;
    }
    return result;
}

// 0x72ff0
bool SetupNpScheduleInfoJob::tryListCurrentPromotions(void*)
{
    NPGameServiceChannel* const gameServChannel = LobbyDaemon::_instance->_npServchmgr->_gameServChannel;
    if (gameServChannel == nullptr)
        return false;
    NPLobbyJobTransaction* const tran =
        new (Memory::_Manager[2]->Alloc(sizeof(NPLobbyJobTransaction), kFile, 127)) NPLobbyJobTransaction;
    if (gameServChannel->SendRequestPromotionStampListCurrentPromotions(tran->Set(this, 98),
                                                                        BnsCommonConfig::Config->_npGameCode))
        return true;
    JOB_LOG(Log::LT_ERROR, 130, L"[job], send request list current promotions; unsent", L"");
    if (tran != nullptr)
        tran->~NPLobbyJobTransaction();
    Memory::_Manager[2]->Free(tran, kFile, 131);
    return false;
}

// 0x73160
bool SetupNpScheduleInfoJob::listCurrentPromotionsAck(void* param)
{
    StsMsgLib::_StsMsgResponsePromotionStampListCurrentPromotions* const res =
        static_cast<StsMsgLib::_StsMsgResponsePromotionStampListCurrentPromotions*>(param);
    if (res == nullptr)
    {
        JOB_LOG(Log::LT_ERROR, 142, L"[job], null param", L"");
        return false;
    }
    if (res->msgInfo.errInfo.nStatusCode != 200 &&
        (res->msgInfo.errInfo.nStatusCode != 400 ||
         _wcsicmp(L"Success", res->msgInfo.errInfo.pwszReason != nullptr ? res->msgInfo.errInfo.pwszReason : L"null") != 0))
    {
        // The original log has no comma before np-tid.
        JOB_LOG(Log::LT_ERROR, 149, L"[job], list current promotions failed",
                L"np-tid:%u, cmd:%d, type:%d, status-code:%u, reason:%s, error-code:%d", res->GetTransactionId(),
                res->GetCommand(), res->GetMessageType(), res->msgInfo.errInfo.nStatusCode,
                res->msgInfo.errInfo.pwszReason != nullptr ? res->msgInfo.errInfo.pwszReason : L"null",
                res->msgInfo.errInfo.nErrorCode);
        return false;
    }
    bool found = false;
    for (int i = 0; i < res->nPromotionListCount; ++i)
    {
        char targetType;
        switch (static_cast<short>(res->pPromotionList[i].nBoardType))
        {
        case 5:
            targetType = 1;
            break;
        case 6:
            targetType = 0;
            break;
        default:
            continue;
        }
        _promotionIds[targetType].push_back(res->pPromotionList[i].nPromotionId);
        found = true;
    }
    JOB_LOG(Log::LT_DEBUG, 178, L"[job], list current promotions ok",
            L", app-group-code:%s, promotionIdCount[all]:%d, promotionIdCount[pccafe]:%d", BnsCommonConfig::Config->_npGameCode,
            _promotionIds[0].size(), _promotionIds[1].size());
    transit(found ? TRY_PROMOTIONSTAMP_GET_PROMOTION_POLICY : FIN_SETUP_NP_SCHEDULE_INFO_JOB);
    return true;
}

// 0x733e0
bool SetupNpScheduleInfoJob::tryGetPromotionPolicy(void*)
{
    NPGameServiceChannel* const gameServChannel = LobbyDaemon::_instance->_npServchmgr->_gameServChannel;
    if (gameServChannel == nullptr)
        return false;
    unsigned int i = 0;
    while (_promotionIds[i].empty())
    {
        ++i;
        if (i >= 2)
        {
            transit(FIN_SETUP_NP_SCHEDULE_INFO_JOB);
            return true;
        }
    }
    int const promotionId = _promotionIds[i].front();
    _promotionIds[i].pop_front();
    if (promotionId == 0)
    {
        transit(FIN_SETUP_NP_SCHEDULE_INFO_JOB);
        return true;
    }
    NPLobbyJobTransaction* const tran =
        new (Memory::_Manager[2]->Alloc(sizeof(NPLobbyJobTransaction), kFile, 225)) NPLobbyJobTransaction;
    if (gameServChannel->SendRequestPromotionStampGetPromotionPolicy(tran->Set(this, 100), promotionId))
        return true;
    // The original log text says "list current promotions" here too.
    JOB_LOG(Log::LT_ERROR, 228, L"[job], send request list current promotions; unsent", L"");
    if (tran != nullptr)
        tran->~NPLobbyJobTransaction();
    Memory::_Manager[2]->Free(tran, kFile, 229);
    return false;
}

// 0x73630
// LIFT: Not done. The body (about 3000 bytes) builds TimeBasedPlaySeasonSchedule::Data from the policy, sorts the
// rules and gives them to LobbyDaemon::_timeBasedPlaySeasonSchedule. It is a later card.
bool SetupNpScheduleInfoJob::getPromotionPolicyAck(void*)
{
    LIFT_STUB(0x73630);
}
