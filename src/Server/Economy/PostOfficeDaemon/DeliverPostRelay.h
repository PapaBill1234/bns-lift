// DeliverPostRelay.obj (PostOfficeDaemon PDB). Layouts from include/pdb/PostOfficeDaemon/types.h.
#pragma once
#include <stddef.h>
#include "RelayContext.h"
#include "PingRelay.h"

class PostContext;

// PDB type 0x2C88. The class has no data.
class DeliverPostRelayRequest : public RelayRequest
{
public:
    DeliverPostRelayRequest() {}
    virtual ~DeliverPostRelayRequest() {}
};
static_assert(sizeof(DeliverPostRelayRequest) == 0x8, "sizeof DeliverPostRelayRequest");

// types.h:1937
class DeliverPostRelayResponse : public RelayResponse
{
public:
    // PDB ctor (ResultState, short const) with default arguments. 0x65c0 stores (1, 0).
    DeliverPostRelayResponse(ResultState resultState = RESULTSTATE_SUCCESS, short const failReason = 0)
        : RelayResponse(resultState, failReason) {}
    virtual ~DeliverPostRelayResponse() {}  // slot 0
};
static_assert(sizeof(DeliverPostRelayResponse) == 0x10, "sizeof DeliverPostRelayResponse");

class DeliverPostRelayContext : public RelayContext
{
public:
    DeliverPostRelayContext(EconomyHeader const& economyHeader, DeliverPostRelayRequest const& request,
                            PostContext* const postContext);  // 0xfb80
    virtual ~DeliverPostRelayContext();                                // 0xfc70

    virtual unsigned short const GetRequestWid() const;            // LIFT: folded with 0xfb40 (PingGenerator.cpp)
    virtual RelayHeader const MakeRelayHeader() const;             // 0x10310
    virtual bool ComposeRequestPacket(FragmentPacket&) const;      // 0x10350
    virtual bool ComposeRequestPacket(Packet&) const;              // LIFT: folded with 0x34c40
    virtual bool ComposeResponsePacket(FragmentPacket&) const;     // LIFT: folded with 0x34c40
    virtual bool ComposeResponsePacket(Packet&) const;             // LIFT: folded with 0x34c40
    virtual bool processRelayRequest(Channel* const) const;        // 0xfd00
    virtual bool processRelayResponse() const;                     // 0xfe00
    virtual bool processRelayTimeout();                            // 0x102c0
    virtual void initResponse(RelayResponse* const);               // 0xfb50

    DeliverPostRelayRequest _request;
    DeliverPostRelayResponse _response;
    PostContext* _postContext;
};
static_assert(sizeof(DeliverPostRelayContext) == 0x80, "sizeof DeliverPostRelayContext");
static_assert(offsetof(DeliverPostRelayContext, _request) == 0x60, "DeliverPostRelayContext::_request");
static_assert(offsetof(DeliverPostRelayContext, _response) == 0x68, "DeliverPostRelayContext::_response");
static_assert(offsetof(DeliverPostRelayContext, _postContext) == 0x78, "DeliverPostRelayContext::_postContext");
