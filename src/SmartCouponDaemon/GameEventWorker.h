// GameEventWorker.obj (SmartCouponDaemon PDB). Layouts from include/pdb/SmartCouponDaemon/types.h.
#pragma once
#include <stddef.h>
#include "Thread.h"

class GameEventManager;
class RetrieveEventLogContext;
class EventObject;
class ThreadManager;

class GameEventWorker : public Thread
{
public:
    virtual ~GameEventWorker();
    virtual wchar_t const* Name();
    virtual void run();
    virtual void stop();

    int _workerId;
    GameEventManager* _mgrInstance;
    void* _failedEventHandler;
};
static_assert(sizeof(GameEventWorker) == 0x48, "sizeof GameEventWorker");
static_assert(offsetof(GameEventWorker, _workerId) == 0x30, "GameEventWorker::_workerId");

class GameEventManager
{
public:
    static bool PostGameEventLogList(RetrieveEventLogContext* context);
    static bool Initialize(void (*failedEventHandler)(EventObject*), ThreadManager* threadManager, unsigned int threadCount);  // ❓ arguments
    static void Clear();

    static GameEventManager* Instance;

    unsigned int _threadCount;
    GameEventWorker** _threads;
    void* _gameEventHandle;
};
static_assert(sizeof(GameEventManager) == 0x18, "sizeof GameEventManager");
static_assert(offsetof(GameEventManager, _gameEventHandle) == 0x10, "GameEventManager::_gameEventHandle");
