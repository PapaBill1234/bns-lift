// LobbyDaemon.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "LobbyDaemon.h"
#include <algorithm>
#include <intrin.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <wchar.h>
#include "../../External/BannedWordFilter/BannedWordFilterLib.h"
#include "AccountInventoryChannel.h"
#include "Channel.h"
#include "CliSession.h"
#include "CliSessionManager.h"
#include "Console.h"
#include "ContentsRuleConfigDefinition.h"
#include "FragmentPacket.h"
#include "GameTimeSchedule.h"
#include "GameWorld.h"
#include "InfoGateChannel.h"
#include "GamedChannel.h"
#include "LobbyGateChannel.h"
#include "ManageChannel.h"
#include "PacketBufferHandler.h"
#include "PostOfficeChannel.h"
#include "LobbyCharacterDeletionScheduler.h"
#include "LobbyConfig.h"
#include "LobbyPerfMonitor.h"
#include "LobbyStats.h"
#include "LobbyTick.h"
#include "LiftStub.h"
#include "Log.h"
#include "Memory.h"
#include "Network.h"
#include "MemoryManager.h"
#include "Mileage.h"
#include "NPServiceChannel.h"
#include "Packet.h"
#include "PacketUtil.h"
#include "PipeConsole.h"
#include "RefCntObject.h"
#include "Session.h"
#include "AbandonChargeJob.h"
#include "ActivateGradeJob.h"
#include "AddSlotJob.h"
#include "AuctionBidJob.h"
#include "AuctionDeliverJob.h"
#include "AuctionEscrowJob.h"
#include "AuctionRollbackEscrowJob.h"
#include "BLDaemonInfo.h"
#include "BindCharacterSlotJob.h"
#include "CancelWaitCharacterDeletionJob.h"
#include "ChangeCharacterAppearanceJob.h"
#include "ChangeCharacterRaceJob.h"
#include "ChangeCharacterSexJob.h"
#include "ChangeUserNameJob.h"
#include "ContentsRuleConfigDefinition.h"
#include "CreateCharacterJob.h"
#include "CreateInitialUserNameJob.h"
#include "DeleteCharacterJob.h"
#include "DepositMileageJob.h"
#include "EndWaitGameWorldJob.h"
#include "EnterGameWorldJob.h"
#include "ExtendJumpingCharacterCreationQuotaJob.h"
#include "GameTimeSchedule.h"
#include "GetChargeInfoJob.h"
#include "GetGoodsCountJob.h"
#include "GetLobbyServiceItemJob.h"
#include "GiveupWaitGameWorldJob.h"
#include "InitCliSessionWlobbyTokenJob.h"
#include "InitCliSessionWnpTokenJob.h"
#include "KickJob.h"
#include "LeaveGameWorldJob.h"
#include "ListGoodsJob.h"
#include "ListLobbyServiceItemJob.h"
#include "LobbyCharacterDeletionScheduler.h"
#include "LobbyDB.h"
#include "LobbyJob.h"
#include "LobbyLocale.h"
#include "LobbyPerfMonitor.h"
#include "LobbyStats.h"
#include "LobbyTick.h"
#include "LobbyToken.h"
#include "LogoutInGameWorldJob.h"
#include "LogoutJob.h"
#include "Mileage.h"
#include "RecoverPcJob.h"
#include "RenameCharacterJob.h"
#include "SecondPasswordGetStatusJob.h"
#include "SecondPasswordIsVerifiedJob.h"
#include "SetupNpScheduleInfoJob.h"
#include "StartChargeJob.h"
#include "StartCliSessionWlobbyTokenJob.h"
#include "StartCliSessionWnpTokenJob.h"
#include "StopChargeJob.h"
#include "TakeAccountTimeBasedPlayRewardJob.h"
#include "TakeGoodsJob.h"
#include "TencentUIC.h"
#include "TryEnterGameWorldJob.h"
#include "Db.h"
#include "SysInfo.h"
#include "PerfCounterProvider.h"
#include "BnsCommonConfigDefinition.h"
#include <stdio.h>

LobbyDaemon* LobbyDaemon::_instance = nullptr;  // PDB static member (file-scope data in the original).
CoolDown* GCoolDown = nullptr;                  // PDB global.
LobbyObjPoolMemAllocator* GObjPoolMemAlloc = nullptr;  // PDB global, rva 0x2095D8. initialize (0x9b300) sets it.
ObjPoolTimer* GObjPoolTimer = nullptr;                 // PDB global, rva 0x2095E0. initialize (0x9b300) sets it.
BannedWordFilterMemoryAllocator BannedWordFilterMemoryAllocatorInstance;  // PDB global, rva 0x2056A0.
extern wchar_t const* LobbyErrorDesc[28];  // LIFT: PDB public LobbyErrorDesc. LobbyGamePacketHandler.cpp has the definition.

// LIFT: PDB globals of the LobbyDaemon perf counter sets. The values are from the exe data at each rva.
// ❓ The PDB module of these globals is not known. They are here because initialize (0x9b300) is the only user.
GUID const LobbyDaemonProviderGuid = {0x0374222d, 0x2e11, 0x4bb7, {0xa2, 0x51, 0xa3, 0xa5, 0x8c, 0x32, 0x5d, 0x1b}};  // rva 0x201B20

struct
{
    BL_PERF_COUNTERSET_INFO CounterSet;
    BL_PERF_COUNTER_INFO Counter0;
    BL_PERF_COUNTER_INFO Counter1;
} LobbyDaemonSystemInfo = {  // rva 0x2077F0
    {{0xcc569971, 0x85f5, 0x43f2, {0xb8, 0xc7, 0x74, 0xd8, 0x51, 0xdd, 0x57, 0xd9}},
     {0x0374222d, 0x2e11, 0x4bb7, {0xa2, 0x51, 0xa3, 0xa5, 0x8c, 0x32, 0x5d, 0x1b}}, 2, 2},
    {1, 0x10100, 0, 8, 100, 0, 0},
    {2, 0x10100, 0, 8, 100, 0, 0},
};

struct
{
    BL_PERF_COUNTERSET_INFO CounterSet;
    BL_PERF_COUNTER_INFO Counter0;
    BL_PERF_COUNTER_INFO Counter1;
    BL_PERF_COUNTER_INFO Counter2;
    BL_PERF_COUNTER_INFO Counter3;
    BL_PERF_COUNTER_INFO Counter4;
} LobbyDaemonWorldClusterInfo = {  // rva 0x207860
    {{0xefab60a9, 0xe55e, 0x4a49, {0xb5, 0xcf, 0x93, 0xb3, 0x50, 0x5c, 0xfc, 0xe2}},
     {0x0374222d, 0x2e11, 0x4bb7, {0xa2, 0x51, 0xa3, 0xa5, 0x8c, 0x32, 0x5d, 0x1b}}, 5, 2},
    {1, 0x10100, 0, 8, 100, 0, 0},
    {2, 0x10100, 0, 8, 100, 0, 0},
    {3, 0x10100, 0, 8, 100, 0, 0},
    {4, 0x10100, 0, 8, 100, 0, 0},
    {5, 0x10100, 0, 8, 100, 0, 0},
};

BL_PERF_COUNTERSET_INFO_LIST LobbyDaemonPerfCounterSetInfoList[2] = {  // rva 0x201B30
    {&LobbyDaemonSystemInfo.CounterSet, sizeof(LobbyDaemonSystemInfo)},
    {&LobbyDaemonWorldClusterInfo.CounterSet, sizeof(LobbyDaemonWorldClusterInfo)},
};
BL_PERF_COUNTERSET_INFO_LIST* LobbyDaemonPerfCounterSetInfoListPtr = LobbyDaemonPerfCounterSetInfoList;  // rva 0x201B50
int const LobbyDaemonPerfCounterSetTotal = 2;  // rva 0x201A74

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

#pragma comment(linker, "/INCLUDE:?GenerateClikey@@YA_KXZ")  // LIFT: keep until the caller is lifted (0x993c0); the readers of the stored pointer are still stubs.
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

#pragma comment(linker, "/INCLUDE:?GenerateJobid@@YA_KXZ")  // LIFT: keep until the caller is lifted (0x99410); the readers of the stored pointer are still stubs.
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

#pragma comment(linker, "/INCLUDE:?GenerateLobbyTokenkey@@YA_KXZ")  // LIFT: keep until the caller is lifted (0x99460); the readers of the stored pointer are still stubs.
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
    if (report != nullptr)
    {
        // LIFT: the original calls 0x2ef40 with _lgatechmgr. InfoGateChannelManager::Broadcast and the
        // LobbyGateChannelManager body are the same (folded). Both classes have the same layout (0x48).
        InfoGateChannelManager* const lgatechmgr = reinterpret_cast<InfoGateChannelManager*>(LobbyDaemon::_instance->_lgatechmgr);
        Packet const* const packet = report->GetPacket();
        if (packet == nullptr)
        {
            Log::Write(Log::LT_ERROR, L"LobbyGateChannel.cpp", 1049,
                       L"[lobby-gate], broadcast update-world-info-list-notify fail; invalid parameter");
        }
        else
        {
            if (!lgatechmgr->Broadcast(packet))
                Log::Write(Log::LT_ERROR, L"LobbyGateChannel.cpp", 1054,
                           L"[lobby-gate], broadcast update-world-info-list-notify fail; broadcast fail");
        }
        report->removeReferenceCount(L"LobbyDaemon.cpp", 212);
    }
    else
    {
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 215, L"[lobby], listen world reporter fail; null report");
    }
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
    if (!BnsCommonConfig::LoadBnsCommonConfig())
    {
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1212, L"[lobbydaemon], initialize, failed to initialize bns common config");
        Sleep(3000);
        return false;
    }
    if (!ContentsRuleConfig::LoadContentsRuleConfig())
    {
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1220,
                   L"[lobbydaemon], initialize, failed to initialize contents rule config");
        Sleep(3000);
        return false;
    }

    wchar_t wdsn[1024];
    char dsn[1024];
    char buffer[1008];  // LIFT: frame +0x13f0 to +0x17e0 of 0x9b300.
    FILE* fp = nullptr;
    int error;
    // LIFT: the HR converts buffer directly into wdsn. ❓ The original source can have a step between fread and the
    // conversion (the frame has dsn and a size local of 1024). That step is not in this build.
    char* const certFile = _config->_certFile;
    _time64(nullptr);
    if (certFile == nullptr)
    {
        error = 2;
    }
    else if (fopen_s(&fp, certFile, "rb") != 0 || fp == nullptr ||  // LIFT: mode "rb" at .rdata 0x1e18d0
             static_cast<int>(fread(buffer, 1, 1000, fp)) <= 0)
    {
        error = 3;  // BUG: 0x9b300 fp is not closed when fread fails.
    }
    else
    {
        error = 0;
        fclose(fp);
    }
    if (error != 0)
    {
        _config->ClearCertInfo();  // BUG: 0x9b300 strlen of a null pointer when error is 2.
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1241, L"[lobby], cannot execute, error:%d", error);
        return false;
    }
    wdsn[1023] = L'\0';
    MultiByteToWideChar(CP_ACP, 0, buffer, -1, wdsn, 1023);
    memset(dsn, 0, sizeof(dsn));

    if (!_config->_allowClientIPAddressInLogs)
    {
        Log::Write(Log::LT_DEBUG, L"LobbyDaemon.cpp", 1250, L"[lobbydd], client ip address in logs is not allowed");
        Daemon::Instance->allowClientIPAddressInLogs = false;
    }
    _config->Dump();
    BnsCommonConfig::Dump();
    ContentsRuleConfig::Dump();

    if (!_config->Check())
    {
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1262, L"[lobby], check configuration fail");
        return false;
    }
    if (!Db::Initialize(1, wdsn))
    {
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1280, L"[lobby], initialize db fail");
        return false;
    }
    Log::Write(Log::LT_NOTICE, L"LobbyDaemon.cpp", 1283, L"[lobby], initialize Lobby D/B ok");

    // Locale set.
    int const languagesLength = static_cast<int>(wcslen(_config->_supportLanguages)) + 1;
    wchar_t* const languages =
        static_cast<wchar_t*>(Memory::_Manager[2]->AllocZero(2 * languagesLength, L"LobbyDaemon.cpp", 1290));
    wcscpy_s(languages, languagesLength, _config->_supportLanguages);
    wchar_t seps[2];  // ❓ array size
    wcscpy(seps, L";");
    wchar_t* next = nullptr;
    int count = 0;
    for (wchar_t* token = wcstok_s(languages, seps, &next); token != nullptr; token = wcstok_s(nullptr, seps, &next))
        ++count;
    if (count <= 0)
    {
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1307, L"[lobby], initialize locale set fail; no support language exists");
        Memory::_Manager[2]->Free(languages, L"LobbyDaemon.cpp", 1308);
        return false;
    }
    _localeset.count = count;
    _localeset.locales =
        static_cast<LobbyLocale**>(Memory::_Manager[2]->AllocZero(sizeof(LobbyLocale*) * count, L"LobbyDaemon.cpp", 1313));
    wcscpy_s(languages, languagesLength, _config->_supportLanguages);
    next = nullptr;
    int index = 0;
    for (wchar_t* token = wcstok_s(languages, seps, &next); token != nullptr; token = wcstok_s(nullptr, seps, &next))
    {
        int const language = LobbyLocale::GetLanguageType(token);
        LobbyLocale* const locale = LobbyLocale::CreateLocale(language);
        if (locale == nullptr)
        {
            Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1324,
                       L"[lobby], initialize locale set fail; invalid locale parameter, language:%s", token);
            Memory::_Manager[2]->Free(languages, L"LobbyDaemon.cpp", 1325);
            return false;
        }
        _localeset.locales[index++] = locale;
        _localeset.languages[language] = true;
        Log::Write(Log::LT_NOTICE, L"LobbyDaemon.cpp", 1332, L"[lobby], create locale ok, languages:%s", token);
    }
    Memory::_Manager[2]->Free(languages, L"LobbyDaemon.cpp", 1336);
    Log::Write(Log::LT_NOTICE, L"LobbyDaemon.cpp", 1337, L"[lobby], initialize locale set ok");

    // Service items.
    _serviceItems = ::new (Memory::_Manager[2]->Alloc(sizeof(ServiceItems), L"LobbyDaemon.cpp", 1344)) ServiceItems();
    if (!_serviceItems->Add(SERVICEITEMTYPE_CHANGE_CHARACTER_APPEARANCE, _config->_itemDataIdsForChangeCharacterAppearance))
    {
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1348,
                   L"[lobby], initialize service items fail; add change-character-appearance item fail");
        return false;
    }
    if (!_serviceItems->Add(SERVICEITEMTYPE_RENAME_CHARACTER, _config->_itemDataIdsForRenameCharacter))
    {
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1354,
                   L"[lobby], initialize service items fail; add rename-character item fail");
        return false;
    }
    if (!_serviceItems->Add(SERVICEITEMTYPE_ADD_SLOT, _config->_itemDataIdsForAddSlot))
    {
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1360, L"[lobby], initialize service items fail; add add-slot item fail");
        return false;
    }
    if (!_serviceItems->Add(SERVICEITEMTYPE_CHANGE_USER_NAME, _config->_itemDataIdsForChangeUserName))
    {
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1366, L"[lobby], initialize service items fail; add change-user item fail");
        return false;
    }
    if (!_serviceItems->Add(SERVICEITEMTYPE_EXTEND_JUMPING_CHARACTER_CREATION_QUOTA,
                            _config->_itemDataIdsForExtendJumpingCharacterCreationQuota))
    {
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1372,
                   L"[lobby], initialize service items fail; add extend-jumping-character-creation-quota item fail");
        return false;
    }
    if (!_serviceItems->Add(SERVICEITEMTYPE_CHANGE_CHARACTER_SEX, _config->_itemDataIdsForChangeCharacterSex))
    {
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1378,
                   L"[lobby], initialize service items fail; add change-character-sex item fail");
        return false;
    }
    if (!_serviceItems->Add(SERVICEITEMTYPE_CHANGE_CHARACTER_RACE, _config->_itemDataIdsForChangeCharacterRace))
    {
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1384,
                   L"[lobby], initialize service items fail; add change-character-race item fail");
        return false;
    }
    if (!_serviceItems->Add(SERVICEITEMTYPE_RENAME_CHARACTER_BY_SYSTEM, _config->_itemDataIdsForRenameCharacterBySystem))
    {
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1390,
                   L"[lobby], initialize service items fail; add rename-character-by-sytem item fail");
        return false;
    }

    _tick = ::new (Memory::_Manager[2]->Alloc(sizeof(LobbyTick), L"LobbyDaemon.cpp", 1398)) LobbyTick(_config->_timerInterval);

    // Daemon list files.
    wchar_t lobbyGateListFilePath[260] = {0};
    wchar_t gamedListFilePath[260] = {0};
    wchar_t infoGateListFilePath[260] = {0};
    if (_wmakepath_s(lobbyGateListFilePath, 260, nullptr, _config->_configPath, L"lobby-gated-list.config.xml", nullptr) != 0)
    {
        Log::Write(L"LobbyDaemon.cpp", 1408, GetLastError(),
                   L"[lobby], failed to make lobby-gate list file path, configPath:%s, configFileName:%s",
                   _config->_configPath, L"lobby-gated-list.config.xml");
        return false;
    }
    if (_wmakepath_s(gamedListFilePath, 260, nullptr, _config->_configPath, L"gamed-list.config.xml", nullptr) != 0)
    {
        Log::Write(L"LobbyDaemon.cpp", 1412, GetLastError(),
                   L"[lobby], failed to make gamed list file path, configPath:%s, configFileName:%s", _config->_configPath,
                   L"gamed-list.config.xml");
        return false;
    }
    if (_wmakepath_s(infoGateListFilePath, 260, nullptr, _config->_configPath, L"infogate-list.config.xml", nullptr) != 0)
    {
        Log::Write(L"LobbyDaemon.cpp", 1416, GetLastError(),
                   L"[lobby], failed to make info-gate list file path, configPath:%s, configFileName:%s",
                   _config->_configPath, L"infogate-list.config.xml");
        return false;
    }
    _daemonInfoTable =
        ::new (Memory::_Manager[2]->Alloc(sizeof(BLDaemonInfoTable), L"LobbyDaemon.cpp", 1420)) BLDaemonInfoTable();
    if (!_daemonInfoTable->Load(lobbyGateListFilePath))
    {
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1422, L"[lobby], setup lobby-gate list fail, filePath:%s",
                   lobbyGateListFilePath);
        return false;
    }
    if (!_daemonInfoTable->Load(gamedListFilePath))
    {
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1426, L"[lobby], setup gamed list fail, filePath:%s", gamedListFilePath);
        return false;
    }
    if (_config->_useInfoGate && !_daemonInfoTable->Load(infoGateListFilePath))
    {
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1433, L"[lobby], setup info-gate list fail, filePath:%s",
                   infoGateListFilePath);
        return false;
    }

    // Perf monitor.
    if (_config->_usePerfMonitor)
    {
        if (!PerfCounterProvider::Initialize(LobbyDaemonProviderGuid, LobbyDaemonPerfCounterSetInfoList,
                                             LobbyDaemonPerfCounterSetTotal))
        {
            Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1447, L"[lobby] init perf counter provider fail");
            return false;
        }
        _systemPerfMon =
            ::new (Memory::_Manager[2]->Alloc(sizeof(SystemPerfMonitor), L"LobbyDaemon.cpp", 1451)) SystemPerfMonitor();
        if (!_systemPerfMon->Initialize())
        {
            _systemPerfMon->removeReferenceCount(L"LobbyDaemon.cpp", 1454);
            _systemPerfMon = nullptr;
            Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1456, L"[lobby], init system perf monitor fail");
            return false;
        }
    }

    // Game world registry and reporter.
    _gameWorldRegistry =
        ::new (Memory::_Manager[2]->Alloc(sizeof(GameWorldRegistry), L"LobbyDaemon.cpp", 1465)) GameWorldRegistry();
    if (!_gameWorldRegistry->Setup(static_cast<short>(_config->_reservedMinGameWorldWidRange),
                                   static_cast<short>(_config->_reservedMaxGameWorldWidRange)))
    {
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1467, L"[lobby], setup world registry fail");
        return false;
    }
    _gameWorldReporter =
        ::new (Memory::_Manager[2]->Alloc(sizeof(GameWorldReporter), L"LobbyDaemon.cpp", 1471)) GameWorldReporter();
    if (!_gameWorldReporter->Initialize(GameWorldReporterListener, _gameWorldRegistry, _config->_worldInfoListUpdatePeriod))
    {
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1473, L"[lobby], setup world reporter fail");
        return false;
    }
    _gameWorldReporter->WriteReport();

    // Banned word filter.
    _bannedWordFilter =
        ::new (Memory::_Manager[2]->Alloc(sizeof(BannedWordFilterLib), L"LobbyDaemon.cpp", 1483)) BannedWordFilterLib();
    if (!_bannedWordFilter->Initialize(&BannedWordFilterMemoryAllocatorInstance))
    {
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1485, L"[lobby], init banned-word-filter fail");
        return false;
    }
    Log::Write(Log::LT_NOTICE, L"LobbyDaemon.cpp", 1488, L"[lobby], init banned-word-filter ok");
    wchar_t filterFilePath[260] = {0};
    if (_wmakepath_s(filterFilePath, 260, nullptr, _config->_dataPath, L"BnSFilterName.txt", nullptr) != 0)
    {
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1492,
                   L"[lobby], failed to make banned word filter file path, dataPath:%s, filterFileName:%s", _config->_dataPath,
                   L"BnSFilterName.txt");
        return false;
    }
    if (!_bannedWordFilter->LoadNameFilterFile(filterFilePath))
    {
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1496, L"[lobby], load banned-word-filter resource fail, path:%s",
                   filterFilePath);
        return false;
    }
    Log::Write(Log::LT_NOTICE, L"LobbyDaemon.cpp", 1499, L"[lobby], load banned-word-filter resource ok, path:%s",
               filterFilePath);

    if (_config->_waitCharacterDeletion)
    {
        _charaterDeletionScheduler = ::new (Memory::_Manager[2]->Alloc(sizeof(LobbyCharacterDeletionScheduler),
                                                                      L"LobbyDaemon.cpp", 1506)) LobbyCharacterDeletionScheduler();
    }
    if (_config->_enableGameTimeSchedule)
    {
        _gameTimeScheduler =
            ::new (Memory::_Manager[2]->Alloc(sizeof(GameTimeScheduler), L"LobbyDaemon.cpp", 1512)) GameTimeScheduler();
        _gameTimeScheduler->Initialize();
    }
    if (_config->_exportLobbyStatsFilePeriod > 0)
    {
        _stats = ::new (Memory::_Manager[2]->Alloc(sizeof(LobbyStats), L"LobbyDaemon.cpp", 1521)) LobbyStats();
        if (!_stats->Initialize(_config->_exportLobbyStatsFilePath, L"lobby", L"stats", 1000 * _config->_exportLobbyStatsFilePeriod))
        {
            Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1523, L"[lobby], init lobby stats fail, path:%s, period:%d(sec)",
                       _config->_exportLobbyStatsFilePath, _config->_exportLobbyStatsFilePeriod);
            return false;
        }
        Log::Write(Log::LT_NOTICE, L"LobbyDaemon.cpp", 1526, L"[lobby], init lobby stats ok, path:%s, period:%d(sec)",
                   _config->_exportLobbyStatsFilePath, _config->_exportLobbyStatsFilePeriod);
    }

    // Object pools.
    GObjPoolMemAlloc =
        ::new (Memory::_Manager[1]->Alloc(sizeof(LobbyObjPoolMemAllocator), L"LobbyDaemon.cpp", 1533)) LobbyObjPoolMemAllocator();
    GObjPoolTimer = ::new (Memory::_Manager[2]->Alloc(sizeof(ObjPoolTimer), L"LobbyDaemon.cpp", 1534)) ObjPoolTimer();
    CliSession::_pool.Initialize(CliSession::_vtbl(), _config->_initCliSessionCount, _config->_reuseWaitTime);
    GObjPoolTimer->Add(&CliSession::_pool);
    InitCliSessionWnpTokenJob::_pool.Initialize(InitCliSessionWnpTokenJob::_vtbl(), _config->_initLobbyJobCount, _config->_reuseWaitTime);
    GObjPoolTimer->Add(&InitCliSessionWnpTokenJob::_pool);
    StartCliSessionWnpTokenJob::_pool.Initialize(StartCliSessionWnpTokenJob::_vtbl(), _config->_initLobbyJobCount, _config->_reuseWaitTime);
    GObjPoolTimer->Add(&StartCliSessionWnpTokenJob::_pool);
    LogoutJob::_pool.Initialize(LogoutJob::_vtbl(), _config->_initLobbyJobCount, _config->_reuseWaitTime);
    GObjPoolTimer->Add(&LogoutJob::_pool);
    KickJob::_pool.Initialize(KickJob::_vtbl(), _config->_initLobbyJobCount, _config->_reuseWaitTime);
    GObjPoolTimer->Add(&KickJob::_pool);
    CreateCharacterJob::_pool.Initialize(CreateCharacterJob::_vtbl(), _config->_initLobbyJobCount, _config->_reuseWaitTime);
    GObjPoolTimer->Add(&CreateCharacterJob::_pool);
    DeleteCharacterJob::_pool.Initialize(DeleteCharacterJob::_vtbl(), _config->_initLobbyJobCount, _config->_reuseWaitTime);
    GObjPoolTimer->Add(&DeleteCharacterJob::_pool);
    TryEnterGameWorldJob::_pool.Initialize(TryEnterGameWorldJob::_vtbl(), _config->_initLobbyJobCount, _config->_reuseWaitTime);
    GObjPoolTimer->Add(&TryEnterGameWorldJob::_pool);
    EnterGameWorldJob::_pool.Initialize(EnterGameWorldJob::_vtbl(), _config->_initLobbyJobCount, _config->_reuseWaitTime);
    GObjPoolTimer->Add(&EnterGameWorldJob::_pool);
    LeaveGameWorldJob::_pool.Initialize(LeaveGameWorldJob::_vtbl(), _config->_initLobbyJobCount, _config->_reuseWaitTime);
    GObjPoolTimer->Add(&LeaveGameWorldJob::_pool);
    LogoutInGameWorldJob::_pool.Initialize(LogoutInGameWorldJob::_vtbl(), _config->_initLobbyJobCount, _config->_reuseWaitTime);
    GObjPoolTimer->Add(&LogoutInGameWorldJob::_pool);
    InitCliSessionWlobbyTokenJob::_pool.Initialize(InitCliSessionWlobbyTokenJob::_vtbl(), _config->_initLobbyJobCount, _config->_reuseWaitTime);
    GObjPoolTimer->Add(&InitCliSessionWlobbyTokenJob::_pool);
    StartCliSessionWlobbyTokenJob::_pool.Initialize(StartCliSessionWlobbyTokenJob::_vtbl(), _config->_initLobbyJobCount, _config->_reuseWaitTime);
    GObjPoolTimer->Add(&StartCliSessionWlobbyTokenJob::_pool);
    EndWaitGameWorldJob::_pool.Initialize(EndWaitGameWorldJob::_vtbl(), _config->_initLobbyJobCount, _config->_reuseWaitTime);
    GObjPoolTimer->Add(&EndWaitGameWorldJob::_pool);
    GiveupWaitGameWorldJob::_pool.Initialize(GiveupWaitGameWorldJob::_vtbl(), _config->_initLobbyJobCount, _config->_reuseWaitTime);
    GObjPoolTimer->Add(&GiveupWaitGameWorldJob::_pool);
    CancelWaitCharacterDeletionJob::_pool.Initialize(CancelWaitCharacterDeletionJob::_vtbl(), _config->_initLobbyJobCount, _config->_reuseWaitTime);
    GObjPoolTimer->Add(&CancelWaitCharacterDeletionJob::_pool);
    AbandonChargeJob::_pool.Initialize(AbandonChargeJob::_vtbl(), _config->_initLobbyJobCount, _config->_reuseWaitTime);
    GObjPoolTimer->Add(&AbandonChargeJob::_pool);
    GetChargeInfoJob::_pool.Initialize(GetChargeInfoJob::_vtbl(), _config->_initLobbyJobCount, _config->_reuseWaitTime);
    GObjPoolTimer->Add(&GetChargeInfoJob::_pool);
    StartChargeJob::_pool.Initialize(StartChargeJob::_vtbl(), _config->_initLobbyJobCount, _config->_reuseWaitTime);
    GObjPoolTimer->Add(&StartChargeJob::_pool);
    StopChargeJob::_pool.Initialize(StopChargeJob::_vtbl(), _config->_initLobbyJobCount, _config->_reuseWaitTime);
    GObjPoolTimer->Add(&StopChargeJob::_pool);
    RecoverPcJob::_pool.Initialize(RecoverPcJob::_vtbl(), _config->_initLobbyJobCount, _config->_reuseWaitTime);
    GObjPoolTimer->Add(&RecoverPcJob::_pool);
    GetGoodsCountJob::_pool.Initialize(GetGoodsCountJob::_vtbl(), _config->_initLobbyJobCount, _config->_reuseWaitTime);
    GObjPoolTimer->Add(&GetGoodsCountJob::_pool);
    ListGoodsJob::_pool.Initialize(ListGoodsJob::_vtbl(), _config->_initLobbyJobCount, _config->_reuseWaitTime);
    GObjPoolTimer->Add(&ListGoodsJob::_pool);
    ListLobbyServiceItemJob::_pool.Initialize(ListLobbyServiceItemJob::_vtbl(), _config->_initLobbyJobCount, _config->_reuseWaitTime);
    GObjPoolTimer->Add(&ListLobbyServiceItemJob::_pool);
    TakeGoodsJob::_pool.Initialize(TakeGoodsJob::_vtbl(), _config->_initLobbyJobCount, _config->_reuseWaitTime);
    GObjPoolTimer->Add(&TakeGoodsJob::_pool);
    GetLobbyServiceItemJob::_pool.Initialize(GetLobbyServiceItemJob::_vtbl(), _config->_initLobbyJobCount, _config->_reuseWaitTime);
    GObjPoolTimer->Add(&GetLobbyServiceItemJob::_pool);
    ChangeCharacterAppearanceJob::_pool.Initialize(ChangeCharacterAppearanceJob::_vtbl(), _config->_initLobbyJobCount, _config->_reuseWaitTime);
    GObjPoolTimer->Add(&ChangeCharacterAppearanceJob::_pool);
    ChangeCharacterSexJob::_pool.Initialize(ChangeCharacterSexJob::_vtbl(), _config->_initLobbyJobCount, _config->_reuseWaitTime);
    GObjPoolTimer->Add(&ChangeCharacterSexJob::_pool);
    ChangeCharacterRaceJob::_pool.Initialize(ChangeCharacterRaceJob::_vtbl(), _config->_initLobbyJobCount, _config->_reuseWaitTime);
    GObjPoolTimer->Add(&ChangeCharacterRaceJob::_pool);
    RenameCharacterJob::_pool.Initialize(RenameCharacterJob::_vtbl(), _config->_initLobbyJobCount, _config->_reuseWaitTime);
    GObjPoolTimer->Add(&RenameCharacterJob::_pool);
    AddSlotJob::_pool.Initialize(AddSlotJob::_vtbl(), _config->_initLobbyJobCount, _config->_reuseWaitTime);
    GObjPoolTimer->Add(&AddSlotJob::_pool);
    SecondPasswordGetStatusJob::_pool.Initialize(SecondPasswordGetStatusJob::_vtbl(), _config->_initLobbyJobCount, _config->_reuseWaitTime);
    GObjPoolTimer->Add(&SecondPasswordGetStatusJob::_pool);
    SecondPasswordIsVerifiedJob::_pool.Initialize(SecondPasswordIsVerifiedJob::_vtbl(), _config->_initLobbyJobCount, _config->_reuseWaitTime);
    GObjPoolTimer->Add(&SecondPasswordIsVerifiedJob::_pool);
    CreateInitialUserNameJob::_pool.Initialize(CreateInitialUserNameJob::_vtbl(), _config->_initLobbyJobCount, _config->_reuseWaitTime);
    GObjPoolTimer->Add(&CreateInitialUserNameJob::_pool);
    ActivateGradeJob::_pool.Initialize(ActivateGradeJob::_vtbl(), _config->_initLobbyJobCount, _config->_reuseWaitTime);
    GObjPoolTimer->Add(&ActivateGradeJob::_pool);
    AuctionEscrowJob::_pool.Initialize(AuctionEscrowJob::_vtbl(), _config->_initLobbyJobCount, _config->_reuseWaitTime);
    GObjPoolTimer->Add(&AuctionEscrowJob::_pool);
    AuctionRollbackEscrowJob::_pool.Initialize(AuctionRollbackEscrowJob::_vtbl(), _config->_initLobbyJobCount, _config->_reuseWaitTime);
    GObjPoolTimer->Add(&AuctionRollbackEscrowJob::_pool);
    AuctionDeliverJob::_pool.Initialize(AuctionDeliverJob::_vtbl(), _config->_initLobbyJobCount, _config->_reuseWaitTime);
    GObjPoolTimer->Add(&AuctionDeliverJob::_pool);
    AuctionBidJob::_pool.Initialize(AuctionBidJob::_vtbl(), _config->_initLobbyJobCount, _config->_reuseWaitTime);
    GObjPoolTimer->Add(&AuctionBidJob::_pool);
    ChangeUserNameJob::_pool.Initialize(ChangeUserNameJob::_vtbl(), _config->_initLobbyJobCount, _config->_reuseWaitTime);
    GObjPoolTimer->Add(&ChangeUserNameJob::_pool);
    DepositMileageJob::_pool.Initialize(DepositMileageJob::_vtbl(), _config->_initLobbyJobCount, _config->_reuseWaitTime);
    GObjPoolTimer->Add(&DepositMileageJob::_pool);
    ExtendJumpingCharacterCreationQuotaJob::_pool.Initialize(ExtendJumpingCharacterCreationQuotaJob::_vtbl(), _config->_initLobbyJobCount, _config->_reuseWaitTime);
    GObjPoolTimer->Add(&ExtendJumpingCharacterCreationQuotaJob::_pool);
    UpgradeJumpingCharacterStateJob::_pool.Initialize(UpgradeJumpingCharacterStateJob::_vtbl(), _config->_initLobbyJobCount, _config->_reuseWaitTime);
    GObjPoolTimer->Add(&UpgradeJumpingCharacterStateJob::_pool);
    BindCharacterSlotJob::_pool.Initialize(BindCharacterSlotJob::_vtbl(), _config->_initLobbyJobCount, _config->_reuseWaitTime);
    GObjPoolTimer->Add(&BindCharacterSlotJob::_pool);
    SetupNpScheduleInfoJob::_pool.Initialize(SetupNpScheduleInfoJob::_vtbl(), _config->_initLobbyJobCount, _config->_reuseWaitTime);
    GObjPoolTimer->Add(&SetupNpScheduleInfoJob::_pool);
    TakeAccountTimeBasedPlayRewardJob::_pool.Initialize(TakeAccountTimeBasedPlayRewardJob::_vtbl(), _config->_initLobbyJobCount, _config->_reuseWaitTime);
    GObjPoolTimer->Add(&TakeAccountTimeBasedPlayRewardJob::_pool);
    // Cli-session manager, job manager and lobby-token desk.
    _clisessionMgr = ::new (Memory::_Manager[2]->Alloc(sizeof(CliSessionManager), L"LobbyDaemon.cpp", 1587))
        CliSessionManager(GenerateClikey);
    int accountHashCount = _config->_accountHashCount;
    if (accountHashCount <= 0)
        accountHashCount = 2 * SysInfo::ProcessorCount();
    int cliSessionHashCount = _config->_cliSessionHashCount;
    if (cliSessionHashCount <= 0)
        cliSessionHashCount = 2 * SysInfo::ProcessorCount();
    if (!_clisessionMgr->Initialize(cliSessionHashCount, accountHashCount,
                                    static_cast<short>(_config->_reservedMinLobbyGateWidRange),
                                    static_cast<short>(_config->_reservedMaxLobbyGateWidRange),
                                    static_cast<short>(_config->_reservedMinGameWorldWidRange),
                                    static_cast<short>(_config->_reservedMaxGameWorldWidRange)))
    {
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1594, L"[lobby], initialize cli-session manager fail");
        return false;
    }
    _jobMgr = ::new (Memory::_Manager[2]->Alloc(sizeof(LobbyJobManager), L"LobbyDaemon.cpp", 1603)) LobbyJobManager(GenerateJobid);
    int lobbyJobHashCount = _config->_lobbyJobHashCount;
    if (lobbyJobHashCount <= 0)
        lobbyJobHashCount = 2 * SysInfo::ProcessorCount();
    if (!_jobMgr->Initialize(lobbyJobHashCount))
    {
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1605, L"[lobby], initialize job manager fail");
        return false;
    }
    _tokenDesk = ::new (Memory::_Manager[2]->Alloc(sizeof(LobbyTokenDesk), L"LobbyDaemon.cpp", 1613))
        LobbyTokenDesk(_config->_lobbyTokenLifeTime, GenerateLobbyTokenkey);
    if (!_tick->Add(_tokenDesk))
    {
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1615, L"[lobby], add lobby-token-desk to tick fail");
        return false;
    }

    // Random store initialization schedule.
    int dbrtnLoadRandomStoreInitializationSchedule = 0;
    if (!LobbyDB::LoadRandomStoreInitializationSchedule(dbrtnLoadRandomStoreInitializationSchedule,
                                                        &_currentRandomStoreInitSchedule))
    {
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1625, L"[lobby], load random store initialization schedule fail, dbrtn:%d, ",
                   dbrtnLoadRandomStoreInitializationSchedule);
        return false;
    }
    Log::Write(Log::LT_DEBUG, L"LobbyDaemon.cpp", 1628,
               L"[lobby], load current random-store-initialization-schedule ok, schedule-number:%I64u, "
               L"slot-count-init-schedule-number:%I64u, premium-draw-count-init-schedule-number:%I64u",
               _currentRandomStoreInitSchedule.scheduleNumber, _currentRandomStoreInitSchedule.slotCountInitScheduleNumber,
               _currentRandomStoreInitSchedule.premiumDrawCountInitScheduleNumber);

    // Mileage.
    if (_config->_enableMileage)
    {
        _mileageManager = ::new (Memory::_Manager[2]->Alloc(sizeof(MileageManager), L"LobbyDaemon.cpp", 1632)) MileageManager();
        if (!_mileageManager->Initialize(_time64(nullptr) + 604800LL * _config->_mileageScheduleWeekCount))
        {
            int const lobbyError = static_cast<int>(TLobbyError);
            Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1637, L"[lobby], init mileage manager fail, error:%s",
                       static_cast<unsigned int>(lobbyError) >= 28 ? L"LOBERR_UNDEFINED" : LobbyErrorDesc[lobbyError]);
            return false;
        }
        Log::Write(Log::LT_NOTICE, L"LobbyDaemon.cpp", 1640, L"[lobby], init mileage promotion manager ok");
        _mileageInterimDepositTimer = ::new (Memory::_Manager[2]->Alloc(sizeof(MileageInterimDepositTimer),
                                                                       L"LobbyDaemon.cpp", 1643))
            MileageInterimDepositTimer(60000 * _config->_mileageDepositPeriod);
        if (!_tick->Add(_mileageInterimDepositTimer))
        {
            Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1646, L"[lobby], add mileage interim deposit timer to tick fail");
            return false;
        }
        Log::Write(Log::LT_NOTICE, L"LobbyDaemon.cpp", 1649, L"[lobby], setup mileage interim deposit timer ok");
    }

    // NP channel and Tencent UIC.
    if (!NPChannel::Setup(BnsCommonConfig::Config->_npProgramId, BnsCommonConfig::Config->_npGameCode))
    {
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1661, L"[lobby], setup np-channel failed");
        return false;
    }
    NPChannel::_recvCompletionLog = _config->_enableNpRecvCompletionLog;
    if (!_config->_tencentUICEnable)
        return true;
    _tencentUIC = ::new (Memory::_Manager[2]->Alloc(sizeof(TencentUIC), L"LobbyDaemon.cpp", 1669)) TencentUIC();
    if (_tencentUIC->Initialize(_config->_tencentUICConfigFile))
        return true;
    Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1671, L"[lobby], tencent uic initilize failed");
    return false;
}

// 0x9d520
bool LobbyDaemon::initNetwork()
{
    // LIFT: LTCG dropped the handler argument; 0x9d520 passes ecx = worker thread count only.
    if (!Network::Initialize(FailedEventObjectHandler, _config->_workerThreadCount))
    {
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1684, L"[lobbygate], init network fail");
        return false;
    }

    // LIFT: the OpenPort bools are constant (LTCG removed them): accept off, recv on, nagle off. OpenPort stores
    // _enableAccept = 0 and _enableRecv = 1 (SmartCouponDaemon::initNetwork passes the same values).
    {
        RawPacketBufferHandler pbh;
        int const maxNPSessionCount = _config->_maxNPSessionCount;
        unsigned int const maxSession = maxNPSessionCount <= 0 ? 0 : maxNPSessionCount + 1;
        if (!Network::OpenPort(2, 0, 2, NPChannel::_sessionHandler, &pbh, maxSession, false, true, false))
        {
            Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1702, L"[lobby], setup np port fail");
            return false;
        }
        Log::Write(Log::LT_NOTICE, L"LobbyDaemon.cpp", 1706, L"[lobby], setup np port ok");
    }

    if (_config->_useAccountInventory)
    {
        void* mem = Memory::_Manager[2]->Alloc(sizeof(AccountInventorySessionHandler), L"LobbyDaemon.cpp", 1714);
        _accountInventorySessionHandler = mem != nullptr ? ::new (mem) AccountInventorySessionHandler : nullptr;
        TrustedPacketBufferHandler pbh;
        // BUG: 0x9d520 the original tests _accountInventoryMaxSessionCount but uses _maxNPSessionCount + 1. Kept for parity.
        unsigned int const maxSession =
            _config->_accountInventoryMaxSessionCount <= 0 ? 0 : _config->_maxNPSessionCount + 1;
        if (!Network::OpenPort(3, 0, 2, _accountInventorySessionHandler, &pbh, maxSession, false, true, false))
        {
            Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1727, L"[lobby], setup account inventory port fail");
            return false;
        }
        Log::Write(Log::LT_NOTICE, L"LobbyDaemon.cpp", 1731, L"[lobby], setup account inventory port ok");
    }

    if (_config->_enableAuctionEscrowService)
    {
        void* mem = Memory::_Manager[2]->Alloc(sizeof(PostOfficeSessionHandler), L"LobbyDaemon.cpp", 1738);
        _postOfficeSessionHandler = mem != nullptr ? ::new (mem) PostOfficeSessionHandler : nullptr;
        TrustedPacketBufferHandler pbh;
        if (!Network::OpenPort(7, 0, 2, _postOfficeSessionHandler, &pbh, _config->_maxPostOfficeSessionCount, false, true,
                               false))
        {
            Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1744, L"[lobby], setup post-office port fail");
            return false;
        }
        Log::Write(Log::LT_NOTICE, L"LobbyDaemon.cpp", 1748, L"[lobby], setup post-office port ok");
    }

    {
        TrustedPacketBufferHandler pbh;
        void* mem = Memory::_Manager[2]->Alloc(sizeof(LobbyGateChannelManager), L"LobbyDaemon.cpp", 1756);
        _lgatechmgr = mem != nullptr ? ::new (mem) LobbyGateChannelManager : nullptr;
        // BUG: 0x9d520 the original does not check the manager for nullptr when the alloc fails (also below).
        if (!_lgatechmgr->Initialize(static_cast<short>(_config->_reservedMinLobbyGateWidRange),
                                     static_cast<short>(_config->_reservedMaxLobbyGateWidRange)))
        {
            Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1759,
                       L"[lobby], setup lobby-gate port fail; init lobby-gate channel manager fail");
            return false;
        }
        int const maxLobbyGateSessionCount = _config->_maxLobbyGateSessionCount;
        unsigned int const maxSession = maxLobbyGateSessionCount <= 0 ? 0 : maxLobbyGateSessionCount + 1;
        if (!Network::OpenPort(4, static_cast<unsigned short>(_config->_lobbyGatePort), 2, _lgatechmgr, &pbh, maxSession,
                               false, true, false))
        {
            Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1772, L"[lobby], setup lobby-gate port fail.");
            return false;
        }
        Log::Write(Log::LT_NOTICE, L"LobbyDaemon.cpp", 1776, L"[lobby], setup lobby-gate port ok");
    }

    if (_config->_useInfoGate)
    {
        TrustedPacketBufferHandler pbh;
        void* mem = Memory::_Manager[2]->Alloc(sizeof(InfoGateChannelManager), L"LobbyDaemon.cpp", 1783);
        _infogatechmgr = mem != nullptr ? ::new (mem) InfoGateChannelManager : nullptr;
        if (!_infogatechmgr->Initialize(static_cast<short>(_config->_reservedMinInfoGateWidRange),
                                        static_cast<short>(_config->_reservedMaxInfoGateWidRange)))
        {
            Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1786,
                       L"[lobby], setup info-gate port fail; init info-gate channel manager fail");
            return false;
        }
        int const maxInfoGateSessionCount = _config->_maxInfoGateSessionCount;
        unsigned int const maxSession = maxInfoGateSessionCount <= 0 ? 0 : maxInfoGateSessionCount + 1;
        if (!Network::OpenPort(6, static_cast<unsigned short>(_config->_infoGatePort), 2, _infogatechmgr, &pbh, maxSession,
                               false, true, false))
        {
            Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1799, L"[lobby], setup info-gate port fail.");
            return false;
        }
        Log::Write(Log::LT_NOTICE, L"LobbyDaemon.cpp", 1803, L"[lobby], setup info-gate port ok");
    }

    {
        TrustedPacketBufferHandler pbh;
        void* mem = Memory::_Manager[2]->Alloc(sizeof(GamedChannelManager), L"LobbyDaemon.cpp", 1811);
        _gamedchmgr = mem != nullptr ? ::new (mem) GamedChannelManager : nullptr;
        if (!_gamedchmgr->Initialize(static_cast<short>(_config->_reservedMinGameWorldWidRange),
                                     static_cast<short>(_config->_reservedMaxGameWorldWidRange)))
        {
            Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1814, L"[lobby], setup gamed port fail; init gamed channel manager fail");
            return false;
        }
        int const maxGameWorldSessionCount = _config->_maxGameWorldSessionCount;
        unsigned int const maxSession = maxGameWorldSessionCount <= 0 ? 0 : maxGameWorldSessionCount + 1;
        if (!Network::OpenPort(5, static_cast<unsigned short>(_config->_worldPort), 2, _gamedchmgr, &pbh, maxSession, false,
                               true, false))
        {
            Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1827, L"[lobby], setup gamed port fail.");
            return false;
        }
        Log::Write(Log::LT_NOTICE, L"LobbyDaemon.cpp", 1831, L"[lobby], setup gamed port ok");
    }

    {
        TrustedPacketBufferHandler pbh;
        void* mem = Memory::_Manager[2]->Alloc(sizeof(ManageSessionHandler), L"LobbyDaemon.cpp", 1839);
        _manageSessionHandler = mem != nullptr ? ::new (mem) ManageSessionHandler : nullptr;
        int const maxManageSessionCount = _config->_maxManageSessionCount;
        unsigned int const maxSession = maxManageSessionCount <= 0 ? 0 : maxManageSessionCount + 1;
        if (!Network::OpenPort(1, static_cast<unsigned short>(_config->_managePort), 3, _manageSessionHandler, &pbh,
                               maxSession, false, true, false))
        {
            Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1850, L"[lobby], setup manage port fail.");
            return false;
        }
        Log::Write(Log::LT_NOTICE, L"LobbyDaemon.cpp", 1854, L"[lobby], setup manage port ok");
    }

    Log::Write(Log::LT_NOTICE, L"LobbyDaemon.cpp", 1857, L"[lobby], init network ok");
    return true;
}

// 0x9dca0
bool LobbyDaemon::onStart()
{
    ObjPoolTimer::Start(1000);  // LIFT: LTCG put 1000 in the body of 0x62c80
    _tick->Start();
    if (_gameTimeScheduler != nullptr && !_gameTimeScheduler->Start())
    {
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1867, L"[lobby], start game-time-scheduler fail");
        return false;
    }
    if (!startNPChannel())
    {
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1875, L"[lobby], start np fail");
        return false;
    }
    if (ContentsRuleConfig::GetContentsRuleConfig()->GetUseTimeBasedPlaySchedule() && !setupNpScheduleInfo())
    {
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1886, L"[lobby], request time based play season schedule to np fail");
        return false;
    }
    if (_config->_useAccountInventory)
    {
        if (!Network::OpenPort(3))
        {
            Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1897, L"[lobby], start fail; open account-inventory port fail");
            return false;
        }
        _accountInventoryChannel = ::new (Memory::_Manager[2]->Alloc(sizeof(AccountInventoryChannel), L"LobbyDaemon.cpp", 1901))
            AccountInventoryChannel(_accountInventorySessionHandler);
        // BUG: 0x9dca0 does not check the channel after a failed Alloc. InitializeTransactionChannel then runs with a
        // null this. The same is true for the post-office channel below.
        if (!_accountInventoryChannel->InitializeTransactionChannel(LobbyDaemon::_instance->_config->_lobbyJobTransactionLifeTime))
        {
            Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1904, L"[lobby], start fail; init account inventory channel fail");
            return false;
        }
        _accountInventoryInitialConnectEvent.Make();
        if (!_accountInventoryChannel->Connect(1, 3, _config->_accountInventoryAddr,
                                               static_cast<unsigned short>(_config->_accountInventoryPort), 5, true))
        {
            Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1918, L"[lobby], start fail; connect to account inventory fail");
            return false;
        }
        if (_accountInventoryInitialConnectEvent.Event == nullptr
            || WaitForSingleObject(_accountInventoryInitialConnectEvent.Event, 5000) != WAIT_OBJECT_0)
        {
            Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1924, L"[lobby], start fail; initial connect to account inventory fail");
            return false;
        }
    }
    if (_config->_enableAuctionEscrowService)
    {
        if (!Network::OpenPort(7))
        {
            Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1934, L"[lobby], open post-office port fail");
            return false;
        }
        _postOfficeChannel = ::new (Memory::_Manager[2]->Alloc(sizeof(PostOfficeChannel), L"LobbyDaemon.cpp", 1938))
            PostOfficeChannel(_postOfficeSessionHandler);
        if (!_postOfficeChannel->InitializeTransactionChannel(LobbyDaemon::_instance->_config->_lobbyJobTransactionLifeTime))
        {
            Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1941, L"[lobby], start fail; init post-office channel fail");
            return false;
        }
        _postOfficeInitialConnectEvent.Make();
        if (!_postOfficeChannel->Connect(1, 7, _config->_postOfficeAddr,
                                         static_cast<unsigned short>(_config->_postOfficePort), 5, true))
        {
            Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1950, L"[lobby], start fail; connect to post-office fail");
            return false;
        }
        if (_postOfficeInitialConnectEvent.Event == nullptr
            || WaitForSingleObject(_postOfficeInitialConnectEvent.Event, 5000) != WAIT_OBJECT_0)
        {
            Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1955, L"[lobby], start fail; initial connect to post-office fail");
            return false;
        }
    }
    if (!Network::OpenPort(5))
    {
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1961, L"[lobby], open gamed port fail");
        return false;
    }
    if (!Network::OpenPort(4))
    {
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1966, L"[lobby], open lobby-gate port fail");
        return false;
    }
    if (_config->_useInfoGate && !Network::OpenPort(6))
    {
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1973, L"[lobby], open info-gate port fail");
        return false;
    }
    if (!Network::OpenPort(1))
    {
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1979, L"[lobby], open manage port fail");
        return false;
    }
    if (_gameWorldReporter != nullptr && !_gameWorldReporter->Start())
    {
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1984, L"[lobby], start world repoter fail");
        return false;
    }
    if (_charaterDeletionScheduler != nullptr
        && !_charaterDeletionScheduler->Start(1000 * _config->_characterDeletionSchedulerPeriod,
                                              _config->_characterDeletionSchedulerConcurrentProcessingCount))
    {
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 1991, L"[lobby], start character deletion scheduler fail");
        return false;
    }
    if (_config->_enableMileageBatchRetryOnStartup)
    {
        MileageBatchRetryDeposit* retry = ::new (Memory::_Manager[2]->Alloc(sizeof(MileageBatchRetryDeposit), L"LobbyDaemon.cpp", 1998))
            MileageBatchRetryDeposit(_config->_mileageBatchRetryConcurrentCount);
        if (!_tick->Add(retry))
            Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 2001, L"[lobby], start mileage deposit batch retry fail");
        // BUG: 0x9dca0 calls removeReferenceCount also when Alloc failed (null this).
        retry->removeReferenceCount(L"LobbyDaemon.cpp", 2002);
    }
    if (_stats != nullptr)
        _stats->Start();
    if (_systemPerfMon != nullptr && !_systemPerfMon->Start())
    {
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 2011, L"[lobby], start system perf monitor fail");
        return false;
    }
    Log::Write(Log::LT_NOTICE, L"LobbyDaemon.cpp", 2016, L"[lobby], ready");
    return true;
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
    if (!Network::OpenPort(2))
    {
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 2252, L"[lobby], start np channel fail; open np port fail");
        return false;
    }
    _npServchmgr = ::new (Memory::_Manager[2]->Alloc(sizeof(NPServiceChannelManager), L"LobbyDaemon.cpp", 2256))
        NPServiceChannelManager();
    _npInitialConnectEvent.Make();
    // BUG: 0x9f010 does not check _npServchmgr after a failed Alloc. Initialize then runs with a null this.
    if (!_npServchmgr->Initialize(2, _config->_npAddr, static_cast<unsigned short>(_config->_npPort), 5))
    {
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 2261,
                   L"[lobby], start np channel fail; initialize np service channel manager fail");
        return false;
    }
    if (_npInitialConnectEvent.Event == nullptr || WaitForSingleObject(_npInitialConnectEvent.Event, 5000) != WAIT_OBJECT_0)
    {
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 2266, L"[lobby], start np channel fail; wait initiali connect fail");
        return false;
    }
    Log::Write(Log::LT_NOTICE, L"LobbyDaemon.cpp", 2271, L"[lobby], start np channel ok");
    return true;
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
