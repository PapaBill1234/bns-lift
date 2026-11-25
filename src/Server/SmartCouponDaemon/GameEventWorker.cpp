// GameEventWorker.obj (SmartCouponDaemon PDB).
#include <windows.h>
#include <winsock2.h>
#include <new>
#include "GameEventWorker.h"
#include "AlertSender.h"
#include "CouponJob.h"
#include "CrashHandler.h"
#include "Daemon.h"
#include "EventNotiJob.h"
#include "Log.h"
#include "LogBuffer.h"
#include "ManagerChannel.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "Network.h"
#include "SendPublicationEvent.h"
#include "SmartCouponDB.h"
#include "SmartCouponDaemon.h"
#include "SysInfo.h"

namespace
{
wchar_t const* const kFile = L"GameEventWorker.cpp";

// LIFT: Not in the PDB. Inlined assert crash (Log, AlertSender, MakeCrash).
void assertCrash(int line)
{
    Log::Write(Log::LT_ERROR, kFile, line, L"== CRASH == ASSERT CRASH");
    AlertSender::Write(kFile, line, L"== CRASH == ASSERT CRASH");
    CrashHandler::MakeCrash("GameEventWorker.cpp", line, L"");
}
}  // namespace

// LIFT: lift macro, not in any PDB. The 11 id128::guid arguments of the "acc:%08X-..." format.
#define GEW_ACC_ARGS(a) \
    (a).id1, (a).id2, (a).id3, (a).id4[0], (a).id4[1], (a).id4[2], (a).id4[3], (a).id4[4], (a).id4[5], (a).id4[6], (a).id4[7]

GameEventManager* GameEventManager::Instance = nullptr;
ThreadManager* GameEventManager::WorkerManager = nullptr;
EventObject* GameEventManager::EndEventObject = nullptr;

// 0xaa80
wchar_t const* GameEventWorker::Name()
{
    return L"GameEvent";
}

// 0x231f0 PDB: S_GPROC32 code size 6. COMDAT folded with NetworkEndEvent::EventId.
unsigned int GameEventEndEvent::EventId() const
{
    return 1;  // LIFT: mov eax, 1 at 0x231f0
}

// 0xaad0
bool GameEventEndEvent::HandleEvent(EventContext*, unsigned long)
{
    return true;
}

// GameEventLogEvent::EventId 0x7d80 is in DaemonPacketHandler.cpp (PDB module DaemonPacketHandler.obj).

// 0xaa90
unsigned int SendPublicationEvent::EventId() const
{
    return 129;
}

// 0xaaa0
SendPublicationEvent::~SendPublicationEvent()
{
}

// 0xaae0
GameEventManager::GameEventManager()
{
    if (Instance != nullptr)
        assertCrash(42);
    Instance = this;
    WorkerManager = nullptr;
    void* mem = Memory::_Manager[2]->Alloc(sizeof(GameEventEndEvent), kFile, 46);
    EventObject* endEvent;
    if (mem != nullptr)
        endEvent = new (mem) GameEventEndEvent();
    else
        endEvent = nullptr;
    EndEventObject = endEvent;
    _threadCount = 0;
    _threads = nullptr;
    _gameEventHandle = nullptr;
}

// 0xabc0
GameEventManager::~GameEventManager()
{
    if (Instance == nullptr)
        assertCrash(56);
    Instance = nullptr;
    if (_threads != nullptr)
    {
        Memory::_Manager[2]->Free(_threads, kFile, 61);
        _threads = nullptr;
    }
    if (EndEventObject != nullptr)
    {
        EndEventObject->removeReferenceCount(kFile, 67);
        EndEventObject = nullptr;
    }
}

// 0xac90
bool GameEventManager::Initialize(void (*failedEventHandler)(EventObject*), ThreadManager* threadManager,
                                  unsigned int threadCount)
{
    // ❓ 0xac90 tests rcx (= threadManager after LTCG drops the handler) and has no ref to the handler.
    // A test of failedEventHandler gives "lea FailedEventObjectHandler; test" in our build.
    if (Instance != nullptr || threadManager == nullptr)
        assertCrash(75);
    void* mem = Memory::_Manager[1]->Alloc(sizeof(GameEventManager), kFile, 77);
    GameEventManager* mgr = mem ? new (mem) GameEventManager() : nullptr;
    Instance = mgr;
    WorkerManager = threadManager;
    if (mgr == nullptr)
        assertCrash(80);
    HANDLE port = CreateIoCompletionPort(INVALID_HANDLE_VALUE, nullptr, 0, 0);
    Instance->_gameEventHandle = port;
    if (port == nullptr || port == INVALID_HANDLE_VALUE)
    {
        Log::Write(kFile, 86, static_cast<long>(GetLastError()), L"CreateIoCompletionPort, game-event");
        return false;
    }
    if (initWorkerThread(threadCount))
        return true;
    Log::Write(Log::LT_ERROR, kFile, 93, L"Worker Thread Initialize Error");
    return false;
}

// 0xae20
bool GameEventManager::initWorkerThread(unsigned int threadCount)
{
    GameEventManager* mgr = Instance;
    unsigned int count = threadCount;
    if (count == 0)
        count = 2 * SysInfo::ProcessorCount();
    mgr->_threads = static_cast<GameEventWorker**>(
        Memory::_Manager[2]->AllocZero(sizeof(GameEventWorker*) * count, kFile, 113));
    for (unsigned int i = 0; i < count; ++i)
    {
        void* mem = Memory::_Manager[2]->Alloc(sizeof(GameEventWorker), kFile, 116);
        if (mem != nullptr)
        {
            GameEventWorker* worker = new (mem) GameEventWorker();
            mgr->_threads[i] = worker;
            // LIFT: r9 is not set at 0xaeef. Initialize (0xb370) writes r9 before it reads it.
            worker->Initialize(static_cast<int>(i + 1), mgr, nullptr);
            WorkerManager->StartThread(worker, nullptr);  // LIFT: r8 not set at 0xaefe; StartThread (0x1f820) writes r8 first
        }
    }
    mgr->_threadCount = count;
    Sleep(1000);
    return true;
}

// 0xaf40
void GameEventManager::Clear()
{
    GameEventManager* mgr = Instance;
    if (mgr->_gameEventHandle != nullptr)
    {
        for (unsigned int i = 0; i < mgr->_threadCount; ++i)
        {
            if (mgr->_threads[i] != nullptr)
            {
                WorkerManager->StopThread(mgr->_threads[i]->_id, 0, false, false);
                mgr = Instance;
            }
        }
        for (unsigned int i = 0; i < mgr->_threadCount; ++i)
        {
            if (mgr->_threads[i] == nullptr)
                continue;
            // Inlined ThreadManager lookup and stop of the thread.
            ThreadManager* tm = WorkerManager;
            for (unsigned int idx = 0; idx < tm->_maxThreadCount; ++idx)
            {
                Thread* t = tm->_threads[idx];
                if (t == nullptr || t->_id != mgr->_threads[i]->_id)
                    continue;
                if (tm->_threadHandles[idx] != nullptr)
                {
                    static_cast<GameEventWorker*>(t)->stop();  // LIFT: call [rax+20h] at 0xb033 = vftable slot 4 = stop
                    if (WaitForSingleObject(tm->_threadHandles[idx], 2000) != 0)
                        TerminateThread(tm->_threadHandles[idx], 0);
                    tm->_threads[idx] = nullptr;
                    InterlockedDecrement(reinterpret_cast<long volatile*>(&tm->_runningThreadCount));
                    mgr = Instance;
                }
                break;
            }
            GameEventWorker* worker = mgr->_threads[i];
            if (worker != nullptr)
            {
                // The binary calls the virtual deleting destructor. Its body does not free memory.
                worker->~GameEventWorker();
                mgr = Instance;
            }
            Memory::_Manager[2]->Free(mgr->_threads[i], kFile, 153);
            Instance->_threads[i] = nullptr;
            mgr = Instance;
        }
    }
    if (mgr->_gameEventHandle != nullptr)
    {
        CloseHandle(mgr->_gameEventHandle);
        mgr = Instance;
        Instance->_gameEventHandle = nullptr;
    }
    mgr->~GameEventManager();
    Memory::_Manager[1]->Free(Instance, kFile, 163);  // BUG: 0xaf40 the dtor set Instance to null, so this frees null and leaks the manager.
    Instance = nullptr;
}

// 0xb140
bool GameEventManager::PostGameEventLogList(RetrieveEventLogContext* context)
{
    // LIFT: 0xb140 the "handle is null" log is the last block of the binary. The code reads the handle one time.
    HANDLE gameEventHandle = (Instance != nullptr) ? Instance->_gameEventHandle : nullptr;
    if (gameEventHandle == nullptr)
    {
        Log::Write(Log::LT_ERROR, kFile, 173, L"post game-event-log-list, game event handle is null");
        return false;
    }
    for (int i = 0; i < context->_count; ++i)
    {
        // Inlined RetrieveEventLogContext index check.
        EventLogInfo* info;
        if (i < 0 || i >= context->_count)
        {
            Log::Write(Log::LT_ERROR, L"SmartCouponDB.cpp", 113, L"get-eventloginfo, invalid index, index:%d, count:%d", i,
                       context->_count);
            info = nullptr;
        }
        else
        {
            info = &context->_eventLogList[i];
        }
        if (info == nullptr)
        {
            Log::Write(Log::LT_ERROR, kFile, 182, L"post game-event-log-list, invalid info, index:%d, count:%d", i,
                       context->_count);
            continue;
        }
        void* mem = Memory::_Manager[2]->Alloc(sizeof(GameEventLogEvent), kFile, 186);
        GameEventLogEvent* ev = nullptr;
        if (mem != nullptr)
        {
            ev = new (mem) GameEventLogEvent();
            ev->_gameEventLogId = info->logId;
            ev->_gameAccountId = info->gameAccountId;
            ev->_wid = info->wid;
            ev->_pcdbid = info->pcdbid;
            ev->_gameEventId = info->gameEventId;
            if (info->wid == 0 && info->pcdbid == 0)
                ev->_eventTargetType = 1;
            else if (info->wid != 0 && info->pcdbid != 0)
                ev->_eventTargetType = 2;
            else
                ev->_eventTargetType = 0;
        }
        PostQueuedCompletionStatus(gameEventHandle, 0, reinterpret_cast<ULONG_PTR>(static_cast<EventObject*>(ev)),
                                   nullptr);
        Log::Write(Log::LT_DEBUG, kFile, 201, L"post game-event-log-list, post, event-log-id:%I64d, index:%d, count:%d",
                   info->logId, i, context->_count);
    }
    return true;
}

// 0xb370
void GameEventWorker::Initialize(int workerId, GameEventManager* mgrInstance, void (*failedEventHandler)(EventObject*))
{
    (void)failedEventHandler;
    if (workerId <= 0 || &SmartCouponDaemon::FailedEventObjectHandler == nullptr)
        assertCrash(224);
    _mgrInstance = mgrInstance;
    // BUG: 0xb370 the argument is not used. The code always takes SmartCouponDaemon::FailedEventObjectHandler.
    _failedEventHandler = &SmartCouponDaemon::FailedEventObjectHandler;
    _workerId = workerId;
}

// 0xb410
void GameEventWorker::run()
{
    EventObject* endEvent = GameEventManager::EndEventObject;
    void* handle = GameEventManager::Instance ? GameEventManager::Instance->_gameEventHandle : nullptr;
    LogBufferAllocator::Initialize();
    Log::Write(Log::LT_DEBUG, kFile, 247, L"[event-log-worker], worker run, id:%I64u(%d)", _id, _workerId);
    while (_run)
    {
        DWORD numOfBytes = 0;
        EventObject* eventObject = nullptr;
        EventContext* context = nullptr;
        BOOL ok = GetQueuedCompletionStatus(handle, &numOfBytes, reinterpret_cast<PULONG_PTR>(&eventObject),
                                            reinterpret_cast<LPOVERLAPPED*>(&context), 1000);
        _lastExecuted = _threadManager->_now;
        if (ok)
        {
            if (eventObject == endEvent)
            {
                Log::Write(Log::LT_DEBUG, kFile, 263, L"[event-log-worker], catch terminiate event, id:%I64u(%d)", _id,
                           _workerId);
                break;
            }
            if (eventObject != nullptr)
            {
                eventObject->addReferenceCount(false, kFile, 270);
                if (!eventObject->HandleEvent(context, numOfBytes))
                {
                    Log::Write(Log::LT_DEBUG, kFile, 273,
                               L"[event-log-worker], event object handle failed, id:%I64u(%d)", _id, _workerId);
                    handleFailedEvent(eventObject, context, numOfBytes);
                }
                eventObject->removeReferenceCount(kFile, 276);
            }
        }
        else
        {
            int err = WSAGetLastError();
            if (err != WAIT_TIMEOUT)
                Log::Write(Log::LT_DEBUG, kFile, 288, L"[event-log-worker], IOCP error, error: %d", err);
        }
    }
    Log::Write(Log::LT_DEBUG, kFile, 293, L"[event-log-worker], stopped, id: id:%I64u(%d)", _id, _workerId);
}

// 0xb5f0
void GameEventWorker::stop()
{
    Log::Write(Log::LT_DEBUG, kFile, 299, L"[event-log-worker], worker stop, id:%I64u(%d)", _id, _workerId);
    PostQueuedCompletionStatus(GameEventManager::Instance ? GameEventManager::Instance->_gameEventHandle : nullptr, 0,
                               reinterpret_cast<ULONG_PTR>(GameEventManager::EndEventObject), nullptr);
}

// 0xb650
void GameEventWorker::handleFailedEvent(EventObject* eventObject, EventContext*, unsigned long)
{
    int state = Daemon::Instance->State;
    unsigned int eventId = eventObject != nullptr ? eventObject->EventId() : 0;
    // BUG: 0xb650 the format has %I64u, but the code gives a 32-bit event id.
    Log::Write(Log::LT_DEBUG, kFile, 308, L"[event-log], handle failed event, id:%I64u, daemon-state:%d", eventId, state);
    if (static_cast<unsigned int>(state) > Daemon::STATE_STOPPING)
    {
        _failedEventHandler(eventObject);
        if (eventObject != nullptr)
            eventObject->removeReferenceCount(kFile, 328);
    }
}

// 0xb6e0
bool GameEventLogEvent::HandleEvent(EventContext*, unsigned long)
{
    auto const& acc = _gameAccountId.guid;
    Log::Write(Log::LT_DEBUG, kFile, 335,
               L"[event-log], handle event, log-id:%I64d, acc:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, wid:%d, pcdbid:0x%I64X, game-event-id:%d",
               _gameEventLogId, GEW_ACC_ARGS(acc), static_cast<int>(_wid), _pcdbid, _gameEventId);
    RetrievePublicationContext publicationContext(128);
    int dbRetValue = 0;
    bool dbOk;
    switch (_eventTargetType)
    {
    case 1:
        dbOk = SmartCouponDB::ProcessAccountGameEventLog(&dbRetValue, _gameEventLogId, &_gameAccountId, _gameEventId,
                                                         &publicationContext);
        break;
    case 2:
        dbOk = SmartCouponDB::ProcessCharacterGameEventLog(&dbRetValue, _gameEventLogId, &_gameAccountId, _wid, _pcdbid,
                                                           _gameEventId, &publicationContext);
        break;
    default:
        Log::Write(Log::LT_ERROR, kFile, 353,
                   L"[event-log], handle event, fail, invalid target type, log-id:%I64d, acc:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, wid:%d, pcdbid:0x%I64X, game-event-id:%d, target-type:%d",
                   _gameEventLogId, GEW_ACC_ARGS(acc), static_cast<int>(_wid), _pcdbid, _gameEventId,
                   static_cast<int>(_eventTargetType));
        removeReferenceCount(kFile, 354);
        return true;
    }
    if (!dbOk)
    {
        Log::Write(Log::LT_ERROR, kFile, 361,
                   L"[event-log], handle game event log, failed in db, log-id:%I64d, acc:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, wid:%d, pcdbid:0x%I64X, game-event-id:%d, target-type:%d, dbRetValue:%d",
                   _gameEventLogId, GEW_ACC_ARGS(acc), static_cast<int>(_wid), _pcdbid, _gameEventId,
                   static_cast<int>(_eventTargetType), dbRetValue);
        int updateRetValue = 0;
        if (!SmartCouponDB::UpdateStatusToProcessFailure(&updateRetValue, _gameEventLogId, &_gameAccountId, _wid, _pcdbid,
                                                         _gameEventId))
        {
            Log::Write(Log::LT_ERROR, kFile, 368,
                       L"[event-log], handle game event log, db update fail, log-id:%I64d, acc:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, wid:%d, pcdbid:0x%I64X, game-event-id:%d, target-type:%d, dbRetValue:%d",
                       _gameEventLogId, GEW_ACC_ARGS(acc), static_cast<int>(_wid), _pcdbid, _gameEventId,
                       static_cast<int>(_eventTargetType), updateRetValue);
        }
        removeReferenceCount(kFile, 370);
        return true;
    }
    for (int idx = 0; idx < publicationContext._count; ++idx)
    {
        PublicationInfo* info = publicationContext.GetPublicationInfo(idx);
        if (info == nullptr)
        {
            Log::Write(Log::LT_ERROR, kFile, 381,
                       L"[event-log], handle game event log, publication info is null, log-id:%I64d, acc:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, wid:%d, pcdbid:0x%I64X, game-event-id:%d, target-type:%d, idx:%d",
                       _gameEventLogId, GEW_ACC_ARGS(acc), static_cast<int>(_wid), _pcdbid, _gameEventId,
                       static_cast<int>(_eventTargetType), idx);
            continue;
        }
        void* mem = Memory::_Manager[2]->Alloc(sizeof(SendPublicationEvent), kFile, 385);
        SendPublicationEvent* ev =
            mem ? new (mem) SendPublicationEvent(info->publicationId, info->gameAccountId, info->couponEventId) : nullptr;
        // LIFT: 0xb6e0 the copy is a source-form change. It removes the biased pointer const 0x16.
        // The behaviour does not change: main already logged the fields of info, not of ev.
        PublicationInfo const posted = *info;
        PostQueuedCompletionStatus(Network::iocpHandle(), 0, reinterpret_cast<ULONG_PTR>(static_cast<EventObject*>(ev)),
                                   nullptr);
        // BUG: 0xbc19 the original logs the fields of ev after the post. ev can be null or already freed.
        // This code logs a copy of the publication info.
        auto const& pacc = posted.gameAccountId.guid;
        Log::Write(Log::LT_DEBUG, kFile, 388,
                   L"[event-log], post publication event, publication-id:%I64d, acc:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, coupon-event-id:%d",
                   posted.publicationId, GEW_ACC_ARGS(pacc), posted.couponEventId);
    }
    removeReferenceCount(kFile, 391);
    return true;
}

// 0xbe30
bool SendPublicationEvent::HandleEvent(EventContext*, unsigned long)
{
    auto const& acc = _gameAccountId.guid;
    Log::Write(Log::LT_DEBUG, kFile, 399,
               L"[publication-event], handle event start, acc:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, publication-id:%I64d, coupon-event-id:%d",
               GEW_ACC_ARGS(acc), _publicationId, _couponEventId);
    void* mem = EventNotiJob::_pool.Checkout(kFile, 401);  // LIFT: LTCG put the args into Checkout (0x15ff: line 0x191)
    EventNotiJob* job = mem ? new (mem) EventNotiJob() : nullptr;
    if (!job->Initialize(&_gameAccountId, _couponEventId, _publicationId, _managementTid))
    {
        Log::Write(Log::LT_ERROR, kFile, 404,
                   L"[publication-event], handle event fail, init job fail, acc:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, publication-id:%I64d, coupon-event-id:%d",
                   GEW_ACC_ARGS(acc), _publicationId, _couponEventId);
        if (job != nullptr)
            job->removeReferenceCount(kFile, 423);
        if (_managementTid > 0)
        {
            void* evMem = Memory::_Manager[2]->Alloc(sizeof(SendRetryCouponPublicationFailEvent), kFile, 427);
            SendRetryCouponPublicationFailEvent* ev =
                evMem ? new (evMem) SendRetryCouponPublicationFailEvent(_managementTid, 2) : nullptr;
            PostQueuedCompletionStatus(Network::iocpHandle(), 0,
                                       reinterpret_cast<ULONG_PTR>(static_cast<EventObject*>(ev)), nullptr);
            Log::Write(Log::LT_DEBUG, kFile, 430,
                       L"[publication-event], handle event, post retry-coupon-publication-fail-event, tid:%I64d, failReason:%d",
                       _managementTid, 2);
        }
        removeReferenceCount(kFile, 433);
        return true;
    }
    JobManager* jobMgr = SmartCouponDaemon::_instance->_jobMgr;
    if (jobMgr->Register(job))
    {
        if (job == nullptr)
        {
            // Inlined JobManager execute check (CouponJob.cpp).
            Log::Write(Log::LT_ERROR, L"CouponJob.cpp", 206, L"== CRASH == [job-mgr], execute fail; null job");
            AlertSender::Write(L"CouponJob.cpp", 206, L"== CRASH == [job-mgr], execute fail; null job");
        }
        else if (job->execute(1, nullptr))
        {
            jobMgr->remove(job->_id);
        }
        Log::Write(Log::LT_DEBUG, kFile, 415,
                   L"[publication-event], handle event end, acc:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, publication-id:%I64d, coupon-event-id:%d",
                   GEW_ACC_ARGS(acc), _publicationId, _couponEventId);
        job->removeReferenceCount(kFile, 417);
        removeReferenceCount(kFile, 418);
    }
    else
    {
        Log::Write(Log::LT_ERROR, kFile, 409,
                   L"[publication-event], handle event fail, start job fail, acc:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, publication-id:%I64d, coupon-event-id:%d",
                   GEW_ACC_ARGS(acc), _publicationId, _couponEventId);
        job->removeReferenceCount(kFile, 410);
        removeReferenceCount(kFile, 411);
    }
    return true;
}

// 0xc2f0
bool RetryCouponPublicationEvent::HandleEvent(EventContext*, unsigned long)
{
    auto const& acc = _gameAccountId.guid;
    Log::Write(Log::LT_DEBUG, kFile, 439,
               L"[retry-coupon-publication], handle event, tid:%I64d, acc:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, publication-id:%I64d",
               _tid, GEW_ACC_ARGS(acc), _publicationId);
    int dbRetValue = 0;
    char failReason;  // LIFT: 0xc477 the original keeps it in bl (mov bl,4)
    if (!SmartCouponDB::LoadSingleCouponPublication(&dbRetValue, _publicationId, &_gameAccountId, &_couponEventId))
    {
        Log::Write(Log::LT_ERROR, kFile, 446,
                   L"[retry-coupon-publication], handle event, failed to load, tid:%I64d, acc:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, publication-id:%I64d, dbRetValue:%d",
                   _tid, GEW_ACC_ARGS(acc), _publicationId, dbRetValue);
        failReason = 4;
    // LIFT: 0xc2f0 the original has one shared fail path ($_ERROR_3). The zero coupon-event-id case jumps to it.
    postFail:
        void* mem = Memory::_Manager[2]->Alloc(sizeof(SendRetryCouponPublicationFailEvent), kFile, 465);
        SendRetryCouponPublicationFailEvent* ev = mem ? new (mem) SendRetryCouponPublicationFailEvent(_tid, failReason) : nullptr;
        PostQueuedCompletionStatus(Network::iocpHandle(), 0, reinterpret_cast<ULONG_PTR>(static_cast<EventObject*>(ev)),
                                   nullptr);
        Log::Write(Log::LT_DEBUG, kFile, 468,
                   L"[retry-coupon-publication], handle event, post retry-coupon-publication-fail-event, tid:%I64d, failReason:%d",
                   _tid, static_cast<int>(failReason));
        removeReferenceCount(kFile, 470);
        return true;
    }
    if (_couponEventId == 0)
    {
        failReason = 10;
        goto postFail;
    }
    void* mem = Memory::_Manager[2]->Alloc(sizeof(SendPublicationEvent), kFile, 456);
    SendPublicationEvent* ev = nullptr;
    if (mem != nullptr)
    {
        ev = new (mem) SendPublicationEvent(_publicationId, _gameAccountId, _couponEventId);
        ev->_managementTid = _tid;
    }
    PostQueuedCompletionStatus(Network::iocpHandle(), 0,
                               reinterpret_cast<ULONG_PTR>(static_cast<EventObject*>(ev)), nullptr);
    Log::Write(Log::LT_DEBUG, kFile, 459,
               L"[retry-coupon-publication], handle event, post publication-event, publication-id:%I64d, acc:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, coupon-event-id:%d, management-tid:%I64d",
               _publicationId, GEW_ACC_ARGS(acc), _couponEventId, _tid);
    removeReferenceCount(kFile, 461);
    return true;
}

// 0xc6e0
bool SendRetryCouponPublicationOkEvent::HandleEvent(EventContext*, unsigned long)
{
    // LIFT: inlined manager channel get (SmartCouponDaemon.cpp line 88). It reads _instance again after each call.
    EnterCriticalSection(&SmartCouponDaemon::_instance->_managerChannelLock.CS);
    ManagerChannel* channel = SmartCouponDaemon::_instance->_managerChannel;
    if (channel != nullptr)
        channel->addReferenceCount(false, L"SmartCouponDaemon.cpp", 88);
    LeaveCriticalSection(&SmartCouponDaemon::_instance->_managerChannelLock.CS);
    if (channel != nullptr)
    {
        channel->SendRetryCouponPublicationOk(const_cast<Session*>(channel->GetSession()), _tid, _acceptTid);
        channel->removeReferenceCount(kFile, 481);
    }
    else
    {
        Log::Write(Log::LT_ERROR, kFile, 485,
                   L"[retry-coupon-publication-ok-event], handle event, invalid management channel, tid:%I64d, accept-tid:%I64d",
                   _tid, _acceptTid);
    }
    removeReferenceCount(kFile, 488);
    return true;
}

// 0xc7d0
bool SendRetryCouponPublicationFailEvent::HandleEvent(EventContext*, unsigned long)
{
    // LIFT: inlined manager channel get (SmartCouponDaemon.cpp line 88). It reads _instance again after each call.
    EnterCriticalSection(&SmartCouponDaemon::_instance->_managerChannelLock.CS);
    ManagerChannel* channel = SmartCouponDaemon::_instance->_managerChannel;
    if (channel != nullptr)
        channel->addReferenceCount(false, L"SmartCouponDaemon.cpp", 88);
    LeaveCriticalSection(&SmartCouponDaemon::_instance->_managerChannelLock.CS);
    if (channel != nullptr)
    {
        channel->SendRetryCouponPublicationFail(const_cast<Session*>(channel->GetSession()), _tid, _reason);
        channel->removeReferenceCount(kFile, 499);
    }
    else
    {
        Log::Write(Log::LT_ERROR, kFile, 503,
                   L"[retry-coupon-publication-fail-event], handle event, invalid management channel, tid:%I64d, reason:%d",
                   _tid, static_cast<int>(_reason));
    }
    removeReferenceCount(kFile, 506);
    return true;
}
