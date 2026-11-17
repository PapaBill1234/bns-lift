// PingRelay.obj (PostOfficeDaemon PDB). Layouts from include/pdb/PostOfficeDaemon/types.h.
#pragma once
#include <stddef.h>
#include "RelayContext.h"

// PDB type 0x2BA9: RelayRequest is not virtual, has no data and has only a constructor.
class RelayRequest
{
public:
    RelayRequest() {}
};

// PDB type 0x2B56. The derived request classes put the vfptr at +0 and the empty base at +8.
class PingRelayRequest : public RelayRequest
{
public:
    explicit PingRelayRequest(unsigned long long const pingSeq) : _pingSeq(pingSeq) {}  // inlined in 0x4ed0
    virtual ~PingRelayRequest() {}

    unsigned long long const _pingSeq;
};
static_assert(sizeof(PingRelayRequest) == 0x10, "sizeof PingRelayRequest");

class PingRelayResponse : public RelayResponse
{
public:
    // PDB ctor (ResultState, short const) with default arguments. 0x5120 stores (1, 0) and _pingSeq 0.
    PingRelayResponse(ResultState resultState = RESULTSTATE_SUCCESS, short const failReason = 0)
        : RelayResponse(resultState, failReason), _pingSeq(0) {}
    virtual ~PingRelayResponse() {}  // 0x4ce0 (inline)

    unsigned long long _pingSeq;
};
static_assert(sizeof(PingRelayResponse) == 0x18, "sizeof PingRelayResponse");
static_assert(offsetof(PingRelayResponse, _pingSeq) == 0x10, "PingRelayResponse::_pingSeq");

class PingRelayContext : public RelayContext
{
public:
    PingRelayContext(EconomyHeader const& economyHeader, PingRelayRequest const& request)  // inlined in 0x4ed0
        : RelayContext(economyHeader), _request(request) {}
    virtual ~PingRelayContext() {}  // 0x4d20 (inline)

    virtual unsigned short const GetRequestWid() const;            // 0xfb40 (PingGenerator.cpp)
    virtual RelayHeader const MakeRelayHeader() const;             // 0xaf30
    virtual bool ComposeRequestPacket(FragmentPacket&) const;      // ❓ folded (PingGenerator.cpp)
    virtual bool ComposeRequestPacket(Packet&) const;              // 0xaf70
    virtual bool ComposeResponsePacket(FragmentPacket&) const;     // ❓ folded with 0x34c40
    virtual bool ComposeResponsePacket(Packet&) const;             // 0x34c40 (PingGenerator.cpp)
    virtual bool processRelayRequest(Channel* const) const;        // 0xaad0
    virtual bool processRelayResponse() const;                     // 0xabd0
    virtual bool processRelayTimeout();                            // 0xaed0
    virtual void initResponse(RelayResponse* const);               // 0x4cf0 (PingGenerator.cpp)

    PingRelayRequest _request;
    PingRelayResponse _response;
};
static_assert(sizeof(PingRelayContext) == 0x88, "sizeof PingRelayContext");
static_assert(offsetof(PingRelayContext, _request) == 0x60, "PingRelayContext::_request");
static_assert(offsetof(PingRelayContext, _response) == 0x70, "PingRelayContext::_response");
