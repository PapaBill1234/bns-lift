// marketdealeragentchannel.h: marketdealeragentchannel.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: the classes have no members and no bases yet. Later waves add the PDB layouts.
#pragma once
#include "GameDaemonFwd.h"

class MarketDealerAgentChannel
{
public:
    void __cdecl Initialize(short);  // 0x15b3e0
    bool __cdecl SendHello(void);  // 0x15b510
};

class MarketDealerAgentChannelManager
{
public:
    struct SaleItem {};
public:
    bool __cdecl Initialize(short, short *const);  // 0x15f2b0
    void __cdecl Destroy(void);  // 0x15f610
    bool __cdecl IsConnected(short);  // 0x15f780
private:
    ::MarketDealerAgentChannel * __cdecl acquire(unsigned int);  // 0x15f7e0
public:
    bool __cdecl Send(short, ::Packet const *);  // 0x15f8b0
    void __cdecl SendReserveSale(::Pc *, unsigned __int64, char, __int64, int, int);  // 0x15f9a0
    void __cdecl SendCancelSaleReservation(::Pc *, unsigned __int64, unsigned __int64);  // 0x15fba0
    void __cdecl SendRegisterSale(::Pc *, __int64, unsigned __int64, unsigned __int64, int, ::MarketDealerAgentChannelManager::SaleItem);  // 0x15fce0
    void __cdecl SendUpdateSalePrice(::Pc *, unsigned __int64, __int64);  // 0x15ff50
    void __cdecl SendAbandonSale(::Pc *, unsigned __int64);  // 0x1600a0
    void __cdecl SendReserveBid(::Pc *, unsigned __int64, unsigned __int64, __int64);  // 0x160310
    void __cdecl SendCancelBidReservation(::Pc *, unsigned __int64, unsigned __int64, unsigned __int64);  // 0x1604f0
    void __cdecl SendRegisterBid(::Pc *, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64);  // 0x160640
    void __cdecl SendUpdateBidPrice(::Pc *, unsigned __int64, unsigned __int64, unsigned __int64, __int64);  // 0x1607a0
    void __cdecl SendAbandonBid(::Pc *, unsigned __int64, unsigned __int64);  // 0x160920
    void __cdecl SendReservePurchase(::Pc *, unsigned __int64, unsigned __int64, __int64);  // 0x160dd0
    void __cdecl SendCancelPurchaseReservation(::Pc *, unsigned __int64, unsigned __int64, unsigned __int64);  // 0x160fb0
    void __cdecl SendRegisterPurchase(::Pc *, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64);  // 0x161100
    void __cdecl SendRetrieveSaleList(::Pc *, char, char, __int64, char);  // 0x161260
    void __cdecl SendRetrieveBidList(::Pc *);  // 0x1613e0
    void __cdecl SendRetrieveBidRankStatus(::Pc *, __int64 *const, int);  // 0x161520
    bool __cdecl SendRetrieveReservationList(short, unsigned __int64, __int64);  // 0x1617f0
};

class MarketDealerAgentSessionHandler
{
public:
    virtual bool __cdecl OnAccept(::Session const *) const;  // 0x15af30
    virtual bool __cdecl OnConnect(::Session const *, bool) const;  // 0x15af70
    virtual void __cdecl OnClose(::Session const *, bool) const;  // 0x15b1a0
    virtual bool __cdecl PacketHandler(::Session const *, ::Packet const *) const;  // 0x15b380
};

bool __cdecl HandleMarketServiceRegisterPurchaseFail(::Session const *, ::Packet const *);  // 0x15b6b0
bool __cdecl HandleMarketServiceRegisterPurchaseOk(::Session const *, ::Packet const *);  // 0x15b850
bool __cdecl HandleMarketServiceCancelPurchaseReservationFail(::Session const *, ::Packet const *);  // 0x15b8f0
bool __cdecl HandleMarketServiceCancelPurchaseReservationOk(::Session const *, ::Packet const *);  // 0x15b960
bool __cdecl HandleMarketServiceReservePurchaseFail(::Session const *, ::Packet const *);  // 0x15b9c0
bool __cdecl HandleMarketServiceReservePurchaseOk(::Session const *, ::Packet const *);  // 0x15bb60
bool __cdecl HandleMarketServiceAbandonBidFail(::Session const *, ::Packet const *);  // 0x15bd10
bool __cdecl HandleMarketServiceAbandonBidOk(::Session const *, ::Packet const *);  // 0x15be50
bool __cdecl HandleMarketServiceUpdateBidPriceFail(::Session const *, ::Packet const *);  // 0x15bf40
bool __cdecl HandleMarketServiceUpdateBidPriceOk(::Session const *, ::Packet const *);  // 0x15c0f0
bool __cdecl HandleMarketServiceRegisterBidFail(::Session const *, ::Packet const *);  // 0x15c190
bool __cdecl HandleMarketServiceRegisterBidOk(::Session const *, ::Packet const *);  // 0x15c330
bool __cdecl HandleMarketServiceCancelBidReservationFail(::Session const *, ::Packet const *);  // 0x15c3d0
bool __cdecl HandleMarketServiceCancelBidReservationOk(::Session const *, ::Packet const *);  // 0x15c440
bool __cdecl HandleMarketServiceReserveBidFail(::Session const *, ::Packet const *);  // 0x15c4a0
bool __cdecl HandleMarketServiceReserveBidOk(::Session const *, ::Packet const *);  // 0x15c640
bool __cdecl HandleMarketServiceAbandonSaleFail(::Session const *, ::Packet const *);  // 0x15c7f0
bool __cdecl HandleMarketServiceAbandonSaleOk(::Session const *, ::Packet const *);  // 0x15c930
bool __cdecl HandleMarketServiceUpdateSalePriceFail(::Session const *, ::Packet const *);  // 0x15ca20
bool __cdecl HandleMarketServiceUpdateSalePriceOk(::Session const *, ::Packet const *);  // 0x15cb30
bool __cdecl HandleMarketServiceRegisterSaleFail(::Session const *, ::Packet const *);  // 0x15cc30
bool __cdecl HandleMarketServiceRegisterSaleOk(::Session const *, ::Packet const *);  // 0x15ce20
bool __cdecl HandleMarketServiceCancelSaleReservationFail(::Session const *, ::Packet const *);  // 0x15d010
bool __cdecl HandleMarketServiceCancelSaleReservationOk(::Session const *, ::Packet const *);  // 0x15d090
bool __cdecl HandleMarketServiceReserveSaleFail(::Session const *, ::Packet const *);  // 0x15d100
bool __cdecl HandleMarketServiceReserveSaleOk(::Session const *, ::Packet const *);  // 0x15d2f0
bool __cdecl HandleMarketServiceRetrieveBidListFail(::Session const *, ::Packet const *);  // 0x15d4f0
bool __cdecl HandleMarketServiceRetrieveBidListOk(::Session const *, ::Packet const *);  // 0x15d620
bool __cdecl HandleMarketServiceRetrieveBidRankStatusFail(::Session const *, ::Packet const *);  // 0x15dcb0
bool __cdecl HandleMarketServiceRetrieveBidRankStatusOk(::Session const *, ::Packet const *);  // 0x15de20
bool __cdecl HandleMarketServiceRetrieveSaleListFail(::Session const *, ::Packet const *);  // 0x15e2e0
bool __cdecl HandleMarketServiceRetrieveSaleListOk(::Session const *, ::Packet const *);  // 0x15e460
bool __cdecl HandleMarketServiceHelloFail(::Session const *, ::Packet const *);  // 0x15eb10
bool __cdecl HandleMarketServiceHelloOk(::Session const *, ::Packet const *);  // 0x15eb40
bool __cdecl HandleMarketServiceRetrieveReservationListOk(::Session const *, ::Packet const *);  // 0x15eb70
bool __cdecl HandleMarketServiceRetrieveReservationListFail(::Session const *, ::Packet const *);  // 0x15ed80
bool __cdecl HandleMarketServiceCancelReservationListOk(::Session const *, ::Packet const *);  // 0x15ef50
bool __cdecl HandleMarketServiceCancelReservationListFail(::Session const *, ::Packet const *);  // 0x15f0e0
