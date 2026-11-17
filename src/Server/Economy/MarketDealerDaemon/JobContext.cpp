// JobContext.obj (MarketDealerDaemon PDB). Source file name from log strings: "JobContext.cpp".
// Card lift-marketdealerdaemon-8: part 1 (RetrieveSaleListJob, RetrieveBidListJob, RetrieveBidRankStatusJob).
// The COMDAT copies in this module that are already lifted elsewhere:
// - AutoCS::~AutoCS 0x8770, AutoCS::Leave 0x8800: bodies below (Lock.h COMDAT, same code as PostOfficeDaemon 0x3c80/0x3c90).
// - AutoCS::Enter 0x8780: Lock.h has no declaration. ❓ Lock.h is not in the files of this card.
// - RepeatPacketDecomposer::Reset 0x8880: src/Server/BloodLib/source/PacketUtil.cpp.
#include <windows.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>
#include <new>
#include "JobContext.h"
#include "MarketDealerDefine.h"
#include "MarketDB.h"
#include "MarketDealerDaemon.h"
#include "SaleContext.h"
#include "BidContext.h"
#include "SaleTimeContext.h"
#include "DeliveryContext.h"
#include "Postman.h"
#include "FragmentPacket.h"
#include "PacketUtil.h"
#include "Packet.h"
#include "Session.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "Lock.h"
#include "Log.h"
#include "AlertSender.h"
#include "CrashHandler.h"

#define JOB_CONTEXT_FILE L"JobContext.cpp"
static wchar_t const* const MODULE_NAME = L"job context";

#define JOB_CONTEXT_CRASH(line, ...)                                    \
    do                                                                  \
    {                                                                   \
        Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, line, __VA_ARGS__); \
        AlertSender::Write(JOB_CONTEXT_FILE, line, __VA_ARGS__);        \
    } while (0)

#define INVALID_PACKET L"== CRASH == [%s], %s; invalid parameter, packet:0x%p"
#define INVALID_SESSION L"== CRASH == [%s], %s; invalid parameter, session:0x%p"
#define FAIL_DECOMPOSE L"[%s], %s; failed to decompose packet"

#define LOCK_H_WIDE L"e:\\dailybuild02\\marketdealerdaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\bloodlib\\include\\Lock.h"
#define LOCK_H_NARROW "e:\\dailybuild02\\marketdealerdaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\bloodlib\\include\\Lock.h"

// LIFT: inlined assert of BloodLib (Log, alert, crash). No PDB name.
static void assertCrash(wchar_t const* wideFile, char const* file, int line)
{
    Log::Write(Log::LT_ERROR, wideFile, line, L"== CRASH == ASSERT CRASH");
    AlertSender::Write(wideFile, line, L"== CRASH == ASSERT CRASH");
    CrashHandler::MakeCrash(file, line, L"");
}

// LIFT: inlined array new of this module (0x8890, 0x9d10, 0xab50). It allocates 8 bytes more than the
// elements, but it does not write a count and the elements start at the allocated address.
template <typename T>
static T* jobArrayNew(int count, int line)
{
    void* raw = Memory::_Manager[2]->Alloc(sizeof(T) * static_cast<long long>(count) + 8, JOB_CONTEXT_FILE, line);
    if (raw == nullptr)
        return nullptr;
    T* items = static_cast<T*>(raw);
    for (int i = count - 1, n = 0; i >= 0; --i, ++n)
        ::new (static_cast<void*>(&items[n])) T();
    return items;
}

// LIFT: inlined array delete of this module (0x8a10, 0x9e90, 0xaae0).
// ❓ The original also writes the pointer to a thread-local slot (TLS block + 0x10) before Free.
static void jobArrayDelete(void* items, int line)
{
    Memory::_Manager[2]->Free(items, JOB_CONTEXT_FILE, line);
}

// LIFT: Packet::Compose(PacketComposer*, int n, ...) is called in 0xaf90 and 0xb590.
// Packet.h has only ComposeV. This helper gives the variadic form.
static unsigned short composeWith(Packet& packet, PacketComposer* pcr, int n, ...)
{
    va_list args;
    va_start(args, n);
    unsigned short const result = packet.ComposeV(pcr, n, args);
    va_end(args);
    return result;
}

// LIFT: inlined increment of the repeat count of RepeatPacketComposer (0xb590).
// It is the same code as FragmentPacket::IncRepeatCount.
static void incRepeatCount(RepeatPacketComposer& rpc)
{
    int const index = rpc.start[rpc.top] + 1;
    if (rpc.subTop < 0)
        rpc.index = index;
    else
        rpc.sub[rpc.subTop].index = index;
    ++*rpc.counts[rpc.top];
}

// LIFT: format arguments of an id128 in the "%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X" form (inlined).
#define ID128_ARGS(id)                                                                                          \
    (id).guid.id1, static_cast<int>((id).guid.id2), static_cast<int>((id).guid.id3),                            \
        static_cast<int>((id).guid.id4[0]), static_cast<int>((id).guid.id4[1]),                                 \
        static_cast<int>((id).guid.id4[2]), static_cast<int>((id).guid.id4[3]),                                 \
        static_cast<int>((id).guid.id4[4]), static_cast<int>((id).guid.id4[5]),                                 \
        static_cast<int>((id).guid.id4[6]), static_cast<int>((id).guid.id4[7])

// LIFT: format arguments of a SaleItemInfo (the same order in all RegisterSaleJob logs).
#define SALE_ITEM_ARGS(item)                                                                                    \
    static_cast<int>((item)._itemCommonCategory), static_cast<int>((item)._itemFirstCategory),                  \
        static_cast<int>((item)._itemSecondCategory), static_cast<int>((item)._itemThirdCategory),              \
        static_cast<int>((item)._itemType), (item)._itemInstanceId, (item)._itemDataId,                          \
        static_cast<int>((item)._itemLevel), (item)._itemExp, (item)._itemAmount,                                \
        static_cast<int>((item)._itemGrade), static_cast<int>((item)._itemEquipLevel), (item)._itemXmlData

// ---- AutoCS (Lock.h COMDAT) ----

// LIFT: inlined in 0xc450 and the other handleJob functions (assert at Lock.h line 113).
// The same code as PostOfficeDaemon CachedWatchdog.cpp. The MarketDealerDaemon exe has no other copy.
AutoCS::AutoCS(CriticalSection* cs) : CS(cs), EnterCount(0)
{
    if (cs == nullptr)
        assertCrash(LOCK_H_WIDE, LOCK_H_NARROW, 113);
    EnterCriticalSection(&CS->CS);
    EnterCount = 1;
}

// 0x8770
AutoCS::~AutoCS()
{
    Leave();
}

// 0x8800
void AutoCS::Leave()
{
    if (CS == nullptr)
        assertCrash(LOCK_H_WIDE, LOCK_H_NARROW, 122);
    if (EnterCount == 1)
        LeaveCriticalSection(&CS->CS);
    --EnterCount;
}

// ---- RetrieveSaleListJob ----

// 0x8890
RetrieveSaleListJob::RetrieveSaleListJob(int searchCount)
    : _tid(0),
      _wid(0),
      _sellerPcId(0),
      _searchType(0),
      _orderType(0),
      _searchKey(0),
      _pageNo(0),
      _searchCount(searchCount),
      _mySaleList(nullptr),
      _maxListCount(searchCount),
      _currListCount(0)
{
    _mySaleList = jobArrayNew<MySaleInfo>(searchCount, 56);
}

// 0x8a10
RetrieveSaleListJob::~RetrieveSaleListJob()
{
    if (_mySaleList != nullptr)
        jobArrayDelete(_mySaleList, 62);
}

// 0x8a80
bool RetrieveSaleListJob::Initialize(Packet const*& packet)
{
    wchar_t const* const fn = L"RetrieveSaleListJob::Initialize";
    if (packet == nullptr)
    {
        JOB_CONTEXT_CRASH(68, INVALID_PACKET, MODULE_NAME, fn, packet);
        return false;
    }
    short cmd = 0;
    if (packet->Decompose("hqhqQQqc", &cmd, &_tid, &_wid, &_sellerPcId, &_searchType, &_orderType, &_searchKey,
                          &_pageNo) == 0)
    {
        Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 81, FAIL_DECOMPOSE, MODULE_NAME, fn);
        return false;
    }
    Log::Write(Log::LT_DEBUG, JOB_CONTEXT_FILE, 84,
               L"[%s], %s; decomposed packet, tid:0x%I64X, wid:%d, sellerPcId:0x%I64X, searchType:%d, orderType:%d, "
               L"searchKey:0x%I64X, pageNo:%d",
               MODULE_NAME, fn, _tid, static_cast<int>(_wid), _sellerPcId, static_cast<int>(_searchType),
               static_cast<int>(_orderType), _searchKey, static_cast<int>(_pageNo));
    return true;
}

// 0x8c60
bool RetrieveSaleListJob::ReplySuccess(Session const*& session) const
{
    wchar_t const* const fn = L"RetrieveSaleListJob::ReplySuccess";
    wchar_t const* const failFormat =
        L"[%s], %s; failed to compose my sale list packet, tid:0x%I64X, wid:%d, sellerPcId:0x%I64X, searchType:%d, "
        L"orderType:%d, searchKey:0x%I64X, pageNo:%d";
    if (session == nullptr)
    {
        JOB_CONTEXT_CRASH(92, INVALID_SESSION, MODULE_NAME, fn, session);
        return false;
    }

    FragmentPacket replyPacket(MarketDealer_RetrieveSaleListOkCmd, "hiqhqQQqcCqQqqqiQihiis;");
    replyPacket.packet.Allocate(&replyPacket.composer);
    if (replyPacket.Compose(7, _tid, static_cast<int>(_wid), _sellerPcId, static_cast<int>(_searchType),
                            static_cast<int>(_orderType), _searchKey, static_cast<int>(_pageNo)) == 0)
    {
        Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 105, failFormat, MODULE_NAME, fn, _tid, static_cast<int>(_wid),
                   _sellerPcId, static_cast<int>(_searchType), static_cast<int>(_orderType), _searchKey,
                   static_cast<int>(_pageNo));
        return false;
    }
    if (_searchType == MARKETDEALER_SEARCHTYPE_PREV_SEARCH)
    {
        if (!composeResponsePacketReversely(replyPacket))
        {
            Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 111, failFormat, MODULE_NAME, fn, _tid, static_cast<int>(_wid),
                       _sellerPcId, static_cast<int>(_searchType), static_cast<int>(_orderType), _searchKey,
                       static_cast<int>(_pageNo));
            return false;
        }
    }
    else if (!composeResponsePacket(replyPacket))
    {
        Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 117, failFormat, MODULE_NAME, fn, _tid, static_cast<int>(_wid),
                   _sellerPcId, static_cast<int>(_searchType), static_cast<int>(_orderType), _searchKey,
                   static_cast<int>(_pageNo));
        return false;
    }

    if (replyPacket.packet.Splitter != nullptr)
        replyPacket.packet.Splitter->Finalize(replyPacket.packet.CurHeader);
    session->Send(&replyPacket.packet);
    Log::Write(Log::LT_NOTICE, JOB_CONTEXT_FILE, 124,
               L"[%s], %s; sent retrieve sale list success ack, tid:0x%I64X, wid:%d, sellerPcId:0x%I64X, "
               L"searchType:%d, orderType:%d, searchKey:0x%I64X, pageNo:%d",
               MODULE_NAME, fn, _tid, static_cast<int>(_wid), _sellerPcId, static_cast<int>(_searchType),
               static_cast<int>(_orderType), _searchKey, static_cast<int>(_pageNo));
    return true;
}

// 0x9060
void RetrieveSaleListJob::ReplyFailure(Session const*& session, short const& failReason) const
{
    wchar_t const* const fn = L"RetrieveSaleListJob::ReplyFailure";
    if (session == nullptr)
    {
        JOB_CONTEXT_CRASH(132, INVALID_SESSION, MODULE_NAME, fn, session);
        return;
    }
    session->Send("hqhqQQqcE", MarketDealer_RetrieveSaleListFailCmd, _tid, static_cast<int>(_wid), _sellerPcId,
                  static_cast<int>(_searchType), static_cast<int>(_orderType), _searchKey, static_cast<int>(_pageNo),
                  static_cast<int>(failReason));
    Log::Write(Log::LT_NOTICE, JOB_CONTEXT_FILE, 137,
               L"[%s], %s; sent retrieve sale list failure ack, tid:0x%I64X, wid:%d, sellerPcId:0x%I64X, "
               L"searchType:%d, orderType:%d, searchKey:0x%I64X, pageNo:%d, failReason:%d",
               MODULE_NAME, fn, _tid, static_cast<int>(_wid), _sellerPcId, static_cast<int>(_searchType),
               static_cast<int>(_orderType), _searchKey, static_cast<int>(_pageNo), static_cast<int>(failReason));
}

// 0x91e0
bool RetrieveSaleListJob::verifyParameter(short& failReason) const
{
    wchar_t const* const fn = L"RetrieveSaleListJob::verifyParameter";
    wchar_t const* const invalidFormat =
        L"[%s], %s; invalid parameter, tid:0x%I64X, wid:%d, sellerPcId:0x%I64X, searchType:%d, orderType:%d, "
        L"searchKey:0x%I64X, pageNo:%d";
    if (_sellerPcId <= 0 || _searchType <= MARKETDEALER_SEARCHTYPE_INVALID_TYPE ||
        _searchType >= MARKETDEALER_SEARCHTYPE_MAX_TYPE || _orderType <= MARKETDEALER_ORDERTYPE_INVALID_TYPE ||
        _orderType >= MARKETDEALER_ORDERTYPE_MAX_TYPE)
    {
        Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 145, invalidFormat, MODULE_NAME, fn, _tid, static_cast<int>(_wid),
                   _sellerPcId, static_cast<int>(_searchType), static_cast<int>(_orderType), _searchKey,
                   static_cast<int>(_pageNo));
    }
    else
    {
        if (_searchType == MARKETDEALER_SEARCHTYPE_FIRST_SERACH)
            return true;
        if (_searchKey > 0)
            return true;
        Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 152, invalidFormat, MODULE_NAME, fn, _tid, static_cast<int>(_wid),
                   _sellerPcId, static_cast<int>(_searchType), static_cast<int>(_orderType), _searchKey,
                   static_cast<int>(_pageNo));
    }
    failReason = MARKETDEALER_RETRIEVESALELISTFAIL_INVALID_PARAMETER;
    return false;
}

// 0x92e0
bool RetrieveSaleListJob::handleJob(short& failReason)
{
    int dbRetValue = 0;
    if (MarketDB::RetrieveSaleList(dbRetValue, *this))
        return true;
    Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 165,
               L"[%s], %s; failed to retrieve sale list, dbRetValue:%d, tid:0x%I64X, wid:%d, sellerPcId:0x%I64X, "
               L"searchType:%d, orderType:%d, searchKey:0x%I64X, pageNo:%d",
               MODULE_NAME, L"RetrieveSaleListJob::handleJob", dbRetValue, _tid, static_cast<int>(_wid), _sellerPcId,
               static_cast<int>(_searchType), static_cast<int>(_orderType), _searchKey, static_cast<int>(_pageNo));
    failReason = MARKETDEALER_DB_ERROR;
    return false;
}

// 0x93c0
bool RetrieveSaleListJob::addMySaleInfo(MySaleInfo const& mySaleInfo)
{
    if (_maxListCount > _currListCount)
    {
        memcpy(&_mySaleList[_currListCount], &mySaleInfo, sizeof(MySaleInfo));
        ++_currListCount;
        return true;
    }
    JOB_CONTEXT_CRASH(179,
                      L"== CRASH == [%s], %s; cannot add my sale info; array list is full, tid:0x%I64X, wid:%d, "
                      L"sellerPcId:0x%I64X, searchType:%d, orderType:%d, searchKey:0x%I64X, pageNo:%d, "
                      L"maxListCount:%d, currListCount:%d, saleId:0x%I64X",
                      MODULE_NAME, L"RetrieveSaleListJob::addMySaleInfo", _tid, static_cast<int>(_wid), _sellerPcId,
                      static_cast<int>(_searchType), static_cast<int>(_orderType), _searchKey,
                      static_cast<int>(_pageNo), _maxListCount, _currListCount, mySaleInfo._saleInfo._saleId);
    return false;
}

// 0x9540
bool RetrieveSaleListJob::composeResponsePacket(FragmentPacket& packet) const
{
    wchar_t const* const fn = L"RetrieveSaleListJob::composeResponsePacket";
    __time64_t const currentTime = _time64(nullptr);
    if (currentTime == -1)
    {
        JOB_CONTEXT_CRASH(192,
                          L"== CRASH == [%s], %s; time function error, tid:0x%I64X, wid:%d, sellerPcId:0x%I64X, "
                          L"searchType:%d, orderType:%d, searchKey:0x%I64X, pageNo:%d, currentTime:%I64d",
                          MODULE_NAME, fn, _tid, static_cast<int>(_wid), _sellerPcId, static_cast<int>(_searchType),
                          static_cast<int>(_orderType), _searchKey, static_cast<int>(_pageNo), currentTime);
        return false;
    }

    packet.StartRepeat();
    for (int i = 0; i < _currListCount; ++i)
    {
        MySaleInfo const& mySaleInfo = _mySaleList[i];
        int line = 0;

        if (packet.FreeSize() <= 37)
            packet.packet.Allocate(&packet.composer);
        long long remainTime = mySaleInfo._saleInfo._saleExpirationTime - currentTime;
        if (remainTime <= 0)
            remainTime = 0;
        if (packet.Compose(6, mySaleInfo._saleInfo._saleId, static_cast<int>(mySaleInfo._saleInfo._saleType),
                           mySaleInfo._saleInfo._salePrice, mySaleInfo._saleInfo._unitPrice,
                           mySaleInfo._saleInfo._topBidPrice, remainTime) == 0)
        {
            line = 216;
        }
        else
        {
            SaleItemInfo const& item = mySaleInfo._saleItemInfo;
            if (packet.FreeSize() <= 2 * (wcslen(item._itemXmlData) + 1) + 15)
                packet.packet.Allocate(&packet.composer);
            if (packet.Compose(6, static_cast<int>(item._itemType), item._itemDataId, static_cast<int>(item._itemLevel),
                               item._itemExp, item._itemAmount, item._itemXmlData) == 0)
                line = 235;
        }
        if (line != 0)
        {
            Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, line,
                       L"[%s], %s; failed to compose my sale list packet, tid:0x%I64X, wid:%d, sellerPcId:0x%I64X, "
                       L"searchType:%d, orderType:%d, searchKey:0x%I64X, pageNo:%d, saleId:0x%I64X",
                       MODULE_NAME, fn, _tid, static_cast<int>(_wid), _sellerPcId, static_cast<int>(_searchType),
                       static_cast<int>(_orderType), _searchKey, static_cast<int>(_pageNo),
                       mySaleInfo._saleInfo._saleId);
            return false;
        }
        packet.IncRepeatCount();
    }
    packet.composer.PopRepeatCount();
    return true;
}

// 0x9930
bool RetrieveSaleListJob::composeResponsePacketReversely(FragmentPacket& packet) const
{
    wchar_t const* const fn = L"RetrieveSaleListJob::composeResponsePacketReversely";
    __time64_t const currentTime = _time64(nullptr);
    if (currentTime == -1)
    {
        JOB_CONTEXT_CRASH(250,
                          L"== CRASH == [%s], %s; time function error, tid:0x%I64X, wid:%d, sellerPcId:0x%I64X, "
                          L"searchType:%d, orderType:%d, searchKey:0x%I64X, pageNo:%d, currentTime:%I64d",
                          MODULE_NAME, fn, _tid, static_cast<int>(_wid), _sellerPcId, static_cast<int>(_searchType),
                          static_cast<int>(_orderType), _searchKey, static_cast<int>(_pageNo), currentTime);
        return false;
    }

    packet.StartRepeat();
    for (int i = _currListCount - 1; i >= 0; --i)
    {
        MySaleInfo const& mySaleInfo = _mySaleList[i];
        int line = 0;

        if (packet.FreeSize() <= 37)
            packet.packet.Allocate(&packet.composer);
        long long remainTime = mySaleInfo._saleInfo._saleExpirationTime - currentTime;
        if (remainTime <= 0)
            remainTime = 0;
        if (packet.Compose(6, mySaleInfo._saleInfo._saleId, static_cast<int>(mySaleInfo._saleInfo._saleType),
                           mySaleInfo._saleInfo._salePrice, mySaleInfo._saleInfo._unitPrice,
                           mySaleInfo._saleInfo._topBidPrice, remainTime) == 0)
        {
            line = 274;
        }
        else
        {
            SaleItemInfo const& item = mySaleInfo._saleItemInfo;
            if (packet.FreeSize() <= 2 * (wcslen(item._itemXmlData) + 1) + 15)
                packet.packet.Allocate(&packet.composer);
            if (packet.Compose(6, static_cast<int>(item._itemType), item._itemDataId, static_cast<int>(item._itemLevel),
                               item._itemExp, item._itemAmount, item._itemXmlData) == 0)
                line = 293;
        }
        if (line != 0)
        {
            Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, line,
                       L"[%s], %s; failed to compose my sale list packet, tid:0x%I64X, wid:%d, sellerPcId:0x%I64X, "
                       L"searchType:%d, orderType:%d, searchKey:0x%I64X, pageNo:%d, saleId:0x%I64X",
                       MODULE_NAME, fn, _tid, static_cast<int>(_wid), _sellerPcId, static_cast<int>(_searchType),
                       static_cast<int>(_orderType), _searchKey, static_cast<int>(_pageNo),
                       mySaleInfo._saleInfo._saleId);
            return false;
        }
        packet.IncRepeatCount();
    }
    packet.composer.PopRepeatCount();
    return true;
}

// ---- RetrieveBidListJob ----

// 0x9d10
RetrieveBidListJob::RetrieveBidListJob(int concurrentBidCount)
    : _tid(0), _wid(0), _bidderPcId(0), _myBidList(nullptr), _maxListCount(concurrentBidCount), _currListCount(0)
{
    _myBidList = jobArrayNew<MyBidInfo>(concurrentBidCount, 318);
}

// 0x9e90
RetrieveBidListJob::~RetrieveBidListJob()
{
    if (_myBidList != nullptr)
        jobArrayDelete(_myBidList, 324);
}

// 0x9f00
bool RetrieveBidListJob::Initialize(Packet const*& packet)
{
    wchar_t const* const fn = L"RetrieveBidListJob::Initialize";
    if (packet == nullptr)
    {
        JOB_CONTEXT_CRASH(330, INVALID_PACKET, MODULE_NAME, fn, packet);
        return false;
    }
    short cmd = 0;
    if (packet->Decompose("hqhq", &cmd, &_tid, &_wid, &_bidderPcId) == 0)
    {
        Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 339, FAIL_DECOMPOSE, MODULE_NAME, fn);
        return false;
    }
    Log::Write(Log::LT_DEBUG, JOB_CONTEXT_FILE, 342, L"[%s], %s; decomposed packet, tid:0x%I64X, wid:%d, bidderPcId:0x%I64X",
               MODULE_NAME, fn, _tid, static_cast<int>(_wid), _bidderPcId);
    return true;
}

// 0xa060
bool RetrieveBidListJob::ReplySuccess(Session const*& session) const
{
    wchar_t const* const fn = L"RetrieveBidListJob::ReplySuccess";
    wchar_t const* const failFormat =
        L"[%s], %s; failed to compose my bid list packet, tid:0x%I64X, wid:%d, bidderPcId:0x%I64X";
    if (session == nullptr)
    {
        JOB_CONTEXT_CRASH(350, INVALID_SESSION, MODULE_NAME, fn, session);
        return false;
    }

    FragmentPacket replyPacket(MarketDealer_RetrieveBidListOkCmd, "hiqhqCqqqhsqqiQihiis;");
    replyPacket.packet.Allocate(&replyPacket.composer);
    if (replyPacket.Compose(3, _tid, static_cast<int>(_wid), _bidderPcId) == 0)
    {
        Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 359, failFormat, MODULE_NAME, fn, _tid, static_cast<int>(_wid),
                   _bidderPcId);
        return false;
    }
    if (!composeResponsePacket(replyPacket))
    {
        Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 364, failFormat, MODULE_NAME, fn, _tid, static_cast<int>(_wid),
                   _bidderPcId);
        return false;
    }

    if (replyPacket.packet.Splitter != nullptr)
        replyPacket.packet.Splitter->Finalize(replyPacket.packet.CurHeader);
    session->Send(&replyPacket.packet);
    Log::Write(Log::LT_NOTICE, JOB_CONTEXT_FILE, 370,
               L"[%s], %s; sent retrieve bid list success ack, tid:0x%I64X, wid:%d, bidderPcId:0x%I64X", MODULE_NAME,
               fn, _tid, static_cast<int>(_wid), _bidderPcId);
    return true;
}

// 0xa340
void RetrieveBidListJob::ReplyFailure(Session const*& session, short const& failReason) const
{
    wchar_t const* const fn = L"RetrieveBidListJob::ReplyFailure";
    if (session == nullptr)
    {
        JOB_CONTEXT_CRASH(378, INVALID_SESSION, MODULE_NAME, fn, session);
        return;
    }
    session->Send("hqhqE", MarketDealer_RetrieveBidListFailCmd, _tid, static_cast<int>(_wid), _bidderPcId,
                  static_cast<int>(failReason));
    Log::Write(Log::LT_NOTICE, JOB_CONTEXT_FILE, 383,
               L"[%s], %s; sent retrieve bid list failure ack, tid:0x%I64X, wid:%d, bidderPcId:0x%I64X, failReason:%d",
               MODULE_NAME, fn, _tid, static_cast<int>(_wid), _bidderPcId, static_cast<int>(failReason));
}

// 0xa470
bool RetrieveBidListJob::verifyParameter(short& failReason) const
{
    if (_bidderPcId > 0)
        return true;
    Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 389,
               L"[%s], %s; invalid parameter, tid:0x%I64X, wid:%d, bidderPcId:0x%I64X", MODULE_NAME,
               L"RetrieveBidListJob::verifyParameter", _tid, static_cast<int>(_wid), _bidderPcId);
    failReason = MARKETDEALER_RETRIEVEBIDLISTFAIL_INVALID_PARAMETER;
    return false;
}

// 0xa4f0
bool RetrieveBidListJob::handleJob(short& failReason)
{
    int dbRetValue = 0;
    if (MarketDB::RetrieveBidList(dbRetValue, *this))
        return true;
    Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 401,
               L"[%s], %s; failed to retrieve bid list, dbRetValue:%d, tid:0x%I64X, wid:%d, bidderPcId:0x%I64X",
               MODULE_NAME, L"RetrieveBidListJob::handleJob", dbRetValue, _tid, static_cast<int>(_wid), _bidderPcId);
    failReason = MARKETDEALER_DB_ERROR;
    return false;
}

// 0xa5a0
bool RetrieveBidListJob::addMyBidInfo(MyBidInfo const& myBidInfo)
{
    if (_maxListCount > _currListCount)
    {
        memcpy(&_myBidList[_currListCount], &myBidInfo, sizeof(MyBidInfo));
        ++_currListCount;
        return true;
    }
    JOB_CONTEXT_CRASH(415,
                      L"== CRASH == [%s], %s; cannot add my bid info; array list is full, tid:0x%I64X, wid:%d, "
                      L"bidderPcId:0x%I64X, maxListCount:%d, currListCount:%d, saleId:0x%I64X, bidId:0x%I64X",
                      MODULE_NAME, L"RetrieveBidListJob::addMyBidInfo", _tid, static_cast<int>(_wid), _bidderPcId,
                      _maxListCount, _currListCount, myBidInfo._saleInfo._saleId, myBidInfo._bidId);
    return false;
}

// 0xa6e0
bool RetrieveBidListJob::composeResponsePacket(FragmentPacket& packet) const
{
    wchar_t const* const fn = L"RetrieveBidListJob::composeResponsePacket";
    __time64_t const currentTime = _time64(nullptr);
    if (currentTime == -1)
    {
        JOB_CONTEXT_CRASH(428,
                          L"== CRASH == [%s], %s; time function error, tid:0x%I64X, wid:%d, bidderPcId:0x%I64X, "
                          L"currentTime:%I64d",
                          MODULE_NAME, fn, _tid, static_cast<int>(_wid), _bidderPcId, currentTime);
        return false;
    }

    packet.StartRepeat();
    for (int i = 0; i < _currListCount; ++i)
    {
        MyBidInfo const& myBidInfo = _myBidList[i];
        SaleInfo const& saleInfo = myBidInfo._saleInfo;
        int line = 0;

        if (packet.FreeSize() <= 2 * (wcslen(saleInfo._seller._participantName) + 1) + 46)
            packet.packet.Allocate(&packet.composer);
        long long remainTime = saleInfo._saleExpirationTime - currentTime;
        if (remainTime <= 0)
            remainTime = 0;
        if (packet.Compose(8, myBidInfo._bidId, saleInfo._saleId, myBidInfo._bidPrice,
                           static_cast<int>(saleInfo._seller._participantWid), saleInfo._seller._participantName,
                           saleInfo._bidUnitPrice, saleInfo._topBidPrice, remainTime) == 0)
        {
            line = 456;
        }
        else
        {
            SaleItemInfo const& item = myBidInfo._saleItemInfo;
            if (packet.FreeSize() <= 2 * (wcslen(item._itemXmlData) + 1) + 15)
                packet.packet.Allocate(&packet.composer);
            if (packet.Compose(6, static_cast<int>(item._itemType), item._itemDataId, static_cast<int>(item._itemLevel),
                               item._itemExp, item._itemAmount, item._itemXmlData) == 0)
                line = 476;
        }
        if (line != 0)
        {
            Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, line,
                       L"[%s], %s; failed to compose my bid list packet, tid:0x%I64X, wid:%d, bidderPcId:0x%I64X, "
                       L"saleId:0x%I64X, bidId:0x%I64X",
                       MODULE_NAME, fn, _tid, static_cast<int>(_wid), _bidderPcId, saleInfo._saleId, myBidInfo._bidId);
            return false;
        }
        packet.IncRepeatCount();
    }
    packet.composer.PopRepeatCount();
    return true;
}

// ---- RetrieveBidRankStatusJob ----

// 0xaae0
RetrieveBidRankStatusJob::~RetrieveBidRankStatusJob()
{
    if (_myBidRankStatusList != nullptr)
        jobArrayDelete(_myBidRankStatusList, 505);
}

// 0xab50
bool RetrieveBidRankStatusJob::Initialize(Packet const*& packet)
{
    wchar_t const* const fn = L"RetrieveBidRankStatusJob::Initialize";
    if (packet == nullptr)
    {
        JOB_CONTEXT_CRASH(511, INVALID_PACKET, MODULE_NAME, fn, packet);
        return false;
    }

    // LIFT: inlined RepeatPacketDecomposer setup (format "hqhqCq;", the command is skipped).
    RepeatPacketDecomposer rpd;
    rpd.format = "hqhqCq;";
    rpd.len = 7;
    rpd.index = 1;
    rpd.offset = 2;
    rpd.top = -1;
    if (packet->Decompose(&rpd, 3, &_tid, &_wid, &_bidderPcId) == 0)
    {
        Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 520, FAIL_DECOMPOSE, MODULE_NAME, fn);
        return false;
    }
    Log::Write(Log::LT_DEBUG, JOB_CONTEXT_FILE, 523, L"[%s], %s; decomposed packet, tid:0x%I64X, wid:%d, bidderPcId:0x%I64X",
               MODULE_NAME, fn, _tid, static_cast<int>(_wid), _bidderPcId);

    int const concurrentBidCount = MarketDealerDaemon::_instance->_config->_concurrentBidCount;
    // LIFT: inlined repeat count read of PacketUtil.cpp (assert at line 241).
    Packet const* const p = packet;
    if (p == nullptr)
        assertCrash(L"source\\PacketUtil.cpp", "source\\PacketUtil.cpp", 241);
    short const saleIdCount = static_cast<short>(
        rpd.PushRepeatCount(reinterpret_cast<char const*>(p->CurHeader + 1) + rpd.offset,
                            static_cast<unsigned short>(p->CurHeader->size - 2) - rpd.offset));
    if (saleIdCount <= 0 || saleIdCount > concurrentBidCount)
    {
        Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 529,
                   L"[%s], %s; invalid repeat count, tid:0x%I64X, wid:%d, bidderPcId:0x%I64X, saleIdCount:%d, "
                   L"concurrentBidCount:%d",
                   MODULE_NAME, fn, _tid, static_cast<int>(_wid), _bidderPcId, static_cast<int>(saleIdCount),
                   concurrentBidCount);
        return false;
    }

    _myBidRankStatusList = jobArrayNew<MyBidRankStatusInfo>(saleIdCount, 533);
    // BUG: 0xab50 no null check after the array new; the Decompose below writes to a null list.
    _currListCount = saleIdCount;
    for (int i = 0; i < saleIdCount; ++i)
    {
        if (packet->Decompose(&rpd, 1, &_myBidRankStatusList[i]._saleId) == 0)
        {
            Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 539,
                       L"[%s], %s; failed to decompose packet, tid:0x%I64X, wid:%d, bidderPcId:0x%I64X", MODULE_NAME,
                       fn, _tid, static_cast<int>(_wid), _bidderPcId);
            return false;
        }
        // LIFT: inlined decrement of the repeat count of RepeatPacketDecomposer.
        rpd.index = rpd.start[rpd.top] + 1;
        --rpd.counts[rpd.top];
    }

    // LIFT: inlined end of repeat of PacketUtil.cpp (assert at line 248: the repeat format must start with 'C').
    if (rpd.top < 0 || rpd.format[rpd.start[rpd.top]] != 'C')
        assertCrash(L"source\\PacketUtil.cpp", "source\\PacketUtil.cpp", 248);
    rpd.skipRepeatFormat();
    return true;
}

// 0xaf90
bool RetrieveBidRankStatusJob::ReplySuccess(Session const*& session) const
{
    wchar_t const* const fn = L"RetrieveBidRankStatusJob::ReplySuccess";
    wchar_t const* const failFormat =
        L"[%s], %s; failed to compose my bid rank status list packet, tid:0x%I64X, wid:%d, bidderPcId:0x%I64X";
    if (session == nullptr)
    {
        JOB_CONTEXT_CRASH(553, INVALID_SESSION, MODULE_NAME, fn, session);
        return false;
    }

    // LIFT: Packet has no constructor. The original sets all fields to zero (inlined).
    Packet replyPacket;
    replyPacket.Splitter = nullptr;
    replyPacket.IsFragmentPacket = false;
    replyPacket.FragmentPacketCmd = 0;
    replyPacket.CurHeader = nullptr;
    replyPacket.ListHead = nullptr;
    replyPacket.ListTail = nullptr;
    // LIFT: inlined RepeatPacketComposer setup.
    RepeatPacketComposer rpc;
    rpc.format = "hqhqCqQ;";
    rpc.len = 8;
    rpc.index = 0;
    rpc.top = -1;
    rpc.subTop = -1;
    replyPacket.Allocate();
    if (composeWith(replyPacket, &rpc, 4, MarketDealer_RetrieveBidRankStatusOkCmd, _tid, static_cast<int>(_wid),
                    _bidderPcId) == 0)
    {
        Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 565, failFormat, MODULE_NAME, fn, _tid, static_cast<int>(_wid),
                   _bidderPcId);
        return false;
    }
    if (!composeResponsePacket(rpc, replyPacket))
    {
        Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 570, failFormat, MODULE_NAME, fn, _tid, static_cast<int>(_wid),
                   _bidderPcId);
        return false;
    }
    session->Send(&replyPacket);
    Log::Write(Log::LT_NOTICE, JOB_CONTEXT_FILE, 575,
               L"[%s], %s; sent retrieve bid rank status success ack, tid:0x%I64X, wid:%d, bidderPcId:0x%I64X",
               MODULE_NAME, fn, _tid, static_cast<int>(_wid), _bidderPcId);
    return true;
}

// 0xb2c0
void RetrieveBidRankStatusJob::ReplyFailure(Session const*& session, short const& failReason) const
{
    wchar_t const* const fn = L"RetrieveBidRankStatusJob::ReplyFailure";
    if (session == nullptr)
    {
        JOB_CONTEXT_CRASH(583, INVALID_SESSION, MODULE_NAME, fn, session);
        return;
    }
    session->Send("hqhqE", MarketDealer_RetrieveBidRankStatusFailCmd, _tid, static_cast<int>(_wid), _bidderPcId,
                  static_cast<int>(failReason));
    Log::Write(Log::LT_NOTICE, JOB_CONTEXT_FILE, 588,
               L"[%s], %s; sent retrieve bid rank status failure ack, tid:0x%I64X, wid:%d, bidderPcId:0x%I64X, "
               L"failReason:%d",
               MODULE_NAME, fn, _tid, static_cast<int>(_wid), _bidderPcId, static_cast<int>(failReason));
}

// 0xb3f0
bool RetrieveBidRankStatusJob::verifyParameter(short& failReason) const
{
    wchar_t const* const fn = L"RetrieveBidRankStatusJob::verifyParameter";
    if (_bidderPcId <= 0)
    {
        Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 594,
                   L"[%s], %s; invalid parameter, tid:0x%I64X, wid:%d, bidderPcId:0x%I64X", MODULE_NAME, fn, _tid,
                   static_cast<int>(_wid), _bidderPcId);
        failReason = MARKETDEALER_RETRIEVEBIDRANKSTATUSFAIL_INVALID_PARAMETER;
        return false;
    }
    for (int i = 0; i < _currListCount; ++i)
    {
        if (_myBidRankStatusList[i]._saleId <= 0)
        {
            Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 602,
                       L"[%s], %s; invalid parameter, tid:0x%I64X, wid:%d, bidderPcId:0x%I64X, saleId:0x%I64X",
                       MODULE_NAME, fn, _tid, static_cast<int>(_wid), _bidderPcId, _myBidRankStatusList[i]._saleId);
            failReason = MARKETDEALER_RETRIEVEBIDRANKSTATUSFAIL_INVALID_PARAMETER;
            return false;
        }
    }
    return true;
}

// 0xb4f0
bool RetrieveBidRankStatusJob::handleJob(short& /*failReason*/)
{
    for (int i = 0; i < _currListCount; ++i)
    {
        MyBidRankStatusInfo& info = _myBidRankStatusList[i];
        SaleContext* const saleContext = MarketDealerDaemon::_instance->_saleContextManager->GetContext(info._saleId);
        if (saleContext != nullptr)
        {
            info._bidRankStatus = (_bidderPcId == saleContext->_saleInfo._topBidder._participantPcId)
                                      ? MARKETDEALER_BIDRANKSTATUS_TOP_BIDDER
                                      : MARKETDEALER_BIDRANKSTATUS_NO_TOP_BIDDER;
            saleContext->removeReferenceCount(JOB_CONTEXT_FILE, 620);
        }
        else
        {
            info._bidRankStatus = MARKETDEALER_BIDRANKSTATUS_NO_SUCH_SALE;
        }
    }
    return true;
}

// 0xb590
bool RetrieveBidRankStatusJob::composeResponsePacket(RepeatPacketComposer& rpc, Packet& packet) const
{
    rpc.PushRepeatCount(&packet);
    for (int i = 0; i < _currListCount; ++i)
    {
        MyBidRankStatusInfo const& info = _myBidRankStatusList[i];
        if (composeWith(packet, &rpc, 2, info._saleId, static_cast<int>(info._bidRankStatus)) == 0)
        {
            Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 636,
                       L"[%s], %s; failed to compose my bid rank status list packet, tid:0x%I64X, wid:%d, "
                       L"bidderPcId:0x%I64X, saleId:0x%I64X, bidRankStatus:%d",
                       MODULE_NAME, L"RetrieveBidRankStatusJob::composeResponsePacket", _tid, static_cast<int>(_wid),
                       _bidderPcId, info._saleId, static_cast<int>(info._bidRankStatus));
            return false;
        }
        incRepeatCount(rpc);
    }
    rpc.PopRepeatCount();
    return true;
}

// ---- ReserveSaleJob ----

// 0xb6d0
bool ReserveSaleJob::Initialize(Packet const*& packet)
{
    wchar_t const* const fn = L"ReserveSaleJob::Initialize";
    if (packet == nullptr)
    {
        JOB_CONTEXT_CRASH(664, INVALID_PACKET, MODULE_NAME, fn, packet);
        return false;
    }
    short cmd = 0;
    int concurrentSaleCountBonus = 0;
    int accumulatedSaleCountBonus = 0;
    Participant& seller = _saleInfo._seller;
    if (packet->Decompose("hqQhqossqii", &cmd, &_tid, &_saleInfo._saleType, &seller._participantWid,
                          &seller._participantPcId, &seller._participantAccountId, seller._participantWorldName, 33,
                          seller._participantName, 33, &_saleInfo._salePrice, &concurrentSaleCountBonus,
                          &accumulatedSaleCountBonus) == 0)
    {
        Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 683, FAIL_DECOMPOSE, MODULE_NAME, fn);
        return false;
    }
    Log::Write(Log::LT_DEBUG, JOB_CONTEXT_FILE, 686,
               L"[%s], %s; decomposed packet, tid:0x%I64X, saleType:%d, participantWid:%d, participantPcId:0x%I64X, "
               L"participantAccountId:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, participantWorldName:%s, "
               L"participantName:%s, salePrice:%I64d, bonus:(%d/%d)",
               MODULE_NAME, fn, _tid, static_cast<int>(_saleInfo._saleType), static_cast<int>(seller._participantWid),
               seller._participantPcId, ID128_ARGS(seller._participantAccountId), seller._participantWorldName,
               seller._participantName, _saleInfo._salePrice, concurrentSaleCountBonus, accumulatedSaleCountBonus);
    _concurrentSaleCount += concurrentSaleCountBonus;
    _accumulatedSaleCount += accumulatedSaleCountBonus;
    return true;
}

// 0xb9c0
void ReserveSaleJob::ReplySuccess(Session const*& session) const
{
    wchar_t const* const fn = L"ReserveSaleJob::ReplySuccess";
    if (session == nullptr)
    {
        JOB_CONTEXT_CRASH(696, INVALID_SESSION, MODULE_NAME, fn, session);
        return;
    }
    session->Send("hqq", MarketDealer_ReserveSaleOkCmd, _tid, _saleInfo._saleId);
    Log::Write(Log::LT_NOTICE, JOB_CONTEXT_FILE, 701,
               L"[%s], %s; sent reserve sale success ack, tid:0x%I64X, saleId:0x%I64X, sellerPcId:0x%I64X, "
               L"salePrice:%I64d",
               MODULE_NAME, fn, _tid, _saleInfo._saleId, _saleInfo._seller._participantPcId, _saleInfo._salePrice);
}

// 0xbae0
void ReserveSaleJob::ReplyFailure(Session const*& session, short const& failReason) const
{
    wchar_t const* const fn = L"ReserveSaleJob::ReplyFailure";
    if (session == nullptr)
    {
        JOB_CONTEXT_CRASH(707, INVALID_SESSION, MODULE_NAME, fn, session);
        return;
    }
    session->Send("hqE", MarketDealer_ReserveSaleFailCmd, _tid, static_cast<int>(failReason));
    Log::Write(Log::LT_NOTICE, JOB_CONTEXT_FILE, 712,
               L"[%s], %s; sent reserve sale failure ack, tid:0x%I64X, saleId:0x%I64X, sellerPcId:0x%I64X, "
               L"salePrice:%I64d, failReason:%d",
               MODULE_NAME, fn, _tid, _saleInfo._saleId, _saleInfo._seller._participantPcId, _saleInfo._salePrice,
               static_cast<int>(failReason));
}

// 0xbc10
bool ReserveSaleJob::verifyParameter(short& failReason) const
{
    Participant const& seller = _saleInfo._seller;
    char const saleType = _saleInfo._saleType;
    if (saleType > ECONOMY_SALETYPE_INVALID_TYPE && saleType < ECONOMY_SALETYPE_GLOBAL_MAX &&
        seller._participantWid > 0 && seller._participantPcId > 0 &&
        (seller._participantAccountId.id[0] != 0 || seller._participantAccountId.id[1] != 0) &&
        wcslen(seller._participantWorldName) != 0 && wcslen(seller._participantName) != 0 && _saleInfo._salePrice > 0)
    {
        return true;
    }
    Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 730,
               L"[%s], %s; invalid parameter, tid:0x%I64X, saleType:%d, participantWid:%d, participantPcId:0x%I64X, "
               L"participantAccountId:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, participantWorldName:%s, "
               L"participantName:%s, salePrice:%I64d",
               MODULE_NAME, L"ReserveSaleJob::verifyParameter", _tid, static_cast<int>(saleType),
               static_cast<int>(seller._participantWid), seller._participantPcId,
               ID128_ARGS(seller._participantAccountId), seller._participantWorldName, seller._participantName,
               _saleInfo._salePrice);
    failReason = MARKETDEALER_RESERVESALEFAIL_INVALID_PARAMETER;
    return false;
}

// 0xbe20
bool ReserveSaleJob::handleJob(short& failReason)
{
    wchar_t const* const fn = L"ReserveSaleJob::handleJob";
    if (_saleInfo._saleType == ECONOMY_SALETYPE_AUCTION &&
        !SaleContext::DetermineBidUnitPrice(_saleInfo._salePrice, _saleInfo._bidUnitPrice))
    {
        JOB_CONTEXT_CRASH(742,
                          L"== CRASH == [%s], %s; failed to determine bid unit price, tid:0x%I64X, saleId:0x%I64X, "
                          L"sellerPcId:0x%I64X, salePrice:%I64d",
                          MODULE_NAME, fn, _tid, _saleInfo._saleId, _saleInfo._seller._participantPcId,
                          _saleInfo._salePrice);
        failReason = MARKETDEALER_SYSTEM_ERROR;
        return false;
    }

    _saleInfo._unitPrice = _saleInfo._salePrice;
    SaleContext* saleContext = nullptr;
    int dbRetValue = 0;
    if (!MarketDB::ReserveSale(dbRetValue, *this))
    {
        Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 751,
                   L"[%s], %s; failed to reserve sale, dbRetValue:%d, tid:0x%I64X, saleId:0x%I64X, sellerPcId:0x%I64X, "
                   L"salePrice:%I64d",
                   MODULE_NAME, fn, dbRetValue, _tid, _saleInfo._saleId, _saleInfo._seller._participantPcId,
                   _saleInfo._salePrice);
        if (dbRetValue == 2)
            failReason = MARKETDEALER_RESERVESALEFAIL_EXCEEDED_CONCURRENT_SALE_COUNT;
        else if (dbRetValue == 3)
            failReason = MARKETDEALER_RESERVESALEFAIL_EXCEEDED_ACCUMULATED_SALE_COUNT;
        else
            failReason = MARKETDEALER_DB_ERROR;
        return false;
    }

    _saleInfo._saleStatus = SaleInfo::SALESTATUS_RESERVING;
    void* const memory = Memory::_Manager[2]->Alloc(sizeof(SaleContext), JOB_CONTEXT_FILE, 768);
    if (memory != nullptr)
        saleContext = ::new (memory) SaleContext(_saleInfo);
    // BUG: 0xbe20 no null check: a failed alloc gives AddContext and removeReferenceCount a null context.
    if (!MarketDealerDaemon::_instance->_saleContextManager->AddContext(saleContext))
    {
        JOB_CONTEXT_CRASH(770,
                          L"== CRASH == [%s], %s; exception occurred; failed to add sale context, tid:0x%I64X, "
                          L"saleId:0x%I64X, sellerPcId:0x%I64X, salePrice:%I64d",
                          MODULE_NAME, fn, _tid, _saleInfo._saleId, _saleInfo._seller._participantPcId,
                          _saleInfo._salePrice);
    }
    Log::Write(Log::LT_DEBUG, JOB_CONTEXT_FILE, 773,
               L"[%s], %s; succeeded to reserve sale, tid:0x%I64X, saleId:0x%I64X, sellerPcId:0x%I64X, salePrice:%I64d",
               MODULE_NAME, fn, _tid, _saleInfo._saleId, _saleInfo._seller._participantPcId, _saleInfo._salePrice);
    saleContext->removeReferenceCount(JOB_CONTEXT_FILE, 774);
    return true;
}

// ---- CancelSaleReservationJob ----

// 0xc160
bool CancelSaleReservationJob::Initialize(Packet const*& packet)
{
    wchar_t const* const fn = L"CancelSaleReservationJob::Initialize";
    if (packet == nullptr)
    {
        JOB_CONTEXT_CRASH(803, INVALID_PACKET, MODULE_NAME, fn, packet);
        return false;
    }
    short cmd = 0;
    if (packet->Decompose("hqqq", &cmd, &_tid, &_saleId, &_sellerPcId) == 0)
    {
        Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 812, FAIL_DECOMPOSE, MODULE_NAME, fn);
        return false;
    }
    Log::Write(Log::LT_DEBUG, JOB_CONTEXT_FILE, 815,
               L"[%s], %s; decomposed packet, tid:0x%I64X, saleId:0x%I64X, sellerPcId:0x%I64X", MODULE_NAME, fn, _tid,
               _saleId, _sellerPcId);
    return true;
}

// 0xc2c0
void CancelSaleReservationJob::ReplySuccess(Session const*& session) const
{
    wchar_t const* const fn = L"CancelSaleReservationJob::ReplySuccess";
    if (session == nullptr)
    {
        JOB_CONTEXT_CRASH(823, INVALID_SESSION, MODULE_NAME, fn, session);
        return;
    }
    session->Send("hq", MarketDealer_CancelSaleReservationOkCmd, _tid);
    Log::Write(Log::LT_NOTICE, JOB_CONTEXT_FILE, 828,
               L"[%s], %s; sent cancel sale reservation success ack, tid:0x%I64X, saleId:0x%I64X, sellerPcId:0x%I64X",
               MODULE_NAME, fn, _tid, _saleId, _sellerPcId);
}

// 0xc3d0
bool CancelSaleReservationJob::verifyParameter(short& failReason) const
{
    if (_saleId > 0 && _sellerPcId > 0)
        return true;
    Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 846,
               L"[%s], %s; invalid parameter, tid:0x%I64X, saleId:0x%I64X, sellerPcId:0x%I64X", MODULE_NAME,
               L"CancelSaleReservationJob::verifyParameter", _tid, _saleId, _sellerPcId);
    failReason = MARKETDEALER_CANCELSALERESERVATIONFAIL_INVALID_PARAMETER;
    return false;
}

// 0xc450
bool CancelSaleReservationJob::handleJob(short& failReason)
{
    wchar_t const* const fn = L"CancelSaleReservationJob::handleJob";
    SaleContext* const saleContext = MarketDealerDaemon::_instance->_saleContextManager->GetContext(_saleId);
    if (saleContext == nullptr)
    {
        Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 858,
                   L"[%s], %s; there is no such sale context, tid:0x%I64X, saleId:0x%I64X, sellerPcId:0x%I64X",
                   MODULE_NAME, fn, _tid, _saleId, _sellerPcId);
        failReason = MARKETDEALER_CANCELSALERESERVATIONFAIL_NO_SUCH_SALE;
        return false;
    }

    {
        AutoCS autoLock(&saleContext->_lock);
        if (saleContext->_saleInfo._saleStatus != SaleInfo::SALESTATUS_RESERVING)
        {
            Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 868,
                       L"[%s], %s; sale status is not reserving, tid:0x%I64X, saleId:0x%I64X, sellerPcId:0x%I64X, "
                       L"saleStatus:%d",
                       MODULE_NAME, fn, _tid, _saleId, _sellerPcId, static_cast<int>(saleContext->_saleInfo._saleStatus));
            failReason = MARKETDEALER_CANCELSALERESERVATIONFAIL_NO_SUCH_SALE;
        }
        else if (saleContext->_saleInfo._seller._participantPcId != _sellerPcId)
        {
            Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 873,
                       L"[%s], %s; seller pcid is not same, tid:0x%I64X, saleId:0x%I64X, sellerPcId:0x%I64X, "
                       L"contextPcId:0x%I64X",
                       MODULE_NAME, fn, _tid, _saleId, _sellerPcId, saleContext->_saleInfo._seller._participantPcId);
            failReason = MARKETDEALER_CANCELSALERESERVATIONFAIL_NO_SUCH_SALE;
        }
        else
        {
            int dbRetValue = 0;
            if (MarketDB::CancelSaleReservation(dbRetValue, *this))
            {
                saleContext->_saleInfo._saleStatus = SaleInfo::SALESTATUS_RESERVATION_CANCELLATION;
                autoLock.Leave();
                if (!MarketDealerDaemon::_instance->_saleContextManager->RemoveContext(_saleId))
                {
                    JOB_CONTEXT_CRASH(888,
                                      L"== CRASH == [%s], %s; exception occurred; failed to remove sale context, "
                                      L"tid:0x%I64X, saleId:0x%I64X, sellerPcId:0x%I64X",
                                      MODULE_NAME, fn, _tid, _saleId, _sellerPcId);
                }
                Log::Write(Log::LT_DEBUG, JOB_CONTEXT_FILE, 891,
                           L"[%s], %s; succeeded to cancel sale reservation, tid:0x%I64X, saleId:0x%I64X, "
                           L"sellerPcId:0x%I64X",
                           MODULE_NAME, fn, _tid, _saleId, _sellerPcId);
                saleContext->removeReferenceCount(JOB_CONTEXT_FILE, 892);
                return true;
            }
            Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 880,
                       L"[%s], %s; failed to cancel sale reservation, dbRetValue:%d, tid:0x%I64X, saleId:0x%I64X, "
                       L"sellerPcId:0x%I64X",
                       MODULE_NAME, fn, dbRetValue, _tid, _saleId, _sellerPcId);
            failReason = MARKETDEALER_DB_ERROR;
        }
    }
    saleContext->removeReferenceCount(JOB_CONTEXT_FILE, 898);
    return false;
}

// ---- RegisterSaleJob ----

// 0xc8a0
bool RegisterSaleJob::Initialize(PacketConcatenateBuffer*& fpc)
{
    wchar_t const* const fn = L"RegisterSaleJob::Initialize";
    if (fpc == nullptr)
    {
        JOB_CONTEXT_CRASH(923, L"== CRASH == [%s], %s; invalid parameter, fpc:0x%p", MODULE_NAME, fn, fpc);
        return false;
    }
    fpc->decomposer.SetFormat("hiqqqqiQcccQqihiiccs", 2);
    SaleItemInfo& item = _saleItemInfo;
    if (!fpc->Decompose(18, &_tid, &_saleId, &_sellerPcId, &_pawnId, &_saleDuration, &item._itemCommonCategory,
                        &item._itemFirstCategory, &item._itemSecondCategory, &item._itemThirdCategory, &item._itemType,
                        &item._itemInstanceId, &item._itemDataId, &item._itemLevel, &item._itemExp, &item._itemAmount,
                        &item._itemGrade, &item._itemEquipLevel, item._itemXmlData, 1025))
    {
        Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 946, FAIL_DECOMPOSE, MODULE_NAME, fn);
        return false;
    }
    Log::Write(Log::LT_DEBUG, JOB_CONTEXT_FILE, 949,
               L"[%s], %s; decomposed packet, tid:0x%I64X, saleId:0x%I64X, sellerPcId:0x%I64X, pawnId:0x%I64X, "
               L"saleDuration:%d, itemCommonCategory:%d, itemFirstCategory:%d, itemSecondCategory:%d, "
               L"itemThirdCategory:%d, itemType:%d, itemInstanceId:0x%I64X, itemDataId:%d, itemLevel:%d, itemExp:%d, "
               L"itemAmount:%d, itemGrade:%d, itemEquipLevel:%d, itemXmlData:%s",
               MODULE_NAME, fn, _tid, _saleId, _sellerPcId, _pawnId, _saleDuration, SALE_ITEM_ARGS(item));
    return true;
}

// 0xcc50
void RegisterSaleJob::ReplySuccess(Session const*& session) const
{
    wchar_t const* const fn = L"RegisterSaleJob::ReplySuccess";
    if (session == nullptr)
    {
        JOB_CONTEXT_CRASH(957, INVALID_SESSION, MODULE_NAME, fn, session);
        return;
    }
    session->Send("hq", MarketDealer_RegisterSaleOkCmd, _tid);
    Log::Write(Log::LT_NOTICE, JOB_CONTEXT_FILE, 962,
               L"[%s], %s; sent register sale success ack, tid:0x%I64X, saleId:0x%I64X, sellerPcId:0x%I64X",
               MODULE_NAME, fn, _tid, _saleId, _sellerPcId);
}

// 0xcd60
bool RegisterSaleJob::verifyParameter(short& failReason) const
{
    wchar_t const* const fn = L"RegisterSaleJob::verifyParameter";
    SaleItemInfo const& item = _saleItemInfo;
    if (_saleId <= 0 || _sellerPcId <= 0 || _pawnId <= 0 || _saleDuration <= 0)
    {
        Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 982,
                   L"[%s], %s; invalid parameter, tid:0x%I64X, saleId:0x%I64X, sellerPcId:0x%I64X, pawnId:0x%I64X, "
                   L"saleDuration:%d, itemCommonCategory:%d, itemFirstCategory:%d, itemSecondCategory:%d, "
                   L"itemThirdCategory:%d, itemType:%d, itemInstanceId:0x%I64X, itemDataId:%d, itemLevel:%d, itemExp:%d, "
                   L"itemAmount:%d, itemGrade:%d, itemEquipLevel:%d, itemXmlData:%s",
                   MODULE_NAME, fn, _tid, _saleId, _sellerPcId, _pawnId, _saleDuration, SALE_ITEM_ARGS(item));
        failReason = MARKETDEALER_REGISTERSALEFAIL_INVALID_PARAMETER;
        return false;
    }

    MarketDealerFailReason const validity = item.CheckItemDataValidity();
    failReason = static_cast<short>(validity);
    if (validity == MARKETDEALER_NO_ERROR)
        return true;

    int line = 0;
    wchar_t const* format = nullptr;
    switch (validity)
    {
    case MARKETDEALER_REGISTERSALEFAIL_INVALID_ITEM_DATA:
        line = 990;
        format = L"[%s], %s; invalid item data, tid:0x%I64X, saleId:0x%I64X, sellerPcId:0x%I64X, pawnId:0x%I64X, "
                 L"saleDuration:%d, itemCommonCategory:%d, itemFirstCategory:%d, itemSecondCategory:%d, "
                 L"itemThirdCategory:%d, itemType:%d, itemInstanceId:0x%I64X, itemDataId:%d, itemLevel:%d, itemExp:%d, "
                 L"itemAmount:%d, itemGrade:%d, itemEquipLevel:%d, itemXmlData:%s";
        break;
    case MARKETDEALER_REGISTERSALEFAIL_INVALID_MONEY_ITEM_DATA:
        line = 993;
        format = L"[%s], %s; invalid money item data, tid:0x%I64X, saleId:0x%I64X, sellerPcId:0x%I64X, "
                 L"pawnId:0x%I64X, saleDuration:%d, itemCommonCategory:%d, itemFirstCategory:%d, "
                 L"itemSecondCategory:%d, itemThirdCategory:%d, itemType:%d, itemInstanceId:0x%I64X, itemDataId:%d, "
                 L"itemLevel:%d, itemExp:%d, itemAmount:%d, itemGrade:%d, itemEquipLevel:%d, itemXmlData:%s";
        break;
    case MARKETDEALER_REGISTERSALEFAIL_INVALID_DEFAULT_ITEM_DATA:
        line = 996;
        format = L"[%s], %s; invalid default item data, tid:0x%I64X, saleId:0x%I64X, sellerPcId:0x%I64X, "
                 L"pawnId:0x%I64X, saleDuration:%d, itemCommonCategory:%d, itemFirstCategory:%d, "
                 L"itemSecondCategory:%d, itemThirdCategory:%d, itemType:%d, itemInstanceId:0x%I64X, itemDataId:%d, "
                 L"itemLevel:%d, itemExp:%d, itemAmount:%d, itemGrade:%d, itemEquipLevel:%d, itemXmlData:%s";
        break;
    case MARKETDEALER_REGISTERSALEFAIL_INVALID_CUSTOM_ITEM_DATA:
        line = 999;
        format = L"[%s], %s; invalid custom item data, tid:0x%I64X, saleId:0x%I64X, sellerPcId:0x%I64X, "
                 L"pawnId:0x%I64X, saleDuration:%d, itemCommonCategory:%d, itemFirstCategory:%d, "
                 L"itemSecondCategory:%d, itemThirdCategory:%d, itemType:%d, itemInstanceId:0x%I64X, itemDataId:%d, "
                 L"itemLevel:%d, itemExp:%d, itemAmount:%d, itemGrade:%d, itemEquipLevel:%d, itemXmlData:%s";
        break;
    default:
        Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 1002,
                   L"[%s], %s; unknown error, tid:0x%I64X, saleId:0x%I64X, sellerPcId:0x%I64X, pawnId:0x%I64X, "
                   L"saleDuration:%d, itemCommonCategory:%d, itemFirstCategory:%d, itemSecondCategory:%d, "
                   L"itemThirdCategory:%d, itemType:%d, itemInstanceId:0x%I64X, itemDataId:%d, itemLevel:%d, itemExp:%d, "
                   L"itemAmount:%d, itemGrade:%d, itemEquipLevel:%d, itemXmlData:%s",
                   MODULE_NAME, fn, _tid, _saleId, _sellerPcId, _pawnId, _saleDuration, SALE_ITEM_ARGS(item));
        failReason = MARKETDEALER_UNKNOWN_ERROR;
        return false;
    }
    Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, line, format, MODULE_NAME, fn, _tid, _saleId, _sellerPcId, _pawnId,
               _saleDuration, SALE_ITEM_ARGS(item));
    return false;
}

// 0xd170
bool RegisterSaleJob::handleJob(short& failReason)
{
    wchar_t const* const fn = L"RegisterSaleJob::handleJob";
    SaleContext* const saleContext = MarketDealerDaemon::_instance->_saleContextManager->GetContext(_saleId);
    if (saleContext == nullptr)
    {
        Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 1016,
                   L"[%s], %s; there is no such sale context, tid:0x%I64X, saleId:0x%I64X, sellerPcId:0x%I64X",
                   MODULE_NAME, fn, _tid, _saleId, _sellerPcId);
        failReason = MARKETDEALER_REGISTERSALEFAIL_NO_SUCH_SALE;
        return false;
    }

    {
        AutoCS autoLock(&saleContext->_lock);
        SaleInfo& saleInfo = saleContext->_saleInfo;
        int dbRetValue = 0;
        if (saleInfo._saleStatus != SaleInfo::SALESTATUS_RESERVING)
        {
            Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 1026,
                       L"[%s], %s; sale status is not reserving, tid:0x%I64X, saleId:0x%I64X, sellerPcId:0x%I64X, "
                       L"saleStatus:%d",
                       MODULE_NAME, fn, _tid, _saleId, _sellerPcId, static_cast<int>(saleInfo._saleStatus));
            failReason = MARKETDEALER_REGISTERSALEFAIL_INVALID_SALE_STATUS;
        }
        else if (saleInfo._seller._participantPcId != _sellerPcId)
        {
            Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 1031,
                       L"[%s], %s; seller pcid is not same, tid:0x%I64X, saleId:0x%I64X, sellerPcId:0x%I64X, "
                       L"contextPcId:0x%I64X",
                       MODULE_NAME, fn, _tid, _saleId, _sellerPcId, saleInfo._seller._participantPcId);
            failReason = MARKETDEALER_REGISTERSALEFAIL_PCID_IS_NOT_SAME;
        }
        else if (!SaleContext::DetermineUnitPrice(saleInfo._salePrice, _saleItemInfo._itemAmount, _unitPrice))
        {
            JOB_CONTEXT_CRASH(1038,
                              L"== CRASH == [%s], %s; failed to determine unit price, tid:0x%I64X, saleId:0x%I64X, "
                              L"sellerPcId:0x%I64X, salePrice:%I64d, itemAmount:%d",
                              MODULE_NAME, fn, _tid, _saleId, _sellerPcId, saleInfo._salePrice,
                              _saleItemInfo._itemAmount);
            failReason = MARKETDEALER_SYSTEM_ERROR;
        }
        else if (!MarketDB::RegisterSale(dbRetValue, *this))
        {
            Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 1045,
                       L"[%s], %s; failed to register sale, dbRetValue:%d, tid:0x%I64X, saleId:0x%I64X, "
                       L"sellerPcId:0x%I64X",
                       MODULE_NAME, fn, dbRetValue, _tid, _saleId, _sellerPcId);
            failReason = MARKETDEALER_DB_ERROR;
        }
        else
        {
            saleInfo._pawnId = _pawnId;
            saleInfo._unitPrice = _unitPrice;
            saleInfo._saleExpirationTime = _saleExpirationTime;
            saleInfo._saleStatus = SaleInfo::SALESTATUS_SELLING;
            memcpy(&saleContext->_saleItemInfo, &_saleItemInfo, sizeof(SaleItemInfo));
            autoLock.Leave();

            if (!MarketDealerDaemon::_instance->_saleTimeContextManager->AddContext(_saleId, _saleExpirationTime,
                                                                                    saleInfo._saleType, saleContext))
            {
                JOB_CONTEXT_CRASH(1059,
                                  L"== CRASH == [%s], %s; exception occurred; failed to add saletime context, "
                                  L"tid:0x%I64X, saleId:0x%I64X, sellerPcId:0x%I64X",
                                  MODULE_NAME, fn, _tid, _saleId, _sellerPcId);
            }
            Log::Write(Log::LT_DEBUG, JOB_CONTEXT_FILE, 1062,
                       L"[%s], %s; succeeded to register sale, tid:0x%I64X, saleId:0x%I64X, sellerPcId:0x%I64X",
                       MODULE_NAME, fn, _tid, _saleId, _sellerPcId);
            saleContext->removeReferenceCount(JOB_CONTEXT_FILE, 1063);
            return true;
        }
    }
    saleContext->removeReferenceCount(JOB_CONTEXT_FILE, 1069);
    return false;
}

// ---- UpdateSalePriceJob ----

// 0xd700
bool UpdateSalePriceJob::Initialize(Packet const*& packet)
{
    wchar_t const* const fn = L"UpdateSalePriceJob::Initialize";
    if (packet == nullptr)
    {
        JOB_CONTEXT_CRASH(1094, INVALID_PACKET, MODULE_NAME, fn, packet);
        return false;
    }
    short cmd = 0;
    if (packet->Decompose("hqqqq", &cmd, &_tid, &_saleId, &_sellerPcId, &_newSalePrice) == 0)
    {
        Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 1104, FAIL_DECOMPOSE, MODULE_NAME, fn);
        return false;
    }
    Log::Write(Log::LT_DEBUG, JOB_CONTEXT_FILE, 1107,
               L"[%s], %s; decomposed packet, tid:0x%I64X, saleId:0x%I64X, sellerPcId:0x%I64X, newSalePrice:%I64d",
               MODULE_NAME, fn, _tid, _saleId, _sellerPcId, _newSalePrice);
    return true;
}

// 0xd870
void UpdateSalePriceJob::ReplySuccess(Session const*& session) const
{
    wchar_t const* const fn = L"UpdateSalePriceJob::ReplySuccess";
    if (session == nullptr)
    {
        JOB_CONTEXT_CRASH(1115, INVALID_SESSION, MODULE_NAME, fn, session);
        return;
    }
    session->Send("hq", MarketDealer_UpdateSalePriceOkCmd, _tid);
    Log::Write(Log::LT_NOTICE, JOB_CONTEXT_FILE, 1120,
               L"[%s], %s; sent update sale price success ack, tid:0x%I64X, saleId:0x%I64X, sellerPcId:0x%I64X, "
               L"newSalePrice:%I64d",
               MODULE_NAME, fn, _tid, _saleId, _sellerPcId, _newSalePrice);
}

// 0xd980
void UpdateSalePriceJob::ReplyFailure(Session const*& session, short const& failReason) const
{
    wchar_t const* const fn = L"UpdateSalePriceJob::ReplyFailure";
    if (session == nullptr)
    {
        JOB_CONTEXT_CRASH(1126, INVALID_SESSION, MODULE_NAME, fn, session);
        return;
    }
    session->Send("hqE", MarketDealer_UpdateSalePriceFailCmd, _tid, static_cast<int>(failReason));
    Log::Write(Log::LT_NOTICE, JOB_CONTEXT_FILE, 1131,
               L"[%s], %s; sent update sale price failure ack, tid:0x%I64X, saleId:0x%I64X, sellerPcId:0x%I64X, "
               L"newSalePrice:%I64d, failReason:%d",
               MODULE_NAME, fn, _tid, _saleId, _sellerPcId, _newSalePrice, static_cast<int>(failReason));
}

// 0xdaa0
bool UpdateSalePriceJob::verifyParameter(short& failReason) const
{
    if (_saleId > 0 && _sellerPcId > 0 && _newSalePrice > 0)
        return true;
    Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 1139,
               L"[%s], %s; invalid parameter, tid:0x%I64X, saleId:0x%I64X, sellerPcId:0x%I64X, newSalePrice:%I64d",
               MODULE_NAME, L"UpdateSalePriceJob::verifyParameter", _tid, _saleId, _sellerPcId, _newSalePrice);
    failReason = MARKETDEALER_UPDATESALEPRICEFAIL_INVALID_PARAMETER;
    return false;
}

// 0xdb30
bool UpdateSalePriceJob::handleJob(short& failReason)
{
    wchar_t const* const fn = L"UpdateSalePriceJob::handleJob";
    SaleContext* const saleContext = MarketDealerDaemon::_instance->_saleContextManager->GetContext(_saleId);
    if (saleContext == nullptr)
    {
        Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 1151,
                   L"[%s], %s; there is no such sale context, tid:0x%I64X, saleId:0x%I64X, sellerPcId:0x%I64X, "
                   L"newSalePrice:%I64d",
                   MODULE_NAME, fn, _tid, _saleId, _sellerPcId, _newSalePrice);
        failReason = MARKETDEALER_UPDATESALEPRICEFAIL_NO_SUCH_SALE;
        return false;
    }

    {
        AutoCS autoLock(&saleContext->_lock);
        SaleInfo& saleInfo = saleContext->_saleInfo;
        _saleType = saleInfo._saleType;
        bool ready = false;
        if (saleInfo._saleStatus != SaleInfo::SALESTATUS_SELLING)
        {
            Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 1162,
                       L"[%s], %s; sale status is not selling, tid:0x%I64X, saleId:0x%I64X, sellerPcId:0x%I64X, "
                       L"newSalePrice:%I64d, saleStatus:%d",
                       MODULE_NAME, fn, _tid, _saleId, _sellerPcId, _newSalePrice,
                       static_cast<int>(saleInfo._saleStatus));
            failReason = MARKETDEALER_UPDATESALEPRICEFAIL_INVALID_SALE_STATUS;
        }
        else if (saleInfo._seller._participantPcId != _sellerPcId)
        {
            Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 1167,
                       L"[%s], %s; seller pcid is not same, tid:0x%I64X, saleId:0x%I64X, sellerPcId:0x%I64X, "
                       L"newSalePrice:%I64d, contextPcId:0x%I64X",
                       MODULE_NAME, fn, _tid, _saleId, _sellerPcId, _newSalePrice, saleInfo._seller._participantPcId);
            failReason = MARKETDEALER_UPDATESALEPRICEFAIL_PCID_IS_NOT_SAME;
        }
        else if (_saleType == ECONOMY_SALETYPE_AUCTION && saleContext->_bidCount > 0)
        {
            Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 1174,
                       L"[%s], %s; exists bid, tid:0x%I64X, saleId:0x%I64X, sellerPcId:0x%I64X, newSalePrice:%I64d, "
                       L"bidCount:%d",
                       MODULE_NAME, fn, _tid, _saleId, _sellerPcId, _newSalePrice, saleContext->_bidCount);
            failReason = MARKETDEALER_UPDATESALEPRICEFAIL_EXISTS_BID;
        }
        else if (_saleType == ECONOMY_SALETYPE_AUCTION &&
                 !SaleContext::DetermineBidUnitPrice(_newSalePrice, _newBidUnitPrice))
        {
            JOB_CONTEXT_CRASH(1179,
                              L"== CRASH == [%s], %s; failed to determine bid unit price, tid:0x%I64X, saleId:0x%I64X, "
                              L"sellerPcId:0x%I64X, newSalePrice:%I64d",
                              MODULE_NAME, fn, _tid, _saleId, _sellerPcId, _newSalePrice);
            failReason = MARKETDEALER_SYSTEM_ERROR;
        }
        else if (!SaleContext::DetermineUnitPrice(_newSalePrice, saleContext->_saleItemInfo._itemAmount, _newUnitPrice))
        {
            JOB_CONTEXT_CRASH(1187,
                              L"== CRASH == [%s], %s; failed to determine unit price, tid:0x%I64X, saleId:0x%I64X, "
                              L"sellerPcId:0x%I64X, newSalePrice:%I64d, itemAmount:%d",
                              MODULE_NAME, fn, _tid, _saleId, _sellerPcId, _newSalePrice,
                              saleContext->_saleItemInfo._itemAmount);
            failReason = MARKETDEALER_SYSTEM_ERROR;
        }
        else
        {
            ready = true;
        }

        if (ready)
        {
            int dbRetValue = 0;
            if (MarketDB::UpdateSalePrice(dbRetValue, *this))
            {
                if (_saleType == ECONOMY_SALETYPE_AUCTION)
                    saleInfo._bidUnitPrice = _newBidUnitPrice;
                saleInfo._unitPrice = _newUnitPrice;
                saleInfo._salePrice = _newSalePrice;
                autoLock.Leave();
                if (_saleType == ECONOMY_SALETYPE_AUCTION)
                {
                    Log::Write(Log::LT_DEBUG, JOB_CONTEXT_FILE, 1213,
                               L"[%s], %s; succeeded to update sale price, tid:0x%I64X, saleId:0x%I64X, "
                               L"sellerPcId:0x%I64X, newSalePrice:%I64d, newUnitPrice:%I64d, newBidUnitPrice:%I64d",
                               MODULE_NAME, fn, _tid, _saleId, _sellerPcId, _newSalePrice, _newUnitPrice,
                               _newBidUnitPrice);
                }
                else
                {
                    Log::Write(Log::LT_DEBUG, JOB_CONTEXT_FILE, 1215,
                               L"[%s], %s; succeeded to update sale price, tid:0x%I64X, saleId:0x%I64X, "
                               L"sellerPcId:0x%I64X, newSalePrice:%I64d, newUnitPrice:%I64d",
                               MODULE_NAME, fn, _tid, _saleId, _sellerPcId, _newSalePrice, _newUnitPrice);
                }
                saleContext->removeReferenceCount(JOB_CONTEXT_FILE, 1216);
                return true;
            }
            Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 1194,
                       L"[%s], %s; failed to update sale price, dbRetValue:%d, tid:0x%I64X, saleId:0x%I64X, "
                       L"sellerPcId:0x%I64X, newSalePrice:%I64d",
                       MODULE_NAME, fn, dbRetValue, _tid, _saleId, _sellerPcId, _newSalePrice);
            failReason = (dbRetValue == 2) ? MARKETDEALER_UPDATESALEPRICEFAIL_EXISTS_BID : MARKETDEALER_DB_ERROR;
        }
    }
    saleContext->removeReferenceCount(JOB_CONTEXT_FILE, 1222);
    return false;
}

// ---- AbandonSaleJob ----

// 0xe1d0
bool AbandonSaleJob::Initialize(Packet const*& packet)
{
    wchar_t const* const fn = L"AbandonSaleJob::Initialize";
    if (packet == nullptr)
    {
        JOB_CONTEXT_CRASH(1245, INVALID_PACKET, MODULE_NAME, fn, packet);
        return false;
    }
    short cmd = 0;
    if (packet->Decompose("hqqq", &cmd, &_tid, &_saleId, &_sellerPcId) == 0)
    {
        Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 1254, FAIL_DECOMPOSE, MODULE_NAME, fn);
        return false;
    }
    Log::Write(Log::LT_DEBUG, JOB_CONTEXT_FILE, 1257,
               L"[%s], %s; decomposed packet, tid:0x%I64X, saleId:0x%I64X, sellerPcId:0x%I64X", MODULE_NAME, fn, _tid,
               _saleId, _sellerPcId);
    return true;
}

// 0xe330
void AbandonSaleJob::ReplySuccess(Session const*& session) const
{
    wchar_t const* const fn = L"AbandonSaleJob::ReplySuccess";
    if (session == nullptr)
    {
        JOB_CONTEXT_CRASH(1265, INVALID_SESSION, MODULE_NAME, fn, session);
        return;
    }
    session->Send("hq", MarketDealer_AbandonSaleOkCmd, _tid);
    Log::Write(Log::LT_NOTICE, JOB_CONTEXT_FILE, 1270,
               L"[%s], %s; sent abandon sale success ack, tid:0x%I64X, saleId:0x%I64X, sellerPcId:0x%I64X",
               MODULE_NAME, fn, _tid, _saleId, _sellerPcId);
}

// 0xe440
bool AbandonSaleJob::verifyParameter(short& failReason) const
{
    if (_saleId > 0 && _sellerPcId > 0)
        return true;
    Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 1288,
               L"[%s], %s; invalid parameter, tid:0x%I64X, saleId:0x%I64X, sellerPcId:0x%I64X", MODULE_NAME,
               L"AbandonSaleJob::verifyParameter", _tid, _saleId, _sellerPcId);
    failReason = MARKETDEALER_ABANDONSALEFAIL_INVALID_PARAMETER;
    return false;
}

// 0xe4c0
bool AbandonSaleJob::handleJob(short& failReason)
{
    wchar_t const* const fn = L"AbandonSaleJob::handleJob";
    char const kDeliveryReasonSaleAbandonment = 3;  // ECONOMY_MARKET_DELIVERYREASON_SALE_ABANDONMENT (types.h:352)
    SaleContextManager* const saleContextManager = MarketDealerDaemon::_instance->_saleContextManager;
    SaleContext* const saleContext = saleContextManager->GetContext(_saleId);
    if (saleContext == nullptr)
    {
        Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 1301,
                   L"[%s], %s; there is no such sale context, tid:0x%I64X, saleId:0x%I64X, sellerPcId:0x%I64X",
                   MODULE_NAME, fn, _tid, _saleId, _sellerPcId);
        failReason = MARKETDEALER_ABANDONSALEFAIL_NO_SUCH_SALE;
        return false;
    }

    {
        AutoCS autoLock(&saleContext->_lock);
        SaleInfo& saleInfo = saleContext->_saleInfo;
        _saleType = saleInfo._saleType;
        int dbRetValue = 0;
        if (saleInfo._saleStatus != SaleInfo::SALESTATUS_SELLING)
        {
            Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 1312,
                       L"[%s], %s; sale status is not selling, tid:0x%I64X, saleId:0x%I64X, sellerPcId:0x%I64X, "
                       L"saleStatus:%d",
                       MODULE_NAME, fn, _tid, _saleId, _sellerPcId, static_cast<int>(saleInfo._saleStatus));
            failReason = MARKETDEALER_ABANDONSALEFAIL_INVALID_SALE_STATUS;
        }
        else if (saleInfo._seller._participantPcId != _sellerPcId)
        {
            Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 1317,
                       L"[%s], %s; seller pcid is not same, tid:0x%I64X, saleId:0x%I64X, sellerPcId:0x%I64X, "
                       L"contextPcId:0x%I64X",
                       MODULE_NAME, fn, _tid, _saleId, _sellerPcId, saleInfo._seller._participantPcId);
            failReason = MARKETDEALER_ABANDONSALEFAIL_PCID_IS_NOT_SAME;
        }
        else if (_saleType == ECONOMY_SALETYPE_AUCTION && saleContext->_bidCount > 0)
        {
            Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 1324,
                       L"[%s], %s; exists bid, tid:0x%I64X, saleId:0x%I64X, sellerPcId:0x%I64X, bidCount:%d",
                       MODULE_NAME, fn, _tid, _saleId, _sellerPcId, saleContext->_bidCount);
            failReason = MARKETDEALER_ABANDONSALEFAIL_EXISTS_BID;
        }
        else if (!MarketDB::AbandonSale(dbRetValue, *this))
        {
            Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 1332,
                       L"[%s], %s; failed to abandon sale, dbRetValue:%d, tid:0x%I64X, saleId:0x%I64X, "
                       L"sellerPcId:0x%I64X",
                       MODULE_NAME, fn, dbRetValue, _tid, _saleId, _sellerPcId);
            failReason = (dbRetValue == 2) ? MARKETDEALER_ABANDONSALEFAIL_EXISTS_BID : MARKETDEALER_DB_ERROR;
        }
        else
        {
            saleInfo._saleStatus = SaleInfo::SALESTATUS_SALE_ABANDONMENT;
            autoLock.Leave();

            if (!MarketDealerDaemon::_instance->_saleTimeContextManager->RemoveContext(_saleId,
                                                                                       saleInfo._saleExpirationTime))
            {
                JOB_CONTEXT_CRASH(1355,
                                  L"== CRASH == [%s], %s; exception occurred; failed to remove saletime context, "
                                  L"tid:0x%I64X, saleId:0x%I64X, sellerPcId:0x%I64X, saleExpirationTime:%I64d",
                                  MODULE_NAME, fn, _tid, _saleId, _sellerPcId, saleInfo._saleExpirationTime);
            }

            DeliveryContext* deliveryContext = nullptr;
            void* const memory = Memory::_Manager[2]->Alloc(sizeof(DeliveryContext), JOB_CONTEXT_FILE, 1359);
            if (memory != nullptr)
            {
                DeliveryInfo deliveryInfo;
                deliveryInfo._deliveryId = _deliveryId;
                deliveryInfo._deliveryReason = kDeliveryReasonSaleAbandonment;
                deliveryInfo._saleId = _saleId;
                deliveryInfo._pawnId = saleInfo._pawnId;
                deliveryInfo._pawnServiceId = saleInfo._saleId;
                memcpy(&deliveryInfo._pawnOwner, &saleInfo._seller, sizeof(Participant));
                memcpy(&deliveryInfo._recipient, &saleInfo._seller, sizeof(Participant));
                memcpy(&deliveryInfo._marketStatement, &_marketStatement, sizeof(MarketStatement));
                deliveryInfo._jobStatus = DeliveryInfo::JOBSTATUS_DELIVERY_READY;
                deliveryContext = ::new (memory) DeliveryContext(deliveryInfo, saleContext->_saleItemInfo);
            }

            if (!saleContextManager->RemoveContext(_saleId))
            {
                JOB_CONTEXT_CRASH(1371,
                                  L"== CRASH == [%s], %s; exception occurred; failed to remove sale context, "
                                  L"saleId:0x%I64X",
                                  MODULE_NAME, fn, _saleId);
            }
            Log::Write(Log::LT_DEBUG, JOB_CONTEXT_FILE, 1375,
                       L"[%s], %s; succeeded to abandon sale, tid:0x%I64X, saleId:0x%I64X, sellerPcId:0x%I64X, "
                       L"saleType:%d, deliveryId:0x%I64X, statementTitle:%s, statementBody:%s",
                       MODULE_NAME, fn, _tid, _saleId, _sellerPcId, static_cast<int>(_saleType), _deliveryId,
                       _marketStatement._statementTitle, _marketStatement._statementBody);

            {
                // BUG: 0xe4c0 no null check after the DeliveryContext Alloc; the lock uses a null context.
                AutoCS deliveryLock(&deliveryContext->_lock);  // ❓ The original calls the out-of-line AutoCS::Enter 0x8780.
                if (!MarketDealerDaemon::_instance->_deliveryContextManager->AddContext(deliveryContext))
                {
                    JOB_CONTEXT_CRASH(1383,
                                      L"== CRASH == [%s], %s; exception occurred; failed to add delivery context, "
                                      L"deliveryId:0x%I64X, saleId:0x%I64X",
                                      MODULE_NAME, fn, _deliveryId, _saleId);
                }
                if (!Postman::DeliverPost(deliveryContext))
                {
                    Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 1388,
                               L"[%s], %s; failed to deliver post, deliveryId:0x%I64X, saleId:0x%I64X", MODULE_NAME,
                               fn, _deliveryId, _saleId);
                }
            }
            saleContext->removeReferenceCount(JOB_CONTEXT_FILE, 1392);
            deliveryContext->removeReferenceCount(JOB_CONTEXT_FILE, 1393);
            return true;
        }
    }
    saleContext->removeReferenceCount(JOB_CONTEXT_FILE, 1399);
    return false;
}

// ---- ReserveBidJob ----

// 0xecb0
bool ReserveBidJob::Initialize(Packet const*& packet)
{
    wchar_t const* const fn = L"ReserveBidJob::Initialize";
    if (packet == nullptr)
    {
        JOB_CONTEXT_CRASH(1420, INVALID_PACKET, MODULE_NAME, fn, packet);
        return false;
    }
    short cmd = 0;
    Participant& bidder = _bidInfo._dealingInfo._trader;
    if (packet->Decompose("hqqhqossq", &cmd, &_tid, &_saleId, &bidder._participantWid, &bidder._participantPcId,
                          &bidder._participantAccountId, bidder._participantWorldName, 33, bidder._participantName, 33,
                          &_bidInfo._dealingInfo._dealingPrice) == 0)
    {
        Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 1434, FAIL_DECOMPOSE, MODULE_NAME, fn);
        return false;
    }
    Log::Write(Log::LT_DEBUG, JOB_CONTEXT_FILE, 1437,
               L"[%s], %s; decomposed packet, tid:0x%I64X, saleId:0x%I64X, participantWid:%d, participantPcId:0x%I64X, "
               L"participantAccountId:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, participantWorldName:%s, "
               L"participantName:%s, bidPrice:%I64d",
               MODULE_NAME, fn, _tid, _saleId, static_cast<int>(bidder._participantWid), bidder._participantPcId,
               ID128_ARGS(bidder._participantAccountId), bidder._participantWorldName, bidder._participantName,
               _bidInfo._dealingInfo._dealingPrice);
    return true;
}

// 0xef60
void ReserveBidJob::ReplySuccess(Session const*& session) const
{
    wchar_t const* const fn = L"ReserveBidJob::ReplySuccess";
    if (session == nullptr)
    {
        JOB_CONTEXT_CRASH(1445, INVALID_SESSION, MODULE_NAME, fn, session);
        return;
    }
    DealingInfo const& dealing = _bidInfo._dealingInfo;
    session->Send("hqq", MarketDealer_ReserveBidOkCmd, _tid, dealing._dealingId);
    Log::Write(Log::LT_NOTICE, JOB_CONTEXT_FILE, 1450,
               L"[%s], %s; sent reserve bid success ack, tid:0x%I64X, saleId:0x%I64X, bidId:0x%I64X, "
               L"bidderPcId:0x%I64X, bidPrice:%I64d",
               MODULE_NAME, fn, _tid, _saleId, dealing._dealingId, dealing._trader._participantPcId,
               dealing._dealingPrice);
}

// 0xf080
void ReserveBidJob::ReplyFailure(Session const*& session, short const& failReason) const
{
    wchar_t const* const fn = L"ReserveBidJob::ReplyFailure";
    if (session == nullptr)
    {
        JOB_CONTEXT_CRASH(1456, INVALID_SESSION, MODULE_NAME, fn, session);
        return;
    }
    DealingInfo const& dealing = _bidInfo._dealingInfo;
    session->Send("hqE", MarketDealer_ReserveBidFailCmd, _tid, static_cast<int>(failReason));
    Log::Write(Log::LT_NOTICE, JOB_CONTEXT_FILE, 1461,
               L"[%s], %s; sent reserve bid failure ack, tid:0x%I64X, saleId:0x%I64X, bidId:0x%I64X, "
               L"bidderPcId:0x%I64X, bidPrice:%I64d, failReason:%d",
               MODULE_NAME, fn, _tid, _saleId, dealing._dealingId, dealing._trader._participantPcId,
               dealing._dealingPrice, static_cast<int>(failReason));
}

// 0xf1b0
bool ReserveBidJob::verifyParameter(short& failReason) const
{
    Participant const& bidder = _bidInfo._dealingInfo._trader;
    if (_saleId > 0 && bidder._participantWid > 0 && bidder._participantPcId > 0 &&
        (bidder._participantAccountId.id[0] != 0 || bidder._participantAccountId.id[1] != 0) &&
        wcslen(bidder._participantWorldName) != 0 && wcslen(bidder._participantName) != 0 &&
        _bidInfo._dealingInfo._dealingPrice > 0)
    {
        return true;
    }
    Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 1473,
               L"[%s], %s; invalid parameter, tid:0x%I64X, saleId:0x%I64X, participantWid:%d, participantPcId:0x%I64X, "
               L"participantAccountId:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, participantWorldName:%s, "
               L"participantName:%s, bidPrice:%I64d",
               MODULE_NAME, L"ReserveBidJob::verifyParameter", _tid, _saleId,
               static_cast<int>(bidder._participantWid), bidder._participantPcId,
               ID128_ARGS(bidder._participantAccountId), bidder._participantWorldName, bidder._participantName,
               _bidInfo._dealingInfo._dealingPrice);
    failReason = MARKETDEALER_RESERVEBIDFAIL_INVALID_PARAMETER;
    return false;
}

// 0xf3b0
bool ReserveBidJob::handleJob(short& failReason)
{
    wchar_t const* const fn = L"ReserveBidJob::handleJob";
    DealingInfo const& dealing = _bidInfo._dealingInfo;
    SaleContext* const saleContext = MarketDealerDaemon::_instance->_saleContextManager->GetContext(_saleId);
    if (saleContext == nullptr)
    {
        Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 1485,
                   L"[%s], %s; there is no such sale context, tid:0x%I64X, saleId:0x%I64X, bidId:0x%I64X, "
                   L"bidderPcId:0x%I64X, bidPrice:%I64d",
                   MODULE_NAME, fn, _tid, _saleId, dealing._dealingId, dealing._trader._participantPcId,
                   dealing._dealingPrice);
        failReason = MARKETDEALER_RESERVEBIDFAIL_NO_SUCH_SALE;
        return false;
    }

    {
        AutoCS autoLock(&saleContext->_lock);
        SaleInfo const& saleInfo = saleContext->_saleInfo;
        long long const bidderPcId = dealing._trader._participantPcId;
        if (saleInfo._saleStatus != SaleInfo::SALESTATUS_SELLING)
        {
            Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 1495,
                       L"[%s], %s; sale status is not selling, tid:0x%I64X, saleId:0x%I64X, bidId:0x%I64X, "
                       L"bidderPcId:0x%I64X, bidPrice:%I64d, saleStatus:%d",
                       MODULE_NAME, fn, _tid, _saleId, dealing._dealingId, bidderPcId, dealing._dealingPrice,
                       static_cast<int>(saleInfo._saleStatus));
            failReason = MARKETDEALER_RESERVEBIDFAIL_INVALID_SALE_STATUS;
        }
        else if (saleInfo._saleType != ECONOMY_SALETYPE_AUCTION)
        {
            Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 1500,
                       L"[%s], %s; sale type is not auction, tid:0x%I64X, saleId:0x%I64X, bidId:0x%I64X, "
                       L"bidderPcId:0x%I64X, bidPrice:%I64d, saleType:%d",
                       MODULE_NAME, fn, _tid, _saleId, dealing._dealingId, bidderPcId, dealing._dealingPrice,
                       static_cast<int>(saleInfo._saleType));
            failReason = MARKETDEALER_RESERVEBIDFAIL_SALE_TYPE_IS_NOT_AUCTION;
        }
        else if (saleInfo._seller._participantPcId == bidderPcId)
        {
            Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 1505,
                       L"[%s], %s; seller and bidder are same, tid:0x%I64X, saleId:0x%I64X, bidId:0x%I64X, "
                       L"bidderPcId:0x%I64X, bidPrice:%I64d, sellerPcId:0x%I64X",
                       MODULE_NAME, fn, _tid, _saleId, dealing._dealingId, bidderPcId, dealing._dealingPrice,
                       saleInfo._seller._participantPcId);
            failReason = MARKETDEALER_RESERVEBIDFAIL_SELLER_AND_BIDDER_ARE_SAME;
        }
        else if (saleContext->IsBidding(bidderPcId))
        {
            Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 1510,
                       L"[%s], %s; already exists bid, tid:0x%I64X, saleId:0x%I64X, bidId:0x%I64X, "
                       L"bidderPcId:0x%I64X, bidPrice:%I64d",
                       MODULE_NAME, fn, _tid, _saleId, dealing._dealingId, dealing._trader._participantPcId,
                       dealing._dealingPrice);
            failReason = MARKETDEALER_RESERVEBIDFAIL_ALREADY_BID;
        }
        else if (saleInfo._topBidPrice > 0 && saleInfo._bidUnitPrice + saleInfo._topBidPrice > dealing._dealingPrice)
        {
            Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 1516,
                       L"[%s], %s; insufficient bid price, tid:0x%I64X, saleId:0x%I64X, bidId:0x%I64X, "
                       L"bidderPcId:0x%I64X, bidPrice:%I64d, topBidPrice:%I64d, bidUnitPrice:%I64d",
                       MODULE_NAME, fn, _tid, _saleId, dealing._dealingId, dealing._trader._participantPcId,
                       dealing._dealingPrice, saleInfo._topBidPrice, saleInfo._bidUnitPrice);
            failReason = MARKETDEALER_RESERVEBIDFAIL_INSUFFICIENT_BID_PRICE;
        }
        else if (saleInfo._topBidPrice <= 0 && saleInfo._salePrice > dealing._dealingPrice)
        {
            Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 1523,
                       L"[%s], %s; insufficient bid price, tid:0x%I64X, saleId:0x%I64X, bidId:0x%I64X, "
                       L"bidderPcId:0x%I64X, bidPrice:%I64d, bidInitPrice:%I64d",
                       MODULE_NAME, fn, _tid, _saleId, dealing._dealingId, dealing._trader._participantPcId,
                       dealing._dealingPrice, saleInfo._salePrice);
            failReason = MARKETDEALER_RESERVEBIDFAIL_INSUFFICIENT_BID_PRICE;
        }
        else
        {
            int dbRetValue = 0;
            if (MarketDB::ReserveBid(dbRetValue, *this))
            {
                _bidInfo._bidStatus = BidInfo::BIDSTATUS_RESERVING;
                if (!saleContext->AddBidContext(_bidInfo))
                {
                    JOB_CONTEXT_CRASH(1548,
                                      L"== CRASH == [%s], %s; exception occurred; failed to add bid context, "
                                      L"tid:0x%I64X, saleId:0x%I64X, bidId:0x%I64X, bidderPcId:0x%I64X, "
                                      L"bidPrice:%I64d",
                                      MODULE_NAME, fn, _tid, _saleId, dealing._dealingId,
                                      dealing._trader._participantPcId, dealing._dealingPrice);
                }
                autoLock.Leave();
                Log::Write(Log::LT_DEBUG, JOB_CONTEXT_FILE, 1552,
                           L"[%s], %s; succeeded to reserve bid, tid:0x%I64X, saleId:0x%I64X, bidId:0x%I64X, "
                           L"bidderPcId:0x%I64X, bidPrice:%I64d",
                           MODULE_NAME, fn, _tid, _saleId, dealing._dealingId, dealing._trader._participantPcId,
                           dealing._dealingPrice);
                saleContext->removeReferenceCount(JOB_CONTEXT_FILE, 1553);
                return true;
            }
            Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 1531,
                       L"[%s], %s; failed to reserve bid, dbRetValue:%d, tid:0x%I64X, saleId:0x%I64X, bidId:0x%I64X, "
                       L"bidderPcId:0x%I64X, bidPrice:%I64d",
                       MODULE_NAME, fn, dbRetValue, _tid, _saleId, dealing._dealingId,
                       dealing._trader._participantPcId, dealing._dealingPrice);
            if (dbRetValue == 2)
                failReason = MARKETDEALER_RESERVEBIDFAIL_EXCEEDED_CONCURRENT_BID_COUNT;
            else if (dbRetValue == 3)
                failReason = MARKETDEALER_RESERVEBIDFAIL_ALREADY_BID;
            else
                failReason = MARKETDEALER_DB_ERROR;
        }
    }
    saleContext->removeReferenceCount(JOB_CONTEXT_FILE, 1559);
    return false;
}

// ---- CancelBidReservationJob ----

// 0xfae0
bool CancelBidReservationJob::Initialize(Packet const*& packet)
{
    wchar_t const* const fn = L"CancelBidReservationJob::Initialize";
    if (packet == nullptr)
    {
        JOB_CONTEXT_CRASH(1590, INVALID_PACKET, MODULE_NAME, fn, packet);
        return false;
    }
    short cmd = 0;
    if (packet->Decompose("hqqqq", &cmd, &_tid, &_saleId, &_bidId, &_bidderPcId) == 0)
    {
        Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 1600, FAIL_DECOMPOSE, MODULE_NAME, fn);
        return false;
    }
    Log::Write(Log::LT_DEBUG, JOB_CONTEXT_FILE, 1603,
               L"[%s], %s; decomposed packet, tid:0x%I64X, saleId:0x%I64X, bidId:0x%I64X, bidderPcId:0x%I64X",
               MODULE_NAME, fn, _tid, _saleId, _bidId, _bidderPcId);
    return true;
}

// 0xfc50
void CancelBidReservationJob::ReplySuccess(Session const*& session) const
{
    wchar_t const* const fn = L"CancelBidReservationJob::ReplySuccess";
    if (session == nullptr)
    {
        JOB_CONTEXT_CRASH(1611, INVALID_SESSION, MODULE_NAME, fn, session);
        return;
    }
    session->Send("hq", MarketDealer_CancelBidReservationOkCmd, _tid);
    Log::Write(Log::LT_NOTICE, JOB_CONTEXT_FILE, 1616,
               L"[%s], %s; sent cancel bid reservation success ack, tid:0x%I64X, saleId:0x%I64X, bidId:0x%I64X, "
               L"bidderPcId:0x%I64X",
               MODULE_NAME, fn, _tid, _saleId, _bidId, _bidderPcId);
}

// 0xfd60
void CancelBidReservationJob::ReplyFailure(Session const*& session, short const& failReason) const
{
    wchar_t const* const fn = L"CancelBidReservationJob::ReplyFailure";
    if (session == nullptr)
    {
        JOB_CONTEXT_CRASH(1622, INVALID_SESSION, MODULE_NAME, fn, session);
        return;
    }
    session->Send("hqE", MarketDealer_CancelBidReservationFailCmd, _tid, static_cast<int>(failReason));
    Log::Write(Log::LT_NOTICE, JOB_CONTEXT_FILE, 1627,
               L"[%s], %s; sent cancel bid reservation failure ack, tid:0x%I64X, saleId:0x%I64X, bidId:0x%I64X, "
               L"bidderPcId:0x%I64X, failReason:%d",
               MODULE_NAME, fn, _tid, _saleId, _bidId, _bidderPcId, static_cast<int>(failReason));
}

// 0xfe80
bool CancelBidReservationJob::verifyParameter(short& failReason) const
{
    if (_saleId > 0 && _bidId > 0 && _bidderPcId > 0)
        return true;
    Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 1635,
               L"[%s], %s; invalid parameter, tid:0x%I64X, saleId:0x%I64X, bidId:0x%I64X, bidderPcId:0x%I64X",
               MODULE_NAME, L"CancelBidReservationJob::verifyParameter", _tid, _saleId, _bidId, _bidderPcId);
    failReason = MARKETDEALER_CANCELBIDRESERVATIONFAIL_INVALID_PARAMETER;
    return false;
}

// 0xff10
bool CancelBidReservationJob::handleJob(short& failReason)
{
    wchar_t const* const fn = L"CancelBidReservationJob::handleJob";
    BidContext* bidContext = nullptr;
    SaleContext* const saleContext = MarketDealerDaemon::_instance->_saleContextManager->GetContext(_saleId);
    if (saleContext != nullptr)
    {
        AutoCS autoLock(&saleContext->_lock);
        bidContext = saleContext->GetBidContext(_bidderPcId);
        if (bidContext == nullptr)
        {
            Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 1655,
                       L"[%s], %s; there is no such bid context, tid:0x%I64X, saleId:0x%I64X, bidId:0x%I64X, "
                       L"bidderPcId:0x%I64X",
                       MODULE_NAME, fn, _tid, _saleId, _bidId, _bidderPcId);
            failReason = MARKETDEALER_CANCELBIDRESERVATIONFAIL_NO_SUCH_BID;
            autoLock.Leave();
            saleContext->removeReferenceCount(JOB_CONTEXT_FILE, 1708);
            return false;
        }

        BidInfo& bidInfo = bidContext->_bidInfo;
        bool failed = true;
        int dbRetValue = 0;
        if (bidInfo._dealingInfo._dealingId != _bidId)
        {
            Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 1660,
                       L"[%s], %s; bid id is not same, tid:0x%I64X, saleId:0x%I64X, bidId:0x%I64X, bidderPcId:0x%I64X, "
                       L"contextId:0x%I64X",
                       MODULE_NAME, fn, _tid, _saleId, _bidId, _bidderPcId, bidInfo._dealingInfo._dealingId);
            failReason = MARKETDEALER_CANCELBIDRESERVATIONFAIL_NO_SUCH_BID;
        }
        else if (bidInfo._dealingInfo._trader._participantPcId != _bidderPcId)
        {
            Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 1665,
                       L"[%s], %s; bidder pcId is not same, tid:0x%I64X, saleId:0x%I64X, bidId:0x%I64X, "
                       L"bidderPcId:0x%I64X, contextPcId:0x%I64X",
                       MODULE_NAME, fn, _tid, _saleId, _bidId, _bidderPcId,
                       bidInfo._dealingInfo._trader._participantPcId);
            failReason = MARKETDEALER_CANCELBIDRESERVATIONFAIL_PCID_IS_NOT_SAME;
        }
        else if (bidInfo._bidStatus != BidInfo::BIDSTATUS_RESERVING)
        {
            Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 1670,
                       L"[%s], %s; bid status is not reserving, tid:0x%I64X, saleId:0x%I64X, bidId:0x%I64X, "
                       L"bidderPcId:0x%I64X, bidStatus:%d",
                       MODULE_NAME, fn, _tid, _saleId, _bidId, _bidderPcId, static_cast<int>(bidInfo._bidStatus));
            failReason = MARKETDEALER_CANCELBIDRESERVATIONFAIL_INVALID_BID_STATUS;
        }
        else if (!MarketDB::CancelBidReservation(dbRetValue, *this))
        {
            Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 1677,
                       L"[%s], %s; failed to cancel bid reservation, dbRetValue:%d, tid:0x%I64X, saleId:0x%I64X, "
                       L"bidId:0x%I64X, bidderPcId:0x%I64X",
                       MODULE_NAME, fn, dbRetValue, _tid, _saleId, _bidId, _bidderPcId);
            failReason = MARKETDEALER_DB_ERROR;
        }
        else
        {
            bidInfo._bidStatus = BidInfo::BIDSTATUS_RESERVATION_CANCELLATION;
            if (!saleContext->RemoveBidContext(_bidderPcId))
            {
                JOB_CONTEXT_CRASH(1684,
                                  L"== CRASH == [%s], %s; exception occurred; failed to remove bid context, "
                                  L"tid:0x%I64X, saleId:0x%I64X, bidId:0x%I64X, bidderPcId:0x%I64X",
                                  MODULE_NAME, fn, _tid, _saleId, _bidId, _bidderPcId);
            }
            failed = false;
        }
        autoLock.Leave();
        if (failed)
        {
            bidContext->removeReferenceCount(JOB_CONTEXT_FILE, 1706);
            saleContext->removeReferenceCount(JOB_CONTEXT_FILE, 1708);
            return false;
        }
    }
    else
    {
        // The sale context is gone (the sale is closed). Only the DB row is cancelled.
        int dbRetValue = 0;
        if (!MarketDB::CancelBidReservation(dbRetValue, *this))
        {
            Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 1690,
                       L"[%s], %s; failed to cancel bid reservation, dbRetValue:%d, tid:0x%I64X, saleId:0x%I64X, "
                       L"bidId:0x%I64X, bidderPcId:0x%I64X",
                       MODULE_NAME, fn, dbRetValue, _tid, _saleId, _bidId, _bidderPcId);
            failReason = MARKETDEALER_DB_ERROR;
            return false;
        }
    }
    Log::Write(Log::LT_DEBUG, JOB_CONTEXT_FILE, 1696,
               L"[%s], %s; succeeded to cancel bid reservation, tid:0x%I64X, saleId:0x%I64X, bidId:0x%I64X, "
               L"bidderPcId:0x%I64X",
               MODULE_NAME, fn, _tid, _saleId, _bidId, _bidderPcId);
    if (bidContext != nullptr)
        bidContext->removeReferenceCount(JOB_CONTEXT_FILE, 1698);
    if (saleContext != nullptr)
        saleContext->removeReferenceCount(JOB_CONTEXT_FILE, 1700);
    return true;
}

// ---- RegisterBidJob ----

// 0x10540
bool RegisterBidJob::Initialize(Packet const*& packet)
{
    wchar_t const* const fn = L"RegisterBidJob::Initialize";
    if (packet == nullptr)
    {
        JOB_CONTEXT_CRASH(1733, INVALID_PACKET, MODULE_NAME, fn, packet);
        return false;
    }
    short cmd = 0;
    if (packet->Decompose("hqqqqq", &cmd, &_tid, &_saleId, &_bidId, &_bidderPcId, &_pawnId) == 0)
    {
        Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 1744, FAIL_DECOMPOSE, MODULE_NAME, fn);
        return false;
    }
    Log::Write(Log::LT_DEBUG, JOB_CONTEXT_FILE, 1747,
               L"[%s], %s; decomposed packet, tid:0x%I64X, saleId:0x%I64X, bidId:0x%I64X, bidderPcId:0x%I64X, "
               L"pawnId:0x%I64X",
               MODULE_NAME, fn, _tid, _saleId, _bidId, _bidderPcId, _pawnId);
    return true;
}

// 0x106e0
void RegisterBidJob::ReplySuccess(Session const*& session) const
{
    wchar_t const* const fn = L"RegisterBidJob::ReplySuccess";
    if (session == nullptr)
    {
        JOB_CONTEXT_CRASH(1755, INVALID_SESSION, MODULE_NAME, fn, session);
        return;
    }
    session->Send("hq", MarketDealer_RegisterBidOkCmd, _tid);
    Log::Write(Log::LT_NOTICE, JOB_CONTEXT_FILE, 1760,
               L"[%s], %s; sent register bid success ack, tid:0x%I64X, saleId:0x%I64X, bidId:0x%I64X, "
               L"bidderPcId:0x%I64X, pawnId:0x%I64X",
               MODULE_NAME, fn, _tid, _saleId, _bidId, _bidderPcId, _pawnId);
}

// 0x10800
void RegisterBidJob::ReplyFailure(Session const*& session, short const& failReason) const
{
    wchar_t const* const fn = L"RegisterBidJob::ReplyFailure";
    if (session == nullptr)
    {
        JOB_CONTEXT_CRASH(1766, INVALID_SESSION, MODULE_NAME, fn, session);
        return;
    }
    session->Send("hqE", MarketDealer_RegisterBidFailCmd, _tid, static_cast<int>(failReason));
    Log::Write(Log::LT_NOTICE, JOB_CONTEXT_FILE, 1771,
               L"[%s], %s; sent register bid failure ack, tid:0x%I64X, saleId:0x%I64X, bidId:0x%I64X, "
               L"bidderPcId:0x%I64X, pawnId:0x%I64X, failReason:%d",
               MODULE_NAME, fn, _tid, _saleId, _bidId, _bidderPcId, _pawnId, static_cast<int>(failReason));
}

// 0x10930
bool RegisterBidJob::verifyParameter(short& failReason) const
{
    if (_saleId > 0 && _bidId > 0 && _bidderPcId > 0 && _pawnId > 0)
        return true;
    Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 1780,
               L"[%s], %s; invalid parameter, tid:0x%I64X, saleId:0x%I64X, bidId:0x%I64X, bidderPcId:0x%I64X, "
               L"pawnId:0x%I64X",
               MODULE_NAME, L"RegisterBidJob::verifyParameter", _tid, _saleId, _bidId, _bidderPcId, _pawnId);
    failReason = MARKETDEALER_REGISTERBIDFAIL_INVALID_PARAMETER;
    return false;
}

// 0x109d0
bool RegisterBidJob::handleJob(short& failReason)
{
    wchar_t const* const fn = L"RegisterBidJob::handleJob";
    SaleContext* const saleContext = MarketDealerDaemon::_instance->_saleContextManager->GetContext(_saleId);
    if (saleContext == nullptr)
    {
        Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 1795,
                   L"[%s], %s; there is no such sale context, tid:0x%I64X, saleId:0x%I64X, bidId:0x%I64X, "
                   L"bidderPcId:0x%I64X, pawnId:0x%I64X",
                   MODULE_NAME, fn, _tid, _saleId, _bidId, _bidderPcId, _pawnId);
        failReason = MARKETDEALER_REGISTERBIDFAIL_NO_SUCH_SALE;
        return false;
    }

    {
        AutoCS autoLock(&saleContext->_lock);
        SaleInfo& saleInfo = saleContext->_saleInfo;
        if (saleInfo._saleStatus != SaleInfo::SALESTATUS_SELLING)
        {
            Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 1805,
                       L"[%s], %s; sale status is not selling, tid:0x%I64X, saleId:0x%I64X, bidId:0x%I64X, "
                       L"bidderPcId:0x%I64X, pawnId:0x%I64X, saleStatus:%d",
                       MODULE_NAME, fn, _tid, _saleId, _bidId, _bidderPcId, _pawnId,
                       static_cast<int>(saleInfo._saleStatus));
            failReason = MARKETDEALER_REGISTERBIDFAIL_INVALID_SALE_STATUS;
            autoLock.Leave();
            saleContext->removeReferenceCount(JOB_CONTEXT_FILE, 1881);
            return false;
        }
        BidContext* const bidContext = saleContext->GetBidContext(_bidderPcId);
        if (bidContext == nullptr)
        {
            Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 1812,
                       L"[%s], %s; there is no such bid context, tid:0x%I64X, saleId:0x%I64X, bidId:0x%I64X, "
                       L"bidderPcId:0x%I64X, pawnId:0x%I64X",
                       MODULE_NAME, fn, _tid, _saleId, _bidId, _bidderPcId, _pawnId);
            failReason = MARKETDEALER_REGISTERBIDFAIL_NO_SUCH_BID;
            autoLock.Leave();
            saleContext->removeReferenceCount(JOB_CONTEXT_FILE, 1881);
            return false;
        }

        BidInfo& bidInfo = bidContext->_bidInfo;
        int dbRetValue = 0;
        bool failed = true;
        if (bidInfo._dealingInfo._dealingId != _bidId)
        {
            Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 1817,
                       L"[%s], %s; bid id is not same, tid:0x%I64X, saleId:0x%I64X, bidId:0x%I64X, bidderPcId:0x%I64X, "
                       L"pawnId:0x%I64X, contextId:0x%I64X",
                       MODULE_NAME, fn, _tid, _saleId, _bidId, _bidderPcId, _pawnId, bidInfo._dealingInfo._dealingId);
            failReason = MARKETDEALER_REGISTERBIDFAIL_NO_SUCH_BID;
        }
        else if (bidInfo._dealingInfo._trader._participantPcId != _bidderPcId)
        {
            Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 1822,
                       L"[%s], %s; bidder pcId is not same, tid:0x%I64X, saleId:0x%I64X, bidId:0x%I64X, "
                       L"bidderPcId:0x%I64X, pawnId:0x%I64X, contextPcId:0x%I64X",
                       MODULE_NAME, fn, _tid, _saleId, _bidId, _bidderPcId, _pawnId,
                       bidInfo._dealingInfo._trader._participantPcId);
            failReason = MARKETDEALER_REGISTERBIDFAIL_PCID_IS_NOT_SAME;
        }
        else if (bidInfo._bidStatus != BidInfo::BIDSTATUS_RESERVING)
        {
            Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 1827,
                       L"[%s], %s; bid status is not reserving, tid:0x%I64X, saleId:0x%I64X, bidId:0x%I64X, "
                       L"bidderPcId:0x%I64X, pawnId:0x%I64X, bidStatus:%d",
                       MODULE_NAME, fn, _tid, _saleId, _bidId, _bidderPcId, _pawnId,
                       static_cast<int>(bidInfo._bidStatus));
            failReason = MARKETDEALER_REGISTERBIDFAIL_INVALID_BID_STATUS;
        }
        else if ((_bidPrice = bidInfo._dealingInfo._dealingPrice, saleInfo._topBidPrice > 0) &&
                 saleInfo._bidUnitPrice + saleInfo._topBidPrice > _bidPrice)
        {
            Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 1835,
                       L"[%s], %s; insufficient bid price, tid:0x%I64X, saleId:0x%I64X, bidId:0x%I64X, "
                       L"bidderPcId:0x%I64X, pawnId:0x%I64X, topBidPrice:%I64d, bidUnitPrice:%I64d, bidPrice:%I64d",
                       MODULE_NAME, fn, _tid, _saleId, _bidId, _bidderPcId, _pawnId, saleInfo._topBidPrice,
                       saleInfo._bidUnitPrice, _bidPrice);
            // BUG: 0x109d0 uses the reserve bid fail reason (39), not MARKETDEALER_REGISTERBIDFAIL_INSUFFICIENT_BID_PRICE.
            failReason = MARKETDEALER_RESERVEBIDFAIL_INSUFFICIENT_BID_PRICE;
        }
        else if (saleInfo._topBidPrice <= 0 && saleInfo._salePrice > _bidPrice)
        {
            Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 1842,
                       L"[%s], %s; insufficient bid price, tid:0x%I64X, saleId:0x%I64X, bidId:0x%I64X, "
                       L"bidderPcId:0x%I64X, pawnId:0x%I64X, bidInitPrice:%I64d, bidPrice:%I64d",
                       MODULE_NAME, fn, _tid, _saleId, _bidId, _bidderPcId, _pawnId, saleInfo._salePrice, _bidPrice);
            // BUG: 0x109d0 uses the reserve bid fail reason (39), not MARKETDEALER_REGISTERBIDFAIL_INSUFFICIENT_BID_PRICE.
            failReason = MARKETDEALER_RESERVEBIDFAIL_INSUFFICIENT_BID_PRICE;
        }
        else if (!SaleContext::DetermineUnitPrice(_bidPrice, saleContext->_saleItemInfo._itemAmount, _newUnitPrice))
        {
            JOB_CONTEXT_CRASH(1850,
                              L"== CRASH == [%s], %s; failed to determine unit price, tid:0x%I64X, saleId:0x%I64X, "
                              L"bidId:0x%I64X, bidderPcId:0x%I64X, pawnId:0x%I64X, bidPrice:%I64d, itemAmount:%d",
                              MODULE_NAME, fn, _tid, _saleId, _bidId, _bidderPcId, _pawnId, _bidPrice,
                              saleContext->_saleItemInfo._itemAmount);
            failReason = MARKETDEALER_SYSTEM_ERROR;
        }
        else if (!MarketDB::RegisterBid(dbRetValue, *this))
        {
            Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 1857,
                       L"[%s], %s; failed to register bid, dbRetValue:%d, tid:0x%I64X, saleId:0x%I64X, bidId:0x%I64X, "
                       L"bidderPcId:0x%I64X, pawnId:0x%I64X",
                       MODULE_NAME, fn, dbRetValue, _tid, _saleId, _bidId, _bidderPcId, _pawnId);
            failReason = MARKETDEALER_DB_ERROR;
        }
        else
        {
            bidInfo._dealingInfo._pawnId = _pawnId;
            bidInfo._bidStatus = BidInfo::BIDSTATUS_BIDDING;
            ++saleContext->_bidCount;
            if (!saleContext->SetTopBidInfo(bidInfo))
            {
                JOB_CONTEXT_CRASH(1866,
                                  L"== CRASH == [%s], %s; exception occurred; failed to set top bid info, "
                                  L"tid:0x%I64X, saleId:0x%I64X, bidId:0x%I64X, bidderPcId:0x%I64X, pawnId:0x%I64X, "
                                  L"bidPrice:%I64d",
                                  MODULE_NAME, fn, _tid, _saleId, _bidId, _bidderPcId, _pawnId,
                                  bidInfo._dealingInfo._dealingPrice);
            }
            saleInfo._unitPrice = _newUnitPrice;
            failed = false;
        }

        autoLock.Leave();
        if (failed)
        {
            bidContext->removeReferenceCount(JOB_CONTEXT_FILE, 1879);
            saleContext->removeReferenceCount(JOB_CONTEXT_FILE, 1881);
            return false;
        }
        Log::Write(Log::LT_DEBUG, JOB_CONTEXT_FILE, 1871,
                   L"[%s], %s; succeeded to register bid, tid:0x%I64X, saleId:0x%I64X, bidId:0x%I64X, "
                   L"bidderPcId:0x%I64X, pawnId:0x%I64X, bidPrice:%I64d",
                   MODULE_NAME, fn, _tid, _saleId, _bidId, _bidderPcId, _pawnId, bidInfo._dealingInfo._dealingPrice);
        bidContext->removeReferenceCount(JOB_CONTEXT_FILE, 1872);
        saleContext->removeReferenceCount(JOB_CONTEXT_FILE, 1873);
        return true;
    }
}

// ---- UpdateBidPriceJob ----

// 0x11360
bool UpdateBidPriceJob::Initialize(Packet const*& packet)
{
    wchar_t const* const fn = L"UpdateBidPriceJob::Initialize";
    if (packet == nullptr)
    {
        JOB_CONTEXT_CRASH(1907, INVALID_PACKET, MODULE_NAME, fn, packet);
        return false;
    }
    short cmd = 0;
    if (packet->Decompose("hqqqqqq", &cmd, &_tid, &_saleId, &_bidId, &_bidderPcId, &_maxDealingPrice,
                          &_extraBidPrice) == 0)
    {
        Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 1919, FAIL_DECOMPOSE, MODULE_NAME, fn);
        return false;
    }
    Log::Write(Log::LT_DEBUG, JOB_CONTEXT_FILE, 1922,
               L"[%s], %s; decomposed packet, tid:0x%I64X, saleId:0x%I64X, bidId:0x%I64X, bidderPcId:0x%I64X, "
               L"maxDealingPrice:%I64d, extraBidPrice:%I64d",
               MODULE_NAME, fn, _tid, _saleId, _bidId, _bidderPcId, _maxDealingPrice, _extraBidPrice);
    return true;
}

// 0x11510
void UpdateBidPriceJob::ReplySuccess(Session const*& session) const
{
    wchar_t const* const fn = L"UpdateBidPriceJob::ReplySuccess";
    if (session == nullptr)
    {
        JOB_CONTEXT_CRASH(1930, INVALID_SESSION, MODULE_NAME, fn, session);
        return;
    }
    session->Send("hq", MarketDealer_UpdateBidPriceOkCmd, _tid);
    Log::Write(Log::LT_NOTICE, JOB_CONTEXT_FILE, 1935,
               L"[%s], %s; sent update bid price success ack, tid:0x%I64X, saleId:0x%I64X, bidId:0x%I64X, "
               L"bidderPcId:0x%I64X, maxDealingPrice:%I64d, extraBidPrice:%I64d",
               MODULE_NAME, fn, _tid, _saleId, _bidId, _bidderPcId, _maxDealingPrice, _extraBidPrice);
}

// 0x11630
void UpdateBidPriceJob::ReplyFailure(Session const*& session, short const& failReason) const
{
    wchar_t const* const fn = L"UpdateBidPriceJob::ReplyFailure";
    if (session == nullptr)
    {
        JOB_CONTEXT_CRASH(1941, INVALID_SESSION, MODULE_NAME, fn, session);
        return;
    }
    session->Send("hqE", MarketDealer_UpdateBidPriceFailCmd, _tid, static_cast<int>(failReason));
    Log::Write(Log::LT_NOTICE, JOB_CONTEXT_FILE, 1946,
               L"[%s], %s; sent update bid price failure ack, tid:0x%I64X, saleId:0x%I64X, bidId:0x%I64X, "
               L"bidderPcId:0x%I64X, maxDealingPrice:%I64d, extraBidPrice:%I64d, failReason:%d",
               MODULE_NAME, fn, _tid, _saleId, _bidId, _bidderPcId, _maxDealingPrice, _extraBidPrice,
               static_cast<int>(failReason));
}

// 0x11770
bool UpdateBidPriceJob::verifyParameter(short& failReason) const
{
    if (_saleId > 0 && _bidId > 0 && _bidderPcId > 0 && _maxDealingPrice > 0 && _extraBidPrice > 0)
        return true;
    Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 1956,
               L"[%s], %s; invalid parameter, tid:0x%I64X, saleId:0x%I64X, bidId:0x%I64X, bidderPcId:0x%I64X, "
               L"maxDealingPrice:%I64d, extraBidPrice:%I64d",
               MODULE_NAME, L"UpdateBidPriceJob::verifyParameter", _tid, _saleId, _bidId, _bidderPcId,
               _maxDealingPrice, _extraBidPrice);
    failReason = MARKETDEALER_UPDATEBIDPRICEFAIL_INVALID_PARAMETER;
    return false;
}

// 0x11820
bool UpdateBidPriceJob::handleJob(short& failReason)
{
    wchar_t const* const fn = L"UpdateBidPriceJob::handleJob";
    SaleContext* const saleContext = MarketDealerDaemon::_instance->_saleContextManager->GetContext(_saleId);
    if (saleContext == nullptr)
    {
        Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 1971,
                   L"[%s], %s; there is no such sale context, tid:0x%I64X, saleId:0x%I64X, bidId:0x%I64X, "
                   L"bidderPcId:0x%I64X, maxDealingPrice:%I64d, extraBidPrice:%I64d",
                   MODULE_NAME, fn, _tid, _saleId, _bidId, _bidderPcId, _maxDealingPrice, _extraBidPrice);
        failReason = MARKETDEALER_UPDATEBIDPRICEFAIL_NO_SUCH_SALE;
        return false;
    }

    {
        AutoCS autoLock(&saleContext->_lock);
        SaleInfo& saleInfo = saleContext->_saleInfo;
        if (saleInfo._saleStatus != SaleInfo::SALESTATUS_SELLING)
        {
            Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 1981,
                       L"[%s], %s; sale status is not selling, tid:0x%I64X, saleId:0x%I64X, bidId:0x%I64X, "
                       L"bidderPcId:0x%I64X, maxDealingPrice:%I64d, extraBidPrice:%I64d, saleStatus:%d",
                       MODULE_NAME, fn, _tid, _saleId, _bidId, _bidderPcId, _maxDealingPrice, _extraBidPrice,
                       static_cast<int>(saleInfo._saleStatus));
            failReason = MARKETDEALER_UPDATEBIDPRICEFAIL_INVALID_SALE_STATUS;
            autoLock.Leave();
            saleContext->removeReferenceCount(JOB_CONTEXT_FILE, 2068);
            return false;
        }
        BidContext* const bidContext = saleContext->GetBidContext(_bidderPcId);
        if (bidContext == nullptr)
        {
            Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 1988,
                       L"[%s], %s; there is no such bid context, tid:0x%I64X, saleId:0x%I64X, bidId:0x%I64X, "
                       L"bidderPcId:0x%I64X, maxDealingPrice:%I64d, extraBidPrice:%I64d",
                       MODULE_NAME, fn, _tid, _saleId, _bidId, _bidderPcId, _maxDealingPrice, _extraBidPrice);
            failReason = MARKETDEALER_UPDATEBIDPRICEFAIL_NO_SUCH_BID;
            autoLock.Leave();
            saleContext->removeReferenceCount(JOB_CONTEXT_FILE, 2068);
            return false;
        }

        BidInfo& bidInfo = bidContext->_bidInfo;
        long long const currentBidPrice = bidInfo._dealingInfo._dealingPrice;
        int dbRetValue = 0;
        bool failed = true;
        if (bidInfo._dealingInfo._dealingId != _bidId)
        {
            Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 1993,
                       L"[%s], %s; bid id is not same, tid:0x%I64X, saleId:0x%I64X, bidId:0x%I64X, bidderPcId:0x%I64X, "
                       L"maxDealingPrice:%I64d, extraBidPrice:%I64d, contextId:0x%I64X",
                       MODULE_NAME, fn, _tid, _saleId, _bidId, _bidderPcId, _maxDealingPrice, _extraBidPrice,
                       bidInfo._dealingInfo._dealingId);
            failReason = MARKETDEALER_UPDATEBIDPRICEFAIL_NO_SUCH_BID;
        }
        else if (bidInfo._dealingInfo._trader._participantPcId != _bidderPcId)
        {
            Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 1998,
                       L"[%s], %s; bidder pcId is not same, tid:0x%I64X, saleId:0x%I64X, bidId:0x%I64X, "
                       L"bidderPcId:0x%I64X, maxDealingPrice:%I64d, extraBidPrice:%I64d, contextPcId:0x%I64X",
                       MODULE_NAME, fn, _tid, _saleId, _bidId, _bidderPcId, _maxDealingPrice, _extraBidPrice,
                       bidInfo._dealingInfo._trader._participantPcId);
            failReason = MARKETDEALER_UPDATEBIDPRICEFAIL_PCID_IS_NOT_SAME;
        }
        else if (bidInfo._bidStatus != BidInfo::BIDSTATUS_BIDDING)
        {
            Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 2003,
                       L"[%s], %s; bid status is not bidding, tid:0x%I64X, saleId:0x%I64X, bidId:0x%I64X, "
                       L"bidderPcId:0x%I64X, maxDealingPrice:%I64d, extraBidPrice:%I64d, bidStatus:%d",
                       MODULE_NAME, fn, _tid, _saleId, _bidId, _bidderPcId, _maxDealingPrice, _extraBidPrice,
                       static_cast<int>(bidInfo._bidStatus));
            failReason = MARKETDEALER_UPDATEBIDPRICEFAIL_INVALID_BID_STATUS;
        }
        else if (saleInfo._topBidder._participantPcId == _bidderPcId)
        {
            Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 2008,
                       L"[%s], %s; top bidder, tid:0x%I64X, saleId:0x%I64X, bidId:0x%I64X, bidderPcId:0x%I64X, "
                       L"maxDealingPrice:%I64d, extraBidPrice:%I64d",
                       MODULE_NAME, fn, _tid, _saleId, _bidId, _bidderPcId, _maxDealingPrice, _extraBidPrice);
            failReason = MARKETDEALER_UPDATEBIDPRICEFAIL_TOP_BIDDER;
        }
        else if (saleInfo._bidUnitPrice > _extraBidPrice)
        {
            Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 2013,
                       L"[%s], %s; insufficient bid price, tid:0x%I64X, saleId:0x%I64X, bidId:0x%I64X, "
                       L"bidderPcId:0x%I64X, maxDealingPrice:%I64d, extraBidPrice:%I64d, bidUnitPrice:%I64d",
                       MODULE_NAME, fn, _tid, _saleId, _bidId, _bidderPcId, _maxDealingPrice, _extraBidPrice,
                       saleInfo._bidUnitPrice);
            failReason = MARKETDEALER_UPDATEBIDPRICEFAIL_INSUFFICIENT_BID_PRICE;
        }
        else if (saleInfo._bidUnitPrice + saleInfo._topBidPrice > _extraBidPrice + currentBidPrice)
        {
            Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 2019,
                       L"[%s], %s; insufficient bid price, tid:0x%I64X, saleId:0x%I64X, bidId:0x%I64X, "
                       L"bidderPcId:0x%I64X, maxDealingPrice:%I64d, extraBidPrice:%I64d, topBidPrice:%I64d, "
                       L"bidUnitPrice:%I64d, currentBidPrice:%I64d",
                       MODULE_NAME, fn, _tid, _saleId, _bidId, _bidderPcId, _maxDealingPrice, _extraBidPrice,
                       saleInfo._topBidPrice, saleInfo._bidUnitPrice, currentBidPrice);
            failReason = MARKETDEALER_UPDATEBIDPRICEFAIL_INSUFFICIENT_BID_PRICE;
        }
        else if (_extraBidPrice + currentBidPrice > _maxDealingPrice)
        {
            Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 2024,
                       L"[%s], %s; max dealing price excess, tid:0x%I64X, saleId:0x%I64X, bidId:0x%I64X, "
                       L"bidderPcId:0x%I64X, maxDealingPrice:%I64d, extraBidPrice:%I64d, currentBidPrice:%I64d",
                       MODULE_NAME, fn, _tid, _saleId, _bidId, _bidderPcId, _maxDealingPrice, _extraBidPrice,
                       currentBidPrice);
            failReason = MARKETDEALER_UPDATEBIDPRICEFAIL_MAX_DEALING_PRICE_EXCESS;
        }
        else if ((_newBidPrice = _extraBidPrice + currentBidPrice,
                  !SaleContext::DetermineUnitPrice(_newBidPrice, saleContext->_saleItemInfo._itemAmount,
                                                   _newUnitPrice)))
        {
            JOB_CONTEXT_CRASH(2033,
                              L"== CRASH == [%s], %s; failed to determine unit price, tid:0x%I64X, saleId:0x%I64X, "
                              L"bidId:0x%I64X, bidderPcId:0x%I64X, maxDealingPrice:%I64d, extraBidPrice:%I64d, "
                              L"bidPrice:%I64d, itemAmount:%d",
                              MODULE_NAME, fn, _tid, _saleId, _bidId, _bidderPcId, _maxDealingPrice, _extraBidPrice,
                              _newBidPrice, saleContext->_saleItemInfo._itemAmount);
            failReason = MARKETDEALER_SYSTEM_ERROR;
        }
        else if (!MarketDB::UpdateBidPrice(dbRetValue, *this))
        {
            Log::Write(Log::LT_ERROR, JOB_CONTEXT_FILE, 2040,
                       L"[%s], %s; failed to update bid price, dbRetValue:%d, tid:0x%I64X, saleId:0x%I64X, "
                       L"bidId:0x%I64X, bidderPcId:0x%I64X, maxDealingPrice:%I64d, extraBidPrice:%I64d",
                       MODULE_NAME, fn, dbRetValue, _tid, _saleId, _bidId, _bidderPcId, _maxDealingPrice,
                       _extraBidPrice);
            failReason = MARKETDEALER_DB_ERROR;
        }
        else
        {
            if (!bidContext->SetNewBidPrice(_newBidPrice))
            {
                JOB_CONTEXT_CRASH(2046,
                                  L"== CRASH == [%s], %s; exception occurred; failed to set new bid price, "
                                  L"tid:0x%I64X, saleId:0x%I64X, bidId:0x%I64X, bidderPcId:0x%I64X, "
                                  L"maxDealingPrice:%I64d, extraBidPrice:%I64d, newBidPrice:%I64d",
                                  MODULE_NAME, fn, _tid, _saleId, _bidId, _bidderPcId, _maxDealingPrice,
                                  _extraBidPrice, _newBidPrice);
            }
            if (!saleContext->SetTopBidInfo(bidInfo))
            {
                JOB_CONTEXT_CRASH(2053,
                                  L"== CRASH == [%s], %s; exception occurred; failed to set top bid info, "
                                  L"tid:0x%I64X, saleId:0x%I64X, bidId:0x%I64X, bidderPcId:0x%I64X, "
                                  L"maxDealingPrice:%I64d, extraBidPrice:%I64d, bidPrice:%I64d",
                                  MODULE_NAME, fn, _tid, _saleId, _bidId, _bidderPcId, _maxDealingPrice,
                                  _extraBidPrice, bidInfo._dealingInfo._dealingPrice);
            }
            saleInfo._unitPrice = _newUnitPrice;
            failed = false;
        }

        autoLock.Leave();
        if (failed)
        {
            bidContext->removeReferenceCount(JOB_CONTEXT_FILE, 2066);
            saleContext->removeReferenceCount(JOB_CONTEXT_FILE, 2068);
            return false;
        }
        Log::Write(Log::LT_DEBUG, JOB_CONTEXT_FILE, 2058,
                   L"[%s], %s; succeeded to update bid price, tid:0x%I64X, saleId:0x%I64X, bidId:0x%I64X, "
                   L"bidderPcId:0x%I64X, maxDealingPrice:%I64d, extraBidPrice:%I64d, bidPrice:%I64d",
                   MODULE_NAME, fn, _tid, _saleId, _bidId, _bidderPcId, _maxDealingPrice, _extraBidPrice,
                   bidInfo._dealingInfo._dealingPrice);
        bidContext->removeReferenceCount(JOB_CONTEXT_FILE, 2059);
        saleContext->removeReferenceCount(JOB_CONTEXT_FILE, 2060);
        return true;
    }
}
