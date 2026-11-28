// smartcoupondchannel.cpp: smartcoupondchannel.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "smartcoupondchannel.h"
#include "../BloodLib/include/Log.h"
#include "../BloodLib/include/AlertSender.h"
#include "LiftStub.h"

#pragma comment(linker, "/INCLUDE:?GenerateGameEventTid@@YA_KXZ")  // LIFT: dead-strip keep (no live caller yet)
#pragma comment(linker, "/INCLUDE:?OnAccept@SmartCouponSessionHandler@@UEBA_NPEBVSession@@@Z")  // LIFT: dead-strip keep (no live caller yet)

#define SMARTCOUPONDCHANNEL_FILE L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\gamedaemon\\..\\Shared\\SmartCoupondChannel.cpp"

// PDB: static data in UnityBuild12.obj (rva 0x101E120). ❓ The start value is not in the PDB. 0 is assumed.
static unsigned __int64 __gameEventSeed__ = 0;

// 0x27fe0
unsigned __int64 __cdecl GenerateGameEventTid(void)
{
    unsigned __int64 tid = static_cast<unsigned __int64>(
        InterlockedIncrement64(reinterpret_cast<volatile LONG64 *>(&__gameEventSeed__)));
    if (tid == 0)
    {
        // The counter wrapped around to 0. Skip 0: take the next value.
        unsigned __int64 next = static_cast<unsigned __int64>(
            InterlockedExchangeAdd64(reinterpret_cast<volatile LONG64 *>(&__gameEventSeed__), 1));
        Log::Write(Log::LT_ERROR, SMARTCOUPONDCHANNEL_FILE, 23, L"[gameevent], tid overflow");
        return next + 1;
    }
    return tid;
}

// 0x28030
bool __cdecl SmartCouponSessionHandler::OnAccept(::Session const *) const
{
    Log::Write(Log::LT_ERROR, SMARTCOUPONDCHANNEL_FILE, 33,
               L"== CRASH == [game-smart], cannot accept from smart (game connect to smart)");
    AlertSender::Write(SMARTCOUPONDCHANNEL_FILE, 33,
                       L"== CRASH == [game-smart], cannot accept from smart (game connect to smart)");
    return false;
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
