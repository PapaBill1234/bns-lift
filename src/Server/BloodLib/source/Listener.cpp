// Listener.obj (CacheGate PDB).
#include "Listener.h"
#include <winsock2.h>
#include <mswsock.h>
#include <windows.h>
#include <string.h>
#include <intrin.h>
#include "AlertSender.h"
#include "CrashHandler.h"
#include "Log.h"
#include "Network.h"
#include "Port.h"
#include "Session.h"

static wchar_t const LISTENER_FILE[] = L"source\\Listener.cpp";

// Inlined crash macro.
#define LISTENER_ASSERT_CRASH(line)                                                  \
    do                                                                               \
    {                                                                                \
        Log::Write(Log::LT_ERROR, LISTENER_FILE, line, L"== CRASH == ASSERT CRASH"); \
        AlertSender::Write(LISTENER_FILE, line, L"== CRASH == ASSERT CRASH");       \
        CrashHandler::MakeCrash("source\\Listener.cpp", line, L"");                  \
    } while (0)

// 0x31F60 vector deleting destructor
PortListener::~PortListener()
{
    Clear();
}

// 0x11E80 (folded with TrustedPacketBufferHandler::MinimalPacketSize)
unsigned int PortListener::EventId() const
{
    return 2;
}

// 0x31FD0
bool PortListener::Initialize(Port* port, void* iocpHandle, unsigned short portNo)
{
    if (_socket != INVALID_SOCKET)
        LISTENER_ASSERT_CRASH(34);

    SOCKET listenSocket = WSASocketW(AF_INET, SOCK_STREAM, IPPROTO_TCP, nullptr, 0, WSA_FLAG_OVERLAPPED);
    if (listenSocket == INVALID_SOCKET)
    {
        Log::Write(LISTENER_FILE, 41, WSAGetLastError(), L"WSASocket()");
        return false;
    }

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    memset(addr.sin_zero, 0, sizeof(addr.sin_zero));
    addr.sin_port = htons(portNo);
    if (bind(listenSocket, reinterpret_cast<sockaddr const*>(&addr), sizeof(addr)) == SOCKET_ERROR)
    {
        Log::Write(LISTENER_FILE, 52, WSAGetLastError(), L"bind()");
        closesocket(listenSocket);
        return false;
    }

    if (!port->_nagle)
    {
        int optval = 1;
        if (setsockopt(listenSocket, IPPROTO_TCP, TCP_NODELAY, reinterpret_cast<char const*>(&optval), sizeof(optval)) ==
            SOCKET_ERROR)
        {
            Log::Write(LISTENER_FILE, 62, WSAGetLastError(), L"setsockopt(), TCP_NODELAY, TRUE");
            closesocket(listenSocket);
            return false;
        }
    }

    _socket = listenSocket;
    _portInstance = port;
    addReferenceCount(LISTENER_FILE, 71);

    if (CreateIoCompletionPort(reinterpret_cast<HANDLE>(_socket), iocpHandle, reinterpret_cast<ULONG_PTR>(this), 0) ==
        nullptr)
    {
        Log::Write(LISTENER_FILE, 75, GetLastError(), L"CreateIoCompletionPort()");
    }
    else if (listen(_socket, 128) == SOCKET_ERROR)
    {
        Log::Write(LISTENER_FILE, 82, WSAGetLastError(), L"bind()");  // BUG: 0x31FD0 the text names bind(), not listen().
    }
    else
    {
        int i;
        for (i = 0; i < 128; ++i)
        {
            memset(&_context[i], 0, sizeof(_context[i]));
            _context[i]._id = EVID_IO_ACCEPT;
            _context[i]._index = i;
            _context[i]._socket = INVALID_SOCKET;
            _context[i]._localAddrSize = sizeof(sockaddr_in) + 16;
            _context[i]._remoteAddrSize = sizeof(sockaddr_in) + 16;
            if (!asyncAccept(i))
                break;
        }
        if (i >= 128)
            return true;
    }
    Clear();
    return false;
}

// 0x32270
// LIFT: noinline. The original Initialize (0x31fd0) calls this function in all 4 exes. VS2010 /LTCG inlines it without the attribute.
__declspec(noinline) void PortListener::Clear()
{
    SOCKET listenSocket = static_cast<SOCKET>(
        _InterlockedExchange64(reinterpret_cast<volatile long long*>(&_socket), static_cast<long long>(INVALID_SOCKET)));
    if (listenSocket != INVALID_SOCKET)
    {
        closesocket(listenSocket);
        _portInstance = nullptr;
        removeReferenceCount(LISTENER_FILE, 113);
    }
}

// 0x322B0
bool PortListener::HandleEvent(EventContext* context, unsigned long bytes)
{
    AcceptContext* acceptContext = static_cast<AcceptContext*>(context);
    if (acceptContext == nullptr || acceptContext->_id != EVID_IO_ACCEPT)
        LISTENER_ASSERT_CRASH(119);

    if (!accept(acceptContext))
    {
        if (acceptContext->_socket != INVALID_SOCKET)
        {
            closesocket(acceptContext->_socket);
            acceptContext->_socket = INVALID_SOCKET;
        }
    }
    acceptContext->_socket = INVALID_SOCKET;
    asyncAccept(acceptContext->_index);
    return true;
}

// 0x32360
bool PortListener::HandleFailedEvent(EventContext* context, unsigned long bytes)
{
    AcceptContext* acceptContext = static_cast<AcceptContext*>(context);
    Log::Write(LISTENER_FILE, 144, WSAGetLastError(),
               L"[listener], handle failed event received, port:%d, id:%u, socket:%I64x, internal:%I64x",
               _portInstance->_id, acceptContext->_index, acceptContext->_socket, acceptContext->Internal);
    closesocket(acceptContext->_socket);
    acceptContext->_socket = INVALID_SOCKET;
    asyncAccept(acceptContext->_index);
    return true;
}

// 0x323F0
bool PortListener::asyncAccept(int index)
{
    AcceptContext& context = _context[index];
    if (context._socket == INVALID_SOCKET)
    {
        context._socket = WSASocketW(AF_INET, SOCK_STREAM, IPPROTO_TCP, nullptr, 0, WSA_FLAG_OVERLAPPED);
        if (context._socket == INVALID_SOCKET)
        {
            Log::Write(LISTENER_FILE, 160, WSAGetLastError(), L"WSASocket()");
            return false;
        }
    }

    DWORD recvdSize = 0;
    if (Network::AcceptExFunc(_socket, context._socket, context._buffer, 0, sizeof(sockaddr_in) + 16,
                              sizeof(sockaddr_in) + 16, &recvdSize, &context))
        return true;

    int error = WSAGetLastError();
    if (error == ERROR_IO_PENDING)
        return true;

    Log::Write(LISTENER_FILE, 174, error, L"AcceptEx()");
    closesocket(context._socket);
    context._socket = INVALID_SOCKET;
    return false;
}

// 0x32510
bool PortListener::accept(AcceptContext* context)
{
    if (context == nullptr || context->_index >= 128)
        LISTENER_ASSERT_CRASH(186);

    if (!_portInstance->_enableAccept)
    {
        Log::Write(Log::LT_ERROR, LISTENER_FILE, 190, L"[listener], port is not opened, id:%d, port:%d",
                   _portInstance->_id, _portInstance->_portNumber);
        return false;
    }

    if (setsockopt(context->_socket, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT, reinterpret_cast<char const*>(&_socket),
                   sizeof(_socket)) == SOCKET_ERROR)
    {
        Log::Write(LISTENER_FILE, 197, WSAGetLastError(), L"setsockopt()");
        return false;
    }

    int bufferSize = 0;
    // BUG: 0x32510 sets the buffer size on _context[0]._socket, not on context->_socket.
    setsockopt(_context[0]._socket, SOL_SOCKET, SO_SNDBUF, reinterpret_cast<char const*>(&bufferSize), sizeof(bufferSize));
    setsockopt(_context[0]._socket, SOL_SOCKET, SO_RCVBUF, reinterpret_cast<char const*>(&bufferSize), sizeof(bufferSize));

    sockaddr_in* localAddr;
    sockaddr_in* remoteAddr;
    int localAddrSize;
    int remoteAddrSize;
    Network::AcceptSockAddrsFunc(context->_buffer, context->_recvdSize, context->_localAddrSize, context->_remoteAddrSize,
                                 reinterpret_cast<sockaddr**>(&localAddr), &localAddrSize,
                                 reinterpret_cast<sockaddr**>(&remoteAddr), &remoteAddrSize);

    Session* session = _portInstance->MakeNewSession(&context->_socket, remoteAddr->sin_addr.s_addr,
                                                     ntohs(remoteAddr->sin_port), _portInstance->_initialMode);
    if (session == nullptr)
    {
        Log::Write(Log::LT_ERROR, LISTENER_FILE, 224,
                   L"[listener], cannot make new session, port:%d, remote-address:(%s:%d)", _portInstance->_id,
                   Network::GetAddressStringW(remoteAddr->sin_addr.s_addr), static_cast<int>(ntohs(remoteAddr->sin_port)));
        return false;
    }

    session->_lock.Enter();
    bool result = session->recv();
    session->_lock.Leave();
    if (!result)
    {
        session->removeReferenceCount(LISTENER_FILE, 230);
        _portInstance->RemoveSession(session);
        return false;
    }
    session->removeReferenceCount(LISTENER_FILE, 235);
    return true;
}
