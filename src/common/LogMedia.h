// LogMedia (CacheGate PDB). Layout from include/pdb/CacheGate/types.h.
// The constructor and the destructor are inline in the original.
// Writable (0xcd80) and GetLastFileName (0xffd0) are in a later card.
#pragma once
#include <windows.h>
#include <stddef.h>
#include <string.h>
#include "Lock.h"

class LogBuffer;

class LogMedia
{
public:
    virtual ~LogMedia() {}                         // slot 0 (inline, 0x13850)
    virtual bool Writable();                       // slot 1
    virtual void Flush() = 0;                      // slot 2
    virtual wchar_t* GetLastFileName();            // slot 3
    virtual int GetType() const = 0;               // slot 4
protected:
    virtual void write(LogBuffer const* logbuf) = 0;  // slot 5

    LogMedia()  // ❓ inlined in Console::Console (0x13f50)
        : _bufferNodePos(-1), _head(nullptr), _tail(nullptr)
    {
        memset(_next, 0, sizeof(_next));
        for (int i = 0; i < 11; ++i)
            _enable[i] = true;
    }

public:
    int _bufferNodePos;
    LogMedia* _next[11];
    bool _enable[11];
    SpinLock _lock;
    LogBuffer* _head;
    LogBuffer* _tail;
};
static_assert(sizeof(LogMedia) == 0xB0, "sizeof LogMedia");
static_assert(offsetof(LogMedia, _bufferNodePos) == 0x8, "LogMedia::_bufferNodePos");
static_assert(offsetof(LogMedia, _next) == 0x10, "LogMedia::_next");
static_assert(offsetof(LogMedia, _enable) == 0x68, "LogMedia::_enable");
static_assert(offsetof(LogMedia, _lock) == 0x78, "LogMedia::_lock");
static_assert(offsetof(LogMedia, _head) == 0xA0, "LogMedia::_head");
static_assert(offsetof(LogMedia, _tail) == 0xA8, "LogMedia::_tail");
