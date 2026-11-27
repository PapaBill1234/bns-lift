// npservicechannel.cpp: npservicechannel.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "npservicechannel_gd.h"
#include "npchannel2.h"
#include "LiftStub.h"

// 0x16e840
void __cdecl NPGameServiceChannelCmdDispatcher(unsigned int, ::StsMsgLib::ECommand &)
{
    LIFT_STUB(0x16e840);
}

// 0x16e920
bool __cdecl NPServiceChannelManager::Initialize(unsigned int, unsigned long, unsigned short, long, long)
{
    LIFT_STUB(0x16e920);
}

// 0x16eb40
void __cdecl NPServiceChannelManager::CheckPing(void)
{
    LIFT_STUB(0x16eb40);
}

// 0x16ebc0
bool __cdecl NPServiceChannelManager::OnConnect(::NPChannel *, bool) const
{
    LIFT_STUB(0x16ebc0);
}

// 0x16ee90
bool __cdecl NPServiceChannelManager::OnClose(::NPChannel *, bool) const
{
    LIFT_STUB(0x16ee90);
}

// 0x16f020
bool __cdecl NPServiceChannelManager::HandleMessage(::NPChannel *, ::StsMsgLib::_StsMsg *, void *) const
{
    LIFT_STUB(0x16f020);
}

// 0x16f1b0
bool __cdecl NPGameServiceChannel::SendResponseGameGroupValidateGroupFail(unsigned int, wchar_t const *, int)
{
    LIFT_STUB(0x16f1b0);
}

// 0x16f240
bool __cdecl NPGameServiceChannel::SendResponseGameGroupGetChannelPropertyOk(unsigned int, wchar_t *, ::NPChatChannelType, int, int, int, int, int, int, int, int, ::StsMsgLib::_StsMsgResponseGameGroupGetChannelProperty::ETransportType, int)
{
    LIFT_STUB(0x16f240);
}

// 0x16f340
bool __cdecl NPGameServiceChannel::SendResponseGameGroupGetChannelPropertyFail(unsigned int, wchar_t const *, int)
{
    LIFT_STUB(0x16f340);
}

// 0x16f3e0
bool __cdecl NPGameServiceChannel::SendResponseGameGroupGroupInfoFail(unsigned int, wchar_t const *, int)
{
    LIFT_STUB(0x16f3e0);
}

// 0x16f470
void __cdecl NPGameTransaction::Expire(void)
{
    LIFT_STUB(0x16f470);
}
