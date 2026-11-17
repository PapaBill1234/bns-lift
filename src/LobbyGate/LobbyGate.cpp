// LobbyGate.obj (LobbyGate PDB).
#include "LobbyGate.h"

#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wchar.h>
#include <new>

#include "AlertSender.h"
#include "BnsCommonConfigDefinition.h"
#include "Client.h"
#include "Console.h"
#include "ContentsRuleConfigDefinition.h"
#include "CrashHandler.h"
#include "LobbyDChannel.h"
#include "Log.h"
#include "LogFile.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "Network.h"
#include "PacketBufferHandler.h"
#include "PcCafeMileageFeverTimeScheduleList.h"
#include "PipeConsole.h"
#include "TimerQueue.h"
#include "WorldListManager.h"

static wchar_t const* const kFile = L"LobbyGate.cpp";

LobbyGate* LobbyGate::_instance = nullptr;

wchar_t const* LobbyGateReloadInvalidRestoreTimer::INVALID_REASON_STR[3] = {
    L"daemon config reload failed",
    L"contents rule config reload failed",
    L"bns common config reload failed",
};

// 0x12690
wchar_t const* LobbyGate::ShortName()
{
    return L"lobbygate";
}

// 0x126a0
wchar_t const* LobbyGate::Name()
{
    return L"LobbyGate";
}

// 0x126b0
wchar_t const* LobbyGate::ServiceName()
{
    return L"BnS lobby gate";
}

// 0x126c0
wchar_t const* LobbyGate::Descriptions()
{
    return L"Blade&Soul Lobby Gate";
}

// 0x126e0
ClientSessionHandler::~ClientSessionHandler()
{
}

// 0x12700
unsigned long long LobbyD::GetId()
{
    return _wid;
}

// 0x12710
LobbyD::~LobbyD()
{
}

// 0x12750
LobbyDSessionHandler::~LobbyDSessionHandler()
{
    // The member destructor of _connlock deletes the critical section.
}

// 0x12780
unsigned int LobbyGateReloadInvalidRestoreTimer::EventId() const
{
    return 130;
}

// 0x12790
bool LobbyGateReloadInvalidRestoreTimer::HandleEvent(EventContext* context, unsigned long numOfBytes)
{
    restoreInvalid();
    return true;
}

// 0x127a0
void LobbyGateReloadInvalidRestoreTimer::restoreInvalid()
{
    for (int i = 0; i < 3; ++i)
    {
        wchar_t const* const reason = INVALID_REASON_STR[i];
        PipeConsole* const pipeConsole = Daemon::Instance->pipeConsole;
        if (pipeConsole == nullptr)
            continue;
        // Inlined PipeConsole::SetInvalidInfo(reason, false).
        pipeConsole->_lock.Enter();
        for (PipeConsole::ItemNode* node = pipeConsole->_invalid._head._next; node != &pipeConsole->_invalid._tail;
             node = node->_next)
        {
            if (wcscmp(node->_key, reason) == 0)
            {
                node->_next->_prev = node->_prev;
                node->_prev->_next = node->_next;
                Memory::_Manager[2]->Free(node, L"source\\PipeConsole.cpp", 837);  // 0x12876: r8 = L"source\\PipeConsole.cpp", r9d = 837.
                break;
            }
        }
        pipeConsole->_lock.Leave();
    }
    _isExecuted = true;
}

// 0x13BB0 (scalar deleting dtor, folded with LobbyGateCooldownTimer)
LobbyGateReloadInvalidRestoreTimer::~LobbyGateReloadInvalidRestoreTimer()
{
}

// 0x21830
unsigned int LobbyGateReloadInvalidRestoreTimer::TimerClass() const
{
    return 2;
}

// 0x128b0
extern "C" int __cdecl wmain(int argc, wchar_t** argv)
{
    LobbyGate daemon;
    LobbyGate::_instance = &daemon;
    BloodDaemonMain(argc, argv);
    return 0;
}

// 0x129c0
LobbyGate::~LobbyGate()
{
    if (_config != nullptr)
    {
        Memory::_Manager[1]->Free(const_cast<LobbyGateConfig*>(_config), L"source\\DaemonConfig.cpp", 115);
        _config = nullptr;
    }
    if (BnsCommonConfig::ConfigNoReload != nullptr)
    {
        // BUG: 0x129c0 ConfigNoReload is not set to null after the free.
        Memory::_Manager[1]->Free(BnsCommonConfig::ConfigNoReload, L"source\\DaemonConfig.cpp", 115);
    }
    if (BnsCommonConfig::Config != nullptr)
    {
        Memory::_Manager[2]->Free(BnsCommonConfig::Config, L"..\\Shared\\BnsCommonConfigDefinition.cpp", 295);
        BnsCommonConfig::Config = nullptr;
    }
    while (BnsCommonConfig::ConfigOlds != nullptr)
    {
        BnsCommonConfig* const next = BnsCommonConfig::ConfigOlds->_NEXT;
        Memory::_Manager[2]->Free(BnsCommonConfig::ConfigOlds, L"..\\Shared\\BnsCommonConfigDefinition.cpp", 301);
        BnsCommonConfig::ConfigOlds = next;
    }
    ContentsRuleConfig::DestroyContentsRuleConfig();
    if (_logfile != nullptr)
    {
        _logfile->~LogFile();
        Memory::_Manager[2]->Free(_logfile, kFile, 130);
        _logfile = nullptr;
    }
    if (_restoreReloadTimer != nullptr)
    {
        _restoreReloadTimer->removeReferenceCount(kFile, 133);
        _restoreReloadTimer = nullptr;
    }
    // The member destructor of _broadcastCrypt calls BroadcastCrypt::clear.
}

// 0x12b60
void LobbyGate::PrintDependency()
{
    wprintf(L"packet lobbygate %d.0\n", 58);
    wprintf(L"packet lobby-lobbygate %d.0\n", 58);
    wprintf(L"lib xmlreader %s.0\n", L"15");
    wprintf(L"security cert %d.0\n", 6);
    wprintf(L"config bns-common-config %d\n", 2);
    // BUG: 0x12b60 the format has two %d but the call gives one argument.
    wprintf(L"config contents-rule-client %d.%d\n", 65);
    // BUG: 0x12b60 the format has two %d but the call gives one argument.
    wprintf(L"config contents-rule-server %d.%d\n", 72);
}

// 0x12bf0
void LobbyGate::AddJobTimer(unsigned long long gateKey, char reason)
{
    if (_config->_closeTimeout <= 0)
        return;
    void* const mem = Memory::_Manager[2]->Alloc(sizeof(ClientSessionTimerJob), kFile, 171);
    ClientSessionTimerJob* timer = nullptr;
    if (mem != nullptr)
    {
        timer = new (mem) ClientSessionTimerJob();
        timer->StartTick = 0;
        timer->next = nullptr;
        timer->prev = nullptr;
        timer->SlotIndex = -1;
        timer->InLtq = false;
        timer->_timerReason = static_cast<ClientSessionTimerJob::TimerReason>(reason);
        timer->_key = gateKey;
    }
    if (!GlobalTimerQueue->Add(_config->_closeTimeout, timer))
    {
        // BUG: 0x12bf0 timer is not checked for null.
        timer->removeReferenceCount(kFile, 173);
    }
}

// 0x12cd0
long LobbyGate::GetTimerInterval()
{
    return _config->_timerInterval;
}

// 0x12ce0
long LobbyGate::GetTimerMaxTime()
{
    return _config->_timerMaxTime;
}

// 0x12cf0
void LobbyGate::FailedEventObjectHandler(EventObject* eventObject)
{
    unsigned int const id = eventObject->EventId();
    if (id != 3 && id != 5)
        Log::Write(Log::LT_DEBUG, kFile, 196, L"[lobbygate], unknown event object id, id: %d, object: %p", id,
                   eventObject);
}

// 0x12d40
bool LobbyGate::initLog()
{
    _config = static_cast<LobbyGateConfig const*>(DaemonConfig::Load(
        LobbyGateConfig::_Def, 29, sizeof(LobbyGateConfig), L"lobbygate.config.xml", Daemon::Instance->ShortName(), false));
    if (_config == nullptr)
        return false;
    SetCurrentDirectoryW(_config->_rootPath);

    int dumpType = 261;
    if (_config->_dumpType < 0)
        return false;
    if (_config->_dumpType == 2)
        dumpType = 327;
    else if (_config->_dumpType > 2)
        return false;
    CrashHandler::Instance->_option = 7;
    CrashHandler::Instance->_dumpType = dumpType;
    CrashHandler::SetLogPath(_config->_logPath);

    void* const buffer = Memory::_Manager[2]->Alloc(sizeof(LogFile), kFile, 240);
    _logfile = buffer ? new (buffer) LogFile(_config->_logPath, 2, 0) : nullptr;  // LIFT: LTCG folded the args. initialize 0x21ef5 sets _filetype = 2. logType is not read.
    // BUG: 0x12d40 _logfile is not checked for null.
    _logfile->_enable[2] = false;
    Log::InitMedia(console);
    Log::InitMedia(_logfile);
    return true;
}

// 0x12e60
bool LobbyGate::setArgument(int argc, wchar_t const** argv)
{
    return false;
}

// 0x12e70
bool LobbyGate::initialize()
{
    if (!BnsCommonConfig::LoadBnsCommonConfig())
    {
        Log::Write(Log::LT_ERROR, kFile, 261, L"[scd], initialize, failed to initialize bns common config");
        Sleep(3000);
        return false;
    }
    if (!ContentsRuleConfig::LoadContentsRuleConfig())
    {
        Log::Write(Log::LT_ERROR, kFile, 268, L"[lobbygate], initialize, failed to initialize contents rule config");
        Sleep(3000);
        return false;
    }

    char buffer[1000];
    FILE* fp = nullptr;
    _time64(nullptr);
    int err = 0;
    if (_config->_certFile == nullptr)
        err = 2;
    else if (fopen_s(&fp, _config->_certFile, "rb") != 0 || fp == nullptr ||  // 0x12f3f: "rb"
             static_cast<long long>(fread(buffer, 1, sizeof(buffer), fp)) <= 0)
        err = 3;
    if (err != 0)
    {
        // BUG: 0x12e70 null dereference when err is 2 (certFile is null). The fp is not closed when err is 3.
        memset(_config->_certFile, 0, strlen(_config->_certFile));
        const_cast<LobbyGateConfig*>(_config)->_certFile = nullptr;
        Log::Write(Log::LT_ERROR, kFile, 290, L"Cannot execute (%d)", err);
        return false;
    }
    fclose(fp);

    void* mem = Memory::_Manager[2]->Alloc(sizeof(GateKeyManager), kFile, 308);
    if (mem != nullptr)
        memset(mem, 0, sizeof(GateKeyManager));
    _gatekeyManager = static_cast<GateKeyManager*>(mem);
    mem = Memory::_Manager[2]->Alloc(sizeof(ClientManager), kFile, 309);
    if (mem != nullptr)
        memset(mem, 0, sizeof(ClientManager));
    _clientManager = static_cast<ClientManager*>(mem);
    _gatekeyManager->Initialize(_config->_cliSessionHashCount);
    _clientManager->Initialize(_config->_cliSessionHashCount);

    // BUG: 0x12e70 the result of the next two Alloc calls is not checked.
    _worldListManger = static_cast<WorldListManager*>(Memory::_Manager[2]->Alloc(sizeof(WorldListManager), kFile, 314));
    _worldListManger->_worldList = nullptr;
    InitializeSRWLock(&_worldListManger->_srwLock);
    _pcCafeMileageFeverTimeScheduleListManager = static_cast<PcCafeMileageFeverTimeScheduleListManager*>(
        Memory::_Manager[2]->Alloc(sizeof(PcCafeMileageFeverTimeScheduleListManager), kFile, 317));
    _pcCafeMileageFeverTimeScheduleListManager->_scheduleList = nullptr;
    InitializeSRWLock(&_pcCafeMileageFeverTimeScheduleListManager->_srwLock);

    _sessionHandlerCount = 25;
    _sessionHandlerList = static_cast<SessionHandler**>(
        Memory::_Manager[2]->Alloc(sizeof(SessionHandler*) * _sessionHandlerCount, kFile, 325));
    return true;
}

// 0x13220
bool LobbyGate::initNetwork()
{
    if (!Network::Initialize(FailedEventObjectHandler, _config->_workerThreadCount))
    {
        Log::Write(Log::LT_ERROR, kFile, 337, L"[lobbygate], init network fail");
        return false;
    }
    if (!_broadcastCrypt.Initialize(BroadcastCrypt::BROADCAST_DAEMON, PacketCrypt::ALGORITHM_DEFAULT, 0))  // LIFT: LTCG folded all args into 0x23000. 0x13266 sets rcx only. The callee logs type 0.
    {
        Log::Write(Log::LT_ERROR, kFile, 346, L"[lobbygate], init broadcast crypt fail");
        return false;
    }

    void* mem = Memory::_Manager[1]->Alloc(sizeof(LobbyDSessionHandler), kFile, 353);
    LobbyDSessionHandler* lobbydHandler = nullptr;
    if (mem != nullptr)
    {
        lobbydHandler = new (mem) LobbyDSessionHandler();
        lobbydHandler->_lobbydHandlerList = LobbyLobbyGatePacketLobbyGateSideHandlerList;
        lobbydHandler->_lobbydFragmentHandlerList = LobbyLobbyGatePacketLobbyGateSideFragmentHandlerList;
        lobbydHandler->_lobbydPacketVer = 58;
    }
    mem = Memory::_Manager[1]->Alloc(sizeof(ClientSessionHandler), kFile, 361);
    ClientSessionHandler* const clientHandler = mem ? new (mem) ClientSessionHandler() : nullptr;
    _sessionHandlerList[1] = clientHandler;
    _sessionHandlerList[2] = lobbydHandler;

    // 0x13344: the binary puts an object with only a vftable on the stack and gives its address.
    TrustedPacketBufferHandler trustedBufferHandler;
    if (!Network::OpenPort(2, 0, 2, _sessionHandlerList[2], &trustedBufferHandler, 0, true, true, false))  // LIFT: LTCG removed the bools. 0x20500 sets _enableAccept and _enableRecv (0x207a3, 0x207a7). Port::Initialize sets _nagle = 0 (0x2588a).
    {
        Log::Write(Log::LT_ERROR, kFile, 369, L"[lobbygate], failed to open lobbyd channel port");  // 0x13370
        return false;
    }

    mem = Memory::_Manager[2]->Alloc(sizeof(LobbyD), kFile, 373);
    LobbyD* lobbyD = nullptr;
    if (mem != nullptr)
    {
        lobbyD = new (mem) LobbyD();
        lobbyD->_state = 0;
        lobbyD->_wid = 0;
    }
    _lobbyD = lobbyD;
    // 0x13408: r8d = _lobbyAddr (+0x4C), r9w = _lobbyPort (+0x50). LTCG changed the PDB prototype. IDA labels are wrong.
    // LIFT: waitAck true, portId 2 (0x21373), timeout 5000 (0x17bfe), reconnect false. LTCG folded these constants.
    if (!_lobbyD->Hello(static_cast<LobbyDSessionHandler*>(_sessionHandlerList[2]), true, 2, _config->_lobbyAddr,
                        static_cast<unsigned short>(_config->_lobbyPort), 5000, false))
    {
        Log::Write(Log::LT_ERROR, kFile, 375, L"[lobbygate], init lobbyd channel fail");
        return false;
    }
    Log::Write(Log::LT_NOTICE, kFile, 379, L"[lobbygate], init lobbyd channel ok");

    // 0x13470: the same vftable-only stack object.
    ClientPacketBufferHandler clientBufferHandler;
    if (!Network::OpenPort(1, static_cast<unsigned short>(_config->_clientPort), 0, _sessionHandlerList[1],
                           &clientBufferHandler, _config->_maxClientSession, true, true, false))  // LIFT: the same callee 0x20500. See above.
    {
        Log::Write(Log::LT_ERROR, kFile, 405, L"Cannot open Client port, %d",
                   static_cast<unsigned short>(_config->_clientPort));  // 0x134b6: the binary reads a word.
        return false;
    }

    AlertSender::_alertSender.init(_config->_alertSendAddress, ShortName(), 0, 1000);  // LIFT: LTCG folded the args. 0x19e5b: _worldId = 0. 0x19e61: _maxLogCount = 1000.

    // LIFT: LTCG removed portId. 0x20860 reads _port[0], thus port id 1.
    // BUG: 0x134d9 and 0x13500 read _maxIdleTime (int) as a word. Values above 65535 wrap.
    if (_config->_maxIdleTimeEnable &&
        !Network::SetMaxIdleTime(1, _config->_disconnectAfterIdleTime,
                                 static_cast<unsigned short>(_config->_maxIdleTime)))
    {
        Log::Write(Log::LT_ERROR, kFile, 415, L"Cannot Set Max Idle Time, %d", static_cast<unsigned short>(_config->_maxIdleTime));
        return false;
    }
    Log::Write(Log::LT_NOTICE, kFile, 420, L"[lobbygate], init network ok");
    return true;
}

// 0x13550
bool LobbyGate::onStart()
{
    Log::Write(Log::LT_NOTICE, kFile, 428, L"[lobbygate], ready");
    return true;
}

// 0x13580
void LobbyGate::shutdown()
{
    Network::Clear();
    if (_lobbyD != nullptr)
    {
        _lobbyD->RemoveSession(nullptr, false);
        _lobbyD->removeReferenceCount(kFile, 439);
        _lobbyD = nullptr;
    }
    if (_gatekeyManager != nullptr)
    {
        _gatekeyManager->Finalize();
        Memory::_Manager[2]->Free(_gatekeyManager, kFile, 445);
        _gatekeyManager = nullptr;
    }
    if (_clientManager != nullptr)
    {
        _clientManager->Finalize();
        Memory::_Manager[2]->Free(_clientManager, kFile, 451);
        _clientManager = nullptr;
    }
    if (_worldListManger != nullptr)
    {
        AcquireSRWLockExclusive(&_worldListManger->_srwLock);
        WorldList* const old = _worldListManger->_worldList;
        _worldListManger->_worldList = nullptr;
        ReleaseSRWLockExclusive(&_worldListManger->_srwLock);
        if (old != nullptr)
            old->removeReferenceCount(L"WorldListManager.cpp", 191);
        Memory::_Manager[2]->Free(_worldListManger, kFile, 455);
        _worldListManger = nullptr;
    }
    if (_pcCafeMileageFeverTimeScheduleListManager != nullptr)
    {
        AcquireSRWLockExclusive(&_pcCafeMileageFeverTimeScheduleListManager->_srwLock);
        PcCafeMileageFeverTimeScheduleList* const old = _pcCafeMileageFeverTimeScheduleListManager->_scheduleList;
        _pcCafeMileageFeverTimeScheduleListManager->_scheduleList = nullptr;
        ReleaseSRWLockExclusive(&_pcCafeMileageFeverTimeScheduleListManager->_srwLock);
        if (old != nullptr)
            old->removeReferenceCount(L"PcCafeMileageFeverTimeScheduleList.cpp", 98);
        Memory::_Manager[2]->Free(_pcCafeMileageFeverTimeScheduleListManager, kFile, 458);
        _pcCafeMileageFeverTimeScheduleListManager = nullptr;
    }
    if (_sessionHandlerList != nullptr)
    {
        Memory::_Manager[2]->Free(_sessionHandlerList, kFile, 461);
        _sessionHandlerList = nullptr;
    }
    AlertSender::_alertSender.fini();
    Log::Write(Log::LT_NOTICE, kFile, 465, L"[lobbygate], shutdown");
}

// 0x13770
bool LobbyGate::reload(wchar_t** argv, int argc)
{
    if (_restoreReloadTimer != nullptr)
    {
        Log::Write(Log::LT_DEBUG, kFile, 473, L"[lobbygate], remove reload timer");
        if (GlobalTimerQueue->Remove(_restoreReloadTimer))
        {
            LobbyGateReloadInvalidRestoreTimer* const restoreTimer =
                static_cast<LobbyGateReloadInvalidRestoreTimer*>(_restoreReloadTimer);
            if (!restoreTimer->_isExecuted)
                restoreTimer->restoreInvalid();
        }
        _restoreReloadTimer->removeReferenceCount(kFile, 478);
        _restoreReloadTimer = nullptr;
    }

    SYSTEMTIME tm;
    wchar_t timeStr[128];
    GetLocalTime(&tm);
    swprintf_s(timeStr, 128, L" at %04d-%02d-%02d %02d:%02d:%02d", tm.wYear, tm.wMonth, tm.wDay, tm.wHour, tm.wMinute,
               tm.wSecond);

    bool isChanged = false;
    Log::Write(Log::LT_NOTICE, kFile, 492, L"[lobbygate], bns common config reloading...");
    if (BnsCommonConfig::ReloadBnsCommonConfig(isChanged))
    {
        if (isChanged)
        {
            BnsCommonConfig::Dump();
            Log::Write(Log::LT_NOTICE, kFile, 511, L"[lobbygate], bns common config reload complete, done");
        }
        else
        {
            Log::Write(Log::LT_NOTICE, kFile, 506, L"[lobbygate], bns common config reload complete, not changed");
        }
        if (pipeConsole != nullptr)
            pipeConsole->SetRunningInfo(LobbyGateReloadInvalidRestoreTimer::INVALID_REASON_STR[2], nullptr);
        if (pipeConsole != nullptr)
            pipeConsole->SetRunningInfo(L"bns common config reload succeed", timeStr);
    }
    else
    {
        Log::Write(Log::LT_ERROR, kFile, 495, L"[scd], bns common config reload fail");
        PipeConsole* pc = pipeConsole;
        if (pc != nullptr)
        {
            // Inlined PipeConsole::SetRunningInfo(L"bns common config reload succeed", nullptr).
            pc->_lock.Enter();
            for (PipeConsole::ItemNode* node = pc->_running._head._next; node != &pc->_running._tail;
                 node = node->_next)
            {
                if (wcsncmp(node->_key, L"bns common config reload succeed", 33) == 0)
                {
                    node->_next->_prev = node->_prev;
                    node->_prev->_next = node->_next;
                    Memory::_Manager[2]->Free(node, L"source\\PipeConsole.cpp", 837);  // 0x13940: r8 = L"source\\PipeConsole.cpp", r9d = 837.
                    break;
                }
            }
            pc->_lock.Leave();
        }
        if (pipeConsole != nullptr)
            pipeConsole->SetRunningInfo(LobbyGateReloadInvalidRestoreTimer::INVALID_REASON_STR[2], timeStr);
        pc = pipeConsole;
        wchar_t const* const reason = LobbyGateReloadInvalidRestoreTimer::INVALID_REASON_STR[2];
        if (pc != nullptr)
        {
            // Inlined PipeConsole::SetInvalidInfo(reason, true).
            pc->_lock.Enter();
            PipeConsole::ItemNode* node = pc->_invalid._head._next;
            while (node != &pc->_invalid._tail && wcscmp(node->_key, reason) != 0)
                node = node->_next;
            if (node == &pc->_invalid._tail)
                PipeConsole::addNode(pc->_invalid, reason, L"");  // 0x139d6: valueString (0x1400627d8) is L"".
            pc->_lock.Leave();
        }
        void* const mem = Memory::_Manager[2]->Alloc(sizeof(LobbyGateReloadInvalidRestoreTimer), kFile, 499);
        Timer* const timer = mem ? new (mem) LobbyGateReloadInvalidRestoreTimer() : nullptr;
        _restoreReloadTimer = timer;
        GlobalTimerQueue->Add(60000, timer);
    }

    Log::Write(Log::LT_NOTICE, kFile, 519, L"[lobbygate], contents rule config reloading...");
    Log::Write(Log::LT_NOTICE, kFile, 532,
               L"[lobbygate], contents rule config reload complete(reload-count:%d), not changed",
               ContentsRuleConfig::ConfigReloadCount);
    if (pipeConsole != nullptr)
        pipeConsole->SetRunningInfo(LobbyGateReloadInvalidRestoreTimer::INVALID_REASON_STR[1], nullptr);
    if (pipeConsole != nullptr)
        pipeConsole->SetRunningInfo(L"contents rule config reload succeed", timeStr);
    return true;
}

// 0x13ba0
unsigned int LobbyGateCooldownTimer::EventId() const
{
    return 129;
}

// 0x13bb0
LobbyGateCooldownTimer::~LobbyGateCooldownTimer()
{
}

// 0x28750
unsigned int LobbyGateCooldownTimer::TimerClass() const
{
    return 1;
}

// 0x13bf0
bool LobbyGateCooldownTimer::HandleEvent(EventContext* context, unsigned long numOfBytes)
{
    LobbyGate* const lobbyGate = LobbyGate::_instance;
    _elapsed += 3000;
    int const remainClient = lobbyGate->_clientManager->DisconnectAll();
    int remainTime = 0;
    if (_completeDelay - _elapsed > 0)
        remainTime = _completeDelay - _elapsed;
    Log::Write(Log::LT_NOTICE, kFile, 593, L"[cooldown], report status, remain-client-count:%d, remain-time:%d(sec)",
               remainClient, remainTime);
    if (remainClient != 0 && _completeDelay >= _elapsed)
    {
        Daemon::Instance->GlobalTimerQueue->Add(3000, this);
        return true;
    }
    Daemon::Instance->setState(8);  // STATE_COOLDOWNED
    Log::Write(Log::LT_NOTICE, kFile, 599, L"[lobbygate], cooldown completed");
    removeReferenceCount(kFile, 600);
    return true;
}

// 0x13d20
bool LobbyGate::cooldown()
{
    Log::Write(Log::LT_NOTICE, kFile, 618, L"[lobbygate], cooldown started");
    Network::ClosePort(1);  // LIFT: LTCG removed portId. 0x207e0 reads _port[0].
    void* const mem = Memory::_Manager[2]->Alloc(sizeof(LobbyGateCooldownTimer), kFile, 624);
    Timer* const timer = mem ? new (mem) LobbyGateCooldownTimer(1000 * _config->_cooldownCompleteDelay) : nullptr;
    GlobalTimerQueue->Add(3000, timer);
    return false;
}

// 0x21830
unsigned long long LobbyGateReloadInvalidRestoreTimer::TimerId() const
{
    return 2;
}

// 0x27fc0
unsigned long long ClientSessionTimerJob::TimerId() const
{
    return 0;
}
// LIFT: empty body. vftable 0x7c030 slot 0 is the folded Timer scalar deleting destructor (0x13bb0).
// ❓ Not in index.tsv. The vtable needs a body.
ClientSessionTimerJob::~ClientSessionTimerJob()
{
}

// 0x27FC0 (folded with ReconnectTimer::TimerClass)
unsigned int ClientSessionTimerJob::TimerClass() const
{
    return 0;
}

// 0x28750
unsigned long long LobbyGateCooldownTimer::TimerId() const
{
    return 1;  // bytes at 0x28750: mov eax, 1; ret
}
