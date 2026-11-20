// SharedChannel.obj (SmartCouponDaemon PDB). Layouts from include/pdb/SmartCouponDaemon/types.h and IDA.
#pragma once
#include <stddef.h>
#include "RefCntObject.h"
#include "Channel.h"

class Packet;
class Session;

class SharedChannel : public DynamicRefCntObj
{
public:
    // The channel that SharedChannel gives to the network layer.
    class RawChannel : public Channel
    {
    public:
        // LIFT: Inlined in SharedChannel::Connect (0x63D0) and SharedChannel::Accept (0x6510).
        RawChannel(unsigned long long id, SharedChannel* owner) : _id(id), _owner(owner)
        {
            _ref = 1;
            _tag = 10;
            _history = nullptr;
        }
        virtual ~RawChannel() {}                       // 0x63A0
        virtual unsigned long long GetId();            // 0x6390

        unsigned long long _id;
        SharedChannel* _owner;
    };

    SharedChannel() : _rawChannel(nullptr) {}  // LIFT: inlined in the callers
    virtual bool Connect(unsigned long long id, unsigned int portId, unsigned long ip, unsigned short portNo,
                         long timeout, bool reconnect);          // 0x63D0 (slot 4)
    virtual bool Accept(unsigned long long id, Session const* session);  // 0x6510 (slot 5)
    virtual void Close();                                        // 0x6690 (slot 6)
    virtual void StopReconnect();                                // 0x6720 (slot 7)
    virtual ~SharedChannel();                                    // 0x4270 (body in SharedChannel.h line 36)

    bool IsConnected();                                          // 0x67B0
    bool Send(char const* format, ...);                          // 0x4B70 (LobbyDaemon)
    bool Send(Packet const* packet);                             // 0x4BA0 (LobbyDaemon)

protected:
    bool sendV(char const* format, char* args);                  // 0x4C50 (LobbyDaemon)

public:

    Channel* _rawChannel;
};
static_assert(sizeof(SharedChannel::RawChannel) == 0x38, "sizeof SharedChannel::RawChannel");
static_assert(sizeof(SharedChannel) == 0x20, "sizeof SharedChannel");
static_assert(offsetof(SharedChannel, _rawChannel) == 0x18, "SharedChannel::_rawChannel");

// Layout from include/pdb/LobbyDaemon/types.h.
class SharedChannelList
{
public:
    ~SharedChannelList();                                                       // 0x4D20 (LobbyDaemon)
    bool Initialize(unsigned long long idmin, unsigned long long idmax);         // 0x4D60 (LobbyDaemon)
    bool Set(SharedChannel* channel);                                           // 0x4E20 (LobbyDaemon)

    SharedChannel** _channels;
    unsigned long long _idmin;
    int _idsize;
    int _size;
};
static_assert(sizeof(SharedChannelList) == 0x18, "sizeof SharedChannelList");
static_assert(offsetof(SharedChannelList, _idmin) == 0x8, "SharedChannelList::_idmin");
static_assert(offsetof(SharedChannelList, _idsize) == 0x10, "SharedChannelList::_idsize");
static_assert(offsetof(SharedChannelList, _size) == 0x14, "SharedChannelList::_size");
