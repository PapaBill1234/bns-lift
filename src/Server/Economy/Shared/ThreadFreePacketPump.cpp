// ThreadFreePacketPump.obj (LobbyGate PDB).
// 0x1000-0x1390 and 0x13a0, 0x1510, 0x1740 are inline RefCntObject / EventObject copies or
// scalar deleting destructors. They are in src/common/ or made by the compiler.
#include <windows.h>
#include <intrin.h>
#include <new>
#include "ThreadFreePacketPump.h"
#include "FragmentPacket.h"
#include "Session.h"
#include "Memory.h"
#include "MemoryManager.h"
#include "Log.h"
#include "AlertSender.h"

// LIFT: The original builds this file in each exe project. LobbyGate uses ..\Economy\Shared, the
// Economy daemons use ..\Shared (ThreadFreePacketPumpShortPath.cpp sets the macro).
#ifndef TFPP_FILE
#define TFPP_FILE L"..\\Economy\\Shared\\ThreadFreePacketPump.cpp"
#endif

unsigned long long GPacketPumpEventKey = 0;

ThreadFreePacketPumpEvent::ThreadFreePacketPumpEvent(unsigned int eventId, Type type, unsigned long long key)
{
    // The members are protected. Check the PDB offsets here.
    static_assert(offsetof(ThreadFreePacketPumpEvent, _eventId) == 0x18, "ThreadFreePacketPumpEvent::_eventId");
    static_assert(offsetof(ThreadFreePacketPumpEvent, _key) == 0x20, "ThreadFreePacketPumpEvent::_key");
    static_assert(offsetof(ThreadFreePacketPumpEvent, _handler) == 0x30, "ThreadFreePacketPumpEvent::_handler");
    _ref = 1;
    _tag = 10;
    _history = nullptr;
    _eventId = eventId;
    _type = type;
    _key = key;
    _session = nullptr;
    _handler = nullptr;
}

// 0x1380
unsigned int ThreadFreePacketPumpEvent::EventId() const
{
    return _eventId;
}

// 0x13f0
ThreadFreePacketPumpEvent::~ThreadFreePacketPumpEvent()
{
    if (_session != nullptr)
        const_cast<Session*>(_session)->removeReferenceCount(TFPP_FILE, 31);
}

// 0x1440
bool ThreadFreePacketPumpEvent::initialize(Session const* session, Daemon::PacketHandler handler)
{
    if (session != nullptr && handler != nullptr)
    {
        _session = session;
        _handler = handler;
        const_cast<Session*>(session)->addReferenceCount(TFPP_FILE, 45);
        return true;
    }
    Log::Write(Log::LT_ERROR, TFPP_FILE, 38,
               L"== CRASH == [packet-pump], 0x%016I64X, invalid parameter, session:0x%p, handler:0x%p",
               session != nullptr ? session->_id : 0ULL, session, reinterpret_cast<void*>(handler));
    AlertSender::Write(TFPP_FILE, 38,
                       L"== CRASH == [packet-pump], 0x%016I64X, invalid parameter, session:0x%p, handler:0x%p",
                       session != nullptr ? session->_id : 0ULL, session, reinterpret_cast<void*>(handler));
    return false;
}

// 0x1530
ThreadFreePacketPump::~ThreadFreePacketPump()
{
    if (_packet != nullptr)
    {
        const_cast<Packet*>(_packet)->Clear();
        Memory::_Manager[2]->Free(const_cast<Packet*>(_packet), TFPP_FILE, 63);
    }
}

// 0x15b0
bool ThreadFreePacketPump::Initialize(Session const* session, Packet const* packet, Daemon::PacketHandler handler)
{
    if (packet == nullptr)
    {
        Log::Write(Log::LT_ERROR, TFPP_FILE, 70,
                   L"== CRASH == [packet-pump], 0x%016I64X, invalid parameter, session:0x%p, packet:0x%p, handler:0x%p",
                   session != nullptr ? session->_id : 0ULL, session, packet, handler);
        AlertSender::Write(TFPP_FILE, 70,
                           L"== CRASH == [packet-pump], 0x%016I64X, invalid parameter, session:0x%p, packet:0x%p, handler:0x%p",
                           session != nullptr ? session->_id : 0ULL, session, packet, handler);
        return false;
    }
    if (!initialize(session, handler))
        return false;
    _packet = packet;
    return true;
}

// 0x1680
bool ThreadFreePacketPump::HandleEvent(EventContext* context, unsigned long param)
{
    int command = _packet->CurHeader[1].size;
    Log::Write(Log::LT_DEBUG, TFPP_FILE, 87, L"[packet-pump], handle start, %I64u, session:0x%016I64X, command:%d",
               _key, _session->_id, command);
    _handler(_session, _packet);
    Log::Write(Log::LT_DEBUG, TFPP_FILE, 93, L"[packet-pump], handle end, %I64u, session:0x%016I64X, command:%d",
               _key, _session->_id, command);
    removeReferenceCount(TFPP_FILE, 96);
    return true;
}

// 0x1760
ThreadFreeFragmentPacketPump::~ThreadFreeFragmentPacketPump()
{
    if (_fpc != nullptr)
    {
        // LIFT: LobbyGate 0x1791 calls vtable slot 4 (0x24f0) with flag 1. 0x24f0 runs the dtor only and does not free.
        _fpc->~FragmentPacketConcatenater();
        Memory::_Manager[2]->Free(_fpc, TFPP_FILE, 114);
    }
}

// 0x17f0
bool ThreadFreeFragmentPacketPump::Initialize(Session const* session, FragmentPacketConcatenater* fpc,
                                              Daemon::PacketHandler handler)
{
    if (fpc == nullptr)
    {
        Log::Write(Log::LT_ERROR, TFPP_FILE, 121,
                   L"== CRASH == [packet-pump], 0x%016I64X, invalid parameter, session:0x%p, fpc:0x%p, handler:0x%p",
                   session != nullptr ? session->_id : 0ULL, session, fpc, handler);
        AlertSender::Write(TFPP_FILE, 121,
                           L"== CRASH == [packet-pump], 0x%016I64X, invalid parameter, session:0x%p, fpc:0x%p, handler:0x%p",
                           session != nullptr ? session->_id : 0ULL, session, fpc, handler);
        return false;
    }
    if (!initialize(session, handler))
        return false;
    _fpc = fpc;
    return true;
}

// 0x18c0
bool ThreadFreeFragmentPacketPump::HandleEvent(EventContext* context, unsigned long param)
{
    int command = _fpc->Command;
    Log::Write(Log::LT_DEBUG, TFPP_FILE, 138, L"[packet-pump], handle start, %I64u, session:0x%016I64X, command:%d",
               _key, _session->_id, command);
    // The handler gets the concatenater as a packet (original cast).
    _handler(_session, reinterpret_cast<Packet const*>(_fpc));
    Log::Write(Log::LT_DEBUG, TFPP_FILE, 144, L"[packet-pump], handle end, %I64u, session:0x%016I64X, command:%d",
               _key, _session->_id, command);
    removeReferenceCount(TFPP_FILE, 147);
    return true;
}

// 0x1980
bool __pump_packet(unsigned int eventId, void* iocp, Session const* session, Packet const* packet, int cmd,
                   Daemon::PacketHandler handler)
{
    Packet* copy = ::new (Memory::_Manager[2]->Alloc(sizeof(Packet), TFPP_FILE, 172)) Packet;
    copy->Splitter = nullptr;
    copy->IsFragmentPacket = false;
    copy->FragmentPacketCmd = 0;
    copy->CurHeader = nullptr;
    copy->ListHead = nullptr;
    copy->ListTail = nullptr;
    copy->Allocate();
    copy->Add(reinterpret_cast<char const*>(packet->CurHeader) + 2, packet->CurHeader->size - 2);

        ThreadFreePacketPump* pump =
        ::new (Memory::_Manager[2]->Alloc(sizeof(ThreadFreePacketPump), TFPP_FILE, 176)) ThreadFreePacketPump(  // line 0xB0 at LobbyGate 0x1a0f
            eventId, _InterlockedIncrement64(reinterpret_cast<long long volatile*>(&GPacketPumpEventKey)));
    if (!pump->Initialize(session, copy, handler))
    {
        Log::Write(Log::LT_ERROR, TFPP_FILE, 179,
                   L"[packet-pump], pump packet fail; init pump fail, event-id:%u, iocp:%I64u, session:0x%016I64X, cmd:%d",
                   eventId, iocp, session->_id, cmd);
        if (copy != nullptr)
        {
            copy->Clear();
            Memory::_Manager[2]->Free(copy, TFPP_FILE, 181);
        }
        // BUG: 0x1980 pump is not checked for nullptr before this call.
        pump->removeReferenceCount(TFPP_FILE, 182);
        return false;
    }
    Log::Write(Log::LT_DEBUG, TFPP_FILE, 187, L"[packet-pump], post, %I64u", pump->GetKey());
    if (PostQueuedCompletionStatus(iocp, 0, reinterpret_cast<ULONG_PTR>(pump), nullptr))
        return true;
    Log::Write(Log::LT_ERROR, TFPP_FILE, 192,
               L"[packet-pump], post packet pump fail; switch to dedicated thread handing, event-id:%u, iocp:%I64u, session:0x%016I64X, cmd:%d",
               eventId, iocp, session->_id, cmd);
    bool result = handler(session, copy);
    pump->removeReferenceCount(TFPP_FILE, 194);
    return result;
}

// 0x1bc0
bool __pump_fragment_packet(unsigned int eventId, void* iocp, Session const* session, Packet const* packet, int cmd,
                            Daemon::PacketHandler handler)
{
    bool completed = false;
    FragmentPacketConcatenater* concatenater = static_cast<FragmentPacketConcatenater*>(session->_concatenater);
    if (concatenater == nullptr)
    {
        FragmentPacketConcatenater c;
        concatenater = static_cast<FragmentPacketConcatenater*>(session->SetPacketConcatenater(&c));
    }

    wchar_t const* format;
    int line;
    if (!concatenater->Add(packet, &completed, cmd != 0))  // LIFT: 0x1cea does not set r9b. Add (0x25d0) writes r9 at 0x25ef before it reads it.
    {
        format = L"[packet-pump], concatenate fragment packet fail, event-id:%u, iocp:%I64u, session:0x%016I64X, cmd:%d";
        line = 217;
        goto fail;
    }
    if (!completed)
        return true;

    {
        // LobbyGate 0x1d4c gives line 0xE0 (224).
        FragmentPacketConcatenater* fpc =
            ::new (Memory::_Manager[2]->Alloc(sizeof(FragmentPacketConcatenater), TFPP_FILE, 224)) FragmentPacketConcatenater;
        if (!fpc->Copy(concatenater))
        {
            // BUG: 0x1bc0 fpc is not freed on this path.
            format = L"[packet-pump], fragment packet concatenater copy fail, event-id:%u, iocp:%I64u, session:0x%016I64X, cmd:%d";
            line = 227;
            goto fail;
        }
        concatenater->Clear();

        ThreadFreeFragmentPacketPump* pump =
            ::new (Memory::_Manager[2]->Alloc(sizeof(ThreadFreeFragmentPacketPump), TFPP_FILE, 233))
                ThreadFreeFragmentPacketPump(
                    eventId, _InterlockedIncrement64(reinterpret_cast<long long volatile*>(&GPacketPumpEventKey)));
        if (!pump->Initialize(session, fpc, handler))
        {
            Log::Write(Log::LT_ERROR, TFPP_FILE, 236,
                       L"[packet-pump], pump fragment packet fail; init pump fail, event-id:%u, iocp:%I64u, session:0x%016I64X, cmd:%d",
                       eventId, iocp, session->_id, cmd);
            if (fpc != nullptr)
            {
                // LIFT: LobbyGate 0x1791 calls vtable slot 4 (0x24f0) with flag 1. 0x24f0 runs the dtor only and does not free.
                fpc->~FragmentPacketConcatenater();
                Memory::_Manager[2]->Free(fpc, TFPP_FILE, 238);
            }
            // BUG: 0x1bc0 pump is not checked for nullptr before this call.
            pump->removeReferenceCount(TFPP_FILE, 239);
            return true;
        }
        Log::Write(Log::LT_DEBUG, TFPP_FILE, 244, L"[packet-pump], post, %I64u", pump->GetKey());
        if (PostQueuedCompletionStatus(iocp, 0, reinterpret_cast<ULONG_PTR>(pump), nullptr))
            return true;
        Log::Write(Log::LT_ERROR, TFPP_FILE, 249,
                   L"[packet-pump], post fragment packet pump fail; switch to dedicated thread handing, event-id:%u, iocp:%I64u, session:0x%016I64X, cmd:%d",
                   eventId, iocp, session->_id, cmd);
        bool result = handler(session, reinterpret_cast<Packet const*>(fpc));
        pump->removeReferenceCount(TFPP_FILE, 251);
        return result;
    }

fail:
    Log::Write(Log::LT_ERROR, TFPP_FILE, line, format, eventId, iocp, session->_id, cmd);
    concatenater->Clear();
    return true;
}

// 0x1fc0
bool TFPP_PumpPacket(unsigned int eventId, void* iocp, Session const* session, Packet const* packet, int cmd,
                     int offset, Daemon::PacketHandler const* PH, Daemon::PacketHandler const* fragmentPH)
{
    if (iocp == INVALID_HANDLE_VALUE || session == nullptr || packet == nullptr || PH == nullptr ||
        fragmentPH == nullptr || cmd - offset < 0)  // LIFT: offset is 0 in the binary (folded)
    {
        Log::Write(Log::LT_ERROR, TFPP_FILE, 262,
                   L"== CRASH == [packet-pump], invalid parameter, event-id:%u, iocp:%I64u, session:0x%p, packet:0x%p, cmd:%d, offset:%d, PH:0x%p, fragmentPH:0x%p",
                   eventId, iocp, session, packet, cmd, offset, PH, fragmentPH);
        AlertSender::Write(TFPP_FILE, 262,
                           L"== CRASH == [packet-pump], invalid parameter, event-id:%u, iocp:%I64u, session:0x%p, packet:0x%p, cmd:%d, offset:%d, PH:0x%p, fragmentPH:0x%p",
                           eventId, iocp, session, packet, cmd, offset, PH, fragmentPH);
        return false;
    }
    if (fragmentPH[cmd - offset] != nullptr)
        return __pump_fragment_packet(eventId, iocp, session, packet, cmd, fragmentPH[cmd - offset]);
    return __pump_packet(eventId, iocp, session, packet, cmd, PH[cmd - offset]);
}
