// Connection.obj (SmartCouponDaemon PDB). Layouts from include/pdb/CacheGate/types.h.
// The Async*Context layouts are from IDA only (❓). The PDB gives only the names and sizes.
#pragma once
#include <winsock2.h>
#include <stddef.h>

class Session;
struct SendBufferList;

// ❓ layout from IDA. Session, SessionRecvBuffer, SessionSendBuffer set _id (3, 16, 18).
struct EventContext : public _OVERLAPPED
{
    int _id;
};
static_assert(sizeof(EventContext) == 0x28, "sizeof EventContext");

// ❓ layout from IDA (Session::Connect 0x1BF20).
struct AsyncConnectContext : public EventContext
{
    Session* _session;
    unsigned long long _socket;
    sockaddr_in _remoteAddr;
    bool _firstConnect;
    long long _timeout;
    int _tryReconnectCount;
};
static_assert(sizeof(AsyncConnectContext) == 0x60, "sizeof AsyncConnectContext");
static_assert(offsetof(AsyncConnectContext, _remoteAddr) == 0x38, "AsyncConnectContext::_remoteAddr");
static_assert(offsetof(AsyncConnectContext, _timeout) == 0x50, "AsyncConnectContext::_timeout");

// ❓ layout from IDA (Session::recv 0x1CA50).
struct AsyncRecvContext : public EventContext
{
    Session* _session;
    WSABUF _wsaBuffer;
};
static_assert(sizeof(AsyncRecvContext) == 0x40, "sizeof AsyncRecvContext");

// ❓ layout from IDA (SessionSendBuffer::Add 0x2A030).
struct AsyncSendContext : public EventContext
{
    Session* _session;
    SendBufferList* _bufferList;
};
static_assert(sizeof(AsyncSendContext) == 0x38, "sizeof AsyncSendContext");

class Connection
{
public:
    Connection() : _socket(INVALID_SOCKET), _ip(0), _portNumber(0) {}  // ❓ inlined in Session::initialize (0x1BC90)
    virtual ~Connection() {}  // ❓ body inlined in the vector deleting destructor (0x2A7C0)

    bool Accept(Session* session, unsigned long long socket, unsigned long ip, unsigned short portNumber);  // 0x2A800
    bool AsyncConnect(AsyncConnectContext* context, bool nagle);                                         // 0x2A960
    bool CompleteAsyncConnect(AsyncConnectContext* context);                                             // 0x2AB50
    bool AsyncRecv(AsyncRecvContext* context, unsigned int* flags);                                      // 0x2AC10
    bool AsyncSend(AsyncSendContext* context);                                                           // 0x2AC90

protected:
    unsigned long GetLocalAddress() const;  // 0x2AEA0

private:
    unsigned long long makeConnectSocket(bool nagle);  // 0x2AD10

public:
    unsigned long long _socket;
    unsigned long _ip;
    unsigned short _portNumber;
};
static_assert(sizeof(Connection) == 0x18, "sizeof Connection");
static_assert(offsetof(Connection, _socket) == 0x8, "Connection::_socket");
static_assert(offsetof(Connection, _ip) == 0x10, "Connection::_ip");
static_assert(offsetof(Connection, _portNumber) == 0x14, "Connection::_portNumber");
