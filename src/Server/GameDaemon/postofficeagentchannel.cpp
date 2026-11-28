// postofficeagentchannel.cpp: postofficeagentchannel.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "postofficeagentchannel.h"
#include "cachedaemonchannel.h"
#include "pc.h"
#include "LiftStub.h"
#include "AlertSender.h"
#include "Log.h"

// LIFT: per-exe path literal (lessons A6).
#define POSTOFFICEAGENTCHANNEL_FILE L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\gamedaemon\\PostOfficeAgentChannel.cpp"

// 0x1961b0
#pragma comment(linker, "/INCLUDE:?OnAccept@PostOfficeAgentSessionHandler@@UEBA_NPEBVSession@@@Z")  // LIFT: dead-strip keep (no live caller yet)
bool __cdecl PostOfficeAgentSessionHandler::OnAccept(::Session const *) const
{
    Log::Write(Log::LT_ERROR, POSTOFFICEAGENTCHANNEL_FILE, 24,
               L"== CRASH == [game-post], cannot accept from posta (game connect to posta)");
    AlertSender::Write(POSTOFFICEAGENTCHANNEL_FILE, 24,
                       L"== CRASH == [game-post], cannot accept from posta (game connect to posta)");
    return false;
}

// 0x1961f0
bool __cdecl PostOfficeAgentSessionHandler::OnConnect(::Session const *, bool) const
{
    LIFT_STUB(0x1961f0);
}

// 0x196420
void __cdecl PostOfficeAgentSessionHandler::OnClose(::Session const *, bool) const
{
    LIFT_STUB(0x196420);
}

// 0x196600
bool __cdecl PostOfficeAgentSessionHandler::PacketHandler(::Session const *, ::Packet const *) const
{
    LIFT_STUB(0x196600);
}

// 0x196660
void __cdecl PostOfficeAgentChannel::Initialize(short)
{
    LIFT_STUB(0x196660);
}

// 0x196790
bool __cdecl PostOfficeAgentChannel::SendHello(void)
{
    LIFT_STUB(0x196790);
}

// 0x196930
bool __cdecl HandlePostOfficeServiceCheckPostCapacityOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x196930);
}

// 0x1969d0
bool __cdecl HandlePostOfficeServiceCheckPostCapacityFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x1969d0);
}

// 0x196b60
bool __cdecl HandlePostOfficeServiceRetrieveCharacterInfoOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x196b60);
}

// 0x196cf0
bool __cdecl HandlePostOfficeServiceRetrieveCharacterInfoFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x196cf0);
}

// 0x196e80
bool __cdecl HandlePostOfficeServiceHelloOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x196e80);
}

// 0x196f80
bool __cdecl HandlePostOfficeServiceHelloFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x196f80);
}

// 0x197080
bool __cdecl PostOfficeAgentChannelManager::Initialize(short, short *const)
{
    LIFT_STUB(0x197080);
}

// 0x1973e0
void __cdecl PostOfficeAgentChannelManager::Destroy(void)
{
    LIFT_STUB(0x1973e0);
}

// 0x197550
::PostOfficeAgentChannel * __cdecl PostOfficeAgentChannelManager::acquire(unsigned int)
{
    LIFT_STUB(0x197550);
}

// 0x197620
bool __cdecl PostOfficeAgentChannelManager::Send(short, char const *, ...)
{
    LIFT_STUB(0x197620);
}

// 0x197710
bool __cdecl PostOfficeAgentChannelManager::Send(short, ::Packet const *)
{
    LIFT_STUB(0x197710);
}

// 0x197800
void __cdecl PostOfficeAgentChannelManager::SendDeliverPostReq(::Pc *, char, char, short, __int64, wchar_t *, wchar_t *, wchar_t *, ::CachedChannel::AttachedItem *const, short)
{
    LIFT_STUB(0x197800);
}
