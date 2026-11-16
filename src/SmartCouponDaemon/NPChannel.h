// NPChannel.obj and NPServiceChannel.obj (SmartCouponDaemon PDB). Layouts from include/pdb/SmartCouponDaemon/types.h.
#pragma once
#include <stddef.h>
#include "SharedChannel.h"

class NPChannel;
class NPPing;
class NPTransactionRegistry;
class SessionHandler;

namespace StsMsgLib
{
struct _StsMsg;
class IStsMsg;
}

class NPMessageHandler
{
public:
    virtual bool OnConnect(NPChannel*, bool) const = 0;                               // slot 0
    virtual bool OnClose(NPChannel*, bool) const = 0;                                 // slot 1
    virtual bool HandleMessage(NPChannel*, StsMsgLib::_StsMsg*, void*) const = 0;     // slot 2
};
static_assert(sizeof(NPMessageHandler) == 0x8, "sizeof NPMessageHandler");

class NPChannel : public SharedChannel
{
public:
    virtual ~NPChannel();
    virtual bool Connect(unsigned long long, unsigned int, unsigned long, unsigned short, long, bool);

    static bool Setup(int programId, wchar_t const* gameCode);  // ❓ arguments
    static void Cleanup();                                      // ❓ address

    static SessionHandler* _sessionHandler;  // ❓ type

    StsMsgLib::IStsMsg* _sts;
    NPMessageHandler* _handler;
    NPTransactionRegistry* _tranRegistry;
    NPPing* _ping;
};

class NPServiceChannel : public NPChannel
{
public:
    virtual ~NPServiceChannel();
};
static_assert(sizeof(NPServiceChannel) == 0x40, "sizeof NPServiceChannel");

class NPServiceChannelManager : public NPMessageHandler
{
public:
    // ❓ Inlined in SmartCouponDaemon::initialize (0x150E0).
    NPServiceChannelManager() : _init(false), _npServChannel(nullptr) {}
    virtual bool OnConnect(NPChannel*, bool) const;
    virtual bool OnClose(NPChannel*, bool) const;
    virtual bool HandleMessage(NPChannel*, StsMsgLib::_StsMsg*, void*) const;

    bool Initialize(unsigned long ip, unsigned short port);  // ❓ name and arguments

    bool _init;
    NPServiceChannel* _npServChannel;
};
static_assert(sizeof(NPServiceChannelManager) == 0x18, "sizeof NPServiceChannelManager");
