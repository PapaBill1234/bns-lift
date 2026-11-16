// Listener.obj (CacheGate PDB). Layout from include/pdb/CacheGate/types.h and IDA.
#pragma once
#include <stddef.h>
#include "Connection.h"
#include "TimerQueue.h"

class Port;

class PortListener : public DynamicEventObject
{
public:
    struct AcceptContext : public EventContext
    {
        unsigned int _index;
        unsigned long long _socket;
        unsigned char _buffer[128];
        unsigned int _recvdSize;
        unsigned int _localAddrSize;
        unsigned int _remoteAddrSize;
    };

    PortListener() : _portInstance(nullptr), _socket(~0ULL) {}  // ❓ inlined in Port::Initialize
    virtual ~PortListener();                                                     // 0x31F60
    virtual unsigned int EventId() const;                                        // 0x11E80
    virtual bool HandleEvent(EventContext* context, unsigned long bytes);        // 0x322B0
    bool Initialize(Port* port, void* iocpHandle, unsigned short portNo);        // 0x31FD0
    void Clear();                                                                // 0x32270
    bool HandleFailedEvent(EventContext* context, unsigned long bytes);          // 0x32360

private:
    bool asyncAccept(int index);              // 0x323F0
    bool accept(AcceptContext* context);      // 0x32510

public:
    Port* _portInstance;
    unsigned long long _socket;
    AcceptContext _context[128];
};
static_assert(sizeof(PortListener::AcceptContext) == 200, "sizeof PortListener::AcceptContext");
static_assert(offsetof(PortListener::AcceptContext, _index) == 0x28, "AcceptContext::_index");
static_assert(offsetof(PortListener::AcceptContext, _buffer) == 0x38, "AcceptContext::_buffer");
static_assert(offsetof(PortListener::AcceptContext, _remoteAddrSize) == 0xC0, "AcceptContext::_remoteAddrSize");
static_assert(sizeof(PortListener) == 0x6428, "sizeof PortListener");
static_assert(offsetof(PortListener, _context) == 0x28, "PortListener::_context");
