// EventNotiJob.obj (SmartCouponDaemon PDB). Source file name from log strings: "EventNotiJob.cpp".
#include <winsock2.h>
#include <windows.h>
#include <stdlib.h>
#include <wchar.h>
#include <new>
#include "EventNotiJob.h"
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "Network.h"
#include "NPChannel.h"
#include "SmartCouponDB.h"
#include "SmartCouponDaemon.h"

static wchar_t const* const kFile = L"EventNotiJob.cpp";

namespace
{
// 0x60828 (PDB StateDef, EventNotiJob.obj)
JobStateDef const StateDef[] = {
    {0, L"INIT"},
    {1, L"EVENT_NOTI"},
    {2, L"FIN"},
};
}  // namespace

ObjPool EventNotiJob::_pool(1, sizeof(EventNotiJob), L"EventNotiJob");  // 0x52A30 LIFT: LTCG put the args into the ctor (0x11a4: id 1, size 0x90)
JobDef const EventNotiJob::_def = {1, StateDef, 2, L"EventNotiJob"};  // 0x83230

// 0x9860
RefCntPoolObj::~RefCntPoolObj()
{
}

// 0x9890
CouponJob::~CouponJob()
{
    // CriticalSection::~CriticalSection does DeleteCriticalSection.
}

// 0x98D0
bool CouponJob::dispatch_work(int task, void* param)
{
    return work(task, param);
}

// 0x9920
JobDef const* EventNotiJob::GetDefinition() const
{
    return &_def;
}

// 0x9930
void EventNotiJob::deallocate_me(void* ptr, wchar_t const* file, int line)
{
    this->~EventNotiJob();
    _pool.Checkin(ptr, file, line);
}

// 0x9970
unsigned int SendRetryCouponPublicationOkEvent::EventId() const
{
    return 131;
}

// 0x9980
SendRetryCouponPublicationOkEvent::~SendRetryCouponPublicationOkEvent()
{
}

// 0x99B0
unsigned int SendRetryCouponPublicationFailEvent::EventId() const
{
    return 132;
}

// 0x99C0
SendRetryCouponPublicationFailEvent::~SendRetryCouponPublicationFailEvent()
{
}

// 0x99F0
EventNotiJob::EventNotiJob()
    : _gameAccountId(ID128_GUID_ZERO), _couponEventId(0), _publicationId(0), _acceptTid(0),
      _fromManagementDaemon(false), _managementTid(0), _managementReason(-1)
{
}

// 0x9A80
EventNotiJob::~EventNotiJob()
{
    finalize();
}

// 0x9AE0
bool EventNotiJob::Initialize(id128 const* gameAccountId, int couponEventId, long long publicationId,
                              long long managementTid)
{
    if ((gameAccountId->id[0] | gameAccountId->id[1]) != 0 && couponEventId != 0 && publicationId != 0)
    {
        _gameAccountId = *gameAccountId;
        _couponEventId = couponEventId;
        _publicationId = publicationId;
        if (managementTid > 0)
        {
            _fromManagementDaemon = true;
            _managementTid = managementTid;
        }
        return true;
    }
    auto const& acc = gameAccountId->guid;
    Log::Write(Log::LT_ERROR, kFile, 83,
               L"[job], init fail; invalid parameter, jobid:0x%I64X, type:%d, state:%dacc:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X,  coupon-event-id:%d, publicationid:%I64d, management-tid:%I64d",
               _id, GetDefinition()->type, _state, acc.id1, acc.id2, acc.id3, acc.id4[0], acc.id4[1], acc.id4[2],
               acc.id4[3], acc.id4[4], acc.id4[5], acc.id4[6], acc.id4[7], couponEventId, publicationId,
               managementTid);
    return false;
}

// 0x9CC0
void EventNotiJob::finalize()
{
    if (!_fromManagementDaemon)
        return;
    if (_managementReason == -1)
    {
        Log::Write(Log::LT_ERROR, kFile, 107,
                   L"[job], finalize fail; unknown error, jobid:0x%I64X, type:%d, state:%dmanagement-tid:%I64d", _id,
                   GetDefinition()->type, _state, _managementTid);
        _managementReason = 1;
    }
    if (_managementReason == 0)
    {
        void* mem = Memory::_Manager[2]->Alloc(sizeof(SendRetryCouponPublicationOkEvent), kFile, 113);
        SendRetryCouponPublicationOkEvent* evt =
            mem ? new (mem) SendRetryCouponPublicationOkEvent(_managementTid, _acceptTid) : nullptr;
        PostQueuedCompletionStatus(Network::iocpHandle(), 0,
                                   reinterpret_cast<ULONG_PTR>(evt), nullptr);
        Log::Write(Log::LT_DEBUG, kFile, 116,
                   L"[job], post sendRetryCouponPublicationOkEvent;, jobid:0x%I64X, type:%d, state:%d tid:%I64d, accept-tid:%I64d",
                   _id, GetDefinition()->type, _state, _managementTid, _acceptTid);
    }
    if (_managementReason > 0)
    {
        void* mem = Memory::_Manager[2]->Alloc(sizeof(SendRetryCouponPublicationFailEvent), kFile, 121);
        SendRetryCouponPublicationFailEvent* evt =
            mem ? new (mem) SendRetryCouponPublicationFailEvent(_managementTid, _managementReason) : nullptr;
        PostQueuedCompletionStatus(Network::iocpHandle(), 0,
                                   reinterpret_cast<ULONG_PTR>(evt), nullptr);
        Log::Write(Log::LT_DEBUG, kFile, 124,
                   L"[job], post sendRetryCouponPublicationFailEvent;, jobid:0x%I64X, type:%d, state:%d tid:%I64d, failReason:%d",
                   _id, GetDefinition()->type, _state, _managementTid, static_cast<int>(_managementReason));
    }
}

// 0x9F10
bool EventNotiJob::work(int task, void* param)
{
    bool result = false;
    if (_state == 0 && task == 1)
    {
        result = init();
        task = 0;
    }
    if (_state == 1)
    {
        if (task == 0)
            return eventNotiReq();
        if (task == 2)
            return eventNotiRes(param);
        if (task == 3)
            return eventNotiExpire();
    }
    return result;
}

// 0x9F90
bool EventNotiJob::init()
{
    auto const& acc = _gameAccountId.guid;
    // LIFT: orig 0x9FB2 tests the job pointer for the id/type/state args (-1 when null), like a log macro.
    CouponJob const* const job = this;
    Log::Write(Log::LT_DEBUG, kFile, 161,
               L"[job], init ok, jobid:0x%I64X, type:%d, state:%d, acc:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X,  coupon-event-id:%d, publicationid:%I64d, management-tid:%I64d",
               job ? job->_id : 0, job ? job->GetDefinition()->type : -1, job ? job->_state : -1, acc.id1, acc.id2, acc.id3, acc.id4[0], acc.id4[1], acc.id4[2],
               acc.id4[3], acc.id4[4], acc.id4[5], acc.id4[6], acc.id4[7], _couponEventId, _publicationId,
               _managementTid);
    transit(1);
    return true;
}

// 0xA0E0
bool EventNotiJob::eventNotiReq()
{
    NPServiceChannel* const ch = SmartCouponDaemon::_instance->_npChannelMgr->_npServChannel;
    if (ch == nullptr)
    {
        Log::Write(Log::LT_ERROR, kFile, 172, L"[job], event-noti req fail; npchannel is null, jobid:0x%I64X, type:%d, state:%d",
                   _id, GetDefinition()->type, _state);
    }
    else if (ch->SendRequestEventNoti(this, &_gameAccountId, _couponEventId, _publicationId))
    {
        Log::Write(Log::LT_DEBUG, kFile, 182, L"[job], event-noti req ok, jobid:0x%I64X, type:%d, state:%d", _id,
                   GetDefinition()->type, _state);
        return true;
    }
    else
    {
        auto const& acc = _gameAccountId.guid;
        Log::Write(Log::LT_ERROR, kFile, 178,
                   L"[job], event-noti req fail; unsent, jobid:0x%I64X, type:%d, state:%dacc:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X,  coupon-event-id:%d, publication-id:%I64d",
                   _id, GetDefinition()->type, _state, acc.id1, acc.id2, acc.id3, acc.id4[0], acc.id4[1], acc.id4[2],
                   acc.id4[3], acc.id4[4], acc.id4[5], acc.id4[6], acc.id4[7], _couponEventId, _publicationId);
    }
    if (_fromManagementDaemon)
        _managementReason = 5;
    transit(2);
    return true;
}

// 0xA310
bool EventNotiJob::eventNotiRes(void* param)
{
    if (param == nullptr)
    {
        Log::Write(Log::LT_ERROR, kFile, 198, L"[job], null param, jobid:0x%I64X, type:%d, state:%d", _id,
                   GetDefinition()->type, _state);
        transit(2);
        return true;
    }
    StsMsgLib::_StsMsgResponse* const res = static_cast<StsMsgLib::_StsMsgResponse*>(param);
    unsigned int const status = res->msgInfo.errInfo.nStatusCode;
    wchar_t const* const reason = res->msgInfo.errInfo.pwszReason;
    int const err = res->msgInfo.errInfo.nErrorCode;
    auto const& acc = _gameAccountId.guid;

    bool success = status == 200 || (status == 400 && _wcsicmp(L"Success", reason ? reason : L"null") == 0);
    if (!success && err != 5809)
    {
        if (err != 42 && err != 5812 && err != 30002)
        {
            int dbRetValue = 0;
            if (!SmartCouponDB::UpdateStatusToPublicationFailure(&dbRetValue, _publicationId, &_gameAccountId,
                                                                 _couponEventId))
            {
                Log::Write(Log::LT_ERROR, kFile, 229,
                           L"[job], event-noti res fail, db update fail, jobid:0x%I64X, type:%d, state:%dacc:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X,  coupon-event-id:%d, publication-id:%I64d, dbRetValue:%d",
                           _id, GetDefinition()->type, _state, acc.id1, acc.id2, acc.id3, acc.id4[0], acc.id4[1],
                           acc.id4[2], acc.id4[3], acc.id4[4], acc.id4[5], acc.id4[6], acc.id4[7], _couponEventId,
                           _publicationId, dbRetValue);
            }
        }
        Log::Write(Log::LT_ERROR, kFile, 238,
                   L"[job], event-noti res fail, jobid:0x%I64X, type:%d, state:%d,np-tid:%u, cmd:%d, type:%d, status-code:%u, reason:%s, error-code:%d",
                   _id, GetDefinition()->type, _state, res->GetTransactionId(), res->GetCommand(),
                   res->GetMessageType(), status, reason ? reason : L"null", err);
        if (_fromManagementDaemon)
            _managementReason = 6;
        transit(2);
        return true;
    }

    int const cmd = res->GetCommand();
    if (static_cast<unsigned int>(cmd - 2851) < 2)
    {
        long long const* acceptTid = nullptr;
        wchar_t const* const acceptTidStr =
            static_cast<StsMsgLib::_StsMsgResponseRewardBrokerEventNoti*>(res)->pwszAcceptTid;
        if (acceptTidStr != nullptr)
        {
            _acceptTid = _wtoi64(acceptTidStr);
            acceptTid = &_acceptTid;
            if (_acceptTid <= 0)
            {
                Log::Write(Log::LT_ERROR, kFile, 282,
                           L"[job], event-noti res ok; np response, jobid:0x%I64X, type:%d, state:%d invalid accept-tid, acc:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, coupon-event-id:%d, publication-id:%I64d, accept-tid:%I64d",
                           _id, GetDefinition()->type, _state, acc.id1, acc.id2, acc.id3, acc.id4[0], acc.id4[1],
                           acc.id4[2], acc.id4[3], acc.id4[4], acc.id4[5], acc.id4[6], acc.id4[7], _couponEventId,
                           _publicationId, _acceptTid);
            }
        }
        else
        {
            _acceptTid = 0;
        }
        Log::Write(Log::LT_DEBUG, kFile, 291,
                   L"[job], event-noti res ok, np response, jobid:0x%I64X, type:%d, state:%d acc:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, coupon-event-id:%d, publication-id:%I64d, accept-tid:%I64d",
                   _id, GetDefinition()->type, _state, acc.id1, acc.id2, acc.id3, acc.id4[0], acc.id4[1], acc.id4[2],
                   acc.id4[3], acc.id4[4], acc.id4[5], acc.id4[6], acc.id4[7], _couponEventId, _publicationId,
                   _acceptTid);
        int dbRetValue = 0;
        if (!SmartCouponDB::UpdateStatusToPublicationSuccess(&dbRetValue, _publicationId, &_gameAccountId,
                                                             _couponEventId, acceptTid))
        {
            Log::Write(Log::LT_ERROR, kFile, 297,
                       L"[job], event-noti res ok, db update fail, jobid:0x%I64X, type:%d, state:%dacc:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, coupon-event-id:%d, publication-id:%I64d, dbRetValue:%d",
                       _id, GetDefinition()->type, _state, acc.id1, acc.id2, acc.id3, acc.id4[0], acc.id4[1],
                       acc.id4[2], acc.id4[3], acc.id4[4], acc.id4[5], acc.id4[6], acc.id4[7], _couponEventId,
                       _publicationId, dbRetValue);
        }
        Log::Write(Log::LT_DEBUG, kFile, 300, L"[job], event-noti res ok, jobid:0x%I64X, type:%d, state:%d", _id,
                   GetDefinition()->type, _state);
        if (_fromManagementDaemon)
            _managementReason = 0;
    }
    else
    {
        Log::Write(Log::LT_ERROR, kFile, 270, L"[job], invalid sts cmd, jobid:0x%I64X, type:%d, state:%dcommand:%d",
                   _id, GetDefinition()->type, _state, cmd);
    }
    transit(2);
    return true;
}

// 0xA9D0
// LIFT: noinline. The orig calls it out of line (SCD 0xa9d0).
__declspec(noinline) bool EventNotiJob::eventNotiExpire()
{
    Log::Write(Log::LT_ERROR, kFile, 313, L"[job], event-noti expire, jobid:0x%I64X, type:%d, state:%d", _id,
               GetDefinition()->type, _state);
    if (_fromManagementDaemon)
        _managementReason = 3;
    transit(2);
    return true;
}
