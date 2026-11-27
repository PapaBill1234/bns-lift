// marketreaderagentchannel.cpp: marketreaderagentchannel.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "marketreaderagentchannel.h"
#include "pc.h"
#include "LiftStub.h"

// 0x1618f0
bool __cdecl MarketReaderAgentSessionHandler::OnAccept(::Session const *) const
{
    LIFT_STUB(0x1618f0);
}

// 0x161930
bool __cdecl MarketReaderAgentSessionHandler::OnConnect(::Session const *, bool) const
{
    LIFT_STUB(0x161930);
}

// 0x161b60
void __cdecl MarketReaderAgentSessionHandler::OnClose(::Session const *, bool) const
{
    LIFT_STUB(0x161b60);
}

// 0x161d40
bool __cdecl MarketReaderAgentSessionHandler::PacketHandler(::Session const *, ::Packet const *) const
{
    LIFT_STUB(0x161d40);
}

// 0x161dd0
void __cdecl MarketReaderAgentChannel::Initialize(short)
{
    LIFT_STUB(0x161dd0);
}

// 0x161f00
bool __cdecl MarketReaderAgentChannel::SendHello(void)
{
    LIFT_STUB(0x161f00);
}

// 0x1620a0
bool __cdecl HandleMarketServiceSearchItemOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x1620a0);
}

// 0x1629c0
bool __cdecl HandleMarketServiceSearchItemFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x1629c0);
}

// 0x162b90
bool __cdecl HandleMarketServiceRetrieveInstantSaleItemLowestPriceOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x162b90);
}

// 0x162d50
bool __cdecl HandleMarketServiceRetrieveInstantSaleItemLowestPriceFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x162d50);
}

// 0x162ee0
bool __cdecl MarketReaderAgentChannelManager::Initialize(short, short *const)
{
    LIFT_STUB(0x162ee0);
}

// 0x163240
void __cdecl MarketReaderAgentChannelManager::Destroy(void)
{
    LIFT_STUB(0x163240);
}

// 0x1633b0
::MarketReaderAgentChannel * __cdecl MarketReaderAgentChannelManager::acquire(unsigned int)
{
    LIFT_STUB(0x1633b0);
}

// 0x163480
bool __cdecl MarketReaderAgentChannelManager::Send(short, ::Packet const *)
{
    LIFT_STUB(0x163480);
}

// 0x163570
bool __cdecl MarketReaderAgentChannelManager::SendSearchItem(::Pc *, char, char, char, char, int, __int64, __int64, __int64)
{
    LIFT_STUB(0x163570);
}

// 0x163760
bool __cdecl MarketReaderAgentChannelManager::SendRetrieveInstantSaleItemLowestPrice(::Pc *, int)
{
    LIFT_STUB(0x163760);
}
