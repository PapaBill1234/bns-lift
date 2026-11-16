// LobbyDChannel.obj (LobbyGate PDB). Source: .scratch/hr/LobbyDChannel.c
#include "Network.h"
#include <string.h>
#include <wchar.h>
#include "LobbyDChannel.h"
#include "Session.h"
#include "Connection.h"
#include "Packet.h"
#include "PacketBuffer.h"
#include "Memory.h"
#include "Log.h"
#include "AlertSender.h"
#include "Daemon.h"
#include "PipeConsole.h"
#include "LobbyGate.h"

namespace
{
wchar_t const* const LOBBYD_FILE = L"LobbyDChannel.cpp";
wchar_t const* const SESSION_FILE = L"source\\Session.cpp";
wchar_t const* const TFPP_FILE = L"..\\Economy\\Shared\\ThreadFreePacketPump.cpp";
wchar_t const* const CHANNEL_H_FILE =
    L"E:\\DailyBuild02\\LobbyGate-Common-0.0.348\\depot\\Branch\\348NC\\Program\\Server\\BloodLib\\include\\Channel.h";
wchar_t const* const DISCONNECTED_LOBBYD = L"disconnected lobbyd";

// ❓ The PDB type id128::<unnamed-type-guid> has the fields id1, id2, id3 and id4[8].
struct GuidFields
{
    unsigned int id1;
    unsigned short id2;
    unsigned short id3;
    unsigned char id4[8];
};

GuidFields guidOf(id128 const* value)
{
    GuidFields g;
    memcpy(&g, value->guid, sizeof(g));
    return g;
}

// ❓ Inlined search in PipeConsole::_invalid (wcsncmp with 20 characters).
PipeConsole::ItemNode* findDisconnectedNode(PipeConsole* console)
{
    PipeConsole::ItemNode* node = console->_invalid._head._next;
    while (node != &console->_invalid._tail)
    {
        if (wcsncmp(node->_key, DISCONNECTED_LOBBYD, 20) == 0)
            return node;
        node = node->_next;
    }
    return nullptr;
}

// ❓ Inlined PipeConsole::SetInvalidInfo(L"disconnected lobbyd", true). PipeConsole::addNode is private,
// thus the friend classes call it. Each caller writes the add step inline.
#define LOBBYD_SET_DISCONNECTED_INFO()                                                                       \
    do                                                                                                       \
    {                                                                                                        \
        if (Daemon::Instance != nullptr && Daemon::Instance->pipeConsole != nullptr)                         \
        {                                                                                                    \
            PipeConsole* console = Daemon::Instance->pipeConsole;                                            \
            console->_lock.Enter();                                                                          \
            if (findDisconnectedNode(console) == nullptr)                                                    \
                PipeConsole::addNode(console->_invalid, DISCONNECTED_LOBBYD, L""); /* ❓ value: valueString */ \
            console->_lock.Leave();                                                                          \
        }                                                                                                    \
    } while (0)

// ❓ Inlined PipeConsole::SetInvalidInfo(L"disconnected lobbyd", false).
void clearDisconnectedInfo()
{
    if (Daemon::Instance == nullptr || Daemon::Instance->pipeConsole == nullptr)
        return;
    PipeConsole* console = Daemon::Instance->pipeConsole;
    console->_lock.Enter();
    PipeConsole::ItemNode* node = findDisconnectedNode(console);
    if (node != nullptr)
    {
        node->_next->_prev = node->_prev;
        node->_prev->_next = node->_next;
        Memory::_Manager[2]->Free(node, L"", 837);  // ❓ file string at 0x1400857D8
    }
    console->_lock.Leave();
}

// ❓ Inlined Session::GetChannel with the reference (source\Session.cpp 1051).
LobbyD* acquireChannel(Session const* session)
{
    Channel* channel = session->_channel;
    if (channel == nullptr || session->_waitForRelease)
        return nullptr;
    channel->addReferenceCount(SESSION_FILE, 1051);
    return static_cast<LobbyD*>(session->_channel);
}

// ❓ Inlined connection check of the LobbyD::Send* functions.
bool isConnected(Session* session)
{
    session->_lock.Enter();
    bool connected = session->_state == Session::CONNECTED && session->_connection->_socket != INVALID_SOCKET;
    session->_lock.Leave();
    return connected;
}

// ❓ Inlined fail path "not connected" of the LobbyD::Send* functions.
bool failNotConnected(Session* session, short cmd, int line)
{
    Log::Write(Log::LT_ERROR, LOBBYD_FILE, line, L"[channel], 0x%.16I64X, send fail, not connected, cmd:%d",
               session != nullptr ? session->_id : 0ULL, static_cast<int>(cmd));
    if (session != nullptr)
        session->removeReferenceCount(CHANNEL_H_FILE, 52);
    return false;
}

// ❓ Inlined fail path "compose fail" of the LobbyD::Send* functions.
bool failCompose(Session* session, Packet& packet, short cmd, int line)
{
    Log::Write(Log::LT_ERROR, LOBBYD_FILE, line, L"[channel], 0x%.16I64X, send fail, compose fail, cmd:%d",
               session->_id, static_cast<int>(cmd));
    session->removeReferenceCount(CHANNEL_H_FILE, 52);
    packet.Clear();
    return false;
}

// ❓ Inlined masking of the client IP address in the logs.
void formatIpAddress(unsigned int ipAddress, wchar_t (&ipStr)[20])
{
    if (LobbyGate::_instance != nullptr)
    {
        LobbyGateConfig const* config = LobbyGate::_instance->_config;
        if (config != nullptr && !config->_allowClientIPAddressInLogs)
            ipAddress = 0;
    }
    wcsncpy(ipStr, Network::GetAddressStringW(ipAddress), 20);
}
}  // namespace

// 0x9200
bool LobbyDSessionHandler::isBypassPacket(short cmd)
{
    switch (cmd)
    {
    case 26: case 27: case 29: case 30: case 32: case 33: case 34: case 37: case 39: case 40:
    case 42: case 43: case 45: case 46: case 48: case 49: case 50: case 52: case 53: case 55:
    case 56: case 58: case 59: case 61: case 62: case 63: case 65: case 66: case 69: case 72:
    case 75: case 77: case 78: case 81: case 83: case 84: case 86: case 87: case 89: case 90:
    case 92: case 93: case 95: case 96: case 98: case 99: case 101: case 102: case 104: case 105:
    case 107: case 108: case 109: case 110:
        return true;
    default:
        return false;
    }
}

// 0x92a0
bool LobbyDSessionHandler::OnAccept(Session const* session) const
{
    unsigned long long id = session != nullptr ? session->_id : 0;
    Log::Write(Log::LT_ERROR, LOBBYD_FILE, 92, L"== CRASH == [channel], 0x%.16I64X, accept, invalid call", id);
    AlertSender::Write(LOBBYD_FILE, 92, L"== CRASH == [channel], 0x%.16I64X, accept, invalid call", id);
    return false;
}

// 0x9310
bool LobbyDSessionHandler::OnConnect(Session const* session, bool firstConnected) const
{
    CriticalSection& connlock = const_cast<CriticalSection&>(_connlock);
    connlock.Enter();
    LobbyD* lobbyD = acquireChannel(session);
    connlock.Leave();
    if (lobbyD == nullptr)
    {
        Log::Write(Log::LT_ERROR, LOBBYD_FILE, 105, L"[channel], 0x%.16I64X, connect without channel", session->_id);
        return false;
    }

    clearDisconnectedInfo();
    if (firstConnected)
        Log::Write(Log::LT_DEBUG, LOBBYD_FILE, 114, L"[channel], 0x%.16I64X, connect", session->_id);
    else
        Log::Write(Log::LT_DEBUG, LOBBYD_FILE, 116, L"[channel], 0x%.16I64X, reconnect", session->_id);
    lobbyD->hello();
    lobbyD->removeReferenceCount(SESSION_FILE, 1059);
    return true;
}

// 0x94c0
void LobbyDSessionHandler::OnClose(Session const* session, bool tryReconnect) const
{
    LobbyD* lobbyD = acquireChannel(session);
    Log::Write(Log::LT_DEBUG, LOBBYD_FILE, 128, L"[channel], 0x%.16I64X, close", session->_id);
    if (lobbyD != nullptr)
    {
        lobbyD->_state = 0;
        Log::Write(Log::LT_DEBUG, LOBBYD_FILE, 132, L"[channel], 0x%.16I64X, disable service", session->_id);
    }
    LOBBYD_SET_DISCONNECTED_INFO();
    if (tryReconnect)
        Log::Write(Log::LT_DEBUG, LOBBYD_FILE, 140, L"[channel], 0x%.16I64X, try reconnect", session->_id);
    if (lobbyD != nullptr)
        lobbyD->removeReferenceCount(SESSION_FILE, 1059);
}

// 0x9660
bool LobbyDSessionHandler::PacketHandler(Session const* session, Packet const* packet) const
{
    Packet::Header const* header = packet->CurHeader;
    LobbyD* lobbyD = acquireChannel(session);
    if (lobbyD != nullptr)
        lobbyD->GetId();  // The result is not used.

    bool result = false;
    short cmd = static_cast<short>(header[1].size);
    if (_lobbydHandlerList == nullptr || _lobbydHandlerList[header[1].size] == nullptr)
    {
        Log::Write(Log::LT_ERROR, LOBBYD_FILE, 163, L"[channel], 0x%.16I64X, handle fail, no such cmd, cmd:%d",
                   session->_id, static_cast<int>(header[1].size));
        result = false;
    }
    else if (isBypassPacket(cmd))
    {
        // Inlined TFPP_PumpPacket(128, iocp, session, packet, 1, 0, bypassHandler, bypassHandlerFF).
        void* iocp = Network::Instance != nullptr ? Network::Instance->_iocpHandle : nullptr;
        if (iocp == INVALID_HANDLE_VALUE)
        {
            Log::Write(Log::LT_ERROR, TFPP_FILE, 262,
                       L"== CRASH == [packet-pump], invalid parameter, event-id:%u, iocp:%I64u, session:0x%p, "
                       L"packet:0x%p, cmd:%d, offset:%d, PH:0x%p, fragmentPH:0x%p",
                       128U, ~0ULL, session, packet, 1, 0, bypassHandler, bypassHandlerFF);
            AlertSender::Write(TFPP_FILE, 262,
                               L"== CRASH == [packet-pump], invalid parameter, event-id:%u, iocp:%I64u, session:0x%p, "
                               L"packet:0x%p, cmd:%d, offset:%d, PH:0x%p, fragmentPH:0x%p",
                               128U, ~0ULL, session, packet, 1, 0, bypassHandler, bypassHandlerFF);
            result = false;
        }
        else if (bypassHandlerFF[1] != nullptr)
        {
            result = __pump_fragment_packet(128, iocp, session, packet, 1, bypassHandlerFF[1]);
        }
        else
        {
            result = __pump_packet(128, iocp, session, packet, 1, bypassHandler[1]);
        }
    }
    else
    {
        void* iocp = Network::Instance != nullptr ? Network::Instance->_iocpHandle : nullptr;
        result = TFPP_PumpPacket(128, iocp, session, packet, header[1].size, 0,  // ❓ event-id and offset
                                 reinterpret_cast<TFPP_PacketHandler const*>(_lobbydHandlerList),
                                 reinterpret_cast<TFPP_PacketHandler const*>(_lobbydFragmentHandlerList));
    }

    if (lobbyD != nullptr)
        lobbyD->removeReferenceCount(SESSION_FILE, 1059);
    return result;
}

// 0x98a0
short LobbyDSessionHandler::SwitchCmdLobbyDaemonToLobbyGate(short cmd)
{
    switch (cmd)
    {
    case 26: return 15;
    case 27: return 16;
    case 29: return 18;
    case 30: return 19;
    case 32: return 21;
    case 33: return 22;
    case 34: return 23;
    case 37: return 29;
    case 39: return 31;
    case 40: return 32;
    case 45: return 37;
    case 46: return 38;
    case 48: return 40;
    case 49: return 41;
    case 50: return 42;
    case 52: return 44;
    case 53: return 45;
    case 55: return 47;
    case 56: return 48;
    case 58: return 50;
    case 59: return 51;
    case 61: return 53;
    case 62: return 54;
    case 63: return 55;
    case 65: return 57;
    case 66: return 58;
    case 69: return 61;
    case 72: return 64;
    case 75: return 67;
    case 77: return 69;
    case 78: return 70;
    case 81: return 73;
    case 83: return 75;
    case 84: return 76;
    case 86: return 78;
    case 87: return 79;
    case 89: return 81;
    case 90: return 82;
    case 92: return 84;
    case 93: return 85;
    case 95: return 87;
    case 96: return 88;
    case 98: return 90;
    case 99: return 91;
    case 101: return 93;
    case 102: return 94;
    case 104: return 96;
    case 105: return 97;
    case 107: return 99;
    case 108: return 100;
    case 109: return 101;
    case 110: return 102;
    default: return 0;
    }
}

// 0x9bd0
bool LobbyD::Hello(LobbyDSessionHandler* handler, unsigned int waitAck, unsigned short portId)
{
    LOBBYD_SET_DISCONNECTED_INFO();

    _helloEvent.Event = CreateEventW(nullptr, FALSE, FALSE, nullptr);
    if (_helloEvent.Event == nullptr)
    {
        Log::Write(Log::LT_ERROR, LOBBYD_FILE, 271, L"make hello event fail");
        return false;
    }

    if (handler != nullptr)
        handler->_connlock.Enter();
    // ❓ The pseudocode forwards only rdx and r8. The other arguments are not visible.
    bool made = MakeSession(waitAck, portId, 0, 0, false);
    if (handler != nullptr)
        handler->_connlock.Leave();
    if (!made)
    {
        Log::Write(Log::LT_ERROR, LOBBYD_FILE, 281, L"make session fail");
        return false;
    }

    if (_helloEvent.Event == nullptr || WaitForSingleObject(_helloEvent.Event, INFINITE) != 0)
    {
        Log::Write(Log::LT_ERROR, LOBBYD_FILE, 290, L"wait hello event fail");
        return false;
    }
    if (_state == 1)
        return true;
    Log::Write(Log::LT_ERROR, LOBBYD_FILE, 294, L"service not available");
    return false;
}

// 0x9d80
bool LobbyD::hello()
{
    Session* session = const_cast<Session*>(GetSession());
    if (_helloEvent.Event != nullptr)
        ResetEvent(_helloEvent.Event);
    LobbyGateConfig const* config = LobbyGate::_instance->_config;
    // BUG: 0x9d80 Send is called also when the session is null.
    session->Send("hhhh", 1, static_cast<int>(static_cast<short>(config->_predefinedWorldId)), 58,
                  static_cast<int>(static_cast<short>(config->_internalPort)));
    Log::Write(Log::LT_DEBUG, LOBBYD_FILE, 315,
               L"[channel], 0x%.16I64X, send, cmd:%d, gate-wid:%d, lobbylobbygatepacket-version:%d, internal-port:%d",
               session != nullptr ? session->_id : 0ULL, 1, config->_predefinedWorldId, 58,
               static_cast<int>(static_cast<unsigned short>(config->_internalPort)));
    if (session != nullptr)
        session->removeReferenceCount(CHANNEL_H_FILE, 52);
    return true;
}

// 0x9e70
bool LobbyD::SendInitSessionWithNPTokenReq(unsigned long long gateKey, id128 const* npToken,
                                           id128 const* portalAccountId, unsigned int ipAddress)
{
    short const cmd = 6;
    Session* session = const_cast<Session*>(GetSession());
    if (session == nullptr || !isConnected(session))
        return failNotConnected(session, cmd, 328);

    Packet packet{};  // ❓ inlined constructor
    packet.Allocate();
    id128 portalCopy = *portalAccountId;
    id128 npCopy = *npToken;
    if (packet.Compose("hqooi", static_cast<int>(cmd), gateKey, &npCopy, &portalCopy, ipAddress) == 0)
        return failCompose(session, packet, cmd, 338);

    packet.ListHead->encrypt(session->_currentCrypt, session->_security3rd);
    PacketBuffer const* list[1] = {packet.ListHead};
    session->_lock.Enter();
    session->send(list, 1);  // ❓ count is not initialized in the pseudocode
    session->_lock.Leave();

    wchar_t ipStr[20];
    formatIpAddress(ipAddress, ipStr);
    GuidFields np = guidOf(npToken);
    GuidFields pa = guidOf(portalAccountId);
    Log::Write(Log::LT_DEBUG, LOBBYD_FILE, 347,
               L"[channel], 0x%.16I64X, send, cmd:%d, gateKey:0x%I64X, "
               L"npToken:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, "
               L"portalAccountId:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, ipAddress:%s",
               session->_id, static_cast<int>(cmd), gateKey, np.id1, np.id2, np.id3, np.id4[0], np.id4[1], np.id4[2],
               np.id4[3], np.id4[4], np.id4[5], np.id4[6], np.id4[7], pa.id1, pa.id2, pa.id3, pa.id4[0], pa.id4[1],
               pa.id4[2], pa.id4[3], pa.id4[4], pa.id4[5], pa.id4[6], pa.id4[7], ipStr);
    session->removeReferenceCount(CHANNEL_H_FILE, 52);
    packet.Clear();
    return true;
}

// 0xa280
bool LobbyD::SendStartSessionWithNPTokenReq(unsigned long long cliKey, id128 const* npToken,
                                            id128 const* portalAccountId, unsigned int ipAddress)
{
    short const cmd = 9;
    Session* session = const_cast<Session*>(GetSession());
    if (session == nullptr || !isConnected(session))
        return failNotConnected(session, cmd, 360);

    Packet packet{};  // ❓ inlined constructor
    packet.Allocate();
    id128 portalCopy = *portalAccountId;
    id128 npCopy = *npToken;
    // BUG: 0xa280 the format "hqoo" does not use the ipAddress argument.
    if (packet.Compose("hqoo", static_cast<int>(cmd), cliKey, &npCopy, &portalCopy, ipAddress) == 0)
        return failCompose(session, packet, cmd, 370);

    packet.ListHead->encrypt(session->_currentCrypt, session->_security3rd);
    PacketBuffer const* list[1] = {packet.ListHead};
    session->_lock.Enter();
    session->send(list, 1);  // ❓ count is not initialized in the pseudocode
    session->_lock.Leave();

    wchar_t ipStr[20];
    formatIpAddress(ipAddress, ipStr);
    GuidFields np = guidOf(npToken);
    GuidFields pa = guidOf(portalAccountId);
    Log::Write(Log::LT_DEBUG, LOBBYD_FILE, 379,
               L"[channel], 0x%.16I64X, send, cmd:%d, cliKey:0x%I64X, "
               L"npToken:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, "
               L"portalAccountId:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, ipAddress:%s",
               session->_id, static_cast<int>(cmd), cliKey, np.id1, np.id2, np.id3, np.id4[0], np.id4[1], np.id4[2],
               np.id4[3], np.id4[4], np.id4[5], np.id4[6], np.id4[7], pa.id1, pa.id2, pa.id3, pa.id4[0], pa.id4[1],
               pa.id4[2], pa.id4[3], pa.id4[4], pa.id4[5], pa.id4[6], pa.id4[7], ipStr);
    session->removeReferenceCount(CHANNEL_H_FILE, 52);
    packet.Clear();
    return true;
}

// 0xa690
bool LobbyD::SendInitSessionWithLobbyTokenReq(unsigned long long gateKey, unsigned long long cliKey,
                                              unsigned long long lobbyToken, unsigned int ipAddress)
{
    short const cmd = 12;
    Session* session = const_cast<Session*>(GetSession());
    if (session == nullptr || !isConnected(session))
        return failNotConnected(session, cmd, 392);

    Packet packet{};  // ❓ inlined constructor
    packet.Allocate();
    if (packet.Compose("hqqqi", static_cast<int>(cmd), gateKey, cliKey, lobbyToken, ipAddress) == 0)
        return failCompose(session, packet, cmd, 402);

    packet.ListHead->encrypt(session->_currentCrypt, session->_security3rd);
    PacketBuffer const* list[1] = {packet.ListHead};
    session->_lock.Enter();
    session->send(list, 1);  // ❓ count is not initialized in the pseudocode
    session->_lock.Leave();

    wchar_t ipStr[20];
    formatIpAddress(ipAddress, ipStr);
    Log::Write(Log::LT_DEBUG, LOBBYD_FILE, 411,
               L"[channel], 0x%.16I64X, send, cmd:%d, gateKey:0x%I64X, cliKey:0x%I64X, lobbyToken:0x%I64X, "
               L"ipAddress:%s",
               session->_id, static_cast<int>(cmd), gateKey, cliKey, lobbyToken, ipStr);
    session->removeReferenceCount(CHANNEL_H_FILE, 52);
    packet.Clear();
    return true;
}

// 0xa920
bool LobbyD::SendStartSessionWithLobbyTokenReq(unsigned long long cliKey)
{
    short const cmd = 15;
    Session* session = const_cast<Session*>(GetSession());
    if (session == nullptr || !isConnected(session))
        return failNotConnected(session, cmd, 424);

    Packet packet{};  // ❓ inlined constructor
    packet.Allocate();
    if (packet.Compose("hq", static_cast<int>(cmd), cliKey) == 0)
        return failCompose(session, packet, cmd, 434);

    packet.ListHead->encrypt(session->_currentCrypt, session->_security3rd);
    PacketBuffer const* list[1] = {packet.ListHead};
    session->_lock.Enter();
    session->send(list, 1);  // ❓ count is not initialized in the pseudocode
    session->_lock.Leave();

    Log::Write(Log::LT_DEBUG, LOBBYD_FILE, 440, L"[channel], 0x%.16I64X, send, cmd:%d, cliKey:0x%I64X", session->_id,
               static_cast<int>(cmd), cliKey);
    session->removeReferenceCount(CHANNEL_H_FILE, 52);
    packet.Clear();
    return true;
}

// 0xab20
bool LobbyD::SendLostAnonymousConnectionNotify(long long gateKey)
{
    short const cmd = 18;
    Session* session = const_cast<Session*>(GetSession());
    if (session == nullptr || !isConnected(session))
        return failNotConnected(session, cmd, 453);

    Packet packet{};  // ❓ inlined constructor
    packet.Allocate();
    if (packet.Compose("hq", static_cast<int>(cmd), gateKey) == 0)
        return failCompose(session, packet, cmd, 463);

    packet.ListHead->encrypt(session->_currentCrypt, session->_security3rd);
    PacketBuffer const* list[1] = {packet.ListHead};
    session->_lock.Enter();
    session->send(list, 1);  // ❓ count is not initialized in the pseudocode
    session->_lock.Leave();

    Log::Write(Log::LT_DEBUG, LOBBYD_FILE, 469, L"[channel], 0x%.16I64X, send, cmd:%d, gateKey:0x%I64X", session->_id,
               static_cast<int>(cmd), gateKey);
    session->removeReferenceCount(CHANNEL_H_FILE, 52);
    packet.Clear();
    return true;
}

// 0xad20
bool LobbyD::SendLostConnectionNotify(unsigned long long cliKey)
{
    short const cmd = 19;
    Session* session = const_cast<Session*>(GetSession());
    if (session == nullptr || !isConnected(session))
        return failNotConnected(session, cmd, 482);

    Packet packet{};  // ❓ inlined constructor
    packet.Allocate();
    if (packet.Compose("hq", static_cast<int>(cmd), cliKey) == 0)
        return failCompose(session, packet, cmd, 492);

    packet.ListHead->encrypt(session->_currentCrypt, session->_security3rd);
    PacketBuffer const* list[1] = {packet.ListHead};
    session->_lock.Enter();
    session->send(list, 1);  // ❓ count is not initialized in the pseudocode
    session->_lock.Leave();

    Log::Write(Log::LT_DEBUG, LOBBYD_FILE, 498, L"[channel], 0x%.16I64X, send, cmd:%d, cliKey:0x%I64X", session->_id,
               static_cast<int>(cmd), cliKey);
    session->removeReferenceCount(CHANNEL_H_FILE, 52);
    packet.Clear();
    return true;
}
