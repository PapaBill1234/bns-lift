// LobbyEvent.obj (LobbyDaemon PDB, 2019 + PDB).
// LIFT: Classes with only stub bodies do not have full PDB layouts yet.
#pragma once
#include "TimerQueue.h"

struct EventContext;
class FragmentPacketConcatenater;
class Packet;
class SharedChannel;

class NPLobbyMessageHandleEvent
{
public:
    virtual ~NPLobbyMessageHandleEvent();  // 0xbbad0
    virtual bool HandleEvent(EventContext*, unsigned long);  // 0xbbb60
};

class PacketHandleEvent
{
public:
    virtual ~PacketHandleEvent();  // 0xbbbe0
    virtual bool HandleEvent(EventContext*, unsigned long);  // 0xbbc60
};

class SharedChannelFragmentPacketHandleEvent : public DynamicEventObject
{
public:
    SharedChannelFragmentPacketHandleEvent(SharedChannel*, FragmentPacketConcatenater*, bool (__cdecl*)(SharedChannel*, FragmentPacketConcatenater*));  // 0xbb950
    virtual ~SharedChannelFragmentPacketHandleEvent();  // 0xbb9e0
    virtual unsigned int EventId() const { return 0; }  // 0x5a0a0 (folded)
    virtual bool HandleEvent(EventContext*, unsigned long);  // 0xbba60

private:
    SharedChannel* _channel;
    FragmentPacketConcatenater* _fpc;
    bool (__cdecl* _handler)(SharedChannel*, FragmentPacketConcatenater*);
};
static_assert(sizeof(SharedChannelFragmentPacketHandleEvent) == 0x30, "sizeof SharedChannelFragmentPacketHandleEvent");

class SharedChannelPacketHandleEvent : public DynamicEventObject
{
public:
    SharedChannelPacketHandleEvent(SharedChannel*, Packet*, bool (__cdecl*)(SharedChannel*, Packet const*));  // 0xbb7f0
    virtual ~SharedChannelPacketHandleEvent();  // 0xbb880
    virtual unsigned int EventId() const { return 0; }  // 0x5a0a0 (folded)
    virtual bool HandleEvent(EventContext*, unsigned long);  // 0xbb900

private:
    SharedChannel* _channel;
    Packet const* _packet;
    bool (__cdecl* _handler)(SharedChannel*, Packet const*);
};
static_assert(sizeof(SharedChannelPacketHandleEvent) == 0x30, "sizeof SharedChannelPacketHandleEvent");

class StopPlayTimerEvent
{
public:
    virtual bool HandleEvent(EventContext*, unsigned long);  // 0xbbcf0
};
