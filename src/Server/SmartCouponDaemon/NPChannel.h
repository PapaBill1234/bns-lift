// NPChannel.obj (..\Shared\NPChannel2.cpp), NPServiceChannel.obj and NPMessageHandler.obj (SmartCouponDaemon PDB).
#pragma once
#include "NPChannelBase.h"


class NPServiceChannel : public NPChannel
{
public:
    NPServiceChannel() {}            // LIFT: inlined in NPServiceChannelManager::Initialize (0x10340)
    virtual ~NPServiceChannel() {}   // 0xFD50 (scalar deleting destructor only)

    bool SendRequestEventNoti(CouponJob* job, id128 const* gameAccountId, int couponEventId,
                              long long publicationId);  // 0xFF10
};
static_assert(sizeof(NPServiceChannel) == 0x40, "sizeof NPServiceChannel");

typedef bool (*NPServiceMessageHandler)(NPChannel*, StsMsgLib::_StsMsg*, NPTransaction*);  // PDB S_UDT (0x4B4E)

class NPMsgHandleEvent : public DynamicEventObject
{
public:
    // LIFT: Inlined in NPServiceChannelManager::HandleMessage (0x10700).
    NPMsgHandleEvent(NPChannel* channel, StsMsgLib::_StsMsg* msg, NPTransaction* tran, NPServiceMessageHandler handler)
        : _channel(channel), _msg(msg), _tran(tran), _handler(handler)
    {
    }
    virtual ~NPMsgHandleEvent();                                   // 0x10230
    virtual unsigned int EventId() const { return 0; }             // LIFT: xor eax, eax at 0x1d7a0
    virtual bool HandleEvent(EventContext* ctx, unsigned long);    // 0x102C0

    NPChannel* _channel;
    StsMsgLib::_StsMsg* _msg;
    NPTransaction* _tran;
    NPServiceMessageHandler _handler;
};
static_assert(sizeof(NPMsgHandleEvent) == 56, "sizeof NPMsgHandleEvent");

class NPServiceChannelManager : public NPMessageHandler
{
public:
    // LIFT: Inlined in SmartCouponDaemon::initialize (0x150E0).
    NPServiceChannelManager() : _init(false), _npServChannel(nullptr) {}
    virtual bool OnConnect(NPChannel*, bool) const;                                  // 0x104A0
    virtual bool OnClose(NPChannel*, bool) const;                                    // 0x10560
    virtual bool HandleMessage(NPChannel*, StsMsgLib::_StsMsg*, void*) const;        // 0x10700

    bool Initialize(unsigned int portId, unsigned long ip, unsigned short portNo, long timeout);  // 0x10340

    bool _init;
    NPServiceChannel* _npServChannel;
};
static_assert(sizeof(NPServiceChannelManager) == 0x18, "sizeof NPServiceChannelManager");

void NPServiceChannelCmdDispatcher(unsigned int id, StsMsgLib::ECommand& eCmd);            // 0xFD80
bool NPHandlerEventNoti(NPChannel* channel, StsMsgLib::_StsMsg* msg, NPTransaction* tran);  // 0xFBC0

// Size 1 (include/pdb/SmartCouponDaemon/types.h). Static members only.
class NPMsgHelper
{
public:
    static long long LocaleHourToUTCTime(int hour, long long const UTCTime, int const timeZoneSecond);  // 0x2BE0 (LobbyDaemon)
};
