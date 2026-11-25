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
#include "PacketUtil.h"
#include "SharedChannel.h"
#include "StringUtil.h"
#include <time.h>

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
bool HandleLobbyLobbyGate_GetCharacterInfoListReq(SharedChannel* channel, Packet const* packet)
{
    // LIFT: the PDB signature has SharedChannel*; the pseudocode types it as LobbyGateChannel* (LobbyGateChannel derives from SharedChannel).
    LobbyGateChannel* gate = static_cast<LobbyGateChannel*>(channel);
    short cmd = 0;
    unsigned long long clikey = 0;
    if (packet->Decompose("hq", &cmd, &clikey) == 0)
    {
        Log::Write(Log::LT_ERROR, L"LobbyLobbyGatePacketHandler.cpp", 699,
                   L"[lobby-gate], get character list fail; decompose fail, gate-wid:%d, cli-key:0x%I64X",
                   gate != nullptr ? static_cast<int>(gate->GetWid()) : 0, clikey);
        return true;
    }
    CliSession* cliSession = LobbyDaemon::_instance->_clisessionMgr->Select(clikey);
    if (cliSession == nullptr)
    {
        Log::Write(Log::LT_ERROR, L"LobbyLobbyGatePacketHandler.cpp", 705,
                   L"[lobby-gate], get character list fail; no such cli-session, gate-wid:%d, cli-key:0x%I64X",
                   gate != nullptr ? static_cast<int>(gate->GetWid()) : 0, clikey);
        gate->SendGetCharacterInfoListFail(clikey, 4);
        return true;
    }
    long long now = _time64(nullptr);
    FragmentPacket fp(36, "hiqqhCqohsbqQQi;");
    fp.packet.Allocate(&fp.composer);
    fp.Compose(3, clikey, now, LobbyDaemon::_instance->_timeZoneBias);
    CliSession::ErrCode err = cliSession->FetchCharacterInfoList(&fp);
    if (err != CliSession::ERR_OK)
    {
        Log::Write(Log::LT_ERROR, L"LobbyLobbyGatePacketHandler.cpp", 719,
                   L"[lobby-gate], get character list fail; fetch fail, error:%d, gate-wid:%d, cli-key:0x%I64X",
                   static_cast<int>(err), gate != nullptr ? static_cast<int>(gate->GetWid()) : 0, clikey);
        gate->SendGetCharacterInfoListFail(clikey, err == CliSession::ERR_INVALID_STATE ? 5 : 2);
        cliSession->removeReferenceCount(L"LobbyLobbyGatePacketHandler.cpp", 727);
        return true;
    }
    if (fp.packet.Splitter != nullptr)
        fp.packet.Splitter->Finalize(fp.packet.CurHeader);
    channel->Send(&fp.packet);
    Log::Write(Log::LT_DEBUG, L"LobbyLobbyGatePacketHandler.cpp", 734,
               L"[lobby-gate], get character info list ok, gate-wid:%d, cli-key:0x%I64X",
               gate != nullptr ? static_cast<int>(gate->GetWid()) : 0, clikey);
    cliSession->removeReferenceCount(L"LobbyLobbyGatePacketHandler.cpp", 736);
    return true;
}

// 0xc5630
bool HandleLobbyLobbyGate_GetCharacterInfoReq(SharedChannel* channel, Packet const* packet)
{
    // LIFT: the PDB signature has SharedChannel*; the pseudocode types it as LobbyGateChannel* (LobbyGateChannel derives from SharedChannel).
    LobbyGateChannel* gate = static_cast<LobbyGateChannel*>(channel);
    short cmd = 0;
    unsigned long long clikey = 0;
    id128 slotid = ID128_GUID_ZERO;  // LIFT: the original loads the zero id from ID128_GUID_ZERO.
    if (packet->Decompose("hqo", &cmd, &clikey, &slotid) == 0)
    {
        Log::Write(Log::LT_ERROR, L"LobbyLobbyGatePacketHandler.cpp", 756,
                   L"[lobby-gate], get character info fail; decompose fail, gate-wid:%d, cli-key:0x%I64X, slot-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
                   gate != nullptr ? static_cast<int>(gate->GetWid()) : 0, clikey,
                   slotid.guid.id1, slotid.guid.id2, slotid.guid.id3,
                   slotid.guid.id4[0], slotid.guid.id4[1], slotid.guid.id4[2], slotid.guid.id4[3],
                   slotid.guid.id4[4], slotid.guid.id4[5], slotid.guid.id4[6], slotid.guid.id4[7]);
        return true;
    }
    CliSession* cliSession = LobbyDaemon::_instance->_clisessionMgr->Select(clikey);
    if (cliSession == nullptr)
    {
        Log::Write(Log::LT_ERROR, L"LobbyLobbyGatePacketHandler.cpp", 763,
                   L"[lobby-gate], get character info fail; no such cli-session, gate-wid:%d, cli-key:0x%I64X, slot-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
                   gate != nullptr ? static_cast<int>(gate->GetWid()) : 0, clikey,
                   slotid.guid.id1, slotid.guid.id2, slotid.guid.id3,
                   slotid.guid.id4[0], slotid.guid.id4[1], slotid.guid.id4[2], slotid.guid.id4[3],
                   slotid.guid.id4[4], slotid.guid.id4[5], slotid.guid.id4[6], slotid.guid.id4[7]);
        gate->SendGetCharacterInfoFail(clikey, slotid, 4);
        return true;
    }
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    PacketComposer pcr;  // LIFT: inlined constructor (PDB PacketComposer(char const*, int))
    pcr.format = nullptr;
    pcr.len = 0;
    pcr.index = 0;
    pcr.SetFormat("hqqohsbqQQi", 0);
    p.Allocate();
    p.Compose(&pcr, 2, 39, clikey);
    // LIFT: the original puts the fetch fail block first (block order 0xc5630).
    if (!cliSession->FetchCharacterInfo(slotid, &p, &pcr))
    {
        int error = static_cast<int>(TLobbyError);
        Log::Write(Log::LT_ERROR, L"LobbyLobbyGatePacketHandler.cpp", 778,
                   L"[lobby-gate], get character info fail; fetch fail, error:%d, gate-wid:%d, cli-key:0x%I64X, slot-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
                   error, gate != nullptr ? static_cast<int>(gate->GetWid()) : 0, clikey,
                   slotid.guid.id1, slotid.guid.id2, slotid.guid.id3,
                   slotid.guid.id4[0], slotid.guid.id4[1], slotid.guid.id4[2], slotid.guid.id4[3],
                   slotid.guid.id4[4], slotid.guid.id4[5], slotid.guid.id4[6], slotid.guid.id4[7]);
        short reason = 2;
        switch (error)  // LIFT: HR 0xc5630 shows a switch (error - 5, then == 1).
        {
        case LOBERR_INVALID_SESSION_STATE:
            reason = 5;
            break;
        case LOBERR_NO_SUCH_CHARACTER:
            reason = 6;
            break;
        }
        gate->SendGetCharacterInfoFail(clikey, slotid, reason);
        // BUG: 0xc5630 the fetch fail path does not release the cli-session reference (Select adds one). Kept for parity.
    }
    else
    {
        channel->Send(&p);
        Log::Write(Log::LT_DEBUG, L"LobbyLobbyGatePacketHandler.cpp", 800,
                   L"[lobby-gate], get character info ok, gate-wid:%d, cli-key:0x%I64X, slot-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
                   gate != nullptr ? static_cast<int>(gate->GetWid()) : 0, clikey,
                   slotid.guid.id1, slotid.guid.id2, slotid.guid.id3,
                   slotid.guid.id4[0], slotid.guid.id4[1], slotid.guid.id4[2], slotid.guid.id4[3],
                   slotid.guid.id4[4], slotid.guid.id4[5], slotid.guid.id4[6], slotid.guid.id4[7]);
        cliSession->removeReferenceCount(L"LobbyLobbyGatePacketHandler.cpp", 802);
    }
    return true;
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
