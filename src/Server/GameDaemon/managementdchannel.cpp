// managementdchannel.cpp: managementdchannel.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "managementdchannel.h"
#include "LiftStub.h"

// 0x156b70
__cdecl ManagementdChannel::~ManagementdChannel(void)
{
    LIFT_STUB(0x156b70);
}

// 0x156b80
bool __cdecl ManagementdChannel::PacketHandler(::Session const *, ::Packet const *) const
{
    LIFT_STUB(0x156b80);
}

// 0x156be0
bool __cdecl ManagementdChannel::onCloseAll(void)
{
    LIFT_STUB(0x156be0);
}

// 0x156c10
bool __cdecl HandleGamedManagementd_HelloReq(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x156c10);
}

// 0x156d10
bool __cdecl HandleGamedManagementd_AnnounceNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x156d10);
}

// 0x156fd0
bool __cdecl HandleGamedManagementd_CharInfoReq(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x156fd0);
}

// 0x1572d0
bool __cdecl HandleGamedManagementd_SendHomeReq(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x1572d0);
}

// 0x1579a0
bool __cdecl HandleGamedManagementd_KickReq(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x1579a0);
}

// 0x157c90
bool __cdecl HandleGamedManagementd_DepositInGuildBankItemReq(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x157c90);
}

// 0x157fe0
bool __cdecl HandleGamedManagementd_WithdrawFromGuildBankItemReq(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x157fe0);
}

// 0x158340
bool __cdecl HandleGamedManagementd_RenameGuildReq(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x158340);
}

// 0x158640
bool __cdecl HandleGamedManagementd_BanishGuildMemberReq(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x158640);
}

// 0x158a10
bool __cdecl HandleGamedManagementd_DelegateGuildLeaderReq(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x158a10);
}

// 0x158df0
bool __cdecl HandleGamedManagementd_JoinGuildReq(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x158df0);
}

// 0x159320
bool __cdecl HandleGamedManagementd_UnloadCacheNotify(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x159320);
}
