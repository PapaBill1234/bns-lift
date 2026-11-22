// LobbyGamePacketHandler.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "PlacementNew.h"
#include <string.h>
#include <wchar.h>
#include <winsock2.h>
#include <windows.h>
#include "LobbyGamePacketHandler.h"
#include "BLDaemonInfo.h"
#include "CliSession.h"
#include "CliSessionManager.h"
#include "Connection.h"
#include "GameWorld.h"
#include "GamedChannel.h"
#include "LobbyConfig.h"
#include "LobbyDaemon.h"
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "Network.h"
#include "NPServiceChannel.h"
#include "Packet.h"
#include "AlertSender.h"
#include "CliSessionTable.h"
#include "EnterGameWorldJob.h"
#include "LeaveGameWorldJob.h"
#include "LogoutInGameWorldJob.h"
#include "AbandonChargeJob.h"
#include "StartChargeJob.h"
#include "StopChargeJob.h"
#include "LobbyJob.h"
#include "LobbyJobParams.h"
#include "LobbyToken.h"
#include "ObjectPool.h"
#include "PacketBuffer.h"
#include "PacketUtil.h"
#include "Session.h"
#include "BnsCommonConfigDefinition.h"
#include "LiftStub.h"

// LIFT: the handler table (LobbyGamePacketLobbySideHandlerList) is a null placeholder (ld-18). The handlers have no lifted caller. Keep them until the table is lifted.
#pragma comment(linker, "/INCLUDE:?HandleLobbyGame_HelloReq@@YA_NPEBVSession@@PEBVPacket@@@Z")  // LIFT: keep until the caller is lifted (0x88260)
#pragma comment(linker, "/INCLUDE:?HandleLobbyGame_ServiceOpenNotify@@YA_NPEBVSession@@PEBVPacket@@@Z")  // LIFT: keep until the caller is lifted (0x88cd0)
#pragma comment(linker, "/INCLUDE:?HandleLobbyGame_NPPresenceKickReq@@YA_NPEAVSharedChannel@@PEBVPacket@@@Z")  // LIFT: keep until the caller is lifted (0x88f30)
#pragma comment(linker, "/INCLUDE:?HandleLobbyGame_UpdateBotScoreNotify@@YA_NPEAVSharedChannel@@PEBVPacket@@@Z")  // LIFT: keep until the caller is lifted (0x89d90)
#pragma comment(linker, "/INCLUDE:?HandleLobbyGame_KickOk@@YA_NPEAVSharedChannel@@PEBVPacket@@@Z")  // LIFT: keep until the caller is lifted (0x8a400)
#pragma comment(linker, "/INCLUDE:?HandleLobbyGame_KickFail@@YA_NPEAVSharedChannel@@PEBVPacket@@@Z")  // LIFT: keep until the caller is lifted (0x8a560)
#pragma comment(linker, "/INCLUDE:?HandleLobbyGame_CreateCharacterOk@@YA_NPEAVSharedChannel@@PEBVPacket@@@Z")  // LIFT: keep until the caller is lifted (0x8a7c0)
#pragma comment(linker, "/INCLUDE:?HandleLobbyGame_CreateCharacterFail@@YA_NPEAVSharedChannel@@PEBVPacket@@@Z")  // LIFT: keep until the caller is lifted (0x8aad0)
#pragma comment(linker, "/INCLUDE:?HandleLobbyGame_DeleteCharacterOk@@YA_NPEAVSharedChannel@@PEBVPacket@@@Z")  // LIFT: keep until the caller is lifted (0x8ad30)
#pragma comment(linker, "/INCLUDE:?HandleLobbyGame_DeleteCharacterFail@@YA_NPEAVSharedChannel@@PEBVPacket@@@Z")  // LIFT: keep until the caller is lifted (0x8af90)
#pragma comment(linker, "/INCLUDE:?HandleLobbyGame_RestoreCharacterOk@@YA_NPEAVSharedChannel@@PEBVPacket@@@Z")  // LIFT: keep until the caller is lifted (0x8b1f0)
#pragma comment(linker, "/INCLUDE:?HandleLobbyGame_RestoreCharacterFail@@YA_NPEAVSharedChannel@@PEBVPacket@@@Z")  // LIFT: keep until the caller is lifted (0x8b350)
#pragma comment(linker, "/INCLUDE:?HandleLobbyGame_UpdateCharacterDataReq@@YA_NPEAVSharedChannel@@PEBVPacket@@@Z")  // LIFT: keep until the caller is lifted (0x8c250)

// LIFT: placeholder. The owner is the LobbyDaemon BnsCommonConfigDefinition module (0x1890 and up). Delete this line when that module lands.
BnsCommonConfig* BnsCommonConfig::Config = nullptr;

// LIFT: placeholder for the PDB public LobbyErrorDesc (.data 0003:2032, 28 entries, names as in enum LobbyError). The owner is the module that defines it (not found in the PDB module list). ❓
wchar_t const* LobbyErrorDesc[28] = {
    L"LOBERR_UNKNOWN", L"LOBERR_SYSTEM", L"LOBERR_DB_FAIL", L"LOBERR_INVALID_PARAMETER", L"LOBERR_NOT_INITAILIZED",
    L"LOBERR_INVALID_SESSION_STATE", L"LOBERR_NO_SUCH_CHARACTER", L"LOBERR_GAMEWORLD_NOT_FOUND",
    L"LOBERR_GAMEWORLD_NOT_ALIVE", L"LOBERR_GAMEWORLD_NOT_USABLE", L"LOBERR_GAMEWORLD_ENTRANCE_NOT_ALLOWED",
    L"LOBERR_GAMEWORLD_PRE_CHARACTER_CREATION_MODE", L"LOBERR_GAMEWORLD_FULL",
    L"LOBERR_GAMEWORLD_CHARACTER_MANAGEMENT_NOT_ALLOWED", L"LOBERR_GAMEWORLD_NEW_ACCOUNT_CHARACTER_CREATION_NOT_ALLOWED",
    L"LOBERR_CHARGE_NOT_STARTED", L"LOBERR_IN_LOBBY_SERVICE", L"LOBERR_INVALID_STATE", L"LOBERR_NAME_DUPLICATED",
    L"LOBERR_NAME_LIMITED", L"LOBERR_VIP_NOT_AVAILABLE", L"LOBERR_VIP_UNKNOWN_ID", L"LOBERR_INSUFFICIENT_BUFFER",
    L"LOBERR_ALREADY_INITIALIZED", L"LOBERR_NOT_FOUND", L"LOBERR_STOP_PLAY_ALREADY_RESERVED",
    L"LOBERR_GAME_TIME_SCHEDULE_NO_NEED_TO_SCHEDULE", L"LOBERR_GAME_TIME_SCHEDULE_IN_SCHEDULED_BLOCK_TIME"};

// 0x88260
// LIFT: local log helper for the 10 fail logs of HandleLobbyGame_HelloReq (0x88260). Not a PDB name.
#define LGP_HELLO_FAIL_LOG(line, reason)                                                                              \
    Log::Write(Log::LT_ERROR, L"LobbyGamePacketHandler.cpp", line,                                                    \
               L"[gamed], handle hello fail; " reason                                                                 \
               L", session-id:0x%I64X, world-cluster-id:%d, wid:%d, packet-version:%d, internal-port:%d",             \
               session->_id, static_cast<int>(worldClusterId), static_cast<int>(worldId),                             \
               static_cast<int>(packetVersion), static_cast<int>(internalPort))
bool HandleLobbyGame_HelloReq(Session const* session, Packet const* packet)
{
    short cmd = 0;
    short packetVersion = 0;
    short worldClusterId = 0;
    short worldId = 0;
    unsigned short internalPort = 0;
    int errorCode;
    BLDaemonInfo const* info;
    wchar_t acc[16];
    wchar_t exp[16];

    if (packet->Decompose("hhhhh", &cmd, &worldClusterId, &worldId, &packetVersion, &internalPort) == 0)
    {
        unsigned long long id = 0;
        if (session != nullptr)
            id = session->_id;
        Log::Write(Log::LT_ERROR, L"LobbyGamePacketHandler.cpp", 57,
                   L"[gamed], handle hello fail; decompose fail, session-id:0x%I64X, world-cluster-id:%d, wid:%d, packet-version:%d, internal-port:%d",
                   id, static_cast<int>(worldClusterId), static_cast<int>(worldId), static_cast<int>(packetVersion),
                   static_cast<int>(internalPort));
        errorCode = 1;
        goto sendFail;
    }
    if (packetVersion != 83)
    {
        unsigned long long id = 0;
        if (session != nullptr)
            id = session->_id;
        Log::Write(Log::LT_ERROR, L"LobbyGamePacketHandler.cpp", 63,
                   L"[gamed], handle hello fail; packet version mismatch, session-id:0x%I64X, world-cluster-id:%d, wid:%d, packet-version:%d, internal-port:%d",
                   id, static_cast<int>(worldClusterId), static_cast<int>(worldId), static_cast<int>(packetVersion),
                   static_cast<int>(internalPort));
        errorCode = 8;
        goto sendFail;
    }
    BLDaemonID daemonId;
    daemonId.kind = 1;
    daemonId.wid = worldId;
    info = LobbyDaemon::_instance->_daemonInfoTable->Find(daemonId);
    if (info == nullptr)
    {
        unsigned long long id = 0;
        if (session != nullptr)
            id = session->_id;
        Log::Write(Log::LT_ERROR, L"LobbyGamePacketHandler.cpp", 70,
                   L"[gamed], handle hello fail; unknown gamed, session-id:0x%I64X, world-cluster-id:%d, wid:%d, packet-version:%d, internal-port:%d",
                   id, static_cast<int>(worldClusterId), static_cast<int>(worldId), static_cast<int>(packetVersion),
                   static_cast<int>(internalPort));
        errorCode = 9;
        goto sendFail;
    }
    if (session->_connection->_ip != info->internal_ipv4)
    {
        wcscpy_s(acc, 15, Network::GetAddressStringW(session->_connection->_ip));
        wcscpy_s(exp, 15, Network::GetAddressStringW(info->internal_ipv4));
        Log::Write(Log::LT_ERROR, L"LobbyGamePacketHandler.cpp", 79,
                   L"[gamed], handle hello fail; ip address mismatch, accept:%s, expect:%s, session-id:0x%I64X, world-cluster-id:%d, wid:%d, packet-version:%d, internal-port:%d",
                   acc, exp, session->_id, static_cast<int>(worldClusterId), static_cast<int>(worldId),
                   static_cast<int>(packetVersion), static_cast<int>(internalPort));
        errorCode = 10;
    sendFail:
        session->Send("hh", 3, errorCode);
        return false;
    }
    GameWorld* world = LobbyDaemon::_instance->_gameWorldRegistry->Get(worldId);
    if (world == nullptr)
    {
        LGP_HELLO_FAIL_LOG(92, L"game-world information not registered");
        errorCode = 13;
        goto sendFail;
    }
    if (worldClusterId != world->GetDB().clusterId)
    {
        LGP_HELLO_FAIL_LOG(98, L"world-cluster-id mismatch");
        errorCode = 14;
        goto sendFail;
    }
    if (world->_live)
    {
        LGP_HELLO_FAIL_LOG(104, L"channel duplicated; close both channel");
        GamedChannel* old = LobbyDaemon::_instance->_gamedchmgr->Acquire(worldId);
        if (old != nullptr)
        {
            old->Close();
            old->removeReferenceCount(L"LobbyGamePacketHandler.cpp", 108);
        }
        errorCode = 12;
        goto sendFail;
    }

    void* mem = Memory::_Manager[2]->Alloc(48, L"LobbyGamePacketHandler.cpp", 115);
    // BUG: the original dereferences a null channel when Alloc fails (0x88260).
    GamedChannel* channel = mem != nullptr ? new (mem) GamedChannel() : nullptr;
    if (!channel->InitializeTransactionChannel(LobbyDaemon::_instance->_config->_lobbyJobTransactionLifeTime))
    {
        LGP_HELLO_FAIL_LOG(117, L"initialize channel fail");
        session->Send("hh", 3, 2);
        channel->removeReferenceCount(L"LobbyGamePacketHandler.cpp", 119);
        return false;
    }
    if (!channel->Accept(worldId, session))
    {
        LGP_HELLO_FAIL_LOG(124, L"accept session fail");
        session->Send("hh", 3, 2);
        channel->removeReferenceCount(L"LobbyGamePacketHandler.cpp", 126);
        return false;
    }
    if (!LobbyDaemon::_instance->_gamedchmgr->Add(channel))
    {
        LGP_HELLO_FAIL_LOG(131, L"already exists");
        session->Send("hh", 3, 12);
        channel->removeReferenceCount(L"LobbyGamePacketHandler.cpp", 133);
        return false;
    }

    LobbyDaemon* daemon = LobbyDaemon::_instance;
    RepeatPacketComposer rpc;
    rpc.format = nullptr;
    rpc.len = 0;
    rpc.index = 0;
    rpc.PacketFormatIterator::SetFormat("hCQiiiqqChiiii;;qqqi", 0);
    rpc.top = -1;
    rpc.subTop = -1;
    Packet p;
    p.Splitter = nullptr;
    p.IsFragmentPacket = false;
    memset(&p.FragmentPacketCmd, 0, 28);
    p.Allocate();
    if (p.Compose(&rpc, 1, 2) == 0)
    {
        LGP_HELLO_FAIL_LOG(145, L"packet compose fail");
        session->Send("hh", 3, 2);
        channel->removeReferenceCount(L"LobbyGamePacketHandler.cpp", 147);
        return false;
    }
    if (!daemon->_timeBasedPlaySeasonSchedule.Compose(rpc, p))
    {
        LGP_HELLO_FAIL_LOG(154, L"packet compose fail - time based schedule");
        session->Send("hh", 3, 2);
        channel->removeReferenceCount(L"LobbyGamePacketHandler.cpp", 156);
        return false;
    }
    if (p.Compose(&rpc, 3, daemon->_currentRandomStoreInitSchedule.scheduleNumber,
                  daemon->_currentRandomStoreInitSchedule.slotCountInitScheduleNumber,
                  daemon->_currentRandomStoreInitSchedule.premiumDrawCountInitScheduleNumber) == 0)
    {
        Log::Write(Log::LT_ERROR, L"LobbyDaemon.cpp", 806,
                   L"[random-store], packet compose failed, random store initialization schedule");
        LGP_HELLO_FAIL_LOG(163, L"packet compose fail - random store initialization schedule");
        session->Send("hh", 3, 2);
        channel->removeReferenceCount(L"LobbyGamePacketHandler.cpp", 165);
        return false;
    }
    if (p.Compose(&rpc, 1, LobbyDaemon::_instance->_config->_gameMileageEffectiveDurationInDays) == 0)
    {
        LGP_HELLO_FAIL_LOG(172, L"packet compose fail");
        session->Send("hh", 3, 2);
        channel->removeReferenceCount(L"LobbyGamePacketHandler.cpp", 174);
        return false;
    }
    if (p.Splitter != nullptr)
        p.Splitter->Finalize(p.CurHeader);
    PacketBuffer* listHead = p.ListHead;
    listHead->encrypt(session->_currentCrypt, session->_security3rd);
    PacketBuffer const* list = listHead;
    Session* self = const_cast<Session*>(session);
    EnterCriticalSection(&self->_lock.CS);
    session->send(&list, 1);
    LeaveCriticalSection(&self->_lock.CS);
    Log::Write(Log::LT_NOTICE, L"LobbyGamePacketHandler.cpp", 182,
               L"[gamed], handle hello ok, session-id:0x%I64X, world-cluster-id:%d, wid:%d, packet-version:%d, internal-port:%d",
               session->_id, static_cast<int>(worldClusterId), static_cast<int>(worldId),
               static_cast<int>(packetVersion), static_cast<int>(internalPort));
    channel->removeReferenceCount(L"LobbyGamePacketHandler.cpp", 184);
    return true;
}
#undef LGP_HELLO_FAIL_LOG

// 0x88cd0
bool HandleLobbyGame_ServiceOpenNotify(Session const* session, Packet const* packet)
{
    unsigned long long id = 0;
    short cmd = 0;
    short worldClusterId = 0;
    short worldId = 0;
    if (packet->Decompose("hhh", &cmd, &worldClusterId, &worldId) == 0)
    {
        if (session != nullptr)
            id = session->_id;
        Log::Write(Log::LT_ERROR, L"LobbyGamePacketHandler.cpp", 202,
                   L"[gamed], handle service open notify fail; decompose fail, session-id:0x%I64X, world-cluster-id:%d, worldId:%d",
                   id, static_cast<int>(worldClusterId), static_cast<int>(worldId));
        return true;
    }
    // LIFT: GameWorldRegistry::Get (0x4e8b0) is inlined here.
    GameWorldRegistry* registry = LobbyDaemon::_instance->_gameWorldRegistry;
    int index = worldId - registry->_min;
    GameWorld* world = nullptr;
    if (index < 0 || index >= registry->_size)
    {
        Log::Write(Log::LT_ERROR, L"GameWorld.cpp", 761, L"[game-world-registry], get fail; wid out of range, wid:%d",
                   static_cast<int>(worldId));
    }
    else
    {
        world = registry->_worlds[index];
    }
    if (world == nullptr)
    {
        if (session != nullptr)
            id = session->_id;
        Log::Write(Log::LT_ERROR, L"LobbyGamePacketHandler.cpp", 208,
                   L"[gamed], handle service open notify fail; game-world information not registered, session-id:0x%I64X, world-cluster-id:%d, worldId:%d",
                   id, static_cast<int>(worldClusterId), static_cast<int>(worldId));
        return false;
    }
    if (worldClusterId != world->GetDB().clusterId)
    {
        if (session != nullptr)
            id = session->_id;
        Log::Write(Log::LT_ERROR, L"LobbyGamePacketHandler.cpp", 213,
                   L"[gamed], handle service open notify fail; world-cluster-id mismatch, session-id:0x%I64X, world-cluster-id:%d, worldId:%d",
                   id, static_cast<int>(worldClusterId), static_cast<int>(worldId));
        return false;
    }
    if (world->_live)
    {
        if (session != nullptr)
            id = session->_id;
        Log::Write(Log::LT_ERROR, L"LobbyGamePacketHandler.cpp", 218,
                   L"[gamed], handle service open notify fail; channel duplicated; close both channel, session-id:0x%I64X, world-cluster-id:%d, worldId:%d",
                   id, static_cast<int>(worldClusterId), static_cast<int>(worldId));
        GamedChannel* old = LobbyDaemon::_instance->_gamedchmgr->Acquire(worldId);
        if (old != nullptr)
        {
            old->Close();
            old->removeReferenceCount(L"LobbyGamePacketHandler.cpp", 222);
            return false;
        }
        return false;
    }
    world->_live = true;
    if (session != nullptr)
        id = session->_id;
    Log::Write(Log::LT_DEBUG, L"LobbyGamePacketHandler.cpp", 229,
               L"[gamed], handle service open notify; set live ok, session-id:0x%I64X, world-cluster-id:%d, worldId:%d",
               id, static_cast<int>(worldClusterId), static_cast<int>(worldId));
    return true;
}

// 0x88f30
bool HandleLobbyGame_NPPresenceKickReq(SharedChannel* channel, Packet const* packet)
{
    short cmd = 0;
    unsigned long long pcdbid = 0;
    char targetApp = -1;
    char force = 0;
    Packet p;
    p.Splitter = nullptr;
    p.IsFragmentPacket = false;
    memset(&p.FragmentPacketCmd, 0, 28);
    if (packet->Decompose("hqQQ", &cmd, &pcdbid, &targetApp, &force) == 0)
    {
        Log::Write(Log::LT_ERROR, L"LobbyGamePacketHandler.cpp", 247,
                   L"[gamed], handle np presence kick req fail; decompose fail");
        return true;
    }
    short wid = 0;
    if (channel->_rawChannel != nullptr)
        wid = static_cast<short>(channel->_rawChannel->GetId());
    CliSession* cliSession = LobbyDaemon::_instance->_clisessionMgr->Select_index_pcid(wid, pcdbid);
    if (cliSession == nullptr)
    {
        Log::Write(Log::LT_ERROR, L"LobbyGamePacketHandler.cpp", 254,
                   L"[gamed], handle np presence kick req fail; cli-session not found, pcdbid:0x%I64x", pcdbid);
        return true;
    }
    NPGameServiceChannel* gameServChannel = LobbyDaemon::_instance->_npServchmgr->_gameServChannel;
    if (gameServChannel == nullptr)
    {
        Log::Write(Log::LT_ERROR, L"LobbyGamePacketHandler.cpp", 261,
                   L"[gamed], handle np presence kick req fail; np is not available, pcdbid:0x%I64x", pcdbid);
        goto cleanup;
    }
    // LIFT: the PDB parameter t (NPTransaction*) has no register in the original (LTCG removed it). The value is not used.
    if (targetApp != 0)
    {
        if (targetApp != 1)
        {
            Log::Write(Log::LT_ERROR, L"LobbyGamePacketHandler.cpp", 282,
                       L"[gamed], handle np presence kick req fail; unknown target app, pcdbid:0x%I64x, targetApp:%d, force:%d",
                       pcdbid, static_cast<int>(targetApp), static_cast<int>(force));
            goto cleanup;
        }
        if (!gameServChannel->SendRequestPresenceKick(nullptr, cliSession->_acb._id,
                                                      BnsCommonConfig::Config->_npAppId, force == 1))
        {
            Log::Write(Log::LT_ERROR, L"LobbyGamePacketHandler.cpp", 277,
                       L"[gamed], handle np presence kick req fail; send to np fail, pcdbid:0x%I64x, targetApp:%d, force:%d",
                       pcdbid, static_cast<int>(targetApp), static_cast<int>(force));
            goto cleanup;
        }
    }
    else
    {
        if (!gameServChannel->SendRequestPresenceKick(nullptr, cliSession->_acb._id,
                                                      BnsCommonConfig::Config->_npClientAppId, force == 1))
        {
            Log::Write(Log::LT_ERROR, L"LobbyGamePacketHandler.cpp", 270,
                       L"[gamed], handle np presence kick req fail; send to np fail, pcdbid:0x%I64x, targetApp:%d, force:%d",
                       pcdbid, static_cast<int>(targetApp), static_cast<int>(force));
            goto cleanup;
        }
    }
    Log::Write(Log::LT_DEBUG, L"LobbyGamePacketHandler.cpp", 286,
               L"[gamed], handle np presence kick req ok, pcdbid:0x%I64x, cli-key:0x%I64x, targetApp:%d, force:%d",
               pcdbid, cliSession->_clikey, static_cast<int>(targetApp), static_cast<int>(force));
    p.Allocate();
    if (p.Compose("hqQQ", 18, pcdbid, static_cast<int>(targetApp), static_cast<int>(force)) != 0)
    {
        channel->Send(&p);
    }
    else
    {
        Log::Write(Log::LT_ERROR, L"LobbyGamePacketHandler.cpp", 291,
                   L"[gamed], send np presence kick notify fail; compose fail, pcid:0x%I64x, targetApp:%d, force:%d",
                   pcdbid, static_cast<int>(targetApp), static_cast<int>(force));
    }
cleanup:
    cliSession->removeReferenceCount(L"LobbyGamePacketHandler.cpp", 299);
    return true;
}

// LIFT: inlined in 0x89270, 0x899a0, 0x89d90 and 0x8a060: the id of the raw channel, or 0.
static unsigned long long LgpChannelId(SharedChannel* channel)
{
    if (channel != nullptr && channel->_rawChannel != nullptr)
        return channel->_rawChannel->GetId();
    return 0;
}

// LIFT: inlined in 0x8a400 to 0x8b350: the id of the raw channel, as a signed 16-bit wid.
static int LgpWid(SharedChannel* channel)
{
    return static_cast<short>(LgpChannelId(channel));
}

// 0x89270
bool HandleLobbyGame_EnterWorldReq(SharedChannel*, Packet const*)
{
    LIFT_STUB(0x89270);
}

// 0x899a0
bool HandleLobbyGame_LeaveWorldReq(SharedChannel*, Packet const*)
{
    LIFT_STUB(0x899a0);
}

// 0x89d90
bool HandleLobbyGame_UpdateBotScoreNotify(SharedChannel* channel, Packet const* packet)
{
    short cmd = 0;
    unsigned long long pcid = 0;
    unsigned long long clikey = 0;
    int botScore = 0;

    if (packet->Decompose("hqqi", &cmd, &pcid, &clikey, &botScore) == 0)
    {
        Log::Write(Log::LT_ERROR, L"LobbyGamePacketHandler.cpp", 476,
                   L"[gamed], handle update bot score notify fail; decompose fail, channel-id:%I64d, pcid:0x%I64X, cli-key:0x%I64X, botScore:%d",
                   LgpChannelId(channel), pcid, clikey, botScore);
        return true;
    }
    short wid = static_cast<short>(LgpChannelId(channel));
    CliSession* cliSession = LobbyDaemon::_instance->_clisessionMgr->Select_index_pcid(wid, pcid);
    if (cliSession == nullptr)
    {
        Log::Write(Log::LT_ERROR, L"LobbyGamePacketHandler.cpp", 482,
                   L"[gamed], handle update bot score notify fail; no such cli-session, channel-id:%I64d, pcid:0x%I64X, cli-key:0x%I64X, botScore:%d",
                   LgpChannelId(channel), pcid, clikey, botScore);
        return true;
    }
    int line;
    if (cliSession->_clikey != clikey)
    {
        Log::Write(Log::LT_ERROR, L"LobbyGamePacketHandler.cpp", 487,
                   L"[gamed], handle update bot score notify fail; cli-key mismatch, found-cli-key:0x%I64X, channel-id:%I64d, pcid:0x%I64X, cli-key:0x%I64X, botScore:%d",
                   cliSession->_clikey, LgpChannelId(channel), pcid, clikey, botScore);
        line = 488;
    }
    else
    {
        if (!cliSession->UpdateBotScore(pcid, botScore))
        {
            unsigned int error = static_cast<unsigned int>(TLobbyError);
            unsigned long long id = LgpChannelId(channel);
            wchar_t const* desc = error >= 28 ? L"LOBERR_UNDEFINED" : LobbyErrorDesc[error];
            // BUG: the original log text says update character-data in the bot score handler (0x89d90).
            Log::Write(Log::LT_ERROR, L"LobbyGamePacketHandler.cpp", 495,
                       L"[gamed], handle update character-data fail; update fail, error:%s, channel-id:%I64d, pcid:0x%I64X, cli-key:0x%I64X, botScore:%d",
                       desc, id, pcid, clikey, botScore);
        }
        else
        {
            Log::Write(Log::LT_DEBUG, L"LobbyGamePacketHandler.cpp", 499,
                       L"[gamed], handle update bot score notify ok, channel-id:%I64d, pcid:0x%I64X, cli-key:0x%I64X, botScore:%d",
                       LgpChannelId(channel), pcid, clikey, botScore);
        }
        line = 502;
    }
    cliSession->removeReferenceCount(L"LobbyGamePacketHandler.cpp", line);
    return true;
}

// 0x8a060
bool HandleLobbyGame_LogoutNotify(SharedChannel*, Packet const*)
{
    LIFT_STUB(0x8a060);
}

// 0x8a400
bool HandleLobbyGame_KickOk(SharedChannel* channel, Packet const* packet)
{
    short cmd = 0;
    unsigned long long tid = 0;
    if (packet->Decompose("hq", &cmd, &tid) == 0)
    {
        Log::Write(Log::LT_ERROR, L"LobbyGamePacketHandler.cpp", 575,
                   L"[gamed], handle kick ok fail; decompose fail, wid:%d, tid:0x%I64X",
                   LgpWid(channel), tid);
        return true;
    }
    if (!LobbyDaemon::_instance->_jobMgr->ExecuteW(tid, 114, nullptr))
    {
        Log::Write(Log::LT_ERROR, L"LobbyGamePacketHandler.cpp", 580,
                   L"[gamed], handle kick ok fail; execute task fail, wid:%d, tid:0x%I64X",
                   LgpWid(channel), tid);
        return true;
    }
    Log::Write(Log::LT_DEBUG, L"LobbyGamePacketHandler.cpp", 584,
               L"[gamed], handle kick ok ok, wid:%d, tid:0x%I64X",
               LgpWid(channel), tid);
    return true;
}

// 0x8a560
bool HandleLobbyGame_KickFail(SharedChannel* channel, Packet const* packet)
{
    short cmd = 0;
    unsigned long long tid = 0;
    WorldKickFailParam param;
    param.reason = 0;
    if (packet->Decompose("hqE", &cmd, &tid, &param) == 0)
    {
        Log::Write(Log::LT_ERROR, L"LobbyGamePacketHandler.cpp", 604,
                   L"[gamed], handle kick fail fail; decompose fail, wid:%d, tid:0x%I64X, reason:%d",
                   LgpWid(channel), tid, static_cast<int>(param.reason));
        return true;
    }
    // LIFT: LobbyJobManager::ExecuteW (0xc20a0) is inlined in 0x8a560.
    if (!LobbyDaemon::_instance->_jobMgr->ExecuteW(tid, 115, &param))
    {
        Log::Write(Log::LT_ERROR, L"LobbyGamePacketHandler.cpp", 609,
                   L"[gamed], handle kick fail fail; execute task fail, wid:%d, tid:0x%I64X, reason:%d",
                   LgpWid(channel), tid, static_cast<int>(param.reason));
        return true;
    }
    Log::Write(Log::LT_DEBUG, L"LobbyGamePacketHandler.cpp", 613,
               L"[gamed], handle kick fail ok, wid:%d, tid:0x%I64X, reason:%d",
               LgpWid(channel), tid, static_cast<int>(param.reason));
    return true;
}

// 0x8a7c0
bool HandleLobbyGame_CreateCharacterOk(SharedChannel* channel, Packet const* packet)
{
    short cmd = 0;
    unsigned long long tid = 0;
    CreateCharacterOkParam param;
    memset(&param, 0, sizeof(param));
    param.showcaseDataSize = 512;
    if (packet->Decompose("hqhhb", &cmd, &tid, &param, &param.level, param.showcaseData, &param.showcaseDataSize) == 0)
    {
        Log::Write(Log::LT_ERROR, L"LobbyGamePacketHandler.cpp", 635,
                   L"[gamed], handle create character ok fail; decompose fail, wid:%d, tid:0x%I64X, job:%d, level:%d, showcase-size:%d",
                   LgpWid(channel), tid, static_cast<int>(param.job), static_cast<int>(param.level), static_cast<int>(param.showcaseDataSize));
        return true;
    }
    // LIFT: LobbyJobManager::ExecuteW (0xc20a0) is inlined in 0x8a7c0.
    if (!LobbyDaemon::_instance->_jobMgr->ExecuteW(tid, 105, &param))
    {
        Log::Write(Log::LT_ERROR, L"LobbyGamePacketHandler.cpp", 640,
                   L"[gamed], handle create character ok fail; execute job fail, wid:%d, tid:0x%I64X, job:%d, level:%d, showcase-size:%d",
                   LgpWid(channel), tid, static_cast<int>(param.job), static_cast<int>(param.level), static_cast<int>(param.showcaseDataSize));
        return true;
    }
    Log::Write(Log::LT_DEBUG, L"LobbyGamePacketHandler.cpp", 644,
               L"[gamed], handle create character ok ok,wid:%d, tid:0x%I64X, job:%d, level:%d, showcase-size:%d",
               LgpWid(channel), tid, static_cast<int>(param.job), static_cast<int>(param.level), static_cast<int>(param.showcaseDataSize));
    return true;
}

// 0x8aad0
bool HandleLobbyGame_CreateCharacterFail(SharedChannel* channel, Packet const* packet)
{
    short cmd = 0;
    unsigned long long tid = 0;
    short reason = 0;
    if (packet->Decompose("hqE", &cmd, &tid, &reason) == 0)
    {
        Log::Write(Log::LT_ERROR, L"LobbyGamePacketHandler.cpp", 662,
                   L"[gamed], handle create character fail fail; decompose fail, wid:%d, tid:0x%I64X, reason:%d",
                   LgpWid(channel), tid, static_cast<int>(reason));
        return true;
    }
    // LIFT: LobbyJobManager::ExecuteW (0xc20a0) is inlined in 0x8aad0.
    if (!LobbyDaemon::_instance->_jobMgr->ExecuteW(tid, 106, &reason))
    {
        Log::Write(Log::LT_ERROR, L"LobbyGamePacketHandler.cpp", 667,
                   L"[gamed], handle create character fail fail; execute job fail, wid:%d, tid:0x%I64X, reason:%d",
                   LgpWid(channel), tid, static_cast<int>(reason));
        return true;
    }
    Log::Write(Log::LT_DEBUG, L"LobbyGamePacketHandler.cpp", 671,
               L"[gamed], handle create character fail ok, wid:%d, tid:0x%I64X, reason:%d",
               LgpWid(channel), tid, static_cast<int>(reason));
    return true;
}

// 0x8ad30
bool HandleLobbyGame_DeleteCharacterOk(SharedChannel* channel, Packet const* packet)
{
    short cmd = 0;
    unsigned long long tid = 0;
    DeleteCharacterOkParam param;
    param.level = 0;
    if (packet->Decompose("hqh", &cmd, &tid, &param) == 0)
    {
        Log::Write(Log::LT_ERROR, L"LobbyGamePacketHandler.cpp", 691,
                   L"[gamed], handle delete character ok fail; decompose fail, wid:%d, tid:0x%I64X, level:%d",
                   LgpWid(channel), tid, static_cast<int>(param.level));
        return true;
    }
    // LIFT: LobbyJobManager::ExecuteW (0xc20a0) is inlined in 0x8ad30.
    if (!LobbyDaemon::_instance->_jobMgr->ExecuteW(tid, 108, &param))
    {
        Log::Write(Log::LT_ERROR, L"LobbyGamePacketHandler.cpp", 696,
                   L"[gamed], handle delete character ok fail; execute job fail, wid:%d, tid:0x%I64X, level:%d",
                   LgpWid(channel), tid, static_cast<int>(param.level));
        return true;
    }
    Log::Write(Log::LT_DEBUG, L"LobbyGamePacketHandler.cpp", 700,
               L"[gamed], handle delete character ok ok, wid:%d, tid:0x%I64X, level:%d",
               LgpWid(channel), tid, static_cast<int>(param.level));
    return true;
}

// 0x8af90
bool HandleLobbyGame_DeleteCharacterFail(SharedChannel* channel, Packet const* packet)
{
    short cmd = 0;
    unsigned long long tid = 0;
    short reason = 0;
    if (packet->Decompose("hqE", &cmd, &tid, &reason) == 0)
    {
        Log::Write(Log::LT_ERROR, L"LobbyGamePacketHandler.cpp", 718,
                   L"[gamed], handle delete character fail fail; decompose fail, wid:%d, tid:0x%I64X, reason:%d",
                   LgpWid(channel), tid, static_cast<int>(reason));
        return true;
    }
    // LIFT: LobbyJobManager::ExecuteW (0xc20a0) is inlined in 0x8af90.
    if (!LobbyDaemon::_instance->_jobMgr->ExecuteW(tid, 109, &reason))
    {
        Log::Write(Log::LT_ERROR, L"LobbyGamePacketHandler.cpp", 723,
                   L"[gamed], handle delete character fail fail; execute job fail, wid:%d, tid:0x%I64X, reason:%d",
                   LgpWid(channel), tid, static_cast<int>(reason));
        return true;
    }
    Log::Write(Log::LT_DEBUG, L"LobbyGamePacketHandler.cpp", 727,
               L"[gamed], handle delete character fail ok, wid:%d, tid:0x%I64X, reason:%d",
               LgpWid(channel), tid, static_cast<int>(reason));
    return true;
}

// 0x8b1f0
bool HandleLobbyGame_RestoreCharacterOk(SharedChannel* channel, Packet const* packet)
{
    short cmd = 0;
    unsigned long long tid = 0;
    if (packet->Decompose("hq", &cmd, &tid) == 0)
    {
        Log::Write(Log::LT_ERROR, L"LobbyGamePacketHandler.cpp", 745,
                   L"[gamed], handle restore character ok fail; decompose fail, wid:%d, tid:0x%I64X",
                   LgpWid(channel), tid);
        return true;
    }
    if (!LobbyDaemon::_instance->_jobMgr->ExecuteW(tid, 111, nullptr))
    {
        Log::Write(Log::LT_ERROR, L"LobbyGamePacketHandler.cpp", 750,
                   L"[gamed], handle restore character ok fail; execute job fail, wid:%d, tid:0x%I64X",
                   LgpWid(channel), tid);
        return true;
    }
    Log::Write(Log::LT_DEBUG, L"LobbyGamePacketHandler.cpp", 754,
               L"[gamed], handle restore character ok ok, wid:%d, tid:0x%I64X",
               LgpWid(channel), tid);
    return true;
}

// 0x8b350
bool HandleLobbyGame_RestoreCharacterFail(SharedChannel* channel, Packet const* packet)
{
    short cmd = 0;
    unsigned long long tid = 0;
    short reason = 0;
    if (packet->Decompose("hqE", &cmd, &tid, &reason) == 0)
    {
        Log::Write(Log::LT_ERROR, L"LobbyGamePacketHandler.cpp", 772,
                   L"[gamed], handle restore character fail fail; decompose fail, wid:%d, tid:0x%I64X, reason:%d",
                   LgpWid(channel), tid, static_cast<int>(reason));
        return true;
    }
    // LIFT: LobbyJobManager::ExecuteW (0xc20a0) is inlined in 0x8b350.
    if (!LobbyDaemon::_instance->_jobMgr->ExecuteW(tid, 112, &reason))
    {
        Log::Write(Log::LT_ERROR, L"LobbyGamePacketHandler.cpp", 777,
                   L"[gamed], handle restore character fail fail; execute job fail, wid:%d, tid:0x%I64X, reason:%d",
                   LgpWid(channel), tid, static_cast<int>(reason));
        return true;
    }
    Log::Write(Log::LT_DEBUG, L"LobbyGamePacketHandler.cpp", 781,
               L"[gamed], handle restore character fail ok, wid:%d, tid:0x%I64X, reason:%d",
               LgpWid(channel), tid, static_cast<int>(reason));
    return true;
}

// 0x8b5b0
bool HandleLobbyGame_StartChargeReq(SharedChannel*, Packet const*)
{
    LIFT_STUB(0x8b5b0);
}

// 0x8b9b0
bool HandleLobbyGame_StopChargeReq(SharedChannel*, Packet const*)
{
    LIFT_STUB(0x8b9b0);
}

// 0x8be60
bool HandleLobbyGame_AbandonChargeNotify(SharedChannel*, Packet const*)
{
    LIFT_STUB(0x8be60);
}

// 0x8c250
bool HandleLobbyGame_UpdateCharacterDataReq(SharedChannel* sharedChannel, Packet const* packet)
{
    GamedChannel* channel = static_cast<GamedChannel*>(sharedChannel);
    short cmd = 0;
    unsigned long long gametid = 0;
    unsigned long long pcid = 0;
    unsigned long long clikey = 0;
    short level = 0;
    short showcaseSize = 512;
    char showcase[512];

    if (packet->Decompose("hqqqhb", &cmd, &gametid, &pcid, &clikey, &level, showcase, &showcaseSize) == 0)
    {
        Log::Write(Log::LT_ERROR, L"LobbyGamePacketHandler.cpp", 975,
                   L"[gamed], handle update character-data fail; decompose fail, channel-id:%I64d, game-tid:0x%I64X, pcid:0x%I64X, cli-key:0x%I64X, level:%d, showcase-size:%d",
                   LgpChannelId(channel), gametid, pcid, clikey, static_cast<int>(level), static_cast<int>(showcaseSize));
        return true;
    }
    short wid = static_cast<short>(LgpChannelId(channel));
    CliSession* cliSession = LobbyDaemon::_instance->_clisessionMgr->Select_index_pcid(wid, pcid);
    if (cliSession == nullptr)
    {
        Log::Write(Log::LT_ERROR, L"LobbyGamePacketHandler.cpp", 982,
                   L"[gamed], handle update character-data fail; no such cli-session, channel-id:%I64d, game-tid:0x%I64X, pcid:0x%I64X, cli-key:0x%I64X, level:%d, showcase-size:%d",
                   LgpChannelId(channel), gametid, pcid, clikey, static_cast<int>(level), static_cast<int>(showcaseSize));
        channel->SendUpdateCharacterDataFail(gametid, 5);
        return true;
    }
    int line;
    if (cliSession->_clikey != clikey)
    {
        Log::Write(Log::LT_ERROR, L"LobbyGamePacketHandler.cpp", 989,
                   L"[gamed], handle update character-data fail; cli-key mismatch, found-cli-key:0x%I64X, channel-id:%I64d, game-tid:0x%I64X, pcid:0x%I64X, cli-key:0x%I64X, level:%d, showcase-size:%d",
                   cliSession->_clikey, LgpChannelId(channel), gametid, pcid, clikey, static_cast<int>(level),
                   static_cast<int>(showcaseSize));
        channel->SendUpdateCharacterDataFail(gametid, 5);
        line = 991;
    }
    else if (!cliSession->UpdateCharacterData(pcid, level, showcase, showcaseSize))
    {
        unsigned int error = static_cast<unsigned int>(TLobbyError);
        unsigned long long id = LgpChannelId(channel);
        wchar_t const* desc = error >= 28 ? L"LOBERR_UNDEFINED" : LobbyErrorDesc[error];
        Log::Write(Log::LT_ERROR, L"LobbyGamePacketHandler.cpp", 998,
                   L"[gamed], handle update character-data fail; update fail, error:%s, channel-id:%I64d, game-tid:0x%I64X, pcid:0x%I64X, cli-key:0x%I64X, level:%d, showcase-size:%d",
                   desc, id, gametid, pcid, clikey, static_cast<int>(level), static_cast<int>(showcaseSize));
        channel->SendUpdateCharacterDataFail(gametid, error == 6 ? 45 : 2);
        line = 1012;
    }
    else
    {
        channel->SendUpdateCharacterDataOk(gametid);
        Log::Write(Log::LT_DEBUG, L"LobbyGamePacketHandler.cpp", 1018,
                   L"[gamed], handle update character-data ok, channel-id:%I64d, game-tid:0x%I64X, pcid:0x%I64X, cli-key:0x%I64X, level:%d, showcase-size:%d",
                   LgpChannelId(channel), gametid, pcid, clikey, static_cast<int>(level), static_cast<int>(showcaseSize));
        line = 1020;
    }
    cliSession->removeReferenceCount(L"LobbyGamePacketHandler.cpp", line);
    return true;
}

// 0x8c660
bool HandleLobbyGame_UpdateAccountDataReq(SharedChannel*, Packet const*)
{
    LIFT_STUB(0x8c660);
}

// 0x8d590
bool HandleLobbyGame_TryRegisterGuildReq(SharedChannel*, Packet const*)
{
    LIFT_STUB(0x8d590);
}

// 0x8d9a0
bool HandleLobbyGame_FinishRegisterGuildNotify(SharedChannel*, Packet const*)
{
    LIFT_STUB(0x8d9a0);
}

// 0x8db10
bool HandleLobbyGame_CancelRegisterGuildNotify(SharedChannel*, Packet const*)
{
    LIFT_STUB(0x8db10);
}

// 0x8dc80
bool HandleLobbyGame_TryRenameGuildReq(SharedChannel*, Packet const*)
{
    LIFT_STUB(0x8dc80);
}

// 0x8e010
bool HandleLobbyGame_FinishRenameGuildNotify(SharedChannel*, Packet const*)
{
    LIFT_STUB(0x8e010);
}

// 0x8e220
bool HandleLobbyGame_CancelRenameGuildNotify(SharedChannel*, Packet const*)
{
    LIFT_STUB(0x8e220);
}

// 0x8e390
bool HandleLobbyGame_DeleteGuildNotify(SharedChannel*, Packet const*)
{
    LIFT_STUB(0x8e390);
}

// 0x8e520
bool HandleLobbyGame_ChangeCharacterAppearanceOk(SharedChannel*, Packet const*)
{
    LIFT_STUB(0x8e520);
}

// 0x8e820
bool HandleLobbyGame_ChangeCharacterAppearanceFail(SharedChannel*, Packet const*)
{
    LIFT_STUB(0x8e820);
}

// 0x8eab0
bool HandleLobbyGame_ChangeCharacterSexOk(SharedChannel*, Packet const*)
{
    LIFT_STUB(0x8eab0);
}

// 0x8edb0
bool HandleLobbyGame_ChangeCharacterSexFail(SharedChannel*, Packet const*)
{
    LIFT_STUB(0x8edb0);
}

// 0x8f040
bool HandleLobbyGame_ChangeCharacterRaceOk(SharedChannel*, Packet const*)
{
    LIFT_STUB(0x8f040);
}

// 0x8f340
bool HandleLobbyGame_ChangeCharacterRaceFail(SharedChannel*, Packet const*)
{
    LIFT_STUB(0x8f340);
}

// 0x8f5d0
bool HandleLobbyGame_RenameCharacterOk(SharedChannel*, Packet const*)
{
    LIFT_STUB(0x8f5d0);
}

// 0x8f870
bool HandleLobbyGame_RenameCharacterFail(SharedChannel*, Packet const*)
{
    LIFT_STUB(0x8f870);
}

// 0x8fb00
bool HandleLobbyGame_ExtendJumpingCharacterCreationQuotaWithAccountInventoryItemReq(SharedChannel*, Packet const*)
{
    LIFT_STUB(0x8fb00);
}

// 0x8ffc0
bool HandleLobbyGame_UpgradeJumpingCharacterStateWithCreationQuotaReq(SharedChannel*, Packet const*)
{
    LIFT_STUB(0x8ffc0);
}

// 0x903d0
bool HandleLobbyGame_UpdateJumpingCharacterStateReq(SharedChannel*, Packet const*)
{
    LIFT_STUB(0x903d0);
}

// 0x907e0
bool HandleLobbyGame_SetAppDataNotify(SharedChannel*, Packet const*)
{
    LIFT_STUB(0x907e0);
}

// 0x90f70
bool HandleLobbyGame_FriendMessageNotify(SharedChannel*, Packet const*)
{
    LIFT_STUB(0x90f70);
}

// 0x91ab0
bool HandleLobbyGame_SecondPasswordGetStatusReq(SharedChannel*, Packet const*)
{
    LIFT_STUB(0x91ab0);
}

// 0x91e80
bool HandleLobbyGame_SecondPasswordIsVerifiedReq(SharedChannel*, Packet const*)
{
    LIFT_STUB(0x91e80);
}

// 0x92280
bool HandleLobbyGame_AuctionEscrowOk(SharedChannel*, Packet const*)
{
    LIFT_STUB(0x92280);
}

// 0x92400
bool HandleLobbyGame_AuctionEscrowFail(SharedChannel*, Packet const*)
{
    LIFT_STUB(0x92400);
}

// 0x926a0
bool HandleLobbyGame_AuctionBidReq(SharedChannel*, Packet const*)
{
    LIFT_STUB(0x926a0);
}

// 0x92ca0
bool HandleLobbyGame_GetGradeListReq(SharedChannel*, Packet const*)
{
    LIFT_STUB(0x92ca0);
}

// 0x92f00
bool HandleLobbyGame_ActivateGradeReq(SharedChannel*, Packet const*)
{
    LIFT_STUB(0x92f00);
}

// 0x93540
bool HandleLobbyGame_DepositGameMileageReq(SharedChannel*, Packet const*)
{
    LIFT_STUB(0x93540);
}

// 0x94780
bool HandleLobbyGame_BoastEventInWorldNotify(SharedChannel*, Packet const*)
{
    LIFT_STUB(0x94780);
}

// 0x94910
bool HandleLobbyGame_TakeAccountTimeBasedPlayRewardReq(SharedChannel*, Packet const*)
{
    LIFT_STUB(0x94910);
}

// 0x94df0
bool HandleLobbyGame_UpdateAccountExpReq(SharedChannel*, Packet const*)
{
    LIFT_STUB(0x94df0);
}

// 0x951f0
bool HandleLobbyGame_UpdateAccountContentQuotaReq(SharedChannel*, Packet const*)
{
    LIFT_STUB(0x951f0);
}

// 0x95890
bool HandleLobbyGame_UpdateAccountRecycleTimeReq(SharedChannel*, Packet const*)
{
    LIFT_STUB(0x95890);
}
