// LobbyManagePacketHandler.obj (LobbyDaemon PDB, 2019 + PDB).
// LIFT: gap-19 lifts HelloReq, the two index cleanup handlers, ManageChannel::GetId and the handler table.
#include "PlacementNew.h"
#include <winsock2.h>
#include <windows.h>
#include "LobbyManagePacketHandler.h"
#include "ManageChannel.h"
#include "CliSession.h"
#include "CliSessionManager.h"
#include "LiftStub.h"
#include "LobbyDaemon.h"
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "Packet.h"
#include "Session.h"
#include "StringUtil.h"

namespace
{
// LIFT: No PDB symbol. The binary uses the literal as the file string of the log calls (first use at 0x587d0).
wchar_t const* const MANAGE_HANDLER_FILE = L"LobbyManagePacketHandler.cpp";
}

#define ACCOUNT_GUID_ARGS(a)                                                                                        \
    (a).guid.id1, (a).guid.id2, (a).guid.id3, (a).guid.id4[0], (a).guid.id4[1], (a).guid.id4[2], (a).guid.id4[3], \
        (a).guid.id4[4], (a).guid.id4[5], (a).guid.id4[6], (a).guid.id4[7]

#define LD_H(f) reinterpret_cast<void*>(&(f))
// LIFT: PDB global at .data rva 0x202530 (272 bytes = 17 entries). Entries read from .data: 1 HelloReq (auth 0),
// 4 AnnounceNotify, 5 KickReq, 8 CleanupGameAccountIdIndexReq, 11 CleanupPcidIndexReq, 14 RetryMileageDepositReq (auth 1).
// No entry is a fragment handler. All other entries are null.
LobbyManagePacketHandlerDef LobbyManagePacketLobbySideHandlerList[17] = {
    /*  0 */ {nullptr, false, false},
    /*  1 */ {LD_H(HandleLobbyManage_HelloReq), false, false},
    /*  2 */ {nullptr, false, false},
    /*  3 */ {nullptr, false, false},
    /*  4 */ {LD_H(HandleLobbyManage_AnnounceNotify), true, false},
    /*  5 */ {LD_H(HandleLobbyManage_KickReq), true, false},
    /*  6 */ {nullptr, false, false},
    /*  7 */ {nullptr, false, false},
    /*  8 */ {LD_H(HandleLobbyManage_CleanupGameAccountIdIndexReq), true, false},
    /*  9 */ {nullptr, false, false},
    /* 10 */ {nullptr, false, false},
    /* 11 */ {LD_H(HandleLobbyManage_CleanupPcidIndexReq), true, false},
    /* 12 */ {nullptr, false, false},
    /* 13 */ {nullptr, false, false},
    /* 14 */ {LD_H(HandleLobbyManage_RetryMileageDepositReq), true, false},
    /* 15 */ {nullptr, false, false},
    /* 16 */ {nullptr, false, false}};
#undef LD_H

// 0x58770
unsigned long long ManageChannel::GetId()
{
    return _manageWid;
}

// 0x587d0
bool HandleLobbyManage_HelloReq(Session const* session, Packet const* packet)
{
    unsigned long long id = 0;
    short cmd = 0;
    short manageWid = 0;
    short packetVersion = 0;
    if (packet->Decompose("hhh", &cmd, &manageWid, &packetVersion) == 0)
    {
        if (session != nullptr)
            id = session->_id;
        Log::Write(Log::LT_ERROR, MANAGE_HANDLER_FILE, 35,
                   L"[manage], handle hello fail; decompose fail, session-id:0x%I64X, mgt-wid:%d, packet-version:%d", id,
                   static_cast<int>(manageWid), static_cast<int>(packetVersion));
        session->Send("hh", 3, 1);
        return false;
    }
    if (packetVersion != 7)
    {
        if (session != nullptr)
            id = session->_id;
        Log::Write(Log::LT_ERROR, MANAGE_HANDLER_FILE, 41,
                   L"[manage], handle hello fail; packet version mismatch, require-packet-version:%d, session-id:0x%I64X, mgt-wid:%d, packet-version:%d",
                   7, id, static_cast<int>(manageWid), static_cast<int>(packetVersion));
        session->Send("hh", 3, 7);
        return false;
    }

    void* mem = Memory::_Manager[2]->Alloc(sizeof(ManageChannel), MANAGE_HANDLER_FILE, 46);
    ManageChannel* channel = mem != nullptr ? ::new (mem) ManageChannel(static_cast<unsigned short>(manageWid)) : nullptr;
    // BUG: 0x587d0 the original does not check channel for nullptr before SetSession when the alloc fails.
    channel->SetSession(session);
    session->Send("h", 2);
    if (session != nullptr)
        id = session->_id;
    Log::Write(Log::LT_NOTICE, MANAGE_HANDLER_FILE, 51,
               L"[manage], handle hello ok, session-id:0x%I64X, mgt-wid:%d, packet-version:%d", id,
               static_cast<int>(manageWid), static_cast<int>(packetVersion));
    channel->removeReferenceCount(MANAGE_HANDLER_FILE, 53);
    return true;
}

// 0x589b0
bool HandleLobbyManage_AnnounceNotify(Session const*, Packet const*)
{
    LIFT_STUB(0x589b0);
}

// 0x58b00
bool HandleLobbyManage_KickReq(Session const*, Packet const*)
{
    LIFT_STUB(0x58b00);
}

// 0x590a0
bool HandleLobbyManage_CleanupGameAccountIdIndexReq(Session const* session, Packet const* packet)
{
    id128 account;
    account.id[0] = 0;
    account.id[1] = 0;
    unsigned long long id = 0;
    short cmd = 0;
    unsigned long long tid = 0;
    if (packet->Decompose("hqo", &cmd, &tid, &account) == 0)
    {
        if (session != nullptr)
            id = session->_id;
        Log::Write(Log::LT_ERROR, MANAGE_HANDLER_FILE, 146,
                   L"[manage], handle cleanup game-account-id index req fail; decompose fail, session-id:0x%I64X, tid:0x%I64X, game-account-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
                   id, tid, ACCOUNT_GUID_ARGS(account));
        return true;
    }

    CliSessionManager* mgr = LobbyDaemon::_instance != nullptr ? LobbyDaemon::_instance->_clisessionMgr : nullptr;
    if (mgr == nullptr)
    {
        if (session != nullptr)
            id = session->_id;
        Log::Write(Log::LT_ERROR, MANAGE_HANDLER_FILE, 152,
                   L"[manage], handle cleanup game-account-id index req fail; cli-session manager unavailable, session-id:0x%I64X, tid:0x%I64X, game-account-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
                   id, tid, ACCOUNT_GUID_ARGS(account));
        ManageChannel::SendCleanupGameAccountIdIndexFail(session, tid, 2);
        return true;
    }

    CliSession* cs = mgr->Select_index_account(account);
    if (cs == nullptr)
    {
        if (session != nullptr)
            id = session->_id;
        Log::Write(Log::LT_ERROR, MANAGE_HANDLER_FILE, 159,
                   L"[manage], handle cleanup game-account-id index req fail; no such game-account-id index, session-id:0x%I64X, tid:0x%I64X, game-account-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
                   id, tid, ACCOUNT_GUID_ARGS(account));
        ManageChannel::SendCleanupGameAccountIdIndexFail(session, tid, 4);
        return true;
    }

    mgr->Delete_index_account(account);
    ManageChannel::SendCleanupGameAccountIdIndexOk(session, tid);
    if (session != nullptr)
        id = session->_id;
    int const state = cs->_state;
    Log::Write(Log::LT_DEBUG, MANAGE_HANDLER_FILE, 168,
               L"[manage], handle cleanup game-account-id index req ok, cli-key:0x%I64X, cli-state:%d.%d, session-id:0x%I64X, tid:0x%I64X, game-account-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
               cs->_clikey, static_cast<int>(static_cast<unsigned short>(static_cast<unsigned int>(state) >> 16)),
               static_cast<int>(static_cast<unsigned short>(state)), id, tid, ACCOUNT_GUID_ARGS(account));
    cs->removeReferenceCount(MANAGE_HANDLER_FILE, 170);
    return true;
}

// 0x59470
bool HandleLobbyManage_CleanupPcidIndexReq(Session const* session, Packet const* packet)
{
    unsigned long long id = 0;
    short cmd = 0;
    unsigned long long tid = 0;
    unsigned long long pcid = 0;
    short wid = 0;
    if (packet->Decompose("hqqh", &cmd, &tid, &pcid, &wid) == 0)
    {
        if (session != nullptr)
            id = session->_id;
        Log::Write(Log::LT_ERROR, MANAGE_HANDLER_FILE, 188,
                   L"[manage], handle cleanup pc-id index fail; decompose fail, session-id:0x%I64X, tid:0x%I64X, pcid:0x%I64X, wid:%d",
                   id, tid, pcid, static_cast<int>(wid));
        return false;
    }

    CliSessionManager* mgr = LobbyDaemon::_instance != nullptr ? LobbyDaemon::_instance->_clisessionMgr : nullptr;
    if (mgr == nullptr)
    {
        if (session != nullptr)
            id = session->_id;
        Log::Write(Log::LT_DEBUG, MANAGE_HANDLER_FILE, 194,
                   L"[manage], handle cleanup pc-id index fail; cli-session manager not available, session-id:0x%I64X, tid:0x%I64X, pcid:0x%I64X, wid:%d",
                   id, tid, pcid, static_cast<int>(wid));
        ManageChannel::SendCleanupPcidIndexFail(session, tid, 2);
        return true;
    }

    CliSession* cs = mgr->Select_index_pcid(wid, pcid);
    if (cs == nullptr)
    {
        if (session != nullptr)
            id = session->_id;
        Log::Write(Log::LT_ERROR, MANAGE_HANDLER_FILE, 201,
                   L"[manage], handle cleanup pc-id index fail; no such pc-id index, session-id:0x%I64X, tid:0x%I64X, pcid:0x%I64X, wid:%d",
                   id, tid, pcid, static_cast<int>(wid));
        ManageChannel::SendCleanupPcidIndexFail(session, tid, 4);
        return true;
    }

    mgr->Delete_index_pcid(wid, pcid);
    ManageChannel::SendCleanupPcidIndexOk(session, tid);
    if (session != nullptr)
        id = session->_id;
    int const state = cs->_state;
    Log::Write(Log::LT_DEBUG, MANAGE_HANDLER_FILE, 211,
               L"[manage], handle cleanup pc-id index ok, cli-key:0x%I64X, cli-state:%d.%d, session-id:0x%I64X, tid:0x%I64X, pcid:0x%I64X, wid:%d",
               cs->_clikey, static_cast<int>(static_cast<unsigned short>(static_cast<unsigned int>(state) >> 16)),
               static_cast<int>(static_cast<unsigned short>(state)), id, tid, pcid, static_cast<int>(wid));
    cs->removeReferenceCount(MANAGE_HANDLER_FILE, 213);
    return true;
}

// 0x59820
bool HandleLobbyManage_RetryMileageDepositReq(Session const*, Packet const*)
{
    LIFT_STUB(0x59820);
}

#undef ACCOUNT_GUID_ARGS
