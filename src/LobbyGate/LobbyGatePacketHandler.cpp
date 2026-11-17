// LobbyGatePacketHandler.obj (LobbyGate PDB).
#include "Network.h"
#include "LobbyGatePacketHandler.h"
#include "LobbyDPacketHandler.h"
#include "Session.h"
#include "Connection.h"
#include "Packet.h"
#include "PacketBuffer.h"
#include "Log.h"
#include "Daemon.h"
#include "StringUtil.h"
#include "Client.h"
#include "FragmentPacket.h"
#include "LobbyGate.h"
#include "LobbyDChannel.h"
#include "ContentsRuleConfigDefinition.h"
#include "WorldListManager.h"
#include "PcCafeMileageFeverTimeScheduleList.h"

static wchar_t const* const HANDLER_FILE = L"LobbyGatePacketHandler.cpp";  // LIFT: No PDB symbol. The binary uses the literal.
static wchar_t const* const CHANNEL_H_FILE =                                // LIFT: No PDB symbol. The binary uses the literal.
    L"E:\\DailyBuild02\\LobbyGate-Common-0.0.348\\depot\\Branch\\348NC\\Program\\Server\\BloodLib\\include\\Channel.h";

// ❓ The GUID fields of an id128 in the order of the "%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X" format.
#define ID128_ARGS(x)                                                                                     \
    *reinterpret_cast<unsigned int const*>(&(x).guid[0]),                                                 \
        static_cast<unsigned int>(*reinterpret_cast<unsigned short const*>(&(x).guid[4])),                \
        static_cast<unsigned int>(*reinterpret_cast<unsigned short const*>(&(x).guid[6])), (x).guid[8],   \
        (x).guid[9], (x).guid[10], (x).guid[11], (x).guid[12], (x).guid[13], (x).guid[14], (x).guid[15]

// 0x91b00
void* AnyAuthedLobbyGatePacketHandlerList[110] = {
    nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
    reinterpret_cast<void*>(&HandleLobbyGate_PingReq),  // 9
    nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,  // 10..19
    nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,  // 20..29
    nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,  // 30..39
    nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,  // 40..49
    nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,  // 50..59
    nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,  // 60..69
    nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,  // 70..79
    nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,  // 80..89
    nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,  // 90..99
    nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,                                      // 100..105
    reinterpret_cast<void*>(&HandleLobbyGate_ContentsRuleListReq),  // 106
    nullptr, nullptr, nullptr,
};

// 0x91e70
void* NotAuthedLobbyGatePacketHandlerList[110] = {
    nullptr,
    reinterpret_cast<void*>(&HandleLobbyGate_HelloReq),  // 1
    nullptr,
    reinterpret_cast<void*>(&HandleLobbyGate_LoginWithNPTokenReq),  // 3
    nullptr, nullptr,
    reinterpret_cast<void*>(&HandleLobbyGate_LoginWithLobbyTokenReq),  // 6
};

#define LG_NOP reinterpret_cast<void*>(&HandleLobbyLobbyGate_ChangedGradeLevelNotify)  // LIFT: folded `return true;` body

// 0x921e0. The PacketHandler of ClientSessionHandler (0x6b70) calls the handlers for 24 and 103 and calls
// HandleLobbyGate_BypassPacket for all other entries that are not null.
void* AuthedLobbyGatePacketHandlerList[110] = {
    nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,  // 0..9
    nullptr, nullptr, LG_NOP, LG_NOP, nullptr, nullptr, nullptr, LG_NOP, nullptr, nullptr,    // 10..19
    LG_NOP, nullptr, nullptr, nullptr,
    reinterpret_cast<void*>(&HandleLobbyGate_GetWorldInfoListReq),  // 24
    nullptr, nullptr, LG_NOP, nullptr, nullptr,                     // 25..29
    LG_NOP, nullptr, nullptr, LG_NOP, nullptr, nullptr, LG_NOP, nullptr, nullptr, LG_NOP,     // 30..39
    nullptr, nullptr, nullptr, LG_NOP, nullptr, nullptr, LG_NOP, nullptr, nullptr, LG_NOP,    // 40..49
    nullptr, nullptr, LG_NOP, nullptr, nullptr, nullptr, LG_NOP, nullptr, nullptr, LG_NOP,    // 50..59
    nullptr, nullptr, LG_NOP, nullptr, nullptr, LG_NOP, nullptr, nullptr, LG_NOP, nullptr,    // 60..69
    nullptr, LG_NOP, nullptr, nullptr, LG_NOP, nullptr, nullptr, LG_NOP, nullptr, nullptr,    // 70..79
    LG_NOP, nullptr, nullptr, LG_NOP, nullptr, nullptr, LG_NOP, nullptr, nullptr, LG_NOP,     // 80..89
    nullptr, nullptr, LG_NOP, nullptr, nullptr, LG_NOP, nullptr, nullptr, LG_NOP, nullptr,    // 90..99
    nullptr, nullptr, nullptr,
    reinterpret_cast<void*>(&HandleLobbyGate_GetPcCafeMileageFeverTimeScheduleListReq),  // 103
    nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
};

#undef LG_NOP

// 0x142a0
bool HandleLobbyGate_PingReq(Session const* session, Packet const* packet)
{
    Log::Write(Log::LT_DEBUG, HANDLER_FILE, 31, L"[lobbygate], ping recv ok, SessionId:0x%I64X", session->_id);
    return true;
}

// 0x142e0
bool HandleLobbyGate_ContentsRuleListReq(Session* session, Packet const* packet)
{
    Packet sendPacket{};  // LIFT: inlined constructor
    long long* extraData = static_cast<long long*>(session->_extraData);
    long long lastSendTime = extraData != nullptr ? *extraData : 0;
    long long now = static_cast<long long>(GetTickCount64()) - Daemon::Instance->StartSystemTick64;
    if (lastSendTime <= 0 || lastSendTime <= ContentsRuleConfig::ConfigLastReloadTime || now <= 30000 ||
        now - lastSendTime >= 30000)
    {
        if (ContentsRuleConfig::ListPacket != nullptr)
            sendPacket.Copy(&ContentsRuleConfig::ListPacket->packet);
        if (extraData != nullptr)
            *extraData = now;
        // BUG: 0x1438a ListHead is null when ContentsRuleConfig::ListPacket is null.
        PacketBuffer* listHead = sendPacket.ListHead;
        listHead->encrypt(session->_currentCrypt, session->_security3rd);
        PacketBuffer const* list = listHead;
        session->_lock.Enter();
        session->send(&list, 1);
        session->_lock.Leave();
        Log::Write(Log::LT_DEBUG, HANDLER_FILE, 47, L"[lobbygate], sent LobbyGate_ContentsRuleListOk, SessionId:0x%I64X",
                   session->_id);
    }
    else
    {
        session->Send("hE", 108, 234);  // ❓ the pseudocode shows only 108; 234 is the reason in the log
        Log::Write(Log::LT_DEBUG, HANDLER_FILE, 52,
                   L"[lobbygate], sent LobbyGate_ContentsRuleListFail, SessionId:0x%I64X, reason:%d", session->_id, 234);
    }
    sendPacket.Clear();
    return true;
}

// 0x14470
bool HandleLobbyGate_HelloReq(Session* session, Packet* packet)
{
    short cmd;
    short packetVersion;
    char handshakeData[4000];
    short handshakeDataSize = 4000;
    if (packet->Decompose("hhb", &cmd, &packetVersion, handshakeData, &handshakeDataSize) == 0)
    {
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 68, L"[lobbygate], Session(%I64x), helloreq, decompose packet fail",
                   session->_id);
        session->FailHandshake();
        return false;
    }
    if (packetVersion != 58)
    {
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 75,
                   L"[lobbygate], Session(%I64x), helloreq, Invalid version %d (Current %d)", session->_id,
                   static_cast<int>(packetVersion), 58);
        session->FailHandshake();
        return false;
    }

    Packet reply{};  // LIFT: inlined constructor
    reply.Allocate();
    reply.Compose("hb", 2);  // ❓ no argument for "b" in the original
    if (handshakeDataSize <= 0)
    {
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 87, L"[lobbygate], Session(%I64X), helloreq, Invalid handshake data",
                   session->_id);
        session->FailHandshake();
        reply.Clear();
        return false;
    }
    unsigned char* body = reinterpret_cast<unsigned char*>(const_cast<char*>(reply.GetFreeBody()));
    int bufferSize = reply.CurHeader != nullptr ? static_cast<unsigned short>(4000 - reply.CurHeader->size) : 0;
    if (!session->SetHandshakeParameter(reinterpret_cast<unsigned char const*>(handshakeData), handshakeDataSize, body,
                                        &bufferSize))
    {
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 103, L"[lobbygate], Session(%I64X), helloreq, SetHandshakeParameter fail",
                   session->_id);
        session->FailHandshake();
        reply.Clear();
        return false;
    }
    reinterpret_cast<short*>(body)[-1] = static_cast<short>(bufferSize);
    reply.AddSize(static_cast<short>(bufferSize));
    PacketBuffer* listHead = reply.ListHead;
    listHead->encrypt(session->_currentCrypt, session->_security3rd);
    PacketBuffer const* list = listHead;
    session->_lock.Enter();
    session->send(&list, 1);
    session->_lock.Leave();
    if (session->_cryptMode == 3)
        session->completeHandshake();
    reply.Clear();
    return true;
}

// 0x14750
bool HandleLobbyGate_LoginWithNPTokenReq(Session* session, Packet* packet)
{
    short cmd;
    id128 npGameToken;
    id128 portalAccountId;
    if (packet->Decompose("hoo", &cmd, &npGameToken, &portalAccountId) == 0)
    {
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 134,
                   L"[lobbygate], 0x%.16I64X, %I64d, decompose fail, LoginWithNPTokenReq, "
                   L"npGameToken:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, "
                   L"portalAccountId:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
                   session->_id, 0LL, ID128_ARGS(npGameToken), ID128_ARGS(portalAccountId));
        return false;
    }
    Log::Write(Log::LT_DEBUG, HANDLER_FILE, 140,
               L"[lobbygate], 0x%.16I64X, %I64d, recv: LoginWithNPTokenReq, "
               L"npGameToken:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, "
               L"portalAccountId:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
               session->_id, 0LL, ID128_ARGS(npGameToken), ID128_ARGS(portalAccountId));

    long long gateKey = LobbyGate::_instance->_gatekeyManager->MakeGateKey(session);
    if (gateKey == 0)
    {
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 145,
                   L"[lobbygate], 0x%.16I64X, %I64d, failed to MakeGateKey, LoginWithNPTokenReq, "
                   L"npGameToken:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, "
                   L"portalAccountId:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
                   session->_id, 0LL, ID128_ARGS(npGameToken), ID128_ARGS(portalAccountId));
        session->Send("hh", 5);  // ❓ the reason argument is not in the pseudocode
        return true;
    }
    id128 npToken = npGameToken;
    id128 portalId = portalAccountId;
    if (!LobbyGate::_instance->_lobbyD->SendInitSessionWithNPTokenReq(static_cast<unsigned long long>(gateKey), &npToken,
                                                                       &portalId,
                                                                       static_cast<unsigned int>(session->_connection->_ip)))
    {
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 152,
                   L"[lobbygate], 0x%.16I64X, %I64d, failed to sendInitSessionWithNPTokenReq, LoginWithNPTokenReq, "
                   L"npGameToken:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, "
                   L"portalAccountId:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
                   session->_id, 0LL, ID128_ARGS(npGameToken), ID128_ARGS(portalAccountId));
        session->Send("hh", 5);  // ❓ the reason argument is not in the pseudocode
        return true;
    }
    return true;
}

// 0x14ae0
bool HandleLobbyGate_LoginWithLobbyTokenReq(Session* session, Packet* packet)
{
    short cmd;
    unsigned long long cliKey = 0;
    unsigned long long lobbyToken;
    if (packet->Decompose("hqq", &cmd, &cliKey, &lobbyToken) == 0)
    {
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 179,
                   L"[lobbygate], 0x%.16I64X, %I64d, decompose fail, LoginWithLobbyTokenReq, cliKey:0x%I64X, "
                   L"lobbyToken:0x%I64X",
                   session->_id, 0LL, cliKey, lobbyToken);
        return false;
    }
    Log::Write(Log::LT_DEBUG, HANDLER_FILE, 183,
               L"[lobbygate], 0x%.16I64X, %I64d, recv: LoginWithLobbyTokenReq, cliKey:0x%I64X, lobbyToken:0x%I64X",
               session->_id, 0LL, cliKey, lobbyToken);

    long long gateKey = LobbyGate::_instance->_gatekeyManager->MakeGateKey(session);
    if (gateKey == 0)
    {
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 188,
                   L"[lobbygate], 0x%.16I64X, %I64d, failed to MakeGateKey, LoginWithLobbyTokenReq, cliKey:0x%I64X, "
                   L"lobbyToken:0x%I64X",
                   session->_id, 0LL, cliKey, lobbyToken);
        session->Send("hh", 8);  // ❓ the reason argument is not in the pseudocode
        return true;
    }
    if (!LobbyGate::_instance->_lobbyD->SendInitSessionWithLobbyTokenReq(
            static_cast<unsigned long long>(gateKey), cliKey, lobbyToken,
            static_cast<unsigned int>(session->_connection->_ip)))
    {
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 195,
                   L"[lobbygate], 0x%.16I64X, %I64d, failed to sendInitSessionWithLobbyTokenReq, LoginWithLobbyTokenReq, "
                   L"cliKey:0x%I64X, lobbyToken:0x%I64X, gatekey:0x%I64X",
                   session->_id, 0LL, cliKey, lobbyToken, gateKey);
        session->Send("hh", 8);  // ❓ the reason argument is not in the pseudocode
        return true;
    }
    return true;
}

// 0x14c90
bool HandleLobbyGate_BypassPacket(Client* client, Packet const* packet)
{
    unsigned long long cliKey = client->GetId();
    if (cliKey == 0)
    {
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 214, L"[lobbygate], failed to handle bypasspacket, invalid clikey");
        return false;
    }
    // The command is the low byte of the short after the packet header.
    short cmd = ClientSessionHandler::SwitchCmdLobbyGateToLobbyDaemon(
        static_cast<signed char>(packet->CurHeader[1].size));
    Session* session = const_cast<Session*>(LobbyGate::_instance->_lobbyD->GetSession());
    if (session == nullptr)
    {
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 224, L"[lobbygate], failed to get lobbyd session, clikey:0x%I64X, cmd:%d",
                   cliKey, static_cast<int>(cmd));
        return false;
    }
    session->_lock.Enter();
    bool connected = session->_state == Session::CONNECTED && session->_connection->_socket != INVALID_SOCKET;
    session->_lock.Leave();
    if (!connected)
    {
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 231, L"[lobbygate], failed to send, not connected, cliKey:0x%I64X, cmd:%d",
                   cliKey, static_cast<int>(cmd));
        session->removeReferenceCount(CHANNEL_H_FILE, 52);
        return false;
    }

    Packet p{};  // LIFT: inlined constructor
    p.Allocate();
    if (p.Compose("hq", static_cast<int>(cmd), cliKey) == 0)
    {
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 241, L"[lobbygate], failed to compose packet, cliKey:0x%I64X, cmd:%d",
                   cliKey, static_cast<int>(cmd));
        session->removeReferenceCount(CHANNEL_H_FILE, 52);
        p.Clear();
        return false;
    }
    Packet::Header const* header = packet->CurHeader;
    unsigned short bodySize = static_cast<unsigned short>(header->size - 2);
    int dataSize = bodySize - 2;
    if (bodySize > 2)
    {
        unsigned short freeSize = p.CurHeader != nullptr ? static_cast<unsigned short>(4000 - p.CurHeader->size) : 0;
        if (freeSize <= dataSize)
            p.Allocate();
        p.Add(header + 2, static_cast<short>(dataSize));
    }
    PacketBuffer* listHead = p.ListHead;
    listHead->encrypt(session->_currentCrypt, session->_security3rd);
    PacketBuffer const* list = listHead;
    session->_lock.Enter();
    session->send(&list, 1);
    session->_lock.Leave();
    Log::Write(Log::LT_DEBUG, HANDLER_FILE, 259, L"[lobbygate], send ok, cmd:%d, cliKey:0x%I64X", static_cast<int>(cmd),
               cliKey);
    session->removeReferenceCount(CHANNEL_H_FILE, 52);
    p.Clear();
    return true;
}

// 0x14f40
bool HandleLobbyGate_GetWorldInfoListReq(Client* client, Packet const* packet)
{
    unsigned long long cliKey = client->GetId();
    if (cliKey == 0)
    {
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 270, L"[lobbygate], GetWorldInfoListReq, invalid clikey");
        return false;
    }
    Log::Write(Log::LT_DEBUG, HANDLER_FILE, 279, L"[lobbygate], recv: GetWorldInfoListReq, cliKey:0x%I64X", cliKey);
    LobbyD* lobbyD = LobbyGate::_instance->_lobbyD;
    if (lobbyD == nullptr)
    {
        // BUG: 0x14fa4 the format is split into two arguments. The second part is printed as a value.
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 284, L"[lobbygate], fail to get world list, invalid lobbyd channel, ",
                   L"GetWorldInfoListReq, cliKey:0x%I64X", cliKey);
        client->Send("hh", 19);  // ❓ the reason argument is not in the pseudocode
        return true;
    }
    if (lobbyD->_state != 1)
    {
        // BUG: 0x14fd5 the format is split into two arguments.
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 291, L"[lobbygate], fail to get world list, service not avaliable, ",
                   L"GetWorldInfoListReq, cliKey:0x%I64X", cliKey);
        client->Send("hh", 19);  // ❓ the reason argument is not in the pseudocode
        return true;
    }

    // Inlined WorldListManager::GetWorldList ❓
    WorldListManager* manager = LobbyGate::_instance->_worldListManger;
    WorldList* worldList = nullptr;
    AcquireSRWLockShared(&manager->_srwLock);
    if (manager->_worldList != nullptr)
    {
        worldList = manager->_worldList;
        worldList->addReferenceCount(L"WorldListManager.cpp", 0xEA);
    }
    ReleaseSRWLockShared(&manager->_srwLock);

    if (worldList != nullptr)
    {
        client->Send(&worldList->_fp.packet);
        worldList->removeReferenceCount(HANDLER_FILE, 339);
    }
    else
    {
        // BUG: 0x15090 the format is split into two arguments.
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 300, L"[lobbygate], fail to get world list, ",
                   L"GetWorldInfoListReq, cliKey:0x%I64X", cliKey);
        client->Send("hh", 19, 2);  // BUG: 0x150b0 "hh" uses only one value after the command.
    }
    return true;
}

// 0x150f0
bool HandleLobbyGate_GetPcCafeMileageFeverTimeScheduleListReq(Client* client, Packet const* packet)
{
    unsigned long long cliKey = client->GetId();
    if (cliKey == 0)
    {
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 349, L"[lobbygate], GetPcCafeMileageFeverTimeScheduleListReq, invalid clikey");
        return false;
    }
    Log::Write(Log::LT_DEBUG, HANDLER_FILE, 358,
               L"[lobbygate], recv: GetPcCafeMileageFeverTimeScheduleListReq, cliKey:0x%I64X", cliKey);
    LobbyD* lobbyD = LobbyGate::_instance->_lobbyD;
    if (lobbyD == nullptr)
    {
        // BUG: 0x15154 the format is split into two arguments.
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 363, L"[lobbygate], fail to get world list, invalid lobbyd channel, ",
                   L"GetPcCafeMileageFeverTimeScheduleListReq, cliKey:0x%I64X", cliKey);
        client->Send("hh", 105);  // ❓ the reason argument is not in the pseudocode
        return true;
    }
    if (lobbyD->_state != 1)
    {
        // BUG: 0x15185 the format is split into two arguments.
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 370, L"[lobbygate], fail to get world list, service not avaliable, ",
                   L"GetPcCafeMileageFeverTimeScheduleListReq, cliKey:0x%I64X", cliKey);
        client->Send("hh", 105);  // ❓ the reason argument is not in the pseudocode
        return true;
    }

    // Inlined PcCafeMileageFeverTimeScheduleListManager::GetScheduleList ❓
    PcCafeMileageFeverTimeScheduleListManager* manager = LobbyGate::_instance->_pcCafeMileageFeverTimeScheduleListManager;
    PcCafeMileageFeverTimeScheduleList* scheduleList = nullptr;
    AcquireSRWLockShared(&manager->_srwLock);
    if (manager->_scheduleList != nullptr)
    {
        scheduleList = manager->_scheduleList;
        scheduleList->addReferenceCount(L"PcCafeMileageFeverTimeScheduleList.cpp", 0x8D);
    }
    ReleaseSRWLockShared(&manager->_srwLock);

    if (scheduleList != nullptr)
    {
        client->Send(&scheduleList->_fp.packet);
        scheduleList->removeReferenceCount(HANDLER_FILE, 387);
    }
    else
    {
        // BUG: 0x15240 the format is split into two arguments.
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 378, L"[lobbygate], fail to get world list, ",
                   L"GetPcCafeMileageFeverTimeScheduleListReq, cliKey:0x%I64X", cliKey);
        client->Send("hh", 105, 2);  // BUG: 0x15260 "hh" uses only one value after the command.
    }
    return true;
}
