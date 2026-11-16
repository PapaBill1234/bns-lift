// EventNotiJob.obj (SmartCouponDaemon PDB). Layouts from include/pdb/SmartCouponDaemon/types.h.
#pragma once
#include <stddef.h>
#include "CouponJob.h"
#include "StringUtil.h"

class ObjPool;

class EventNotiJob : public CouponJob
{
public:
    EventNotiJob();  // ❓ address
    virtual ~EventNotiJob();
    virtual JobDef const* GetDefinition() const;
    virtual void deallocate_me(void* ptr, wchar_t const* file, int line);
    virtual bool work(int, void*);

    static ObjPool* _pool;  // ❓ name and type

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
