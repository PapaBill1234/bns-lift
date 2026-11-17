// PostOfficeDB.obj (PostOfficeDaemon PDB).
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <string.h>
#include <new>
#include "PostOfficeDB.h"
#include "Db.h"
#include "Log.h"
#include "AlertSender.h"
#include "Memory.h"
#include "PostContext.h"
#include "PostOfficeDaemon.h"
#include "UnsentPostContext.h"

#define POSTOFFICEDB_FILE L"PostOfficeDB.cpp"
#define POSTOFFICEDB_TAG L"postoffice db"

#define FAIL_ACQUIRE L"[%s], %s; failed to acquire transaction, dbId:%d"
#define FAIL_PREPARE L"[%s], %s; failed to prepare sql, query:%s"
#define FAIL_BIND L"[%s], %s; failed to bind parameter"
#define FAIL_EXECUTE L"[%s], %s; failed to execute stored procedure, dbRetValue:%d"
#define FAIL_FETCH L"[%s], %s; failed to fetch"
#define FAIL_ADD_CRASH L"== CRASH == [%s], %s; exception occurred; failed to add post context, postId:0x%I64X"
#define FAIL_ADD_EXISTS L"[%s], %s; exception occurred; failed to add post context; post context already exists, postId:0x%I64X"
#define FAIL_REGISTER_UNSENT L"[%s], %s; exception occurred; failed to register unsent post, recipientWid:%u, postId:0x%I64X"
#define FAIL_REMOVE_CRASH L"== CRASH == [%s], %s; exception occurred; failed to remove post context, postId:0x%I64X"

namespace
{
unsigned int const kDbId = 1;
unsigned long long const kNullData = static_cast<unsigned long long>(-1);  // SQL_NULL_DATA
unsigned long long const kNts = static_cast<unsigned long long>(-3);       // SQL_NTS
int const kMaxAttachedItem = 10;
int const kItemColumnCount = 7;

wchar_t* Query(wchar_t const* text) { return const_cast<wchar_t*>(text); }

// ❓ Not a PDB function. The 87 column binds are inlined in each loader. This keeps the order and types.
bool BindPostColumns(DbTransaction* tran, PostInfo& postInfo, AttachedItemInfo* items, unsigned long long* postLen,
                     unsigned long long (*itemLen)[kItemColumnCount])
{
    if (!tran->BindCol(1, &postInfo._postId, 0, SQL_C_SBIGINT, &postLen[0])) return false;
    if (!tran->BindCol(2, &postInfo._invoiceId, 0, SQL_C_SBIGINT, &postLen[1])) return false;
    if (!tran->BindCol(3, &postInfo._postType, 0, SQL_C_STINYINT, &postLen[2])) return false;
    if (!tran->BindCol(4, &postInfo._deliveryReason, 0, SQL_C_STINYINT, &postLen[3])) return false;
    if (!tran->BindCol(5, &postInfo._postHint, 0, SQL_C_SBIGINT, &postLen[4])) return false;
    if (!tran->BindCol(6, &postInfo._senderServiceType, 0, SQL_C_STINYINT, &postLen[5])) return false;
    if (!tran->BindCol(7, &postInfo._senderWid, 0, SQL_C_SSHORT, &postLen[6])) return false;
    if (!tran->BindCol(8, &postInfo._senderPcId, 0, SQL_C_SBIGINT, &postLen[7])) return false;
    if (!tran->BindCol(9, &postInfo._senderAccountId, 0, SQL_C_GUID, &postLen[8])) return false;
    if (!tran->BindCol(10, postInfo._senderWorldName, 66, SQL_C_WCHAR, &postLen[9])) return false;
    if (!tran->BindCol(11, postInfo._senderName, 66, SQL_C_WCHAR, &postLen[10])) return false;
    if (!tran->BindCol(12, &postInfo._recipientWid, 0, SQL_C_SSHORT, &postLen[11])) return false;
    if (!tran->BindCol(13, &postInfo._recipientPcId, 0, SQL_C_SBIGINT, &postLen[12])) return false;
    if (!tran->BindCol(14, postInfo._recipientName, 66, SQL_C_WCHAR, &postLen[13])) return false;
    if (!tran->BindCol(15, postInfo._postTitle, 130, SQL_C_WCHAR, &postLen[14])) return false;
    if (!tran->BindCol(16, postInfo._postMessage, 2050, SQL_C_WCHAR, &postLen[15])) return false;
    if (!tran->BindCol(17, &postInfo._postStatus, 0, SQL_C_STINYINT, &postLen[16])) return false;
    for (int i = 0; i < kMaxAttachedItem; ++i)
    {
        unsigned int const column = 18 + kItemColumnCount * i;
        AttachedItemInfo& item = items[i];
        if (!tran->BindCol(column + 0, &item._itemType, 0, SQL_C_STINYINT, &itemLen[i][0])) return false;
        if (!tran->BindCol(column + 1, &item._itemCategory, 0, SQL_C_STINYINT, &itemLen[i][1])) return false;
        if (!tran->BindCol(column + 2, &item._itemInstanceId, 0, SQL_C_SBIGINT, &itemLen[i][2])) return false;
        if (!tran->BindCol(column + 3, &item._itemDataId, 0, SQL_C_SLONG, &itemLen[i][3])) return false;
        if (!tran->BindCol(column + 4, &item._itemLevel, 0, SQL_C_SSHORT, &itemLen[i][4])) return false;
        if (!tran->BindCol(column + 5, &item._itemAmount, 0, SQL_C_SBIGINT, &itemLen[i][5])) return false;
        if (!tran->BindCol(column + 6, item._itemXmlData, 0x802, SQL_C_WCHAR, &itemLen[i][6])) return false;
    }
    return true;
}

void ClearRow(PostInfo& postInfo, AttachedItemInfo* items)
{
    memset(&postInfo, 0, sizeof(postInfo));
    memset(items, 0, sizeof(AttachedItemInfo) * kMaxAttachedItem);
}

// ❓ Not a PDB function. Inlined in each loader: allocate the PostContext and copy the fetched row.
PostContext* MakePostContext(PostInfo const& postInfo, AttachedItemInfo* items,
                             unsigned long long (*itemLen)[kItemColumnCount], int contextLine, int itemLine)
{
    PostContext* postContext = nullptr;
    void* const memory = Memory::_Manager[2]->Alloc(sizeof(PostContext), POSTOFFICEDB_FILE, contextLine);
    if (memory != nullptr)
        postContext = ::new (memory) PostContext();
    // BUG: 0x14e50 no null check after the PostContext Alloc (same in all loaders).
    memcpy(&postContext->_postInfo, &postInfo, sizeof(PostInfo));
    for (int i = 0; i < kMaxAttachedItem; ++i)
    {
        if (itemLen[i][0] == kNullData)
            break;
        items[i]._itemNo = static_cast<char>(i + 1);
        ++postContext->_attachedItemCount;
    }
    if (postContext->_attachedItemCount > 0)
    {
        int const count = postContext->_attachedItemCount;
        // ❓ new AttachedItemContext[count]. The +8 is the array count slot, but the code uses the raw pointer.
        AttachedItemContext* list = static_cast<AttachedItemContext*>(Memory::_Manager[2]->Alloc(
            sizeof(AttachedItemContext) * static_cast<long long>(count) + 8, POSTOFFICEDB_FILE, itemLine));
        if (list != nullptr)
        {
            for (int i = 0; i < count; ++i)
                memset(&list[i], 0, sizeof(AttachedItemContext));
        }
        postContext->_attachedItemList = list;
        // BUG: 0x14e50 no null check after the item list Alloc.
        for (int i = 0; i < count; ++i)
            postContext->_attachedItemList[i] = items[i];
    }
    return postContext;
}
}  // namespace

// 0x14e00
AutoDbTran::~AutoDbTran()
{
    if (Tran != nullptr)
    {
        if (TimeoutSec != 10)
            SQLSetStmtAttrW(Tran->StmtHandle, SQL_QUERY_TIMEOUT,
                            reinterpret_cast<SQLPOINTER>(static_cast<long long>(TimeoutSec)), 0);
        Db::ReleaseTransaction(Tran);
        Tran = nullptr;
    }
}

// 0x14e50
bool PostOfficeDB::LoadPostList(int* dbRetValue)
{
    wchar_t const* const fn = L"PostOfficeDB::LoadPostList";
    unsigned long long paramLen[1] = {0};
    unsigned long long postLen[17] = {0};
    unsigned long long itemLen[kMaxAttachedItem][kItemColumnCount] = {{0}};
    PostInfo postInfo;
    AttachedItemInfo attachedItemInfo[kMaxAttachedItem];
    memset(attachedItemInfo, 0, sizeof(attachedItemInfo));

    AutoDbTran tran(kDbId);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 29, FAIL_ACQUIRE, POSTOFFICEDB_TAG, fn, kDbId);
        return false;
    }
    tran.TimeoutSec = 0;
    SQLSetStmtAttrW(tran.Tran->StmtHandle, SQL_QUERY_TIMEOUT, nullptr, 0);

    wchar_t const* const query = L"{?=CALL dbo.usp_LoadPostList}";
    if (!tran.Tran->Prepare(Query(query)))
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 35, FAIL_PREPARE, POSTOFFICEDB_TAG, fn, query);
        return false;
    }
    if (!tran.Tran->BindParam(1, SQL_PARAM_OUTPUT, dbRetValue, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramLen[0]) ||
        !BindPostColumns(tran.Tran, postInfo, attachedItemInfo, postLen, itemLen))
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 150, FAIL_BIND, POSTOFFICEDB_TAG, fn);
        return false;
    }
    if (!tran.Tran->Execute())
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 88, FAIL_EXECUTE, POSTOFFICEDB_TAG, fn, *dbRetValue);
        return false;
    }

    for (;;)
    {
        ClearRow(postInfo, attachedItemInfo);
        int const result = tran.Tran->Fetch(0);  // ❓ argument
        if (result == -1)
        {
            Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 103, FAIL_FETCH, POSTOFFICEDB_TAG, fn);
            return false;
        }
        if (result == 0)
            break;

        PostContext* const postContext = MakePostContext(postInfo, attachedItemInfo, itemLen, 109, 121);
        PostOfficeDaemon* const daemon = PostOfficeDaemon::_instance;
        if (!daemon->_postContextManager->AddContext(postContext))
        {
            Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 127, FAIL_ADD_CRASH, POSTOFFICEDB_TAG, fn, postInfo._postId);
            AlertSender::Write(POSTOFFICEDB_FILE, 127, FAIL_ADD_CRASH, POSTOFFICEDB_TAG, fn, postInfo._postId);
            postContext->removeReferenceCount(POSTOFFICEDB_FILE, 128);
            continue;
        }
        postContext->removeReferenceCount(POSTOFFICEDB_FILE, 132);
        if (!daemon->_unsentPostContextManager->RegisterUnsentPost(postInfo._recipientWid, postInfo._postId, true))
        {
            Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 135, FAIL_REGISTER_UNSENT, POSTOFFICEDB_TAG, fn,
                       static_cast<unsigned int>(postInfo._recipientWid), postInfo._postId);
            if (!daemon->_postContextManager->RemoveContext(postInfo._postId))
            {
                Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 138, FAIL_REMOVE_CRASH, POSTOFFICEDB_TAG, fn,
                           postInfo._postId);
                AlertSender::Write(POSTOFFICEDB_FILE, 138, FAIL_REMOVE_CRASH, POSTOFFICEDB_TAG, fn, postInfo._postId);
            }
        }
    }
    return *dbRetValue == 0;
}

// 0x15fa0
bool PostOfficeDB::LoadSinglePost(int* dbRetValue, long long postId)
{
    wchar_t const* const fn = L"PostOfficeDB::LoadSinglePost";
    unsigned long long paramLen[2] = {0, 0};
    unsigned long long postLen[17] = {0};
    unsigned long long itemLen[kMaxAttachedItem][kItemColumnCount] = {{0}};
    PostInfo postInfo;
    AttachedItemInfo attachedItemInfo[kMaxAttachedItem];
    memset(attachedItemInfo, 0, sizeof(attachedItemInfo));

    AutoDbTran tran(kDbId);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 158, FAIL_ACQUIRE, POSTOFFICEDB_TAG, fn, kDbId);
        return false;
    }
    wchar_t const* const query = L"{?=CALL dbo.usp_LoadSinglePost(?)}";
    if (!tran.Tran->Prepare(Query(query)))
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 164, FAIL_PREPARE, POSTOFFICEDB_TAG, fn, query);
        return false;
    }
    if (!tran.Tran->BindParam(1, SQL_PARAM_OUTPUT, dbRetValue, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramLen[0]) ||
        !tran.Tran->BindParam(2, SQL_PARAM_INPUT, &postId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[1]) ||
        !BindPostColumns(tran.Tran, postInfo, attachedItemInfo, postLen, itemLen))
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 271, FAIL_BIND, POSTOFFICEDB_TAG, fn);
        return false;
    }
    if (!tran.Tran->Execute())
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 219, FAIL_EXECUTE, POSTOFFICEDB_TAG, fn, *dbRetValue);
        return false;
    }

    ClearRow(postInfo, attachedItemInfo);
    int const result = tran.Tran->Fetch(0);  // ❓ argument
    if (result == -1)
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 228, FAIL_FETCH, POSTOFFICEDB_TAG, fn);
        return false;
    }
    if (result == 0)
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 232, L"[%s], %s; there is no such post, postId:0x%I64X",
                   POSTOFFICEDB_TAG, fn, postId);
        return false;
    }
    if (*dbRetValue != 0)
        return false;

    PostContext* const postContext = MakePostContext(postInfo, attachedItemInfo, itemLen, 242, 254);
    if (!PostOfficeDaemon::_instance->_postContextManager->AddContext(postContext))
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 260, FAIL_ADD_CRASH, POSTOFFICEDB_TAG, fn, postInfo._postId);
        AlertSender::Write(POSTOFFICEDB_FILE, 260, FAIL_ADD_CRASH, POSTOFFICEDB_TAG, fn, postInfo._postId);
        postContext->removeReferenceCount(POSTOFFICEDB_FILE, 261);
        return false;
    }
    postContext->removeReferenceCount(POSTOFFICEDB_FILE, 265);
    return true;
}

#define Q10 L"?,?,?,?,?,?,?,?,?,?,"

// 0x16f20
bool PostOfficeDB::RegisterPost(int* dbRetValue, PostInfo* postInfo, AttachedItemContext* const attachedItemList,
                                unsigned int attachedItemCount)
{
    wchar_t const* const fn = L"PostOfficeDB::RegisterPost";
    if (attachedItemCount > static_cast<unsigned int>(kMaxAttachedItem))
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 278, L"== CRASH == [%s], %s; invalid parameter, attachedItemCount:%d",
                   POSTOFFICEDB_TAG, fn, attachedItemCount);
        AlertSender::Write(POSTOFFICEDB_FILE, 278, L"== CRASH == [%s], %s; invalid parameter, attachedItemCount:%d",
                           POSTOFFICEDB_TAG, fn, attachedItemCount);
        return false;
    }
    if (attachedItemCount > 0 && attachedItemList == nullptr)
    {
        // BUG: 0x16f20 logs the error but does not return. The code continues with a null list.
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 283, L"== CRASH == [%s], %s; invalid parameter, attachedItemList:0x%p",
                   POSTOFFICEDB_TAG, fn, static_cast<void*>(nullptr));
        AlertSender::Write(POSTOFFICEDB_FILE, 283, L"== CRASH == [%s], %s; invalid parameter, attachedItemList:0x%p",
                           POSTOFFICEDB_TAG, fn, static_cast<void*>(nullptr));
    }

    AutoDbTran tran(kDbId);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 290, FAIL_ACQUIRE, POSTOFFICEDB_TAG, fn, kDbId);
        return false;
    }
    wchar_t const* const query =
        L"{?=CALL dbo.usp_RegisterPost(" Q10 Q10 Q10 Q10 Q10 Q10 Q10 Q10 L"?,?,?,?,?,?)}";
    if (!tran.Tran->Prepare(Query(query)))
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 306, FAIL_PREPARE, POSTOFFICEDB_TAG, fn, query);
        return false;
    }

    unsigned long long retLen = 0;
    unsigned long long postLen[16] = {0};
    unsigned long long itemLen[kMaxAttachedItem][kItemColumnCount] = {{0}};
    postLen[13] = kNts;
    if (postInfo->_invoiceId == 0) postLen[1] = kNullData;
    if (postInfo->_postHint == 0) postLen[4] = kNullData;
    if (postInfo->_senderPcId == 0) postLen[7] = kNullData;
    if (postInfo->_senderAccountId.id[0] == 0 && postInfo->_senderAccountId.id[1] == 0) postLen[8] = kNullData;
    postLen[9] = postInfo->_senderWorldName[0] == L'\0' ? kNullData : kNts;
    postLen[10] = postInfo->_senderName[0] == L'\0' ? kNullData : kNts;
    postLen[14] = postInfo->_postTitle[0] == L'\0' ? kNullData : kNts;
    postLen[15] = postInfo->_postMessage[0] == L'\0' ? kNullData : kNts;

    DbTransaction* const t = tran.Tran;
    bool bound =
        t->BindParam(1, SQL_PARAM_OUTPUT, dbRetValue, 0, 0, SQL_INTEGER, SQL_C_SLONG, &retLen) &&
        t->BindParam(2, SQL_PARAM_OUTPUT, &postInfo->_postId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &postLen[0]) &&
        t->BindParam(3, SQL_PARAM_INPUT, &postInfo->_invoiceId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &postLen[1]) &&
        t->BindParam(4, SQL_PARAM_INPUT, &postInfo->_postType, 0, 0, SQL_TINYINT, SQL_C_STINYINT, &postLen[2]) &&
        t->BindParam(5, SQL_PARAM_INPUT, &postInfo->_deliveryReason, 0, 0, SQL_TINYINT, SQL_C_STINYINT, &postLen[3]) &&
        t->BindParam(6, SQL_PARAM_INPUT, &postInfo->_postHint, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &postLen[4]) &&
        t->BindParam(7, SQL_PARAM_INPUT, &postInfo->_senderServiceType, 0, 0, SQL_TINYINT, SQL_C_STINYINT,
                     &postLen[5]) &&
        t->BindParam(8, SQL_PARAM_INPUT, &postInfo->_senderWid, 0, 0, SQL_SMALLINT, SQL_C_SSHORT, &postLen[6]) &&
        t->BindParam(9, SQL_PARAM_INPUT, &postInfo->_senderPcId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &postLen[7]) &&
        t->BindParam(10, SQL_PARAM_INPUT, &postInfo->_senderAccountId, 0, 0, SQL_GUID, SQL_C_GUID, &postLen[8]) &&
        t->BindParam(11, SQL_PARAM_INPUT, postInfo->_senderWorldName, 0x42, 0x20, SQL_WVARCHAR, SQL_C_WCHAR,
                     &postLen[9]) &&
        t->BindParam(12, SQL_PARAM_INPUT, postInfo->_senderName, 0x42, 0x20, SQL_WVARCHAR, SQL_C_WCHAR, &postLen[10]) &&
        t->BindParam(13, SQL_PARAM_INPUT, &postInfo->_recipientWid, 0, 0, SQL_SMALLINT, SQL_C_SSHORT, &postLen[11]) &&
        t->BindParam(14, SQL_PARAM_INPUT, &postInfo->_recipientPcId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &postLen[12]) &&
        t->BindParam(15, SQL_PARAM_INPUT, postInfo->_recipientName, 0x42, 0x20, SQL_WVARCHAR, SQL_C_WCHAR,
                     &postLen[13]) &&
        t->BindParam(16, SQL_PARAM_INPUT, postInfo->_postTitle, 0x82, 0x40, SQL_WVARCHAR, SQL_C_WCHAR, &postLen[14]) &&
        t->BindParam(17, SQL_PARAM_INPUT, postInfo->_postMessage, 0x802, 0x400, SQL_WVARCHAR, SQL_C_WCHAR,
                     &postLen[15]);

    for (int i = 0; bound && i < kMaxAttachedItem; ++i)
    {
        unsigned int const index = 18 + kItemColumnCount * i;
        unsigned long long* const len = itemLen[i];
        if (static_cast<unsigned int>(i) < attachedItemCount)
        {
            AttachedItemContext& item = attachedItemList[i];
            if (item._itemInstanceId == 0) len[2] = kNullData;
            if (item._itemDataId == 0) len[3] = kNullData;
            if (item._itemLevel == 0) len[4] = kNullData;
            len[6] = item._itemXmlData[0] == L'\0' ? kNullData : kNts;
            bound = t->BindParam(index + 0, SQL_PARAM_INPUT, &item._itemType, 0, 0, SQL_TINYINT, SQL_C_STINYINT, &len[0]) &&
                    t->BindParam(index + 1, SQL_PARAM_INPUT, &item._itemCategory, 0, 0, SQL_TINYINT, SQL_C_STINYINT,
                                 &len[1]) &&
                    t->BindParam(index + 2, SQL_PARAM_INPUT, &item._itemInstanceId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT,
                                 &len[2]) &&
                    t->BindParam(index + 3, SQL_PARAM_INPUT, &item._itemDataId, 0, 0, SQL_INTEGER, SQL_C_SLONG, &len[3]) &&
                    t->BindParam(index + 4, SQL_PARAM_INPUT, &item._itemLevel, 0, 0, SQL_SMALLINT, SQL_C_SSHORT, &len[4]) &&
                    t->BindParam(index + 5, SQL_PARAM_INPUT, &item._itemAmount, 0, 0, SQL_BIGINT, SQL_C_SBIGINT,
                                 &len[5]) &&
                    t->BindParam(index + 6, SQL_PARAM_INPUT, item._itemXmlData, 0x802, 0x400, SQL_WVARCHAR, SQL_C_WCHAR,
                                 &len[6]);
        }
        else
        {
            for (int c = 0; c < kItemColumnCount; ++c)
                len[c] = kNullData;
            bound = t->BindParam(index + 0, SQL_PARAM_INPUT, nullptr, 0, 0, SQL_TINYINT, SQL_C_STINYINT, &len[0]) &&
                    t->BindParam(index + 1, SQL_PARAM_INPUT, nullptr, 0, 0, SQL_TINYINT, SQL_C_STINYINT, &len[1]) &&
                    t->BindParam(index + 2, SQL_PARAM_INPUT, nullptr, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &len[2]) &&
                    t->BindParam(index + 3, SQL_PARAM_INPUT, nullptr, 0, 0, SQL_INTEGER, SQL_C_SLONG, &len[3]) &&
                    t->BindParam(index + 4, SQL_PARAM_INPUT, nullptr, 0, 0, SQL_SMALLINT, SQL_C_SSHORT, &len[4]) &&
                    t->BindParam(index + 5, SQL_PARAM_INPUT, nullptr, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &len[5]) &&
                    t->BindParam(index + 6, SQL_PARAM_INPUT, nullptr, 0, 0x400, SQL_WVARCHAR, SQL_C_WCHAR, &len[6]);
        }
    }
    if (!bound)
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 404, FAIL_BIND, POSTOFFICEDB_TAG, fn);
        return false;
    }
    if (!t->Execute())
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 394, FAIL_EXECUTE, POSTOFFICEDB_TAG, fn, *dbRetValue);
        return false;
    }
    return *dbRetValue == 0;
}

#undef Q10

namespace
{
// ❓ Not a PDB function. The two UpdateStatusToDelivery* functions have the same body (inlined twice).
bool UpdatePostStatus(int* dbRetValue, long long postId, wchar_t const* fn, wchar_t const* query, int acquireLine,
                      int prepareLine, int bindLine, int executeLine)
{
    unsigned long long paramLen[2] = {0, 0};
    AutoDbTran tran(kDbId);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, acquireLine, FAIL_ACQUIRE, POSTOFFICEDB_TAG, fn, kDbId);
        return false;
    }
    if (!tran.Tran->Prepare(Query(query)))
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, prepareLine, FAIL_PREPARE, POSTOFFICEDB_TAG, fn, query);
        return false;
    }
    if (!tran.Tran->BindParam(1, SQL_PARAM_OUTPUT, dbRetValue, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramLen[0]) ||
        !tran.Tran->BindParam(2, SQL_PARAM_INPUT, &postId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[1]))
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, bindLine, FAIL_BIND, POSTOFFICEDB_TAG, fn);
        return false;
    }
    if (!tran.Tran->Execute())
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, executeLine, FAIL_EXECUTE, POSTOFFICEDB_TAG, fn, *dbRetValue);
        return false;
    }
    return *dbRetValue == 0;
}
}  // namespace

// 0x17bf0
bool PostOfficeDB::UpdateStatusToDeliverySuccess(int* dbRetValue, long long postId)
{
    return UpdatePostStatus(dbRetValue, postId, L"PostOfficeDB::UpdateStatusToDeliverySuccess",
                            L"{?=CALL dbo.usp_UpdateStatusToDeliverySuccess(?)}", 412, 418, 447, 437);
}

// 0x17e00
bool PostOfficeDB::UpdateStatusToDeliveryFailure(int* dbRetValue, long long postId)
{
    return UpdatePostStatus(dbRetValue, postId, L"PostOfficeDB::UpdateStatusToDeliveryFailure",
                            L"{?=CALL dbo.usp_UpdateStatusToDeliveryFailure(?)}", 455, 461, 490, 480);
}

// 0x18010
bool PostOfficeDB::LoadRetryReadySinglePost(int* dbRetValue, long long postId, long long invoiceId,
                                            long long recipientPcId)
{
    wchar_t const* const fn = L"PostOfficeDB::LoadRetryReadySinglePost";
    unsigned long long paramLen[4] = {0, 0, 0, 0};
    unsigned long long postLen[17] = {0};
    unsigned long long itemLen[kMaxAttachedItem][kItemColumnCount] = {{0}};
    PostInfo postInfo;
    AttachedItemInfo attachedItemInfo[kMaxAttachedItem];
    memset(attachedItemInfo, 0, sizeof(attachedItemInfo));

    AutoDbTran tran(kDbId);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 498, FAIL_ACQUIRE, POSTOFFICEDB_TAG, fn, kDbId);
        return false;
    }
    wchar_t const* const query = L"{?=CALL dbo.usp_LoadRetryReadySinglePost(?,?,?)}";
    if (!tran.Tran->Prepare(Query(query)))
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 504, FAIL_PREPARE, POSTOFFICEDB_TAG, fn, query);
        return false;
    }
    if (invoiceId == 0)
        paramLen[2] = kNullData;
    if (!tran.Tran->BindParam(1, SQL_PARAM_OUTPUT, dbRetValue, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramLen[0]) ||
        !tran.Tran->BindParam(2, SQL_PARAM_INPUT, &postId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[1]) ||
        !tran.Tran->BindParam(3, SQL_PARAM_INPUT, &invoiceId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[2]) ||
        !tran.Tran->BindParam(4, SQL_PARAM_INPUT, &recipientPcId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[3]) ||
        !BindPostColumns(tran.Tran, postInfo, attachedItemInfo, postLen, itemLen))
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 628, FAIL_BIND, POSTOFFICEDB_TAG, fn);
        return false;
    }
    if (!tran.Tran->Execute())
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 567, FAIL_EXECUTE, POSTOFFICEDB_TAG, fn, *dbRetValue);
        return false;
    }

    ClearRow(postInfo, attachedItemInfo);
    int const result = tran.Tran->Fetch(0);  // ❓ argument
    if (result == -1)
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 576, FAIL_FETCH, POSTOFFICEDB_TAG, fn);
        return false;
    }
    if (result == 0)
    {
        // ❓ The tail of the text is cut in the pseudocode. "recipientPcId:0x%I64X" is a guess.
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 580,
                   L"[%s], %s; there is no such post, postId:0x%I64X, invoiceId:0x%I64X, recipientPcId:0x%I64X",
                   POSTOFFICEDB_TAG, fn, postId, invoiceId, recipientPcId);
        return false;
    }
    if (*dbRetValue != 0)
        return false;

    PostContext* const postContext = MakePostContext(postInfo, attachedItemInfo, itemLen, 590, 602);
    PostOfficeDaemon* const daemon = PostOfficeDaemon::_instance;
    if (!daemon->_postContextManager->AddContext(postContext))
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 608, FAIL_ADD_EXISTS, POSTOFFICEDB_TAG, fn, postInfo._postId);
        postContext->removeReferenceCount(POSTOFFICEDB_FILE, 609);
        return false;
    }
    postContext->removeReferenceCount(POSTOFFICEDB_FILE, 613);
    if (daemon->_unsentPostContextManager->RegisterUnsentPost(postInfo._recipientWid, postInfo._postId, true))
        return true;
    Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 616, FAIL_REGISTER_UNSENT, POSTOFFICEDB_TAG, fn,
               static_cast<unsigned int>(postInfo._recipientWid), postInfo._postId);
    if (!daemon->_postContextManager->RemoveContext(postInfo._postId))
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 619, FAIL_REMOVE_CRASH, POSTOFFICEDB_TAG, fn, postInfo._postId);
        AlertSender::Write(POSTOFFICEDB_FILE, 619, FAIL_REMOVE_CRASH, POSTOFFICEDB_TAG, fn, postInfo._postId);
    }
    return false;
}

// 0x190f0
bool PostOfficeDB::LoadRetryReadyPostList(int* dbRetValue)
{
    wchar_t const* const fn = L"PostOfficeDB::LoadRetryReadyPostList";
    unsigned long long paramLen[1] = {0};
    unsigned long long postLen[17] = {0};
    unsigned long long itemLen[kMaxAttachedItem][kItemColumnCount] = {{0}};
    PostInfo postInfo;
    AttachedItemInfo attachedItemInfo[kMaxAttachedItem];
    memset(attachedItemInfo, 0, sizeof(attachedItemInfo));

    AutoDbTran tran(kDbId);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 636, FAIL_ACQUIRE, POSTOFFICEDB_TAG, fn, kDbId);
        return false;
    }
    tran.TimeoutSec = 0;
    SQLSetStmtAttrW(tran.Tran->StmtHandle, SQL_QUERY_TIMEOUT, nullptr, 0);

    wchar_t const* const query = L"{?=CALL dbo.usp_LoadRetryReadyPostList}";
    if (!tran.Tran->Prepare(Query(query)))
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 642, FAIL_PREPARE, POSTOFFICEDB_TAG, fn, query);
        return false;
    }
    if (!tran.Tran->BindParam(1, SQL_PARAM_OUTPUT, dbRetValue, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramLen[0]) ||
        !BindPostColumns(tran.Tran, postInfo, attachedItemInfo, postLen, itemLen))
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 757, FAIL_BIND, POSTOFFICEDB_TAG, fn);
        return false;
    }
    if (!tran.Tran->Execute())
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 695, FAIL_EXECUTE, POSTOFFICEDB_TAG, fn, *dbRetValue);
        return false;
    }

    for (;;)
    {
        ClearRow(postInfo, attachedItemInfo);
        int const result = tran.Tran->Fetch(0);  // ❓ argument
        if (result == -1)
        {
            Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 710, FAIL_FETCH, POSTOFFICEDB_TAG, fn);
            return false;
        }
        if (result == 0)
            break;

        PostContext* const postContext = MakePostContext(postInfo, attachedItemInfo, itemLen, 716, 728);
        PostOfficeDaemon* const daemon = PostOfficeDaemon::_instance;
        if (!daemon->_postContextManager->AddContext(postContext))
        {
            Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 734, FAIL_ADD_EXISTS, POSTOFFICEDB_TAG, fn, postInfo._postId);
            postContext->removeReferenceCount(POSTOFFICEDB_FILE, 735);
            continue;
        }
        postContext->removeReferenceCount(POSTOFFICEDB_FILE, 739);
        if (!daemon->_unsentPostContextManager->RegisterUnsentPost(postInfo._recipientWid, postInfo._postId, true))
        {
            Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 742, FAIL_REGISTER_UNSENT, POSTOFFICEDB_TAG, fn,
                       static_cast<unsigned int>(postInfo._recipientWid), postInfo._postId);
            if (!daemon->_postContextManager->RemoveContext(postInfo._postId))
            {
                Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 745, FAIL_REMOVE_CRASH, POSTOFFICEDB_TAG, fn,
                           postInfo._postId);
                AlertSender::Write(POSTOFFICEDB_FILE, 745, FAIL_REMOVE_CRASH, POSTOFFICEDB_TAG, fn, postInfo._postId);
            }
        }
    }
    return *dbRetValue == 0;
}

// 0x1a220
bool PostOfficeDB::UpdateStatusToRetryReady(int* dbRetValue, long long postId, long long invoiceId,
                                            long long recipientPcId)
{
    wchar_t const* const fn = L"PostOfficeDB::UpdateStatusToRetryReady";
    unsigned long long paramLen[4] = {0, 0, 0, 0};
    AutoDbTran tran(kDbId);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 765, FAIL_ACQUIRE, POSTOFFICEDB_TAG, fn, kDbId);
        return false;
    }
    wchar_t const* const query = L"{?=CALL dbo.usp_UpdateStatusToRetryReady(?,?,?)}";
    if (!tran.Tran->Prepare(Query(query)))
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 771, FAIL_PREPARE, POSTOFFICEDB_TAG, fn, query);
        return false;
    }
    if (invoiceId == 0)
        paramLen[2] = kNullData;
    if (!tran.Tran->BindParam(1, SQL_PARAM_OUTPUT, dbRetValue, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramLen[0]) ||
        !tran.Tran->BindParam(2, SQL_PARAM_INPUT, &postId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[1]) ||
        !tran.Tran->BindParam(3, SQL_PARAM_INPUT, &invoiceId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[2]) ||
        !tran.Tran->BindParam(4, SQL_PARAM_INPUT, &recipientPcId, 0, 0, SQL_BIGINT, SQL_C_SBIGINT, &paramLen[3]))
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 808, FAIL_BIND, POSTOFFICEDB_TAG, fn);
        return false;
    }
    if (!tran.Tran->Execute())
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 798, FAIL_EXECUTE, POSTOFFICEDB_TAG, fn, *dbRetValue);
        return false;
    }
    return *dbRetValue == 0;
}

// 0x1a500
bool PostOfficeDB::ResetAllDeliveryFailurePost(int* dbRetValue)
{
    wchar_t const* const fn = L"PostOfficeDB::ResetAllDeliveryFailurePost";
    unsigned long long paramLen[1] = {0};
    AutoDbTran tran(kDbId);
    if (tran.Tran == nullptr)
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 816, FAIL_ACQUIRE, POSTOFFICEDB_TAG, fn, kDbId);
        return false;
    }
    wchar_t const* const query = L"{?=CALL dbo.usp_ResetAllDeliveryFailurePost}";
    if (!tran.Tran->Prepare(Query(query)))
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 822, FAIL_PREPARE, POSTOFFICEDB_TAG, fn, query);
        return false;
    }
    if (!tran.Tran->BindParam(1, SQL_PARAM_OUTPUT, dbRetValue, 0, 0, SQL_INTEGER, SQL_C_SLONG, &paramLen[0]))
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 849, FAIL_BIND, POSTOFFICEDB_TAG, fn);
        return false;
    }
    if (!tran.Tran->Execute())
    {
        Log::Write(Log::LT_ERROR, POSTOFFICEDB_FILE, 839, FAIL_EXECUTE, POSTOFFICEDB_TAG, fn, *dbRetValue);
        return false;
    }
    return *dbRetValue == 0;
}
