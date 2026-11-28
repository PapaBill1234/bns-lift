// nofile.cpp: no source file in the PDB (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
// LIFT: per-exe StlMemory.h path (A6). The inlined StlAllocator::deallocate of this exe uses the GameDaemon build path.
#define LIFT_STLMEMORY_FILE \
    L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\bloodlib\\include\\StlMemory.h"
#include "GameDaemonFwd.h"
#include "datapacker.h"
#include "datareaderimpl.h"
#include "effectcontent.h"
#include "inventory.h"
#include "jsoncpp.h"
#include "lobbytokenauthtran.h"
#include "rankingseason.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:??1SlateScrollCache@Data@@QEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:??1RankingSeasonInfo@@QEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)
// 0x118e0
// PDB: compiler-generated. The body is the inlined destructor of stones.
__cdecl Data::SlateScrollCache::~SlateScrollCache(void)
{
}

// 0x157c0
// PDB: compiler-generated. The body is the inlined destructor of _pathTokenW and _pathW (StlAllocator<..., 2>).
#pragma comment(linker, "/INCLUDE:??1FileName@ZipPackedReaderIO@@QEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)
__cdecl ZipPackedReaderIO::FileName::~FileName(void)
{
}

// 0x191c0 EventObject::~EventObject: LIFT: no body in wave 0 (shared class DynamicEventObject has another form or the change needs codegen (W1, pattern 35)).

// PDB: AccountContentQuota, size 0x18. AccountRecycleTime, size 0x10. Only this file needs the complete types.
struct AccountContentQuota
{
    int _data_id;                  // +0x0
    short _version;                // +0x4
    long long _quantity;           // +0x8
    long long _last_update_time;   // +0x10
};

struct AccountRecycleTime
{
    short _groupId;                // +0x0
    long long _actualTime;         // +0x8
};

typedef std::vector<AccountContentQuota, StlAllocator<AccountContentQuota, 2> > AccountContentQuotaList;
typedef std::vector<AccountRecycleTime, StlAllocator<AccountRecycleTime, 2> > AccountRecycleTimeList;

// LIFT: partial layout of LogoutOkParam (PDB size 0x68). The class has no members in the header yet.
struct LogoutOkParamView
{
    char _head[0x28];
    AccountContentQuotaList accountContentQuotaList;  // +0x28
    AccountRecycleTimeList accountRecycleTimeList;    // +0x48
};

// LIFT: partial layout of TimeBasedPlayInfoList (PDB size 0x80). Only the fields that clear() writes.
struct TimeBasedPlayInfoView
{
    int scheduleNumber;                   // +0x0
    int duration;                         // +0x4
    long long startTimeUTC;               // +0x8
    long long expireTimeUTC;              // +0x10
    unsigned long long ackAndRewards;     // +0x18 acknowledgedPlayTime, rewardList, activated (one qword store)
};

struct TimeBasedPlayInfoListView
{
    bool _isPcCafe;                       // +0x0
    bool _useLock;                        // +0x1
    char _pad0[6];
    void* _timeLock;                      // +0x8
    long long _lastCheckTimeUTC;          // +0x10
    long long _lastResetTimeUTC[2];       // +0x18
    long long _nextResetTimeUTC[2];       // +0x28
    void* _infoLock;                      // +0x38
    TimeBasedPlayInfoView info[2];        // +0x40
};

// LIFT: partial layout of EnterWorldOkParam (PDB size 0xC58).
struct EnterWorldOkParamView
{
    char _head[0xB70];
    TimeBasedPlayInfoListView timeBasedRewardInfoList;  // +0xB70
    char _mid[0xC18 - 0xBF0];
    AccountContentQuotaList accountContentQuotaList;    // +0xC18
    AccountRecycleTimeList accountRecycleTimeList;      // +0xC38
};

// 0xc0000
// PDB: compiler-generated. The body is the inlined destructor of the 2 vectors (last member first).
#pragma comment(linker, "/INCLUDE:??1LogoutOkParam@@QEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)
__cdecl LogoutOkParam::~LogoutOkParam(void)
{
    LogoutOkParamView* self = reinterpret_cast<LogoutOkParamView*>(this);
    self->accountRecycleTimeList.~AccountRecycleTimeList();
    self->accountContentQuotaList.~AccountContentQuotaList();
}

// 0x13fd20
// PDB: compiler-generated. The 2 vectors, then the inlined TimeBasedPlayInfoList::clear (members in reverse order).
#pragma comment(linker, "/INCLUDE:??1EnterWorldOkParam@@QEAA@XZ")  // LIFT: dead-strip keep (no live caller yet)
__cdecl EnterWorldOkParam::~EnterWorldOkParam(void)
{
    EnterWorldOkParamView* self = reinterpret_cast<EnterWorldOkParamView*>(this);
    self->accountRecycleTimeList.~AccountRecycleTimeList();
    self->accountContentQuotaList.~AccountContentQuotaList();
    TimeBasedPlayInfoListView& list = self->timeBasedRewardInfoList;
    list._isPcCafe = false;
    list._useLock = false;
    list._lastCheckTimeUTC = 0;
    list._lastResetTimeUTC[0] = 0;
    list._lastResetTimeUTC[1] = 0;
    list._nextResetTimeUTC[0] = 0;
    list._nextResetTimeUTC[1] = 0;
    list.info[0].scheduleNumber = 0;
    list.info[0].duration = 0;
    list.info[0].startTimeUTC = 0;
    list.info[0].expireTimeUTC = 0;
    list.info[0].ackAndRewards = 0;
    list.info[1].scheduleNumber = 0;
    list.info[1].duration = 0;
    list.info[1].startTimeUTC = 0;
    list.info[1].expireTimeUTC = 0;
    list.info[1].ackAndRewards = 0;
}

// 0x14a320
__cdecl TakeTimeBasedPlayRewardResponseParam::~TakeTimeBasedPlayRewardResponseParam(void)
{
    LIFT_STUB(0x14a320);
}

// 0x1b4030
// PDB: compiler-generated. The body is the inlined destructor of resultScheduleList.
__cdecl RankingSeasonInfo::~RankingSeasonInfo(void)
{
}

// 0x1ee8e0
__cdecl ZoneCounterSet::~ZoneCounterSet(void)
{
    LIFT_STUB(0x1ee8e0);
}

// 0x3408d0 TextStreamPacketBufferHandler::~TextStreamPacketBufferHandler: LIFT: no body in wave 0 (shared class TextStreamPacketBufferHandler has another form or the change needs codegen (W1, pattern 35)).

// 0x340920 RawPacketBufferHandler::~RawPacketBufferHandler: LIFT: no body in wave 0 (shared class RawPacketBufferHandler has another form or the change needs codegen (W1, pattern 35)).

// 0x4bfa70
__cdecl InventoryCacheUpdate::~InventoryCacheUpdate(void)
{
    LIFT_STUB(0x4bfa70);
}

// 0x4bfee0
__cdecl InventoryClientUpdate::~InventoryClientUpdate(void)
{
    LIFT_STUB(0x4bfee0);
}

// 0x5b3750
__cdecl FallDeathEffect::FallDeathEffect(void)
{
    LIFT_STUB(0x5b3750);
}

// 0x681060
__cdecl Json::Reader::~Reader(void)
{
    LIFT_STUB(0x681060);
}

// 0x6a8430
__cdecl Json::LogicError::~LogicError(void)
{
    LIFT_STUB(0x6a8430);
}

// 0x6a84d0
__cdecl Json::Exception::Exception(::Json::Exception const &)
{
    LIFT_STUB(0x6a84d0);
}

// 0x6a85d0
__cdecl Json::LogicError::LogicError(::Json::LogicError const &)
{
    LIFT_STUB(0x6a85d0);
}

// 0x6eba80
__cdecl LoadTableBinder::~LoadTableBinder(void)
{
    LIFT_STUB(0x6eba80);
}

// 0x720df0 wmain$dtor$0: LIFT: no body in wave 0 (unwind funclet; no source function).
