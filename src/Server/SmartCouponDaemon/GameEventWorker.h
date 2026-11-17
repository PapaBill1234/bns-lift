// GameEventWorker.obj (SmartCouponDaemon PDB). Layouts from include/pdb/SmartCouponDaemon/types.h.
#pragma once
#include <stddef.h>
#include "Thread.h"
#include "TimerQueue.h"
#include "StringUtil.h"

class GameEventManager;
class RetrieveEventLogContext;
class ThreadManager;

class GameEventWorker : public Thread
{
public:
    // LIFT: Inlined in GameEventManager::initWorkerThread (0xAE20).
    GameEventWorker() : _workerId(0), _mgrInstance(nullptr), _failedEventHandler(nullptr) { _maxFrozenSeconds = 60; }
    virtual ~GameEventWorker() {}
    virtual wchar_t const* Name();  // 0xAA80
    virtual void run();             // 0xB410
    virtual void stop();            // 0xB5F0

    void Initialize(int workerId, GameEventManager* mgrInstance, void (*failedEventHandler)(EventObject*));  // 0xB370

private:
    void handleFailedEvent(EventObject* eventObject, EventContext* context, unsigned long numOfBytes);  // 0xB650

public:
    int _workerId;
    GameEventManager* _mgrInstance;
    void (*_failedEventHandler)(EventObject*);
};
static_assert(sizeof(GameEventWorker) == 0x48, "sizeof GameEventWorker");
static_assert(offsetof(GameEventWorker, _workerId) == 0x30, "GameEventWorker::_workerId");

class GameEventManager
{
public:
    static bool PostGameEventLogList(RetrieveEventLogContext* context);  // 0xB140
    static bool Initialize(void (*failedEventHandler)(EventObject*), ThreadManager* threadManager,
                           unsigned int threadCount);  // 0xAC90
    static void Clear();                               // 0xAF40

    static GameEventManager* Instance;
    static ThreadManager* WorkerManager;
    static EventObject* EndEventObject;

private:
    GameEventManager();   // 0xAAE0
    ~GameEventManager();  // 0xABC0
    static bool initWorkerThread(unsigned int threadCount);  // 0xAE20

public:
    unsigned int _threadCount;
    GameEventWorker** _threads;
    void* _gameEventHandle;
};
static_assert(sizeof(GameEventManager) == 0x18, "sizeof GameEventManager");
static_assert(offsetof(GameEventManager, _gameEventHandle) == 0x10, "GameEventManager::_gameEventHandle");

class GameEventEndEvent : public DynamicEventObject
{
public:
    // LIFT: Inlined in GameEventManager::GameEventManager (0xAAE0).
    GameEventEndEvent() { _tag = 1546; }
    virtual unsigned int EventId() const;                       // 0x231F0
    virtual bool HandleEvent(EventContext* ctx, unsigned long);  // 0xAAD0
    virtual ~GameEventEndEvent() {}
};
static_assert(sizeof(GameEventEndEvent) == 0x18, "sizeof GameEventEndEvent");

class GameEventLogEvent : public DynamicEventObject
{
public:
    // LIFT: Inlined in GameEventManager::PostGameEventLogList (0xB140).
    GameEventLogEvent()
        : _gameEventLogId(0), _wid(0), _pcdbid(0), _gameEventId(0), _eventTargetType(0)
    {
        _gameAccountId.id[0] = 0;
        _gameAccountId.id[1] = 0;
    }
    virtual ~GameEventLogEvent() {}                             // 0x7D90
    virtual unsigned int EventId() const;                       // 0x7D80
    virtual bool HandleEvent(EventContext* ctx, unsigned long);  // 0xB6E0

    long long _gameEventLogId;
    id128 _gameAccountId;
    short _wid;
    long long _pcdbid;
    int _gameEventId;
    char _eventTargetType;
};
static_assert(sizeof(GameEventLogEvent) == 0x48, "sizeof GameEventLogEvent");
static_assert(offsetof(GameEventLogEvent, _wid) == 0x30, "GameEventLogEvent::_wid");
static_assert(offsetof(GameEventLogEvent, _eventTargetType) == 0x44, "GameEventLogEvent::_eventTargetType");
