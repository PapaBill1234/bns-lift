// PipeConsole.obj (CacheGate PDB). Layouts from include/pdb/CacheGate/types.h and the IDA types.
#pragma once
#include "Thread.h"
#include "Lock.h"
#include <windows.h>
#include <stddef.h>

struct PipeInstance
{
    OVERLAPPED oOverlap;
    void* hPipeInst;
    unsigned long cbRead;
    unsigned long cbToWrite;
    unsigned long dwState;
    int fPendingIO;
    wchar_t chRequest[4096];
    wchar_t chReply[4096];
};
static_assert(sizeof(PipeInstance) == 0x4038, "sizeof PipeInstance");
static_assert(offsetof(PipeInstance, hPipeInst) == 0x20, "PipeInstance::hPipeInst");
static_assert(offsetof(PipeInstance, chRequest) == 0x38, "PipeInstance::chRequest");
static_assert(offsetof(PipeInstance, chReply) == 0x2038, "PipeInstance::chReply");

class PipeCommandProcess : public Thread
{
public:
    struct Command
    {
        Command* _next;
        Command* _prev;
        wchar_t** _argv;
        int _argc;
    };
    struct CommandList
    {
        Command _head;
        Command _tail;
    };

private:
    PipeCommandProcess();
    virtual ~PipeCommandProcess();
    virtual wchar_t const* Name();
    virtual void run();

    void processCommand(CommandList& list);
    bool addCommand(wchar_t** argv, int argc);
    static void clear(CommandList& list);

    SystemEvent _notifyEvent;
    CriticalSection _lock;
    CommandList _remote;
    CommandList _local;

    friend class PipeConsole;
};
static_assert(sizeof(PipeCommandProcess) == 0xE0, "sizeof PipeCommandProcess");

class PipeConsole : public Thread
{
public:
    struct ItemNode
    {
        ItemNode* _next;
        ItemNode* _prev;
        wchar_t _key[129];
        wchar_t _value[129];
    };
    struct ItemList
    {
        ItemNode _head;
        ItemNode _tail;
    };

    void SetInvalidInfo(wchar_t const* keyString, bool isInvalid);
    void SetRunningInfo(wchar_t const* keyString, wchar_t const* valueString);
    // 0x25000 (SmartCouponDaemon). The body does not use the arguments.
    void SetDetectFrozenThread(bool detect, int crashCount);

protected:
    PipeConsole();
    virtual ~PipeConsole();
    bool init();

private:
    virtual wchar_t const* Name();
    virtual void run();

    void processCommand(PipeInstance& pipe);
    void checkFrozenThread();
    void writeReply(PipeInstance& pipe, wchar_t const* format, ...);
    int writeStateInfo(wchar_t* buffer, int& len);
    void writeStateReply(PipeInstance& pipe);
    void writeStateReply2(PipeInstance& pipe);
    bool initPipe();
    static bool connectPipe(void* pipe, OVERLAPPED* overlapped);
    static void disconnectAndReconnect(PipeInstance& pipe);
    static bool addNode(ItemList& list, wchar_t const* keyString, wchar_t const* valueString);
    static void clear(ItemList& list);
    void cleanup();

public:
    // Daemon reads and writes these members directly (inlined code).
    CriticalSection _lock;
    int _state;
    ItemList _invalid;
    ItemList _running;
    bool _detectFrozenThread;
    int _crashIfExistFrozenThreadCount;

private:
    PipeCommandProcess _commandProcess;
    PipeInstance _pipe[4];
    void* _events[4];

    friend class Daemon;
    friend class CacheD;  // ❓ CacheD::Initialize (CacheGate 0x2430) calls addNode (inlined SetInvalidInfo).
    friend class CacheDChannel;  // ❓ CacheDChannel::onClose (CacheGate 0x3E40) calls addNode (inlined SetInvalidInfo).
    friend class LobbyD;  // ❓ LobbyD::Hello (LobbyGate 0x9bd0) uses _invalid and addNode (inlined SetInvalidInfo).
    friend class LobbyDSessionHandler;  // ❓ OnConnect/OnClose (LobbyGate 0x9310, 0x94c0) use _invalid and addNode.
};
static_assert(sizeof(PipeConsole) == 0x10AA8, "sizeof PipeConsole");
static_assert(offsetof(PipeConsole, _state) == 0x58, "PipeConsole::_state");
static_assert(offsetof(PipeConsole, _invalid) == 0x60, "PipeConsole::_invalid");
static_assert(offsetof(PipeConsole, _running) == 0x490, "PipeConsole::_running");
static_assert(offsetof(PipeConsole, _detectFrozenThread) == 0x8C0, "PipeConsole::_detectFrozenThread");
