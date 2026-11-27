// marketreaderagentchannel.h: marketreaderagentchannel.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class MarketReaderAgentChannel
{
public:
    void __cdecl Initialize(short);  // 0x161dd0
    bool __cdecl SendHello(void);  // 0x161f00
};

class MarketReaderAgentChannelManager
{
public:
    bool __cdecl Initialize(short, short *const);  // 0x162ee0
    void __cdecl Destroy(void);  // 0x163240
private:
    ::MarketReaderAgentChannel * __cdecl acquire(unsigned int);  // 0x1633b0
public:
    bool __cdecl Send(short, ::Packet const *);  // 0x163480
    bool __cdecl SendSearchItem(::Pc *, char, char, char, char, int, __int64, __int64, __int64);  // 0x163570
    bool __cdecl SendRetrieveInstantSaleItemLowestPrice(::Pc *, int);  // 0x163760
};

class MarketReaderAgentSessionHandler
{
public:
    virtual bool __cdecl OnAccept(::Session const *) const;  // 0x1618f0
    virtual bool __cdecl OnConnect(::Session const *, bool) const;  // 0x161930
    virtual void __cdecl OnClose(::Session const *, bool) const;  // 0x161b60
    virtual bool __cdecl PacketHandler(::Session const *, ::Packet const *) const;  // 0x161d40
};

bool __cdecl HandleMarketServiceSearchItemOk(::Session const *, ::Packet const *);  // 0x1620a0
bool __cdecl HandleMarketServiceSearchItemFail(::Session const *, ::Packet const *);  // 0x1629c0
bool __cdecl HandleMarketServiceRetrieveInstantSaleItemLowestPriceOk(::Session const *, ::Packet const *);  // 0x162b90
bool __cdecl HandleMarketServiceRetrieveInstantSaleItemLowestPriceFail(::Session const *, ::Packet const *);  // 0x162d50
