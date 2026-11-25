// LobbyGamePacketHandler.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include <new>
#include <vector>
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
#include "InfoGateChannel.h"
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
#include "CrashHandler.h"
#include "LobbyDB.h"
#include "RefCntObject.h"
#include "StlMemory.h"
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

// LIFT: inlined in 0x89270, 0x899a0, 0x89d90, 0x8a060, 0x8d9a0, 0x8db10, 0x8e010, 0x8e220, 0x8e390, 0x8e520 to 0x8f870 and 0x907e0: the id of the raw channel, or 0.
static __forceinline unsigned long long LgpChannelId(SharedChannel const* channel)
{
    if (channel != nullptr && channel->_rawChannel != nullptr)
        return channel->_rawChannel->GetId();
    return 0;
}

// LIFT: inlined in 0x8a400 to 0x8b350, 0x8c660 and 0x907e0: the id of the raw channel, as a signed 16-bit wid.
static __forceinline int LgpWid(SharedChannel const* channel)
{
    return static_cast<short>(LgpChannelId(channel));
}

// LIFT: inlined __FILEW__ literal of the assert and log macros (0x8c660, 0x8d9a0, 0x8db10, 0x8e010, 0x8e220, 0x8e390, 0x8e820, 0x8edb0, 0x8f340, 0x8f5d0, 0x8f870, 0x907e0).
static wchar_t const HANDLER_FILE[] = L"LobbyGamePacketHandler.cpp";

// LIFT: inlined assert of BloodLib (Log, alert, crash). No PDB name. Inlined in 0x8c660 and 0x907e0.
static __forceinline void assertCrash(wchar_t const* wideFile, char const* file, int line)
{
    Log::Write(Log::LT_ERROR, wideFile, line, L"== CRASH == ASSERT CRASH");
    AlertSender::Write(wideFile, line, L"== CRASH == ASSERT CRASH");
    CrashHandler::MakeCrash(file, line, L"");
}

// LIFT: inlined in 0x8c660. A TLobbyError value of 28 or more gives the text "LOBERR_UNDEFINED".
static __forceinline wchar_t const* LobbyErrorText(int error)
{
    if (static_cast<unsigned int>(error) >= 28)
        return L"LOBERR_UNDEFINED";
    return LobbyErrorDesc[error];
}

// LIFT: inlined in 0x8c660. LOBERR_DB_FAIL gives 3, LOBERR_INVALID_PARAMETER gives 4, all other errors give 2.
static __forceinline short UpdateFailCode(int error)
{
    switch (error)
    {
    case 2:
        return 3;
    case 3:
        return 4;
    default:
        return 2;
    }
}

// LIFT: inlined __FILEW__ literal of the LobbyDB checks (guild id and rename key) in 0x8d9a0, 0x8db10, 0x8e010 and 0x8e390. LobbyDB.cpp logs the invalid-parameter case in the caller.
static wchar_t const LOBBYDB_FILE[] = L"LobbyDB.cpp";

// LIFT: inlined LobbyJobManager::ExecuteW (0xc20a0) in the job-result handlers. The task ids have no PDB name. ❓
enum
{
    JOB_TASK_CHANGE_APPEARANCE_OK = 123,
    JOB_TASK_CHANGE_APPEARANCE_FAIL = 124,
    JOB_TASK_RENAME_CHARACTER_OK = 126,
    JOB_TASK_RENAME_CHARACTER_FAIL = 127,
    JOB_TASK_CHANGE_SEX_OK = 136,
    JOB_TASK_CHANGE_SEX_FAIL = 137,
    JOB_TASK_CHANGE_RACE_OK = 139,
    JOB_TASK_CHANGE_RACE_FAIL = 140
};

// PDB layouts (include/pdb/LobbyDaemon/types.h).
struct ChangeCharacterAppearanceOkParam
{
    char* showcaseData;
    short showcaseDataSize;
};
static_assert(sizeof(ChangeCharacterAppearanceOkParam) == 0x10, "sizeof ChangeCharacterAppearanceOkParam");
struct ChangeCharacterSexOkParam
{
    char* showcaseData;
    short showcaseDataSize;
};
static_assert(sizeof(ChangeCharacterSexOkParam) == 0x10, "sizeof ChangeCharacterSexOkParam");
struct ChangeCharacterRaceOkParam
{
    char* showcaseData;
    short showcaseDataSize;
};
static_assert(sizeof(ChangeCharacterRaceOkParam) == 0x10, "sizeof ChangeCharacterRaceOkParam");
struct RenameCharacterOkParam
{
    unsigned long long pcid;
};
static_assert(sizeof(RenameCharacterOkParam) == 0x8, "sizeof RenameCharacterOkParam");

// LIFT: inlined PacketDecomposer setup in 0x8e820, 0x8edb0, 0x8f340, 0x8f5d0, 0x8f870 and the showcase handlers (0x8e520, 0x8eab0, 0x8f040). The command (first format letter) is skipped.
static __forceinline void SetupDecomposer(PacketDecomposer* pdr, char const* format, int len)
{
    pdr->format = format;
    pdr->len = len;
    pdr->index = 1;
    pdr->offset = 2;
}

// LIFT: shared body of the three showcase "Ok" handlers (0x8e520, 0x8eab0, 0x8f040). The original code has one copy per handler.
// Format "hqb": tid, then a variable block (showcase data).
template <typename Param>
static __forceinline bool HandleShowcaseOk(SharedChannel* channel, Packet const* packet, int task, wchar_t const* decomposeFail1,
                             int line1, wchar_t const* decomposeFail2, int line2, wchar_t const* execFail, int lineExec,
                             wchar_t const* okText, int lineOk)
{
    Param param = {};
    PacketDecomposer pdr;
    SetupDecomposer(&pdr, "hqb", 3);
    Packet::VarData showcaseData = {};
    unsigned long long tid = 0;
    if (packet->Decompose(&pdr, 1, &tid) == 0)
    {
        Log::Write(Log::LT_ERROR, HANDLER_FILE, line1, decomposeFail1, LgpChannelId(channel), tid, 0);
        return true;
    }
    if (packet->Decompose(&pdr, &showcaseData) == 0)
    {
        int size = showcaseData.size != nullptr ? *showcaseData.size : 0;
        Log::Write(Log::LT_ERROR, HANDLER_FILE, line2, decomposeFail2, LgpChannelId(channel), tid, size);
        return true;
    }
    param.showcaseData = showcaseData.buffer;
    param.showcaseDataSize = *showcaseData.size;
    if (!LobbyDaemon::_instance->_jobMgr->ExecuteW(tid, task, &param))
    {
        Log::Write(Log::LT_ERROR, HANDLER_FILE, lineExec, execFail, LgpChannelId(channel), tid,
                   static_cast<int>(*showcaseData.size));
        return true;
    }
    Log::Write(Log::LT_DEBUG, HANDLER_FILE, lineOk, okText, LgpChannelId(channel), tid,
               static_cast<int>(*showcaseData.size));
    return true;
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

#pragma comment(linker, "/INCLUDE:?HandleLobbyGame_UpdateAccountDataReq@@YA_NPEAVSharedChannel@@PEBVPacket@@@Z")   // LIFT: keep until the caller is lifted (0x8c660)
// 0x8c660
bool HandleLobbyGame_UpdateAccountDataReq(SharedChannel* sharedChannel, Packet const* packet)
{
    GamedChannel* const channel = static_cast<GamedChannel*>(sharedChannel);

    // LIFT: inlined RepeatPacketDecomposer setup. The command is skipped (index 1, offset 2).
    RepeatPacketDecomposer rpd;
    rpd.format = "hqqqiCQiqqihcccc;qiqCihqq;Chq;";
    rpd.len = 30;
    rpd.index = 1;
    rpd.offset = 2;
    rpd.top = -1;

    unsigned long long channelId = 0;
    unsigned long long gametid = 0;
    unsigned long long pcid = 0;
    unsigned long long clikey = 0;
    int botScore = 0;
    TimeBasedPlayInfoList playInfo;
    GameAccountExpInfo::ExpInfo accExpInfo;
    memset(&accExpInfo, 0, sizeof(accExpInfo));
    std::vector<AccountContentQuota, StlAllocator<AccountContentQuota, 2> > quotaList;
    std::vector<AccountRecycleTime, StlAllocator<AccountRecycleTime, 2> > recycleTimeList;

    if (packet->Decompose(&rpd, 4, &gametid, &pcid, &clikey, &botScore) == 0)
    {
        if (channel != nullptr && channel->_rawChannel != nullptr)
            channelId = channel->_rawChannel->GetId();
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 1051,
                   L"[gamed], handle update account-data fail; decompose fail, channel-id:%I64d, game-tid:0x%I64X, "
                   L"pcid:0x%I64X, cli-key:0x%I64X, bot-score:%d",
                   channelId, gametid, pcid, clikey, botScore);
        return true;
    }
    if (!playInfo.Decompose(rpd, packet))
    {
        if (channel != nullptr && channel->_rawChannel != nullptr)
            channelId = channel->_rawChannel->GetId();
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 1057,
                   L"[gamed], handle update account-data fail; decompose(TimeBasedPlayInfoList) fail, "
                   L"channel-id:%I64d, game-tid:0x%I64X, pcid:0x%I64X, cli-key:0x%I64X, bot-score:%d",
                   channelId, gametid, pcid, clikey, botScore);
        return true;
    }
    if (packet->Decompose(&rpd, 3, &accExpInfo.exp, &accExpInfo.expQuotaPerDay, &accExpInfo.lastUpdateTime) == 0)
    {
        if (channel != nullptr && channel->_rawChannel != nullptr)
            channelId = channel->_rawChannel->GetId();
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 1063,
                   L"[gamed], handle update account-data fail; decompose(AccountExpInfo) fail, channel-id:%I64d, "
                   L"game-tid:0x%I64X, pcid:0x%I64X, cli-key:0x%I64X, bot-score:%d",
                   channelId, gametid, pcid, clikey, botScore);
        return true;
    }

    // LIFT: inlined repeat count read of PacketUtil.cpp (assert at line 241).
    if (packet == nullptr)
        assertCrash(L"source\\PacketUtil.cpp", "source\\PacketUtil.cpp", 241);
    // BUG: 0x8c660 the count is a signed value from the packet. A negative count converts to a huge reserve size.
    unsigned long long const quotaCount = static_cast<unsigned long long>(rpd.PushRepeatCount(
        reinterpret_cast<char const*>(packet->CurHeader + 1) + rpd.offset,
        static_cast<unsigned short>(packet->CurHeader->size - 2) - rpd.offset));
    quotaList.reserve(quotaCount);
    for (int i = 0; i < static_cast<int>(quotaCount); ++i)
    {
        AccountContentQuota quota;
        memset(&quota, 0, sizeof(quota));
        if (packet->Decompose(&rpd, 4, &quota.dataId, &quota.version, &quota.quantity, &quota.lastUpdateTime) == 0)
        {
            if (channel != nullptr && channel->_rawChannel != nullptr)
                channelId = channel->_rawChannel->GetId();
            Log::Write(Log::LT_ERROR, HANDLER_FILE, 1078,
                       L"[gamed], handle update account-data fail; decompose(AccountContentQuotaList) fail, "
                       L"channel-id:%I64d, game-tid:0x%I64X, pcid:0x%I64X, cli-key:0x%I64X, bot-score:%d",
                       channelId, gametid, pcid, clikey, botScore);
            return true;
        }
        // LIFT: inlined decrement of the repeat count of RepeatPacketDecomposer.
        rpd.index = rpd.start[rpd.top] + 1;
        --rpd.counts[rpd.top];
        quotaList.push_back(quota);
    }

    // LIFT: inlined end of repeat of PacketUtil.cpp (assert at line 248: the repeat format must start with 'C').
    if (rpd.top < 0 || rpd.format[rpd.start[rpd.top]] != 'C')
        assertCrash(L"source\\PacketUtil.cpp", "source\\PacketUtil.cpp", 248);
    static_cast<PacketFormatIterator&>(rpd).skipRepeatFormat();  // LIFT: virtual call as in the original (0x8c660)
    --rpd.top;

    // LIFT: the original keeps the repeat count of the recycle list in a 16-bit value (0x8c660).
    short const recycleCount = static_cast<short>(rpd.PushRepeatCount(
        reinterpret_cast<char const*>(packet->CurHeader + 1) + rpd.offset,
        static_cast<unsigned short>(packet->CurHeader->size - 2) - rpd.offset));
    recycleTimeList.reserve(static_cast<unsigned long long>(static_cast<long long>(recycleCount)));
    for (int i = 0; i < static_cast<int>(recycleCount); ++i)
    {
        AccountRecycleTime recycleTime;
        memset(&recycleTime, 0, sizeof(recycleTime));
        if (packet->Decompose(&rpd, 2, &recycleTime.groupId, &recycleTime.time) == 0)
        {
            if (channel != nullptr && channel->_rawChannel != nullptr)
                channelId = channel->_rawChannel->GetId();
            Log::Write(Log::LT_ERROR, HANDLER_FILE, 1099,
                       L"[gamed], handle update account-data fail; decompose(AccountRecycleTimeList) fail, "
                       L"channel-id:%I64d, game-tid:0x%I64X, pcid:0x%I64X, cli-key:0x%I64X, bot-score:%d",
                       channelId, gametid, pcid, clikey, botScore);
            return true;
        }
        rpd.index = rpd.start[rpd.top] + 1;
        --rpd.counts[rpd.top];
        recycleTimeList.push_back(recycleTime);
    }
    if (rpd.top < 0 || rpd.format[rpd.start[rpd.top]] != 'C')
        assertCrash(L"source\\PacketUtil.cpp", "source\\PacketUtil.cpp", 248);
    static_cast<PacketFormatIterator&>(rpd).skipRepeatFormat();  // LIFT: virtual call as in the original (0x8c660)
    --rpd.top;

    short const wid = channel->_rawChannel != nullptr ? static_cast<short>(channel->_rawChannel->GetId()) : 0;
    CliSession* const session = LobbyDaemon::_instance->_clisessionMgr->Select_index_pcid(wid, pcid);
    if (session == nullptr)
    {
        if (channel->_rawChannel != nullptr)
            channelId = channel->_rawChannel->GetId();
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 1112,
                   L"[gamed], handle update account-data fail; no such cli-session, channel-id:%I64d, "
                   L"game-tid:0x%I64X, pcid:0x%I64X, cli-key:0x%I64X, bot-score:%d",
                   channelId, gametid, pcid, clikey, botScore);
        channel->SendUpdateAccountDataFail(gametid, 5);
        return true;
    }
    if (clikey != session->_clikey)
    {
        if (channel->_rawChannel != nullptr)
            channelId = channel->_rawChannel->GetId();
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 1119,
                   L"[gamed], handle update account-data fail; cli-key mismatch, found-cli-key:0x%I64X, "
                   L"channel-id:%I64d, game-tid:0x%I64X, pcid:0x%I64X, cli-key:0x%I64X, bot-score:%d",
                   session->_clikey, channelId, gametid, pcid, clikey, botScore);
        channel->SendUpdateAccountDataFail(gametid, 5);
        session->removeReferenceCount(HANDLER_FILE, 1121);
        return true;
    }

    short dataCode = 0;
    if (!session->UpdateAccountData(pcid, botScore, playInfo))
    {
        int const error = TLobbyError;
        unsigned long long const id = channel->_rawChannel != nullptr ? channel->_rawChannel->GetId() : 0;
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 1129,
                   L"[gamed], handle update account-data fail; update fail, error:%s, channel-id:%I64d, "
                   L"game-tid:0x%I64X, pcid:0x%I64X, cli-key:0x%I64X, bot-score:%d",
                   LobbyErrorText(error), id, gametid, pcid, clikey, botScore);
        dataCode = UpdateFailCode(error);
    }
    short expCode = 0;
    if (!session->UpdateAccountExp(pcid, accExpInfo))
    {
        int const error = TLobbyError;
        unsigned long long const id = channel->_rawChannel != nullptr ? channel->_rawChannel->GetId() : 0;
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 1152,
                   L"[gamed], handle update account-exp fail; update fail, error:%s, channel-id:%I64d, "
                   L"game-tid:0x%I64X, pcid:0x%I64X, cli-key:0x%I64X, bot-score:%d",
                   LobbyErrorText(error), id, gametid, pcid, clikey, botScore);
        expCode = UpdateFailCode(error);
    }
    short quotaCode = 0;
    if (!session->UpdateAccountContentQuota(pcid, quotaList))
    {
        int const error = TLobbyError;
        unsigned long long const id = channel->_rawChannel != nullptr ? channel->_rawChannel->GetId() : 0;
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 1169,
                   L"[gamed], handle update account-content-quota fail; update fail, error:%s, channel-id:%I64d, "
                   L"game-tid:0x%I64X, pcid:0x%I64X, cli-key:0x%I64X, bot-score:%d",
                   LobbyErrorText(error), id, gametid, pcid, clikey, botScore);
        quotaCode = UpdateFailCode(error);
    }
    short recycleCode = 0;
    if (!session->UpdateAccountRecycleTime(pcid, recycleTimeList))
    {
        int const error = TLobbyError;
        unsigned long long const id = channel->_rawChannel != nullptr ? channel->_rawChannel->GetId() : 0;
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 1186,
                   L"[gamed], handle update account-recycle-time fail; update fail, error:%s, channel-id:%I64d, "
                   L"game-tid:0x%I64X, pcid:0x%I64X, cli-key:0x%I64X, bot-score:%d",
                   LobbyErrorText(error), id, gametid, pcid, clikey, botScore);
        recycleCode = UpdateFailCode(error);
    }

    if (dataCode != 0 || expCode != 0 || quotaCode != 0 || recycleCode != 0)
    {
        // BUG: 0x8c660 sends only the UpdateAccountData code (0 when only a later update fails); kept for parity.
        channel->SendUpdateAccountDataFail(gametid, dataCode);
        session->removeReferenceCount(HANDLER_FILE, 1202);
    }
    else
    {
        channel->SendUpdateAccountDataOk(gametid);
        if (channel->_rawChannel != nullptr)
            channelId = channel->_rawChannel->GetId();
        Log::Write(Log::LT_DEBUG, HANDLER_FILE, 1208,
                   L"[gamed], handle update account-data ok, channel-id:%I64d, game-tid:0x%I64X, pcid:0x%I64X, "
                   L"cli-key:0x%I64X, bot-score:%d",
                   channelId, gametid, pcid, clikey, botScore);
        session->removeReferenceCount(HANDLER_FILE, 1210);
    }
    return true;
}

// 0x8d590
bool HandleLobbyGame_TryRegisterGuildReq(SharedChannel*, Packet const*)
{
    LIFT_STUB(0x8d590);
}

#pragma comment(linker, "/INCLUDE:?HandleLobbyGame_FinishRegisterGuildNotify@@YA_NPEAVSharedChannel@@PEBVPacket@@@Z")   // LIFT: keep until the caller is lifted (0x8d9a0)
// 0x8d9a0
bool HandleLobbyGame_FinishRegisterGuildNotify(SharedChannel* sharedChannel, Packet const* packet)
{
    SharedChannel* const channel = sharedChannel;
    short cmd = 0;
    unsigned long long gametid = 0;
    unsigned long long guildid = 0;
    if (packet->Decompose("hqq", &cmd, &gametid, &guildid) == 0)
    {
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 1329,
                   L"[gamed], handle finish register guild notify fail; decompose fail");
        return true;
    }
    int dbrtn = 0;
    bool dbOk = false;
    if (guildid == 0)
    {
        // LIFT: inlined invalid-parameter check of LobbyDB::FinishGuildRegistration.
        Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 2288, L"[lobbydb], finish guild registration fail; invalid parameter");
    }
    else
    {
        dbOk = LobbyDB::FinishGuildRegistration(dbrtn, guildid);
    }
    if (!dbOk)
    {
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 1335,
                   L"[gamed], handle finish register guild notify fail; db fail, dbrtn:%d, channel-id:%I64d, game-tid:0x%I64X, "
                   L"guild-id:0x%I64X",
                   dbrtn, LgpChannelId(channel), gametid, guildid);
        return true;
    }
    Log::Write(Log::LT_DEBUG, HANDLER_FILE, 1339,
               L"[gamed], handle finish register guild notify ok, channel-id:%I64d, game-tid:0x%I64X, guild-id:0x%I64X",
               LgpChannelId(channel), gametid, guildid);
    return true;
}

#pragma comment(linker, "/INCLUDE:?HandleLobbyGame_CancelRegisterGuildNotify@@YA_NPEAVSharedChannel@@PEBVPacket@@@Z")   // LIFT: keep until the caller is lifted (0x8db10)
// 0x8db10
bool HandleLobbyGame_CancelRegisterGuildNotify(SharedChannel* sharedChannel, Packet const* packet)
{
    SharedChannel* const channel = sharedChannel;
    short cmd = 0;
    unsigned long long gametid = 0;
    unsigned long long guildid = 0;
    if (packet->Decompose("hqq", &cmd, &gametid, &guildid) == 0)
    {
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 1358,
                   L"[gamed], handle cancel register guild notify fail; decompose fail");
        return true;
    }
    int dbrtn = 0;
    bool dbOk = false;
    if (guildid == 0)
    {
        // LIFT: inlined invalid-parameter check of LobbyDB::CancelGuildRegistration.
        Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 2348, L"[lobbydb], cancel guild registration fail; invalid parameter");
    }
    else
    {
        dbOk = LobbyDB::CancelGuildRegistration(dbrtn, guildid);
    }
    if (!dbOk)
    {
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 1364,
                   L"[gamed], handle cancel register guild notify fail; db fail, dbrtn:%d, channel-id:%I64d, game-tid:0x%I64X, "
                   L"guild-id:0x%I64X",
                   dbrtn, LgpChannelId(channel), gametid, guildid);
        return true;
    }
    Log::Write(Log::LT_DEBUG, HANDLER_FILE, 1368,
               L"[gamed], handle cancel register guild notify ok, channel-id:%I64d, game-tid:0x%I64X, guild-id:0x%I64X",
               LgpChannelId(channel), gametid, guildid);
    return true;
}

// 0x8dc80
bool HandleLobbyGame_TryRenameGuildReq(SharedChannel*, Packet const*)
{
    LIFT_STUB(0x8dc80);
}

#pragma comment(linker, "/INCLUDE:?HandleLobbyGame_FinishRenameGuildNotify@@YA_NPEAVSharedChannel@@PEBVPacket@@@Z")   // LIFT: keep until the caller is lifted (0x8e010)
// 0x8e010
bool HandleLobbyGame_FinishRenameGuildNotify(SharedChannel* sharedChannel, Packet const* packet)
{
    SharedChannel* const channel = sharedChannel;
    short cmd = 0;
    unsigned long long tid = 0;
    unsigned long long guildId = 0;
    unsigned long long renameKey = 0;
    if (packet->Decompose("hqqq", &cmd, &tid, &guildId, &renameKey) == 0)
    {
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 1482,
                   L"[gamed], rename-guild; handle finish rename guild notify fail; decompose fail");
        return true;
    }
    Log::Write(Log::LT_DEBUG, HANDLER_FILE, 1486,
               L"[gamed], rename-guild; handle finish rename guild notify; packet decomposed, channel-id:%I64d, "
               L"game-tid:0x%I64X, guild-id:0x%I64X, guild-rename-key:0x%I64X",
               LgpChannelId(channel), tid, guildId, renameKey);
    int dbrtn = 0;
    bool dbOk = false;
    if (renameKey != 0)
    {
        dbOk = LobbyDB::FinishRenameGuild(dbrtn, guildId, renameKey);
    }
    else
    {
        // LIFT: inlined invalid-parameter check of LobbyDB::FinishRenameGuild.
        Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 2548, L"[lobbydb], finish rename guild; invalid parameter");
    }
    if (dbOk)
    {
        Log::Write(Log::LT_DEBUG, HANDLER_FILE, 1495,
                   L"[gamed], rename-guild; handle finish rename guild notify ok, channel-id:%I64d, "
                   L"game-tid:0x%I64X, guild-id:0x%I64X, guild-rename-key:0x%I64X",
                   LgpChannelId(channel), tid, guildId, renameKey);
        return true;
    }
    Log::Write(Log::LT_ERROR, HANDLER_FILE, 1491,
               L"[gamed], rename-guild; handle finish rename guild notify fail; db fail, dbrtn:%d, "
               L"channel-id:%I64d, game-tid:0x%I64X, guild-id:0x%I64X, guild-rename-key:0x%I64X",
               dbrtn, LgpChannelId(channel), tid, guildId, renameKey);
    return true;
}

#pragma comment(linker, "/INCLUDE:?HandleLobbyGame_CancelRenameGuildNotify@@YA_NPEAVSharedChannel@@PEBVPacket@@@Z")   // LIFT: keep until the caller is lifted (0x8e220)
// 0x8e220
bool HandleLobbyGame_CancelRenameGuildNotify(SharedChannel* sharedChannel, Packet const* packet)
{
    SharedChannel* const channel = sharedChannel;
    short cmd = 0;
    unsigned long long renameKey = 0;
    if (packet->Decompose("hq", &cmd, &renameKey) == 0)
    {
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 1515,
                   L"[gamed], rename-guild; handle cancel rename guild notify fail; decompose fail");
        return true;
    }
    Log::Write(Log::LT_DEBUG, HANDLER_FILE, 1519,
               L"[gamed], rename-guild; handle cancel rename guild notify packet decomposed, channel-id:%I64d, "
               L"guild-rename-key:0x%I64X",
               LgpChannelId(channel), renameKey);
    int dbrtn = 0;
    if (!LobbyDB::CancelRenameGuild(dbrtn, renameKey))
    {
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 1523,
                   L"[gamed], rename-guild; handle cancel rename guild notify fail; db fail, dbrtn:%d, "
                   L"channel-id:%I64d, guild-rename-key:0x%I64X",
                   dbrtn, LgpChannelId(channel), renameKey);
        return true;
    }
    Log::Write(Log::LT_DEBUG, HANDLER_FILE, 1527,
               L"[gamed], rename-guild; handle cancel rename guild notify ok, channel-id:%I64d, "
               L"guild-rename-key:0x%I64X",
               LgpChannelId(channel), renameKey);
    return true;
}

#pragma comment(linker, "/INCLUDE:?HandleLobbyGame_DeleteGuildNotify@@YA_NPEAVSharedChannel@@PEBVPacket@@@Z")   // LIFT: keep until the caller is lifted (0x8e390)
// 0x8e390
bool HandleLobbyGame_DeleteGuildNotify(SharedChannel* sharedChannel, Packet const* packet)
{
    SharedChannel* const channel = sharedChannel;
    short cmd = 0;
    unsigned long long gametid = 0;
    unsigned long long guildid = 0;
    if (packet->Decompose("hqq", &cmd, &gametid, &guildid) == 0)
    {
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 1546,
                   L"[gamed], handle delete guild notify fail; decompose fail");
        return true;
    }
    int dbrtn = 0;
    bool dbOk = false;
    if (guildid == 0)
    {
        // LIFT: inlined invalid-parameter check of LobbyDB::DeleteGuild.
        Log::Write(Log::LT_ERROR, LOBBYDB_FILE, 2408, L"[lobbydb], guild deletion fail; invalid parameter");
    }
    else
    {
        dbOk = LobbyDB::DeleteGuild(dbrtn, guildid, LobbyDaemon::_instance->_config->_guildNameReuseLimitDuration);
    }
    if (!dbOk)
    {
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 1552,
                   L"[gamed], handle delete guild notify fail; db fail, dbrtn:%d, channel-id:%I64d, game-tid:0x%I64X, "
                   L"guild-id:0x%I64X",
                   dbrtn, LgpChannelId(channel), gametid, guildid);
        return true;
    }
    Log::Write(Log::LT_DEBUG, HANDLER_FILE, 1556,
               L"[gamed], handle delete guild notify ok, channel-id:%I64d, game-tid:0x%I64X, guild-id:0x%I64X",
               LgpChannelId(channel), gametid, guildid);
    return true;
}

#pragma comment(linker, "/INCLUDE:?HandleLobbyGame_ChangeCharacterAppearanceOk@@YA_NPEAVSharedChannel@@PEBVPacket@@@Z")   // LIFT: keep until the caller is lifted (0x8e520)
// 0x8e520
bool HandleLobbyGame_ChangeCharacterAppearanceOk(SharedChannel* channel, Packet const* packet)
{
    return HandleShowcaseOk<ChangeCharacterAppearanceOkParam>(channel, packet, JOB_TASK_CHANGE_APPEARANCE_OK,
                                L"[gamed], handle change-character-appearance-ok fail; decompose fail, channel-id:%I64d, tid:0x%I64X, "
                                L"showcase-data-size:%d",
                                1579,
                                L"[gamed], handle change-character-appearance-ok fail; decompose fail, channel-id:%I64d, tid:0x%I64X, "
                                L"showcase-data-size:%d",
                                1585,
                                L"[gamed], handle change-character-appearance-ok fail; execute job fail, channel-id:%I64d, tid:0x%I64X, "
                                L"showcase-data-size:%d",
                                1594,
                                L"[gamed], handle change-character-appearance-ok ok, channel-id:%I64d, tid:0x%I64X, "
                                L"showcase-data-size:%d",
                                1598);
}

#pragma comment(linker, "/INCLUDE:?HandleLobbyGame_ChangeCharacterAppearanceFail@@YA_NPEAVSharedChannel@@PEBVPacket@@@Z")   // LIFT: keep until the caller is lifted (0x8e820)
// 0x8e820
bool HandleLobbyGame_ChangeCharacterAppearanceFail(SharedChannel* channel, Packet const* packet)
{
    PacketDecomposer pdr;
    SetupDecomposer(&pdr, "hqE", 3);
    unsigned long long tid = 0;
    short reason = 0;
    if (packet->Decompose(&pdr, 2, &tid, &reason) == 0)
    {
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 1617,
                   L"[gamed], handle change-character-appearance-fail fail; decompose fail, channel-id:%I64d, tid:0x%I64X, reason:%d",
                   LgpChannelId(channel), tid, static_cast<int>(reason));
        return true;
    }
    if (!LobbyDaemon::_instance->_jobMgr->ExecuteW(tid, JOB_TASK_CHANGE_APPEARANCE_FAIL, &reason))
    {
        // BUG: 0x8e820 original logs 'appearance-ok' in the Fail handler (copy-paste); kept for parity
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 1623,
                   L"[gamed], handle change-character-appearance-ok fail; execute job fail, channel-id:%I64d, tid:0x%I64X, "
                   L"reason:%d",
                   LgpChannelId(channel), tid, static_cast<int>(reason));
        return true;
    }
    Log::Write(Log::LT_DEBUG, HANDLER_FILE, 1627,
               L"[gamed], handle change-character-appearance-fail ok, channel-id:%I64d, tid:0x%I64X, reason:%d",
               LgpChannelId(channel), tid, static_cast<int>(reason));
    return true;
}

#pragma comment(linker, "/INCLUDE:?HandleLobbyGame_ChangeCharacterSexOk@@YA_NPEAVSharedChannel@@PEBVPacket@@@Z")   // LIFT: keep until the caller is lifted (0x8eab0)
// 0x8eab0
bool HandleLobbyGame_ChangeCharacterSexOk(SharedChannel* channel, Packet const* packet)
{
    return HandleShowcaseOk<ChangeCharacterSexOkParam>(channel, packet, JOB_TASK_CHANGE_SEX_OK,
                                L"[gamed], handle change-character-sex-ok fail; decompose fail, channel-id:%I64d, tid:0x%I64X, "
                                L"showcase-data-size:%d",
                                1650,
                                L"[gamed], handle change-character-sex-ok fail; decompose fail, channel-id:%I64d, tid:0x%I64X, "
                                L"showcase-data-size:%d",
                                1656,
                                L"[gamed], handle change-character-sex-ok fail; execute job fail, channel-id:%I64d, tid:0x%I64X, "
                                L"showcase-data-size:%d",
                                1665,
                                L"[gamed], handle change-character-sex-ok ok, channel-id:%I64d, tid:0x%I64X, "
                                L"showcase-data-size:%d",
                                1669);
}

#pragma comment(linker, "/INCLUDE:?HandleLobbyGame_ChangeCharacterSexFail@@YA_NPEAVSharedChannel@@PEBVPacket@@@Z")   // LIFT: keep until the caller is lifted (0x8edb0)
// 0x8edb0
bool HandleLobbyGame_ChangeCharacterSexFail(SharedChannel* channel, Packet const* packet)
{
    PacketDecomposer pdr;
    SetupDecomposer(&pdr, "hqE", 3);
    unsigned long long tid = 0;
    short reason = 0;
    if (packet->Decompose(&pdr, 2, &tid, &reason) == 0)
    {
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 1688,
                   L"[gamed], handle change-character-sex-fail fail; decompose fail, channel-id:%I64d, tid:0x%I64X, reason:%d",
                   LgpChannelId(channel), tid, static_cast<int>(reason));
        return true;
    }
    if (!LobbyDaemon::_instance->_jobMgr->ExecuteW(tid, JOB_TASK_CHANGE_SEX_FAIL, &reason))
    {
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 1694,
                   L"[gamed], handle change-character-sex-fail fail; execute job fail, channel-id:%I64d, tid:0x%I64X, "
                   L"reason:%d",
                   LgpChannelId(channel), tid, static_cast<int>(reason));
        return true;
    }
    Log::Write(Log::LT_DEBUG, HANDLER_FILE, 1698,
               L"[gamed], handle change-character-sex-fail ok, channel-id:%I64d, tid:0x%I64X, reason:%d",
               LgpChannelId(channel), tid, static_cast<int>(reason));
    return true;
}

#pragma comment(linker, "/INCLUDE:?HandleLobbyGame_ChangeCharacterRaceOk@@YA_NPEAVSharedChannel@@PEBVPacket@@@Z")   // LIFT: keep until the caller is lifted (0x8f040)
// 0x8f040
bool HandleLobbyGame_ChangeCharacterRaceOk(SharedChannel* channel, Packet const* packet)
{
    return HandleShowcaseOk<ChangeCharacterRaceOkParam>(channel, packet, JOB_TASK_CHANGE_RACE_OK,
                                L"[gamed], handle change-character-race-ok fail; decompose fail, channel-id:%I64d, tid:0x%I64X, "
                                L"showcase-data-size:%d",
                                1721,
                                L"[gamed], handle change-character-race-ok fail; decompose fail, channel-id:%I64d, tid:0x%I64X, "
                                L"showcase-data-size:%d",
                                1727,
                                L"[gamed], handle change-character-race-ok fail; execute job fail, channel-id:%I64d, tid:0x%I64X, "
                                L"showcase-data-size:%d",
                                1736,
                                L"[gamed], handle change-character-race-ok ok, channel-id:%I64d, tid:0x%I64X, "
                                L"showcase-data-size:%d",
                                1740);
}

#pragma comment(linker, "/INCLUDE:?HandleLobbyGame_ChangeCharacterRaceFail@@YA_NPEAVSharedChannel@@PEBVPacket@@@Z")   // LIFT: keep until the caller is lifted (0x8f340)
// 0x8f340
bool HandleLobbyGame_ChangeCharacterRaceFail(SharedChannel* channel, Packet const* packet)
{
    PacketDecomposer pdr;
    SetupDecomposer(&pdr, "hqE", 3);
    unsigned long long tid = 0;
    short reason = 0;
    if (packet->Decompose(&pdr, 2, &tid, &reason) == 0)
    {
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 1759,
                   L"[gamed], handle change-character-race-fail fail; decompose fail, channel-id:%I64d, tid:0x%I64X, reason:%d",
                   LgpChannelId(channel), tid, static_cast<int>(reason));
        return true;
    }
    if (!LobbyDaemon::_instance->_jobMgr->ExecuteW(tid, JOB_TASK_CHANGE_RACE_FAIL, &reason))
    {
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 1765,
                   L"[gamed], handle change-character-race-fail fail; execute job fail, channel-id:%I64d, tid:0x%I64X, "
                   L"reason:%d",
                   LgpChannelId(channel), tid, static_cast<int>(reason));
        return true;
    }
    Log::Write(Log::LT_DEBUG, HANDLER_FILE, 1769,
               L"[gamed], handle change-character-race-fail ok, channel-id:%I64d, tid:0x%I64X, reason:%d",
               LgpChannelId(channel), tid, static_cast<int>(reason));
    return true;
}

#pragma comment(linker, "/INCLUDE:?HandleLobbyGame_RenameCharacterOk@@YA_NPEAVSharedChannel@@PEBVPacket@@@Z")   // LIFT: keep until the caller is lifted (0x8f5d0)
// 0x8f5d0
bool HandleLobbyGame_RenameCharacterOk(SharedChannel* channel, Packet const* packet)
{
    PacketDecomposer pdr;
    SetupDecomposer(&pdr, "hqq", 3);
    unsigned long long tid = 0;
    RenameCharacterOkParam param = {};
    if (packet->Decompose(&pdr, 2, &tid, &param) == 0)
    {
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 1790,
                   L"[gamed], handle rename-character-ok fail; decompose fail, channel-id:%I64d, tid:0x%I64X, pcid:0x%I64X",
                   LgpChannelId(channel), tid, param.pcid);
        return true;
    }
    if (!LobbyDaemon::_instance->_jobMgr->ExecuteW(tid, JOB_TASK_RENAME_CHARACTER_OK, &param))
    {
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 1796,
                   L"[gamed], handle rename-character-ok fail; execute job fail, channel-id:%I64d, tid:0x%I64X, "
                   L"pcid:0x%I64X",
                   LgpChannelId(channel), tid, param.pcid);
        return true;
    }
    Log::Write(Log::LT_DEBUG, HANDLER_FILE, 1800,
               L"[gamed], handle rename-character-ok ok, channel-id:%I64d, tid:0x%I64X, pcid:0x%I64X",
               LgpChannelId(channel), tid, param.pcid);
    return true;
}

#pragma comment(linker, "/INCLUDE:?HandleLobbyGame_RenameCharacterFail@@YA_NPEAVSharedChannel@@PEBVPacket@@@Z")   // LIFT: keep until the caller is lifted (0x8f870)
// 0x8f870
bool HandleLobbyGame_RenameCharacterFail(SharedChannel* channel, Packet const* packet)
{
    PacketDecomposer pdr;
    SetupDecomposer(&pdr, "hqE", 3);
    unsigned long long tid = 0;
    short reason = 0;
    if (packet->Decompose(&pdr, 2, &tid, &reason) == 0)
    {
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 1819,
                   L"[gamed], handle rename-character-fail fail; decompose fail, channel-id:%I64d, tid:0x%I64X, reason:%d",
                   LgpChannelId(channel), tid, static_cast<int>(reason));
        return true;
    }
    if (!LobbyDaemon::_instance->_jobMgr->ExecuteW(tid, JOB_TASK_RENAME_CHARACTER_FAIL, &reason))
    {
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 1825,
                   L"[gamed], handle rename-character-fail fail; execute job fail, channel-id:%I64d, tid:0x%I64X, "
                   L"reason:%d",
                   LgpChannelId(channel), tid, static_cast<int>(reason));
        return true;
    }
    Log::Write(Log::LT_DEBUG, HANDLER_FILE, 1829,
               L"[gamed], handle rename-character-fail ok, channel-id:%I64d, tid:0x%I64X, reason:%d",
               LgpChannelId(channel), tid, static_cast<int>(reason));
    return true;
}

// 0x8fb00
// LIFT: the body needs ExtendJumpingCharacterCreationQuotaJob::_pool (.data 0x2040a0) and ObjPool::Checkout (0x628c0). The LobbyDaemon ObjectPool module is not lifted. ❓
bool HandleLobbyGame_ExtendJumpingCharacterCreationQuotaWithAccountInventoryItemReq(SharedChannel*, Packet const*)
{
    LIFT_STUB(0x8fb00);
}

// 0x8ffc0
// LIFT: the body needs UpgradeJumpingCharacterStateJob::_pool (0x204150) and ObjPool::Checkout (0x628c0). The LobbyDaemon ObjectPool module is not lifted.
bool HandleLobbyGame_UpgradeJumpingCharacterStateWithCreationQuotaReq(SharedChannel*, Packet const*)
{
    LIFT_STUB(0x8ffc0);
}

// 0x903d0
// LIFT: the body needs UpgradeJumpingCharacterStateJob::_pool (0x204150) and ObjPool::Checkout (0x628c0). The LobbyDaemon ObjectPool module is not lifted.
bool HandleLobbyGame_UpdateJumpingCharacterStateReq(SharedChannel*, Packet const*)
{
    LIFT_STUB(0x903d0);
}

#pragma comment(linker, "/INCLUDE:?HandleLobbyGame_SetAppDataNotify@@YA_NPEAVSharedChannel@@PEBVPacket@@@Z")   // LIFT: keep until the caller is lifted (0x907e0)
// 0x907e0
// LIFT: PDB StsMsgLib::_StsMsgRequestPresenceSetAppData (sizeof 0x38). The type is not in a LobbyDaemon header yet.
namespace StsMsgLib
{
struct _StsMsgRequestPresenceSetAppData : public _StsMsgRequest
{
    struct AppData
    {
        struct Field
        {
            char* pszKey;
            wchar_t* pwszValue;
        };
        Field* pFields;
        int nFieldCount;
    };
    id128* pUserId;
    id128* pAppId;
    AppData appData;
};
static_assert(sizeof(_StsMsgRequestPresenceSetAppData) == 0x38, "sizeof _StsMsgRequestPresenceSetAppData");
static_assert(offsetof(_StsMsgRequestPresenceSetAppData, appData) == 0x28, "_StsMsgRequestPresenceSetAppData::appData");
}  // namespace StsMsgLib

bool HandleLobbyGame_SetAppDataNotify(SharedChannel* channel, Packet const* packet)
{
    // LIFT: inlined RepeatPacketDecomposer setup. The command is skipped (index 1, offset 2).
    RepeatPacketDecomposer pdr;
    pdr.format = "hqCss;";
    pdr.len = 6;
    pdr.index = 1;
    pdr.offset = 2;
    pdr.top = -1;

    unsigned long long pcid = 0;
    StsMsgLib::_StsMsgRequestPresenceSetAppData::AppData::Field* fields = nullptr;
    int fieldCount = 0;

    if (packet->Decompose(&pdr, 1, &pcid) == 0)
    {
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 2039,
                   L"[gamed], handle set-app-data notify fail; decompose pc-id fail, channel-id:%I64d, pcid:0x%I64X",
                   LgpChannelId(channel), pcid);
        return true;
    }
    if (!LobbyDaemon::_instance->_config->_enableFriendMessageNotification)
    {
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 2045,
                   L"[gamed], handle set-app-data-notify fail; configuration disabled, channel-id:%I64d, "
                   L"pcid:0x%I64X",
                   LgpChannelId(channel), pcid);
        return true;
    }

    // LIFT: inlined repeat count read of PacketUtil.cpp (assert at line 241). The count is kept in a 16-bit value.
    if (packet == nullptr)
        assertCrash(L"source\\PacketUtil.cpp", "source\\PacketUtil.cpp", 241);
    short const count = static_cast<short>(pdr.PushRepeatCount(
        reinterpret_cast<char const*>(packet->CurHeader + 1) + pdr.offset,
        static_cast<unsigned short>(packet->CurHeader->size - 2) - pdr.offset));
    bool decomposed = true;
    if (count > 0)
    {
        fieldCount = count;
        fields = static_cast<StsMsgLib::_StsMsgRequestPresenceSetAppData::AppData::Field*>(
            Memory::_Manager[2]->AllocZero(16 * static_cast<long long>(count), HANDLER_FILE, 2053));
        for (int i = 0; i < count; ++i)
        {
            Packet::VarStr key = {nullptr, nullptr};
            Packet::VarStr value = {nullptr, nullptr};
            if (packet->Decompose(&pdr, &key) == 0)
            {
                Log::Write(Log::LT_ERROR, HANDLER_FILE, 2065,
                           L"[gamed], handle set-app-data notify fail; decompose app-data-key fail, key-index:%d, "
                           L"channel-id:%I64d, pcid:0x%I64X",
                           i, LgpChannelId(channel), pcid);
                decomposed = false;
                break;
            }
            if (packet->Decompose(&pdr, &value) == 0)
            {
                Log::Write(Log::LT_ERROR, HANDLER_FILE, 2071,
                           L"[gamed], handle set-app-data notify fail; decompose app-data-value fail, "
                           L"value-index:%d, channel-id:%I64d, pcid:0x%I64X",
                           i, LgpChannelId(channel), pcid);
                decomposed = false;
                break;
            }
            if (*key.len <= 0)
            {
                Log::Write(Log::LT_ERROR, HANDLER_FILE, 2077,
                           L"[gamed], handle set-app-data notify fail; invalid key length, key-index:%d, "
                           L"key-length:%d, channel-id:%I64d, pcid:0x%I64X",
                           i, *key.len, LgpChannelId(channel), pcid);
                decomposed = false;
                break;
            }
            if (*value.len < 0)
            {
                Log::Write(Log::LT_ERROR, HANDLER_FILE, 2083,
                           L"[gamed], handle set-app-data notify fail; invalid value length, value-index:%d, "
                           L"value-length:%d, channel-id:%I64d, pcid:0x%I64X",
                           i, *value.len, LgpChannelId(channel), pcid);
                decomposed = false;
                break;
            }
            fields[i].pszKey = static_cast<char*>(
                Memory::_Manager[2]->AllocZero(*key.len + 1, HANDLER_FILE, 2087));
            fields[i].pwszValue = static_cast<wchar_t*>(
                Memory::_Manager[2]->AllocZero(2LL * (*value.len + 1), HANDLER_FILE, 2088));
            String::UnicodeToMultibyte(fields[i].pszKey, *key.len + 1, key.str);
            wcsncpy(fields[i].pwszValue, value.str, *value.len);
            // LIFT: inlined decrement of the repeat count of RepeatPacketDecomposer.
            pdr.index = pdr.start[pdr.top] + 1;
            --pdr.counts[pdr.top];
        }
    }

    if (decomposed)
    {
        // LIFT: inlined end of repeat of PacketUtil.cpp (assert at line 248: the repeat format must start with 'C').
        if (pdr.top < 0 || pdr.format[pdr.start[pdr.top]] != 'C')
            assertCrash(L"source\\PacketUtil.cpp", "source\\PacketUtil.cpp", 248);
        static_cast<PacketFormatIterator&>(pdr).skipRepeatFormat();  // LIFT: virtual call as in the original (0x907e0)
        --pdr.top;

        // LIFT: the original tests only the raw channel here, not the shared channel (0x907e0).
        short const wid = channel->_rawChannel == nullptr ? 0 : static_cast<short>(channel->_rawChannel->GetId());
        CliSession* const session = LobbyDaemon::_instance->_clisessionMgr->Select_index_pcid(wid, pcid);
        if (session == nullptr)
        {
            Log::Write(Log::LT_ERROR, HANDLER_FILE, 2101,
                       L"[gamed], handle set-app-data notify fail; cli-session not found, channel-id:%I64d, "
                       L"pcid:0x%I64X",
                       LgpChannelId(channel), pcid);
        }
        else
        {
            NPGameServiceChannel* const gameServChannel = LobbyDaemon::_instance->_npServchmgr->_gameServChannel;
            if (gameServChannel == nullptr)
            {
                Log::Write(Log::LT_ERROR, HANDLER_FILE, 2108,
                           L"[gamed], handle set-app-data notify fail; np N/A, channel-id:%I64d, pcid:0x%I64X",
                           LgpChannelId(channel), pcid);
            }
            else
            {
                StsMsgLib::_StsMsgRequestPresenceSetAppData msg;
                msg.msgInfo.eCmd = StsMsgLib::COMMAND_SRV_PRES_SET_APP_DATA;
                msg.msgInfo.msgType = StsMsgLib::MESSAGE_TYPE_REQUEST;
                msg.msgInfo.nTxnId = 0;
                msg.pUserId = &session->_acb._id;
                msg.pAppId = &BnsCommonConfig::Config->_npAppId;
                msg.appData.pFields = fields;
                msg.appData.nFieldCount = fieldCount;
                if (gameServChannel->SendMsg(&msg, true, nullptr))
                {
                    Log::Write(Log::LT_DEBUG, HANDLER_FILE, 2118,
                               L"[gamed], handle set-app-data notify ok, cli-key:0x%I64X, channel-id:%I64d, "
                               L"pcid:0x%I64X",
                               session->_clikey, LgpChannelId(channel), pcid);
                }
                else
                {
                    Log::Write(Log::LT_ERROR, HANDLER_FILE, 2114,
                               L"[gamed], handle set-app-data notify fail; send to np fail, cli-key:0x%I64X, "
                               L"channel-id:%I64d, pcid:0x%I64X",
                               session->_clikey, LgpChannelId(channel), pcid);
                }
            }
            session->removeReferenceCount(HANDLER_FILE, 2122);
        }
    }

    // LIFT: free the key and value copies. The unused entries are zero (AllocZero).
    if (fields != nullptr)
    {
        for (int i = 0; i < fieldCount; ++i)
        {
            if (fields[i].pszKey != nullptr)
            {
                Memory::_Manager[2]->Free(fields[i].pszKey, HANDLER_FILE, 2129);
                fields[i].pszKey = nullptr;
            }
            if (fields[i].pwszValue != nullptr)
            {
                Memory::_Manager[2]->Free(fields[i].pwszValue, HANDLER_FILE, 2131);
                fields[i].pwszValue = nullptr;
            }
        }
        Memory::_Manager[2]->Free(fields, HANDLER_FILE, 2134);
    }
    return true;
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
bool HandleLobbyGame_AuctionEscrowOk(SharedChannel* channel, Packet const* packet)
{
    PacketDecomposer pdr;
    SetupDecomposer(&pdr, "hq", 2);
    unsigned long long tid = 0;
    if (packet->Decompose(&pdr, 1, &tid) == 0)
    {
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 2418,
                   L"[gamed], handle auction escrow ok fail; decompose fail, wid:%d, tid:0x%I64X", LgpWid(channel), tid);
        return true;
    }
    // LIFT: the task id 131 has no PDB name. ❓
    if (!LobbyDaemon::_instance->_jobMgr->ExecuteW(tid, 131, nullptr))
    {
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 2423,
                   L"[gamed], handle auction escrow ok fail; execute job fail, wid:%d, tid:0x%I64X", LgpWid(channel), tid);
        return true;
    }
    Log::Write(Log::LT_DEBUG, HANDLER_FILE, 2427, L"[gamed], handle auction escrow ok ok, wid:%d, tid:0x%I64X",
               LgpWid(channel), tid);
    return true;
}

// 0x92400
bool HandleLobbyGame_AuctionEscrowFail(SharedChannel* channel, Packet const* packet)
{
    PacketDecomposer pdr;
    SetupDecomposer(&pdr, "hqE", 3);
    unsigned long long tid = 0;
    short reason = 0;
    if (packet->Decompose(&pdr, 2, &tid, &reason) == 0)
    {
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 2446,
                   L"[gamed], handle auction escrow fail fail; decompose fail, wid:%d, tid:0x%I64X, reason:%d",
                   LgpWid(channel), tid, static_cast<int>(reason));
        return true;
    }
    // LIFT: the task id 132 has no PDB name. ❓
    if (!LobbyDaemon::_instance->_jobMgr->ExecuteW(tid, 132, &reason))
    {
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 2451,
                   L"[gamed], handle auction escrow fail fail; execute job fail, wid:%d, tid:0x%I64X, reason:%d",
                   LgpWid(channel), tid, static_cast<int>(reason));
        return true;
    }
    Log::Write(Log::LT_DEBUG, HANDLER_FILE, 2455,
               L"[gamed], handle auction escrow fail ok, wid:%d, tid:0x%I64X, reason:%d", LgpWid(channel), tid,
               static_cast<int>(reason));
    return true;
}

// 0x926a0
bool HandleLobbyGame_AuctionBidReq(SharedChannel*, Packet const*)
{
    LIFT_STUB(0x926a0);
}

// 0x92ca0
bool HandleLobbyGame_GetGradeListReq(SharedChannel* sharedChannel, Packet const* packet)
{
    GamedChannel* const channel = static_cast<GamedChannel*>(sharedChannel);
    PacketDecomposer pdr;
    SetupDecomposer(&pdr, "hqQqi", 5);
    unsigned long long gameTid = 0;
    char locationHint = 0;
    unsigned long long pcid = 0;
    int reqRevision = 0;
    if (packet->Decompose(&pdr, 4, &gameTid, &locationHint, &pcid, &reqRevision) == 0)
    {
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 2520,
                   L"[gamed], handle get grade list req fail; decompose fail, wid:%d, game-tid:0x%I64X, location-hint:%d, pcid:0x%I64X, req-revision:%d",
                   LgpWid(channel), gameTid, static_cast<int>(locationHint), pcid, reqRevision);
        return true;
    }
    // LIFT: the original does not check channel for null after the decompose (0x92ca0).
    short wid = channel->_rawChannel != nullptr ? static_cast<short>(channel->_rawChannel->GetId()) : 0;
    CliSession* cs = LobbyDaemon::_instance->_clisessionMgr->Select_index_pcid(wid, pcid);
    if (cs == nullptr)
    {
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 2526,
                   L"[gamed], handle get grade list req fail; no such session, wid:%d, game-tid:0x%I64X, location-hint:%d, pcid:0x%I64X, req-revision:%d",
                   channel->_rawChannel != nullptr ? static_cast<int>(static_cast<short>(channel->_rawChannel->GetId())) : 0,
                   gameTid, static_cast<int>(locationHint), pcid, reqRevision);
        channel->SendGetGradeListFail(gameTid, locationHint, pcid, 5);
        return true;
    }
    cs->HandleGameGetGradeList(channel, gameTid, locationHint, pcid, reqRevision);
    Log::Write(Log::LT_DEBUG, HANDLER_FILE, 2533,
               L"[gamed], handle get grade list req ok, wid:%d, game-tid:0x%I64X, location-hint:%d, pcid:0x%I64X, req-revision:%d",
               channel->_rawChannel != nullptr ? static_cast<int>(static_cast<short>(channel->_rawChannel->GetId())) : 0,
               gameTid, static_cast<int>(locationHint), pcid, reqRevision);
    cs->removeReferenceCount(HANDLER_FILE, 2535);
    return true;
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
bool HandleLobbyGame_BoastEventInWorldNotify(SharedChannel* channel, Packet const* packet)
{
    short cmd = 0;
    short worldClusterId = 0;
    short boastEventDataId = 0;
    wchar_t pcName[40];
    pcName[0] = 0;
    if (packet->Decompose("hhsh", &cmd, &worldClusterId, pcName, 33, &boastEventDataId) == 0)
    {
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 2880, L"[gamed], handle boast event in world notify fail; decompose fail");
        return true;
    }
    InfoGateChannelManager* infogatechmgr = LobbyDaemon::_instance->_infogatechmgr;
    if (infogatechmgr == nullptr)
    {
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 2887,
                   L"[gamed], handle boast event in world notify fail; info-gate channel manager not available, channel-id:%I64d, world-cluster-id:%d, pc-name:%s, boast-event-dataId:%d",
                   LgpChannelId(channel), static_cast<int>(worldClusterId), pcName, static_cast<int>(boastEventDataId));
        return true;
    }
    infogatechmgr->BroadcastBoastEventInWorldNotify(worldClusterId, pcName, boastEventDataId);
    Log::Write(Log::LT_DEBUG, HANDLER_FILE, 2893,
               L"[gamed], handle boast event in world notify ok, channel-id:%I64d, world-cluster-id:%d, pc-name:%s, boast-event-dataId:%d",
               LgpChannelId(channel), static_cast<int>(worldClusterId), pcName, static_cast<int>(boastEventDataId));
    return true;
}

// 0x94910
bool HandleLobbyGame_TakeAccountTimeBasedPlayRewardReq(SharedChannel*, Packet const*)
{
    LIFT_STUB(0x94910);
}

// 0x94df0
bool HandleLobbyGame_UpdateAccountExpReq(SharedChannel* sharedChannel, Packet const* packet)
{
    GamedChannel* const channel = static_cast<GamedChannel*>(sharedChannel);

    // LIFT: inlined RepeatPacketDecomposer setup. The command is skipped (index 1, offset 2).
    RepeatPacketDecomposer rpd;
    rpd.format = "hqqqqiq";
    rpd.len = 7;
    rpd.index = 1;
    rpd.offset = 2;
    rpd.top = -1;

    unsigned long long gametid = 0;
    unsigned long long pcid = 0;
    unsigned long long clikey = 0;
    GameAccountExpInfo::ExpInfo accExpInfo;
    memset(&accExpInfo, 0, sizeof(accExpInfo));

    if (packet->Decompose(&rpd, 3, &gametid, &pcid, &clikey) == 0)
    {
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 2965,
                   L"[gamed], handle update account-exp fail; decompose fail, channel-id:%I64d, game-tid:0x%I64X, pcid:0x%I64X, cli-key:0x%I64X",
                   LgpChannelId(channel), gametid, pcid, clikey);
        return true;
    }
    if (packet->Decompose(&rpd, 3, &accExpInfo.exp, &accExpInfo.expQuotaPerDay, &accExpInfo.lastUpdateTime) == 0)
    {
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 2970,
                   L"[gamed], handle update account-exp fail; decompose(AccountExpInfo) fail, channel-id:%I64d, game-tid:0x%I64X, pcid:0x%I64X, cli-key:0x%I64X",
                   LgpChannelId(channel), gametid, pcid, clikey);
        return true;
    }
    // LIFT: the original does not check channel for null after the decompose (0x94df0).
    unsigned long long channelId = 0;
    short wid = channel->_rawChannel != nullptr ? static_cast<short>(channel->_rawChannel->GetId()) : 0;
    CliSession* cs = LobbyDaemon::_instance->_clisessionMgr->Select_index_pcid(wid, pcid);
    if (cs == nullptr)
    {
        if (channel->_rawChannel != nullptr)
            channelId = channel->_rawChannel->GetId();
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 2977,
                   L"[gamed], handle update account-exp fail; no such cli-session, channel-id:%I64d, game-tid:0x%I64X, pcid:0x%I64X, cli-key:0x%I64X",
                   channelId, gametid, pcid, clikey);
        channel->SendUpdateAccountExpFail(gametid, pcid, 5);
        return true;
    }
    if (clikey != cs->_clikey)
    {
        if (channel->_rawChannel != nullptr)
            channelId = channel->_rawChannel->GetId();
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 2984,
                   L"[gamed], handle update account-exp fail; cli-key mismatch, found-cli-key:0x%I64X, channel-id:%I64d, game-tid:0x%I64X, pcid:0x%I64X, cli-key:0x%I64X",
                   cs->_clikey, channelId, gametid, pcid, clikey);
        channel->SendUpdateAccountExpFail(gametid, pcid, 5);
        cs->removeReferenceCount(HANDLER_FILE, 2986);
        return true;
    }
    if (!cs->UpdateAccountExp(pcid, accExpInfo))
    {
        int error = TLobbyError;
        if (channel->_rawChannel != nullptr)
            channelId = channel->_rawChannel->GetId();
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 2993,
                   L"[gamed], handle update account-exp fail; update fail, error:%s, channel-id:%I64d, game-tid:0x%I64X, pcid:0x%I64X, cli-key:0x%I64X",
                   LobbyErrorText(error), channelId, gametid, pcid, clikey);
        channel->SendUpdateAccountExpFail(gametid, pcid, UpdateFailCode(error));
        cs->removeReferenceCount(HANDLER_FILE, 3007);
        return true;
    }
    channel->SendUpdateAccountExpOk(gametid, pcid);
    if (channel->_rawChannel != nullptr)
        channelId = channel->_rawChannel->GetId();
    Log::Write(Log::LT_DEBUG, HANDLER_FILE, 3013,
               L"[gamed], handle update account-exp ok, channel-id:%I64d, game-tid:0x%I64X, pcid:0x%I64X, cli-key:0x%I64X",
               channelId, gametid, pcid, clikey);
    cs->removeReferenceCount(HANDLER_FILE, 3015);
    return true;
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
