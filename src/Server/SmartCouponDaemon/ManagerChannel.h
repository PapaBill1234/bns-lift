// ManagerChannel.obj and ManagerPacketHandler.obj (SmartCouponDaemon PDB).
// Layouts from include/pdb/SmartCouponDaemon/types.h.
#pragma once
#include <stddef.h>
#include "Channel.h"
#include "TimerQueue.h"
#include "StringUtil.h"

class Session;
class Packet;

class ManagerChannel : public Channel
{
public:
    // LIFT: Inlined in HandleSmartCouponManager_HelloReq (0xEF40).
    ManagerChannel(unsigned short managerWid) : _managerWid(managerWid)
    {
        _ref = 1;
        _tag = 10;
        _history = nullptr;
    }
    virtual ~ManagerChannel() {}               // 0xEED0
    virtual unsigned long long GetId();        // 0xEEC0

    void SendRetryCouponPublicationOk(Session* session, long long tid, long long acceptTid);  // 0xEB80
    void SendRetryCouponPublicationFail(Session* session, long long tid, short failReason);   // 0xED20

    unsigned short const _managerWid;
};
static_assert(sizeof(ManagerChannel) == 0x30, "sizeof ManagerChannel");
static_assert(offsetof(ManagerChannel, _managerWid) == 0x28, "ManagerChannel::_managerWid");

class ManagerSessionHandler : public SessionHandler
{
public:
    virtual bool OnAccept(Session const* session) const;                          // 0xE7A0
    virtual bool OnConnect(Session const* session, bool firstConnected) const;    // 0xE7F0
    virtual void OnClose(Session const* session, bool tryReconnect) const;        // 0xE830
    virtual bool PacketHandler(Session const* session, Packet const* packet) const;  // 0xE980
    virtual ~ManagerSessionHandler() {}
};
static_assert(sizeof(ManagerSessionHandler) == 0x8, "sizeof ManagerSessionHandler");

class RetryCouponPublicationEvent : public DynamicEventObject
{
public:
    // LIFT: Inlined in HandleSmartCouponManager_RetryCouponPublicationReq (0xF2F0).
    RetryCouponPublicationEvent() : _tid(0), _gameAccountId(ID128_GUID_ZERO), _publicationId(0), _couponEventId(0)
    {
        _ref = 1;
        _tag = 10;
        _history = nullptr;
    }
    virtual ~RetryCouponPublicationEvent() {}  // 0xEF10
    virtual unsigned int EventId() const;      // 0xEF00
    virtual bool HandleEvent(EventContext* context, unsigned long numOfBytes);  // GameEventWorker.obj

    long long _tid;
    id128 _gameAccountId;
    long long _publicationId;
    int _couponEventId;
};
static_assert(sizeof(RetryCouponPublicationEvent) == 0x40, "sizeof RetryCouponPublicationEvent");
static_assert(offsetof(RetryCouponPublicationEvent, _tid) == 0x18, "RetryCouponPublicationEvent::_tid");
static_assert(offsetof(RetryCouponPublicationEvent, _gameAccountId) == 0x20, "RetryCouponPublicationEvent::_gameAccountId");

// SmartCouponManagerPacketSmartCouponSideHandlerList.obj (data only).
extern bool (*SmartCouponManagerPacketSmartCouponSideHandlerList[10])(Session const* session, Packet const* packet);

bool HandleSmartCouponManager_HelloReq(Session const* session, Packet const* packet);                         // 0xEF40
bool HandleSmartCouponManager_RetryCouponPublicationReq(Session const* session, Packet const* packet);        // 0xF2F0
bool HandleSmartCouponManager_LoadRetryReadyGameEventLogListReq(Session const* session, Packet const* packet);  // 0xF7F0
