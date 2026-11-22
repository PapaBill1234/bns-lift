// AccountInventoryChannel.obj (LobbyDaemon PDB, 2019 + PDB). Source: ~/.cache/bns-lift/hr/LobbyDaemon/AccountInventoryChannel.c
// 0x64e0 Network::iocpHandle is the inline body in Network.h (COMDAT copy, not a separate definition here).
#include "PlacementNew.h"
#include <winsock2.h>
#include <windows.h>
#include <new>
#include "AccountInventoryChannel.h"
#include "AlertSender.h"
#include "Connection.h"
#include "Daemon.h"
#include "FragmentPacket.h"
#include "LiftStub.h"
#include "LobbyDaemon.h"
#include "LobbyEvent.h"
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "Network.h"
#include "Packet.h"
#include "Session.h"
#include "StringUtil.h"
#if defined(__clang__)
#include "crt_cpp_overload.h"
#endif

#pragma comment(linker, "/INCLUDE:??$swprintf_s@$0IB@@@YAHAEAY0IB@_WPEB_WZZ")  // LIFT: keep 0x8790 until AccountInventoryChannel::Connect (0x6500) is lifted
#pragma comment(linker, "/INCLUDE:?SendHelloReq@AccountInventoryChannel@@QEAA_NFFF@Z")  // LIFT: keep until the caller is lifted (0x66b0)
#pragma comment(linker, "/INCLUDE:?SendLoginNotify@AccountInventoryChannel@@QEAA_NAEBTid128@@@Z")  // LIFT: keep until the caller is lifted (0x67b0)
#pragma comment(linker, "/INCLUDE:?SendLogoutNotify@AccountInventoryChannel@@QEAA_NAEBTid128@@@Z")  // LIFT: keep until the caller is lifted (0x68a0)
#pragma comment(linker, "/INCLUDE:?SendGetGoodsCountReq@AccountInventoryChannel@@QEAA_NPEAVTransaction@TransactionChannel@@AEBTid128@@@Z")  // LIFT: keep until the caller is lifted (0x6990)
#pragma comment(linker, "/INCLUDE:?SendListGoodsReq@AccountInventoryChannel@@QEAA_NPEAVTransaction@TransactionChannel@@AEBTid128@@D@Z")  // LIFT: keep until the caller is lifted (0x6bd0)
#pragma comment(linker, "/INCLUDE:?SendTakeGoodsReq@AccountInventoryChannel@@QEAA_NPEAVTransaction@TransactionChannel@@AEBTid128@@_K@Z")  // LIFT: keep until the caller is lifted (0x6e30)
#pragma comment(linker, "/INCLUDE:?SendRetrieveLobbyServiceItemListReq@AccountInventoryChannel@@QEAA_NPEAVTransaction@TransactionChannel@@AEBTid128@@D_J@Z")  // LIFT: keep until the caller is lifted (0x7090)
#pragma comment(linker, "/INCLUDE:?SendRetrieveSingleWarehouseItemReq@AccountInventoryChannel@@QEAA_NPEAVTransaction@TransactionChannel@@_KAEBTid128@@1@Z")  // LIFT: keep until the caller is lifted (0x72f0)
#pragma comment(linker, "/INCLUDE:?SendTryWarehouseItemConsumptionReq@AccountInventoryChannel@@QEAA_NPEAVTransaction@TransactionChannel@@_K1AEBTid128@@@Z")  // LIFT: keep until the caller is lifted (0x7590)
#pragma comment(linker, "/INCLUDE:?SendFinishWarehouseItemConsumptionReq@AccountInventoryChannel@@QEAA_NPEAVTransaction@TransactionChannel@@_K1AEBTid128@@F@Z")  // LIFT: keep until the caller is lifted (0x7810)
#pragma comment(linker, "/INCLUDE:?SendConsumeWarehouseItemReq@AccountInventoryChannel@@QEAA_NPEAVTransaction@TransactionChannel@@_K1AEBTid128@@@Z")  // LIFT: keep until the caller is lifted (0x7ab0)
#pragma comment(linker, "/INCLUDE:?SendRetrieveCharacterGoodsCountReq@AccountInventoryChannel@@QEAA_NPEAVTransaction@TransactionChannel@@AEBTid128@@_K@Z")  // LIFT: keep until the caller is lifted (0x7d30)
#pragma comment(linker, "/INCLUDE:?OnAccept@AccountInventorySessionHandler@@UEBA_NPEBVSession@@@Z")  // LIFT: keep until the caller is lifted (0x8020)
#pragma comment(linker, "/INCLUDE:?PacketHandler@AccountInventorySessionHandler@@UEBA_NPEBVSession@@PEBVPacket@@@Z")  // LIFT: keep until the caller is lifted (0x82f0)
template int __cdecl swprintf_s<129>(wchar_t (&)[129], wchar_t const*, ...);  // 0x8790 (CRT template instance, VS2010 crt_cpp_overload.h)

namespace
{
wchar_t const* const ACCOUNT_INVENTORY_FILE = L"AccountInventoryChannel.cpp";  // LIFT: No PDB symbol. The binary uses the literal.
wchar_t const* const SESSION_FILE = L"source\\Session.cpp";

}

// PDB AccountInventoryLobbyPacketHandlerDef (sizeof 16).
struct AccountInventoryLobbyPacketHandlerDef
{
    void* handler;
    bool auth;
    bool fragment;
};
static_assert(sizeof(AccountInventoryLobbyPacketHandlerDef) == 0x10, "sizeof AccountInventoryLobbyPacketHandlerDef");

// PDB global (37 entries). No lifted module owns the table yet.
// LIFT: ld-18 defines it with null entries so that LobbyDaemon.exe links. The handler card fills it and then removes this
// definition. ❓ The original entries (handler, auth, fragment) are not read.
AccountInventoryLobbyPacketHandlerDef AccountInventoryLobbyPacketLobbySideHandlerList[37];

// The game-account-id log arguments: id1 id2 id3 id4[0..7] (format %08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X).
// LIFT: lift-only macro. It writes the guid fields as the original call sites do for the %08X-%04X-... log text (0x82f0 and the send functions).
#define ACCOUNT_GUID_ARGS(a)                                                                                        \
    (a).guid.id1, (a).guid.id2, (a).guid.id3, (a).guid.id4[0], (a).guid.id4[1], (a).guid.id4[2], (a).guid.id4[3], \
        (a).guid.id4[4], (a).guid.id4[5], (a).guid.id4[6], (a).guid.id4[7]

// 0x6500
bool AccountInventoryChannel::Connect(unsigned long long, unsigned int, unsigned long, unsigned short, long, bool)
{
    LIFT_STUB(0x6500);
}

// 0x66b0
bool AccountInventoryChannel::SendHelloReq(short version, short wid, short internalPort)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    // LIFT: internalPort is not used in the binary (r9w is never read).
    if (0 == p.Compose("hhhh", 1, 9, static_cast<int>(version), static_cast<int>(wid)))
    {
        Log::Write(Log::LT_ERROR, ACCOUNT_INVENTORY_FILE, 53,
                   L"[account-inventory], send hello req fail; compose fail");
        return false;
    }
    return Send(&p);
}

// 0x67b0
bool AccountInventoryChannel::SendLoginNotify(id128 const& account)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 == p.Compose("ho", 36, account))
    {
        Log::Write(Log::LT_ERROR, ACCOUNT_INVENTORY_FILE, 67,
                   L"[account-inventory], send login notify fail; compose fail");
        return false;
    }
    return Send(&p);
}

// 0x68a0
bool AccountInventoryChannel::SendLogoutNotify(id128 const& account)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 == p.Compose("ho", 35, account))
    {
        Log::Write(Log::LT_ERROR, ACCOUNT_INVENTORY_FILE, 81,
                   L"[account-inventory], send logout notify fail; compose fail");
        return false;
    }
    return Send(&p);
}

// 0x6990
bool AccountInventoryChannel::SendGetGoodsCountReq(TransactionChannel::Transaction* t, id128 const& account)
{
    if (t == nullptr)
    {
        Log::Write(Log::LT_ERROR, ACCOUNT_INVENTORY_FILE, 92,
                   L"[account-inventory], send get-goods-count req fail; invalid param, game-account-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X", ACCOUNT_GUID_ARGS(account));
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
    if (0 == p.Compose("hqo", 4, t->GetTid(), account))
    {
        Log::Write(Log::LT_ERROR, ACCOUNT_INVENTORY_FILE, 101,
                   L"[account-inventory], send get-goods-count req fail; compose fail, game-account-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X", ACCOUNT_GUID_ARGS(account));
        return false;
    }
    return TSend(t, &p);
}

// 0x6bd0
bool AccountInventoryChannel::SendListGoodsReq(TransactionChannel::Transaction* t, id128 const& account, char languageCode)
{
    if (t == nullptr)
    {
        Log::Write(Log::LT_ERROR, ACCOUNT_INVENTORY_FILE, 112,
                   L"[account-inventory], send list-goods req fail; invalid param, game-account-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X", ACCOUNT_GUID_ARGS(account));
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
    if (0 == p.Compose("hqoc", 7, t->GetTid(), account, static_cast<int>(languageCode)))
    {
        Log::Write(Log::LT_ERROR, ACCOUNT_INVENTORY_FILE, 121,
                   L"[account-inventory], send list-goods req fail; compose fail, game-account-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X", ACCOUNT_GUID_ARGS(account));
        return false;
    }
    return TSend(t, &p);
}

// 0x6e30
bool AccountInventoryChannel::SendTakeGoodsReq(TransactionChannel::Transaction* t, id128 const& account, unsigned long long goodsId)
{
    if (t == nullptr)
    {
        Log::Write(Log::LT_ERROR, ACCOUNT_INVENTORY_FILE, 132,
                   L"[account-inventory], send take-goods req fail; invalid param, goods-id:0x%I64X, game-account-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X", goodsId, ACCOUNT_GUID_ARGS(account));
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
    if (0 == p.Compose("hqoq", 10, t->GetTid(), account, goodsId))
    {
        Log::Write(Log::LT_ERROR, ACCOUNT_INVENTORY_FILE, 141,
                   L"[account-inventory], send take-goods req fail; compose fail, goods-id:0x%I64X, game-account-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X", goodsId, ACCOUNT_GUID_ARGS(account));
        return false;
    }
    return TSend(t, &p);
}

// 0x7090
bool AccountInventoryChannel::SendRetrieveLobbyServiceItemListReq(TransactionChannel::Transaction* t, id128 const& account, char searchType, long long searchKey)
{
    if (t == nullptr)
    {
        Log::Write(Log::LT_ERROR, ACCOUNT_INVENTORY_FILE, 152,
                   L"[account-inventory], send retrieve lobby service item list req fail; invalid param, game-account-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X", ACCOUNT_GUID_ARGS(account));
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
    if (0 == p.Compose("hqoQq", 13, t->GetTid(), account, static_cast<int>(searchType), searchKey))
    {
        Log::Write(Log::LT_ERROR, ACCOUNT_INVENTORY_FILE, 161,
                   L"[account-inventory], send retrieve lobby service item list req fail; compose fail, game-account-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X", ACCOUNT_GUID_ARGS(account));
        return false;
    }
    return TSend(t, &p);
}

// 0x72f0
bool AccountInventoryChannel::SendRetrieveSingleWarehouseItemReq(TransactionChannel::Transaction* t, unsigned long long itemInstanceId, id128 const& account, unsigned long long ownerPcId)
{
    if (t == nullptr)
    {
        Log::Write(Log::LT_ERROR, ACCOUNT_INVENTORY_FILE, 171,
                   L"[account-inventory], send retrieve single warehouse item req fail; invalid param, item-instance-id:0x%I64X, game-account-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, pcid:0x%I64X", itemInstanceId, ACCOUNT_GUID_ARGS(account), ownerPcId);
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
    if (0 == p.Compose("hqqoq", 16, t->GetTid(), itemInstanceId, account, ownerPcId))
    {
        Log::Write(Log::LT_ERROR, ACCOUNT_INVENTORY_FILE, 179,
                   L"[account-inventory], send retrieve single warehouse item req fail; compose fail, item-instance-id:0x%I64X, game-account-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, pcid:0x%I64X", itemInstanceId, ACCOUNT_GUID_ARGS(account), ownerPcId);
        return false;
    }
    return TSend(t, &p);
}

// 0x7590
bool AccountInventoryChannel::SendTryWarehouseItemConsumptionReq(TransactionChannel::Transaction* t, unsigned long long labelId, unsigned long long itemInstanceId, id128 const& account)
{
    if (t == nullptr)
    {
        Log::Write(Log::LT_ERROR, ACCOUNT_INVENTORY_FILE, 211,
                   L"[account-inventory], send try warehouse item consumption req fail; invalid param, label-id:0x%I64X, item-instance-id:0x%I64X, game-account-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X", labelId, itemInstanceId, ACCOUNT_GUID_ARGS(account));
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
    if (0 == p.Compose("hqqqo", 19, t->GetTid(), labelId, itemInstanceId, account))
    {
        Log::Write(Log::LT_ERROR, ACCOUNT_INVENTORY_FILE, 224,
                   L"[account-inventory], send try warehouse item consumption req fail; compose fail, label-id:0x%I64X, item-instance-id:0x%I64X, game-account-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X", labelId, itemInstanceId, ACCOUNT_GUID_ARGS(account));
        return false;
    }
    return TSend(t, &p);
}

// 0x7810
bool AccountInventoryChannel::SendFinishWarehouseItemConsumptionReq(TransactionChannel::Transaction* t, unsigned long long labelId, unsigned long long itemInstanceId, id128 const& account, short result)
{
    (void)result;  // LIFT: 0x7810 the PDB signature has this parameter. LTCG folded the constant 0 into the body: the body uses 0.
    if (t == nullptr)
    {
        Log::Write(Log::LT_ERROR, ACCOUNT_INVENTORY_FILE, 237,
                   L"[account-inventory], send finish warehouse item consumption req fail; invalid param, result:%d, label-id:0x%I64X, item-instance-id:0x%I64X, game-account-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X", 0, labelId, itemInstanceId, ACCOUNT_GUID_ARGS(account));
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
    if (0 == p.Compose("hqqqoE", 22, t->GetTid(), labelId, itemInstanceId, account, 0))
    {
        Log::Write(Log::LT_ERROR, ACCOUNT_INVENTORY_FILE, 251,
                   L"[account-inventory], send finish warehouse item consumption req fail; compose fail, result:%d, label-id:0x%I64X, item-instance-id:0x%I64X, game-account-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X", 0, labelId, itemInstanceId, ACCOUNT_GUID_ARGS(account));
        return false;
    }
    return TSend(t, &p);
}

// 0x7ab0
bool AccountInventoryChannel::SendConsumeWarehouseItemReq(TransactionChannel::Transaction* t, unsigned long long labelId, unsigned long long itemInstanceId, id128 const& account)
{
    if (t == nullptr)
    {
        Log::Write(Log::LT_ERROR, ACCOUNT_INVENTORY_FILE, 263,
                   L"[account-inventory], send consume-ware-house-item-req fail; null transaction, label-id:0x%I64X, item-instance-id:0x%I64X, game-account-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X", labelId, itemInstanceId, ACCOUNT_GUID_ARGS(account));
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
    if (0 == p.Compose("hqqqo", 28, t->GetTid(), labelId, itemInstanceId, account))
    {
        Log::Write(Log::LT_ERROR, ACCOUNT_INVENTORY_FILE, 276,
                   L"[account-inventory], send consume-ware-house-item-req fail; compose fail, label-id:0x%I64X, item-instance-id:0x%I64X, game-account-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X", labelId, itemInstanceId, ACCOUNT_GUID_ARGS(account));
        return false;
    }
    return TSend(t, &p);
}

// 0x7d30
bool AccountInventoryChannel::SendRetrieveCharacterGoodsCountReq(TransactionChannel::Transaction* t, id128 const& account, unsigned long long characterId)
{
    if (t == nullptr)
    {
        Log::Write(Log::LT_ERROR, ACCOUNT_INVENTORY_FILE, 286,
                   L"[account-inventory], send retrieve-character-goods-count-req fail; null transaction, game-account-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, pcid:0x%I64X", ACCOUNT_GUID_ARGS(account), characterId);
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
    if (0 == p.Compose("hqoq", 31, t->GetTid(), account, characterId))
    {
        Log::Write(Log::LT_ERROR, ACCOUNT_INVENTORY_FILE, 294,
                   L"[account-inventory], send retrieve-character-goods-count-req fail; compose fail, tid:0x%I64X, game-account-id:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, pcid:0x%I64X", t->GetTid(), ACCOUNT_GUID_ARGS(account), characterId);
        return false;
    }
    return TSend(t, &p);
}

// 0x8020
bool AccountInventorySessionHandler::OnAccept(Session const* session) const
{
    unsigned long long id = session != nullptr ? session->_id : 0;
    Connection* connection = session->_connection;
    int portNumber = connection->_portNumber;
    Log::Write(Log::LT_ERROR, ACCOUNT_INVENTORY_FILE, 315,
               L"[account-inventory], accept N/A, session-id:0x%I64X, ip-address:%s, port:%d", id,
               Network::GetAddressStringW(connection->_ip), portNumber);
    return false;
}

// 0x8080
bool AccountInventorySessionHandler::OnConnect(Session const*, bool) const
{
    LIFT_STUB(0x8080);
}

// 0x81b0
void AccountInventorySessionHandler::OnClose(Session const*, bool) const
{
    LIFT_STUB(0x81b0);
}

// 0x82f0
bool AccountInventorySessionHandler::PacketHandler(Session const* session, Packet const* packet) const
{
    if (session == nullptr || packet == nullptr)
    {
        Log::Write(Log::LT_ERROR, ACCOUNT_INVENTORY_FILE, 371,
                   L"== CRASH == [account-inventory], handle packet failed; invalid parameter");
        AlertSender::Write(ACCOUNT_INVENTORY_FILE, 371,
                           L"== CRASH == [account-inventory], handle packet failed; invalid parameter");
        return false;
    }

    Packet::Header const* header = packet->CurHeader;
    unsigned short bodySize = static_cast<unsigned short>(header->size - 2);
    if (bodySize < 2u)
    {
        Log::Write(Log::LT_ERROR, ACCOUNT_INVENTORY_FILE, 377,
                   L"[account-inventory], handle packet failed; invalid packet size, size:%d, session-id:0x%I64X",
                   static_cast<int>(bodySize), session->_id);
        return false;
    }

    short cmd = header[1].size;
    if (static_cast<unsigned short>(cmd - 1) > 0x23u)
    {
        Log::Write(Log::LT_ERROR, ACCOUNT_INVENTORY_FILE, 385,
                   L"[account-inventory], handle packet failed; invalid packet command, cmd:%d, session-id:0x%I64X",
                   static_cast<int>(cmd), session->_id);
        return false;
    }

    AccountInventoryLobbyPacketHandlerDef const* def = &AccountInventoryLobbyPacketLobbySideHandlerList[cmd];
    if (def->handler == nullptr)
    {
        Log::Write(Log::LT_ERROR, ACCOUNT_INVENTORY_FILE, 392,
                   L"[account-inventory], handle packet failed; handler not exists, cmd:%d, session-id:0x%I64X",
                   static_cast<int>(cmd), session->_id);
        return false;
    }

    bool result = false;
    Channel* channel = session->GetChannel();
    void* iocp = nullptr;
    SharedChannel* shared = channel != nullptr ? static_cast<SharedChannel::RawChannel*>(channel)->_owner : nullptr;
    if (cmd == 2 || cmd == 3)
    {
        Log::Write(Log::LT_DEBUG, ACCOUNT_INVENTORY_FILE, 403,
                   L"[account-inventory], handle begin, cmd:%d, session-id:0x%I64X", static_cast<int>(cmd), session->_id);
        result = reinterpret_cast<Daemon::PacketHandler>(def->handler)(session, packet);
        Log::Write(Log::LT_DEBUG, ACCOUNT_INVENTORY_FILE, 405,
                   L"[account-inventory], handle end, cmd:%d, session-id:0x%I64X", static_cast<int>(cmd), session->_id);
    }
    else if (shared != nullptr && def->auth)
    {
        if (def->fragment)
        {
            bool completed = false;
            ConcatenatePacket(session, packet, completed);
            if (completed)
            {
                FragmentPacketConcatenater* concatenater = static_cast<FragmentPacketConcatenater*>(session->_concatenater);
                void* mem = Memory::_Manager[2]->Alloc(sizeof(FragmentPacketConcatenater), ACCOUNT_INVENTORY_FILE, 416);
                FragmentPacketConcatenater* fpc = mem != nullptr ? ::new (mem) FragmentPacketConcatenater : nullptr;
                // BUG: 0x82f0 fpc is not checked for nullptr before Copy when the alloc fails.
                if (fpc->Copy(concatenater))
                {
                    void* eventMem = Memory::_Manager[2]->Alloc(sizeof(SharedChannelFragmentPacketHandleEvent), ACCOUNT_INVENTORY_FILE, 418);
                    SharedChannelFragmentPacketHandleEvent* event =
                        eventMem != nullptr
                            ? ::new (eventMem) SharedChannelFragmentPacketHandleEvent(
                                  shared, fpc, reinterpret_cast<bool (*)(SharedChannel*, FragmentPacketConcatenater*)>(def->handler))
                            : nullptr;
                    iocp = Network::iocpHandle();
                    PostQueuedCompletionStatus(iocp, 0, reinterpret_cast<ULONG_PTR>(event), nullptr);
                }
                else
                {
                    if (shared->_rawChannel != nullptr)
                        iocp = reinterpret_cast<void*>(shared->_rawChannel->GetId());
                    Log::Write(Log::LT_ERROR, ACCOUNT_INVENTORY_FILE, 422,
                               L"[account-inventory], handle packet fail; copy fragment packet concatenater fail, cmd:%d, channel-id:%I64d",
                               static_cast<int>(cmd), iocp);
                    if (fpc != nullptr)
                        fpc->~FragmentPacketConcatenater();  // LIFT: vtable slot 4 with flag 1 runs the destructor only.
                    Memory::_Manager[2]->Free(fpc, ACCOUNT_INVENTORY_FILE, 423);
                }
                concatenater->Clear();
            }
        }
        else
        {
            void* mem = Memory::_Manager[2]->Alloc(sizeof(Packet), ACCOUNT_INVENTORY_FILE, 430);
            Packet* copy = nullptr;
            if (mem != nullptr)
            {
                copy = static_cast<Packet*>(mem);
                copy->CurHeader = nullptr;
                copy->Splitter = nullptr;
                copy->ListHead = nullptr;
                copy->ListTail = nullptr;
                copy->IsFragmentPacket = false;
                copy->FragmentPacketCmd = 0;
            }
            // BUG: 0x82f0 copy is not checked for nullptr before Allocate/Add when the alloc fails.
            copy->Allocate();
            copy->Add(&packet->CurHeader[1], static_cast<short>(packet->CurHeader->size - 2));
            void* eventMem = Memory::_Manager[2]->Alloc(sizeof(SharedChannelPacketHandleEvent), ACCOUNT_INVENTORY_FILE, 433);
            SharedChannelPacketHandleEvent* event =
                eventMem != nullptr
                    ? ::new (eventMem) SharedChannelPacketHandleEvent(
                          shared, copy, reinterpret_cast<bool (*)(SharedChannel*, Packet const*)>(def->handler))
                    : nullptr;
            iocp = Network::iocpHandle();
            PostQueuedCompletionStatus(iocp, 0, reinterpret_cast<ULONG_PTR>(event), nullptr);
        }
        result = true;
    }

    if (channel != nullptr)
        channel->removeReferenceCount(SESSION_FILE, 1059);
    return result;
}
