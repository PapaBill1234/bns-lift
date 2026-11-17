// SharedChannel.obj (SmartCouponDaemon PDB). Layouts from include/pdb/SmartCouponDaemon/types.h and IDA.
#pragma once
#include <stddef.h>
#include "RefCntObject.h"
#include "Channel.h"

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

    Channel* _rawChannel;
};
static_assert(sizeof(SharedChannel::RawChannel) == 0x38, "sizeof SharedChannel::RawChannel");
static_assert(sizeof(SharedChannel) == 0x20, "sizeof SharedChannel");
static_assert(offsetof(SharedChannel, _rawChannel) == 0x18, "SharedChannel::_rawChannel");
