// LobbyDaemon.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "LobbyDaemon.h"
#include <algorithm>
#include <intrin.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <wchar.h>
#include "../../External/BannedWordFilter/BannedWordFilterLib.h"
#include "Channel.h"
#include "CliSession.h"
#include "CliSessionManager.h"
#include "Console.h"
#include "FragmentPacket.h"
#include "GameWorld.h"
#include "InfoGateChannel.h"
#include "LobbyConfig.h"
#include "LiftStub.h"
#include "Log.h"
#include "Memory.h"
#include "Network.h"
#include "MemoryManager.h"
#include "NPChannel.h"
#include "Packet.h"
#include "PacketUtil.h"
#include "PipeConsole.h"
#include "RefCntObject.h"
#include "Session.h"

LobbyDaemon* LobbyDaemon::_instance = nullptr;  // PDB static member (file-scope data in the original).
CoolDown* GCoolDown = nullptr;                  // PDB global.

// LIFT: strings from LobbyDaemon.exe (UTF-16 literals). The order follows the PDB enum ReloadInvalidReason.
// The order was verified against the LobbyDaemon exe table at rva 0x201268.
wchar_t const* LobbydReloadInvalidRestoreTimer::INVALID_REASON_STR[5] = {
    L"daemon config reload failed",
    L"daemon list reload failed",
    L"world list reload failed",
    L"contents rule config reload failed",
    L"bns common config reload failed",
};

// 0x991c0 SystemEvent::~SystemEvent is inline in Lock.h.

#pragma comment(linker, "/INCLUDE:?Make@SystemEvent@@QEAA_NXZ")  // LIFT: keep until the caller is lifted (0x991f0)
// 0x991f0
bool SystemEvent::Make()
{
    Event = CreateEventW(nullptr, FALSE, FALSE, nullptr);
    return Event != nullptr;
}

// 0x99220
wchar_t const* LobbyDaemon::ShortName()
{
    return L"lobbyd";
}

// 0x99230
wchar_t const* LobbyDaemon::Name()
{
    return L"LobbyDaemon";
}

// 0x99240
wchar_t const* LobbyDaemon::ServiceName()
{
    return L"BnS lobby daemon";
}

// 0x99250
wchar_t const* LobbyDaemon::Descriptions()
{
    return L"Blade&Soul Lobby Daemon";
}

#pragma comment(linker, "/INCLUDE:?Alloc@LobbyObjPoolMemAllocator@@UEAAPEAX_KPEB_WH@Z")  // LIFT: keep until the caller is lifted (0x99260)
// 0x99260
void* LobbyObjPoolMemAllocator::Alloc(unsigned long long size, wchar_t const*, int)
{
    unsigned long long const sz = _alignment * ((_alignment + size - 1) / _alignment);
    _lock.Enter();
    if (static_cast<unsigned long long>(_end - _mem) < sz)
    {
        // BUG: 0x99260 the rest of the old block leaks, and the VirtualAlloc result is not checked.
        _mem = static_cast<unsigned char*>(VirtualAlloc(nullptr, _systemAllocationGranularity, MEM_COMMIT | MEM_RESERVE,
                                                        PAGE_READWRITE));
        _end = _mem + _systemAllocationGranularity;
    }
    unsigned char* const ret = _mem;
    _mem += sz;
    _lock.Leave();
    return ret;
}

#pragma comment(linker, "/INCLUDE:?Alloc@BannedWordFilterMemoryAllocator@@UEAAPEAX_KPEB_WH@Z")  // LIFT: keep until the caller is lifted (0x99380)
// 0x99380
void* BannedWordFilterMemoryAllocator::Alloc(unsigned long long size, wchar_t const* file, int line)
{
    return Memory::_Manager[2]->Alloc(size, file, line);
}

#pragma comment(linker, "/INCLUDE:?Realloc@BannedWordFilterMemoryAllocator@@UEAAPEAXPEAX_KPEB_WH@Z")  // LIFT: keep until the caller is lifted (0x99390)
// 0x99390
void* BannedWordFilterMemoryAllocator::Realloc(void* ptr, unsigned long long size, wchar_t const* file, int line)
{
    return Memory::_Manager[2]->Realloc(ptr, size, file, line);
}

#pragma comment(linker, "/INCLUDE:?Free@BannedWordFilterMemoryAllocator@@UEAAXPEAXPEB_WH@Z")  // LIFT: keep until the caller is lifted (0x993b0)
// 0x993b0
void BannedWordFilterMemoryAllocator::Free(void* ptr, wchar_t const* file, int line)
{
    Memory::_Manager[2]->Free(ptr, file, line);
}

#pragma comment(linker, "/INCLUDE:?GenerateClikey@@YA_KXZ")  // LIFT: keep until the caller is lifted (0x993c0)
// 0x993c0
unsigned long long GenerateClikey()
{
    static unsigned __int64 __seed__ = 0;  // PDB static counter (file-scope data in the original).
    long long const result = _InterlockedIncrement64(reinterpret_cast<volatile __int64*>(&__seed__));
    if (result == 0)
    {
        // The counter wrapped to 0. Take the next value and log it.
        long long const v = _InterlockedExchangeAdd64(reinterpret_cast<volatile __int64*>(&__seed__), 1);
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 157, L"[lobby], cli-key overflow");
        return static_cast<unsigned long long>(v + 1);
    }
    return static_cast<unsigned long long>(result);
}

#pragma comment(linker, "/INCLUDE:?GenerateJobid@@YA_KXZ")  // LIFT: keep until the caller is lifted (0x99410)
// 0x99410
unsigned long long GenerateJobid()
{
    static unsigned __int64 __seed__ = 0;  // PDB static counter (file-scope data in the original).
    long long const result = _InterlockedIncrement64(reinterpret_cast<volatile __int64*>(&__seed__));
    if (result == 0)
    {
        // The counter wrapped to 0. Take the next value and log it.
        long long const v = _InterlockedExchangeAdd64(reinterpret_cast<volatile __int64*>(&__seed__), 1);
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 173, L"[lobby], job-id overflow");
        return static_cast<unsigned long long>(v + 1);
    }
    return static_cast<unsigned long long>(result);
}

#pragma comment(linker, "/INCLUDE:?GenerateLobbyTokenkey@@YA_KXZ")  // LIFT: keep until the caller is lifted (0x99460)
// 0x99460
unsigned long long GenerateLobbyTokenkey()
{
    static unsigned __int64 __seed__ = 0;  // PDB static counter (file-scope data in the original).
    long long const result = _InterlockedIncrement64(reinterpret_cast<volatile __int64*>(&__seed__));
    if (result == 0)
    {
        // The counter wrapped to 0. Take the next value and log it.
        long long const v = _InterlockedExchangeAdd64(reinterpret_cast<volatile __int64*>(&__seed__), 1);
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 188, L"[lobby], token-key overflow");
        return static_cast<unsigned long long>(v + 1);
    }
    return static_cast<unsigned long long>(result);
}

#pragma comment(linker, "/INCLUDE:?GameWorldReporterListener@@YAXPEAVGameWorldReporter@@@Z")  // LIFT: keep until the caller is lifted (0x994b0)
// 0x994b0
void GameWorldReporterListener(GameWorldReporter* reporter)
{
    if (reporter == nullptr)
    {
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 201, L"[lobby], listen world reporter fail; invalid parameter");
        return;
    }
    // Inlined accessor: copy _report under the lock and add a reference.
    GameWorldReport* report = nullptr;
    reporter->_lock.Enter();
    if (reporter->_report != nullptr)
    {
        report = reporter->_report;
        report->addReferenceCount(false, L"GameWorld.cpp", 1246);
    }
    reporter->_lock.Leave();
    if (report == nullptr)
    {
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 215, L"[lobby], listen world reporter fail; null report");
        return;
    }
    // LIFT: the original calls 0x2ef40 with _lgatechmgr. InfoGateChannelManager::Broadcast and the
    // LobbyGateChannelManager body are the same (folded). Both classes have the same layout (0x48).
    InfoGateChannelManager* const lgatechmgr = reinterpret_cast<InfoGateChannelManager*>(LobbyDaemon::_instance->_lgatechmgr);
    Packet const* const packet = report->GetPacket();
    if (packet != nullptr)
    {
        if (!lgatechmgr->Broadcast(packet))
            Log::Write(Log::LT_ERROR, L"LobbyGateChannel.cpp", 1054,
                       L"[lobby-gate], broadcast update-world-info-list-notify fail; broadcast fail");
    }
    else
    {
        Log::Write(Log::LT_ERROR, L"LobbyGateChannel.cpp", 1049,
                   L"[lobby-gate], broadcast update-world-info-list-notify fail; invalid parameter");
    }
    report->removeReferenceCount(L"LobbyDaemon.cpp", 212);
}

#pragma comment(linker, "/INCLUDE:?HandleEvent@CoolDown@@UEAA_NPEAUEventContext@@K@Z")  // LIFT: keep until the caller is lifted (0x995c0)
// 0x995c0
bool CoolDown::HandleEvent(EventContext*, unsigned long)
{
    if (!_run)
    {
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 240, L"[cooldown], not started");
        return false;
    }
    CliSessionManager* const clisessionMgr = LobbyDaemon::_instance->_clisessionMgr;
    if (clisessionMgr == nullptr)
    {
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 246, L"[cooldown], cli-session manager not found");
        return false;
    }
    long long const elapsed = static_cast<long long>(GetTickCount64()) - Daemon::Instance->StartSystemTick64;
    long long const halfEnd = _end - _duration / 2;
    int const size = clisessionMgr->_size;
    int remain = 0;
    if (static_cast<int>((_end - elapsed) / 1000) > 0)
        remain = static_cast<int>((_end - elapsed) / 1000);
    Log::Write(Log::LT_NOTICE, L"LobbyDaemon.cpp", 258,
               L"[cooldown], report status, remain-cli-session-count:%d, remain-time:%d(sec)", clisessionMgr->_size,
               remain);
    if (!((size > 0 || elapsed < halfEnd) && elapsed < _end))
    {
        if (size <= 0)
        {
            Log::Write(Log::LT_NOTICE, L"LobbyDaemon.cpp", 270, L"[cooldown], success. u can SHUTDOWN SAFELY");
        }
        else
        {
            CliSessionTable::CliSessionList remainCsList;
            clisessionMgr->SelectAll(remainCsList);
            for (CliSessionTable::CliSessionList::iterator it = remainCsList.begin(); it != remainCsList.end(); ++it)
            {
                CliSession* const cs = *it;
                if (cs != nullptr)
                {
                    int const state = cs->_state;
                    Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 281,
                               L"[cooldown], cli-session not finished, cli-key:0x%I64X, cli-state:%d.%d", cs->_clikey,
                               static_cast<int>(static_cast<unsigned short>(static_cast<unsigned int>(state) >> 16)),
                               static_cast<int>(static_cast<unsigned short>(state)));
                    cs->removeReferenceCount(L"LobbyDaemon.cpp", 282);
                }
            }
            Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 286,
                       L"[cooldown], fail; some jobs remains; u may try SHUTDOWN UNSAFELY or retry COOLDOWN, "
                       L"remain-cli-session-count:%d",
                       size);
            remainCsList.clear();
        }
        // Inlined Daemon::setState(STATE_COOLDOWNED).
        LobbyDaemon* const daemon = LobbyDaemon::_instance;
        daemon->State = Daemon::STATE_COOLDOWNED;
        PipeConsole* const pipeConsole = daemon->pipeConsole;
        if (pipeConsole != nullptr)
        {
            pipeConsole->_lock.Enter();
            pipeConsole->_state = 8;
            pipeConsole->_lock.Leave();
        }
        if (daemon->console != nullptr)
            daemon->console->SetState(8);
        _run = false;
    }
    else if (!Daemon::Instance->AddTimer(_period, this))
    {
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 297,
                   L"[cooldown], fail; add timer fail; u may try SHUTDOWN UNSAFELY or retry COOLDOWN, "
                   L"remain-cli-session-count:%d",
                   size);
        _run = false;
    }
    return true;
}

#pragma comment(linker, "/INCLUDE:?Start@CoolDown@@QEAA_NJJ@Z")  // LIFT: keep until the caller is lifted (0x99880)
// 0x99880
bool CoolDown::Start(long period, long duration)
{
    CoolDown* const self = GCoolDown;
    if (duration <= 0)
    {
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 309, L"[cooldown], start fail; invalid parameter");
        return false;
    }
    if (self->_run)
    {
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 314, L"[cooldown], start fail; already running");
        return false;
    }
    self->_period = period;
    self->_duration = duration;
    long long const now = static_cast<long long>(GetTickCount64());
    self->_run = true;
    self->_end = (static_cast<long long>(duration) - Daemon::Instance->StartSystemTick64) + now;
    if (!Daemon::Instance->AddTimer(self->_period, self))
    {
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 325, L"[cooldown], start fail; add timer fail");
        self->_run = false;
        return false;
    }
    Log::Write(Log::LT_NOTICE, L"LobbyDaemon.cpp", 330, L"[cooldown], start, period:%d(msec), duration:%d(msec)", period,
               duration);
    return true;
}

#pragma comment(linker, "/INCLUDE:?EventId@LobbydReloadInvalidRestoreTimer@@UEBAIXZ")  // LIFT: keep until the caller is lifted (0x99990)
// 0x99990
unsigned int LobbydReloadInvalidRestoreTimer::EventId() const
{
    return 130;
}

#pragma comment(linker, "/INCLUDE:?HandleEvent@LobbydReloadInvalidRestoreTimer@@UEAA_NPEAUEventContext@@K@Z")  // LIFT: keep until the caller is lifted (0x999a0)
// 0x999a0
bool LobbydReloadInvalidRestoreTimer::HandleEvent(EventContext*, unsigned long)
{
    restoreInvalid();
    return true;
}

// 0x999b0
void LobbydReloadInvalidRestoreTimer::restoreInvalid()
{
    for (int i = 0; i < 5; ++i)
    {
        wchar_t const* const reason = INVALID_REASON_STR[i];
        PipeConsole* const pipeConsole = Daemon::Instance->pipeConsole;
        if (pipeConsole == nullptr)
            continue;
        // Inlined PipeConsole::SetInvalidInfo(reason, false).
        pipeConsole->_lock.Enter();
        PipeConsole::ItemNode* node = pipeConsole->_invalid._head._next;
        while (node != &pipeConsole->_invalid._tail)
        {
            if (wcscmp(node->_key, reason) == 0)
                break;
            node = node->_next;
        }
        if (node != &pipeConsole->_invalid._tail && node != nullptr)
        {
            node->_next->_prev = node->_prev;
            node->_prev->_next = node->_next;
            Memory::_Manager[2]->Free(node, L"source\\PipeConsole.cpp", 837);
        }
        pipeConsole->_lock.Leave();
    }
    _isExecuted = true;
}

#pragma comment(linker, "/INCLUDE:?Add@ServiceItems@@QEAA_NW4ServiceItemType@LobbyDaemon@@PEB_W@Z")  // LIFT: keep until the caller is lifted (0x99ac0)
// 0x99ac0
bool ServiceItems::Add(LobbyDaemon::ServiceItemType type, wchar_t const* idListString)
{
    if (static_cast<unsigned int>(type) > LobbyDaemon::SERVICEITEMTYPE_RENAME_CHARACTER_BY_SYSTEM ||
        idListString == nullptr)
    {
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 424,
                   L"[lobby], add service item id candidates fail; invalid param, type:%d, source-str:%s",
                   static_cast<int>(type), idListString != nullptr ? idListString : L"null");
        return false;
    }
    unsigned long long const length = wcslen(idListString);
    if (length != 0)
    {
        wchar_t* const buffer =
            static_cast<wchar_t*>(Memory::_Manager[2]->AllocZero(2 * length + 2, L"LobbyDaemon.cpp", 431));
        wcscpy_s(buffer, length + 1, idListString);
        wchar_t delimiter[2];
        delimiter[0] = L';';
        delimiter[1] = 0;
        wchar_t* next = nullptr;
        std::vector<unsigned int, StlAllocator<unsigned int, 2> >& idList = _idList[type];
        for (wchar_t* token = wcstok_s(buffer, delimiter, &next); token != nullptr;
             token = wcstok_s(nullptr, delimiter, &next))
        {
            unsigned int const id = static_cast<unsigned int>(_wtoi(token));
            if (id == 0)
            {
                // LIFT: the ids that were added before stay in the list (the original has no rollback).
                Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 444,
                           L"[lobby], add service item id candidates fail; not numeric token exists, token:%s, type:%d",
                           token, static_cast<int>(type));
                Memory::_Manager[2]->Free(buffer, L"LobbyDaemon.cpp", 445);
                return false;
            }
            idList.push_back(id);
        }
        std::sort(idList.begin(), idList.end());
        Memory::_Manager[2]->Free(buffer, L"LobbyDaemon.cpp", 456);
    }
    Log::Write(Log::LT_DEBUG, L"LobbyDaemon.cpp", 459, L"[lobby], add service item id candidates ok, type:%d, source:%s",
               static_cast<int>(type), idListString);
    return true;
}

#pragma comment(linker, "/INCLUDE:?GetNextResetTimeUTC@Data@TimeBasedPlaySeasonSchedule@@QEBAX_JAEA_J1@Z")  // LIFT: keep until the caller is lifted (0x99d20)
// 0x99d20
void TimeBasedPlaySeasonSchedule::Data::GetNextResetTimeUTC(long long conditionTimeUTC, long long& prevResetTimeUTC,
                                                            long long& nextResetTimeUTC) const
{
    nextResetTimeUTC = 0;
    prevResetTimeUTC = 0;
    long long const now = _time64(nullptr);
    long long const startTimeUTC = scheduleTime.startTimeUTC;
    long long reset;
    if (startTimeUTC > conditionTimeUTC)
    {
        if (targetType == 0)
        {
            reset = NPMsgHelper::LocaleHourToUTCTime(resetHour, scheduleTime.startTimeUTC, resetHourTimeZoneBiasSecond);
            if (reset <= scheduleTime.startTimeUTC)
                reset += 86400;
        }
        else
        {
            if (targetType == 1)
            {
                prevResetTimeUTC = startTimeUTC;
                nextResetTimeUTC = scheduleTime.endTimeUTC;
            }
            return;
        }
    }
    else
    {
        if (scheduleTime.endTimeUTC < conditionTimeUTC)
        {
            prevResetTimeUTC = 0;
            nextResetTimeUTC = 0;
            return;
        }
        if (targetType != 0)
        {
            prevResetTimeUTC = startTimeUTC;
            nextResetTimeUTC = scheduleTime.endTimeUTC;
            return;
        }
        reset = NPMsgHelper::LocaleHourToUTCTime(resetHour, now, resetHourTimeZoneBiasSecond);
        if (reset <= now)
            reset += 86400;
    }
    nextResetTimeUTC = reset;
    prevResetTimeUTC = reset - 86400;
}

// 0x99df0
TimeBasedPlaySeasonSchedule::TimeBasedPlaySeasonSchedule()
{
    // The Data and Rule constructors are inline (LobbyDaemon.h). They set the same values as 0x99df0 sets.
    for (int i = 0; i < 2; ++i)
        _scheduleData[i].targetType = static_cast<char>(i);
}

#pragma comment(linker, "/INCLUDE:?Compose@TimeBasedPlaySeasonSchedule@@QEBA_NAEAVRepeatPacketComposer@@AEAVPacket@@@Z")  // LIFT: keep until the caller is lifted (0x99ef0)
// 0x99ef0
bool TimeBasedPlaySeasonSchedule::Compose(RepeatPacketComposer& rpc, Packet& packet) const
{
    rpc.PushRepeatCount(&packet);
    for (Data const* pdata = &_scheduleData[0]; pdata != &_scheduleData[2]; ++pdata)
    {
        Data const& data = *pdata;
        if (packet.FreeSize() < 0x17u)
            packet.Allocate();
        if (packet.Compose(&rpc, 6, static_cast<int>(data.targetType), data.resetHour,
                        data.resetHourTimeZoneBiasSecond, data.scheduleNumber, data.scheduleTime.startTimeUTC,
                        data.scheduleTime.endTimeUTC) == 0)
        {
            Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 634,
                       L"[time-based], packet compose failed - time based schedule");
            return false;
        }
        rpc.PushRepeatCount(&packet);
        for (Rule const* prule = &data.rule[0]; prule != &data.rule[6]; ++prule)
        {
            Rule const& rule = *prule;
            int k = 0;
            while (rule.rewardList[k].id == 0)
            {
                if (++k >= 4)
                    break;
            }
            // All 4 reward ids are 0 and minutes is -1: the rule list ends here.
            if (k >= 4 && rule.minutes == -1)
                break;
            if (packet.FreeSize() < 0x12u)
                packet.Allocate();
            bool ok = packet.Compose(&rpc, 1, static_cast<int>(rule.minutes)) != 0;
            for (int r = 0; r < 4; ++r)
                ok = ok && packet.Compose(&rpc, 1, rule.rewardList[r].id) != 0;
            if (!ok)
            {
                Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 669,
                           L"[time-based], packet compose failed - time based schedule rule");
                return false;
            }
            rpc.IncRepeatCount();
        }
        rpc.PopRepeatCount();
        rpc.IncRepeatCount();
    }
    rpc.PopRepeatCount();
    return true;
}

// 0x9a230
LobbyDaemon::LobbyDaemon()
{
    // LIFT: Daemon::Daemon() and the member constructors (TimeBasedPlaySeasonSchedule 0x99df0) run before this body.
    _config = nullptr;
    _timeZoneBias = 0;
    _serviceItems = nullptr;
    _tick = nullptr;
    _daemonInfoTable = nullptr;
    _gameWorldRegistry = nullptr;
    _gameWorldReporter = nullptr;
    _bannedWordFilter = nullptr;
    _charaterDeletionScheduler = nullptr;
    _stats = nullptr;
    _tencentUIC = nullptr;
    _clisessionMgr = nullptr;
    _jobMgr = nullptr;
    _tokenDesk = nullptr;
    _npServchmgr = nullptr;
    _accountInventoryChannel = nullptr;
    _accountInventorySessionHandler = nullptr;
    _gamedchmgr = nullptr;
    _lgatechmgr = nullptr;
    _manageSessionHandler = nullptr;
    _infogatechmgr = nullptr;
    _postOfficeChannel = nullptr;
    _postOfficeSessionHandler = nullptr;
    _npInitialConnectEvent.Event = nullptr;
    _setupNpScheduleInfoEvent.Event = nullptr;
    _accountInventoryInitialConnectEvent.Event = nullptr;
    _postOfficeInitialConnectEvent.Event = nullptr;
    _systemPerfMon = nullptr;
    _currentRandomStoreInitSchedule.scheduleNumber = 0;
    _currentRandomStoreInitSchedule.slotCountInitScheduleNumber = 0;
    _currentRandomStoreInitSchedule.premiumDrawCountInitScheduleNumber = 0;
    _mileageManager = nullptr;
    _mileageInterimDepositTimer = nullptr;
    _gameTimeScheduler = nullptr;
    _restoreReloadTimer = nullptr;
    LobbyDaemon::_instance = this;
    _localeset.locales = nullptr;
    _localeset.count = 0;
    memset(_localeset.languages, 0, sizeof(_localeset.languages));  // the original clears count and languages with two 8-byte stores
    _currentRandomStoreInitSchedule.scheduleNumber = 0;
    _currentRandomStoreInitSchedule.slotCountInitScheduleNumber = 0;
    _currentRandomStoreInitSchedule.premiumDrawCountInitScheduleNumber = 0;
}

// 0x9a3c0
LobbyDaemon::~LobbyDaemon()
{
    LIFT_STUB(0x9a3c0);
}

// 0x9ae30
void LobbyDaemon::PrintDependency()
{
    wprintf(L"packet lobby-lobbygate %d.0\n", 58);
    wprintf(L"packet lobby-game %d.0\n", 83);
    wprintf(L"packet lobby-manage %d.0\n", 7);
    wprintf(L"packet accountinventory-lobby %d.0\n", 9);
    wprintf(L"packet lobby-infogate %d.0\n", 3);
    wprintf(L"packet post-office %d.0\n", 15);
    wprintf(L"packet ecomomy-common %d.0\n", 10);
    wprintf(L"lib xmlreader %s.0\n", L"15");
    wprintf(L"lib stsmsglib %s.0\n", L"119");
    wprintf(L"lib bannedwordfilter %s.0\n", L"2");
    wprintf(L"lib fsdreader %s.0\n", L"1");
    wprintf(L"security cert %d.0\n", 6);
    wprintf(L"config bns-common-config %d\n", 2);
    wprintf(L"config contents-rule-client %d.%d\n", 65, 0);
    wprintf(L"config contents-rule-server %d.%d\n", 72, 0);
}

// 0x9af60
long LobbyDaemon::GetTimerInterval()
{
    return _config->_timerInterval;
}

// 0x9af70
long LobbyDaemon::GetTimerMaxTime()
{
    return _config->_timerMaxTime;
}

#pragma comment(linker, "/INCLUDE:?SetTimeZoneBias@LobbyDaemon@@QEAA_NXZ")  // LIFT: keep until the caller is lifted (0x9af80)
// 0x9af80
bool LobbyDaemon::SetTimeZoneBias()
{
    TIME_ZONE_INFORMATION tzi;
    DWORD const result = GetTimeZoneInformation(&tzi);
    if (result == TIME_ZONE_ID_INVALID)
    {
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1106, L"GetTimeZoneInfomation failed");
        return false;
    }
    int bias = tzi.Bias;
    if (result == TIME_ZONE_ID_UNKNOWN)
    {
        Log::Write(Log::LT_DEBUG, L"LobbyDaemon.cpp", 1113, L"[lobbyd], SetTimeZoneBias, Name:%s", tzi.StandardName);
    }
    else if (result == TIME_ZONE_ID_STANDARD)
    {
        bias = tzi.StandardBias + tzi.Bias;
        Log::Write(Log::LT_DEBUG, L"LobbyDaemon.cpp", 1117, L"[lobbyd], SetTimeZoneBias, StandardName:%s",
                   tzi.StandardName);
    }
    else if (result == TIME_ZONE_ID_DAYLIGHT)
    {
        bias = tzi.DaylightBias + tzi.Bias;
        Log::Write(Log::LT_DEBUG, L"LobbyDaemon.cpp", 1121, L"[lobbyd], SetTimeZoneBias, DaylightName:%s",
                   tzi.DaylightName);
    }
    long long const seconds = -60LL * bias;
    _timeZoneBias = seconds;
    Log::Write(Log::LT_DEBUG, L"LobbyDaemon.cpp", 1127, L"[lobbyd], SetTimeZoneBias, bias(minutes):%d", seconds / 60);
    return true;
}

#pragma comment(linker, "/INCLUDE:?FailedEventObjectHandler@LobbyDaemon@@SAXPEAVEventObject@@@Z")  // LIFT: keep until the caller is lifted (0x9b0c0)
// 0x9b0c0
void LobbyDaemon::FailedEventObjectHandler(EventObject* eventObject)
{
    switch (eventObject->EventId())
    {
    case 3:
    {
        int const mask = LobbyDaemon::_instance->_config->_typeForFailedEventObjectLog;
        if (((1 << eventObject->EventId()) & mask) == 0)
            return;
        unsigned long const lastError = GetLastError();
        unsigned int const eventId = eventObject->EventId();
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1140,
                   L"[lobbydaemon], FailedEventObjectHandler, id: %d, object: %p, error:%d", eventId, eventObject,
                   lastError);
        break;
    }
    case 5:
    {
        int const mask = LobbyDaemon::_instance->_config->_typeForFailedEventObjectLog;
        if (((1 << eventObject->EventId()) & mask) == 0)
            return;
        unsigned long const lastError = GetLastError();
        unsigned int const eventId = eventObject->EventId();
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1148,
                   L"[lobbydaemon], FailedEventObjectHandler, id: %d, object: %p, error:%d", eventId, eventObject,
                   lastError);
        break;
    }
    default:
    {
        unsigned long const lastError = GetLastError();
        unsigned int const eventId = eventObject->EventId();
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1153,
                   L"[lobbydaemon], FailedEventObjectHandler, id: %d, object: %p, error:%d", eventId, eventObject,
                   lastError);
        break;
    }
    }
}

// 0x9b1b0
bool LobbyDaemon::initLog()
{
    LIFT_STUB(0x9b1b0);
}

// 0x9b300
bool LobbyDaemon::initialize()
{
    LIFT_STUB(0x9b300);
}

// 0x9d520
bool LobbyDaemon::initNetwork()
{
    LIFT_STUB(0x9d520);
}

// 0x9dca0
bool LobbyDaemon::onStart()
{
    LIFT_STUB(0x9dca0);
}

// 0x9e2f0
void LobbyDaemon::shutdown()
{
    LIFT_STUB(0x9e2f0);
}

// 0x9e5b0
bool LobbyDaemon::reload(wchar_t**, int)
{
    LIFT_STUB(0x9e5b0);
}

// LIFT: no LD RVA. vftable ??_7CoolDown@@6B@ slot 6 points to the folded 0x5a0a0 (xor eax, eax; ret).
unsigned int CoolDown::TimerClass() const
{
    return 0;
}

// LIFT: no LD RVA. vftable ??_7CoolDown@@6B@ slot 7 points to the folded 0x5a0a0 (xor eax, eax; ret).
unsigned long long CoolDown::TimerId() const
{
    return 0;
}

// 0x9ef40
// LIFT: the return value is as in the exe (0x9efdc): Start ok returns false, Start fail logs and returns true.
bool LobbyDaemon::cooldown()
{
    if (GCoolDown == nullptr)
        GCoolDown = ::new (Memory::_Manager[2]->Alloc(sizeof(CoolDown), L"LobbyDaemon.cpp", 2234)) CoolDown();
    // BUG: 0x9ef40 does not check GCoolDown after a failed Alloc. Start then runs with a null this.
    if (GCoolDown->Start(5000, 2 * _config->_lobbyTokenLifeTime))
        return false;
    Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 2238, L"[lobby], start cooldown fail");
    return true;
}

// 0x9f010
bool LobbyDaemon::startNPChannel()
{
    LIFT_STUB(0x9f010);
}

// 0x9f130
bool LobbyDaemon::setupNpScheduleInfo()
{
    LIFT_STUB(0x9f130);
}

// 0x9f240
#pragma comment(linker, "/INCLUDE:?FilterBannedWord@LobbyDaemon@@QEAA?AW4BannedWordFilterResult@1@PEB_W@Z")  // LIFT: keep until the caller is lifted (0x9f240)
LobbyDaemon::BannedWordFilterResult LobbyDaemon::FilterBannedWord(wchar_t const* word)
{
    if (word == nullptr || wcslen(word) == 0)
        return SWF_INVALID_PARAMETER;
    bool filtered = false;
    if (_bannedWordFilter == nullptr)
    {
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 2302, L"[lobby], filter word fail;not ready, word:%s", word);
        return SWF_ERROR;
    }
    if (!_bannedWordFilter->FilterName(word, &filtered))
    {
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 2307, L"[lobby], filter word fail;try fail, word:%s", word);
        return SWF_ERROR;
    }
    if (filtered)
    {
        Log::Write(Log::LT_DEBUG, L"LobbyDaemon.cpp", 2312, L"[lobby], forbidden word, name:%s", word);
        return SWF_FORBIDDEN;
    }
    return SWF_OK;
}

// 0x9f340
#pragma comment(linker, "/INCLUDE:?CheckServiceItemDataId@LobbyDaemon@@QEAA_NW4ServiceItemType@1@I@Z")  // LIFT: keep until the caller is lifted (0x9f340)
bool LobbyDaemon::CheckServiceItemDataId(ServiceItemType type, unsigned int itemDataId)
{
    if (_serviceItems == nullptr || static_cast<unsigned int>(type) > SERVICEITEMTYPE_RENAME_CHARACTER_BY_SYSTEM)
        return false;
    // LIFT: the exe inlines std::binary_search (VS2010 _Lower_bound loop). include/vs2010/algorithm has no
    // binary_search, so the loop is written here.
    typedef std::vector<unsigned int, StlAllocator<unsigned int, 2> > IdList;
    IdList const& idList = _serviceItems->_idList[type];
    IdList::const_iterator first = idList.begin();
    IdList::const_iterator const last = idList.end();
    long long count = last - first;
    while (count > 0)
    {
        long long const half = count / 2;
        if (first[half] < itemDataId)
        {
            first += half + 1;
            count -= half + 1;
        }
        else
        {
            count = half;
        }
    }
    return first != last && !(itemDataId < *first);
}

// 0x9f3c0
#pragma comment(linker, "/INCLUDE:?GetAddressStringWForLogs@LobbyDaemon@@SAPEB_WK@Z")  // LIFT: keep until the caller is lifted (0x9f3c0)
wchar_t const* LobbyDaemon::GetAddressStringWForLogs(unsigned long addr)
{
    if (_instance != nullptr)
    {
        LobbyConfig const* const config = _instance->_config;
        if (config != nullptr && !config->_allowClientIPAddressInLogs)
            addr = 0;
    }
    return Network::GetAddressStringW(addr);
}

// 0x9f3f0
bool ConcatenatePacket(Session const* session, Packet const* packet, bool& completed)
{
    completed = false;
    FragmentPacketConcatenater* concatenater = static_cast<FragmentPacketConcatenater*>(session->_concatenater);
    if (concatenater == nullptr)
    {
        FragmentPacketConcatenater c;
        concatenater = static_cast<FragmentPacketConcatenater*>(session->SetPacketConcatenater(&c));
    }
    // LIFT: the LD PDB gives Add (0x1530) 2 parameters. The shared header has a 3rd, unused parameter.
    // 0x9f4f8 does not set r9b, so false is given here.
    if (concatenater->Add(packet, &completed, false))
        return true;
    concatenater->Clear();
    return false;
}

// 0x9a1b0. C linkage, the signature is not in the public. wmain_bridge.c calls it.
// LIFT: LobbyDaemon::_instance is set in the constructor (0x9a230), not here.
extern "C" int __cdecl wmain(int argc, wchar_t** argv)
{
    LobbyDaemon daemonInstance;
    BloodDaemonMain(argc, argv);
    return 0;
}

// LIFT: LobbyDaemon.exe (2019 + PDB) has no ClientSideDaemonChannel symbol, so this function has no LD RVA.
// BloodLib Channel.cpp in lift_common emits the ClientSideDaemonChannel vftable, so the link needs a body.
// LobbyDaemon.cpp is the LD-only owner. The argument 0 means "no LD RVA". The stub does not return success.
bool ClientSideDaemonChannel::onAccept(Session const*)
{
    LIFT_STUB(0);
}
