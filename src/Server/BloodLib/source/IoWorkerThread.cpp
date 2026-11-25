// IoWorkerThread.obj (CacheGate PDB).
#include "IoWorkerThread.h"
#include <winsock2.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include "AlertSender.h"
#include "CrashHandler.h"
#include "Daemon.h"
#include "Listener.h"
#include "Log.h"
#include "LogBuffer.h"
#include "Network.h"
#include "Session.h"

static wchar_t const IOWORKER_FILE[] = L"source\\IoWorkerThread.cpp";

// Inlined crash macro.
#define IOWORKER_ASSERT_CRASH(line)                                                  \
    do                                                                               \
    {                                                                                \
        Log::Write(Log::LT_ERROR, IOWORKER_FILE, line, L"== CRASH == ASSERT CRASH"); \
        AlertSender::Write(IOWORKER_FILE, line, L"== CRASH == ASSERT CRASH");       \
        CrashHandler::MakeCrash("source\\IoWorkerThread.cpp", line, L"");            \
    } while (0)

__declspec(thread) int IoWorker::WorkerId;
__declspec(thread) ZSTD_CCtx_s* IoWorker::ZstdCCtx;

// PDB ZSTD_defaultCMem (CacheGate zstd_compress.obj, 0x469c0). All members are null (default allocator).
static ZSTD_customMem const ZSTD_defaultCMem = {nullptr, nullptr, nullptr};

// 0x199E0
wchar_t const* IoWorker::Name()
{
    return L"IoWorker";
}

// 0x199F0 vector deleting destructor
IoWorker::~IoWorker()
{
}

// 0x19A00
bool IoWorker::Initialize(int workerId, Network* networkInstance, void (*failedEventHandler)(EventObject*))
{
    // LIFT: LTCG put a constant in place of failedEventHandler. 0x19A1C loads 0x4B40
    // (PDB: CacheGate::FailedEventObjectHandler) and 0x19A80 stores it.
    if (workerId <= 0 || failedEventHandler == nullptr)
        IOWORKER_ASSERT_CRASH(42);

    _networkInstance = networkInstance;
    _failedEventHandler = failedEventHandler;
    _workerId = workerId;
    return true;
}

// 0x19AA0
void IoWorker::yield()
{
    PostQueuedCompletionStatus(_networkInstance->_iocpHandle, 0, 0, nullptr);
}

// 0x19AC0
void IoWorker::run()
{
    EventObject* endEventObject = Network::EndEventObject;
    WorkerId = _workerId;
    DWORD numOfBytes = 0;
    LPOVERLAPPED context = nullptr;
    EventObject* eventObject = nullptr;
    HANDLE iocpHandle = _networkInstance->_iocpHandle;

    LogBufferAllocator::Initialize();
    PacketBufferAllocator::Initialize();
    ZstdCCtx = ZSTD_createCCtx_advanced(ZSTD_defaultCMem);
    srand(static_cast<unsigned int>(_time64(nullptr)) + _workerId);

    // Inlined block. The order and the state check come from 0x19AC0.
    auto handleFailedEvent = [this](EventObject* eventObject, EventContext* context, unsigned long numOfBytes) {
        if (static_cast<unsigned int>(Daemon::Instance->State) <= static_cast<unsigned int>(Daemon::STATE_STOPPING))
            return;

        switch (eventObject->EventId())
        {
        case EVID_IO_ACCEPT:
            static_cast<PortListener*>(static_cast<DynamicEventObject*>(eventObject))->HandleFailedEvent(context, numOfBytes);
            break;
        case EVID_IO_CONNECT:
            static_cast<Session*>(eventObject)->HandleFailedEvent(context, numOfBytes);
            break;
        }
        _failedEventHandler(eventObject);
    };

    BOOL result;
    for (;;)
    {
        result = GetQueuedCompletionStatus(iocpHandle, &numOfBytes, reinterpret_cast<PULONG_PTR>(&eventObject), &context,
                                           1000);
        _lastExecuted = _threadManager->_now;
        if (!_run)
        {
            Log::Write(Log::LT_DEBUG, IOWORKER_FILE, 94, L"[worker], run flag has off; stop, id: %d", WorkerId);
            break;
        }

        if (!result)
        {
            if (eventObject != nullptr && context != nullptr)
            {
                eventObject->addReferenceCount(false, IOWORKER_FILE, 126);
                handleFailedEvent(eventObject, static_cast<EventContext*>(context), numOfBytes);
                eventObject->removeReferenceCount(IOWORKER_FILE, 128);
            }
            else
            {
                int error = WSAGetLastError();
                if (error != WAIT_TIMEOUT)
                    Log::Write(Log::LT_DEBUG, IOWORKER_FILE, 135, L"[worker], IOCP error, error: %d", error);
            }
            continue;
        }

        if (eventObject == endEventObject)
        {
            Log::Write(Log::LT_DEBUG, IOWORKER_FILE, 103, L"[worker], catch terminiate event, id: %d", WorkerId);
            break;
        }

        if (eventObject != nullptr)
        {
            eventObject->addReferenceCount(false, IOWORKER_FILE, 111);
            if (!eventObject->HandleEvent(static_cast<EventContext*>(context), numOfBytes))
            {
                Log::Write(Log::LT_DEBUG, IOWORKER_FILE, 114, L"[worker], event object handle failed, id: %d", WorkerId);
                handleFailedEvent(eventObject, static_cast<EventContext*>(context), numOfBytes);
            }
            eventObject->removeReferenceCount(IOWORKER_FILE, 117);
        }
    }
    Log::Write(Log::LT_DEBUG, IOWORKER_FILE, 140, L"[worker], stopped, id: %d", WorkerId);
}

// 0x19DD0
void IoWorker::stop()
{
    PostQueuedCompletionStatus(_networkInstance->_iocpHandle, 0, reinterpret_cast<ULONG_PTR>(Network::EndEventObject),
                               nullptr);
}
