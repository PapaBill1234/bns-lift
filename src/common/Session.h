// Session.obj (CacheGate PDB). Layout from include/pdb/CacheGate/types.h.
#pragma once
#include <stddef.h>
#include "Lock.h"
#include "MemoryManager.h"
#include "TimerQueue.h"
#include "PacketBuffer.h"

class Connection;
class SessionSendBuffer;
class SessionRecvBuffer;
class Port;
class Channel;
class Client;
class Packet;
class PacketBuffer;
class PacketBufferHandler;
class PacketConcatenater;
class PacketCrypt;
class Security3rdParty;
class ReconnectTimer;
struct AsyncConnectContext;
struct EventContext;

class Session : public EventObject
{
public:
    enum State
    {
        CLOSED = 0x0,
        CLOSING = 0x1,
        FORCE_CLOSING = 0x2,
        CONNECTING = 0x3,
        POSTPONE_CONNECTING = 0x4,
        CONNECTED = 0x5,
    };

protected:
    Session();                                                                  // 0xDEE0
    Session(unsigned int option, PacketBufferHandler const* bufferHandler);       // 0xDF80
    virtual ~Session();                                                           // 0xE0A0
    virtual unsigned int EventId() const;                                         // 0xDED0
    virtual bool HandleEvent(EventContext* context, unsigned long numOfBytes);    // 0xF1C0
    virtual void deallocate_me(void* ptr, wchar_t const* file, int line);         // 0xFD80

    bool Connect(Port* port, unsigned long long id, unsigned long ip, unsigned short portNumber, long timeout,
                 bool nagle, bool reconnect);                                      // 0xE570
    bool Accept(Port* port, unsigned long long id, unsigned long long* socket, unsigned long ip,
                unsigned short portNumber, int option);                            // 0xE7C0
    void HandleFailedEvent(EventContext* context, unsigned long numOfBytes);      // 0xF5D0
    bool SetChannel(Channel* channel);                                            // 0xF960

public:
    void Close(bool graceful);                                                    // 0xEE30
    void StopReconnect() const;                                                   // 0xF9B0
    Channel* GetChannel() const;                                                  // 0x1D330 (SmartCouponDaemon)
    void Send(char const* format, ...) const;                                     // 0xFA10
    void Send(Packet const* packet) const;                                        // 0xFA40
    void SendV(char const* format, char* args) const;                             // 0xFAA0
    PacketConcatenater* SetPacketConcatenater(PacketConcatenater const* concatenater) const;  // 0xFC40
    // ❓ The PDB name is SetHandshakeParameter(PacketCrypt::Algorithm, char const*, int, char*, int*) const,
    // but the code uses only four arguments (rdx, r8d, r9, stack). This declaration follows the code.
    bool SetHandshakeParameter(unsigned char const* param, int paramSize, unsigned char* replyParam,
                               int* replyParamSize) const;                        // 0x19530 (LobbyGate)
    bool FailHandshake() const;                                                   // 0x19790 (LobbyGate)

private:
    bool initialize(Port* port, unsigned long long id, int option);               // 0xE2E0
    void clear();                                                                 // 0xE4B0
    bool tryReconnect(long timeout);                                              // 0xEA40
    bool reconnect();                                                             // 0xEC40
    bool close(bool graceful);                                                    // 0xEE90
    bool Recv();                                                                  // 0xF090
    bool recv();                                                                  // 0xF0D0
    bool handlePacket();                                                          // 0xF750
    bool sendNext(unsigned long sentSize);                                        // 0xFDC0
    bool send(PacketBuffer const** const pbufferList, int count) const;           // 0xFE90
    void* allocateCrypt(PacketCrypt::Type type, PacketCrypt::Algorithm algorithm) const;  // 0x19460 (LobbyGate)
    void deallocateCrypt(void* crypt) const;             // 0x194C0 (LobbyGate)
    void completeHandshake();                            // 0x197E0 (LobbyGate)

public:
    CriticalSection _lock;
    Connection* _connection;
    SessionSendBuffer* _sendBuffer;
    int _state;
    int _option;
    bool _recvPending;
    bool _sendPending;
    bool _connectPending;
    Session* _next;
    unsigned long long _id;
    unsigned int _createdPort;
    int _connectCount;
    unsigned int _minPacketSize;
    long long _lastRecvTime;
    long long _idleStatePos;
    StaticPageMemoryManager _allocator;
    Port* _port;
    Channel* _channel;
    void* _extraData;
    bool _waitForRelease;
    AsyncConnectContext* _connectContext;
    SessionRecvBuffer* _recvBuffer;
    PacketBufferHandler* _bufferHandler;
    PacketConcatenater* _concatenater;
    ReconnectTimer* _reconnectTimer;
    int _cryptMode;
    PacketCrypt* _currentCrypt;
    PacketCrypt* _handshakeCrypt;
    PacketCrypt* _sessionCrypt;
    Security3rdParty* _security3rd;

    friend class Port;
    friend class SessionPool;
    friend class Channel;
    friend class IoWorker;
    friend class Network;
    friend class ReconnectTimer;
    friend class PortListener;
    friend class ClientPacketBufferHandler;
    friend class ManagerChannel;  // ❓ access for the inlined send in ManagerChannel::SendRetryCouponPublication* (SmartCouponDaemon)
    friend class DChannel;        // ❓ access for the inlined send in DChannel (SmartCouponDaemon)
    friend class Client;          // ❓ access for the inlined send in Client::Send* (LobbyGate)
    friend class ClientManager;   // ❓ access for the inlined send in ClientManager::broadcast (LobbyGate)
    friend class LobbyD;          // ❓ access for the inlined send in LobbyD::Send* (LobbyGate)
    friend class NPChannel;        // ❓ access for the inlined send in NPChannel::SendMsg (SmartCouponDaemon)
    friend class NPSessionHandler; // ❓ access for NPSessionHandler::OnConnect/OnClose (SmartCouponDaemon)
    friend class ManagementSessionHandler; // ❓ access for the inlined send in the management handlers (PostOfficeDaemon)
    friend class WorldChannel;             // ❓ access for the inlined send in WorldChannel::SendRelayResponse (PostOfficeDaemon)
    // ❓ access for the inlined send and completeHandshake in the LobbyGate packet handlers
    friend bool HandleLobbyGate_ContentsRuleListReq(Session* session, Packet const* packet);
    friend bool HandleLobbyGate_HelloReq(Session* session, Packet* packet);
    friend bool HandleLobbyGate_BypassPacket(Client* client, Packet const* packet);
};
static_assert(sizeof(Session) == 0x128, "sizeof Session");
static_assert(offsetof(Session, _lock) == 0x18, "Session::_lock");
static_assert(offsetof(Session, _connection) == 0x40, "Session::_connection");
static_assert(offsetof(Session, _state) == 0x50, "Session::_state");
static_assert(offsetof(Session, _next) == 0x60, "Session::_next");
static_assert(offsetof(Session, _id) == 0x68, "Session::_id");
static_assert(offsetof(Session, _allocator) == 0x90, "Session::_allocator");
static_assert(offsetof(Session, _port) == 0xB8, "Session::_port");
static_assert(offsetof(Session, _waitForRelease) == 0xD0, "Session::_waitForRelease");
static_assert(offsetof(Session, _reconnectTimer) == 0xF8, "Session::_reconnectTimer");
static_assert(offsetof(Session, _security3rd) == 0x120, "Session::_security3rd");
