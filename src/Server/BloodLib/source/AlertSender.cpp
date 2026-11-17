// AlertSender.obj (SmartCouponDaemon PDB).
// Compiler-made code in AlertSender.obj (not lifted by hand):
//   0x194A0 swprintf_s<64>, 0x19470 swprintf_s<260>: template overloads from crt_cpp_overload.h.
//   0x18AD0 scalar deleting destructor, 0x51E30 its dtor$0 (calls Thread::~Thread).
//   0x52A50 dynamic initializer, 0x52B80 atexit destructor, 0x52A20 its dtor$0 (_alertSender).
#include <winsock2.h>
#include "AlertSender.h"
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#if defined(__clang__)
#include <crt_cpp_overload.h>  // The Wine headers do not have swprintf_s<N>. VS2010 has it.
#endif
#include "Daemon.h"
#include "Memory.h"
#include "MemoryManager.h"

#define ALERT_SENDER_FILE L"source\\AlertSender.cpp"

// 0x52A50 (SmartCouponDaemon) dynamic initializer.
AlertSender AlertSender::_alertSender;

// 0x18A10 (SmartCouponDaemon)
AlertSender::AlertSender()
{
    _maxFrozenSeconds = 60;  // LIFT: The inlined Thread constructor in this exe writes 60.
    _bufferList._head = nullptr;
    _bufferList._tail = nullptr;
    _bufferList._count = 0;
    InitializeCriticalSection(&_cs);
    _socket = INVALID_SOCKET;
    memset(&_remoteAddr, 0, sizeof(_remoteAddr));
    _sockEvent = nullptr;
    _itemEvent = nullptr;
    _threadId = 0;
    _init = false;
    _maxLogCount = 1000;
    _daemonNameBytes = 0;
    _daemonName[0] = 0;  // The original writes 4 zero bytes over _daemonNameBytes and _daemonName[0].
    _versionBytes = 0;
    _version[0] = 0;
    _worldId = 0;
}

// 0x18A00 (SmartCouponDaemon)
wchar_t const* AlertSender::Name()
{
    return L"alert-sender";
}

// 0x52B80 (SmartCouponDaemon) atexit destructor and 0x18AD0 scalar deleting destructor.
AlertSender::~AlertSender()
{
    fini();
    DeleteCriticalSection(&_cs);
}

// 0x19DA0 (LobbyGate)
// LTCG: the code uses _alertSender and not `this`. rcx holds address. The compiler put in the
// constants daemonName L"LOBBYGATE", worldId 0 and maxLogCount 1000.
bool AlertSender::init(wchar_t* address, wchar_t const* daemonName, int worldId, int maxLogCount)
{
    size_t nameLength = wcslen(daemonName);
    wcsncpy(_daemonName, daemonName, nameLength);
    _daemonNameBytes = static_cast<short>(nameLength * 2);
    _daemonName[nameLength] = 0;
    Daemon::Version ver;
    Daemon::LoadVersion(&ver, _version, 64);
    size_t versionLength = wcslen(_version);
    int addrLen = sizeof(_remoteAddr);
    _version[versionLength] = 0;
    memset(&_remoteAddr, 0, sizeof(_remoteAddr));
    _versionBytes = static_cast<short>(versionLength * 2);
    _worldId = worldId;
    _maxLogCount = maxLogCount;
    if (WSAStringToAddressW(address, AF_INET, nullptr, &_remoteAddr, &addrLen) == SOCKET_ERROR)
        return false;
    _itemEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    if (_itemEvent == nullptr || !createSocket())
        return false;
    if (connect(_socket, &_remoteAddr, sizeof(_remoteAddr)) == SOCKET_ERROR && WSAGetLastError() != WSAEWOULDBLOCK)
        return false;
    if (!Daemon::Instance->threadManager->StartThread(this, &_threadId))
        return false;
    _init = true;
    return true;
}

// 0x18B20 (SmartCouponDaemon)
void AlertSender::fini()
{
    if (Daemon::Instance != nullptr)
    {
        ThreadManager* threadManager = Daemon::Instance->threadManager;
        if (threadManager != nullptr && _run)
            threadManager->StopThread(_threadId, 2000, true, true);
    }
    if (_socket != INVALID_SOCKET)
    {
        closesocket(_socket);
        _socket = INVALID_SOCKET;
    }
    if (_sockEvent != nullptr)
    {
        WSACloseEvent(_sockEvent);
        _sockEvent = nullptr;
    }
    if (_itemEvent != nullptr)
    {
        CloseHandle(_itemEvent);
        _itemEvent = nullptr;
    }
    memset(&_remoteAddr, 0, sizeof(_remoteAddr));
    _daemonNameBytes = 0;
    _daemonName[0] = 0;
    _worldId = 0;
    EnterCriticalSection(&_cs);
    AlertBuffer* buffer = _bufferList._head;
    while (buffer != nullptr)
    {
        AlertBuffer* next = buffer->_next;
        Memory::_Manager[2]->Free(buffer, ALERT_SENDER_FILE, 95);
        buffer = next;
    }
    _bufferList._head = nullptr;
    _bufferList._tail = nullptr;
    _bufferList._count = 0;
    LeaveCriticalSection(&_cs);
}

// 0x18C40 (SmartCouponDaemon)
bool AlertSender::createSocket()
{
    if (_socket != INVALID_SOCKET)
    {
        closesocket(_socket);
        _socket = INVALID_SOCKET;
    }
    if (_sockEvent != nullptr)
    {
        WSACloseEvent(_sockEvent);
        _sockEvent = nullptr;
    }
    _socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    _sockEvent = WSACreateEvent();
    return _socket != INVALID_SOCKET && _sockEvent != nullptr &&
           WSAEventSelect(_socket, _sockEvent, FD_READ | FD_WRITE | FD_CONNECT | FD_CLOSE) != SOCKET_ERROR;
}

// 0x18CD0 (SmartCouponDaemon)
void AlertSender::Write(wchar_t const* file, int line, wchar_t const* format, ...)
{
    va_list args;
    va_start(args, format);
    _alertSender.writev2(file, line, format, args);
    va_end(args);
}

// 0x18CF0 (SmartCouponDaemon)
// LTCG removed `this`. The code uses _alertSender, that is the same object.
void AlertSender::writev2(wchar_t const* file, int line, wchar_t const* format, char* args)
{
    if (!_init || !_run)
        return;

    wchar_t fstr[260];
    short fileBytes;
    if (file != nullptr)
    {
        wchar_t name[264];
        wchar_t ext[264];
        _wsplitpath_s(file, nullptr, 0, nullptr, 0, name, 260, ext, 260);
        short count = static_cast<short>(swprintf_s(fstr, L"%s%s", name, ext));
        if (count < 0)
            return;
        fileBytes = static_cast<short>(count * 2);
    }
    else
    {
        fstr[0] = 0;
        fileBytes = 0;
    }

    // The original makes this string and does not use it.
    wchar_t lstr[64];
    if (static_cast<short>(swprintf_s(lstr, L"%d,", line)) < 0)
        return;

    wchar_t log[2000];
    short logCount = static_cast<short>(vswprintf_s(log, 2000, format, args));
    if (logCount < 0)
        return;

    short size = static_cast<short>(fileBytes + 2 * logCount + _versionBytes + _daemonNameBytes + 20);
    AlertBuffer* buffer = static_cast<AlertBuffer*>(
        Memory::_Manager[2]->AllocZero(size + sizeof(AlertBuffer), ALERT_SENDER_FILE, 399));
    if (buffer == nullptr)
        return;

    *reinterpret_cast<short*>(&buffer->_buffer[buffer->_count]) = size;
    buffer->_count += 2;
    *reinterpret_cast<short*>(&buffer->_buffer[buffer->_count]) = 2;
    buffer->_count += 2;
    *reinterpret_cast<short*>(&buffer->_buffer[buffer->_count]) = _daemonNameBytes;
    buffer->_count += 2;
    int bytes = _daemonNameBytes;
    memcpy(&buffer->_buffer[buffer->_count], _daemonName, _daemonNameBytes);
    buffer->_count += bytes;
    *reinterpret_cast<int*>(&buffer->_buffer[buffer->_count]) = _worldId;
    buffer->_count += 4;
    *reinterpret_cast<short*>(&buffer->_buffer[buffer->_count]) = _versionBytes;
    buffer->_count += 2;
    bytes = _versionBytes;
    memcpy(&buffer->_buffer[buffer->_count], _version, _versionBytes);
    buffer->_count += bytes;
    *reinterpret_cast<short*>(&buffer->_buffer[buffer->_count]) = fileBytes;
    buffer->_count += 2;
    memcpy(&buffer->_buffer[buffer->_count], fstr, fileBytes);
    buffer->_count += fileBytes;
    *reinterpret_cast<int*>(&buffer->_buffer[buffer->_count]) = line;
    buffer->_count += 4;
    *reinterpret_cast<short*>(&buffer->_buffer[buffer->_count]) = static_cast<short>(2 * logCount);
    buffer->_count += 2;
    bytes = 2 * logCount;
    memcpy(&buffer->_buffer[buffer->_count], log, bytes);
    buffer->_count += bytes;

    bool added;
    EnterCriticalSection(&_cs);
    if (_maxLogCount > _bufferList._count)
    {
        if (_bufferList._tail != nullptr)
        {
            _bufferList._tail->_next = buffer;
            _bufferList._tail = buffer;
            buffer->_next = nullptr;
            ++_bufferList._count;
        }
        else
        {
            _bufferList._head = buffer;
            _bufferList._tail = buffer;
            _bufferList._count = 1;
        }
        added = true;
    }
    else
    {
        added = false;
    }
    LeaveCriticalSection(&_cs);
    if (added)
        SetEvent(_itemEvent);
    else
        Memory::_Manager[2]->Free(buffer, ALERT_SENDER_FILE, 427);
}

// 0x19300 (SmartCouponDaemon)
bool AlertSender::sendRemain(AlertBufferList& bufferList)
{
    EnterCriticalSection(&_cs);
    if (_bufferList._head != nullptr)
    {
        if (bufferList._tail != nullptr)
        {
            bufferList._tail->_next = _bufferList._head;
            bufferList._tail = _bufferList._tail;
            bufferList._count += _bufferList._count;
        }
        else
        {
            bufferList._head = _bufferList._head;
            bufferList._tail = _bufferList._tail;
            bufferList._count = _bufferList._count;
        }
        _bufferList._head = nullptr;
        _bufferList._tail = nullptr;
        _bufferList._count = 0;
    }
    LeaveCriticalSection(&_cs);

    while (bufferList._head != nullptr)
    {
        AlertBuffer* buffer = bufferList._head;
        WSABUF buf;
        buf.len = buffer->_count - buffer->_sent;
        buf.buf = &buffer->_buffer[buffer->_sent];
        DWORD sent = 0;
        if (WSASend(_socket, &buf, 1, &sent, 0, nullptr, nullptr) != 0)
        {
            if (WSAGetLastError() != WSAEWOULDBLOCK)
                return false;
            continue;
        }
        buffer->_sent += sent;
        if (buffer->_count <= buffer->_sent)
        {
            AlertBuffer* head = bufferList._head;
            if (head != nullptr)
            {
                if (head == bufferList._tail)
                {
                    bufferList._head = nullptr;
                    bufferList._tail = nullptr;
                    bufferList._count = 0;
                }
                else
                {
                    --bufferList._count;
                    bufferList._head = head->_next;
                }
                Memory::_Manager[2]->Free(head, ALERT_SENDER_FILE, 85);
            }
        }
    }
    return true;
}

// 0x19060 (SmartCouponDaemon)
void AlertSender::run()
{
    AlertBufferList list;
    list._head = nullptr;
    list._tail = nullptr;
    list._count = 0;

    while (_run)
    {
        HANDLE handles[2] = {_sockEvent, _itemEvent};
        bool failed = false;
        bool reconnect = false;
        bool fatal = false;
        if (WaitForMultipleObjects(2, handles, FALSE, 1000) == WAIT_FAILED)
        {
            fatal = true;
        }
        else
        {
            _lastExecuted = _threadManager->_now;
            DWORD result = WaitForSingleObject(_itemEvent, 0);
            if (result == WAIT_OBJECT_0 || result == WAIT_TIMEOUT)
            {
                ResetEvent(_itemEvent);
                failed = !sendRemain(list);
            }
            else if (result == WAIT_FAILED)
            {
                fatal = true;
            }

            if (!fatal)
            {
                result = WaitForSingleObject(_sockEvent, 0);
                if (result == WAIT_OBJECT_0)
                {
                    WSANETWORKEVENTS events;
                    memset(&events, 0, sizeof(events));
                    if (WSAEnumNetworkEvents(_socket, _sockEvent, &events) == SOCKET_ERROR)
                    {
                        reconnect = true;
                    }
                    else if ((events.lNetworkEvents & FD_CONNECT) != 0)
                    {
                        if (events.iErrorCode[FD_CONNECT_BIT] != 0)
                            reconnect = true;
                        else
                            failed = !sendRemain(list);
                    }
                    else if ((events.lNetworkEvents & FD_WRITE) != 0)
                    {
                        if (events.iErrorCode[FD_WRITE_BIT] != 0)
                            reconnect = true;
                        else
                            failed = !sendRemain(list);
                    }
                    else if ((events.lNetworkEvents & FD_CLOSE) != 0)
                    {
                        reconnect = true;
                    }
                }
                else if (result == WAIT_FAILED)
                {
                    fatal = true;
                }
            }
        }

        if (!fatal && (failed || reconnect))
        {
            Sleep(3000);
            // BUG: 0x19060 the loop does not end if _count > _maxLogCount and _head is null.
            while (_maxLogCount < list._count)
            {
                if (list._head != nullptr)
                {
                    AlertBuffer* head = list._head;
                    if (head == list._tail)
                    {
                        list._head = nullptr;
                        list._tail = nullptr;
                        list._count = 0;
                    }
                    else
                    {
                        list._head = head->_next;
                        --list._count;
                    }
                    Memory::_Manager[2]->Free(head, ALERT_SENDER_FILE, 85);
                }
            }
            for (AlertBuffer* buffer = list._head; buffer != nullptr; buffer = buffer->_next)
                buffer->_sent = 0;
            if ((createSocket() && connect(_socket, &_remoteAddr, sizeof(_remoteAddr)) != SOCKET_ERROR) ||
                WSAGetLastError() == WSAEWOULDBLOCK)
                continue;
            fatal = true;
        }
        if (fatal)
            stop();
    }

    AlertBuffer* buffer = list._head;
    while (buffer != nullptr)
    {
        AlertBuffer* next = buffer->_next;
        Memory::_Manager[2]->Free(buffer, ALERT_SENDER_FILE, 95);
        buffer = next;
    }
}
