// EventNotiJob.obj (SmartCouponDaemon PDB). Layouts from include/pdb/SmartCouponDaemon/types.h.
#pragma once
#include <stddef.h>
#include "CouponJob.h"
#include "ObjectPool.h"
#include "StringUtil.h"
#include "TimerQueue.h"

class EventNotiJob : public CouponJob
{
public:
    EventNotiJob();           // 0x99F0
    virtual ~EventNotiJob();  // 0x9A80
    virtual JobDef const* GetDefinition() const;                            // 0x9920
    virtual void deallocate_me(void* ptr, wchar_t const* file, int line);   // 0x9930
    virtual bool work(int task, void* param);                               // 0x9F10

    bool Initialize(id128 const* gameAccountId, int couponEventId, long long publicationId,
                    long long managementTid);  // 0x9AE0

private:
    void finalize();                // 0x9CC0
    bool init();                    // 0x9F90
    bool eventNotiReq();            // 0xA0E0
    bool eventNotiRes(void* param); // 0xA310
    bool eventNotiExpire();         // 0xA9D0

public:
    static ObjPool _pool;     // dynamic init 0x52A30
    static JobDef const _def;

    id128 _gameAccountId;
    int _couponEventId;
    long long _publicationId;
    long long _acceptTid;
    bool _fromManagementDaemon;
    long long _managementTid;
    short _managementReason;
};
static_assert(sizeof(EventNotiJob) == 0x90, "sizeof EventNotiJob");
static_assert(offsetof(EventNotiJob, _gameAccountId) == 0x50, "EventNotiJob::_gameAccountId");
static_assert(offsetof(EventNotiJob, _managementReason) == 0x88, "EventNotiJob::_managementReason");

// ❓ Header placement. The HandleEvent bodies are in GameEventWorker.obj.
class SendRetryCouponPublicationOkEvent : public DynamicEventObject
{
public:
    // ❓ Inlined in EventNotiJob::finalize (0x9CC0).
    SendRetryCouponPublicationOkEvent(long long tid, long long acceptTid) : _tid(tid), _acceptTid(acceptTid) {}
    virtual ~SendRetryCouponPublicationOkEvent();                    // 0x9980
    virtual unsigned int EventId() const;                            // 0x9970
    virtual bool HandleEvent(EventContext* ctx, unsigned long);      // 0xC6E0
    long long _tid;
    long long _acceptTid;
};
static_assert(sizeof(SendRetryCouponPublicationOkEvent) == 0x28, "sizeof SendRetryCouponPublicationOkEvent");
static_assert(offsetof(SendRetryCouponPublicationOkEvent, _tid) == 0x18, "SendRetryCouponPublicationOkEvent::_tid");

class SendRetryCouponPublicationFailEvent : public DynamicEventObject
{
public:
    // ❓ Inlined in EventNotiJob::finalize (0x9CC0).
    SendRetryCouponPublicationFailEvent(long long tid, short reason) : _tid(tid), _reason(reason) {}
    virtual ~SendRetryCouponPublicationFailEvent();                  // 0x99C0
    virtual unsigned int EventId() const;                            // 0x99B0
    virtual bool HandleEvent(EventContext* ctx, unsigned long);      // 0xC7D0
    long long _tid;
    short _reason;
};
static_assert(sizeof(SendRetryCouponPublicationFailEvent) == 0x28, "sizeof SendRetryCouponPublicationFailEvent");
static_assert(offsetof(SendRetryCouponPublicationFailEvent, _reason) == 0x20, "SendRetryCouponPublicationFailEvent::_reason");
