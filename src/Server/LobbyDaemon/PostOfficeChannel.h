// PostOfficeChannel.obj (LobbyDaemon PDB, 2019 + PDB). Layouts from include/pdb/LobbyDaemon/types.h.
#pragma once
#include <stddef.h>
#include "Channel.h"
#include "Lock.h"
#include "StringUtil.h"
#include "TransactionChannel.h"

class Packet;
class Session;

struct PostOfficeSenderInfo
{
public:
    char serviceType;
    short wid;
    unsigned long long pcid;
    id128 accountId;
    wchar_t worldName[33];
    wchar_t name[33];
};
static_assert(sizeof(PostOfficeSenderInfo) == 0xA8, "sizeof PostOfficeSenderInfo");
static_assert(offsetof(PostOfficeSenderInfo, serviceType) == 0x0, "PostOfficeSenderInfo::serviceType");
static_assert(offsetof(PostOfficeSenderInfo, wid) == 0x2, "PostOfficeSenderInfo::wid");
static_assert(offsetof(PostOfficeSenderInfo, pcid) == 0x8, "PostOfficeSenderInfo::pcid");
static_assert(offsetof(PostOfficeSenderInfo, accountId) == 0x10, "PostOfficeSenderInfo::accountId");
static_assert(offsetof(PostOfficeSenderInfo, worldName) == 0x20, "PostOfficeSenderInfo::worldName");
static_assert(offsetof(PostOfficeSenderInfo, name) == 0x62, "PostOfficeSenderInfo::name");

struct PostOfficeRecipientInfo
{
public:
    short wid;
    unsigned long long pcid;
    wchar_t name[33];
};
static_assert(sizeof(PostOfficeRecipientInfo) == 0x58, "sizeof PostOfficeRecipientInfo");
static_assert(offsetof(PostOfficeRecipientInfo, wid) == 0x0, "PostOfficeRecipientInfo::wid");
static_assert(offsetof(PostOfficeRecipientInfo, pcid) == 0x8, "PostOfficeRecipientInfo::pcid");
static_assert(offsetof(PostOfficeRecipientInfo, name) == 0x10, "PostOfficeRecipientInfo::name");

struct PostOfficeAttachedItemInfo
{
public:
    char itemType;
    char category;
    unsigned long long instanceId;
    unsigned int dataId;
    short level;
    long long amount;
    wchar_t itemXmlData[1025];
};
static_assert(sizeof(PostOfficeAttachedItemInfo) == 0x828, "sizeof PostOfficeAttachedItemInfo");
static_assert(offsetof(PostOfficeAttachedItemInfo, itemType) == 0x0, "PostOfficeAttachedItemInfo::itemType");
static_assert(offsetof(PostOfficeAttachedItemInfo, category) == 0x1, "PostOfficeAttachedItemInfo::category");
static_assert(offsetof(PostOfficeAttachedItemInfo, instanceId) == 0x8, "PostOfficeAttachedItemInfo::instanceId");
static_assert(offsetof(PostOfficeAttachedItemInfo, dataId) == 0x10, "PostOfficeAttachedItemInfo::dataId");
static_assert(offsetof(PostOfficeAttachedItemInfo, level) == 0x14, "PostOfficeAttachedItemInfo::level");
static_assert(offsetof(PostOfficeAttachedItemInfo, amount) == 0x18, "PostOfficeAttachedItemInfo::amount");
static_assert(offsetof(PostOfficeAttachedItemInfo, itemXmlData) == 0x20, "PostOfficeAttachedItemInfo::itemXmlData");

class PostOfficeSessionHandler;

class PostOfficeChannel : public TransactionChannel
{
public:
    // LIFT: the PDB ctor has no out-of-line body. It is inline in LobbyDaemon::onStart (0x9dca0).
    // The scalar deleting destructor is 0x99340 (LobbyDaemon.obj).
    explicit PostOfficeChannel(PostOfficeSessionHandler* handler) : _handler(handler) {}
    virtual bool Connect(unsigned long long, unsigned int, unsigned long, unsigned short, long, bool);  // 0x639f0
    bool SendHelloReq();  // 0x63ba0
    // LIFT: The PDB has 12 parameters. Call sites give deliveryReason = 1, postHint = 0, reservedHint = ID128_GUID_ZERO
    // and postTitle = L"" (constants in the binary at 0x63cb0, so LTCG removes the 4 parameters).
    bool SendRegisterPostReq(TransactionChannel::Transaction* t, unsigned long long invoiceId, char postType,
                             char deliveryReason, unsigned long long postHint, id128 const& reservedHint,
                             PostOfficeSenderInfo const& senderInfo, PostOfficeRecipientInfo const& recipientInfo,
                             wchar_t* postTitle, wchar_t* postMessage, PostOfficeAttachedItemInfo const* itemInfoList,
                             int itemInfoCount);  // 0x63cb0

    PostOfficeSessionHandler* _handler;
    wchar_t _daemonInvalidInfoKey[129];
};
static_assert(sizeof(PostOfficeChannel) == 0x140, "sizeof PostOfficeChannel");
static_assert(offsetof(PostOfficeChannel, _handler) == 0x30, "PostOfficeChannel::_handler");
static_assert(offsetof(PostOfficeChannel, _daemonInvalidInfoKey) == 0x38, "PostOfficeChannel::_daemonInvalidInfoKey");

class PostOfficeSessionHandler : public SessionHandler
{
public:
    virtual bool OnAccept(Session const*) const;  // 0x64170
    virtual bool OnConnect(Session const*, bool) const;  // 0x641d0
    virtual void OnClose(Session const*, bool) const;  // 0x642e0
    virtual bool PacketHandler(Session const*, Packet const*) const;  // 0x64420

    CriticalSection _connectLock;
};
static_assert(sizeof(PostOfficeSessionHandler) == 0x30, "sizeof PostOfficeSessionHandler");
static_assert(offsetof(PostOfficeSessionHandler, _connectLock) == 0x8, "PostOfficeSessionHandler::_connectLock");
