// smartcoupondchannel.cpp: smartcoupondchannel.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "smartcoupondchannel.h"
#include "LiftStub.h"

// 0x27fe0
unsigned __int64 __cdecl GenerateGameEventTid(void)
{
    LIFT_STUB(0x27fe0);
}

// 0x28030
bool __cdecl SmartCouponSessionHandler::OnAccept(::Session const *) const
{
    LIFT_STUB(0x28030);
}

// 0x28070
bool __cdecl SmartCouponSessionHandler::OnConnect(::Session const *, bool) const
{
    LIFT_STUB(0x28070);
}

// 0x282a0
void __cdecl SmartCouponSessionHandler::OnClose(::Session const *, bool) const
{
    LIFT_STUB(0x282a0);
}

// 0x28480
bool __cdecl SmartCouponSessionHandler::PacketHandler(::Session const *, ::Packet const *) const
{
    LIFT_STUB(0x28480);
}

// 0x284e0
void __cdecl SmartCoupondChannel::Initialize(short)
{
    LIFT_STUB(0x284e0);
}

// 0x28610
bool __cdecl SmartCoupondChannel::SendHello(void)
{
    LIFT_STUB(0x28610);
}

// 0x28780
bool __cdecl SmartCoupondChannelManager::Initialize(short, short *const)
{
    LIFT_STUB(0x28780);
}

// 0x28ad0
void __cdecl SmartCoupondChannelManager::Destroy(void)
{
    LIFT_STUB(0x28ad0);
}

// 0x28c40
::SmartCoupondChannel * __cdecl SmartCoupondChannelManager::acquire(unsigned int)
{
    LIFT_STUB(0x28c40);
}

// 0x28d10
bool __cdecl SmartCoupondChannelManager::Send(short, char const *, ...)
{
    LIFT_STUB(0x28d10);
}

// 0x28e00
bool __cdecl SmartCoupondChannelManager::LoadGameEventConfig(wchar_t const *)
{
    LIFT_STUB(0x28e00);
}

// 0x28eb0
bool __cdecl SmartCoupondChannelManager::SendGameEventByCharacterReq(short, int, ::id128 const &, unsigned __int64)
{
    LIFT_STUB(0x28eb0);
}

// 0x29170
bool __cdecl SmartCoupondChannelManager::checkGameEventConfig(int, ::id128 const &)
{
    LIFT_STUB(0x29170);
}
