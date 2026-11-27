// SmartCouponDB.obj (SmartCouponDaemon PDB). Layouts from include/pdb/SmartCouponDaemon/types.h.
#pragma once
#include <stddef.h>
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "StringUtil.h"
#include "Db.h"

struct EventLogInfo
{
    long long logId;
    id128 gameAccountId;
    short wid;
    long long pcdbid;
    int gameEventId;
};
static_assert(sizeof(EventLogInfo) == 0x30, "sizeof EventLogInfo");
static_assert(offsetof(EventLogInfo, wid) == 0x18, "EventLogInfo::wid");
static_assert(offsetof(EventLogInfo, pcdbid) == 0x20, "EventLogInfo::pcdbid");
static_assert(offsetof(EventLogInfo, gameEventId) == 0x28, "EventLogInfo::gameEventId");

class RetrieveEventLogContext
{
public:
    // LIFT: Inlined in the callers (AllocZero, L"SmartCouponDB.cpp", 82).
    RetrieveEventLogContext(int maxCount) : _count(0), _maxCount(maxCount)
    {
        _eventLogList = static_cast<EventLogInfo*>(
            Memory::_Manager[2]->AllocZero(sizeof(EventLogInfo) * maxCount, L"SmartCouponDB.cpp", 82));
    }
    // LIFT: Inlined in the callers (Free, L"SmartCouponDB.cpp", 88).
    ~RetrieveEventLogContext()
    {
        if (_eventLogList != nullptr)
        {
            Memory::_Manager[2]->Free(_eventLogList, L"SmartCouponDB.cpp", 88);
            _eventLogList = nullptr;
        }
    }
    bool AddEventLogInfo(EventLogInfo const* info);  // 0x10A00

    EventLogInfo* _eventLogList;
    int _count;
    int _maxCount;
};
static_assert(sizeof(RetrieveEventLogContext) == 0x10, "sizeof RetrieveEventLogContext");

struct PublicationInfo
{
    long long publicationId;
    id128 gameAccountId;
    int couponEventId;
};
static_assert(sizeof(PublicationInfo) == 0x20, "sizeof PublicationInfo");

class RetrievePublicationContext
{
public:
    // LIFT: Inlined in the callers (AllocZero, L"SmartCouponDB.cpp", 37).
    RetrievePublicationContext(int maxCount) : _count(0), _maxCount(maxCount)
    {
        _publicationList = static_cast<PublicationInfo*>(
            Memory::_Manager[2]->AllocZero(sizeof(PublicationInfo) * maxCount, L"SmartCouponDB.cpp", 37));
    }
    // LIFT: Inlined in the callers (Free, L"SmartCouponDB.cpp", 43).
    ~RetrievePublicationContext()
    {
        if (_publicationList != nullptr)
        {
            Memory::_Manager[2]->Free(_publicationList, L"SmartCouponDB.cpp", 43);
            _publicationList = nullptr;
        }
    }
    // LIFT: Inlined in SmartCouponDaemon::loadUnhandledCouponPublication (0x161A0).
    PublicationInfo* GetPublicationInfo(int index)
    {
        if (index < 0 || index >= _count)
        {
            Log::Write(Log::LT_ERROR, L"SmartCouponDB.cpp", 68, L"get-publicationinfo, invalid index, index:%d, count:%d",
                       index, _count);
            return nullptr;
        }
        return &_publicationList[index];
    }
    bool AddPublicationInfo(PublicationInfo const* info);  // 0x108E0

    PublicationInfo* _publicationList;
    int _count;
    int _maxCount;
};
static_assert(sizeof(RetrievePublicationContext) == 0x10, "sizeof RetrievePublicationContext");

// RAII holder of a DbTransaction. The ctor is inlined in the callers.
struct AutoDbTran
{
    // LIFT: Inlined ctor.
    explicit AutoDbTran(unsigned int dbId) : Tran(Db::AllocTransaction(dbId)), TimeoutSec(10) {}
    ~AutoDbTran();  // 0x10850

    DbTransaction* Tran;
    int TimeoutSec;
};

class SmartCouponDB
{
public:
    static bool const RegisterGameEventLog(int& dbRetValue, id128& gameAccountId, short worldId, long long pcdbid,
                                           int gameEventId, long long& outGameEventLogId);  // 0x10B00 (PDB signature)
    static bool UpdateStatusToProcessFailure(int* dbRetValue, long long gameEventLogId, id128* gameAccountId,
                                             short worldId, long long pcdbid, int gameEventId);  // 0x11130
    static bool ProcessCharacterGameEventLog(int* dbRetValue, long long gameEventLogId, id128* gameAccountId,
                                             short worldId, long long pcdbid, int gameEventId,
                                             RetrievePublicationContext* outPublicationContext);  // 0x117C0
    static bool ProcessAccountGameEventLog(int* dbRetValue, long long gameEventLogId, id128* gameAccountId,
                                           int gameEventId, RetrievePublicationContext* outPublicationContext);  // 0x12170
    static bool LoadSingleCouponPublication(int* dbRetValue, long long publicationId, id128* gameAccountId,
                                            int* outCouponEventId);  // 0x13DD0
    static bool LoadCouponPublicationList(int* dbRetValue, RetrievePublicationContext* context);  // 0x13A30
    static bool LoadGameEventLogList(int* dbRetValue, RetrieveEventLogContext* context);          // 0x13620
    static bool LoadRetryReadyGameEventLogList(int* dbRetValue, RetrieveEventLogContext* context);  // 0x145F0
    static bool UpdateStatusToPublicationSuccess(int* dbRetValue, long long publicationId, id128 const* gameAccountId,
                                                 int couponEventId, long long const* acceptTid);  // 0x129C0
    static bool UpdateStatusToPublicationFailure(int* dbRetValue, long long publicationId, id128 const* gameAccountId,
                                                 int couponEventId);  // 0x13060
};
