// clientsessionhandler.cpp: clientsessionhandler.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "clientsessionhandler.h"
#include "user.h"
#include "../BloodLib/include/Session.h"
#include <new>
#include "Memory.h"
#include "MemoryManager.h"
#include "Log.h"
#include "AlertSender.h"
#include "LiftStub.h"

#define CLIENTSESSIONHANDLER_FILE L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\gamedaemon\\ClientSessionHandler.cpp"

#pragma comment(linker, "/INCLUDE:?OnAccept@ClientSessionHandler@@UEBA_NPEBVSession@@@Z")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?OnConnect@ClientSessionHandler@@UEBA_NPEBVSession@@_N@Z")  // LIFT: dead-strip keep (no live caller yet)

// 0x7d6b0
void __cdecl ClientSessionHandler::OnCreated(::Session const *) const
{
    LIFT_STUB(0x7d6b0);
}

// 0x7d730
void __cdecl ClientSessionHandler::OnDestroyed(::Session const *) const
{
    LIFT_STUB(0x7d730);
}

// 0x7d7b0
bool __cdecl ClientSessionHandler::OnAccept(::Session const *session) const
{
    // ❓ The pseudocode drops the line argument of Alloc. The line below is not from the original.
    void *mem = Memory::_Manager[2]->Alloc(sizeof(::ClientSessionData), CLIENTSESSIONHANDLER_FILE, 57);
    ::ClientSessionData *data = mem != nullptr ? new (mem)::ClientSessionData() : nullptr;
    if (session != nullptr)
        const_cast< ::Session *>(session)->_extraData = data;
    return true;
}

// 0x7d810
bool __cdecl ClientSessionHandler::OnConnect(::Session const *session, bool firstConnected) const
{
    Log::Write(Log::LT_ERROR, CLIENTSESSIONHANDLER_FILE, 68, L"== CRASH == [client session handler], OnConnect; called ... wrong");
    AlertSender::Write(CLIENTSESSIONHANDLER_FILE, 68, L"== CRASH == [client session handler], OnConnect; called ... wrong");
    return false;
}

// 0x7d850
void __cdecl ClientSessionHandler::OnClose(::Session const *, bool) const
{
    LIFT_STUB(0x7d850);
}

// 0x7da70
bool __cdecl ClientSessionHandler::PacketHandler(::Session const *, ::Packet const *) const
{
    LIFT_STUB(0x7da70);
}

// 0x7e310
void __cdecl ClientSessionHandler::sendRightFailPacket(::Session const *, short) const
{
    LIFT_STUB(0x7e310);
}

// 0x7e530
unsigned short __cdecl ClientSessionHandler::getDataSize(short, char const *, unsigned __int64)
{
    LIFT_STUB(0x7e530);
}

// 0x7e6d0
void __cdecl ClientSessionHandler::logMaxRecvDisconnect(__int64, ::User *, __int64, __int64) const
{
    LIFT_STUB(0x7e6d0);
}
