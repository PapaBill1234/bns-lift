// Connection.obj (CacheGate PDB). Layouts from include/pdb/CacheGate/types.h.
// The EventContext and Async*Context layouts match the LobbyGate PDB (types 0x11A0, 0x3130, 0x3092, 0x3171).
#pragma once
#include <winsock2.h>
#include <stddef.h>

class Session;
struct SendBufferList;

// PDB enum EventContextId. Session, SessionRecvBuffer, SessionSendBuffer set _id (3, 16, 18).
enum EventContextId : int
{
    EVID_INVALID = 0x0,
    EVID_IO_ACCEPT = 0x2,
    EVID_IO_CONNECT = 0x3,
    EVID_IO_RECV = 0x10,
    EVID_IO_SEND = 0x12,
    EVID_IO_READ = 0x20,
    EVID_IO_WRITE = 0x21,
    EVID_OTHER = 0x80,
};

struct EventContext : public _OVERLAPPED
{
    int _id;
};
static_assert(sizeof(EventContext) == 0x28, "sizeof EventContext");

// Used by Session::Connect (0xE570).
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

// Used by Session::recv (0xF0D0).
struct AsyncRecvContext : public EventContext
{
    Session* _session;
    WSABUF _wsaBuffer;
};
static_assert(sizeof(AsyncRecvContext) == 0x40, "sizeof AsyncRecvContext");

// Used by SessionSendBuffer::Add (0x1A350).
struct AsyncSendContext : public EventContext
{
    Session* _session;
    SendBufferList* _bufferList;
};
static_assert(sizeof(AsyncSendContext) == 0x38, "sizeof AsyncSendContext");

class Connection
{
public:
    Connection() : _socket(INVALID_SOCKET), _ip(0), _portNumber(0) {}  // PDB constructor, inlined in Session::Session (0xDEE0)
    virtual ~Connection();  // 0x1AAE0 (vector deleting destructor)

    bool Accept(Session* session, unsigned long long socket, unsigned long ip, unsigned short portNumber);  // 0x1AB20
    bool AsyncConnect(AsyncConnectContext* context, bool nagle);                                         // 0x1AC80
    bool CompleteAsyncConnect(AsyncConnectContext* context);                                             // 0x1AE70
    bool AsyncRecv(AsyncRecvContext* context, unsigned int* recvdSize);                                    // 0x1AF30
    bool AsyncSend(AsyncSendContext* context);                                                           // 0x1AFB0

    friend class NPChannel;  // LIFT: access helper. No PDB in the set has friend records. NPChannel2.cpp calls GetLocalAddress (PDB: protected).

protected:
    unsigned long GetLocalAddress() const;  // 0x2AEA0 (SmartCouponDaemon). Not in the CacheGate exe.

private:
    unsigned long long makeConnectSocket(bool nagle);  // 0x1B030

public:
    unsigned long long _socket;
    unsigned long _ip;
    unsigned short _portNumber;
};
static_assert(sizeof(Connection) == 0x18, "sizeof Connection");
static_assert(offsetof(Connection, _socket) == 0x8, "Connection::_socket");
static_assert(offsetof(Connection, _ip) == 0x10, "Connection::_ip");
static_assert(offsetof(Connection, _portNumber) == 0x14, "Connection::_portNumber");
