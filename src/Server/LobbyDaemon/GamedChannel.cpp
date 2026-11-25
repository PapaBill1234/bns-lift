// GamedChannel.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "PlacementNew.h"
#include <winsock2.h>
#include <windows.h>
#include "GamedChannel.h"
#include "AlertSender.h"
#include "Connection.h"
#include "CliSessionManager.h"
#include "FragmentPacket.h"
#include "GameWorld.h"
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
// LIFT: No PDB symbol. The binary uses the literal as the file string of the log and reference count calls (first use at 0x804a0).
wchar_t const* const GAMED_FILE = L"GamedChannel.cpp";
// LIFT: No PDB symbol. The binary uses the literal as the file string of SharedChannelList::Acquire/Remove errors (lines 200 and 234; used in GamedChannelManager::Remove 0x804a0 and GamedChannelManager::Acquire 0x805b0).
wchar_t const* const SHARED_CHANNEL_FILE = L"..\\Shared\\SharedChannel.cpp";
// LIFT: No PDB symbol. The binary uses the literal as the file string of the Session reference count call (line 1059; used in GamedChannelManager::PacketHandler 0x80980).
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
#pragma comment(linker, "/INCLUDE:?SendChangeCharacterRaceReq@GamedChannel@@QEAA_NPEAVTransaction@TransactionChannel@@_K1DDPEADF2F@Z")  // LIFT: keep until the caller is lifted (0x82b70)
#pragma comment(linker, "/INCLUDE:?SendRenameCharacterReq@GamedChannel@@QEAA_NPEAVTransaction@TransactionChannel@@_K1PEB_W2@Z")  // LIFT: keep until the caller is lifted (0x82db0)
#pragma comment(linker, "/INCLUDE:?SendExtendJumpingCharacterCreationQuotaWithAccountInventoryItemOk@GamedChannel@@QEAAX_KH@Z")  // LIFT: keep until the caller is lifted (0x82f70)
#pragma comment(linker, "/INCLUDE:?SendExtendJumpingCharacterCreationQuotaWithAccountInventoryItemFail@GamedChannel@@QEAAX_KF@Z")  // LIFT: keep until the caller is lifted (0x83060)
#pragma comment(linker, "/INCLUDE:?SendUpgradeJumpingCharacterStateWithCreationQuotaOk@GamedChannel@@QEAAX_KDH@Z")  // LIFT: keep until the caller is lifted (0x83150)
#pragma comment(linker, "/INCLUDE:?SendUpgradeJumpingCharacterStateWithCreationQuotaFail@GamedChannel@@QEAAX_KF@Z")  // LIFT: keep until the caller is lifted (0x83250)
#pragma comment(linker, "/INCLUDE:?SendUpdateJumpingCharacterStateOk@GamedChannel@@QEAAX_KD@Z")  // LIFT: keep until the caller is lifted (0x83340)
#pragma comment(linker, "/INCLUDE:?SendUpdateJumpingCharacterStateFail@GamedChannel@@QEAAX_KF@Z")  // LIFT: keep until the caller is lifted (0x83430)
#pragma comment(linker, "/INCLUDE:?SendSecondPasswordGetStatusOk@GamedChannel@@QEAAX_K0DHH_J11@Z")  // LIFT: keep until the caller is lifted (0x83520)
#pragma comment(linker, "/INCLUDE:?SendSecondPasswordGetStatusFail@GamedChannel@@QEAAX_K0F@Z")  // LIFT: keep until the caller is lifted (0x83670)
#pragma comment(linker, "/INCLUDE:?SendSecondPasswordIsVerifiedOk@GamedChannel@@QEAAX_K0@Z")  // LIFT: keep until the caller is lifted (0x83770)
#pragma comment(linker, "/INCLUDE:?SendSecondPasswordIsVerifiedFail@GamedChannel@@QEAAX_K0F@Z")  // LIFT: keep until the caller is lifted (0x83860)
#pragma comment(linker, "/INCLUDE:?SendAuctionEscrowReq@GamedChannel@@QEAA_NPEAVTransaction@TransactionChannel@@_K_JAEBTid128@@1@Z")  // LIFT: keep until the caller is lifted (0x83960)
#pragma comment(linker, "/INCLUDE:?SendGetGradeListFail@GamedChannel@@QEAAX_KD0F@Z")  // LIFT: keep until the caller is lifted (0x83b00)
#pragma comment(linker, "/INCLUDE:?SendActivateGradeOk@GamedChannel@@QEAAX_K0HH_J1@Z")  // LIFT: keep until the caller is lifted (0x83c20)
#pragma comment(linker, "/INCLUDE:?SendActivateGradeFail@GamedChannel@@QEAAX_K0HHF@Z")  // LIFT: keep until the caller is lifted (0x83d60)
#pragma comment(linker, "/INCLUDE:?SendChangedGradeNotify@GamedChannel@@QEAAX_KHHH_NH_J2PEB_W@Z")  // LIFT: keep until the caller is lifted (0x83ea0)
#pragma comment(linker, "/INCLUDE:?SendChangedGradeLevelNotify@GamedChannel@@QEAAX_KHHHHHH@Z")  // LIFT: keep until the caller is lifted (0x84090)
#pragma comment(linker, "/INCLUDE:?SendDepositGameMileageOk@GamedChannel@@QEAAX_KDD000AEBTid128@@0F_JH@Z")  // LIFT: keep until the caller is lifted (0x841a0)
#pragma comment(linker, "/INCLUDE:?SendDepositGameMileageFail@GamedChannel@@QEAAX_KDD000AEBTid128@@FH@Z")  // LIFT: keep until the caller is lifted (0x84310)
#pragma comment(linker, "/INCLUDE:?SendAuctionBidOk@GamedChannel@@QEAAX_KAEATid128@@@Z")  // LIFT: keep until the caller is lifted (0x84460)
#pragma comment(linker, "/INCLUDE:?SendAuctionBidFail@GamedChannel@@QEAAX_KAEATid128@@F@Z")  // LIFT: keep until the caller is lifted (0x845f0)
#pragma comment(linker, "/INCLUDE:?SendTakeAccountTimeBasedPlayRewardFail@GamedChannel@@QEAAX_K0HDF_JFH@Z")  // LIFT: keep until the caller is lifted (0x84790)
#pragma comment(linker, "/INCLUDE:?SendUpdateAccountExpOk@GamedChannel@@QEAAX_K0@Z")  // LIFT: keep until the caller is lifted (0x848f0)
#pragma comment(linker, "/INCLUDE:?SendUpdateAccountExpFail@GamedChannel@@QEAAX_K0F@Z")  // LIFT: keep until the caller is lifted (0x849c0)
#pragma comment(linker, "/INCLUDE:?SendUpdateAccountContentQuotaOk@GamedChannel@@QEAAX_K0@Z")  // LIFT: keep until the caller is lifted (0x84aa0)
#pragma comment(linker, "/INCLUDE:?SendUpdateAccountContentQuotaFail@GamedChannel@@QEAAX_K0F@Z")  // LIFT: keep until the caller is lifted (0x84b70)
#pragma comment(linker, "/INCLUDE:?SendUpdateAccountRecycleTimeOk@GamedChannel@@QEAAX_K0@Z")  // LIFT: keep until the caller is lifted (0x84c50)
#pragma comment(linker, "/INCLUDE:?SendUpdateAccountRecycleTimeFail@GamedChannel@@QEAAX_K0F@Z")  // LIFT: keep until the caller is lifted (0x84d20)

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
void GamedChannelManager::OnClose(Session const* session, bool) const
{
    Channel* channel = session->GetChannel();
    if (channel != nullptr)
    {
        SharedChannel* shared = static_cast<SharedChannel::RawChannel*>(channel)->_owner;
        if (shared != nullptr)
        {
            short wid = 0;
            Log::Write(Log::LT_ERROR, GAMED_FILE, 113, L"[gamed], gamed channel closed, wid:%d",
                       shared->_rawChannel != nullptr ? static_cast<int>(static_cast<short>(shared->_rawChannel->GetId())) : 0);
            if (shared->_rawChannel != nullptr)
                wid = static_cast<short>(shared->_rawChannel->GetId());
            const_cast<GamedChannelManager*>(this)->Remove(wid);
            if (wid != 0)
            {
                GameWorld* world = LobbyDaemon::_instance->_gameWorldRegistry->Get(wid);
                if (world != nullptr)
                    world->_live = false;
                LobbyDaemon::_instance->_clisessionMgr->OnCloseGamedChannel(wid);
            }
        }
        else
        {
            Log::Write(Log::LT_ERROR, GAMED_FILE, 118,
                       L"== CRASH == [gamed], gamed channel closed exception; raw-channel has no shared-channel, channel-id:%I64d",
                       channel->GetId());
            AlertSender::Write(GAMED_FILE, 118,
                               L"== CRASH == [gamed], gamed channel closed exception; raw-channel has no shared-channel, channel-id:%I64d",
                               channel->GetId());
        }
        channel->removeReferenceCount(SESSION_FILE, 1059);
    }
    Log::Write(Log::LT_ERROR, GAMED_FILE, 130, L"[gamed], session closed, session-id:0x%I64X", session->_id);
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
    if (0 == p.Compose("hqqobisbQh", 20, t->GetTid(), pcid, gameAccountId, externalInfoData,
                  static_cast<int>(externalInfoSize), ipaddress, characterName, characterCreationData,
                  static_cast<int>(characterCreationDataSize), static_cast<int>(jumpingCharacter),
                  static_cast<int>(topCharacterLevel)))
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

// 0x82b70
bool GamedChannel::SendChangeCharacterRaceReq(TransactionChannel::Transaction* t, unsigned long long serviceId, unsigned long long pcid, char newRace, char newSex, char* showcaseData, short showcaseDataSize, char* makingData, short makingDataSize)
{
    if (t == nullptr)
    {
        Log::Write(Log::LT_ERROR, GAMED_FILE, 612,
                   L"== CRASH == [gamed], send change-character-race req fail; null transaction");
        AlertSender::Write(GAMED_FILE, 612,
                           L"== CRASH == [gamed], send change-character-race req fail; null transaction");
        return false;
    }

    if (!(newRace > 0 && newSex > 0 && showcaseData != nullptr && showcaseDataSize > 0 && makingData != nullptr && makingDataSize > 0))
    {
        Log::Write(Log::LT_ERROR, GAMED_FILE, 618,
                   L"== CRASH == [gamed], send change-character-race req fail; invalid parameter, tid:0x%I64X", t->GetTid());
        AlertSender::Write(GAMED_FILE, 618,
                           L"== CRASH == [gamed], send change-character-race req fail; invalid parameter, tid:0x%I64X",
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
    if (0 == p.Compose("hqqqccbb", 63, t->GetTid(), serviceId, pcid, static_cast<int>(newRace), static_cast<int>(newSex), showcaseData, static_cast<int>(showcaseDataSize), makingData, static_cast<int>(makingDataSize)))
    {
        Log::Write(Log::LT_ERROR, GAMED_FILE, 634,
                   L"[gamed], send change-character-race req fail; compose fail, tid:0x%I64X", t->GetTid());
        return false;
    }
    return TSend(t, &p);
}

// 0x82db0
bool GamedChannel::SendRenameCharacterReq(TransactionChannel::Transaction* t, unsigned long long serviceId, unsigned long long pcid, wchar_t const* oldName, wchar_t const* newName)
{
    if (t == nullptr)
    {
        Log::Write(Log::LT_ERROR, GAMED_FILE, 645,
                   L"== CRASH == [gamed], send rename-character req fail; null transaction");
        AlertSender::Write(GAMED_FILE, 645,
                           L"== CRASH == [gamed], send rename-character req fail; null transaction");
        return false;
    }

    if (!(oldName != nullptr && newName != nullptr))
    {
        Log::Write(Log::LT_ERROR, GAMED_FILE, 651,
                   L"== CRASH == [gamed], send rename-character req fail; invalid parameter, tid:0x%I64X", t->GetTid());
        AlertSender::Write(GAMED_FILE, 651,
                           L"== CRASH == [gamed], send rename-character req fail; invalid parameter, tid:0x%I64X",
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
    if (0 == p.Compose("hqqqss", 66, t->GetTid(), serviceId, pcid, oldName, newName))
    {
        Log::Write(Log::LT_ERROR, GAMED_FILE, 665,
                   L"[gamed], send rename-character req fail; compose fail, tid:0x%I64X", t->GetTid());
        return false;
    }
    return TSend(t, &p);
}

// 0x82f70
void GamedChannel::SendExtendJumpingCharacterCreationQuotaWithAccountInventoryItemOk(unsigned long long tid, int remainQuota)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 == p.Compose("hqi", 70, tid, remainQuota))
        Log::Write(Log::LT_ERROR, GAMED_FILE, 679,
                   L"[gamed], send extend-jumping-character-creation-quota ok fail; compose fail, game-tid:0x%I64X", tid);
    else
        Send(&p);
}

// 0x83060
void GamedChannel::SendExtendJumpingCharacterCreationQuotaWithAccountInventoryItemFail(unsigned long long tid, short reason)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 == p.Compose("hqE", 71, tid, static_cast<int>(reason)))
        Log::Write(Log::LT_ERROR, GAMED_FILE, 693,
                   L"[gamed], send extend-jumping-character-creation-quota fail; compose fail, game-tid:0x%I64X", tid);
    else
        Send(&p);
}

// 0x83150
void GamedChannel::SendUpgradeJumpingCharacterStateWithCreationQuotaOk(unsigned long long tid, char jumpingCharacterState, int remainQuota)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 == p.Compose("hqQi", 73, tid, static_cast<int>(jumpingCharacterState), remainQuota))
        Log::Write(Log::LT_ERROR, GAMED_FILE, 707,
                   L"[gamed], send upgrade-jumping-character-state ok fail; compose fail, game-tid:0x%I64X", tid);
    else
        Send(&p);
}

// 0x83250
void GamedChannel::SendUpgradeJumpingCharacterStateWithCreationQuotaFail(unsigned long long tid, short reason)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 == p.Compose("hqE", 74, tid, static_cast<int>(reason)))
        Log::Write(Log::LT_ERROR, GAMED_FILE, 721,
                   L"[gamed], send upgrade-jumping-character-state fail; compose fail, game-tid:0x%I64X", tid);
    else
        Send(&p);
}

// 0x83340
void GamedChannel::SendUpdateJumpingCharacterStateOk(unsigned long long tid, char jumpingCharacterState)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 == p.Compose("hqQ", 76, tid, static_cast<int>(jumpingCharacterState)))
        Log::Write(Log::LT_ERROR, GAMED_FILE, 735,
                   L"[gamed], send update-jumping-character-state ok fail; compose fail, game-tid:0x%I64X", tid);
    else
        Send(&p);
}

// 0x83430
void GamedChannel::SendUpdateJumpingCharacterStateFail(unsigned long long tid, short reason)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 == p.Compose("hqE", 77, tid, static_cast<int>(reason)))
        Log::Write(Log::LT_ERROR, GAMED_FILE, 749,
                   L"[gamed], send update-jumping-character-state fail; compose fail, game-tid:0x%I64X", tid);
    else
        Send(&p);
}

// 0x83520
void GamedChannel::SendSecondPasswordGetStatusOk(unsigned long long tid, unsigned long long pcid, char blockStatus, int authFailLimitCount, int authFailCount, long long blockedUntil, long long deleteAt, long long actionMask)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 == p.Compose("hqqQiiqqq", 81, tid, pcid, static_cast<int>(blockStatus), authFailLimitCount, authFailCount, blockedUntil, deleteAt, actionMask))
        Log::Write(Log::LT_ERROR, GAMED_FILE, 764,
                   L"[gamed], send second-password-get-status ok fail; compose fail, game-tid:0x%I64X", tid);
    else
        Send(&p);
}

// 0x83670
void GamedChannel::SendSecondPasswordGetStatusFail(unsigned long long tid, unsigned long long pcid, short reason)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 == p.Compose("hqqE", 82, tid, pcid, static_cast<int>(reason)))
        Log::Write(Log::LT_ERROR, GAMED_FILE, 778,
                   L"[gamed], send second-password-get-status fail fail; compose fail, game-tid:0x%I64X", tid);
    else
        Send(&p);
}

// 0x83770
void GamedChannel::SendSecondPasswordIsVerifiedOk(unsigned long long tid, unsigned long long pcid)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 == p.Compose("hqq", 84, tid, pcid))
        Log::Write(Log::LT_ERROR, GAMED_FILE, 792,
                   L"[gamed], send second-password-is-verified ok fail; compose fail, game-tid:0x%I64X", tid);
    else
        Send(&p);
}

// 0x83860
void GamedChannel::SendSecondPasswordIsVerifiedFail(unsigned long long tid, unsigned long long pcid, short reason)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 == p.Compose("hqqE", 85, tid, pcid, static_cast<int>(reason)))
        Log::Write(Log::LT_ERROR, GAMED_FILE, 806,
                   L"[gamed], send second-password-is-verified fail fail; compose fail, game-tid:0x%I64X", tid);
    else
        Send(&p);
}

// 0x83960
bool GamedChannel::SendAuctionEscrowReq(TransactionChannel::Transaction* t, unsigned long long pcid, long long money, id128 const& auctionId, unsigned long long escrowId)
{
    if (t == nullptr)
    {
        Log::Write(Log::LT_ERROR, GAMED_FILE, 816,
                   L"== CRASH == [gamed], send auction escrow req fail; null transaction");
        AlertSender::Write(GAMED_FILE, 816,
                           L"== CRASH == [gamed], send auction escrow req fail; null transaction");
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
    if (0 == p.Compose("hqqqoq", 86, t->GetTid(), pcid, money, auctionId, escrowId))
    {
        Log::Write(Log::LT_ERROR, GAMED_FILE, 829,
                   L"[gamed], send auction escrow req fail; compose fail, tid:0x%I64X", t->GetTid());
        return false;
    }
    return TSend(t, &p);
}

// 0x83b00
void GamedChannel::SendGetGradeListFail(unsigned long long tid, char locationHint, unsigned long long pcid, short reason)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 == p.Compose("hqQqE", 94, tid, static_cast<int>(locationHint), pcid, static_cast<int>(reason)))
        Log::Write(Log::LT_ERROR, GAMED_FILE, 842,
                   L"[gamed], send get grade list fail fail; compose fail, game-tid:0x%I64X, location-hint:%d, pcid:0x%I64X, reason:%d",
                   tid, static_cast<int>(locationHint), pcid, static_cast<int>(reason));
    else
        Send(&p);
}

// 0x83c20
void GamedChannel::SendActivateGradeOk(unsigned long long tid, unsigned long long pcid, int gameGradeKey, int gradeId, long long effectiveFrom, long long effectiveTo)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 == p.Compose("hqqiiqq", 98, tid, pcid, gameGradeKey, gradeId, effectiveFrom, effectiveTo))
        Log::Write(Log::LT_ERROR, GAMED_FILE, 855,
                   L"[gamed], send activate grade ok fail; compose fail, game-tid:0x%I64X, pcid:0x%I64X, game-grade-key:%d, grade-id:%d",
                   tid, pcid, gameGradeKey, gradeId);
    else
        Send(&p);
}

// 0x83d60
void GamedChannel::SendActivateGradeFail(unsigned long long tid, unsigned long long pcid, int keyType, int key, short reason)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 == p.Compose("hqqQiE", 99, tid, pcid, keyType, key, static_cast<int>(reason)))
        Log::Write(Log::LT_ERROR, GAMED_FILE, 868,
                   L"[gamed], send activate grade fail fail; compose fail, game-tid:0x%I64X, pcid:0x%I64X, key-type:%d, key:%d, reason:%d",
                   tid, pcid, keyType, key, static_cast<int>(reason));
    else
        Send(&p);
}

// 0x83ea0
void GamedChannel::SendChangedGradeNotify(unsigned long long pcid, int revision, int gameGradeKey, int gradeId, bool activation, int gradeCount, long long totalEffectiveFrom, long long totalEffectiveTo, wchar_t const* reason)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    // LIFT: The binary compares the reason text with the five known names. Other text (and null or empty text) gives 0.
    char reasonCode = 0;
    if (reason != nullptr && reason[0] != L'\0')
    {
        if (wcscmp(reason, L"Activated") == 0)
            reasonCode = 1;
        else if (wcscmp(reason, L"ActivatedWithAdding") == 0)
            reasonCode = 2;
        else if (wcscmp(reason, L"Added") == 0)
            reasonCode = 3;
        else if (wcscmp(reason, L"Deleted") == 0)
            reasonCode = 4;
        else if (wcscmp(reason, L"DeletedAndExhausted") == 0)
            reasonCode = 5;
    }

    if (0 != p.Compose("hqiiiQiqqQ", 95, pcid, revision, gameGradeKey, gradeId, static_cast<int>(activation), gradeCount, totalEffectiveFrom, totalEffectiveTo, static_cast<int>(reasonCode)))
        Send(&p);
}

// 0x84090
void GamedChannel::SendChangedGradeLevelNotify(unsigned long long pcid, int revision, int levelId, int accumulateGradeScore, int minimumLevelScore, int maximumLevelScore, int maximumGradeScore)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hqiiiiii", 96, pcid, revision, levelId, accumulateGradeScore, minimumLevelScore, maximumLevelScore, maximumGradeScore))
        Send(&p);
}

// 0x841a0
void GamedChannel::SendDepositGameMileageOk(unsigned long long tid, char locationHint, char depositType, unsigned long long requestId, unsigned long long externalKey, unsigned long long pcid, id128 const& userId, unsigned long long receiptId, short virtualCurrencyId, long long virtualCurrencyAmount, int errorInfo)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hqQQqqqoqhqi", 101, tid, static_cast<int>(locationHint), static_cast<int>(depositType), requestId, externalKey, pcid, userId, receiptId, static_cast<int>(virtualCurrencyId), virtualCurrencyAmount, errorInfo))
        Send(&p);
}

// 0x84310
void GamedChannel::SendDepositGameMileageFail(unsigned long long tid, char locationHint, char depositType, unsigned long long requestId, unsigned long long externalKey, unsigned long long pcid, id128 const& userId, short failReason, int errorInfo)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hqQQqqqoEi", 102, tid, static_cast<int>(locationHint), static_cast<int>(depositType), requestId, externalKey, pcid, userId, static_cast<int>(failReason), errorInfo))
        Send(&p);
}

// 0x84460
void GamedChannel::SendAuctionBidOk(unsigned long long pcId, id128& auctionId)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 == p.Compose("hqo", 90, pcId, auctionId))
        Log::Write(Log::LT_ERROR, GAMED_FILE, 986,
                   L"[gamed], send auction bid ok fail; compose fail, pcid:0x%I64X, %08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
                   pcId, auctionId.guid.id1, auctionId.guid.id2, auctionId.guid.id3, auctionId.guid.id4[0], auctionId.guid.id4[1], auctionId.guid.id4[2], auctionId.guid.id4[3], auctionId.guid.id4[4], auctionId.guid.id4[5], auctionId.guid.id4[6], auctionId.guid.id4[7]);
    else
        Send(&p);
}

// 0x845f0
void GamedChannel::SendAuctionBidFail(unsigned long long pcId, id128& auctionId, short reason)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 == p.Compose("hqoE", 91, pcId, auctionId, static_cast<int>(reason)))
        Log::Write(Log::LT_ERROR, GAMED_FILE, 1000,
                   L"[gamed], send auction bid fail fail; compose fail, pcid:0x%I64X, %08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, reason:%d",
                   pcId, auctionId.guid.id1, auctionId.guid.id2, auctionId.guid.id3, auctionId.guid.id4[0], auctionId.guid.id4[1], auctionId.guid.id4[2], auctionId.guid.id4[3], auctionId.guid.id4[4], auctionId.guid.id4[5], auctionId.guid.id4[6], auctionId.guid.id4[7], static_cast<int>(reason));
    else
        Send(&p);
}

// 0x84790
void GamedChannel::SendTakeAccountTimeBasedPlayRewardFail(unsigned long long tid, unsigned long long pcid, int schedule, char targetType, short playTime, long long requestTime, short failReason, int errorInfo)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 == p.Compose("hqqiQhqEi", 106, tid, pcid, schedule, static_cast<int>(targetType), static_cast<int>(playTime), requestTime, static_cast<int>(failReason), errorInfo))
        Log::Write(Log::LT_ERROR, GAMED_FILE, 1015,
                   L"[gamed], send take account time based play reward fail fail; compose fail, pcid:%#I64x, reason:%d, error:%d",
                   pcid, static_cast<int>(failReason), errorInfo);
    else
        Send(&p);
}

// 0x848f0
void GamedChannel::SendUpdateAccountExpOk(unsigned long long tid, unsigned long long pcid)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hqq", 108, tid, pcid))
        Send(&p);
}

// 0x849c0
void GamedChannel::SendUpdateAccountExpFail(unsigned long long tid, unsigned long long pcid, short reason)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hqqE", 109, tid, pcid, static_cast<int>(reason)))
        Send(&p);
}

// 0x84aa0
void GamedChannel::SendUpdateAccountContentQuotaOk(unsigned long long tid, unsigned long long pcid)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hqq", 111, tid, pcid))
        Send(&p);
}

// 0x84b70
void GamedChannel::SendUpdateAccountContentQuotaFail(unsigned long long tid, unsigned long long pcid, short reason)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hqqE", 112, tid, pcid, static_cast<int>(reason)))
        Send(&p);
}

// 0x84c50
void GamedChannel::SendUpdateAccountRecycleTimeOk(unsigned long long tid, unsigned long long pcid)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hqq", 114, tid, pcid))
        Send(&p);
}

// 0x84d20
void GamedChannel::SendUpdateAccountRecycleTimeFail(unsigned long long tid, unsigned long long pcid, short reason)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 != p.Compose("hqqE", 115, tid, pcid, static_cast<int>(reason)))
        Send(&p);
}
