// Port.obj (CacheGate PDB). Layout from include/pdb/CacheGate/types.h.
#pragma once
#include <stddef.h>
#include "Lock.h"
#include "MemoryManager.h"
#include "RefCntObject.h"
#include "StlMemory.h"
#include <deque>

class Session;
class SessionPool;
class PortListener;
class IdleStateTable;
class SessionHandler;
class PacketBufferHandler;
class Channel;

class SessionPool : public BaseRefCntObj
{
protected:
    SessionPool(unsigned int portId);                                           // 0x184E0
    virtual ~SessionPool();                                                     // 0x18600
    bool Initialize(int maxSession, int prepareRatio, bool useUnusedSessionReadOnly);  // 0x186F0
    Session* MakeSession(PacketBufferHandler const* bufferHandler);             // 0x18820
    void RemoveSession(Session* session);                                       // 0x18A30

private:
    void addToPool(Session* session);  // 0x18AD0

public:
    static long long Allocated;
    static long long Using;

    unsigned int _portId;
    bool _valid;
    bool _useUnusedSessionReadOnly;
    Session* _head;
    Session* _tail;
    CriticalSection _lock;
    PagePoolMemoryManager _allocator;
    std::deque<Session*, StlAllocator<Session*, 2> > _sessionQueue;

    friend class Port;
    friend class Session;  // ❓ access for Session::deallocate_me (0xFD80)
};
static_assert(sizeof(SessionPool) == 0xD0, "sizeof SessionPool");
static_assert(offsetof(SessionPool, _portId) == 0x18, "SessionPool::_portId");
static_assert(offsetof(SessionPool, _lock) == 0x30, "SessionPool::_lock");
static_assert(offsetof(SessionPool, _allocator) == 0x58, "SessionPool::_allocator");
static_assert(offsetof(SessionPool, _sessionQueue) == 0xA0, "SessionPool::_sessionQueue");

class Port
{
public:
    // ❓ Inlined in Network::OpenPort (0xD2C0) and Network::Clear (0xCFD0).
    Port()
        : _iocpHandle(nullptr), _sessionList(nullptr), _pool(nullptr), _listener(nullptr), _idleStateTable(nullptr),
          _sessionHandler(nullptr), _bufferHandler(nullptr)
    {
        Clear();
    }
    ~Port() { Clear(); }

protected:
    bool Initialize(unsigned int id, unsigned short portNumber, unsigned int maxSession, int initialMode, bool enableRecv,
                    bool nagle, void* iocpHandle, SessionHandler const* sessionHandler,
                    PacketBufferHandler const* bufferHandler);                                         // 0x18B70
    void Clear();                                                                                      // 0x18DF0
    Session* MakeNewSession(unsigned long long* socket, unsigned long ip, unsigned short portNumber, int option);  // 0x18F40
    bool MakeNewSession(unsigned long ip, unsigned short portNumber, Channel* channel, long timeout, bool nagle,
                        bool reconnect, Session** session);                                            // 0x19010
    bool RemoveSession(Session* session);                                                              // 0x19120
    void ReconnectSession(unsigned long long id);                                                      // 0x192A0
    void CloseSession(unsigned long long sessionId, bool force);                                       // 0x25F20 (LobbyGate)
    long long GetSessionLastRecvTime(unsigned long long sessionId);                                    // 0x26220 (LobbyGate)

private:
    Session* makeSession(unsigned long long& id);  // 0x19420
    void clearPool();                              // 0x195A0

public:
    // ❓ Inlined in Network::OpenPort (0xD2C0). The message is from source\\Port.cpp line 330.
    bool StartAccept();

public:
    unsigned int _id;
    unsigned short _portNumber;
    void* _iocpHandle;
    bool _enableAccept;
    bool _enableRecv;
    bool _nagle;
    int _initialMode;
    unsigned int _maxSession;
    unsigned int _unusedSessionIndex;
    unsigned int _sessionCount;
    CriticalSection _sessionLock;
    Session** _sessionList;
    SessionPool* _pool;
    PortListener* _listener;
    IdleStateTable* _idleStateTable;
    SessionHandler const* _sessionHandler;
    PacketBufferHandler const* _bufferHandler;

    friend class Network;
    friend class PortListener;
    friend class Session;
    friend class Channel;
    friend class IdleStateTable;
};
static_assert(sizeof(Port) == 0x80, "sizeof Port");
static_assert(offsetof(Port, _sessionLock) == 0x28, "Port::_sessionLock");
static_assert(offsetof(Port, _sessionList) == 0x50, "Port::_sessionList");
static_assert(offsetof(Port, _bufferHandler) == 0x78, "Port::_bufferHandler");
