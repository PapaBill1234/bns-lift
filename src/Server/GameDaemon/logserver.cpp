// logserver.cpp: logserver.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "logserver.h"
#include "logarchivecontext.h"
#include "../BloodLib/include/Log.h"
#include "LiftStub.h"

// 0x6ba5a0
__cdecl LogServer::~LogServer(void)
{
    LIFT_STUB(0x6ba5a0);
}

// 0x6ba6b0
bool __cdecl LogServer::Initialize(bool, unsigned __int64)
{
    LIFT_STUB(0x6ba6b0);
}

// 0x6ba780
bool __cdecl LogServer::Connect(unsigned long, unsigned short)
{
    LIFT_STUB(0x6ba780);
}

// 0x6ba7a0
void __cdecl LogServer::Close(void)
{
    LIFT_STUB(0x6ba7a0);
}

// 0x6ba870
void __cdecl LogServer::ClearLogData(void)
{
    LIFT_STUB(0x6ba870);
}

// 0x6ba900
bool __cdecl LogServer::AsyncSend(void)
{
    LIFT_STUB(0x6ba900);
}

// 0x6bab30
bool __cdecl LogServer::SendComplete(void)
{
    LIFT_STUB(0x6bab30);
}

// 0x6bad70
bool __cdecl LogServer::RecvComplete(void)
{
    LIFT_STUB(0x6bad70);
}

// 0x6baf30
bool __cdecl LogServer::waitComplete(void)
{
    LIFT_STUB(0x6baf30);
}

#pragma comment(linker, "/INCLUDE:?AsyncRecv@LogServer@@QEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)

static wchar_t const LOG_SERVER_FILE[] = L"source\\LogServer.cpp";

// LIFT: partial view of LogServer (PDB size 0xA8): _sock +0x8 (base LogArchiveSession), _readBuffer +0x30.
struct LogServerView
{
    char base0[0x8];
    unsigned __int64 _sock;
    char base1[0x30 - 0x10];
    LogArchiveReadBuffer _readBuffer;
};
static_assert(offsetof(LogServerView, _sock) == 0x8, "LogServer::_sock");
static_assert(offsetof(LogServerView, _readBuffer) == 0x30, "LogServer::_readBuffer");

// 0x6bb020
bool __cdecl LogServer::AsyncRecv(void)
{
    LogServerView *self = reinterpret_cast<LogServerView *>(this);
    // LIFT: _wsaBuf is private in LogArchiveReadBuffer (+0x20). Read it by offset.
    WSABUF *wsaBuf = reinterpret_cast<WSABUF *>(reinterpret_cast<char *>(&self->_readBuffer) + 0x20);
    DWORD bytes = 0;
    DWORD flags = 0;
    if (WSARecv(static_cast<SOCKET>(self->_sock), wsaBuf, 1, &bytes, &flags,
                static_cast<LPOVERLAPPED>(&self->_readBuffer), nullptr) != SOCKET_ERROR)
        return true;
    DWORD error = WSAGetLastError();
    if (error == WSA_IO_PENDING)
        return true;
    // ❓ HR hides the message literal (pipe.chReply[3516]). L"WSARecv()" is assumed (same as Connection.cpp).
    Log::Write(LOG_SERVER_FILE, 315, error, L"WSARecv()");
    return false;
}

// 0x6bb0a0
bool __cdecl LogServer::HandlePacket(::Packet const *)
{
    LIFT_STUB(0x6bb0a0);
}
