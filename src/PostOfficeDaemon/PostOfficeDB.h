// PostOfficeDB.obj (PostOfficeDaemon PDB). Card lift-postofficedaemon-5 lifts the bodies.
#pragma once

class PostInfo;
class AttachedItemContext;

class PostOfficeDB
{
public:
    static bool RegisterPost(int* dbRetValue, PostInfo* postInfo, AttachedItemContext* const attachedItemList,
                             unsigned int attachedItemCount);                                             // 0x16f20
    static bool LoadRetryReadySinglePost(int* dbRetValue, long long postId, long long invoiceId,
                                         long long recipientPcId);                                        // 0x18010
    static bool LoadRetryReadyPostList(int* dbRetValue);                                                  // 0x190f0
    static bool UpdateStatusToRetryReady(int* dbRetValue, long long postId, long long invoiceId,
                                         long long recipientPcId);                                        // 0x1a220
    static bool ResetAllDeliveryFailurePost(int* dbRetValue);                                             // 0x1a500
};

// UnsentPostContext.obj. Card lift-postofficedaemon-5 lifts the bodies.
#include "Lock.h"

class UnsentPostContextList;

class UnsentPostContextManager
{
public:
    bool RegisterUnsentPost(unsigned short wid, long long postId, bool hasPostContext);  // 0xd190

    CriticalSection _reloadLock;
    UnsentPostContextList** _containerList[33];
    int _arrayBoundary[33][2];
};
