// PostContext.obj (PostOfficeDaemon PDB).
// No code: FragmentPacket::FreeSize 0x10fa0 (COMDAT, in common), std::map code 0x11cc0, 0x12650, 0x126b0,
// 0x12a80, 0x1d0c0..0x1d680 (STL).
#include "PostContext.h"
#include <string.h>
#include <wchar.h>
#include <windows.h>
#include "Log.h"
#include "AlertSender.h"
#include "Memory.h"
#include "FragmentPacket.h"
#include "RelayContext.h"

#define POST_CONTEXT_FILE L"PostContext.cpp"
static wchar_t const* const MODULE_NAME = L"post context";  // PDB MODULE_NAME

#define POST_CONTEXT_CRASH(line, fmt, ...)                                       \
    do                                                                           \
    {                                                                            \
        Log::Write(Log::LT_ERROR, POST_CONTEXT_FILE, line, fmt, __VA_ARGS__);    \
        AlertSender::Write(POST_CONTEXT_FILE, line, fmt, __VA_ARGS__);           \
    } while (0)

// ---- AttachedItemInfo ----

// 0x10fc0
AttachedItemInfo::CheckResult const AttachedItemInfo::CheckValidityItemData() const
{
    if (_itemType >= 4)
        return CHECKRESULT_INVALID_ITEM_DATA;
    if (_itemCategory <= 0 || _itemCategory >= 7 || _itemAmount <= 0)
        return CHECKRESULT_INVALID_ITEM_DATA;

    switch (_itemType)
    {
    case 1:
        if (_itemCategory != 1 || _itemInstanceId != 0 || _itemDataId != 0 || _itemLevel != 0 || wcslen(_itemXmlData) != 0)
            return CHECKRESULT_INVALID_MONEY_DATA;
        break;
    case 2:
        if (_itemCategory == 1 || _itemInstanceId == 0 || _itemDataId == 0 || _itemLevel <= 0 || wcslen(_itemXmlData) != 0)
            return CHECKRESULT_INVALID_DEFAULT_ITEM_DATA;
        break;
    case 3:
        if (_itemCategory == 1 || _itemInstanceId == 0 || _itemDataId == 0 || _itemLevel <= 0)
            return CHECKRESULT_INVALID_DEFAULT_ITEM_DATA;
        if (wcslen(_itemXmlData) == 0)
            return CHECKRESULT_INVALID_CUSTOM_ITEM_DATA;
        break;
    default:
        return CHECKRESULT_NO_SUCH_ITEM_TYPE;
    }
    return CHECKRESULT_NO_ERROR;
}

// ---- AttachedItemContext ----

// 0x110e0
__declspec(noinline) AttachedItemContext& AttachedItemContext::operator=(AttachedItemInfo const& rhs)
{
    _itemNo = rhs._itemNo;
    _itemType = rhs._itemType;
    _itemCategory = rhs._itemCategory;
    _itemInstanceId = rhs._itemInstanceId;
    _itemDataId = rhs._itemDataId;
    _itemLevel = rhs._itemLevel;
    _itemAmount = rhs._itemAmount;
    wcsncpy(_itemXmlData, rhs._itemXmlData, 1025);
    return *this;
}

// ---- PostInfo ----

// 0x11140
PostInfo::PostInfo()
{
    _postId = 0;
    _invoiceId = 0;
    _postType = 0;
    _deliveryReason = 0;
    _postHint = 0;
    _reservedHint = ID128_GUID_ZERO;
    _senderServiceType = 0;
    _senderWid = 0;
    _senderPcId = 0;
    _senderAccountId = ID128_GUID_ZERO;
    memset(_senderWorldName, 0, sizeof(_senderWorldName));
    memset(_senderName, 0, sizeof(_senderName));
    _recipientWid = 0;
    _recipientPcId = 0;
    memset(_recipientName, 0, sizeof(_recipientName));
    memset(_postTitle, 0, sizeof(_postTitle));
    memset(_postMessage, 0, sizeof(_postMessage));
    _postStatus = 0;
}

// 0x11290
bool PostInfo::CheckValidityPostData()
{
    if (_postType >= 3 || _deliveryReason <= 0)
        return false;
    if (_senderServiceType <= 0 || _senderServiceType >= 8)
        return false;
    if (_senderWid == 0 || _recipientWid == 0 || _recipientPcId == 0 || wcslen(_recipientName) == 0)
        return false;

    if (_senderServiceType == 3)
    {
        if (_invoiceId != 0 || _senderPcId == 0)
            return false;
        if (_senderAccountId.id[0] == ID128_GUID_ZERO.id[0] && _senderAccountId.id[1] == ID128_GUID_ZERO.id[1])
            return false;
        if (wcslen(_senderWorldName) == 0)
            return false;
        return wcslen(_senderName) != 0;
    }

    if (_invoiceId == 0)
        return false;

#define POST_HAS_ACCOUNT_ID (_senderAccountId.id[0] != ID128_GUID_ZERO.id[0] || _senderAccountId.id[1] != ID128_GUID_ZERO.id[1])
    switch (_senderServiceType)
    {
    case 1:
        if (_deliveryReason >= 3 || _postHint == 0 || _senderPcId != 0 || POST_HAS_ACCOUNT_ID || wcslen(_senderWorldName) != 0)
            return false;
        return wcslen(_senderName) == 0;
    case 2:
        if (_deliveryReason >= 8 || _postHint == 0 || _senderPcId != 0 || POST_HAS_ACCOUNT_ID || wcslen(_senderWorldName) != 0 ||
            wcslen(_senderName) != 0 || wcslen(_postTitle) == 0)
            return false;
        return wcslen(_postMessage) != 0;
    case 7:
        if (_deliveryReason >= 6 || _senderPcId != 0 || POST_HAS_ACCOUNT_ID || wcslen(_senderWorldName) != 0 ||
            wcslen(_senderName) != 0)
            return false;
        return wcslen(_postMessage) != 0;
    default:
        return true;
    }
#undef POST_HAS_ACCOUNT_ID
}

// ---- PostContext ----

// 0x11510
PostContext::PostContext() : _attachedItemList(nullptr), _attachedItemCount(0)
{
}

// 0x11590
PostContext::~PostContext()
{
    if (_attachedItemList != nullptr)
    {
        Memory::_Manager[2]->Free(_attachedItemList, POST_CONTEXT_FILE, 233);
        _attachedItemList = nullptr;
    }
}

// 0x11620
bool PostContext::InitAttachedItemInfo(AttachedItemContext* attachedItemList, int attachedItemCount)
{
    if (attachedItemList != nullptr && attachedItemCount > 0)
    {
        _attachedItemList = attachedItemList;
        _attachedItemCount = attachedItemCount;
        return true;
    }
    POST_CONTEXT_CRASH(239, L"== CRASH == [%s], %s; invalid parameter, attachedItemList:0x%p, attachedItemCount:%d",
                       MODULE_NAME, L"PostContext::InitAttachedItemInfo", attachedItemList, attachedItemCount);
    return false;
}

// 0x116e0
bool PostContext::ComposeDeliveryPacket(FragmentPacket& packet)
{
    PostInfo const& info = _postInfo;
    id128 reservedHint = info._reservedHint;
    id128 senderAccountId = info._senderAccountId;

    if (!packet.Compose(17, info._postId, static_cast<int>(info._postType), static_cast<int>(info._deliveryReason),
                        info._invoiceId, info._postHint, &reservedHint, static_cast<int>(info._senderServiceType),
                        static_cast<int>(info._senderWid), info._senderPcId, &senderAccountId, info._senderWorldName,
                        info._senderName, static_cast<int>(info._recipientWid), info._recipientPcId, info._recipientName,
                        info._postTitle, info._postMessage))
    {
        Log::Write(Log::LT_ERROR, POST_CONTEXT_FILE, 269, L"[%s], %s; failed to compose post body packet, postId:0x%I64X",
                   MODULE_NAME, L"PostContext::ComposeDeliveryPacket", info._postId);
        return false;
    }

    Log::Write(Log::LT_DEBUG, POST_CONTEXT_FILE, 272,
               L"[%s], %s; composed post body packet, postId:0x%I64X, invoiceId:0x%I64X, postType:%d, deliveryReason:%d, "
               L"postHint:0x%I64X, reservedHint:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, senderServiceType:%d, "
               L"senderWid:%d, senderPcId:0x%I64X, senderAccountId:%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X, "
               L"senderWorldName:%s, senderName:%s, recipientWid:%d, recipientPcId:0x%I64X, recipientName:%s, postTitle:%s, "
               L"postMessage:%s",
               MODULE_NAME, L"PostContext::ComposeDeliveryPacket", info._postId, info._invoiceId,
               static_cast<int>(info._postType), static_cast<int>(info._deliveryReason), info._postHint,
               reservedHint.guid.id1, reservedHint.guid.id2, reservedHint.guid.id3, reservedHint.guid.id4[0],
               reservedHint.guid.id4[1], reservedHint.guid.id4[2], reservedHint.guid.id4[3], reservedHint.guid.id4[4],
               reservedHint.guid.id4[5], reservedHint.guid.id4[6], reservedHint.guid.id4[7],
               static_cast<int>(info._senderServiceType), static_cast<int>(info._senderWid), info._senderPcId,
               senderAccountId.guid.id1, senderAccountId.guid.id2, senderAccountId.guid.id3, senderAccountId.guid.id4[0],
               senderAccountId.guid.id4[1], senderAccountId.guid.id4[2], senderAccountId.guid.id4[3],
               senderAccountId.guid.id4[4], senderAccountId.guid.id4[5], senderAccountId.guid.id4[6],
               senderAccountId.guid.id4[7], info._senderWorldName, info._senderName, static_cast<int>(info._recipientWid),
               info._recipientPcId, info._recipientName, info._postTitle, info._postMessage);

    packet.StartRepeat();
    for (int i = 0; i < _attachedItemCount; ++i)
    {
        AttachedItemContext const& item = _attachedItemList[i];
        if (static_cast<unsigned short>(packet.FreeSize()) <= 2 * (wcslen(item._itemXmlData) + 1) + 24)
            packet.packet.Allocate(&packet.composer);

        if (!packet.Compose(7, static_cast<int>(item._itemType), static_cast<int>(item._itemCategory), item._itemInstanceId,
                            static_cast<int>(item._itemDataId), static_cast<int>(item._itemLevel), item._itemAmount,
                            item._itemXmlData))
        {
            Log::Write(Log::LT_ERROR, POST_CONTEXT_FILE, 294, L"[%s], %s; failed to compose post attachment packet, postId:0x%I64X",
                       MODULE_NAME, L"PostContext::ComposeDeliveryPacket", info._postId);
            return false;
        }

        Log::Write(Log::LT_DEBUG, POST_CONTEXT_FILE, 297,
                   L"[%s], %s; composed post attachment packet, postId:0x%I64X, itemNo:%d, itemType:%d, itemCategory:%d, "
                   L"itemInstanceId:0x%I64X, itemDataId:%d, itemLevel:%d, itemAmount:%I64d, itemXmlData:%s",
                   MODULE_NAME, L"PostContext::ComposeDeliveryPacket", info._postId, static_cast<int>(item._itemNo),
                   static_cast<int>(item._itemType), static_cast<int>(item._itemCategory), item._itemInstanceId,
                   item._itemDataId, static_cast<int>(item._itemLevel), item._itemAmount, item._itemXmlData);
        packet.IncRepeatCount();
    }
    packet.composer.PopRepeatCount();
    return true;
}

// ---- PostContextManager ----

// 0x11d10
bool PostContextManager::initContextManager()
{
    if (_lockList != nullptr || _containerList != nullptr)
    {
        POST_CONTEXT_CRASH(342, L"== CRASH == [%s], %s; post context manager is already initialized, lockList:0x%p, containerList:0x%p",
                           MODULE_NAME, L"PostContextManager::initContextManager", _lockList, _containerList);
        return false;
    }
    _lockList = liftArrayNew(CriticalSection, _bucketCount, POST_CONTEXT_FILE, 346);
    _containerList = liftArrayNew(Container, _bucketCount, POST_CONTEXT_FILE, 347);
    return true;
}

// 0x11ea0
PostContext* PostContextManager::GetContext(long long postId)
{
    if (postId == 0)
    {
        POST_CONTEXT_CRASH(355, L"== CRASH == [%s], %s; invalid parameter, postId:0x%I64X",
                           MODULE_NAME, L"PostContextManager::GetContext", 0LL);
        return nullptr;
    }
    if (_lockList == nullptr || _containerList == nullptr)
    {
        POST_CONTEXT_CRASH(359, L"== CRASH == [%s], %s; invalid post context manager, lockList:0x%p, containerList:0x%p",
                           MODULE_NAME, L"PostContextManager::GetContext", _lockList, _containerList);
        return nullptr;
    }

    int const index = static_cast<int>(postId % _bucketCount);
    PostContext* postContext = nullptr;
    _lockList[index].Enter();
    Container::iterator it = _containerList[index].find(postId);
    if (it != _containerList[index].end())
    {
        postContext = it->second;
        if (postContext == nullptr)
        {
            _lockList[index].Leave();
            POST_CONTEXT_CRASH(372, L"== CRASH == [%s], %s; post context is null, postId:0x%I64X, postContext:0x%p",
                               MODULE_NAME, L"PostContextManager::GetContext", postId, nullptr);
            return nullptr;
        }
        postContext->addReferenceCount(POST_CONTEXT_FILE, 375);
    }
    _lockList[index].Leave();
    return postContext;
}

// 0x12110
bool PostContextManager::AddContext(PostContext* postContext)
{
    if (postContext == nullptr)
    {
        POST_CONTEXT_CRASH(385, L"== CRASH == [%s], %s; invalid parameter, postContext:0x%p",
                           MODULE_NAME, L"PostContextManager::AddContext", nullptr);
        return false;
    }
    if (_lockList == nullptr || _containerList == nullptr)
    {
        POST_CONTEXT_CRASH(389, L"== CRASH == [%s], %s; invalid post context manager, lockList:0x%p, containerList:0x%p",
                           MODULE_NAME, L"PostContextManager::AddContext", _lockList, _containerList);
        return false;
    }
    long long const postId = postContext->_postInfo._postId;
    if (postId == 0)
    {
        POST_CONTEXT_CRASH(395, L"== CRASH == [%s], %s; invalid post Id, postId:0x%I64X",
                           MODULE_NAME, L"PostContextManager::AddContext", 0LL);
        return false;
    }

    int const index = static_cast<int>(postId % _bucketCount);
    _lockList[index].Enter();
    if (!_containerList[index].insert(std::pair<long long, PostContext*>(postId, postContext)).second)
    {
        _lockList[index].Leave();
        Log::Write(Log::LT_ERROR, POST_CONTEXT_FILE, 406, L"[%s], %s; failed to add post context, postId:0x%I64X",
                   MODULE_NAME, L"PostContextManager::AddContext", postId);
        return false;
    }
    postContext->addReferenceCount(POST_CONTEXT_FILE, 410);
    InterlockedIncrement(&_contextCount);
    _lockList[index].Leave();
    return true;
}

// 0x123a0
bool PostContextManager::RemoveContext(long long postId)
{
    if (postId == 0)
    {
        POST_CONTEXT_CRASH(422, L"== CRASH == [%s], %s; invalid parameter, postId:0x%I64X",
                           MODULE_NAME, L"PostContextManager::RemoveContext", 0LL);
        return false;
    }
    if (_lockList == nullptr || _containerList == nullptr)
    {
        POST_CONTEXT_CRASH(426, L"== CRASH == [%s], %s; invalid post context manager, lockList:0x%p, containerList:0x%p",
                           MODULE_NAME, L"PostContextManager::RemoveContext", _lockList, _containerList);
        return false;
    }

    int const index = static_cast<int>(postId % _bucketCount);
    _lockList[index].Enter();
    Container::iterator it = _containerList[index].find(postId);
    if (it == _containerList[index].end())
    {
        _lockList[index].Leave();
        Log::Write(Log::LT_ERROR, POST_CONTEXT_FILE, 436, L"[%s], %s; no such post context, postId:0x%I64X",
                   MODULE_NAME, L"PostContextManager::RemoveContext", postId);
        return false;
    }
    PostContext* const postContext = it->second;
    if (postContext == nullptr)
    {
        _lockList[index].Leave();
        POST_CONTEXT_CRASH(443, L"== CRASH == [%s], %s; post context is null, postId:0x%I64X, postContext:0x%p",
                           MODULE_NAME, L"PostContextManager::RemoveContext", postId, nullptr);
        return false;
    }
    _containerList[index].erase(it);
    postContext->removeReferenceCount(POST_CONTEXT_FILE, 448);
    InterlockedDecrement(&_contextCount);
    _lockList[index].Leave();
    return true;
}
