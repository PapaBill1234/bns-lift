// AuctionEscrow.obj (LobbyDaemon PDB, 2019 + PDB).
#include "AuctionEscrow.h"
#include "CliSession.h"
#include "Log.h"
#include <stdarg.h>
#include <wchar.h>

#pragma comment(linker, "/INCLUDE:?GetDeliveryPostMessage@AuctionEscrow@@SA_NPEAU_StsMsgRequestGameAuctionDeliver@StsMsgLib@@PEA_WH@Z")  // LIFT: keep until the caller is lifted (0x13630).
#pragma comment(linker, "/INCLUDE:?GetRollbackEscrowPostMessage@AuctionEscrow@@SA_NPEAUTryAuctionEscrowRollbackOutParam@LobbyDB@@PEA_WH@Z")  // LIFT: keep until the caller is lifted (0x14770).

// 0x135e0
bool __printXml(wchar_t*& __lob_json_buf, wchar_t* __lob_json_end, wchar_t const* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    int count = _vsnwprintf_s(__lob_json_buf, __lob_json_end - __lob_json_buf, static_cast<size_t>(-1), fmt, args);
    va_end(args);
    if (count < 0)
        return false;
    __lob_json_buf += count;
    return true;
}

// LIFT: the original inlines the checks and literal copies at 0x13630 and 0x14770.
template <size_t N>
static __forceinline bool appendXml(wchar_t*& __xmlbuf, wchar_t* end, wchar_t const (&text)[N])
{
    if (end - __xmlbuf < static_cast<ptrdiff_t>(N))
        return false;
    wcscpy_s(__xmlbuf, end - __xmlbuf, text);
    __xmlbuf += N - 1;
    return true;
}

// LIFT: the package, price, and fee macros are inline in the originals (0x13630, 0x14770).
static __forceinline bool appendPackage(wchar_t*& __xmlbuf, wchar_t* end, long long amount)
{
    return appendXml(__xmlbuf, end, L"<Package>") &&
           appendXml(__xmlbuf, end, L"<Item") &&
           appendXml(__xmlbuf, end, L" ID=\"") && __printXml(__xmlbuf, end, L"%d", 0) &&
           appendXml(__xmlbuf, end, L"\"") &&
           appendXml(__xmlbuf, end, L" LV=\"") && __printXml(__xmlbuf, end, L"%d", 0) &&
           appendXml(__xmlbuf, end, L"\"") &&
           appendXml(__xmlbuf, end, L" Amount=\"") && __printXml(__xmlbuf, end, L"%I64d", amount) &&
           appendXml(__xmlbuf, end, L"\"") &&
           appendXml(__xmlbuf, end, L"/>") &&
           appendXml(__xmlbuf, end, L"</Package>");
}

static __forceinline bool appendPrice(wchar_t*& __xmlbuf, wchar_t* end, unsigned long long sale, unsigned long long bid)
{
    return appendXml(__xmlbuf, end, L"<Price") &&
           appendXml(__xmlbuf, end, L" Sale=\"") && __printXml(__xmlbuf, end, L"%I64u", sale) &&
           appendXml(__xmlbuf, end, L"\"") &&
           appendXml(__xmlbuf, end, L" Bid=\"") && __printXml(__xmlbuf, end, L"%I64u", bid) &&
           appendXml(__xmlbuf, end, L"\"") &&
           appendXml(__xmlbuf, end, L"/>");
}

static __forceinline bool appendFee(wchar_t*& __xmlbuf, wchar_t* end, unsigned long long currency)
{
    return appendXml(__xmlbuf, end, L"<Fee") &&
           appendXml(__xmlbuf, end, L" Currency=\"") && __printXml(__xmlbuf, end, L"%I64u", currency) &&
           appendXml(__xmlbuf, end, L"\"") &&
           appendXml(__xmlbuf, end, L" GameItem=\"") && __printXml(__xmlbuf, end, L"%I64u", 0ULL) &&
           appendXml(__xmlbuf, end, L"\"") &&
           appendXml(__xmlbuf, end, L"/>");
}

// 0x13630
bool AuctionEscrow::GetDeliveryPostMessage(StsMsgLib::_StsMsgRequestGameAuctionDeliver* param,
                                          wchar_t* buf, int bufsizeInWords)
{
    if (param == nullptr || buf == nullptr || bufsizeInWords <= 0)
    {
        Log::Write(Log::LT_ERROR, L"AuctionEscrow.cpp", 111,
                   L"[auction-escrow], get delivery post message fail; invalid param");
        TLobbyError = LOBERR_INVALID_PARAMETER;
        return false;
    }

    // LIFT: LTCG folds bufsizeInWords to 1025 at the original call site (0x13630).
    typedef StsMsgLib::_StsMsgRequestGameAuctionDeliver Request;
    wchar_t* __xmlbuf = buf;
    wchar_t* end = buf + bufsizeInWords;
    TLobbyError = LOBERR_INSUFFICIENT_BUFFER;
    if (param->AuctionMessage.eAuctionEventType == Request::AUCTIONEVENTTYPE_SUCCESS)
    {
        if (param->AuctionMessage.eAuctionUserType != Request::AUCTIONUSERTYPE_SELLER &&
            param->AuctionMessage.eAuctionUserType != Request::AUCTIONUSERTYPE_BUYER)
            return false;
    }
    else if (param->AuctionMessage.eAuctionEventType != Request::AUCTIONEVENTTYPE_EXPIRED &&
             param->AuctionMessage.eAuctionEventType != Request::AUCTIONEVENTTYPE_CANCELED)
    {
        TLobbyError = LOBERR_INVALID_PARAMETER;
        return false;
    }

    if (!appendXml(__xmlbuf, end, L"<Auction>") || !appendPackage(__xmlbuf, end, param->AuctionMessage.nQuantity))
        return false;

    if (param->AuctionMessage.eAuctionEventType == Request::AUCTIONEVENTTYPE_SUCCESS)
    {
        if (!appendPrice(__xmlbuf, end, param->AuctionMessage.nSalePrice, param->AuctionMessage.nBidPrice) ||
            !appendFee(__xmlbuf, end, param->AuctionMessage.nCurrencyFee))
            return false;
    }
    else if (!appendPrice(__xmlbuf, end, param->AuctionMessage.nSalePrice, 0) || !appendFee(__xmlbuf, end, 0))
    {
        return false;
    }

    if (param->AuctionMessage.eAuctionEventType == Request::AUCTIONEVENTTYPE_SUCCESS &&
        param->AuctionMessage.eAuctionUserType == Request::AUCTIONUSERTYPE_SELLER)
    {
        if (!appendXml(__xmlbuf, end, L"<Delivery") || !appendXml(__xmlbuf, end, L" Income=\"") ||
            !__printXml(__xmlbuf, end, L"%I64u", static_cast<unsigned long long>(param->AuctionMessage.nSalePrice) -
                                                 static_cast<unsigned long long>(param->AuctionMessage.nCurrencyFee)))
            return false;
    }
    else
    {
        if (param->nDeliveryItemCount <= 0 || param->pDeliveryItem == nullptr)
        {
            TLobbyError = LOBERR_INVALID_PARAMETER;
            return false;
        }
        if (!appendXml(__xmlbuf, end, L"<Delivery") || !appendXml(__xmlbuf, end, L" GameItem=\"") ||
            !__printXml(__xmlbuf, end, L"%I64d", param->pDeliveryItem->nQuantity))
            return false;
    }

    return appendXml(__xmlbuf, end, L"\"") &&
           appendXml(__xmlbuf, end, L"/>") &&
           appendXml(__xmlbuf, end, L"<Time") &&
           appendXml(__xmlbuf, end, L" Registered=\"") &&
           __printXml(__xmlbuf, end, L"%I64u", static_cast<unsigned long long>(param->AuctionMessage.tRegistered)) &&
           appendXml(__xmlbuf, end, L"\"") &&
           appendXml(__xmlbuf, end, L"/>") &&
           appendXml(__xmlbuf, end, L"</Auction>");
}

// 0x14770
bool AuctionEscrow::GetRollbackEscrowPostMessage(LobbyDB::TryAuctionEscrowRollbackOutParam* param,
                                                wchar_t* buf, int bufsizeInWords)
{
    if (param == nullptr || buf == nullptr || bufsizeInWords <= 0)
    {
        Log::Write(Log::LT_ERROR, L"AuctionEscrow.cpp", 270,
                   L"[auction-escrow], get rollback escrow post message fail; invalid param");
        TLobbyError = LOBERR_INVALID_PARAMETER;
        return false;
    }

    // LIFT: LTCG folds bufsizeInWords to 1025 at the original call site (0x14770).
    wchar_t* __xmlbuf = buf;
    wchar_t* end = buf + bufsizeInWords;
    TLobbyError = LOBERR_INSUFFICIENT_BUFFER;
    return appendXml(__xmlbuf, end, L"<Auction>") &&
           appendPackage(__xmlbuf, end, param->gameMoneyAmount) &&
           appendFee(__xmlbuf, end, 0) &&
           appendXml(__xmlbuf, end, L"<Delivery") &&
           appendXml(__xmlbuf, end, L" GameItem=\"") &&
           __printXml(__xmlbuf, end, L"%I64d", param->gameMoneyAmount) &&
           appendXml(__xmlbuf, end, L"\"") &&
           appendXml(__xmlbuf, end, L"/>") &&
           appendXml(__xmlbuf, end, L"</Auction>");
}
