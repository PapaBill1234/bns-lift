// Connection.obj (CacheGate PDB).
#include "Connection.h"
#include <winsock2.h>
#include <mswsock.h>
#include <windows.h>
#include "AlertSender.h"
#include "CrashHandler.h"
#include "Log.h"
#include "Network.h"
#include "SessionBuffer.h"

static wchar_t const CONNECTION_FILE[] = L"source\\Connection.cpp";

// Inlined crash macro.
#define CONNECTION_ASSERT_CRASH(line)                                                  \
    do                                                                                 \
    {                                                                                  \
        Log::Write(Log::LT_ERROR, CONNECTION_FILE, line, L"== CRASH == ASSERT CRASH"); \
        AlertSender::Write(CONNECTION_FILE, line, L"== CRASH == ASSERT CRASH");       \
        CrashHandler::MakeCrash("source\\Connection.cpp", line, L"");                  \
    } while (0)

// 0x1AAE0 vector deleting destructor
Connection::~Connection()
{
    if (_socket != INVALID_SOCKET)
    {
        closesocket(_socket);
        _socket = INVALID_SOCKET;
    }
}

// 0x1AB20
bool Connection::Accept(Session* session, unsigned long long socket, unsigned long ip, unsigned short portNumber)
{
    if (_socket != INVALID_SOCKET)
        CONNECTION_ASSERT_CRASH(46);

    if (socket != INVALID_SOCKET && ip != 0 && portNumber != 0)
    {
        HANDLE iocpHandle = Network::Instance != nullptr ? Network::Instance->_iocpHandle : nullptr;
        if (CreateIoCompletionPort(reinterpret_cast<HANDLE>(socket), iocpHandle, reinterpret_cast<ULONG_PTR>(session), 0) != nullptr)
        {
            _socket = socket;
            _ip = ip;
            _portNumber = portNumber;
            return true;
        }
        Log::Write(CONNECTION_FILE, 57, GetLastError(), L"CreateIoCompletionPort");
    }
    else
    {
        AlertSender::Write(CONNECTION_FILE, 50,
                           L"[connection], Accept failed, invalid parameter SOCKET:0x%I64x, ipaddress:%d, port:%d",
                           socket, ip, static_cast<int>(portNumber));
        Log::Write(Log::LT_ERROR, CONNECTION_FILE, 50,
                   L"[connection], Accept failed, invalid parameter SOCKET:0x%I64x, ipaddress:%d, port:%d", socket, ip,
                   static_cast<int>(portNumber));
    }
    return false;
}

// 0x1AC80
bool Connection::AsyncConnect(AsyncConnectContext* context, bool nagle)
{
    if (_socket != INVALID_SOCKET)
        CONNECTION_ASSERT_CRASH(103);

    if (context->_socket == INVALID_SOCKET)
    {
        unsigned long long connectSocket = makeConnectSocket(nagle);
        if (connectSocket == INVALID_SOCKET)
            return false;
        HANDLE iocpHandle = Network::Instance != nullptr ? Network::Instance->_iocpHandle : nullptr;
        if (CreateIoCompletionPort(reinterpret_cast<HANDLE>(connectSocket), iocpHandle,
                                   reinterpret_cast<ULONG_PTR>(context->_session), 0) == nullptr)
        {
            Log::Write(CONNECTION_FILE, 122, GetLastError(), L"CreateIoCompletionPort");
            closesocket(connectSocket);
            return false;
        }
        context->_socket = connectSocket;
    }

    DWORD error = 0;
    if (Network::ConnectExFunc(context->_socket, reinterpret_cast<sockaddr const*>(&context->_remoteAddr), 16, nullptr, 0,
                               nullptr, context) ||
        (error = WSAGetLastError()) == WSA_IO_PENDING)
    {
        int cnt = 16;
        sockaddr_in localAddr = {};
        if (getsockname(context->_socket, reinterpret_cast<sockaddr*>(&localAddr), &cnt) != SOCKET_ERROR)
        {
            Log::Write(Log::LT_DEBUG, CONNECTION_FILE, 151, L"[session], test, reconnect, this:%p, addr:(%s:%d)", this,
                       Network::GetAddressStringW(localAddr.sin_addr.s_addr), static_cast<int>(ntohs(localAddr.sin_port)));
        }
        return true;
    }

    Log::Write(CONNECTION_FILE, 138, error, L"ConnectEx()");
    closesocket(context->_socket);
    context->_socket = INVALID_SOCKET;
    return false;
}

// 0x1AE70
bool Connection::CompleteAsyncConnect(AsyncConnectContext* context)
{
    if (setsockopt(context->_socket, SOL_SOCKET, SO_UPDATE_CONNECT_CONTEXT, nullptr, 0) == SOCKET_ERROR)
    {
        Log::Write(CONNECTION_FILE, 161, WSAGetLastError(), L"setsocketopt()");
        closesocket(context->_socket);
        context->_socket = INVALID_SOCKET;
        return false;
    }
    _socket = context->_socket;
    _ip = context->_remoteAddr.sin_addr.s_addr;
    _portNumber = ntohs(context->_remoteAddr.sin_port);
    context->_timeout = 0;
    context->_firstConnect = true;
    context->_socket = INVALID_SOCKET;
    return true;
}

// 0x1AF30
bool Connection::AsyncRecv(AsyncRecvContext* context, unsigned int* recvdSize)
{
    (void)recvdSize;  // The original code does not use it.
    if (_socket == INVALID_SOCKET)
        return false;
    DWORD recvSize = 0;
    DWORD recvFlag = 0;
    if (WSARecv(_socket, &context->_wsaBuffer, 1, &recvSize, &recvFlag, context, nullptr) == SOCKET_ERROR)
    {
        DWORD error = WSAGetLastError();
        if (error != WSA_IO_PENDING)
        {
            Log::Write(CONNECTION_FILE, 190, error, L"WSARecv()");
            return false;
        }
    }
    return true;
}

// 0x1AFB0
bool Connection::AsyncSend(AsyncSendContext* context)
{
    if (_socket == INVALID_SOCKET)
        return false;
    SendBufferList* bufferList = context->_bufferList;
    DWORD sentSize = 0;
    if (WSASend(_socket, static_cast<WSABUF*>(bufferList->_wsaBuffer), bufferList->_count, &sentSize,
                0, context, nullptr) == SOCKET_ERROR)
    {
        DWORD error = WSAGetLastError();
        if (error != WSA_IO_PENDING)
        {
            Log::Write(CONNECTION_FILE, 225, error, L"WSASend()");
            return false;
        }
    }
    return true;
}

// 0x1B030
unsigned long long Connection::makeConnectSocket(bool nagle)
{
    SOCKET s = WSASocketW(AF_INET, SOCK_STREAM, IPPROTO_TCP, nullptr, 0, WSA_FLAG_OVERLAPPED);
    if (s == INVALID_SOCKET)
    {
        Log::Write(CONNECTION_FILE, 251, WSAGetLastError(), L"WSASocket()");
        return INVALID_SOCKET;
    }
    int bufferSize = 0;
    setsockopt(s, SOL_SOCKET, SO_RCVBUF, reinterpret_cast<char const*>(&bufferSize), sizeof(bufferSize));
    setsockopt(s, SOL_SOCKET, SO_SNDBUF, reinterpret_cast<char const*>(&bufferSize), sizeof(bufferSize));
    if (!nagle)
    {
        // BUG: 0x1B030 optNagle is 0, so TCP_NODELAY is set off, not on. The option has no effect.
        int optNagle = 0;
        if (setsockopt(s, IPPROTO_TCP, TCP_NODELAY, reinterpret_cast<char const*>(&optNagle), sizeof(optNagle)) ==
            SOCKET_ERROR)
        {
            Log::Write(CONNECTION_FILE, 264, WSAGetLastError(), L"setsockopt(), setup TCP_NODELAY opt failed");
            closesocket(s);
            return INVALID_SOCKET;
        }
    }
    sockaddr_in localAddr = {};
    localAddr.sin_family = AF_INET;
    if (bind(s, reinterpret_cast<sockaddr const*>(&localAddr), sizeof(localAddr)) == SOCKET_ERROR)
    {
        Log::Write(CONNECTION_FILE, 276, WSAGetLastError(), L"bind()");
        closesocket(s);
        return INVALID_SOCKET;
    }
    return s;
}
