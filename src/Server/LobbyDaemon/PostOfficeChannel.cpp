// PostOfficeChannel.obj (LobbyDaemon PDB, 2019 + PDB). Source: ~/.cache/bns-lift/hr/LobbyDaemon/PostOfficeChannel.c
#include "PlacementNew.h"
#include <winsock2.h>
#include <windows.h>
#include <new>
#include <string.h>
#include <wchar.h>
#include "PostOfficeChannel.h"
#include "AlertSender.h"
#include "Connection.h"
#include "Daemon.h"
#include "FragmentPacket.h"
#include "LobbyConfig.h"
#include "LobbyDaemon.h"
#include "LobbyEvent.h"
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "Network.h"
#include "Packet.h"
#include "PacketUtil.h"
#include "PipeConsole.h"
#include "Session.h"
#include "StringUtil.h"
#if defined(__clang__)
#include "crt_cpp_overload.h"
#endif

#pragma comment(linker, "/INCLUDE:?SendRegisterPostReq@PostOfficeChannel@@QEAA_NPEAVTransaction@TransactionChannel@@_KDD1AEBTid128@@AEBUPostOfficeSenderInfo@@AEBUPostOfficeRecipientInfo@@PEA_W5PEBUPostOfficeAttachedItemInfo@@H@Z")  // LIFT: keep until the caller is lifted (0x63cb0)
#pragma comment(linker, "/INCLUDE:?Connect@PostOfficeChannel@@UEAA_N_KIKGJ_N@Z")  // LIFT: keep until the caller is lifted (0x639f0)
#pragma comment(linker, "/INCLUDE:?OnAccept@PostOfficeSessionHandler@@UEBA_NPEBVSession@@@Z")  // LIFT: keep until the caller is lifted (0x64170)
#pragma comment(linker, "/INCLUDE:?OnConnect@PostOfficeSessionHandler@@UEBA_NPEBVSession@@_N@Z")  // LIFT: keep until the caller is lifted (0x641d0)
#pragma comment(linker, "/INCLUDE:?OnClose@PostOfficeSessionHandler@@UEBAXPEBVSession@@_N@Z")  // LIFT: keep until the caller is lifted (0x642e0)
#pragma comment(linker, "/INCLUDE:?PacketHandler@PostOfficeSessionHandler@@UEBA_NPEBVSession@@PEBVPacket@@@Z")  // LIFT: keep until the caller is lifted (0x64420)

// PDB global (bool (*[7])(Session const*, Packet const*)). The handler table owner is PostOfficeClientSideHandlerList (0x32b50), not this module.
extern Daemon::PacketHandler PostOfficePacketClientSideHandlerList[7];

namespace
{
// LIFT: No PDB symbol. The binary uses the literal as the file string of the log calls (first use at 0x639f0).
wchar_t const* const POST_OFFICE_FILE = L"PostOfficeChannel.cpp";
// LIFT: No PDB symbol. The binary uses the literal as the file string of the Session reference count calls (lines 1051, 1059).
wchar_t const* const SESSION_FILE = L"source\\Session.cpp";

// LIFT: Inlined PipeConsole::SetInvalidInfo(key, true) in 0x639f0 and 0x642e0. The compare is an inline wcscmp.
// PipeConsole::addNode is private, thus PostOfficeChannel and PostOfficeSessionHandler are friends of PipeConsole.
// addNode (0x15ED0 in CacheGate) does not read the value argument. The binary passes a literal L"" (valueString).
#define POST_OFFICE_SET_INVALID_INFO(console, key)                                    \
    do                                                                                \
    {                                                                                 \
        CriticalSection* const lockPtr = &(console)->_lock;                           \
        lockPtr->Enter();                                                             \
        PipeConsole::ItemNode* node = (console)->_invalid._head._next;                \
        PipeConsole::ItemList* const invalidList = &(console)->_invalid;              \
        while (node != &invalidList->_tail)                                           \
        {                                                                             \
            if (wcscmp(node->_key, (key)) == 0)                                       \
                break;                                                                \
            node = node->_next;                                                       \
        }                                                                             \
        if (node == &invalidList->_tail || node == nullptr)                           \
            PipeConsole::addNode(*invalidList, (key), L"");                           \
        lockPtr->Leave();                                                             \
    } while (0)

// LIFT: Inlined Session::GetChannel with the reference (source\Session.cpp 1051) in 0x641d0 and 0x642e0.
Channel* acquireChannel(Session const* session)
{
    Channel* channel = session->_channel;
    if (channel == nullptr || session->_waitForRelease)
        return nullptr;
    channel->addReferenceCount(false, SESSION_FILE, 1051);
    return session->_channel;
}
}  // namespace

// 0x639f0
bool PostOfficeChannel::Connect(unsigned long long id, unsigned int portId, unsigned long ip, unsigned short portNo,
                                long timeout, bool reconnect)
{
    swprintf_s(_daemonInvalidInfoKey, L"[post-office], post-office disconnected %I64d(%s:%d)", id,
               Network::GetAddressStringW(ip), static_cast<int>(portNo));
    PipeConsole* pipeConsole = LobbyDaemon::_instance->pipeConsole;
    if (pipeConsole != nullptr)
        POST_OFFICE_SET_INVALID_INFO(pipeConsole, _daemonInvalidInfoKey);

    if (_handler != nullptr)
        _handler->_connectLock.Enter();
    bool connected = SharedChannel::Connect(id, portId, ip, portNo, timeout, reconnect);
    if (_handler != nullptr)
        _handler->_connectLock.Leave();

    if (connected)
    {
        Log::Write(Log::LT_DEBUG, POST_OFFICE_FILE, 34, L"[post-office], try connect success");
        return connected;
    }
    Log::Write(Log::LT_ERROR, POST_OFFICE_FILE, 36, L"[post-office], try connect fail");
    return false;
}

// 0x63ba0
bool PostOfficeChannel::SendHelloReq()
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    // LIFT: the third argument and the last argument are 64-bit zero stores in the binary (0x63c1b, 0x63c2c).
    if (0 == p.Compose("hhhhhQ", 1, 15, 0LL, 10, static_cast<int>(static_cast<short>(LobbyDaemon::_instance->_config->_worldId)), 0LL))
    {
        Log::Write(Log::LT_ERROR, POST_OFFICE_FILE, 54, L"[post-office], send hello req fail; compose fail");
        return false;
    }
    return Send(&p);
}

// 0x63cb0
bool PostOfficeChannel::SendRegisterPostReq(TransactionChannel::Transaction* t, unsigned long long invoiceId,
                                            char postType, char deliveryReason, unsigned long long postHint,
                                            id128 const& reservedHint, PostOfficeSenderInfo const& senderInfo,
                                            PostOfficeRecipientInfo const& recipientInfo, wchar_t* postTitle,
                                            wchar_t* postMessage, PostOfficeAttachedItemInfo const* itemInfoList,
                                            int itemInfoCount)
{
    if (t == nullptr || (itemInfoCount > 0 && itemInfoList == nullptr))
    {
        Log::Write(Log::LT_ERROR, POST_OFFICE_FILE, 70,
                   L"[post-office], send register post req fail; invalid param, invoice-id:0x%I64X", invoiceId);
        return false;
    }

    FragmentPacket fp(4, "hiqqQcqoQhqosshqsssCQQqihqs;");
    fp.packet.Allocate(&fp.composer);
    if (fp.Compose(17, t->GetTid(), invoiceId, static_cast<int>(deliveryReason), static_cast<int>(postType), postHint,
                   reservedHint, static_cast<int>(senderInfo.serviceType), static_cast<int>(senderInfo.wid),
                   senderInfo.pcid, senderInfo.accountId, senderInfo.worldName, senderInfo.name,
                   static_cast<int>(recipientInfo.wid), recipientInfo.pcid, recipientInfo.name, postTitle,
                   postMessage) == 0)
    {
        Log::Write(Log::LT_ERROR, POST_OFFICE_FILE, 83,
                   L"[post-office], send register post req fail; compose fail, invoice-id:0x%I64X", invoiceId);
        return false;
    }

    if (fp.packet.CurHeader == nullptr || static_cast<unsigned short>(4000 - fp.packet.CurHeader->size) < 2u)
        fp.packet.Allocate(&fp.composer);
    fp.composer.PushRepeatCount(&fp.packet);

    int index = 0;
    long long position = 0;
    if (itemInfoCount > 0)
    {
        PostOfficeAttachedItemInfo const* item = itemInfoList;
        while (true)
        {
            if (fp.packet.CurHeader == nullptr || static_cast<unsigned short>(4000 - fp.packet.CurHeader->size) < 0x18u)
                fp.packet.Allocate(&fp.composer);
            if (fp.Compose(6, static_cast<unsigned int>(item->itemType), static_cast<unsigned int>(item->category),
                           item->instanceId, item->dataId, static_cast<int>(item->level), item->amount) == 0)
            {
                Log::Write(Log::LT_ERROR, POST_OFFICE_FILE, 106,
                           L"[post-office], send register post req fail; compose item fail, index:%d, invoice-id:0x%I64X",
                           index, invoiceId);
                return false;
            }

            // LIFT: the original needs wcslen + 2 free bytes (repne scasw count, then inc at 0x63fb4).
            unsigned long long xmlSize = wcslen(item->itemXmlData) + 2;
            unsigned short freeSize = fp.packet.CurHeader != nullptr ? static_cast<unsigned short>(4000 - fp.packet.CurHeader->size) : 0;
            if (freeSize < xmlSize)
                fp.packet.Allocate(&fp.composer);
            if (fp.Compose(1, item->itemXmlData) == 0)
            {
                Log::Write(Log::LT_ERROR, POST_OFFICE_FILE, 117,
                           L"[post-office], send register post req fail; compose item xml data fail, index:%d, invoice-id:0x%I64X",
                           index, invoiceId);
                return false;
            }

            fp.composer.IncRepeatCount();
            ++index;
            ++position;
            ++item;
            if (position >= itemInfoCount)
                break;
        }
    }

    fp.composer.PopRepeatCount();
    if (fp.packet.Splitter != nullptr)
        fp.packet.Splitter->Finalize(fp.packet.CurHeader);
    return TSend(t, &fp.packet);
}

// 0x64170
bool PostOfficeSessionHandler::OnAccept(Session const* session) const
{
    unsigned long long id = session != nullptr ? session->_id : 0;
    Connection* connection = session->_connection;
    int portNumber = connection->_portNumber;
    Log::Write(Log::LT_ERROR, POST_OFFICE_FILE, 145,
               L"[post-office], accept N/A, session-id:0x%I64X, ip-address:%s, port:%d", id,
               Network::GetAddressStringW(connection->_ip), portNumber);
    return false;
}

// 0x641d0
bool PostOfficeSessionHandler::OnConnect(Session const* session, bool) const
{
    CriticalSection& connectLock = const_cast<CriticalSection&>(_connectLock);
    connectLock.Enter();
    Channel* channel = acquireChannel(session);
    connectLock.Leave();

    bool result;
    PostOfficeChannel* postOffice =
        channel != nullptr ? static_cast<PostOfficeChannel*>(static_cast<SharedChannel::RawChannel*>(channel)->_owner) : nullptr;
    if (channel != nullptr && postOffice != nullptr)
    {
        Log::Write(Log::LT_DEBUG, POST_OFFICE_FILE, 160, L"[post-office], connected, session-id:0x%016I64X", session->_id);
        result = postOffice->SendHelloReq();
        PipeConsole* pipeConsole = LobbyDaemon::_instance->pipeConsole;
        if (pipeConsole != nullptr)
            pipeConsole->SetInvalidInfo(postOffice->_daemonInvalidInfoKey, false);
    }
    else
    {
        Log::Write(Log::LT_ERROR, POST_OFFICE_FILE, 168, L"[post-office], connected; empty channel, session-id:0x%016I64X",
                   session->_id);
        result = false;
    }

    if (channel != nullptr)
        channel->removeReferenceCount(SESSION_FILE, 1059);
    return result;
}

// 0x642e0
void PostOfficeSessionHandler::OnClose(Session const* session, bool) const
{
    Channel* channel = acquireChannel(session);
    PostOfficeChannel* postOffice =
        channel != nullptr ? static_cast<PostOfficeChannel*>(static_cast<SharedChannel::RawChannel*>(channel)->_owner) : nullptr;
    if (postOffice != nullptr)
    {
        PipeConsole* pipeConsole = LobbyDaemon::_instance->pipeConsole;
        if (pipeConsole != nullptr)
            POST_OFFICE_SET_INVALID_INFO(pipeConsole, postOffice->_daemonInvalidInfoKey);
    }
    if (channel != nullptr)
        channel->removeReferenceCount(SESSION_FILE, 1059);
    Log::Write(Log::LT_ERROR, POST_OFFICE_FILE, 192, L"[post-office], closed, session-id:0x%016I64X", session->_id);
}

// 0x64420
bool PostOfficeSessionHandler::PacketHandler(Session const* session, Packet const* packet) const
{
    void* iocpHandle = nullptr;
    if (session == nullptr || packet == nullptr)
    {
        Log::Write(Log::LT_ERROR, POST_OFFICE_FILE, 201,
                   L"== CRASH == [post-office], handle packet failed; invalid parameter");
        AlertSender::Write(POST_OFFICE_FILE, 201, L"== CRASH == [post-office], handle packet failed; invalid parameter");
        return false;
    }

    Packet::Header const* header = packet->CurHeader;
    unsigned short bodySize = static_cast<unsigned short>(header->size - 2);
    if (bodySize < 2u)
    {
        Log::Write(Log::LT_ERROR, POST_OFFICE_FILE, 207,
                   L"[post-office], handle packet failed; invalid packet size, size:%d, session-id:0x%I64X",
                   static_cast<int>(bodySize), session->_id);
        return false;
    }

    short const* const pCmd = &header[1].size;
    if (pCmd == nullptr || static_cast<unsigned short>(*pCmd - 1) > 5u)
    {
        Log::Write(Log::LT_ERROR, POST_OFFICE_FILE, 216,
                   L"[post-office], handle packet failed; invalid packet command, cmd:%d, session-id:0x%I64X",
                   static_cast<int>(*pCmd), session->_id);
        return false;
    }

    Daemon::PacketHandler handler = PostOfficePacketClientSideHandlerList[*pCmd];
    if (handler == nullptr)
    {
        Log::Write(Log::LT_ERROR, POST_OFFICE_FILE, 222,
                   L"[post-office], handle packet failed; handler not exists, cmd:%d, session-id:0x%I64X",
                   static_cast<int>(*pCmd), session->_id);
        return false;
    }

    if (*pCmd == 2 || *pCmd == 3)
    {
        Log::Write(Log::LT_DEBUG, POST_OFFICE_FILE, 231, L"[post-office], handle begin, cmd:%d, session-id:0x%I64X",
                   static_cast<int>(*pCmd), session->_id);
        bool result = handler(session, packet);
        Log::Write(Log::LT_DEBUG, POST_OFFICE_FILE, 233, L"[post-office], handle end, cmd:%d, session-id:0x%I64X",
                   static_cast<int>(*pCmd), session->_id);
        return result;
    }

    // The packet copy goes to the IOCP queue. The event handler runs the table handler on a worker thread.
    void* mem = Memory::_Manager[2]->Alloc(sizeof(Packet), POST_OFFICE_FILE, 237);
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
    // BUG: 0x64420 copy is not checked for nullptr before Allocate/Add when the alloc fails.
    copy->Allocate();
    copy->Add(&packet->CurHeader[1], static_cast<short>(packet->CurHeader->size - 2));

    void* eventMem = Memory::_Manager[2]->Alloc(sizeof(PacketHandleEvent), POST_OFFICE_FILE, 240);
    PacketHandleEvent* event = eventMem != nullptr ? ::new (eventMem) PacketHandleEvent(session, copy, reinterpret_cast<void*>(handler)) : nullptr;
    iocpHandle = Network::iocpHandle();
    PostQueuedCompletionStatus(iocpHandle, 0, reinterpret_cast<ULONG_PTR>(event), nullptr);
    return true;
}
