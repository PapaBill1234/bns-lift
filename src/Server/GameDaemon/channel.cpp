// channel.cpp: channel.cpp (GameDaemon PDB, 2019 + PDB).
#include "channel_gd.h"
#include "../BloodLib/include/Channel.h"
#include "../BloodLib/include/Session.h"
#include "../BloodLib/include/Log.h"
#include "../BloodLib/include/AlertSender.h"
#include "../BloodLib/include/CrashHandler.h"
#include "../BloodLib/include/Memory.h"
#include "../BloodLib/include/MemoryManager.h"
#include "LiftStub.h"
#include <stdarg.h>

#pragma comment(linker, "/INCLUDE:?Send@DaemonChannel@@QEAA_NPEBDZZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Send@DaemonChannel@@QEAA_NPEBVPacket@@PEAVSession@@@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Send@DaemonChannel@@QEAA_NPEBVPacketList@@@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?initialize@ClientSideDaemonChannel@@IEAAXIKG@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Send@ClientSideHashedDaemonChannel@@QEAA_N_KPEBDZZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Send@ClientSideHashedDaemonChannel@@QEAA_N_KPEBVPacket@@@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?initialize@ClientSideHashedDaemonChannel@@IEAAXIKG@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?releaseSession@ClientSideHashedDaemonChannel@@MEAAXPEAVSession@@@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Initialize@ServerSideDaemonChannel@@QEAA_NH@Z")  // LIFT: dead-strip keep (no live caller yet)

static wchar_t const CHANNEL_FILE[] = L"source\\Channel.cpp";

// LIFT: inlined assert of BloodLib (Log, alert, crash). No PDB name. Same form as BloodLib/source/Channel.cpp.
#define CHANNEL_ASSERT_CRASH(line)                                                  \
    do                                                                              \
    {                                                                               \
        Log::Write(Log::LT_ERROR, CHANNEL_FILE, line, L"== CRASH == ASSERT CRASH"); \
        AlertSender::Write(CHANNEL_FILE, line, L"== CRASH == ASSERT CRASH");       \
        CrashHandler::MakeCrash("source\\Channel.cpp", line, L"");                  \
    } while (0)

// 0x69a3e0
bool DaemonChannel::Send(char const* format, ...)
{
    va_list args;
    va_start(args, format);
    Session* session = getSession();
    if (session == nullptr)
        return false;
    session->SendV(format, args);
    releaseSession(session);
    va_end(args);
    return true;
}

// 0x69a440
bool DaemonChannel::Send(Packet const* packet, Session* session)
{
    session->Send(packet);
    releaseSession(session);
    return true;
}

// 0x69a4c0
bool DaemonChannel::Send(PacketList const* packetList)
{
    Session* session = getSession();
    if (session == nullptr)
        return false;
    EnterCriticalSection(&session->_lock.CS);
    session->send(packetList->GetBufferList(), packetList->GetCount());
    LeaveCriticalSection(&session->_lock.CS);
    releaseSession(session);
    return true;
}

// 0x69a740
void __cdecl ClientSideDaemonChannel::initialize(unsigned int portId, unsigned long ip, unsigned short port)
{
    if (ip == 0 || port == 0 || session != nullptr)
        CHANNEL_ASSERT_CRASH(292);
    PortId = portId;
    ServerIp = ip;
    ServerPort = port;
}

// 0x69a7e0
bool __cdecl ClientSideDaemonChannel::initSession(bool *, bool, bool)
{
    LIFT_STUB(0x69a7e0);
}

// 0x69aa70
__cdecl ClientSideHashedDaemonChannel::~ClientSideHashedDaemonChannel(void)
{
    LIFT_STUB(0x69aa70);
}

// 0x69abf0
bool __cdecl ClientSideHashedDaemonChannel::Send(unsigned __int64 hashKey, char const* format, ...)
{
    va_list args;
    va_start(args, format);
    Session* session = getSession(hashKey);
    if (session == nullptr)
        return false;
    session->SendV(format, args);
    releaseSession(session);
    va_end(args);
    return true;
}

// 0x69ac40
bool __cdecl ClientSideHashedDaemonChannel::Send(unsigned __int64 hashKey, ::Packet const* packet)
{
    Session* session = getSession(hashKey);
    if (session == nullptr)
        return false;
    session->Send(packet);
    releaseSession(session);
    return true;
}

// 0x69acc0
// ❓ HR (0x69acc0) stores the constant 4 in _portId and moves ip and port one argument down. LTCG propagated
// the constant portId of the only caller. The source form below is the plain form.
void __cdecl ClientSideHashedDaemonChannel::initialize(unsigned int portId, unsigned long ip, unsigned short port)
{
    if (ip == 0 || port == 0 || _session != nullptr)
        CHANNEL_ASSERT_CRASH(484);
    _portId = portId;
    _serverIp = ip;
    _serverPort = port;
}

// 0x69ad60
bool __cdecl ClientSideHashedDaemonChannel::initSession(bool *, bool, bool)
{
    LIFT_STUB(0x69ad60);
}

// 0x69af30
::Session * __cdecl ClientSideHashedDaemonChannel::getSession(unsigned __int64)
{
    LIFT_STUB(0x69af30);
}

// 0x69afb0
void __cdecl ClientSideHashedDaemonChannel::releaseSession(::Session *session)
{
    if (session != nullptr)
        session->removeReferenceCount(CHANNEL_FILE, 581);
}

// 0x69b000
__cdecl ServerSideDaemonChannel::~ServerSideDaemonChannel(void)
{
    LIFT_STUB(0x69b000);
}

// 0x69b0a0
bool __cdecl ServerSideDaemonChannel::Initialize(int maxSession)
{
    if (maxSession <= 0 || MaxSession != 0 || SessionCount != 0 || SessionList != nullptr)
        CHANNEL_ASSERT_CRASH(619);
    MaxSession = maxSession;
    SessionCount = 0;
    LastSelected = 0;
    SessionList = static_cast<Session**>(Memory::_Manager[2]->AllocZero(sizeof(Session*) * MaxSession, CHANNEL_FILE, 625));
    UsedList = static_cast<bool*>(Memory::_Manager[2]->AllocZero(MaxSession, CHANNEL_FILE, 626));
    return true;
}

// 0x69b170
void __cdecl ServerSideDaemonChannel::CloseAll(void)
{
    LIFT_STUB(0x69b170);
}

// 0x69b260
bool __cdecl ServerSideDaemonChannel::onAccept(::Session const *)
{
    LIFT_STUB(0x69b260);
}

// 0x69b340
void __cdecl ServerSideDaemonChannel::onClose(::Session const *, bool, bool)
{
    LIFT_STUB(0x69b340);
}

// 0x69b4c0
::Session * __cdecl ServerSideDaemonChannel::getSession(void)
{
    LIFT_STUB(0x69b4c0);
}

// 0x69b670
void __cdecl ServerSideDaemonChannel::releaseSession(::Session *)
{
    LIFT_STUB(0x69b670);
}
