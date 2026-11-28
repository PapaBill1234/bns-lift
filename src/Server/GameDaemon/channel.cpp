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
#pragma comment(linker, "/INCLUDE:?Send@ClientSideHashedDaemonChannel@@QEAA_N_KPEBDZZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?Send@ClientSideHashedDaemonChannel@@QEAA_N_KPEBVPacket@@@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?releaseSession@ClientSideHashedDaemonChannel@@MEAAXPEAVSession@@@Z")  // LIFT: dead-strip keep (no live caller yet)

static wchar_t const CHANNEL_FILE[] = L"source\\Channel.cpp";

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
// LIFT: log path (E16): the inlined assert calls Log::Write and AlertSender::Write.
void __cdecl ClientSideDaemonChannel::initialize(unsigned int, unsigned long, unsigned short)
{
    LIFT_STUB(0x69a740);
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
// LIFT: log path (E16): the inlined assert calls Log::Write and AlertSender::Write.
void __cdecl ClientSideHashedDaemonChannel::initialize(unsigned int, unsigned long, unsigned short)
{
    LIFT_STUB(0x69acc0);
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
// LIFT: log path (E16): the inlined assert calls Log::Write and AlertSender::Write.
bool __cdecl ServerSideDaemonChannel::Initialize(int)
{
    LIFT_STUB(0x69b0a0);
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
