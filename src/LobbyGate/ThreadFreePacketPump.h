// ThreadFreePacketPump.obj (LobbyGate PDB). Layouts from include/pdb/LobbyGate/types.h.
#pragma once
#include <stddef.h>
#include "TimerQueue.h"
#include "Packet.h"

class Session;
class FragmentPacketConcatenater;

typedef bool (*TFPP_PacketHandler)(Session const* session, Packet const* packet);  // ❓ typedef name

extern unsigned long long GPacketPumpEventKey;

class ThreadFreePacketPumpEvent : public DynamicEventObject
{
public:
    // ❓ Not in the PDB as a separate value. Values from __pump_packet 0x1980.
    enum
    {
        TYPE_PACKET = 0,
        TYPE_FRAGMENT_PACKET = 1,
    };

    // ❓ The constructor is inlined (__pump_packet 0x1980, __pump_fragment_packet 0x1bc0).
    ThreadFreePacketPumpEvent(unsigned int eventId, int type);

    virtual bool initialize(Session const* session, void* handler);  // 0x1440, slot 6
    virtual ~ThreadFreePacketPumpEvent();                             // 0x13f0
    virtual unsigned int EventId() const;                             // 0x1380

    unsigned int _eventId;
    int _type;
    unsigned long long _key;
    Session const* _session;
    void* _handler;
};
static_assert(sizeof(ThreadFreePacketPumpEvent) == 0x38, "sizeof ThreadFreePacketPumpEvent");
static_assert(offsetof(ThreadFreePacketPumpEvent, _eventId) == 0x18, "ThreadFreePacketPumpEvent::_eventId");
static_assert(offsetof(ThreadFreePacketPumpEvent, _key) == 0x20, "ThreadFreePacketPumpEvent::_key");
static_assert(offsetof(ThreadFreePacketPumpEvent, _handler) == 0x30, "ThreadFreePacketPumpEvent::_handler");

class ThreadFreePacketPump : public ThreadFreePacketPumpEvent
{
public:
    // ❓ The constructor is inlined (__pump_packet 0x1980).
    explicit ThreadFreePacketPump(unsigned int eventId)
        : ThreadFreePacketPumpEvent(eventId, TYPE_PACKET), _packet(nullptr) {}
    virtual ~ThreadFreePacketPump();                                                    // 0x1530
    virtual bool HandleEvent(EventContext* context, unsigned long param);               // 0x1680
    bool Initialize(Session const* session, Packet const* packet, TFPP_PacketHandler handler);  // 0x15b0

    Packet const* _packet;
};
static_assert(sizeof(ThreadFreePacketPump) == 0x40, "sizeof ThreadFreePacketPump");

class ThreadFreeFragmentPacketPump : public ThreadFreePacketPumpEvent
{
public:
    // ❓ The constructor is inlined (__pump_fragment_packet 0x1bc0).
    explicit ThreadFreeFragmentPacketPump(unsigned int eventId)
        : ThreadFreePacketPumpEvent(eventId, TYPE_FRAGMENT_PACKET), _fpc(nullptr) {}
    virtual ~ThreadFreeFragmentPacketPump();                                            // 0x1760
    virtual bool HandleEvent(EventContext* context, unsigned long param);               // 0x18c0
    bool Initialize(Session const* session, FragmentPacketConcatenater* fpc, TFPP_PacketHandler handler);  // 0x17f0

    FragmentPacketConcatenater* _fpc;
};
static_assert(sizeof(ThreadFreeFragmentPacketPump) == 0x40, "sizeof ThreadFreeFragmentPacketPump");

bool __pump_packet(unsigned int eventId, void* iocp, Session const* session, Packet const* packet, int cmd,
                   TFPP_PacketHandler handler);  // 0x1980
bool __pump_fragment_packet(unsigned int eventId, void* iocp, Session const* session, Packet const* packet, int cmd,
                            TFPP_PacketHandler handler);  // 0x1bc0
bool TFPP_PumpPacket(unsigned int eventId, void* iocp, Session const* session, Packet const* packet, int cmd,
                     int offset, TFPP_PacketHandler const* PH, TFPP_PacketHandler const* fragmentPH);  // 0x1fc0
