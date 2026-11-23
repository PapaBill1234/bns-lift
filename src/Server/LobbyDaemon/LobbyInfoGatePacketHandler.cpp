// LobbyInfoGatePacketHandler.obj (LobbyDaemon PDB, 2019 + PDB). Lifted: 0x56d40 to 0x57880.
// LIFT: LobbyInfoGatePacketLobbySideHandlerList (the handler table) is defined in LobbyInfoGatePacketLobbySideHandlerList.cpp.
#include "PlacementNew.h"
#include <winsock2.h>
#include <windows.h>
#include <string.h>
#include <wchar.h>
#include <new>
#include "LobbyInfoGatePacketHandler.h"
#include "BLDaemonInfo.h"
#include "CliSession.h"
#include "CliSessionManager.h"
#include "Connection.h"
#include "FragmentPacket.h"
#include "GameWorld.h"
#include "InfoGateChannel.h"
#include "LobbyDaemon.h"
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "Network.h"
#include "Packet.h"
#include "Session.h"
#include "StringUtil.h"

namespace
{
// LIFT: No PDB symbol. The binary uses the literal as the file string of every Log::Write and reference count call.
wchar_t const* const HANDLER_FILE = L"LobbyInfoGatePacketHandler.cpp";

// LIFT: BLDaemonInfo.h (card lift-lobbydaemon-20) owns the PDB layouts of BLDaemonID (0x8) and BLDaemonInfo (0x10).
// This card reads only the fields below, at the PDB offsets. The verify card replaces these two types with the header types.
struct BLDaemonIdLayout
{
    int kind;    // +0x0
    short wid;   // +0x4
};
struct BLDaemonInfoLayout
{
    BLDaemonIdLayout id;          // +0x0
    unsigned long internal_ipv4;  // +0x8
};
}

// 0x56d40
bool HandleLobbyInfoGate_HelloReq(Session const* session, Packet const* packet)
{
    unsigned long long sid = 0;
    short cmd = 0;
    short gateWid = 0;
    short packetVersion = 0;
    short internalPort = 0;
    short sendReason;

    if (packet->Decompose("hhhh", &cmd, &gateWid, &packetVersion, &internalPort) == 0)
    {
        if (session != nullptr)
            sid = session->_id;
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 30,
                   L"[infogate], handle hello-req fail; decompose fail, session-id:0x%I64X, gate-wid:%d, packet-version:%d, ip-address:%s, internal-port:%d",
                   sid, static_cast<int>(gateWid), static_cast<int>(packetVersion),
                   Network::GetAddressStringW(session->_connection->_ip), static_cast<int>(internalPort));
        return false;
    }

    if (packetVersion != 3)
    {
        if (session != nullptr)
            sid = session->_id;
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 36,
                   L"[infogate], handle hello-req fail; packet version mismatch, required-packet-version:%d, session-id:0x%I64X, gate-wid:%d, packet-version:%d, ip-address:%s, internal-port:%d",
                   3, sid, static_cast<int>(gateWid), static_cast<int>(packetVersion),
                   Network::GetAddressStringW(session->_connection->_ip), static_cast<int>(internalPort));
        sendReason = 10;
    }
    else
    {
        BLDaemonIdLayout id;
        id.kind = 4;
        id.wid = gateWid;
        BLDaemonInfoLayout const* info = reinterpret_cast<BLDaemonInfoLayout const*>(
            LobbyDaemon::_instance->_daemonInfoTable->Find(reinterpret_cast<BLDaemonID const&>(id)));
        if (info == nullptr)
        {
            if (session != nullptr)
                sid = session->_id;
            Log::Write(Log::LT_ERROR, HANDLER_FILE, 43,
                       L"[infogate], handle hello fail; unknown info-gate, session-id:0x%I64X, gate-wid:%d, packet-version:%d, ip-address:%s, internal-port:%d",
                       sid, static_cast<int>(gateWid), static_cast<int>(packetVersion),
                       Network::GetAddressStringW(session->_connection->_ip), static_cast<int>(internalPort));
            sendReason = 11;
        }
        else
        {
            unsigned long ip = session->_connection->_ip;
            if (ip != info->internal_ipv4)
            {
                wchar_t acc[15];
                wchar_t exp[15];
                wcscpy_s(acc, 15u, Network::GetAddressStringW(ip));
                wcscpy_s(exp, 15u, Network::GetAddressStringW(info->internal_ipv4));
                Log::Write(Log::LT_ERROR, HANDLER_FILE, 52,
                           L"[lobby-gate], handle hello fail; ip address mismatch, accept:%s, expect:%s, session-id:0x%I64X, gate-wid:%d, packet-version:%d, ip-address:%s, internal-port:%d",
                           acc, exp, session->_id, static_cast<int>(gateWid), static_cast<int>(packetVersion),
                           Network::GetAddressStringW(session->_connection->_ip), static_cast<int>(internalPort));
                sendReason = 12;
            }
            else
            {
                FragmentPacket fp(2, "hiChhQ;");
                fp.packet.Allocate(&fp.composer);
                if (!LobbyDaemon::_instance->_gameWorldRegistry->FetchWorldInfoListForInfoGate(&fp))
                {
                    Log::Write(Log::LT_ERROR, HANDLER_FILE, 62,
                               L"[infogate], handle hello fail; fetch world-info-list fail, session-id:0x%I64X, gate-wid:%d, packet-version:%d, ip-address:%s, internal-port:%d",
                               session->_id, static_cast<int>(gateWid), static_cast<int>(packetVersion),
                               Network::GetAddressStringW(session->_connection->_ip), static_cast<int>(internalPort));
                    session->Send("hh", 3, 2);
                    fp.packet.Clear();
                    return false;
                }
                if (fp.packet.Splitter != nullptr)
                    fp.packet.Splitter->Finalize(fp.packet.CurHeader);

                void* memory = Memory::_Manager[2]->Alloc(sizeof(InfoGateChannel), HANDLER_FILE, 70);
                InfoGateChannel* channel = memory != nullptr ? ::new (memory) InfoGateChannel() : nullptr;
                // BUG: 0x56d40 no null check after the Alloc. A failed Alloc gives a null call.
                if (!channel->Accept(gateWid, session))
                {
                    Log::Write(Log::LT_ERROR, HANDLER_FILE, 73,
                               L"[infogate], handle hello fail; accept session fail, session-id:0x%I64X, gate-wid:%d, packet-version:%d, ip-address:%s, internal-port:%d",
                               session->_id, static_cast<int>(gateWid), static_cast<int>(packetVersion),
                               Network::GetAddressStringW(session->_connection->_ip), static_cast<int>(internalPort));
                    session->Send("hh", 3, 2);
                    channel->removeReferenceCount(HANDLER_FILE, 75);
                    fp.packet.Clear();
                    return false;
                }
                if (LobbyDaemon::_instance->_infogatechmgr->Add(channel))
                {
                    session->Send(&fp.packet);
                    channel->StartBroadcast();
                    Log::Write(Log::LT_NOTICE, HANDLER_FILE, 95,
                               L"[infogate], handle hello ok, session-id:0x%I64X, gate-wid:%d, packet-version:%d, ip-address:%s, internal-port:%d",
                               session->_id, static_cast<int>(gateWid), static_cast<int>(packetVersion),
                               Network::GetAddressStringW(session->_connection->_ip), static_cast<int>(internalPort));
                    channel->removeReferenceCount(HANDLER_FILE, 97);
                    fp.packet.Clear();
                    return true;
                }
                Log::Write(Log::LT_ERROR, HANDLER_FILE, 80,
                           L"[infogate], handle hello fail; already exists; close both channel, session-id:0x%I64X, gate-wid:%d, packet-version:%d, ip-address:%s, internal-port:%d",
                           session->_id, static_cast<int>(gateWid), static_cast<int>(packetVersion),
                           Network::GetAddressStringW(session->_connection->_ip), static_cast<int>(internalPort));
                InfoGateChannel* existing = LobbyDaemon::_instance->_infogatechmgr->Acquire(gateWid);
                if (existing != nullptr)
                {
                    existing->Close();
                    existing->removeReferenceCount(HANDLER_FILE, 84);
                }
                session->Send("hh", 3, 14);
                channel->removeReferenceCount(HANDLER_FILE, 88);
                fp.packet.Clear();
                return false;
            }
        }
    }
    session->Send("hh", 3, static_cast<int>(sendReason));
    return false;
}

// 0x57350
bool HandleLobbyInfoGate_AuthTokenReq(SharedChannel* channel, Packet const* packet)
{
    InfoGateChannel* ch = static_cast<InfoGateChannel*>(channel);
    short cmd = 0;
    unsigned long long tid = 0;
    unsigned long long clikey = 0;
    id128 infoGateToken;
    // LIFT: the original copies ID128_ID_ZERO (rva 0x12D870); the loads are at 0x57373 and 0x57384.
    infoGateToken.id[0] = ID128_ID_ZERO.id[0];
    infoGateToken.id[1] = ID128_ID_ZERO.id[1];

    if (packet->Decompose("hqqo", &cmd, &tid, &clikey, &infoGateToken) == 0)
    {
        int wid = 0;  // LIFT: inlined InfoGateChannel::GetWid at the call site
        if (ch != nullptr)
            wid = ch->GetWid();
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 119,
                   L"[infogate], handle auth-token-req fail; decompose fail, gate-wid:%d, tid:0x%I64X, cli-key:0x%I64X, infogate-token:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
                   wid, tid, clikey, infoGateToken.guid.id1, infoGateToken.guid.id2, infoGateToken.guid.id3,
                   infoGateToken.guid.id4[0], infoGateToken.guid.id4[1], infoGateToken.guid.id4[2], infoGateToken.guid.id4[3],
                   infoGateToken.guid.id4[4], infoGateToken.guid.id4[5], infoGateToken.guid.id4[6], infoGateToken.guid.id4[7]);
        ch->SendAuthTokenFail(tid, clikey, 2);
        return true;
    }

    CliSession* cliSession = LobbyDaemon::_instance->_clisessionMgr->Select(clikey);
    if (cliSession == nullptr)
    {
        int wid = 0;  // LIFT: inlined InfoGateChannel::GetWid at the call site
        if (ch != nullptr)
            wid = ch->GetWid();
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 127,
                   L"[infogate], handle auth-token-req fail; no such cli-session, gate-wid:%d, tid:0x%I64X, cli-key:0x%I64X, infogate-token:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
                   wid, tid, clikey, infoGateToken.guid.id1, infoGateToken.guid.id2, infoGateToken.guid.id3,
                   infoGateToken.guid.id4[0], infoGateToken.guid.id4[1], infoGateToken.guid.id4[2], infoGateToken.guid.id4[3],
                   infoGateToken.guid.id4[4], infoGateToken.guid.id4[5], infoGateToken.guid.id4[6], infoGateToken.guid.id4[7]);
        ch->SendAuthTokenFail(tid, clikey, 4);
        return true;
    }

    if (!(infoGateToken.id[0] == cliSession->_infoGateToken.id[0] && infoGateToken.id[1] == cliSession->_infoGateToken.id[1]))
    {
        // LIFT: The original prints the required infogate token of the cli-session first in this log line (an auth secret).
        // This lift writes zero in its place. The format string and the argument count are the same.
        int wid = 0;  // LIFT: inlined InfoGateChannel::GetWid at the call site
        if (ch != nullptr)
            wid = ch->GetWid();
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 136,
                   L"[infogate], handle auth-token-req fail; token mismatch, required-infogate-token:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, gate-wid:%d, tid:0x%I64X, cli-key:0x%I64X, infogate-token:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
                   0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
                   wid, tid, clikey, infoGateToken.guid.id1, infoGateToken.guid.id2, infoGateToken.guid.id3,
                   infoGateToken.guid.id4[0], infoGateToken.guid.id4[1], infoGateToken.guid.id4[2], infoGateToken.guid.id4[3],
                   infoGateToken.guid.id4[4], infoGateToken.guid.id4[5], infoGateToken.guid.id4[6], infoGateToken.guid.id4[7]);
        ch->SendAuthTokenFail(tid, clikey, 15);
        cliSession->removeReferenceCount(HANDLER_FILE, 138);
        return true;
    }

    ch->SendAuthTokenOk(tid, clikey, cliSession->_acb._userid);
    int wid = 0;  // LIFT: inlined InfoGateChannel::GetWid at the call site
    if (ch != nullptr)
        wid = ch->GetWid();
    // LIFT: The original prints the valid infogate token here. It equals the session secret, so this lift writes zero.
    Log::Write(Log::LT_DEBUG, HANDLER_FILE, 144,
               L"[infogate], handle auth-token-req ok, gate-wid:%d, tid:0x%I64X, cli-key:0x%I64X, infogate-token:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
               wid, tid, clikey, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u);
    cliSession->removeReferenceCount(HANDLER_FILE, 149);
    return true;
}

// 0x57880
bool HandleLobbyInfoGate_GetWorldInfoListReq(SharedChannel* channel, Packet const* packet)
{
    InfoGateChannel* ch = static_cast<InfoGateChannel*>(channel);
    short cmd = 0;

    if (packet->Decompose("h", &cmd) == 0)
    {
        int wid = 0;  // LIFT: inlined InfoGateChannel::GetWid at the call site
        if (ch != nullptr)
            wid = ch->GetWid();
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 164,
                   L"[infogate], handle get-world-info-list-req fail; decompose fail, gate-wid:%d", wid);
        // LIFT: The callee does not use the reason (it composes 2). The original passes a stale register.
        ch->SendGetWorldInfoListFail(2);
        return true;
    }

    FragmentPacket fp(8, "hiChhQ;");
    fp.packet.Allocate(&fp.composer);
    if (LobbyDaemon::_instance->_gameWorldRegistry->FetchWorldInfoListForInfoGate(&fp))
    {
        if (fp.packet.Splitter != nullptr)
            fp.packet.Splitter->Finalize(fp.packet.CurHeader);
        channel->Send(&fp.packet);
        int wid = 0;  // LIFT: inlined InfoGateChannel::GetWid at the call site
        if (ch != nullptr)
            wid = ch->GetWid();
        Log::Write(Log::LT_DEBUG, HANDLER_FILE, 183,
                   L"[infogate], handle get-world-info-list-req ok, gate-wid:%d", wid);
    }
    else
    {
        int wid = 0;  // LIFT: inlined InfoGateChannel::GetWid at the call site
        if (ch != nullptr)
            wid = ch->GetWid();
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 174,
                   L"[infogate], handle get-world-info-list-req fail; fetch world-info-list fail, gate-wid:%d", wid);
        ch->SendGetWorldInfoListFail(2);
    }
    fp.packet.Clear();
    return true;
}
