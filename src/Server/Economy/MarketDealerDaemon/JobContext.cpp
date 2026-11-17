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

// ---- AutoCS (Lock.h COMDAT) ----

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
