// PingGenerator.obj (PostOfficeDaemon PDB). Layouts from include/pdb/PostOfficeDaemon/types.h.
#pragma once
#include <stddef.h>
#include "TimerQueue.h"

class PingGenerator : public Timer
{
public:
    explicit PingGenerator(unsigned short wid) : _wid(wid), _pingSeq(0) {}  // ❓ inlined in 0x3d20

    virtual unsigned int TimerClass() const;         // 0x54a70 (CachedWatchdog.cpp)
    virtual unsigned long long TimerId() const;      // 0x5d860 (CachedWatchdog.cpp)
    virtual bool HandleEvent(EventContext* context, unsigned long bytes);  // 0x4d70
    virtual ~PingGenerator() {}  // ❓ folded with Timer dtor 0x12c60

    unsigned short const _wid;
    unsigned long long _pingSeq;

private:
    bool sendPing();  // 0x4ed0
};
static_assert(sizeof(PingGenerator) == 0x48, "sizeof PingGenerator");
static_assert(offsetof(PingGenerator, _wid) == 0x38, "PingGenerator::_wid");
static_assert(offsetof(PingGenerator, _pingSeq) == 0x40, "PingGenerator::_pingSeq");
