// ThreadFreePacketPump.obj (LobbyGate PDB). Layouts from include/pdb/LobbyGate/types.h.
#pragma once
#include <stddef.h>
#include "TimerQueue.h"
#include "Packet.h"
#include "Daemon.h"

class Session;
class FragmentPacketConcatenater;


extern unsigned long long GPacketPumpEventKey;

// PDB type 0x20F1 (LobbyGate), size 0x38.
class ThreadFreePacketPumpEvent : public DynamicEventObject
{
public:
    // PDB enum 0x20D8 (LobbyGate).
    enum Type
    {
        TYPE_PACKET = 0,
        TYPE_FRAGMENT_PACKET = 1,
    };

    // PDB constructor, inlined in __pump_packet (0x1980) and __pump_fragment_packet (0x1bc0).
    ThreadFreePacketPumpEvent(unsigned int eventId, Type type, unsigned long long key);

    virtual ~ThreadFreePacketPumpEvent();                             // 0x13f0
    virtual unsigned int EventId() const;                             // 0x1380
    int GetType() const { return _type; }
    unsigned long long GetKey() const { return _key; }

protected:
    virtual bool initialize(Session const* session, Daemon::PacketHandler handler);  // 0x1440, slot 6

    unsigned int _eventId;
    Type _type;
    unsigned long long _key;
    Session const* _session;
    Daemon::PacketHandler _handler;
};
static_assert(sizeof(ThreadFreePacketPumpEvent) == 0x38, "sizeof ThreadFreePacketPumpEvent");

class ThreadFreePacketPump : public ThreadFreePacketPumpEvent
{
public:
    // PDB constructor, inlined in __pump_packet (0x1980).
    ThreadFreePacketPump(unsigned int eventId, unsigned long long key)
        : ThreadFreePacketPumpEvent(eventId, TYPE_PACKET, key), _packet(nullptr) {}
    virtual ~ThreadFreePacketPump();                                                    // 0x1530
    virtual bool HandleEvent(EventContext* context, unsigned long param);               // 0x1680
    bool Initialize(Session const* session, Packet const* packet, Daemon::PacketHandler handler);  // 0x15b0

private:
    Packet const* _packet;
};
static_assert(sizeof(ThreadFreePacketPump) == 0x40, "sizeof ThreadFreePacketPump");

class ThreadFreeFragmentPacketPump : public ThreadFreePacketPumpEvent
{
public:
    // PDB constructor, inlined in __pump_fragment_packet (0x1bc0).
    ThreadFreeFragmentPacketPump(unsigned int eventId, unsigned long long key)
        : ThreadFreePacketPumpEvent(eventId, TYPE_FRAGMENT_PACKET, key), _fpc(nullptr) {}
    virtual ~ThreadFreeFragmentPacketPump();                                            // 0x1760
    virtual bool HandleEvent(EventContext* context, unsigned long param);               // 0x18c0
    bool Initialize(Session const* session, FragmentPacketConcatenater* fpc, Daemon::PacketHandler handler);  // 0x17f0

private:
    FragmentPacketConcatenater* _fpc;
};
static_assert(sizeof(ThreadFreeFragmentPacketPump) == 0x40, "sizeof ThreadFreeFragmentPacketPump");

bool __pump_packet(unsigned int eventId, void* iocp, Session const* session, Packet const* packet, int cmd,
                   Daemon::PacketHandler handler);  // 0x1980
bool __pump_fragment_packet(unsigned int eventId, void* iocp, Session const* session, Packet const* packet, int cmd,
                            Daemon::PacketHandler handler);  // 0x1bc0
bool TFPP_PumpPacket(unsigned int eventId, void* iocp, Session const* session, Packet const* packet, int cmd,
                     int offset, Daemon::PacketHandler const* PH, Daemon::PacketHandler const* fragmentPH);  // 0x1fc0
