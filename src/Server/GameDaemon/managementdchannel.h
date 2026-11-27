// managementdchannel.h: managementdchannel.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class ManagementdChannel
{
public:
    virtual __cdecl ~ManagementdChannel(void);  // 0x156b70
    virtual bool __cdecl PacketHandler(::Session const *, ::Packet const *) const;  // 0x156b80
protected:
    virtual bool __cdecl onCloseAll(void);  // 0x156be0
};

bool __cdecl HandleGamedManagementd_HelloReq(::Session const *, ::Packet const *);  // 0x156c10
bool __cdecl HandleGamedManagementd_AnnounceNotify(::Session const *, ::Packet const *);  // 0x156d10
bool __cdecl HandleGamedManagementd_CharInfoReq(::Session const *, ::Packet const *);  // 0x156fd0
bool __cdecl HandleGamedManagementd_SendHomeReq(::Session const *, ::Packet const *);  // 0x1572d0
bool __cdecl HandleGamedManagementd_KickReq(::Session const *, ::Packet const *);  // 0x1579a0
bool __cdecl HandleGamedManagementd_DepositInGuildBankItemReq(::Session const *, ::Packet const *);  // 0x157c90
bool __cdecl HandleGamedManagementd_WithdrawFromGuildBankItemReq(::Session const *, ::Packet const *);  // 0x157fe0
bool __cdecl HandleGamedManagementd_RenameGuildReq(::Session const *, ::Packet const *);  // 0x158340
bool __cdecl HandleGamedManagementd_BanishGuildMemberReq(::Session const *, ::Packet const *);  // 0x158640
bool __cdecl HandleGamedManagementd_DelegateGuildLeaderReq(::Session const *, ::Packet const *);  // 0x158a10
bool __cdecl HandleGamedManagementd_JoinGuildReq(::Session const *, ::Packet const *);  // 0x158df0
bool __cdecl HandleGamedManagementd_UnloadCacheNotify(::Session const *, ::Packet const *);  // 0x159320
