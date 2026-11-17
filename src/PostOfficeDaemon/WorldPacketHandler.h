// WorldPacketHandler.obj (PostOfficeDaemon PDB). Layouts from include/pdb/PostOfficeDaemon/types.h and 0x1f650.
// The context functions that are not in WorldPacketHandler.obj are in the modules RetrieveCharacterInfoRelay
// (0x1de30..0x1e410) and CheckPostCapacityRelay (0x9180..0x9740). A later card lifts them.
#pragma once
#include <stddef.h>
#include "RelayContext.h"
#include "PingRelay.h"

class Session;
class Packet;

// ❓ The PDB has no body for this class. Layout from the ctor 0x1f650 and the handler 0x1fdd0.
class RetrieveCharacterInfoRelayRequest : public RelayRequest
{
public:
    RetrieveCharacterInfoRelayRequest() : _gameTid(0), _requestWid(0), _targetWid(0)  // ❓ inline
    {
        for (int i = 0; i < 33; ++i)
            _targetCharacterName[i] = 0;
    }
    virtual ~RetrieveCharacterInfoRelayRequest() {}  // ❓ inline (vtable folded, pipe.chRequest+3860)

    long long _gameTid;
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
    virtual ~RetrieveCharacterInfoRelayResponse() {}  // ❓ inline

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

    virtual unsigned short const GetRequestWid() const;            // ❓ folded with 0x1f800
    virtual RelayHeader const MakeRelayHeader() const;             // later card (RetrieveCharacterInfoRelay)
    virtual bool ComposeRequestPacket(FragmentPacket&) const;      // later card
    virtual bool ComposeRequestPacket(Packet&) const;              // later card
    virtual bool ComposeResponsePacket(FragmentPacket&) const;     // later card
    virtual bool ComposeResponsePacket(Packet&) const;             // later card
    virtual bool processRelayRequest(Channel* const) const;        // later card
    virtual bool processRelayResponse() const;                     // later card
    virtual bool processRelayTimeout();                            // later card
    virtual void initResponse(RelayResponse* const response);      // 0x1f770

    RetrieveCharacterInfoRelayRequest _request;
    RetrieveCharacterInfoRelayResponse _response;
};
static_assert(sizeof(RetrieveCharacterInfoRelayContext) == 208, "sizeof RetrieveCharacterInfoRelayContext");
static_assert(offsetof(RetrieveCharacterInfoRelayContext, _request) == 0x60, "_request");
static_assert(offsetof(RetrieveCharacterInfoRelayContext, _response) == 0xB8, "_response");

// ❓ The PDB has no body for this class. Layout from the handler 0x20250.
class CheckPostCapacityRelayRequest : public RelayRequest
{
public:
    CheckPostCapacityRelayRequest() : _gameTid(0), _requestWid(0), _targetWid(0), _targetPcId(0) {}  // ❓ inline
    virtual ~CheckPostCapacityRelayRequest() {}  // ❓ inline

    long long _gameTid;
    unsigned short _requestWid;
    unsigned short _targetWid;
    long long _targetPcId;
};
static_assert(sizeof(CheckPostCapacityRelayRequest) == 0x20, "sizeof CheckPostCapacityRelayRequest");
static_assert(offsetof(CheckPostCapacityRelayRequest, _targetPcId) == 0x18, "_targetPcId");

class CheckPostCapacityRelayResponse : public RelayResponse
{
public:
    virtual ~CheckPostCapacityRelayResponse() {}  // ❓ inline
};
static_assert(sizeof(CheckPostCapacityRelayResponse) == 0x10, "sizeof CheckPostCapacityRelayResponse");

class CheckPostCapacityRelayContext : public RelayContext
{
public:
    CheckPostCapacityRelayContext(EconomyHeader const& economyHeader, CheckPostCapacityRelayRequest const& request)
        : RelayContext(economyHeader), _request(request)  // ❓ inlined in 0x20250
    {
        _response._resultState = RelayResponse::RESULTSTATE_SUCCESS;
        _response._failReason = 0;
    }
    virtual ~CheckPostCapacityRelayContext() {}  // 0x1f840 (scalar deleting dtor)

    virtual unsigned short const GetRequestWid() const;            // 0x1f800
    virtual RelayHeader const MakeRelayHeader() const;             // later card (CheckPostCapacityRelay)
    virtual bool ComposeRequestPacket(FragmentPacket&) const;      // later card
    virtual bool ComposeRequestPacket(Packet&) const;              // later card
    virtual bool ComposeResponsePacket(FragmentPacket&) const;     // later card
    virtual bool ComposeResponsePacket(Packet&) const;             // later card
    virtual bool processRelayRequest(Channel* const) const;        // later card
    virtual bool processRelayResponse() const;                     // later card
    virtual bool processRelayTimeout();                            // later card
    virtual void initResponse(RelayResponse* const response);      // 0x1f810

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
