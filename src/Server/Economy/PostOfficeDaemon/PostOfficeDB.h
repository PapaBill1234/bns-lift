// PostOfficeDB.obj (PostOfficeDaemon PDB). Card lift-postofficedaemon-5 lifts the bodies.
#pragma once

#include "Db.h"

class PostInfo;
class AttachedItemContext;

// RAII holder of a DbTransaction. The ctor is inlined in the callers.
struct AutoDbTran
{
    // LIFT: Inlined ctor.
    explicit AutoDbTran(unsigned int dbId) : Tran(Db::AllocTransaction(dbId)), TimeoutSec(10) {}
    ~AutoDbTran();  // 0x14e00

    DbTransaction* Tran;
    int TimeoutSec;
};

class PostOfficeDB
{
public:
    static bool LoadPostList(int* dbRetValue);                                                            // 0x14e50
    static bool LoadSinglePost(int* dbRetValue, long long postId);                                        // 0x15fa0
    static bool RegisterPost(int* dbRetValue, PostInfo* postInfo, AttachedItemContext* const attachedItemList,
                             unsigned int attachedItemCount);                                             // 0x16f20
    static bool LoadRetryReadySinglePost(int* dbRetValue, long long postId, long long invoiceId,
                                         long long recipientPcId);                                        // 0x18010
    static bool LoadRetryReadyPostList(int* dbRetValue);                                                  // 0x190f0
    static bool UpdateStatusToRetryReady(int* dbRetValue, long long postId, long long invoiceId,
                                         long long recipientPcId);                                        // 0x1a220
    static bool ResetAllDeliveryFailurePost(int* dbRetValue);                                             // 0x1a500
    static bool UpdateStatusToDeliverySuccess(int* dbRetValue, long long postId);                         // 0x17bf0
    static bool UpdateStatusToDeliveryFailure(int* dbRetValue, long long postId);                         // 0x17e00
};

// The users of UnsentPostContextManager include this header. Keep them working.
#include "UnsentPostContext.h"
