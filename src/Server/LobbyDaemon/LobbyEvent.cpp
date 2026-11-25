// LobbyEvent.obj (LobbyDaemon PDB, 2019 + PDB).
#include "LobbyEvent.h"
#include "FragmentPacket.h"
#include "LiftStub.h"
#include "NPServiceChannel.h"
#include "Memory.h"
#include "Session.h"
#include "SharedChannel.h"

#pragma comment(linker, "/INCLUDE:??0SharedChannelPacketHandleEvent@@QEAA@PEAVSharedChannel@@PEAVPacket@@P6A_N0PEBV2@@Z@Z")  // LIFT: Keep 0xbb7f0 until its caller is lifted.
#pragma comment(linker, "/INCLUDE:??0SharedChannelFragmentPacketHandleEvent@@QEAA@PEAVSharedChannel@@PEAVFragmentPacketConcatenater@@P6A_N01@Z@Z")  // LIFT: Keep 0xbb950 until its caller is lifted.

// 0xbb7f0
SharedChannelPacketHandleEvent::SharedChannelPacketHandleEvent(
    SharedChannel* channel, Packet* packet, bool (__cdecl* handler)(SharedChannel*, Packet const*))
    : _channel(channel), _packet(packet), _handler(handler)
{
    if (channel != nullptr)
        channel->addReferenceCount(false, L"LobbyEvent.cpp", 25);
}

// 0xbb880
SharedChannelPacketHandleEvent::~SharedChannelPacketHandleEvent()
{
    if (_packet != nullptr)
    {
        Packet* packet = const_cast<Packet*>(_packet);
        packet->~Packet();
        Memory::_Manager[Memory::DYNAMIC]->Free(packet, L"LobbyEvent.cpp", 30);
    }
    if (_channel != nullptr)
        _channel->removeReferenceCount(L"LobbyEvent.cpp", 32);
}

// 0xbb900
bool SharedChannelPacketHandleEvent::HandleEvent(EventContext*, unsigned long)
{
    if (_handler != nullptr && _channel != nullptr && _packet != nullptr)
        _handler(_channel, _packet);
    removeReferenceCount(L"LobbyEvent.cpp", 38);
    return true;
}

// 0xbb950
SharedChannelFragmentPacketHandleEvent::SharedChannelFragmentPacketHandleEvent(
    SharedChannel* channel, FragmentPacketConcatenater* fpc,
    bool (__cdecl* handler)(SharedChannel*, FragmentPacketConcatenater*))
    : _channel(channel), _fpc(fpc), _handler(handler)
{
    if (channel != nullptr)
        channel->addReferenceCount(false, L"LobbyEvent.cpp", 50);
}

// 0xbb9e0
SharedChannelFragmentPacketHandleEvent::~SharedChannelFragmentPacketHandleEvent()
{
    if (_fpc != nullptr)
    {
        _fpc->~FragmentPacketConcatenater();
        Memory::_Manager[Memory::DYNAMIC]->Free(_fpc, L"LobbyEvent.cpp", 55);
    }
    if (_channel != nullptr)
        _channel->removeReferenceCount(L"LobbyEvent.cpp", 57);
}

// 0xbba60
bool SharedChannelFragmentPacketHandleEvent::HandleEvent(EventContext*, unsigned long)
{
    if (_handler != nullptr && _channel != nullptr && _fpc != nullptr)
        _handler(_channel, _fpc);
    removeReferenceCount(L"LobbyEvent.cpp", 63);
    return true;
}

// 0xbbad0
NPLobbyMessageHandleEvent::~NPLobbyMessageHandleEvent()
{
    if (_channel != nullptr)
        _channel->removeReferenceCount(L"LobbyEvent.cpp", 82);
    if (_tran != nullptr)
    {
        _tran->~NPTransaction();
        Memory::_Manager[Memory::DYNAMIC]->Free(_tran, L"LobbyEvent.cpp", 84);
        _tran = nullptr;
    }
}

// 0xbbb60
bool NPLobbyMessageHandleEvent::HandleEvent(EventContext*, unsigned long)
{
    if (_channel != nullptr && _msg != nullptr)
    {
        if (_handler != nullptr)
            _handler(_channel, _msg, _tran);
        if (_msg != nullptr)
            _channel->_sts->ReleaseStsMsg(_msg);
    }
    removeReferenceCount(L"LobbyEvent.cpp", 93);
    return true;
}

// LIFT: card 24 adds this constructor (card 6 module). The null check is safe: the original inlines it in 0x64420 after its own session null check.
// LobbyEvent.cpp line 107 (no LD RVA: the constructor is inlined in PostOfficeSessionHandler::PacketHandler 0x64420)
PacketHandleEvent::PacketHandleEvent(Session const* session, Packet const* packet, void* handler)
    : _session(session), _packet(packet), _handler(handler)
{
    if (session != nullptr)
        const_cast<Session*>(session)->addReferenceCount(false, L"LobbyEvent.cpp", 107);
}

// 0xbbbe0
PacketHandleEvent::~PacketHandleEvent()
{
    if (_packet != nullptr)
    {
        const_cast<Packet*>(_packet)->Clear();
        Memory::_Manager[Memory::DYNAMIC]->Free(const_cast<Packet*>(_packet), L"LobbyEvent.cpp", 112);
    }
    if (_session != nullptr)
        const_cast<Session*>(_session)->removeReferenceCount(L"LobbyEvent.cpp", 114);
}

// 0xbbc60
bool PacketHandleEvent::HandleEvent(EventContext*, unsigned long)
{
    // LIFT: the PDB type of _handler is bool (*)(Session const*, Packet const*). The lift keeps void* (PostOfficeChannel.cpp gives it).
    bool (*const handler)(Session const*, Packet const*) = reinterpret_cast<bool (*)(Session const*, Packet const*)>(_handler);
    if (handler != nullptr && _session != nullptr && _packet != nullptr)
        handler(_session, _packet);
    removeReferenceCount(L"LobbyEvent.cpp", 120);
    return true;
}

// 0xbbcf0
bool StopPlayTimerEvent::HandleEvent(EventContext*, unsigned long)
{
    LIFT_STUB(0xbbcf0);
}
