// CacheGateSessionHandler.obj (CacheGate PDB).
#include "CacheGateSessionHandler.h"

#include <winsock2.h>
#include <windows.h>
#include <wchar.h>

#include "AlertSender.h"
#include "CacheD.h"
#include "CacheGate.h"
#include "ClientManager.h"
#include "Connection.h"
#include "Log.h"
#include "Network.h"
#include "Packet.h"
#include "PacketUtil.h"
#include "Session.h"

static wchar_t const HANDLER_FILE[] = L"CacheGateSessionHandler.cpp";
static wchar_t const HANDLER_HEADER_FILE[] =
    L"e:\\dailybuild02\\cachegate-common-0.0.348\\depot\\branch\\348nc\\program\\server\\economy\\cachegate\\CacheGateSessionHandler.h";
static wchar_t const FRAGMENT_PACKET_FILE[] = L"..\\..\\Packet\\FragmentPacket.cpp";
// The inlined Session::GetChannel uses the Session.cpp path.
static wchar_t const SESSION_FILE[] = L"source\\Session.cpp";

// PDB: OuterWorldDdataHeader (CacheGate type 0x2B25, sizeof 22, same members). The body of the relay packets
// after the command.
#pragma pack(push, 2)
struct OuterWorldDdataHeader
{
    unsigned short fromWid;
    unsigned short toWid;
    unsigned long long tid;
    unsigned short hint;
    unsigned long long reserved;
};
#pragma pack(pop)
static_assert(sizeof(OuterWorldDdataHeader) == 22, "sizeof OuterWorldDdataHeader");

// LIFT: Packet has no constructor. The original sets these fields inline.
static void zeroPacket(Packet* packet)
{
    packet->Splitter = nullptr;
    packet->IsFragmentPacket = false;
    packet->FragmentPacketCmd = 0;
    packet->CurHeader = nullptr;
    packet->ListHead = nullptr;
    packet->ListTail = nullptr;
}

static void setRepeatDecomposer(RepeatPacketDecomposer* rpd, char const* format, int len)  // LIFT: lift helper name, not in any PDB
{
    rpd->format = format;
    rpd->len = len;
    rpd->index = 1;
    rpd->offset = 2;
    rpd->top = -1;
}

// 0x4040
CacheGateSessionHandler::~CacheGateSessionHandler()
{
}

// 0xCD80 (size 3: returns true)
bool CacheGateSessionHandler::OnAccept(Session const* session) const
{
    return true;
}

// 0x40c0
bool CacheGateSessionHandler::OnConnect(Session const* session, bool firstConnected) const
{
    Log::Write(Log::LT_ERROR, HANDLER_HEADER_FILE, 24, L"== CRASH == [cachegate session handler], OnConnect; called ... wrong");
    AlertSender::Write(HANDLER_HEADER_FILE, 24, L"== CRASH == [cachegate session handler], OnConnect; called ... wrong");
    return false;
}

// 0x4100
void CacheGateSessionHandler::OnClose(Session const* session, bool tryReconnect) const
{
    Log::Write(Log::LT_DEBUG, HANDLER_HEADER_FILE, 30, L"[cachegate session handler], on close, portid : %d",
               static_cast<int>(session->_id >> 32));
    CacheGate::_instance->_clientManager->ReleaseSession(session->_id);
}

// 0x4150 (COMDAT folded with CacheDChannel::PacketHandler)
bool CacheGateSessionHandler::PacketHandler(Session const* session, Packet const* packet) const
{
    Daemon::PacketHandler handler =
        CacheGatePacketServerSideHandlerList[static_cast<unsigned short>(packet->CurHeader[1].size)];
    return handler != nullptr && handler(session, packet);
}

// 0x4c00
bool HandleCacheGateHello(Session const* session, Packet const* packet)
{
    RepeatPacketDecomposer rpd;
    setRepeatDecomposer(&rpd, "hhhh", 4);
    unsigned short packetVersion = 0;
    unsigned short economyPacketVersion = 0;
    unsigned short wid = 0;
    if (packet->Decompose(&rpd, 3, &packetVersion, &economyPacketVersion, &wid) == 0)
    {
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 23, L"[cg], Hello Recv, packet decompose fail");
        return false;
    }

    unsigned long ip = session->_connection->_ip;
    if (packetVersion != 4)
    {
        session->Send("hE", 3);  // BUG: 0x4C00 the format has an error code, but no error code is given.
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 31,
                   L"[cg], Hello Recv, Missmatch CurrPacketVersion:%d, RecvPacketVersion:%d, wid:%d, ipAddress:%s",
                   4, packetVersion, wid, Network::GetAddressStringW(ip));
        return false;
    }
    if (economyPacketVersion != 10)
    {
        session->Send("hE", 3, 5);
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 38,
                   L"[cg], Hello Recv, Missmatch EconomyPacketVersion EconomyPacketVersion:%d, RecvPacketVersion:%d, wid:%d, ipAddress:%s",
                   10, economyPacketVersion, wid, Network::GetAddressStringW(ip));
        return false;
    }

    ClientManager* clientManager = CacheGate::_instance->_clientManager;
    Session* current = clientManager->GetSession(wid);
    if (current != nullptr)
    {
        current->Close(false);
        session->Send("hE", 3);  // BUG: 0x4C00 the format has an error code, but no error code is given.
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 63,
                   L"[cg], Hello Recv, Duplicate ServerID:%d, CurrSessionId:0x%.16I64X, NewSessionId:0x%.16I64X",
                   wid, current->_id, session->_id);
        return false;
    }

    if (clientManager->AddSession(wid, session))
    {
        session->Send("h", 2);
        Log::Write(Log::LT_DEBUG, HANDLER_FILE, 68, L"[cg], HelloOK Send, sessionId:0x%.16I64X, wid:%d, ipAddress:%s",
                   session->_id, wid, Network::GetAddressStringW(ip));
        return true;
    }

    current = clientManager->GetSession(wid);
    if (current != nullptr)
        current->Close(false);
    session->Send("hE", 3);  // BUG: 0x4C00 the format has an error code, but no error code is given.
    Log::Write(Log::LT_ERROR, HANDLER_FILE, 52, L"[cg], client add session fail, wid:%d, ipAddress:%s", wid,
               Network::GetAddressStringW(ip));
    return false;
}

// 0x4f20
bool HandleCacheGateHelloOk(Session const* session, Packet const* packet)
{
    unsigned long ip = session->_connection->_ip;
    // Inlined Session::GetChannel.
    Channel* channel = nullptr;
    if (session->_channel != nullptr && !session->_waitForRelease)
    {
        session->_channel->addReferenceCount(SESSION_FILE, 1051);
        channel = session->_channel;
    }
    if (channel == nullptr)
    {
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 88, L"[cg], unknow hello ok, wid:xx, ipAddress:%s",
                   Network::GetAddressStringW(ip));
        return false;
    }

    CacheD* cached = static_cast<CacheD*>(channel);
    if (cached->Verify(session) == 0)
    {
        cached->_lock.Enter();
        cached->_status = 1;
        cached->_lock.Leave();
        Log::Write(Log::LT_DEBUG, HANDLER_FILE, 83, L"[cg], hello ok, cached wid:%d, ipAddress:%s", cached->_id,
                   Network::GetAddressStringW(ip));
        cached->removeReferenceCount(HANDLER_FILE, 84);
    }
    // BUG: 0x4F20 the channel reference is not released when Verify fails.
    return true;
}

// 0x5040
bool HandleCacheGateHelloFail(Session const* session, Packet const* packet)
{
    RepeatPacketDecomposer rpd;
    setRepeatDecomposer(&rpd, "hE", 2);
    short errorCode = 0;
    if (packet->Decompose(&rpd, 1, &errorCode) == 0)
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 102, L"[cg], hellofail recv, packet decompose faile");

    unsigned long ip = session->_connection->_ip;
    // Inlined Session::GetChannel.
    Channel* channel = nullptr;
    if (session->_channel != nullptr && !session->_waitForRelease)
    {
        session->_channel->addReferenceCount(SESSION_FILE, 1051);
        channel = session->_channel;
    }
    if (channel != nullptr)
    {
        CacheD* cached = static_cast<CacheD*>(channel);
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 107, L"[cg], hellofail recv, ipAddress:%s, wid:%d, error-reason:%d",
                   Network::GetAddressStringW(ip), cached->_id, errorCode);
        cached->removeReferenceCount(HANDLER_FILE, 108);
    }
    else
    {
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 111, L"[cg], hellofail recv, ipAddress:%s, unknowWid, error-reason:%d",
                   Network::GetAddressStringW(ip), errorCode);
    }
    return false;
}

// 0x51c0
bool HandleCacheGateRelay(Session const* session, Packet const* packet)
{
    bool isClient = (session->_id >> 32) == 1;
    RepeatPacketDecomposer rpd;
    setRepeatDecomposer(&rpd, "hhhqhq", 6);
    OuterWorldDdataHeader recv;
    if (packet->Decompose(&rpd, 5, &recv.fromWid, &recv.toWid, &recv.tid, &recv.hint, &recv.reserved) == 0)
    {
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 129, L"[cg], relay recv, packet decompose fail");
        return false;
    }

    unsigned short recvSize = static_cast<unsigned short>(packet->CurHeader->size - 2);
    CacheD* cached = nullptr;
    Session const* target = nullptr;
    if (isClient)
    {
        Log::Write(Log::LT_DEBUG, HANDLER_FILE, 138,
                   L"[cg], relay recv, client(wid:%d) -> cached(wid:%d), tid:0x%.16I64X, recvDataSize:%d",
                   recv.fromWid, recv.toWid, recv.tid, recvSize);
        cached = CacheGate::_instance->_cachedList.Find(recv.toWid);
        if (cached != nullptr && cached->_status == 1)
            target = cached->GetSession();
    }
    else
    {
        Log::Write(Log::LT_DEBUG, HANDLER_FILE, 148,
                   L"[cg], relay recv, client(wid:%d) <- cached(wid:%d), tid:0x%.16I64X, recvDataSize:%d",
                   recv.toWid, recv.fromWid, recv.tid, recvSize);
        target = CacheGate::_instance->_clientManager->GetSession(recv.toWid);
    }

    Packet p;
    zeroPacket(&p);
    p.Allocate();
    OuterWorldDdataHeader owdh;
    owdh.tid = recv.tid;
    owdh.hint = recv.hint;
    owdh.reserved = recv.reserved;
    if (target != nullptr)
    {
        owdh.fromWid = recv.fromWid;
        owdh.toWid = recv.toWid;
        short cmd = 4;
        p.Add(&cmd, sizeof(cmd));
        p.Add(&owdh, sizeof(owdh));
        p.Add(reinterpret_cast<char const*>(packet->CurHeader) + 26, static_cast<short>(packet->CurHeader->size - 26));
        target->Send(&p);
        unsigned short sendSize = static_cast<unsigned short>(p.CurHeader->size - 2);
        if (isClient)
        {
            Log::Write(Log::LT_DEBUG, HANDLER_FILE, 171,
                       L"[cg], relay send, client(wid:%d) -> cached(wid:%d), tid:0x%.16I64X, sendDataSize:%d",
                       recv.fromWid, recv.toWid, recv.tid, sendSize);
            const_cast<Session*>(target)->removeReferenceCount(HANDLER_FILE, 172);
        }
        else
        {
            Log::Write(Log::LT_DEBUG, HANDLER_FILE, 175,
                       L"[cg], relay send, client(wid:%d) <- cached(wid:%d), tid:0x%.16I64X, sendDataSize:%d",
                       recv.toWid, recv.fromWid, recv.tid, sendSize);
        }
    }
    else
    {
        unsigned short wid = static_cast<unsigned short>(CacheGate::_instance->_config->_wid);
        owdh.fromWid = wid;
        owdh.toWid = recv.fromWid;
        short cmd = 5;
        short reason = cached != nullptr ? 3 : 8;
        p.Add(&cmd, sizeof(cmd));
        p.Add(&owdh, sizeof(owdh));
        p.Add(&reason, sizeof(reason));
        session->Send(&p);
        if (isClient)
            Log::Write(Log::LT_ERROR, HANDLER_FILE, 193,
                       L"[cg], relay fail, cachegate(wid:%d) -> client(wid:%d), tid:0x%.16I64X, reason:%d", wid,
                       recv.fromWid, recv.tid, reason);
        else
            Log::Write(Log::LT_ERROR, HANDLER_FILE, 196,
                       L"[cg], relay fail, cachegate(wid:%d) -> cached(wid:%d), tid:0x%.16I64X, reason:%d", wid,
                       recv.fromWid, recv.tid, reason);
    }
    if (isClient && cached != nullptr)
        cached->removeReferenceCount(HANDLER_FILE, 200);
    return true;
}

// 0x57a0
bool HandleCacheGateRelayFail(Session const* session, Packet const* packet)
{
    RepeatPacketDecomposer rpd;
    setRepeatDecomposer(&rpd, "hhhqhqE", 7);
    unsigned short fromWid;  // The original does not set these values.
    unsigned short toWid;
    unsigned long long tid;
    unsigned short hint;
    unsigned long long reserved;
    packet->Decompose(&rpd, 5, &fromWid, &toWid, &tid, &hint, &reserved);
    Log::Write(Log::LT_ERROR, HANDLER_FILE, 216, L"[cg], invalid packet, relayfail, from(wid:%d) -> to(wid:%d), tid:0x%.16I64X",
               fromWid, toWid, tid);
    return false;
}

// 0x5880
bool HandleCacheGateFragmentRelay(Session const* session, Packet const* packet)
{
    bool isClient = (session->_id >> 32) == 1;
    PacketConcatenater* concatenater = session->_concatenater;
    if (concatenater == nullptr)
    {
        SendFragmentPacketConcatenater local;
        concatenater = session->SetPacketConcatenater(&local);
    }
    SendFragmentPacketConcatenater* sfc = static_cast<SendFragmentPacketConcatenater*>(concatenater);

    // Inlined SendFragmentPacketConcatenater concatenate check.
    int remain = *reinterpret_cast<int const*>(reinterpret_cast<char const*>(packet->CurHeader) + 4);
    bool fail = false;
    int failLine = 0;
    if (remain > 0)
    {
        if (sfc->_packet.CurHeader != nullptr)
        {
            fail = true;
            failLine = 352;
        }
    }
    else if (sfc->_packet.CurHeader == nullptr)
    {
        fail = true;
        failLine = 364;
    }
    if (fail)
    {
        Log::Write(Log::LT_ERROR, FRAGMENT_PACKET_FILE, failLine, L"[fragment packet], Send Fragment Packet conacatnating failed");
        concatenater->Clear();
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 250, L"[cg], fragment relay recv, concatenate fail");
        concatenater->Clear();
        return false;
    }

    bool last = remain > 0 ? (static_cast<unsigned short>(packet->CurHeader->size - 2) - 6 == remain) : (remain == 0);
    sfc->_packet.Concatenate(packet, nullptr);  // LIFT: LTCG folded concatHandler. The call (0x59A6) sets no r8. 0x7300 writes r8 before it reads it.
    if (!last)
        return true;

    PacketDecomposer pd;
    pd.format = "hihhqhq";
    pd.len = 7;
    pd.index = 2;
    pd.offset = 6;
    OuterWorldDdataHeader recv;
    if (sfc->_packet.Decompose(&pd, 5, &recv.fromWid, &recv.toWid, &recv.tid, &recv.hint, &recv.reserved) == 0)
    {
        Log::Write(Log::LT_ERROR, HANDLER_FILE, 268, L"[cg], fragment relay recv, packet decompose fail");
        concatenater->Clear();
        return false;
    }

    CacheD* cached = nullptr;
    Session const* target = nullptr;
    if (isClient)
    {
        Log::Write(Log::LT_DEBUG, HANDLER_FILE, 277,
                   L"[cg], fragment relay recv, client(wid:%d) -> cached(wid:%d), tid:0x%.16I64X, recvDataSize:fragment",
                   recv.fromWid, recv.toWid, recv.tid);
        cached = CacheGate::_instance->_cachedList.Find(recv.toWid);
        if (cached != nullptr && cached->_status == 1)
            target = cached->GetSession();
    }
    else
    {
        Log::Write(Log::LT_DEBUG, HANDLER_FILE, 287,
                   L"[cg], fragment relay recv, client(wid:%d) <- cached(wid:%d), tid:0x%.16I64X, recvDataSize:fragment",
                   recv.toWid, recv.fromWid, recv.tid);
        target = CacheGate::_instance->_clientManager->GetSession(recv.toWid);
    }

    if (target != nullptr)
    {
        target->Send(&sfc->_packet);
        if (!isClient)
        {
            Log::Write(Log::LT_DEBUG, HANDLER_FILE, 299,
                       L"[cg], fragment relay send, client(wid:%d) <- cached(wid:%d), tid:0x%.16I64X, sendDataSize:fragment",
                       recv.toWid, recv.fromWid, recv.tid);
            concatenater->Clear();
            return true;
        }
        Log::Write(Log::LT_DEBUG, HANDLER_FILE, 295,
                   L"[cg], fragment relay send, client(wid:%d) -> cached(wid:%d), tid:0x%.16I64X, sendDataSize:fragment",
                   recv.fromWid, recv.toWid, recv.tid);
        const_cast<Session*>(target)->removeReferenceCount(HANDLER_FILE, 296);
    }
    else
    {
        Packet failPacket;
        zeroPacket(&failPacket);
        failPacket.Allocate();
        unsigned short wid = static_cast<unsigned short>(CacheGate::_instance->_config->_wid);
        OuterWorldDdataHeader owdh;
        owdh.fromWid = wid;
        owdh.toWid = recv.fromWid;
        owdh.tid = recv.tid;
        owdh.hint = recv.hint;
        owdh.reserved = recv.reserved;
        short cmd = 5;
        short reason = cached != nullptr ? 3 : 8;
        failPacket.Add(&cmd, sizeof(cmd));
        failPacket.Add(&owdh, sizeof(owdh));
        failPacket.Add(&reason, sizeof(reason));
        session->Send(&failPacket);
        if (isClient)
            Log::Write(Log::LT_ERROR, HANDLER_FILE, 325,
                       L"[cg], fragment relay fail, cachegate(wid:%d) -> client(wid:%d), tid:0x%.16I64X, reason:%d", wid,
                       recv.fromWid, recv.tid, reason);
        else
            Log::Write(Log::LT_ERROR, HANDLER_FILE, 328,
                       L"[cg], fragment relay fail, cachegate(wid:%d) -> cached(wid:%d), tid:0x%.16I64X, reason:%d", wid,
                       recv.fromWid, recv.tid, reason);
    }
    if (isClient && cached != nullptr)
        cached->removeReferenceCount(HANDLER_FILE, 332);
    concatenater->Clear();
    return true;
}
