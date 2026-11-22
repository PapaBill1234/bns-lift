// LobbyInfoGatePacketHandler.obj (LobbyDaemon PDB, 2019 + PDB). Lifted: 0x56d40 to 0x57880.
// LIFT: LobbyInfoGatePacketLobbySideHandlerList (the handler table) is defined in InfoGateChannel.cpp with null entries.
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

// LIFT: keep until the handler table is filled (the table in InfoGateChannel.cpp still holds null entries)
#pragma comment(linker, "/INCLUDE:?HandleLobbyInfoGate_HelloReq@@YA_NPEBVSession@@PEBVPacket@@@Z")  // LIFT: keep until the caller is lifted (0x56d40)
#pragma comment(linker, "/INCLUDE:?HandleLobbyInfoGate_AuthTokenReq@@YA_NPEAVSharedChannel@@PEBVPacket@@@Z")  // LIFT: keep until the caller is lifted (0x57350)
#pragma comment(linker, "/INCLUDE:?HandleLobbyInfoGate_GetWorldInfoListReq@@YA_NPEAVSharedChannel@@PEBVPacket@@@Z")  // LIFT: keep until the caller is lifted (0x57880)

namespace
{
// LIFT: No PDB symbol. The binary uses the literal as the file string of every Log::Write and reference count call.
wchar_t const* const HANDLER_FILE = L"LobbyInfoGatePacketHandler.cpp";

// LIFT: Lift helper, not in any PDB. The binary inlines this at each use: the gate wid of the raw channel, or 0.
__forceinline int GateWid(SharedChannel* channel)
{
    int wid = 0;
    if (channel != nullptr)
    {
        if (channel->_rawChannel != nullptr)
            wid = static_cast<short>(channel->_rawChannel->GetId());
    }
    return wid;
}
}

// 0x56d40
bool HandleLobbyInfoGate_HelloReq(Session const* session, Packet const* packet)
{
    unsigned long long sid = 0;
    // LIFT: The PDB local names are lost. The Decompose format "hhhh" reads: command, gate wid, packet version, internal port.
    short command = 0;
    short gateWid = 0;
    short packetVersion = 0;
    short internalPort = 0;
    short sendReason;

    if (packet->Decompose("hhhh", &command, &gateWid, &packetVersion, &internalPort) == 0)
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
        BLDaemonID id;
        id.kind = 4;
        id.wid = gateWid;
        BLDaemonInfo const* info = LobbyDaemon::_instance->_daemonInfoTable->Find(id);
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
                wchar_t accept[15];
                wchar_t expect[15];
                wcscpy_s(accept, 15u, Network::GetAddressStringW(ip));
                wcscpy_s(expect, 15u, Network::GetAddressStringW(info->internal_ipv4));
                Log::Write(Log::LT_ERROR, HANDLER_FILE, 52,
                           L"[lobby-gate], handle hello fail; ip address mismatch, accept:%s, expect:%s, session-id:0x%I64X, gate-wid:%d, packet-version:%d, ip-address:%s, internal-port:%d",
                           accept, expect, session->_id, static_cast<int>(gateWid), static_cast<int>(packetVersion),
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
                    channel->_broadcastable = true;
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
    short cmd = 0;
    unsigned long long tid = 0;
    unsigned long long clikey = 0;
    id128 infoGateToken;
    infoGateToken.id[0] = 0;
    infoGateToken.id[1] = 0;

    if (packet->Decompose("hqqo", &cmd, &tid, &clikey, &infoGateToken) == 0)
    {
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 119,
                   L"[infogate], handle auth-token-req fail; decompose fail, gate-wid:%d, tid:0x%I64X, cli-key:0x%I64X, infogate-token:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
                   GateWid(channel), tid, clikey, infoGateToken.guid.id1, infoGateToken.guid.id2, infoGateToken.guid.id3,
                   infoGateToken.guid.id4[0], infoGateToken.guid.id4[1], infoGateToken.guid.id4[2], infoGateToken.guid.id4[3],
                   infoGateToken.guid.id4[4], infoGateToken.guid.id4[5], infoGateToken.guid.id4[6], infoGateToken.guid.id4[7]);
        static_cast<InfoGateChannel*>(channel)->SendAuthTokenFail(tid, clikey, 2);
        return true;
    }

    CliSession* cliSession = LobbyDaemon::_instance->_clisessionMgr->Select(clikey);
    if (cliSession == nullptr)
    {
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 127,
                   L"[infogate], handle auth-token-req fail; no such cli-session, gate-wid:%d, tid:0x%I64X, cli-key:0x%I64X, infogate-token:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
                   GateWid(channel), tid, clikey, infoGateToken.guid.id1, infoGateToken.guid.id2, infoGateToken.guid.id3,
                   infoGateToken.guid.id4[0], infoGateToken.guid.id4[1], infoGateToken.guid.id4[2], infoGateToken.guid.id4[3],
                   infoGateToken.guid.id4[4], infoGateToken.guid.id4[5], infoGateToken.guid.id4[6], infoGateToken.guid.id4[7]);
        static_cast<InfoGateChannel*>(channel)->SendAuthTokenFail(tid, clikey, 4);
        return true;
    }

    if (infoGateToken.id[0] == cliSession->_infoGateToken.id[0] && infoGateToken.id[1] == cliSession->_infoGateToken.id[1])
    {
        static_cast<InfoGateChannel*>(channel)->SendAuthTokenOk(tid, clikey, cliSession->_acb._userid);
        Log::Write(Log::LT_DEBUG, HANDLER_FILE, 144,
                   L"[infogate], handle auth-token-req ok, gate-wid:%d, tid:0x%I64X, cli-key:0x%I64X, infogate-token:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
                   GateWid(channel), tid, clikey, infoGateToken.guid.id1, infoGateToken.guid.id2, infoGateToken.guid.id3,
                   infoGateToken.guid.id4[0], infoGateToken.guid.id4[1], infoGateToken.guid.id4[2], infoGateToken.guid.id4[3],
                   infoGateToken.guid.id4[4], infoGateToken.guid.id4[5], infoGateToken.guid.id4[6], infoGateToken.guid.id4[7]);
        cliSession->removeReferenceCount(HANDLER_FILE, 149);
        return true;
    }

    // LIFT: The original prints the required infogate token of the cli-session first in this log line (an auth secret).
    // This lift writes zero in its place. The format string and the argument count are the same.
    Log::Write(Log::LT_ERROR, HANDLER_FILE, 136,
               L"[infogate], handle auth-token-req fail; token mismatch, required-infogate-token:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, gate-wid:%d, tid:0x%I64X, cli-key:0x%I64X, infogate-token:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
               0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u,
               GateWid(channel), tid, clikey, infoGateToken.guid.id1, infoGateToken.guid.id2, infoGateToken.guid.id3,
               infoGateToken.guid.id4[0], infoGateToken.guid.id4[1], infoGateToken.guid.id4[2], infoGateToken.guid.id4[3],
               infoGateToken.guid.id4[4], infoGateToken.guid.id4[5], infoGateToken.guid.id4[6], infoGateToken.guid.id4[7]);
    static_cast<InfoGateChannel*>(channel)->SendAuthTokenFail(tid, clikey, 15);
    cliSession->removeReferenceCount(HANDLER_FILE, 138);
    return true;
}

// 0x57880
bool HandleLobbyInfoGate_GetWorldInfoListReq(SharedChannel* channel, Packet const* packet)
{
    short cmd = 0;

    if (packet->Decompose("h", &cmd) == 0)
    {
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 164,
                   L"[infogate], handle get-world-info-list-req fail; decompose fail, gate-wid:%d", GateWid(channel));
        // LIFT: The callee does not use the reason (it composes 2). The original passes a stale register.
        static_cast<InfoGateChannel*>(channel)->SendGetWorldInfoListFail(2);
        return true;
    }

    FragmentPacket fp(8, "hiChhQ;");
    fp.packet.Allocate(&fp.composer);
    if (LobbyDaemon::_instance->_gameWorldRegistry->FetchWorldInfoListForInfoGate(&fp))
    {
        if (fp.packet.Splitter != nullptr)
            fp.packet.Splitter->Finalize(fp.packet.CurHeader);
        channel->Send(&fp.packet);
        Log::Write(Log::LT_DEBUG, HANDLER_FILE, 183,
                   L"[infogate], handle get-world-info-list-req ok, gate-wid:%d", GateWid(channel));
    }
    else
    {
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 174,
                   L"[infogate], handle get-world-info-list-req fail; fetch world-info-list fail, gate-wid:%d", GateWid(channel));
        static_cast<InfoGateChannel*>(channel)->SendGetWorldInfoListFail(2);
    }
    fp.packet.Clear();
    return true;
}
