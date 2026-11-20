// LobbyEvent.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once

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

class SharedChannelFragmentPacketHandleEvent
{
public:
    SharedChannelFragmentPacketHandleEvent(SharedChannel*, FragmentPacketConcatenater*, bool (__cdecl*)(SharedChannel*, FragmentPacketConcatenater*));  // 0xbb950
    virtual ~SharedChannelFragmentPacketHandleEvent();  // 0xbb9e0
    virtual bool HandleEvent(EventContext*, unsigned long);  // 0xbba60
};

class SharedChannelPacketHandleEvent
{
public:
    SharedChannelPacketHandleEvent(SharedChannel*, Packet*, bool (__cdecl*)(SharedChannel*, Packet const*));  // 0xbb7f0
    virtual ~SharedChannelPacketHandleEvent();  // 0xbb880
    virtual bool HandleEvent(EventContext*, unsigned long);  // 0xbb900
};

class StopPlayTimerEvent
{
public:
    virtual bool HandleEvent(EventContext*, unsigned long);  // 0xbbcf0
};
