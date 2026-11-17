// PostContext.obj (PostOfficeDaemon PDB). Layouts from include/pdb/PostOfficeDaemon/types.h.
#pragma once
#include <stddef.h>
#include <map>
#include "RefCntObject.h"
#include "Lock.h"
#include "StlMemory.h"

class FragmentPacket;

// types.h:1335. The member names of the guid part come from the decompiler (id1..id4).
union id128
{
    struct
    {
        unsigned long id1;
        unsigned short id2;
        unsigned short id3;
        unsigned char id4[8];
    } guid;
    unsigned long long id[2];
};
static_assert(sizeof(id128) == 0x10, "sizeof id128");

class PostInfo
{
public:
    PostInfo();                           // 0x11140
    bool CheckValidityPostData();         // 0x11290

    long long _postId;
    long long _invoiceId;
    char _postType;
    char _deliveryReason;
    long long _postHint;
    id128 _reservedHint;
    char _senderServiceType;
    short _senderWid;
    long long _senderPcId;
    id128 _senderAccountId;
    wchar_t _senderWorldName[33];
    wchar_t _senderName[33];
    short _recipientWid;
    long long _recipientPcId;
    wchar_t _recipientName[33];
    wchar_t _postTitle[65];
    wchar_t _postMessage[1025];
    char _postStatus;
};
static_assert(sizeof(PostInfo) == 2472, "sizeof PostInfo");

class AttachedItemInfo
{
public:
    int CheckValidityItemData();          // 0x10fc0. ❓ return type (0 = valid, 1..5 = error)

    char _itemNo;
    char _itemType;
    char _itemCategory;
    long long _itemInstanceId;
    int _itemDataId;
    short _itemLevel;
    long long _itemAmount;
    wchar_t _itemXmlData[1025];
};
static_assert(sizeof(AttachedItemInfo) == 2088, "sizeof AttachedItemInfo");

class AttachedItemContext
{
public:
    AttachedItemContext& operator=(AttachedItemInfo const& rhs);  // 0x110e0

    char _itemNo;
    char _itemType;
    char _itemCategory;
    long long _itemInstanceId;
    int _itemDataId;
    short _itemLevel;
    long long _itemAmount;
    wchar_t _itemXmlData[1025];
};
static_assert(sizeof(AttachedItemContext) == 2088, "sizeof AttachedItemContext");

class PostContext : public DynamicRefCntObj
{
public:
    PostContext();                                                                       // 0x11510
    virtual ~PostContext();                                                              // 0x11590
    bool InitAttachedItemInfo(AttachedItemContext* attachedItemList, int attachedItemCount);  // 0x11620
    bool ComposeDeliveryPacket(FragmentPacket& packet);                                  // 0x116e0

    CriticalSection _lock;
    PostInfo _postInfo;
    AttachedItemContext* _attachedItemList;
    int _attachedItemCount;
};
static_assert(sizeof(PostContext) == 2552, "sizeof PostContext");
static_assert(offsetof(PostContext, _postInfo) == 0x40, "PostContext::_postInfo");
static_assert(offsetof(PostContext, _attachedItemCount) == 0x9F0, "PostContext::_attachedItemCount");

class PostContextManager
{
public:
    typedef std::map<long long, PostContext*, std::less<long long>,
                     StlAllocator<std::pair<long long const, PostContext*>, 2> > Container;  // ❓ typedef name and allocator

    bool initContextManager();                    // 0x11d10
    PostContext* GetContext(long long postId);    // 0x11ea0. Adds a reference.
    bool AddContext(PostContext* postContext);    // 0x12110
    bool RemoveContext(long long postId);         // 0x123a0

    int const _bucketCount;
    CriticalSection* _lockList;
    Container* _containerList;
    long volatile _contextCount;  // The PDB type is int. The code uses Interlocked calls on it.
};
static_assert(sizeof(PostContextManager) == 0x20, "sizeof PostContextManager");
static_assert(offsetof(PostContextManager, _contextCount) == 0x18, "PostContextManager::_contextCount");

// The users of PostDeliveryEvent include this header.
#include "PostDeliveryEvent.h"
