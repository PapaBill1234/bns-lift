// marketdealeragentchannel.cpp: marketdealeragentchannel.cpp (GameDaemon PDB, 2019 + PDB). Wave 0: stubs only. A stub is not a lift.
#include "marketdealeragentchannel.h"
#include "pc.h"
#include "LiftStub.h"
#include "AlertSender.h"
#include "Log.h"

// LIFT: per-exe path literal (lessons A6).
#define MARKETDEALERAGENTCHANNEL_FILE L"e:\\dailybuild02\\gamedaemon-common-0.0.348\\depot\\branch\\348nc\\program\\server\\gamedaemon\\MarketDealerAgentChannel.cpp"

// 0x15af30
#pragma comment(linker, "/INCLUDE:?OnAccept@MarketDealerAgentSessionHandler@@UEBA_NPEBVSession@@@Z")  // LIFT: dead-strip keep (no live caller yet)
bool __cdecl MarketDealerAgentSessionHandler::OnAccept(::Session const *) const
{
    Log::Write(Log::LT_ERROR, MARKETDEALERAGENTCHANNEL_FILE, 29,
               L"== CRASH == [game-marketD], cannot accept from marketD (game connect to marketD)");
    AlertSender::Write(MARKETDEALERAGENTCHANNEL_FILE, 29,
                       L"== CRASH == [game-marketD], cannot accept from marketD (game connect to marketD)");
    return false;
}

// 0x15af70
bool __cdecl MarketDealerAgentSessionHandler::OnConnect(::Session const *, bool) const
{
    LIFT_STUB(0x15af70);
}

// 0x15b1a0
void __cdecl MarketDealerAgentSessionHandler::OnClose(::Session const *, bool) const
{
    LIFT_STUB(0x15b1a0);
}

// 0x15b380
bool __cdecl MarketDealerAgentSessionHandler::PacketHandler(::Session const *, ::Packet const *) const
{
    LIFT_STUB(0x15b380);
}

// 0x15b3e0
void __cdecl MarketDealerAgentChannel::Initialize(short)
{
    LIFT_STUB(0x15b3e0);
}

// 0x15b510
bool __cdecl MarketDealerAgentChannel::SendHello(void)
{
    LIFT_STUB(0x15b510);
}

// 0x15b6b0
bool __cdecl HandleMarketServiceRegisterPurchaseFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x15b6b0);
}

// 0x15b850
bool __cdecl HandleMarketServiceRegisterPurchaseOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x15b850);
}

// 0x15b8f0
#pragma comment(linker, "/INCLUDE:?HandleMarketServiceCancelPurchaseReservationFail@@YA_NPEBVSession@@PEBVPacket@@@Z")  // LIFT: dead-strip keep (no live caller yet)
bool __cdecl HandleMarketServiceCancelPurchaseReservationFail(::Session const *, ::Packet const *packet)
{
    short c;
    unsigned __int64 tid = 0;
    short reason = 0;
    packet->Decompose("hqE", &c, &tid, &reason);
    Log::Write(Log::LT_ERROR, MARKETDEALERAGENTCHANNEL_FILE, 228,
               L"[game-marketD], MarketService_CancelPurchaseReservationFail; tid:0x%I64x, reason:%d", tid, static_cast<int>(reason));
    return true;
}

// 0x15b960
#pragma comment(linker, "/INCLUDE:?HandleMarketServiceCancelPurchaseReservationOk@@YA_NPEBVSession@@PEBVPacket@@@Z")  // LIFT: dead-strip keep (no live caller yet)
bool __cdecl HandleMarketServiceCancelPurchaseReservationOk(::Session const *, ::Packet const *packet)
{
    short c;
    unsigned __int64 tid = 0;
    packet->Decompose("hq", &c, &tid);
    Log::Write(Log::LT_DEBUG, MARKETDEALERAGENTCHANNEL_FILE, 239,
               L"[game-marketD], MarketService_CancelPurchaseReservationOk; tid:0x%I64x", tid);
    return true;
}

// 0x15b9c0
bool __cdecl HandleMarketServiceReservePurchaseFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x15b9c0);
}

// 0x15bb60
bool __cdecl HandleMarketServiceReservePurchaseOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x15bb60);
}

// 0x15bd10
bool __cdecl HandleMarketServiceAbandonBidFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x15bd10);
}

// 0x15be50
bool __cdecl HandleMarketServiceAbandonBidOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x15be50);
}

// 0x15bf40
bool __cdecl HandleMarketServiceUpdateBidPriceFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x15bf40);
}

// 0x15c0f0
bool __cdecl HandleMarketServiceUpdateBidPriceOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x15c0f0);
}

// 0x15c190
bool __cdecl HandleMarketServiceRegisterBidFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x15c190);
}

// 0x15c330
bool __cdecl HandleMarketServiceRegisterBidOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x15c330);
}

// 0x15c3d0
#pragma comment(linker, "/INCLUDE:?HandleMarketServiceCancelBidReservationFail@@YA_NPEBVSession@@PEBVPacket@@@Z")  // LIFT: dead-strip keep (no live caller yet)
bool __cdecl HandleMarketServiceCancelBidReservationFail(::Session const *, ::Packet const *packet)
{
    short c;
    unsigned __int64 tid = 0;
    short reason = 0;
    packet->Decompose("hqE", &c, &tid, &reason);
    Log::Write(Log::LT_ERROR, MARKETDEALERAGENTCHANNEL_FILE, 400,
               L"[game-marketD], HandleMarketServiceCancelBidReservationFail; tid:0x%I64x, reason:%d", tid, static_cast<int>(reason));
    return true;
}

// 0x15c440
#pragma comment(linker, "/INCLUDE:?HandleMarketServiceCancelBidReservationOk@@YA_NPEBVSession@@PEBVPacket@@@Z")  // LIFT: dead-strip keep (no live caller yet)
bool __cdecl HandleMarketServiceCancelBidReservationOk(::Session const *, ::Packet const *packet)
{
    short c;
    unsigned __int64 tid = 0;
    packet->Decompose("hq", &c, &tid);
    Log::Write(Log::LT_DEBUG, MARKETDEALERAGENTCHANNEL_FILE, 411,
               L"[game-marketD], HandleMarketServiceCancelBidReservationOk; tid:0x%I64x", tid);
    return true;
}

// 0x15c4a0
bool __cdecl HandleMarketServiceReserveBidFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x15c4a0);
}

// 0x15c640
bool __cdecl HandleMarketServiceReserveBidOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x15c640);
}

// 0x15c7f0
bool __cdecl HandleMarketServiceAbandonSaleFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x15c7f0);
}

// 0x15c930
bool __cdecl HandleMarketServiceAbandonSaleOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x15c930);
}

// 0x15ca20
bool __cdecl HandleMarketServiceUpdateSalePriceFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x15ca20);
}

// 0x15cb30
bool __cdecl HandleMarketServiceUpdateSalePriceOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x15cb30);
}

// 0x15cc30
bool __cdecl HandleMarketServiceRegisterSaleFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x15cc30);
}

// 0x15ce20
bool __cdecl HandleMarketServiceRegisterSaleOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x15ce20);
}

// 0x15d010
#pragma comment(linker, "/INCLUDE:?HandleMarketServiceCancelSaleReservationFail@@YA_NPEBVSession@@PEBVPacket@@@Z")  // LIFT: dead-strip keep (no live caller yet)
bool __cdecl HandleMarketServiceCancelSaleReservationFail(::Session const *, ::Packet const *packet)
{
    short c;
    unsigned __int64 tid = 0;
    short reason = 0;
    packet->Decompose("hqE", &c, &tid, &reason);
    // LIFT: inlined pc id form (low 32 bits of the db id + 0x1000000000000); no PDB name for the helper.
    Log::Write(Log::LT_DEBUG, MARKETDEALERAGENTCHANNEL_FILE, 654,
               L"[game-marketD], HandleMarketServiceCancelSaleReservationFail; pc:0x%I64x, reason:%d",
               static_cast<unsigned int>(tid) + 0x1000000000000ULL, static_cast<int>(reason));
    return true;
}

// 0x15d090
#pragma comment(linker, "/INCLUDE:?HandleMarketServiceCancelSaleReservationOk@@YA_NPEBVSession@@PEBVPacket@@@Z")  // LIFT: dead-strip keep (no live caller yet)
bool __cdecl HandleMarketServiceCancelSaleReservationOk(::Session const *, ::Packet const *packet)
{
    short c;
    unsigned __int64 tid = 0;
    packet->Decompose("hq", &c, &tid);
    // LIFT: inlined pc id form (low 32 bits of the db id + 0x1000000000000); no PDB name for the helper.
    Log::Write(Log::LT_DEBUG, MARKETDEALERAGENTCHANNEL_FILE, 668,
               L"[game-marketD], HandleMarketServiceCancelSaleReservationOk; pc:0x%I64x",
               static_cast<unsigned int>(tid) + 0x1000000000000ULL);
    return true;
}

// 0x15d100
bool __cdecl HandleMarketServiceReserveSaleFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x15d100);
}

// 0x15d2f0
bool __cdecl HandleMarketServiceReserveSaleOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x15d2f0);
}

// 0x15d4f0
bool __cdecl HandleMarketServiceRetrieveBidListFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x15d4f0);
}

// 0x15d620
bool __cdecl HandleMarketServiceRetrieveBidListOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x15d620);
}

// 0x15dcb0
bool __cdecl HandleMarketServiceRetrieveBidRankStatusFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x15dcb0);
}

// 0x15de20
bool __cdecl HandleMarketServiceRetrieveBidRankStatusOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x15de20);
}

// 0x15e2e0
bool __cdecl HandleMarketServiceRetrieveSaleListFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x15e2e0);
}

// 0x15e460
bool __cdecl HandleMarketServiceRetrieveSaleListOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x15e460);
}

// 0x15eb10
#pragma comment(linker, "/INCLUDE:?HandleMarketServiceHelloFail@@YA_NPEBVSession@@PEBVPacket@@@Z")  // LIFT: dead-strip keep (no live caller yet)
bool __cdecl HandleMarketServiceHelloFail(::Session const *, ::Packet const *)
{
    Log::Write(Log::LT_DEBUG, MARKETDEALERAGENTCHANNEL_FILE, 1194, L"[game-marketD], HandleMarketServiceHelloFail");
    return true;
}

// 0x15eb40
#pragma comment(linker, "/INCLUDE:?HandleMarketServiceHelloOk@@YA_NPEBVSession@@PEBVPacket@@@Z")  // LIFT: dead-strip keep (no live caller yet)
bool __cdecl HandleMarketServiceHelloOk(::Session const *, ::Packet const *)
{
    Log::Write(Log::LT_DEBUG, MARKETDEALERAGENTCHANNEL_FILE, 1200, L"[game-marketD], HandleMarketServiceHelloOk");
    return true;
}

// 0x15eb70
bool __cdecl HandleMarketServiceRetrieveReservationListOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x15eb70);
}

// 0x15ed80
bool __cdecl HandleMarketServiceRetrieveReservationListFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x15ed80);
}

// 0x15ef50
bool __cdecl HandleMarketServiceCancelReservationListOk(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x15ef50);
}

// 0x15f0e0
bool __cdecl HandleMarketServiceCancelReservationListFail(::Session const *, ::Packet const *)
{
    LIFT_STUB(0x15f0e0);
}

// 0x15f2b0
bool __cdecl MarketDealerAgentChannelManager::Initialize(short, short *const)
{
    LIFT_STUB(0x15f2b0);
}

// 0x15f610
void __cdecl MarketDealerAgentChannelManager::Destroy(void)
{
    LIFT_STUB(0x15f610);
}

// 0x15f780
bool __cdecl MarketDealerAgentChannelManager::IsConnected(short)
{
    LIFT_STUB(0x15f780);
}

// 0x15f7e0
::MarketDealerAgentChannel * __cdecl MarketDealerAgentChannelManager::acquire(unsigned int)
{
    LIFT_STUB(0x15f7e0);
}

// 0x15f8b0
bool __cdecl MarketDealerAgentChannelManager::Send(short, ::Packet const *)
{
    LIFT_STUB(0x15f8b0);
}

// 0x15f9a0
void __cdecl MarketDealerAgentChannelManager::SendReserveSale(::Pc *, unsigned __int64, char, __int64, int, int)
{
    LIFT_STUB(0x15f9a0);
}

// 0x15fba0
void __cdecl MarketDealerAgentChannelManager::SendCancelSaleReservation(::Pc *, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x15fba0);
}

// 0x15fce0
void __cdecl MarketDealerAgentChannelManager::SendRegisterSale(::Pc *, __int64, unsigned __int64, unsigned __int64, int, ::MarketDealerAgentChannelManager::SaleItem)
{
    LIFT_STUB(0x15fce0);
}

// 0x15ff50
void __cdecl MarketDealerAgentChannelManager::SendUpdateSalePrice(::Pc *, unsigned __int64, __int64)
{
    LIFT_STUB(0x15ff50);
}

// 0x1600a0
void __cdecl MarketDealerAgentChannelManager::SendAbandonSale(::Pc *, unsigned __int64)
{
    LIFT_STUB(0x1600a0);
}

// 0x160310
void __cdecl MarketDealerAgentChannelManager::SendReserveBid(::Pc *, unsigned __int64, unsigned __int64, __int64)
{
    LIFT_STUB(0x160310);
}

// 0x1604f0
void __cdecl MarketDealerAgentChannelManager::SendCancelBidReservation(::Pc *, unsigned __int64, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x1604f0);
}

// 0x160640
void __cdecl MarketDealerAgentChannelManager::SendRegisterBid(::Pc *, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x160640);
}

// 0x1607a0
void __cdecl MarketDealerAgentChannelManager::SendUpdateBidPrice(::Pc *, unsigned __int64, unsigned __int64, unsigned __int64, __int64)
{
    LIFT_STUB(0x1607a0);
}

// 0x160920
void __cdecl MarketDealerAgentChannelManager::SendAbandonBid(::Pc *, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x160920);
}

// 0x160dd0
void __cdecl MarketDealerAgentChannelManager::SendReservePurchase(::Pc *, unsigned __int64, unsigned __int64, __int64)
{
    LIFT_STUB(0x160dd0);
}

// 0x160fb0
void __cdecl MarketDealerAgentChannelManager::SendCancelPurchaseReservation(::Pc *, unsigned __int64, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x160fb0);
}

// 0x161100
void __cdecl MarketDealerAgentChannelManager::SendRegisterPurchase(::Pc *, unsigned __int64, unsigned __int64, unsigned __int64, unsigned __int64)
{
    LIFT_STUB(0x161100);
}

// 0x161260
void __cdecl MarketDealerAgentChannelManager::SendRetrieveSaleList(::Pc *, char, char, __int64, char)
{
    LIFT_STUB(0x161260);
}

// 0x1613e0
void __cdecl MarketDealerAgentChannelManager::SendRetrieveBidList(::Pc *)
{
    LIFT_STUB(0x1613e0);
}

// 0x161520
void __cdecl MarketDealerAgentChannelManager::SendRetrieveBidRankStatus(::Pc *, __int64 *const, int)
{
    LIFT_STUB(0x161520);
}

// 0x1617f0
bool __cdecl MarketDealerAgentChannelManager::SendRetrieveReservationList(short, unsigned __int64, __int64)
{
    LIFT_STUB(0x1617f0);
}
