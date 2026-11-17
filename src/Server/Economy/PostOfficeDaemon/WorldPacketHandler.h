// WorldPacketHandler.obj (PostOfficeDaemon PDB). Layouts from include/pdb/PostOfficeDaemon/types.h and 0x1f650.
// The context functions that are not in WorldPacketHandler.obj are in RetrieveCharacterInfoRelay.cpp
// (0x1de30..0x1e410) and CheckPostCapacityRelay.cpp (0x9180..0x9740).
#pragma once
#include <stddef.h>
#include "RelayContext.h"
#include "PingRelay.h"

class Session;
class Packet;

// PDB type 0x2BF2.
class RetrieveCharacterInfoRelayRequest : public RelayRequest
{
public:
    RetrieveCharacterInfoRelayRequest() : _gameTid(0), _requestWid(0), _targetWid(0)  // inlined at 0x1fe48-0x1fe64: vtable, 0, 0, memset 0x42
    {
        for (int i = 0; i < 33; ++i)
            _targetCharacterName[i] = 0;
    }
    virtual ~RetrieveCharacterInfoRelayRequest() {}  // vtable folded, pipe.chRequest+3860

    unsigned long long _gameTid;
    unsigned short _requestWid;
    unsigned short _targetWid;
    wchar_t _targetCharacterName[33];
};
static_assert(sizeof(RetrieveCharacterInfoRelayRequest) == 0x58, "sizeof RetrieveCharacterInfoRelayRequest");
static_assert(offsetof(RetrieveCharacterInfoRelayRequest, _requestWid) == 0x10, "_requestWid");
static_assert(offsetof(RetrieveCharacterInfoRelayRequest, _targetCharacterName) == 0x14, "_targetCharacterName");

class RetrieveCharacterInfoRelayResponse : public RelayResponse
{
public:
    // PDB ctor (ResultState, short const) with default arguments. 0x57f0 stores (1, 0).
    RetrieveCharacterInfoRelayResponse(ResultState resultState = RESULTSTATE_SUCCESS, short const failReason = 0)
        : RelayResponse(resultState, failReason), _resultPcId(0) {}  // inlined at 0x5853-0x5874: +8 = 1, +0xC = 0, +0x10 = 0
    virtual ~RetrieveCharacterInfoRelayResponse() {}

    long long _resultPcId;
};
static_assert(sizeof(RetrieveCharacterInfoRelayResponse) == 0x18, "sizeof RetrieveCharacterInfoRelayResponse");
static_assert(offsetof(RetrieveCharacterInfoRelayResponse, _resultPcId) == 0x10, "_resultPcId");

class RetrieveCharacterInfoRelayContext : public RelayContext
{
public:
    RetrieveCharacterInfoRelayContext(EconomyHeader const& economyHeader,
                                      RetrieveCharacterInfoRelayRequest const& request);  // 0x1f650
    virtual ~RetrieveCharacterInfoRelayContext() {}  // 0x1f7a0 (scalar deleting dtor)

    virtual unsigned short const GetRequestWid() const;            // LIFT: folded with 0x1f800
    virtual RelayHeader const MakeRelayHeader() const;             // 0x1e110
    virtual bool ComposeRequestPacket(FragmentPacket&) const;      // LIFT: folded with 0x34c40
    virtual bool ComposeRequestPacket(Packet&) const;              // 0x1e150
    virtual bool ComposeResponsePacket(FragmentPacket&) const;     // LIFT: folded with 0x34c40
    virtual bool ComposeResponsePacket(Packet&) const;             // 0x1e230
    virtual bool processRelayRequest(Channel* const) const;        // 0x1de30
    virtual bool processRelayResponse() const;                     // 0x1df30
    virtual bool processRelayTimeout();                            // 0x1e0b0
    virtual void initResponse(RelayResponse* const response);      // 0x1f770

    short const convertFailReason(RelayResponse::ResultState const resultState, short const failReason) const;  // 0x1e410

    RetrieveCharacterInfoRelayRequest _request;
    RetrieveCharacterInfoRelayResponse _response;
};
static_assert(sizeof(RetrieveCharacterInfoRelayContext) == 208, "sizeof RetrieveCharacterInfoRelayContext");
static_assert(offsetof(RetrieveCharacterInfoRelayContext, _request) == 0x60, "_request");
static_assert(offsetof(RetrieveCharacterInfoRelayContext, _response) == 0xB8, "_response");

// PDB type 0x2C44.
class CheckPostCapacityRelayRequest : public RelayRequest
{
public:
    CheckPostCapacityRelayRequest() : _gameTid(0), _requestWid(0), _targetWid(0), _targetPcId(0) {}  // inlined at 0x202bd-0x202cf: vtable, 0, 0, 0
    virtual ~CheckPostCapacityRelayRequest() {}

    unsigned long long _gameTid;
    unsigned short _requestWid;
    unsigned short _targetWid;
    long long _targetPcId;
};
static_assert(sizeof(CheckPostCapacityRelayRequest) == 0x20, "sizeof CheckPostCapacityRelayRequest");
static_assert(offsetof(CheckPostCapacityRelayRequest, _targetPcId) == 0x18, "_targetPcId");

class CheckPostCapacityRelayResponse : public RelayResponse
{
public:
    // PDB ctor (ResultState, short const) with default arguments. 0x5ee0 stores (1, 0).
    CheckPostCapacityRelayResponse(ResultState resultState = RESULTSTATE_SUCCESS, short const failReason = 0)
        : RelayResponse(resultState, failReason) {}
    virtual ~CheckPostCapacityRelayResponse() {}
};
static_assert(sizeof(CheckPostCapacityRelayResponse) == 0x10, "sizeof CheckPostCapacityRelayResponse");

class CheckPostCapacityRelayContext : public RelayContext
{
public:
    CheckPostCapacityRelayContext(EconomyHeader const& economyHeader, CheckPostCapacityRelayRequest const& request)
        : RelayContext(economyHeader), _request(request)  // inlined in 0x20250
    {
    }
    virtual ~CheckPostCapacityRelayContext() {}  // 0x1f840 (scalar deleting dtor)

    virtual unsigned short const GetRequestWid() const;            // 0x1f800
    virtual RelayHeader const MakeRelayHeader() const;             // 0x9450
    virtual bool ComposeRequestPacket(FragmentPacket&) const;      // LIFT: folded with 0x34c40
    virtual bool ComposeRequestPacket(Packet&) const;              // 0x9490
    virtual bool ComposeResponsePacket(FragmentPacket&) const;     // LIFT: folded with 0x34c40
    virtual bool ComposeResponsePacket(Packet&) const;             // 0x9570
    virtual bool processRelayRequest(Channel* const) const;        // 0x9180
    virtual bool processRelayResponse() const;                     // 0x9280
    virtual bool processRelayTimeout();                            // 0x9400
    virtual void initResponse(RelayResponse* const response);      // 0x1f810

    short const convertFailReason(RelayResponse::ResultState const resultState, short const failReason) const;  // 0x9740

    CheckPostCapacityRelayRequest _request;
    CheckPostCapacityRelayResponse _response;
};
static_assert(sizeof(CheckPostCapacityRelayContext) == 144, "sizeof CheckPostCapacityRelayContext");
static_assert(offsetof(CheckPostCapacityRelayContext, _request) == 96, "_request");
static_assert(offsetof(CheckPostCapacityRelayContext, _response) == 128, "_response");

bool HandlePostOfficeServiceHelloReq(Session const* session, Packet const* packet);                   // 0x1f890
bool HandlePostOfficeServiceRetrieveCharacterInfoReq(Session const* session, Packet const* packet);  // 0x1fdd0
bool HandlePostOfficeServiceCheckPostCapacityReq(Session const* session, Packet const* packet);      // 0x20250
bool HandlePostOfficeServiceRegisterPostReq(Session const* session, Packet const* packet);           // 0x20720
