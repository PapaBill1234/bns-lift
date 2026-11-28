// logserver.cpp: logserver.cpp (GameDaemon PDB, 2019 + PDB).
#include "logserver.h"
#include "logarchivesession.h"
#include "logarchivecontext.h"
#include "logserversessionhandler.h"
#include "../BloodLib/include/Log.h"
#include "../BloodLib/include/AlertSender.h"
#include "../BloodLib/include/Packet.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?Initialize@LogServer@@QEAA_N_N_K@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Connect@LogServer@@UEAA_NKG@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?ClearLogData@LogServer@@QEAAXXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?AsyncSend@LogServer@@QEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?SendComplete@LogServer@@QEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?RecvComplete@LogServer@@QEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?waitComplete@LogServer@@QEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?HandlePacket@LogServer@@UEAA_NPEBVPacket@@@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?AsyncRecv@LogServer@@QEAA_NXZ")  // LIFT: dead-strip keep (no live caller yet)

static wchar_t const LOG_SERVER_FILE[] = L"source\\LogServer.cpp";

// LIFT: partial view of LogServer (PDB size 0xA8). The class holds no members yet; the view reads them by offset.
struct LogServerView
{
    char base0[0x8];
    unsigned __int64 _sock;               // +0x8 (base LogArchiveSession)
    char base1[0x18 - 0x10];
    void *_sendCompletion;                // +0x18
    void *_recvCompletion;                // +0x20
    char _handler[0x30 - 0x28];           // +0x28 (LogServerSessionHandler, vtable pointer only)
    LogArchiveReadBuffer _readBuffer;     // +0x30
    LogArchiveWriteContext _writeContext; // +0x60
    bool _seqIdLogEnable;                 // +0x98
    unsigned __int64 _seqIdLogMaxCount;   // +0xA0
};
static_assert(offsetof(LogServerView, _sock) == 0x8, "LogServer::_sock");
static_assert(offsetof(LogServerView, _sendCompletion) == 0x18, "LogServer::_sendCompletion");
static_assert(offsetof(LogServerView, _recvCompletion) == 0x20, "LogServer::_recvCompletion");
static_assert(offsetof(LogServerView, _readBuffer) == 0x30, "LogServer::_readBuffer");
static_assert(offsetof(LogServerView, _writeContext) == 0x60, "LogServer::_writeContext");
static_assert(offsetof(LogServerView, _seqIdLogEnable) == 0x98, "LogServer::_seqIdLogEnable");
static_assert(offsetof(LogServerView, _seqIdLogMaxCount) == 0xA0, "LogServer::_seqIdLogMaxCount");

// The original inlines this select at each use: status != 0 gives buffer 0, else buffer 1.
static inline LogArchiveWriteBuffer *PendingBuffer(LogArchiveWriteContext *context)
{
    return context->_status != 0 ? context->_pWriteBuffers[0] : context->_pWriteBuffers[1];
}

// LIFT: the log messages of this file are not in the HR cache (pipe.chReply[...]). ❓ Each format string is assumed.

// 0x6ba5a0
__cdecl LogServer::~LogServer(void)
{
    LIFT_STUB(0x6ba5a0);
}

// 0x6ba6b0
bool __cdecl LogServer::Initialize(bool seqIdLogEnable, unsigned __int64 seqIdLogMaxCount)
{
    LogServerView *self = reinterpret_cast<LogServerView *>(this);
    self->_sendCompletion = WSACreateEvent();
    if (self->_sendCompletion == nullptr)
    {
        Log::Write(LOG_SERVER_FILE, 40, WSAGetLastError(), L"WSACreateEvent()");
        return false;
    }
    self->_recvCompletion = WSACreateEvent();
    if (self->_recvCompletion == nullptr)
    {
        Log::Write(LOG_SERVER_FILE, 46, WSAGetLastError(), L"WSACreateEvent()");
        return false;
    }
    self->_seqIdLogEnable = seqIdLogEnable;
    self->_writeContext.hEvent = self->_sendCompletion;
    self->_readBuffer.hEvent = self->_recvCompletion;
    self->_seqIdLogMaxCount = seqIdLogMaxCount;
    return true;
}

// 0x6ba780
bool __cdecl LogServer::Connect(unsigned long ip, unsigned short port)
{
    // LIFT: LogServer has no base member in the header yet; call the base body through a cast.
    return reinterpret_cast<LogArchiveSession *>(this)->LogArchiveSession::Connect(ip, port);
}

// 0x6ba7a0
void __cdecl LogServer::Close(void)
{
    LIFT_STUB(0x6ba7a0);
}

// 0x6ba870
void __cdecl LogServer::ClearLogData(void)
{
    LogServerView *self = reinterpret_cast<LogServerView *>(this);
    LogArchiveWriteContext *context = &self->_writeContext;
    if (PendingBuffer(context) != nullptr)
        PendingBuffer(context)->ClearNetworkBuffer();
    if (context->_status != 2 && context->GetWritingBuffer() != nullptr)
        context->GetWritingBuffer()->ClearNetworkBuffer();
    context->_status = 2;
    self->_readBuffer.ClearBuffer();
}

// LIFT: the sequence id log of AsyncSend and SendComplete reads three fields of a log record.
static inline unsigned __int64 RecordSeqId(char const *record) { return *reinterpret_cast<unsigned __int64 const *>(record + 7); }
static inline unsigned short RecordType(char const *record) { return *reinterpret_cast<unsigned short const *>(record + 5); }
static inline int RecordValue(char const *record) { return *reinterpret_cast<int const *>(record + 31); }

// 0x6ba900
bool __cdecl LogServer::AsyncSend(void)
{
    LogServerView *self = reinterpret_cast<LogServerView *>(this);
    LogArchiveWriteContext *context = &self->_writeContext;
    DWORD bytesSent = 0;
    if (self->_sock == INVALID_SOCKET)
        return false;
    if (context->_status == 2 && PendingBuffer(context)->_currBufferCount == 0)
        return true;
    bool pending = false;
    if (WSASend(static_cast<SOCKET>(self->_sock), PendingBuffer(context)->_pWsaBufs,
                PendingBuffer(context)->_currBufferCount, &bytesSent, 0, static_cast<LPWSAOVERLAPPED>(context),
                nullptr) == SOCKET_ERROR)
    {
        DWORD error = WSAGetLastError();
        if (error != WSA_IO_PENDING)
        {
            Log::Write(LOG_SERVER_FILE, 111, error, L"WSASend()");
            return false;
        }
        pending = true;
    }
    if (self->_seqIdLogEnable)
    {
        _WSABUF *wsaBufs = PendingBuffer(context)->_pWsaBufs;
        for (unsigned int i = 0; i < PendingBuffer(context)->_currBufferCount; ++i)
        {
            char const *record = wsaBufs[i].buf;
            unsigned __int64 seqId = RecordSeqId(record);
            unsigned short type = RecordType(record);
            int value = RecordValue(record);
            if (seqId < self->_seqIdLogMaxCount)
            {
                if (i == 0)
                    Log::Write(Log::LT_DEBUG, LOG_SERVER_FILE, 133, L"AsyncSend count=%d pending=%s",
                               PendingBuffer(context)->_currBufferCount, pending ? L"true" : L"false");
                Log::Write(Log::LT_DEBUG, LOG_SERVER_FILE, 136, L"  [%d] type=%d seq=%I64u value=%d", i, (int)type,
                           seqId, value);
            }
        }
    }
    context->SwitchStatus();
    return true;
}

// 0x6bab30
bool __cdecl LogServer::SendComplete(void)
{
    LogServerView *self = reinterpret_cast<LogServerView *>(this);
    LogArchiveWriteContext *context = &self->_writeContext;
    DWORD bytes = 0;
    DWORD flags = 0;
    if (context->_status == 2)
    {
        Log::Write(Log::LT_ERROR, LOG_SERVER_FILE, 153, L"SendComplete() called with no pending send");
        AlertSender::Write(LOG_SERVER_FILE, 153, L"SendComplete() called with no pending send");
        return false;
    }
    if (!WSAGetOverlappedResult(static_cast<SOCKET>(self->_sock), static_cast<LPWSAOVERLAPPED>(context), &bytes, FALSE,
                                &flags))
    {
        Log::Write(LOG_SERVER_FILE, 158, WSAGetLastError(), L"WSAGetOverlappedResult()");
        return false;
    }
    if (bytes == 0)
    {
        Log::Write(Log::LT_ERROR, LOG_SERVER_FILE, 162, L"SendComplete() sent 0 bytes");
        return false;
    }
    if (self->_seqIdLogEnable)
    {
        _WSABUF *wsaBufs = context->GetWritingBuffer()->_pWsaBufs;
        for (unsigned int i = 0; i < context->GetWritingBuffer()->_currBufferCount; ++i)
        {
            char const *record = wsaBufs[i].buf;
            unsigned __int64 seqId = RecordSeqId(record);
            unsigned short type = RecordType(record);
            int value = RecordValue(record);
            if (seqId < self->_seqIdLogMaxCount)
            {
                if (i == 0)
                    Log::Write(Log::LT_DEBUG, LOG_SERVER_FILE, 187, L"SendComplete count=%d",
                               context->GetWritingBuffer()->_currBufferCount);
                Log::Write(Log::LT_DEBUG, LOG_SERVER_FILE, 190, L"  [%d] type=%d seq=%I64u value=%d", i, (int)type,
                           seqId, value);
            }
        }
    }
    context->GetWritingBuffer()->ClearNetworkBuffer();
    if (PendingBuffer(context)->_currBufferCount != 0)
        return AsyncSend();
    context->_status = 2;
    return true;
}

// 0x6bad70
bool __cdecl LogServer::RecvComplete(void)
{
    LogServerView *self = reinterpret_cast<LogServerView *>(this);
    DWORD bytes = 0;
    DWORD flags = 0;
    if (self->_sock == INVALID_SOCKET)
    {
        Log::Write(Log::LT_ERROR, LOG_SERVER_FILE, 212, L"RecvComplete() invalid socket");
        return false;
    }
    if (!WSAGetOverlappedResult(static_cast<SOCKET>(self->_sock), static_cast<LPWSAOVERLAPPED>(&self->_readBuffer),
                                &bytes, FALSE, &flags))
    {
        Log::Write(Log::LT_ERROR, LOG_SERVER_FILE, 217, L"WSAGetOverlappedResult() failed");
        CancelIo(reinterpret_cast<HANDLE>(self->_sock));
        return false;
    }
    if (bytes == 0)
    {
        CancelIo(reinterpret_cast<HANDLE>(self->_sock));
        Log::Write(Log::LT_ERROR, LOG_SERVER_FILE, 224, L"RecvComplete() received 0 bytes");
        return false;
    }
    Packet packet;
    packet.Allocate();
    // LIFT: the original tests only the upper bound. bytes below 2 would make the Add size negative, so it is also rejected.
    if (bytes > 0x7FFF || bytes < 2)
    {
        Log::Write(Log::LT_ERROR, LOG_SERVER_FILE, 233, L"RecvComplete() invalid size");
        AlertSender::Write(LOG_SERVER_FILE, 233, L"RecvComplete() invalid size");
        CancelIo(reinterpret_cast<HANDLE>(self->_sock));
        return false;
    }
    packet.Add(self->_readBuffer._wsaBuf.buf + 2, static_cast<short>(bytes - 2));
    self->_readBuffer.ClearBuffer();
    if (!HandlePacket(&packet))
    {
        CancelIo(reinterpret_cast<HANDLE>(self->_sock));
        return false;
    }
    return AsyncRecv();
}

// 0x6baf30
bool __cdecl LogServer::waitComplete(void)
{
    LogServerView *self = reinterpret_cast<LogServerView *>(this);
    LogArchiveWriteContext *context = &self->_writeContext;
    DWORD bytes = 0;
    DWORD flags = 0;
    if (context->_status == 2)
        return false;
    if (!WSAGetOverlappedResult(static_cast<SOCKET>(self->_sock), static_cast<LPWSAOVERLAPPED>(context), &bytes, TRUE,
                                &flags))
    {
        Log::Write(LOG_SERVER_FILE, 289, WSAGetLastError(), L"WSAGetOverlappedResult()");
        return false;
    }
    if (bytes == 0)
    {
        Log::Write(Log::LT_ERROR, LOG_SERVER_FILE, 294, L"waitComplete() sent 0 bytes");
        return false;
    }
    context->GetWritingBuffer()->ClearNetworkBuffer();
    if (PendingBuffer(context)->_currBufferCount == 0)
        context->_status = 2;
    return true;
}

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
bool __cdecl LogServer::HandlePacket(::Packet const *packet)
{
    // LIFT: _handler (LogServerSessionHandler, 8 bytes) is at +0x28.
    LogServerSessionHandler *handler =
        reinterpret_cast<LogServerSessionHandler *>(reinterpret_cast<char *>(this) + 0x28);
    // LIFT: the command id is the byte after the 2 byte packet size.
    unsigned char command = reinterpret_cast<unsigned char const *>(packet->CurHeader)[2];
    int line;
    if (command >= 8)
    {
        // ❓ HR hides the format string (pipe.chReply[3524]). The text is assumed.
        Log::Write(Log::LT_ERROR, LOG_SERVER_FILE, 328, L"invalid packet command %d", (int)(char)command);
        line = 328;
    }
    else
    {
        switch (command)
        {
        case 0:
            return handler->HandleVersionNotifyPacket(this, packet);
        case 2:
            return handler->HandleInitAckPacket(this, packet);
        case 6:
            return handler->HandlePingAckPacket(this, packet);
        case 7:
            return handler->HandleControlRequeryNotifyPacket(this, packet);
        default:
            break;
        }
        Log::Write(Log::LT_ERROR, LOG_SERVER_FILE, 345, L"invalid packet command %d", (int)(char)command);
        line = 345;
    }
    AlertSender::Write(LOG_SERVER_FILE, line, L"invalid packet command %d", (unsigned int)(char)command);
    return false;
}
