// GamedChannel.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "PlacementNew.h"
#include <winsock2.h>
#include <windows.h>
#include "GamedChannel.h"
#include "AlertSender.h"
#include "Connection.h"
#include "FragmentPacket.h"
#include "LiftStub.h"
#include "LobbyDaemon.h"
#include "Log.h"
#include "Network.h"
#include "Packet.h"
#include "PacketUtil.h"
#include "Session.h"
#include "StringUtil.h"

namespace
{
wchar_t const* const GAMED_FILE = L"GamedChannel.cpp";  // LIFT: No PDB symbol. The binary uses the literal.
// LIFT: No PDB symbol. The binary uses the literal as the file string of SharedChannelList::Acquire/Remove errors (lines 200 and 234; used in GamedChannelManager::Remove and Acquire).
wchar_t const* const SHARED_CHANNEL_FILE = L"..\\Shared\\SharedChannel.cpp";
// LIFT: No PDB symbol. The binary uses the literal as the file string of the Session reference count call (line 1059; used in GamedChannelManager::PacketHandler).
wchar_t const* const SESSION_FILE = L"source\\Session.cpp";
}

#pragma comment(linker, "/INCLUDE:??1GamedChannelManager@@UEAA@XZ")  // LIFT: keep until the caller is lifted (0x80300)
#pragma comment(linker, "/INCLUDE:?Add@GamedChannelManager@@QEAA_NPEAVGamedChannel@@@Z")  // LIFT: keep until the caller is lifted (0x803e0)
#pragma comment(linker, "/INCLUDE:?Remove@GamedChannelManager@@QEAAXF@Z")  // LIFT: keep until the caller is lifted (0x804a0)
#pragma comment(linker, "/INCLUDE:?Acquire@GamedChannelManager@@QEAAPEAVGamedChannel@@F@Z")  // LIFT: keep until the caller is lifted (0x805b0)
#pragma comment(linker, "/INCLUDE:?OnAccept@GamedChannelManager@@UEBA_NPEBVSession@@@Z")  // LIFT: keep until the caller is lifted (0x80680)
#pragma comment(linker, "/INCLUDE:?OnConnect@GamedChannelManager@@UEBA_NPEBVSession@@_N@Z")  // LIFT: keep until the caller is lifted (0x806e0)
#pragma comment(linker, "/INCLUDE:?PacketHandler@GamedChannelManager@@UEBA_NPEBVSession@@PEBVPacket@@@Z")  // LIFT: keep until the caller is lifted (0x80980)
#pragma comment(linker, "/INCLUDE:?SendStopPlayNotify@GamedChannel@@QEAAX_KF@Z")  // LIFT: keep until the caller is lifted (0x80d50)
#pragma comment(linker, "/INCLUDE:?SendCreateCharacterReq@GamedChannel@@QEAA_NPEAVTransaction@TransactionChannel@@_KAEBTid128@@PEBDFHPEB_WPEADF_NF@Z")  // LIFT: keep until the caller is lifted (0x80e20)
#pragma comment(linker, "/INCLUDE:?SendDeleteCharacterReq@GamedChannel@@QEAA_NPEAVTransaction@TransactionChannel@@_KPEBDFH@Z")  // LIFT: keep until the caller is lifted (0x81040)
#pragma comment(linker, "/INCLUDE:?SendRestoreCharacterReq@GamedChannel@@QEAA_NPEAVTransaction@TransactionChannel@@_K@Z")  // LIFT: keep until the caller is lifted (0x811c0)
#pragma comment(linker, "/INCLUDE:?SendDeleteCharacterCompleteNotify@GamedChannel@@QEAAX_K@Z")  // LIFT: keep until the caller is lifted (0x81320)
#pragma comment(linker, "/INCLUDE:?SendCloseSessionNotify@GamedChannel@@QEAAX_K@Z")  // LIFT: keep until the caller is lifted (0x813e0)
#pragma comment(linker, "/INCLUDE:?SendKickReq@GamedChannel@@QEAA_NPEAVTransaction@TransactionChannel@@_K11D@Z")  // LIFT: keep until the caller is lifted (0x814a0)
#pragma comment(linker, "/INCLUDE:?SendEnterWorldFail@GamedChannel@@QEAAX_KF@Z")  // LIFT: keep until the caller is lifted (0x81620)
#pragma comment(linker, "/INCLUDE:?SendLeaveWorldOk@GamedChannel@@QEAAX_K0@Z")  // LIFT: keep until the caller is lifted (0x816f0)
#pragma comment(linker, "/INCLUDE:?SendLeaveWorldFail@GamedChannel@@QEAAX_KF@Z")  // LIFT: keep until the caller is lifted (0x817c0)
#pragma comment(linker, "/INCLUDE:?SendUpdateCharacterDataOk@GamedChannel@@QEAAX_K@Z")  // LIFT: keep until the caller is lifted (0x81890)
#pragma comment(linker, "/INCLUDE:?SendUpdateCharacterDataFail@GamedChannel@@QEAAX_KF@Z")  // LIFT: keep until the caller is lifted (0x81950)
#pragma comment(linker, "/INCLUDE:?SendUpdateAccountDataOk@GamedChannel@@QEAAX_K@Z")  // LIFT: keep until the caller is lifted (0x81a20)
#pragma comment(linker, "/INCLUDE:?SendUpdateAccountDataFail@GamedChannel@@QEAAX_KF@Z")  // LIFT: keep until the caller is lifted (0x81ae0)
#pragma comment(linker, "/INCLUDE:?SendTryRegisterGuildOk@GamedChannel@@QEAAX_K0@Z")  // LIFT: keep until the caller is lifted (0x81bb0)
#pragma comment(linker, "/INCLUDE:?SendTryRegisterGuildFail@GamedChannel@@QEAAX_KF@Z")  // LIFT: keep until the caller is lifted (0x81c80)
#pragma comment(linker, "/INCLUDE:?SendTryRenameGuildOk@GamedChannel@@QEAAX_K0D0@Z")  // LIFT: keep until the caller is lifted (0x81d50)
#pragma comment(linker, "/INCLUDE:?SendTryRenameGuildFail@GamedChannel@@QEAAX_K0DF@Z")  // LIFT: keep until the caller is lifted (0x81e40)
#pragma comment(linker, "/INCLUDE:?SendAccountInventoryNotify@GamedChannel@@QEAAX_KDPEAUCharacterInventoryItem@@HD0@Z")  // LIFT: keep until the caller is lifted (0x81f30)
#pragma comment(linker, "/INCLUDE:?SendStartChargeOk@GamedChannel@@QEAAX_KPEA_WJDIF@Z")  // LIFT: keep until the caller is lifted (0x821f0)
#pragma comment(linker, "/INCLUDE:?SendStartChargeFail@GamedChannel@@QEAAX_KF@Z")  // LIFT: keep until the caller is lifted (0x82300)
#pragma comment(linker, "/INCLUDE:?SendStopChargeOk@GamedChannel@@QEAAX_K@Z")  // LIFT: keep until the caller is lifted (0x823d0)
#pragma comment(linker, "/INCLUDE:?SendStopChargeFail@GamedChannel@@QEAAX_KF@Z")  // LIFT: keep until the caller is lifted (0x82490)
#pragma comment(linker, "/INCLUDE:?SendUpdateChargeRemainTimeNotify@GamedChannel@@QEAAX_KJFI@Z")  // LIFT: keep until the caller is lifted (0x82560)
#pragma comment(linker, "/INCLUDE:?SendApplyNewChargeItemNotify@GamedChannel@@QEAAX_KPEB_WJIF@Z")  // LIFT: keep until the caller is lifted (0x82650)
#pragma comment(linker, "/INCLUDE:?SendChangeCharacterAppearanceReq@GamedChannel@@QEAA_NPEAVTransaction@TransactionChannel@@_K1PEADF2F@Z")  // LIFT: keep until the caller is lifted (0x82750)
#pragma comment(linker, "/INCLUDE:?SendChangeCharacterSexReq@GamedChannel@@QEAA_NPEAVTransaction@TransactionChannel@@_K1DPEADF2F@Z")  // LIFT: keep until the caller is lifted (0x82950)

// PDB LobbyGamePacketHandlerDef (sizeof 16).
struct LobbyGamePacketHandlerDef
{
    void* handler;
    bool auth;
    bool fragment;
};
static_assert(sizeof(LobbyGamePacketHandlerDef) == 0x10, "sizeof LobbyGamePacketHandlerDef");

// PDB global (116 entries). No lifted module owns the table yet.
// LIFT: ld-18 defines it with null entries so that LobbyDaemon.exe links. The packet handler cards (ld-16, ld-21, ld-26) fill it
// and then remove this definition. ❓ The original entries (handler, auth, fragment) are not read.
LobbyGamePacketHandlerDef LobbyGamePacketLobbySideHandlerList[116];

// 0x7b2b0
// LIFT: TransactionChannel::TSend belongs to the TransactionChannel card (ld-28). This stub lets LobbyDaemon.exe link. Remove it there. It is noinline so the callers call it out of line, as the original does (A4).
__declspec(noinline) bool TransactionChannel::TSend(Transaction*, Packet const*)
{
    // LIFT: the volatile flag keeps /OPT:ICF from folding this stub into GamedChannelManager::OnClose (0x80790).
    // It also stops LTCG from treating the stub as noreturn. The callers keep their Packet::Clear after the call.
    static volatile long s_tsendStubCalls = 0;
    s_tsendStubCalls = 1;
    if (s_tsendStubCalls != 0)
    {
        LIFT_STUB(0x7b2b0);
    }
    return false;
}

// 0x80300
GamedChannelManager::~GamedChannelManager()
{
    // LIFT: 0x80300 loop at GamedChannel.cpp:30 releases each channel. The explicit list destructor call is
    // inlined (SharedChannel.cpp:190). The member destructors run it a second time (original sequence).
    SharedChannel** channels = _channels._channels;
    for (SharedChannel** i = channels + _channels._idsize; channels != i; ++channels)
    {
        if (*channels != nullptr)
            (*channels)->removeReferenceCount(GAMED_FILE, 30);
    }
    _channels.~SharedChannelList();
}

// 0x803e0
bool GamedChannelManager::Add(GamedChannel* channel)
{
    if (channel != nullptr && channel->_rawChannel != nullptr &&
        static_cast<unsigned short>(channel->_rawChannel->GetId()) != 0)
    {
        bool result = false;
        _lock.Enter();
        if (_channels.Set(channel))
        {
            channel->addReferenceCount(GAMED_FILE, 53);
            result = true;
        }
        _lock.Leave();
        return result;
    }
    Log::Write(Log::LT_ERROR, GAMED_FILE, 47, L"[gamed], add fail; invalid parameter");
    return false;
}

// 0x804a0
void GamedChannelManager::Remove(short wid)
{
    if (wid == 0)
    {
        Log::Write(Log::LT_ERROR, GAMED_FILE, 63, L"[gamed], remove fail; invalid wid");
        return;
    }
    _lock.Enter();
    long long id = wid;
    int index = wid - static_cast<int>(_channels._idmin);
    if (index < 0 || index >= _channels._idsize)
    {
        Log::Write(Log::LT_ERROR, SHARED_CHANNEL_FILE, 200,
                   L"[shared-channel-list], acquire fail; id out of range, id:%I64d", id);
    }
    else
    {
        SharedChannel* channel = _channels._channels[index];
        if (channel != nullptr)
        {
            int removeIndex = static_cast<int>(id) - static_cast<int>(_channels._idmin);
            if (removeIndex < 0 || removeIndex >= _channels._idsize)
            {
                Log::Write(Log::LT_ERROR, SHARED_CHANNEL_FILE, 234,
                           L"[shared-channel-list], remove fail; id out of range, id:%I64d", id);
            }
            else if (_channels._channels[removeIndex] != nullptr)
            {
                _channels._channels[removeIndex] = nullptr;
                --_channels._size;
            }
            channel->removeReferenceCount(GAMED_FILE, 71);
        }
    }
    _lock.Leave();
}

// 0x805b0
GamedChannel* GamedChannelManager::Acquire(short wid)
{
    if (wid == 0)
    {
        Log::Write(Log::LT_ERROR, GAMED_FILE, 79, L"[gamed], acquire fail; invalid wid");
        return nullptr;
    }
    _lock.Enter();
    SharedChannel* channel;
    int index = wid - static_cast<int>(_channels._idmin);
    if (index < 0 || index >= _channels._idsize)
    {
        Log::Write(Log::LT_ERROR, SHARED_CHANNEL_FILE, 200,
                   L"[shared-channel-list], acquire fail; id out of range, id:%I64d", static_cast<long long>(wid));
        channel = nullptr;
    }
    else
    {
        channel = _channels._channels[index];
        if (channel != nullptr)
            channel->addReferenceCount(GAMED_FILE, 86);
    }
    _lock.Leave();
    return static_cast<GamedChannel*>(channel);
}

// 0x80680
bool GamedChannelManager::OnAccept(Session const* session) const
{
    unsigned long long id = session != nullptr ? session->_id : 0;
    Connection* connection = session->_connection;
    int portNumber = connection->_portNumber;
    Log::Write(Log::LT_DEBUG, GAMED_FILE, 93,
               L"[gamed], accept session, session-id:0x%I64X, ip-address:%s, port:%d", id,
               Network::GetAddressStringW(connection->_ip), portNumber);
    return true;
}

// 0x806e0
bool GamedChannelManager::OnConnect(Session const* session, bool) const
{
    unsigned long long id = session != nullptr ? session->_id : 0;
    Connection* connection = session->_connection;
    int portNumber = connection->_portNumber;
    Log::Write(Log::LT_ERROR, GAMED_FILE, 99,
               L"== CRASH == [gamed], connect session forbidden, session-id:0x%I64X, ip-address:%s, port:%d", id,
               Network::GetAddressStringW(connection->_ip), portNumber);
    connection = session->_connection;
    unsigned long long sessionId = session->_id;
    portNumber = connection->_portNumber;
    AlertSender::Write(GAMED_FILE, 99,
                       L"== CRASH == [gamed], connect session forbidden, session-id:0x%I64X, ip-address:%s, port:%d",
                       sessionId, Network::GetAddressStringW(connection->_ip), portNumber);
    return false;
}

// 0x80790
void GamedChannelManager::OnClose(Session const*, bool) const
{
    // Not done: needs LobbyDaemon::_instance->_gameWorldRegistry and ->_clisessionMgr (LobbyDaemon layout, cards ld-15/ld-20).
    LIFT_STUB(0x80790);
}

// 0x80980
bool GamedChannelManager::PacketHandler(Session const* session, Packet const* packet) const
{
    if (session == nullptr || packet == nullptr)
    {
        Log::Write(Log::LT_ERROR, GAMED_FILE, 139, L"== CRASH == [gamed], handle packet failed; invalid parameter");
        AlertSender::Write(GAMED_FILE, 139, L"== CRASH == [gamed], handle packet failed; invalid parameter");
        return false;
    }

    Packet::Header const* header = packet->CurHeader;
    unsigned short bodySize = static_cast<unsigned short>(header->size - 2);
    if (bodySize < 2u)
    {
        Log::Write(Log::LT_ERROR, GAMED_FILE, 145,
                   L"[gamed], handle packet failed; invalid packet size, size:%d, session-id:0x%I64X",
                   static_cast<int>(bodySize), session->_id);
        return false;
    }

    short cmd = header[1].size;
    if (static_cast<unsigned short>(cmd - 1) > 0x72u)
    {
        Log::Write(Log::LT_ERROR, GAMED_FILE, 153,
                   L"[gamed], handle packet failed; invalid packet command, cmd:%d, session-id:0x%I64X",
                   static_cast<int>(cmd), session->_id);
        return false;
    }

    LobbyGamePacketHandlerDef const* def = &LobbyGamePacketLobbySideHandlerList[cmd];
    if (def->handler == nullptr)
    {
        Log::Write(Log::LT_ERROR, GAMED_FILE, 160,
                   L"[gamed], handle packet failed; handler not exists, cmd:%d, session-id:0x%I64X",
                   static_cast<int>(cmd), session->_id);
        return false;
    }

    bool result = false;
    Channel* channel = session->GetChannel();
    SharedChannel* shared = channel != nullptr ? static_cast<SharedChannel::RawChannel*>(channel)->_owner : nullptr;
    if (def->auth)
    {
        if (shared != nullptr)
        {
            GamedChannel* gamed = static_cast<GamedChannel*>(shared);
            if (def->fragment)
            {
                bool completed = false;
                ConcatenatePacket(session, packet, completed);
                if (completed)
                {
                    PacketConcatenater* concatenater = session->_concatenater;
                    Log::Write(Log::LT_DEBUG, GAMED_FILE, 222, L"[gamed], handle begin, cmd:%d, channel-id:%I64d",
                               static_cast<int>(cmd),
                               shared->_rawChannel != nullptr ? shared->_rawChannel->GetId() : 0ULL);
                    reinterpret_cast<void (*)(GamedChannel*, PacketConcatenater*)>(def->handler)(gamed, concatenater);
                    Log::Write(Log::LT_DEBUG, GAMED_FILE, 224, L"[gamed], handle end, cmd:%d, channel-id:%I64d",
                               static_cast<int>(cmd),
                               shared->_rawChannel != nullptr ? shared->_rawChannel->GetId() : 0ULL);
                    concatenater->Clear();
                }
            }
            else
            {
                Log::Write(Log::LT_DEBUG, GAMED_FILE, 230, L"[gamed], handle begin, cmd:%d, channel-id:%I64d",
                           static_cast<int>(cmd),
                           shared->_rawChannel != nullptr ? shared->_rawChannel->GetId() : 0ULL);
                reinterpret_cast<void (*)(GamedChannel*, Packet const*)>(def->handler)(gamed, packet);
                Log::Write(Log::LT_DEBUG, GAMED_FILE, 232, L"[gamed], handle end, cmd:%d, channel-id:%I64d",
                           static_cast<int>(cmd),
                           shared->_rawChannel != nullptr ? shared->_rawChannel->GetId() : 0ULL);
            }
            result = true;
        }
        else
        {
            Log::Write(Log::LT_ERROR, GAMED_FILE, 238, L"== CRASH == [gamed], handle packet fail; unknown handler type");
            AlertSender::Write(GAMED_FILE, 238, L"== CRASH == [gamed], handle packet fail; unknown handler type");
        }
    }
    else
    {
        Log::Write(Log::LT_DEBUG, GAMED_FILE, 209, L"[gamed], handle begin, cmd:%d, session-id:0x%I64X",
                   static_cast<int>(cmd), session->_id);
        result = reinterpret_cast<bool (*)(Session const*, Packet const*)>(def->handler)(session, packet);
        Log::Write(Log::LT_DEBUG, GAMED_FILE, 211, L"[gamed], handle end, cmd:%d, session-id:0x%I64X",
                   static_cast<int>(cmd), session->_id);
    }

    if (channel != nullptr)
        channel->removeReferenceCount(SESSION_FILE, 1059);
    return result;
}

// 0x80d50
void GamedChannel::SendStopPlayNotify(unsigned long long pcid, short reason)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hqQ", 19, pcid, static_cast<int>(reason)))
        Send(&p);
}

// 0x80e20
bool GamedChannel::SendCreateCharacterReq(TransactionChannel::Transaction* t, unsigned long long pcid,
                                          id128 const& gameAccountId, char const* externalInfoData,
                                          short externalInfoSize, int ipaddress, wchar_t const* characterName,
                                          char* characterCreationData, short characterCreationDataSize,
                                          bool jumpingCharacter, short topCharacterLevel)
{
    if (t == nullptr)
    {
        Log::Write(Log::LT_ERROR, GAMED_FILE, 259,
                   L"== CRASH == [gamed], send create character req fail; null transaction");
        AlertSender::Write(GAMED_FILE, 259, L"== CRASH == [gamed], send create character req fail; null transaction");
        return false;
    }

    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (p.Compose("hqqobisbQh", 20, t->GetTid(), pcid, gameAccountId, externalInfoData,
                  static_cast<int>(externalInfoSize), ipaddress, characterName, characterCreationData,
                  static_cast<int>(characterCreationDataSize), static_cast<int>(jumpingCharacter),
                  static_cast<int>(topCharacterLevel)) == 0)
    {
        Log::Write(Log::LT_ERROR, GAMED_FILE, 267,
                   L"[gamed], send create character req fail; compose fail, tid:0x%I64X", t->GetTid());
        return false;
    }
    return TSend(t, &p);
}

// 0x81040
bool GamedChannel::SendDeleteCharacterReq(TransactionChannel::Transaction* t, unsigned long long pcid,
                                          char const* externalInfoData, short externalInfoSize, int ipaddress)
{
    if (t == nullptr)
    {
        Log::Write(Log::LT_ERROR, GAMED_FILE, 277,
                   L"== CRASH == [gamed], send delete character req fail; null transaction");
        AlertSender::Write(GAMED_FILE, 277, L"== CRASH == [gamed], send delete character req fail; null transaction");
        return false;
    }

    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 == p.Compose("hqqbi", 23, t->GetTid(), pcid, externalInfoData, static_cast<int>(externalInfoSize), ipaddress))
    {
        Log::Write(Log::LT_ERROR, GAMED_FILE, 285,
                   L"[gamed], send delete character req fail; compose fail, tid:0x%I64X", t->GetTid());
        return false;
    }
    return TSend(t, &p);
}

// 0x811c0
bool GamedChannel::SendRestoreCharacterReq(TransactionChannel::Transaction* t, unsigned long long pcid)
{
    if (t == nullptr)
    {
        Log::Write(Log::LT_ERROR, GAMED_FILE, 295,
                   L"== CRASH == [gamed], send restore character req fail; null transaction");
        AlertSender::Write(GAMED_FILE, 295, L"== CRASH == [gamed], send restore character req fail; null transaction");
        return false;
    }

    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 == p.Compose("hqq", 26, t->GetTid(), pcid))
    {
        Log::Write(Log::LT_ERROR, GAMED_FILE, 303,
                   L"[gamed], send restore character req fail; compose fail, tid:0x%I64X", t->GetTid());
        return false;
    }
    return TSend(t, &p);
}

// 0x81320
void GamedChannel::SendDeleteCharacterCompleteNotify(unsigned long long pcid)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hq", 29, pcid))
        Send(&p);
}

// 0x813e0
void GamedChannel::SendCloseSessionNotify(unsigned long long clikey)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hq", 13, clikey))
        Send(&p);
}

// 0x814a0
bool GamedChannel::SendKickReq(TransactionChannel::Transaction* t, unsigned long long pcid, unsigned long long clikey,
                               unsigned long long gamekey, char reason)
{
    if (t == nullptr)
    {
        Log::Write(Log::LT_ERROR, GAMED_FILE, 335, L"== CRASH == [gamed], send kick req fail; null transaction");
        AlertSender::Write(GAMED_FILE, 335, L"== CRASH == [gamed], send kick req fail; null transaction");
        return false;
    }

    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 == p.Compose("hqqqqQ", 14, t->GetTid(), pcid, clikey, gamekey, static_cast<int>(reason)))
    {
        Log::Write(Log::LT_ERROR, GAMED_FILE, 343, L"[gamed], send kick req fail; compose fail, tid:0x%I64X",
                   t->GetTid());
        return false;
    }
    return TSend(t, &p);
}

// 0x81620
void GamedChannel::SendEnterWorldFail(unsigned long long tid, short reason)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hqE", 7, tid, static_cast<int>(reason)))
        Send(&p);
}

// 0x816f0
void GamedChannel::SendLeaveWorldOk(unsigned long long tid, unsigned long long token)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hqq", 9, tid, token))
        Send(&p);
}

// 0x817c0
void GamedChannel::SendLeaveWorldFail(unsigned long long tid, short reason)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hqE", 10, tid, static_cast<int>(reason)))
        Send(&p);
}

// 0x81890
void GamedChannel::SendUpdateCharacterDataOk(unsigned long long tid)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hq", 40, tid))
        Send(&p);
}

// 0x81950
void GamedChannel::SendUpdateCharacterDataFail(unsigned long long tid, short reason)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hqE", 41, tid, static_cast<int>(reason)))
        Send(&p);
}

// 0x81a20
void GamedChannel::SendUpdateAccountDataOk(unsigned long long tid)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hq", 43, tid))
        Send(&p);
}

// 0x81ae0
void GamedChannel::SendUpdateAccountDataFail(unsigned long long tid, short reason)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hqE", 44, tid, static_cast<int>(reason)))
        Send(&p);
}

// 0x81bb0
void GamedChannel::SendTryRegisterGuildOk(unsigned long long tid, unsigned long long guildid)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hqq", 46, tid, guildid))
        Send(&p);
}

// 0x81c80
void GamedChannel::SendTryRegisterGuildFail(unsigned long long tid, short reason)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hqE", 47, tid, static_cast<int>(reason)))
        Send(&p);
}

// 0x81d50
void GamedChannel::SendTryRenameGuildOk(unsigned long long tid, unsigned long long guildId, char renameGuildType, unsigned long long renamekey)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hqqcq", 51, tid, guildId, static_cast<int>(renameGuildType), renamekey))
        Send(&p);
}

// 0x81e40
void GamedChannel::SendTryRenameGuildFail(unsigned long long tid, unsigned long long guildId, char renameGuildType, short failReason)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hqqcE", 52, tid, guildId, static_cast<int>(renameGuildType), static_cast<int>(failReason)))
        Send(&p);
}

// 0x81f30
void GamedChannel::SendAccountInventoryNotify(unsigned long long pcid, char notificationType, CharacterInventoryItem* items,
                                              int itemCount, char itemRemain, unsigned long long goodsLabelIdMin)
{
    FragmentPacket fp(56, "hiqQCqqi;Qq");
    fp.packet.Allocate(&fp.composer);
    fp.Compose(2, pcid, static_cast<unsigned int>(notificationType));
    if (fp.packet.CurHeader == nullptr || static_cast<unsigned short>(4000 - fp.packet.CurHeader->size) < 2u)
        fp.packet.Allocate(&fp.composer);
    fp.composer.PushRepeatCount(&fp.packet);
    if (items != nullptr && itemCount > 0)
    {
        int index = 0;
        long long position = 0;
        while (true)
        {
            if (fp.packet.CurHeader == nullptr || static_cast<unsigned short>(4000 - fp.packet.CurHeader->size) < 0x14u)
                fp.packet.Allocate(&fp.composer);
            if (fp.Compose(3, items->instanceId, items->labelId, static_cast<int>(items->dataId)) == 0)
            {
                Log::Write(Log::LT_ERROR, GAMED_FILE, 475,
                           L"[gamed], send list character inventory item ok fail; compose #%d item fail, "
                           L"label-id:0x%I64X, item-instance-id:0x%I64X, item-data-id:%u",
                           index, items->labelId, items->instanceId, items->dataId);
                return;
            }
            RepeatPacketComposer& composer = fp.composer;
            int start = composer.start[composer.top] + 1;
            if (composer.subTop < 0)
                composer.index = start;
            else
                composer.sub[composer.subTop].index = start;
            ++*composer.counts[composer.top];
            ++index;
            ++position;
            ++items;
            if (position >= itemCount)
                break;
        }
    }

    fp.composer.PopRepeatCount();
    if (fp.packet.CurHeader == nullptr || static_cast<unsigned short>(4000 - fp.packet.CurHeader->size) < 9u)
        fp.packet.Allocate(&fp.composer);
    fp.Compose(2, static_cast<unsigned int>(itemRemain), goodsLabelIdMin);
    if (fp.packet.Splitter != nullptr)
        fp.packet.Splitter->Finalize(fp.packet.CurHeader);
    Send(&fp.packet);
}

// 0x821f0
void GamedChannel::SendStartChargeOk(unsigned long long tid, wchar_t* chargeKey, long remainPlayTime, char chargeBaseType, unsigned int itemId, short reservations)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hqsiQih", 31, tid, chargeKey, static_cast<int>(remainPlayTime), static_cast<int>(chargeBaseType), itemId, static_cast<int>(reservations)))
        Send(&p);
}

// 0x82300
void GamedChannel::SendStartChargeFail(unsigned long long tid, short reason)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hqE", 32, tid, static_cast<int>(reason)))
        Send(&p);
}

// 0x823d0
void GamedChannel::SendStopChargeOk(unsigned long long tid)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hq", 34, tid))
        Send(&p);
}

// 0x82490
void GamedChannel::SendStopChargeFail(unsigned long long tid, short reason)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hqE", 35, tid, static_cast<int>(reason)))
        Send(&p);
}

// 0x82560
void GamedChannel::SendUpdateChargeRemainTimeNotify(unsigned long long pcid, long remainPlayTime, short reservations, unsigned int itemId)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hqihi", 36, pcid, static_cast<int>(remainPlayTime), static_cast<int>(reservations), itemId))
        Send(&p);
}

// 0x82650
void GamedChannel::SendApplyNewChargeItemNotify(unsigned long long pcid, wchar_t const* chargeKey, long remainPlayTime, unsigned int itemId, short reservations)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hqsiih", 37, pcid, chargeKey, static_cast<int>(remainPlayTime), itemId, static_cast<int>(reservations)))
        Send(&p);
}

// 0x82750
bool GamedChannel::SendChangeCharacterAppearanceReq(TransactionChannel::Transaction* t, unsigned long long serviceId, unsigned long long pcid, char* showcaseData, short showcaseDataSize, char* makingData, short makingDataSize)
{
    if (t == nullptr)
    {
        Log::Write(Log::LT_ERROR, GAMED_FILE, 551,
                   L"== CRASH == [gamed], send change-character-appearance req fail; null transaction");
        AlertSender::Write(GAMED_FILE, 551,
                           L"== CRASH == [gamed], send change-character-appearance req fail; null transaction");
        return false;
    }

    if (!(showcaseData != nullptr && showcaseDataSize > 0 && makingData != nullptr && makingDataSize > 0))
    {
        Log::Write(Log::LT_ERROR, GAMED_FILE, 557,
                   L"== CRASH == [gamed], send change-character-appearance req fail; invalid parameter, tid:0x%I64X", t->GetTid());
        AlertSender::Write(GAMED_FILE, 557,
                           L"== CRASH == [gamed], send change-character-appearance req fail; invalid parameter, tid:0x%I64X",
                           t->GetTid());
        return false;
    }

    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (p.Compose("hqqqbb", 57, t->GetTid(), serviceId, pcid, showcaseData, static_cast<int>(showcaseDataSize), makingData, static_cast<int>(makingDataSize)) == 0)
    {
        Log::Write(Log::LT_ERROR, GAMED_FILE, 571, L"[gamed], send change-character-appearance req fail; compose fail, tid:0x%I64X",
                   t->GetTid());
        return false;
    }
    return TSend(t, &p);
}

// 0x82950
bool GamedChannel::SendChangeCharacterSexReq(TransactionChannel::Transaction* t, unsigned long long serviceId, unsigned long long pcid, char newSex, char* showcaseData, short showcaseDataSize, char* makingData, short makingDataSize)
{
    if (t == nullptr)
    {
        Log::Write(Log::LT_ERROR, GAMED_FILE, 581,
                   L"== CRASH == [gamed], send change-character-sex req fail; null transaction");
        AlertSender::Write(GAMED_FILE, 581,
                           L"== CRASH == [gamed], send change-character-sex req fail; null transaction");
        return false;
    }

    if (!(newSex > 0 && showcaseData != nullptr && showcaseDataSize > 0 && makingData != nullptr && makingDataSize > 0))
    {
        Log::Write(Log::LT_ERROR, GAMED_FILE, 587,
                   L"== CRASH == [gamed], send change-character-sex req fail; invalid parameter, tid:0x%I64X", t->GetTid());
        AlertSender::Write(GAMED_FILE, 587,
                           L"== CRASH == [gamed], send change-character-sex req fail; invalid parameter, tid:0x%I64X",
                           t->GetTid());
        return false;
    }

    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 == p.Compose("hqqqcbb", 60, t->GetTid(), serviceId, pcid, static_cast<int>(newSex), showcaseData, static_cast<int>(showcaseDataSize), makingData, static_cast<int>(makingDataSize)))
    {
        Log::Write(Log::LT_ERROR, GAMED_FILE, 602, L"[gamed], send change-character-sex req fail; compose fail, tid:0x%I64X",
                   t->GetTid());
        return false;
    }
    return TSend(t, &p);
}

// 0x82f70
void GamedChannel::SendExtendJumpingCharacterCreationQuotaWithAccountInventoryItemOk(unsigned long long, int)
{
    LIFT_STUB(0x82f70);
}

// 0x83060
void GamedChannel::SendExtendJumpingCharacterCreationQuotaWithAccountInventoryItemFail(unsigned long long, short)
{
    LIFT_STUB(0x83060);
}

// 0x83150
void GamedChannel::SendUpgradeJumpingCharacterStateWithCreationQuotaOk(unsigned long long, char, int)
{
    LIFT_STUB(0x83150);
}

// 0x83250
void GamedChannel::SendUpgradeJumpingCharacterStateWithCreationQuotaFail(unsigned long long, short)
{
    LIFT_STUB(0x83250);
}

// 0x83340
void GamedChannel::SendUpdateJumpingCharacterStateOk(unsigned long long, char)
{
    LIFT_STUB(0x83340);
}

// 0x83430
void GamedChannel::SendUpdateJumpingCharacterStateFail(unsigned long long, short)
{
    LIFT_STUB(0x83430);
}

// 0x83520
void GamedChannel::SendSecondPasswordGetStatusOk(unsigned long long, unsigned long long, char, int, int, long long, long long, long long)
{
    LIFT_STUB(0x83520);
}

// 0x83670
void GamedChannel::SendSecondPasswordGetStatusFail(unsigned long long, unsigned long long, short)
{
    LIFT_STUB(0x83670);
}

// 0x83770
void GamedChannel::SendSecondPasswordIsVerifiedOk(unsigned long long, unsigned long long)
{
    LIFT_STUB(0x83770);
}

// 0x83860
void GamedChannel::SendSecondPasswordIsVerifiedFail(unsigned long long, unsigned long long, short)
{
    LIFT_STUB(0x83860);
}

// 0x83b00
void GamedChannel::SendGetGradeListFail(unsigned long long, char, unsigned long long, short)
{
    LIFT_STUB(0x83b00);
}

// 0x83c20
void GamedChannel::SendActivateGradeOk(unsigned long long, unsigned long long, int, int, long long, long long)
{
    LIFT_STUB(0x83c20);
}

// 0x83d60
void GamedChannel::SendActivateGradeFail(unsigned long long, unsigned long long, int, int, short)
{
    LIFT_STUB(0x83d60);
}

// 0x83ea0
void GamedChannel::SendChangedGradeNotify(unsigned long long, int, int, int, bool, int, long long, long long, wchar_t const*)
{
    LIFT_STUB(0x83ea0);
}

// 0x84090
void GamedChannel::SendChangedGradeLevelNotify(unsigned long long, int, int, int, int, int, int)
{
    LIFT_STUB(0x84090);
}

// 0x841a0
void GamedChannel::SendDepositGameMileageOk(unsigned long long, char, char, unsigned long long, unsigned long long, unsigned long long, id128 const&, unsigned long long, short, long long, int)
{
    LIFT_STUB(0x841a0);
}

// 0x84310
void GamedChannel::SendDepositGameMileageFail(unsigned long long, char, char, unsigned long long, unsigned long long, unsigned long long, id128 const&, short, int)
{
    LIFT_STUB(0x84310);
}

// 0x84460
void GamedChannel::SendAuctionBidOk(unsigned long long, id128&)
{
    LIFT_STUB(0x84460);
}

// 0x845f0
void GamedChannel::SendAuctionBidFail(unsigned long long, id128&, short)
{
    LIFT_STUB(0x845f0);
}

// 0x84790
void GamedChannel::SendTakeAccountTimeBasedPlayRewardFail(unsigned long long, unsigned long long, int, char, short, long long, short, int)
{
    LIFT_STUB(0x84790);
}

// 0x848f0
void GamedChannel::SendUpdateAccountExpOk(unsigned long long, unsigned long long)
{
    LIFT_STUB(0x848f0);
}

// 0x849c0
void GamedChannel::SendUpdateAccountExpFail(unsigned long long, unsigned long long, short)
{
    LIFT_STUB(0x849c0);
}

// 0x84aa0
void GamedChannel::SendUpdateAccountContentQuotaOk(unsigned long long, unsigned long long)
{
    LIFT_STUB(0x84aa0);
}

// 0x84b70
void GamedChannel::SendUpdateAccountContentQuotaFail(unsigned long long, unsigned long long, short)
{
    LIFT_STUB(0x84b70);
}

// 0x84c50
void GamedChannel::SendUpdateAccountRecycleTimeOk(unsigned long long, unsigned long long)
{
    LIFT_STUB(0x84c50);
}

// 0x84d20
void GamedChannel::SendUpdateAccountRecycleTimeFail(unsigned long long, unsigned long long, short)
{
    LIFT_STUB(0x84d20);
}
