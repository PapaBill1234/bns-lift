// AlertSender.obj (CacheGate PDB). Layouts from include/pdb/CacheGate/types.h.
#pragma once
#include <winsock2.h>
#include "Thread.h"

struct AlertBuffer
{
    AlertBuffer* _next;
    int _sent;
    int _count;
    char _buffer[8];
};
static_assert(sizeof(AlertBuffer) == 0x18, "sizeof AlertBuffer");
static_assert(offsetof(AlertBuffer, _buffer) == 0x10, "AlertBuffer::_buffer");

struct AlertBufferList
{
    AlertBuffer* _head;
    AlertBuffer* _tail;
    int _count;
};
static_assert(sizeof(AlertBufferList) == 0x18, "sizeof AlertBufferList");

class AlertSender : public Thread
{
public:
    virtual wchar_t const* Name();
    static void Write(wchar_t const* file, int line, wchar_t const* format, ...);

private:
    AlertSender();
    virtual ~AlertSender();
    virtual void run();
    bool init(wchar_t* address, wchar_t const* daemonName, int worldId, int maxLogCount);
    void fini();
    bool createSocket();
    void writev2(wchar_t const* file, int line, wchar_t const* format, char* args);
    bool sendRemain(AlertBufferList& bufferList);

    static AlertSender _alertSender;

    friend class Daemon;
    friend class LobbyGate;  // ❓ LobbyGate::initNetwork and shutdown (LobbyGate 0x13220, 0x13580) call init and fini.

public:
    unsigned long long _socket;
    void* _sockEvent;
    void* _itemEvent;
    unsigned long long _threadId;
    int _maxLogCount;
    bool _init;
    sockaddr _remoteAddr;
    short _daemonNameBytes;
    wchar_t _daemonName[64];
    short _versionBytes;
    wchar_t _version[64];
    int _worldId;
    CRITICAL_SECTION _cs;
    AlertBufferList _bufferList;
};
static_assert(sizeof(AlertSender) == 0x1B0, "sizeof AlertSender");
