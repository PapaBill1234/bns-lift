// InfoGateChannel.obj (LobbyDaemon PDB, 2019 + PDB). Lifted: 0x2e6d0 to 0x2f300.
#include "PlacementNew.h"
#include <winsock2.h>
#include <windows.h>
#include <new>
#include "InfoGateChannel.h"
#include "LobbyInfoGatePacketHandler.h"
#include "AlertSender.h"
#include "Connection.h"
#include "Daemon.h"
#include "FragmentPacket.h"
#include "LobbyDaemon.h"
#include "LobbyEvent.h"
#include "Log.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "Network.h"
#include "Packet.h"
#include "Session.h"
#include "StringUtil.h"

namespace
{
// LIFT: No PDB symbol. The binary uses the literal as the file string of the log and reference count calls (first use at 0x2e6d0).
wchar_t const* const INFOGATE_FILE = L"InfoGateChannel.cpp";
// LIFT: No PDB symbol. The binary uses the literal as the file string of SharedChannelList::Acquire/Remove errors (lines 200 and 234).
wchar_t const* const SHARED_CHANNEL_FILE = L"..\\Shared\\SharedChannel.cpp";
// LIFT: No PDB symbol. The binary uses the literal as the file string of the Session reference count calls (lines 1051 and 1059).
wchar_t const* const SESSION_FILE = L"source\\Session.cpp";
// LIFT: No PDB symbol. The binary uses the literal as the file string of the Session release in InfoGateChannelManager::Broadcast (0x2ef40, line 52).
wchar_t const* const CHANNEL_H_FILE =
    L"E:\\DailyBuild02\\LobbyDaemon-Common-0.0.348\\depot\\Branch\\348NC\\Program\\Server\\BloodLib\\include\\Channel.h";
}

#pragma comment(linker, "/INCLUDE:??1InfoGateChannelManager@@UEAA@XZ")  // LIFT: keep until the caller is lifted (0x2ea70)
#pragma comment(linker, "/INCLUDE:?Add@InfoGateChannelManager@@QEAA_NPEAVInfoGateChannel@@@Z")  // LIFT: keep until the caller is lifted (0x2eb50)
#pragma comment(linker, "/INCLUDE:?Remove@InfoGateChannelManager@@QEAAXF@Z")  // LIFT: keep until the caller is lifted (0x2ec10)
#pragma comment(linker, "/INCLUDE:?Acquire@InfoGateChannelManager@@QEAAPEAVInfoGateChannel@@F@Z")  // LIFT: keep until the caller is lifted (0x2ed20)
#pragma comment(linker, "/INCLUDE:?BroadcastBoastEventInWorldNotify@InfoGateChannelManager@@QEAAXFPEB_WF@Z")  // LIFT: keep until the caller is lifted (0x2edf0)
#pragma comment(linker, "/INCLUDE:?Broadcast@InfoGateChannelManager@@QEAA_NPEBVPacket@@@Z")  // LIFT: keep until the caller is lifted (0x2ef40)
#pragma comment(linker, "/INCLUDE:?OnAccept@InfoGateChannelManager@@UEBA_NPEBVSession@@@Z")  // LIFT: keep until the caller is lifted (0x2f040)
#pragma comment(linker, "/INCLUDE:?OnConnect@InfoGateChannelManager@@UEBA_NPEBVSession@@_N@Z")  // LIFT: keep until the caller is lifted (0x2f0b0)
#pragma comment(linker, "/INCLUDE:?OnClose@InfoGateChannelManager@@UEBAXPEBVSession@@_N@Z")  // LIFT: keep until the caller is lifted (0x2f170)

// 0x2e6d0
void InfoGateChannel::SendAuthTokenOk(unsigned long long tid, unsigned long long clikey, id128 const& infoGateToken)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 == p.Compose("hqqo", 5, tid, clikey, infoGateToken))
        Log::Write(Log::LT_ERROR, INFOGATE_FILE, 29,
                   L"[infogate], send auth token ok fail; compose fail, tid:0x%I64X, cli-key:0x%I64X, infogate-token:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
                   tid, clikey, infoGateToken.guid.id1, infoGateToken.guid.id2, infoGateToken.guid.id3, infoGateToken.guid.id4[0], infoGateToken.guid.id4[1], infoGateToken.guid.id4[2], infoGateToken.guid.id4[3], infoGateToken.guid.id4[4], infoGateToken.guid.id4[5], infoGateToken.guid.id4[6], infoGateToken.guid.id4[7]);
    else
        Send(&p);
}

// 0x2e870
void InfoGateChannel::SendAuthTokenFail(unsigned long long tid, unsigned long long clikey, short reason)
{
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 == p.Compose("hqqE", 6, tid, clikey, static_cast<int>(reason)))
        Log::Write(Log::LT_ERROR, INFOGATE_FILE, 42,
                   L"[infogate], send auth token fail fail; compose fail, tid:0x%I64X, cli-key:0x%I64X, reason:%d",
                   tid, clikey, static_cast<int>(reason));
    else
        Send(&p);
}

// 0x2e980
void InfoGateChannel::SendGetWorldInfoListFail(short reason)
{
    // LIFT: the original composes the constant 2 for both the packet and the log (reason is not used).
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 == p.Compose("hh", 9, 2))
        Log::Write(Log::LT_ERROR, INFOGATE_FILE, 62,
                   L"[infogate], send auth token fail fail; compose fail, reason:%d", 2);
    else
        Send(&p);
}

// 0x2ea70
InfoGateChannelManager::~InfoGateChannelManager()
{
    // LIFT: 0x2ea70 loop at InfoGateChannel.cpp:81 releases each channel. The explicit list destructor call is
    // inlined (SharedChannel.cpp:190). The member destructors run it a second time (original sequence).
    SharedChannel** channels = _channels._channels;
    for (SharedChannel** i = channels + _channels._idsize; channels != i; ++channels)
    {
        if (*channels != nullptr)
            (*channels)->removeReferenceCount(INFOGATE_FILE, 81);
    }
    _channels.~SharedChannelList();
}

// 0x2eb50
bool InfoGateChannelManager::Add(InfoGateChannel* channel)
{
    if (channel != nullptr && channel->_rawChannel != nullptr &&
        static_cast<unsigned short>(channel->_rawChannel->GetId()) != 0)
    {
        bool result = false;
        _lock.Enter();
        if (_channels.Set(channel))
        {
            channel->addReferenceCount(false, INFOGATE_FILE, 104);
            result = true;
        }
        _lock.Leave();
        return result;
    }
    Log::Write(Log::LT_ERROR, INFOGATE_FILE, 98, L"[infogate], add fail; invalid parameter");
    return false;
}

// 0x2ec10
void InfoGateChannelManager::Remove(short wid)
{
    if (wid == 0)
    {
        Log::Write(Log::LT_ERROR, INFOGATE_FILE, 114, L"[infogate], remove fail; invalid wid");
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
            channel->removeReferenceCount(INFOGATE_FILE, 122);
        }
    }
    _lock.Leave();
}

// 0x2ed20
InfoGateChannel* InfoGateChannelManager::Acquire(short wid)
{
    if (wid == 0)
    {
        Log::Write(Log::LT_ERROR, INFOGATE_FILE, 130, L"[infogate], acquire fail; invalid wid");
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
            channel->addReferenceCount(false, INFOGATE_FILE, 137);
    }
    _lock.Leave();
    return static_cast<InfoGateChannel*>(channel);
}

// 0x2edf0
void InfoGateChannelManager::BroadcastBoastEventInWorldNotify(short worldClusterId, wchar_t const* pcName, short boastEventDataId)
{
    if (worldClusterId <= 0 || boastEventDataId <= 0)
    {
        Log::Write(Log::LT_ERROR, INFOGATE_FILE, 146,
                   L"[infogate], broadcast boast event in world notify fail; invalid parameter");
        return;
    }
    Packet p;  // LIFT: inlined constructor
    p.CurHeader = nullptr;
    p.Splitter = nullptr;
    p.ListHead = nullptr;
    p.ListTail = nullptr;
    p.IsFragmentPacket = false;
    p.FragmentPacketCmd = 0;
    p.Allocate();
    if (0 == p.Compose("hhsh", 10, static_cast<unsigned int>(worldClusterId), pcName, static_cast<int>(boastEventDataId)))
    {
        Log::Write(Log::LT_ERROR, INFOGATE_FILE, 156,
                   L"[infogate], broadcast boast event in world notify fail; compose fail, world-cluster-id:%d, pc-name:%s, boast-event-dataId:%d",
                   static_cast<int>(worldClusterId), pcName, static_cast<int>(boastEventDataId));
        return;
    }
    if (!Broadcast(&p))
    {
        Log::Write(Log::LT_ERROR, INFOGATE_FILE, 162,
                   L"[infogate], broadcast boast event in world notify fail; broadcast fail");
        return;
    }
}

// 0x2ef40
bool InfoGateChannelManager::Broadcast(Packet const* packet)
{
    _lock.Enter();
    SharedChannel** channels = _channels._channels;
    for (SharedChannel** i = channels + _channels._idsize; channels != i; ++channels)
    {
        SharedChannel* channel = *channels;
        if (channel != nullptr && static_cast<InfoGateChannel*>(channel)->IsBroadcastable() && channel->_rawChannel != nullptr)
        {
            // LIFT: Channel::GetSession returns a counted reference (released below, Channel.h:52).
            Session* session = const_cast<Session*>(channel->_rawChannel->GetSession());
            if (session != nullptr)
            {
                session->_lock.Enter();
                // LIFT: state 5 is the connected state. ❓ No PDB enum name.
                bool ready = session->_state == 5 && session->_connection->_socket != INVALID_SOCKET;
                session->_lock.Leave();
                if (ready)
                {
                    session->Send(packet);
                    session->removeReferenceCount(CHANNEL_H_FILE, 52);
                }
            }
        }
    }
    _lock.Leave();
    return true;
}

// 0x2f040
bool InfoGateChannelManager::OnAccept(Session const* session) const
{
    int portNumber = 0;
    unsigned int ip = 0;
    unsigned long long id = 0;
    if (session != nullptr)
    {
        Connection* connection = session->_connection;
        id = session->_id;
        portNumber = connection->_portNumber;
        ip = connection->_ip;
    }
    Log::Write(Log::LT_DEBUG, INFOGATE_FILE, 202,
               L"[infogate], session accepted, session-id:0x%I64X, ip-address:%s, port:%d", id,
               Network::GetAddressStringW(ip), portNumber);
    return true;
}

// 0x2f0b0
bool InfoGateChannelManager::OnConnect(Session const* session, bool) const
{
    int portNumber = 0;
    unsigned int ip = 0;
    unsigned long long id = 0;
    if (session != nullptr)
    {
        Connection* connection = session->_connection;
        id = session->_id;
        portNumber = connection->_portNumber;
        ip = connection->_ip;
    }
    Log::Write(Log::LT_ERROR, INFOGATE_FILE, 208,
               L"== CRASH == [infogate], session connected; forbidden, session-id:0x%I64X, ip-address:%s, port:%d", id,
               Network::GetAddressStringW(ip), portNumber);
    portNumber = 0;
    ip = 0;
    id = 0;
    if (session != nullptr)
    {
        Connection* connection = session->_connection;
        id = session->_id;
        portNumber = connection->_portNumber;
        ip = connection->_ip;
    }
    AlertSender::Write(INFOGATE_FILE, 208,
                       L"== CRASH == [infogate], session connected; forbidden, session-id:0x%I64X, ip-address:%s, port:%d",
                       id, Network::GetAddressStringW(ip), portNumber);
    return false;
}

// 0x2f170
void InfoGateChannelManager::OnClose(Session const* session, bool) const
{
    Channel* channel = session->GetChannel();
    if (channel != nullptr)
    {
        SharedChannel* shared = static_cast<SharedChannel::RawChannel*>(channel)->_owner;
        if (shared != nullptr)
        {
            short wid = 0;
            Log::Write(Log::LT_ERROR, INFOGATE_FILE, 222, L"[infogate], infogate channel closed, gate-wid:%d",
                       shared->_rawChannel != nullptr ? static_cast<int>(static_cast<short>(shared->_rawChannel->GetId())) : 0);
            if (shared->_rawChannel != nullptr)
            {
                shared->_rawChannel->GetId();
                if (shared->_rawChannel != nullptr)
                    wid = static_cast<short>(shared->_rawChannel->GetId());
            }
            const_cast<InfoGateChannelManager*>(this)->Remove(wid);
        }
        else
        {
            Log::Write(Log::LT_ERROR, INFOGATE_FILE, 227,
                       L"== CRASH == [infogate], infogate channel closed exception; raw-channel has no shared-channel, channel-id:%I64d",
                       channel->GetId());
            AlertSender::Write(INFOGATE_FILE, 227,
                               L"== CRASH == [infogate], infogate channel closed exception; raw-channel has no shared-channel, channel-id:%I64d",
                               channel->GetId());
        }
        channel->removeReferenceCount(SESSION_FILE, 1059);
    }
    Connection* connection = session->_connection;
    unsigned long long id = session->_id;
    int portNumber = connection->_portNumber;
    Log::Write(Log::LT_ERROR, INFOGATE_FILE, 235,
               L"[infogate], session closed, session-id:0x%I64X, ip-address:%s, port:%d", id,
               Network::GetAddressStringW(connection->_ip), portNumber);
}

// 0x2f300
bool InfoGateChannelManager::PacketHandler(Session const* session, Packet const* packet) const
{
    if (session == nullptr || packet == nullptr)
    {
        Log::Write(Log::LT_ERROR, INFOGATE_FILE, 244,
                   L"== CRASH == [infogate], handle packet failed; invalid parameter");
        AlertSender::Write(INFOGATE_FILE, 244,
                           L"== CRASH == [infogate], handle packet failed; invalid parameter");
        return false;
    }

    Packet::Header const* header = packet->CurHeader;
    unsigned short bodySize = static_cast<unsigned short>(header->size - 2);
    if (bodySize < 2u)
    {
        Connection* connection = session->_connection;
        unsigned long long id = session->_id;
        int portNumber = connection->_portNumber;
        Log::Write(Log::LT_ERROR, INFOGATE_FILE, 250,
                   L"[infogate], handle packet failed; invalid packet size, size:%d, session-id:0x%I64X, ip-address:%s, port:%d",
                   static_cast<int>(bodySize), id, Network::GetAddressStringW(connection->_ip), portNumber);
        return false;
    }

    short cmd = header[1].size;
    if (static_cast<unsigned short>(cmd - 1) > 9u)
    {
        Connection* connection = session->_connection;
        unsigned long long id = session->_id;
        int portNumber = connection->_portNumber;
        Log::Write(Log::LT_ERROR, INFOGATE_FILE, 258,
                   L"[infogate], handle packet failed; invalid packet command, cmd:%d, session-id:0x%I64X, ip-address:%s, port:%d",
                   static_cast<int>(cmd), id, Network::GetAddressStringW(connection->_ip), portNumber);
        return false;
    }

    LobbyInfoGatePacketHandlerDef const* def = &LobbyInfoGatePacketLobbySideHandlerList[cmd];
    if (def->handler == nullptr)
    {
        Connection* connection = session->_connection;
        unsigned long long id = session->_id;
        int portNumber = connection->_portNumber;
        Log::Write(Log::LT_ERROR, INFOGATE_FILE, 265,
                   L"[infogate], handle packet failed; handler not exists, cmd:%d, session-id:0x%I64X, ip-address:%s, port:%d",
                   static_cast<int>(cmd), id, Network::GetAddressStringW(connection->_ip), portNumber);
        return false;
    }

    bool result = false;
    Channel* channel = session->GetChannel();
    void* iocp = nullptr;
    SharedChannel* shared = channel != nullptr ? static_cast<SharedChannel::RawChannel*>(channel)->_owner : nullptr;
    if (cmd == 1)
    {
        {
            Connection* connection = session->_connection;
            unsigned long long id = session->_id;
            int portNumber = connection->_portNumber;
            Log::Write(Log::LT_DEBUG, INFOGATE_FILE, 276,
                       L"[infogate], handle begin, cmd:%d, session-id:0x%I64X, ip-address:%s, port:%d", 1, id,
                       Network::GetAddressStringW(connection->_ip), portNumber);
        }
        result = reinterpret_cast<Daemon::PacketHandler>(def->handler)(session, packet);
        {
            Connection* connection = session->_connection;
            unsigned long long id = session->_id;
            int portNumber = connection->_portNumber;
            Log::Write(Log::LT_DEBUG, INFOGATE_FILE, 278,
                       L"[infogate], handle end, cmd:%d, session-id:0x%I64X, ip-address:%s, port:%d", 1, id,
                       Network::GetAddressStringW(connection->_ip), portNumber);
        }
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
                void* mem = Memory::_Manager[2]->Alloc(sizeof(FragmentPacketConcatenater), INFOGATE_FILE, 290);
                FragmentPacketConcatenater* fpc = mem != nullptr ? ::new (mem) FragmentPacketConcatenater : nullptr;
                // BUG: 0x2f300 fpc is not checked for nullptr before Copy when the alloc fails.
                if (fpc->Copy(concatenater))
                {
                    void* eventMem = Memory::_Manager[2]->Alloc(sizeof(SharedChannelFragmentPacketHandleEvent), INFOGATE_FILE, 292);
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
                    Log::Write(Log::LT_ERROR, INFOGATE_FILE, 296,
                               L"[infogate], handle packet fail; copy fragment packet concatenater fail, cmd:%d, channel-id:%I64d",
                               static_cast<int>(cmd), iocp);
                    if (fpc != nullptr)
                        fpc->~FragmentPacketConcatenater();  // LIFT: vtable slot 4 with flag 1 runs the destructor only.
                    Memory::_Manager[2]->Free(fpc, INFOGATE_FILE, 297);
                }
                concatenater->Clear();
            }
        }
        else
        {
            void* mem = Memory::_Manager[2]->Alloc(sizeof(Packet), INFOGATE_FILE, 305);
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
            // BUG: 0x2f300 copy is not checked for nullptr before Allocate/Add when the alloc fails.
            copy->Allocate();
            copy->Add(&packet->CurHeader[1], static_cast<short>(packet->CurHeader->size - 2));
            void* eventMem = Memory::_Manager[2]->Alloc(sizeof(SharedChannelPacketHandleEvent), INFOGATE_FILE, 308);
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
