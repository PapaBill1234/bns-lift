// chattingserverchannel.cpp: chattingserverchannel.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "chattingserverchannel.h"
#include "pc.h"
#include "LiftStub.h"

// 0x76ca0
__cdecl ChattingServerChannel::~ChattingServerChannel(void)
{
    LIFT_STUB(0x76ca0);
}

// 0x76cb0
bool __cdecl ChattingServerChannel::InitSession(void)
{
    LIFT_STUB(0x76cb0);
}

// 0x76df0
bool __cdecl ChattingServerChannel::PacketHandler(::Session const *, ::Packet const *) const
{
    LIFT_STUB(0x76df0);
}

// 0x76e80
bool __cdecl ChattingServerChannel::onConnect(::Session const *, bool)
{
    LIFT_STUB(0x76e80);
}

// 0x76f10
void __cdecl ChattingServerChannel::onClose(::Session const *, bool, bool)
{
    LIFT_STUB(0x76f10);
}

// 0x77050
bool __cdecl HandleChattingGame_A2G_AUTHENTICATE_USERNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x77050);
}

// 0x77250
bool __cdecl HandleChattingGame_A2G_PROTOCOL_VERSIONNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x77250);
}

// 0x772a0
bool __cdecl HandleChattingGame_A2G_AUTHENTICATE_GUILDNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x772a0);
}

// 0x776e0
void __cdecl ChattingServerChannel::SendServerId(::Session const *)
{
    LIFT_STUB(0x776e0);
}

// 0x77840
void __cdecl ChattingServerChannel::SendAuthenticateUserResult(__int64, wchar_t const *, int, __int64, __int64, __int64, int, int)
{
    LIFT_STUB(0x77840);
}

// 0x779f0
void __cdecl ChattingServerChannel::SendChattingAvailable(::Pc *)
{
    LIFT_STUB(0x779f0);
}

// 0x77a50
void __cdecl ChattingServerChannel::SendAuthenticateGuildResult(wchar_t const *, __int64, __int64, int, int)
{
    LIFT_STUB(0x77a50);
}
