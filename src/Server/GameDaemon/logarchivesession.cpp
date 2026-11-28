// logarchivesession.cpp: logarchivesession.cpp (GameDaemon PDB, 2019 + PDB).
#include "logarchivesession.h"
#include "../BloodLib/include/Network.h"
#include "../BloodLib/include/Log.h"
#include "../BloodLib/include/AlertSender.h"
#include "../BloodLib/include/Packet.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:??1LogArchiveSession@@UEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Close@LogArchiveSession@@UEAAXXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Connect@LogArchiveSession@@UEAA_NKG@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Send@LogArchiveSession@@QEAA_NPEBVPacket@@@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Recv@LogArchiveSession@@QEAA_NPEAVPacket@@@Z")  // LIFT: dead-strip keep (no live caller yet)

static wchar_t const LOG_ARCHIVE_SESSION_FILE[] = L"source\\LogArchiveSession.cpp";

// LIFT: sessionNames is a PDB static (rva 0xE761F8). The strings are not in the HR cache.
// ❓ The three names below are assumed from the SessionType enumerators.
wchar_t const *LogArchiveSession::sessionNames[LOGARCHIVE_SESSION_MAX] = {L"Invalid", L"LogAgent", L"LogServer"};

// 0x6b9d00
// LIFT: the destructor calls Close. The compiler inlines it (same line 249 in HR).
__cdecl LogArchiveSession::~LogArchiveSession(void)
{
    Close();
}

// 0x6b9d60
// ❓ HR hides every message literal (pipe.chReply[...]). The format strings below are assumed.
bool __cdecl LogArchiveSession::Connect(unsigned long ip, unsigned short port)
{
    if (_sock != INVALID_SOCKET)
        return false;
    _sock = WSASocketW(AF_INET, SOCK_STREAM, IPPROTO_TCP, nullptr, 0, WSA_FLAG_OVERLAPPED);
    if (_sock == INVALID_SOCKET)
    {
        Log::Write(LOG_ARCHIVE_SESSION_FILE, 263, WSAGetLastError(), L"WSASocket()");
        return false;
    }
    if (_timeoutSecond != 0)
    {
        u_long argp = 1;
        ioctlsocket(_sock, FIONBIO, &argp);
    }
    sockaddr_in remoteAddr;
    remoteAddr.sin_family = AF_INET;
    remoteAddr.sin_port = htons(port);
    remoteAddr.sin_addr.S_un.S_addr = ip;
    memset(remoteAddr.sin_zero, 0, sizeof(remoteAddr.sin_zero));
    Log::Write(Log::LT_DEBUG, LOG_ARCHIVE_SESSION_FILE, 43, L"[%s] connect to %s:%d", sessionNames[_sessionType],
               Network::GetAddressStringW(ip), (int)port);
    DWORD error;
    if (WSAConnect(_sock, reinterpret_cast<sockaddr const *>(&remoteAddr), sizeof(remoteAddr), nullptr, nullptr,
                   nullptr, nullptr) != SOCKET_ERROR ||
        (error = WSAGetLastError()) == WSAEWOULDBLOCK)
    {
        fd_set rset;
        rset.fd_count = 1;
        rset.fd_array[0] = _sock;
        fd_set wset;
        memcpy(&wset, &rset, sizeof(wset));
        timeval timeout;
        timeout.tv_sec = _timeoutSecond;
        timeout.tv_usec = 0;
        if (select(1, &rset, &wset, nullptr, &timeout) != 0)
            return true;
        Log::Write(LOG_ARCHIVE_SESSION_FILE, 69, WSAETIMEDOUT, L"[%s] connect timeout", sessionNames[_sessionType]);
        closesocket(_sock);
        _sock = INVALID_SOCKET;
        return false;
    }
    closesocket(_sock);
    _sock = INVALID_SOCKET;
    Log::Write(LOG_ARCHIVE_SESSION_FILE, 52, error, L"[%s] connect failed", sessionNames[_sessionType]);
    return false;
}

// 0x6b9fd0
bool __cdecl LogArchiveSession::Send(::Packet const *packet)
{
    if (_sock == INVALID_SOCKET)
        return false;
    char buffer[4000];
    int total;
    int sent = 0;
    // LIFT: the size check against the buffer is a server safety check (the original copies size - 2 bytes).
    if (packet == nullptr || packet->CurHeader == nullptr ||
        static_cast<unsigned short>(packet->CurHeader->size) > sizeof(buffer))
    {
        Log::Write(Log::LT_ERROR, LOG_ARCHIVE_SESSION_FILE, 273, L"invalid packet");
        AlertSender::Write(LOG_ARCHIVE_SESSION_FILE, 273, L"invalid packet");
        total = 0;
    }
    else
    {
        Packet::Header const *header = packet->CurHeader;
        *reinterpret_cast<Packet::Header *>(buffer) = *header;
        total = *reinterpret_cast<short *>(buffer);
        memcpy(&buffer[2], header + 1, static_cast<unsigned short>(header->size - 2));
    }
    fd_set wset;
    wset.fd_array[0] = _sock;
    timeval timeout;
    timeout.tv_sec = _timeoutSecond;
    wset.fd_count = 1;
    timeout.tv_usec = 0;
    if (select(1, nullptr, &wset, nullptr, &timeout) != 0)
    {
        if (total > 0)
        {
            do
            {
                int result = send(_sock, &buffer[sent], total - sent, 0);
                if (result == SOCKET_ERROR || result == 0)
                {
                    DWORD error = WSAGetLastError();
                    if (error != WSAEWOULDBLOCK)
                    {
                        Log::Write(LOG_ARCHIVE_SESSION_FILE, 122, error, L"[%s] send failed",
                                   sessionNames[_sessionType]);
                        Close();
                        return false;
                    }
                    if (select(1, &wset, nullptr, nullptr, &timeout) == 0)
                    {
                        Log::Write(LOG_ARCHIVE_SESSION_FILE, 115, WSAETIMEDOUT, L"[%s] send timeout",
                                   sessionNames[_sessionType]);
                        Close();
                        return false;
                    }
                }
                sent += result;
            } while (sent < total);
        }
        return true;
    }
    Log::Write(LOG_ARCHIVE_SESSION_FILE, 98, WSAETIMEDOUT, L"[%s] send failed", sessionNames[_sessionType]);
    Close();
    return false;
}

// 0x6ba1f0
bool __cdecl LogArchiveSession::Recv(::Packet *packet)
{
    if (_sock == INVALID_SOCKET)
    {
        Log::Write(Log::LT_ERROR, LOG_ARCHIVE_SESSION_FILE, 137, L"invalid socket %d", -1);
        return false;
    }
    char buffer[4000];
    memset(buffer, 0, sizeof(buffer));
    packet->Allocate();
    // LIFT: the original passes an uninitialized 3rd argument (timeout). recv ignores it.
    if (recv(buffer, 2, 0) == -1)
    {
        Log::Write(Log::LT_ERROR, LOG_ARCHIVE_SESSION_FILE, 153, L"recv header failed");
        return false;
    }
    int bodySize = *reinterpret_cast<short *>(buffer) - 2;
    // LIFT: the lower bound is a server safety check (the original only tests the upper bound).
    if (bodySize >= 0 && bodySize <= 4000)
    {
        int received = recv(buffer, bodySize, 0);
        if (received != -1)
        {
            packet->Add(buffer, static_cast<short>(received));
            return true;
        }
    }
    Log::Write(Log::LT_ERROR, LOG_ARCHIVE_SESSION_FILE, 162, L"recv body failed");
    return false;
}

// 0x6ba300
int __cdecl LogArchiveSession::recv(char *buffer, int recvSize, int)
{
    int received = 0;
    fd_set rset;
    rset.fd_array[0] = _sock;
    timeval timeout;
    timeout.tv_sec = _timeoutSecond;
    rset.fd_count = 1;
    timeout.tv_usec = 0;
    if (select(1, &rset, nullptr, nullptr, &timeout) == 0)
    {
        Log::Write(LOG_ARCHIVE_SESSION_FILE, 192, WSAETIMEDOUT, L"[%s] recv timeout", sessionNames[_sessionType]);
        Close();
        return -1;
    }
    if (recvSize <= 0)
        return received;
    DWORD error;
    int line;
    wchar_t const *format;
    while (true)
    {
        int result = ::recv(_sock, &buffer[received], recvSize - received, 0);
        if (result == SOCKET_ERROR || result == 0)
        {
            error = WSAGetLastError();
            if (error != WSAEWOULDBLOCK)
            {
                format = L"[%s] recv failed";
                line = 214;
                break;
            }
            if (select(1, &rset, nullptr, nullptr, &timeout) == 0)
            {
                format = L"[%s] recv wait timeout";
                line = 207;
                error = WSAETIMEDOUT;
                break;
            }
            // BUG: the original adds result (-1 or 0) to the offset here. Retry the read instead.
            continue;
        }
        if (result > 0x7FFF)
        {
            Log::Write(Log::LT_ERROR, LOG_ARCHIVE_SESSION_FILE, 222, L"[%s] recv size %d too large",
                       sessionNames[_sessionType], result);
            AlertSender::Write(LOG_ARCHIVE_SESSION_FILE, 222, L"[%s] recv size %d too large",
                               sessionNames[_sessionType], result);
            Close();
            return -1;
        }
        received += result;
        if (received >= recvSize)
            return received;
    }
    Log::Write(LOG_ARCHIVE_SESSION_FILE, line, error, format, sessionNames[_sessionType]);
    Close();
    return -1;
}

// 0x6ba510
void __cdecl LogArchiveSession::Close(void)
{
    if (_sock != INVALID_SOCKET)
    {
        if (closesocket(_sock) == SOCKET_ERROR)
        {
            // ❓ The text of the format string is not in the HR cache (0x6ba510). The text below is a guess.
            Log::Write(LOG_ARCHIVE_SESSION_FILE, 249, WSAGetLastError(), L"closesocket failed");
        }
        _sock = INVALID_SOCKET;
    }
}
