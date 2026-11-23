// LobbyLobbyGatePacketHandler.obj (LobbyDaemon PDB, 2019 + PDB). A function with LIFT_STUB is not a lift.
#include <winsock2.h>
#include <windows.h>
#include "LobbyLobbyGatePacketHandler.h"
#include "CliSession.h"
#include "CliSessionManager.h"
#include "FragmentPacket.h"
#include "LiftStub.h"
#include "LobbyDaemon.h"
#include "LobbyGateChannel.h"
#include "Log.h"
#include "Packet.h"
#include "SharedChannel.h"

extern wchar_t const* LobbyErrorDesc[28];  // LIFT: PDB public LobbyErrorDesc (.data 0003:2032), defined in LobbyGamePacketHandler.cpp (placeholder, owner module not found).

// 0xc25c0
bool HandleLobbyLobbyGate_HelloReq(Session const*, Packet const*)
{
    LIFT_STUB(0xc25c0);
}

// 0xc2d90
bool HandleLobbyLobbyGate_InitSessionWithNPTokenReq(SharedChannel*, Packet const*)
{
    LIFT_STUB(0xc2d90);
}

// 0xc3380
bool HandleLobbyLobbyGate_StartSessionWithNPTokenReq(SharedChannel*, Packet const*)
{
    LIFT_STUB(0xc3380);
}

// 0xc3890
bool HandleLobbyLobbyGate_InitSessionWithLobbyTokenReq(SharedChannel*, Packet const*)
{
    LIFT_STUB(0xc3890);
}

// 0xc3e70
bool HandleLobbyLobbyGate_StartSessionWithLobbyTokenReq(SharedChannel*, Packet const*)
{
    LIFT_STUB(0xc3e70);
}

// 0xc4180
bool HandleLobbyLobbyGate_LostAnonymousConnectionNotify(SharedChannel*, Packet const*)
{
    LIFT_STUB(0xc4180);
}

// 0xc43f0
bool HandleLobbyLobbyGate_LostConnectionNotify(SharedChannel*, Packet const*)
{
    LIFT_STUB(0xc43f0);
}

// 0xc4650
bool HandleLobbyLobbyGate_LogoutNotify(SharedChannel*, Packet const*)
{
    LIFT_STUB(0xc4650);
}

// 0xc48b0
bool HandleLobbyLobbyGate_GetEnterWorldTokenReq(SharedChannel*, Packet const*)
{
    LIFT_STUB(0xc48b0);
}

// 0xc4df0
bool HandleLobbyLobbyGate_GetWaitInfoReq(SharedChannel*, Packet const*)
{
    LIFT_STUB(0xc4df0);
}

// 0xc5040
bool HandleLobbyLobbyGate_GiveupWaitReq(SharedChannel*, Packet const*)
{
    LIFT_STUB(0xc5040);
}

// 0xc5360
bool HandleLobbyLobbyGate_GetCharacterInfoListReq(SharedChannel*, Packet const*)
{
    LIFT_STUB(0xc5360);
}

// 0xc5630
bool HandleLobbyLobbyGate_GetCharacterInfoReq(SharedChannel*, Packet const*)
{
    LIFT_STUB(0xc5630);
}

// 0xc5ae0
#pragma comment(linker, "/INCLUDE:?HandleLobbyLobbyGate_CheckCharacterNameReq@@YA_NPEAVSharedChannel@@PEBVPacket@@@Z")  // LIFT: keep until the caller is lifted (0xc5ae0).
bool HandleLobbyLobbyGate_CheckCharacterNameReq(SharedChannel*, Packet const*)
{
    Log::Write(Log::LT_ERROR, L"LobbyLobbyGatePacketHandler.cpp", 807, L"[lobby-gate], check character name req fail; N/A");
    return true;
}

// 0xc5b10
bool HandleLobbyLobbyGate_CreateCharacterReq(SharedChannel*, Packet const*)
{
    LIFT_STUB(0xc5b10);
}

// 0xc6190
bool HandleLobbyLobbyGate_DeleteCharacterReq(SharedChannel*, Packet const*)
{
    LIFT_STUB(0xc6190);
}

// 0xc67e0
bool HandleLobbyLobbyGate_CancelWaitCharacterDeletionReq(SharedChannel*, Packet const*)
{
    LIFT_STUB(0xc67e0);
}

// 0xc6e30
bool HandleLobbyLobbyGate_RecoverCharacterReq(SharedChannel*, Packet const*)
{
    LIFT_STUB(0xc6e30);
}

// 0xc7540
bool HandleLobbyLobbyGate_BindCharacterSlotReq(SharedChannel*, Packet const*)
{
    LIFT_STUB(0xc7540);
}

// 0xc7af0
bool HandleLobbyLobbyGate_GetChargeInfoReq(SharedChannel*, Packet const*)
{
    LIFT_STUB(0xc7af0);
}

// 0xc7df0
bool HandleLobbyLobbyGate_GetGoodsCountReq(SharedChannel*, Packet const*)
{
    LIFT_STUB(0xc7df0);
}

// 0xc8080
bool HandleLobbyLobbyGate_ListGoodsReq(SharedChannel*, Packet const*)
{
    LIFT_STUB(0xc8080);
}

// 0xc83d0
bool HandleLobbyLobbyGate_TakeGoodsReq(SharedChannel*, Packet const*)
{
    LIFT_STUB(0xc83d0);
}

// 0xc85e0
bool HandleLobbyLobbyGate_ListLobbyServiceItemInfoReq(SharedChannel*, Packet const*)
{
    LIFT_STUB(0xc85e0);
}

// 0xc8860
bool HandleLobbyLobbyGate_GetLobbyServiceItemInfoReq(SharedChannel*, Packet const*)
{
    LIFT_STUB(0xc8860);
}

// 0xc8aa0
#pragma comment(linker, "/INCLUDE:?HandleLobbyLobbyGate_GetServiceEntryListReq@@YA_NPEAVSharedChannel@@PEBVPacket@@@Z")  // LIFT: keep until the caller is lifted (0xc8aa0).
bool HandleLobbyLobbyGate_GetServiceEntryListReq(SharedChannel* channel, Packet const* packet)
{
    // LIFT: the PDB signature has SharedChannel*; the pseudocode types it as LobbyGateChannel* (LobbyGateChannel derives from SharedChannel).
    LobbyGateChannel* gate = static_cast<LobbyGateChannel*>(channel);
    short cmd = 0;
    unsigned long long clikey = 0;
    if (packet->Decompose("hq", &cmd, &clikey) == 0)
    {
        Log::Write(Log::LT_ERROR, L"LobbyLobbyGatePacketHandler.cpp", 1359,
                   L"[lobby-gate], handle get service-entry list req fail; decompose fail, cli-key:0x%I64X", clikey);
        return true;
    }
    CliSession* cliSession = LobbyDaemon::_instance->_clisessionMgr->Select(clikey);
    if (cliSession == nullptr)
    {
        Log::Write(Log::LT_ERROR, L"LobbyLobbyGatePacketHandler.cpp", 1366,
                   L"[lobby-gate], handle get service-entry list req fail; no such cli-session, cli-key:0x%I64X", clikey);
        gate->SendGetServiceEntryListFail(clikey, 4);
        return true;
    }
    FragmentPacket fp(80, "hiqCqQqohq;");
    fp.packet.Allocate(&fp.composer);
    fp.Compose(1, clikey);
    if (!cliSession->FetchServiceEntryList(&fp))
    {
        unsigned int error = static_cast<unsigned int>(TLobbyError);
        short failCode;
        wchar_t const* desc;
        if (error == 5)
        {
            failCode = 5;
            desc = LobbyErrorDesc[error];
        }
        else
        {
            failCode = 2;
            desc = error >= 28 ? L"LOBERR_UNDEFINED" : LobbyErrorDesc[error];
        }
        Log::Write(Log::LT_ERROR, L"LobbyLobbyGatePacketHandler.cpp", 1390,
                   L"[lobby-gate], handle get service-entry list req fail; compose lsit fail, error:%s, cli-key:0x%I64X",
                   desc, clikey);
        gate->SendGetServiceEntryListFail(clikey, failCode);
        cliSession->removeReferenceCount(L"LobbyLobbyGatePacketHandler.cpp", 1393);
        return true;
    }
    if (fp.packet.Splitter != nullptr)
        fp.packet.Splitter->Finalize(fp.packet.CurHeader);
    channel->Send(&fp.packet);
    Log::Write(Log::LT_DEBUG, L"LobbyLobbyGatePacketHandler.cpp", 1401,
               L"[lobby-gate], handle get service-entry list req ok, cli-key:0x%I64X", clikey);
    cliSession->removeReferenceCount(L"LobbyLobbyGatePacketHandler.cpp", 1403);
    return true;
}

// 0xc8d00
bool HandleLobbyLobbyGate_ChangeCharacterAppearanceWithAccountInventoryItemReq(SharedChannel*, Packet const*)
{
    LIFT_STUB(0xc8d00);
}

// 0xc9300
bool HandleLobbyLobbyGate_ChangeCharacterSexWithAccountInventoryItemReq(SharedChannel*, Packet const*)
{
    LIFT_STUB(0xc9300);
}

// 0xc9940
bool HandleLobbyLobbyGate_ChangeCharacterRaceWithAccountInventoryItemReq(SharedChannel*, Packet const*)
{
    LIFT_STUB(0xc9940);
}

// 0xc9fc0
bool HandleLobbyLobbyGate_RenameCharacterWithAccountInventoryItemReq(SharedChannel*, Packet const*)
{
    LIFT_STUB(0xc9fc0);
}

// 0xca560
bool HandleLobbyLobbyGate_AddSlotWithAccountInventoryItemReq(SharedChannel*, Packet const*)
{
    LIFT_STUB(0xca560);
}

// 0xca8b0
bool HandleLobbyLobbyGate_ChangeUserNameWithAccountInventoryItemReq(SharedChannel*, Packet const*)
{
    LIFT_STUB(0xca8b0);
}

// 0xcac70
bool HandleLobbyLobbyGate_ExtendJumpingCharacterCreationQuotaWithAccountInventoryItemReq(SharedChannel*, Packet const*)
{
    LIFT_STUB(0xcac70);
}

// 0xcafd0
bool HandleLobbyLobbyGate_CreateInitialUserNameReq(SharedChannel*, Packet const*)
{
    LIFT_STUB(0xcafd0);
}

// 0xcb330
bool HandleLobbyLobbyGate_ActivateGradeReq(SharedChannel*, Packet const*)
{
    LIFT_STUB(0xcb330);
}
