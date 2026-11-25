// LobbyEvent.obj (LobbyDaemon PDB, 2019 + PDB).
// LIFT: Layouts from tools/pdbcls.py LobbyDaemon <Class>.
#pragma once
#include <stddef.h>
#include "TimerQueue.h"

struct EventContext;
class FragmentPacketConcatenater;
class NPChannel;
class NPTransaction;
class Packet;
class Session;
class SharedChannel;
namespace StsMsgLib
{
struct _StsMsg;
}

// PDB NPLobbyMessageHandleEvent (sizeof 0x38, DynamicEventObject base).
class NPLobbyMessageHandleEvent : public DynamicEventObject
{
public:
    virtual ~NPLobbyMessageHandleEvent();  // 0xbbad0
    virtual unsigned int EventId() const { return 0; }  // 0x5a0a0 (folded)
    virtual bool HandleEvent(EventContext*, unsigned long);  // 0xbbb60

    NPChannel* _channel;
    StsMsgLib::_StsMsg* _msg;
    NPTransaction* _tran;
    bool (*_handler)(NPChannel*, StsMsgLib::_StsMsg*, NPTransaction*);
};
static_assert(sizeof(NPLobbyMessageHandleEvent) == 0x38, "sizeof NPLobbyMessageHandleEvent");
static_assert(offsetof(NPLobbyMessageHandleEvent, _channel) == 0x18, "NPLobbyMessageHandleEvent::_channel");
static_assert(offsetof(NPLobbyMessageHandleEvent, _handler) == 0x30, "NPLobbyMessageHandleEvent::_handler");

class PacketHandleEvent : public DynamicEventObject
{
public:
    // LIFT: The constructor is inlined (PostOfficeSessionHandler::PacketHandler 0x64420). Layout: include/pdb/LobbyDaemon/types.h.
    PacketHandleEvent(Session const*, Packet const*, void*);
    virtual ~PacketHandleEvent();  // 0xbbbe0
    virtual unsigned int EventId() const { return 0; }  // 0x5a0a0 (folded)
    virtual bool HandleEvent(EventContext*, unsigned long);  // 0xbbc60

    Session const* _session;
    Packet const* _packet;
    void* _handler;
};
static_assert(sizeof(PacketHandleEvent) == 0x30, "sizeof PacketHandleEvent");

class SharedChannelFragmentPacketHandleEvent : public DynamicEventObject
{
public:
    SharedChannelFragmentPacketHandleEvent(SharedChannel*, FragmentPacketConcatenater*, bool (__cdecl*)(SharedChannel*, FragmentPacketConcatenater*));  // 0xbb950
    virtual ~SharedChannelFragmentPacketHandleEvent();  // 0xbb9e0
    virtual unsigned int EventId() const { return 0; }  // 0x5a0a0 (folded)
    virtual bool HandleEvent(EventContext*, unsigned long);  // 0xbba60

private:
    SharedChannelFragmentPacketHandleEvent(SharedChannelFragmentPacketHandleEvent const&);
    SharedChannelFragmentPacketHandleEvent& operator=(SharedChannelFragmentPacketHandleEvent const&);

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
    SharedChannelPacketHandleEvent(SharedChannelPacketHandleEvent const&);
    SharedChannelPacketHandleEvent& operator=(SharedChannelPacketHandleEvent const&);

    SharedChannel* _channel;
    Packet const* _packet;
    bool (__cdecl* _handler)(SharedChannel*, Packet const*);
};
static_assert(sizeof(SharedChannelPacketHandleEvent) == 0x30, "sizeof SharedChannelPacketHandleEvent");

// PDB StopPlayTimerEvent (sizeof 0x48, Timer base).
class StopPlayTimerEvent : public Timer
{
public:
    // LIFT: the PDB ctor StopPlayTimerEvent(unsigned long long, int) has no out-of-line body.
    StopPlayTimerEvent(unsigned long long clikey, int kickReason) : _clikey(clikey), _kickReason(kickReason) {}
    virtual unsigned int TimerClass() const { return 0; }  // 0x5a0a0 (folded)
    virtual unsigned long long TimerId() const { return 0; }  // 0x5a0a0 (folded)
    virtual bool HandleEvent(EventContext*, unsigned long);  // 0xbbcf0

    unsigned long long _clikey;
    int _kickReason;
};
static_assert(sizeof(StopPlayTimerEvent) == 0x48, "sizeof StopPlayTimerEvent");
static_assert(offsetof(StopPlayTimerEvent, _clikey) == 0x38, "StopPlayTimerEvent::_clikey");
