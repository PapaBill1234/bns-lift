// PipeConsole.obj (CacheGate PDB).
#include "PipeConsole.h"
#include "Daemon.h"
#include "Log.h"
#include "AlertSender.h"
#include "CrashHandler.h"
#include "LogBuffer.h"
#include "Memory.h"
#include <shellapi.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <wchar.h>
#if defined(__clang__)
#include <crt_cpp_overload.h>  // The Wine headers do not have swprintf_s<N>. VS2010 has it.
#endif

static wchar_t const PIPE_CONSOLE_FILE[] = L"source\\PipeConsole.cpp";  // LIFT: name; LobbyGate wide string at 0x857d8 (Log::Write arg at 0x296d3).

// 0x14810
wchar_t const* PipeCommandProcess::Name()
{
    return L"PipeCommandProcess";
}

// 0x14820
wchar_t const* PipeConsole::Name()
{
    return L"PipeConsole";
}

// 0x14830
PipeCommandProcess::PipeCommandProcess()
{
    _maxFrozenSeconds = 60;
    _notifyEvent.Event = CreateEventW(nullptr, FALSE, FALSE, nullptr);
    _remote._head._argv = nullptr;
    _remote._head._argc = 0;
    _remote._head._prev = &_remote._head;
    _remote._head._next = &_remote._tail;
    _remote._tail._argv = nullptr;
    _remote._tail._argc = 0;
    _remote._tail._prev = &_remote._head;
    _remote._tail._next = &_remote._tail;
    _local._head._argv = nullptr;
    _local._head._argc = 0;
    _local._head._prev = &_local._head;
    _local._head._next = &_local._tail;
    _local._tail._argv = nullptr;
    _local._tail._argc = 0;
    _local._tail._prev = &_local._head;
    _local._tail._next = &_local._tail;
}

// 0x14950 (0x148e0 is the vector deleting destructor)
PipeCommandProcess::~PipeCommandProcess()
{
    clear(_remote);
    clear(_local);
}

// 0x149c0
void PipeCommandProcess::run()
{
    LogBufferAllocator::Initialize();
    PacketBufferAllocator::Initialize();
    while (_run)
    {
        if (_notifyEvent.Event != nullptr)
            WaitForSingleObject(_notifyEvent.Event, 1000);
        _lastExecuted = _threadManager->_now;

        _lock.Enter();
        if (_remote._head._next != &_remote._tail)
        {
            // Move all of _remote to the end of _local.
            _local._tail._prev->_next = _remote._head._next;
            _remote._head._next->_prev = _local._tail._prev;
            _remote._tail._prev->_next = &_local._tail;
            _local._tail._prev = _remote._tail._prev;
            _remote._head._argv = nullptr;
            _remote._head._argc = 0;
            _remote._head._prev = &_remote._head;
            _remote._head._next = &_remote._tail;
            _remote._tail._argv = nullptr;
            _remote._tail._argc = 0;
            _remote._tail._prev = &_remote._head;
            _remote._tail._next = &_remote._tail;
        }
        _lock.Leave();

        processCommand(_local);
        clear(_local);
    }
}

// 0x14ad0
void PipeCommandProcess::processCommand(CommandList& list)
{
    for (Command* command = list._head._next; command != &list._tail; command = command->_next)
    {
        wchar_t** argv = command->_argv;
        if (argv == nullptr)
            continue;
        int argc = command->_argc;
        if (argc < 1)
            continue;
        if (wcscmp(argv[0], L"cooldown-req") == 0)
            Daemon::Cooldown();
        else if (wcscmp(argv[0], L"reload-req") == 0)
            Daemon::Reload(argv, argc);
        else if (wcscmp(argv[0], L"crash-mail-req2") == 0 && argc >= 4)
            CrashHandler::SetMailInfo(argv[1], argv[2], argv[3]);
    }
}

// 0x14bd0
bool PipeCommandProcess::addCommand(wchar_t** argv, int argc)
{
    Command* command = (Command*)Memory::_Manager[2]->AllocZero(sizeof(Command), PIPE_CONSOLE_FILE, 110);
    if (command == nullptr)
        return false;
    command->_argv = argv;
    command->_next = nullptr;
    command->_prev = nullptr;
    command->_argc = argc;

    _lock.Enter();
    _remote._tail._prev->_next = command;
    command->_prev = _remote._tail._prev;
    _remote._tail._prev = command;
    command->_next = &_remote._tail;
    _lock.Leave();

    if (_notifyEvent.Event != nullptr)
        SetEvent(_notifyEvent.Event);
    return true;
}

// 0x14c90
void PipeCommandProcess::clear(CommandList& list)
{
    Command* node = list._head._next;
    while (node != &list._tail)
    {
        Command* current = node;
        node = node->_next;
        if (current->_argv != nullptr)
            LocalFree(current->_argv);
        Memory::_Manager[2]->Free(current, PIPE_CONSOLE_FILE, 155);
    }
    list._head._next = &list._tail;
    list._head._prev = &list._head;
    list._tail._prev = &list._head;
    list._tail._next = &list._tail;
    list._head._argv = nullptr;
    list._head._argc = 0;
    list._tail._argv = nullptr;
    list._tail._argc = 0;
}

// 0x14d30
PipeConsole::PipeConsole()
{
    _maxFrozenSeconds = 60;
    _state = 1;
    _detectFrozenThread = false;
    _crashIfExistFrozenThreadCount = 0;
    _running._head._value[0] = 0;
    _running._tail._key[0] = 0;
    _running._tail._value[0] = 0;
    _running._head._key[0] = 0;
    _running._head._prev = &_running._head;
    _running._tail._prev = &_running._head;
    _running._head._next = &_running._tail;
    _running._tail._next = &_running._tail;
    _invalid._head._key[0] = 0;
    _invalid._head._value[0] = 0;
    _invalid._head._prev = &_invalid._head;
    _invalid._tail._key[0] = 0;
    _invalid._tail._value[0] = 0;
    _invalid._head._next = &_invalid._tail;
    _invalid._tail._prev = &_invalid._head;
    _invalid._tail._next = &_invalid._tail;
    memset(_pipe, 0, sizeof(_pipe));
    _events[0] = nullptr;
    _events[1] = nullptr;
    _events[2] = nullptr;
    _events[3] = nullptr;
}

// 0x14e60 (0x14e40 is the scalar deleting destructor)
PipeConsole::~PipeConsole()
{
    cleanup();
}

// 0x14f10
bool PipeConsole::init()
{
    // 0x29690 (LobbyGate): xor r8d, r8d (threadId = nullptr) before both StartThread calls (0x296b0, 0x296f4).
    if (!initPipe())
        return false;
    if (!Daemon::Instance->threadManager->StartThread(&_commandProcess, nullptr))
    {
        Log::Write(Log::LT_ERROR, PIPE_CONSOLE_FILE, 212,
                   L"[pipe-console], cannot start pipe command process thread, error:%d", GetLastError());
        return false;
    }
    if (!Daemon::Instance->threadManager->StartThread(this, nullptr))
    {
        Log::Write(Log::LT_ERROR, PIPE_CONSOLE_FILE, 217,
                   L"[pipe-console], cannot start pipe thread, error:%d", GetLastError());
        return false;
    }
    return true;
}

// 0x14fa0
void PipeConsole::processCommand(PipeInstance& pipe)
{
    // BUG: 0x14fa0 cbRead can be 0x2000, so the index can be 4096 (one past chRequest).
    pipe.chRequest[pipe.cbRead / 2] = 0;
    writeReply(pipe, L"error \"invalid cmd\"");

    int argc = 0;
    wchar_t** argv = (wchar_t**)CommandLineToArgvW((LPCWSTR)pipe.chRequest, &argc);
    if (argv == nullptr)
        return;

    if (argc < 1)
    {
        Log::Write(Log::LT_ERROR, PIPE_CONSOLE_FILE, 238, L"[pipe-console], invalid request, cmd:%s",
                   pipe.chRequest);
    }
    else if (wcscmp(argv[0], L"state-req2") == 0)
    {
        writeStateReply2(pipe);
    }
    else if (wcscmp(argv[0], L"state-req") == 0)
    {
        writeStateReply(pipe);
    }
    else if (wcscmp(argv[0], L"cooldown-req") == 0)
    {
        if (_commandProcess.addCommand(argv, argc))
        {
            writeReply(pipe, L"cooldown-ok");
            return;  // The command list owns argv now.
        }
        writeReply(pipe, L"cooldown-fail");
    }
    else if (wcscmp(argv[0], L"reload-req") == 0)
    {
        if (_commandProcess.addCommand(argv, argc))
        {
            writeReply(pipe, L"reload-ok");
            return;
        }
        writeReply(pipe, L"reload-fail");
    }
    else if (wcscmp(argv[0], L"crash-mail-req2") == 0)
    {
        if (_commandProcess.addCommand(argv, argc))
        {
            writeReply(pipe, L"crash-mail-ok2");
            return;
        }
        writeReply(pipe, L"crash-mail-fail2");
    }
    LocalFree(argv);
}

// 0x15190
void PipeConsole::checkFrozenThread()
{
    ThreadManager* threadManager = Daemon::Instance->threadManager;
    if (threadManager == nullptr)
        return;

    unsigned int maxThreadCount = threadManager->_maxThreadCount;
    long long now = threadManager->_now;
    int frozenCount = 0;
    unsigned int count = 0;
    Thread* threads[1024];
    for (unsigned int i = 0; i < maxThreadCount; ++i)
    {
        if (count >= 1024)
            break;
        Thread* thread = threadManager->_threads[i];
        if (thread != nullptr && thread->_run)
            threads[count++] = thread;
    }

    wchar_t buffer[256];
    for (unsigned int i = 0; i < count; ++i)
    {
        Thread* thread = threads[i];
        if (thread == nullptr)
            continue;
        long long maxFrozenSeconds = thread->_maxFrozenSeconds;
        if (maxFrozenSeconds == 0)
            continue;
        swprintf_s(buffer, L"thread frozen, name:%s, id:%#I64x", thread->Name(), thread->_id);
        long long lastExecuted = thread->_lastExecuted;
        long long frozenSeconds = now - lastExecuted;
        if (lastExecuted != 0 && maxFrozenSeconds < frozenSeconds)
        {
            Log::Write(Log::LT_ERROR, PIPE_CONSOLE_FILE, 335,
                       L"[thread], thread frozen, name:%s, id:0x%08x, frozen-seconds:%d, max-frozen-seconds:%d",
                       thread->Name(), thread->_id, frozenSeconds, maxFrozenSeconds);
            SetInvalidInfo(buffer, true);
            ++frozenCount;
        }
        else
        {
            SetInvalidInfo(buffer, false);
        }
    }

    if (_crashIfExistFrozenThreadCount != 0 && frozenCount >= _crashIfExistFrozenThreadCount)
    {
        // Inlined crash macro.
        Log::Write(Log::LT_ERROR, PIPE_CONSOLE_FILE, 349, L"== CRASH == ASSERT CRASH");
        AlertSender::Write(PIPE_CONSOLE_FILE, 349, L"== CRASH == ASSERT CRASH");
        CrashHandler::MakeCrash("source\\PipeConsole.cpp", 349, L"");
    }
}

// 0x154d0
void PipeConsole::writeReply(PipeInstance& pipe, wchar_t const* format, ...)
{
    va_list args;
    va_start(args, format);
    int length = vswprintf(pipe.chReply, 4096, format, args);
    va_end(args);
    if (length >= 0)
    {
        pipe.chReply[length] = 0;
        pipe.cbToWrite = length * 2;
    }
    else
    {
        pipe.chReply[0] = 0;
        pipe.cbToWrite = 0;
    }
}

// 0x15540
int PipeConsole::writeStateInfo(wchar_t* buffer, int& len)
{
    int size = len;
    len = 0;
    _lock.Enter();
    int state = _state;
    if (state == 4)
    {
        if (_invalid._head._next == &_invalid._tail)
        {
            for (ItemNode* node = _running._head._next; node != &_running._tail; node = node->_next)
            {
                int n = swprintf(&buffer[len], size - len, L"\"%s:%s\" ", node->_key, node->_value);
                if (n > 0)
                    len += n;
            }
        }
        else
        {
            state = 5;
            for (ItemNode* node = _invalid._head._next; node != &_invalid._tail; node = node->_next)
            {
                int n = swprintf(&buffer[len], size - len, L"\"%s\" ", node->_key);
                if (n > 0)
                    len += n;
            }
        }
    }
    _lock.Leave();
    if (len > 0)
        buffer[len - 1] = 0;
    buffer[len] = 0;
    return state;
}

// 0x15680
void PipeConsole::writeStateReply(PipeInstance& pipe)
{
    wchar_t stateInfo[1024];
    int len = 1024;
    unsigned int state = writeStateInfo(stateInfo, len);
    if (state >= 10)
        state = 0;
    writeReply(pipe, L"%s %s %s", L"state-ok", Daemon::StateString[state], stateInfo);
}

// 0x15710
void PipeConsole::writeStateReply2(PipeInstance& pipe)
{
    wchar_t stateInfo[1024];
    int len = 1024;
    unsigned int state = writeStateInfo(stateInfo, len);
    if (state >= 10)
        state = 0;
    writeReply(pipe, L"%s %s %s %s", L"state-ok2", Daemon::Instance->VerStr, Daemon::StateString[state],
               stateInfo);
}

// 0x157b0
void PipeConsole::run()
{
    LogBufferAllocator::Initialize();
    PacketBufferAllocator::Initialize();
    DWORD bytesTransferred = 0;
    unsigned long long lastCheck = GetTickCount64() - Daemon::Instance->StartSystemTick64;
    while (_run)
    {
        DWORD result = WaitForMultipleObjects(4, _events, FALSE, 1000);
        if (result == WAIT_FAILED)
        {
            // BUG: 0x157b0 the address of GetLastError is given, not its result.
            Log::Write(Log::LT_ERROR, PIPE_CONSOLE_FILE, 500,
                       L"[pipe-console], WaitForMultipleObject error, error:%d", &GetLastError);
            return;
        }
        _lastExecuted = _threadManager->_now;
        unsigned long long tick = GetTickCount64() - Daemon::Instance->StartSystemTick64;
        if (_detectFrozenThread && (long long)(tick - lastCheck) > 5000)
        {
            checkFrozenThread();
            lastCheck = tick;
        }

        unsigned int index = result - WAIT_OBJECT_0;
        if (index > 3)
            continue;
        PipeInstance& pipe = _pipe[index];

        if (pipe.fPendingIO)
        {
            BOOL success = GetOverlappedResult(pipe.hPipeInst, &pipe.oOverlap, &bytesTransferred, FALSE);
            switch (pipe.dwState)
            {
            case 0:  // connecting
                if (!success)
                {
                    Log::Write(Log::LT_ERROR, PIPE_CONSOLE_FILE, 538, L"[pipe-console], connect failed, error:%d",
                               GetLastError());
                    goto reconnect;
                }
                pipe.dwState = 1;
                break;
            case 1:  // reading
                if (!success || bytesTransferred == 0)
                    goto reconnect;
                pipe.cbRead = bytesTransferred;
                pipe.dwState = 2;
                break;
            case 2:  // writing
                if (!success || bytesTransferred != pipe.cbToWrite)
                    goto reconnect;
                pipe.dwState = 1;
                break;
            default:
                Log::Write(Log::LT_ERROR, PIPE_CONSOLE_FILE, 567, L"[pipe-console], invalid pipe state, state:%d",
                           pipe.dwState);
                break;
            }
        }

        switch (pipe.dwState)
        {
        case 1:  // reading
        {
            BOOL success;
            DWORD error;
            success = ReadFile(pipe.hPipeInst, pipe.chRequest, sizeof(pipe.chRequest), &pipe.cbRead, &pipe.oOverlap);
            if (success && pipe.cbRead != 0)
            {
                pipe.dwState = 2;
                pipe.fPendingIO = 0;
                continue;
            }
            error = GetLastError();
            if (!success && error == ERROR_IO_PENDING)
            {
                pipe.fPendingIO = 1;
                continue;
            }
            goto reconnect;
        }
        case 2:  // writing
        {
            processCommand(pipe);
            BOOL success = WriteFile(pipe.hPipeInst, pipe.chReply, pipe.cbToWrite, &bytesTransferred, &pipe.oOverlap);
            if (success && bytesTransferred == pipe.cbToWrite)
            {
                pipe.dwState = 1;
                pipe.fPendingIO = 0;
                continue;
            }
            DWORD error = GetLastError();
            if (!success && error == ERROR_IO_PENDING)
            {
                pipe.fPendingIO = 1;
                continue;
            }
            goto reconnect;
        }
        // LIFT: one call site for all errors, as in the original 0x157b0.
    reconnect:
        disconnectAndReconnect(pipe);
        continue;
        default:
            Log::Write(Log::LT_ERROR, PIPE_CONSOLE_FILE, 639, L"[pipe-console], invalid pipe state, state:%d",
                       pipe.dwState);
            break;
        }
    }
}

// 0x15af0
bool PipeConsole::initPipe()
{
    wchar_t pipeName[128];
    swprintf_s(pipeName, L"\\\\.\\pipe\\bns_daemon_%08x", GetCurrentProcessId());
    for (int i = 0; i < 4; ++i)
    {
        _events[i] = CreateEventW(nullptr, TRUE, TRUE, nullptr);
        if (_events[i] == nullptr)
        {
            Log::Write(Log::LT_ERROR, PIPE_CONSOLE_FILE, 655,
                       L"[pipe-console], cannot initialize pipe; create event failed, error:%d", GetLastError());
            return false;
        }
        _pipe[i].oOverlap.hEvent = _events[i];
        _pipe[i].hPipeInst = CreateNamedPipeW((LPCWSTR)pipeName, PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED,
                                              PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, 4, 0x2000,
                                              0x2000, 5000, nullptr);
        if (_pipe[i].hPipeInst == INVALID_HANDLE_VALUE)
        {
            Log::Write(Log::LT_ERROR, PIPE_CONSOLE_FILE, 676,
                       L"[pipe-console], cannot initialize pipe; create named pipe failed, error:%d", GetLastError());
            return false;
        }
        _pipe[i].fPendingIO = connectPipe(_pipe[i].hPipeInst, &_pipe[i].oOverlap);
        _pipe[i].dwState = _pipe[i].fPendingIO ? 0 : 1;
    }
    Log::Write(Log::LT_DEBUG, PIPE_CONSOLE_FILE, 687, L"[pipe-console], initialize pipe");
    return true;
}

// 0x15c80
// LIFT: noinline. The original initPipe (0x15af0) and disconnectAndReconnect (0x15d20) call this function.
__declspec(noinline) bool PipeConsole::connectPipe(void* pipe, OVERLAPPED* overlapped)
{
    if (ConnectNamedPipe(pipe, overlapped))
    {
        Log::Write(Log::LT_ERROR, PIPE_CONSOLE_FILE, 698,
                   L"[pipe-console], cannot connect pipe; ConnectNamedPipe failed, error:%d", GetLastError());
        return false;
    }
    DWORD error = GetLastError();
    if (error == ERROR_IO_PENDING)
        return true;
    if (error == ERROR_PIPE_CONNECTED && SetEvent(overlapped->hEvent))
        return false;
    Log::Write(Log::LT_ERROR, PIPE_CONSOLE_FILE, 717,
               L"[pipe-console], cannot connect pipe; ConnectNamedPipe failed, error:%d", GetLastError());
    return false;
}

// 0x15d20
// LIFT: noinline. The original run (0x157b0) calls this function.
__declspec(noinline) void PipeConsole::disconnectAndReconnect(PipeInstance& pipe)
{
    if (!DisconnectNamedPipe(pipe.hPipeInst))
    {
        Log::Write(Log::LT_ERROR, PIPE_CONSOLE_FILE, 728, L"[pipe-console], disconnect named pipe failed, error:%d",
                   GetLastError());
    }
    pipe.fPendingIO = connectPipe(pipe.hPipeInst, &pipe.oOverlap);
    pipe.dwState = pipe.fPendingIO ? 0 : 1;
}

// 0x15d90
void PipeConsole::SetInvalidInfo(wchar_t const* keyString, bool isInvalid)
{
    _lock.Enter();
    ItemNode* node = _invalid._head._next;
    for (; node != &_invalid._tail; node = node->_next)
    {
        if (wcscmp(node->_key, keyString) == 0)
            break;
    }
    if (node == &_invalid._tail)
        node = nullptr;
    if (isInvalid)
    {
        if (node == nullptr)
            addNode(_invalid, keyString, L"");
    }
    else if (node != nullptr)
    {
        node->_next->_prev = node->_prev;
        node->_prev->_next = node->_next;
        Memory::_Manager[2]->Free(node, PIPE_CONSOLE_FILE, 837);
    }
    _lock.Leave();
}

// 0x2A5A0 (LobbyGate)
void PipeConsole::SetRunningInfo(wchar_t const* keyString, wchar_t const* valueString)
{
    _lock.Enter();
    ItemNode* node = _running._head._next;
    for (; node != &_running._tail; node = node->_next)
    {
        if (wcscmp(node->_key, keyString) == 0)
            break;
    }
    if (node == &_running._tail)
        node = nullptr;
    if (node == nullptr)
    {
        if (valueString != nullptr && *valueString != 0)
            addNode(_running, keyString, valueString);
    }
    else if (valueString != nullptr && *valueString != 0)
    {
        wcsncpy_s(node->_value, 129, valueString, 128);
        node->_value[128] = 0;
    }
    else
    {
        node->_next->_prev = node->_prev;
        node->_prev->_next = node->_next;
        Memory::_Manager[2]->Free(node, PIPE_CONSOLE_FILE, 837);
    }
    _lock.Leave();
}

// 0x25000 (SmartCouponDaemon)
void PipeConsole::SetDetectFrozenThread(bool detect, int crashCount)
{
    // LIFT: LTCG removed the arguments. 0x25000 overwrites edx (0x25035) and r8d (0x2503c) before any read. The binary always sets true and 0.
    (void)detect;
    (void)crashCount;
    ThreadManager* threadManager = Daemon::Instance->threadManager;
    if (threadManager != nullptr)
    {
        // Reset the last run time of each running thread (inlined ThreadManager code).
        threadManager->_now = _time64(nullptr);
        Thread* threads[1024];
        unsigned int count = 0;
        for (unsigned int i = 0; i < threadManager->_maxThreadCount; ++i)
        {
            if (count >= 1024)
                break;
            Thread* thread = threadManager->_threads[i];
            if (thread != nullptr && thread->_run)
                threads[count++] = thread;
        }
        for (unsigned int i = 0; i < count; ++i)
        {
            Thread* thread = threads[i];
            if (thread != nullptr && thread->_maxFrozenSeconds != 0)
                thread->_lastExecuted = thread->_threadManager->_now;
        }
    }
    _detectFrozenThread = true;
    _crashIfExistFrozenThreadCount = 0;
}

// 0x15ed0
// LIFT: noinline. The original SetInvalidInfo (0x15d90) and checkFrozenThread (0x15190) call this function.
__declspec(noinline) bool PipeConsole::addNode(ItemList& list, wchar_t const* keyString, wchar_t const* valueString)
{
    ItemNode* node = (ItemNode*)Memory::_Manager[2]->AllocZero(sizeof(ItemNode), PIPE_CONSOLE_FILE, 842);
    if (node == nullptr)
        return false;
    wcsncpy_s(node->_key, 129, keyString, 128);
    node->_key[128] = 0;
    // BUG: 0x15ed0 valueString is not used; the value is always L"".
    wcsncpy_s(node->_value, 129, L"", 128);
    node->_value[128] = 0;
    node->_prev = &list._head;
    node->_next = list._head._next;
    list._head._next->_prev = node;
    list._head._next = node;
    return true;
}

// 0x15f90
void PipeConsole::clear(ItemList& list)
{
    ItemNode* node = list._head._next;
    while (node != &list._tail)
    {
        ItemNode* current = node;
        node = node->_next;
        Memory::_Manager[2]->Free(current, PIPE_CONSOLE_FILE, 870);
    }
    list._head._prev = &list._head;
    list._head._key[0] = 0;
    list._head._value[0] = 0;
    list._tail._key[0] = 0;
    list._tail._value[0] = 0;
    list._head._next = &list._tail;
    list._tail._prev = &list._head;
    list._tail._next = &list._tail;
}

// 0x16030
void PipeConsole::cleanup()
{
    clear(_invalid);
    clear(_running);
    for (int i = 0; i < 4; ++i)
    {
        DisconnectNamedPipe(_pipe[i].hPipeInst);
        CloseHandle(_pipe[i].hPipeInst);
        _pipe[i].hPipeInst = INVALID_HANDLE_VALUE;
    }
    for (int i = 0; i < 4; ++i)
    {
        CloseHandle(_events[i]);
        _events[i] = nullptr;
    }
    ThreadManager* threadManager = Daemon::Instance->threadManager;
    if (threadManager != nullptr)
    {
        if (_commandProcess._run)
            threadManager->StopThread(_commandProcess._id, 2000, true, true);
        if (_run)
            threadManager->StopThread(_id, 2000, true, true);
    }
}
