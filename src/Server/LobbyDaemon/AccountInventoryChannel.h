// AccountInventoryChannel.obj (LobbyDaemon PDB, 2019 + PDB). Wave 0: declarations of the stubbed functions only.
// LIFT: AccountInventoryChannel has its PDB layout (ld-18 batch 1). AccountInventorySessionHandler has no layout yet.
#pragma once
#include <stddef.h>
#include "TransactionChannel.h"

class Packet;
class Session;
union id128;
class AccountInventorySessionHandler;

class AccountInventoryChannel : public TransactionChannel
{
public:
    virtual ~AccountInventoryChannel();
    virtual bool Connect(unsigned long long, unsigned int, unsigned long, unsigned short, long, bool);  // 0x6500
    bool SendHelloReq(short version, short wid, short internalPort);  // 0x66b0
    bool SendLoginNotify(id128 const& account);  // 0x67b0
    bool SendLogoutNotify(id128 const& account);  // 0x68a0
    bool SendGetGoodsCountReq(TransactionChannel::Transaction* t, id128 const& account);  // 0x6990
    bool SendListGoodsReq(TransactionChannel::Transaction* t, id128 const& account, char languageCode);  // 0x6bd0
    bool SendTakeGoodsReq(TransactionChannel::Transaction* t, id128 const& account, unsigned long long goodsId);  // 0x6e30
    bool SendRetrieveLobbyServiceItemListReq(TransactionChannel::Transaction* t, id128 const& account, char searchType, long long searchKey);  // 0x7090
    bool SendRetrieveSingleWarehouseItemReq(TransactionChannel::Transaction* t, unsigned long long itemInstanceId, id128 const& account, unsigned long long ownerPcId);  // 0x72f0
    bool SendTryWarehouseItemConsumptionReq(TransactionChannel::Transaction* t, unsigned long long labelId, unsigned long long itemInstanceId, id128 const& account);  // 0x7590
    bool SendFinishWarehouseItemConsumptionReq(TransactionChannel::Transaction* t, unsigned long long labelId, unsigned long long itemInstanceId, id128 const& account, short result);  // 0x7810
    bool SendConsumeWarehouseItemReq(TransactionChannel::Transaction* t, unsigned long long labelId, unsigned long long itemInstanceId, id128 const& account);  // 0x7ab0
    bool SendRetrieveCharacterGoodsCountReq(TransactionChannel::Transaction* t, id128 const& account, unsigned long long characterId);  // 0x7d30

    AccountInventorySessionHandler* _handler;
    wchar_t _daemonInvalidInfoKey[129];
};
static_assert(sizeof(AccountInventoryChannel) == 0x140, "sizeof AccountInventoryChannel");
static_assert(offsetof(AccountInventoryChannel, _handler) == 0x30, "AccountInventoryChannel::_handler");
static_assert(offsetof(AccountInventoryChannel, _daemonInvalidInfoKey) == 0x38, "AccountInventoryChannel::_daemonInvalidInfoKey");

class AccountInventorySessionHandler
{
public:
    virtual bool OnAccept(Session const*) const;  // 0x8020
    virtual bool OnConnect(Session const*, bool) const;  // 0x8080
    virtual void OnClose(Session const*, bool) const;  // 0x81b0
    virtual bool PacketHandler(Session const*, Packet const*) const;  // 0x82f0
};
