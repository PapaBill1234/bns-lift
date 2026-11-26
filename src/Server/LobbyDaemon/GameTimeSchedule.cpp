// GameTimeSchedule.obj (LobbyDaemon PDB, 2019 + PDB). Lifted from the pseudocode with PDB types.
#include <new>
#include <string.h>
#include <time.h>
#include <winsock2.h>
#include <windows.h>
#if defined(__clang__)
#include "crt_cpp_overload.h"
#endif
#include "GameTimeSchedule.h"
#include "AlertSender.h"
#include "CliSession.h"
#include "LiftStub.h"
#include "CliSessionManager.h"
#include "KickJob.h"
#include "LobbyDaemon.h"
#include "LobbyJob.h"
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "ObjectPoolLobbyDaemon.h"

static wchar_t const kFile[] = L"GameTimeSchedule.cpp";

// PDB public LobbyErrorDesc (28 entries). LobbyGamePacketHandler.cpp has the placeholder definition. ❓
extern wchar_t const* LobbyErrorDesc[28];

// LIFT: inlined in GameTimeQueue::Block (0x4bb80). A TLobbyError value of 28 or more gives "LOBERR_UNDEFINED".
static __forceinline wchar_t const* LobbyErrorText(int error)
{
    if (static_cast<unsigned int>(error) >= LOBERR_MAX)
        return L"LOBERR_UNDEFINED";
    return LobbyErrorDesc[error];
}

// 0x4b8e0
// The string has 42 hex digits. Each digit gives 4 hours, most significant bit first.
bool IDEV612_TimeTable::Initialize(char const* timeTableStr)
{
    if (timeTableStr == nullptr || strlen(timeTableStr) != 42)
        return false;

    for (int i = 0; i < 42; ++i)
    {
        char c = timeTableStr[i];
        char value;
        if (c >= '0' && c <= '9')
            value = c - '0';
        else if (c >= 'a' && c <= 'f')
            value = c - 'a' + 10;
        else if (c >= 'A' && c <= 'F')
            value = c - 'A' + 10;
        else
            return false;

        for (int bit = 0; bit < 4; ++bit)
            _table[i * 4 + bit] = ((value << bit) & 8) != 0;
    }
    return true;
}

// 0x4b9a0
GameTimeQueue::GameTimeQueue() : _index(-1), _block(false)
{
}

// 0x4b9e0
// LIFT: the loop is the PDB inline RefCntList::Popfront.
GameTimeQueue::~GameTimeQueue()
{
    while (RefCntListNode* node = _queue.Popfront())
        node->removeReferenceCount(kFile, 112);
}

// 0x4ba80
bool GameTimeQueue::Pushback(GameTimeScheduleNode* node)
{
    if (node == nullptr)
    {
        Log::Write(Log::LT_ERROR, kFile, 119,
                   L"== CRASH == [game-time], push node into queue fail; invalid parameter, queue-index:%d", _index);
        AlertSender::Write(kFile, 119,
                           L"== CRASH == [game-time], push node into queue fail; invalid parameter, queue-index:%d",
                           _index);
        TLobbyError = LOBERR_INVALID_PARAMETER;
        return false;
    }

    bool result = false;
    _lock.Enter();
    if (_block)
        TLobbyError = LOBERR_GAME_TIME_SCHEDULE_IN_SCHEDULED_BLOCK_TIME;
    else if (_queue.Pushback(node))
        result = true;
    else
        TLobbyError = LOBERR_SYSTEM;
    _lock.Leave();
    return result;
}

// 0x4bb80
// The nodes move to a local list under the lock. The sessions are then stopped or kicked without the lock.
// LIFT: the original does not release the node when the session is not found (no removeReferenceCount at line 206).
void GameTimeQueue::Block()
{
    RefCntList reservedList;

    _lock.Enter();
    if (_block)
    {
        Log::Write(Log::LT_ERROR, kFile, 162,
                   L"== CRASH == [game-time], block queue fail; already blocked, queue-index:%d", _index);
        AlertSender::Write(kFile, 162, L"== CRASH == [game-time], block queue fail; already blocked, queue-index:%d",
                           _index);
    }
    else
    {
        _block = true;
        Log::Write(Log::LT_DEBUG, kFile, 167, L"[game-time], block queue ok, queue-index:%d, queue-size:%d", _index,
                   _queue.Size());
        while (RefCntListNode* node = _queue.Popfront())
        {
            reservedList.Pushback(node);
            node->removeReferenceCount(kFile, 170);
        }
    }
    _lock.Leave();

    while (GameTimeScheduleNode* node = static_cast<GameTimeScheduleNode*>(reservedList.Popfront()))
    {
        CliSession* cs = LobbyDaemon::_instance->_clisessionMgr->Select(node->GetClikey());
        if (cs == nullptr)
            continue;

        if (cs->ReserveStopPlay(true, 6, 12))
        {
            Log::Write(Log::LT_DEBUG, kFile, 187,
                       L"[game-time], block queue; reserve stop play ok, queue-index:%d, cli-key:0x%I64X", _index,
                       cs->_clikey);
        }
        else if (TLobbyError == LOBERR_STOP_PLAY_ALREADY_RESERVED)
        {
            Log::Write(Log::LT_DEBUG, kFile, 193,
                       L"[game-time], block queue; stop play already reserved, queue-index:%d, cli-key:0x%I64X",
                       _index, cs->_clikey);
        }
        else
        {
            Log::Write(Log::LT_DEBUG, kFile, 199,
                       L"[game-time], block queue; kick cli-session, reason:%s, queue-index:%d, cli-key:0x%I64X",
                       LobbyErrorText(TLobbyError), _index, cs->_clikey);
            void* mem = KickJob::_pool.Checkout(kFile, 200);
            KickJob* job = mem != nullptr ? new (mem) KickJob(cs, 12, nullptr) : nullptr;
            LobbyJobManager* jobMgr = LobbyDaemon::_instance->_jobMgr;
            if (jobMgr->Register(job))
                jobMgr->Execute(job, 1, nullptr);
            job->removeReferenceCount(kFile, 203);
        }
        cs->removeReferenceCount(kFile, 205);
        node->removeReferenceCount(kFile, 206);
    }
}

// 0x4bf90
void GameTimeQueue::Release()
{
    _lock.Enter();
    if (!_block)
    {
        Log::Write(Log::LT_ERROR, kFile, 216,
                   L"== CRASH == [game-time], release queue fail; not blocked, queue-index:%d", _index);
        AlertSender::Write(kFile, 216, L"== CRASH == [game-time], release queue fail; not blocked, queue-index:%d",
                           _index);
    }
    else
    {
        _block = false;
        Log::Write(Log::LT_DEBUG, kFile, 221, L"[game-time], requeue queue ok, queue-index:%d", _index);
    }
    _lock.Leave();
}

// 0x4c020
GameTimeScheduler::GameTimeScheduler() : _currentQueue(0), _currentQueueTime(0), _run(false)
{
}

// 0x4c0e0 (scalar deleting destructor 0x4c0c0)
GameTimeScheduler::~GameTimeScheduler()
{
}

// 0x4c150
// The queue index is hour + 24 * weekday. The week starts on Monday.
bool GameTimeScheduler::Start()
{
    if (_run)
    {
        Log::Write(Log::LT_ERROR, kFile, 270, L"== CRASH == [game-time], start scheduler fail; already started");
        AlertSender::Write(kFile, 270, L"== CRASH == [game-time], start scheduler fail; already started");
        return false;
    }

    long long now = _time64(nullptr);
    tm ts;
    memset(&ts, 0, sizeof(ts));
    _localtime64_s(&ts, &now);
    int weekday = ts.tm_wday != 0 ? ts.tm_wday - 1 : 6;
    int index = ts.tm_hour + 24 * weekday;
    if (index < 0 || index >= 168)
    {
        Log::Write(Log::LT_ERROR, kFile, 285,
                   L"== CRASH == [game-time], start scheduler fail; invalid queue index, index:%d", index);
        AlertSender::Write(kFile, 285,
                           L"== CRASH == [game-time], start scheduler fail; invalid queue index, index:%d", index);
        return false;
    }

    _queues[index].Block();
    _currentQueue = index;
    ts.tm_sec = 0;
    ts.tm_min = 0;
    _currentQueueTime = _mktime64(&ts);
    _run = true;
    LobbyDaemon::_instance->AddTimer(1000 * (static_cast<long>(_currentQueueTime - now) + 3600), this);
    return true;
}

// 0x4c2e0
// Each hour: release the current queue, then block the next queue.
bool GameTimeScheduler::HandleEvent(EventContext*, unsigned long)
{
    if (_run)
    {
        _queues[_currentQueue].Release();
        _currentQueueTime += 3600;
        if (++_currentQueue >= 168)
            _currentQueue = 0;
        _queues[_currentQueue].Block();
        LobbyDaemon::_instance->AddTimer(1000 * (static_cast<long>(_currentQueueTime - _time64(nullptr)) + 3600),
                                         this);
    }
    return true;
}

// 0x4c390
// The session ends at the first hour (from now) that the time table does not allow.
// LIFT: LTCG removed the cs check from this out-of-line copy. Its inline copy in
// StartCliSessionWnpTokenJob::loginAccount (0xdb950) keeps the log at line 336.
bool GameTimeScheduler::Schedule(CliSession* cs, IDEV612_TimeTable const& table, long long* outClosestEndTime)
{
    if (cs == nullptr)
    {
        Log::Write(Log::LT_ERROR, kFile, 336, L"[game-time], schedule fail; invalid parameter");
        return false;
    }

    long long now = _time64(nullptr);
    tm tmnow;
    memset(&tmnow, 0, sizeof(tmnow));
    _localtime64_s(&tmnow, &now);
    int weekday = tmnow.tm_wday != 0 ? tmnow.tm_wday - 1 : 6;
    int hour = tmnow.tm_hour;
    int index = hour + 24 * weekday;
    if (static_cast<unsigned int>(index) >= 168)
    {
        TLobbyError = LOBERR_GAME_TIME_SCHEDULE_NO_NEED_TO_SCHEDULE;
        return false;
    }

    bool const* begin = table._table;
    bool const* end = table._table + 168;
    bool const* p = begin + index;
    while (*p)
    {
        if (++p == end)
            p = begin;
        if (p == begin + index)
        {
            TLobbyError = LOBERR_GAME_TIME_SCHEDULE_NO_NEED_TO_SCHEDULE;
            return false;
        }
    }

    int pos = static_cast<int>(p - begin);
    int endWeekday = pos / 24;
    int endHour = pos % 24;
    if (endWeekday == weekday && endHour == hour)
    {
        TLobbyError = LOBERR_GAME_TIME_SCHEDULE_IN_SCHEDULED_BLOCK_TIME;
        return false;
    }

    int queueIndex = 24 * endWeekday + endHour;
    if (static_cast<unsigned int>(queueIndex) >= 168)
    {
        Log::Write(Log::LT_ERROR, kFile, 364,
                   L"[game-time], schedule fail; queue index out of range, index:%d, cli-key:0x%I64X", queueIndex,
                   cs->_clikey);
        TLobbyError = LOBERR_SYSTEM;
        return false;
    }

    void* mem = Memory::_Manager[2]->Alloc(sizeof(GameTimeScheduleNode), kFile, 369);
    GameTimeScheduleNode* node = mem != nullptr ? new (mem) GameTimeScheduleNode(cs->_clikey, queueIndex) : nullptr;
    if (!_queues[queueIndex].Pushback(node))
    {
        TLobbyError = LOBERR_GAME_TIME_SCHEDULE_IN_SCHEDULED_BLOCK_TIME;
        node->removeReferenceCount(kFile, 376);
        return false;
    }

    Log::Write(Log::LT_DEBUG, kFile, 382,
               L"[game-time], schedule ok, queue-index:%d, weekday:%d, hour:%d, cli-key:0x%I64X", queueIndex,
               endWeekday, endHour, cs->_clikey);
    cs->setScheduledEndTime(node);

    if (outClosestEndTime != nullptr)
    {
        int hours = endHour + 24 * (endWeekday - weekday) - hour;
        if (hours < 0)
            hours += 168;
        tmnow.tm_sec = 0;
        tmnow.tm_min = 0;
        tmnow.tm_hour += hours;
        *outClosestEndTime = _mktime64(&tmnow);
    }
    node->removeReferenceCount(kFile, 395);
    return true;
}

// 0x4c6a0
void GameTimeScheduler::Unschedule(CliSession* cs, GameTimeScheduleNode* node)
{
    if (cs != nullptr && node != nullptr)
    {
        int queueIndex = node->GetQueueIndex();
        if (static_cast<unsigned int>(queueIndex) < 168)
        {
            _queues[queueIndex].Remove(node);
            Log::Write(Log::LT_DEBUG, kFile, 415, L"[game-time], unschedule ok, index:%d, cli-key:0x%I64X", queueIndex,
                       cs->_clikey);
        }
        else
        {
            Log::Write(Log::LT_ERROR, kFile, 410,
                       L"== CRASH == [game-time], unschedule fail; queue index out of range, index:%d, cli-key:0x%I64X",
                       queueIndex, cs->_clikey);
            AlertSender::Write(
                kFile, 410,
                L"== CRASH == [game-time], unschedule fail; queue index out of range, index:%d, cli-key:0x%I64X",
                queueIndex, cs->_clikey);
        }
    }
    else
    {
        Log::Write(Log::LT_ERROR, kFile, 403,
                   L"== CRASH == [game-time], unschedule fail; invalid parameter, cli-session:%p, node:%p", cs, node);
        AlertSender::Write(kFile, 403,
                           L"== CRASH == [game-time], unschedule fail; invalid parameter, cli-session:%p, node:%p", cs,
                           node);
    }
}
